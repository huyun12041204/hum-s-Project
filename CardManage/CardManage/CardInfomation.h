#pragma once
// CCMCCKey 对话框

class CCMCCKey : public CDialogEx
{
	DECLARE_DYNAMIC(CCMCCKey)

public:
	CCMCCKey(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCMCCKey();

	// 对话框数据
	enum { IDD = IDD_CMCC_Key_Form };
	void Initialize_Form();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
};
#pragma once


// CCUCKey 对话框

class CCUCKey : public CDialogEx
{
	DECLARE_DYNAMIC(CCUCKey)

public:
	CCUCKey(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCUCKey();

	// 对话框数据
	enum { IDD = IDD_CUC_Key_Form };
		void Initialize_Form();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持


	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnClose();
	afx_msg void OnDestroy();
};

#pragma once


// CLocalInformation 对话框

class CLocalInformation : public CDialogEx
{
	DECLARE_DYNAMIC(CLocalInformation)

public:
	CLocalInformation(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLocalInformation();

	// 对话框数据
	enum { IDD = IDD_LocalInformation_Form };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void Initialize_Form();
	afx_msg void OnBnClickedUsesystemtimeCheck2();
	int _IsDateTimeFormat(CString csData);
	CString GetDateTime();
	CString GetLocalInforamtion();
	afx_msg void OnDestroy();
};

#pragma once


// CCardKey 对话框

class CCardKey : public CDialogEx
{
	DECLARE_DYNAMIC(CCardKey)

public:
	CCardKey(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CCardKey();

	// 对话框数据
	enum { IDD = IDD_Card_Key_Form };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


public:
	// 获取是否使用了PS
	CButton m_UsePS;
	CString GetPIN(int iPIN);
	void Initialize_Form();
	afx_msg void OnBnClickedKey();
	afx_msg void OnDestroy();
};

#pragma once


// CMilenage 对话框

class CMilenageForm : public CDialogEx
{
	DECLARE_DYNAMIC(CMilenageForm)

public:
	CMilenageForm(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMilenageForm();

	// 对话框数据
	enum { IDD = IDD_Milenage_Form };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CButton m_IsOPC;
	void Initialize_Form();
	afx_msg void OnDestroy();
};

#pragma once
#include "afxwin.h"

// CKeySetting 对话框
class CKeySetting : public CDialogEx
{
	DECLARE_DYNAMIC(CKeySetting)

public:
	CKeySetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CKeySetting();

// 对话框数据
	enum { IDD = IDD_KeySetting_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_KeyTab;
	CCardKey m_CardKey;
	CMilenageForm m_Milenage;
	CLocalInformation m_Local;
	CCMCCKey m_CMCCKey;
	CCUCKey  m_CUCKey;
	CString csSettingName;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	bool Initialize_Dialog(void);
	bool GetUsePS(void);
	bool SetUsePS(bool bCheck);
	CString GetPIN(int iPIN);
	CString GetKI(void);
	CString GetOpc(void);
	CString GetCi(int iNumber);
	int GetRi(int iNumber);
	bool OpenKeySetting(CString csPath);
	bool TransactKeySetting(CString csData);

	int Save2File(CString csPath);
	// 获取Key数据，用于存于文件中，生成数据，符合KeyFile 格式
	int GenerateKeyData2File(CString& csData);



	CString GetLocalInformation(int iCode);
	// 根据CFL来安装相对应的Key
	bool InstallCFLSetting(int iType);

	afx_msg void OnTcnSelchangeKeyTab(NMHDR *pNMHDR, LRESULT *pResult);
	void SetData2Output();
};
#pragma once


// CUST 对话框

class CUST : public CDialogEx
{
	DECLARE_DYNAMIC(CUST)

public:
	CUST(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CUST();

// 对话框数据
	enum { IDD = IDD_UST_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BYTE ucUST[12];
	DECLARE_MESSAGE_MAP()
public:
	int SetUST(CString csUST);

	afx_msg void OnChangeUST(UINT id);

	afx_msg void OnBnClickedOk();
};


#pragma once
#include "afxwin.h"
#include "afxcmn.h"


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
	void SetSTKSW(int iSW);

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


