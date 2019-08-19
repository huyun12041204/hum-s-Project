// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

#pragma once

/////////////////////////////////////////////////////////////////////////////
// COutputList 窗口
#pragma once
#include "..\AllUsedSource\ExpAPDU\ExpAPDU.h"

/////////////////////////////////////////////////////////////////////////////
// COutputList 窗口
#define  _DEF_APDU_ATR     01
#define  _DEF_APDU_PPS     02
#define  _DEF_APDU_HEAD    03
#define  _DEF_APDU_ACK     04
#define  _DEF_APDU_NULL    05
#define  _DEF_APDU_DATA    06
#define  _DEF_APDU_SW      07


#define  _DEF_DESCRIPTTION 11

#define _DEF_FORMATE_LENGTH 400

#define _DEF_NAME_LENGTH    40

#define  DEF_OUTPUTLIST_HOTKEY_C_C 10100

class COutputList : public CListBox
{
	// 构造
public:

	// 实现
public:


protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnViewOutput();
	afx_msg void OnLbnDblclk();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnEditSave();
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnKillFocus(CWnd* pNewWnd);

	void _APDUExplainFormat(CString&csText,int iFormatLength = _DEF_FORMATE_LENGTH);
	void FomatAddString(CString csText,int iNT = _DEF_DESCRIPTTION);
	int  FomatAPDU(CString csText,CStringArray& csArray,int iNT);
	int  FomatDesription(CString csText,CStringArray& csArray);
	void RemvoeAllSelect();
	//	afx_msg void OnLbnSelchange();

	int PreSelect(int iIndex, BOOL bSel);
	int PostSelect(int iIndex, BOOL bSel);
	void TabSelectItem(int iIndex, BOOL bSel = TRUE);
	int GetSelectFistItem();
	int GetSelectLastItem();


	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void         AdjustHorzScroll();
	long         GetTextWidth(CString csText);
	CString      GetSpaceText(long lTextWidth);
};


class COutputWnd : public CDockablePane
{
// 构造
public:
	COutputWnd();

	void UpdateFonts();

// 特性
protected:
	CMFCTabCtrl	m_wndTabs;

	COutputList m_wndOutputBuild;
	COutputList m_wndOutputDebug;
	COutputList m_wndOutputFind;

protected:
	void FillBuildWindow();
	void FillDebugWindow();
	void FillFindWindow();

	void AdjustHorzScroll(CListBox& wndListBox);

// 实现
public:
	virtual ~COutputWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

