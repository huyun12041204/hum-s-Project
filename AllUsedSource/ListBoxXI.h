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
	// ������CImageList
	CImageList *m_pImageList;
	CSize       m_imageSize;
//������ǰ��״ֵ̬����
	int        iMeasureItem;
	// ÿ��Ĺ�������
	struct LBDataXI
	{
		// ͼ�����,���Ϊ-1,���ʾ��ͼ��
		int iImageIndex;
		int iStatue;
		// �������ݵ�ָ��
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

	// ɾ����������
	void DeleteItemData(int nIndex);
public:
	afx_msg void OnPaint();
	afx_msg void OnPaintClipboard(CWnd* pClipAppWnd, HGLOBAL hPaintStruct);
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
};



#endif // _LISTBOX_XI