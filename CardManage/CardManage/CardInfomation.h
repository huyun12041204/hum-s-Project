#pragma once
// CCMCCKey �Ի���

class CCMCCKey : public CDialogEx
{
	DECLARE_DYNAMIC(CCMCCKey)

public:
	CCMCCKey(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCMCCKey();

	// �Ի�������
	enum { IDD = IDD_CMCC_Key_Form };
	void Initialize_Form();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
};
#pragma once


// CCUCKey �Ի���

class CCUCKey : public CDialogEx
{
	DECLARE_DYNAMIC(CCUCKey)

public:
	CCUCKey(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCUCKey();

	// �Ի�������
	enum { IDD = IDD_CUC_Key_Form };
		void Initialize_Form();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��


	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnClose();
	afx_msg void OnDestroy();
};

#pragma once


// CLocalInformation �Ի���

class CLocalInformation : public CDialogEx
{
	DECLARE_DYNAMIC(CLocalInformation)

public:
	CLocalInformation(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLocalInformation();

	// �Ի�������
	enum { IDD = IDD_LocalInformation_Form };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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


// CCardKey �Ի���

class CCardKey : public CDialogEx
{
	DECLARE_DYNAMIC(CCardKey)

public:
	CCardKey(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CCardKey();

	// �Ի�������
	enum { IDD = IDD_Card_Key_Form };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()


public:
	// ��ȡ�Ƿ�ʹ����PS
	CButton m_UsePS;
	CString GetPIN(int iPIN);
	void Initialize_Form();
	afx_msg void OnBnClickedKey();
	afx_msg void OnDestroy();
};

#pragma once


// CMilenage �Ի���

class CMilenageForm : public CDialogEx
{
	DECLARE_DYNAMIC(CMilenageForm)

public:
	CMilenageForm(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMilenageForm();

	// �Ի�������
	enum { IDD = IDD_Milenage_Form };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CButton m_IsOPC;
	void Initialize_Form();
	afx_msg void OnDestroy();
};

#pragma once
#include "afxwin.h"

// CKeySetting �Ի���
class CKeySetting : public CDialogEx
{
	DECLARE_DYNAMIC(CKeySetting)

public:
	CKeySetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CKeySetting();

// �Ի�������
	enum { IDD = IDD_KeySetting_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	// ��ȡKey���ݣ����ڴ����ļ��У��������ݣ�����KeyFile ��ʽ
	int GenerateKeyData2File(CString& csData);



	CString GetLocalInformation(int iCode);
	// ����CFL����װ���Ӧ��Key
	bool InstallCFLSetting(int iType);

	afx_msg void OnTcnSelchangeKeyTab(NMHDR *pNMHDR, LRESULT *pResult);
	void SetData2Output();
};
#pragma once


// CUST �Ի���

class CUST : public CDialogEx
{
	DECLARE_DYNAMIC(CUST)

public:
	CUST(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CUST();

// �Ի�������
	enum { IDD = IDD_UST_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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


// CSIMToolkit �Ի���

class CSIMToolkit : public CDialogEx
{
	DECLARE_DYNAMIC(CSIMToolkit)

public:
	CSIMToolkit(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSIMToolkit();

	// �Ի�������
	enum { IDD = IDD_SIMToolkit_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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


