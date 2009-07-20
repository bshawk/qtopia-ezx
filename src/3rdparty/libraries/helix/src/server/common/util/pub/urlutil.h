/* ***** BEGIN LICENSE BLOCK *****  
 * Source last modified: $Id: urlutil.h,v 1.6 2008/05/12 09:19:11 vijendrakumara Exp $ 
 *   
 * Portions Copyright (c) 1995-2003 RealNetworks, Inc. All Rights Reserved.  
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
/* $ID$ */

#ifndef _URLUTIL_H_
#define _URLUTIL_H_

/*
 * XXXAAK -- for unescaping the URL but DONOT replacing a '+'
 * with a SPACE
 */
void unescape_url_without_plus(char *url);

void        DecodeURL(const BYTE* pEnc, size_t nEncLen, char* szDec);
void        DecodeURL(const char* pEnc, char* szDec);

// 3GPP compliant stream identifier functions (see 3GPP 26.234-550)
BOOL        IsStreamId(const char* pBuf);
BOOL        GetStreamId(const char* pBuf, UINT32* puStreamId);
const char* GetPort(const char *host);

#endif // _URLUTIL_H_
