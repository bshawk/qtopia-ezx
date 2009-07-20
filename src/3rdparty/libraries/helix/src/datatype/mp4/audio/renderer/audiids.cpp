/* ***** BEGIN LICENSE BLOCK ***** 
 * Version: RCSL 1.0/RPSL 1.0 
 *  
 * Portions Copyright (c) 1995-2002 RealNetworks, Inc. All Rights Reserved. 
 *      
 * The contents of this file, and the files included with this file, are 
 * subject to the current version of the RealNetworks Public Source License 
 * Version 1.0 (the "RPSL") available at 
 * http://www.helixcommunity.org/content/rpsl unless you have licensed 
 * the file under the RealNetworks Community Source License Version 1.0 
 * (the "RCSL") available at http://www.helixcommunity.org/content/rcsl, 
 * in which case the RCSL will apply. You may also obtain the license terms 
 * directly from RealNetworks.  You may not use this file except in 
 * compliance with the RPSL or, if you have a valid RCSL with RealNetworks 
 * applicable to this file, the RCSL.  Please see the applicable RPSL or 
 * RCSL for the rights, obligations and limitations governing use of the 
 * contents of the file.  
 *  
 * This file is part of the Helix DNA Technology. RealNetworks is the 
 * developer of the Original Code and owns the copyrights in the portions 
 * it created. 
 *  
 * This file, and the files included with this file, is distributed and made 
 * available on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER 
 * EXPRESS OR IMPLIED, AND REALNETWORKS HEREBY DISCLAIMS ALL SUCH WARRANTIES, 
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS 
 * FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT. 
 * 
 * Technology Compatibility Kit Test Suite(s) Location: 
 *    http://www.helixcommunity.org/content/tck 
 * 
 * Contributor(s): 
 *  
 * ***** END LICENSE BLOCK ***** */ 

/****************************************************************************
 *  Includes
 */
#include "hlxclib/stdio.h"
#include "hlxclib/string.h"

#define INITGUID 1

#include "hxtypes.h"
#include "hxwintyp.h"
#include "hxresult.h"
#include "hxcom.h"
#include "hxcomm.h"
#include "ihxpckts.h"
#include "ihxfgbuf.h"
#include "hxcore.h"
#include "hxrendr.h"
#include "hxplugn.h"
#include "hxasm.h"
#include "hxupgrd.h"
#include "hxengin.h"
#include "hxprefs.h"
#include "hxerror.h"
#include "hxwin.h"
#include "hxthread.h"
#include "hxmon.h"
#include "hxformt.h"
#include "hxacodec.h"
#include "hxplgns.h"
#include "ihxtlogsystem.h"
#include "ihxtlogsystemcontext.h"
#include "hxdllaccess.h"
#undef INITGUID

#include "mp4arender.ver"
#include "mp4audio.h"
#include "mp4afmt.h"

#include "dllpath.h"
#include "hxheap.h"

#if !defined(HELIX_FEATURE_DLLACCESS_CLIENT)
ENABLE_DLLACCESS_PATHS(mp4arend);
#endif	// HELIX_FEATURE_DLLACCESS_CLIENT


/****************************************************************************
 * 
 *  Function:
 * 
 *	HXCreateInstance()
 * 
 *  Purpose:
 * 
 *	Function implemented by all plugin DLL's to create an instance of 
 *	any of the objects supported by the DLL. This method is similar to 
 *	Window's CoCreateInstance() in its purpose, except that it only 
 *	creates objects from this plugin DLL.
 *
 *	NOTE: Aggregation is never used. Therefore and outer unknown is
 *	not passed to this function, and you do not need to code for this
 *	situation.
 * 
 */

STDAPI ENTRYPOINTCALLTYPE ENTRYPOINT(HXCREATEINSTANCE)
(   
    IUnknown**  /*OUT*/	ppIUnknown  
)   
{   
    return CMP4AudioRenderer::HXCreateInstance(ppIUnknown);
}   

/****************************************************************************
 * 
 *  Function:
 * 
 *	CanUnload()
 * 
 *  Purpose:
 * 
 *	Function implemented by all plugin DLL's if it returns HXR_OK 
 *	then the pluginhandler can unload the DLL
 *
 */

STDAPI ENTRYPOINTCALLTYPE ENTRYPOINT(CanUnload)(void)
{
    return ((CHXBaseCountingObject::ObjectsActive() > 0) ? HXR_FAIL : HXR_OK);
}

STDAPI ENTRYPOINTCALLTYPE ENTRYPOINT(CanUnload2)(void)
{
    return ENTRYPOINT(CanUnload)();
}
