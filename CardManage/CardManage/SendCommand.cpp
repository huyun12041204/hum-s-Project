// SendCommand.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "SendCommand.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// CSendCommand 对话框

IMPLEMENT_DYNAMIC(CSendCommand, CDialogEx)

CSendCommand::CSendCommand(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSendCommand::IDD, pParent)
{

}

CSendCommand::~CSendCommand()
{
}

void CSendCommand::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ComList_Ctrl, m_CommandList_Ctrl);
	DDX_Control(pDX, IDC_Command_File, m_CommandFile_Ctrl);
	DDX_Control(pDX, IDC_Send_Combo, m_SendCombo_Ctrl);
}


BEGIN_MESSAGE_MAP(CSendCommand, CDialogEx)
	ON_BN_CLICKED(IDC_Send_Button,               &CSendCommand::OnBnClickedSendButton)
	ON_BN_CLICKED(IDC_Send2_Button,              &CSendCommand::OnBnClickedSend2Button)
	ON_BN_CLICKED(IDC_Interrupt_Check,           &CSendCommand::OnBnClickedInterruptCheck)
	ON_BN_CLICKED(IDC_Run_Script_Button,         &CSendCommand::OnBnClickedRunScriptButton)
	ON_NOTIFY(NM_CLICK,        IDC_ComList_Ctrl, &CSendCommand::OnNMClickComlistCtrl)
	ON_NOTIFY(NM_DBLCLK,       IDC_Command_File, &CSendCommand::OnNMDblclkCommandFile)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_Command_File, &CSendCommand::OnLvnItemchangedCommandFile)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_DROPFILES()

	ON_BN_CLICKED(IDC_Expain_Button, &CSendCommand::OnBnClickedExpainButton)
END_MESSAGE_MAP()


// CSendCommand 消息处理程序


void CSendCommand::OnBnClickedSendButton()
{
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();

	CSIMToolkit* cToolkit = CurMainFrm->GetSIMToolKit();
	CString csSendCommand;
	CString csResp;
	int iSW;

	//GetDlgItemText(IDC_Send_Edit,csSendCommand);
	GetDlgItemText(IDC_Send_Combo,csSendCommand);

	csResp   = CurMainFrm->_TestCaseSendCommand(csSendCommand);

	if (((CButton*) GetDlgItem(IDC_ContinueSTK_Check))->GetCheck())
	{
		iSW      = _CString2Int(csResp.Right(4));
		while((iSW&0xFF00) == 0x9100)
		{
			cToolkit->SetSTKSW(iSW);
			iSW    = cToolkit->ContinueCurrentSTK();
			csResp = Int2CString(iSW,4);
		}
	}

	
	SetDlgItemText(IDC_Resp_Edit,csResp);


	CString csADD;
	for (int i = 0 ; i< m_SendCombo_Ctrl.GetCount() ; i ++)
	{
		m_SendCombo_Ctrl.GetLBText(i,csADD);

		_DeleteEnterSpace(csADD);
		_DeleteEnterSpace(csSendCommand);
		if (csADD.Compare(csSendCommand) == 0)
			return;
	}

	m_SendCombo_Ctrl.AddString(csSendCommand);
}



// //初始化指令列表
void CSendCommand::InitCommandList(void)
{

	LONG lStyle;
	lStyle = GetWindowLong(m_CommandList_Ctrl.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_LIST; //设置style
	SetWindowLong(m_CommandList_Ctrl.m_hWnd, GWL_STYLE, lStyle);//设置style

	m_CommandList_Ctrl.InsertItem(0,  "SELECT");
	m_CommandList_Ctrl.InsertItem(1,  "SELECT GSM");
	m_CommandList_Ctrl.InsertItem(2,  "SELECT ADF");
	m_CommandList_Ctrl.InsertItem(3,  "VERIFY PIN1");
	m_CommandList_Ctrl.InsertItem(4,  "VERIFY PIN81");
	m_CommandList_Ctrl.InsertItem(5,  "VERIFY ADM");
	m_CommandList_Ctrl.InsertItem(6,  "VERIFY PS");
	m_CommandList_Ctrl.InsertItem(7,  "DISABLE PIN1");
	m_CommandList_Ctrl.InsertItem(8,  "ENABLE PIN1");
	m_CommandList_Ctrl.InsertItem(9,  "UNBLOCK PIN1");
	m_CommandList_Ctrl.InsertItem(10, "READ BINARY");
	m_CommandList_Ctrl.InsertItem(11, "READ RECORD");

	SetDlgItemInt(IDC_InterruptTime_Edit,22000);
	SetDlgItemInt(IDC_SequenceNumber_Edit,02);
}

void CSendCommand::InitCommandFile(void)
{
	LONG lStyle;
	lStyle = GetWindowLong(m_CommandFile_Ctrl.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_LIST; //设置style
	SetWindowLong(m_CommandFile_Ctrl.m_hWnd, GWL_STYLE, lStyle);//设置style
	m_CommandFile_Ctrl.SetExtendedStyle(LVS_EX_CHECKBOXES|m_CommandFile_Ctrl.GetExtendedStyle());
}


void CSendCommand::OnNMClickComlistCtrl(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	//// TODO: 在此添加控件通知处理程序代码
	//*pResult = 0;
	SetAPDU2Edit();


}


void CSendCommand::SetAPDU2Edit()
{
	CString csAPDU;
	CString csTemp;


	CMainFrame* pMain;
	pMain = (CMainFrame*) AfxGetApp()->GetMainWnd();
	csTemp.Empty();

	int iCommandNumber = m_CommandList_Ctrl.GetSelectionMark();

	switch(iCommandNumber)
	{
	case  00:csAPDU= _T("00A40004023F00");break;
	case  01:csAPDU= _T("00A40004027F20");break;
	case  02:
		if (pMain->GetAIDFromApplicationList(csTemp))
			csAPDU = _T("00A40404")+Int2CString(csTemp.GetLength()/2,2)+csTemp;
		else
			csAPDU= _T("00A40004027FF0");break;
		break;
	case  03:
		if (pMain ->GetPINFromKeySetting(csTemp,1))
			csAPDU = _T("00200001")+Int2CString(csTemp.GetLength()/2,2)+csTemp;
		else
			csAPDU= _T("002000010831323334FFFFFFFF");break;
		break;
	case  04:
		if (pMain ->GetPINFromKeySetting(csTemp,0x81))
			csAPDU = _T("00200081")+Int2CString(csTemp.GetLength()/2,2)+csTemp;
		else
			csAPDU= _T("00200081083132333435363738");break;
	case  05:
		if (pMain ->GetPINFromKeySetting(csTemp,0xA))
			csAPDU = _T("0020000A")+Int2CString(csTemp.GetLength()/2,2)+csTemp;
		else
			csAPDU= _T("0020000A083132333435363738");break;
	case  06:
		if (pMain ->GetPINFromKeySetting(csTemp,0xF))
			csAPDU = _T("00170001")+Int2CString(csTemp.GetLength()/2,2)+csTemp;
		else
			csAPDU= _T("00170001083635363330393639");break;
	case  7:
		if (pMain ->GetPINFromKeySetting(csTemp,1))
			csAPDU = _T("00260001")+Int2CString(csTemp.GetLength()/2,2)+csTemp;
		else
			csAPDU= _T("002600010831323334FFFFFFFF");break;
	case  8:
		if (pMain ->GetPINFromKeySetting(csTemp,1))
			csAPDU = _T("00280001")+Int2CString(csTemp.GetLength()/2,2)+csTemp;
		else
			csAPDU= _T("002800010831323334FFFFFFFF");break;
	case  9:
		if (pMain ->GetPINFromKeySetting(csTemp,1))
			csAPDU = _T("002C000110")+csTemp;
		else
			csAPDU = _T("002C00011031323334FFFFFFFF");

		if (pMain ->GetPINFromKeySetting(csTemp,0x91))
			csAPDU = csAPDU+csTemp;
		else
			csAPDU = csAPDU+_T("3132333435363738");break;

	case 10:csAPDU= _T("00B0000001");break;
	case 11:csAPDU= _T("00B2000001");break;
	default:break;
	}
	if (_AppendSpace(csAPDU))
		SetDlgItemText( IDC_Send_Combo,csAPDU);
}

void CSendCommand::OnBnClickedRunScriptButton()
{
	CMainFrame* pMain;
	pMain = (CMainFrame*)AfxGetApp()->GetMainWnd();
	pMain->NewRunSendCommandScriptThread();

}


void CSendCommand::OnLvnItemchangedCommandFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


// 打开并且执行文件
int CSendCommand::OpenFileRunScript(CString csFilePath)
{
	CString csData;
	CFileStatus csSta;
	CStdioFile CSFFile;
	int iRet;

	if (!CSFFile.Open(csFilePath,CFile::shareDenyRead))
		return 0;

	if (!CSFFile.GetStatus(csFilePath,csSta))
	{
		CSFFile.Close();
		return 0;
	}

	do 
	{
		//读取文件内容
		iRet = CSFFile.ReadString(csData);
		if (iRet != FALSE)
		{
			_DeleteNote(csData);
			if (!csData.IsEmpty())
			{
				if (!RunSrcipt(csData))
					break;	
			}
	
		}
	} while (iRet);

	CSFFile.Close();

	if (iRet != FALSE)
		return -1;
	else
		return 1;
	
}

// 通过MainFrame 发送指令
bool CSendCommand::RunSrcipt(CString csSend)
{
	CMainFrame *pMainFrame;
	CString csResp;
	bool bRet;
	pMainFrame =(CMainFrame*)AfxGetApp()->GetMainWnd();


	if (csSend == _T("$0"))
		bRet = pMainFrame->_TestCaseColdReset();
	else
	{
		if (!_IsAllHex(csSend))
			return false;
		csResp = pMainFrame->_TestCaseSendCommand(csSend);
		bRet = (csResp.GetLength()>=4);
	}


	return bRet;


}


// //打开并且运行列表中的脚本
int CSendCommand::OpenRunScriptList(void)
{
	int iRet;
	CString csPath;
	iRet = m_CommandFile_Ctrl.GetItemCount();


	for (int i = 0 ; i < iRet ; i++)
	{
		if (m_CommandFile_Ctrl.GetCheck(i))
		{
			csPath = m_CommandFile_Ctrl.GetItemText(i,0);
			if (OpenFileRunScript(csPath)!= 1)
				return -1;
		}
	}


	return 1;
}


void CSendCommand::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialogEx::OnLButtonDblClk(nFlags, point);

}


void CSendCommand::OnNMDblclkCommandFile(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (!m_CommandFile_Ctrl.DeleteItem(m_CommandFile_Ctrl.GetSelectionMark()))
		MessageBox(_T("删除选项失败"));
	*pResult = 0;
}


//void CSendCommand::OnHdnEnddragCommandFile(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
//	// TODO: 在此添加控件通知处理程序代码
//	*pResult = 0;
//
//	int iFileCount;
////
////	iFileCount = Dragfile
//}


void CSendCommand::OnDropFiles(HDROP hDropInfo)
{

	int iFileCount = DragQueryFile(hDropInfo,-1,NULL,0);

	CString csPath;
	//CString csName;
	int iCounter;

	for (int i = 0 ; i < iFileCount ; i++)
	{
		iCounter =m_CommandFile_Ctrl.GetItemCount();
		DragQueryFile(hDropInfo,i,csPath.GetBuffer(MAX_PATH),MAX_PATH);
		csPath.ReleaseBuffer();
		m_CommandFile_Ctrl.InsertItem(iCounter, csPath);
		m_CommandFile_Ctrl.SetCheck(iCounter);
	}

}


void CSendCommand::OnBnClickedSend2Button()
{
	
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();


	CString csSendCommand;
	CString csResult;
	UINT uiTime,uiNumber;
	GetDlgItemText(IDC_Send_Combo,csSendCommand);

	uiTime  = GetDlgItemInt(IDC_InterruptTime_Edit);
	uiNumber= GetDlgItemInt(IDC_SequenceNumber_Edit);

	_DeleteEnterSpace(csSendCommand);

	csResult = CurMainFrm->_InterruptSend(csSendCommand,uiTime,uiNumber,TRUE,FALSE,NULL);

	SetDlgItemText(IDC_Resp_Edit,csResult);


}


void CSendCommand::OnBnClickedInterruptCheck()
{
	if (((CButton*)GetDlgItem(IDC_Interrupt_Check))->GetCheck())
	{
		GetDlgItem(IDC_InterruptTime_Edit)->EnableWindow(TRUE);
		GetDlgItem(IDC_SequenceNumber_Edit)->EnableWindow(TRUE);
		GetDlgItem(IDC_Send2_Button)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_InterruptTime_Edit)->EnableWindow(FALSE);
		GetDlgItem(IDC_SequenceNumber_Edit)->EnableWindow(FALSE);
		GetDlgItem(IDC_Send2_Button)->EnableWindow(FALSE);
	}
	
	
}


bool CSendCommand::InitContrl(void)
{
	GetDlgItem(IDC_InterruptTime_Edit)->EnableWindow(FALSE);
	GetDlgItem(IDC_SequenceNumber_Edit)->EnableWindow(FALSE);
	GetDlgItem(IDC_Send2_Button)->EnableWindow(FALSE);
	InitCommandList();
	InitCommandFile();
	return true;
}

BOOL CSendCommand::PreTranslateMessage(MSG* pMsg)
{
	if ((pMsg->message == WM_KEYDOWN)&&
		(pMsg->wParam == VK_RETURN))
	{
		int iID = GetFocus()->GetDlgCtrlID() ;
		switch(iID)
		{
		case IDC_Send_Combo:       m_SendCombo_Ctrl.ShowDropDown(TRUE);break;
		case IDC_Send2_Button:     OnBnClickedSend2Button();break;
		case IDC_Send_Button:      OnBnClickedSendButton();break;
		case IDC_ContinueSTK_Check:
		case IDC_Interrupt_Check: ((CButton*)GetDlgItem(iID))->SetCheck(!((CButton* )GetDlgItem(iID))->GetCheck());break;
		case IDC_ComList_Ctrl:     SetAPDU2Edit();break;
		case IDC_Resp_Edit: CDialogEx::PreTranslateMessage(pMsg);break;
		default:
			if (m_SendCombo_Ctrl.GetDroppedState())
				m_SendCombo_Ctrl.ShowDropDown(FALSE);
			else
				m_SendCombo_Ctrl.ShowDropDown(TRUE);
			break;
		}
		

		
		return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);


}


void CSendCommand::OnBnClickedExpainButton()
{
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString csSend, csResp;

	GetDlgItemText(IDC_Send_Combo,csSend);
	GetDlgItemText(IDC_Resp_Edit,csResp);
	_DeleteEnterSpace(csResp);
	if (csResp.GetLength()<4)
		csResp = _T("9000");

	CurMainFrm->_TestCaseExpCommand(csSend,csResp);

}

// ChangeFile.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "SendCommand.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// CChangeFile 对话框

IMPLEMENT_DYNAMIC(CChangeFile, CDialogEx)

	CChangeFile::CChangeFile(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChangeFile::IDD, pParent)
	, iCurrentEF(0)
	, iCurrentMark(0)
{

}


void CChangeFile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FileRecord_Combo, m_FileRecord);
	DDX_Control(pDX, IDC_FileType_Combo, m_FileType);
	DDX_Control(pDX, IDC_FileData_ProGrid, m_FileData_ProGrid);
}


void CChangeFile::Initialize_Control()
{
	m_FileType.ResetContent();
	m_FileType.AddString(_T("Binary"));
	m_FileType.AddString(_T("Record"));
	m_FileType.AddString(_T("Cyclic"));
	m_FileRecord.ResetContent();
	m_FileRecord.EnableWindow(FALSE);
	m_FileType.EnableWindow(FALSE);

	//m_FileData_ProGrid.EnableDescriptionArea(FALSE);
	//m_FileData_ProGrid.EnableHeaderCtrl(FALSE);

	m_FileData_ProGrid.EnableHeaderCtrl(FALSE);
	m_FileData_ProGrid.EnableDescriptionArea();
	m_FileData_ProGrid.SetVSDotNetLook();
	m_FileData_ProGrid.MarkModifiedProperties();
	m_FileData_ProGrid.ModifyStyle(WS_BORDER,WS_CAPTION);
//	m_FileData_ProGrid.ModifyStyle(0,WS_CLIPSIBLINGS);
	//解决滚动条和标题不重绘的问题
	m_FileData_ProGrid.ModifyStyle(0,WS_CLIPCHILDREN);

	HDITEM Item1;
	Item1.cxy = 120;
	Item1.mask = HDI_WIDTH;
	m_FileData_ProGrid.GetHeaderCtrl().SetItem(0,new HDITEM(Item1));

	//iCurrentEF   = 0;
	//iCurrentMark = _DEF_Card;


}



BEGIN_MESSAGE_MAP(CChangeFile, CDialogEx)
	ON_BN_CLICKED(IDOK,                            &CChangeFile::OnBnClickedOk)
	ON_BN_CLICKED(IDC_2Right_Button,               &CChangeFile::OnBnClicked2rightButton)
	ON_BN_CLICKED(IDC_2Left_Button,                &CChangeFile::OnBnClicked2leftButton)
	ON_EN_KILLFOCUS(IDC_FileData_Eidt,             &CChangeFile::OnEnKillfocusFiledataEidt)
	ON_EN_CHANGE(IDC_FileData_Eidt,                &CChangeFile::OnEnChangeFiledataEidt)
	ON_CBN_SELCHANGE(IDC_FileRecord_Combo,         &CChangeFile::OnCbnSelchangeFilerecordCombo)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, &CChangeFile::OnPropertyChanged)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CChangeFile 消息处理程序


void CChangeFile::OnApplicationLook(UINT id)
{
	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		m_FileData_ProGrid.SetCustomColors(((COLORREF)-1) ,((COLORREF)-1) ,RGB(206,212,225),RGB(106,112,128) ,RGB(206,212,225) ,((COLORREF)-1), RGB(206,212,225));
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		m_FileData_ProGrid.SetCustomColors(((COLORREF)-1) ,((COLORREF)-1) ,RGB(206,212,225),RGB(106,112,128) ,RGB(206,212,225) ,((COLORREF)-1), RGB(206,212,225));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		m_FileData_ProGrid.SetCustomColors(((COLORREF)-1) ,((COLORREF)-1) ,RGB(206,212,225),RGB(106,112,128) ,RGB(206,212,225) ,((COLORREF)-1), RGB(206,212,225));
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		m_FileData_ProGrid.SetCustomColors(((COLORREF)-1) ,((COLORREF)-1) ,RGB(206,212,225),RGB(106,112,128) ,RGB(206,212,225) ,((COLORREF)-1), RGB(206,212,225));
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		m_FileData_ProGrid.SetCustomColors(((COLORREF)-1) ,((COLORREF)-1) ,RGB(206,212,225),RGB(106,112,128) ,RGB(206,212,225) ,((COLORREF)-1), RGB(206,212,225));
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		m_FileData_ProGrid.SetCustomColors(((COLORREF)-1) ,((COLORREF)-1) ,RGB(206,212,225),RGB(106,112,128) ,RGB(206,212,225) ,((COLORREF)-1), RGB(206,212,225));
		break;
	case ID_VIEW_APPLOOK_WINDOWS_7:
		m_FileData_ProGrid.SetCustomColors(((COLORREF)-1) ,((COLORREF)-1) ,RGB(206,212,225),RGB(106,112,128) ,RGB(206,212,225) ,((COLORREF)-1), RGB(206,212,225));
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			m_FileData_ProGrid.SetCustomColors(((COLORREF)-1) ,((COLORREF)-1) ,RGB(213,228,242),RGB(157,189,216) ,RGB(213,228,242),((COLORREF)-1) ,RGB(213,228,242));
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			m_FileData_ProGrid.SetCustomColors(((COLORREF)-1) ,((COLORREF)-1) ,RGB(235,235,235),RGB(129,129,129) ,RGB(235,235,235) ,((COLORREF)-1) ,RGB(235,235,235));
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			m_FileData_ProGrid.SetCustomColors(((COLORREF)-1) ,((COLORREF)-1) ,RGB(233,238,247),RGB(124,124,124) ,RGB(233,238,247) ,((COLORREF)-1) ,RGB(233,238,247));
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			m_FileData_ProGrid.SetCustomColors(((COLORREF)-1) ,((COLORREF)-1) ,RGB(206,212,225),RGB(106,112,128) ,RGB(206,212,225) ,((COLORREF)-1), RGB(206,212,225));
			break;
		}
	}


}


void CChangeFile::SetFileData(CString csFCI,CString csData)
{
	CString csResult;
	CString csFileInformation,csFileType;
	CString csTemp;
	int iFileNumber;


	csFileValue.Empty();


	csFCI               = GetTLVData(csFCI,0x62);
	csFileInformation   = GetTLVData(csFCI,0x82);
	csFileType          = csFileInformation.Mid(00,02);
	iFileType           = _CString2Int(csFileType);
	csFileValue         = csData;

	switch(iFileType&0x7)
	{
	case 01:

		m_FileType.SetCurSel(0);
		m_FileRecord.EnableWindow(FALSE);
		//SetDlgItemText(IDC_FileData_Eidt,csData);
		iRecordLen = csData.GetLength()/2;
		csTemp = csData;
		break;
	case 02:
	case 06:

		if ((iFileType&0x7) == 2)
			m_FileType.SetCurSel(1);
		else
			m_FileType.SetCurSel(2);

		iFileNumber = _CString2Int(csFileInformation.Mid(0x8 ,02));
		iRecordLen  = _CString2Int(csFileInformation.Mid(04 ,04));

		for(int iCyc = 0 ; iCyc < iFileNumber; iCyc++)
		{
			csTemp.Format("%d",iCyc+1);
			m_FileRecord.AddString(csTemp);
		}
		m_FileRecord.SetCurSel(0);
		m_FileRecord.EnableWindow(TRUE);


		csTemp = csFileValue.Mid(0,iRecordLen*2);


		//OnCbnSelchangeFilerecordCombo();
		break;
	default:
		break;
	}

	//_AppendEnter(csTemp);
	_AppendSpace(csTemp);
	//_AppendSign(csTemp,"\r",24);
	SetDlgItemText(IDC_FileData_Eidt,csTemp);
	OnBnClicked2rightButton();
}

void CChangeFile::_SetFileData(CString csFCI,CString csData)
{
	CString csFileStru,csTemp;

	int iSize,iRecLen,iRecNum;

	csFileStru = csFCI.Mid(26,02);

	iSize      = _CString2Int(csFCI.Mid(04,04));

	csFileValue  = csData;
	switch(_CString2Int(csFileStru))
	{
	case 00:

		iFileType = 01;
		m_FileType.SetCurSel(0);
		m_FileRecord.EnableWindow(FALSE);
		//SetDlgItemText(IDC_FileData_Eidt,csData);
		iRecordLen = csData.GetLength()/2;

		csTemp = csData;

		break;
	case 01:
	case 03:
		iRecLen    = _CString2Int(csFCI.Mid(28,04));
		iRecNum    = iSize / iRecLen;
		iRecordLen = iRecLen;


		if (_CString2Int(csFileStru) == 01)
		{
			iFileType = 02;
			m_FileType.SetCurSel(1);
		}
		else
		{
			iFileType = 06;
			m_FileType.SetCurSel(2);
		}
		for(int iCyc = 0 ; iCyc < iRecNum; iCyc++)
		{
			csTemp.Format("%d",iCyc+1);
			m_FileRecord.AddString(csTemp);
		}
		m_FileRecord.SetCurSel(0);
		m_FileRecord.EnableWindow(TRUE);

		csTemp = csData.Mid(0,iRecLen*2);


		//SetDlgItemText(IDC_FileData_Eidt,csData.Mid(0,iRecLen*2));
		break;
	default:
		break;

	}


	//_AppendEnter(csTemp);
	_AppendSpace(csTemp);
//	_AppendSign(csData,"\r",24);
	SetDlgItemText(IDC_FileData_Eidt,csTemp);

	OnBnClicked2rightButton();

}

void CChangeFile::OnBnClickedOk()
{
	int iRet,iNumber;
	bool bRet;
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CString csUpdate;

	iRet = GetDlgItemText(IDC_FileData_Eidt
		,csUpdate);

	if (!iRet)
		return;

	switch(iFileType&0x7)
	{	
	case 01:

		bRet = CurMainFrm->_TestCaseUpdateBinaryData(csUpdate,CurMainFrm->bIsUICC);

		break;
	case 02:

		iNumber = m_FileRecord.GetCurSel()+1;

		bRet = CurMainFrm->_TestCaseUpdateRecordData(iNumber,csUpdate,CurMainFrm->bIsUICC);

		break;

	case 06:

		iNumber = m_FileRecord.GetCurSel();

		iRet    = csFileValue.GetLength();

		csFileValue = csFileValue.Left(iNumber*iRecordLen*2) + csUpdate + csFileValue.Right(iRet -(iNumber+1)*iRecordLen*2);

		bRet = CurMainFrm-> _TestCaseUpdateCycLicData(csFileValue,iRecordLen,m_FileRecord.GetCount(),CurMainFrm->bIsUICC);

		break;

	default:
		break;
	}

	if (!bRet)
		MessageBox(_T("文件更新失败"));
	else
	{
		MessageBox(_T("文件更新成功"));
		//CurMainFrm->CklClassViewTree(NULL);
		iRet = m_FileRecord.GetCurSel();
		CurMainFrm->Changefilevalue();
		m_FileRecord.SetCurSel(iRet);
		OnCbnSelchangeFilerecordCombo();
		OnBnClicked2rightButton();
		

	}



	//CDialogEx::OnOK();
}

void CChangeFile::OnEnKillfocusFiledataEidt()
{
	FormatEdit(IDC_FileData_Eidt,iRecordLen*2);
}

void CChangeFile::FormatEdit(int iContrlID,int iEditLen)
{

	CString csData;
	CString csPadding;

	int iInputLen;

	csPadding = _T("F");

	iInputLen = GetDlgItemText(iContrlID,csData);

	_DeleteEnterSpace(csData);

	iInputLen = csData.GetLength();

	if (iInputLen == 0)
		return;
	if (iInputLen < iEditLen)
	{
		do 
		{
			csData = csData + csPadding;

		} while (csData.GetLength() < iEditLen);

	}

//	_AppendEnter(csData);
	_AppendSpace(csData);
	//_AppendSign(csData,"\r",24);
	SetDlgItemText(iContrlID,csData);
}

void CChangeFile::OnCbnSelchangeFilerecordCombo()
{
	CString csCurrentRecord;

	csCurrentRecord = csFileValue.Mid(m_FileRecord.GetCurSel()*iRecordLen*2,iRecordLen*2);
	_AppendSpace(csCurrentRecord);
	SetDlgItemText(IDC_FileData_Eidt,csCurrentRecord);
	ExplainFileRecord(csCurrentRecord);

}

void CChangeFile::ExplainFileRecord(CString csRecord )
{
	CMFCPropertyGridProperty *pGroup;

	m_FileData_ProGrid.RemoveAll();
	_DeleteEnterSpace(csRecord);
	pGroup = Explain_FileData(csRecord,iCurrentEF,iCurrentMark);

	if (pGroup != NULL)
		m_FileData_ProGrid.AddProperty(pGroup);


}

void CChangeFile::SetCurrentFileInformation(int iEFFID, int iDFMark)
{
	 iCurrentEF   = iEFFID;
	 iCurrentMark = iDFMark;

	 if (iCurrentEF == NULL)
	 {
		 SetFileEmpty();
		 SetDlgItemText(IDC_File_Path_Text,"-");
		 SetDlgItemText(IDC_File_Name_Group,"-");
	 }
	 else
	 {
		 CString csFID;
		 csFID.Empty();
		 _Int2CString(iEFFID,csFID,4);
		 if (!csFID.IsEmpty())
			 SetDlgItemText(IDC_File_Path_Text,csFID);
		 CString csFileName;
		 csFileName.Empty();
		 //if ((!Try2GenerateFileName    (iDFMark,iEFFID,csFileName,false))&&
			// (!GetFileNameFromReference(iEFFID,iDFMark,csFileName,false)))
		 if(!GetFileNameFromReference(iEFFID,iDFMark,csFileName,false))
			 csFileName = csFID;
		 SetDlgItemText(IDC_File_Name_Group,csFileName);
	 }



}
	
void CChangeFile::SetFileEmpty()
{
	csFileValue.Empty();
	SetDlgItemText(IDC_FileData_Eidt,csFileValue);
	m_FileRecord.EnableWindow(FALSE);
	m_FileType  .EnableWindow(FALSE);
	m_FileData_ProGrid.RemoveAll();
}

void CChangeFile::OnEnChangeFiledataEidt()
{


}

// SearchFile.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "SendCommand.h"
#include "afxdialogex.h"

#include "MainFrm.h"

// CSearchFile 对话框

IMPLEMENT_DYNAMIC(CSearchFile, CDialogEx)

	CSearchFile::CSearchFile(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSearchFile::IDD, pParent)
{

}

void CSearchFile::InstallCurrentPath(CString csPath,HTREEITEM bCurrentItem)
{
	bSearchItem = bCurrentItem;
	SetDlgItemText(IDC_CurrentPath_Edit,csPath);
	GetDlgItem(IDC_CurrentPath_Edit)->EnableWindow(FALSE);
}

void CSearchFile::InstallSearchFile(bool bSure)
{
	bSearch = bSure;
	bAddTreeList = false;
	GetDlgItem(IDC_StartFile_Edit)->ShowWindow(true);
	GetDlgItem(IDC_EndFile_Edit)->EnableWindow(bSure);
	GetDlgItem(IDC_EndFile_Edit)->ShowWindow(bSure);
	GetDlgItem(IDC_STATIC4)->ShowWindow(bSure);
	GetDlgItem(IDC_AddFile_Edit)->ShowWindow(false);
	if (bSure)
		SetDlgItemText(IDC_STATIC3,_T("搜索范围"));
	else
		SetDlgItemText(IDC_STATIC3,_T("找寻文件"));


	GetDlgItem(IDC_StartFile_Edit)->SetFocus();
}

void CSearchFile::FormatEdit(int iContrlID,int iEditLen)
{

	CString csData;
	CString csPadding;

	int iInputLen;

	csPadding = _T("F");

	iInputLen = GetDlgItemText(iContrlID,csData);

	_DeleteEnterSpace(csData);

	iInputLen = csData.GetLength();

	if (iInputLen == 0)
		return;
	if (iInputLen < iEditLen)
	{
		do 
		{
			csData = csData + csPadding;

		} while (csData.GetLength() < iEditLen);

	}
	else
		csData.Left(iEditLen);

	SetDlgItemText(iContrlID,csData);
}

void CSearchFile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSearchFile, CDialogEx)
	ON_EN_CHANGE   (IDC_StartFile_Edit, &CSearchFile::OnEnChangeStartfileEdit)
	ON_EN_KILLFOCUS(IDC_StartFile_Edit, &CSearchFile::OnEnKillfocusStartfileEdit)
	ON_BN_CLICKED  (IDOK,               &CSearchFile::OnBnClickedOk)

END_MESSAGE_MAP()


// CSearchFile 消息处理程序


void CSearchFile::OnEnChangeStartfileEdit()
{

	CString csData;

	GetDlgItemText(IDC_StartFile_Edit,csData);
	if (csData.GetLength() >= 2 )
		csData = csData.Left(02)+_T("FF");
	SetDlgItemText(IDC_EndFile_Edit,csData);
}


void CSearchFile::OnEnKillfocusStartfileEdit()
{

}


void CSearchFile::OnBnClickedOk()
{

	CMainFrame *CurMainFrm;


	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();

	CString csFile;



	if (!bAddTreeList)
	{
		GetDlgItemText(IDC_StartFile_Edit,csFile);
		iStart = _CString2Int(csFile);
		GetDlgItemText(IDC_EndFile_Edit,csFile);
		iEnd = _CString2Int(csFile);


		CurMainFrm->NewSearchFileThread();
		CurMainFrm->NewSetStatusThread();
	}
	else
	{
		GetDlgItemText(IDC_AddFile_Edit,csFile);
		CurMainFrm->InsatllFile2ClassTree(csFile,_T(""),iAddDir);
	}
	CDialogEx::OnOK();
}

CString CSearchFile::GetSearchDF()
{

	CString csData;
	GetDlgItemText(IDC_CurrentPath_Edit,csData);
	return csData;
}

void CSearchFile::InstallClassTree(int iDIR)
{
	bAddTreeList = true;

	iAddDir        = iDIR;

	GetDlgItem(IDC_EndFile_Edit)->EnableWindow(false);
	GetDlgItem(IDC_EndFile_Edit)->ShowWindow(false);
	GetDlgItem(IDC_StartFile_Edit)->ShowWindow(false);
	GetDlgItem(IDC_STATIC4)->ShowWindow(false);

	SetDlgItemText(IDC_STATIC3,_T("添加文件"));
	GetDlgItem(IDC_AddFile_Edit)->ShowWindow(true);
	GetDlgItem(IDC_AddFile_Edit)->SetFocus();
}

void CChangeFile::OnBnClicked2rightButton()
{
	CString csRecord;

	GetDlgItemText(IDC_FileData_Eidt,csRecord);
	
	ExplainFileRecord(csRecord);

	//m_FileData_ProGrid.RedrawWindow();
}

void CChangeFile::OnBnClicked2leftButton()
{
	CString csRecord;


	if (ComplileFileData(m_FileData_ProGrid.GetProperty(0),iCurrentEF,iCurrentMark,csRecord,&iRecordLen))
	{
		SetDlgItemText(IDC_FileData_Eidt,csRecord);
		FormatEdit(IDC_FileData_Eidt,iRecordLen*2);
	}
	else
	{
		//MessageBox("There are some errors in data");
	}
}


afx_msg LRESULT CChangeFile::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{

//	GetOwner()->SendMessage(AFX_WM_PROPERTY_CHANGED,wParam, lParam);

	return ExcutePropertyChanged(wParam,lParam);
}
int CChangeFile::GetPropertyCourtPath(CMFCPropertyGridProperty* lParam,BYTE* ucPath)
{
	int iLen;
	CMFCPropertyGridCtrl *PropCtrl;
	CMFCPropertyGridProperty* lParent[10];
	int iSum;

	lParent [0] = lParam;
	PropCtrl = &m_FileData_ProGrid;
	for (iLen = 1 ; iLen < 10 ; iLen += 1)
	{
		lParent[iLen] = lParent[iLen-1]->GetParent();
		if (lParent[iLen] == NULL)
			break;
	}

	iSum = PropCtrl->GetPropertyCount();

	for (int j = 0 ; j < iSum ;j ++)
	{

		if (m_FileData_ProGrid.GetProperty(j) == lParent[iLen-1])
			ucPath[0] = j; break; 
	}

	for (int i = 1 ;i  < iLen ; i ++)
	{
		iSum = lParent[iLen-i]->GetSubItemsCount();
		for (int k = 0 ; k < iSum ; k++)
		{
			if (lParent[iLen-i]->GetSubItem(k) == lParent[iLen-1-i]  )
				ucPath[i] = k;
		}
	}

	return iLen;
}
int CChangeFile::ExcutePropertyChanged(WPARAM wParam, LPARAM lParam)
{
	int iRet =0;
	switch(iCurrentEF)
	{
	case 0x4F30:
		if (iCurrentMark == _DEF_PHONEBOOK) 
			iRet = ExcutePBRChanged( wParam,  lParam);
	}

	return 0;
}

int CChangeFile::ExcutePBRChanged(WPARAM wParam, LPARAM lParam)
{
	CMFCPropertyGridProperty* pGropTemp[3];
	CString csTempFID1,csTempSFI1;
	CString csTempFID2,csTempSFI2;

	//Type1 SNE
	pGropTemp[0] = m_FileData_ProGrid.GetProperty(0)->GetSubItem(0)->GetSubItem(2);
	pGropTemp[1] = m_FileData_ProGrid.GetProperty(0)->GetSubItem(1)->GetSubItem(0);

	csTempFID1 = pGropTemp[0]->GetSubItem(0)->GetValue();
	csTempSFI1 = pGropTemp[0]->GetSubItem(1)->GetValue();
	csTempFID2 = pGropTemp[1]->GetSubItem(0)->GetValue();
	csTempSFI2 = pGropTemp[1]->GetSubItem(1)->GetValue();


	if (csTempFID1.IsEmpty()&&csTempSFI1.IsEmpty()&&csTempFID2.IsEmpty()&&csTempSFI2.IsEmpty() )
	{
		EnableProperty(pGropTemp[0],TRUE);
		EnableProperty(pGropTemp[1],TRUE);
	}
	else if(csTempFID1.IsEmpty()&&csTempSFI1.IsEmpty())
	{
		EnableProperty(pGropTemp[0],FALSE);
		EnableProperty(pGropTemp[1],TRUE);
	}
	else if(csTempFID2.IsEmpty()&&csTempSFI2.IsEmpty())
	{
		EnableProperty(pGropTemp[1],FALSE);
		EnableProperty(pGropTemp[0],TRUE);
	}




	

	//Type1 ANR
	pGropTemp[0] = m_FileData_ProGrid.GetProperty(0)->GetSubItem(0)->GetSubItem(3);
	pGropTemp[1] = m_FileData_ProGrid.GetProperty(0)->GetSubItem(1)->GetSubItem(1);

	csTempFID1 = pGropTemp[0]->GetSubItem(0)->GetValue();
	csTempSFI1 = pGropTemp[0]->GetSubItem(1)->GetValue();
	csTempFID2 = pGropTemp[1]->GetSubItem(0)->GetValue();
	csTempSFI2 = pGropTemp[1]->GetSubItem(1)->GetValue();


	if (csTempFID1.IsEmpty()&&csTempSFI1.IsEmpty()&&csTempFID2.IsEmpty()&&csTempSFI2.IsEmpty() )
	{
		EnableProperty(pGropTemp[0],TRUE);
		EnableProperty(pGropTemp[1],TRUE);
	}
	else if(csTempFID1.IsEmpty()&&csTempSFI1.IsEmpty())
	{
		EnableProperty(pGropTemp[0],FALSE);
		EnableProperty(pGropTemp[1],TRUE);
	}
	else if(csTempFID2.IsEmpty()&&csTempSFI2.IsEmpty())
	{
		EnableProperty(pGropTemp[1],FALSE);
		EnableProperty(pGropTemp[0],TRUE);
	}


	//Type1 Email
	pGropTemp[0] = m_FileData_ProGrid.GetProperty(0)->GetSubItem(0)->GetSubItem(7);
	pGropTemp[1] = m_FileData_ProGrid.GetProperty(0)->GetSubItem(1)->GetSubItem(2);
	
	csTempFID1 = pGropTemp[0]->GetSubItem(0)->GetValue();
	csTempSFI1 = pGropTemp[0]->GetSubItem(1)->GetValue();
	csTempFID2 = pGropTemp[1]->GetSubItem(0)->GetValue();
	csTempSFI2 = pGropTemp[1]->GetSubItem(1)->GetValue();


	if (csTempFID1.IsEmpty()&&csTempSFI1.IsEmpty()&&csTempFID2.IsEmpty()&&csTempSFI2.IsEmpty() )
	{
		EnableProperty(pGropTemp[0],TRUE);
		EnableProperty(pGropTemp[1],TRUE);
	}
	else if(csTempFID1.IsEmpty()&&csTempSFI1.IsEmpty())
	{
		EnableProperty(pGropTemp[0],FALSE);
		EnableProperty(pGropTemp[1],TRUE);
	}
	else if(csTempFID2.IsEmpty()&&csTempSFI2.IsEmpty())
	{
		EnableProperty(pGropTemp[1],FALSE);
		EnableProperty(pGropTemp[0],TRUE);
	}
	return 0;
}

void CChangeFile::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
}






void CChangeFile::UpdateFonts(void)
{

	//GetDlgItem(IDC_FileData_Eidt)->SetFont(&afxGlobalData.fontRegular);
}


void CChangeFile::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rectTree;
	//m_ListBox.GetWindowRect(rectTree);

	GetWindowRect(rectTree);
	//m_AppcationList.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}


HBRUSH CChangeFile::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
