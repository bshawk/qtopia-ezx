/* ***** BEGIN LICENSE BLOCK *****
 * Source last modified: $Id: chxphook.h,v 1.4 2007/07/06 21:58:08 jfinnecy Exp $
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


#ifndef _CHXPHOOK_H_
#define _CHXPHOOK_H_

#include "hxphook.h"

typedef _INTERFACE  IHXPlayer			    IHXPlayer;
typedef _INTERFACE  IHXPacket			    IHXPacket;
typedef _INTERFACE  IHXPacketHook		    IHXPacketHook;
typedef _INTERFACE  IHXPacketHookManager	    IHXPacketHookManager;
typedef _INTERFACE  IHXPacketHookHelperResponse    IHXPacketHookHelperResponse;

class PacketHookManager : public IHXPacketHookManager
{
protected:

    virtual ~PacketHookManager();


    LONG32		m_lRefCount;
    
    ULONG32		m_ulTotalStreams;
    ULONG32		m_ulRecordableStreams;

    IHXPlayer*		m_pPlayer;
    IHXPacketHook*	m_pPacketHook;

public:

    PacketHookManager(IHXPlayer* pPlayer);

    // helper functions
    STDMETHOD(OnPacket)		(THIS_
				IHXPacket* pPacket);

    STDMETHOD(OnEndOfPackets)	(THIS_
				ULONG32	ulStreamID);

    /*
     *	IUnknown methods
     */
    STDMETHOD(QueryInterface)	(THIS_
				REFIID riid,
				void** ppvObj);

    STDMETHOD_(ULONG32,AddRef)	(THIS);

    STDMETHOD_(ULONG32,Release)	(THIS);

    
    /*
     * IHXPacketHookManager methods
     */

    /************************************************************************
     *	Method:
     *	    IHXPacketHookManager::InitHook
     *	Purpose:
     *	    called by the top level client to pass the IHXPacketHook object
     */
    STDMETHOD(InitHook)		(THIS_
				IHXPacketHook* pPacketHook);

    /************************************************************************
     *	Method:
     *	    IHXPacketHookManager::CloseHook
     *	Purpose:
     *	    called by the top level client to close the hook connection
     */
    STDMETHOD(CloseHook)	(THIS);

    /************************************************************************
     *	Method:
     *	    IHXPacketHookManager::StartHook
     *	Purpose:
     *	    called by the top level client to start recording
     */
    STDMETHOD(StartHook)	(THIS);

    /************************************************************************
     *	Method:
     *	    IHXPacketHookManager::StopHook
     *	Purpose:
     *	    called by the top level client to stop recording
     */
    STDMETHOD(StopHook)		(THIS);
};

class PacketHookHelperResponse : public IHXPacketHookHelperResponse
{
protected:

    virtual ~PacketHookHelperResponse();


    LONG32		    m_lRefCount;

    ULONG32		    m_ulStreamID;
    PacketHookManager*	    m_pPacketHookManager;

public:

    PacketHookHelperResponse(PacketHookManager* pPacketHookManager,
			    ULONG32		    ulStreamID);

    /*
     *	IUnknown methods
     */
    STDMETHOD(QueryInterface)	(THIS_
				REFIID riid,
				void** ppvObj);

    STDMETHOD_(ULONG32,AddRef)	(THIS);

    STDMETHOD_(ULONG32,Release)	(THIS);

    /*
     * IHXPacketHookHelperResponse methods
     */

    /************************************************************************
     *	Method:
     *	    IHXPacketHookHelperResponse::OnPacket
     *	Purpose:
     *	    called by the renderer to pass the packet for recording
     */
    STDMETHOD(OnPacket)		(THIS_
				IHXPacket* pPacket);

    /************************************************************************
     *	Method:
     *	    IHXPacketHookManager::OnEndOfPackets
     *	Purpose:
     *	    called by the renderer to notify the end of this stream
     */
    STDMETHOD(OnEndOfPackets)	(THIS);
};

#endif // _CHXPHOOK_H_