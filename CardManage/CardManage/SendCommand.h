#pragma once
#include "resource.h"
#include "afxcmn.h"

// CSendCommand �Ի���

class CSendCommand : public CDialogEx
{
	DECLARE_DYNAMIC(CSendCommand)

public:
	CSendCommand(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSendCommand();

// �Ի�������
	enum { IDD = IDD_SendCommand_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSendButton();

	CListCtrl m_CommandList_Ctrl;
	CListCtrl m_CommandFile_Ctrl;
	// //��ʼ��ָ���б�
	void InitCommandList(void);
	afx_msg void OnNMClickComlistCtrl(NMHDR *pNMHDR, LRESULT *pResult);

	void SetAPDU2Edit();

	afx_msg void OnBnClickedRunScriptButton();

	afx_msg void OnLvnItemchangedCommandFile(NMHDR *pNMHDR, LRESULT *pResult);
	// �򿪲���ִ���ļ�  return 1 �ɹ�, 0 ��ʧ��, -X ִ���ļ�ʧ��
	int OpenFileRunScript(CString csFilePath);
	// ͨ��MainFrame ����ָ��
	bool RunSrcipt(CString csSend);
	// //�򿪲��������б��еĽű�
	int OpenRunScriptList(void);
	void InitCommandFile(void);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnNMDblclkCommandFile(NMHDR *pNMHDR, LRESULT *pResult);
	//afx_msg void OnHdnEnddragCommandFile(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedSend2Button();
	afx_msg void OnBnClickedInterruptCheck();
	bool InitContrl(void);
	CComboBox m_SendCombo_Ctrl;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedExpainButton();
};


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
protected:
	afx_msg LRESULT OnPropertyChanged(WPARAM wParam, LPARAM lParam);
public:
	CMFCPropertyGridCtrl m_FileData_ProGrid;
	CComboBox m_FileRecord;
	CComboBox m_FileType;
	CString   csFileValue;
	int       iFileType;
	int       iRecordLen;
	// //��ǰEF
	int iCurrentEF;
	// ��ǰ��DF����ADF
	int iCurrentMark;
	void SetFileData(CString csFCI,CString csData);
	void _SetFileData(CString csFCI,CString csData);
	void Initialize_Control();

	void OnApplicationLook(UINT id);
	void FormatEdit(int iContrlID,int iEditLen);

	DECLARE_MESSAGE_MAP()

	afx_msg void OnBnClickedOk();
	afx_msg void OnEnKillfocusFiledataEidt();
	afx_msg void OnCbnSelchangeFilerecordCombo();
	afx_msg void OnEnChangeFiledataEidt();
	
public:
	void ExplainFileRecord(CString csRecord);
	void SetCurrentFileInformation(int iEFFID, int iDFMark);
	void SetFileEmpty();


	afx_msg void OnBnClicked2rightButton();
	afx_msg void OnBnClicked2leftButton();

	int GetPropertyCourtPath(CMFCPropertyGridProperty* lParam,BYTE* ucPath);
	int ExcutePropertyChanged(WPARAM wParam, LPARAM lParam);
	int ExcutePBRChanged(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void UpdateFonts(void);
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};


#pragma once
#include "resource.h"
#include "afxpropertygridctrl.h"

// CSearchFile �Ի���

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
	CSearchFile(CWnd* pParent = NULL);   // ��׼���캯��
	void InstallCurrentPath(CString csPath,HTREEITEM bCurrentItem);
	void InstallSearchFile(bool bSure);
	void FormatEdit(int iContrlID,int iEditLen);
	CString GetSearchDF();

	// �Ի�������
	enum { IDD = IDD_SearchFile_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeStartfileEdit();
	afx_msg void OnEnKillfocusStartfileEdit();
	afx_msg void OnBnClickedOk();
	void InstallClassTree(int iDIR);
};
