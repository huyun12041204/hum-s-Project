// SIMToolkit.cpp : 实现文件
//

#include "stdafx.h"

#include "CardManage.h"
#include "SIMToolkit.h"
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
				csName = TransationASC(csItem.Mid(02,csItem.GetLength()-02));
			else
				csName = TransationUCS2(csItem.Mid(04,csItem.GetLength()-04));


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

int  CSIMToolkit::GetItemID(int iNum,CString csFetch)
{
	csFetch = _GetTLVData(csFetch,0xD0);
	if (csFetch.IsEmpty())
		return -1 ;

	csFetch = _GetTLVData(csFetch,0x8F,iNum);

	if (csFetch.IsEmpty())
		return -2 ;


	return CString2Int( csFetch.Left(02));
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
	csFetch = _GetTLVData(csFetch,0xD0);
	if (csFetch.IsEmpty())
		return iNumber;
	iOffset = 0 ;
	iLen    = csFetch.GetLength();
	do 
	{
		iFirstTag = CString2Int(csFetch.Mid(iOffset,02));

		iOffset   += _GetTLVData(csFetch.Mid(iOffset,iLen-iOffset),iFirstTag).GetLength();
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
	csFetch = _GetTLVData(csFetch,0xD0);
	if (csFetch.IsEmpty())
		return csTemp;
	iOffset = 0 ;
	iLen    = csFetch.GetLength();
	do 
	{

		iFirstTag = CString2Int(csFetch.Mid(iOffset,02));

		csTemp    =_GetTLVData(csFetch.Mid(iOffset,iLen-iOffset),iFirstTag); 

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

	csFetch = _GetTLVData(csCurrentFetch,0xD0);

	csFetch= _GetTLVData(csFetch,0x81);

	return CString2Int(csFetch);
}

int CSIMToolkit::_DisplayText(CString csText)
{
	CString csDCS;
	CString csResult;

	csDCS = csText.Left(02);

	switch(CString2Int(csDCS))
	{
	case 0x08:
		csResult = TransationUCS2(csText.Mid(02,csText.GetLength()-02));
		break;


	case 0x04:
		csResult = TransationASC(csText.Mid(02,csText.GetLength()-02));
		break;

	case 0x00:
		csResult = Transation7bit(csText.Mid(02,csText.GetLength()-02));
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

	switch(CString2Int(csDCS))
	{
	case 0x80:
	
		csAlphaId = TransationUCS2(csAlphaId);
		break;
	case 0x04:
		csAlphaId = TransationASC(csAlphaId);
		break;
	default:
		csAlphaId = TransationASC(csAlpha);
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

	switch(CString2Int(csDCS))
	{
	case 0x08:

		csInputData = csInput.Mid(2,csInput.GetLength()-2);
		csInputData = TransationUCS2(csInputData);

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
	csPSIMC = _GetTLVData(csCurrentFetch,0xD0);
	if (csPSIMC.IsEmpty())
		return 0;
	csTemp = _GetTLVData(csPSIMC,0x91);
	if (csTemp.IsEmpty())
		csTemp = _GetTLVData(csPSIMC,0x11);

	if (csTemp.IsEmpty())
		return 0;


	*iMin = CString2Int(csTemp.Mid(0,2));
	*iMax = CString2Int(csTemp.Mid(2,2));

	return 1;
}


int CSIMToolkit::ContinueCurrentSTK()
{
	int iResult;
	CString csAdd;
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
		else 
			return iRet;

		
		

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

	csPSIMC = _GetTLVData(csFetch ,0xD0);

	GetDlgItem(IDC_Alpha_Edit)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_Text_Edit)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_Input_Edit)->ShowWindow(SW_HIDE);
	m_Menu_Listbox.ResetContent();


	if (csPSIMC.IsEmpty())
		return -1;

	csTemp = _GetTLVData(csPSIMC,0x0D);
	if (!csTemp.IsEmpty())
		_DisplayText(csTemp);
	csTemp = _GetTLVData(csPSIMC,0x8D);
	if (!csTemp.IsEmpty())
		_DisplayText(csTemp);


	csTemp = _GetTLVData(csPSIMC,0x05);
	if (!csTemp.IsEmpty())
		_DisplayAlpha(csTemp);
	csTemp = _GetTLVData(csPSIMC,0x85);
	if (!csTemp.IsEmpty())
		_DisplayAlpha(csTemp);

	if((!_GetTLVData(csPSIMC,0x8F).IsEmpty()) ||(!_GetTLVData(csPSIMC,0x0F).IsEmpty()))
		InstallMenu(csFetch);

	csTemp = _GetTLVData(csPSIMC,0x17);
	if (!csTemp.IsEmpty())
		_DisplayInput(csTemp);
	csTemp = _GetTLVData(csPSIMC,0x97);
	if (!csTemp.IsEmpty())
		_DisplayInput(csTemp);




	return 0;
}

int CSIMToolkit::GenerateTerminal(int iDetails,int* iResult, CString& csADD)
{
	int iRet;

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
			csADD    = _T("14080000000000000000");
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

		csData =  ConvertUCS2(csData);

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
			csData = ConvertASC(csData);
			iLen = csData.GetLength()/2;
			csData=  _T("04")+csData;
		}	
	}



	if ((iLen < iMin)||(iLen >iMax))
		return 0;

	iRet = ContinueCurrentTerminalResponse(iDes,00,_GenerateTLVData(csData,0x0D));


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

		csData =  ConvertUCS2(csData);

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
			csData = ConvertASC(csData);

			csData=  _T("04")+csData;
		}	
	}


	iRet = ContinueCurrentTerminalResponse(iDes,00,_GenerateTLVData(csData,0x0D));


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
