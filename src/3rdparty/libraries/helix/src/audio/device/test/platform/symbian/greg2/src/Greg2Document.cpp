/*
 * ============================================================================
 *  Name     : CGreg2Document from Greg2Document.h
 *  Part of  : greg2
 *  Created  : 12/11/2002 by 
 *  Implementation notes:
 *     Initial content was generated by Series 60 AppWizard.
 *  Version  :
 *  Copyright: 
 * ============================================================================
 */

// INCLUDE FILES
#include "Greg2Document.h"
#include "Greg2AppUi.h"

// ================= MEMBER FUNCTIONS =======================

// constructor
CGreg2Document::CGreg2Document(CEikApplication& aApp)
    : CAknDocument(aApp)    
{
}

// destructor
CGreg2Document::~CGreg2Document()
{
}

// EPOC default constructor can leave.
void CGreg2Document::ConstructL()
{
}

// Two-phased constructor.
CGreg2Document* CGreg2Document::NewL(
    CEikApplication& aApp)     // CGreg2App reference
{
    CGreg2Document* self = new (ELeave) CGreg2Document( aApp );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop();

    return self;
}
    
// ----------------------------------------------------
// CGreg2Document::CreateAppUiL()
// constructs CGreg2AppUi
// ----------------------------------------------------
//
CEikAppUi* CGreg2Document::CreateAppUiL()
{
    return new (ELeave) CGreg2AppUi;
}

// End of File  
