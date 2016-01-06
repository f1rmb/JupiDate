/***************************************************************
 * Name:      JupiDateMain.h
 * Purpose:   Defines Application Frame
 * Author:    Daniel Caujolle-Bert (danielvador@gmail.com)
 * Created:   2015-12-30
 * Copyright: Daniel Caujolle-Bert (http://naboo.homelinux.org)
 * License:
 **************************************************************/

#ifndef JUPIDATEMAIN_H
#define JUPIDATEMAIN_H

//(*Headers(JupiDateFrame)
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/tglbtn.h>
#include <wx/statline.h>
#include <wx/panel.h>
#include <wx/snglinst.h>
#include <wx/choice.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/utils.h>
#include <wx/frame.h>
#include <wx/timer.h>
#include <wx/combobox.h>
//*)

#include <vector>
#include <ctb-0.16/ctb.h>


class JupiDateFrame: public wxFrame
{
    public:
        JupiDateFrame(wxWindow* parent, wxWindowID id = -1);
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
        static const long ID_STATICLINE3;
        static const long ID_TEXTCTRL1;
        static const long ID_PANEL1;
        static const long ID_BUTTON1;
        static const long ID_TEXTCTRL2;
        static const long ID_TOGGLEBUTTON2;
        static const long ID_BUTTON2;
        static const long ID_STATICLINE1;
        static const long ID_BUTTON3;
        static const long ID_TIMER1;
        static const long ID_TIMER2;
        //*)

        //(*Declarations(JupiDateFrame)
        wxBitmapButton* m_wUpdateSerialListBtn;
        wxButton* m_wQuitBtn;
        wxBoxSizer* m_wRXSizer;
        wxTextCtrl* m_wRXText;
        wxTimer m_wRXTimer;
        wxComboBox* m_wSerialList;
        wxPanel* Panel1;
        wxChoice* m_wSpeedchoice;
        wxToggleButton* m_wHoldBtn;
        wxStaticLine* StaticLine3;
        wxStaticLine* StaticLine1;
        wxToggleButton* m_wConnBtn;
        wxButton* m_wClearBtn;
        wxTextCtrl* m_wDateText;
        wxSingleInstanceChecker w_SingleInstanceChecker;
        wxTimer m_wDateTimeTimer;
        wxButton* m_wSetBtn;
        //*)

        wxArrayString    m_serialArray;
        ctb::IOBase     *m_deviceBase;
        ctb::SerialPort  m_devicePort;

        DECLARE_EVENT_TABLE()
};

#endif // JUPIDATEMAIN_H
