// ExpDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CardManage.h"
#include "ExpDialog.h"
#include "afxdialogex.h"
#include "..\AllUsedSource\ExpAPDU\ExpAPDU.h"

// CExpDialog �Ի���

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


// CExpDialog ��Ϣ�������


void CExpDialog::OnEnChangeCommandEdit()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

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



	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
