#pragma once


// CSkinListCtrl  
	class CSkinListCtrl : public CListCtrl  
{  
 DECLARE_DYNAMIC(CSkinListCtrl)  

public:  
	unsigned int LIST_ITEM_HEIGHT;  
	int  iSelectedSubItem;
public:  
	CSkinListCtrl();  
	virtual ~CSkinListCtrl();  
protected:  
	DECLARE_MESSAGE_MAP()  
public:  
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);  
protected:  
	void Init();  
	virtual void DrawSubItem(CDC *pDC, int nItem, int nSubItem, CRect &rSubItem, bool bSelected, bool bFocus);  
	virtual void DrawRemainSpace(LPNMLVCUSTOMDRAW lpnmcd);  
	virtual void draw_row_bg(CDC *pDC, RECT rc, bool bSelected, bool bFocus,int nRow);  
	virtual void draw_row_bg(CDC *pDC, RECT rc, bool bSelected, bool bFocus, bool bOdd);  
	void InvalidateItem(int nItem);  

	void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);  
public:  
	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);  
	virtual void PreSubclassWindow();  
//	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);  
	// ��ȡ��ǰѡ���SubItem
	int GetSelectSubItem(void);

	// ��ȡ�е���Ŀ
	int GetColumnCount(void);

	// ����Column ��С
	void AdjustColumnSize(int icx);
	// ɾ�����е���
	int DeleteAllColumn(void);


	// ����ѡ��SubItem ����Ϊ -1�����ʾͨ������ȡ
	int SetSelectedSumItem(int iSubItem);
	// ��ȡ���ʱ��ȡ����SubItem ���ش��ڵ��� 0 ������ -1 Ϊʧ�ܣ�����ֵ ����
	int GetHitTestSubItem(void);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	};  




