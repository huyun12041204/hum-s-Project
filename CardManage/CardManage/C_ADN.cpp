// C_ADN.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "C_ADN.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// C_ADN 对话框

IMPLEMENT_DYNAMIC(C_ADN, CDialogEx)

C_ADN::C_ADN(CWnd* pParent /*=NULL*/)
	: CDialogEx(C_ADN::IDD, pParent)
	, bLocalPhoneBook(0)
{

}

C_ADN::~C_ADN()
{
}

void C_ADN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Phonebook_List, m_PhoneBook_List);
}


BEGIN_MESSAGE_MAP(C_ADN, CDialogEx)
END_MESSAGE_MAP()


// 初始化参数


void C_ADN::InitParameter(void)
{
	//一般读取 7F10下的号簿
	bLocalPhoneBook = false;

	//遵循 3GPP 的规范
	iPhoneBookType         = _DEF_PhoneBook_3GPP;

}
// 初始化各个控件
void C_ADN::InitContrl(void)
{

	LONG lStyle;
	lStyle = GetWindowLong(m_PhoneBook_List.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
//	lStyle |= LVS_LIST; //设置style
	SetWindowLong(m_PhoneBook_List.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_PhoneBook_List.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
//	dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	m_PhoneBook_List.SetExtendedStyle(dwStyle); //设置扩展风格
	int iRet;
	iRet = m_PhoneBook_List.InsertColumn( 0, "Record", LVCFMT_CENTER, 50);
	iRet =m_PhoneBook_List.InsertColumn( 1, "First Alpha", LVCFMT_CENTER, 100);//插入列
	iRet =m_PhoneBook_List.InsertColumn( 2, "Dialling Numbers", LVCFMT_CENTER, 150);//插入列

	//iRet =m_PhoneBook_List.InsertColumn( 3, "Second Name", LVCFMT_LEFT, 132);//插入列
	//iRet =m_PhoneBook_List.InsertColumn( 4, "Additional Number", LVCFMT_LEFT, 132);//插入列
	//iRet =m_PhoneBook_List.InsertColumn( 5, "Email", LVCFMT_LEFT, 132);//插入列	

	
//	m_PhoneBook_List.SetItemText(m_PhoneBook_List.InsertItem(1,_T("1")), 1, _T("123456"));
	//iRet =m_PhoneBook_List.EnableWindow(FALSE);

}


// 获取MainFrame 并且给 卡片发送指令， 相关参数按照MainFrame 里处理 发送成功返回9000 ， 其他根据卡片实际返回， 如果失去响应返回0
int C_ADN::GetHandle2SendCommand(CString csSend, CString& csResp)
{
	int iRet;
	extern int  iThread;
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();

	if (iThread == Def_Thread_Ending)
		return 0;


	csResp = CurMainFrm->_TestCaseSendCommand(csSend);

	if (csResp.GetLength() < 4)
		iRet = 0;
	else
		iRet = CString2Int(csResp.Right(04));
	return iRet;
}




// //选中号簿的初始目录 返回值详情 See funcation GetHandle2SendCommand
int C_ADN::_SelectPhoneBookDF_3GPP(void)
{
	CString csResp;
	int iRet;

	csResp.Empty();
	iRet  = 0;
	if (bLocalPhoneBook)
		//选中3GPP 目录
		iRet  =  GetHandle2SendCommand(_T("00A4040C05A000000087"),csResp);
	else
		iRet  =  GetHandle2SendCommand(_T("00A4000C027F10"),csResp);

	//此处容易出现91xx的情况
	if ((iRet& 0xF000) == 0x9000)
		iRet  =  GetHandle2SendCommand(_T("00A4000C025F3A"),csResp);

	return iRet;
}


// 必须保证当前目录为 PhoneBook 情况下，参能正常执行，返回 如上
int C_ADN::_SelectPBREF_3GPP(CString& csResp)
{
	int iRet  =  GetHandle2SendCommand(_T("00A40004024F30"),csResp);

	iRet  =  GetHandle2SendCommand(_T("00C00000")+Int2CString(iRet&0xFF,2),csResp);

	return iRet;
}


// 读取 pbr 文件 获取 ADN 文件的 FID 返回 FID 的总数
int C_ADN::_GetADNFile_Signt(CString& csFIDList,int iRecNum,int iRecLen)
{
	CString csResp;
	int iRet;

	iRet = 0;
	csFIDList.Empty();
	for (int i = 1 ; i <= iRecNum ; i ++)
	{
	
		csResp.Empty();
		if (GetHandle2SendCommand(_T("00B2")+Int2CString(i,2)+_T("04")+Int2CString(iRecLen,2),csResp) != 0x9000)
			return 0;

		csResp = _GetTLVData(csResp,0xA8);
		if (!csResp.IsEmpty())
		{
			csResp = _GetTLVData(csResp,0xC0);
			if (!csResp.IsEmpty())
			{
				csFIDList += csResp.Left(4);
				iRet      += 1;
			}
		}
	}
	return iRet;
}


int C_ADN::WriteTestADN(void)
{
	int iRet;
	switch(iPhoneBookType)
	{
	case _DEF_PhoneBook_3GPP: iRet = WriteTestADN_3GPP();break;
	case _DEF_PhoneBook_GSM:	 iRet  = WriteTestADN_GSM();break;
	}

	return iRet;
}

int C_ADN::WriteTestADN_3GPP(void)
{

	int iRet,iADNFileNum,iADNNum,iADNSum,iADNLen,iExADNSum;
	CString csResp,csADNList,csADNData,csAlpha,csPhoneNum;
	iADNFileNum = 0;
	iADNNum     = 0;
	iADNSum     = 0;

	iRet = _SelectPhoneBookDF_3GPP();
	if ( iRet != 0x9000)
		return FALSE;

	iRet = _SelectPBREF_3GPP(csResp);
	if ( iRet != 0x9000)
		return FALSE;

	csResp = _GetTLVData(csResp,0x62);
	csResp = _GetTLVData(csResp,0x82) ;

	iADNFileNum = _GetADNFile_Signt(csADNList,CString2Int(csResp.Mid(0x8,02)),CString2Int(csResp.Mid(06,02)) );

	iExADNSum = _GetANDSum_3GPP(csADNList,iADNFileNum);

	for (int i = 0 ; i < iADNFileNum; i++)
	{
		iRet  =  GetHandle2SendCommand(_T("00A4000402")+csADNList.Mid(i*4,4),csResp);
		if ((iRet&0xFF00) != 0x6100)
			return FALSE;
		iRet  =  GetHandle2SendCommand(_T("00C00000")+Int2CString(iRet&0xFF,2),csResp);
		if (iRet != 0x9000)
			return FALSE;

		csResp = _GetTLVData(csResp,0x62);
		csResp = _GetTLVData(csResp,0x82) ;
		iADNNum = CString2Int(csResp.Mid(0x8,02));
		iADNLen = CString2Int(csResp.Mid(6,02));
		for (int j = 1 ; j <= iADNNum;j++)
		{
			iADNSum += 1;
			csADNData.Empty();
			csAlpha.Format("%04d",iADNSum);
			csPhoneNum.Format("%04d",iADNSum);
			csADNData = _Genrate80ADN(_T("号码")+csAlpha,iADNLen-14,_T("+1381234")+csPhoneNum);
			iRet      = GetHandle2SendCommand(_T("00DC")+Int2CString(j,02)+_T("04")+Int2CString(iADNLen,02)+csADNData,csResp);
			if (iRet != 0x9000)
				return FALSE;	
			SetProgress2StatusBar(iExADNSum,iADNSum);
		}
	}

	return TRUE;
}


// 获取ADN 总数,这个需要在选择 PBR 之后
int C_ADN::_GetANDSum_3GPP(CString csFileList,int iADNFileNum)
{
	int iADNNum,iRet;
	CString csResp;
	iADNNum = 0;

	for (int i = 0 ; i < iADNFileNum; i++)
	{
		iRet  =  GetHandle2SendCommand(_T("00A4000402")+csFileList.Mid(i*4,4),csResp);
		if ((iRet&0xFF00) != 0x6100)
			return FALSE;
		iRet  =  GetHandle2SendCommand(_T("00C00000")+Int2CString(iRet&0xFF,2),csResp);
		if (iRet != 0x9000)
			return FALSE;

		csResp = _GetTLVData(csResp,0x62);
		csResp = _GetTLVData(csResp,0x82) ;
		iADNNum += CString2Int(csResp.Mid(0x8,02));


	}
	return iADNNum;
}


// 把具体进度输出到状态栏
int C_ADN::SetProgress2StatusBar(int iSum, int iCurrent)
{
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CurMainFrm->SetProgressCounter(iSum,iCurrent);
	return 0;
}

int C_ADN::ReadSetADN2List(void)
{
	int iRet;
	switch(iPhoneBookType)
	{
	case _DEF_PhoneBook_3GPP: iRet  = ReadSetADN2List_3GPP();break;
	case _DEF_PhoneBook_GSM:	 iRet  = ReadSetADN2List_GSM();break;
	}

	return iRet;

	
	
}

// 显示 总数，空的，占用的
void C_ADN::SetPhoneBookDisplay(int iSum, int iUsed)
{
	SetDlgItemInt(IDC_PhoneNumber_Dis,iSum);
	SetDlgItemInt(IDC_EmptyPhoneNumber_dis,iSum-iUsed);
	SetDlgItemInt(IDC_UsedPhoneNumber_dis,iUsed);
}

// 遵循GSM 标准的号簿
int C_ADN::WriteTestADN_GSM(void)
{
	int iRet,iADNNum,iADNLen;
	CString csResp,csADNData,csAlpha,csPhoneNum;
	iRet  =  GetHandle2SendCommand(_T("A0A40000027F10"),csResp);
	if ((iRet&0xFF00) != 0x9F00)
		return FALSE;
	iRet  =  GetHandle2SendCommand(_T("A0A40000026F3A"),csResp);
	if ((iRet&0xFF00) != 0x9F00)
		return FALSE;
	iRet  =  GetHandle2SendCommand(_T("A0C00000")+Int2CString(iRet&0xFF,2),csResp);
	if (iRet != 0x9000)
		return FALSE;

	iADNLen = CString2Int(csResp.Mid(28,02));
	if (iADNLen < 14)
		return FALSE;
	iADNNum = CString2Int(csResp.Mid(04,04)) /iADNLen;


	for (int j = 1 ; j <= iADNNum;j++)
	{

		csADNData.Empty();
		csAlpha.Format("%04d",j);
		csPhoneNum.Format("%04d",j);
		csADNData = _Genrate80ADN(_T("号码")+csAlpha,iADNLen-14,_T("+1381234")+csPhoneNum);
		iRet      = GetHandle2SendCommand(_T("A0DC")+Int2CString(j,02)+_T("04")+Int2CString(iADNLen,02)+csADNData,csResp);
		if (iRet != 0x9000)
			return FALSE;	
		SetProgress2StatusBar(j,iADNNum);
	}


	return TRUE;
}

// 遵循3GPP 规范来读取号簿
int C_ADN::ReadSetADN2List_3GPP(void)
{
	int iRet,iADNFileNum,iADNNum,iADNSum,iADNLen,iExADNSum;
	CString csResp,csADNList,csADNData,csAlpha,csPhoneNum;
	iADNFileNum = 0;
	iADNNum     = 0;
	iADNSum     = 0;

	m_PhoneBook_List.DeleteAllItems();

	iRet = _SelectPhoneBookDF_3GPP();
	if ( iRet != 0x9000)
		return FALSE;

	iRet = _SelectPBREF_3GPP(csResp);
	if ( iRet != 0x9000)
		return FALSE;

	csResp = _GetTLVData(csResp,0x62);
	csResp = _GetTLVData(csResp,0x82) ;

	iADNFileNum = _GetADNFile_Signt(csADNList,CString2Int(csResp.Mid(0x8,02)),CString2Int(csResp.Mid(06,02)) );

	iExADNSum = _GetANDSum_3GPP(csADNList,iADNFileNum);



	for (int i = 0 ; i < iADNFileNum; i++)
	{
		iRet  =  GetHandle2SendCommand(_T("00A4000402")+csADNList.Mid(i*4,4),csResp);
		if ((iRet&0xFF00) != 0x6100)
			return FALSE;
		iRet  =  GetHandle2SendCommand(_T("00C00000")+Int2CString(iRet&0xFF,2),csResp);
		if (iRet != 0x9000)
			return FALSE;

		csResp = _GetTLVData(csResp,0x62);
		csResp = _GetTLVData(csResp,0x82) ;
		iADNNum = CString2Int(csResp.Mid(0x8,02));
		iADNLen = CString2Int(csResp.Mid(6,02));
		for (int j = 1 ; j <= iADNNum;j++)
		{
			iRet      = GetHandle2SendCommand(_T("00B2")+Int2CString(j,02)+_T("04")+Int2CString(iADNLen,02),csResp);
			if (iRet != 0x9000)
				return FALSE;	
			csADNData = csResp.Left(iADNLen*2);
			if (!_WipeEmpty(csADNData).IsEmpty())
			{
				iADNSum++;
				SetPhoneBookDisplay(iExADNSum,iADNSum);
				csPhoneNum.Format("%d",iADNSum);
				iRet = m_PhoneBook_List.InsertItem(iADNSum,csPhoneNum);

				csAlpha    = csADNData.Left(csADNData.GetLength() - 28);;
				csPhoneNum = csADNData.Mid(csAlpha.GetLength(),24);

				m_PhoneBook_List.SetItemText(iRet, 1, TransationAlphaIdentifier(csAlpha));
				m_PhoneBook_List.SetItemText(iRet, 2, _TransationADNNumber(csPhoneNum));

			}

			SetProgress2StatusBar(iExADNSum,iADNSum);
		}
	}
	return TRUE;
	return 0;
}

// 遵循GSM 规范读取号簿
int C_ADN::ReadSetADN2List_GSM(void)
{
	int iRet,iADNNum,iADNLen,iADNSum;
	CString csResp,csADNData,csAlpha,csPhoneNum;
	iRet  =  GetHandle2SendCommand(_T("A0A40000027F10"),csResp);
	if ((iRet&0xFF00) != 0x9F00)
		return FALSE;
	iRet  =  GetHandle2SendCommand(_T("A0A40000026F3A"),csResp);
	if ((iRet&0xFF00) != 0x9F00)
		return FALSE;
	iRet  =  GetHandle2SendCommand(_T("A0C00000")+Int2CString(iRet&0xFF,2),csResp);
	if (iRet != 0x9000)
		return FALSE;

	iADNLen = CString2Int(csResp.Mid(28,02));
	if (iADNLen < 14)
		return FALSE;
	iADNSum = CString2Int(csResp.Mid(04,04)) /iADNLen;
	iADNNum = 0;
	for (int j = 1 ; j <= iADNSum;j++)
	{
		iRet      = GetHandle2SendCommand(_T("A0B2")+Int2CString(j,02)+_T("04")+Int2CString(iADNLen,02),csResp);
		if (iRet != 0x9000)
			return FALSE;	
		csADNData = csResp.Left(iADNLen*2);
		if (!_WipeEmpty(csADNData).IsEmpty())
		{
			iADNNum ++ ;
			SetPhoneBookDisplay(iADNSum,iADNNum);
			csPhoneNum.Format("%d",iADNNum);
			iRet = m_PhoneBook_List.InsertItem(iADNNum,csPhoneNum);

			csAlpha    = csADNData.Left(csADNData.GetLength() - 28);;
			csPhoneNum = csADNData.Mid(csAlpha.GetLength(),24);

			m_PhoneBook_List.SetItemText(iRet, 1, TransationAlphaIdentifier(csAlpha));
			m_PhoneBook_List.SetItemText(iRet, 2, _TransationADNNumber(csPhoneNum));

		}

		SetProgress2StatusBar(iADNSum,j);
	}

	return TRUE;
}


// 设置 号簿 类别， GSM USIM 等
int C_ADN::SetAbbreviatedDiallingNumbersType(int iType)
{
	iPhoneBookType = iType;
	return TRUE;
}
