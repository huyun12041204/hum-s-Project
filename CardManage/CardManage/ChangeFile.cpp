// ChangeFile.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "ChangeFile.h"
#include "afxdialogex.h"
#include "MainFrm.h"


// CChangeFile 对话框

IMPLEMENT_DYNAMIC(CChangeFile, CDialogEx)

CChangeFile::CChangeFile(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChangeFile::IDD, pParent)
{

}


void CChangeFile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FileRecord_Combo, m_FileRecord);
	DDX_Control(pDX, IDC_FileType_Combo, m_FileType);
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


}

void CChangeFile::SetFileData(CString csFCI,CString csData)
{
	CString csResult;
	CString csFileInformation,csFileType;
	CString csTemp;
	int iFileNumber;


	csFileValue.Empty();


	csFCI               = _GetTLVData(csFCI,0x62);
	csFileInformation   = _GetTLVData(csFCI,0x82);
	csFileType          = csFileInformation.Mid(00,02);
	iFileType           = CString2Int(csFileType);
	csFileValue         = csData;

	switch(iFileType&0x7)
	{
	case 01:

		m_FileType.SetCurSel(0);
		m_FileRecord.EnableWindow(FALSE);
		SetDlgItemText(IDC_FileData_Eidt,csData);
		iRecordLen = csData.GetLength()/2;
		break;
	case 02:
	case 06:

		if ((iFileType&0x7) == 2)
			m_FileType.SetCurSel(1);
		else
			m_FileType.SetCurSel(2);

		iFileNumber = CString2Int(csFileInformation.Mid(0x8 ,02));
		iRecordLen  = CString2Int(csFileInformation.Mid(04 ,04));

		for(int iCyc = 0 ; iCyc < iFileNumber; iCyc++)
		{
			csTemp.Format("%d",iCyc+1);
			m_FileRecord.AddString(csTemp);
		}
		m_FileRecord.SetCurSel(0);
		m_FileRecord.EnableWindow(TRUE);
		SetDlgItemText(IDC_FileData_Eidt,csFileValue.Mid(0,iRecordLen*2));
		break;
	default:
		break;
	}
}

void CChangeFile::_SetFileData(CString csFCI,CString csData)
{
	CString csFileStru,csTemp;

	int iSize,iRecLen,iRecNum;

	csFileStru = csFCI.Mid(26,02);

	iSize      = CString2Int(csFCI.Mid(04,04));

		csFileValue  = csData;
	switch(CString2Int(csFileStru))
	{
	case 00:

		iFileType = 01;
		m_FileType.SetCurSel(0);
		m_FileRecord.EnableWindow(FALSE);
		SetDlgItemText(IDC_FileData_Eidt,csData);
		iRecordLen = csData.GetLength()/2;

		break;
	case 01:
	case 03:
		iRecLen    = CString2Int(csFCI.Mid(28,04));
		iRecNum    = iSize / iRecLen;
		iRecordLen = iRecLen;
	

		if (CString2Int(csFileStru) == 01)
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
		SetDlgItemText(IDC_FileData_Eidt,csData.Mid(0,iRecLen*2));
		break;
	default:
		break;
	
	}

}


BEGIN_MESSAGE_MAP(CChangeFile, CDialogEx)
	ON_BN_CLICKED(IDOK, &CChangeFile::OnBnClickedOk)
	ON_EN_KILLFOCUS(IDC_FileData_Eidt, &CChangeFile::OnEnKillfocusFiledataEidt)
	ON_CBN_SELCHANGE(IDC_FileRecord_Combo, &CChangeFile::OnCbnSelchangeFilerecordCombo)
END_MESSAGE_MAP()


// CChangeFile 消息处理程序


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
		CurMainFrm->CklClassViewTree(NULL);
	}
	


	CDialogEx::OnOK();
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

	SetDlgItemText(iContrlID,csData);
}

void CChangeFile::OnCbnSelchangeFilerecordCombo()
{
	SetDlgItemText(IDC_FileData_Eidt,csFileValue.Mid(m_FileRecord.GetCurSel()*iRecordLen*2,iRecordLen*2));
}
