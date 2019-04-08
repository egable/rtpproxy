/* Auto-generated by genfincode.sh - DO NOT EDIT! */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "rtpp_types.h"
#include "rtpp_debug.h"
#include "rtpp_port_table.h"
#include "rtpp_port_table_fin.h"
static void rtpp_ptbl_get_port_fin(void *pub) {
    fprintf(stderr, "Method rtpp_port_table@%p::get_port (rtpp_ptbl_get_port) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
void rtpp_port_table_fin(struct rtpp_port_table *pub) {
    RTPP_DBG_ASSERT(pub->get_port != (rtpp_ptbl_get_port_t)&rtpp_ptbl_get_port_fin);
    pub->get_port = (rtpp_ptbl_get_port_t)&rtpp_ptbl_get_port_fin;
}
#if defined(RTPP_FINTEST)
#include <assert.h>
#include <stddef.h>
#include "rtpp_mallocs.h"
#include "rtpp_refcnt.h"
#include "rtpp_linker_set.h"
#define CALL_TFIN(pub, fn) ((void (*)(typeof(pub)))((pub)->fn))(pub)

void
rtpp_port_table_fintest()
{
    int naborts_s;

    struct {
        struct rtpp_port_table pub;
    } *tp;

    naborts_s = _naborts;
    tp = rtpp_rzmalloc(sizeof(*tp), offsetof(typeof(*tp), pub.rcnt));
    assert(tp != NULL);
    assert(tp->pub.rcnt != NULL);
    CALL_SMETHOD(tp->pub.rcnt, attach, (rtpp_refcnt_dtor_t)&rtpp_port_table_fin,
      &tp->pub);
    CALL_SMETHOD(tp->pub.rcnt, decref);
    CALL_TFIN(&tp->pub, get_port);
    assert((_naborts - naborts_s) == 1);
}
const static void *_rtpp_port_table_ftp = (void *)&rtpp_port_table_fintest;
DATA_SET(rtpp_fintests, _rtpp_port_table_ftp);
#endif /* RTPP_FINTEST */
