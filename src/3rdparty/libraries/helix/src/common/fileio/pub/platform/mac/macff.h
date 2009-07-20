/* ***** BEGIN LICENSE BLOCK *****
 * Source last modified: $Id: macff.h,v 1.7 2007/07/06 20:35:19 jfinnecy Exp $
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

#ifndef __MACFINDFILE_H
#define __MACFINDFILE_H

#include "hxtypes.h"
#include "findfile.h"

#if defined(_CARBON) || defined(_MAC_UNIX)
#include "hxstring.h"
#endif

class CMacFindFile : public CFindFile
{
public:

	CMacFindFile	(const char *path,
			const char *delimiter,
			const char *pattern);

	virtual ~CMacFindFile();

	static int pmatch(const char* pattern, const char* string); // public so rndir can use it, too
	
#ifdef _DEBUG
	static void TestFF(const char *directorypath, const char *pfilter);
#endif
	
protected:
	virtual HXBOOL	OS_OpenDirectory (const char * dirName);
	virtual char *	OS_GetNextFile ();
	virtual void	OS_CloseDirectory ();

	// the pattern methods are used to initialize the
	// pattern-matching routines and then compare
	// individual filenames to the specified pattern.
	virtual HXBOOL	OS_InitPattern ();
	virtual HXBOOL	OS_FileMatchesPattern (const char * fname);
	virtual void 	OS_FreePattern ();

#if defined(_CARBON) || defined(_MAC_UNIX)	// for macff_carbon.cpp

	FSIterator 	m_FSIterator;
	char *		m_pszOutFileName;
	
#else	// !defined _CARBON, for macff.cpp
	
	// throw OS-specific directory and pattern-matching
	// variables here!
	char*		    m_pCurrentDirectory;
	char*		    m_pCurrentFileName;
	char*		    m_pNextFileName;
	
//	FSSpec			m_DirSpec;
	INT32			m_DirID;
	INT16			m_VRefNum;
	INT16			m_nIndex;
#endif

};

#endif // __MACFINDFILE_H

