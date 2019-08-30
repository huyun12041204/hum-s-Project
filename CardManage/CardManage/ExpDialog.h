#pragma once


// CExpDialog 对话框

class CExpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CExpDialog)

public:
	CExpDialog(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CExpDialog();

// 对话框数据
	enum { IDD = IDD_Explain_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeCommandEdit();
};
