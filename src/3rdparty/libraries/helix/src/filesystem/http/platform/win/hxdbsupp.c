/* ***** BEGIN LICENSE BLOCK *****
 * Source last modified: $Id: hxdbsupp.c,v 1.4 2004/07/09 18:40:24 hubbe Exp $
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
 * terms of the GNU General Public License Version 2 or later (the
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

/*
 * These are platform specific routines
 */

#include <tchar.h>

#define MUTEX_NAME	_T("HTTP_Cache_FSDB_Mutex")

static HX_RESULT
GrabMutex (const DB* pDbConst)
{
    DB*        pDb    = (DB*) pDbConst;  // Lose the const
    HX_RESULT  rc     = HXR_OK;
    
    
    LOG ("GrabMutex()");

    if (pDb->hMutex == NULL)
    {
    	pDb->hMutex = CreateMutex (NULL, FALSE, MUTEX_NAME);
    }
    
	rc = WaitForSingleObject(pDb->hMutex, 5 * 1000);
    switch (rc)
    {
      case WAIT_OBJECT_0:
        break;
      case WAIT_TIMEOUT:
        LOG ("    Could not get mutex: Timeout");
        break;
      case WAIT_ABANDONED:
        LOG ("    Could not get mutex: Abandoned");
        break;
      default:
        LOGX ((szDbgTemp, "    Could not get mutex: Unknown error [%lu]", rc));
        break;
    }
    
    return((rc == WAIT_OBJECT_0) ? HXR_OK : HXR_FAIL);
}

static HX_RESULT
FreeMutex (const DB* pDb)
{
    HX_RESULT rc = HXR_OK;
    
	LOG ("FreeMutex()");

    if (pDb == NULL)
    {
    	LOG (" *** FreeMutex(): NULL parameter: pDb");
        return(HXR_FAIL);
    }    

    if (pDb->hMutex != NULL)
    {
    	if (ReleaseMutex(pDb->hMutex) == FALSE)
        {
        	LOG ("*** Error releasing mutex");
        }
    }
    else
    {
    	LOG ("*** Mutex is null");
    }
    return(HXR_OK);
}

static HX_RESULT
CloseMutex (const DB* pDbConst)
{
    DB* pDb = (DB*) pDbConst;    // Lose the const
    
    HX_RESULT  rc     = HXR_OK;
    
	LOG ("CloseMutex()");

    if (pDb == NULL)
    {
    	LOG (" *** CloseMutex(): NULL parameter: pDb");
        return(HXR_FAIL);
    }    

    if (pDb->hMutex != NULL)
    {
    	if (CloseHandle(pDb->hMutex) == FALSE)
        {
        	LOG ("*** Error destroying mutex");
        }
        pDb->hMutex = NULL;
    }
    else
    {
    	LOG ("*** Mutex is null");
    }
    return(HXR_OK);
}
