/**********************************************************
 ListBoxXI.cpp : implementation file
 Written by WangYao (wangyao1052@163.com)
 Version: V1.0 2014-06-07
**********************************************************/

#include "stdafx.h"
#include "ListBoxXI.h"
#include "math.h"

#define	LBXI_CX_BORDER   2
#define	LBXI_CY_BORDER   2


// CListBoxXI

IMPLEMENT_DYNAMIC(CListBoxXI, CListBox)

CListBoxXI::CListBoxXI()
{
	m_pImageList = NULL;
	m_imageSize.cx = 0;
	m_imageSize.cy = 0;
	iMeasureItem   = _LISTBOX_XI_SHOW;
}

CListBoxXI::~CListBoxXI()
{
}

//---------------------------------------------------------
// ����: SetImageList
// ����: ���ù�����ImageList
// ����: 
//       pImageList --- ImageList��ָ��
// ����: ��
//---------------------------------------------------------
void CListBoxXI::SetImageList(CImageList* pImageList)
{
	m_pImageList = pImageList;
	if (m_pImageList)
	{
		int cx;
		int cy;
		ImageList_GetIconSize(*m_pImageList, &cx, &cy);
		m_imageSize.cx = cx;
		m_imageSize.cy = cy;
	}
	else
	{
		m_imageSize.cx = 0;
		m_imageSize.cy = 0;
	}

	memset(iImageStatue, 01, 100);

	Invalidate();
}

//---------------------------------------------------------
// ����: GetImageList
// ����: ��ȡ����ImageList��ָ��
// ����: ��
// ����: ����ImageList��ָ��,��û�й���ImageList����NULL
//---------------------------------------------------------
CImageList* CListBoxXI::GetImageList() const
{
	return m_pImageList;
}

//---------------------------------------------------------
// ����: GetItemImage
// ����: ��ȡ���ͼƬ����
// ����: 
//       nIndex  --- ������(��0Ϊ���)
// ����:
//       ��0Ϊ��ʼ��ͼƬ�������
//       �����ڴ���,��nIndex������Χ,����-1
//       ����û�й���ͼƬ,����-1
//---------------------------------------------------------
int CListBoxXI::GetItemImage(int nIndex)
{
	LBDataXI* pLBData = (LBDataXI*)CListBox::GetItemData(nIndex);
	if (pLBData == (LBDataXI*)LB_ERR || pLBData == NULL)
	{
		return -1;
	}

	return pLBData->iImageIndex;
}

//---------------------------------------------------------
// ����: SetItemImage
// ����: �������ͼƬ����
// ����: 
//       nIndex      --- ������(��0Ϊ���)
//       nImageIndex --- ͼƬ����(��0Ϊ���)
//       bRepaint    --- �Ƿ��ػ�
// ����:
//       �ɹ�����0,ʧ�ܷ���-1
//---------------------------------------------------------
int CListBoxXI::SetItemImage(int nIndex, int nImageIndex, BOOL bRepaint)
{
	LBDataXI* pLBData = (LBDataXI*)CListBox::GetItemData(nIndex);
	if (pLBData == (LBDataXI*)LB_ERR || pLBData == NULL)
	{
		return -1;
	}
	pLBData->iImageIndex = nImageIndex;

	if (bRepaint)
	{
		Invalidate();
	}

	return 0;
}


int CListBoxXI::GetItemStatue(int nIndex)
{
	LBDataXI* pLBData = (LBDataXI*)CListBox::GetItemData(nIndex);
	if (pLBData == (LBDataXI*)LB_ERR || pLBData == NULL)
	{
		return -1;
	}

	return pLBData->iStatue;
}

int CListBoxXI::SetItemStatue(int nIndex,int nStatue,BOOL bRepaint)
{
	LBDataXI* pLBData = (LBDataXI*)CListBox::GetItemData(nIndex);
	if (pLBData == (LBDataXI*)LB_ERR || pLBData == NULL)
	{
		return -1;
	}
	if (pLBData->iStatue == nStatue)
	{
		return TRUE;
	}

	pLBData->iStatue = nStatue;

	CString csText;

	GetText(nIndex, csText);

	InsertString(nIndex + 1, csText, pLBData->iImageIndex, nStatue);

	DeleteString(nIndex);

	if (bRepaint)
	{
		Invalidate();
	}

	return TRUE;
}



//---------------------------------------------------------
// ����: AddString
// ����: �����
// ����: lpszString  --- �ַ���ָ��
//        nImageIndex --- ͼƬ����(��0Ϊ���)
// ����: �����������ֵ
//        ʧ���򷵻�LB_ERR��LB_ERRSPACE
//---------------------------------------------------------
int CListBoxXI::AddString(LPCTSTR lpszString, int nImageIndex /*= 0*/, int nStatue /*= _LISTBOX_XI_SHOW*/, BOOL bRepain /*= TRUE*/)
{
	iMeasureItem = nStatue;
	int nIndex = CListBox::AddString(lpszString);

	if (nIndex != LB_ERR && nIndex != LB_ERRSPACE)
	{

		LBDataXI *pData = new LBDataXI();
		pData->iImageIndex = nImageIndex;
		pData->pData = NULL;
		pData->iStatue = nStatue;
		CListBox::SetItemData(nIndex, (DWORD_PTR)pData);
	}
	if (bRepain)
		Invalidate();

	return nIndex;
}

//---------------------------------------------------------
// ����: InsertString
// ����: ��ָ��λ�ò�����
// ����: 
//       nIndex      --- ָ��λ��
//       lpszString  --- �ַ���ָ��
//       nImageIndex --- ͼƬ����(��0Ϊ���)
// ����: 
//       ����������ֵ
//       ʧ���򷵻�LB_ERR��LB_ERRSPACE
//---------------------------------------------------------
int CListBoxXI::InsertString(int nIndex, LPCTSTR lpszString, int nImageIndex, int nStatue /*= 1*/)
{
	iMeasureItem = nStatue;
	int nRet = CListBox::InsertString(nIndex, lpszString);
	if (nRet != LB_ERR && nRet != LB_ERRSPACE)
	{
		LBDataXI *pData = new LBDataXI();
		pData->iImageIndex = nImageIndex;
		pData->pData = NULL;
		pData->iStatue = nStatue;
		
		CListBox::SetItemData(nIndex, (DWORD_PTR)pData);
	}

	return nRet;
}

//---------------------------------------------------------
// ����: DeleteString
// ����: ɾ����
// ����: 
//       nIndex  --- ����
// ����: 
//       �ɹ��򷵻ص�ǰ��ʣ������
//       ʧ���򷵻�LB_ERR
//---------------------------------------------------------
int CListBoxXI::DeleteString(UINT nIndex)
{
	DeleteItemData(nIndex);

	return CListBox::DeleteString(nIndex);
}

//---------------------------------------------------------
// ����: ResetContent
// ����: �������
//---------------------------------------------------------
void CListBoxXI::ResetContent()
{
	int nCnt = CListBox::GetCount();
	for (int i = 0; i < nCnt; ++i)
	{
		DeleteItemData(i);
	}

	CListBox::ResetContent();
}

//---------------------------------------------------------
// ����: GetItemData
// ����: ��ȡ�����������
// ����:
//       nIndex --- ����
// ����:
//       ����������,ʧ���򷵻�LB_ERR
//---------------------------------------------------------
DWORD_PTR CListBoxXI::GetItemData(int nIndex) const
{
	LBDataXI* pLBData = (LBDataXI*)CListBox::GetItemData(nIndex);
	if (pLBData == (LBDataXI*)LB_ERR || pLBData == NULL)
	{
		return LB_ERR;
	}

	return (DWORD_PTR)pLBData->pData;
}

//---------------------------------------------------------
// ����: SetItemData
// ����: ���������������
// ����:
//       nIndex     --- ����
//       dwItemData --- ���������� 
// ����:
//       �ɹ�����LB_OKAY, ʧ�ܷ���LB_ERR
//---------------------------------------------------------
int CListBoxXI::SetItemData(int nIndex, DWORD_PTR dwItemData)
{
	LBDataXI* pLBData = (LBDataXI*)CListBox::GetItemData(nIndex);
	if (pLBData == (LBDataXI*)LB_ERR || pLBData == NULL)
	{
		return LB_ERR;
	}

	pLBData->pData = (LPVOID)dwItemData;
	return LB_OKAY;
}

//---------------------------------------------------------
// ����: GetItemDataPtr
// ����: ��ȡ�����������
// ����:
//       nIndex --- ����
// ����:
//       ����������,ʧ���򷵻�LB_ERR
//---------------------------------------------------------
void* CListBoxXI::GetItemDataPtr(int nIndex) const
{
	LBDataXI* pLBData = (LBDataXI*)CListBox::GetItemDataPtr(nIndex);
	if (pLBData == (LBDataXI*)LB_ERR || pLBData == NULL)
	{
		return (void*)LB_ERR;
	}

	return pLBData->pData;
}

//---------------------------------------------------------
// ����: SetItemDataPtr
// ����: ���������������
// ����:
//       nIndex --- ����
//       pData  --- ����������
// ����:
//       �ɹ�����LB_OKAY, ʧ���򷵻�LB_ERR
//---------------------------------------------------------
int CListBoxXI::SetItemDataPtr(int nIndex, void* pData)
{
	LBDataXI* pLBData = (LBDataXI*)CListBox::GetItemDataPtr(nIndex);
	if (pLBData == (LBDataXI*)LB_ERR || pLBData == NULL)
	{
		return LB_ERR;
	}

	pLBData->pData = pData;
	return LB_OKAY;
}

void CListBoxXI::DeleteItemData(int nIndex)
{
	LBDataXI* pLBData = (LBDataXI*)CListBox::GetItemData(nIndex);
	if (pLBData != (LBDataXI*)LB_ERR)
	{
		delete pLBData;
		CListBox::SetItemData(nIndex, (DWORD_PTR)NULL);
	}
}

void CListBoxXI::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);


	pDC->SetBkMode(TRANSPARENT);
	RECT& rcItem = lpDrawItemStruct->rcItem;

	LBDataXI* pData;
	pData = (LBDataXI*)CListBox::GetItemDataPtr(lpDrawItemStruct->itemID);
	if ((pData == NULL) ||
		(pData == (LBDataXI*)0xFFFFFFFF))
	{
		return;
	}


	// �Ƿ���ѡ��״̬
	BOOL bIsSelected = (lpDrawItemStruct->itemAction | ODA_SELECT) 
		&& (lpDrawItemStruct->itemState & ODS_SELECTED);

	// �Ƿ��ڽ���״̬
	BOOL bIsFocused = (lpDrawItemStruct->itemAction | ODA_FOCUS) 
		&& (lpDrawItemStruct->itemState & ODS_FOCUS);

	// ���Ʊ���
	if (bIsSelected)
	{
		COLORREF oldColor = pDC->GetBkColor();
		pDC->FillSolidRect(&rcItem, ::GetSysColor(COLOR_HIGHLIGHT));
		pDC->SetBkColor(oldColor);
	}
	else
	{
		pDC->FillSolidRect(&rcItem, pDC->GetBkColor());
	}

	if (pData->iStatue == _LISTBOX_XI_HIDE)
		return;

	// ����ICON
	CRect rcIcon(rcItem.left, rcItem.top, rcItem.left, rcItem.top);


	if (m_pImageList)
	{
		HICON hIcon = m_pImageList->ExtractIcon(pData->iImageIndex);
		if (hIcon)
		{
			rcIcon.right = rcItem.left + m_imageSize.cx + 2 * LBXI_CX_BORDER;
			rcIcon.bottom = rcItem.top + m_imageSize.cy + 2 * LBXI_CY_BORDER;


			CPoint pos(rcIcon.left + LBXI_CX_BORDER, rcIcon.top + LBXI_CY_BORDER);
			pDC->DrawState(pos, m_imageSize, hIcon, DSS_NORMAL, (CBrush*)NULL);
			::DestroyIcon(hIcon);
		}
	}

	// ����Text
	if (bIsSelected)
	{
		pDC->SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
	}
	else
	{
		pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
	}




	CString cstrItemText;
	CListBox::GetText(lpDrawItemStruct->itemID, cstrItemText);

	//��������˻��з����ʾ��Ϊ����
	BOOL bSingleLine = (cstrItemText.Find(_T("\n")) < 0);


	CRect rcText(rcItem);
	rcText.left = rcIcon.right;

	//���Ϊ���У��˴���Ϊ�м䲼�֣����ֻᶨ�����Դ˴������ֳߴ�����һ������Ŀ��
	rcText.top = rcIcon.top+ (!bSingleLine)*LBXI_CY_BORDER;
	CSize szText = pDC->GetTextExtent(cstrItemText);

	if (bSingleLine)
		pDC->DrawText(cstrItemText, rcText, DT_LEFT | DT_VCENTER | DT_SINGLELINE | DT_WORDBREAK);
	else
		pDC->DrawText(cstrItemText, rcText, DT_LEFT );


}

CSize CListBoxXI::GetFontSize()
{
	//GetFont();
	CSize csRet;
	CFont* cFont =  CListBox::GetFont();
	LOGFONT  _temp;
	cFont->GetLogFont(&_temp);
	csRet.cy = abs(_temp.lfHeight) ;
	csRet.cx = _temp.lfWidth;
	

	return csRet;

}

void CListBoxXI::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	CDC *pDC = GetDC();

	CString szItemText;
	GetText(lpMeasureItemStruct->itemID, szItemText);
	CSize sText = pDC->GetTextExtent(szItemText);

	//CSize szText = GetFontSize();
	ReleaseDC(pDC);

	LBDataXI* pData;
	pData = (LBDataXI*)CListBox::GetItemDataPtr(lpMeasureItemStruct->itemID);
	lpMeasureItemStruct->itemHeight = 0;
	CRect rectTemp;
	GetWindowRect(rectTemp);

	//�����ǰ״̬Ϊ���أ���ǰ���Ϊ0��
	if (iMeasureItem == _LISTBOX_XI_HIDE)
	{
		iMeasureItem = _LISTBOX_XI_SHOW;
		return;
	}


	//�����Ϊ���ؿ�ʼ������
	lpMeasureItemStruct->itemHeight = sText.cy > m_imageSize.cy + 2 * LBXI_CY_BORDER ? sText.cy : m_imageSize.cy + 2 * LBXI_CY_BORDER;

	//lpMeasureItemStruct->itemHeight = 16;
	int iEnter = 0;
	for (int i = 0; i < szItemText.GetLength(); i++)
	{
		i = szItemText.Find("\n", i + 1);
		if (i < 0)
			break;

		iEnter++;
	}

	CSize sFont = GetFontSize();

	lpMeasureItemStruct->itemHeight += sFont.cy * iEnter;

}

BOOL CListBoxXI::PreCreateWindow(CREATESTRUCT& cs)
{


	if (!CListBox::PreCreateWindow(cs))
		return FALSE;


	cs.style |= LBS_MULTIPLESEL;
	cs.style |= LBS_OWNERDRAWVARIABLE;
	cs.style |= LBS_HASSTRINGS;


	return TRUE;
}


BEGIN_MESSAGE_MAP(CListBoxXI, CListBox)
	ON_WM_SETFOCUS()
	ON_WM_MEASUREITEM()
	ON_WM_PAINT()
	ON_WM_PAINTCLIPBOARD()
	ON_WM_MEASUREITEM()
END_MESSAGE_MAP()

// CListBoxXI message handlers

void CListBoxXI::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CListBox::OnPaint()
	CListBox::OnPaint();
}


void CListBoxXI::OnPaintClipboard(CWnd* pClipAppWnd, HGLOBAL hPaintStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CListBox::OnPaintClipboard(pClipAppWnd, hPaintStruct);
}


void CListBoxXI::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CListBox::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}



#if _LISTBOX_XI_EX
int CListBoxXI::SetImageStatue(int nImageIndex, int nStatue)
{
	if (nImageIndex > 100)
		return FALSE;

	iImageStatue[nImageIndex] = nStatue;

	return TRUE;
}

int CListBoxXI::_AddString(LPCTSTR lpszString, int nImageIndex)
{
	
	return AddString(lpszString, nImageIndex, iImageStatue[nImageIndex],TRUE);
}
#endif
