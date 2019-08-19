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

// LeftView.h : CLeftView ��Ľӿ�
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
protected: // �������л�����

	DECLARE_DYNCREATE(CLeftView)

// ����
public:
	CCardManageDoc* GetDocument();

// ����
public:

	CImageList       m_ClassViewImages;
	CClassTreeCtrl   m_wndClassCtrl;
	CClassToolBar    m_wndToolBar;
	// ��ʷѡ����,���ڱܿ��ظ�����
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


// ʵ��
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
	// Qualifier: ��ȡItem�ı�ʾ�������ΪDF���򷵻�FALSE����֮TRUE
	// Parameter: HTREEITEM hItem
	//************************************
	BOOL _GetFileMark(HTREEITEM hItem, int* iFileMark);
	//************************************
	// Method:    _GetFileExpectDescription
	// FullName:  CLeftView::_GetFileExpectDescription
	// Access:    public 
	// Returns:   BOOL
	// Qualifier: �˴���Ref�����ȡItemӦ�õ�����
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
	// �޸������ڵ�����
	bool ChangeEFDescription(HTREEITEM hFileItem,CString csDes);
	bool ChangeDFDescription(HTREEITEM hFileItem,CString csDes);
	bool ChangeADFDescription(HTREEITEM hFileItem,CString csDes);
	bool ChangeEFDescription(CString csPath,CString csDes);
	// ͨ��FID
	HTREEITEM _GetItem(int iFID,HTREEITEM hParentItem);
	HTREEITEM _GetItem(CString csPath);
	HTREEITEM _GetItem(CString csAID,HTREEITEM hParentItem);
	// ������ʷѡ����,����ȷ���ڵ���Tree ʱ,���Ϊ�ظ�����,�򲻽��в���
	void _SetHistoryItem(HTREEITEM hItem);

	// ��_SetHistoryItem
	HTREEITEM _GetHistoryItem(void);

};

