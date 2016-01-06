/***************************************************************
 * Name:      JupiDateApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Daniel Caujolle-Bert (danielvador@gmail.com)
 * Created:   2015-12-30
 * Copyright: Daniel Caujolle-Bert (http://naboo.homelinux.org)
 * License:
 **************************************************************/

#include "JupiDateApp.h"

//(*AppHeaders
#include "JupiDateMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(JupiDateApp);

bool JupiDateApp::OnInit()
{
#if 0
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	JupiDateFrame* Frame = new JupiDateFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
#else
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	JupiDateFrame* Frame = new JupiDateFrame(0, wxApp::GetAppName());
    	Frame->Show();
    	SetTopWindow(Frame);
    }
#endif // 0
    return wxsOK;

}
