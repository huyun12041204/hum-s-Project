#pragma once


// CExpDialog �Ի���

class CExpDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CExpDialog)

public:
	CExpDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CExpDialog();

// �Ի�������
	enum { IDD = IDD_Explain_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeCommandEdit();
};
