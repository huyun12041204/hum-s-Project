#pragma once
#include "resource.h"
#include "afxcmn.h"

// CSendCommand 对话框

class CSendCommand : public CDialogEx
{
	DECLARE_DYNAMIC(CSendCommand)

public:
	CSendCommand(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSendCommand();

// 对话框数据
	enum { IDD = IDD_SendCommand_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSendButton();

	CListCtrl m_CommandList_Ctrl;
	CListCtrl m_CommandFile_Ctrl;
	// //初始化指令列表
	void InitCommandList(void);
	afx_msg void OnNMClickComlistCtrl(NMHDR *pNMHDR, LRESULT *pResult);

	void SetAPDU2Edit();

	afx_msg void OnBnClickedRunScriptButton();

	afx_msg void OnLvnItemchangedCommandFile(NMHDR *pNMHDR, LRESULT *pResult);
	// 打开并且执行文件  return 1 成功, 0 打开失败, -X 执行文件失败
	int OpenFileRunScript(CString csFilePath);
	// 通过MainFrame 发送指令
	bool RunSrcipt(CString csSend);
	// //打开并且运行列表中的脚本
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

// CChangeFile 对话框

class CChangeFile : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeFile)

public:
	CChangeFile(CWnd* pParent = NULL);   // 标准构造函数

	// 对话框数据
	enum { IDD = IDD_ChangeFile_Dialog};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
protected:
	afx_msg LRESULT OnPropertyChanged(WPARAM wParam, LPARAM lParam);
public:
	CMFCPropertyGridCtrl m_FileData_ProGrid;
	CComboBox m_FileRecord;
	CComboBox m_FileType;
	CString   csFileValue;
	int       iFileType;
	int       iRecordLen;
	// //当前EF
	int iCurrentEF;
	// 当前的DF或者ADF
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
