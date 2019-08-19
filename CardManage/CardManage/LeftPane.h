#pragma once
#include "CExCtrl.h"

#define  _DEF_Application_Name_Column          0  
#define  _DEF_Application_Path_Column          1 
#define  _DEF_Application_Descriptor_Column    2 
// CLeftPane

class CLeftPane : public CDockablePane
{
	DECLARE_DYNAMIC(CLeftPane)

public:

	//CMFCPropertyGridCtrl m_ListBox;

	CSkinListCtrl m_AppcationList;


public:
	CLeftPane();
	virtual ~CLeftPane();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void UpdateFonts();
	void AddNewApplication(CString csName,CString csPath,CString csDescriptor);
	void TransationAppList(CString csApplist);

protected:

	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStartupMenu();
	//CMFCPropertyGridProperty* GetSelectGroup(void);
	afx_msg void OnUsim();
	afx_msg void OnSelectApplication();
	afx_msg void OnUpdateSelectApplication(CCmdUI *pCmdUI);
	BOOL GetApplicationName(CString& csName);
};


#pragma once

#define  _DEF_PIN_Name_Column   0 
#define  _DEF_PIN_Remind_Column   1 
#define  _DEF_PIN_Verifyed_Column 2 
#define  _DEF_PIN_Disabled_Column 3 

#define  _DEF_PIN1_Item   0
#define  _DEF_PUK1_Item   1

#define  _DEF_PIN2_Item   2
#define  _DEF_PIN81_Item  2
#define  _DEF_PUK2_Item   3
#define  _DEF_PUK81_Item  3
#define  _DEF_PINA_Item   4

// CPINStatus

class CPINStatus : public CDockablePane
{
	DECLARE_DYNAMIC(CPINStatus)

public:
	CPINStatus();
	virtual ~CPINStatus();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CSkinListCtrl m_wndPinShow;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	// 安装Pin是否校验的状态
	bool Insatll_PinVerifyStatus(UINT uiVerSta);
	bool Init_PINStatus();
	bool SetPin1Disable(bool bSet);
	bool NotAllowEdit(CMFCPropertyGridProperty* Prop);
	bool SetPinPukRemaindNumber(int iRemainNumber,int iNumber, bool bIsPin);
};


