/***************************************************************
 * Name:      JupiDateMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Daniel Caujolle-Bert (danielvador@gmail.com)
 * Created:   2015-12-30
 * Copyright: Daniel Caujolle-Bert (http://naboo.homelinux.org)
 * License:
 **************************************************************/

#include "JupiDateMain.h"

//(*InternalHeaders(JupiDateFrame)
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/intl.h>
#include <wx/font.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/artprov.h>
//*)
#include <wx/msgdlg.h>
#include <wx/log.h>
//#include <wx/app.h>
#include <wx/mstream.h>
#include <wx/stdpaths.h>

#include "version.h"

#include "resource.h"

#if 0
#include <stdlib.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <linux/serial.h>
#endif

#include <vector>

//(*IdInit(JupiDateFrame)
const long JupiDateFrame::ID_BITMAPBUTTON1 = wxNewId();
const long JupiDateFrame::ID_COMBOBOX1 = wxNewId();
const long JupiDateFrame::ID_CHOICE1 = wxNewId();
const long JupiDateFrame::ID_TOGGLEBUTTON1 = wxNewId();
const long JupiDateFrame::ID_STATICLINE1 = wxNewId();
const long JupiDateFrame::ID_TEXTCTRL1 = wxNewId();
const long JupiDateFrame::ID_PANEL1 = wxNewId();
const long JupiDateFrame::ID_BUTTON1 = wxNewId();
const long JupiDateFrame::ID_TEXTCTRL2 = wxNewId();
const long JupiDateFrame::ID_TOGGLEBUTTON2 = wxNewId();
const long JupiDateFrame::ID_BUTTON2 = wxNewId();
const long JupiDateFrame::ID_STATICLINE2 = wxNewId();
const long JupiDateFrame::ID_BUTTON3 = wxNewId();
const long JupiDateFrame::ID_TIMER1 = wxNewId();
const long JupiDateFrame::ID_TIMER2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(JupiDateFrame,wxFrame)
    //(*EventTable(JupiDateFrame)
    //*)
END_EVENT_TABLE()


void JupiDateFrame::_updateSerialList()
{
    std::vector<std::string> sList;

    m_wConnBtn->Enable(false);
    m_wSerialList->Enable(false);
    Update();

    _closeSerialPort();

	// Build serial device array
	if (ctb::GetAvailablePorts(sList) && sList.size())
	{
		std::vector<std::string>::iterator it = sList.begin();

		m_serialArray.Clear();

		while (it != sList.end())
		{
			m_serialArray.Add(wxString::FromAscii((*it).c_str()));
			it++;
		}
	}

	m_wSerialList->Clear();
	m_wSerialList->Append(m_serialArray);
    m_wSerialList->SetSelection(0);
    m_wSetBtn->Enable(false);

    m_wSerialList->Enable();
    m_wConnBtn->Enable();
}

void JupiDateFrame::_enableSizerChilds(wxSizer *sizer, bool enable)
{
    wxSizerItemList           &items = sizer->GetChildren();
    wxSizerItemList::iterator  it = items.begin();
    while(it != items.end())
    {
        if ((*it)->IsWindow())
        {
            wxWindow *o = (*it)->GetWindow();

            o->Enable(enable);
        }
        else if ((*it)->IsSizer())
        {
            wxSizer *s = (*it)->GetSizer();

            _enableSizerChilds(s, enable);
        }

        it++;
    }
}

void JupiDateFrame::_closeSerialPort()
{
    if (m_deviceBase)
    {
        if (m_devicePort.IsOpen())
            m_devicePort.Close();

        m_deviceBase = NULL;
        m_wSetBtn->Enable(false);
        m_wSerialList->Enable();
        m_wSpeedchoice->Enable();
        m_wUpdateSerialListBtn->Enable();
        _enableSizerChilds(m_wRXSizer, false);

        m_wConnBtn->SetLabel(wxT("Connect"));
    }
}

void JupiDateFrame::_updateDateTime()
{
    wxDateTime dt = wxDateTime::Now();

    wxString str = wxEmptyString;
    bool tick = dt.GetTicks() % 2 ? true : false;

    str = wxString::Format(wxT("%02d%c%02d%c%02d - %02d/%02d/%d UTC"),
                           dt.GetHour(wxDateTime::UTC), tick ? ':' : ' ', dt.GetMinute(wxDateTime::UTC), tick ? ':' : ' ', dt.GetSecond(wxDateTime::UTC),
                           dt.GetDay(wxDateTime::UTC), dt.GetMonth(wxDateTime::UTC) + 1, dt.GetYear(wxDateTime::UTC));
    m_wDateText->SetValue(str);
}

JupiDateFrame::JupiDateFrame(wxWindow* parent, wxString appName, wxWindowID id) : m_deviceBase(NULL)
{
    //(*Initialize(JupiDateFrame)
    wxBoxSizer* BoxSizer15;
    wxBoxSizer* BoxSizer3;
    wxBoxSizer* BoxSizer7;
    wxBoxSizer* BoxSizer11;
    wxBoxSizer* BoxSizer13;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer9;
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer8;
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer12;
    wxBoxSizer* BoxSizer14;
    wxBoxSizer* BoxSizer6;
    wxBoxSizer* BoxSizer5;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX, _T("wxID_ANY"));
    SetClientSize(wxSize(650,350));
    SetMinSize(wxSize(650,350));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    m_wUpdateSerialListBtn = new wxBitmapButton(this, ID_BITMAPBUTTON1, wxArtProvider::GetBitmap(wxART_MAKE_ART_ID_FROM_STR(_T("wxART_FIND_AND_REPLACE")),wxART_BUTTON), wxDefaultPosition, wxDefaultSize, wxBU_AUTODRAW, wxDefaultValidator, _T("ID_BITMAPBUTTON1"));
    m_wUpdateSerialListBtn->SetToolTip(_("Update serial devices list"));
    BoxSizer2->Add(m_wUpdateSerialListBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wSerialList = new wxComboBox(this, ID_COMBOBOX1, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
    m_wSerialList->SetToolTip(_("Selected serial device"));
    BoxSizer2->Add(m_wSerialList, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wSpeedchoice = new wxChoice(this, ID_CHOICE1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    m_wSpeedchoice->Append(_("1200"));
    m_wSpeedchoice->Append(_("2400"));
    m_wSpeedchoice->SetSelection( m_wSpeedchoice->Append(_("4800")) );
    m_wSpeedchoice->Append(_("9600"));
    m_wSpeedchoice->Append(_("19200"));
    m_wSpeedchoice->Append(_("38400"));
    m_wSpeedchoice->Append(_("57600"));
    BoxSizer2->Add(m_wSpeedchoice, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wConnBtn = new wxToggleButton(this, ID_TOGGLEBUTTON1, _("Connect"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON1"));
    m_wConnBtn->SetToolTip(_("Serial connection"));
    BoxSizer2->Add(m_wConnBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer14 = new wxBoxSizer(wxHORIZONTAL);
    StaticLine1 = new wxStaticLine(this, ID_STATICLINE1, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE1"));
    BoxSizer14->Add(StaticLine1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer14, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer12 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer3->Add(BoxSizer12, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    m_wDateText = new wxTextCtrl(Panel1, ID_TEXTCTRL1, _("--:--:-- - --/--/----"), wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_CENTRE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    m_wDateText->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    wxFont m_wDateTextFont(10,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    m_wDateText->SetFont(m_wDateTextFont);
    m_wDateText->SetToolTip(_("Actual UTC date & time"));
    BoxSizer4->Add(m_wDateText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(BoxSizer4);
    BoxSizer4->Fit(Panel1);
    BoxSizer4->SetSizeHints(Panel1);
    BoxSizer3->Add(Panel1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wSetBtn = new wxButton(this, ID_BUTTON1, _("Set Date"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    m_wSetBtn->SetToolTip(_("Update GPS date"));
    BoxSizer3->Add(m_wSetBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer11 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer3->Add(BoxSizer11, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer3, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    m_wRXSizer = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer9 = new wxBoxSizer(wxVERTICAL);
    m_wRXText = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY|wxVSCROLL, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    wxFont m_wRXTextFont(9,wxFONTFAMILY_SWISS,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Sans"),wxFONTENCODING_DEFAULT);
    m_wRXText->SetFont(m_wRXTextFont);
    m_wRXText->SetToolTip(_("RX monitor"));
    BoxSizer9->Add(m_wRXText, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wRXSizer->Add(BoxSizer9, 1, wxTOP|wxBOTTOM|wxLEFT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer13 = new wxBoxSizer(wxVERTICAL);
    BoxSizer15 = new wxBoxSizer(wxVERTICAL);
    BoxSizer13->Add(BoxSizer15, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wHoldBtn = new wxToggleButton(this, ID_TOGGLEBUTTON2, _("Hold"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TOGGLEBUTTON2"));
    m_wHoldBtn->SetToolTip(_("Hold RX monitor"));
    BoxSizer13->Add(m_wHoldBtn, 0, wxTOP|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wClearBtn = new wxButton(this, ID_BUTTON2, _("Clear"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    m_wClearBtn->SetToolTip(_("Clear RX monitor"));
    BoxSizer13->Add(m_wClearBtn, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    m_wRXSizer->Add(BoxSizer13, 0, wxALIGN_BOTTOM|wxALIGN_CENTER_HORIZONTAL, 5);
    BoxSizer1->Add(m_wRXSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    StaticLine2 = new wxStaticLine(this, ID_STATICLINE2, wxDefaultPosition, wxSize(10,-1), wxLI_HORIZONTAL, _T("ID_STATICLINE2"));
    BoxSizer8->Add(StaticLine2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer8, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer7 = new wxBoxSizer(wxHORIZONTAL);
    BoxSizer5->Add(BoxSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer6 = new wxBoxSizer(wxHORIZONTAL);
    m_wQuitBtn = new wxButton(this, ID_BUTTON3, _("Quit"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    m_wQuitBtn->SetToolTip(_("Exiting"));
    BoxSizer6->Add(m_wQuitBtn, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5->Add(BoxSizer6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer1->Add(BoxSizer5, 0, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(BoxSizer1);
    w_SingleInstanceChecker.Create(_T("JupiDate_") + wxGetUserId() + _T("_Guard"));
    if (w_SingleInstanceChecker.IsAnotherRunning())
    {
          wxMessageDialog dial(NULL, _T("Another instance is already running. Exiting."), _T("Warning !"), (wxOK|wxICON_EXCLAMATION|wxCENTRE));
          dial.ShowModal();
          exit(1);
    }
    m_wDateTimeTimer.SetOwner(this, ID_TIMER1);
    m_wDateTimeTimer.Start(500, false);
    m_wRXTimer.SetOwner(this, ID_TIMER2);
    m_wRXTimer.Start(10, false);
    SetSizer(BoxSizer1);
    Layout();

    Connect(ID_BITMAPBUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&JupiDateFrame::OnBitmapButton1Click);
    Connect(ID_TOGGLEBUTTON1,wxEVT_COMMAND_TOGGLEBUTTON_CLICKED,(wxObjectEventFunction)&JupiDateFrame::Onm_wConnBtnToggle);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&JupiDateFrame::Onm_wSetBtnClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&JupiDateFrame::Onm_wClearBtnClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&JupiDateFrame::Onm_wQuitBtnClick);
    Connect(ID_TIMER1,wxEVT_TIMER,(wxObjectEventFunction)&JupiDateFrame::OnTimer1Trigger);
    Connect(ID_TIMER2,wxEVT_TIMER,(wxObjectEventFunction)&JupiDateFrame::OnTimer2Trigger);
    //*)

    SetTitle(appName + wxT(" v") + wxString::FromAscii(AutoVersion::FULLVERSION_STRING));


    // Use embedded image as icon
#if defined(WIN32)
    SetIcon(wxICON(JupiDate_Icon));
#else
    wxIcon              micon;
    wxMemoryInputStream istream(Jupiter_icon_PNG, sizeof(Jupiter_icon_PNG));
    wxImage             mimg(istream, wxBITMAP_TYPE_ANY); /* or wxBITMAP_TYPE_ANY, etc. */

    mimg.SetMaskColour(221, 173, 115); // Set color mask

    wxBitmap mbmp(mimg);

    micon.CopyFromBitmap(mbmp);
    SetIcon(micon);
#endif

    _enableSizerChilds(m_wRXSizer, false);

    _updateSerialList();
}

JupiDateFrame::~JupiDateFrame()
{
    //(*Destroy(JupiDateFrame)
    //*)
    m_wDateTimeTimer.Stop();
    m_wRXTimer.Stop();
    _closeSerialPort();
}

void JupiDateFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void JupiDateFrame::OnTimer1Trigger(wxTimerEvent& event)
{
    _updateDateTime();
}

void JupiDateFrame::OnBitmapButton1Click(wxCommandEvent& event)
{
    _updateSerialList();
}

void JupiDateFrame::Onm_wSetBtnClick(wxCommandEvent& event)
{
    wxDateTime  dt = wxDateTime::Now();
    char        buffer[80] = "";

    // NMEA line to send (format):
    // $PRWIINIT,A,,,,,,,,,,,,000000,DDMMYY<CR><LF>
    sprintf(buffer, "%s%02d%02d%02d%c%c", "$PRWIINIT,A,,,,,,,,,,,,000000,",
            dt.GetDay(wxDateTime::UTC), dt.GetMonth(wxDateTime::UTC) + 1, dt.GetYear(wxDateTime::UTC) - (dt.GetCentury() * 100),
            '\r', '\n');

    if (m_devicePort.Write(buffer, strlen(buffer)) != (int)strlen(buffer))
    {
        wxMessageDialog(this, wxT("Setting new date to GPS has failed:\n") + wxString(wxSysErrorMsg()), wxT("Error..."), wxOK | wxCAPTION | wxICON_ERROR).ShowModal();

        m_wSetBtn->Enable(false);
        m_wSerialList->Enable();
        m_wSpeedchoice->Enable();
        m_wUpdateSerialListBtn->Enable();
        _enableSizerChilds(m_wRXSizer, false);
        m_wConnBtn->SetValue(false);
        _closeSerialPort();
    }
    else
        wxMessageDialog(this, wxT("GPS has been updated"), wxT("Success..."), wxOK | wxCAPTION | wxICON_INFORMATION).ShowModal();
}

void JupiDateFrame::OnTimer2Trigger(wxTimerEvent& event)
{
    if (m_deviceBase)
    {
        char buffer[255] = "";
        int  len = m_devicePort.Read(buffer, sizeof(buffer) - 1);

        if (len > 0)
        {
            buffer[len] = '\0';

            if (!m_wHoldBtn->GetValue())
                m_wRXText->AppendText(wxString::FromAscii(buffer));
        }
    }
}

void JupiDateFrame::Onm_wConnBtnToggle(wxCommandEvent& event)
{
    if (m_wConnBtn->GetValue())
    {
        if(m_devicePort.Open((const char *)m_wSerialList->GetValue().ToAscii(), wxAtoi(m_wSpeedchoice->GetString(m_wSpeedchoice->GetSelection())), "8N1", ctb::SerialPort::NoFlowControl ) >= 0)
        {
            m_deviceBase = &m_devicePort;

            m_wSetBtn->Enable();
            m_wSerialList->Enable(false);
            m_wSpeedchoice->Enable(false);
            m_wUpdateSerialListBtn->Enable(false);
            _enableSizerChilds(m_wRXSizer, true);
        }
        else
        {
            wxMessageDialog(this, wxT("Could not open serial port ") + m_wSerialList->GetValue()
                            + wxT(" : \n") + wxString(wxSysErrorMsg()), wxT("Error..."), wxOK | wxCAPTION | wxICON_ERROR).ShowModal();
            m_deviceBase = NULL;

            m_wSetBtn->Enable(false);
            m_wSerialList->Enable();
            m_wSpeedchoice->Enable();
            m_wUpdateSerialListBtn->Enable();
            _enableSizerChilds(m_wRXSizer, false);
            m_wConnBtn->SetValue(false);

            return;
        }

        m_wConnBtn->SetLabel(wxT("Disconnect"));
    }
    else
        _closeSerialPort();
}

void JupiDateFrame::Onm_wClearBtnClick(wxCommandEvent& event)
{
    m_wRXText->Clear();
}

void JupiDateFrame::Onm_wQuitBtnClick(wxCommandEvent& event)
{
    Close();
}
