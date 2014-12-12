/*	$NetBSD: shm.h,v 1.42 2006/11/25 21:40:06 christos Exp $	*/

/*-
 * Copyright (c) 1999 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Jason R. Thorpe of the Numerical Aerospace Simulation Facility,
 * NASA Ames Research Center.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by the NetBSD
 *	Foundation, Inc. and its contributors.
 * 4. Neither the name of The NetBSD Foundation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright (c) 1994 Adam Glass
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
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by Adam Glass.
 * 4. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * As defined+described in "X/Open System Interfaces and Headers"
 *                         Issue 4, p. XXX
 */

#ifndef _SYS_SHM_H_
#define _SYS_SHM_H_

#include <sys/ipc.h>

#define	SHM_RDONLY	010000	/* Attach read-only (else read-write) */
#define	SHM_RND		020000	/* Round attach address to SHMLBA */

#define SHMLBA          (sysconf(_SC_PAGESIZE))

typedef unsigned int	shmatt_t;

struct shmid_ds {
	struct ipc_perm	shm_perm;	/* operation permission structure */
	size_t		shm_segsz;	/* size of segment in bytes */
	pid_t		shm_lpid;	/* process ID of last shm operation */
	pid_t		shm_cpid;	/* process ID of creator */
	shmatt_t	shm_nattch;	/* number of current attaches */
	time_t		shm_atime;	/* time of last shmat() */
	time_t		shm_dtime;	/* time of last shmdt() */
	time_t		shm_ctime;	/* time of last change by shmctl() */
};

/*
 * Some systems (e.g. HP-UX) take these as the second (cmd) arg to shmctl().
 */
#define	SHM_LOCK	3	/* Lock segment in memory. */
#define	SHM_UNLOCK	4	/* Unlock a segment locked by SHM_LOCK. */

#if defined(_NETBSD_SOURCE)
/*
 * Permission definitions used in shmflag arguments to shmat(2) and shmget(2).
 * Provided for source compatibility only; do not use in new code!
 */
#define	SHM_R		IPC_R	/* S_IRUSR, R for owner */
#define	SHM_W		IPC_W	/* S_IWUSR, W for owner */

/*
 * System 5 style catch-all structure for shared memory constants that
 * might be of interest to user programs.  Do we really want/need this?
 */
struct shminfo {
	int32_t	shmmax;		/* max shared memory segment size (bytes) */
	int32_t	shmmin;		/* min shared memory segment size (bytes) */
	int32_t	shmmni;		/* max number of shared memory identifiers */
	int32_t	shmseg;		/* max shared memory segments per process */
	int32_t	shmall;		/* max amount of shared memory (pages) */
};

/* Warning: 64-bit structure padding is needed here */
struct shmid_ds_sysctl {
	struct		ipc_perm_sysctl shm_perm;
	uint64_t	shm_segsz;
	pid_t		shm_lpid;
	pid_t		shm_cpid;
	time_t		shm_atime;
	time_t		shm_dtime;
	time_t		shm_ctime;
	uint32_t	shm_nattch;
};
struct shm_sysctl_info {
	struct	shminfo shminfo;
	int32_t	pad;	/* shminfo not a multiple of 64 bits */
	struct	shmid_ds_sysctl shmids[1];
};
#endif /* _NETBSD_SOURCE */

__BEGIN_DECLS
void	*shmat(int shmid, const void *shmaddr, int shmflag);
int	shmctl(int shmid, int shmop, struct shmid_ds *buf);
int	shmdt(const void *shmaddr);
int	shmget(key_t key, size_t size, int shmflag);
__END_DECLS

#endif /* !_SYS_SHM_H_ */