// C_SMS.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "C_SMS.h"
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
		iRet = CString2Int(csResp.Right(04));
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
		*iSMSLen = CString2Int(csResp.Mid(28,02));
		if (*iSMSLen == 0)
			return FALSE;
		*iSMSSum = CString2Int(csResp.Mid(04,04)) / (*iSMSLen);
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
		csResp = _GetTLVData(csResp,0x62);
		csResp = _GetTLVData(csResp,0x82);
		*iSMSLen = CString2Int(csResp.Mid(4,4));
		*iSMSSum = CString2Int(csResp.Mid(0x8,2));
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
		iTemp  = CString2Int (csSMS.Mid(02,02));
		csResp = csSMS.Mid(02,iTemp*2+2);
		csResp = _TransationADNNumber(csResp);
		iOffset = iTemp*2+4;
		iParameter --;
	}

	//相关参数
	if (iParameter>0)
	{
		csResp = csSMS.Mid(iOffset,2);
		iMTI   = CString2Int(csResp);
		iOffset += 2;
		if (iMTI&1)
			iOffset += 2;
		iParameter --;
	}

	//地址，
	if (iParameter>0)
	{
		iTemp    = CString2Int (csSMS.Mid(iOffset,02));
		iTemp    = iTemp/2 + (iTemp%2) + 1;
		iTemp    = iTemp*2+2;
		csResp   = csSMS.Mid(iOffset,iTemp);
		csResp   = _TransationAddress(csResp);
		iOffset += iTemp;
		iParameter --;
	}

	if (iParameter>0)
	{
	iPID = CString2Int( csSMS.Mid(iOffset,2));
	iOffset += 2;
	iDCS = CString2Int( csSMS.Mid(iOffset,2));
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
		iTemp  = CString2Int(csSMS.Mid(iOffset,2))*2;
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
			*iBatch = CString2Int( csSMS.Mid(iOffset+0x8,2));
			*iSum   = CString2Int( csSMS.Mid(iOffset+10,2));
			*iNum   = CString2Int( csSMS.Mid(iOffset+12,2));
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

		if ((!_TraslateParameterofSMS(csCurMessage,_DEF_SMS_Status,csResp))||(CString2Int(csResp) == 0x00))
			continue;


		//获取多条标识
		if (_TraslateParameterofSMS(csCurMessage,_DEF_SMS_Patameter,csResp))
		{
			iMTI = CString2Int(csResp);
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
		csMessage = csMessageFileData.Mid((CString2IntDecimal(csRecord.Mid(i,2))-1 )*0x160 ,0x160);

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
		if (GetHandle2SendCommand(_T("A0DC")+  Int2CString(CString2IntDecimal( csRecord.Mid(i*2,2)),02) +_T("04B000")+ RepeatCString(_T("FF"),0xAF),csResp) != 0x9000)
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
		if (GetHandle2SendCommand(_T("00DC")+  Int2CString(CString2IntDecimal( csRecord.Mid(i*2,2)),02) +_T("04B000")+ RepeatCString(_T("FF"),0xAF),csResp) != 0x9000)
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
	CString csUserDataEdit,csUserData,csUDL,csSCN,csAddress,csDateTime;
	int iMsgNum,iMsgVer,iMsgLen;

	GetDlgItemText(IDC_Message_Edit,csUserDataEdit);
	GetDlgItemText(IDC_ShortMessageCenter_Edit,csSCN);
	GetDlgItemText(IDC_Address_Edit,csAddress);
	GetDlgItemText(IDC_DateTime_Edit,csDateTime);
	csUserDataEdit = ConvertUCS2(csUserDataEdit);

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
		csDateTime = GetSysDate()+GetSysTime();
		csDateTime = csDateTime.Right(12);
	}
		

	csDateTime = _ExchangeAt(csDateTime);
	csMessage.Empty();

	iMsgVer = GenerateChallenge()&0xFF;
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

		//PDI DCS
		csMessage+= _T("0008");

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
	if (((CButton*)GetDlgItem(IDC_UseSystemTime_Check))->GetCheck())
	{
		GetDlgItem(IDC_DateTime_Edit)->EnableWindow(FALSE);
		csDis = GetSysDate()+GetSysTime();
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
	case _DEF_SMS_GSM:  iRet = _ClearMessageFile_GSM() ; break;
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
	// TODO: 在此添加控件通知处理程序代码

}


// 选择GSM 短信中心号文件
int C_SMS::SelectSMSP_GSM(int* iSMSPLen)
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

	if ((iRet == 0x9000)&&(iSMSLen!= NULL))
	{
		*iSMSLen = CString2Int(csResp.Mid(28,02));
	}
	return iRet;
}

// 选择3GPP 短信中心号文件
int C_SMS::SelectSMSP_3GPP(int* iSMSPLen)
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

	if ((iRet == 0x9000)&&(iSMSLen!= NULL))
	{
		csResp = _GetTLVData(csResp,0x62);
		csResp = _GetTLVData(csResp,0x82);
		*iSMSLen = CString2Int(csResp.Mid(4,4));
	}
	return iRet;
}


