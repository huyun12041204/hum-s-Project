// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
class CCardManageView;
#include "OutputWnd.h"
#include "LeftView.h"
#include "../../AllUsedSource/PcscReader/PcscReader.h"
#include "../../AllUsedSource/CCR5/CCR5.h"
#include "CardManageView.h"
#include "SendCommand.h"
#include "LeftPane.h"
#include "CardInfomation.h"
#include "TermnalSetting.h"
#include "C_SMS_ADN.h"
#include "ReferenceWnd.h"
#include "ExpDialog.h"



#define Def_GetFileSystem         1
#define Def_GetApplication        2
#define Def_GetPinStatus          3
#define Def_NotVerify             4
#define Def_GetARR                5

#define Def_APDUExplain           6
#define Def_OTAExplain            7
#define Def_OTADecrypt            8


#define Def_ModulePathExist      0x10
#define Def_ModulePath           0x11
#define Def_KeySettingPath       0x21

#define Def_Card_Connected         0
#define Def_Terminal_Disconnected -1
#define Def_Terminal_Connected    -2
#define Def_Card_Disconnected     -2


#define Def_Thread_Free           0
#define Def_Thread_GetFile        1
#define Def_Thread_SearchFile     2
#define Def_Thread_SaveCard       3
#define Def_Thread_MapFile        4
#define Def_Thread_WriteADN       5
#define Def_Thread_ReadADN        6
#define Def_Thread_ReadSMS        7
#define Def_Thread_ClearSMS       8

#define Def_Thread_RunScript      9

#define Def_Thread_ExportCSV     11
#define Def_Thread_GetFlashData  10

#define Def_Thread_Ending         -1
#define Def_Thread_Suspend        0x100

#define Def_ReaderType_PCSC       0      
#define Def_ReaderType_CCR5       1    






class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)


// ����
public:
	CSplitterWnd m_wndSplitter;

// ��д
public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	CCardManageView* GetRightPane();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա

	//��ͼ �ռ����

	HACCEL m_hAccel;
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	COutputWnd        m_wndOutput;
	CReferenceWnd     m_wndReference;
	CGetFlashWnd      m_wndGetFlash;
	CChangeFile       m_dlgChangeFile;
	CSearchFile       m_dlgSearchFile;
	CSendCommand      m_dlgSendCommand;
	C_ADN             m_dlgADN;  
	C_SMS             m_dlgSMS;  

	CLeftView*        m_wndClassView;
	CCardManageView*  m_wndProperties;

	CMFCRibbonBaseElement* m_ElementATR;
    CMFCRibbonBaseElement* m_ElementSta; 
    CMFCRibbonBaseElement* m_ElementThr; 
	CMFCRibbonBaseElement* m_ElementPro;

	CLeftPane              m_wndLeftPane;	
	CPINStatus             m_wndPinStatus;
	CKeySetting            m_wndKeySetting;
	CSIMToolkit            m_wndSIMToolkit;
	CUST                   m_wndUST;
	//����������
	CPcscReader PcscReader;
	CString     csCardATR;
	CString     csAppList;


	//����״̬����
	bool  bGetFileSystem;
	bool  bGetAppList;
	bool  bGetPinSta;
	bool  bNotVerify;
	bool  bAPDUExplain;
	bool  bOTAExplain;
	bool  bOTADecrypt;
	bool  bGetARR;
	int   iReaderType;
	int   iReaderStatus;



	int iFileNum;
	int iCurNum;


	//���̱���
	HANDLE hThread;
	HANDLE hSetStatusThread;

	HANDLE CCR5Hand;
	BOOL bProByte;
	LONG lWorkTime;




public:
	CString     csCard;
	bool bGetData;
	bool bReadMode;
	bool bIsUICC;


	UINT uiVerifyPIN;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()

	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);


public:
	afx_msg void OnPcscreaderCombo();
	afx_msg void OnGetfilesystemCheck();
	afx_msg void OnConnectbutton();
	afx_msg void OnDisconnectbutton();
	afx_msg void OnGetfilesystembutton();
	afx_msg void OnChangefilevaluebutton();
	afx_msg void OnWarmresetButton();
	afx_msg void OnColdresetButton();
	afx_msg void OnSendcommandButton();
	afx_msg void OnSearchfileButton();
	afx_msg void OnSearchfilesButton();
	afx_msg void OnEndprogressButton();
	afx_msg void OnSuspendprogressButton();
	afx_msg void OnOutputwndCheck();
	afx_msg void OnStatusbarCheck();
	//afx_msg void OnReadermodeCheck();
	//afx_msg void OnIsuiccCheck();
	afx_msg void OnKeyssettingButton();
	afx_msg void OnUsim();
	afx_msg void OnUsimButton();
	afx_msg void OnApplistCheck();
	afx_msg void OnMapfilelistbutton();
	afx_msg void OnMapallfilelistbutton();
	afx_msg void OnSetupmenuButton();
	afx_msg void OnPinstatusCheck();
	afx_msg void OnGetapplistButton();
	//afx_msg void OnGetapplistCheck();
	//afx_msg void OnGetpinstatusCheck();
	afx_msg void OnGetflashCheck();
	afx_msg void OnReadertypeButton();
	afx_msg void OnPCSCReaderButton();
	afx_msg void OnCCR5ReaderButton();
	afx_msg void OnCCR5SettingButton();
	afx_msg void OnResetCTButton();
	afx_msg void OnDisconnectTerminalButton();
	afx_msg void OnConnectTerminalButton();
	afx_msg void OnRequestICCButton();
	afx_msg void OnEjectICCButton();
	afx_msg void OnSendCommandToTerminalButton();
	afx_msg void OnPowerOnButton();
	afx_msg void OnPowerOffButton();

	

protected:

	bool Initialize_Ribbon(void);
	bool Initialize_PcscList(void);


	// ��ʼ������ȫ�ֲ���
	void InitParamater(void);

	// ��ʼ����Ƭ����
	void InitCardParamater(void);


public:

	void _TestCaseExpPcscLastCommand(bool bUICC);
	int  _TestCasePostLastCommand(CString csSW,CString& csResp,bool bUICC);
	void _TestCaseExpCommand(CString csSend,CString csResp);

	int  _TestCaseFileIsExisted(CString csFID,bool bAID = false);
	int  _TestCaseFileIsExisted_UICC(CString csFID,bool bAID = false);
	int  _TestCaseFileIsExisted_GSM(CString csFID);
	int  _TestCasePathIsExisted(CString csPath);
	int  _TestCasePathIsExistedStartMF(CString csPath);
	int  _TestCaseFIDIsExistedInCurrent(CString csFID);



	bool _TestCaseCompareData(CString csData1, CString csData2);

	bool _TestCaseDeleteCardFile(CString csFID);

	bool _TestCaseSelectFile(CString csFile,CString& csResp,bool bUICC = true,bool bAID = false);

	bool _TestCaseSelectFile_PCSC(CString csFile,CString& csResp,bool bUICC = true,bool bAID = false);
	bool _TestCaseSelectFile_CCR5(CString csFile,CString& csResp,bool bUICC = true,bool bAID = false);

	CString _TestCaseReadCurrentFileData(CString csFCI,bool bUICC = true);
	CString _TestCaseReadCurrentFileData_UICC(CString csFCI);
	CString _TestCaseReadCurrentFileData_GSM(CString csFCI);
	CString _TestCaseSelectCurrentFile(HTREEITEM hCurrentItem);
	CString _TestCaseGetBinaryData(int iSize,bool bUICC = true);

	CString _TestCaseReadRecord(int iNumber,int iLength,bool bUICC = true);

	UINT    _TestCaseGetFlashSize();
	CString _TestCaseGetFlashData(UINT uiSize, bool bOutput = true);

	bool _TestCaseVerify(int iNum,bool bSure = false);

	bool _TestCaseEnablePin1(bool bEnable);
	bool _TestCaseChangePin ( int iNum);
	bool _TestCaseUnblockPin( int iNum);
	bool _TestCaseVerifyPS();
	bool _TestCaseUpdateBinaryData(CString csData,bool bUICC = true);
	bool _TestCaseUpdateRecordData(int iNumber,CString csData,bool bUICC = true);
	bool _TestCaseUpdateCycLicData(CString csAllData,int iRecordLen,int iNumber,bool bUICC = true);


public:

	CString _TestCaseSendCommand_PCSC(CString csData);
	CString _TestCaseSendCommand_CCR5(CString csData);

	CString _TestCaseSendCommand(CString csData);

	int _EnvelopMenuSeletion(int iMenu);
	int _AutoFetch(int iFetchLen);
	int _TerminalResponseMenuSeletion(int iMenu);

	int _TerminalProfile(CString csProfile,bool bUICC );
	int _Fetch(int iFetchLen, CString& csResp, bool bUICC);
	int _TerminalResponse(int iDetails,int iResult, CString csAddData ,bool bUICC);
	int _AutoTerminalResponse(CString csPreFetch);


//***********************
	void CheckFileList(void);
	int  CheckMapFile(HTREEITEM hItem);
	bool CheckCardConnected();
	bool ConfirmCardStatue(void);
	bool ConfirmPin1VerifyStatue(void);
//***********************
private:
	static int MapFileThread();
	static int MapAllFileThread(void);
	static int SearchFileThread();
	static int SaveCurrentCardThread();
	static int SetStatusThread();
	static int CheckMapFileListThread();
	static int WriteTestADNThread();
	static int ReadTestADNThread();
	static int ReadShortMessageThread();
	static int ClearShortMessageThread();
	static int RunSendCommandScript();
	static int ExportCSVThread();
	static int _TestGetFlashDataThread();

	
	int _TestGetFlashData();
public:



	bool Connect_Card();
	void MapFile();
	void MapAllFile();
	void Changefilevalue();
	void SetProgressCounter(int iAll,int iCurrent);


	void SearchFile(HTREEITEM hCurrent,bool bSure = true);
	void InsatllFile(HTREEITEM hCurrent,bool bCatalog= true);


	int       _GetApplacationSum();
	int       _GetApplacation(int iNum,CString& csPath);
	int       _MapTeleApplicaiton();

	void      __GetFileThread();
	void      _GetApplicationListThread();
	void      _GetFileThread();
	void      _SearchFileThread();
	void      _SetCurrentStatus();
	void      _SearchFile(int iStartFile,int iEndFile,HTREEITEM hDFItem);

	int        _DFIsUnderItem_UICC(int iFID,HTREEITEM hItem, int CheckLevel = 2);
	void      _SearchFile_UICC(int iStartFile,int iEndFile,HTREEITEM hDFItem);

	void __SearchFile_UICC(int iStartFile,int iEndFile,HTREEITEM hDFItem);
	//���iFID ��DF ���� hItem ��DF�£�
	int       _DFIsUnderItem_GSM(int iFID,HTREEITEM hItem);
	void      _SearchFile_GSM(int iStartFile,int iEndFile,HTREEITEM hDFItem);

	void     NewMapFileThread();
	void     NewMapAllFileThread();
	void     NewSearchFileThread();
	void     NewSetStatusThread();
	void     NewSaveCurrentCardThread();
	void     NewCheckMapFileListThread();
	void     NewWriteTestADNThread();
	void     NewReadTestADNThread();
	void     NewReadShortMessageThread();
	void     NewClearShortMessageThread();
	void     NewRunSendCommandScriptThread();
	void     NewExportCSVThread();
	void     NewGetFlashDataThread();



	BOOL ExportCSV();
	BOOL ExportString( CStdioFile& CSFFile,HTREEITEM hItem);
	BOOL _GenerateFileInformation( HTREEITEM hChildItem, CString csFCI,CString&csInfo );

	int _GetFileAC(int iOperate, CString csFCI, bool bUICC = false);
	int _GetRecordLength(CString csFCI);
	int _GetRecordNumber(CString csFCI);
	int _GetFileSize(CString csFCI);
	int _GetFileSFI(CString csFCI);
	int _GetFileStructure(CString csFCI);
	bool _GetPIN1Enable(CString csFCI, bool bUICC = false);
	bool _GetPIN1EnableInUICC(CString csFCP);





	BOOL SaveTreeItem();
	BOOL SaveDF2Ram(HTREEITEM hDF,int iLevel);
	BOOL SaveEF2Ram(HTREEITEM hEF,int iLevel);
	BOOL SaveParameter2Ram(CString csFCI,int iLevel);
	BOOL SaveData22Ram(CString csFCI,int iLevel);
	BOOL SetRam2TreeItem();
	BOOL Set2TreeItem(CString csCardData,HTREEITEM hDFItem);

	CString  SelectInRam( CString csPath);
	CString  SelectInRam(HTREEITEM hCurrentItem);

	void ExplainFile(HTREEITEM hCurrentItem);


	HTREEITEM  _FileIsExist(int iFile,HTREEITEM hDFItem);
	void InsatllFile2ClassTree(CString csFile,CString csDes,int iDir = _DEF_DF_C,HTREEITEM *hRes = NULL,HTREEITEM hParen = NULL,int iStatue = _LV_NoSure);

	void ChangeFileDesInClassTree(CString csPath,CString csDes);

	void  _GetInSIMToolkid(void);
	int   StartUpCurrentApplicaiton(CString csApp);



	// �ϵ�����
	bool _TestCaseColdReset(void);
	// ����
	bool _TestCaseWarmReset(void);
	// //�޸ĸ��ռ������
	void UpdateFont(void);


	int GetPinStatus(void);
	//�˴�ΪDisable ״̬
	int GetPin1Status(void);
	int GetPinRemianedNumber(int iPin);
	int GetPukRemianedNumber(int iPuk);
	afx_msg void OnUstButton();
	afx_msg void OnUpdateUstButton(CCmdUI *pCmdUI);
	afx_msg void OnAdnButton();
	afx_msg void OnUpdateAdnButton(CCmdUI *pCmdUI);
	afx_msg void OnSmsButton();
	afx_msg void OnUpdateSmsButton(CCmdUI *pCmdUI);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//afx_msg void OnAutoverifypinCheck();
	afx_msg void OnUpdateAutoverifypinCheck(CCmdUI *pCmdUI);
	afx_msg void OnGetPinCounterButton();
	afx_msg void OnUpdateGetPinCounterButton(CCmdUI *pCmdUI);
	
protected:
	// �Ͽ�������,��ǰ֧�� PCSC,CCR5
	int DisConnectReader(void);;
public:
	// ���Ӷ�����
	int ConnectReader(CString csName);
	int ConnectReader_PCSC(CString csName);
	int ConnectReader_CCR5(CString csName);
	// ��CCR5�ϵ粢�һ�ȡATR,���� ֻ��PCSC ��ȡATR
	int PowerOnCard(CString& csATR);
protected:
	// ��ʼ��CCR5�б�
	bool Initialize_CCR5List(void);

public:

	// uiTime 100us;uiSequence 0-6;csSequenceData see CCR5 PRo......
	CString _InterruptSend(CString csSend, UINT uiTime, UINT uiSequence,BOOL bExATR,BOOL bSelf,CString csSequenceData);

	BOOL _SetReference(HTREEITEM hSelectItem);
	// ����ѡ�е�Item ��ֻѡ���ļ���UICC�»�ȡ ARR ,GSM�²������������Phone book �»��Ȼ�ȡPBR
	int ClickClassTreeView(HTREEITEM hSelectItem,CString* csOutPutFCI = NULL);
	int _SelectItem(HTREEITEM hSelectItem,CString* csOutPutFCI);
	int _SetInformation2PropList(HTREEITEM hSelectItem,CString csInputFCI);
	// ����Ƭ����Selectָ����ҷ���FCI�� ���Ӳ��������CliclClassTreeView
	int SelectItemInCard(HTREEITEM hSelectItem, CString* csOutPutFCI);
	//ʹ��UICC ��ָ������������ SelectItemInCard
	int SelectItemInUICCCard(HTREEITEM hSelectItem, CString* csOutPutFCI);

	//ʹ�÷�UICC ��ָ������������ SelectItemInCard
	int SelectItemInNotUICCCard(HTREEITEM hSelectItem, CString* csOutPutFCI);
	int _GetARRInformation(CString csFCI, HTREEITEM hItem,CString&csARRInformation);

	//  ˫��ѡ��Item, ѡ���ļ����� ʹ�ö��̶߳�ȡ�ļ�! ���ҽ���������ļ�����!
	int DClickClassTreeView(HTREEITEM hSelectItem, BOOL bShow = FALSE);
	// ��ȡ��ѡItemָʾ�Ŀ�Ƭ���ļ�,������ʾ��FileData ��!
	int ReadItemInCardAndPutToDisplay(CString csFCI,CString* csOutPutFData=NULL);
	int ReadItemInCardAndPutToDisplayInFile(HTREEITEM hItem,CString* csOutPutData=NULL);
	int SelectItemInFile(HTREEITEM hSelectItem, CString* csOutPutFCI= NULL);

	int  GetProtectedSetting(int iSettingCode,int& iSettingValue);
	int  GetProtectedSetting(int iSettingCode,CString& csSettingValue);
	int  SetProtectedSetting(int iSettingCode,int iSettingValue);
	int  SetProtectedSetting(int iSettingCode,CString csSettingValue);
	int GetAIDFromApplicationList(CString&csAID,UINT uiAIDNumber = 1);
	int GetPINFromKeySetting(CString &csPIN,UINT uiPINCode);


	int GetLocalInformationFromKeySetting(CString& csLocalInformation,int iCode);
	afx_msg void OnOpenModule(UINT iID);
	afx_msg void OnVerifypinButton(UINT iID);

	afx_msg void OnUpdateThreadFreeCardConnected(CCmdUI* pCmdUI);
	afx_msg void OnUpdateThreadBusyCardConnected(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTeminalDisconnected(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTeminalConnected(CCmdUI* pCmdUI);
	afx_msg void OnUpdateIsCCR5(CCmdUI* pCmdUI);
	afx_msg void OnUpdateThreadFree(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCheck(CCmdUI* pCmdUI);
	afx_msg void OnSettingCheck(UINT iID);
	afx_msg void OnExportExcelButton();



	afx_msg void OnDestroy();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnGeflashdataButton();
	afx_msg void OnEraseflashButton();

	afx_msg void OnImportExcelButton();
	BOOL ImportNextRecrod  (CStdioFile& CSFFile);
	BOOL ImportNextDFRecrod(CStdioFile& CSFFile);
	BOOL ImportNextEFRecrod(CStdioFile& CSFFile);
	BOOL _ImportString(CString csString,CString& csFID,CString& csName, CString&csRoute, 
		               CString& csType,CString& csStructure, CString* csSize = NULL, 
					   CString* csRecLen= NULL,CString* csRecNum= NULL, CString* csRead= NULL, 
					   CString* csWrite = NULL, CString* csIncreat= NULL, CString* csDeactive= NULL,
					   CString* csActive= NULL,CString* csContent= NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	CSIMToolkit* GetSIMToolKit();
	COutputWnd * GetOutputWnd();
	CChangeFile* GetChangeFileDlg();

	//afx_msg void OnApduinfoCheck();
	//afx_msg void OnOtainfoCheck();
	//afx_msg void OnOtaDecrypt();
	afx_msg void OnReformatflashButton();
	afx_msg void OnPaint();
	afx_msg void OnReferenceCheck();
	afx_msg void OnExplainButton();
	afx_msg void OnReconvertbutton();



};


