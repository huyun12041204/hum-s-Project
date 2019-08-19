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



#include "BitsAnalyserDoc.h"
#include "OutputWnd.h"
#include "BasicConvert\BasicConvert\BasicConvert.h"

class CBitsAnalyserView : public CView
{
protected: // �������л�����
	CBitsAnalyserView();
	DECLARE_DYNCREATE(CBitsAnalyserView)

// ����
public:
	CBitsAnalyserDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CBitsAnalyserView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	CRichEditCtrl m_wndEdit;
	COutputList   m_APDUList;    
	int bbitsLen ;
	int bdiflen  ;
	BYTE bbits[10];

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	DECLARE_MESSAGE_MAP()
public:
	void UpdateFonts();
//	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	int PrintEdit(char* bInput, UINT uiLen);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	int ViewAPDU(BYTE* ucBits , UINT BitsLen);
};

#ifndef _DEBUG  // BitsAnalyserView.cpp �еĵ��԰汾
inline CBitsAnalyserDoc* CBitsAnalyserView::GetDocument() const
   { return reinterpret_cast<CBitsAnalyserDoc*>(m_pDocument); }
#endif

