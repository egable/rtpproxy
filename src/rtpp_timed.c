/*
 * Copyright (c) 2015 Sippy Software, Inc., http://www.sippysoft.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include <sys/stat.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "rtpp_defines.h"
#include "rtpp_log.h"
#include "rtpp_cfg_stable.h"
#include "rtpp_types.h"
#include "rtpp_queue.h"
#include "rtpp_wi.h"
#include "rtpp_util.h"
#include "rtpp_timed.h"

struct rtpp_timed_cf {
    struct rtpp_timed_obj pub;
    struct rtpp_queue *q;
    double last_run;
    double period;
};

struct rtpp_timed_wi {
    rtpp_timed_cb_t cb_func;
    rtpp_timed_cancel_cb_t cancel_cb_func;
    void *cb_func_arg;
    double when;
};

static void rtpp_timed_destroy(struct rtpp_timed_obj *);
static struct rtpp_wi *rtpp_timed_schedule(struct rtpp_timed_obj *, double offset,
  rtpp_timed_cb_t, rtpp_timed_cancel_cb_t, void *);
static void rtpp_timed_process(struct rtpp_timed_obj *, double);
static int rtpp_timed_cancel(struct rtpp_timed_obj *, struct rtpp_wi *);

struct rtpp_timed_obj *
rtpp_timed_ctor(void)
{
    struct rtpp_timed_cf *rtcp;

    rtcp = malloc(sizeof(struct rtpp_timed_cf));
    if (rtcp == NULL) {
        return (NULL);
    }
    memset(rtcp, '\0', sizeof(struct rtpp_timed_cf));
    rtcp->q = rtpp_queue_init(1, "rtpp_timed(requests)");
    if (rtcp->q == NULL) {
        free(rtcp);
        return (NULL);
    }
    rtcp->last_run = getdtime();
    rtcp->period = 0.1;
    rtcp->pub.dtor = &rtpp_timed_destroy;
    rtcp->pub.process = &rtpp_timed_process;
    rtcp->pub.schedule = &rtpp_timed_schedule;
    rtcp->pub.cancel = &rtpp_timed_cancel;
    return (&rtcp->pub);
}

static void
rtpp_timed_destroy(struct rtpp_timed_obj *pub)
{
    struct rtpp_wi *wi;
    struct rtpp_timed_wi *wi_data;
    struct rtpp_timed_cf *rtpp_timed_cf;

    rtpp_timed_cf = (struct rtpp_timed_cf *)pub;
    while (rtpp_queue_get_length(rtpp_timed_cf->q) > 0) {
        wi = rtpp_queue_get_item(rtpp_timed_cf->q, 1);
        wi_data = rtpp_wi_data_get_ptr(wi, sizeof(struct rtpp_timed_wi));
        wi_data->cancel_cb_func(wi_data->cb_func_arg);
        rtpp_wi_free(wi);
    }

    rtpp_queue_destroy(rtpp_timed_cf->q);
    free(rtpp_timed_cf);
}


static struct rtpp_wi *
rtpp_timed_schedule(struct rtpp_timed_obj *pub, double offset, rtpp_timed_cb_t cb_func,
  rtpp_timed_cancel_cb_t cancel_cb_func, void *cb_func_arg)
{
    struct rtpp_wi *wi;
    struct rtpp_timed_wi wi_data;
    struct rtpp_timed_cf *rtpp_timed_cf;

    rtpp_timed_cf = (struct rtpp_timed_cf *)pub;
    wi_data.cb_func = cb_func;
    wi_data.cancel_cb_func = cancel_cb_func;
    wi_data.cb_func_arg = cb_func_arg;
    wi_data.when = getdtime() + offset;
    
    wi = rtpp_wi_malloc_data(&wi_data, sizeof(wi_data));
    if (wi == NULL) {
        return (NULL);
    }
    rtpp_queue_put_item(wi, rtpp_timed_cf->q);
    return (wi);
}

static int
rtpp_timed_istime(struct rtpp_wi *wi, void *ctimep)
{
    struct rtpp_timed_wi *wi_data;

    wi_data = rtpp_wi_data_get_ptr(wi, sizeof(struct rtpp_timed_wi));
    if (wi_data->when <= *(double *)ctimep)
       return (0);
    return (1);
}

static void
rtpp_timed_process(struct rtpp_timed_obj *pub, double ctime)
{
    struct rtpp_wi *wi;
    struct rtpp_timed_wi *wi_data;
    struct rtpp_timed_cf *rtcp;

    rtcp = (struct rtpp_timed_cf *)pub;
    if (rtcp->last_run + rtcp->period > ctime)
        return;

    for (;;) {
        wi = rtpp_queue_get_first_matching(rtcp->q, rtpp_timed_istime, &ctime);
        if (wi == NULL) {
            return;
        }
        wi_data = rtpp_wi_data_get_ptr(wi, sizeof(struct rtpp_timed_wi));
        wi_data->cb_func(ctime, wi_data->cb_func_arg);
        rtpp_wi_free(wi);
    }
    rtcp->last_run = ctime;
}

static int
rtpp_timed_match_wi(struct rtpp_wi *wia, void *p)
{

    struct rtpp_wi *wib;

    wib = (void *)p;
    if (wia == wib) {
        return (0);
    }
    return (1);
}

static int
rtpp_timed_cancel(struct rtpp_timed_obj *pub, struct rtpp_wi *wi)
{
    struct rtpp_wi *wim;
    struct rtpp_timed_cf *rtcp;
    struct rtpp_timed_wi *wi_data;

    rtcp = (struct rtpp_timed_cf *)pub;
    wim = rtpp_queue_get_first_matching(rtcp->q, rtpp_timed_match_wi, wi);
    if (wim == NULL) {
        return (0);
    }
    wi_data = rtpp_wi_data_get_ptr(wim, sizeof(struct rtpp_timed_wi));
    if (wi_data->cancel_cb_func != NULL) {
        wi_data->cancel_cb_func(wi_data->cb_func_arg);
    }
    rtpp_wi_free(wim);
    return (1);
}
