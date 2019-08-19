// TermnalSetting.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "TermnalSetting.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// CTermnalSetting 对话框

IMPLEMENT_DYNAMIC(CTermnalSetting, CDialogEx)

CTermnalSetting::CTermnalSetting(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTermnalSetting::IDD, pParent)
{

}

CTermnalSetting::~CTermnalSetting()
{
}

void CTermnalSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	GetTerminalSetting();

}


BEGIN_MESSAGE_MAP(CTermnalSetting, CDialogEx)
	ON_BN_CLICKED(IDOK, &CTermnalSetting::OnBnClickedOk)
	ON_BN_CLICKED(ID_Apply_Button, &CTermnalSetting::OnBnClickedApplyButton)
END_MESSAGE_MAP()


// //给CCR5 发送指令 获取 读卡器参数


int CTermnalSetting::GetTerminalSetting(void)
{

	BYTE * ucSetting;
	UINT uiSettingLen;

	ucSetting = new BYTE [60];
	ZeroMemory(ucSetting,60);
	uiSettingLen = 0 ; 

	if (CT_Tran_OK == CCR5_GetTerminalSetting(TerminalHandle,01,ucSetting,&uiSettingLen))
	{
		SetDlgItemInt(IDC_CLK_Setting_Edit,ucSetting[CLK_H]*0x100+ucSetting[CLK_L]);
		SetDlgItemInt(IDC_VCC_Setting_Edit,ucSetting[Vol_H]*0x100+ucSetting[Vol_L]);
		SetDlgItemInt(IDC_Conv_Setting_Edit,ucSetting[Fac_H]*0x100+ucSetting[Fac_L]);
		SetDlgItemInt(IDC_BWT_Setting_Edit,ucSetting[BWT_H]*0x10000+ucSetting[BWT_M]*0x100+ucSetting[BWT_L]);
		SetDlgItemInt(IDC_ICWT_Setting_Edit,ucSetting[ICWT_H]*0x10000+ucSetting[ICWT_M]*0x100+ucSetting[ICWT_L]);
		SetDlgItemInt(IDC_CWT_Setting_Edit,ucSetting[CWT_H]*0x10000+ucSetting[CWT_M]*0x100+ucSetting[CWT_L]);
		SetDlgItemInt(IDC_WWT_Setting_Edit,ucSetting[WWT_H]*0x10000+ucSetting[WWT_M]*0x100+ucSetting[WWT_L]);

		switch(ucSetting[bit18_]>>6)
		{
		case 00: ((CButton*)GetDlgItem(IDC_Direct_Setting_Radio))->SetCheck(TRUE);break;
		case 01: ((CButton*)GetDlgItem(IDC_Inverse_Setting_Radio))->SetCheck(TRUE);break;
		case 02: ((CButton*)GetDlgItem(IDC_Automatic_Setting_Radio))->SetCheck(TRUE);break;
		default:break;
		}
		((CButton*)GetDlgItem(IDC_CommandTime_Check))->SetCheck((ucSetting[bit18_]>>1)&1);
		((CButton*)GetDlgItem(IDC_Scannings_Check))->SetCheck(((ucSetting[bit18_]>>3)&1));
		((CButton*)GetDlgItem(IDC_Measurement_Check))->SetCheck((ucSetting[bit18_]>>4)&1);
		((CButton*)GetDlgItem(IDC_Fastmodes_Check))->SetCheck((ucSetting[bit18_]>>5)&1);

		SetDlgItemInt(IDC_Stopbit_Send_Edit,ucSetting[StopbitS_H]*0x100+ucSetting[StopbitS_L]);
		SetDlgItemInt(IDC_Stopbit_Recive_Edit,ucSetting[StopbitR_H]*0x100+ucSetting[StopbitR_L]);
		
		((CButton*)GetDlgItem(IDC_Stopbit_Scannings_Edit))->EnableWindow(((CButton*)GetDlgItem(IDC_Scannings_Check))->GetCheck());
		SetDlgItemInt(IDC_Stopbit_Scannings_Edit,ucSetting[StopbitS]);

		SetDlgItemInt(IDC_Start_LOW_Edit,ucSetting[StartLOW_H]*0x100+ucSetting[StartLOW_L]);
		SetDlgItemInt(IDC_Length_Edit,ucSetting[Length_H]*0x100+ucSetting[Length_L]);
		SetDlgItemInt(IDC_Scanning_Edit,ucSetting[Scanning_H]*0x100+ucSetting[Scanning_L]);
	}

	SetDlgItemInt(IDC_ATR_WW_Setting_Edit,ucSetting[31]*0x10000+ucSetting[32]*0x100+ucSetting[33]);	
	return 0;
}


void CTermnalSetting::SetTerminalHandle(HANDLE hTerminalHandle)
{
	TerminalHandle = hTerminalHandle;
}


void CTermnalSetting::OnBnClickedOk()
{
	OnBnClickedApplyButton();
	CDialogEx::OnOK();
}


void CTermnalSetting::OnBnClickedApplyButton()
{
	int iRet;
	BYTE *ucSetting;
	ucSetting = new BYTE [0x1F]; 
	ZeroMemory(ucSetting,0x1F);

	GeneratePart1Setting(ucSetting,0x1F);

	iRet = CCR5_SetTerminalSetting(TerminalHandle,1,1,ucSetting,0x1F);

	if (iRet == CT_Tran_OK)
		MessageBox(_T("终端参数修改成功！"));

}


// 生成part1 
int CTermnalSetting::GeneratePart1Setting(BYTE* ucPart1, int uiPartLen)
{
	UINT uiTemp;

	//CLK
	uiTemp =  GetDlgItemInt(IDC_CLK_Setting_Edit);
	ucPart1[CLK_H] =uiTemp/0x100;
	ucPart1[CLK_L] =uiTemp%0x100;

	//VCC
	uiTemp =  GetDlgItemInt(IDC_VCC_Setting_Edit);
	ucPart1[Vol_H] =uiTemp/0x100;
	ucPart1[Vol_L] =uiTemp%0x100;

	//FAC
	uiTemp =  GetDlgItemInt(IDC_Conv_Setting_Edit);
	ucPart1[Fac_H] =uiTemp/0x100;
	ucPart1[Fac_L] =uiTemp%0x100;

	//BWT
	uiTemp =  GetDlgItemInt(IDC_BWT_Setting_Edit);
	ucPart1[BWT_H] = uiTemp/0x10000;
	ucPart1[BWT_M] = (uiTemp/0x100)%0x100;
	ucPart1[BWT_L] = uiTemp%0x100;

	//ICWT
	uiTemp =  GetDlgItemInt(IDC_ICWT_Setting_Edit);
	ucPart1[ICWT_H] = uiTemp/0x10000;
	ucPart1[ICWT_M] = (uiTemp/0x100)%0x100;
	ucPart1[ICWT_L] = uiTemp%0x100;

	//CWT
	uiTemp =  GetDlgItemInt(IDC_CWT_Setting_Edit);
	ucPart1[CWT_H] = uiTemp/0x10000;
	ucPart1[CWT_M] = (uiTemp/0x100)%0x100;
	ucPart1[CWT_L] = uiTemp%0x100;

	//WWT
	uiTemp =  GetDlgItemInt(IDC_WWT_Setting_Edit);
	ucPart1[WWT_H] = uiTemp/0x10000;
	ucPart1[WWT_M] = (uiTemp/0x100)%0x100;
	ucPart1[WWT_L] = uiTemp%0x100;

	//ATR convention:
	if (((CButton*)GetDlgItem(IDC_Direct_Setting_Radio))->GetCheck())
		uiTemp = 0 ;
	else if  (((CButton*)GetDlgItem(IDC_Inverse_Setting_Radio))->GetCheck())
		uiTemp = 1 ;
	else if  (((CButton*)GetDlgItem(IDC_Automatic_Setting_Radio))->GetCheck())
		uiTemp = 2 ;

	ucPart1[bit18_] = ucPart1[bit18_]|uiTemp*0x40;

	//Fast mode:
	ucPart1[bit18_] = ucPart1[bit18_]|(((CButton*)GetDlgItem(IDC_Fastmodes_Check))->GetCheck())*0x20;

	//Setting of communication parameter
	ucPart1[bit18_] = ucPart1[bit18_]|(((CButton*)GetDlgItem(IDC_Measurement_Check))->GetCheck())*0x10;

	//communication mode:
	ucPart1[bit18_] = ucPart1[bit18_]|(((CButton*)GetDlgItem(IDC_Scannings_Check))->GetCheck())*0x8;

	//Time of command:
	ucPart1[bit18_] = ucPart1[bit18_]|(((CButton*)GetDlgItem(IDC_CommandTime_Check))->GetCheck())*2;

	//Control byte
	ucPart1[bit18_] = ucPart1[bit18_]|1;

	ucPart1[19] = 0x10;
	//Scannings
	uiTemp =  GetDlgItemInt(IDC_Stopbit_Scannings_Edit);
	ucPart1[StopbitS] =uiTemp;
	//Stopbit_Send
	uiTemp =  GetDlgItemInt(IDC_Stopbit_Send_Edit);
	ucPart1[StopbitS_H] =uiTemp/0x100;
	ucPart1[StopbitS_L] =uiTemp%0x100;

	//Stopbit_Recieve
	uiTemp =  GetDlgItemInt(IDC_Stopbit_Recive_Edit);
	ucPart1[StopbitR_H] =uiTemp/0x100;
	ucPart1[StopbitR_L] =uiTemp%0x100;

	//StartLOW
	uiTemp =  GetDlgItemInt(IDC_Start_LOW_Edit);
	ucPart1[StartLOW_H] =uiTemp/0x100;
	ucPart1[StartLOW_L] =uiTemp%0x100;

	//Length
	uiTemp =  GetDlgItemInt(IDC_Length_Edit);
	ucPart1[Length_H] =uiTemp/0x100;
	ucPart1[Length_L] =uiTemp%0x100;

	//Scanning
	uiTemp =  GetDlgItemInt(IDC_Scanning_Edit);
	ucPart1[Scanning_H] =uiTemp/0x100;
	ucPart1[Scanning_L] =uiTemp%0x100;

	return 0;
}


