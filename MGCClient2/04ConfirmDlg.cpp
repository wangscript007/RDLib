#include "StdAfx.h"
#include "04ConfirmDlg.h"



C04ConfirmDlg::C04ConfirmDlg(void)
{
}


C04ConfirmDlg::~C04ConfirmDlg(void)
{
}

void C04ConfirmDlg::Init()
{
	::ShowWindow( m_hWnd, SW_MAXIMIZE );
	//CLayeredDialogBase::Init();
}

LRESULT C04ConfirmDlg::OnClose( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	//EndModal( IDCANCEL );
	ShowWindow( false );
	return 0;
}

CControlUI* C04ConfirmDlg::CreateControl( LPCTSTR pstrClass )
{
	return NULL;
}

void C04ConfirmDlg::Notify( TNotifyUI& msg )
{
	CStringW	strSenderName = msg.pSender->GetName();
	CStringW	strType = msg.sType;

	if( strType == L"click")
	{
		if( strSenderName == L"bnOK" )
		{
			//EndModal( IDOK );
			//ShowWindow( false );
			//开始下机操作
			::PostMessage(GlobalData::Instance()->getMainHwnd(),WM_MCG_CONFIRM_LOG_OUT,0,0);
		}
		else if( strSenderName == L"bnCancel" )
		{
			//EndModal( IDCANCEL );
			//ShowWindow( false );
			::PostMessage(GlobalData::Instance()->getMainHwnd(),WM_MCG_CONFIRM_CANCEL,0,0);
		}
	}
	else if( strType == L"timer" )
	{
	}
}

LRESULT C04ConfirmDlg::HandleMessage( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return CDialogBase::HandleMessage(uMsg, wParam, lParam);
}


