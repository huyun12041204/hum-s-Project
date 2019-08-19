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


// CInput2Prop 对话框
#include "CExCtrl.h"
#include "..\AllUsedSource\ExpFile\ExpFile\ExpFile.h"



class CInput2Prop : public CDialogEx
{
	DECLARE_DYNAMIC(CInput2Prop)

public:
	CInput2Prop(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInput2Prop();

	// 对话框数据
	enum { IDD = IDD_InputProp_Dialog };

protected:
	UINT iMin;
	UINT iMax;
	bool bLarge;
	CString csDefault;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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


// CardManageView.h : CCardManageView 类的接口
//
#pragma once









class CCardManageView : public CView
{
protected: // 仅从序列化创建

	DECLARE_DYNCREATE(CCardManageView)

// 特性
public:
	CCardManageDoc* GetDocument() const;

// 操作
public:
	CTabSel	m_wndPropTabs;
	CMFCPropertyGridCtrl m_wndPropList;
	CMFCPropertyGridCtrl m_wndPropData;
	CMFCPropertyGridCtrl m_wndPropExplain;

	CString csPBR;
	int iPBRLen;

	CString csMCCFilePath;
	CString csMNCFilePath;

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
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

// 实现
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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


	// 修改字体
	int UpdateFonts(void);
protected:
	afx_msg LRESULT OnPropertyChanged(WPARAM wParam, LPARAM lParam);
public:
	int ExcutionPropChanged(WPARAM wParam,CMFCPropertyGridProperty* lParam);
	int ExcutionPropListChanged(CMFCPropertyGridProperty* lParam);
	// UICC下的修改
	int ExcutionUICCChange(WPARAM wParam,CMFCPropertyGridProperty* lParam);
	// 修改UICC下的文件结构
	int ExcutionFileStructure(CMFCPropertyGridProperty* lParam);
	int ExcutionFileType(CMFCPropertyGridProperty* lParam);
	
	// 获取当前在根上的第几个分支的第几分支
	int GetPropertyCourtPath(int iID,CMFCPropertyGridProperty* lParam,BYTE* ucPath);
	int ExcutionUICCBasInfo(int wParam, CMFCPropertyGridProperty* lParam, BYTE* ucPath);
	int ExcutionUICCFileAC(int wParam, CMFCPropertyGridProperty* lParam, BYTE* ucPath);
	int ExcutionUICCFileData(int wParam, CMFCPropertyGridProperty* lParam, BYTE* ucPath);
	int ExcutionUICCFileDes(int wParam, CMFCPropertyGridProperty* lParam, BYTE* ucPath);
	int ExcutionUICCFileSec(int wParam, CMFCPropertyGridProperty* lParam, BYTE* ucPath);

	int InitPropData(void);
};

#ifndef _DEBUG  // CardManageView.cpp 中的调试版本
inline CCardManageDoc* CCardManageView::GetDocument() const
{ return reinterpret_cast<CCardManageDoc*>(m_pDocument); }
#endif



#pragma once


