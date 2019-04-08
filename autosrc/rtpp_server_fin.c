/* Auto-generated by genfincode_stat.sh - DO NOT EDIT! */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "rtpp_types.h"
#include "rtpp_debug.h"
#include "rtpp_server.h"
#include "rtpp_server_fin.h"
static void rtpp_server_get_fin(void *pub) {
    fprintf(stderr, "Method rtpp_server@%p::get (rtpp_server_get) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
static void rtpp_server_get_seq_fin(void *pub) {
    fprintf(stderr, "Method rtpp_server@%p::get_seq (rtpp_server_get_seq) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
static void rtpp_server_get_ssrc_fin(void *pub) {
    fprintf(stderr, "Method rtpp_server@%p::get_ssrc (rtpp_server_get_ssrc) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
static void rtpp_server_set_seq_fin(void *pub) {
    fprintf(stderr, "Method rtpp_server@%p::set_seq (rtpp_server_set_seq) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
static void rtpp_server_set_ssrc_fin(void *pub) {
    fprintf(stderr, "Method rtpp_server@%p::set_ssrc (rtpp_server_set_ssrc) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
static void rtpp_server_start_fin(void *pub) {
    fprintf(stderr, "Method rtpp_server@%p::start (rtpp_server_start) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
static const struct rtpp_server_smethods rtpp_server_smethods_fin = {
    .get = (rtpp_server_get_t)&rtpp_server_get_fin,
    .get_seq = (rtpp_server_get_seq_t)&rtpp_server_get_seq_fin,
    .get_ssrc = (rtpp_server_get_ssrc_t)&rtpp_server_get_ssrc_fin,
    .set_seq = (rtpp_server_set_seq_t)&rtpp_server_set_seq_fin,
    .set_ssrc = (rtpp_server_set_ssrc_t)&rtpp_server_set_ssrc_fin,
    .start = (rtpp_server_start_t)&rtpp_server_start_fin,
};
void rtpp_server_fin(struct rtpp_server *pub) {
    RTPP_DBG_ASSERT(pub->smethods != &rtpp_server_smethods_fin &&
      pub->smethods != NULL);
    pub->smethods = &rtpp_server_smethods_fin;
}
#if defined(RTPP_FINTEST)
#include <assert.h>
#include <stddef.h>
#include "rtpp_mallocs.h"
#include "rtpp_refcnt.h"
#include "rtpp_linker_set.h"
#define CALL_TFIN(pub, fn) ((void (*)(typeof(pub)))((pub)->smethods->fn))(pub)

void
rtpp_server_fintest()
{
    int naborts_s;

    struct {
        struct rtpp_server pub;
    } *tp;

    naborts_s = _naborts;
    tp = rtpp_rzmalloc(sizeof(*tp), offsetof(typeof(*tp), pub.rcnt));
    assert(tp != NULL);
    assert(tp->pub.rcnt != NULL);
    CALL_SMETHOD(tp->pub.rcnt, attach, (rtpp_refcnt_dtor_t)&rtpp_server_fin,
      &tp->pub);
    CALL_SMETHOD(tp->pub.rcnt, decref);
    CALL_TFIN(&tp->pub, get);
    CALL_TFIN(&tp->pub, get_seq);
    CALL_TFIN(&tp->pub, get_ssrc);
    CALL_TFIN(&tp->pub, set_seq);
    CALL_TFIN(&tp->pub, set_ssrc);
    CALL_TFIN(&tp->pub, start);
    assert((_naborts - naborts_s) == 6);
}
const static void *_rtpp_server_ftp = (void *)&rtpp_server_fintest;
DATA_SET(rtpp_fintests, _rtpp_server_ftp);
#endif /* RTPP_FINTEST */
