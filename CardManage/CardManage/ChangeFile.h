#pragma once
#include "resource.h"
#include "afxwin.h"

// CChangeFile �Ի���

class CChangeFile : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeFile)

public:
	CChangeFile(CWnd* pParent = NULL);   // ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ChangeFile_Dialog};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

public:
	CComboBox m_FileRecord;
	CComboBox m_FileType;
	CString   csFileValue;
	int       iFileType;
	int       iRecordLen;
	void SetFileData(CString csFCI,CString csData);
	void _SetFileData(CString csFCI,CString csData);
	void Initialize_Control();

	void FormatEdit(int iContrlID,int iEditLen);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnEnKillfocusFiledataEidt();
	afx_msg void OnCbnSelchangeFilerecordCombo();
};
