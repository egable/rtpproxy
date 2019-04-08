/* Auto-generated by genfincode.sh - DO NOT EDIT! */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "rtpp_types.h"
#include "rtpp_debug.h"
#include "rtpp_command_rcache.h"
#include "rtpp_command_rcache_fin.h"
static void rcache_insert_fin(void *pub) {
    fprintf(stderr, "Method rtpp_cmd_rcache@%p::insert (rcache_insert) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
static void rcache_lookup_fin(void *pub) {
    fprintf(stderr, "Method rtpp_cmd_rcache@%p::lookup (rcache_lookup) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
static void rcache_shutdown_fin(void *pub) {
    fprintf(stderr, "Method rtpp_cmd_rcache@%p::shutdown (rcache_shutdown) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
void rtpp_cmd_rcache_fin(struct rtpp_cmd_rcache *pub) {
    RTPP_DBG_ASSERT(pub->insert != (rcache_insert_t)&rcache_insert_fin);
    pub->insert = (rcache_insert_t)&rcache_insert_fin;
    RTPP_DBG_ASSERT(pub->lookup != (rcache_lookup_t)&rcache_lookup_fin);
    pub->lookup = (rcache_lookup_t)&rcache_lookup_fin;
    RTPP_DBG_ASSERT(pub->shutdown != (rcache_shutdown_t)&rcache_shutdown_fin);
    pub->shutdown = (rcache_shutdown_t)&rcache_shutdown_fin;
}
#if defined(RTPP_FINTEST)
#include <assert.h>
#include <stddef.h>
#include "rtpp_mallocs.h"
#include "rtpp_refcnt.h"
#include "rtpp_linker_set.h"
#define CALL_TFIN(pub, fn) ((void (*)(typeof(pub)))((pub)->fn))(pub)

void
rtpp_cmd_rcache_fintest()
{
    int naborts_s;

    struct {
        struct rtpp_cmd_rcache pub;
    } *tp;

    naborts_s = _naborts;
    tp = rtpp_rzmalloc(sizeof(*tp), offsetof(typeof(*tp), pub.rcnt));
    assert(tp != NULL);
    assert(tp->pub.rcnt != NULL);
    CALL_SMETHOD(tp->pub.rcnt, attach, (rtpp_refcnt_dtor_t)&rtpp_cmd_rcache_fin,
      &tp->pub);
    CALL_SMETHOD(tp->pub.rcnt, decref);
    CALL_TFIN(&tp->pub, insert);
    CALL_TFIN(&tp->pub, lookup);
    CALL_TFIN(&tp->pub, shutdown);
    assert((_naborts - naborts_s) == 3);
}
const static void *_rtpp_cmd_rcache_ftp = (void *)&rtpp_cmd_rcache_fintest;
DATA_SET(rtpp_fintests, _rtpp_cmd_rcache_ftp);
#endif /* RTPP_FINTEST */
