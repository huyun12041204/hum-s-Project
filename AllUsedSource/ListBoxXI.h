#pragma once

#ifndef _LISTBOX_XI

#define  _LISTBOX_XI      01

#define  _LISTBOX_XI_HIDE 00
#define  _LISTBOX_XI_SHOW 01

#define  _LISTBOX_XI_EX   01

// CListBoxXI

class CListBoxXI : public CListBox
{
	DECLARE_DYNAMIC(CListBoxXI)

public:
	CListBoxXI();
	virtual ~CListBoxXI();

	void SetImageList(CImageList* pImageList);
	CImageList* GetImageList() const;
	int GetItemImage(int nIndex);
	int SetItemImage(int nIndex, int nImageIndex, BOOL bRepaint = TRUE);

	int GetItemStatue(int nIndex);
	int SetItemStatue(int nIndex, int nStatue, BOOL bRepaint = TRUE);


	int AddString(LPCTSTR lpszString, int nImageIndex = 0, int nStatue = _LISTBOX_XI_SHOW, BOOL bRepain = TRUE);
	int DeleteString(UINT nIndex);
	int InsertString(int nIndex, LPCTSTR lpszString, int nImageIndex, int nStatue = _LISTBOX_XI_SHOW);
	void ResetContent();

	DWORD_PTR GetItemData(int nIndex) const;
	int SetItemData(int nIndex, DWORD_PTR dwItemData);
	void* GetItemDataPtr(int nIndex) const;
	int SetItemDataPtr(int nIndex, void* pData);

protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	CSize GetFontSize();
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

#if _LISTBOX_XI_EX
public:
	int SetImageStatue(int nImageIndex, int nStatue);
	int _AddString(LPCTSTR lpszString, int nImageIndex);
#endif

	DECLARE_MESSAGE_MAP()

private:
	// 关联的CImageList
	CImageList *m_pImageList;
	CSize       m_imageSize;
//用来提前把状态值输入
	int        iMeasureItem;
	// 每项的关联数据
	struct LBDataXI
	{
		// 图像序号,如果为-1,则表示无图像
		int iImageIndex;
		int iStatue;
		// 关联数据的指针
		LPVOID pData;
		LBDataXI()
		{
			iStatue = 1;
			iImageIndex = -1;
			pData = NULL;
		}
	};

#if _LISTBOX_XI_EX
	BOOL        iImageStatue[100];
#endif

	// 删除关联数据
	void DeleteItemData(int nIndex);
public:
	afx_msg void OnPaint();
	afx_msg void OnPaintClipboard(CWnd* pClipAppWnd, HGLOBAL hPaintStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};



#endif // _LISTBOX_XI