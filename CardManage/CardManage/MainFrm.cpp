// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "CardManage.h"
#include "MainFrm.h"





#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int iThread;
CArchive*   m_CurrentArchive;

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()

	ON_COMMAND(ID_PcscReader_Combo, &CMainFrame::OnPcscreaderCombo)
	ON_COMMAND(ID_GetFileSystem_Check, &CMainFrame::OnGetfilesystemCheck)
	ON_COMMAND(ID_Connect_button, &CMainFrame::OnConnectbutton)
	ON_COMMAND(ID_Disconnect_button, &CMainFrame::OnDisconnectbutton)
	ON_COMMAND(ID_GetFileSystem_button, &CMainFrame::OnGetfilesystembutton)
	ON_COMMAND(ID_MapFileList_button, &CMainFrame::OnMapfilelistbutton)
	ON_COMMAND(ID_MapAllFileList_button, &CMainFrame::OnMapallfilelistbutton)
	ON_COMMAND(ID_ChangeFileValue_button, &CMainFrame::OnChangefilevaluebutton)
	ON_COMMAND(ID_WarmReset_Button, &CMainFrame::OnWarmresetButton)
	ON_COMMAND(ID_ColdReset_Button, &CMainFrame::OnColdresetButton)
	ON_COMMAND(ID_SendCommand_Button, &CMainFrame::OnSendcommandButton)
	ON_COMMAND(ID_SearchFile_Button, &CMainFrame::OnSearchfileButton)
	ON_COMMAND(ID_SearchFiles_Button, &CMainFrame::OnSearchfilesButton)
	ON_COMMAND(ID_EndProgress_Button, &CMainFrame::OnEndprogressButton)
	ON_COMMAND(ID_OutputWnd_Check, &CMainFrame::OnOutputwndCheck)
	ON_COMMAND(ID_StatusBar_Check, &CMainFrame::OnStatusbarCheck)
	//ON_COMMAND(ID_ReaderMode_Check, &CMainFrame::OnReadermodeCheck)
	//ON_COMMAND(ID_IsUICC_Check, &CMainFrame::OnIsuiccCheck)
	ON_COMMAND(ID_KeysSetting_Button, &CMainFrame::OnKeyssettingButton)
	ON_COMMAND(ID_USIM, &CMainFrame::OnUsim)
	ON_COMMAND(ID_USIM_Button, &CMainFrame::OnUsimButton)
	ON_COMMAND(ID_AppList_Check, &CMainFrame::OnApplistCheck)
	ON_COMMAND(ID_SetUpMenu_Button, &CMainFrame::OnSetupmenuButton)
	ON_COMMAND(ID_GetAppList_Button, &CMainFrame::OnGetapplistButton)
	ON_COMMAND(ID_PinStatus_Check, &CMainFrame::OnPinstatusCheck)
	//ON_COMMAND(ID_GetAppList_Check, &CMainFrame::OnGetapplistCheck)
	//ON_COMMAND(ID_GetPinStatus_Check, &CMainFrame::OnGetpinstatusCheck)
	ON_COMMAND(ID_UST_Button, &CMainFrame::OnUstButton)
	ON_COMMAND(ID_ADN_Button, &CMainFrame::OnAdnButton)
	ON_COMMAND(ID_SMS_Button, &CMainFrame::OnSmsButton)
	ON_COMMAND(ID_ReaderType_Button, &CMainFrame::OnReadertypeButton)
	ON_COMMAND(ID_PCSCReader_Button, &CMainFrame::OnPCSCReaderButton)
	ON_COMMAND(ID_CCR5Reader_Button, &CMainFrame::OnCCR5ReaderButton)
	ON_COMMAND(ID_CCR5Setting_Button, &CMainFrame::OnCCR5SettingButton)
	ON_COMMAND(ID_Reset_CT_Button, &CMainFrame::OnResetCTButton)
	ON_COMMAND(ID_Disconnect_Terminal_Button, &CMainFrame::OnDisconnectTerminalButton)
	ON_COMMAND(ID_Connect_Terminal_Button, &CMainFrame::OnConnectTerminalButton)
	ON_COMMAND(ID_Request_ICC_Button, &CMainFrame::OnRequestICCButton)
	ON_COMMAND(ID_Eject_ICC_Button, &CMainFrame::OnEjectICCButton)
	ON_COMMAND(ID_Send_Command_To_Terminal_Button, &CMainFrame::OnSendCommandToTerminalButton)
	ON_COMMAND(ID_PowerOn_Button, &CMainFrame::OnPowerOnButton)
	ON_COMMAND(ID_PowerOff_Butoon, &CMainFrame::OnPowerOffButton)
	ON_COMMAND(ID_SuspendProgress_Button, &CMainFrame::OnSuspendprogressButton)
	ON_COMMAND(ID_GetPinCounter_Button, &CMainFrame::OnGetPinCounterButton)
	ON_WM_DROPFILES()
	ON_WM_CLOSE()
	ON_WM_SIZING()
	ON_WM_SIZE()
	ON_WM_CHANGEUISTATE()
	
	ON_COMMAND_RANGE(ID_VerifyPin01_Button,ID_UnblockPin81_Button, &CMainFrame::OnVerifypinButton)
	ON_COMMAND_RANGE(ID_New_CTC, ID_CMCC_M2M_20, &CMainFrame::OnOpenModule)

	ON_UPDATE_COMMAND_UI_RANGE(ID_PCSCReader_Button, ID_PcscReader_Combo, &CMainFrame::OnUpdateTeminalDisconnected)
	ON_UPDATE_COMMAND_UI_RANGE(ID_CCR5Setting_Button,ID_PowerOff_Butoon, &CMainFrame::OnUpdateIsCCR5)
	ON_UPDATE_COMMAND_UI_RANGE(ID_IsUICC_Check,ID_ReaderMode_Check, &CMainFrame::OnUpdateTeminalDisconnected)
	ON_UPDATE_COMMAND_UI_RANGE(ID_GetFileSystem_Check,ID_GetPinStatus_Check, &CMainFrame::OnUpdateTeminalDisconnected)
	ON_UPDATE_COMMAND_UI(ID_Connect_button,&CMainFrame::OnUpdateTeminalDisconnected)
	ON_UPDATE_COMMAND_UI_RANGE(ID_Disconnect_button,ID_SendCommand_Button,&CMainFrame::OnUpdateTeminalConnected)
	ON_UPDATE_COMMAND_UI_RANGE(ID_MapFileList_button,ID_WriteADN_Button,&CMainFrame::OnUpdateThreadFreeCardConnected)
	ON_UPDATE_COMMAND_UI_RANGE(ID_USIM_Button,ID_SMS_Button,&CMainFrame::OnUpdateThreadFreeCardConnected)
	ON_UPDATE_COMMAND_UI_RANGE(ID_New_CTC,ID_CMCC_M2M_20,&CMainFrame::OnUpdateThreadFree)
	ON_UPDATE_COMMAND_UI_RANGE(ID_GetARR_Check,ID_AutoVerifyPin_Check,&CMainFrame::OnUpdateThreadFree)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VerifyPin01_Button,ID_EraseFlash_Button,&CMainFrame::OnUpdateThreadFreeCardConnected)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SuspendProgress_Button,ID_EndProgress_Button,&CMainFrame::OnUpdateThreadBusyCardConnected)
	ON_UPDATE_COMMAND_UI_RANGE(ID_OutputWnd_Check,ID_Reference_Check,&CMainFrame::OnUpdateCheck)

	ON_COMMAND_RANGE(ID_IsUICC_Check,ID_AutoVerifyPin_Check,&CMainFrame::OnSettingCheck)
	ON_COMMAND_RANGE(ID_APDUINFO_Check,ID_OTA_Decrypt_Check,&CMainFrame::OnSettingCheck)

	


	ON_COMMAND(ID_Export_Excel_Button, &CMainFrame::OnExportExcelButton)
	ON_WM_DESTROY()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_GeFlashData_Button, &CMainFrame::OnGeflashdataButton)
	ON_COMMAND(ID_EraseFlash_Button, &CMainFrame::OnEraseflashButton)
	ON_COMMAND(ID_GetFlash_Check, &CMainFrame::OnGetflashCheck)
	ON_COMMAND(ID_Import_Excel_Button, &CMainFrame::OnImportExcelButton)
	//ON_COMMAND(ID_APDUINFO_Check, &CMainFrame::OnApduinfoCheck)
	//ON_COMMAND(ID_OTAINFO_Check, &CMainFrame::OnOtainfoCheck)
	//ON_COMMAND(ID_OTA_Decrypt_Check, &CMainFrame::OnOtaDecrypt)
	ON_COMMAND(ID_ReFormatFlash_Button, &CMainFrame::OnReformatflashButton)
	ON_WM_PAINT()
	ON_WM_SYSCOLORCHANGE()
	ON_COMMAND(ID_Reference_Check, &CMainFrame::OnReferenceCheck)
	ON_COMMAND(ID_Explain_Button, &CMainFrame::OnExplainButton)
	ON_COMMAND(ID_ReConvert_button, &CMainFrame::OnReconvertbutton)
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
}



int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	//return FALSE;

	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;



	//此处创建 Ribbon
	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	Initialize_Ribbon();

	InitParamater();

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	CString strTitlePane1;
	CString strTitlePane2;
	CString strTitlePane3;
	CString strTitlePane4;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	bNameValid = strTitlePane3.LoadString(IDS_STATUS_PANE3);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE3, strTitlePane3, TRUE), strTitlePane3);


	//m_wndStatusBar.AddDynamicElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE3, strTitlePane3, TRUE));

	bNameValid = strTitlePane4.LoadString(IDS_STATUS_PANE4);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE4, strTitlePane4, TRUE), strTitlePane4);
		//m_wndStatusBar.AddDynamicElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE4, strTitlePane4, TRUE));


	m_ElementATR = m_wndStatusBar.GetExElement(1);
	m_ElementSta = m_wndStatusBar.GetExElement(0);
	m_ElementThr = m_wndStatusBar.GetElement(0);
	m_ElementPro = m_wndStatusBar.GetElement(1);

	m_wndStatusBar.RedrawWindow();



	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 创建停靠窗口
	if (!CreateDockingWindows())
	{
		TRACE0("未能创建停靠窗口\n");
		return -1;
	}

	m_wndOutput.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndOutput);

	m_wndGetFlash.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndGetFlash);

	m_wndLeftPane.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndLeftPane);

	m_wndPinStatus.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndPinStatus);

	m_wndReference.EnableDocking(CBRS_ALIGN_ANY);
	DockPane(&m_wndReference);
	
	m_dlgChangeFile.Create(IDD_ChangeFile_Dialog,NULL);
	m_dlgChangeFile.ShowWindow(SW_HIDE);

	m_dlgSearchFile.Create(IDD_SearchFile_Dialog,NULL);
	m_dlgSearchFile.ShowWindow(SW_HIDE);

	m_dlgSendCommand.Create(IDD_SendCommand_Dialog,NULL);
	//m_dlgSendCommand.InitCommandList();
	//m_dlgSendCommand.InitCommandFile();
	m_dlgSendCommand.InitContrl();
	m_dlgSendCommand.ShowWindow(SW_HIDE);

	m_wndKeySetting.Create(IDD_KeySetting_Dialog,NULL);
	m_wndKeySetting.Initialize_Dialog();

	//CString csPath;
	//csPath = AfxGetApp()->GetProfileString(_T("Settings\\Start"),
	//	((CCardManageApp*) AfxGetApp())->GetSettingName(Def_KeySettingPath),
	//	_T(""));
	//if (csPath.IsEmpty())
	//{
	//	__GetCurrentDIR(csPath);
	//	csPath = csPath+_T("\\INI\\KeySetting.ini");
	//}

	//m_wndKeySetting.OpenKeySetting(csPath); 
	m_wndKeySetting.ShowWindow(SW_HIDE);

	m_wndSIMToolkit.Create(IDD_SIMToolkit_Dialog,NULL);
	m_wndSIMToolkit.ShowWindow(SW_HIDE);

	m_wndUST.Create(IDD_UST_Dialog,NULL);
	m_wndUST.ShowWindow(SW_HIDE);
	iThread = Def_Thread_Free;

	m_dlgADN.Create(IDD_AbbreviatedDiallingNumbers_Dialog);
	m_dlgADN.InitContrl();
	m_dlgADN.InitParameter();
	m_dlgADN.ShowWindow(SW_HIDE);


	m_dlgSMS.Create(IDD_ShortMessage_Dialog);
	m_dlgSMS.InitContrl();
	m_dlgSMS.InitParameter();
	m_dlgSMS.ShowWindow(SW_HIDE);

	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);


	m_hAccel= ::LoadAccelerators(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,CCreateContext* pContext)
{
	// 创建拆分窗口
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	CRect rectWindows;

	GetWindowRect(&rectWindows);
	int ix,iy;
	int iLX,iRX;

	ix = rectWindows.Width();
	iy = rectWindows.Height();

	iLX = (ix>300?300:ix/2);
	iRX = ix - iLX;

	
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(iLX, iy), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CCardManageView), CSize(iRX, iy), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	m_wndClassView  = (CLeftView*) m_wndSplitter.GetPane(0,0); 
	m_wndProperties = (CCardManageView*) m_wndSplitter.GetPane(0,1); 

	//m_wndProperties->RedrawWindow();

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

BOOL CMainFrame::CreateDockingWindows()
{
	BOOL bNameValid;
	// 创建输出窗口
	CString strOutputWnd;
	bNameValid = strOutputWnd.LoadString(IDS_OUTPUT_WND);
	ASSERT(bNameValid);
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建输出窗口\n");
		return FALSE; // 未能创建
	}


	
	DWORD dwNoCloseBarStyle = AFX_DEFAULT_DOCKING_PANE_STYLE & ~AFX_CBRS_CLOSE; 


	CString strGetFlashPane;
	bNameValid = strGetFlashPane.LoadString(IDS_PANE_GETFLASH);
	ASSERT(bNameValid);
	if (!m_wndGetFlash.Create(strGetFlashPane, this, CRect(0, 0, 200, 200), TRUE,ID_PANE_GETFLASH,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI)) 
	{
		TRACE0("未能创建输出窗口\n");
		return FALSE; // 未能创建
	}

	

	CString strLeftPane;
	bNameValid = strLeftPane.LoadString(IDS_LEFTPANE_WND);
	ASSERT(bNameValid);
	
	if (!m_wndLeftPane.Create(strLeftPane, this, CRect(0, 0, 200, 200), TRUE,ID_PANE_LEFTWND, 
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI)) 
	{
		TRACE0("未能创建应用窗口\n");
	//	return FALSE; // 未能创建
	}

	if (!m_wndPinStatus.Create(_T("Pin状态"), this, CRect(0, 0, 200, 200),TRUE, ID_PANE_PINSTATUS,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI)) 
	{
		TRACE0("未能创建应用窗口\n");
		//	return FALSE; // 未能创建
	}


	if (!m_wndReference.Create(_T("参考"), this, CRect(0, 0, 100, 100),TRUE,ID_VIEW_REFERENCE, 
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建输出窗口\n");
		return FALSE; // 未能创建
	}



	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

	m_wndGetFlash.SetIcon(hOutputBarIcon, FALSE);
	m_wndReference.SetIcon(hOutputBarIcon, FALSE);

	HICON hAppListBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_APPLIST_WND : IDI_APPLIST_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndLeftPane.SetIcon(hAppListBarIcon, FALSE);

	HICON hPinStatusBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_PINSTATUS_WND : IDI_PINSTATUS_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndPinStatus.SetIcon(hPinStatusBarIcon, FALSE);

}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);

		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		//m_wndProperties->UpdateFonts();
		//m_wndOutput.UpdateFonts();
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		//m_wndProperties->UpdateFonts();
		//m_wndOutput.UpdateFonts();
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		


	//	cT13 = CMFCVisualManager::get(&(m_wndProperties->m_wndPropExplain));
		


	}
	

	((CCardManageApp*)AfxGetApp)->InstallFont();
	UpdateFont();
	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);
	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
	

}
void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}
void CMainFrame::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CFrameWndEx::OnSettingChange(uFlags, lpszSection);
	m_wndOutput.UpdateFonts();
	m_wndGetFlash.UpdateFonts();
}
void CMainFrame::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CFrameWndEx::OnDropFiles(hDropInfo);

}
void CMainFrame::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (iThread != Def_Thread_Free)
	{
		if (MessageBox("关闭程序,需要先结束进行中进程! \n是否确认结束进行!",NULL,MB_OKCANCEL) == IDOK)
		{
			iThread = Def_Thread_Ending;

			TerminateThread(hThread,4);

			iThread = Def_Thread_Free;

		}
		else
			return;

	}


	CFrameWndEx::OnClose();

}
void CMainFrame::OnPcscreaderCombo()
{
	// TODO: 在此添加命令处理程序代码
}
void CMainFrame::OnChangefilevaluebutton()
{
	if ((iThread == Def_Thread_Free)&&(iReaderStatus == 0)&&(bReadMode == true))
		Changefilevalue();
}
void CMainFrame::OnConnectbutton()
{
	if (Connect_Card())
	{
		if (bGetAppList)
		{
			_MapTeleApplicaiton();
			m_wndLeftPane.TransationAppList(csAppList);
		}

		if (bGetPinSta)
		{
			GetPinStatus();
		}

		if (bGetFileSystem)
			MapFile();	

		NewSetStatusThread();
	}	


}
void CMainFrame::OnDisconnectbutton()
{
	csCardATR.Empty();

	switch(iReaderType)
	{
	case Def_ReaderType_PCSC:PcscReader.DisConnectReader();break;
	case Def_ReaderType_CCR5:CCR5_DisConnectTerminal(CCR5Hand);break;
	default:break;
	}

	iReaderStatus = Def_Terminal_Disconnected;

	NewSetStatusThread();
	m_dlgChangeFile.SetCurrentFileInformation(NULL,NULL);
	//_SetCurrentStatus();

}
void CMainFrame::OnGetfilesystembutton()
{
	if ((iThread == Def_Thread_Free)&&(iReaderStatus == Def_Card_Connected)&&(bReadMode == true))
	{
		NewSaveCurrentCardThread();
		NewSetStatusThread();
	}

}
void CMainFrame::OnGetfilesystemCheck()
{
	bGetFileSystem = !bGetFileSystem;
}
void CMainFrame::OnWarmresetButton()
{
	if ((iThread == Def_Thread_Free)&&(iReaderStatus == Def_Card_Connected)&&(bReadMode == true))
	{
		if (!_TestCaseWarmReset())
			OnDisconnectbutton();	
		uiVerifyPIN  = 0;
		m_wndPinStatus.Insatll_PinVerifyStatus(uiVerifyPIN);
		m_dlgChangeFile.SetCurrentFileInformation(NULL,NULL);
	}
}
void CMainFrame::OnColdresetButton()
{

	if ((iThread == Def_Thread_Free)&&(iReaderStatus != Def_Terminal_Disconnected)&&(bReadMode == true))
	{
		if (!_TestCaseColdReset())
			OnDisconnectbutton();	
		uiVerifyPIN = 0;
		m_wndPinStatus.Insatll_PinVerifyStatus(uiVerifyPIN);
		m_dlgChangeFile.SetCurrentFileInformation(NULL,NULL);
	}

}
void CMainFrame::OnSendcommandButton()
{

	if ((iThread == Def_Thread_Free)&&(iReaderStatus == Def_Card_Connected)&&(bReadMode == true))
		m_dlgSendCommand.ShowWindow(SW_SHOW);

}
void CMainFrame::OnSearchfileButton()
{
	if ((iThread == Def_Thread_Free)&&(iReaderStatus == Def_Card_Connected)&&(bReadMode == true))
		SearchFile( m_wndClassView->GetSelectedItem(),false);
}
void CMainFrame::OnSearchfilesButton()
{
	if ((iThread == Def_Thread_Free)&&(iReaderStatus == Def_Card_Connected)&&(bReadMode == true))
		SearchFile( m_wndClassView->GetSelectedItem(),true);
}
void CMainFrame::OnEndprogressButton()
{
	//如果为暂停，则需要继续进程
	if ((iThread&Def_Thread_Suspend) == Def_Thread_Suspend)
		ResumeThread(hThread);

	if ((iThread != Def_Thread_Free)&&(bReadMode == true))
		iThread = Def_Thread_Ending;
}
void CMainFrame::OnSuspendprogressButton()
{
	//当前状态没有处于空闲和结束中状态
	if ((iThread != Def_Thread_Free)&&
		(iThread != Def_Thread_Ending)&&
		(bReadMode == true))
	{

		if ((iThread&Def_Thread_Suspend) == Def_Thread_Suspend)
		{
			ResumeThread(hThread);
			iThread = iThread&0xFF;
		}
		else
		{

			SuspendThread(hThread);
			iThread = iThread|Def_Thread_Suspend;
		}	
	}
}
//void CMainFrame::OnReadermodeCheck()
//{
//	bReadMode = !bReadMode;
//}
void CMainFrame::OnOutputwndCheck()
{
	if (m_wndOutput.IsVisible())
		m_wndOutput.ShowPane(FALSE,FALSE,TRUE);
	else
	{
		m_wndOutput.SetAutoHideMode(FALSE,CBRS_ALIGN_ANY);
		m_wndOutput.ShowPane(TRUE,FALSE,TRUE);
	}


	//SendMessage(WM_SIZE);

}
void CMainFrame::OnStatusbarCheck()
{
	if (m_wndStatusBar.IsWindowVisible())
		//m_wndStatusBar.ShowPane(FALSE,FALSE,TRUE);
		m_wndStatusBar.ModifyStyle(WS_VISIBLE,0);
	else
		m_wndStatusBar.ModifyStyle(0,WS_VISIBLE);
	//m_wndStatusBar.ShowPane(TRUE,FALSE,TRUE);

	SendMessage(WM_SIZE);
	RedrawWindow();
}
//void CMainFrame::OnIsuiccCheck()
//{
//	bIsUICC = !bIsUICC;
//	
//	if (bIsUICC)
//	{
//		m_dlgADN.SetAbbreviatedDiallingNumbersType(_DEF_PhoneBook_3GPP);
//		m_dlgSMS.SetShortMessageType(_DEF_SMS_3GPP);
//	}
//	else
//	{
//		m_dlgADN.SetAbbreviatedDiallingNumbersType(_DEF_PhoneBook_GSM);
//		m_dlgSMS.SetShortMessageType(_DEF_SMS_GSM);
//	}
//}
void CMainFrame::OnKeyssettingButton()
{
	//m_wndKeySetting.OpenKeySetting(GetCurrentDIR()+_T("\\INI\\KeySetting.ini")); 
	m_wndKeySetting.ShowWindow(SW_SHOW);
}
void CMainFrame::OnUsim()
{
	if (!m_wndSIMToolkit.IsWindowVisible())
	{
		m_wndSIMToolkit.ShowWindow(SW_SHOW);
	}
}
void CMainFrame::OnUsimButton()
{
	OnUsim();
}


void CMainFrame::OnApplistCheck()
{
	if (m_wndLeftPane.IsVisible())
		m_wndLeftPane.ShowPane(FALSE,FALSE,TRUE);
	else
	{
		m_wndLeftPane.SetAutoHideMode(FALSE,CBRS_ALIGN_ANY);
		m_wndLeftPane.ShowPane(TRUE,FALSE,TRUE);
	}
}

void CMainFrame::OnPinstatusCheck()
{
	if (m_wndPinStatus.IsVisible())
		m_wndPinStatus.ShowPane(FALSE,FALSE,TRUE);
	else
	{
		m_wndPinStatus.SetAutoHideMode(FALSE,CBRS_ALIGN_ANY);
		m_wndPinStatus.ShowPane(TRUE,FALSE,TRUE);
	}

}

void CMainFrame::OnGetflashCheck()
{
	if (m_wndGetFlash.IsVisible())
		m_wndGetFlash.ShowPane(FALSE,FALSE,TRUE);
	else
	{
		m_wndGetFlash.SetAutoHideMode(FALSE,CBRS_ALIGN_ANY);
		m_wndGetFlash.ShowPane(TRUE,FALSE,TRUE);
	}

}

void CMainFrame::OnReferenceCheck()
{
	if (m_wndReference.IsVisible())
		m_wndReference.ShowPane(FALSE,FALSE,TRUE);
	else
	{
		m_wndReference.SetAutoHideMode(FALSE,CBRS_ALIGN_ANY);
		m_wndReference.ShowPane(TRUE,FALSE,TRUE);
	}
}



void CMainFrame::OnMapfilelistbutton()
{
	MapFile();	
}
void CMainFrame::OnMapallfilelistbutton()
{
	MapAllFile();
}
void CMainFrame::OnSetupmenuButton()
{
	m_wndSIMToolkit.StartSIMToolkit();
	OnUsimButton();
}
void CMainFrame::OnGetapplistButton()
{
	_MapTeleApplicaiton();
	m_wndLeftPane.TransationAppList(csAppList);
}
void CMainFrame::OnReadertypeButton()
{
	if (iReaderType == Def_ReaderType_PCSC)
		OnCCR5ReaderButton();
	else
		OnPCSCReaderButton();

}
void CMainFrame::OnPCSCReaderButton()
{
	Initialize_PcscList();

	CMFCRibbonButton* pFontButton = DYNAMIC_DOWNCAST(
		CMFCRibbonButton, m_wndRibbonBar.FindByID(ID_ReaderType_Button));

	pFontButton->SetText(_T("PCSC"));

}
void CMainFrame::OnCCR5ReaderButton()
{
	Initialize_CCR5List();


	CMFCRibbonButton* pFontButton = DYNAMIC_DOWNCAST(
		CMFCRibbonButton, m_wndRibbonBar.FindByID(ID_ReaderType_Button));

	pFontButton->SetText(_T("CCR5"));
	
}
void CMainFrame::OnCCR5SettingButton()
{
	CTermnalSetting cCCR5Setting;

	if ((iReaderType == Def_ReaderType_CCR5)&& (CCR5Hand != NULL))
	{
		cCCR5Setting.SetTerminalHandle(CCR5Hand);
		cCCR5Setting.DoModal();
	}




	return;

}
void CMainFrame::OnResetCTButton()
{


	if ((iReaderType == Def_ReaderType_CCR5)&& (CCR5Hand != NULL))
	{


	}
}
void CMainFrame::OnDisconnectTerminalButton()
 {

	 m_wndOutput.Print2Output(_T("断开读卡器"),_T(""),_T(""));
	 iReaderStatus = Def_Terminal_Disconnected;
 }
void CMainFrame ::OnConnectTerminalButton()
 {

	 CMFCRibbonComboBox* pFontComboBox = DYNAMIC_DOWNCAST(
		 CMFCRibbonComboBox, m_wndRibbonBar.FindByID(ID_PcscReader_Combo));

	 CString csName = pFontComboBox->GetEditText();

	 if (ConnectReader_CCR5(csName)==0)
		 m_wndOutput.Print2Output(_T("连接读卡器:成功"),_T(""),_T(""));
	 else
		 m_wndOutput.Print2Output(_T("连接读卡器:失败"),_T(""),_T(""));

	 iReaderStatus = Def_Terminal_Connected;


 }
void CMainFrame ::OnRequestICCButton()
 {
	 BYTE* ucResp;
	 UINT uiRespLen;
	 int iRet;

	 uiRespLen = 60;
	 ucResp = new BYTE[uiRespLen];

	 iRet = CCR5_RequestICC(CCR5Hand,01,ucResp,&uiRespLen);

	 if (iRet!= CT_Tran_T0)
		 m_wndOutput.Print2Output(_T("邀请:失败"),_T(""),_T(""));  
	 else
	 {
		  _UcHex2CString(ucResp,uiRespLen,csCardATR);
		 m_wndOutput.Print2Output(_T("邀请:成功"),_T(""),_T(""));
		 iReaderStatus = Def_Card_Connected;
	 }


 }
void CMainFrame ::OnEjectICCButton()
  {
	  BYTE* ucResp;
	  UINT uiRespLen;
	  int iRet;

	  uiRespLen = 60;
	  ucResp = new BYTE[uiRespLen];

	  iRet = CCR5_EjectICC(CCR5Hand,01,ucResp,&uiRespLen);

	  m_wndOutput.Print2Output(_T("弹出卡片"),_T(""),_T(""));  

	  iReaderStatus = Def_Card_Disconnected;

  }
void CMainFrame ::OnSendCommandToTerminalButton()
  {

  }
void CMainFrame::OnUstButton()
{
	CString csFCI,csFileData;
	if ((_TestCaseFileIsExisted_UICC(_T("A000000087"),true)>=0)&&(!_TestCaseSelectFile(_T("6F38"),csFCI)))
	{
		MessageBox(_T("选择UST文件失败！"));
		return;
	}

	csFileData = _TestCaseReadCurrentFileData_UICC(csFCI);

	if (csFileData.IsEmpty())
	{
		MessageBox(_T("文件读取失败！"));
		return;
	}

	m_wndUST.SetUST(csFileData);
	m_wndUST.ShowWindow(SW_SHOW);
}
void CMainFrame::OnAdnButton()
{
	//NewWriteTestADNThread();
	//NewSetStatusThread();

	m_dlgADN.ShowWindow(SW_SHOW);
}
void CMainFrame::OnSmsButton()
{

	if (ConfirmPin1VerifyStatue())
		m_dlgSMS.ShowWindow(SW_SHOW);


	



}
 void CMainFrame::OnPowerOnButton()
 {	
	 byte ucATR[50];
	 int iRet;
	 UINT iATRLen;
	 ZeroMemory(ucATR,50);
	 iATRLen = 0;
	 iRet = CCR5_PowerOnCard(CCR5Hand,NULL,ucATR,&iATRLen,&lWorkTime);
	 csCardATR.Empty();
	 if (iATRLen>0)
	 {
		 _UcHex2CString(ucATR,iATRLen,csCardATR);
		 m_wndOutput.Print2Output(_T("上电:成功"),_T("$Warm Reset"),csCardATR);
		 m_wndOutput.PrintTime2Output(lWorkTime);
		 iReaderStatus = Def_Card_Connected;


	 }
	 else
	 {	
		 csCardATR.Empty();
		 m_wndOutput.Print2Output(_T("上电:失败"),_T("$Warm Reset"),csCardATR);
		iReaderStatus = Def_Card_Disconnected;
	 }

	 InitCardParamater();
	 NewSetStatusThread();

 }
 void CMainFrame::OnPowerOffButton()
 {
	CCR5_PowerOffCard(CCR5Hand);
	iReaderStatus = Def_Card_Disconnected;
	csCardATR.Empty();
	NewSetStatusThread();
	m_dlgChangeFile.SetCurrentFileInformation(NULL,NULL);

 }
 void CMainFrame::OnGetPinCounterButton()
 {
	 GetPinStatus();

 }


 void CMainFrame::OnOpenModule(UINT iID)
 {
	int iModule = 1;
	 switch(iID)
	 { 
	 case ID_New_CTC:            iModule = 1;    break;
	 case ID_New_3GPP2:          iModule = 0xF3 ;break;
	 case ID_New_CDMA:           iModule = 0xF4; break;
	 case ID_New_CMCC:           iModule = 0x11; break;
	 case ID_New_CUC:            iModule = 0x21; break;
	 case ID_New_GSM:            iModule = 0xF1; break;
	 case ID_New_3GPP:           iModule = 0xF2; break;
	 case ID_CTC_Native_301:     iModule = 1;    break;
	 case ID_CTC_M2M_2G3G_301:   iModule = 2;    break;
	 case ID_CTC_M2M_2G3G4G_301: iModule = 3;    break;
	 case ID_CMCC_Native_20A:    iModule = 0x11; break;
	 case ID_CMCC_M2M_20:        iModule = 0x12; break;
	 default:break;
	 }

	 m_wndClassView->Initialize_ClassView(iModule);
//	 m_wndKeySetting.InstallCFLSetting(iModule);

 }

 void CMainFrame::OnUpdateThreadFreeCardConnected(CCmdUI* pCmdUI)
 {
	 if ((iThread == Def_Thread_Free)&&
		 (iReaderStatus == Def_Card_Connected)&&
		 (bReadMode == true))
		 pCmdUI->Enable(TRUE);
	 else
		 pCmdUI->Enable(FALSE);
 }
 void CMainFrame::OnUpdateThreadBusyCardConnected(CCmdUI* pCmdUI)
 {
	 if ((iThread != Def_Thread_Free)&&
		 (iReaderStatus == Def_Card_Connected)&&
		 (bReadMode == true))
		 pCmdUI->Enable(TRUE);
	 else
		 pCmdUI->Enable(FALSE);
 }
 void CMainFrame::OnUpdateTeminalDisconnected(CCmdUI* pCmdUI)
 {
	// if ((iReaderStatus == Def_Terminal_Disconnected)&&
		// (bReadMode == true))
	 if (iReaderStatus == Def_Terminal_Disconnected)
		 pCmdUI->Enable(TRUE);
	 else
		 pCmdUI->Enable(FALSE);

	 switch(pCmdUI->m_nID)
	 {
	 case ID_IsUICC_Check:        pCmdUI->SetCheck(bIsUICC);break;
	 case ID_ReaderMode_Check:    pCmdUI->SetCheck(bReadMode);break;
	 case ID_GetFileSystem_Check: pCmdUI->SetCheck(bGetFileSystem);break;
	 case ID_GetAppList_Check:    pCmdUI->SetCheck(bGetAppList);break;
	 case ID_GetPinStatus_Check:  pCmdUI->SetCheck(bGetPinSta);break;
	 default:break;
	 }

 }
 void CMainFrame::OnUpdateTeminalConnected(CCmdUI* pCmdUI)
 {
	 if ((iReaderStatus != Def_Terminal_Disconnected)&&
		 (bReadMode == true))
		 pCmdUI->Enable(TRUE);
	 else
		 pCmdUI->Enable(FALSE);
 }
 void CMainFrame::OnUpdateIsCCR5(CCmdUI* pCmdUI)
 {

	 if ((iReaderType == Def_ReaderType_CCR5)&&
		 (bReadMode == true))
		 pCmdUI->Enable(TRUE);
	 else
		 pCmdUI->Enable(FALSE);
 }
 void CMainFrame::OnUpdateThreadFree(CCmdUI* pCmdUI)
 {


	 switch(pCmdUI->m_nID)
	 {
	 case ID_AutoVerifyPin_Check: 
		
		 if (!bGetARR)
		 {
			  bNotVerify = false;
			  pCmdUI->SetCheck(FALSE);
			  pCmdUI->Enable(FALSE);
			  return;
		 }
		 pCmdUI->SetCheck(!bNotVerify);		 
		 break;
	 case ID_GetARR_Check:        pCmdUI->SetCheck(bGetARR);
		 break;
	 default:break;
	 }


	 if (iThread == Def_Thread_Free)
		 pCmdUI->Enable(TRUE);
	 else
		 pCmdUI->Enable(FALSE);

 }
 void CMainFrame::OnUpdateCheck(CCmdUI* pCmdUI)
  {
	  switch(pCmdUI->m_nID)
	  {

	  case ID_OutputWnd_Check: pCmdUI->SetCheck(m_wndOutput.IsVisible()); break;
	  case ID_StatusBar_Check: pCmdUI->SetCheck(m_wndStatusBar.IsVisible());break;
	  case ID_PinStatus_Check: pCmdUI->SetCheck(m_wndPinStatus.IsVisible());break;
      case ID_GetFlash_Check:  pCmdUI->SetCheck(m_wndGetFlash.IsVisible());break;
	  case ID_AppList_Check:   pCmdUI->SetCheck(m_wndLeftPane.IsVisible()); break;
	  case ID_Reference_Check: pCmdUI->SetCheck(m_wndReference.IsVisible()); break;
	  case ID_APDUINFO_Check:  pCmdUI->SetCheck(bAPDUExplain);break;
	  case ID_OTAINFO_Check:   
		   if (!bAPDUExplain)
		   {
			   pCmdUI->Enable(FALSE);
			   bOTAExplain = false;
		   }
		  
		  pCmdUI->SetCheck(bOTAExplain);break;
	  case ID_OTA_Decrypt_Check: 
		  if (!bOTAExplain)
		  {
			  pCmdUI->Enable(FALSE);
			  bOTADecrypt = false;
		  }
		  
		  pCmdUI->SetCheck(bOTADecrypt);break;
	  }

  }




 void CMainFrame::OnSettingCheck( UINT iID )
 {
	 switch(iID)
	 {
	 case ID_IsUICC_Check                 : bIsUICC =! bIsUICC;  
		 if (bIsUICC)
		 {
			 m_dlgADN.SetAbbreviatedDiallingNumbersType(_DEF_PhoneBook_3GPP);
			 m_dlgSMS.SetShortMessageType(_DEF_SMS_3GPP);
		 }
		 else
		 {
			 m_dlgADN.SetAbbreviatedDiallingNumbersType(_DEF_PhoneBook_GSM);
			 m_dlgSMS.SetShortMessageType(_DEF_SMS_GSM);
		 }break;
	 case ID_ReaderMode_Check             : bReadMode = ! bReadMode;break;
	 case ID_GetFileSystem_Check          : bGetFileSystem = !bGetFileSystem;break;
	 case ID_GetAppList_Check             : bGetAppList    = !bGetAppList;break;
	 case ID_GetPinStatus_Check           : bGetPinSta     = !bGetPinSta;break;
	 case ID_AutoVerifyPin_Check          : bNotVerify     = !bNotVerify;break;
	 case ID_GetARR_Check                 : bGetARR        = !bGetARR;break;
	 case ID_APDUINFO_Check               : bAPDUExplain   = !bAPDUExplain;break;
	 case ID_OTAINFO_Check                : bOTAExplain    = !bOTAExplain;break;
	 case ID_OTA_Decrypt_Check            : bOTADecrypt    = !bOTADecrypt;break;
	 default:break;
	 }
	 if (iID>=ID_APDUINFO_Check)
	 {
		 SetExplainLevel((Def_DECINFOMATION*bOTADecrypt)|(Def_OTAINFOMATION*bOTAExplain)|(Def_APDUINFOMATION*bAPDUExplain)|(Def_APDUBASICINFOMATION));
	 }
 }

 bool CMainFrame::Initialize_Ribbon(void)
{
	bReadMode      = Initialize_PcscList();
	//bReadMode      = Initialize_CCR5List();
	bIsUICC        = true;
	//此处初始化改从注册表读取
	//bGetFileSystem = false;//自动获取文件系统
	//bGetAppList    = false;
	//bGetPinSta     = true;
	//bNotVerify     = true;



	iReaderStatus  = Def_Terminal_Disconnected;  //卡片未连接状态
	return true;
}
bool CMainFrame::Initialize_PcscList(void)
{

	CMFCRibbonComboBox* pFontComboBox = DYNAMIC_DOWNCAST(
		CMFCRibbonComboBox, m_wndRibbonBar.FindByID(ID_PcscReader_Combo));

	int iSum;
	LPTSTR    szReaderName[10];

	iReaderType    = Def_ReaderType_PCSC;
	pFontComboBox->RemoveAllItems();




	iSum  =  PcscReader.GetContext();
	iSum  =  PcscReader.GetPcsclist(szReaderName);
	if (iSum<1)
		return false;

	for (int i = 0 ;i < iSum;i++)
		pFontComboBox->AddItem(szReaderName[i]);

	pFontComboBox->SelectItem(0);

	return true;
}

// 初始化部分全局参数
void CMainFrame::InitParamater(void)
{


	csCardATR.Empty();
	csAppList.Empty();


	iReaderType   = Def_ReaderType_PCSC;
	iReaderStatus = Def_Terminal_Disconnected;

	 iFileNum = 0 ;
	 iCurNum = 0 ;


	//进程变量

	//hThread          = NULL;
	//hSetStatusThread = NULL;
	//CCR5Hand         = NULL;
	bProByte         = FALSE;
	lWorkTime        = 0;
	uiVerifyPIN      = 0;

}
void CMainFrame::InitCardParamater(void)
{
	lWorkTime        = 0;
	uiVerifyPIN      = 0;
	iFileNum = 0 ;
	iCurNum = 0 ;
}
void CMainFrame::_TestCaseExpPcscLastCommand(bool bUICC)
{
	BYTE *ucSend;
	BYTE *ucSW;
	BYTE *ucResp;
	int iSend,iSW,iResp;



	ucSend  = new BYTE[300];
	ucSW    = new BYTE[2];
	ucResp  = new BYTE[255];

	ZeroMemory(ucSend,300);
	ZeroMemory(ucResp,255);
	ZeroMemory(ucSW,2);

	iSW     = 0 ;
	iResp   = 0 ;
	iSend   = PcscReader.GetLastSend(ucSend);
	iSW     = PcscReader.GetLastSW(ucSW);
	iResp   = PcscReader.GetLastResponse(ucResp);

	CString csSend,csResp,csSW;
	_UcHex2CString(ucSend,iSend,csSend);
	_UcHex2CString(ucResp,iResp,csResp);
	_UcHex2CString(ucSW,2,csSW);
	_TestCaseExpCommand(csSend,csResp+csSW);

	if (bUICC)
	{
		if ((iSW&0xFF00) == 0x6100)
		{
			PcscReader.GetResponse_UICC(iSW&0x00FF);
			_TestCaseExpPcscLastCommand(bUICC);

		}

	}
	else
	{
		if ((iSW&0xFF00) == 0x9F00)
		{
			PcscReader.GetResponse_GSM(iSW&0x00FF);
			_TestCaseExpPcscLastCommand(bUICC);
		}
	}



}
int CMainFrame::_TestCasePostLastCommand(CString csSW,CString& csResp,bool bUICC)
{
	CString csAPDU;

	csAPDU.Empty();

	int iSW = _CString2Int(csSW);

	if ((bUICC)&&((iSW&0xFF00) == 0x6100))
		csAPDU = _T("00C00000")+csSW.Right(02);
	else if((iSW&0xFF00) == 0x9F00)
		csAPDU = _T("A0C00000")+csSW.Right(02);
	if (!csAPDU.IsEmpty())
		csResp = _TestCaseSendCommand(csAPDU);
	
	return _CString2Int(csResp.Right(04));

}

void CMainFrame::_TestCaseExpCommand(CString csSend,CString csResp)
{

	//int iSendLen;
	//int iIns,iSW;
	//CString csResult;
	//CString csSp;

	//
	//_DeleteEnterSpace(csSend);

	//iSendLen = csSend.GetLength();

	//iIns     = _CString2Int(csSend.Mid(2,2));



	//switch(iIns)
	//{
	//case 0x04:
	//	csResult = _T("Deactive 文件");
	//	break;
	//case 0x44:
	//	csResult = _T("Active 文件");
	//	break;

	//case 0x17:
	//	csResult = _T("Verify PS");
	//	break;
	//case 0x20:
	//	csResult = _T("Verify PIN");
	//	break;
	//case 0x24:
	//	csResult = _T("Change PIN");
	//	break;
	//case 0x26:
	//	csResult = _T("Disable PIN");
	//	break;
	//case 0x28:
	//	csResult = _T("Enable PIN");
	//	break;
	//case 0x2C:
	//	csResult = _T("Unblock PIN");
	//	break;
	//case 0xA2:
	//	csResult = _T("Search 文件");
	//	break;
	//case 0xA4:

	//	csSp = csSend.Mid(10,iSendLen-10);
	//	if (csSp.GetLength()== 4)
	//	{
	//		//if ((CString2Int(csSp)&0x0F00)!=(0x0F00))
	//		//	return ;
	//	}

	//	csResult = _T("选择 文件") + csSp;



	//	break;
	//case 0xB0:
	//	csResult = _T("读取 Binary 文件");

	//	break;
	//case 0xB2:
	//	csResult = _T("读取 Record 文件");

	//	break;
	//case 0xD6:

	//	csResult = _T("更新 Binary 文件");

	//	break;
	//case 0xDC:
	//	csResult = _T("更新 Record 文件");

	//	break;
	//case 0xE4:

	//	csResult = _T("删除 文件") + csSend.Mid(10,iSendLen-10);
	//	break;

	//default:
	//	csResult.Empty();
	//	break;

	//}

	//if (!csResult.IsEmpty())
	//{

	//	if(csResp.GetLength() < 4)
	//		csResult += _T("   失去响应");
	//	else
	//	{

	//		iSW      = _CString2Int(csResp.Right(04));

	//		switch(iSW/0x100)
	//		{
	//		case 0x6F:csResult += _T("   内部问题");        break;
	//		case 0x6D:csResult += _T("   不能识别指令");    break;
	//		case 0x6C:csResult += _T("   P3错误");          break;
	//		case 0x6B:csResult += _T("   P1P2错误");        break;
	//		case 0x67:csResult += _T("   P3错误");          break;
	//		case 0x6E:csResult += _T("   Class错误");       break;
	//		case 0x63:csResult += (_T("   PIN剩余次数")+csResp.Right(1));         break;
	//		case 0x62:	
	//			switch(iSW&0xFF)
	//			{
	//			case 0x83 :csResult += _T("   文件无效");          break;
	//			case 0x82 :csResult += _T("   没有找记录");        break;
	//			default:csResult += _T("   失败");                 break;
	//			}
	//			break;
	//		case 0x68:
	//			switch(iSW&0xFF)
	//			{
	//			case 0x81 :csResult += _T("   不支持逻辑通道");          break;
	//			case 0x82 :csResult += _T("   安全状态不满足");        break;
	//			default:csResult += _T("   失败");                 break;
	//			}		
	//			break;
	//		case 0x69:
	//			switch(iSW&0xFF)
	//			{
	//			case 0x81 :csResult += _T("   命令与文件结构矛盾");          break;
	//			case 0x82 :csResult += _T("   安全状态不满足");        break;
	//			case 0x83 :csResult += _T("   鉴权/PIN被锁死");        break;
	//			case 0x84 :csResult += _T("   引用的数据无效");        break;
	//			case 0x85 :csResult += _T("   使用的条件不满足");        break;
	//			case 0x86 :csResult += _T("   没有选择的EF");        break;
	//			default:csResult += _T("   失败");                 break;
	//			}		
	//			break;
	//		case 0x6A:
	//			switch(iSW&0xFF)
	//			{
	//			case 0x80 :csResult += _T("   数据字段中的参数错误");          break;
	//			case 0x81 :csResult += _T("   功能不被支持");          break;
	//			case 0x82 :csResult += _T("   找不到文件");        break;
	//			case 0x83 :csResult += _T("   找不到记录");        break;
	//			case 0x86 :csResult += _T("   错误的参数P1-P2");        break;
	//			case 0x87 :csResult += _T("   Lc与P1-P2不一致");        break;
	//			default:csResult += _T("   失败");                 break;
	//			}	
	//			break;
	//		case 0x98:
	//			switch(iSW&0xFF)
	//			{
	//			case 0x40 :csResult += _T("   鉴权/PIN被锁死");          break;
	//			case 0x04 :csResult += _T("   鉴权/PIN错误");          break;
	//			case 0x50 :csResult += _T("   INCREASE不能被执行，已达到最大值");        break;
	//			case 0x62 :csResult += _T("   鉴权错误,输入数据有误");        break;
	//			default:csResult += _T("   失败");                 break;
	//			}	
	//			break;
	//		case 0x91:csResult += _T("   成功,后续有主动式指令"); break;

	//		default:
	//			if ((iSW == 0x9000)||((iSW&0xFF00) == 0x6100)||((iSW&0xFF00) == 0x9F00))
	//				csResult += _T("   成功");
	//			else
	//				csResult += _T("   失败");
	//		}

	//	}


	//}
	//m_wndOutput.Print2Output(csResult,csSend,csResp);

	m_wndOutput.PrintAPDU(csSend,csResp);

//	m_wndOutput.PrintTime2Output(lWorkTime);
}

int CMainFrame::_TestCaseFileIsExisted(CString csFID,bool bAID)
{
	int iRet = -1;
	if (csFID.IsEmpty())
		return iRet;
	if (bIsUICC)
		iRet = _TestCaseFileIsExisted_UICC(csFID, bAID); 

	else if(!bAID)
		iRet = _TestCaseFileIsExisted_GSM(csFID); 

	return iRet;
}

int CMainFrame::_TestCaseFileIsExisted_UICC(CString csFID,bool bAID)
{
	CString csResp;
	int iFile;

	if (!_TestCaseSelectFile(csFID,csResp,true,bAID))
		return -1;

	csResp = GetTLVData(csResp,0x62);

	csResp = GetTLVData(csResp,0x82);

	iFile  = _CString2Int(csResp.Left(02));

	return iFile;
}

int CMainFrame::_TestCaseFileIsExisted_GSM(CString csFID)
{
	CString csResp;

	if (!_TestCaseSelectFile(csFID,csResp,false))
		return -1;

	return _CString2Int(csResp.Mid(12,02));
}

int CMainFrame::_TestCasePathIsExisted(CString csPath)
{
	CString csSW; 
	CString csLc;

	if (csPath.GetLength() == 0)
	{
		csSW = _TestCaseSendCommand("0012000000");

		if (!csSW.IsEmpty())
			csSW = _T("9000");
		else
			csSW.Empty();


	}
	else
	{
		csLc.Format("%02X",csPath.GetLength()/2);

		csSW = _TestCaseSendCommand("00A4080C"+csLc+csPath);
	}

	return _CString2Int(csSW);
}

int CMainFrame::_TestCasePathIsExistedStartMF(CString csPath)
{
	CString csSW; 
	CString csLc;

	if (csPath.GetLength() == 0)
	{
		csSW = _TestCaseSendCommand("0012000000");

		if (!csSW.IsEmpty())
			csSW = _T("9000");
		else
			csSW.Empty();
	}
	else
	{
		csLc.Format("%02X",csPath.GetLength()/2);

		csSW = _TestCaseSendCommand("00A4080C"+csLc+csPath);
	}

	return _CString2Int(csSW);

}



int CMainFrame::_TestCaseFIDIsExistedInCurrent(CString csFID)
{
	CString csSW; 
	CString csLc;


	csLc.Format("%02X",csFID.GetLength()/2);

	csSW = _TestCaseSendCommand("00A4090C"+csLc+csFID);

	return _CString2Int(csSW);
}

bool CMainFrame::_TestCaseCompareData(CString csData1, CString csData2)
{
	int iLen1,iLen2,iCyc,iData1,iData2;
	CString csTemp1,csTemp2;

	iLen1 = csData1.GetLength();
	iLen2 = csData2.GetLength();

	if (iLen1!=iLen2)
		return false;

	for (iCyc = 0 ; iCyc<iLen1 ; iCyc++)
	{

		csTemp1 = csData1.Mid(iCyc,1);
		csTemp2 = csData2.Mid(iCyc,1);

		if ((csTemp1!="X")&&(csTemp1!="x")&&((csTemp2!="X")&&((csTemp2!="x")&&(csTemp1!="?")&&(csTemp2!="?"))))
		{
			iData1 = _ttoi(csTemp1);
			iData2 = _ttoi(csTemp2);
			if (iData1!=iData2)
				return false;	
		}
	}

	return true;

}

bool CMainFrame::_TestCaseSelectFile(CString csFile,CString& csResp,bool bUICC, bool bAID)
{
	bool bRet;

	if (csFile.IsEmpty())
		return false;

	switch(iReaderType)
	{
	case Def_ReaderType_PCSC:bRet = _TestCaseSelectFile_PCSC(csFile,csResp,bUICC,bAID);break;
	case Def_ReaderType_CCR5:bRet = _TestCaseSelectFile_CCR5(csFile,csResp,bUICC,bAID);break;
	default:break;
	}
	return bRet;
}

bool CMainFrame::_TestCaseSelectFile_PCSC(CString csFile,CString& csResp,bool bUICC, bool bAID)
{
	bool bRet;
	int iFileLen,iResp,iSW;
	BYTE *ucFile;
	BYTE *ucResp;
	BYTE *ucSend;

	if (iReaderStatus!=Def_Card_Connected)
		return false;


	iSW = 00;

	iFileLen = csFile.GetLength()/2;

	ucFile = new BYTE[iFileLen];
	ucResp = new BYTE[257];
	ucSend = new BYTE[0x15];

	ZeroMemory(ucFile,iFileLen);
	ZeroMemory(ucResp,257);



	iFileLen = _CString2UcHex(csFile,ucFile);

	if (bAID)
	{
		PcscReader.Select_UICC_AID(ucFile,iFileLen);
		_TestCaseExpPcscLastCommand(bUICC);

		iSW = PcscReader.GetLastSW(ucResp);
	}
	else
	{
		for (int iCyc = 0 ; iCyc < iFileLen ; iCyc += 2)
		{
			if (bUICC)
				iResp = PcscReader.Select_UICC_FID(ucFile+iCyc);
			else
				iResp = PcscReader.Select_GSM(ucFile[iCyc]*0x100+ucFile[iCyc+1]);

			_TestCaseExpPcscLastCommand(bUICC);

			iSW = PcscReader.GetLastSW(ucResp);

			if (iSW != 0x9000)
				iFileLen = 0;

		}
	}



	if (iSW == 0x9000)
	{
		iResp = PcscReader.GetLastResponse(ucResp);

		_UcHex2CString(ucResp,iResp,csResp);

		bRet   = true;
	}
	else
	{
		csResp.Empty();
		bRet = false;
	}

	delete ucFile;
	delete ucResp;

	return bRet;
}

bool CMainFrame::_TestCaseSelectFile_CCR5(CString csFile,CString& csResp,bool bUICC, bool bAID)
{

	CString csAPDU;
	int iFileLen,iSW;

	iSW = 0;
	if (csFile.IsEmpty())
		return false;

	if (bAID)
	{
		csAPDU = _T("00A40404")+Int2CString(csFile.GetLength()/2,2)+csFile;

		csResp = _TestCaseSendCommand(csAPDU);

		iSW = _TestCasePostLastCommand(csResp.Right(04),csResp,true);

	}
	else
	{
		iFileLen = csFile.GetLength();

		for (int iCyc = 0 ; iCyc < iFileLen ; iCyc += 4)
		{
			if (bUICC)
				csAPDU = _T("00A4000402")+csFile.Mid(iCyc,4);
			else
				csAPDU = _T("A0A4000002")+csFile.Mid(iCyc,4);

			csResp = _TestCaseSendCommand(csAPDU);

			iSW = _TestCasePostLastCommand(csResp.Right(04),csResp,bUICC);
		}
	}

	if (iSW == 0x9000)
		return true;
	else
		return false;
}


bool CMainFrame::_TestCaseDeleteCardFile(CString csFID)
{
	CString csResp;
	csResp = _TestCaseSendCommand(_T("00E4000002")+csFID);

	//csResp = _TestCaseSendCommand(_T("00A4000C02")+csFID);

	if (csResp == _T("9000"))
		return true;
	else
		return false;
}

CString CMainFrame::_TestCaseSendCommand_PCSC(CString csData)
{
	int iSend,iResLen;
	int iRet;
	CString csResp;

	//unsigned int uiResLen;
	unsigned char ucSend[300];
	unsigned char ucResp[300];
	_DeleteEnterSpace(csData);
	iSend  = csData.GetLength();
	ZeroMemory(ucSend,300);
	ZeroMemory(ucResp,300);
	if (iReaderStatus != Def_Card_Connected)
	{
		csData.Empty();
		return csData;
	}

	if ((csData == "0012000000")||(csData == "$0")||(csData == "Reset")||(csData == "reset")||(csData == "RESET"))
	{
		iRet = PcscReader.ResetCard(ColdReset);
		if (iRet == 0)
		{
			iResLen = PcscReader.GetCardATR(ucResp);
			iReaderStatus = Def_Card_Connected;

		}
		else
		{
			iResLen = 0;
			iReaderStatus = Def_Card_Disconnected;
		}

		_UcHex2CString(ucResp,iResLen,csResp);

		uiVerifyPIN = 0;
	}
	else
	{

		iSend = _CString2UcHex(csData,ucSend);

		iRet = PcscReader.SendCommand(ucSend,iSend,ucResp,&iResLen);

		if (iResLen < 2)
			iReaderStatus = Def_Card_Disconnected;
		else
			iReaderStatus = Def_Card_Connected;

		_UcHex2CString(ucResp,iResLen,csResp);

	}
	return csResp;
}

CString CMainFrame::_TestCaseSendCommand_CCR5(CString csData)
{
	int iRet;
	UINT uiSend,uiResLen;
	CString csResp;
	BYTE ucCardStatus;
	BYTE ucSend[300];
	BYTE ucResp[300];
	_DeleteEnterSpace(csData);
	uiSend  = csData.GetLength();
	uiResLen = 0;
	ZeroMemory(ucSend,300);
	ZeroMemory(ucResp,300);
	lWorkTime = 0;
	if (iReaderStatus != Def_Card_Connected)
	{
		csData.Empty();
		return csData;
	}

	if ((csData == "0012000000")||(csData == "$0")||(csData == "Reset")||(csData == "reset")||(csData == "RESET"))
	{
		iRet = CCR5_PowerOffCard(CCR5Hand);


		if (iRet == CT_Tran_OK)
		{
			iRet = CCR5_PowerOnCard(CCR5Hand,&ucCardStatus,ucResp,&uiResLen,&lWorkTime);
			iReaderStatus = Def_Card_Connected;

		}
		else
		{
			uiResLen = 0;
			iReaderStatus = Def_Card_Disconnected;
		}

		_UcHex2CString(ucResp,(int)uiResLen,csResp);

		uiVerifyPIN = 0;
	}
	else
	{
		uiSend = (UINT)_CString2UcHex(csData,ucSend);

		iRet = CCR5_Send2Card(CCR5Hand,ucSend,uiSend,ucResp,&uiResLen,&lWorkTime,bProByte);

		if (iRet != CT_Tran_OK)
			iReaderStatus = Def_Card_Disconnected;
		else
			iReaderStatus = Def_Card_Connected;

		_UcHex2CString(ucResp,(int)uiResLen,csResp);
	}
	return csResp;
}




CString CMainFrame::_TestCaseSendCommand(CString csData)
{
	CString csResp;
	switch(iReaderType)
	{
	case Def_ReaderType_PCSC: csResp = _TestCaseSendCommand_PCSC(csData);break;	
	case Def_ReaderType_CCR5: csResp = _TestCaseSendCommand_CCR5(csData);break;
	}

	_TestCaseExpCommand(csData,csResp);


	return csResp;
}
CString CMainFrame::_TestCaseReadCurrentFileData(CString csFCI,bool bUICC)
{
	CString csResult;

	if (iThread != Def_Thread_Free)
		return csResult;

	if (bGetARR)
	{
		if (!_TestCaseVerify(m_wndProperties->GetAC(1)))
			if (!_TestCaseVerifyPS())			
				return false;
	}


	if (bUICC)
		csResult = _TestCaseReadCurrentFileData_UICC(csFCI);
	else
		csResult = _TestCaseReadCurrentFileData_GSM(csFCI);

	return csResult;

}
CString CMainFrame::_TestCaseReadCurrentFileData_GSM(CString csFCI)
{	CString csResult;

int iFileType,iFileStru;
int iRecLen,iRecNum;
CString csRecLen,csTemp;
iFileType = _CString2Int(csFCI.Mid(12,02));	
if (iFileType == 0x04)
	iFileStru = _CString2Int(csFCI.Mid(26,02));	
else
	return csResult;

if (iFileStru == 0)
{
	csResult = _TestCaseGetBinaryData(_CString2Int(csFCI.Mid(04,04)),false);

}
else
{
	csRecLen = csFCI.Mid(28,02);
	iRecLen  = _CString2Int(csRecLen);
	iRecNum  = _CString2Int(csFCI.Mid(04,04))/iRecLen;


	for (int iNum = 1 ; iNum <= iRecNum;iNum++)
	{

		csTemp.Format("%02X",iNum);

		csTemp = _TestCaseSendCommand(_T("A0B2")+csTemp+_T("04")+csRecLen);

		if (csTemp.Right(04) = _T("9000"))
			csResult += csTemp.Mid(00,csTemp.GetLength()-4);
		else
			return csResult;
	}

}



return csResult;
}
CString CMainFrame::_TestCaseReadCurrentFileData_UICC(CString csFCI)
{
	CString csResult;
	CString csFileInformation,csFileType,csSize,csRescord,csNumber;
	CString csTemp;
	int iType;


	csFCI               = GetTLVData(csFCI,0x62);
	csFileInformation   = GetTLVData(csFCI,0x82);
	csFileType          = csFileInformation.Mid(00,02);
	csSize              = GetTLVData(csFCI,0x80);
	iType               = _CString2Int(csFileType);
	csResult.Empty();

	if ((iType&0x7)== 01)
	{
		csResult = _TestCaseGetBinaryData(_CString2Int(csSize));
	}
	if (((iType&0x7)== 02)||((iType&0x7)== 06))
	{
		csNumber  = csFileInformation.Mid(0x8 ,02);
		csRescord = csFileInformation.Mid(04 ,04);

		for (int iNum = 1 ; iNum <= _CString2Int(csNumber);iNum++)
		{

			csTemp.Format("%02X",iNum);

			csTemp = _TestCaseSendCommand(_T("00B2")+csTemp+_T("04")+csRescord.Mid(02,02));

			if (csTemp.Right(04).Compare (_T("9000")) == 0)
				csResult += csTemp.Mid(00,csTemp.GetLength()-4);
			else
				return csResult;
		}
	}

	return csResult;
}
CString CMainFrame::_TestCaseSelectCurrentFile(HTREEITEM hCurrentItem)
{

	CString csFID,csResult;
	int iLevel;
	HTREEITEM hNextItem[10];
	iLevel = 0;

	do 
	{

		hNextItem[iLevel] = hCurrentItem;
		iLevel ++;
		hCurrentItem  = m_wndClassView->GetNextItem(hCurrentItem,TVGN_PARENT);

	} while (hCurrentItem != NULL);

	for (int i = (iLevel-1) ; i >= 0 ; i-- )
	{
		csFID =  m_wndClassView->_GetItemFID(hNextItem[i]);
		if (csFID.IsEmpty())
			csFID =  m_wndClassView->_GetItemAID(hNextItem[i]);

		if (_TestCaseSelectFile(csFID,csResult,bIsUICC,(csFID.GetLength()!=4)))
			m_wndClassView->ChangeItemState(hNextItem[i],_LV_Existed);
		else
		{
			m_wndClassView->ChangeItemState(hNextItem[i],_LV_Absent);
			break;
		}

	}

	return csResult;




}
CString CMainFrame::_TestCaseGetBinaryData(int iSize,bool bUICC)
{
	int iOffset;
	CString csSend,csResp;
	CString csResult;

	iOffset = 0;
	csResult.Empty();

	while(iSize>iOffset)
	{
		if (iSize -iOffset >= 0xFF)
			csSend.Format("%04X%02X",iOffset,0xFF);
		else
			csSend.Format("%04X%02X",iOffset,iSize -iOffset);

		if (bUICC)
			csResp = _TestCaseSendCommand(_T("00B0")+csSend);
		else
			csResp = _TestCaseSendCommand(_T("A0B0")+csSend);



		iOffset  += 0xFF;

		if (csResp.Right(04) == _T("9000"))
			csResult += csResp.Left(csResp.GetLength()-4);
		else
		{
			csResult.Empty();
			break;
		}
	}

	return csResult.Mid(0,iSize*2);
}
CString CMainFrame::_TestCaseReadRecord(int iNumber,int iLength,bool bUICC)
{
	CString csSend,csResp;

	csSend.Format("%02X%02X%02X",iNumber,04,iLength);

	if (bUICC)
		csResp = _TestCaseSendCommand(_T("00B2")+csSend);
	else
		csResp = _TestCaseSendCommand(_T("A0B2")+csSend);

	if (csResp.GetLength() != (iLength*2+4))
		csResp.Empty();
	else
		csResp.Left(iLength*2);

	return csResp;

}

UINT CMainFrame::_TestCaseGetFlashSize()
{
	UINT uiSize;
	CString csSend,csResp;
	csResp = _TestCaseSendCommand(_T("F0F1000004"));

	if (_CString2Int(csResp.Mid(8))!= 0x9000)
		return FALSE;

	uiSize = _CString2Int(csResp.Mid(0,2))*0x1000000+
		     _CString2Int(csResp.Mid(2,2))*0x10000+
			 _CString2Int(csResp.Mid(4,2))*0x100+
			 _CString2Int(csResp.Mid(6,2));

	return uiSize;
}

CString CMainFrame::_TestCaseGetFlashData(UINT uiSize, bool bOutput /*= true*/)
{
	CString csSend,csResp;
	CString csResult;

	int iSum = uiSize/0x80+  1;
	int iLen = 0x80;
	csResult.Empty();
	if (bOutput)
		m_wndGetFlash.ResetOffset();
	
	for (int i = 0 ; i< iSum ; i++)
	{
		SetProgressCounter(iSum,i);
		if (iThread == Def_Thread_Ending)
			return csResult;

		if (i == iSum -1)
			iLen = uiSize%0x80;
		if (iLen == 0)
			continue;

		csSend.Format("%04X%02X",i,iLen);
		csSend = _T("F0F2")+csSend;
		csResp = _TestCaseSendCommand(csSend);
		if   (_CString2Int(csResp.Right(4))==0x9000)
		{
			csResult+= csResp.Mid(0,iLen*2);
		}
		if (bOutput)
			m_wndGetFlash.DisplayFlashData(csResult);
	}


	SetProgressCounter(iSum,iSum);
	return csResult;
}




bool CMainFrame::_TestCaseUpdateBinaryData(CString csData,bool bUICC)
{

	CString csSend,csResp;
	int iSize,iOffset,iLen;
	CString csOff;
	_DeleteEnterSpace(csData);
	iSize  = csData.GetLength()/2;
	iOffset= 0 ;

	//if (bUICC)
	//	csResp = _TestCaseSendCommand(_T("0020000A083232323232323232"));
	//else
	//	csResp = _TestCaseSendCommand(_T("A0200004083232323232323232"));

	if (!_TestCaseVerify(m_wndProperties->GetAC(2)))
		if (!_TestCaseVerifyPS())
			return false;	

	while(iSize> iOffset)
	{

		if (iSize -iOffset >0xFF)
		{
			csSend.Format("%04X%02X",iOffset,0xFF);
			iLen = 0xFF*2;
		}
		else
		{
			csSend.Format("%04X%02X",iOffset,iSize -iOffset);
			iLen = (iSize -iOffset)*2;

		}

		if (bUICC)
			csResp = _TestCaseSendCommand(_T("00D6")+csSend+csData.Mid(iOffset*2,iLen));
		else
			csResp = _TestCaseSendCommand(_T("A0D6")+csSend+csData.Mid(iOffset*2,iLen));


		iOffset  += 0xFF;

		if(csResp!=_T("9000"))
			return false;
	}


	return true;
}

bool CMainFrame::_TestCaseUpdateRecordData(int iNumber,CString csData,bool bUICC)
{
	CString csSend,csResp;

	if (!_TestCaseVerify(m_wndProperties->GetAC(2)))
		if (!_TestCaseVerifyPS())
			return false;	



	_DeleteEnterSpace(csData);

	csSend.Format("%02X%02X%02X",iNumber,04,csData.GetLength() /2);

	if (bUICC)
		csResp = _TestCaseSendCommand(_T("00DC")+csSend+csData);
	else
		csResp = _TestCaseSendCommand(_T("A0DC")+csSend+csData);

	if(csResp!=_T("9000"))
		return false;
	return true;

}

bool CMainFrame::_TestCaseUpdateCycLicData(CString csAllData,int iRecordLen,int iNumber,bool bUICC)
{

	CString csSend,csResp;
	_DeleteEnterSpace(csAllData);
	if (!_TestCaseVerify(m_wndProperties->GetAC(2)))
		if (!_TestCaseVerifyPS())
			return false;

	if((iRecordLen * iNumber )== (csAllData.GetLength()/2))
	{
		csSend.Format("%02X",iRecordLen);

		if (bUICC)
			csSend = _T("00DC0003")+csSend;
		else
			csSend = _T("A0DC0003")+csSend;


		for (int iCyc = 1 ; iCyc <= iNumber; iCyc ++)
		{
			csResp = _TestCaseSendCommand(csSend+csAllData.Mid(((iNumber-iCyc)*2)*iRecordLen,iRecordLen*2));
			if(csResp!=_T("9000"))
				return false;	
		}
	}

	return true;

}

bool CMainFrame::_TestCaseVerify( int iNum,bool bSure /*= false*/ )
{
	if ((!bSure)&&(bNotVerify))
		return true;


	if ((bIsUICC)&&(iNum == 2))
		iNum = 0x81;
	if ((!bIsUICC)&&(iNum == 0x81))
		iNum = 2;

	CString csNum,csPin,csAPDU,csSW;
	int iSW;
	int iOff;
	if (iNum == 0)
		return true;
	else if(iNum == 0xf)
		return false;
	else 
		csNum.Format("%02X",iNum);

	if (iNum>=0xA)
	{
		if (iNum&0x80)
			iOff = (iNum&0x0F);
		else
			iOff = iNum-0x7;
	}
	else
		iOff = iNum-1;

	if ((uiVerifyPIN >> iOff)&0x1)
		return true;

	csPin = m_wndKeySetting.GetPIN(iNum);

	if (bIsUICC)
		csAPDU = _T("00");
	else
		csAPDU = _T("A0");

	csAPDU = csAPDU+_T("2000")+csNum+_T("08")+csPin;

	csSW = _TestCaseSendCommand(csAPDU);
	iSW  = _CString2Int(csSW);
	if (iNum == 1)
	{
		if ((iSW == 0x9808)||(iSW == 0x6984))
		{
			uiVerifyPIN  = uiVerifyPIN|1;

			m_wndPinStatus.Insatll_PinVerifyStatus(uiVerifyPIN);
			m_wndPinStatus.SetPin1Disable(true);

			return true;
		}
		else
			m_wndPinStatus.SetPin1Disable(false);

	}


	if (iSW != 0x9000)
		return false;
	else
	{
		uiVerifyPIN = uiVerifyPIN| (1<<(iOff-1));
		m_wndPinStatus.Insatll_PinVerifyStatus(uiVerifyPIN);
		return true;
	}

}

bool CMainFrame::_TestCaseEnablePin1(bool bEnable)
{

	CString csIns,csPin,csAPDU,csSW;
	int iSW;

	if (bIsUICC)
		csAPDU = _T("00");
	else
		csAPDU = _T("A0");
	if (bEnable)
		csAPDU =csAPDU+_T("28");
	else
		csAPDU =csAPDU+_T("26");

	csAPDU = csAPDU+_T("000108");

	csPin = m_wndKeySetting.GetPIN(1);

	csAPDU = csAPDU+csPin;

	iSW = _CString2Int(_TestCaseSendCommand(csAPDU));

	if ((iSW == 0x9808)||(iSW == 0x6984)|| (iSW == 0x9000))
	{
		m_wndPinStatus.SetPin1Disable(!bEnable);
		return true;
	}

	return false;

}

bool CMainFrame::_TestCaseChangePin( int iNum)
{
	if ((bIsUICC)&&(iNum == 2))
		iNum = 0x81;
	if ((!bIsUICC)&&(iNum == 0x81))
		iNum = 2;
	CInput2Prop cInputNewPin;
	CString    csNewPin;
	CString    csAPDU;

	cInputNewPin.SetInputData(_T("31323334FFFFFFFF"));
	cInputNewPin.SetInputDataSize(16,16);
	if (cInputNewPin.DoModal() == IDCANCEL)
		return true;

	csNewPin = cInputNewPin.GetInputData();

	if (bIsUICC)
		csAPDU = _T("00");
	else
		csAPDU = _T("A0");

	csAPDU = csAPDU+_T(_T("2400"))+Int2CString(iNum,2)+_T("10")+
		     m_wndKeySetting.GetPIN(iNum)+csNewPin;


	int iSW = _CString2Int(_TestCaseSendCommand(csAPDU));
	if (iSW == 0x9000)
		return true;
	return false;
}

bool CMainFrame::_TestCaseUnblockPin( int iNum)
{

	if ((bIsUICC)&&(iNum == 2))
		iNum = 0x81;
	if ((!bIsUICC)&&(iNum == 0x81))
		iNum = 2;
	CInput2Prop cInputNewPin;
	CString    csNewPin;
	CString    csAPDU;

	cInputNewPin.SetInputData(_T("31323334FFFFFFFF"));
	cInputNewPin.SetInputDataSize(16,16);
	if (cInputNewPin.DoModal() == IDCANCEL)
		return true;

	csNewPin = cInputNewPin.GetInputData();

	if (bIsUICC)
		csAPDU = _T("00");
	else
		csAPDU = _T("A0");

	csAPDU = csAPDU+_T(_T("2C00"))+Int2CString(iNum,2)+_T("10")+
		m_wndKeySetting.GetPIN(iNum+0x10)+csNewPin;


	int iSW = _CString2Int(_TestCaseSendCommand(csAPDU));
	if (iSW == 0x9000)
		return true;
	return false;

}


bool CMainFrame::_TestCaseVerifyPS()
{
	CString csPin,csAPDU,csSW;
	int iSW;

	if (bNotVerify)
		return true;

	if (!m_wndKeySetting.GetUsePS())
		return false;

	csPin = m_wndKeySetting.GetPIN(0xF);

	if (bIsUICC)
		csAPDU = _T("00");
	else
		csAPDU = _T("A0");

	csAPDU = csAPDU+_T("17000108")+csPin;

	csSW = _TestCaseSendCommand(csAPDU);
	iSW  = _CString2Int(csSW);


	if (iSW == 0x9000)
		return true;
	else 
		m_wndKeySetting.SetUsePS(false);
		
	return false;
}

int CMainFrame::_TerminalProfile(CString csProfile,bool bUICC)
{
	CString csSend,csResp,csLc;

	if (bUICC)
		csSend = _T("80100000");
	else
		csSend = _T("A0100000");

	csLc.Format("%02X",csProfile.GetLength()/2);

	csSend = csSend + csLc +csProfile;

	csResp = _TestCaseSendCommand(csSend);

	return _CString2Int(csResp);
}

int CMainFrame::_Fetch(int iFetchLen, CString& csResp, bool bUICC)
{
	CString csSend,csRes,csLe;
	int iSW;

	if (bUICC)
		csSend = _T("80120000");
	else
		csSend = _T("A0120000");

	csLe.Format("%02X",iFetchLen);

	csRes = _TestCaseSendCommand(csSend+csLe);

	iSW   = _CString2Int(csRes.Right(04));

	csResp = csRes.Left(csRes.GetLength()-4);

	return iSW;
}

int CMainFrame::_TerminalResponse(int iDetails,int iResult, CString csAddData ,bool bUICC)
{
	CString csResult;
	CString csDetails;
	CString csSend,csRes,csLe;


	if (bUICC)
		csSend = _T("80140000");
	else
		csSend = _T("A0140000");

	csDetails.Format(_T("%06X"),iDetails);

	csDetails = _T("8103")+csDetails;

	csResult.Format(_T("%02X"),iResult);

	csResult = _T("8301")+csResult;

	csResult = csDetails+_T("82028281")+csResult;

	if (!csAddData.IsEmpty())
		csResult +=csAddData;


	csLe.Format("%02X",csResult.GetLength()/2);

	csRes = _TestCaseSendCommand(csSend+csLe+csResult);

	return _CString2Int(csRes);
}

int CMainFrame::_TerminalResponseMenuSeletion(int iMenu)
{
	CString csID;

	csID.Format("%02X",iMenu);

	return _TerminalResponse(0x012400,0x00, _T("1001")+csID,bIsUICC);
}

int CMainFrame::_EnvelopMenuSeletion(int iMenu)
{
	CString csSend,csRes;
	CString csNum;

	csNum.Format("%02X",iMenu);

	if (bIsUICC)
		csSend = _T("80");
	else
		csSend = _T("A0");

	csSend = csSend+_T("C2000009D307820201811001"+csNum);

	csRes = _TestCaseSendCommand(csSend);

	return _CString2Int(csRes);
}

int CMainFrame::MapFileThread(void)
{

	CMainFrame *CurMainFrm;

	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();

	CurMainFrm-> _GetFileThread(); 

	iThread  = Def_Thread_Free ;

	return 1;

}
int CMainFrame::MapAllFileThread(void)
{

	CMainFrame *CurMainFrm;

	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();


	CurMainFrm-> __GetFileThread(); 

	iThread  = Def_Thread_Free ;

	return 1;

}

int CMainFrame::SearchFileThread(void)
{

	CMainFrame *CurMainFrm;

	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();


	CurMainFrm-> _SearchFileThread(); 

	iThread  = Def_Thread_Free ;

	return 1;

}

int CMainFrame::SaveCurrentCardThread()
{

	CMainFrame *CurMainFrm;

	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();

	CCardManageDoc* NewDOC = CurMainFrm->m_wndProperties->GetDocument();


	CurMainFrm-> SaveTreeItem(); 

	CurMainFrm->bGetData = true;

	iThread = Def_Thread_Free;

	return 0;
}

int CMainFrame::CheckMapFileListThread()
{
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CurMainFrm->CheckFileList();
	iThread = Def_Thread_Free;

	return 0;
}

int CMainFrame:: WriteTestADNThread()
{
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CurMainFrm-> m_dlgADN.WriteTestADN();
	iThread = Def_Thread_Free;
	return 0;
}
int CMainFrame:: ReadTestADNThread()
{
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CurMainFrm-> m_dlgADN.ReadSetADN2List();
	iThread = Def_Thread_Free;
	return 0;
}

int CMainFrame:: ReadShortMessageThread()
{
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CurMainFrm-> m_dlgSMS.ReadShortMessageList();
	iThread = Def_Thread_Free;
	return 0;
}

int CMainFrame:: ClearShortMessageThread()
{
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CurMainFrm-> m_dlgSMS._ClearMessageFile();
	iThread = Def_Thread_Free;
	return 0;
}

int CMainFrame::RunSendCommandScript()
{

	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	if (CurMainFrm-> m_dlgSendCommand.OpenRunScriptList()<0)
		CurMainFrm->MessageBox("脚本运行中出现错误");
	iThread = Def_Thread_Free;
	return 0;
}


int CMainFrame::SetStatusThread()
{

	CMainFrame *CurMainFrm;

	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();

	do 
	{


		Sleep(100);
		CurMainFrm-> _SetCurrentStatus(); 

	} while (iThread != Def_Thread_Free);


	CurMainFrm-> _SetCurrentStatus(); 

	return 0;

}

void CMainFrame::_GetApplicationListThread()
{
	//HTREEITEM hMF,hDF,hEF;
	CString csData;
	CString csAID,csName;
	CString csFCI;
	int iRecLen;
	CString csTemp;


	if (_TestCaseFileIsExisted(_T("3F00"))<0)
		return ;
	if (_TestCaseSelectFile(_T("2F00"),csFCI,bIsUICC))
	{
		csData = _TestCaseReadCurrentFileData(csFCI,bIsUICC);

		if (!bIsUICC)
			iRecLen = _CString2Int( csFCI.Mid(28,2));
		else
		{
			csFCI   = GetTLVData(csFCI,0x62);
			csFCI   = GetTLVData(csFCI,0x82);
			iRecLen = _CString2Int( csFCI.Mid(0x08,04));
		}

		for (int i = 0 ; i < csData.GetLength(); i+= iRecLen*2)
		{
			csTemp = csData.Mid(i,iRecLen*2);
			csTemp = GetTLVData(csTemp,0x61);

			csAID  = GetTLVData( csTemp,0x4F);
			csName = GetTLVData( csTemp,0x50);
		}
		m_wndLeftPane.AddNewApplication(TranslateAscii(csName),csAID,csName);
	}

	if (_TestCaseFileIsExisted(_T("7F20"))>=0)
		m_wndLeftPane.AddNewApplication(_T("GSM"),_T("7F20"),_T("GSM"));

	if (_TestCaseFileIsExisted(_T("7F25"))>=0)
		m_wndLeftPane.AddNewApplication(_T("CDMA"),_T("7F25"),_T("CDMA"));

}

void CMainFrame::NewMapFileThread()
{
	DWORD code;

	if (!ConfirmCardStatue())
		return;


	GetExitCodeThread(hThread,&code);      

	if (code != STILL_ACTIVE)
	{
		hThread  = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE) MapFileThread,NULL, 0, NULL);
	}
	else
		ResumeThread(hThread);

	iThread = Def_Thread_GetFile;
	return ;
}

void CMainFrame::NewMapAllFileThread()
{
	DWORD code;

	if (!ConfirmCardStatue())
		return;


	GetExitCodeThread(hThread,&code);      

	if (code != STILL_ACTIVE)
	{
		hThread  = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE) MapAllFileThread,NULL, 0, NULL);
	}
	else
		ResumeThread(hThread);

	iThread = Def_Thread_GetFile;
	return ;
}

void CMainFrame::NewSearchFileThread()
{
	DWORD code;
	if (!ConfirmCardStatue())
		return;
	GetExitCodeThread(hThread,&code);      

	if (code != STILL_ACTIVE)
	{

		//iFileNum = 0;
		hThread  = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE) SearchFileThread,NULL, 0, NULL);
	}
	else
		ResumeThread(hThread);

	iThread = Def_Thread_SearchFile;
	return ;

}

void CMainFrame::NewSetStatusThread()
{
	DWORD code;
	GetExitCodeThread(hSetStatusThread,&code);      

	if (code != STILL_ACTIVE)
		hSetStatusThread  = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE) SetStatusThread,NULL, 0, NULL);
	else
		ResumeThread(hSetStatusThread);
	return ;
}

void CMainFrame::NewSaveCurrentCardThread()
{

	DWORD code;
	if (!ConfirmCardStatue())
		return;

	GetExitCodeThread(hThread,&code);      

	if (code != STILL_ACTIVE)
	{

		//iFileNum = 0;
		hThread  = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE) SaveCurrentCardThread,NULL, 0, NULL);
	}
	else
		ResumeThread(hThread);

	iThread = Def_Thread_SaveCard;
	return ;

}

void CMainFrame::NewCheckMapFileListThread()
{

	DWORD code;

	if (!ConfirmCardStatue())
		return;


	GetExitCodeThread(hThread,&code);      

	if (code != STILL_ACTIVE)
	{

		//iFileNum = 0;
		hThread  = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE) CheckMapFileListThread,NULL, 0, NULL);
	}
	else
		ResumeThread(hThread);

	iThread = Def_Thread_MapFile;
	return ;

}

void CMainFrame::NewWriteTestADNThread()
{
	DWORD code;

	if (!ConfirmCardStatue())
		return;


	GetExitCodeThread(hThread,&code);      

	if (code != STILL_ACTIVE)
	{

		//iFileNum = 0;
		hThread  = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE) WriteTestADNThread,NULL, 0, NULL);
	}
	else
		ResumeThread(hThread);

	iThread = Def_Thread_WriteADN;
	return ;

}
void CMainFrame::NewReadTestADNThread()
{
	DWORD code;

	if (!ConfirmCardStatue())
		return;


	GetExitCodeThread(hThread,&code);      

	if (code != STILL_ACTIVE)
	{

		//iFileNum = 0;
		hThread  = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE) ReadTestADNThread,NULL, 0, NULL);
	}
	else
		ResumeThread(hThread);

	iThread = Def_Thread_WriteADN;
	return ;

}

void CMainFrame::NewReadShortMessageThread()
{
	DWORD code;

	if (!ConfirmCardStatue())
		return;


	GetExitCodeThread(hThread,&code);      

	if (code != STILL_ACTIVE)
	{

		//iFileNum = 0;
		hThread  = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE) ReadShortMessageThread,NULL, 0, NULL);
		//hThread  = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE) ReadTestADNThread,NULL, 0, NULL);
	}
	else
		ResumeThread(hThread);

	iThread = Def_Thread_ReadSMS;
	return ;

}


void CMainFrame::NewClearShortMessageThread()
{

	DWORD code;

	if (!ConfirmCardStatue())
		return;


	GetExitCodeThread(hThread,&code);      

	if (code != STILL_ACTIVE)
	{

		//iFileNum = 0;
		hThread  = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE) ClearShortMessageThread,NULL, 0, NULL);
		//hThread  = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE) ReadTestADNThread,NULL, 0, NULL);
	}
	else
		ResumeThread(hThread);

	iThread = Def_Thread_ClearSMS;
	return ;


}

void CMainFrame::NewRunSendCommandScriptThread()
{

	DWORD code;

	if (!ConfirmCardStatue())
		return;


	GetExitCodeThread(hThread,&code);      

	if (code != STILL_ACTIVE)
	{
		hThread  = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)RunSendCommandScript,NULL, 0, NULL);
	}
	else
		ResumeThread(hThread);

	iThread = Def_Thread_ClearSMS;
	return ;

}


void CMainFrame::NewGetFlashDataThread()
{
	DWORD code;

	if (bReadMode)
	{
		if (!ConfirmCardStatue())
			return;
	}
	GetExitCodeThread(hThread,&code);      
	if (code != STILL_ACTIVE)
	{
		hThread  = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)_TestGetFlashDataThread,NULL, 0, NULL);
	}
	else
		ResumeThread(hThread);
	iThread = Def_Thread_GetFlashData;
	return ;
}




int CMainFrame::_TestGetFlashDataThread()
{
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CurMainFrm->_TestGetFlashData();
	iThread  = Def_Thread_Free ;
	return 0;
}



int CMainFrame::_TestGetFlashData()
{
	_TestCaseGetFlashData(_TestCaseGetFlashSize()) ;

	MessageBox(_T("读取完成！"));

	return 0;
}




bool CMainFrame::Connect_Card()
{
	int iRet;

	CMFCRibbonComboBox* pFontComboBox = DYNAMIC_DOWNCAST(
		CMFCRibbonComboBox, m_wndRibbonBar.FindByID(ID_PcscReader_Combo));

	CString csName = pFontComboBox->GetEditText();

	//重新连接读卡器清除品状态
	InitCardParamater();

	csCardATR.Empty();
	switch (iReaderStatus)
	{
	case  0:
		iRet = DisConnectReader();
		iReaderStatus = Def_Terminal_Disconnected;
	case -1:
		iRet = ConnectReader(csName);
		if (iRet != 0)
		{
			MessageBox("Select Reader failed!");
			break;
		}
		iReaderStatus = Def_Terminal_Connected;
	case -2:

		iRet = PowerOnCard(csCardATR);
		if (iRet != 0)
		{
			MessageBox("Get ATR failed!");
			break;
		}

		iReaderStatus = Def_Card_Connected;
		break;
	default:
		MessageBox("未知卡片状态，请重启读卡器以及程序！");
		break;
	}
	if (csCardATR.IsEmpty())
		return false;
	else
		return true;

}
void CMainFrame::MapFile()
{

	m_wndClassView->DeleteAllItems();
	bGetData    = false;
	NewMapFileThread();
	NewSetStatusThread();
	m_wndLeftPane.TransationAppList(csAppList);
}
void CMainFrame::MapAllFile()
{

	m_wndClassView->DeleteAllItems();
	bGetData    = false;
	NewMapAllFileThread();
	NewSetStatusThread();
	m_wndLeftPane.TransationAppList(csAppList);
}

void CMainFrame::Changefilevalue()
{
	CString csFCI,csFileData;
	m_wndClassView->_SetHistoryItem(NULL);
	if (m_wndClassView->_IsDFItem(m_wndClassView->GetSelectedItem()))
		return;

	if (!DClickClassTreeView(m_wndClassView->GetSelectedItem(),TRUE))
	{
		return;
	}
}
void CMainFrame::SetProgressCounter(int iAll,int iCurrent)
{
	CString csProgress;

	if (iAll == 0)
		return ;

	iCurrent = iCurrent*100 / iAll;

	csProgress.Format("%d",iCurrent);

	m_ElementPro->SetText(csProgress+_T("%"));
	m_wndStatusBar.RedrawWindow();

}

void CMainFrame::SearchFile(HTREEITEM hCurrent,bool bSure)
{
	CString csPath;

	if (!m_wndClassView->_IsDFItem(hCurrent))
		hCurrent = m_wndClassView->GetNextItem(hCurrent,TVGN_PARENT);

	if (hCurrent == NULL)
		hCurrent = m_wndClassView->GetRootItem();

	csPath = m_wndClassView->_GetItemPath(hCurrent);



	m_dlgSearchFile.InstallCurrentPath(csPath,hCurrent);
	m_dlgSearchFile.InstallSearchFile(bSure);
	m_dlgSearchFile.ShowWindow(SW_SHOW);

}

void CMainFrame ::InsatllFile(HTREEITEM hCurrent,bool bCatalog)
{
	CString csPath;

	if (!m_wndClassView->_IsDFItem(hCurrent))
		hCurrent = m_wndClassView->GetNextItem(hCurrent,TVGN_PARENT);

	if (hCurrent == NULL)
		hCurrent = m_wndClassView->GetRootItem();

	csPath = m_wndClassView->_GetItemPath(hCurrent);
	m_dlgSearchFile.InstallCurrentPath(csPath,hCurrent);
	if (bCatalog)
		m_dlgSearchFile.InstallClassTree(_DEF_DF_C);
	else
		m_dlgSearchFile.InstallClassTree(_DEF_WORK_EF_C);

	m_dlgSearchFile.ShowWindow(SW_SHOW);



}



void CMainFrame ::InsatllFile2ClassTree(CString csFile,CString csDes,int iDir ,HTREEITEM *hRes ,HTREEITEM hParen,int iState)
{
	bool bRet;
	HTREEITEM hSelFile;

	//当加入为空是，则选择当前选中ITEM
	if (hParen == NULL)
		hParen = m_wndClassView->GetSelectedItem();

	//判断ITEM 是否为DF
	if (!m_wndClassView->_IsDFItem(hParen))
		hParen = m_wndClassView->GetNextItem(hParen,TVGN_PARENT);

	switch(iDir)
	{
	case _DEF_DF_C:
		if (csFile.GetLength() == 4)
			bRet = m_wndClassView->Insert_DF(_CString2Int(csFile),csDes,&hSelFile,hParen,iState);
		else
			bRet = m_wndClassView->Insert_ADF(csFile,csDes,&hSelFile,hParen,iState);
		break;
	case _DEF_INTERNAL_EF_C:
	case _DEF_WORK_EF_C:bRet = m_wndClassView->Insert_EF(_CString2Int(csFile),csDes,&hSelFile,hParen,iState);break;
	default:   m_wndClassView->Insert_TEST(_CString2Int(csFile),csDes,&hSelFile,hParen,iState);break;
	}

	if (hSelFile != NULL)
		m_wndClassView->SelectedItem(hSelFile);
	if (hRes!= NULL)
		*hRes = hSelFile;
}

void CMainFrame::ChangeFileDesInClassTree(CString csPath,CString csDes)
{
	m_wndClassView->ChangeEFDescription(csPath,csDes);
}
int CMainFrame::_GetApplacationSum()
{
	return _GetCStringDataSum(csAppList);
}
int CMainFrame::_GetApplacation(int iNum,CString& csPath)
{
	CString csApp;
	int iName,iPath,iDesc,iTypt;
	if (iNum>_GetCStringDataSum(csAppList))
		return -1;

	 _GetCStringData(csAppList,iNum+1,csApp);
	iName = csApp.Find(_T(":"),0);
	iPath = csApp.Find(_T(":"),iName+1);
	iDesc = csApp.Find(_T(":"),iPath+1);
	iTypt = csApp.Find(_T(":"),iDesc+1);
	csPath = csApp.Mid(iName+1,iPath-iName-1);

	return _CString2Int(csApp.Mid(iDesc+1,iTypt-iDesc-1));


}

int CMainFrame::_MapTeleApplicaiton()
{
	CString csData;
	CString csAID,csName;
	CString csFCI;
	int iRecLen;
	CString csTemp;

	csAppList.Empty();



	//if (_TestCaseSelectFile(_T("3F00"),csFCI,bIsUICC))
	//{
	//	if (_GetPIN1Enable(csFCI,bIsUICC))
	//		_TestCaseVerify(1);


	//}
	//else
	//	return 0;

	_TestCaseSelectFile(_T("3F00"),csFCI,bIsUICC);
	if (_TestCaseSelectFile(_T("2F00"),csFCI,bIsUICC))
	{
		csData = _TestCaseReadCurrentFileData(csFCI,bIsUICC);

		if (!bIsUICC)
			iRecLen = _CString2Int( csFCI.Mid(28,2));
		else
		{
			csFCI   = GetTLVData(csFCI,0x62);
			csFCI   = GetTLVData(csFCI,0x82);
			iRecLen = _CString2Int( csFCI.Mid(0X04,04));
		}

		for (int i = 0 ; i < csData.GetLength(); i+= iRecLen*2)
		{
			csTemp = csData.Mid(i,iRecLen*2);
			csTemp = GetTLVData(csTemp,0x61);
			if (!csTemp.IsEmpty())
			{
				csAID  = GetTLVData( csTemp,0x4F);

				csName = csAID.Left(10);
				if (csName == _T("A000000087"))
					csName = _T("3GPP");
				else if(csName == _T("A000000343"))
					csName = _T("3GPP2");
				else
					csName = _T("Test..");

				csAppList += csName+_T(":");
				csAppList += csAID+_T(":");
				csAppList += TranslateAscii(GetTLVData( csTemp,0x50))+_T(":");
				csAppList += _T("01:");
				csAppList += _T(";");
			}


		}
	}

	if (_TestCaseFileIsExisted(_T("7F20"))>=0)
		csAppList += _T("GSM:7F20:GSM:00:;");

	if (_TestCaseFileIsExisted(_T("7F25"))>=0)
		csAppList += _T("CDMA:7F25:CDMA:00:;");


	return 1 ;
	
}
void CMainFrame::__GetFileThread()
{
	HTREEITEM hMFItem,hTeleItem;
	if (!bIsUICC)
		return ;
	m_wndClassView->DeleteAllItems();
	if (_TestCaseFileIsExisted(_T("3F00"))<0)
		return ;
	InsatllFile2ClassTree(_T("3F00"),_T(""),_DEF_DF_C,&hMFItem,TVI_ROOT,_LV_Existed);
	CString csPath;
	int iRet;
	for (int i = 0 ; i < _GetApplacationSum(); i++)
	{
		iRet = _GetApplacation(i,csPath);
		if (iRet < 0)
			return;
		if (_TestCaseFileIsExisted(_T("3F00"))<0)
			return ;
		if (_TestCaseFileIsExisted(csPath,(iRet>0)))
		{
			InsatllFile2ClassTree(csPath,_T(""),_DEF_DF_C,&hTeleItem,hMFItem,_LV_Existed);
			__SearchFile_UICC(0x0001,0xFFFF,hTeleItem);
		}
	}
	__SearchFile_UICC(0x0001,0xFFFF,hMFItem);
	return ;
}

void CMainFrame::_GetFileThread()
{
	HTREEITEM hMFItem,hTeleItem,h3stItem;

	m_wndClassView->DeleteAllItems();



	if (_TestCaseFileIsExisted(_T("3F00"))<0)
		return ;

	InsatllFile2ClassTree(_T("3F00"),_T(""),_DEF_DF_C,&hMFItem,TVI_ROOT,_LV_Existed);

	_SearchFile(0x2F00,0x2FFF,hMFItem);


	if (_TestCaseFileIsExisted(_T("7F10"))>=0)
	{
		InsatllFile2ClassTree(_T("7F10"),_T(""),_DEF_DF_C,&hTeleItem,hMFItem,_LV_Existed);

		_SearchFile(0x6F00,0x6FFF,hTeleItem);


		if (_TestCaseFileIsExisted(_T("5F3A"))>=0)
		{

			InsatllFile2ClassTree(_T("5F3A"),_T(""),_DEF_DF_C,&h3stItem,hTeleItem,_LV_Existed);

			_SearchFile(0x4F00,0x4FFF,h3stItem);

		}
		if (_TestCaseFileIsExisted(_T("5F3B"))>=0)
		{

			InsatllFile2ClassTree(_T("5F3B"),_T(""),_DEF_DF_C,&h3stItem,hTeleItem,_LV_Existed);
			_SearchFile(0x4F00,0x4FFF,h3stItem);

		}
		if (_TestCaseFileIsExisted(_T("5F3C"))>=0)
		{

			InsatllFile2ClassTree(_T("5F3C"),_T(""),_DEF_DF_C,&h3stItem,hTeleItem,_LV_Existed);


			_SearchFile(0x4F00,0x4FFF,h3stItem);

		}
		if (_TestCaseFileIsExisted(_T("5F50"))>=0)
		{

			InsatllFile2ClassTree(_T("5F50"),_T(""),_DEF_DF_C,&h3stItem,hTeleItem,_LV_Existed);

			_SearchFile(0x4F00,0x4FFF,h3stItem);

		}
	}



	CString csPath;
	int iRet;
	for (int i = 0 ; i < _GetApplacationSum(); i++)
	{
		iRet = _GetApplacation(i,csPath);
		if (iRet < 0)
			return;
		if (_TestCaseFileIsExisted(_T("3F00"))<0)
			return ;

		if (_TestCaseFileIsExisted(csPath,(iRet>0)))
		{
			InsatllFile2ClassTree(csPath,_T(""),_DEF_DF_C,&hTeleItem,hMFItem,_LV_Existed);

			_SearchFile(0x6F00,0x6FFF,hTeleItem);
		}

		if (_TestCaseFileIsExisted(_T("5F3A"))>=0)
		{
			InsatllFile2ClassTree(_T("5F3A"),_T(""),_DEF_DF_C,&h3stItem,hTeleItem,_LV_Existed);
			_SearchFile(0x4F00,0x4FFF,h3stItem);
		}
		if (_TestCaseFileIsExisted(_T("5F3B"))>=0)
		{
			InsatllFile2ClassTree(_T("5F3B"),_T(""),_DEF_DF_C,&h3stItem,hTeleItem,_LV_Existed);
			_SearchFile(0x4F00,0x4FFF,h3stItem);
		}

		if (_TestCaseFileIsExisted(_T("5F3C"))>=0)
		{
			InsatllFile2ClassTree(_T("5F3C"),_T(""),_DEF_DF_C,&h3stItem,hTeleItem,_LV_Existed);
			_SearchFile(0x4F00,0x4FFF,h3stItem);
		}
		if (_TestCaseFileIsExisted(_T("5F40"))>=0)
		{
			InsatllFile2ClassTree(_T("5F40"),_T(""),_DEF_DF_C,&h3stItem,hTeleItem,_LV_Existed);
			_SearchFile(0x4F00,0x4FFF,h3stItem);
		}
		if (_TestCaseFileIsExisted(_T("5F50"))>=0)
		{
			InsatllFile2ClassTree(_T("5F50"),_T(""),_DEF_DF_C,&h3stItem,hTeleItem,_LV_Existed);
			_SearchFile(0x4F00,0x4FFF,h3stItem);
		}

		if (_TestCaseFileIsExisted(_T("5F70"))>=0)
		{
			InsatllFile2ClassTree(_T("5F70"),_T(""),_DEF_DF_C,&h3stItem,hTeleItem,_LV_Existed);
			_SearchFile(0x4F00,0x4FFF,h3stItem);
		}
	
	}



	
	return ;
}

void CMainFrame::_SearchFileThread()
{
	CString csDF,csResult,csFile;
	int iSum;

	if (!m_dlgSearchFile.bSearch)
		m_dlgSearchFile.iEnd = m_dlgSearchFile.iStart;

	csDF =m_dlgSearchFile.GetSearchDF();

	iSum = _GetMarkNumber(csDF,_T("||"));

	for (int i  = 0 ; i< iSum; i++)
	{

		 _GetDatasInMark(csDF,_T("||"),i+1,csFile);

		if ((csFile.IsEmpty())||(!_TestCaseSelectFile(csFile,csResult,bIsUICC,(csFile.GetLength()!=4))))
		{
			return ;
		}		
	}
	_SearchFile(m_dlgSearchFile.iStart,m_dlgSearchFile.iEnd,m_dlgSearchFile.bSearchItem);

}

void CMainFrame::_SetCurrentStatus()
{

	CString csTemp;
	
	m_ElementATR->SetText(_T("ATR: ")+csCardATR);

	switch(iReaderStatus)
	{
	case Def_Card_Connected:       csTemp = _T("卡片已连接");break;
	case Def_Terminal_Disconnected:csTemp = _T("终端已断开");break;
	case Def_Card_Disconnected:    csTemp = _T("卡片已断开");break;
	default:                       csTemp = _T("未知状态");break;
	}
	m_ElementSta->SetText(csTemp);



	switch(iThread&0xFF)
	{
	case Def_Thread_Free:        csTemp = _T("空闲状态.......||");break;
	case Def_Thread_GetFile:     csTemp = _T("获取文件中.....||");break;
	case Def_Thread_SearchFile:  csTemp = _T("搜索文件中.....||");break;
	case Def_Thread_SaveCard:    csTemp = _T("保存文件中.....||");break;
	case Def_Thread_MapFile:     csTemp = _T("检查文件列表...||"); break;
	case Def_Thread_ReadADN :    csTemp = _T("读取测试号簿...||"); break;
	case Def_Thread_WriteADN:    csTemp = _T("写入测试号簿...||"); break;
	case Def_Thread_ReadSMS:     csTemp = _T("读取短信.......||"); break;
	case Def_Thread_ClearSMS:    csTemp = _T("清空短信.......||"); break;
	case Def_Thread_RunScript:   csTemp = _T("运行脚本.......||"); break;
	case Def_Thread_Ending:      csTemp = _T("结束进程中.....||");break;
	case Def_Thread_ExportCSV:   csTemp = _T("导出文件中.....||");break;
	case Def_Thread_GetFlashData:csTemp = _T("获取数据中.....||");break;
	default:                     csTemp = _T("未知进程.......||");break;

	}

	if ((iThread&Def_Thread_Suspend) == Def_Thread_Suspend)
	{
		csTemp = _T("暂停 - ")+csTemp;
	}

	m_ElementThr->SetText(csTemp);


	m_wndStatusBar.RedrawWindow();

	if (iThread == Def_Thread_Free)
		m_wndClassView->SetClassTreeEnable(true);
	else
		m_wndClassView->SetClassTreeEnable(false);

}

void CMainFrame::_SearchFile(int iStartFile,int iEndFile,HTREEITEM hDFItem)
{

	if (bIsUICC)
	{
		_SearchFile_UICC(iStartFile,iEndFile,hDFItem);
	}
	else
	{
		_SearchFile_GSM(iStartFile,iEndFile,hDFItem);
	}


}

//检查iFID 的DF 是在 hItem 的DF下；
//************************************
// Method:    _DFIsUnderItem_UICC
// FullName:  CMainFrame::_DFIsUnderItem_UICC
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: int iFID
// Parameter: HTREEITEM hItem
// Parameter: int CheckLevel 2 - 4为有效数值， 
//            2只用前两个判断， 以此类推,
//            非特殊情况使用两种足够
//            特殊卡片 Select 有错误时候使用 高等级
//            或者全局搜索时 使用高等级
//************************************
int CMainFrame::_DFIsUnderItem_UICC(int iFID,HTREEITEM hItem, int CheckLevel /*= 2*/)
{

	int iRet;
	iRet = FALSE;

	HTREEITEM hParent;
	HTREEITEM hRootItem;
	hRootItem = m_wndClassView->GetRootItem();

	//判断1
	//如果DF FID 和 Parent DF FID 相同则判断不成立
	// 如果 FID 和 MF相同则判断不成立
	if (( iFID == _CString2Int( m_wndClassView->_GetItemFID(hItem)))||
		( iFID == _CString2Int( m_wndClassView->_GetItemFID(m_wndClassView->GetRootItem()))))
		return FALSE;


	//判断2
	//使用选择当前DF目录下文件
	//如果失败则表明不成立
	_TestCaseSelectCurrentFile(hItem);//当前目录肯定可以选择，
	if ( _TestCaseFIDIsExistedInCurrent(Int2CString(iFID,4)) != 0x9000)
		return FALSE;

	//判断3
	//获取AID为空，则 表明 可以使用从MF开始的路径的方式。
	if ((CheckLevel >2)&&(m_wndClassView->_GetItemAID(hItem).IsEmpty()))
	{
		CString csPath = m_wndClassView->_GetItemPath(hItem);
		//去除显示路径中的分隔符 

		csPath.Replace(_T("||"),_T(""));
		//加上当前文件
		csPath = csPath + Int2CString(iFID,4);
		//去除路径中 MF 3F00
		csPath = csPath.Mid(4);

		//如果路径无法选择表明 判断不成立
		if (_TestCasePathIsExistedStartMF(csPath) != 0x9000)
			return FALSE;

	}


	//判断4
	//选中hItem的父目录进行选择，如果父目录可以选择，表明判断不成立
	//全体父目录存在；

	//当前目录为 Root时，则没有Parent Item
	if ((CheckLevel >3)&&(hRootItem != hItem))
	{
		hParent = m_wndClassView->GetNextItem(hItem,TVGN_PARENT);
		_TestCaseSelectCurrentFile(hParent);//当前父目录肯定可以选择，
	    //父目录下可以选择，表明判断不成立
		if ( _TestCaseFIDIsExistedInCurrent(Int2CString(iFID,4)) == 0x9000)
			return FALSE;

	}
	//满足以上4个判断 方可判断为目录为当前目录

	return TRUE;
}
void CMainFrame::_SearchFile_UICC(int iStartFile,int iEndFile,HTREEITEM hDFItem)
{

	HTREEITEM hFileItem;
	CString csFile;
	int iRet;

	for (int iCyc = iStartFile ; iCyc <= iEndFile; iCyc++)
	{
		SetProgressCounter(iEndFile-iStartFile,iCyc-iStartFile);

		if (iThread == Def_Thread_Ending)
			return;

		csFile    = Int2CString(iCyc,04);
		iRet      = _TestCaseFileIsExisted(csFile);
		hFileItem = _FileIsExist(iCyc,hDFItem);

		// 文件已经存在,则改变确定并修改文件状态
		if (hFileItem != NULL)
		{
			if (iRet >= 0 )
				m_wndClassView->ChangeItemState(hFileItem,_LV_Existed);
			else
				m_wndClassView->ChangeItemState(hFileItem,_LV_Absent);
		}

		else if(iRet >= 0)
		{//文件没有存在,所以需要添加到列表中
			switch(iRet&0x38)
			{
			case 0x38: 

				if (_DFIsUnderItem_UICC(iCyc,hDFItem))
					InsatllFile2ClassTree(csFile,_T(""),_DEF_DF_C,NULL,hDFItem,_LV_Existed);
				_TestCaseSelectCurrentFile(hDFItem);
				break;
			case 00:InsatllFile2ClassTree(csFile,_T(""),_DEF_INTERNAL_EF_C ,NULL,hDFItem,_LV_Existed);break;
			case 01:InsatllFile2ClassTree(csFile,_T(""),_DEF_WORK_EF_C,NULL,hDFItem,_LV_Existed);break;
			default:InsatllFile2ClassTree(csFile,_T(""),_DEF_PRO_C,NULL,hDFItem,_LV_Existed);break;

			}

		}

	}
}
void CMainFrame::__SearchFile_UICC(int iStartFile,int iEndFile,HTREEITEM hDFItem)
{
	HTREEITEM hFileItem;
	CString csFile;
	int iRet;
	_TestCaseSelectCurrentFile(hDFItem);
	for (int iCyc = iStartFile ; iCyc <= iEndFile; iCyc++)
	{
		SetProgressCounter(iEndFile-iStartFile,iCyc-iStartFile);
		if (iThread == Def_Thread_Ending)
			return;
		csFile    = Int2CString(iCyc,04);
		iRet      = _TestCaseFileIsExisted(csFile);
		hFileItem = _FileIsExist(iCyc,hDFItem);
		if (hFileItem != NULL)
		{
			if (iRet >= 0 )
				m_wndClassView->ChangeItemState(hFileItem,_LV_Existed);
			else
				m_wndClassView->ChangeItemState(hFileItem,_LV_Absent);
		}
		else if(iRet >= 0)
		{//文件没有存在,所以需要添加到列表中
			switch(iRet&0x38)
			{
			case 0x38: 
				if (_DFIsUnderItem_UICC(iCyc,hDFItem,4))
				{
					HTREEITEM hItem;
					InsatllFile2ClassTree(csFile,_T(""),_DEF_DF_C,&hItem,hDFItem,_LV_Existed);
					
					__SearchFile_UICC(iStartFile,iEndFile,hItem);
				}
				_TestCaseSelectCurrentFile(hDFItem);
			
				break;
			case 00:InsatllFile2ClassTree(csFile,_T(""),_DEF_INTERNAL_EF_C ,NULL,hDFItem,_LV_Existed);break;
			case 01:InsatllFile2ClassTree(csFile,_T(""),_DEF_WORK_EF_C,NULL,hDFItem,_LV_Existed);break;
			default:InsatllFile2ClassTree(csFile,_T(""),_DEF_PRO_C,NULL,hDFItem,_LV_Existed);break;
			}
		}
	}
}

//检查iFID 的DF 是在 hItem 的DF下；
int CMainFrame::_DFIsUnderItem_GSM(int iFID,HTREEITEM hItem)
{
	int iRet;
	iRet  =  1;
	HTREEITEM hParentItem;
	hParentItem = m_wndClassView->GetNextItem(hItem,TVGN_PARENT);

	//如果没有父Item 则hItem 为MF GSM 下没有两个MF；所以可以确定一定不是在MF下，否则 继续检查
	if (hParentItem != NULL)
	{
		//选中父Item
		_TestCaseSelectCurrentFile(hParentItem);
		//选择 文件 通过FID
		iRet = _TestCaseFileIsExisted_GSM(Int2CString(iFID,4));

		//选中则表示在hItem下，否则在为在hItem下

		if (iRet>=0)
			iRet = 0;

	}
	return iRet;

}

void CMainFrame::_SearchFile_GSM(int iStartFile,int iEndFile,HTREEITEM hDFItem)
{
	HTREEITEM hFileItem;
	CString csFile;
	int iRet;
	for (int iCyc = iStartFile ; iCyc <= iEndFile; iCyc++)
	{
		SetProgressCounter(iEndFile-iStartFile,iCyc-iStartFile);

		if (iThread == Def_Thread_Ending)
			return;

		csFile = Int2CString(iCyc,4);
		iRet = _TestCaseFileIsExisted_GSM(csFile);

		hFileItem = _FileIsExist(iCyc,hDFItem);


		// 文件已经存在,则改变确定并修改文件状态

		if (hFileItem != NULL)
		{
			if (iRet >= 0 )
				m_wndClassView->ChangeItemState(hFileItem,_LV_Existed);
			else
				m_wndClassView->ChangeItemState(hFileItem,_LV_Absent);
		}
		else if(iRet>=0)
		{
			//文件没有存在,所以需要添加到列表中

			switch(iRet)
			{

				//01 02 为MF 或者DF
			case 01:
				if ((hDFItem == NULL)||(hDFItem == TVGN_ROOT))
					InsatllFile2ClassTree(csFile,_T(""),_DEF_DF_C,NULL,hDFItem,_LV_Existed);
				//重新选中当前目录
				_TestCaseSelectCurrentFile(hDFItem);
				break;
			case 02:
				////此处判断是否为父目录, 用此来剔出层级错误问题
				//hFileItem = hDFItem;
				//do 
				//{
				//	//获取DF FID 如果相等则 退出, Item为NULL,不等则继续
				//	if (CString2Int(m_wndClassView->_GetItemFID(hFileItem))!= iCyc)
				//	{

				//		hFileItem = m_wndClassView->GetNextItem(hFileItem,TVGN_PARENT);
				//		//如果获取到父Item为Null 则表示所找目录不为父目录，可以添加
				//		if (hFileItem == NULL)
				//			InsatllFile2ClassTree(csFile,_T(""),_DEF_DF_C,NULL,hDFItem,_LV_Existed);
				//	}
				//	else
				//		hFileItem = NULL;
				//} while (hFileItem!= NULL);

				if (_DFIsUnderItem_GSM(iCyc,hDFItem) == 1)
					InsatllFile2ClassTree(csFile,_T(""),_DEF_DF_C,NULL,hDFItem,_LV_Existed);
				//重新选中当前目录
				_TestCaseSelectCurrentFile(hDFItem);
				break;

				//04位EF 其他为内部使用，也当EF 使用。
			case 04:InsatllFile2ClassTree(csFile,_T(""),_DEF_WORK_EF_C,NULL,hDFItem,_LV_Existed);break;
			case 00:
			default:InsatllFile2ClassTree(csFile,_T(""),_DEF_PRO_C,NULL,hDFItem,_LV_Existed);break;

			}


		}



		//if ((iRet <= 0)&&(hFileItem != NULL))
		//{
		//	m_wndClassView->ChangeItemState(hFileItem,_LV_Absent);
		//}
		//else if(hFileItem != NULL )
		//{
		//	m_wndClassView->ChangeItemState(hFileItem,_LV_Existed);
		//}
		//else if ((iRet == 02)||(iRet == 01))
		//{
		//	_TestCaseSelectCurrentFile(m_wndClassView->GetNextItem(hDFItem,TVGN_PARENT),false);
		//	if (_TestCaseFileIsExisted_GSM(csFile) != 0)
		//		InsatllFile2ClassTree(csFile,_T(""),_DEF_DF_C,NULL,hDFItem,_LV_Existed);
		//	_TestCaseSelectCurrentFile(hDFItem);
		//}
		//else if(iRet > 0)
		//	InsatllFile2ClassTree(csFile,_T(""),_DEF_WORK_EF_C,NULL,hDFItem,_LV_Existed);
	}

	


}

int CMainFrame::_GetFileAC(int iOperate, CString csFCI, bool bUICC)
{

	int iRet;
	if (bUICC)
	{
	}
	else
	{

		switch(iOperate)
		{
		case 01:
			iRet = _CString2Int( csFCI.Mid(16,1));
			break;
		case 02:
			iRet = _CString2Int( csFCI.Mid(17,1));
			break;
		case 04:
			iRet = _CString2Int( csFCI.Mid(18,1));
			break;
		case 8:
			iRet = _CString2Int( csFCI.Mid(20,1));
			break;
		case 9:
			iRet = _CString2Int( csFCI.Mid(21,1));
			break;
		default:
			iRet = 0xF;
			break;
		}
	}

	return iRet;
}

bool CMainFrame::_GetPIN1Enable(CString csFCI, bool bUICC)
{
	bool bRet;
	if (bUICC)
	{
		bRet = _GetPIN1EnableInUICC(csFCI);
	}
	else
		bRet = Getbit_E(csFCI,105);
	return bRet;
}

bool CMainFrame::_GetPIN1EnableInUICC(CString csFCP)
{
	bool bRet = false;
	CString csC6Value,csPSDO,csDO,csPIN;
	int iLen,iOff,iNum;
	csC6Value = GetTLVData(csFCP,0x62);
	csC6Value = GetTLVData(csC6Value,0xC6);	
	if (csC6Value.IsEmpty())
		return bRet;
	iOff = 0;

	if (!csC6Value.IsEmpty())
	{
		iLen   = csC6Value.GetLength();
		csPSDO = GetTLVData(csC6Value,0x90);
		csDO   = GetTLVData(csC6Value,0x95);

		if (!csPSDO.IsEmpty())
		{
			iOff += 6;
		}
		else
			return bRet;
		if (!csDO.IsEmpty())
		{
			iOff += 6;
		}
		csPIN.Empty();

		iNum  = (iLen- iOff)/6;

		for (int i = 0 ; i <iNum  ; i++)
		{
			csPIN = GetTLVData(csC6Value.Mid(iOff,iLen-iOff),0x83);

			if (_CString2Int(csPIN) == 01)
				bRet = Getbit(csPSDO,0x8 -i);
			else
				iOff += 6;


		}

	}
	return bRet;
}

HTREEITEM CMainFrame::_FileIsExist(int iFile,HTREEITEM hDFItem)
{
	HTREEITEM hCurrentItem;
	CString csFID;

	hCurrentItem = m_wndClassView->GetChildItem(hDFItem);

	while(hCurrentItem)
	{
	//	csFID = m_wndClassView->_GetItemText(hCurrentItem);

		csFID =  m_wndClassView->_GetItemFID(hCurrentItem);
		if (csFID.IsEmpty())
			csFID =  m_wndClassView->_GetItemAID(hCurrentItem);

		if (iFile == _CString2Int(csFID))
			return hCurrentItem;

		hCurrentItem = m_wndClassView->GetNextItem(hCurrentItem,TVGN_NEXT);

	}

	return NULL;
}


BOOL CMainFrame::SaveTreeItem()
{
	csCard.Empty();

	iFileNum = m_wndClassView->StatisticFileNumber();
	iCurNum  = 0;
	SaveDF2Ram(m_wndClassView->GetRootItem(),1);
	return TRUE;
}

BOOL CMainFrame::SaveDF2Ram(HTREEITEM hDF,int iLevel)
{
	HTREEITEM hChild;
	BOOL bRet;
	CString csFID,csFCI;
	CString csStart,csEnd,csFormat;

	bRet = TRUE;

	csFormat = RepeatCString(_T("  "),iLevel);

	//csFID  = m_wndClassView->_GetItemText(hDF);

	csFID =  m_wndClassView->_GetItemFID(hDF);
	if (csFID.IsEmpty())
		csFID =  m_wndClassView->_GetItemAID(hDF);


	csStart = _T("<")+csFID+_T(">");
	csEnd   = _T("</")+csFID+_T(">");

	csCard += csFormat + csStart + _T("\n\r");

	csFCI = _TestCaseSelectCurrentFile(hDF);

	SaveParameter2Ram(csFCI,iLevel);

	hChild = m_wndClassView->GetNextItem(hDF,TVGN_CHILD);

	csCard += csFormat + _T("<File")+ csFID + _T(">\n\r");

	while (hChild != NULL)
	{
		if (iThread == Def_Thread_Ending)
		{
			iThread = Def_Thread_Free;
			return FALSE;
		}

		if (m_wndClassView->_IsDFItem(hChild))
			bRet = SaveDF2Ram(hChild,iLevel+1);
		else
			bRet = SaveEF2Ram(hChild ,iLevel+1 );

		if (bRet == FALSE)
			return bRet;




		hChild = m_wndClassView->GetNextItem(hChild,TVGN_NEXT);

	}

	csCard += csFormat + _T("</File")+ csFID + _T(">\n\r");

	csCard += csFormat + csEnd + _T("\n\r");

	return bRet;
}

BOOL CMainFrame::SaveEF2Ram(HTREEITEM hEF,int iLevel)
{

	BOOL bRet;
	CString csFID,csFCI;
	CString csStart,csEnd,csFormat;

	csFormat = RepeatCString(_T("  "),iLevel);

	//csFID  = m_wndClassView->_GetItemText(hEF);

	csFID =  m_wndClassView->_GetItemFID(hEF);
	if (csFID.IsEmpty())
		csFID =  m_wndClassView->_GetItemAID(hEF);

	csStart = _T("<")+csFID+_T(">");
	csEnd   = _T("</")+csFID+_T(">");

	csCard += csFormat + csStart + _T("\n\r");

	csFCI = _TestCaseSelectCurrentFile(hEF);

	bRet = SaveParameter2Ram(csFCI,iLevel+1);

	bRet = SaveData22Ram(csFCI,iLevel+1);

	csCard += csFormat + csEnd + _T("\n\r");

	iCurNum ++;

	SetProgressCounter(iFileNum,iCurNum);

	return bRet;

}

BOOL CMainFrame ::SaveParameter2Ram(CString csFCI,int iLevel)
{	
	CString csFormat;

	csFormat = RepeatCString(_T("  "),iLevel);

	if (!csFCI.IsEmpty())
	{
		csFCI = csFCI.Left(csFCI.GetLength());
		csCard += (csFormat + _T("<FCI>")+csFCI+_T("</FCI>\n\r"));
	}


	return TRUE;

}

BOOL CMainFrame ::SaveData22Ram(CString csFCI,int iLevel)
{	
	CString csFormat;
	CString csDatas;
	csFormat = RepeatCString(_T("  "),iLevel);

	csDatas += _TestCaseReadCurrentFileData(csFCI,bIsUICC);

	csCard += csFormat+  _T("<Datas>") + csDatas + _T("</Datas>\n\r"); 
	return TRUE;
}

BOOL CMainFrame ::SetRam2TreeItem()
{
	bReadMode  = false;
	m_wndClassView->DeleteAllItems();
	_DeleteEnterSpace(csCard);
	Set2TreeItem(csCard,m_wndClassView->GetRootItem());
	return TRUE;
}

BOOL CMainFrame ::Set2TreeItem(CString csCardData,HTREEITEM hDFItem)
{
	int iRet;
	CString csFID,csFCI,csFile,csNext,csTempFile,csTempRemind;
	HTREEITEM hCurrentItem;
	int iDF;
	do 
	{
		iRet = _GetXMLFirstNode(csCardData,&csFID,&csFile,&csNext,NULL);


		if (!csFID.IsEmpty())
		{
			 ;

			if ((_FindFistNodeCurrnent(csFile,_T("FCI"),&csFCI,&csTempFile))&&(!GetTLVData(csFCI,0x62).IsEmpty()))
			{
				switch(_CString2Int(GetTLVData(GetTLVData(csFCI,0x62),0x82).Left(02))&0x38)
				{
				case 0x38: iDF = _DEF_DF_C;	break;
				case 00:   iDF = _DEF_INTERNAL_EF_C;	break;
				case 01:   iDF = _DEF_WORK_EF_C;	break;
				default:   iDF = _DEF_PRO_C;	break; 
				}
			}
			else
			{
				if (_CString2Int(csFCI.Mid(12,2)) != 04)
					 iDF = _DEF_PRO_C;	
				else
					 iDF = _DEF_WORK_EF_C;	
			}

			InsatllFile2ClassTree(csFID,_T(""),iDF,&hCurrentItem,hDFItem);


			if((_FindFistNodeCurrnent(csFile,_T("File")+csFID,&csTempFile,&csTempRemind))&&(!csTempFile.IsEmpty()))
				Set2TreeItem(csTempFile, hCurrentItem);
			csCardData = csNext;
		}
	} while (!csCardData.IsEmpty());

	return TRUE;

}

CString CMainFrame ::SelectInRam(CString csPath)
{
	int iNum;
	CString csResult,csRemind;
	CString csFile;

	csResult = csCard;

//	iNum = csPath.GetLength() /4 ;

	iNum = _GetMarkNumber(csPath,_T("||"));



	for (int iCyc = 0; iCyc < iNum ; iCyc ++ )
	{

		 _GetDatasInMark(csPath,_T("||"),iCyc+1,csFile);
		 _FindFistNodeCurrnent(csResult,csFile,&csResult,&csRemind);

		if (iCyc != iNum-1)
			_FindFistNodeCurrnent(csResult,_T("File")+csFile,&csResult,&csRemind);

	}

	return csResult;
}

CString CMainFrame ::SelectInRam(HTREEITEM hCurrentItem)
{
	CString csPath;

	csPath = m_wndClassView->_GetItemPath(hCurrentItem);

	return SelectInRam(csPath);
}

void CMainFrame::ExplainFile(HTREEITEM hCurrentItem)
{
	CString csFile;
	int  iDF,iPFID,iPPFID,iFID;
	int  iLayer,iDFLayer;

	iLayer = m_wndClassView->GetFileLayer(hCurrentItem);

	iPPFID = 0;
	iPFID  = 0;

	if (m_wndClassView->_IsDFItem(hCurrentItem))
		iDFLayer = iLayer;
	else
		iDFLayer = iLayer-1;


	iDF = _DEF_Card;

	iPFID = m_wndClassView->GetFileLayerFID(hCurrentItem,iDFLayer);

	if ((iPFID >= 0x5F00) &&(iPFID <= 0x5FFF))
	{
		iPPFID = m_wndClassView-> GetFileLayerFID(hCurrentItem,iDFLayer-1);
	}


	switch(iPPFID)
	{
	case 00:
		if (iPFID == 0x7F10)     iDF = _DEF_Tele;
		else if(iPFID == 0x7F20) iDF = _DEF_GSM;
		else if(iPFID == 0x7F25) iDF = _DEF_CDMA;		
		else if(iPFID == 0x10087) iDF = _DEF_3GPP;
		else if(iPFID == 0x10343) iDF = _DEF_3GPP2;		
		else if(iPFID == 0x10009) iDF = _DEF_ETSI;	
		else if(iPFID == 0x7F2E) iDF = _DEF_CDMA;	
		else iDF = _DEF_Card;	
		break;
	case 0x7F10:
		if (iPFID == 0x5F50)     iDF = _DEF_Tele;
		else if(iPFID == 0x5F3A) iDF = _DEF_PHONEBOOK;
		else if(iPFID == 0x5F3B) iDF = _DEF_MULTIMEDIA;
		else if(iPFID == 0x5F3C) iDF = _DEF_MMSS;		
		else iDF = _DEF_Tele;	
		break;
	case 0x7F20:
		if (iPFID == 0x7F10)     iDF = _DEF_Tele;
		else if(iPFID == 0x7F20) iDF = _DEF_GSM;
		else if(iPFID == 0x7F25) iDF = _DEF_CDMA;		
		else iDF = _DEF_GSM;	
		break;
	case 0x7F25:
		if (iPFID == 0x7F10)     iDF = _DEF_Tele;
		else if(iPFID == 0x7F20) iDF = _DEF_GSM;
		else if(iPFID == 0x7F25) iDF = _DEF_CDMA;		
		else iDF = _DEF_CDMA;	
		break;
	case 0x7F2E:
		if (iPFID == 0x7F10)     iDF = _DEF_Tele;
		else if(iPFID == 0x7F20) iDF = _DEF_GSM;
		else if(iPFID == 0x7F25) iDF = _DEF_CDMA;		
		else iDF = _DEF_CDMA;	
		break;
	case 0x10009:
		if (iPFID == 0x7F10)     iDF = _DEF_Tele;
		else if(iPFID == 0x7F20) iDF = _DEF_GSM;
		else if(iPFID == 0x7F25) iDF = _DEF_CDMA;		
		else if(iPFID == 0x7F2E) iDF = _DEF_CDMA;	
		else iDF = _DEF_ETSI;	
		break;
	case 0x10087:
		if (iPFID     == 0x5F3A) iDF = _DEF_PHONEBOOK;
		else if(iPFID == 0x5F3B) iDF = _DEF_GSMACCESS;
		else if(iPFID == 0x5F3C) iDF = _DEF_MExE;
		else if(iPFID == 0x5F40) iDF = _DEF_WLAN;	
		else if(iPFID == 0x5F50) iDF = _DEF_HNB;	
		else if(iPFID == 0x5F70) iDF = _DEF_SoLSA;	
		else if(iPFID == 0x5F80) iDF = _DEF_BCAST;	
		else iDF = _DEF_3GPP;	
		break;
	case 0x10343:
		if (iPFID == 0x7F10)     iDF = _DEF_Tele;
		else if(iPFID == 0x7F20) iDF = _DEF_GSM;
		else if(iPFID == 0x7F25) iDF = _DEF_CDMA;		
		else iDF = _DEF_3GPP2;	
		break;
	default:iDF = _DEF_Card;break;
	}


	iFID =  m_wndClassView->GetFileLayerFID(hCurrentItem,iLayer);

	m_wndProperties->ExplainFile(iFID,iDF);
	//此处作预留设置ChangeFile的文件类别
	m_dlgChangeFile.SetCurrentFileInformation(iFID,iDF);
	
}

int CMainFrame::StartUpCurrentApplicaiton(CString csApp)
{

	m_wndSIMToolkit.StartSIMToolkit();

	if (!m_wndSIMToolkit.IsWindowVisible())
			m_wndSIMToolkit.ShowWindow(SW_SHOW);


	return 0;
}


int CMainFrame::_GetRecordLength(CString csFCI)
{
	CString csFileInformation;
	int iRecLen;
	if (bIsUICC)
	{
		csFileInformation = GetTLVData(csFCI,0x62);
		csFileInformation  = GetTLVData(csFileInformation,0x82);
		if (csFileInformation.GetLength() < 8)
			iRecLen = 0;
		else
			iRecLen = _CString2Int (csFileInformation.Mid(04 ,04));
	}
	else
		iRecLen  = _CString2Int(csFCI.Mid(28,02));
	return iRecLen;
}
int CMainFrame::_GetRecordNumber(CString csFCI)
{
	CString csFileInformation;
	int iRecNum,iRecLen;

	if (bIsUICC)
	{
		csFileInformation = GetTLVData(csFCI,0x62);
		csFileInformation  = GetTLVData(csFileInformation,0x82);
		if (csFileInformation.GetLength() < 10)
			iRecNum = 0;
		else
			iRecNum = _CString2Int (csFileInformation.Mid(0x8 ,02));
	}
	else
	{
		iRecLen = _CString2Int(csFCI.Mid(28,02));
		if (iRecLen!= 0)
			iRecNum  = _CString2Int(csFCI.Mid(04,04))/iRecLen;
		else
			iRecNum = 0;
	}

	return iRecNum;

}

int CMainFrame::_GetFileSize(CString csFCI)
{
	CString csFileInformation;

	int iFileSize;

	if (bIsUICC)
	{
		csFileInformation = GetTLVData(csFCI,0x62);
		csFileInformation  = GetTLVData(csFileInformation,0x80);
		iFileSize = _CString2Int (csFileInformation);
	}
	else
	{
		iFileSize  = _CString2Int(csFCI.Mid(04,04));
	}

	return iFileSize;

}
int CMainFrame::_GetFileStructure(CString csFCI)
{
	CString csFileInformation;
	int iStructure;
	if (bIsUICC)
	{
		csFileInformation = GetTLVData(csFCI,0x62);
		csFileInformation = GetTLVData(csFileInformation,0x82);
		iStructure        = _CString2Int (csFileInformation.Left(2))&0x7;
	}
	else
	{
		iStructure  = _CString2Int(csFCI.Mid(26,02));
		switch(iStructure)
		{
		case 0:iStructure = 1 ;break;
		case 1:iStructure = 2 ;break;
		case 3:iStructure = 6 ;break;
		}
	}
	return iStructure;
}

int CMainFrame::_GetFileSFI(CString csFCI)
{
	CString csSFI;

	csSFI = GetTLVData(csFCI,0x62);
	if (csSFI.IsEmpty())
		return FALSE;
	csSFI =  GetTLVData(csSFI,0x88);
	if (csSFI.IsEmpty())
		return FALSE;

	return _CString2Int(csSFI)/0x8;
}

void CMainFrame::CheckFileList(void)
{
	iFileNum = m_wndClassView->StatisticFileNumber();
	iCurNum  = 0;
	CheckMapFile(m_wndClassView->GetRootItem());
	iThread = Def_Thread_Free;
}
int CMainFrame ::CheckMapFile(HTREEITEM hItem)
{
	HTREEITEM hChildItem;
	CString csFCI;
	int iAbsent;
	iAbsent = 0 ;
	hChildItem = m_wndClassView->GetChildItem(hItem);

	while(hChildItem)
	{
		
		if (iThread == Def_Thread_Ending)
			return iAbsent;


		if (m_wndClassView->_IsDFItem(hChildItem))
			iAbsent += CheckMapFile(hChildItem);
		else
			iCurNum ++;

		csFCI = _TestCaseSelectCurrentFile(hChildItem);
		if (csFCI.IsEmpty())
			iAbsent += 1;

		hChildItem= m_wndClassView->GetNextItem(hChildItem,TVGN_NEXT);

		SetProgressCounter(iFileNum,iCurNum);
	}
	return iAbsent;
}

bool CMainFrame::CheckCardConnected()
{	bool bRet = true;
	if (iReaderStatus == Def_Card_Connected)
	{
	
		switch(iReaderType)
		{
		case Def_ReaderType_PCSC:bRet = (PcscReader.GetCardATR(NULL)>0);break;
		case Def_ReaderType_CCR5: bRet = (CCR5_GetCardStatus(CCR5Hand) == Statuse_OnVol)  ;break;
		default:break;
		}
		
	}
	return bRet;
}

bool CMainFrame::ConfirmCardStatue(void)
{



	if ((iReaderStatus!=Def_Card_Connected)||
		(!CheckCardConnected()))
	{


		if (MessageBox(_T("需要连接卡片,是否连接?"),_T("连接"),MB_OKCANCEL) == 1 )
		{
			if (!Connect_Card())
				return false;
		}
		else
			return false;
		
	}

	NewSetStatusThread();
	return true;
}


bool CMainFrame::ConfirmPin1VerifyStatue(void)
{
	int iRet;
	if ((uiVerifyPIN&1)== 0)
	{
		iRet = GetPin1Status();

		if (iRet == 0)
		{
			if (MessageBox(_T("需要校验Pin1"),_T("Verify Pin"),MB_OKCANCEL) == 1 )
			{
				if (_TestCaseVerify(1))
					return true;
			}
			return false;
		}
		else if  (iRet != 1)
			return false;
	}

	return true;

}


// 断电重启
bool CMainFrame::_TestCaseColdReset(void)
{

	byte ucATR[50];
	int iRet;
	UINT iATRLen;
	ZeroMemory(ucATR,50);
	iATRLen = 0;

	switch(iReaderType)
	{
	case Def_ReaderType_PCSC: 
		iRet = PcscReader.ResetCard(ColdReset);
		if (!iRet)
			iATRLen = PcscReader.GetCardATR(ucATR);

		break;
	case Def_ReaderType_CCR5: 
		iRet = CCR5_PowerOffCard(CCR5Hand);
		iRet = CCR5_PowerOnCard(CCR5Hand,NULL,ucATR,&iATRLen,&lWorkTime);
		break;
	default:break;
	}

	if (iATRLen>0)
	{
		_UcHex2CString(ucATR,iATRLen,csCardATR);
		m_wndOutput.Print2Output(_T("重新启动:成功"),_T("$Warm Reset"),csCardATR);
		m_wndOutput.PrintTime2Output(lWorkTime);
		return true;
	}
	else
	{	
		csCardATR.Empty();
		m_wndOutput.Print2Output(_T("重新启动:失败"),_T("$Warm Reset"),csCardATR);
		return false;
	}

	InitCardParamater();

}
// 热启
bool CMainFrame::_TestCaseWarmReset(void)
{
	byte ucATR[50];
	int iRet;
	UINT iATRLen;
	ZeroMemory(ucATR,50);
	iATRLen = 0;

	switch(iReaderType)
	{
	case Def_ReaderType_PCSC: 
		iRet = PcscReader.ResetCard(WarmReset);
		if (!iRet)
			iATRLen = PcscReader.GetCardATR(ucATR);
		
		break;
	case Def_ReaderType_CCR5: iRet = CCR5_ResetCard(CCR5Hand,NULL,ucATR,&iATRLen,&lWorkTime);break;
	default:break;
	}

	if (iATRLen>0)
	{
		 _UcHex2CString(ucATR,iATRLen,csCardATR);
		m_wndOutput.Print2Output(_T("热启动:成功"),_T("$Warm Reset"),csCardATR);
		m_wndOutput.PrintTime2Output(lWorkTime);
		return true;
	}
	else
	{	
		csCardATR.Empty();
		m_wndOutput.Print2Output(_T("热启动:失败"),_T("$Warm Reset"),csCardATR);
		return false;
	}

	InitCardParamater();
}
// //修改个空间的字体
void CMainFrame::UpdateFont(void)
{
	m_wndOutput.UpdateFonts();
	m_wndGetFlash.UpdateFonts();
	m_dlgChangeFile.UpdateFonts();
}

int CMainFrame::GetPinStatus(void)
{
	int iRet;
	int iPin1C,iPin2C,iPuk1C,iPuk2C;

	iRet = GetPin1Status();

	if(iRet == 0)
		m_wndPinStatus.SetPin1Disable( false);
	else if(iRet == 1)
	{
		m_wndPinStatus.SetPin1Disable( true);
		uiVerifyPIN = uiVerifyPIN|1;
	}
	iPin1C = 0;
	iPin2C = 0;
	iPuk1C = 0;
	iPuk2C = 0;
	if (bIsUICC)
	{

		
		iPin1C = GetPinRemianedNumber(01);
		//m_wndPinStatus.SetPinPukRemaindNumber(iPin1C,01,true);
		iPin2C = GetPinRemianedNumber(0x81);
		//m_wndPinStatus.SetPinPukRemaindNumber(iPin2C,0x81,true);

		iPuk1C = GetPukRemianedNumber(01);
		//m_wndPinStatus.SetPinPukRemaindNumber(iPuk1C,01,false);
		iPuk2C = GetPukRemianedNumber(0x81);
		//m_wndPinStatus.SetPinPukRemaindNumber(iPuk2C,0x81,false);
		//return TRUE;

	}
	else
	{
		CString csRes;
		if (_TestCaseSelectFile(_T("3F00"),csRes,false))
		{
			iPin1C = _CString2Int(csRes.Mid(36,2))&0xF;
			iPin2C = _CString2Int(csRes.Mid(40,2))&0xF;
			iPuk1C = _CString2Int(csRes.Mid(38,2))&0xF;
			iPuk2C = _CString2Int(csRes.Mid(42,2))&0xF;

		}
	}

	m_wndPinStatus.SetPinPukRemaindNumber(iPin1C,01,true);
	m_wndPinStatus.SetPinPukRemaindNumber(iPin2C,0x81,true);
	m_wndPinStatus.SetPinPukRemaindNumber(iPuk1C,01,false);
	m_wndPinStatus.SetPinPukRemaindNumber(iPuk2C,0x81,false);

	return TRUE;

	
}

//此处为Disable 状态
//************************************
// Method:    GetPin1Status
// FullName:  CMainFrame::GetPin1Status
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: void 
//************************************
int CMainFrame::GetPin1Status(void){

	CString csFCI;

	if (!_TestCaseSelectFile(_T("3F00"),csFCI,bIsUICC))
	{
		MessageBox(_T("Select MF failed!"));
		return -1;		
	}

	return _GetPIN1Enable(csFCI,bIsUICC);
}

int CMainFrame::GetPinRemianedNumber(int iPin)
{
	CString csAPDU,csResp;
	CString csPIN;
	int iRes = 0;

	csPIN.Format("%02X",iPin);
	csAPDU = _T("002000")+csPIN+_T("00");

	csResp = _TestCaseSendCommand(csAPDU);
	iRes   = _CString2Int(csResp);

	if ((iRes&0xFFF0)==0x63C0)
		iRes = iRes&0x000F;
	else
		iRes = 0;
	return iRes;
}

int CMainFrame::GetPukRemianedNumber(int iPuk)
{
	CString csAPDU,csResp;
	CString csPuk;
	int iRes;

	csPuk.Format("%02X",iPuk);
	csAPDU = _T("002C00")+csPuk+_T("00");

	csResp = _TestCaseSendCommand(csAPDU);
	iRes   = _CString2Int(csResp);
	if ((iRes&0xFFF0)==0x63C0)
		iRes = iRes&0x000F;
	else
		iRes = 0;
	return iRes;
}

// 断开读卡器,当前支持 PCSC,CCR5
int CMainFrame::DisConnectReader(void)
{
	int iRet;
	switch(iReaderType)
	{
	case Def_ReaderType_PCSC: iRet = PcscReader.DisConnectReader();break;
	case Def_ReaderType_CCR5: iRet = CCR5_DisConnectTerminal(CCR5Hand);break;
	default:break;
	}
	return iRet;
}

// 连接读卡器
int CMainFrame::ConnectReader(CString csName)
{
	int iRet;
	switch(iReaderType)
	{
	case Def_ReaderType_PCSC: iRet = ConnectReader_PCSC(csName);break;
	case Def_ReaderType_CCR5: iRet = ConnectReader_CCR5(csName);break;
	default:break;
	}
	return iRet;

}

int CMainFrame::ConnectReader_PCSC(CString csName)
{
	int iRet;
	LPTSTR  szReaderName[10];
	iRet =  PcscReader.GetContext();
	iRet =  PcscReader.GetPcsclist(szReaderName);
	iRet =  PcscReader.ConnectReader((LPTSTR)(LPCTSTR)csName);

	return iRet;
}

int CMainFrame::ConnectReader_CCR5(CString csName)
{
	int iRet;
	BYTE ucT_PTS[4] = {"\x12\x00\x02"};
	BYTE ucT_ATR[50];
	BYTE ucT_Mau[50];
	UINT uiT_ATRLen,uiT_MauLen;
	BYTE ucCardStatus;
	iRet = CCR5_ConnectTerminal(&CCR5Hand,atoi(csName.Right(csName.GetLength()-3)),ucT_PTS,0x3,
		ucT_ATR,&uiT_ATRLen,&ucCardStatus,ucT_Mau,&uiT_MauLen);

	if (iRet == CT_Tran_OK)
		iRet = CCR5_SetupTerminal2Default(CCR5Hand);

	if (iRet != CT_Tran_OK)
	{
		CCR5_DisConnectTerminal(CCR5Hand);
		return -1;
	}

	return 0;
}
// 给CCR5上电并且获取ATR,或者 只是PCSC 获取ATR
int CMainFrame::PowerOnCard(CString& csATR)
{
	int iRet;
	BYTE ucATR[50];
	UINT uiATRLen = 0;
	BYTE ucCardStatus;
	lWorkTime = 0;

	switch(iReaderType)
	{
	case Def_ReaderType_PCSC:   uiATRLen = PcscReader.GetCardATR(ucATR);break;
	case Def_ReaderType_CCR5:   iRet     = CCR5_PowerOnCard(CCR5Hand,&ucCardStatus,ucATR,&uiATRLen,&lWorkTime); break;
	default: break;
	}
	if (uiATRLen>0)
		_UcHex2CString(ucATR,uiATRLen,csATR);
	else
		return -1;

	m_wndOutput.Print2Output(_T("上电:成功"),_T("$"),csCardATR);
	m_wndOutput.PrintTime2Output(lWorkTime);


	return 0;
}
// 初始化CCR5列表
bool CMainFrame::Initialize_CCR5List(void)
{
	CMFCRibbonComboBox* pFontComboBox = DYNAMIC_DOWNCAST(
		CMFCRibbonComboBox, m_wndRibbonBar.FindByID(ID_PcscReader_Combo));

	BYTE ucProt[10];
	UINT uiPortMax = 10;
	BOOL bRet;
	CString csTemp;

	iReaderType    = Def_ReaderType_CCR5;

	pFontComboBox->RemoveAllItems();

	bRet = CCR5_GetList(ucProt,&uiPortMax);
	if (bRet)
	{
		for (UINT i = 1 ; i<= uiPortMax;i++)
		{
			csTemp.Format("%d",ucProt[i-1]);
			pFontComboBox->AddItem("COM"+csTemp);
		}
		pFontComboBox->SelectItem(0);
	}

	return true;
}

// uiTime 100us;uiSequence 0-6;csSequenceData see CCR5 Pro......
CString CMainFrame::_InterruptSend(CString csSend, UINT uiTime, UINT uiSequence,BOOL bExATR,BOOL bSelf,CString csSequenceData)
{
	UINT uiRet;
	BYTE *ucPart1;
	BYTE *ucPart2;
	UINT uiPart1Len;
	UINT uiPart2Len;
//	UINT uiByte19;
	UINT uiSetTime;
	//读取part1;
	ucPart1 = new BYTE[0x1F];
	uiPart1Len = 0x1F;
	ucPart2 = new BYTE[0x1C];
	uiPart2Len = 0x1C;
	ZeroMemory(ucPart1,uiPart1Len);
	ZeroMemory(ucPart2,uiPart2Len);
	uiRet = CCR5_GetTerminalSetting(CCR5Hand,00,ucPart1,&uiPart1Len);
	ucPart1[19]= 0xE0;
	uiRet = CCR5_SetTerminalSetting(CCR5Hand,01,01,ucPart1,0x1F);
	if (bSelf)
	{

	}
	else
	{
		switch(uiSequence )
		{
		case 02:

			_CString2UcHex(_T("1000000020006530006660006770006810006940006a80006b000000"),ucPart2);

			for (int i = 4; i<0x1C; i+=3)
			{
				if (ucPart2[i] != 00)
				{
					uiSetTime = uiTime + i/3;
					ucPart2[i+1]= uiSetTime/0x100;
					ucPart2[i+2]= uiSetTime%0x100;
				}
			}
			break;
		case 03:

			_CString2UcHex(_T("11009C4020000A2100D2000000000000000000000000000000000000"),ucPart2);
			for (int i = 4; i<0x1C; i+=3)
			{
				if (ucPart2[i] != 00)
				{
					uiSetTime = ucPart2[i+1]*0x100+ucPart2[i+2] + uiTime;
					ucPart2[i+1]= uiSetTime/0x100;
					ucPart2[i+2]= uiSetTime%0x100;
				}
			}
			break;
			

			break;
		}

		uiRet = CCR5_SetTerminalSetting(CCR5Hand,2,8,ucPart2,0x1C);

	}
	BYTE *ucSend;
	BYTE *ucResp;
	UINT uiSend;
	UINT uiResp;
	LONG lTime;

	uiSend = csSend.GetLength()/2;

	ucSend = new BYTE[uiSend + 0x20];
	ucResp = new BYTE[300];
	ZeroMemory(ucSend,uiSend + 0x20);

	uiSend = _CString2UcHex(csSend,ucSend);

	uiRet = CCR5_Send2Card(CCR5Hand,ucSend,uiSend,ucResp,&uiResp,&lTime);

	ucPart1[19]= 0x10;
	uiRet = CCR5_SetTerminalSetting(CCR5Hand,01,01,ucPart1,0x1F);
	CString csResult;
	 _UcHex2CString(ucResp,uiResp,csResult);
	return csResult;
}



BOOL CMainFrame::_SetReference(HTREEITEM hSelectItem)
{

	CString csPath,csFID,csFile,csRoute;

	csPath = m_wndClassView->_GetItemPath(hSelectItem);

	int iNum = _GetMarkNumber(csPath,_T("||"));

	csRoute.Empty();

	for (int iCyc = 0; iCyc < iNum ; iCyc ++ )
	{

		_GetDatasInMark(csPath,_T("||"),iCyc+1,csFile);

		if (csFile.GetLength()==4)
			csRoute =csRoute+csFile;
		else if (csFile.Mid(0,10)== "A000000087")
			csRoute =csRoute+_T("7FF0");
		else if (csFile.Mid(0,10)== "A000000343")
			csRoute =csRoute+_T("7FF1");

	}

	csFID   = csRoute.Right(4);
	csRoute = csRoute.Left(csRoute.GetLength()-4);

	if ((csRoute.GetLength()>4)&&
		(csRoute.Left(4) == "3F00"))
		csRoute = csRoute.Mid(4);

	if ((!m_wndReference.OpenReference(csRoute,csFID))&&
	    (!m_wndReference._OpenReference( m_wndClassView->_GetItemDescription(hSelectItem))))
		return FALSE;

	return TRUE;
}

// 单击选中的Item ，只选中文件，UICC下获取 ARR ,GSM下不操作，如果在Phone book 下或先获取PBR
int CMainFrame::ClickClassTreeView(HTREEITEM hSelectItem,CString* csOutPutFCI)
{
	//是否Item 为空，如果为空，使用当前选中的；
	//主要应用于不是通过鼠标选中操作时可能出现的情况。
	//如果读卡器没有连接，则进行读卡器连接！

	m_dlgChangeFile.SetCurrentFileInformation(NULL,NULL);

	if ((bReadMode)&&(!ConfirmCardStatue()))
		return FALSE;
	if (hSelectItem== NULL)
		hSelectItem = m_wndClassView->GetSelectedItem();
	if (hSelectItem == NULL )
		return FALSE;
	//如果当前进程为不空闲则不操作！
	if (iThread != Def_Thread_Free)
		return FALSE;
	CString csFCI;

	//找寻规范文档
	if (_SetReference(hSelectItem))
		TRACE("Not found reference");

	if (!_SelectItem(hSelectItem,&csFCI))
		return FALSE;

	if (!_SetInformation2PropList(hSelectItem,csFCI))
		return FALSE;

	if ((bIsUICC)&&(!_SelectItem(hSelectItem,&csFCI)))
			return FALSE;

	if (csOutPutFCI!= NULL)
		*csOutPutFCI = csFCI;

	ExplainFile(hSelectItem);

	return TRUE;
}
int CMainFrame::_SelectItem(HTREEITEM hSelectItem,CString* csOutPutFCI)
{
	int iRet;
	if (bReadMode)
		iRet = SelectItemInCard(hSelectItem,csOutPutFCI);
	else 
		iRet = SelectItemInFile(hSelectItem,csOutPutFCI);
	return iRet;
}

int CMainFrame::_SetInformation2PropList(HTREEITEM hSelectItem,CString csInputFCI)
{
	int iRet = FALSE;

	if (bIsUICC)
	{
		m_wndProperties->SetFCI2PropList(csInputFCI);

		if(bGetARR)
		{
			CString csARRInfo;
			if (_GetARRInformation(csInputFCI,hSelectItem,csARRInfo) == TRUE)
			{
				m_wndProperties->SetExpandedFormatSecurity2PropList(csARRInfo,m_wndClassView->_IsDFItem(hSelectItem));
				iRet = TRUE;
			}
			else
			{
				if(MessageBox(_T("获取 ARR 失败，是否继续当前操作"),_T("Warning"),MB_OKCANCEL)== IDOK)
					iRet = TRUE;
			}
		}
		else
			iRet = TRUE;
	}
	else
	{
		m_wndProperties->_SetFCI2PropList(csInputFCI);
		iRet = TRUE;
	}




	return iRet;
}
// 给卡片发送Select指令，并且返回FCI， 附加操作详情见CliclClassTreeView
int CMainFrame::SelectItemInCard(HTREEITEM hSelectItem, CString* csOutPutFCI)
{
	//int iRet;
	////如果读卡器没有连接，则进行读卡器连接！
	//if (!ConfirmCardStatue())
	//	return FALSE;
	////if (bIsUICC)
	//	iRet = SelectItemInUICCCard( hSelectItem, csOutPutFCI);
	////else
	////	iRet = SelectItemInNotUICCCard( hSelectItem, csOutPutFCI);

	//return iRet;
	CString csFCI;

	csFCI = _TestCaseSelectCurrentFile(hSelectItem);
	if (csOutPutFCI != NULL)
		*csOutPutFCI = csFCI;

	if (csFCI.IsEmpty())
		return FALSE;

	return TRUE;
}

//使用UICC 的指令集，具体操作见 SelectItemInCard
int CMainFrame::SelectItemInUICCCard(HTREEITEM hSelectItem, CString* csOutPutFCI)
{

	CString csFCI;

	csFCI = _TestCaseSelectCurrentFile(hSelectItem);
	if (csOutPutFCI != NULL)
		*csOutPutFCI = csFCI;

	if (csFCI.IsEmpty())
		return FALSE;

	//m_wndProperties->SetFCI2PropList(csFCI);

	//if (!SetARRInformation2PropListInCard(csFCI,hSelectItem))
	//	MessageBox(_T("解析文件ARR文件出错！"));

	//csFCI = _TestCaseSelectCurrentFile(hSelectItem);

	return TRUE;
}
//使用非UICC 的指令集，具体操作见 SelectItemInCard
int CMainFrame::SelectItemInNotUICCCard(HTREEITEM hSelectItem, CString* csOutPutFCI)
{

	CString csFCI;

	csFCI = _TestCaseSelectCurrentFile(hSelectItem);

	if (csFCI.IsEmpty())
		return FALSE;

	if (csOutPutFCI != NULL)
		*csOutPutFCI = csFCI;

	m_wndProperties->_SetFCI2PropList(csFCI);

	return TRUE;
}
// 根据FCI 解析ARR ，并且输出（有可能选进行选择文件等操作）
int CMainFrame::_GetARRInformation(CString csFCI, HTREEITEM hItem,CString&csARRInformation)
{
	HTREEITEM hParentItem;
	CString csInfo,csARRInfo,csARRFID,csTempFCI,csARRData;
	CString csFIDPath,csFileData;
	int iRecordLen,iOffset;
	csInfo = GetTLVData(csFCI,0x62);
	if (csInfo.IsEmpty())
		return FALSE;
	csARRInfo = GetTLVData(csInfo,0xAB);
	if (!csARRInfo.IsEmpty())
	{
		csARRInformation = csARRInfo;
		return TRUE;
	}
	csARRInfo = GetTLVData(csInfo,0x8B);
	if (csARRInfo.IsEmpty())
		return FALSE;
	csARRFID  = csARRInfo.Left(04);
	if (m_wndClassView->_IsDFItem(hItem))
		hParentItem = hItem;
	else
		hParentItem =   m_wndClassView->GetNextItem(hItem,TVGN_PARENT);



	if ((_CString2Int(csARRFID)&0xFF00)== 0x6F00)
	{

		do 
		{
			CString csFID = m_wndClassView->_GetItemFID(hParentItem);

			if ((!csFID.IsEmpty())&&
				((_CString2Int(csFID)&0xFF00)== 0x7F00))
				goto SelectARR;
			else if(!(m_wndClassView->_GetItemAID(hParentItem).IsEmpty()))
				goto SelectARR;


			hParentItem =   m_wndClassView->GetNextItem(hParentItem,TVGN_PARENT);
		} while ((hParentItem != NULL)&&(hParentItem != TVI_ROOT));

		goto SelectARR_FAILED;



	}
	else
	{
		hParentItem = m_wndClassView->_GetItem(_T("3F00"));
	}

SelectARR:

	if (bReadMode)
	{
		csTempFCI = _TestCaseSelectCurrentFile(hParentItem);
		if (_TestCaseSelectFile(csARRFID,csTempFCI))
		{
			csTempFCI        = GetTLVData(csTempFCI,0x62);
			csTempFCI        = GetTLVData(csTempFCI,0x82);
			csARRInfo        = _TestCaseSendCommand(_T("00B2")+csARRInfo.Mid(0x04,02)+_T("04")+csTempFCI.Mid(0x06,02));
			csARRInformation = csARRInfo.Left(csARRInfo.GetLength()-4);
			return TRUE;
		}
	}
	else
	{
		do 
		{
			csFIDPath   = m_wndClassView->_GetItemPath(hParentItem)+ csARRFID+_T("||");
			csInfo = SelectInRam(csFIDPath);
			if (!csInfo.IsEmpty())
			{
				if (!_FindFistNodeCurrnent(csInfo,_T("FCI"),&csFCI,&csFileData))
					return FALSE;
				if (!_FindFistNodeCurrnent(csInfo,_T("Datas"),&csFileData,NULL))
					return FALSE;
				iRecordLen  =  _CString2Int (GetTLVData( GetTLVData(csFCI,0x62) ,0x82).Mid(04,04))*2;
				iOffset     =  _CString2Int(csARRInfo.Mid(04,02))*iRecordLen - iRecordLen;
				csFileData  =  csFileData.Mid(iOffset,iRecordLen);
				csARRInformation = csFileData;
				return TRUE;
			}
			if (csFileData.IsEmpty())
				hParentItem =   m_wndClassView->GetNextItem(hParentItem,TVGN_PARENT);
			else
				hParentItem = NULL;
		} while (hParentItem != NULL);



	}



	//do 
	//{
	//	if (bReadMode)
	//	{
	//		csTempFCI = _TestCaseSelectCurrentFile(hParentItem);
	//		if (_TestCaseSelectFile(csARRFID,csTempFCI))
	//		{
	//			csTempFCI        = GetTLVData(csTempFCI,0x62);
	//			csTempFCI        = GetTLVData(csTempFCI,0x82);
	//			csARRInfo        = _TestCaseSendCommand(_T("00B2")+csARRInfo.Mid(0x04,02)+_T("04")+csTempFCI.Mid(0x06,02));
	//			csARRInformation = csARRInfo;
	//			return TRUE;
	//		}
	//		else
	//			hParentItem =   m_wndClassView->GetNextItem(hParentItem,TVGN_PARENT);
	//	}
	//	else
	//	{
	//		csFIDPath   = m_wndClassView->_GetItemPath(hParentItem)+ csARRFID+_T("||");
	//		csInfo = SelectInRam(csFIDPath);
	//		if (!csInfo.IsEmpty())
	//		{
	//			if (!_FindFistNodeCurrnent(csInfo,_T("FCI"),&csFCI,&csFileData))
	//				return FALSE;
	//			if (!_FindFistNodeCurrnent(csInfo,_T("Datas"),&csFileData,NULL))
	//				return FALSE;
	//			iRecordLen  =  _CString2Int (GetTLVData( GetTLVData(csFCI,0x62) ,0x82).Mid(04,04))*2;
	//			iOffset     =  _CString2Int(csARRInfo.Mid(04,02))*iRecordLen - iRecordLen;
	//			csFileData  =  csFileData.Mid(iOffset,iRecordLen);
	//			csARRInformation = csFileData;
	//			return TRUE;
	//		}
	//		if (csFileData.IsEmpty())
	//			hParentItem =   m_wndClassView->GetNextItem(hParentItem,TVGN_PARENT);
	//		else
	//			hParentItem = NULL;
	//	}	
	//} while (hParentItem != NULL);

SelectARR_FAILED:
	return FALSE;
}

//  双击选中Item, 选中文件并且 使用多线程读取文件! 并且将输入放入文件内容!
int CMainFrame::DClickClassTreeView( HTREEITEM hSelectItem, BOOL bShow /*= FALSE*/)
{

	CString csFCI,csFileData;
	int iRet  = FALSE;
	//选择文件失败则直接无法读取文件
	if (ClickClassTreeView(hSelectItem,&csFCI))
	{
		if (!m_wndClassView->_IsDFItem(hSelectItem))
			if (bReadMode)
				iRet = ReadItemInCardAndPutToDisplay(csFCI,&csFileData);
			else
				iRet = ReadItemInCardAndPutToDisplayInFile(hSelectItem,&csFileData);
		ExplainFile(hSelectItem);
	}
	else
		iRet = FALSE;

	if ((bShow)&&(iRet!=FALSE))
	{

		m_dlgChangeFile.Initialize_Control();

		if (bIsUICC)
			m_dlgChangeFile.SetFileData(csFCI,csFileData);
		else
			m_dlgChangeFile._SetFileData(csFCI,csFileData);
		m_dlgChangeFile.ShowWindow(SW_SHOW);

	}
	return iRet;
}
// 读取所选Item指示的卡片中文件,并且显示到FileData 中! // 此处先使用当前线程
int CMainFrame::ReadItemInCardAndPutToDisplay( CString csFCI,CString* csOutPutFData )
{
	CString csFileData =_TestCaseReadCurrentFileData(csFCI,bIsUICC);
	if (!csFileData.IsEmpty())
		m_wndProperties->SetFile2PropList(csFileData);
	else
		return FALSE;

	if (csOutPutFData!= NULL)
		*csOutPutFData = csFileData;


	return TRUE;
}

//************************************
// Method:    SelectItemInFile
// FullName:  CMainFrame::SelectItemInFile
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: HTREEITEM hSelectItem
// Parameter: CString * csOutPutFCI
//************************************
int CMainFrame::SelectItemInFile( HTREEITEM hSelectItem, CString* csOutPutFCI/*= NULL*/ )
{
	CString csPath,csInfor,csFCI,csFileData;

	csPath = m_wndClassView->_GetItemPath(hSelectItem);

	csInfor = SelectInRam(csPath);

	if (csInfor.IsEmpty())
		return FALSE;

	 _FindFistNodeCurrnent(csInfor,"FCI",&csFCI,&csFileData);
	if (csOutPutFCI!= NULL)
		* csOutPutFCI = csFCI;

	
	return TRUE;

}
int CMainFrame::ReadItemInCardAndPutToDisplayInFile( HTREEITEM hItem,CString* csOutPutData/*=NULL*/ )
{
	CString csInfor,csFileData,csFCI;
	
	csInfor =  SelectInRam(hItem);
	_FindFistNodeCurrnent(csInfor,"FCI",&csFCI,&csFileData);
	
	if (!m_wndClassView->_IsDFItem(hItem))
		 _FindFistNodeCurrnent(csInfor,"Datas",&csFileData,NULL);
	
	if (!csFileData.IsEmpty())
		m_wndProperties->SetFile2PropList(csFileData);
	
	ExplainFile(hItem);
	
	if (csOutPutData != NULL)
		*csOutPutData = csFileData;

	return TRUE;
}
void CMainFrame::OnSizing(UINT fwSide, LPRECT pRect)
{
	CFrameWndEx::OnSizing(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码
}
void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWndEx::OnSize(nType, cx, cy);





	
	// TODO: 在此处添加消息处理程序代码
}
int CMainFrame ::GetProtectedSetting(int iSettingCode,int& iSettingValue)
{
	BOOL bRet = TRUE;
	iSettingValue = 0;
	switch(iSettingCode)
	{
	case Def_GetFileSystem:      iSettingValue        = (int)bGetFileSystem&1;       break;
	case Def_GetApplication:     iSettingValue        = (int)bGetAppList&1;       break;
	case Def_GetPinStatus:       iSettingValue        = (int)bGetPinSta&1;          break;
	case Def_NotVerify:          iSettingValue        = (int)bNotVerify&1;       break;
	case Def_APDUExplain:        iSettingValue        = (int)bAPDUExplain&1;       break;
	case Def_OTAExplain :        iSettingValue        = (int)bOTAExplain&1;       break;
	case Def_OTADecrypt:         iSettingValue        = (int)bOTADecrypt&1;       break;
	case Def_ModulePathExist:    iSettingValue        = (int)m_wndClassView->bModuleExist&1;       break;
	case Def_GetARR       :      iSettingValue        = (int)bGetARR&1;       break;
	default:iSettingValue        = -1;
		    bRet                 = FALSE;              break;
	}
	return bRet ;
}
int CMainFrame ::SetProtectedSetting(int iSettingCode,int iSettingValue)
{


	BOOL bRet = TRUE;
	switch(iSettingCode)
	{
	case Def_GetFileSystem:    bGetFileSystem    = (bool)(iSettingValue&true);break;
	case Def_GetApplication:   bGetAppList       = (bool)(iSettingValue&true);break;
	case Def_GetPinStatus:     bGetPinSta        = (bool)(iSettingValue&true);break;
	case Def_NotVerify:        bNotVerify        = (bool)(iSettingValue&true);break;
	case Def_APDUExplain:      bAPDUExplain      = (bool)(iSettingValue&true);
		SetExplainLevel(bOTADecrypt*Def_DECINFOMATION|bOTAExplain*Def_OTAINFOMATION|bAPDUExplain*Def_APDUINFOMATION|Def_APDUBASICINFOMATION);
		break;
	case Def_OTAExplain:        bOTAExplain      = (bool)(iSettingValue&true);
		SetExplainLevel(bOTADecrypt*Def_DECINFOMATION|bOTAExplain*Def_OTAINFOMATION|bAPDUExplain*Def_APDUINFOMATION|Def_APDUBASICINFOMATION);
		break;
	case Def_OTADecrypt:        bOTADecrypt      = (bool)(iSettingValue&true);
		SetExplainLevel(bOTADecrypt*Def_DECINFOMATION|bOTAExplain*Def_OTAINFOMATION|bAPDUExplain*Def_APDUINFOMATION|Def_APDUBASICINFOMATION);
		break;
	case Def_ModulePathExist:  m_wndClassView->bModuleExist =(bool)(iSettingValue&true);       break;
	case Def_GetARR:           bGetARR                      =(bool)(iSettingValue&true);    break; 
	default:bRet = FALSE; break;
	}
	return bRet ;
}
int CMainFrame ::GetProtectedSetting(int iSettingCode,CString& csSettingValue)
{
	BOOL bRet = TRUE;
	switch(iSettingCode)
	{
	case Def_KeySettingPath:      csSettingValue        = m_wndKeySetting.csSettingName;       break;
	case Def_ModulePath     :     csSettingValue        = m_wndClassView->csModulePath;        break;
	default:csSettingValue.Empty();
		bRet                 = FALSE;              break;
	}
	return bRet ;
}
int CMainFrame ::SetProtectedSetting(int iSettingCode,CString csSettingValue)
{


	BOOL bRet = TRUE;
	switch(iSettingCode)
	{
	case Def_KeySettingPath:    m_wndKeySetting.csSettingName    = csSettingValue;break;
	case Def_ModulePath:        m_wndClassView->csModulePath      = csSettingValue;break;
	default:bRet = FALSE; break;

	}
	return bRet ;
}


//************************************
// Method:    GetAIDFromApplicationList
// FullName:  CMainFrame::GetAIDFromApplicationList
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: CString & csAID
// Parameter: UINT uiAIDNumber 
// 获取应用列表中的AID 成功返回TRUE, 失败返回FALSE
//************************************
int CMainFrame::GetAIDFromApplicationList( CString&csAID,UINT uiAIDNumber /*= 1*/ )
{
	int iRet = FALSE;
	int iSum = _GetApplacationSum();
	UINT uiNumber = 0;
	for (int i = 0 ; i < iSum ; i++)
	{
		if ( _GetApplacation(i,csAID) == 1)
		{
			uiNumber += 1;
			if (uiAIDNumber = uiNumber)
				return TRUE;
		}		
	}


	csAID.Empty();
	return FALSE;
}
//************************************
// Method:    GetPINFromKeySetting
// FullName:  CMainFrame::GetPINFromKeySetting
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: CString & csPIN
// Parameter: UINT uiPINCode (See KeySetting ::GetPIN)
//************************************
int CMainFrame::GetPINFromKeySetting(CString &csPIN,UINT uiPINCode)
{

	csPIN = m_wndKeySetting.GetPIN(uiPINCode);
	if (!csPIN.IsEmpty())
		return TRUE;

	csPIN.Empty();
	return FALSE;

}
int CMainFrame::GetLocalInformationFromKeySetting(CString& csLocalInformation,int iCode)
{
	csLocalInformation = m_wndKeySetting.GetLocalInformation(iCode);
	if (csLocalInformation.IsEmpty())
		return FALSE;
	else
		return TRUE;


}

void CMainFrame::OnVerifypinButton(UINT iID)
{
	bool bRet ; 
	switch(iID)
	{
	case ID_VerifyPin01_Button:bRet  = _TestCaseVerify(1,true);break;
	case ID_VerifyPin81_Button:bRet  = _TestCaseVerify(0x81,true);break;
	case ID_VerifyPin0A_Button:bRet  = _TestCaseVerify(0x0A,true);break;
	case ID_DisablePin01_Button:bRet = _TestCaseEnablePin1(false);break;
	case ID_EnablePin01_Button:bRet  = _TestCaseEnablePin1(true);break;
	case ID_ChangePin01_Button:bRet  = _TestCaseChangePin(1);break;
	case ID_ChangePin81_Button:bRet  = _TestCaseChangePin(0x81);break;
	case ID_UnblockPin01_Button:bRet  = _TestCaseUnblockPin(1);break;
	case ID_UnblockPin81_Button:bRet  = _TestCaseUnblockPin(0x81);break;


	default:break;
	}
	
	if (bRet)
		MessageBox(_T("Pin 操作成功或者取消")) ;
	else
		MessageBox(_T("Pin 操作失败")) ;
	
}



void CMainFrame::NewExportCSVThread()
{
	DWORD code;

	if (bReadMode)
	{
		if (!ConfirmCardStatue())
			return;
	}
	GetExitCodeThread(hThread,&code);      
	if (code != STILL_ACTIVE)
	{
		hThread  = CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE)ExportCSVThread,NULL, 0, NULL);
	}
	else
		ResumeThread(hThread);
	iThread = Def_Thread_ExportCSV;
	return ;
}
int CMainFrame::ExportCSVThread()
{
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CurMainFrm-> ExportCSV(); 
	iThread  = Def_Thread_Free ;
	return TRUE;
}
BOOL CMainFrame::ExportCSV()
{
	CString csFileName;
	CString csFileData;
	CStdioFile CSFFile;
	CFileDialog CFDataFile(FALSE,_T("(*.CSV)|*.CSV"),_T("Profile"),4|2,_T("(*.CSV)|*.CSV||"));


	if ( CFDataFile.DoModal() == IDOK)
	{
		csFileName = CFDataFile.GetPathName();
		

		if (CSFFile.Open(csFileName,CFile::modeCreate|CFile::modeWrite))
		{
			

			ExportString(CSFFile,m_wndClassView->GetRootItem());
			//CSFFile.WriteString(csFileData);
			CSFFile.Close();
			MessageBox(_T("保存完成"));
		}
		else
			MessageBox(_T("保存失败"));

	}

	return TRUE;
}

void CMainFrame::OnExportExcelButton()
{
	// TODO: 在此添加命令处理程序代码
	NewExportCSVThread();
	NewSetStatusThread();
}

BOOL CMainFrame::ExportString( CStdioFile& CSFFile,HTREEITEM hItem)
{


	HTREEITEM hChildItem;
	CString csFCI;
	CString csInfor;
	if (hItem == m_wndClassView->GetRootItem())
	{
		//获取总数
		iFileNum = m_wndClassView->StatisticFileNumber();
		iCurNum  = 0;
		CSFFile.WriteString(_T("FID,描述,路径,类别,结构,文件大小,记录长度,记录条数,短文件标示,Read权限,Write权限,Increat权限,Deactive权限,Active权限,ARR,文件内容,\n"));
		CSFFile.WriteString(_T("3F00\n"));
	}


	hChildItem = m_wndClassView->GetChildItem(hItem);

	while(hChildItem)
	{

		if (iThread == Def_Thread_Ending)
			return FALSE;

		if (_GenerateFileInformation(hChildItem, csFCI,csInfor))
		{
			CSFFile.WriteString(csInfor);
			if (m_wndClassView->_IsDFItem(hChildItem))
				ExportString(CSFFile,hChildItem);
		}

		iCurNum ++;
		hChildItem= m_wndClassView->GetNextItem(hChildItem,TVGN_NEXT);

		SetProgressCounter(iFileNum,iCurNum);
	}
//	return iAbsent;

	return TRUE;
}

BOOL CMainFrame::_GenerateFileInformation( HTREEITEM hItem, CString csFCI,CString&csInfo)
{
	CString csFID;
	CString csDescription;
	CString csPath;
	CString csType;
	CString csStructure;
	CString csSize;
	CString csRecordNumber;
	CString csRecordLength;
	CString csSFI;
	CString csARRInfo;
	CString csRead;
	CString csUpdate;
	CString csIncreat;
	CString csActive;
	CString csDeactive;
	CString csFileData;
	int iOther,itemp;
	int iRecordLength;

	csInfo.Empty();
	csPath = m_wndClassView->_GetItemPath( m_wndClassView->GetNextItem(hItem,TVGN_PARENT));

	//去除3F00||
	if (csPath.GetLength()>6)
		csPath = csPath.Mid(6);
	//去除结尾||
	csPath = csPath.Left(csPath.GetLength()-2);


	csFID  = m_wndClassView->_GetItemFID  (hItem);
	if (csFID.IsEmpty())
		csFID = m_wndClassView->_GetItemAID(hItem);
	csDescription  = m_wndClassView->_GetItemDescription(hItem);
	if (!_SelectItem(hItem,&csFCI))
		return FALSE;
	//文件结构
	itemp = _GetFileStructure(csFCI);
	if (!_TranslateFileStructure(itemp,csStructure))
		return FALSE;;

	if (itemp>1)
	{
		iRecordLength = _GetRecordLength(csFCI);
		csRecordLength.Format("%d",iRecordLength);
		csRecordNumber.Format("%d",_GetRecordNumber(csFCI));
	}
	else
	{
		csRecordLength.Empty();
		csRecordNumber.Empty();
	}
	csSize.Format("%d",_GetFileSize(csFCI));

	itemp = _GetFileSFI(csFCI);

	if (itemp>0)
		csSFI.Format("%d",itemp);
	else
		csSFI.Empty();


	if (m_wndClassView->_IsDFItem(hItem))
	{
		csInfo = csInfo+csFID+_T(",");
		csInfo = csInfo+csDescription+_T(",");
		csInfo = csInfo+csPath+_T(",");
		csType = _T("MF/DF/ADF");
		csInfo = csInfo+csType+_T(",");
		csInfo = csInfo + _T(",\n");

	}

	else
	{
		csInfo = csInfo+csFID+_T(",");
		csInfo = csInfo+csDescription+_T(",");
		csInfo = csInfo+csPath+_T(",");
		csType = _T("EF");
		csInfo = csInfo+csType+_T(",");
		csInfo = csInfo+csStructure+_T(",");
		csInfo = csInfo+csSize+_T(",");
		csInfo = csInfo+csRecordLength+_T(",");
		csInfo = csInfo+csRecordNumber+_T(",");
		csInfo = csInfo+csSFI+_T(",");

		csRead.Empty();
		csUpdate.Empty();
		csIncreat.Empty();
		csDeactive.Empty();
		csActive.Empty();
		if (_GetARRInformation(csFCI,hItem,csARRInfo) == TRUE)
		{
			_GetACFromARR(0x1,csARRInfo,csRead,&iOther);
			_GetACFromARR(0x2,csARRInfo,csUpdate,&iOther);
			_GetACFromARR(0x32,csARRInfo,csIncreat,&iOther,true);
			_GetACFromARR(0x8,csARRInfo,csDeactive,&iOther);
			_GetACFromARR(0x10,csARRInfo,csActive,&iOther);
		}
		csInfo = csInfo+csRead+_T(",");
		csInfo = csInfo+csUpdate+_T(",");
		csInfo = csInfo+csIncreat+_T(",");
		csInfo = csInfo+csDeactive+_T(",");
		csInfo = csInfo+csActive+_T(",");

		csARRInfo = GetTLVData(csFCI,0x62);
		if (!csARRInfo.IsEmpty())
		{
			csARRInfo = GetTLVData(csARRInfo,0x8B);
		}
			
		csInfo = csInfo+csARRInfo+_T(",");
		if (bReadMode)
		{
			_SelectItem(hItem,&csFCI);

			if (bIsUICC)
				csFileData = _TestCaseReadCurrentFileData_UICC(csFCI);
			else
				csFileData = _TestCaseReadCurrentFileData_GSM(csFCI);
		}
		else
		{
			csFileData.Empty();
			csDescription =  SelectInRam(hItem);
			_FindFistNodeCurrnent(csDescription,"Datas",&csFileData,NULL);
		}
		if (!csRecordLength.IsEmpty())
		{
			//此处如果为Record 数据增加换行
			_AppendSign(csFileData,_T("\n"),iRecordLength);
		}
		//使用\r来迫使不被识别成数字
		csFileData = _T("\"")+csFileData+ _T("\r\"");
		csInfo = csInfo+csFileData+_T(",\n");

	}

	return TRUE;
}
void CMainFrame::OnImportExcelButton()
{
	
	CString csFileName;
	CString csFileData;
	CStdioFile CSFFile;
	CFileDialog CFDataFile(TRUE,_T("(*.CSV)|*.CSV"),_T("Profile"),4|2,_T("(*.CSV)|*.CSV||"));
	CString csTemp;

	if ( CFDataFile.DoModal() == IDOK)
	{
		csFileName = CFDataFile.GetPathName();


		if (CSFFile.Open(csFileName,CFile::modeRead))
		{
			//读取文件头
			CSFFile.ReadString(csTemp);
			//读取3F00
			CSFFile.ReadString(csTemp);
			m_wndClassView->DeleteAllItems();
			m_wndClassView->Insert_DF(0x3F00,_T("MF"));


			while(CSFFile.GetPosition() < CSFFile.GetLength())
			{
				if (!ImportNextRecrod(CSFFile))
				{
					if (MessageBox(_T("导入中出现错误，是否继续"),_T("Warning"),MB_YESNO) != IDOK)
					{
						CSFFile.Close();
						return ;
					}
					
				}
			}
			


			//ExportString(CSFFile,m_wndClassView->GetRootItem());
			////CSFFile.WriteString(csFileData);
			//CSFFile.Close();
			//MessageBox(_T("保存完成"));
		}
	//	else
		MessageBox(_T("导入完成"));
		CSFFile.Close();
		return ;

	}


}
BOOL CMainFrame::ImportNextRecrod(CStdioFile& CSFFile)
{
	HTREEITEM hPItem;
	CString csRecord,csRecordTemp;
	//双引号会使得数据换行;
	int iTemp;
	CString csFID,csName,csRoute,csType,csStructure;

	iTemp = 0;
	csRecord.Empty();
	do 
	{
		if (!CSFFile.ReadString(csRecordTemp))
			return FALSE;



		
		iTemp +=  _GetExistNumber(csRecordTemp,_T("\""));
		iTemp -=  _GetExistNumber(csRecordTemp,_T("\\\""));

		csRecord += csRecordTemp;

	} while ( (iTemp%2)!= 0);


	if (!_ImportString(csRecord,csFID,csName, csRoute,csType,csStructure))
		return FALSE;


	hPItem = m_wndClassView->_GetItem(csRoute);
	if (hPItem == NULL)
		return FALSE;

	if (csType.Compare(_T("EF")) == 0)
		m_wndClassView->Insert_EF(_CString2Int(csFID),csName,NULL,hPItem);


	if (csType.Compare(_T("MF/DF/ADF")) == 0)
	{
		if (csFID.GetLength()>10)
			m_wndClassView->Insert_ADF(csFID,csName,NULL,hPItem);
		else if(csFID.GetLength() == 4)
			m_wndClassView->Insert_DF(_CString2Int(csFID),csName,NULL,hPItem);
	}

	return TRUE;

}
BOOL CMainFrame::ImportNextDFRecrod(CStdioFile& CSFFile)
{
	HTREEITEM hPItem;
	CString csRecord;
	CString csFID,csName,csRoute,csType,csStructure;
	if (!CSFFile.ReadString(csRecord))
		return FALSE;
	if (!_ImportString(csRecord,csFID,csName, csRoute,csType,csStructure))
		return FALSE;


	hPItem = m_wndClassView->_GetItem(csRoute);
	if (hPItem == NULL)
		return FALSE;
	if (csType.Compare(_T("MF/DF/ADF")) == 0)
	{
		if (csFID.GetLength()>10)
			m_wndClassView->Insert_ADF(csFID,csName,NULL,hPItem);
		else if(csFID.GetLength() == 4)
			m_wndClassView->Insert_DF(_CString2Int(csFID),csName,NULL,hPItem);
	}

	return TRUE;

}
BOOL CMainFrame::ImportNextEFRecrod(CStdioFile& CSFFile)
{
	HTREEITEM hPItem;
	CString csRecord;
	CString csFID,csName,csRoute,csType,csStructure;
	if (!CSFFile.ReadString(csRecord))
		return FALSE;
	if (!_ImportString(csRecord,csFID,csName, csRoute,csType,csStructure))
		return FALSE;


	hPItem = m_wndClassView->_GetItem(csRoute);
	if (hPItem == NULL)
		return FALSE;

	if (csType.Compare(_T("EF")) == 0)
		m_wndClassView->Insert_EF(_CString2Int(csFID),csName,NULL,hPItem);



	return TRUE;

}
BOOL CMainFrame::_ImportString(CString csString,CString& csFID,CString& csName, CString&csRoute, 
	                           CString& csType,CString& csStructure, CString* csSize, 
	                           CString* csRecLen,CString* csRecNum, CString* csRead, 
	                           CString* csWrite , CString* csIncreat, CString* csDeactive,
	                           CString* csActive,CString* csContent)
{


	if (_GetCSVDataSum(csString)< 5)
		return FALSE;
	
	if (_GetCSVData(csString,1,csFID)<0)
		return FALSE;
	if (_GetCSVData(csString,2,csName)<0)
		return FALSE;
	if (_GetCSVData(csString,3,csRoute)<0)
		return FALSE;
	if (_GetCSVData(csString,4,csType)<0)
		return FALSE;
	if (_GetCSVData(csString,5,csStructure)<0)
		return FALSE;
	 if (csSize != NULL)
		  _GetCSVData(csString,6,*csSize);
			
	 if (csRecLen != NULL)
		  _GetCSVData(csString,7,*csRecLen);
			
	 if (csRecNum != NULL)
		 _GetCSVData(csString,8,*csRecNum);
			
	 if (csRead != NULL)
		 _GetCSVData(csString,9,*csRead);

	 if (csWrite != NULL)
		 _GetCSVData(csString,10,*csWrite);

	 if (csIncreat != NULL)
		 _GetCSVData(csString,11,*csIncreat);

	 if (csDeactive != NULL)
		 _GetCSVData(csString,12,*csDeactive);

	 if (csActive != NULL)
		 _GetCSVData(csString,13,*csActive);

	 if (csContent != NULL)
		 _GetCSVData(csString,14,*csContent);
	 return TRUE;

}



void CMainFrame::OnExplainButton()
{
	CExpDialog cNewExpDialog;
	cNewExpDialog.DoModal();
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnDestroy()
{
	CFrameWndEx::OnDestroy();
}
void CMainFrame::OnKillFocus(CWnd* pNewWnd)
{
	CFrameWndEx::OnKillFocus(pNewWnd);

}
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	CFrameWndEx::OnSetFocus(pOldWnd);

}
void CMainFrame::OnGeflashdataButton()
{
	
	// TODO: 在此添加命令处理程序代码
	NewGetFlashDataThread();
	NewSetStatusThread();
}
void CMainFrame::OnEraseflashButton()
{

	if (!ConfirmCardStatue())
		return;

	if (_TestCaseSendCommand(_T("F0F3000000")) == _T("9000"))
		MessageBox(_T("擦除完成！"));
	else
		MessageBox(_T("擦除失败！"));
}
void CMainFrame::OnReformatflashButton()
{

	CString csFilePath,csFileData;
	CFileDialog CFDataFile(TRUE,_T("*.data|.data"),NULL,4|1,_T("(*.data)|*.data||"));
	CStdioFile CSFFile;
	BOOL bRet;
	CString csFlash,csTemp;
	csFlash.Empty();

	if ( CFDataFile.DoModal() == IDOK)

	{
		csFilePath = CFDataFile.GetPathName();

		if (CSFFile.Open(csFilePath,CFile::modeRead))
		{
			do 
			{
				bRet = CSFFile.ReadString(csTemp);
				csFlash += csTemp;
			} while (bRet);

			CSFFile.Close();
		}
		_DeleteEnterSpace(csFlash);
		m_wndGetFlash.ResetOffset();
		m_wndGetFlash.DisplayFlashData(csFlash);
	}


}


//************************************
// Method:    iGetConvertDataTag
// FullName:  iGetConvertDataTag
// Access:    public 
// Returns:   int 0 注释; 1 纯数据；2 APDU HEAD;3 APDU DATA;4 APDU SW;
//                5 ATR 6 PPS;0xF 未知
// Qualifier:
// Parameter: CString String
//************************************
int iGetConvertDataTag(CString csInput,CString&csOutput)
{
	CString csTag;
	int iTagLen;

	csOutput.Empty();
	if (csInput.Find("//")>=0)
		return 0;

	iTagLen = csInput.Find(":");
	if (iTagLen < 0)
	{
		csOutput = csInput;
		return 1;
	}

    
	csTag    = csInput.Left(iTagLen);
	csOutput = csInput.Mid(iTagLen+1);

	if (csTag.Compare("APDU") == 0)
		return 2;
	else if(csTag.Compare("DATA") == 0)
		return 3;
	else if(csTag.Compare("SW") == 0)
		return 4;
	else if(csTag.Compare("ATR") == 0)
		return 5;
	else if(csTag.Compare("PPS") == 0)
		return 6;

	return 0xF;

}

int __ConvertData2APDU( CString csCurrent,CString* csAPDU )
{


	CString csConText;
	int iTag;
	int iRet = 0;
	iTag = iGetConvertDataTag(csCurrent,csConText);

	switch(iTag)
	{
	case 1: 	   
	case 2:
	case 3:
	case 4:
	case 5: *csAPDU = (*csAPDU) + csConText;break;
	case 6: *csAPDU = (*csAPDU) + csConText;
		    iRet = 0x10;       break;
	default:iRet = 0x10;	   break;
	}
	return iTag|iRet;
}

void CMainFrame::OnReconvertbutton()
{
  CString csFilePath,csFileData;
  CFileDialog CFDataFile(TRUE,_T("*.txt|.txt"),NULL,4|1,_T("(*.txt)|*.txt||"));
  CStdioFile CSFFile;
  CString csTemp;
//  csFlash.Empty();

  if ( CFDataFile.DoModal() == IDOK)

  {
	csFilePath = CFDataFile.GetPathName();

	if (CSFFile.Open(csFilePath,CFile::modeRead|CFile::typeBinary))
	{
	  ULONGLONG lSize = CSFFile.GetLength();
	  WORD wType;

	  CSFFile.SeekToBegin();
	  CSFFile.Read(&wType,2);
	  WCHAR* wbuff; 

	  wbuff = new WCHAR[(UINT)lSize];

	  CSFFile.Read(wbuff,(UINT)lSize-2);

	  csTemp = wbuff;

	  delete wbuff;
	  int lOffset = 0;
	  int iCurrent= 0;
	  int iTYPE;
	  int iPTYPE = 0;
	  
	  CString csCurrent, csAPDU;
	  CStringArray csOutput;

	
	  do 
	  {
		iCurrent = csTemp.Find(_T("\r\n"),lOffset);


		if (iCurrent > 0)
		{
		  csCurrent = csTemp.Mid(lOffset,iCurrent - lOffset);
		  lOffset = iCurrent +2;
		}
		else
		   csCurrent = csTemp.Mid(lOffset);

		iTYPE = __ConvertData2APDU(csCurrent,&csAPDU);

		if ((iTYPE&0x10)!= 0)
		{
			_DeleteEnterSpace(csAPDU);

			if (!csAPDU.IsEmpty())
				m_wndGetFlash.__DisplayFlashData(csAPDU);
			csAPDU.Empty();
		}
		else if (iPTYPE != 0) iPTYPE = iTYPE;

	
	
		
	  } while (iCurrent > 0);

	  CSFFile.Close();
	}
	/*_DeleteEnterSpace(csFlash);
	m_wndGetFlash.ResetOffset();
	m_wndGetFlash.DisplayFlashData(csFlash);*/
  }
}



BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	//bool bTranslate = false;
	//if (pMsg->message == WM_KEYDOWN)
	//{

	//	if (::GetKeyState(VK_SHIFT))
	//	{
	//		bTranslate = true;
	//		switch(pMsg->wParam)
	//		{
	//		case 'A': OnSendcommandButton();break;
	//		case 'B': OnEndprogressButton();break;
	//		case 'C': OnConnectbutton()    ;break;
	//		case 'D': OnDisconnectbutton() ;break;
	//		default : bTranslate = false   ;break;
	//		}
	//	}

	//}
	//if (bTranslate)
	//	return TRUE;


	if (m_hAccel)
	{
		if(::TranslateAccelerator(m_hWnd,m_hAccel,pMsg))
			return (TRUE);
	}

	return CFrameWndEx::PreTranslateMessage(pMsg);
}
CSIMToolkit* CMainFrame::GetSIMToolKit()
{
	return &m_wndSIMToolkit;
}
COutputWnd* CMainFrame::GetOutputWnd()
{
	return &m_wndOutput;
}
CChangeFile* CMainFrame::GetChangeFileDlg()
{
	return &m_dlgChangeFile;

}
void CMainFrame::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	/*int X = GetSystemMetrics(SM_CXMAXTRACK);
	int Y = GetSystemMetrics(SM_CYMAXTRACK);

	TRACE0(Int2CStringDecimal(X)+":");
	TRACE0(Int2CStringDecimal(Y)+"..");*/
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 
	//m_wndRibbonBar.OnDrawCaption();
	CFrameWndEx::OnPaint();
}






