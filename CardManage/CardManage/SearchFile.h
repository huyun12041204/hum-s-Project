#pragma once
#include "resource.h"

// CSearchFile 对话框

class CSearchFile : public CDialogEx
{
	DECLARE_DYNAMIC(CSearchFile)

public:
	bool bSearch;
	bool bAddTreeList;
	int iAddDir;
	HTREEITEM bSearchItem;
	int iStart;
	int iEnd;
	CSearchFile(CWnd* pParent = NULL);   // 标准构造函数
	void InstallCurrentPath(CString csPath,HTREEITEM bCurrentItem);
	void InstallSearchFile(bool bSure);
	void FormatEdit(int iContrlID,int iEditLen);
	CString GetSearchDF();

// 对话框数据
	enum { IDD = IDD_SearchFile_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeStartfileEdit();
	afx_msg void OnEnKillfocusStartfileEdit();
	afx_msg void OnBnClickedOk();
	void InstallClassTree(int iDIR);
};
