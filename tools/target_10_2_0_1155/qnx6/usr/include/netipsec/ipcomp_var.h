/*	$NetBSD: ipcomp_var.h,v 1.3.24.1 2007/05/24 19:13:13 pavel Exp $	*/
/*	$FreeBSD: src/sys/netipsec/ipcomp_var.h,v 1.1.4.1 2003/01/24 05:11:35 sam Exp $	*/
/*	$KAME: ipcomp.h,v 1.8 2000/09/26 07:55:14 itojun Exp $	*/

/*
 * Copyright (C) 1999 WIDE Project.
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
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef _NETIPSEC_IPCOMP_VAR_H_INCLUDED
#define _NETIPSEC_IPCOMP_VAR_H_INCLUDED

#ifndef _INTTYPES_H_INCLUDED
#include <inttypes.h>
#endif

/*
 * These define the algorithm indices into the histogram.  They're
 * presently based on the PF_KEY v2 protocol values which is bogus;
 * they should be decoupled from the protocol at which time we can
 * pack them and reduce the size of the array to a minimum.
 */
#define	IPCOMP_ALG_MAX	8

struct ipcompstat {
	uint64_t	ipcomps_hdrops;	/* Packet shorter than header shows */
	uint64_t	ipcomps_nopf;	/* Protocol family not supported */
	uint64_t	ipcomps_notdb;
	uint64_t	ipcomps_badkcr;
	uint64_t	ipcomps_qfull;
	uint64_t	ipcomps_noxform;
	uint64_t	ipcomps_wrap;
	uint64_t	ipcomps_input;	/* Input IPcomp packets */
	uint64_t	ipcomps_output;	/* Output IPcomp packets */
	uint64_t	ipcomps_invalid;/* Trying to use an invalid TDB */
	uint64_t	ipcomps_ibytes;	/* Input bytes */
	uint64_t	ipcomps_obytes;	/* Output bytes */
	uint64_t	ipcomps_toobig;	/* Packet got > IP_MAXPACKET */
	uint64_t   ipcomps_minlen; /* Packet too short for compress */
	uint64_t	ipcomps_pdrops;	/* Packet blocked due to policy */
	uint64_t	ipcomps_crypto;	/* "Crypto" processing failure */
	uint64_t	ipcomps_hist[IPCOMP_ALG_MAX];/* Per-algorithm op count */
};

#ifdef _KERNEL
extern	int ipcomp_enable;
extern	struct ipcompstat ipcompstat;
#endif /* _KERNEL */
#endif /* !_NETIPSEC_IPCOMP_VAR_H_INCLUDED */

__SRCVERSION( "$URL: http://svn.ott.qnx.com/product/branches/deckard/BB10_2_0X/lib/socket/public/netipsec/ipcomp_var.h $ $Rev: 233581 $" )