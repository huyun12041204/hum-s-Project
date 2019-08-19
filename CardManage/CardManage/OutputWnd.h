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

#pragma once
#include "..\AllUsedSource\ExpAPDU\ExpAPDU.h"

/////////////////////////////////////////////////////////////////////////////
// COutputList ����
#define  _DEF_APDU_ATR     01
#define  _DEF_APDU_SEND    03
#define  _DEF_APDU_RESP    04
#define  _DEF_APDU_PPS     02

#define  _DEF_DESCRIPTTION 11

#define _DEF_FORMATE_LENGTH 400

#define _DEF_NAME_LENGTH    40

#define  DEF_OUTPUTLIST_HOTKEY_C_C 10100

class COutputList : public CListBox
{
// ����
public:

// ʵ��
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
	void FomatATR(CString csText);
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
	void AdjustHorzScroll();
	long     GetTextWidth(CString csText);
	CString GetSpaceText(long lTextWidth);
};

class COutputWnd : public CDockablePane
{
// ����
public:
	void UpdateFonts();
	COutputWnd();
	~COutputWnd();
// ����
protected:
	CMFCTabCtrl	m_wndTabs;

	COutputList m_wndOutputOper;
	COutputList m_wndOutputAPDU;
	COutputList m_wndOutputAll;

protected:

	void AdjustHorzScroll(CListBox& wndListBox);

// ʵ��

public:
	void Print2Output(CString csLog,CString csSend,CString csResp);
	void ResetContent();

protected:

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()

public:
//	afx_msg void OnPaintClipboard(CWnd* pClipAppWnd, HGLOBAL hPaintStruct);

	void PrintTime2Output(long lTime);
	void PrintAPDU(CString csSend,CString csResp);
	void PrintInformation(CString csSend,CString csResp);
	void PrintATRInformation(CString csATR);
};

#pragma once


// CGetFlashWnd

class CGetFlashWnd : public CDockablePane
{
	DECLARE_DYNAMIC(CGetFlashWnd)

public:
	CGetFlashWnd();
	virtual ~CGetFlashWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void AdjustHorzScroll(CListBox& wndListBox);

	CString csFlashdata;
	UINT    uiOffset;
	COutputList m_wndGetFlash;
	DECLARE_MESSAGE_MAP()
public:
	void UpdateFonts();
	void SetFlashData(CString csInput);
	void ResetOffset();
	BOOL GetAPDUFromData(CString csText, CString& csSend, CString &csResp,int* iOffset);
	void DisplayFlashData(CString csInput);
};


