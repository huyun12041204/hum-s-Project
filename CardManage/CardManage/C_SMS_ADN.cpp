// C_SMS.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "C_SMS_ADN.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// C_SMS 对话框

IMPLEMENT_DYNAMIC(C_SMS, CDialogEx)

C_SMS::C_SMS(CWnd* pParent /*=NULL*/)
	: CDialogEx(C_SMS::IDD, pParent)
{

}

C_SMS::~C_SMS()
{
}

void C_SMS::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Message_List, m_Message_List);
}


BEGIN_MESSAGE_MAP(C_SMS, CDialogEx)
	ON_WM_CREATE()
	ON_NOTIFY(NM_DBLCLK, IDC_Message_List, &C_SMS::OnNMDblclkMessageList)
	ON_BN_CLICKED(IDC_Read2List_Button, &C_SMS::OnBnClickedRead2listButton)
	ON_BN_CLICKED(IDC_DeleteChecked_Button, &C_SMS::OnBnClickedDeletecheckedButton)
	ON_BN_CLICKED(IDC_Update2File_Button, &C_SMS::OnBnClickedUpdate2fileButton)
	ON_EN_KILLFOCUS(IDC_DateTime_Edit, &C_SMS::OnEnKillfocusDatetimeEdit)
	ON_BN_CLICKED(IDC_UseSystemTime_Check, &C_SMS::OnBnClickedUsesystemtimeCheck)
	ON_BN_CLICKED(IDC_ClearSMS_Button, &C_SMS::OnBnClickedClearsmsButton)
	ON_BN_CLICKED(IDC_UseCardSMC_Check, &C_SMS::OnBnClickedUsecardsmcCheck)
END_MESSAGE_MAP()


// 初始化控件，把控件相关外观，和参数 设置


int C_SMS::InitContrl(void)
{
	// 初始化 Message List
	LONG lStyle;
	lStyle = GetWindowLong(m_Message_List.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	SetWindowLong(m_Message_List.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_Message_List.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮
	dwStyle |= LVS_EX_CHECKBOXES;//CheckBoxs
	m_Message_List.SetExtendedStyle(dwStyle); //设置扩展风格
	int iRet;
	iRet = m_Message_List.InsertColumn( 0, "Record", LVCFMT_CENTER, 50);
	iRet = m_Message_List.InsertColumn( 1, "Address", LVCFMT_LEFT, 100);//插入列
	iRet = m_Message_List.InsertColumn( 2, "Message", LVCFMT_LEFT, 100);//插入列


	return 0;
}


// 初始化各个参数变量
int C_SMS::InitParameter(void)
{
	iShortMessageType = _DEF_SMS_3GPP;
	return 0;
}




// 读取短信并且加入列表
int C_SMS::ReadShortMessageList(void)
{
	int iRet;
	switch(iShortMessageType)
	{
	case _DEF_SMS_GSM:iRet = ReadShortMessageList_GSM();break;
	case _DEF_SMS_USIM:iRet = ReadShortMessageList_3GPP();break;
	default:break;
	}
	return iRet;
}


// 获取MainFrame 并且给卡片发送指令，相关参数按照MainFrame里处理 Return SW ，失败则返回 0
int C_SMS::GetHandle2SendCommand(CString csSend, CString& csResp)
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
		iRet = _CString2Int(csResp.Right(04));
	return iRet;
}


// 读取GSM短信
int C_SMS::ReadShortMessageList_GSM(void)
{
	int iRet,iSMSSum,iSMSLen;
	CString csResp;
	iRet = _SeleteShortMessage_GSM(&iSMSSum,&iSMSLen);
	if (iRet != 0x9000)
		return FALSE;

	if (iSMSLen!= 176)
		return FALSE;

	csMessageFileData.Empty();

	for (int i = 1 ; i <= iSMSSum; i++)
	{
		iRet = GetHandle2SendCommand(_T("A0B2")+Int2CString(i,2)+_T("04B0"),csResp);

		if (iRet == 0x9000)
			csMessageFileData += csResp.Left(0x160); 
	}
	_TransantionAllMessageData(csMessageFileData);

	return iRet;
}

// 读取USIM短信
int C_SMS::ReadShortMessageList_3GPP(void)
{
	int iRet,iSMSSum,iSMSLen;
	CString csResp;
	iRet = _SeleteShortMessage_3GPP(&iSMSSum,&iSMSLen);
	if (iRet != 0x9000)
		return FALSE;

	if (iSMSLen!= 176)
		return FALSE;

	csMessageFileData.Empty();

	for (int i = 1 ; i <= iSMSSum; i++)
	{
		iRet = GetHandle2SendCommand(_T("00B2")+Int2CString(i,2)+_T("04B0"),csResp);

		if (iRet == 0x9000)
			csMessageFileData += csResp.Left(0x160); 
	}
	_TransantionAllMessageData(csMessageFileData);
	
	return iRet;
}


// //Select 短信，并且返回 短信总数，和短信长度
int C_SMS::_SeleteShortMessage_GSM(int* iSMSSum, int* iSMSLen)
{
	int iRet;
	CString csResp;



	//选择Tele 目录
	iRet  =  GetHandle2SendCommand(_T("A0A40000027F10"),csResp);
	if ((iRet&0xFF00) != 0x9F00)
		return FALSE;
	//选择SMS文件
	iRet  =  GetHandle2SendCommand(_T("A0A40000026F3C"),csResp);
	if ((iRet&0xFF00) != 0x9F00)
		return FALSE;
	iRet  =  GetHandle2SendCommand(_T("A0C00000")+Int2CString(iRet&0xFF,2),csResp);

	if ((iRet == 0x9000)&&(iSMSSum!= NULL)&&(iSMSLen!= NULL))
	{
		*iSMSLen = _CString2Int(csResp.Mid(28,02));
		if (*iSMSLen == 0)
			return FALSE;
		*iSMSSum = _CString2Int(csResp.Mid(04,04)) / (*iSMSLen);
	}
	return iRet;
}


int C_SMS::_SeleteShortMessage_3GPP(int* iSMSSum, int* iSMSLen)
{
	int iRet;
	CString csResp;


	//选择Tele 目录
	iRet  =  GetHandle2SendCommand(_T("00A4000C027F10"),csResp);
	if ((iRet&0xFF00) != 0x9000)
		return FALSE;
	//选择SMS文件
	iRet  =  GetHandle2SendCommand(_T("00A40004026F3C"),csResp);
	if ((iRet&0xFF00) != 0x6100)
		return FALSE;
	iRet  =  GetHandle2SendCommand(_T("00C00000")+Int2CString(iRet&0xFF,2),csResp);

	if ((iRet == 0x9000)&&(iSMSSum!= NULL)&&(iSMSLen!= NULL))
	{
		csResp = GetTLVData(csResp,0x62);
		csResp = GetTLVData(csResp,0x82);
		*iSMSLen = _CString2Int(csResp.Mid(4,4));
		*iSMSSum = _CString2Int(csResp.Mid(0x8,2));
	}
	return iRet;
}





//获取短信中的相关参数，已经换过编码的 
//01 状态（输出为编码值，不为实际意义）， 
//02 短信中心号， 
//03 相关参数（输出为编码值，不为实际意义）， 
//04地址，
//05日期 06时间 ，07 时区，
//08内容 返回数据 
int C_SMS::_TraslateParameterofSMS(CString csSMS, int iParameter,CString& csResp,int* iBatch,int* iSum,int* iNum)
{
	int iOffset,iSMSLen,iTemp;
	int iPID,iDCS,iMTI;




	iSMSLen = csSMS.GetLength();
	if (iSMSLen != 0x160)
		return FALSE;

//	iOffset = 0;
	if (iParameter>0)
	{
		csResp = csSMS.Mid(0,2);
		iParameter --;
	}

	//短信中心号
	if (iParameter>0)
	{
		iTemp  = _CString2Int (csSMS.Mid(02,02));
		csResp = csSMS.Mid(02,iTemp*2+2);
		csResp = _TransationADNNumber(csResp);
		iOffset = iTemp*2+4;
		iParameter --;
	}

	//相关参数
	if (iParameter>0)
	{
		csResp = csSMS.Mid(iOffset,2);
		iMTI   = _CString2Int(csResp);
		iOffset += 2;
		if (iMTI&1)
			iOffset += 2;
		iParameter --;
	}

	//地址，
	if (iParameter>0)
	{
		iTemp    = _CString2Int (csSMS.Mid(iOffset,02));
		iTemp    = iTemp/2 + (iTemp%2) + 1;
		iTemp    = iTemp*2+2;
		csResp   = csSMS.Mid(iOffset,iTemp);
		csResp   = _TransationAddress(csResp);
		iOffset += iTemp;
		iParameter --;
	}

	if (iParameter>0)
	{
	iPID = _CString2Int( csSMS.Mid(iOffset,2));
	iOffset += 2;
	iDCS = _CString2Int( csSMS.Mid(iOffset,2));
	iOffset += 2;
	}
	//日期，
	if (iParameter>0)
	{
		if ((iMTI&3) == 0)
		{
			csResp =  TransationDate(csSMS.Mid(iOffset,6));
			iOffset += 6;
		}
		else
			csResp.Empty();

		iParameter --;
	}

	//Time，
	if (iParameter>0)
	{
		if ((iMTI&3) == 0)
		{
			csResp =  TransationTime(csSMS.Mid(iOffset,6));
			iOffset += 6;
		}
		else
			csResp.Empty();

		iParameter --;
	}
	//TimeZone，
	if (iParameter>0)
	{
		if ((iMTI&3) == 0)
		{
			csResp =  TransationDate(csSMS.Mid(iOffset,2));
			iOffset += 2;
		}
		else
			csResp.Empty();
		iParameter --;
	}


	//Userdata
	if (iParameter>0)
	{
		iTemp  = _CString2Int(csSMS.Mid(iOffset,2))*2;
		if ((iTemp + iOffset+2)>0x160)
			return FALSE;
		csResp = csSMS.Mid(iOffset+2,iTemp);
		iParameter --;
	}

	//当几个参数地址 不为空时， 此处 应该 赋值 出去， 否则 就不赋值
	if ((iBatch != NULL)&&(iSum != NULL)&&(iNum != NULL))
	{
		if (iMTI&0x4)
		{
			*iBatch = _CString2Int( csSMS.Mid(iOffset+0x8,2));
			*iSum   = _CString2Int( csSMS.Mid(iOffset+10,2));
			*iNum   = _CString2Int( csSMS.Mid(iOffset+12,2));
		}
		else
		{
			*iBatch = 0;
			* iSum  = 0;
			* iNum  = 0;
		}
	}

	
	//Tran UserData 

	if (iParameter>0)
	{
		//说明此处存在级联，有级联则需要去除级联头，及各个标识 批次，总数，和当前条数
		if (iMTI&4)	
		//此处去除 050003XXXXXX
			csResp = csSMS.Mid(iOffset+14,iTemp-12);

		csResp = TransationData(csResp,iDCS);
	}


	//Userdata
	//if ((iParameter>0)&&(iBatch!= NULL))
	//{
	//	iTemp  = CString2Int(csSMS.Mid(iOffset,2))*2;

	//	if (iMTI&2)
	//	{
	//		//此处去除 050003XXXXXX
	//		csResp = csSMS.Mid(iOffset+14,iTemp-12);

	//		*iBatch = CString2Int( csSMS.Mid(iOffset+0x8,2));
	//		*iSum   = CString2Int( csSMS.Mid(iOffset+10,2));
	//		*iNum   = CString2Int( csSMS.Mid(iOffset+12,2));

	//	}
	//	else
	//	{
	//		csResp = csSMS.Mid(iOffset+2,iTemp);
	//		*iBatch = 0;
	//		* iSum  = 0;
	//		* iNum  = 0;
	//	}

	//	csResp = TransationData(csResp,iDCS);
	//}


	return TRUE;
}


// 把 所读的所有短信(不包含 CDMA 和 CSIM)都解释出来， 包括多条的 
int C_SMS::_TransantionAllMessageData(CString csAllMessage)
{
	int iMessageSum ;
	int iMsgBatch,iMsgSum,iMsgNum;
	int iMTI;
	int iTemp1;
	CString csCurMessage,csResp;
	CString csRecord,csTransUD,csTemp1,csTemp2;
	CString csMsgDate,csMsgTime,csAddress;
	//默认长度为B0 
	iMessageSum = csAllMessage.GetLength()/0x160;

	iMsgBatch = 0;
	iMsgSum   = 0;
	iMsgNum   = 0;

	m_Message_List.DeleteAllItems();
	for (int iNum = 0 ; iNum < iMessageSum ; iNum++)
	{
		//获取当前需要解释的条数
		csCurMessage = csAllMessage.Mid(iNum*0x160,0x160);
		csRecord.Format("%02d",iNum+1);
		//获取短信状态

		if ((!_TraslateParameterofSMS(csCurMessage,_DEF_SMS_Status,csResp))||(_CString2Int(csResp) == 0x00))
			continue;


		//获取多条标识
		if (_TraslateParameterofSMS(csCurMessage,_DEF_SMS_Patameter,csResp))
		{
			iMTI = _CString2Int(csResp);
			csResp.Empty();
			_TraslateParameterofSMS(csCurMessage,_DEF_SMS_Date,csMsgDate);
			_TraslateParameterofSMS(csCurMessage,_DEF_SMS_Time,csMsgTime);
			_TraslateParameterofSMS(csCurMessage,_DEF_SMS_Address,csAddress);		
			_TraslateParameterofSMS(csCurMessage,_DEF_SMS_TranUserData,csTransUD,&iMsgBatch,&iMsgSum,&iMsgNum);

			if (iMTI&0x4)
			{

				if (iMsgNum != 1 )
					continue;

				for (int i = 2 ; i <= iMsgSum ; i++)
				{
					iTemp1 = _FindMessage(csMsgDate,csMsgTime,iMsgBatch,iMsgSum,i,csAllMessage);
					if (iTemp1!= 0)
					{
						csTemp1.Format("%02d",iTemp1);
						csRecord += csTemp1;
						if (_TraslateParameterofSMS(csAllMessage.Mid((iTemp1-1)*0x160,0x160),_DEF_SMS_TranUserData,csResp))
							csTransUD+= csResp;

					}
				}
			}
		}
		else
			continue;

		_InsertMessageItem(csRecord,csAddress,csTransUD);
	}

	return TRUE;
}


// //把相关的参数都Display出来
int C_SMS::_SetMessageData2Edit(void)
{
	return 0;
}


// 通过批次短信总数，和短信条数找寻短信
int C_SMS::_FindMessage(int iBatch, int iSum, int iNum, CString csAllMessage)
{
	int iMessageSum ;
	int iMsgBatch,iMsgSum,iMsgNum;
	CString csCurMessage,csResp;
	//默认长度为B0 
	iMessageSum = csAllMessage.GetLength()/0x160;

	for (int i = 0 ; i < iMessageSum ; i++)
	{
		//获取当前需要解释的条数
		csCurMessage = csAllMessage.Mid(i*0x160,0x160);

		if (_TraslateParameterofSMS(csCurMessage,_DEF_SMS_UserData,csResp,&iMsgBatch,&iMsgSum,&iMsgNum))
			if ((iBatch== iMsgBatch)&&(iSum == iMsgSum)&&(iNum == iMsgNum))
				return i+1;	
	}
	return 0;
}

// 通过批次日期,时间 ,短信总数，和短信条数找寻短信
int C_SMS::_FindMessage(CString csDate,CString csTime,int iBatch, int iSum, int iNum, CString csAllMessage)
{
	int iMessageSum ;
	int iMsgBatch,iMsgSum,iMsgNum;
	CString csCurMessage,csResp;
	CString csMsgDate,csMsgTime;
	//默认长度为B0 
	iMessageSum = csAllMessage.GetLength()/0x160;

	for (int i = 0 ; i < iMessageSum ; i++)
	{
		//获取当前需要解释的条数
		csCurMessage = csAllMessage.Mid(i*0x160,0x160);

		if (_TraslateParameterofSMS(csCurMessage,_DEF_SMS_Date,csMsgDate) &_TraslateParameterofSMS(csCurMessage,_DEF_SMS_Time,csMsgTime) & _TraslateParameterofSMS(csCurMessage,_DEF_SMS_UserData,csResp,&iMsgBatch,&iMsgSum,&iMsgNum))
			if ((iBatch== iMsgBatch)&&(iSum == iMsgSum)&&(iNum == iMsgNum)&& (csDate== csMsgDate)&& (csTime== csMsgTime))
				return i+1;	
	}
	return 0;
}


int C_SMS::_InsertMessageItem(CString csRecord,CString csAddress,CString csUserData)
{
	int iNumber;
	iNumber = m_Message_List.GetItemCount();
	iNumber    = m_Message_List.InsertItem(iNumber+1,csRecord);

	m_Message_List.SetItemText(iNumber, 1, csAddress);
	m_Message_List.SetItemText(iNumber, 2, csUserData);
	return TRUE;
}


void C_SMS::OnNMDblclkMessageList(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	int iRow,iNum;
	CString csRecord;
	CString csMessage;
	CString csSCN,csAddress,csDate,csTime,csUserData,csTemp;
	iRow      = m_Message_List.GetSelectionMark();
	csRecord  = m_Message_List.GetItemText(iRow,0);
	iNum      = csRecord.GetLength();
	csMessage .Empty();
	csUserData.Empty();
	for (int i = 0 ; i < iNum ; i += 2)
	{
		csMessage = csMessageFileData.Mid((_CString2IntDecimal(csRecord.Mid(i,2))-1 )*0x160 ,0x160);

		if ( _TraslateParameterofSMS(csMessage,_DEF_SMS_TranUserData,csTemp))
			csUserData += csTemp;
	}

	if (_TraslateParameterofSMS(csMessage,_DEF_SMS_SCN,csSCN))
		SetDlgItemText(IDC_ShortMessageCenter_Edit,csSCN);

	if (_TraslateParameterofSMS(csMessage,_DEF_SMS_Address,csAddress))
		SetDlgItemText(IDC_Address_Edit,csAddress);

	if (_TraslateParameterofSMS(csMessage,_DEF_SMS_Date,csDate)&_TraslateParameterofSMS(csMessage,_DEF_SMS_Time,csTime))
		SetDlgItemText(IDC_DateTime_Edit,csDate+_T(" ")+csTime);

	((CButton*)GetDlgItem(IDC_UseSystemTime_Check))->SetCheck(FALSE);
	GetDlgItem(IDC_DateTime_Edit)->EnableWindow(TRUE);

	((CButton*)GetDlgItem(IDC_UseCardSMC_Check))->SetCheck(FALSE);
	GetDlgItem(IDC_ShortMessageCenter_Edit)->EnableWindow(TRUE);

	SetDlgItemText(IDC_Message_Edit,csUserData);

	*pResult = 0;
}


void C_SMS::OnBnClickedRead2listButton()
{
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CurMainFrm->NewReadShortMessageThread();
	CurMainFrm->NewSetStatusThread();
}


// 设置短信类别 GSM USM CDMA CSIM
int C_SMS::SetShortMessageType(int iType)
{

	iShortMessageType = iType;
	return TRUE;
}


void C_SMS::OnBnClickedDeletecheckedButton()
{
	_DeleteMessage();
	return ;
}


// 删除一条短信
int C_SMS::_DeleteMessage()
{
	int iRet;
	switch(iShortMessageType)
	{
	case _DEF_SMS_GSM:iRet = _DeleteMessage_GSM();break;
	case  _DEF_SMS_3GPP:iRet = _DeleteMessage_3GPP();break;
	}
	
	return iRet;
}

int C_SMS::_DeleteMessage_GSM()
{
	int iRet,iSMSSum,iSMSLen;
	CString csRecord,csResp;
	iRet = _SeleteShortMessage_GSM(&iSMSSum,&iSMSLen);
	if (iRet != 0x9000)
		return FALSE;

	if (iSMSLen!= 176)
		return FALSE;

	csRecord.Empty();

	iRet = _GetItemCheck(csRecord);

	for (int i = 0 ; i < iRet ; i +=1)
	{
		if (GetHandle2SendCommand(_T("A0DC")+  Int2CString(_CString2IntDecimal( csRecord.Mid(i*2,2)),02) +_T("04B000")+ RepeatCString(_T("FF"),0xAF),csResp) != 0x9000)
			return FALSE;
	}

	return TRUE;
}

int C_SMS::_DeleteMessage_3GPP()
{
	int iRet,iSMSSum,iSMSLen;
	CString csResp,csRecord;
	iRet = _SeleteShortMessage_3GPP(&iSMSSum,&iSMSLen);
	if (iRet != 0x9000)
		return FALSE;

	if (iSMSLen!= 176)
		return FALSE;

	csRecord.Empty();

	iRet = _GetItemCheck(csRecord);

	for (int i = 0 ; i < iRet ; i +=1)
	{
		if (GetHandle2SendCommand(_T("00DC")+  Int2CString(_CString2IntDecimal( csRecord.Mid(i*2,2)),02) +_T("04B000")+ RepeatCString(_T("FF"),0xAF),csResp) != 0x9000)
			return FALSE;
	}



	return TRUE;

}

// 获取已经被选中的ITEM
int C_SMS::_GetItemCheck(CString& csItem)
{

	int iItemSum;
	CString csRecord;
	iItemSum  = m_Message_List.GetItemCount();

	csItem.Empty();
	for (int i = 0  ; i < iItemSum; i ++ )
	{
		if (m_Message_List.GetCheck(i))
		{
			csItem += m_Message_List.GetItemText(i,0);
		}
	}

	return csItem.GetLength()/2;
}


// 通过Search 找到空白的短信
int C_SMS::_GetEmptyMessage(CString& csRecord)
{
	
	return 0;
}

//int iExt 表示期望的有多少条
int C_SMS::_GetEmptyMessage_GSM(CString& csRecord,int iExt)
{

	CString csResp;
	int iRet = 0;
	int iLen = 0;

	iRet = GetHandle2SendCommand(_T("A0A200101000")+ RepeatCString(_T("FF"),0xF),csResp);

	while((iRet&0xFF00) == 0x9F00)
	{
		if (GetHandle2SendCommand(_T("A0C00000")+Int2CString(iRet&0xFF,2),csResp) == 0x9000)
		{
			csRecord += csResp.Left(2);
			iLen     +=1;
			if(iExt == iLen)
				break;

			if (GetHandle2SendCommand(_T("A0B2")+csRecord.Right(02)+_T("04B0"),csResp)!=0x9000)
				break;

			iRet = GetHandle2SendCommand(_T("A0A200121000")+ RepeatCString(_T("FF"),0xF),csResp);
		}

	}

	return iLen;
}
int C_SMS::_GetEmptyMessage_3GPP(CString& csRecord)
{
	CString csResp;
	int iRet = 0;
	int iLen = 0;

	iRet = GetHandle2SendCommand(_T("00A20104B000")+ RepeatCString(_T("FF"),0xAF),csResp);
	if ((iRet&0xFF00) != 0x6100)
		return FALSE;

	iLen = iRet&0xFF;

	iRet  =  GetHandle2SendCommand(_T("00C00000")+Int2CString(iLen,2),csResp);

	if (iRet != 0x9000)
		return FALSE;

	csRecord = csResp.Left(iLen*2);

	return iLen;
}


// 更新到空的记录中
int C_SMS::_UpdateMessage_GSM(CString csSMSData)
{

	int iRet,iSMSSum,iSMSLen;
	CString csResp,csRecord;

	//如果不能整除则表示不为短信文件内容
	iSMSLen = csSMSData.GetLength();

	if((csSMSData.GetLength()%0x160)!=0)
		return FALSE;
	
	iSMSSum = iSMSLen/0x160;

	if (_SeleteShortMessage_GSM()!= FALSE)
		iRet = _GetEmptyMessage_GSM(csRecord);
	else
		return FALSE;

	if (iSMSSum > iRet)
	{
		MessageBox("短信文件空余记录不足");
		return FALSE;
	}

	for (int i = 0 ; i < iSMSSum ; i++)
	{
		if (GetHandle2SendCommand(_T("A0DC")+ csRecord.Mid(i*2,2)  +_T("04B0")+ csSMSData.Mid(i*0x160,0x160),csResp)!= 0x9000)
			return FALSE;
	}


	return TRUE;
}
// 更新到空的记录中
int C_SMS::_UpdateMessage_3GPP(CString csSMSData)
{

	int iRet,iSMSSum,iSMSLen;
	CString csResp,csRecord;

	//如果不能整除则表示不为短信文件内容
	iSMSLen = csSMSData.GetLength();

	if((csSMSData.GetLength()%0x160)!=0)
		return FALSE;

	iSMSSum = iSMSLen/0x160;

	if (_SeleteShortMessage_3GPP()!= FALSE)
		iRet = _GetEmptyMessage_3GPP(csRecord);
	else
		return FALSE;

	if (iSMSSum > iRet)
	{
		MessageBox("短信文件空余记录不足");
		return FALSE;
	}

	for (int i = 0 ; i < iSMSSum ; i++)
	{
		if (GetHandle2SendCommand(_T("00DC")+ csRecord.Mid(i*2,2)  +_T("04B0")+ csSMSData.Mid(i*0x160,0x160),csResp)!= 0x9000)
			return FALSE;
	}


	return TRUE;
}

void C_SMS::OnBnClickedUpdate2fileButton()
{
	CString csMessage;
	int iRet;

	iRet = _GennerateShortMessage(csMessage);

	if (iRet == FALSE)
		return;


	switch(iShortMessageType)
	{
	case _DEF_SMS_3GPP:iRet = _UpdateMessage_3GPP(csMessage);break;
	case _DEF_SMS_GSM :iRet = _UpdateMessage_GSM(csMessage) ;break;
	}

	if (iRet == FALSE)
		return;

}


// 根据Edit数据生成短信
int C_SMS::_GennerateShortMessage(CString& csMessage)
{
	CString csUserDataEdit,csUserData,csUDL,csSCN,csAddress,csDateTime,csDCS;
	int iMsgNum,iMsgVer,iMsgLen;
	CString csDate,csTime;

	GetDlgItemText(IDC_Message_Edit,csUserDataEdit);
	GetDlgItemText(IDC_ShortMessageCenter_Edit,csSCN);
	GetDlgItemText(IDC_Address_Edit,csAddress);
	GetDlgItemText(IDC_DateTime_Edit,csDateTime);

	if (_IsAllAscii(csUserDataEdit))
	{
		csDCS          = _T("04");
		csUserDataEdit = ConvertAscii(csUserDataEdit);
	}
	else
	{
		csDCS          = _T("08");
		csUserDataEdit = ConvertUcs2(csUserDataEdit);
	}

	

	iMsgLen = csUserDataEdit.GetLength();

	if ((iMsgLen%280) == 0)
		iMsgNum        = (iMsgLen/280);
	else
		iMsgNum        = (iMsgLen/280)+1;


	
	csSCN          = _ConvertADNNumber(csSCN);
	csAddress      = _ConvertAddress(csAddress);
	if (_IsDateTimeFormat(csDateTime))
	{
		csDateTime = csDateTime.Mid(2,2)+ csDateTime.Mid(5,2)+ csDateTime.Mid(8,2)+ csDateTime.Mid(11,2)+ csDateTime.Mid(14,2)+ csDateTime.Mid(17,2);
		
	}else
	{
	
		GetSysDate(csDate);
		GetSysTime(csTime);
		csDateTime =csDate+csTime;
		csDateTime = csDateTime.Right(12);
	}
		

	 _ExchangeAt(csDateTime);
	csMessage.Empty();

	iMsgVer = _GenerateChallenge()&0xFF;

	for (int i=0 ; i < iMsgNum ; i ++)
	{
		//状态
		csMessage += _T("01");
		//短信中心号
		csMessage+= csSCN;
		//相关参数临时使用
		if (iMsgNum>1)
			csMessage+= _T("44");
		else
			csMessage+= _T("00");
		//号码
		csMessage+= csAddress;

		//PID
		csMessage+= _T("00");

		//DCS
		csMessage+= csDCS;

		//日期时间
		csMessage+=  csDateTime;

		//时区
		csMessage+=  _T("00");


		if (i != (iMsgNum -1))
			csUserData = _T("050003")+Int2CString(iMsgVer,2)+Int2CString(iMsgNum,2)+Int2CString(i+1,2)+csUserDataEdit.Mid(i*280,280) ;
		else if(iMsgNum!= 1)
			csUserData = _T("050003")+Int2CString(iMsgVer,2)+Int2CString(iMsgNum,2)+Int2CString(i+1,2)+csUserDataEdit.Right( iMsgLen%280);
		else
			csUserData =  csUserDataEdit;

		csUDL = Int2CString(csUserData.GetLength()/2,02);

		csMessage+=csUDL;
		csMessage+=csUserData;

		csMessage+= RepeatCString("F",0x160*(i+1) - csMessage.GetLength());
	}

	return iMsgNum;
}


// 是否为日期和时间格式 XXXX-XX-XX XX:XX:XX
int C_SMS::_IsDateTimeFormat(CString csData)
{
	if ((csData.GetLength()>18)&&(csData.Mid(04,1) == _T("-"))&&(csData.Mid(07,1) == _T("-"))&&(csData.Mid(10,1) == _T(" "))&&(csData.Mid(13,1) == _T(":"))&&(csData.Mid(16,1) == _T(":")))
		return TRUE;
	return FALSE;
}


void C_SMS::OnEnKillfocusDatetimeEdit()
{
	CString csDateTime,csTemp1,csTempDateTime;
	GetDlgItemText(IDC_DateTime_Edit,csDateTime);
	int iLen;

	csTemp1.Empty();
	csTempDateTime.Empty();
	iLen = csDateTime.GetLength();

	//去除非数字字符
	for (int i = 0 ; i < iLen ; i++)
	{
		csTemp1 = csDateTime.Mid(i ,1);
		if ((csTemp1>=_T("0"))&&(csTemp1<=_T("9")))
			csTempDateTime += csTemp1;
	}

	//先补位
	csTempDateTime += RepeatCString("0",14);
	//取出14 长度数据
	csTempDateTime  = csTempDateTime.Left(14);

	//补齐格式
	csTempDateTime = csTempDateTime.Mid(00,04)+_T("-")+csTempDateTime.Mid(04,02)+_T("-")+csTempDateTime.Mid(06,02)+_T(" ")+csTempDateTime.Mid(0x8,02)+_T(":")+csTempDateTime.Mid(10,02)+_T(":")+csTempDateTime.Mid(12,02);

	SetDlgItemText(IDC_DateTime_Edit,csTempDateTime);
}


void C_SMS::OnBnClickedUsesystemtimeCheck()
{
	CString csDis;
	CString csDate,csTime;
	if (((CButton*)GetDlgItem(IDC_UseSystemTime_Check))->GetCheck())
	{
		GetDlgItem(IDC_DateTime_Edit)->EnableWindow(FALSE);

		GetSysDate(csDate);
		GetSysTime(csTime);
		csDis = csDate+csTime;
		csDis = csDis.Mid(00,04)+_T("-")+csDis.Mid(04,02)+_T("-")+csDis.Mid(06,02)+_T(" ")+csDis.Mid(0x8,02)+_T(":")+csDis.Mid(10,02)+_T(":")+csDis.Mid(12,02);
		SetDlgItemText(IDC_DateTime_Edit,csDis);
	}
	else
		GetDlgItem(IDC_DateTime_Edit)->EnableWindow(TRUE);

	
}


void C_SMS::OnBnClickedClearsmsButton()
{

	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CurMainFrm->NewClearShortMessageThread();
	CurMainFrm->NewSetStatusThread();

}


// 清空号簿文件
int C_SMS::_ClearMessageFile(void)
{
	int iRet;
	switch(iShortMessageType)
	{
	case  _DEF_SMS_GSM :iRet = _ClearMessageFile_GSM() ; break;
	case  _DEF_SMS_3GPP:iRet = _ClearMessageFile_3GPP(); break;
	default: iRet = 0;

	}
	return iRet;
}

int C_SMS::_ClearMessageFile_GSM(void)
{
	int iRet,iSMSSum,iSMSLen;
	CString csResp;
	iRet = _SeleteShortMessage_GSM(&iSMSSum,&iSMSLen);
	if (iRet != 0x9000)
		return FALSE;

	if (iSMSLen!= 176)
		return FALSE;


	for (int i = 0 ; i < iSMSSum ; i +=1)
	{
		if (GetHandle2SendCommand(_T("A0DC")+  Int2CString(i+1,02) +_T("04B000")+ RepeatCString(_T("FF"),0xAF),csResp) != 0x9000)
			return FALSE;
	}

	return TRUE;
}
int C_SMS::_ClearMessageFile_3GPP(void)
{

	int iRet,iSMSSum,iSMSLen;
	CString csResp;
	iRet = _SeleteShortMessage_3GPP(&iSMSSum,&iSMSLen);
	if (iRet != 0x9000)
		return FALSE;

	if (iSMSLen!= 176)
		return FALSE;


	for (int i = 0 ; i < iSMSSum ; i +=1)
	{
		if (GetHandle2SendCommand(_T("00DC")+  Int2CString(i+1,02) +_T("04B000")+ RepeatCString(_T("FF"),0xAF),csResp) != 0x9000)
			return FALSE;
	}

	return TRUE;
}




void C_SMS::OnBnClickedUsecardsmcCheck()
{
	int iRet;
	CString csSMSP;
	if (((CButton*) GetDlgItem(IDC_UseCardSMC_Check))->GetCheck())
	{

		iRet = _GetSMSP(csSMSP);
		csSMSP = csSMSP.Right(30);
		csSMSP = csSMSP.Left(24);
		
			_WipeEmpty(csSMSP);
		if (!csSMSP.IsEmpty())
		{
			csSMSP = _TransationADNNumber(csSMSP);
			SetDlgItemText(IDC_ShortMessageCenter_Edit,csSMSP);
			GetDlgItem(IDC_ShortMessageCenter_Edit)->EnableWindow(FALSE);
			return;
		}
	}

	GetDlgItem(IDC_ShortMessageCenter_Edit)->EnableWindow(TRUE);

}


// 选择GSM 短信中心号文件
int C_SMS::_SelectSMSP_GSM(int* iSMSPLen)
{
	int iRet;
	CString csResp;

	//选择Tele 目录
	iRet  =  GetHandle2SendCommand(_T("A0A40000027F10"),csResp);
	if ((iRet&0xFF00) != 0x9F00)
		return FALSE;
	//选择SMS文件
	iRet  =  GetHandle2SendCommand(_T("A0A40000026F42"),csResp);
	if ((iRet&0xFF00) != 0x9F00)
		return FALSE;
	iRet  =  GetHandle2SendCommand(_T("A0C00000")+Int2CString(iRet&0xFF,2),csResp);

	if ((iRet == 0x9000)&&(iSMSPLen!= NULL))
	{
		*iSMSPLen = _CString2Int(csResp.Mid(28,02));
	}
	return iRet;
}

// 选择3GPP 短信中心号文件
int C_SMS::_SelectSMSP_3GPP(int* iSMSPLen)
{
	int iRet;
	CString csResp;

	//选择Tele 目录
	iRet  =  GetHandle2SendCommand(_T("00A4000C027F10"),csResp);
	if ((iRet&0xFF00) != 0x9000)
		return FALSE;
	//选择SMS文件
	iRet  =  GetHandle2SendCommand(_T("00A40004026F42"),csResp);
	if ((iRet&0xFF00) != 0x6100)
		return FALSE;
	iRet  =  GetHandle2SendCommand(_T("00C00000")+Int2CString(iRet&0xFF,2),csResp);

	if ((iRet == 0x9000)&&(iSMSPLen!= NULL))
	{
		csResp = GetTLVData(csResp,0x62);
		csResp = GetTLVData(csResp,0x82);
		*iSMSPLen = _CString2Int(csResp.Mid(4,4));
	}
	return iRet;
}



// //获取短信中心号 
int C_SMS::_GetSMSP_GSM(CString& csSMSP)
{
	int iLen,iRet;

	iRet = _SelectSMSP_GSM(&iLen);

	if (iRet != 0x9000)
	{
		csSMSP.Empty();
		return FALSE;
	}


	if (GetHandle2SendCommand(_T("A0B20104")+Int2CString(iLen,2),csSMSP) == 0x9000)
		csSMSP.Left(iLen*2);
	else
		return FALSE;



	return TRUE;
}
int C_SMS::_GetSMSP_3GPP(CString& csSMSP)
{
	int iLen,iRet;

	iRet = _SelectSMSP_3GPP(&iLen);

	if (iRet != 0x9000)
	{
		csSMSP.Empty();
		return FALSE;
	}


	if (GetHandle2SendCommand(_T("00B20104")+Int2CString(iLen,2),csSMSP) == 0x9000)
		csSMSP = csSMSP.Left(iLen*2);
	else
		return FALSE;



	return TRUE;
}
int C_SMS::_GetSMSP(CString& csSMSP) 
{
	int iRet;

	switch(iShortMessageType)
	{
	case _DEF_SMS_GSM: iRet = _GetSMSP_GSM(csSMSP);break;
	case _DEF_SMS_3GPP:iRet = _GetSMSP_3GPP(csSMSP);break;
	}
	return iRet;
}

// 是否全部为数字或者字母 是返回1 否则为0 
//int C_SMS::_IsAllASC(CString csSMSData)
//{
//	int iLen;
//
//	iLen = csSMSData.GetLength();
//	for (int i = 0; i <iLen ; i++)
//	{
//		if (*(csSMSData.Mid(i,1)) < 0)
//			return FALSE;
//	}
//
//	return TRUE;
//}
//


// C_ADN.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "C_SMS_ADN.h"
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
	ON_BN_CLICKED(IDC_ReadPhoneBook_Button, &C_ADN::OnBnClickedReadphonebookButton)
	ON_BN_CLICKED(IDC_WriteTestPhoneBook_Button, &C_ADN::OnBnClickedWritetestphonebookButton)
	ON_WM_SETFOCUS()
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
		iRet = _CString2Int(csResp.Right(04));
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

		csResp = GetTLVData(csResp,0xA8);
		if (!csResp.IsEmpty())
		{
			csResp = GetTLVData(csResp,0xC0);
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

	csResp = GetTLVData(csResp,0x62);
	csResp = GetTLVData(csResp,0x82) ;

	iADNFileNum = _GetADNFile_Signt(csADNList,_CString2Int(csResp.Mid(0x8,02)),_CString2Int(csResp.Mid(06,02)) );

	iExADNSum = _GetANDSum_3GPP(csADNList,iADNFileNum);

	for (int i = 0 ; i < iADNFileNum; i++)
	{
		iRet  =  GetHandle2SendCommand(_T("00A4000402")+csADNList.Mid(i*4,4),csResp);
		if ((iRet&0xFF00) != 0x6100)
			return FALSE;
		iRet  =  GetHandle2SendCommand(_T("00C00000")+Int2CString(iRet&0xFF,2),csResp);
		if (iRet != 0x9000)
			return FALSE;

		csResp = GetTLVData(csResp,0x62);
		csResp = GetTLVData(csResp,0x82) ;
		iADNNum = _CString2Int(csResp.Mid(0x8,02));
		iADNLen = _CString2Int(csResp.Mid(6,02));
		for (int j = 1 ; j <= iADNNum;j++)
		{
			iADNSum += 1;
			csADNData.Empty();
			csAlpha.Format("%04d",iADNSum);
			csPhoneNum.Format("%04d",iADNSum);
			 _Genrate80ADN(_T("号码")+csAlpha,iADNLen-14,_T("+1381234")+csPhoneNum,csADNData);
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

		csResp = GetTLVData(csResp,0x62);
		csResp = GetTLVData(csResp,0x82) ;
		iADNNum += _CString2Int(csResp.Mid(0x8,02));


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

	iADNLen = _CString2Int(csResp.Mid(28,02));
	if (iADNLen < 14)
		return FALSE;
	iADNNum = _CString2Int(csResp.Mid(04,04)) /iADNLen;


	for (int j = 1 ; j <= iADNNum;j++)
	{

		csADNData.Empty();
		csAlpha.Format("%04d",j);
		csPhoneNum.Format("%04d",j);
		 _Genrate80ADN(_T("号码")+csAlpha,iADNLen-14,_T("+1381234")+csPhoneNum,csADNData);
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

	csResp = GetTLVData(csResp,0x62);
	csResp = GetTLVData(csResp,0x82) ;

	iADNFileNum = _GetADNFile_Signt(csADNList,_CString2Int(csResp.Mid(0x8,02)),_CString2Int(csResp.Mid(06,02)) );

	iExADNSum = _GetANDSum_3GPP(csADNList,iADNFileNum);



	for (int i = 0 ; i < iADNFileNum; i++)
	{
		iRet  =  GetHandle2SendCommand(_T("00A4000402")+csADNList.Mid(i*4,4),csResp);
		if ((iRet&0xFF00) != 0x6100)
			return FALSE;
		iRet  =  GetHandle2SendCommand(_T("00C00000")+Int2CString(iRet&0xFF,2),csResp);
		if (iRet != 0x9000)
			return FALSE;

		csResp = GetTLVData(csResp,0x62);
		csResp = GetTLVData(csResp,0x82) ;
		iADNNum = _CString2Int(csResp.Mid(0x8,02));
		iADNLen = _CString2Int(csResp.Mid(6,02));
		for (int j = 1 ; j <= iADNNum;j++)
		{
			iRet      = GetHandle2SendCommand(_T("00B2")+Int2CString(j,02)+_T("04")+Int2CString(iADNLen,02),csResp);
			if (iRet != 0x9000)
				return FALSE;	

			csResp = csResp.Left(iADNLen*2);
			csADNData = csResp;
			_WipeEmpty(csResp);
			if (!csResp.IsEmpty())
			{
				iADNSum++;
				SetPhoneBookDisplay(iExADNSum,iADNSum);
				csPhoneNum.Format("%d",iADNSum);
				iRet = m_PhoneBook_List.InsertItem(iADNSum,csPhoneNum);

				csAlpha    = csADNData.Left(csADNData.GetLength() - 28);;
				csPhoneNum = csADNData.Mid(csAlpha.GetLength(),24);

				m_PhoneBook_List.SetItemText(iRet, 1, TranslateAlphaIdentifier(csAlpha));
				m_PhoneBook_List.SetItemText(iRet, 2, _TransationADNNumber(csPhoneNum));

			}

			SetProgress2StatusBar(iExADNSum,j+iADNNum*i);
		}
	}
	return TRUE;
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

	iADNLen = _CString2Int(csResp.Mid(28,02));
	if (iADNLen < 14)
		return FALSE;
	iADNSum = _CString2Int(csResp.Mid(04,04)) /iADNLen;
	iADNNum = 0;
	for (int j = 1 ; j <= iADNSum;j++)
	{
		iRet      = GetHandle2SendCommand(_T("A0B2")+Int2CString(j,02)+_T("04")+Int2CString(iADNLen,02),csResp);
		if (iRet != 0x9000)
			return FALSE;	
		csResp = csResp.Left(iADNLen*2);
		csADNData = csResp;
		_WipeEmpty(csResp);
		if (!csResp.IsEmpty())
		{
			iADNNum ++ ;
			SetPhoneBookDisplay(iADNSum,iADNNum);
			csPhoneNum.Format("%d",iADNNum);
			iRet = m_PhoneBook_List.InsertItem(iADNNum,csPhoneNum);

			csAlpha    = csADNData.Left(csADNData.GetLength() - 28);;

			csPhoneNum = csADNData.Mid(csAlpha.GetLength(),24);

			m_PhoneBook_List.SetItemText(iRet, 1, TranslateAlphaIdentifier(csAlpha));
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


void C_ADN::OnBnClickedReadphonebookButton()
{
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CurMainFrm->NewReadTestADNThread();
	CurMainFrm->NewSetStatusThread();
}


void C_ADN::OnBnClickedWritetestphonebookButton()
{
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CurMainFrm->NewWriteTestADNThread();
	CurMainFrm->NewSetStatusThread();
}


void C_ADN::OnSetFocus(CWnd* pOldWnd)
{
	CDialogEx::OnSetFocus(pOldWnd);
}
