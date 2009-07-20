/* ***** BEGIN LICENSE BLOCK *****
 * Source last modified: $Id: hxmaputils.cpp,v 1.8 2007/07/06 20:34:58 jfinnecy Exp $
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

#include "hxmaputils.h"

#include "hlxclib/ctype.h"
#include "hlxclib/string.h"

DECLARE_ITEMVEC_IMP(HlxMap,IntVec_t, int, 0, 0, 0);

ULONG32 HlxMap::StrHashFunc (const char* key, bool bCaseSens)
{
    // XXXSAB: Need something to reasonably distribute strings...anyone
    //         have an idea?
    ULONG32 ret = 0;

    if (key)
    {
        // XOR together sizeof(ULONG32) chunks of the key string...
        static const int wordSize = sizeof(ULONG32);

        const char* keySrc = key;
        int byteLen = strlen(key);
        int wordLen = byteLen / wordSize;
        
        ULONG32 intWord;
        char* pCharWord = (char*)&intWord;

        for (int i = 0; i < wordLen; ++i)
        {
            strncpy (pCharWord, keySrc, wordSize); /* Flawfinder: ignore */
            keySrc += wordSize; byteLen -= wordSize;

            if (! bCaseSens)
            {
                // If case INsensitive, downshift on the way into the
                // hash algorithm.
                char* pCurChar = pCharWord;
                for (int charIdx = 0;
                     charIdx < wordSize;
                     ++charIdx, ++pCurChar)
                {
                    if (isupper(*(pCurChar)))
                        *pCurChar = tolower(*pCurChar);
                }
            }

            ret ^= intWord;
        }

        if (byteLen > 0)
        {
            HX_ASSERT (byteLen < wordSize);
            intWord = 0;
            strncpy (pCharWord, keySrc, byteLen); /* Flawfinder: ignore */

            if (! bCaseSens)
            {
                // If case INsensitive, downshift on the way into the
                // hash algorithm.
                char* pCurChar = pCharWord;
                for (int charIdx = 0;
                     charIdx < byteLen;
                     ++charIdx, ++pCurChar)
                {
                    if (isupper(*(pCurChar)))
                        *pCurChar = tolower(*pCurChar);
                }
            }
            ret ^= intWord;
        }
    }

#ifdef XXXSAB
    printf ("StrHashFunc(\"%s\", %s) -> %d\n",
            key,
            bCaseSens ? "true" : "false",
            ret);
#endif /* XXXSAB */

    return ret;
}
