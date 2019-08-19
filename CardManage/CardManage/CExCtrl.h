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
	// 获取当前选择的SubItem
	int GetSelectSubItem(void);

	// 获取列的数目
	int GetColumnCount(void);

	// 调整Column 大小
	void AdjustColumnSize(int icx);
	// 删除所有的列
	int DeleteAllColumn(void);


	// 设置选中SubItem 输入为 -1，则表示通过鼠标获取
	int SetSelectedSumItem(int iSubItem);
	// 获取电击时获取到的SubItem 返回大于等于 0 正常， -1 为失败，其他值 错误；
	int GetHitTestSubItem(void);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	};  




