#pragma once
#include "afxwin.h"


// CSIMToolkit 对话框

class CSIMToolkit : public CDialogEx
{
	DECLARE_DYNAMIC(CSIMToolkit)

public:
	CSIMToolkit(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSIMToolkit();

// 对话框数据
	enum { IDD = IDD_SIMToolkit_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString csSetupMenu;
	CString csCurrentFetch;
	CListBox m_Menu_Listbox;
	CListBox m_STK_Listbox;
	int iSTKSW;
public:
	afx_msg void OnDblclkSimtoolkitMenuListbox();
	afx_msg void OnBnClickedStkOkButton();
	afx_msg void OnBnClickedStkCancelButton();
public:


	bool InstallMenu(CString csFetch);

	CString GetPreFetch(void);
	CString _GetMenu(CString csFetch, int iNumber);
	void Set2PreFetch(CString csFetch);

	int  GetItemID(int iNum,CString csFetch);
	int _GetMenuNumber(CString csFetch);

	int GetCurrentCommandDetails(void);
	int _DisplayText(CString csText);
	int _DisplayAlpha(CString csAlpha);
	int _DisplayInput(CString csInput);
	int _GetInputLen(int* iMin , int *iMax);
	int ContinueCurrentSTK();
	int ContinueCurrentFetch(int iFetchLen);
	int ContinueCurrentTerminalResponse(int iDetails, int iResult, CString csADD);
	int TransationFetchData(CString csFetch);
	int GenerateTerminal(int iDetails,int* iResult, CString& csADD);
	int StartSIMToolkit(void);
	int _TerminalProfile(CString csProfile);
	int _MenuSelection(int iID);
	int _InputData(CString csData);
	int _InputKey(CString csData);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLbnDblclkStkCommndListbox();
};
