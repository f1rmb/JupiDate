/***************************************************************
 * Name:      JupiDateMain.h
 * Purpose:   Defines Application Frame
 * Author:    Daniel Caujolle-Bert (danielvador@gmail.com)
 * Created:   2015-12-30
 * Copyright: Daniel Caujolle-Bert (http://naboo.homelinux.org)
 * License:   GPL v2
 **************************************************************/

#ifndef JUPIDATEMAIN_H
#define JUPIDATEMAIN_H

//(*Headers(JupiDateFrame)
#include <wx/bmpbuttn.h>
#include <wx/combobox.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/snglinst.h>
#include <wx/statline.h>
#include <wx/frame.h>
#include <wx/tglbtn.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/utils.h>
#include <wx/timer.h>
//*)

#include <vector>
#include <ctb-0.16/ctb.h>


class JupiDateFrame: public wxFrame
{
    public:
        JupiDateFrame(wxWindow* parent, wxString appName, wxWindowID id = -1);
        virtual ~JupiDateFrame();

    private:
        void _enableSizerChilds(wxSizer *sizer, bool enable);
        void _updateSerialList();
        void _updateDateTime();
        void _closeSerialPort();

        //(*Handlers(JupiDateFrame)
        void OnQuit(wxCommandEvent& event);
        void Onm_wSerListUpdateBtnClick(wxCommandEvent& event);
        void OnTimer1Trigger(wxTimerEvent& event);
        void OnBitmapButton1Click(wxCommandEvent& event);
        void Onm_wSetBtnClick(wxCommandEvent& event);
        void OnTimer2Trigger(wxTimerEvent& event);
        void Onm_wAutoscrollCBClick(wxCommandEvent& event);
        void Onm_wConnBtnToggle(wxCommandEvent& event);
        void Onm_wClearBtnClick(wxCommandEvent& event);
        void Onm_wQuitBtnClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(JupiDateFrame)
        static const long ID_BITMAPBUTTON1;
        static const long ID_COMBOBOX1;
        static const long ID_CHOICE1;
        static const long ID_TOGGLEBUTTON1;
        static const long ID_STATICLINE1;
        static const long ID_TEXTCTRL1;
        static const long ID_PANEL1;
        static const long ID_BUTTON1;
        static const long ID_TEXTCTRL2;
        static const long ID_TOGGLEBUTTON2;
        static const long ID_BUTTON2;
        static const long ID_STATICLINE2;
        static const long ID_BUTTON3;
        static const long ID_TIMER1;
        static const long ID_TIMER2;
        //*)

        //(*Declarations(JupiDateFrame)
        wxToggleButton* m_wConnBtn;
        wxPanel* Panel1;
        wxStaticLine* StaticLine2;
        wxSingleInstanceChecker w_SingleInstanceChecker;
        wxChoice* m_wSpeedchoice;
        wxBoxSizer* m_wRXSizer;
        wxToggleButton* m_wHoldBtn;
        wxBitmapButton* m_wUpdateSerialListBtn;
        wxStaticLine* StaticLine1;
        wxTimer m_wRXTimer;
        wxTextCtrl* m_wRXText;
        wxComboBox* m_wSerialList;
        wxTextCtrl* m_wDateText;
        wxTimer m_wDateTimeTimer;
        wxButton* m_wSetBtn;
        wxButton* m_wQuitBtn;
        wxButton* m_wClearBtn;
        //*)

        wxArrayString    m_serialArray;
        ctb::IOBase     *m_deviceBase;
        ctb::SerialPort  m_devicePort;

        DECLARE_EVENT_TABLE()
};

#endif // JUPIDATEMAIN_H
