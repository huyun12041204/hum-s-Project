// ExpDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "ExpDialog.h"
#include "afxdialogex.h"
#include "..\AllUsedSource\ExpAPDU\ExpAPDU.h"

// CExpDialog 对话框

IMPLEMENT_DYNAMIC(CExpDialog, CDialogEx)

CExpDialog::CExpDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(CExpDialog::IDD, pParent)
{

}

CExpDialog::~CExpDialog()
{
}

void CExpDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CExpDialog, CDialogEx)
	ON_EN_CHANGE(IDC_Command_EDIT, &CExpDialog::OnEnChangeCommandEdit)
END_MESSAGE_MAP()


// CExpDialog 消息处理程序


void CExpDialog::OnEnChangeCommandEdit()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	CString csAPDU;

	GetDlgItemTextA(IDC_Command_EDIT,csAPDU);

	_DeleteEnterSpace(csAPDU);

	if (!__APDUIsComplete(csAPDU))
	{
		SetDlgItemText(IDC_Explain_EDIT,"-----");
		return;
	}

	SetDlgItemText(IDC_Explain_EDIT,"");

	CString csSend,csResponse;
	CStringArray csDisplay;
	CString csEdit,cstemp;
	if (__P3IsLe(csAPDU))
	{
		csSend = csAPDU.Mid(0,10);
		csResponse = csAPDU.Mid(10);

	}
	else
	{
		csSend = csAPDU.Left(csAPDU.GetLength()-4);
		csResponse = csAPDU.Right(4);
	}

	if (	_ExplainAPDU(csSend,csResponse,csDisplay))
	{

		csEdit.Empty();

		for (int i = 0 ; i < csDisplay.GetCount();i++)
		{

			cstemp = csDisplay.GetAt(i);
			cstemp.Replace("\\-", "   ==>>  ");

			csEdit = csEdit + cstemp+ _T("\r\n");
		}

		SetDlgItemText(IDC_Explain_EDIT,csEdit);

	}



	// TODO:  在此添加控件通知处理程序代码
}
