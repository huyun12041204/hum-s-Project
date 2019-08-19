// SearchFile.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "SearchFile.h"
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

	csData    = Delete_Enter_Space(csData);

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
	ON_EN_CHANGE(IDC_StartFile_Edit, &CSearchFile::OnEnChangeStartfileEdit)
	ON_EN_KILLFOCUS(IDC_StartFile_Edit, &CSearchFile::OnEnKillfocusStartfileEdit)
	ON_BN_CLICKED(IDOK, &CSearchFile::OnBnClickedOk)
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
		iStart = CString2Int(csFile);
		GetDlgItemText(IDC_EndFile_Edit,csFile);
		iEnd = CString2Int(csFile);


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
