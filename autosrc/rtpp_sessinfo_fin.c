/* Auto-generated by genfincode.sh - DO NOT EDIT! */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "rtpp_types.h"
#include "rtpp_debug.h"
#include "rtpp_sessinfo.h"
#include "rtpp_sessinfo_fin.h"
static void rtpp_si_append_fin(void *pub) {
    fprintf(stderr, "Method rtpp_sessinfo@%p::append (rtpp_si_append) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
static void rtpp_si_remove_fin(void *pub) {
    fprintf(stderr, "Method rtpp_sessinfo@%p::remove (rtpp_si_remove) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
static void rtpp_si_sync_polltbl_fin(void *pub) {
    fprintf(stderr, "Method rtpp_sessinfo@%p::sync_polltbl (rtpp_si_sync_polltbl) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
static void rtpp_si_update_fin(void *pub) {
    fprintf(stderr, "Method rtpp_sessinfo@%p::update (rtpp_si_update) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
void rtpp_sessinfo_fin(struct rtpp_sessinfo *pub) {
    RTPP_DBG_ASSERT(pub->append != (rtpp_si_append_t)&rtpp_si_append_fin);
    pub->append = (rtpp_si_append_t)&rtpp_si_append_fin;
    RTPP_DBG_ASSERT(pub->remove != (rtpp_si_remove_t)&rtpp_si_remove_fin);
    pub->remove = (rtpp_si_remove_t)&rtpp_si_remove_fin;
    RTPP_DBG_ASSERT(pub->sync_polltbl != (rtpp_si_sync_polltbl_t)&rtpp_si_sync_polltbl_fin);
    pub->sync_polltbl = (rtpp_si_sync_polltbl_t)&rtpp_si_sync_polltbl_fin;
    RTPP_DBG_ASSERT(pub->update != (rtpp_si_update_t)&rtpp_si_update_fin);
    pub->update = (rtpp_si_update_t)&rtpp_si_update_fin;
}
#if defined(RTPP_FINTEST)
#include <assert.h>
#include <stddef.h>
#include "rtpp_mallocs.h"
#include "rtpp_refcnt.h"
#include "rtpp_linker_set.h"
#define CALL_TFIN(pub, fn) ((void (*)(typeof(pub)))((pub)->fn))(pub)

void
rtpp_sessinfo_fintest()
{
    int naborts_s;

    struct {
        struct rtpp_sessinfo pub;
    } *tp;

    naborts_s = _naborts;
    tp = rtpp_rzmalloc(sizeof(*tp), offsetof(typeof(*tp), pub.rcnt));
    assert(tp != NULL);
    assert(tp->pub.rcnt != NULL);
    CALL_SMETHOD(tp->pub.rcnt, attach, (rtpp_refcnt_dtor_t)&rtpp_sessinfo_fin,
      &tp->pub);
    CALL_SMETHOD(tp->pub.rcnt, decref);
    CALL_TFIN(&tp->pub, append);
    CALL_TFIN(&tp->pub, remove);
    CALL_TFIN(&tp->pub, sync_polltbl);
    CALL_TFIN(&tp->pub, update);
    assert((_naborts - naborts_s) == 4);
}
const static void *_rtpp_sessinfo_ftp = (void *)&rtpp_sessinfo_fintest;
DATA_SET(rtpp_fintests, _rtpp_sessinfo_ftp);
#endif /* RTPP_FINTEST */
