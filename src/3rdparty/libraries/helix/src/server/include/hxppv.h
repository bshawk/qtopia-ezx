/* ***** BEGIN LICENSE BLOCK *****  
 * Source last modified: $Id: hxppv.h,v 1.2 2003/01/23 23:42:59 damonlan Exp $ 
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

#ifndef _HXPPV_H_
#define _HXPPV_H_

#ifdef _MACINTOSH // Unsure whether this should be included on other platforms?
#include <time.h> // Get definition of time_t.
#endif

/*
 * Structures and definitions for PPVPermission
 */

#define PPV_MAX_URL_LEN         2048

typedef enum _PPVURLType {
    PPV_URL_TYPE_FILE = 0,
    PPV_URL_TYPE_DIRECTORY    
} PPVURLType;

typedef enum _PPVPermissionType {
    PPV_PERMISSION_GENERAL = 0,
    PPV_PERMISSION_EXPIRES,
    PPV_PERMISSION_DEBIT,
    PPV_PERMISSION_CREDIT,
    PPV_PERMISSION_NONE
} PPVPermissionType;

typedef struct _PPVPermission
{
    char	    	pURL[PPV_MAX_URL_LEN];
    PPVURLType	    	nURLType;
    PPVPermissionType	nPermissionType;
    time_t	    	tExpires;
    UINT32	    	ulDebitTime;
} PPVPermission;


/*
 * Structures and definitions for PPVAccessLog
 */

typedef enum _PPVAccessPermissionOn {
    PPV_PERMISSION_ON_FILE = 0,
    PPV_PERMISSION_ON_DIRECTORY,
    PPV_PERMISSION_ON_NONE
} PPVAccessPermissionOn;

typedef enum _PPVAccessDisconnectType {
    PPV_DISCONNECT_CLIENT = 0,
    PPV_DISCONNECT_TIME_EXPIRED
} PPVAccessDisconnectType;

typedef struct _PPVAccessLog
{
    BOOL		    bAccessGranted;
    char*		    pUserid;
    char*		    pGUID;
    char*		    pIPAddress;
    char*		    pURL;
    PPVPermissionType 	    nPermissionType;
    PPVAccessPermissionOn   nPermOn;
    time_t		    tStartTime;
    time_t		    tStopTime;
    UINT32		    lTotalTime;
    UINT32                  lNCTime;
    PPVAccessDisconnectType nWhyDisconnect;
} PPVAccessLog;


/*
 * Structures and definitions for PPVRegLog
 */

typedef enum _PPVRegStatus
{
    PPV_GUID_REG_SUCCESS = 0,
    PPV_GUID_REG_FAILED_LOCKED,
    PPV_GUID_REG_FAILED_COLLISION,
    PPV_GUID_REG_FAILED_OLD_PLAYER,
    PPV_GUID_REG_FAILED_NO_USER,
    PPV_GUID_REG_FAILED
} PPVRegStatus;

typedef struct _PPVRegLog
{
   PPVRegStatus	    nStatus;
   char*	    pUserid;
   char*	    pGUID;
   char*	    pIPAddress;
   time_t	    tRequestTime;
   char*	    pURLRedirect;
} PPVRegLog;


/****************************************************************************
 * 
 *  Interface:
 *
 *	IHXPPVDatabase
 *
 *  Purpose:
 *	This interface provides access to a backend database used to store
 *	information related to the server's pay-per-view feature.
 *
 *  IID_IHXPPVDatabase:
 *
 *	{00001d00-0901-11d1-8B06-00A024406D59}
 *
 */
DEFINE_GUID(IID_IHXPPVDatabase, 0x00001d00, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
				 0xa0, 0x24, 0x40, 0x6d, 0x59);

#undef  INTERFACE
#define INTERFACE   IHXPPVDatabase

DECLARE_INTERFACE_(IHXPPVDatabase, IUnknown)
{
    /*
     * IUnknown methods
     */
    STDMETHOD(QueryInterface)	(THIS_
				REFIID riid,
				void** ppvObj) PURE;

    STDMETHOD_(ULONG32,AddRef)	(THIS) PURE;

    STDMETHOD_(ULONG32,Release)	(THIS) PURE;

    /*
     * IHXPPVDatabase methods
     */

    /************************************************************************
     *	Method:
     *	    IHXPPVDatabase::InitPPVDB
     *	Purpose:
     *	    Open & Initialize the PPV Database.
     *	    This function will called once per instance before any other
     *	    methods are called.
     *
     * pDBName			Name of the database (if supported)
     * pUserID			User ID to access database (if supported)
     * pPassword		Password to access database (if supported)
     */
    STDMETHOD(InitPPVDB)	(THIS_
				 const char*	pDBName,
				 const char*	pUserID,
				 const char*	pPassword) PURE;

    /************************************************************************
     *	Method:
     *	    IHXPPVDatabase::GetPPVDBInfo
     *	Purpose:
     *	    Get this databases short name.
     *	    This unique identifier is used to identify this database plugin.
     *	    It should be unique enough that no other plugin will ever have
     *	    the same plugin name.
     */
    STDMETHOD(GetPPVDBInfo)	(THIS_
				 REF(const char*) /*OUT*/ pShortName) PURE;

    /************************************************************************
     *	Method:
     *	    IHXPPVDatabase::InsertUser
     *	Purpose:
     *	    Inserts a user into the database (the user should not already
     *	    exist).
     *
     *	    pUserid		Userid key of the record to insert
     *	    pPasswordCipher	Optional Password to associate with this user;
     *				The password being passed in is already
     *				encrypted.
     */
    STDMETHOD(InsertUser)	(THIS_
				 const char*	pUserid,
				 const char*	pPasswordCipher) PURE;

    /************************************************************************
     *	Method:
     *	    IHXPPVDatabase::RemoveUser
     *	Purpose:
     *	    Removes a user from the database.
     *
     *	    pUserid		Userid key of the record
     */
    STDMETHOD(RemoveUser)	(THIS_
				 const char*	pUserid) PURE;

    /************************************************************************
     *	Method:
     *	    IHXPPVDatabase::RegisterGUID
     *	Purpose:
     *	    Registers a GUID to be associated with the pUserid
     *
     *	    pUserid		Userid key of the record
     *	    pGUID		GUID to associate with user record
     *	    bForce		Forces registration of guid, even if
     *				the uuid_writeable flag is set to read only
     */
    STDMETHOD(RegisterGUID)	(THIS_
				 const char*	pUserid,
				 const char*	pGUID,
				 BOOL		bForce) PURE;

    /************************************************************************
     *	Method:
     *	    IHXPPVDatabase::SetPassword
     *	Purpose:
     *	    Sets the password for the user associated with pUserid 
     *
     *	    pUserid		Userid key of the record
     *	    pCipherPassword	User's Password
     */
    STDMETHOD(SetPassword)	(THIS_
				 const char*	pUserid,
				 const char*	pCipherPassword) PURE;

    /************************************************************************
     *	Method:
     *	    IHXPPVDatabase::ValidateUser
     *	Purpose:
     *	    Sets the password for the user associated with pUserid 
     *
     *	    pUserid		Userid key of the record
     *	    pPPVPermission	Permission structure with URL to validate on
     */
    STDMETHOD(ValidateUser)	(THIS_
				 const char*	pUserid,
				 PPVPermission*	pPPVPermission) PURE;

    /************************************************************************
     *	Method:
     *	    IHXPPVDatabase::GrantPermission
     *	Purpose:
     *	    Adds a permission record.
     *
     *	    pUserid		Userid key of the record
     *	    pPPVPermission	Permission structure with URL
     */
    STDMETHOD(GrantPermission)	(THIS_
				 const char*		pUserid,
				 const PPVPermission*	pPPVPermission) PURE;

    /************************************************************************
     *	Method:
     *	    IHXPPVDatabase::RevokePermission
     *	Purpose:
     *	    Removes a permission record.
     *
     *	    pUserid		Userid key of the record
     *	    pPPVPermission	Permission structure with URL
     */
    STDMETHOD(RevokePermission)	(THIS_
				 const char*		pUserid,
				 const PPVPermission*	pPPVPermission) PURE;

    /************************************************************************
     *	Method:
     *	    IHXPPVDatabase::RevokeAllPermissions
     *	Purpose:
     *	    Removes all permission records for a user.
     *
     *	    pUserid		Userid key of the record
     */
    STDMETHOD(RevokeAllPermissions)	(THIS_
					 const char*	pUserid) PURE;
 
    /************************************************************************
     *	Method:
     *	    IHXPPVDatabase::GetRedirect
     *	Purpose:
     *	    Gets the redirection Url corresponding to the requested Url
     *	    from the database.
     *
     *	    pURL		Url key of redirect record (In)
     *	    pURLRedirect	Url to redirect to (Out)
     *	    ulURLRedirectLen	Maximum length of pURLRedirect (In)
     */
    STDMETHOD(GetRedirect)	(THIS_
				 const char*	pURL,
				 char*		pURLRedirect,
				 UINT32		ulURLRedirectLen) PURE;

    /************************************************************************
     *	Method:
     *	    IHXPPVDatabase::PutRedirect
     *	Purpose:
     *	    Adds a redirection Url to the database to correspond with
     *	    the Url key.
     *	    
     *
     *	    pURL		Url key of redirect record (In)
     *	    pURLRedirect	Url to redirect to (In)
     */
    STDMETHOD(PutRedirect)	(THIS_
				 const char*	pURL,
				 const char*	pURLRedirect) PURE;

    /************************************************************************
     *	Method:
     *	    IHXPPVDatabase::GrantTime
     *	Purpose:
     *	    Grants a user time to view (specified by pPPVPermission).
     *
     *	    pUserid		Userid key of the record
     *	    pPPVPermission	Permission structure with URL
     *	    ulGrant		Amount of time to grant
     */
    STDMETHOD(GrantTime)	(THIS_
				 const char*	    	pUserid,
				 const PPVPermission*	pPPVPermission,
				 UINT32			ulGrant) PURE;

    /************************************************************************
     *	Method:
     *	    IHXPPVDatabase::DeductTime
     *	Purpose:
     *	    Deducts a user time to view (specified by pPPVPermission).
     *
     *	    pUserid		Userid key of the record
     *	    pPPVPermission	Permission structure with URL
     *	    ulDeduct		Amount of time to deduct
     */
    STDMETHOD(DeductTime)	(THIS_
				 const char*	    	pUserid,
				 const PPVPermission*	pPPVPermission,
				 UINT32			ulDeduct) PURE;

    /************************************************************************
     *	Method:
     *	    IHXPPVDatabase::GetPasswordFromUserid
     *	Purpose:
     *	    Get's a users password
     *
     *	    pUserid		Userid key of the record (In)
     *	    pCipherPassword	Password to get (Out)
     *	    ulCipherPasswordLen	Maximum length of pCipherPassword
     */
    STDMETHOD(GetPasswordFromUserid)	(THIS_
					 const char*	    pUserid,
					 char*	    	    pCipherPassword,
					 UINT32		    ulCipherPasswordLen) PURE;

    /************************************************************************
     *	Method:
     *	    IHXPPVDatabase::GetUseridFromGUID
     *	Purpose:
     *	    Get's a users id
     *
     *	    pGUID		GUID of existing user (In)
     *	    pUserid		Userid key of the record (Out)
     *	    ulUseridLen		Maximum length of pUserid (In)
     */
    STDMETHOD(GetUseridFromGUID)	(THIS_
					 const char*	    pGUID,
					 char*	    	    pUserid,
					 UINT32		    ulUseridLen) PURE;

    /************************************************************************
     *	Method:
     *	    IHXPPVDatabase::LogReg
     *	Purpose:
     *	    This function inserts a new record into the data with the logging
     *	    information contained in pPPVRegLog
     */
    STDMETHOD(LogReg)		(THIS_
				 PPVRegLog*  pPPVRegLog) PURE;

    /************************************************************************
     *	Method:
     *	    IHXPPVDatabase::LogAccess
     *	Purpose:
     *	    This function inserts a new record into the data with the logging
     *	    information contained in pPPVAccessLog
     */
    STDMETHOD(LogAccess)	(THIS_
				 PPVAccessLog*  pPPVAccessLog) PURE;

};

#endif /*_HXPPV_H_*/