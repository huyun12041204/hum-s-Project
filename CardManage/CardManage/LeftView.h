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

// LeftView.h : CLeftView 类的接口
//


#pragma once

#define _LV_EF 0
#define _LV_EFSelected 1

#define _LV_DF 4
#define _LV_DFSelected 5

#define _LV_ADF 7
#define _LV_ADFSelected 8

#define _LV_ROOT 10

#define _LV_EFAbsent 2
#define _LV_EFAbsentSelected 2


#define _LV_DFAbsent 6
#define _LV_DFAbsentSelected 6

#define _LV_ADFAbsent 9
#define _LV_ADFAbsentSelected 9

#define _LV_ROOT       10
#define _LV_ROOTAbsent 11

#define _LV_Pro       12
#define _LV_ProAbsent 13


#define _LV_NoSure  0
#define _LV_Existed 1
#define _LV_Absent  2


#define  _DEF_WORK_EF_C     0x01
#define  _DEF_INTERNAL_EF_C 0x02
#define  _DEF_PRO_C         0x03
#define  _DEF_DF_C          0x10

class CCardManageDoc;


class CClassToolBar : public CMFCToolBar
{


};

class CClassTreeCtrl : public CTreeCtrl
{

protected:
	DECLARE_MESSAGE_MAP()
	bool GetScreenItem(NMHDR *pNMHDR,HTREEITEM* hItem,UINT*uiFlag);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnChangefilevalueMenu();
	afx_msg void OnUpdateChangefilevalueMenu(CCmdUI *pCmdUI);
	afx_msg void OnSearchfileMenu();
	afx_msg void OnUpdateSearchfileMenu(CCmdUI *pCmdUI);
	afx_msg void OnSearchfilesMenu();
	afx_msg void OnUpdateSearchfilesMenu(CCmdUI *pCmdUI);

	afx_msg void OnSelectfileMenu();
	afx_msg void OnUpdateSelectfileMenu(CCmdUI *pCmdUI);
	afx_msg void OnReadfilevalueMenu();
	afx_msg void OnUpdateReadfilevalueMenu(CCmdUI *pCmdUI);

	bool SetItemCheck(HTREEITEM hItem, BOOL bCheck);
	bool SetChildItemCheck(HTREEITEM hItem, BOOL bCheck);
	bool SetParentCheck(HTREEITEM hItem, BOOL bCheck);
	bool Sort(int iSort);
	bool SortCurrentItem(HTREEITEM hItem);
	bool MapSortCurrentItem(HTREEITEM hItem);
	bool MapDeleteEmpty(HTREEITEM hItem);
	bool DeleteAbsent(int iAbsent);
	bool StatisticFile(HTREEITEM hItem, int& iEF, int& iDF);
	bool IsRestricted();
	void ExpandItem(HTREEITEM hItem,UINT uiCode);
	afx_msg void OnExpandMenu();
	afx_msg void OnReduceMenu();
};

class CLeftView : public CView
{
protected: // 仅从序列化创建

	DECLARE_DYNCREATE(CLeftView)

// 特性
public:
	CCardManageDoc* GetDocument();

// 操作
public:

	CImageList       m_ClassViewImages;
	CClassTreeCtrl   m_wndClassCtrl;
	CClassToolBar    m_wndToolBar;
	// 历史选中项,用于避开重复单击
	HTREEITEM hHistoryItem;
	CString csModulePath;
	bool    bModuleExist;

DECLARE_MESSAGE_MAP()
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	bool OpenProfileSetting();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClassSort();
	afx_msg void OnClassAddCatalog();
	afx_msg void OnClassAddFile();
	afx_msg void OnClassDeleteEmpty();
	afx_msg void OnClassCalculate();
	afx_msg void OnClassMap();
	afx_msg void OnClassOpen();
	afx_msg void OnClassSave();
    afx_msg void OnClassDelete();
    afx_msg void OnUpdateToolBar(CCmdUI *pCmdUI);
	virtual void OnDraw(CDC* /*pDC*/);


// 实现
public:
	//void OnChangefilevalueMenu();
	void OnSearchfileMenu();
	void OnSearchfilesMenu();
	int StatisticFileNumber(void);

	bool  _IsDFItem(HTREEITEM hItem);
	bool  _IsCheckItem(HTREEITEM hItem);

	CString _GetItemPath(HTREEITEM hItem);
	CString _GetItemText(HTREEITEM hItem);
	CString _GetItemFID(HTREEITEM hItem);
	CString _GetItemAID(HTREEITEM hItem);
	CString _GetItemDescription(HTREEITEM hItem);



	//************************************
	// Method:    _GetFileMark
	// FullName:  CLeftView::_GetFileMark
	// Access:    public 
	// Returns:   BOOL
	// Qualifier: 获取Item的标示，如果不为DF，则返回FALSE，反之TRUE
	// Parameter: HTREEITEM hItem
	//************************************
	BOOL _GetFileMark(HTREEITEM hItem, int* iFileMark);
	//************************************
	// Method:    _GetFileExpectDescription
	// FullName:  CLeftView::_GetFileExpectDescription
	// Access:    public 
	// Returns:   BOOL
	// Qualifier: 此处从Ref里面获取Item应该的名称
	// Parameter: HTREEITEM hItem
	//************************************
	//BOOL _GetFileExpectDescription(HTREEITEM hItem, CString& csDescription);


	int GetFileLayer(HTREEITEM hCurrentItem);
	int GetFileLayerFID(HTREEITEM hCurrentItem,int iLayer);


	void OnChangeVisualStyle();


	HTREEITEM DeleteFileItem(HTREEITEM hItem);
	HTREEITEM GetRootItem();

	HTREEITEM GetChildItem(HTREEITEM hItem);
	HTREEITEM GetNextItem(HTREEITEM hItem,UINT nCode);
	HTREEITEM GetSelectedItem();

	void SelectedItem(HTREEITEM hItem);

	BOOL DeleteAllItems();


protected:
	bool GetTempletData(CString csPath, CString& csTemplet);
	bool OpenModuleFile(CString csName, CString& csTemplet);
public:

	void AdjustLayout();
	bool Initialize_ClassView(int iType = 0xFF);

	bool Insert_EF(int iFID, CString csDes , HTREEITEM* hResItem = NULL,HTREEITEM hPareItem =TVI_ROOT, int iState = _LV_NoSure);
	bool Insert_DF(int iFID, CString csDes , HTREEITEM* hResItem = NULL,HTREEITEM hPareItem =TVI_ROOT,int iState = _LV_NoSure);
	bool Insert_TEST(int iFID, CString csDes , HTREEITEM* hResItem = NULL,HTREEITEM hPareItem =TVI_ROOT,int iState = _LV_NoSure);
	bool Insert_ADF(CString csAID, CString csDes , HTREEITEM* hResItem = NULL, HTREEITEM hPareItem = TVI_ROOT, int iState = _LV_NoSure);
	bool Install_Templet(CString csTemplet,HTREEITEM hRoot = TVI_ROOT);
	bool GetTempletData(CString& csTemplet);
	bool ChangeItemState(HTREEITEM hItem,int iState);
	

	int GenerateTreelistData(HTREEITEM hItem,CString &csResult);
	bool SetClassTreeEnable(bool bEnable);
	// 修改括号内的名字
	bool ChangeEFDescription(HTREEITEM hFileItem,CString csDes);
	bool ChangeDFDescription(HTREEITEM hFileItem,CString csDes);
	bool ChangeADFDescription(HTREEITEM hFileItem,CString csDes);
	bool ChangeEFDescription(CString csPath,CString csDes);
	// 通过FID
	HTREEITEM _GetItem(int iFID,HTREEITEM hParentItem);
	HTREEITEM _GetItem(CString csPath);
	HTREEITEM _GetItem(CString csAID,HTREEITEM hParentItem);
	// 设置历史选中项,用于确定在单击Tree 时,如果为重复单击,则不进行操作
	void _SetHistoryItem(HTREEITEM hItem);

	// 如_SetHistoryItem
	HTREEITEM _GetHistoryItem(void);

};

