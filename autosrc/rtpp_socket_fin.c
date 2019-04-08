/* Auto-generated by genfincode.sh - DO NOT EDIT! */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "rtpp_types.h"
#include "rtpp_debug.h"
#include "rtpp_socket.h"
#include "rtpp_socket_fin.h"
static void rtpp_socket_bind_fin(void *pub) {
    fprintf(stderr, "Method rtpp_socket@%p::bind (rtpp_socket_bind) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
static void rtpp_socket_getfd_fin(void *pub) {
    fprintf(stderr, "Method rtpp_socket@%p::getfd (rtpp_socket_getfd) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
static void rtpp_socket_rtp_recv_fin(void *pub) {
    fprintf(stderr, "Method rtpp_socket@%p::rtp_recv (rtpp_socket_rtp_recv) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
static void rtpp_socket_send_pkt_na_fin(void *pub) {
    fprintf(stderr, "Method rtpp_socket@%p::send_pkt_na (rtpp_socket_send_pkt_na) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
static void rtpp_socket_setnonblock_fin(void *pub) {
    fprintf(stderr, "Method rtpp_socket@%p::setnonblock (rtpp_socket_setnonblock) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
static void rtpp_socket_setrbuf_fin(void *pub) {
    fprintf(stderr, "Method rtpp_socket@%p::setrbuf (rtpp_socket_setrbuf) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
static void rtpp_socket_settimestamp_fin(void *pub) {
    fprintf(stderr, "Method rtpp_socket@%p::settimestamp (rtpp_socket_settimestamp) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
static void rtpp_socket_settos_fin(void *pub) {
    fprintf(stderr, "Method rtpp_socket@%p::settos (rtpp_socket_settos) is invoked after destruction\x0a", pub);
    RTPP_AUTOTRAP();
}
void rtpp_socket_fin(struct rtpp_socket *pub) {
    RTPP_DBG_ASSERT(pub->bind != (rtpp_socket_bind_t)&rtpp_socket_bind_fin);
    pub->bind = (rtpp_socket_bind_t)&rtpp_socket_bind_fin;
    RTPP_DBG_ASSERT(pub->getfd != (rtpp_socket_getfd_t)&rtpp_socket_getfd_fin);
    pub->getfd = (rtpp_socket_getfd_t)&rtpp_socket_getfd_fin;
    RTPP_DBG_ASSERT(pub->rtp_recv != (rtpp_socket_rtp_recv_t)&rtpp_socket_rtp_recv_fin);
    pub->rtp_recv = (rtpp_socket_rtp_recv_t)&rtpp_socket_rtp_recv_fin;
    RTPP_DBG_ASSERT(pub->send_pkt_na != (rtpp_socket_send_pkt_na_t)&rtpp_socket_send_pkt_na_fin);
    pub->send_pkt_na = (rtpp_socket_send_pkt_na_t)&rtpp_socket_send_pkt_na_fin;
    RTPP_DBG_ASSERT(pub->setnonblock != (rtpp_socket_setnonblock_t)&rtpp_socket_setnonblock_fin);
    pub->setnonblock = (rtpp_socket_setnonblock_t)&rtpp_socket_setnonblock_fin;
    RTPP_DBG_ASSERT(pub->setrbuf != (rtpp_socket_setrbuf_t)&rtpp_socket_setrbuf_fin);
    pub->setrbuf = (rtpp_socket_setrbuf_t)&rtpp_socket_setrbuf_fin;
    RTPP_DBG_ASSERT(pub->settimestamp != (rtpp_socket_settimestamp_t)&rtpp_socket_settimestamp_fin);
    pub->settimestamp = (rtpp_socket_settimestamp_t)&rtpp_socket_settimestamp_fin;
    RTPP_DBG_ASSERT(pub->settos != (rtpp_socket_settos_t)&rtpp_socket_settos_fin);
    pub->settos = (rtpp_socket_settos_t)&rtpp_socket_settos_fin;
}
#if defined(RTPP_FINTEST)
#include <assert.h>
#include <stddef.h>
#include "rtpp_mallocs.h"
#include "rtpp_refcnt.h"
#include "rtpp_linker_set.h"
#define CALL_TFIN(pub, fn) ((void (*)(typeof(pub)))((pub)->fn))(pub)

void
rtpp_socket_fintest()
{
    int naborts_s;

    struct {
        struct rtpp_socket pub;
    } *tp;

    naborts_s = _naborts;
    tp = rtpp_rzmalloc(sizeof(*tp), offsetof(typeof(*tp), pub.rcnt));
    assert(tp != NULL);
    assert(tp->pub.rcnt != NULL);
    CALL_SMETHOD(tp->pub.rcnt, attach, (rtpp_refcnt_dtor_t)&rtpp_socket_fin,
      &tp->pub);
    CALL_SMETHOD(tp->pub.rcnt, decref);
    CALL_TFIN(&tp->pub, bind);
    CALL_TFIN(&tp->pub, getfd);
    CALL_TFIN(&tp->pub, rtp_recv);
    CALL_TFIN(&tp->pub, send_pkt_na);
    CALL_TFIN(&tp->pub, setnonblock);
    CALL_TFIN(&tp->pub, setrbuf);
    CALL_TFIN(&tp->pub, settimestamp);
    CALL_TFIN(&tp->pub, settos);
    assert((_naborts - naborts_s) == 8);
}
const static void *_rtpp_socket_ftp = (void *)&rtpp_socket_fintest;
DATA_SET(rtpp_fintests, _rtpp_socket_ftp);
#endif /* RTPP_FINTEST */
