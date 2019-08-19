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
#include "BitsAnalyser.h"
//#include "BitsAnalyserView.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//USB 相关变量
usb_dev_handle *dev ; /* the device handle */
char _send[BUF_SIZE + 4];
char _recv[Max_Size];
int  ConnectState ;
int  threadState  ;
UINT uiRecvLen = 0;
UINT uiPrinLen = 0;

UINT GetBits(LPVOID pParam) 
{ 
	int ret;
	while(threadState)
	{
		if(dev)
		{
			ret = usb_bulk_read(dev, EP_IN, _recv+uiRecvLen,BUF_SIZE, 5000);
			if (ret>0)
			{
					uiRecvLen += ret;
			}
			//Sleep(5);
		
		}
	}

	return  0 ; 
} 

UINT ViewBits(LPVOID pParam) 
{ 

//	int ret;
	UINT uiTEmp;
	while(threadState)
	{

		if (uiPrinLen < uiRecvLen)
		{

			CMainFrame* pFrame       = (CMainFrame*)AfxGetApp()->GetMainWnd();
			CBitsAnalyserView* pView =  (CBitsAnalyserView*)(pFrame->GetActiveView());

			uiTEmp = uiRecvLen-uiPrinLen;
			if (uiTEmp>256)
				uiTEmp = 256;

			Sleep(1);
			pView->PrintEdit(_recv+uiPrinLen,uiTEmp );
			pView->ViewAPDU ((BYTE*)_recv+uiPrinLen,uiTEmp );
			uiPrinLen += uiTEmp;
	
		
		}
		else
		 Sleep(1000);
		/*if(dev)
		{
		ret = usb_bulk_read(dev, EP_IN, _recv+uiRecvLen,BUF_SIZE, 5000);
		if (ret>0)
		{
		uiRecvLen += ret;
		}

		}*/
	}

	return 0;
}

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_WM_SETTINGCHANGE()
	ON_COMMAND(ID_Connect_BUTTON, &CMainFrame::OnConnectButton)
	ON_COMMAND(ID_Disconnect_BUTTON, &CMainFrame::OnDisconnectButton)
	ON_UPDATE_COMMAND_UI_RANGE(ID_Connect_BUTTON, ID_Disconnect_BUTTON, &CMainFrame::OnUpdateConnected)
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_VS_2008);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

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



	//自定义参数进行初始化
	__Init();
	return 0;
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
	if (!m_wndOutput.Create(strOutputWnd, this, CRect(0, 0, 100, 100), TRUE, ID_VIEW_OUTPUTWND, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_BOTTOM | CBRS_FLOAT_MULTI))
	{
		TRACE0("未能创建输出窗口\n");
		return FALSE; // 未能创建
	}

	SetDockingWindowIcons(theApp.m_bHiColorIcons);
	return TRUE;
}

void CMainFrame::SetDockingWindowIcons(BOOL bHiColorIcons)
{
	HICON hOutputBarIcon = (HICON) ::LoadImage(::AfxGetResourceHandle(), MAKEINTRESOURCE(bHiColorIcons ? IDI_OUTPUT_WND_HC : IDI_OUTPUT_WND), IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), 0);
	m_wndOutput.SetIcon(hOutputBarIcon, FALSE);

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
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
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
	}

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
}




void CMainFrame::__Init(void)
{
	GetBitThread = NULL;
	ViewBitThread= NULL;
	dev = NULL; /* the device handle */
	ConnectState = 0;
	threadState  = 1;
	uiRecvLen    = 0;
}
void CMainFrame::OnConnectButton()
{
	if(ConnectState == 0)
	{
		usb_init(); /* initialize the library */
		usb_find_busses(); /* find all busses */
		usb_find_devices(); /* find all connected devices */

		if (!(dev = Open_Dev()))
		{
			AfxMessageBox("connect fail!");
			return;
		}

		if (usb_set_configuration(dev, MY_CONFIG) < 0)
		{
			usb_close(dev);
			AfxMessageBox("set config fail!");
			return;
		}

		if (usb_claim_interface(dev, 0) < 0)
		{
			usb_close(dev);
			AfxMessageBox("set interface fail!");
			return;
		}

		ConnectState = 1;
		//GetDlgItem(IDC_ComConnect_Button)->SetWindowText("Disconnect");
	}
	else
	{
		if (dev)
		{
			usb_release_interface(dev, 0);
			usb_close(dev);
			dev = NULL;
		}

		ConnectState = 0;
	}
}


// //打开USB设备
usb_dev_handle * CMainFrame::Open_Dev(void)
{
	struct usb_bus *bus;
	struct usb_device *dev;
	for (bus = usb_get_busses(); bus; bus = bus->next)
	{
		for (dev = bus->devices; dev; dev = dev->next)
		{
			if (dev->descriptor.idVendor == MY_VID
				&& dev->descriptor.idProduct == MY_PID)
			{
				if (GetBitThread == NULL)
					GetBitThread = AfxBeginThread(GetBits, _T("GetBits")); 	
				if (ViewBitThread == NULL)
					ViewBitThread = AfxBeginThread(ViewBits, _T("ViewBits")); 	
				return usb_open(dev);
			}
		}
	}
	return NULL;
}

void CMainFrame::OnDisconnectButton()
{

	if (ConnectState == 1)
	{	if (dev)
		{
			usb_release_interface(dev, 0);
			usb_close(dev);
			dev = NULL;
		}
		ConnectState = 0;
	}
}

 void CMainFrame::OnUpdateConnected(CCmdUI* pCmdUI)
{

	//if (ConnectState)
	//{




	//}


	//// if ((iReaderStatus == Def_Terminal_Disconnected)&&
	//// (bReadMode == true))
	//if (iReaderStatus == Def_Terminal_Disconnected)
	//	pCmdUI->Enable(TRUE);
	//else
	//	pCmdUI->Enable(FALSE);

	switch(pCmdUI->m_nID)
	{
	case ID_Connect_BUTTON:     pCmdUI->Enable(!ConnectState);break;
	case ID_Disconnect_BUTTON:   pCmdUI->Enable(ConnectState);break;
	default:break;
	}

}