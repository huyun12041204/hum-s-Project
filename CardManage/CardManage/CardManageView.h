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


// CInput2Prop �Ի���
#include "CExCtrl.h"
#include "..\AllUsedSource\ExpFile\ExpFile\ExpFile.h"



class CInput2Prop : public CDialogEx
{
	DECLARE_DYNAMIC(CInput2Prop)

public:
	CInput2Prop(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInput2Prop();

	// �Ի�������
	enum { IDD = IDD_InputProp_Dialog };

protected:
	UINT iMin;
	UINT iMax;
	bool bLarge;
	CString csDefault;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	
public:
	void SetInputDataSize(UINT uiMin,UINT uiMax);
	CString GetInputData();
	void  SetInputData(CString csInput);
	afx_msg void OnBnClickedOk();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL OnInitDialog();
};

#pragma once
// CTabSel

class CTabSel : public CMFCTabCtrl
{
protected:
	DECLARE_MESSAGE_MAP()
	afx_msg LRESULT OnPropertyChanged(WPARAM wParam, LPARAM lParam);
};

#pragma once
// CTabSel


// CardManageView.h : CCardManageView ��Ľӿ�
//
#pragma once









class CCardManageView : public CView
{
protected: // �������л�����

	DECLARE_DYNCREATE(CCardManageView)

// ����
public:
	CCardManageDoc* GetDocument() const;

// ����
public:
	CTabSel	m_wndPropTabs;
	CMFCPropertyGridCtrl m_wndPropList;
	CMFCPropertyGridCtrl m_wndPropData;
	CMFCPropertyGridCtrl m_wndPropExplain;

	CString csPBR;
	int iPBRLen;

	CString csMCCFilePath;
	CString csMNCFilePath;

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void InitPropList();
	void AdjustLayout();
 

	CMFCPropertyGridProperty* CreateBasicLife2PropList(CString csValue);
	CMFCPropertyGridProperty* CreateBasicSecurity2PropList(int iTag,CString csValue);
	CMFCPropertyGridProperty* CreateBasicFileDes2PropList(CString csDes);
	CMFCPropertyGridProperty* CreateBasicACType2PropList(CString csType);
	CMFCPropertyGridProperty* CreateBasicInformation2PropList(CString csFCI);
	CMFCPropertyGridProperty* CreateACCell(CString csCell);
	CMFCPropertyGridProperty* CreateAC2PropList( );
    CMFCPropertyGridProperty* CreateFile2PropList(CString csFCI);
	CMFCPropertyGridProperty* CreateA52PropList(CString csFCI);
	CMFCPropertyGridProperty* CreateC62PropList(CString csFCI);

	CMFCPropertyGridProperty* _CreateBasicInformation2PropList(CString csFCI);
	CMFCPropertyGridProperty* _CreateACCell(CString csCell,CString csValue);
	CMFCPropertyGridProperty* _CreateAC2PropList(CString csFCI);
	CMFCPropertyGridProperty* _CreateFile2PropList(CString csFCI);

	void SetFCI2PropList(CString csFCI);
	void _SetFCI2PropList(CString csFCI);
	void SetFile2PropList(CString csData);

	void SetExpandedFormatSecurity2PropList(CString csData,bool bDF);
	//CString GetACFromARR(int iCommand,CString csARR,int* Other);
	//CString TransationSecurityConditionData(int iSTTag,CString csSTData);
	//CString TransationControlReferenceTemplateData(CString csData);
	//CString TransationMultiControlReferenceTemplateData(CString csData);
	

	int GetAC(int iOperate,bool bUICC = true);

protected:

// ʵ��
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
//	afx_msg LRESULT OnPropertyChanged(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:

	void InitPropExpain(void);
	void ExplainFile(int iFID,int iMark);
	bool ExplainFID(int iFID, int iMark);
	bool ExplainGSM(int iFID);
	bool ExplainUSIM(int iFID);
	bool ExplainCSIM(int iFID);
	bool Explain3GPP(int iFID);
	bool Explain3GPP2(int iFID);
	bool ExplainCDMA(int iFID);
	bool ExplainCard(int iFID);
	bool ExplainTelecom(int iFID);
	bool ExplainMMSS(int iFID);
	bool ExplainPhonebook(int iFID);
	bool ExplainGSMACCESS(int iFID);

	int GetRecordNumber4PropList(void);
	CString GetData4PropList(int iNumber);


	CMFCPropertyGridProperty* Explain_PBRData(CString csData,int iNumber);

	int ExplainPhonebookFile(int iFID);


	// �޸�����
	int UpdateFonts(void);
protected:
	afx_msg LRESULT OnPropertyChanged(WPARAM wParam, LPARAM lParam);
public:
	int ExcutionPropChanged(WPARAM wParam,CMFCPropertyGridProperty* lParam);
	int ExcutionPropListChanged(CMFCPropertyGridProperty* lParam);
	// UICC�µ��޸�
	int ExcutionUICCChange(WPARAM wParam,CMFCPropertyGridProperty* lParam);
	// �޸�UICC�µ��ļ��ṹ
	int ExcutionFileStructure(CMFCPropertyGridProperty* lParam);
	int ExcutionFileType(CMFCPropertyGridProperty* lParam);
	
	// ��ȡ��ǰ�ڸ��ϵĵڼ�����֧�ĵڼ���֧
	int GetPropertyCourtPath(int iID,CMFCPropertyGridProperty* lParam,BYTE* ucPath);
	int ExcutionUICCBasInfo(int wParam, CMFCPropertyGridProperty* lParam, BYTE* ucPath);
	int ExcutionUICCFileAC(int wParam, CMFCPropertyGridProperty* lParam, BYTE* ucPath);
	int ExcutionUICCFileData(int wParam, CMFCPropertyGridProperty* lParam, BYTE* ucPath);
	int ExcutionUICCFileDes(int wParam, CMFCPropertyGridProperty* lParam, BYTE* ucPath);
	int ExcutionUICCFileSec(int wParam, CMFCPropertyGridProperty* lParam, BYTE* ucPath);

	int InitPropData(void);
};

#ifndef _DEBUG  // CardManageView.cpp �еĵ��԰汾
inline CCardManageDoc* CCardManageView::GetDocument() const
{ return reinterpret_cast<CCardManageDoc*>(m_pDocument); }
#endif



#pragma once


