// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// CardManage.cpp : ����Ӧ�ó��������Ϊ��
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
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW,  &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
END_MESSAGE_MAP()


// CCardManageApp ����

CCardManageApp::CCardManageApp()
{
	m_bHiColorIcons = TRUE;

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���:
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO: ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("CardManage.AppID.NoVersion"));


	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CCardManageApp ����

CCardManageApp theApp;


// CCardManageApp ��ʼ��

BOOL CCardManageApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
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
		MessageBox(NULL,_T("����ϵhuyun12041204@hotmail.com"),NULL,MB_OK);
		return FALSE;
	}


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	 AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Giesecke&Devrient"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)

	InstallFont();

	InitContextMenuManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CCardManageDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CLeftView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// ���á�DDE ִ�С�
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);


	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand ֮����
	// ������/��
	m_pMainWnd->DragAcceptFiles();



	return TRUE;
}

int CCardManageApp::ExitInstance()
{
	//TODO: �����������ӵĸ�����Դ
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CCardManageApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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
	csText += _T("CardManage��1.0 ��\n\r");
	csText += _T("  ���濨Ƭ�ļ�ģ��.\n\r");
	csText += _T("  ��ȡ�ļ�����.\n\r");
	csText += _T("  ��Ѱ�ļ�ϵͳ.\n\r");
	csText += _T("  ��д�ļ�ϵͳ����������У��PIN��.\n\r");
	csText += _T("  ����APDU�������ϵ�ģʽ��.\n\r");
	csText += _T("  �����ļ�����.\n\r");
	csText += _T("  APDU����.\n\r");
	csText += _T("  ��ȡUST.\n\r");
	csText += _T("  ��д�Ų���֧��3G�Ų�������������չ���ݣ�.\n\r");
	csText += _T("  ��д����.\n\r");
	csText += _T("  STKģ��.\n\r");
	csText += _T("  �ļ�ϵͳ����CSV.\n\r");
	csText += _T("  ת�ذ����ݻ�ȡ�Ͳ���.\n\r");
	SetDlgItemText(IDC_Function_Dis,csText);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CCardManageApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CCardManageApp �Զ������/���淽��

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






// ��װ����
int CCardManageApp::InstallFont(void)
{
	LOGFONT lf;   
	afxGlobalData.fontRegular.GetLogFont(&lf);   
	afxGlobalData.fontRegular.DeleteObject();   
	lf.lfHeight = -12;   
	lstrcpy(lf.lfFaceName, _T("����"));   
	afxGlobalData.fontRegular.CreateFontIndirect(&lf);  
	//���üӴֵ����� 
	afxGlobalData.fontBold.GetLogFont(&lf);   
	afxGlobalData.fontBold.DeleteObject();   
	lf.lfHeight = -12;   
	lstrcpy(lf.lfFaceName, _T("����"));   
	afxGlobalData.fontBold.CreateFontIndirect(&lf);
	afxGlobalData.fontTooltip.GetLogFont(&lf);   
	afxGlobalData.fontTooltip.DeleteObject();   
	lf.lfHeight = -12;   
	lstrcpy(lf.lfFaceName, _T("����"));   
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