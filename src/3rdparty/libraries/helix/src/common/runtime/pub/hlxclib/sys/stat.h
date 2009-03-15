/* ***** BEGIN LICENSE BLOCK *****
 * Source last modified: $Id: stat.h,v 1.9 2008/01/18 09:17:28 vkathuria Exp $
 * 
 * Portions Copyright (c) 1995-2004 RealNetworks, Inc. All Rights Reserved.
 * 
 * The contents of this file, and the files included with this file,
 * are subject to the current version of the RealNetworks Public
 * Source License (the "RPSL") available at
 * http://www.helixcommunity.org/content/rpsl unless you have licensed
 * the file under the current version of the RealNetworks Community
 * Source License (the "RCSL") available at
 * http://www.helixcommunity.org/content/rcsl, in which case the RCSL
 * will apply. You may also obtain the license terms directly from
 * RealNetworks.  You may not use this file except in compliance with
 * the RPSL or, if you have a valid RCSL with RealNetworks applicable
 * to this file, the RCSL.  Please see the applicable RPSL or RCSL for
 * the rights, obligations and limitations governing use of the
 * contents of the file.
 * 
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License Version 2 (the
 * "GPL") in which case the provisions of the GPL are applicable
 * instead of those above. If you wish to allow use of your version of
 * this file only under the terms of the GPL, and not to allow others
 * to use your version of this file under the terms of either the RPSL
 * or RCSL, indicate your decision by deleting the provisions above
 * and replace them with the notice and other provisions required by
 * the GPL. If you do not delete the provisions above, a recipient may
 * use your version of this file under the terms of any one of the
 * RPSL, the RCSL or the GPL.
 * 
 * This file is part of the Helix DNA Technology. RealNetworks is the
 * developer of the Original Code and owns the copyrights in the
 * portions it created.
 * 
 * This file, and the files included with this file, is distributed
 * and made available on an 'AS IS' basis, WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, AND REALNETWORKS HEREBY DISCLAIMS
 * ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET
 * ENJOYMENT OR NON-INFRINGEMENT.
 * 
 * Technology Compatibility Kit Test Suite(s) Location:
 *    http://www.helixcommunity.org/content/tck
 * 
 * Contributor(s):
 * 
 * ***** END LICENSE BLOCK ***** */

#ifndef HLXSYS_SYS_STAT_H
#define HLXSYS_SYS_STAT_H

#if !defined(WIN32_PLATFORM_PSPC) && !defined(_OPENWAVE) && !defined(_WINCE) && !defined(_BREW)
#if defined(_MACINTOSH) && !defined(_MAC_MACHO)
#include <stat.h>
#else
#include <sys/stat.h>
#endif
#endif /* !defined(WIN32_PLATFORM_PSPC) */

#include "hlxclib/sys/types.h"

#if defined __SYMBIAN32__
#define _fileno fileno
#define _fstat  fstat
#define _stat   stat
#define _fstati64 fstat
#define _stati64 stat
#define _lseeki64 lseek
#endif

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Helix implementations */
int __helix_fstat(int filedes, struct stat *buf);
int __helix_stat(const char* pFilename, struct stat *buf);

#if defined(WIN32_PLATFORM_PSPC) || defined(_OPENWAVE) || defined(_BREW)

#if defined(_OPENWAVE) || defined (_BREW)
#define S_IFDIR		0x1000	/* specify a directory*/
#endif 

inline
int fstat(int filedes, struct stat *buf)
{
    return __helix_fstat(filedes, buf);
}

inline
int _stat(const char* pFilename, struct _stat *buf)
{
    return __helix_stat(pFilename, (struct stat *)buf);
}

inline
int stat(const char* pFilename, struct stat *buf)
{
    return __helix_stat(pFilename, buf);
}

#endif /* defined(WIN32_PLATFORM_PSPC) */


#ifdef __cplusplus
};
#endif /* __cplusplus */


#endif /* HLXSYS_SYS_STAT_H */