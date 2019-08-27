// KeySetting.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "CardInfomation.h"
#include "afxdialogex.h"
#include "..\AllUsedSource\ExpAPDU\ExpAPDU.h"
// CKeySetting 对话框

IMPLEMENT_DYNAMIC(CKeySetting, CDialogEx)

CKeySetting::CKeySetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CKeySetting::IDD, pParent)
	, csSettingName(_T(""))
{

}

CKeySetting::~CKeySetting()
{
}

void CKeySetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_Key_Tab,    m_KeyTab);
}


BEGIN_MESSAGE_MAP(CKeySetting, CDialogEx)
	ON_BN_CLICKED(IDOK, &CKeySetting::OnBnClickedOk)
	ON_NOTIFY(TCN_SELCHANGE, IDC_Key_Tab, &CKeySetting::OnTcnSelchangeKeyTab)
END_MESSAGE_MAP()


// CKeySetting 消息处理程序


void CKeySetting::OnBnClickedOk()
{
	//if (!csSettingName.IsEmpty())
	//	Save2File(csSettingName);

	SetData2Output();
	
	CDialogEx::OnOK();
}
void CKeySetting::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
bool CKeySetting::Initialize_Dialog(void)
{

	CRect rs;
	// TODO: 在此添加额外的初始化代码
	m_KeyTab.InsertItem(0, _T("PIN     "));
	m_KeyTab.InsertItem(1, _T("Milenage"));
	m_KeyTab.InsertItem(2, _T("CMCC Key"));
	m_KeyTab.InsertItem(3, _T("CUC Key"));
	m_KeyTab.InsertItem(4, _T("Local Informaiton"));

	m_CardKey .Create(IDD_Card_Key_Form, GetDlgItem(IDC_Key_Tab));
	m_Milenage.Create(IDD_Milenage_Form, GetDlgItem(IDC_Key_Tab));
	m_CMCCKey .Create(IDD_CMCC_Key_Form, GetDlgItem(IDC_Key_Tab));
	m_CUCKey  .Create(IDD_CUC_Key_Form , GetDlgItem(IDC_Key_Tab));
	m_Local   .Create(IDD_LocalInformation_Form, GetDlgItem(IDC_Key_Tab));
	m_KeyTab.GetClientRect(&rs);

	rs.top += 22;
	rs.bottom -= 2;
	rs.left += 1;
	rs.right -= 2;
	m_CardKey  .MoveWindow(&rs);
	m_Milenage .MoveWindow(&rs);
	m_Local    .MoveWindow(&rs);
	m_CMCCKey  .MoveWindow(&rs);
	m_CUCKey   .MoveWindow(&rs);
	m_CardKey  .ShowWindow(true);
	m_Milenage .ShowWindow(false);
	m_Local    .ShowWindow(false);
	m_CMCCKey .ShowWindow(false);
	m_CUCKey    .ShowWindow(false);
	   
	m_KeyTab   .SetCurSel(0);

	m_CardKey .Initialize_Form();
	m_Milenage.Initialize_Form();
	m_Local   .Initialize_Form();
	m_CMCCKey.Initialize_Form();
	m_CUCKey   .Initialize_Form();
	//m_KeyTab
	/*SetDlgItemText(IDC_PIN1_Edit,_T("31323334FFFFFFFF"));
	SetDlgItemText(IDC_PUK1_Edit,_T("31323334FFFFFFFF"));

	SetDlgItemText(IDC_PIN2_Edit,_T("3132333435363738"));
	SetDlgItemText(IDC_PUK2_Edit,_T("31323334FFFFFFFF"));

	SetDlgItemText(IDC_ADMCommand_Edit,_T("20000A08"));
	SetDlgItemText(IDC_ADM_Edit,_T("3132333435363738"));

	SetDlgItemText(IDC_PSCommand_Edit,_T("17000008"));
	SetDlgItemText(IDC_PS_Edit,_T("31323334FFFFFFFF"));

	SetDlgItemText(IDC_KI_Edit,_T("12345678123456781234567812345678"));
	SetDlgItemText(IDC_Opc_Edit,_T("12345678123456781234567812345678"));

	SetDlgItemText(IDC_R1_Edit,_T("20"));
	SetDlgItemText(IDC_R2_Edit,_T("00"));
	SetDlgItemText(IDC_R3_Edit,_T("20"));
	SetDlgItemText(IDC_R4_Edit,_T("40"));
	SetDlgItemText(IDC_R5_Edit,_T("60"));

	SetDlgItemText(IDC_C1_Edit,_T("00000000000000000000000000000000"));
	SetDlgItemText(IDC_C2_Edit,_T("00000000000000000000000000000001"));
	SetDlgItemText(IDC_C3_Edit,_T("00000000000000000000000000000002"));
	SetDlgItemText(IDC_C4_Edit,_T("00000000000000000000000000000004"));
	SetDlgItemText(IDC_C5_Edit,_T("00000000000000000000000000000008"));*/

	csSettingName.Empty();
	SetData2Output();
	return 0;
}
bool CKeySetting::GetUsePS(void)
{
	return (BST_UNCHECKED != m_CardKey.m_UsePS.GetCheck());
}
bool CKeySetting::SetUsePS(bool bCheck)
{
	if (bCheck)
		m_CardKey.m_UsePS.SetCheck(BST_CHECKED);
	else
		m_CardKey.m_UsePS.SetCheck(BST_UNCHECKED);


	OnBnClickedOk();
	return true;

}
//************************************
// Method:    GetPIN
// FullName:  CKeySetting::GetPIN
// Access:    public 
// Returns:   CString
// Qualifier:
// Parameter: int iPIN ; 
// 01:PIN1, 11PUK1 ,02 0x81 PIN2,0x12 0x91 PUK81; 0x4 0xA ADM
//************************************ 
CString CKeySetting::GetPIN(int iPIN)
{
	return m_CardKey.GetPIN(iPIN);
}
CString CKeySetting::GetKI(void)
{
	CString csKI;
	m_Milenage.GetDlgItemTextA(IDC_KI_Edit,csKI);
	return csKI;
}
CString CKeySetting::GetOpc(void)
{
	CString csOPC;
	m_Milenage.GetDlgItemTextA(IDC_Opc_Edit,csOPC);
	return csOPC;
}

CString CKeySetting::GetCi(int iNumber)
{

	CString csCi;
	int iID;
	switch(iNumber)
	{
	case 1:iID = IDC_C1_Edit;break;
	case 2:iID = IDC_C2_Edit;break;
	case 3:iID = IDC_C3_Edit;break;
	case 4:iID = IDC_C4_Edit;break;
	case 5:iID = IDC_C5_Edit;break;
	}
	m_Milenage.GetDlgItemTextA(iID,csCi);
	return csCi;


}

int CKeySetting::GetRi(int iNumber)
{
	CString csRi;
	int iID;
	switch(iNumber)
	{
	case 1:iID = IDC_R1_Edit;break;
	case 2:iID = IDC_R2_Edit;break;
	case 3:iID = IDC_R3_Edit;break;
	case 4:iID = IDC_R4_Edit;break;
	case 5:iID = IDC_R5_Edit;break;
	}
	m_Milenage.GetDlgItemTextA(iID,csRi);
	return _CString2Int(csRi);

}

bool CKeySetting::OpenKeySetting(CString csPath)
{

	CString csData;
	CFileStatus csSta;
	CStdioFile CSFFile;
	int iRet;
	bool bRet;


	if (!CSFFile.Open(csPath,CFile::shareDenyRead))
		return false;

	if (! CSFFile.GetStatus(csPath,csSta))
	{
		CSFFile.Close();
		return false;
	}
	//读取文件头
	iRet = CSFFile.ReadString(csData);

	if ((iRet == FALSE)||(csData!=_T("#Key Setting File#")))
	{
		MessageBox(_T("不是设置文件"));
		CSFFile.Close();
		return false;
	}

	do 
	{
		//读取文件内容
		iRet = CSFFile.ReadString(csData);
		if (iRet == FALSE)
			break;
		bRet = TransactKeySetting(csData);

	} while (iRet);

	CSFFile.Close();

	csSettingName = csPath;

	return true;
}
bool CKeySetting::TransactKeySetting(CString csData)
{

	BOOL bRet;
	CString csName,csValue;
	int iSum;
	bRet = _RecogniseFileData(csData,&csName,&csValue,&iSum);

	if (csName == _T("PIN1"))m_CardKey.SetDlgItemTextA(IDC_PIN1_Edit,csValue);
	else if (csName == _T("PUK1"))m_CardKey.SetDlgItemTextA(IDC_PUK1_Edit,csValue);
	else if (csName == _T("PIN2"))m_CardKey.SetDlgItemTextA(IDC_PIN2_Edit,csValue);
	else if (csName == _T("PUK2"))m_CardKey.SetDlgItemTextA(IDC_PUK2_Edit,csValue);
	else if (csName == _T("ADM1"))m_CardKey.SetDlgItemTextA(IDC_ADM_Edit,csValue);
	else if (csName == _T("Pre_ADM1"))m_CardKey.SetDlgItemTextA(IDC_ADMCommand_Edit,csValue);
	else if (csName == _T("PS"))m_CardKey.SetDlgItemTextA(IDC_PS_Edit,csValue);
	else if (csName == _T("Pre_PS"))m_CardKey.SetDlgItemTextA(IDC_PSCommand_Edit,csValue);
	else if (csName == _T("KI"))m_Milenage.SetDlgItemTextA(IDC_KI_Edit,csValue);
	else if (csName == _T("OPC_OP"))m_Milenage.SetDlgItemTextA(IDC_Opc_Edit,csValue);
	else if (csName == _T("R1"))m_Milenage.SetDlgItemTextA(IDC_R1_Edit,csValue);
	else if (csName == _T("R2"))m_Milenage.SetDlgItemTextA(IDC_R2_Edit,csValue);
	else if (csName == _T("R3"))m_Milenage.SetDlgItemTextA(IDC_R3_Edit,csValue);
	else if (csName == _T("R4"))m_Milenage.SetDlgItemTextA(IDC_R4_Edit,csValue);
	else if (csName == _T("R5"))m_Milenage.SetDlgItemTextA(IDC_R5_Edit,csValue);
	else if (csName == _T("C1"))m_Milenage.SetDlgItemTextA(IDC_C1_Edit,csValue);
	else if (csName == _T("C2"))m_Milenage.SetDlgItemTextA(IDC_C2_Edit,csValue);
	else if (csName == _T("C3"))m_Milenage.SetDlgItemTextA(IDC_C3_Edit,csValue);
	else if (csName == _T("C4"))m_Milenage.SetDlgItemTextA(IDC_C4_Edit,csValue);
	else if (csName == _T("C5"))m_Milenage.SetDlgItemTextA(IDC_C5_Edit,csValue);
	else if (csName == _T("IsOPC"))
	{
		if (_CString2Int(csValue) == 01)	m_Milenage.m_IsOPC.SetCheck(TRUE);
		else m_Milenage.m_IsOPC.SetCheck(FALSE);	
	}
	else if (csName == _T("UsePS"))
	{
		if (_CString2Int(csValue) == 01)	m_CardKey.m_UsePS.SetCheck(TRUE);
		else m_CardKey.m_UsePS.SetCheck(FALSE);	
	}
	else
		return false;

	return true;
}
int  CKeySetting::Save2File(CString csPath)
{
	CString csData;
	CFileStatus csSta;
	CStdioFile CSFFile;

	if (!CSFFile.Open(csPath,CFile::modeWrite))
		return -1;

	if (!CSFFile.GetStatus(csPath,csSta))
	{
		CSFFile.Close();
		return -2;
	}
	csData.Empty();
	GenerateKeyData2File(csData);

	CSFFile.WriteString(csData);

	CSFFile.Close();
	return 1;
}


// 获取Key数据，用于存于文件中，生成数据，符合KeyFile 格式
int CKeySetting::GenerateKeyData2File(CString& csData)
{
	CString csCurKey;
	csData.Empty();

	csData += _T("#Key Setting File#\n");

	m_CardKey.GetDlgItemTextA(IDC_PIN1_Edit,csCurKey);
	csData += (_T("[PIN1]:")+csCurKey+_T("\n"));

	m_CardKey.GetDlgItemTextA(IDC_PUK1_Edit,csCurKey);
	csData += (_T("[PUK1]:")+csCurKey+_T("\n"));

	m_CardKey.GetDlgItemTextA(IDC_PIN2_Edit,csCurKey);
	csData += (_T("[PIN2]:")+csCurKey+_T("\n"));

	m_CardKey.GetDlgItemTextA(IDC_PUK2_Edit,csCurKey);
	csData += (_T("[PUK2]:")+csCurKey+_T("\n"));

	m_CardKey.GetDlgItemTextA(IDC_ADM_Edit,csCurKey);
	csData += (_T("[ADM1]:")+csCurKey+_T("\n"));

	m_CardKey.GetDlgItemTextA(IDC_ADMCommand_Edit,csCurKey);
	csData += (_T("[Pre_ADM1]:")+csCurKey+_T("\n"));

	m_CardKey.GetDlgItemTextA(IDC_PS_Edit,csCurKey);
	csData += (_T("[PS]:")+csCurKey+_T("\n"));

	m_CardKey.GetDlgItemTextA(IDC_PSCommand_Edit,csCurKey);
	csData += (_T("[Pre_PS]:")+csCurKey+_T("\n"));

	if (m_CardKey.m_UsePS.GetCheck()==BST_UNCHECKED)
		csData += (_T("[UsePS]:00\n"));	
	else
		csData += (_T("[UsePS]:01\n"));	




	m_Milenage.GetDlgItemTextA(IDC_KI_Edit,csCurKey);
	csData += (_T("[KI]:")+csCurKey+_T("\n"));

	m_Milenage.GetDlgItemTextA(IDC_Opc_Edit,csCurKey);
	csData += (_T("[OPC_OP]:")+csCurKey+_T("\n"));

	if (m_Milenage.m_IsOPC.GetCheck()==BST_UNCHECKED)
		csData += (_T("[IsOPC]:00\n"));	
	else
		csData += (_T("[IsOPC]:01\n"));	

	m_Milenage.GetDlgItemTextA(IDC_R1_Edit,csCurKey);
	csData += (_T("[R1]:")+csCurKey+_T("\n"));

	m_Milenage.GetDlgItemTextA(IDC_R2_Edit,csCurKey);
	csData += (_T("[R2]:")+csCurKey+_T("\n"));

	m_Milenage.GetDlgItemTextA(IDC_R3_Edit,csCurKey);
	csData += (_T("[R3]:")+csCurKey+_T("\n"));

	m_Milenage.GetDlgItemTextA(IDC_R4_Edit,csCurKey);
	csData += (_T("[R4]:")+csCurKey+_T("\n"));

	m_Milenage.GetDlgItemTextA(IDC_R5_Edit,csCurKey);
	csData += (_T("[R5]:")+csCurKey+_T("\n"));

	m_Milenage.GetDlgItemTextA(IDC_C1_Edit,csCurKey);
	csData += (_T("[C1]:")+csCurKey+_T("\n"));

	m_Milenage.GetDlgItemTextA(IDC_C2_Edit,csCurKey);
	csData += (_T("[C2]:")+csCurKey+_T("\n"));

	m_Milenage.GetDlgItemTextA(IDC_C3_Edit,csCurKey);
	csData += (_T("[C3]:")+csCurKey+_T("\n"));

	m_Milenage.GetDlgItemTextA(IDC_C4_Edit,csCurKey);
	csData += (_T("[C4]:")+csCurKey+_T("\n"));

	m_Milenage.GetDlgItemTextA(IDC_C5_Edit,csCurKey);
	csData += (_T("[C5]:")+csCurKey+_T("\n"));

	return 1;
}


CString CKeySetting::GetLocalInformation(int iCode)
{

	//00：位置信息(MCC，MNC，LAC及Cell ID) ;   
	//01：ME的IMEI ;  
	//02：网络测量结果;   
	//03：当前日期、时间和时区;
	//04：语言设置;
	//05：Timing Advance;
	CString csText;
	CString csLocal;
	switch(iCode)
	{
	//MCCMNC
	case 0:csText =  m_Local.GetLocalInforamtion();
		 _GenerateTLVData(csText,0x13,csLocal);
		break;
	//IMEI
	case 1:m_Local.GetDlgItemTextA(IDC_IMEI_Edit,csText);
		 _GenerateTLVData(csText,0x14,csLocal);break;
	//NMR
	case 2: m_Local.GetDlgItemTextA(IDC_NMR_Edit,csText);
		_GenerateTLVData(csText,0x16,csLocal);break;
	//TIME
	case 3:csText = m_Local.GetDateTime();
		_GenerateTLVData(csText,0x26,csLocal);break;
	case 4:csText = "1D00";
		_GenerateTLVData(csText,0x2D,csLocal);break;
	case 5:csText = "1D00";
		_GenerateTLVData(csText,0x2E,csLocal);break;

	default:break;
	}
	return csLocal;
}


// 根据CFL来安装相对应的Key
bool CKeySetting::InstallCFLSetting(int iType)
{

	CString csName,csDir;
	switch(iType)
	{
	case 0x01:csName = _T("CTC_Native_301.ini");break; 
	case 0x02:csName = _T("CTC_M2M_2G3G_301.ini");break;	
	case 0x03:csName = _T("CTC_M2M_2G3G4G_301.ini");break;
	case 0x11:csName = _T("CMCC_Native_20A.ini");break; 
	case 0x12:csName = _T("CMCC_M2M_20.ini");break;	
	case 0x21:csName = _T("CUC_Normal1.ini");break; 
	case 0x22:csName = _T("CUC_Normal2.ini");break;
	case 0xF1:csName = _T("GSM.ini");break;	
	case 0xF2:csName = _T("3GPP.ini");break;	
	case 0xF3:csName = _T("3GPP2.ini");break;	
	case 0xF4:csName = _T("CDMA.ini");break;	
	default:csName = _T("KeySetting.ini");break;
	}
	__GetCurrentDIR(csDir);
	return OpenKeySetting(csDir+_T("\\INI\\")+ csName);
}


void CKeySetting::OnTcnSelchangeKeyTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int CurSel = m_KeyTab.GetCurSel();
	switch(CurSel)
	{
	case 0:
		m_CardKey .ShowWindow(true);
		m_Milenage.ShowWindow(false);
		m_CUCKey  .ShowWindow(false);
		m_CMCCKey .ShowWindow(false);
		m_Local   .ShowWindow(false);

		break;
	case 1:
		m_CardKey .ShowWindow(false);
		m_Milenage.ShowWindow(true);
		m_CUCKey  .ShowWindow(false);
		m_CMCCKey .ShowWindow(false);
    	m_Local   .ShowWindow(false);
		break;
	case 2:
		m_CardKey  .ShowWindow(false);
		m_Milenage .ShowWindow(false);
		m_CMCCKey  .ShowWindow(true);
		m_CUCKey   .ShowWindow(false);
		m_Local    .ShowWindow(false);

		break;
	case 3:
		m_CardKey  .ShowWindow(false);
		m_Milenage .ShowWindow(false);
		m_CMCCKey  .ShowWindow(false);
		m_CUCKey   .ShowWindow(true);
		m_Local    .ShowWindow(false);

		break;
	case 4:
		m_CardKey .ShowWindow(false);
		m_Milenage.ShowWindow(false);
		m_CUCKey  .ShowWindow(false);
		m_CMCCKey .ShowWindow(false);
		m_Local   .ShowWindow(true);
		break;
	default:
		break;
	}
	*pResult = 0;
}

void CKeySetting::SetData2Output()
{

	//CMainFrame* pMain;
	//COutputWnd* pOutput;
	//pMain = (CMainFrame*) AfxGetApp()->GetMainWnd();
	//pOutput = pMain->GetOutputWnd();
	//pOutput->set

	SetK(GetKI());
	MilenageSetOPc(GetOpc());
	MilenageSetCi(GetCi(1),GetCi(2),GetCi(3),GetCi(4),GetCi(5));
	MilenageSetRi(GetRi(1),GetRi(2),GetRi(3),GetRi(4),GetRi(5));
	//SetOP_C



}

// C:\自写程序\CardManage\CardManage\KeySetting.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "CardInfomation.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// CUST 对话框

IMPLEMENT_DYNAMIC(CUST, CDialogEx)

CUST::CUST(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUST::IDD, pParent)
{

}

CUST::~CUST()
{
}

void CUST::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUST, CDialogEx)
ON_COMMAND_RANGE(IDC_Service1_Radio, IDC_Service89_Radio, &CUST::OnChangeUST)
ON_BN_CLICKED(IDOK, &CUST::OnBnClickedOk)
END_MESSAGE_MAP()


// 把ust 数据 设置到 Dialog


int CUST::SetUST(CString csUST)
{
	int iSum;

	ZeroMemory(ucUST,12);

	iSum = csUST.GetLength()*4;

	if (iSum > 89)
	{
		iSum = 89;
		csUST = csUST.Left(24);
	}


	for (int i = 1 ; i <= iSum ; i++)
	{
		((CButton*)GetDlgItem(1200+i)) ->SetCheck( _Getbit(csUST,i) );
	}


	return _CString2UcHex(csUST,ucUST);
}

void CUST::OnChangeUST(UINT id)
{
	int iLID,iRet;
	iLID = id -IDC_Service1_Radio; 
	iRet = !(((ucUST[iLID/8] >> (iLID%8))&1));
	((CButton*) GetDlgItem(id))->SetCheck(iRet);

	if (iRet)
		ucUST[iLID/8] = ucUST[iLID/8]|( 1 << (iLID%8 ));
	else
		ucUST[iLID/8] = ucUST[iLID/8]-( 1 << (iLID%8));
}

void CUST::OnBnClickedOk()
{
	CString csResp;
	CString csData;
	int iLen;
	CMainFrame* CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();

	if ((CurMainFrm->_TestCaseFileIsExisted_UICC(_T("A000000087"),true) > 0)&&(CurMainFrm->_TestCaseSelectFile(_T("6F38"),csResp)))
	{
		if ((CurMainFrm->_TestCaseVerify(0x0A))||(CurMainFrm->_TestCaseVerifyPS()))
		{
			iLen   = CurMainFrm->_GetFileSize (csResp);
			_UcHex2CString(ucUST,iLen,csData);
			csResp = CurMainFrm->_TestCaseSendCommand(_T("00D60000")+Int2CString(iLen,2)+ csData);
		}
	}

	CDialogEx::OnOK();
}


// SIMToolkit.cpp : 实现文件
//

#include "stdafx.h"

#include "CardManage.h"
#include "CardInfomation.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// CSIMToolkit 对话框

IMPLEMENT_DYNAMIC(CSIMToolkit, CDialogEx)

	CSIMToolkit::CSIMToolkit(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSIMToolkit::IDD, pParent)
{

}

CSIMToolkit::~CSIMToolkit()
{
}

void CSIMToolkit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SIMToolKit_Menu_Listbox, m_Menu_Listbox);
	DDX_Control(pDX, IDC_STK_Commnd_Listbox, m_STK_Listbox);
}


BEGIN_MESSAGE_MAP(CSIMToolkit, CDialogEx)
	ON_LBN_DBLCLK(IDC_SIMToolKit_Menu_Listbox, &CSIMToolkit::OnDblclkSimtoolkitMenuListbox)
	ON_BN_CLICKED(IDC_STK_OK_Button, &CSIMToolkit::OnBnClickedStkOkButton)
	ON_BN_CLICKED(IDC_STK_Cancel_Button, &CSIMToolkit::OnBnClickedStkCancelButton)
	ON_LBN_DBLCLK(IDC_STK_Commnd_Listbox, &CSIMToolkit::OnLbnDblclkStkCommndListbox)
END_MESSAGE_MAP()


// CSIMToolkit 消息处理程序



bool CSIMToolkit::InstallMenu(CString csFetch)
{

	CString csNumber,csName,csItem;

	int iSum;

	m_Menu_Listbox.ResetContent();
	iSum = _GetMenuNumber(csFetch);


	for (int i= 1 ; i <= iSum ;i++)
	{
		csItem = _GetMenu(csFetch,i);
		if (!csItem.IsEmpty())
		{
			csNumber = csItem.Left(02);

			if (csItem.Mid(02,02)!= (_T("80")))
				csName = TranslateAscii(csItem.Mid(02,csItem.GetLength()-02));
			else
				csName = TranslateUcs2(csItem.Mid(04,csItem.GetLength()-04));


			m_Menu_Listbox.AddString(_T("    ") + csName);
		}

	}

	return true;
}

CString CSIMToolkit::GetPreFetch(void)
{

	return csCurrentFetch;
}

void CSIMToolkit::Set2PreFetch(CString csFetch)
{

	csCurrentFetch = csFetch;

}

void CSIMToolkit::SetSTKSW(int iSW)
{
	iSTKSW = iSW;
}

int  CSIMToolkit::GetItemID(int iNum,CString csFetch)
{
	csFetch = GetTLVData(csFetch,0xD0);
	if (csFetch.IsEmpty())
		return -1 ;

	csFetch = GetTLVData(csFetch,0x8F,iNum);

	if (csFetch.IsEmpty())
		return -2 ;


	return _CString2Int( csFetch.Left(02));
}

void CSIMToolkit::OnDblclkSimtoolkitMenuListbox()
{
	int iID;

	iID = m_Menu_Listbox.GetCurSel();

	_MenuSelection(iID+1);
}

int CSIMToolkit::_GetMenuNumber(CString csFetch)
{
	int iNumber;
	int iOffset,iLen;
	int iFirstTag;

	iNumber = 0;
	csFetch = GetTLVData(csFetch,0xD0);
	if (csFetch.IsEmpty())
		return iNumber;
	iOffset = 0 ;
	iLen    = csFetch.GetLength();
	do 
	{
		iFirstTag = _CString2Int(csFetch.Mid(iOffset,02));

		iOffset   += GetTLVData(csFetch.Mid(iOffset,iLen-iOffset),iFirstTag).GetLength();
		iOffset   += 4;

		if ((iFirstTag&0x7F) == 0x0F)
			iNumber += 1;

	} while (iOffset< iLen);



	return iNumber;
}

CString CSIMToolkit::_GetMenu(CString csFetch, int iNumber)
{
	int iCurrent;
	int iOffset,iLen;
	int iFirstTag;
	CString csTemp;

	iCurrent = 0;
	csFetch = GetTLVData(csFetch,0xD0);
	if (csFetch.IsEmpty())
		return csTemp;
	iOffset = 0 ;
	iLen    = csFetch.GetLength();
	do 
	{

		iFirstTag = _CString2Int(csFetch.Mid(iOffset,02));

		csTemp    =GetTLVData(csFetch.Mid(iOffset,iLen-iOffset),iFirstTag); 

		iOffset   += csTemp.GetLength();
		iOffset   += 4;

		if ((iFirstTag&0x7F) == 0x0F)
			iCurrent += 1;

		if (iNumber == iCurrent)
			iLen = 0;
		else
			csTemp.Empty();


	} while (iOffset< iLen);


	return csTemp;

}

void CSIMToolkit::OnBnClickedStkOkButton()
{	

	if ((GetCurrentCommandDetails()&0x00FF00) != 0x2500)
	{
		ContinueCurrentTerminalResponse(GetCurrentCommandDetails(),0x00,_T(""));
		ContinueCurrentSTK();
	}



}

void CSIMToolkit::OnBnClickedStkCancelButton()
{

	if ((GetCurrentCommandDetails()&0x00FF00) != 0x2500)
	{
		ContinueCurrentTerminalResponse(GetCurrentCommandDetails(),0x11,_T(""));
		ContinueCurrentSTK();
	}

}

int CSIMToolkit::GetCurrentCommandDetails(void)
{
	CString csFetch;

	csFetch = GetTLVData(csCurrentFetch,0xD0);

	csFetch= GetTLVData(csFetch,0x81);

	return _CString2Int(csFetch);
}

int CSIMToolkit::_DisplayText(CString csText)
{
	CString csDCS;
	CString csResult;

	csDCS = csText.Left(02);

	switch(_CString2Int(csDCS))
	{
	case 0x08:
		csResult = TranslateUcs2(csText.Mid(02,csText.GetLength()-02));
		break;


	case 0x04:
		csResult = TranslateAscii(csText.Mid(02,csText.GetLength()-02));
		break;

	case 0x00:
		csResult = Translate7bit(csText.Mid(02,csText.GetLength()-02));
		break;

	default:
		break;
	}
	SetDlgItemText(IDC_Text_Edit,csResult);

	GetDlgItem(IDC_Text_Edit)->ShowWindow(SW_SHOW);


	return 0;
}

int CSIMToolkit::_DisplayAlpha(CString csAlpha)
{
	CString csDCS,csAlphaId;

	csDCS =csAlpha.Mid(0,2);

	csAlphaId = csAlpha.Mid(2,csAlpha.GetLength()-2);

	switch(_CString2Int(csDCS))
	{
	case 0x80:

		csAlphaId = TranslateUcs2(csAlphaId);
		break;
	case 0x04:
		csAlphaId = TranslateAscii(csAlphaId);
		break;
	default:
		csAlphaId = TranslateAscii(csAlpha);
		break;
	}

	SetDlgItemText(IDC_Alpha_Edit,csAlphaId);

	GetDlgItem(IDC_Alpha_Edit)->ShowWindow(SW_SHOW);



	return 0;

}

int CSIMToolkit::_DisplayInput(CString csInput)
{
	CString csDCS,csInputData;

	csDCS =csInput.Mid(0,2);

	switch(_CString2Int(csDCS))
	{
	case 0x08:

		csInputData = csInput.Mid(2,csInput.GetLength()-2);
		csInputData = TranslateUcs2(csInputData);

		break;
	case 0x04:

		break;
	case 0x00:

		break;
	default:
		break;
	}

	SetDlgItemText(IDC_Input_Edit,csInputData);

	GetDlgItem(IDC_Input_Edit)->ShowWindow(SW_SHOW);

	return 0;
}

int CSIMToolkit::_GetInputLen(int* iMin , int *iMax)
{
	CString csPSIMC,csTemp;
	csPSIMC = GetTLVData(csCurrentFetch,0xD0);
	if (csPSIMC.IsEmpty())
		return 0;
	csTemp = GetTLVData(csPSIMC,0x91);
	if (csTemp.IsEmpty())
		csTemp = GetTLVData(csPSIMC,0x11);

	if (csTemp.IsEmpty())
		return 0;


	*iMin = _CString2Int(csTemp.Mid(0,2));
	*iMax = _CString2Int(csTemp.Mid(2,2));

	return 1;
}


int CSIMToolkit::ContinueCurrentSTK()
{
	int iResult;
	CString csAdd;
	csAdd.Empty();
	int iRet;

	if ((iSTKSW&0xFF00) != 0x9100)
		return 0;



	iSTKSW = ContinueCurrentFetch(iSTKSW&0xFF);

	if (iSTKSW == 0x9000)
	{
		TransationFetchData(csCurrentFetch);

		iRet = GenerateTerminal(GetCurrentCommandDetails(),&iResult,csAdd);


		if (iRet == 0 )
			iSTKSW = ContinueCurrentTerminalResponse(GetCurrentCommandDetails(),iResult,csAdd);
		else if (iRet <0)
		{
			return iRet;
		}
	}

	return iSTKSW;
}

int CSIMToolkit::_TerminalProfile(CString csProfile)
{
	CMainFrame *CurMainFrm;
	CurMainFrm =(CMainFrame*)AfxGetApp()->GetMainWnd();
	iSTKSW = CurMainFrm->_TerminalProfile(csProfile,CurMainFrm->bIsUICC);
	return iSTKSW;
}

int CSIMToolkit::ContinueCurrentFetch(int iFetchLen)
{
	CMainFrame *CurMainFrm;
	CurMainFrm =(CMainFrame*)AfxGetApp()->GetMainWnd();
	iSTKSW = CurMainFrm->_Fetch(iSTKSW&0x00FF,csCurrentFetch,CurMainFrm->bIsUICC);
	return iSTKSW;
}

int CSIMToolkit::ContinueCurrentTerminalResponse(int iDetails, int iResult, CString csADD)
{
	CMainFrame *CurMainFrm;
	CurMainFrm =(CMainFrame*)AfxGetApp()->GetMainWnd();

	iSTKSW = CurMainFrm ->_TerminalResponse(iDetails,iResult,csADD,CurMainFrm->bIsUICC);

	if (iSTKSW == 0x9000)
	{
		csCurrentFetch = csSetupMenu;
		TransationFetchData(csSetupMenu);
	}


	return iSTKSW;
}

int CSIMToolkit::TransationFetchData(CString csFetch)
{
	CString csPSIMC;
	CString csTemp;

	csPSIMC = GetTLVData(csFetch ,0xD0);

	GetDlgItem(IDC_Alpha_Edit)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_Text_Edit)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_Input_Edit)->ShowWindow(SW_HIDE);
	m_Menu_Listbox.ResetContent();


	if (csPSIMC.IsEmpty())
		return -1;

	csTemp = GetTLVData(csPSIMC,0x0D);
	if (!csTemp.IsEmpty())
		_DisplayText(csTemp);
	csTemp = GetTLVData(csPSIMC,0x8D);
	if (!csTemp.IsEmpty())
		_DisplayText(csTemp);


	csTemp = GetTLVData(csPSIMC,0x05);
	if (!csTemp.IsEmpty())
		_DisplayAlpha(csTemp);
	csTemp = GetTLVData(csPSIMC,0x85);
	if (!csTemp.IsEmpty())
		_DisplayAlpha(csTemp);

	if((!GetTLVData(csPSIMC,0x8F).IsEmpty()) ||(!GetTLVData(csPSIMC,0x0F).IsEmpty()))
		InstallMenu(csFetch);

	csTemp = GetTLVData(csPSIMC,0x17);
	if (!csTemp.IsEmpty())
		_DisplayInput(csTemp);
	csTemp = GetTLVData(csPSIMC,0x97);
	if (!csTemp.IsEmpty())
		_DisplayInput(csTemp);




	return 0;
}

int CSIMToolkit::GenerateTerminal(int iDetails,int* iResult, CString& csADD)
{
	int iRet;
	CMainFrame* pMain; 
		
	pMain= (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString csCommandName;

	*iResult = 0x00;
	iRet = 0;

	switch((iDetails/0x100)&0xFF)
	{
	case 01:
		csCommandName = _T("REFRESH");
		break;
	case 02:
		csCommandName = _T("MORE TIME");
		break;
	case 03:
		csCommandName = _T("POLL INTERVAL");
		break;
	case 04:
		csCommandName = _T("POLLING OFF");
		break;
	case 05:
		csCommandName = _T("SET UP EVENT LIST");
		break;
	case 0x10:
		csCommandName = _T("SET UP CALL");
		break;
	case 0x11:
		csCommandName = _T("SEND SS");
		break;
	case 0x12:
		csCommandName = _T("SEND USSD");
		break;
	case 0x13:
		csCommandName = _T("SEND SHORT MESSAGE");
		break;

	case 0x14:
		csCommandName = _T("SEND DTMF");
		break;

	case 0x15:
		csCommandName = _T("LAUNCH BROWSER");
		break;
	case 0x20:
		csCommandName = _T("PLAY TONE");
		break;

	case 0x21:

		csCommandName = _T("DISPLAY TEXT");
		if ((iDetails&0xFF) == 0x80)
			iRet=  1;
		else
			iRet = 2;
		break;
	case 0x22:
		csCommandName = _T("GET INKEY");
		if (!GetDlgItem(IDC_Input_Edit)->IsWindowVisible())
		{
			SetDlgItemText(IDC_Input_Edit,_T(""));
			GetDlgItem(IDC_Input_Edit)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_Input_Edit)->SetFocus();
		}
		iRet =  1;
		break;

	case 0x23:
		csCommandName = _T("GET INPUT");

		if (!GetDlgItem(IDC_Input_Edit)->IsWindowVisible())
		{
			SetDlgItemText(IDC_Input_Edit,_T(""));
			GetDlgItem(IDC_Input_Edit)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_Input_Edit)->SetFocus();
		}

		iRet = 1;
		break;

	case 0x24:
		csCommandName = _T("SELECT ITEM");
		iRet = 1;
		break;
	case 0x25:
		csSetupMenu = csCurrentFetch;
		csCommandName = _T("SET UP MENU");
		iRet = 0;
		break;


	case 0x26:
		csCommandName = _T("PROVIDE LOCAL INFORMATION");
		iRet = 0;
		*iResult = 0x00;

		if (!pMain->GetLocalInformationFromKeySetting(csADD,iDetails&0xFF))
		{
			switch(iDetails&0xFF)
				{
					//00：位置信息(MCC，MNC，LAC及Cell ID) ;   
					//01：ME的IMEI ;  
					//02：网络测量结果;   
					//03：当前日期、时间和时区;
					//04：语言设置;
					//05：Timing Advance;
				case  0x00:
					csADD    = _T("130700000000000000");
					break;
				case 0x01:
					csADD    = _T("14088A0000000012345678");
					break;
				case 0x02:
					csADD    = _T("161000000000000000000000000000000000");
					break;
				case 0x03:
					csADD    = _T("1D00");
					break;
				case 0x04:
					csADD    = _T("1D00");
					break;
				case 0x05:
					csADD    = _T("1D00");
					break;
				default:
					break;
				}
		}
	

		break;

	case 0x27:
		csCommandName = _T("TIMER MANAGEMENT");
		break;

	case 0x28:
		csCommandName = _T("SET UP IDLE MODEL TEXT");
		break;

	case 0x40:
		csCommandName = _T("OPEN CHANNEL");
		break;
	case 0x41:
		csCommandName = _T("CLOSE CHANNEL");
		break;
	case 0x42:
		csCommandName = _T("RECEIVE DATA");
		break;
	case 0x43:
		csCommandName = _T("SEND DATA");
		break;
	default:
		iRet = 0;
		*iResult = 0x00;
		csADD    = _T("");
		break;
	}


	m_STK_Listbox.AddString(csCommandName);

	return iRet;
}

int CSIMToolkit::_InputData(CString csData)
{
	int iRet;
	int iMin,iMax,iLen;
	int iDes;

	iRet = _GetInputLen(&iMin,&iMax);
	if(iRet == 0)
		return 0;

	iDes = GetCurrentCommandDetails();

	if((iDes&0xFF00) != 0x2300)
		return 0;


	if (iDes&0x2) 
	{

		csData =  ConvertUcs2(csData);

		iLen = csData.GetLength()/4;

		csData=  _T("08")+csData;
	}
	else
	{
		if (iDes&0x8)
		{
			csData = Convert7bit(csData);
			iLen = csData.GetLength()/2;
			csData=  _T("00")+csData;
		}
		else
		{
			csData = ConvertAscii(csData);
			iLen = csData.GetLength()/2;
			csData=  _T("04")+csData;
		}	
	}



	if ((iLen < iMin)||(iLen >iMax))
		return 0;

	iRet = ContinueCurrentTerminalResponse(iDes,00,GenerateTLVData(csData,0x0D));


	while((iRet&0x9100)== 0x9100)

	{
		iRet = ContinueCurrentSTK();
		if (iRet < 0)
			break;
	}

	return 1;

}

int CSIMToolkit::_InputKey(CString csData)
{
	int iRet;
	int iDes;

	iDes = GetCurrentCommandDetails();

	if((iDes&0xFF00) != 0x2200)
		return 0;


	if (iDes&0x2) 
	{

		csData =  ConvertUcs2(csData);

		csData=  _T("08")+csData;
	}
	else
	{
		if (iDes&0x8)
		{
			csData = Convert7bit(csData);

			csData=  _T("00")+csData;
		}
		else
		{
			csData = ConvertAscii(csData);

			csData=  _T("04")+csData;
		}	
	}


	iRet = ContinueCurrentTerminalResponse(iDes,00,GenerateTLVData(csData,0x0D));


	while((iRet&0x9100)== 0x9100)

	{
		iRet = ContinueCurrentSTK();
		if (iRet < 0)
			break;
	}

	return 1;

}

int CSIMToolkit::StartSIMToolkit(void)
{
	int iRet;
	iRet = _TerminalProfile(_T("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"));


	while((iSTKSW&0x9100)== 0x9100)

	{
		iRet = ContinueCurrentSTK();

		if (iRet <0)
			break;

	}


	return iRet;
}

int CSIMToolkit::_MenuSelection(int iID)
{
	int iRet;
	CMainFrame *CurMainFrm;
	CurMainFrm =(CMainFrame*)AfxGetApp()->GetMainWnd();

	if ((GetCurrentCommandDetails() &0x00FF00) == 0x2400)
		iSTKSW = CurMainFrm->_TerminalResponseMenuSeletion(GetItemID(iID,csCurrentFetch) );
	else
		iSTKSW = CurMainFrm->_EnvelopMenuSeletion(GetItemID(iID,csSetupMenu));

	while((iSTKSW&0x9100)== 0x9100)

	{
		iRet = ContinueCurrentSTK();
		if (iRet < 0)
			break;
	}




	return 0;
}

BOOL CSIMToolkit::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) 
	{
		if (GetDlgItem(IDC_Input_Edit),IsWindowVisible())
		{
			CString csInput;

			GetDlgItemText(IDC_Input_Edit,csInput);

			if ((GetCurrentCommandDetails()&0xFF00)== 0x2300 )
				_InputData(csInput);
			else
				_InputKey(csInput);

		}
		return TRUE;
	}
	else
		return CDialogEx::PreTranslateMessage(pMsg);
}

void CSIMToolkit::OnLbnDblclkStkCommndListbox()
{
	m_STK_Listbox.ResetContent();
}
// C:\自写程序\CardManage\CardManage\CardInfomation.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "CardInfomation.h"
#include "afxdialogex.h"


// CCardKey 对话框

IMPLEMENT_DYNAMIC(CCardKey, CDialogEx)

CCardKey::CCardKey(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCardKey::IDD, pParent)
{

}

CCardKey::~CCardKey()
{
}

void CCardKey::DoDataExchange(CDataExchange* pDX)
{

	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_UsePS_Check, m_UsePS);
}


BEGIN_MESSAGE_MAP(CCardKey, CDialogEx)
	ON_BN_CLICKED(IDC_Key, &CCardKey::OnBnClickedKey)
	ON_WM_DESTROY()
END_MESSAGE_MAP()
void CCardKey::Initialize_Form()
{	

	CString csKey;
	CWinApp * pApp;
	pApp = AfxGetApp();
	CString csPath = _T("Settings\\Keys\\PIN");

	csKey = pApp->GetProfileString(csPath,_T("PIN1"));
	if (csKey.IsEmpty())
		csKey =_T("31323334FFFFFFFF");
	SetDlgItemText(IDC_PIN1_Edit,csKey);


	csKey = pApp->GetProfileString(csPath,_T("PIN2"));
	if (csKey.IsEmpty())
		csKey =_T("3132333435363738");
	SetDlgItemText(IDC_PIN2_Edit,csKey);


	csKey = pApp->GetProfileString(csPath,_T("PUK1"));
	if (csKey.IsEmpty())
		csKey =_T("31323334FFFFFFFF");
	SetDlgItemText(IDC_PUK1_Edit,csKey);


	csKey = pApp->GetProfileString(csPath,_T("PUK2"));
	if (csKey.IsEmpty())
		csKey =_T("3132333435363738");
	SetDlgItemText(IDC_PUK2_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("ADM"));
	if (csKey.IsEmpty())
		csKey =_T("3132333435363738");
	SetDlgItemText(IDC_ADM_Edit,csKey);


	csKey = pApp->GetProfileString(csPath,_T("PS"));
	if (csKey.IsEmpty())
		csKey =_T("3132333435363738");
	SetDlgItemText(IDC_PS_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("PSCommand"));
	if (csKey.IsEmpty())
		csKey =_T("17000008");
	SetDlgItemText(IDC_PSCommand_Edit,csKey);


	csKey = pApp->GetProfileString(csPath,_T("ADMCommand"));
	if (csKey.IsEmpty())
		csKey =_T("20000A08");
	SetDlgItemText(IDC_ADMCommand_Edit,csKey);


	int iCheck = pApp->GetProfileInt(csPath,_T("IsPS"),0);

	((CButton*)GetDlgItem(IDC_UsePS_Check))->SetCheck(iCheck);


	//SetDlgItemText(IDC_PIN1_Edit,_T("31323334FFFFFFFF"));
	//SetDlgItemText(IDC_PUK1_Edit,_T("31323334FFFFFFFF"));

	//SetDlgItemText(IDC_PIN2_Edit,_T("3132333435363738"));
	//SetDlgItemText(IDC_PUK2_Edit,_T("31323334FFFFFFFF"));

	//SetDlgItemText(IDC_ADMCommand_Edit,_T("20000A08"));
	//SetDlgItemText(IDC_ADM_Edit,_T("3132333435363738"));

	//SetDlgItemText(IDC_PSCommand_Edit,_T("17000008"));
	//SetDlgItemText(IDC_PS_Edit,_T("31323334FFFFFFFF"));
}
CString CCardKey::GetPIN(int iPIN)
{
	CString csPIN;
	int iRet;
	switch(iPIN)
	{
	case 01:
		iRet = GetDlgItemText(IDC_PIN1_Edit,csPIN);
		break;
	case 0x11:
		iRet = GetDlgItemText(IDC_PUK1_Edit,csPIN);
		break;

	case 02:
	case 0x81:
		iRet = GetDlgItemText(IDC_PIN2_Edit,csPIN);
		break;

	case 0x12:
	case 0x91:
		iRet = GetDlgItemText(IDC_PUK2_Edit,csPIN);
		break;

	case 04:
	case 0x0A:
		iRet = GetDlgItemText(IDC_ADM_Edit,csPIN);
		break;

	case 0xF:
		iRet = GetDlgItemText(IDC_PS_Edit,csPIN);
		break;
	case 0xFA:
		iRet = GetDlgItemText(IDC_ADMCommand_Edit,csPIN);
		break;
	case 0xFF:
		iRet = GetDlgItemText(IDC_PSCommand_Edit,csPIN);
		break;
	}

	return csPIN;
}
// C:\自写程序\CardManage\CardManage\CardInfomation.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "CardInfomation.h"
#include "afxdialogex.h"


// CMilenage 对话框

IMPLEMENT_DYNAMIC(CMilenageForm, CDialogEx)

CMilenageForm::CMilenageForm(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMilenageForm::IDD, pParent)
{

}

CMilenageForm::~CMilenageForm()
{
}

void CMilenageForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IsOpc_Check, m_IsOPC);
}


BEGIN_MESSAGE_MAP(CMilenageForm, CDialogEx)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void CMilenageForm::Initialize_Form()
{


	CString csKey;
	CWinApp * pApp;
	pApp = AfxGetApp();
	CString csPath = _T("Settings\\Keys\\Milenage");


	csKey = pApp->GetProfileString(csPath,_T("KI"));
	if (csKey.IsEmpty())
		csKey =_T("12345678123456781234567812345678");
	SetDlgItemText(IDC_KI_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("OPc"));
	if (csKey.IsEmpty())
		csKey =_T("12345678123456781234567812345678");
	SetDlgItemText(IDC_Opc_Edit,csKey);


	csKey = pApp->GetProfileString(csPath,_T("C1"));
	if (csKey.IsEmpty())
		csKey =_T("00000000000000000000000000000000");
	SetDlgItemText(IDC_C1_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("C2"));
	if (csKey.IsEmpty())
		csKey =_T("00000000000000000000000000000001");
	SetDlgItemText(IDC_C2_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("C3"));
	if (csKey.IsEmpty())
		csKey =_T("00000000000000000000000000000002");
	SetDlgItemText(IDC_C3_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("C4"));
	if (csKey.IsEmpty())
		csKey =_T("00000000000000000000000000000004");
	SetDlgItemText(IDC_C4_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("C5"));
	if (csKey.IsEmpty())
		csKey =_T("00000000000000000000000000000008");
	SetDlgItemText(IDC_C5_Edit,csKey);


	csKey = pApp->GetProfileString(csPath,_T("R1"));
	if (csKey.IsEmpty())
		csKey =_T("20");
	SetDlgItemText(IDC_R1_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("R2"));
	if (csKey.IsEmpty())
		csKey =_T("00");
	SetDlgItemText(IDC_R2_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("R3"));
	if (csKey.IsEmpty())
		csKey =_T("20");
	SetDlgItemText(IDC_R3_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("R4"));
	if (csKey.IsEmpty())
		csKey =_T("40");
	SetDlgItemText(IDC_R4_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("R5"));
	if (csKey.IsEmpty())
		csKey =_T("60");
	SetDlgItemText(IDC_R5_Edit,csKey);


	int iCheck = pApp->GetProfileInt(csPath,_T("Is OPc"),0);

	((CButton*)GetDlgItem(IDC_IsOpc_Check))->SetCheck(iCheck);



}
// CMilenage 消息处理程序


void CCardKey::OnBnClickedKey()
{
	// TODO: 在此添加控件通知处理程序代码
}

// C:\自写程序\CardManage\CardManage\CardInfomation.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "CardInfomation.h"
#include "afxdialogex.h"


// CLocalInformation 对话框

IMPLEMENT_DYNAMIC(CLocalInformation, CDialogEx)

CLocalInformation::CLocalInformation(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLocalInformation::IDD, pParent)
{

}

CLocalInformation::~CLocalInformation()
{
}

void CLocalInformation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLocalInformation, CDialogEx)
	ON_BN_CLICKED(IDC_UseSystemTime_Check2, &CLocalInformation::OnBnClickedUsesystemtimeCheck2)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void CLocalInformation::Initialize_Form()
{

	CString csKey;
	CWinApp * pApp;
	pApp = AfxGetApp();
	CString csPath = _T("Settings\\Keys\\LocalInformation");


	csKey = pApp->GetProfileString(csPath,_T("IMEI"));
	if (csKey.IsEmpty())
		csKey =_T("12345678123456781234567812345678");
	SetDlgItemText(IDC_IMEI_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("MCCMNC"));
	if (csKey.IsEmpty())
		csKey =_T("64F000");
	SetDlgItemText(IDC_MCCMNC_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("LAC"));
	if (csKey.IsEmpty())
		csKey =_T("8549");
	SetDlgItemText(IDC_LAC_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("CellID"));
	if (csKey.IsEmpty())
		csKey =_T("0001");
	SetDlgItemText(IDC_CellID_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("DateTime"));
	if (csKey.IsEmpty())
	{
		CString csDis,csDate,csTime;
		GetSysDate(csDate);
		GetSysTime(csTime);
		csDis = csDate+csTime;
		csKey = csDis.Mid(00,04)+_T("-")+csDis.Mid(04,02)+_T("-")+csDis.Mid(06,02)+_T(" ")+csDis.Mid(0x8,02)+_T(":")+csDis.Mid(10,02)+_T(":")+csDis.Mid(12,02);
	}
	SetDlgItemText(IDC_DateTime_Edit2,csKey);


	csKey = pApp->GetProfileString(csPath,_T("TimeZone"));
	if (csKey.IsEmpty())
		csKey =_T("00");
	SetDlgItemText(IDC_TimeZone_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("NMR"));
	if (csKey.IsEmpty())
		csKey =_T("00");
	SetDlgItemText(IDC_NMR_Edit,csKey);

	//csKey = pApp->GetProfileString(csPath,_T("NMR"));
	//if (csKey.IsEmpty())
	//	csKey =_T("00");
	//SetDlgItemText(IDC_NMR_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("LanguageSetting"));
	if (csKey.IsEmpty())
		csKey =_T("0001");
	SetDlgItemText(IDC_LanguageSetting_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("TimingAdvance"));
	if (csKey.IsEmpty())
		csKey =_T("0001");
	SetDlgItemText(IDC_TimingAdvance_Edit,csKey);

	int iCheck = pApp->GetProfileInt(csPath,_T("UseSystemTime"),0);

	((CButton*)GetDlgItem(IDC_UseSystemTime_Check2))->SetCheck(iCheck);
	if (iCheck)
		GetDlgItem(IDC_DateTime_Edit2)->EnableWindow(FALSE);



	//GetDlgItemText(IDC_MCCMNC_Edit,csKey);
	//pApp->WriteProfileString(csPath,_T("MCCMNC"),csKey);
	//GetDlgItemText(IDC_LAC_Edit,csKey);
	//pApp->WriteProfileString(csPath,_T("LAC"),csKey);
	//GetDlgItemText(IDC_CellID_Edit,csKey);
	//pApp->WriteProfileString(csPath,_T("CellID"),csKey);
	//GetDlgItemText(IDC_IMEI_Edit,csKey);
	//pApp->WriteProfileString(csPath,_T("IMEI"),csKey);
	//GetDlgItemText(IDC_DateTime_Edit2,csKey);
	//pApp->WriteProfileString(csPath,_T("DateTime"),csKey);
	//GetDlgItemText(IDC_TimeZone_Edit,csKey);
	//pApp->WriteProfileString(csPath,_T("TimeZone"),csKey);
	//GetDlgItemText(IDC_NMR_Edit,csKey);
	//pApp->WriteProfileString(csPath,_T("NMR"),csKey);
	//GetDlgItemText(IDC_LanguageSetting_Edit,csKey);
	//pApp->WriteProfileString(csPath,_T("LanguageSetting"),csKey);
	//GetDlgItemText(IDC_TimingAdvance_Edit,csKey);
	//pApp->WriteProfileString(csPath,_T("TimingAdvance"),csKey);
	//int iCheck = ((CButton*)GetDlgItem(IDC_UseSystemTime_Check2))->GetCheck();
	//pApp->WriteProfileInt(csPath,_T("UseSystemTime"),iCheck);


	//SetDlgItemText(IDC_IMEI_Edit,_T("12345678123456781234567812345678"));
	//SetDlgItemText(IDC_MCCMNC_Edit,_T("64F000"));

	//SetDlgItemText(IDC_LAC_Edit,_T("8549"));
	//SetDlgItemText(IDC_CellID_Edit,_T("0001"));
	//SetDlgItemText(IDC_NMR_Edit,_T("12345678123456781234567812345678"));

	//CString csDis,csDate,csTime;
	//GetSysDate(csDate);
	//GetSysTime(csTime);
	//csDis = csDate+csTime;
	//csDis = csDis.Mid(00,04)+_T("-")+csDis.Mid(04,02)+_T("-")+csDis.Mid(06,02)+_T(" ")+csDis.Mid(0x8,02)+_T(":")+csDis.Mid(10,02)+_T(":")+csDis.Mid(12,02);
	//SetDlgItemText(IDC_DateTime_Edit2,csDis);
	//((CButton*)GetDlgItem(IDC_UseSystemTime_Check2))->SetCheck(TRUE);
	//GetDlgItem(IDC_DateTime_Edit2)->EnableWindow(FALSE);
	//SetDlgItemText(IDC_TimeZone_Edit,_T("00"));

	//SetDlgItemText(IDC_LanguageSetting_Edit,_T("0001"));
	//SetDlgItemText(IDC_TimingAdvance_Edit  ,_T("0001"));

}
// CLocalInformation 消息处理程序


void CLocalInformation::OnBnClickedUsesystemtimeCheck2()
{
	CString csDis;
	CString csDate,csTime;
	if (((CButton*)GetDlgItem(IDC_UseSystemTime_Check2))->GetCheck())
	{
		GetDlgItem(IDC_DateTime_Edit2)->EnableWindow(FALSE);

		GetSysDate(csDate);
		GetSysTime(csTime);
		csDis = csDate+csTime;
		csDis = csDis.Mid(00,04)+_T("-")+csDis.Mid(04,02)+_T("-")+csDis.Mid(06,02)+_T(" ")+csDis.Mid(0x8,02)+_T(":")+csDis.Mid(10,02)+_T(":")+csDis.Mid(12,02);
		SetDlgItemText(IDC_DateTime_Edit2,csDis);
	}
	else
		GetDlgItem(IDC_DateTime_Edit2)->EnableWindow(TRUE);
}
int CLocalInformation::_IsDateTimeFormat(CString csData)
{
	if ((csData.GetLength()>18)&&(csData.Mid(04,1) == _T("-"))&&(csData.Mid(07,1) == _T("-"))&&(csData.Mid(10,1) == _T(" "))&&(csData.Mid(13,1) == _T(":"))&&(csData.Mid(16,1) == _T(":")))
		return TRUE;
	return FALSE;
}
CString CLocalInformation::GetDateTime()
{
	CString csDateTime;
	CString csTimeZone;
	csDateTime.Empty();
	if(!((CButton*)GetDlgItem(IDC_UseSystemTime_Check2))->GetCheck())
	{
		GetDlgItemText(IDC_DateTime_Edit2,csDateTime);
		if (!_IsDateTimeFormat(csDateTime))
			csDateTime.Empty();
	}

	if (csDateTime.IsEmpty())
	{
		CString csDate,csTime;
		GetSysDate(csDate);
		GetSysTime(csTime);
		csDateTime = csDate+csTime;
		csDateTime = csDateTime.Mid(00,04)+_T("-")+csDateTime.Mid(04,02)+_T("-")+
			         csDateTime.Mid(06,02)+_T(" ")+csDateTime.Mid(0x8,02)+_T(":")+
					 csDateTime.Mid(10,02)+_T(":")+csDateTime.Mid(12,02);
	    SetDlgItemText(IDC_DateTime_Edit2,csDateTime);
	}
	
	csDateTime = csDateTime.Mid(2,2)+ csDateTime.Mid(5,2)+ csDateTime.Mid(8,2)+ csDateTime.Mid(11,2)+ csDateTime.Mid(14,2)+ csDateTime.Mid(17,2);
	_ExchangeAt(csDateTime);
	GetDlgItemText(IDC_TimeZone_Edit,csTimeZone);

	return csDateTime+csTimeZone;
}
CString CLocalInformation::GetLocalInforamtion()
{
	CString csMCCMNC,csCellID,csLAC;
	CString csText;

	GetDlgItemText(IDC_MCCMNC_Edit,csMCCMNC);
	GetDlgItemText(IDC_CellID_Edit,csCellID);
	GetDlgItemText(IDC_LAC_Edit,csLAC);
	csText = csMCCMNC+csLAC+csCellID;
	return csText;
}// C:\自写程序\CardManage\CardManage\CardInfomation.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "CardInfomation.h"
#include "afxdialogex.h"


// CCMCCKey 对话框

IMPLEMENT_DYNAMIC(CCMCCKey, CDialogEx)

	CCMCCKey::CCMCCKey(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCMCCKey::IDD, pParent)
{

}

CCMCCKey::~CCMCCKey()
{
}

void CCMCCKey::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CCMCCKey::Initialize_Form()
{
	CString csKey;
	CWinApp * pApp;
	pApp = AfxGetApp();
	CString csPath = _T("Settings\\Keys\\CMCC");

	csKey = pApp->GetProfileString(csPath,_T("RFM0"));
	if (csKey.IsEmpty())
		csKey =_T("D82988A3FBB59A6B7429C911B0E65858");
	SetDlgItemText(IDC_RFM0_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("RFM1"));
	if (csKey.IsEmpty())
		csKey =_T("FE20AA0FADC918ABA3CBD601D9D027F2");
	SetDlgItemText(IDC_RFM1_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("RFM2"));
	if (csKey.IsEmpty())
		csKey =_T("865DA51D9CE035348F834942C6E88EE2");
	SetDlgItemText(IDC_RFM2_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("RFM3"));
	if (csKey.IsEmpty())
		csKey =_T("0E0C60B1F82A741B0D5CE2D29FCD3E24");
	SetDlgItemText(IDC_RFM3_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("RFM4"));
	if (csKey.IsEmpty())
		csKey =_T("46544681A599B3022AB5852A45E93B8C");
	SetDlgItemText(IDC_RFM4_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("K1"));
	if (csKey.IsEmpty())
		csKey =_T("11111111111111111111111111111111");
	SetDlgItemText(IDC_K1_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("KIC"));
	if (csKey.IsEmpty())
		csKey =_T("11223344556677889900112233445566");
	SetDlgItemText(IDC_KIC_Edit,csKey);

}


BEGIN_MESSAGE_MAP(CCMCCKey, CDialogEx)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CCMCCKey 消息处理程序
// C:\自写程序\CardManage\CardManage\CardInfomation.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "CardInfomation.h"
#include "afxdialogex.h"


// CCUCKey 对话框

IMPLEMENT_DYNAMIC(CCUCKey, CDialogEx)

	CCUCKey::CCUCKey(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCUCKey::IDD, pParent)
{

}

CCUCKey::~CCUCKey()
{


}

void CCUCKey::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CCUCKey::Initialize_Form()
{


	CString csKey;
	CWinApp * pApp;
	pApp = AfxGetApp();
	CString csPath = _T("Settings\\Keys\\CUC");

	csKey = pApp->GetProfileString(csPath,_T("RFM0"));
	if (csKey.IsEmpty())
		csKey =_T("D82988A3FBB59A6B7429C911B0E65858");
	SetDlgItemText(IDC_CUCRFM0_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("RFM1"));
	if (csKey.IsEmpty())
		csKey =_T("FE20AA0FADC918ABA3CBD601D9D027F2");
	SetDlgItemText(IDC_CUCRFM1_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("RFM2"));
	if (csKey.IsEmpty())
		csKey =_T("865DA51D9CE035348F834942C6E88EE2");
	SetDlgItemText(IDC_CUCRFM2_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("RFM3"));
	if (csKey.IsEmpty())
		csKey =_T("0E0C60B1F82A741B0D5CE2D29FCD3E24");
	SetDlgItemText(IDC_CUCRFM3_Edit,csKey);

	csKey = pApp->GetProfileString(csPath,_T("RFM4"));
	if (csKey.IsEmpty())
		csKey =_T("46544681A599B3022AB5852A45E93B8C");
	SetDlgItemText(IDC_CUCRFM4_Edit,csKey);



}

BEGIN_MESSAGE_MAP(CCUCKey, CDialogEx)
//	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()




void CCUCKey::OnDestroy()
{
	CString csKey;
	CWinApp * pApp;
	pApp = AfxGetApp();
	CString csPath = _T("Settings\\Keys\\CUC");
	GetDlgItemText(IDC_CUCRFM0_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("RFM0"),csKey);
	GetDlgItemText(IDC_CUCRFM1_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("RFM1"),csKey);
	GetDlgItemText(IDC_CUCRFM2_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("RFM2"),csKey);
	GetDlgItemText(IDC_CUCRFM3_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("RFM3"),csKey);
	GetDlgItemText(IDC_CUCRFM4_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("RFM4"),csKey);
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}
void CCMCCKey::OnDestroy()
{
	CString csKey;
	CWinApp * pApp;
	pApp = AfxGetApp();
	CString csPath = _T("Settings\\Keys\\CMCC");
	GetDlgItemText(IDC_RFM0_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("RFM0"),csKey);
	GetDlgItemText(IDC_RFM1_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("RFM1"),csKey);
	GetDlgItemText(IDC_RFM2_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("RFM2"),csKey);
	GetDlgItemText(IDC_RFM3_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("RFM3"),csKey);
	GetDlgItemText(IDC_RFM4_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("RFM4"),csKey);

	GetDlgItemText(IDC_K1_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("K1"),csKey);

	GetDlgItemText(IDC_KIC_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("KIC"),csKey);

	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}
void CLocalInformation::OnDestroy()
{

	CString csKey;
	CWinApp * pApp;
	pApp = AfxGetApp();
	CString csPath = _T("Settings\\Keys\\LocalInformation");
	GetDlgItemText(IDC_MCCMNC_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("MCCMNC"),csKey);
	GetDlgItemText(IDC_LAC_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("LAC"),csKey);
	GetDlgItemText(IDC_CellID_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("CellID"),csKey);
	GetDlgItemText(IDC_IMEI_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("IMEI"),csKey);
	GetDlgItemText(IDC_DateTime_Edit2,csKey);
	pApp->WriteProfileString(csPath,_T("DateTime"),csKey);
	GetDlgItemText(IDC_TimeZone_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("TimeZone"),csKey);
	GetDlgItemText(IDC_NMR_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("NMR"),csKey);
	GetDlgItemText(IDC_LanguageSetting_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("LanguageSetting"),csKey);
	GetDlgItemText(IDC_TimingAdvance_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("TimingAdvance"),csKey);
	int iCheck = ((CButton*)GetDlgItem(IDC_UseSystemTime_Check2))->GetCheck();
	pApp->WriteProfileInt(csPath,_T("UseSystemTime"),iCheck);

	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}
void CCardKey::OnDestroy()
{

	CString csKey;
	CWinApp * pApp;
	pApp = AfxGetApp();
	CString csPath = _T("Settings\\Keys\\PIN");
	GetDlgItemText(IDC_PIN1_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("PIN1"),csKey);
	GetDlgItemText(IDC_PIN2_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("PIN2"),csKey);
	GetDlgItemText(IDC_PUK1_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("PUK1"),csKey);
	GetDlgItemText(IDC_PUK2_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("PUK2"),csKey);
	GetDlgItemText(IDC_ADM_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("ADM"),csKey);

	GetDlgItemText(IDC_PS_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("PS"),csKey);

	//GetDlgItemText(IDC_KIC_Edit,csKey);
	//pApp->WriteProfileString(csPath,_T("PS"),csKey);

	GetDlgItemText(IDC_ADMCommand_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("ADMCommand"),csKey);

	GetDlgItemText(IDC_PSCommand_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("PSCommand"),csKey);

	int iCheck = ((CButton*)GetDlgItem(IDC_UsePS_Check))->GetCheck();
	pApp->WriteProfileInt(csPath,_T("IsPS"),iCheck);



	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}
void CMilenageForm::OnDestroy()
{
	CString csKey;
	CWinApp * pApp;
	pApp = AfxGetApp();
	CString csPath = _T("Settings\\Keys\\Milenage");
	GetDlgItemText(IDC_KI_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("KI"),csKey);
	GetDlgItemText(IDC_Opc_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("OPc"),csKey);
	GetDlgItemText(IDC_C1_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("C1"),csKey);
	GetDlgItemText(IDC_C2_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("C2"),csKey);
	GetDlgItemText(IDC_C3_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("C3"),csKey);
	GetDlgItemText(IDC_C4_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("C4"),csKey);
	GetDlgItemText(IDC_C5_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("C5"),csKey);

	GetDlgItemText(IDC_R1_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("R1"),csKey);
	GetDlgItemText(IDC_R2_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("R2"),csKey);
	GetDlgItemText(IDC_R3_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("R3"),csKey);
	GetDlgItemText(IDC_R4_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("R4"),csKey);
	GetDlgItemText(IDC_R5_Edit,csKey);
	pApp->WriteProfileString(csPath,_T("R5"),csKey);

	int iCheck = ((CButton*)GetDlgItem(IDC_IsOpc_Check))->GetCheck();
	pApp->WriteProfileInt(csPath,_T("Is OPc"),iCheck);



	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}
