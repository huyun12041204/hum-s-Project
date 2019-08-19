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

// CardManage.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "CardManage.h"
#include "MainFrm.h"

#include "CardManageDoc.h"
#include "LeftView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCardManageApp

BEGIN_MESSAGE_MAP(CCardManageApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CCardManageApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW,  &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CCardManageApp 构造

CCardManageApp::CCardManageApp()
{
	m_bHiColorIcons = TRUE;

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则:
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: 将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("CardManage.AppID.NoVersion"));


	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CCardManageApp 对象

CCardManageApp theApp;


// CCardManageApp 初始化

BOOL CCardManageApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	//CString csDate;
	//GetSysDate(csDate);
	//int iDate = _CString2IntDecimal(csDate);

	//if (iDate>20180820)
	//{
	//	return FALSE;
	//}

	CString csDate;
	GetSysDate(csDate);

	if (( _CString2IntDecimal(csDate)> 20191204)||( _CString2IntDecimal(csDate)< 20180825))
	{
		MessageBox(NULL,_T("请联系huyun12041204@hotmail.com"),NULL,MB_OK);
		return FALSE;
	}


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	 AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("Giesecke&Devrient"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)

	InstallFont();

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CCardManageDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CLeftView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// 启用“DDE 执行”
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand 之后发生
	// 启用拖/放
	m_pMainWnd->DragAcceptFiles();



	return TRUE;
}

int CCardManageApp::ExitInstance()
{
	//TODO: 处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CCardManageApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	CString csText;
	csText.Empty();
	csText += _T("CardManage，1.0 版\n\r");
	csText += _T("  保存卡片文件模板.\n\r");
	csText += _T("  获取文件内容.\n\r");
	csText += _T("  搜寻文件系统.\n\r");
	csText += _T("  读写文件系统（可以主动校验PIN）.\n\r");
	csText += _T("  发送APDU（包含断电模式）.\n\r");
	csText += _T("  常用文件解析.\n\r");
	csText += _T("  APDU解析.\n\r");
	csText += _T("  读取UST.\n\r");
	csText += _T("  读写号簿（支持3G号簿，但不包括扩展内容）.\n\r");
	csText += _T("  读写短信.\n\r");
	csText += _T("  STK模拟.\n\r");
	csText += _T("  文件系统导出CSV.\n\r");
	csText += _T("  转载板数据获取和擦除.\n\r");
	SetDlgItemText(IDC_Function_Dis,csText);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CCardManageApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CCardManageApp 自定义加载/保存方法

void CCardManageApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
}

void CCardManageApp::LoadCustomState()
{
	if (!LoadBuiltSetting())
	{
		return;
	}



	return ;
}

void CCardManageApp::SaveCustomState()
{
	if (!SaveCardConnectSetting())
	{
		return;
	}
	if (SaveStartSetting())
	{
	}
	
	return ;

}






// 安装字体
int CCardManageApp::InstallFont(void)
{
	LOGFONT lf;   
	afxGlobalData.fontRegular.GetLogFont(&lf);   
	afxGlobalData.fontRegular.DeleteObject();   
	lf.lfHeight = -12;   
	lstrcpy(lf.lfFaceName, _T("宋体"));   
	afxGlobalData.fontRegular.CreateFontIndirect(&lf);  
	//设置加粗的字体 
	afxGlobalData.fontBold.GetLogFont(&lf);   
	afxGlobalData.fontBold.DeleteObject();   
	lf.lfHeight = -12;   
	lstrcpy(lf.lfFaceName, _T("宋体"));   
	afxGlobalData.fontBold.CreateFontIndirect(&lf);
	afxGlobalData.fontTooltip.GetLogFont(&lf);   
	afxGlobalData.fontTooltip.DeleteObject();   
	lf.lfHeight = -12;   
	lstrcpy(lf.lfFaceName, _T("宋体"));   
	afxGlobalData.fontTooltip.CreateFontIndirect(&lf);
	return 0;
}


CString CCardManageApp::GetSettingName(int iSettingCode)
{
	CString csResult;
	switch(iSettingCode)
	{
	case Def_GetFileSystem:       csResult        = _T("GetFileSystem");       break;
	case Def_GetApplication:      csResult        = _T("GetApplication");       break;
	case Def_GetPinStatus:        csResult        = _T("GetPinStatus");           break;
	case Def_NotVerify:           csResult        = _T("NotVerify");          break;
	case Def_GetARR:              csResult        = _T("GetARR");          break;
	case Def_KeySettingPath:      csResult        = _T("KeySettingPath");          break;
	case Def_ModulePath:          csResult        = _T("ModulePath");          break;
	case Def_ModulePathExist:     csResult        = _T("ModulePathExist");          break;
	case Def_APDUExplain:         csResult        = _T("APDUExpain");          break;
	case Def_OTAExplain:          csResult        = _T("OTAExpain");          break;
	case Def_OTADecrypt:          csResult        = _T("OTADecrypt");          break;
	default:                      csResult        = _T("DEFAULT");            break;
	}
	return csResult;

}


int CCardManageApp::LoadBuiltSetting()
{
	CString csPath,csName; 
	int iSetting ;

	for (int i = 1 ; i <= Def_OTADecrypt ; i ++)
	{
		if (i>= Def_APDUExplain)
			csPath = _T("Settings\\OutputDisplay");
		else
			csPath = _T("Settings\\CardConnect");
		csName =  GetSettingName(i);
		iSetting = 0;	
		((CMainFrame*) GetMainWnd())->SetProtectedSetting(i,GetProfileInt(csPath,csName,iSetting));
	
	}



	return TRUE;
}

int CCardManageApp::SaveCardConnectSetting()
{
	CString csPath,csName; 
	int iSetting = 0;

	for (int i = 1 ; i <= Def_OTADecrypt ; i ++)
	{
		if (i >= Def_APDUExplain)
			csPath = _T("Settings\\OutputDisplay");
		else
			csPath = _T("Settings\\CardConnect");
		csName = GetSettingName(i);
		iSetting = 0;
		if (!((CMainFrame*)  GetMainWnd())->GetProtectedSetting(i,iSetting))
		{
			return FALSE;
		}
		if (!WriteProfileInt(csPath,csName,iSetting))
		{
			//return FALSE;
		}
	}

	return TRUE;
}

int CCardManageApp::SaveStartSetting()
{
	CMainFrame* pMain = (CMainFrame*)GetMainWnd();
	CString csPath,csName,csSetting; 
	csPath = _T("Settings\\Start");
	csName = GetSettingName(Def_KeySettingPath);
	if (pMain->GetProtectedSetting(Def_KeySettingPath,csSetting))
	{
		WriteProfileString(csPath,csName,csSetting);
	}

	csName = GetSettingName(Def_ModulePath);
	if (pMain->GetProtectedSetting(Def_ModulePath,csSetting))
	{
		WriteProfileString(csPath,csName,csSetting);
	}

	int iRet;
	csName = GetSettingName(Def_ModulePathExist);
	if (pMain->GetProtectedSetting(Def_ModulePathExist,iRet))
		 WriteProfileInt(csPath,csName,iRet);


	return true;
}