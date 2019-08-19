// C:\自写程序\CardManage\CardManage\CExCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "CExCtrl.h"





// SkinListCtrl.cpp : implementation file  

// CSkinListCtrl  
IMPLEMENT_DYNAMIC(CSkinListCtrl, CListCtrl)  
CSkinListCtrl::CSkinListCtrl()  
{  
   LIST_ITEM_HEIGHT = 50;  
}  
CSkinListCtrl::~CSkinListCtrl()  
{  
}  
  
BEGIN_MESSAGE_MAP(CSkinListCtrl, CListCtrl)  
    ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CSkinListCtrl::OnNMCustomdraw)  
    //ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, &CSkinListCtrl::OnLvnItemchanged)  
	ON_NOTIFY_REFLECT(NM_CLICK, &CSkinListCtrl::OnNMClick)
	ON_WM_MEASUREITEM_REFLECT()
END_MESSAGE_MAP()  
  
// CSkinListCtrl message handlers  
void CSkinListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)  
{  
    LPNMLVCUSTOMDRAW lpnmcd = (LPNMLVCUSTOMDRAW) pNMHDR;  
    if (lpnmcd ->nmcd.dwDrawStage == CDDS_PREPAINT)  
    {  
        *pResult =  CDRF_NOTIFYITEMDRAW | CDRF_NOTIFYPOSTPAINT;  
		SetSelectedSumItem(-1);
        return;  
    }  
    else if (lpnmcd->nmcd.dwDrawStage == CDDS_ITEMPREPAINT)  
    {  
        /*CRect rSubItem, rectClient; 
        GetItemRect(lpnmcd->nmcd.dwItemSpec, &rSubItem, LVIR_LABEL); 
        GetClientRect(&rectClient);  
        rSubItem.left = 0; 
        rSubItem.right = rectClient.right; 
        rSubItem.NormalizeRect(); 
        bool bSelected = false; 
        if (GetItemState(lpnmcd->nmcd.dwItemSpec, LVIS_SELECTED)) 
        { 
            bSelected = true; 
        } 
        bool bFocus = false; 
        HWND hWndFocus = ::GetFocus(); 
        if (::IsChild(m_hWnd,hWndFocus) || m_hWnd == hWndFocus) 
        { 
            bFocus = true; 
        } 
        CDC dc; 
        dc.Attach(lpnmcd->nmcd.hdc); 
        draw_row_bg(&dc, rSubItem, bSelected , bFocus, (int) lpnmcd->nmcd.dwItemSpec); 
        dc.Detach();*/  
        *pResult =  CDRF_NOTIFYSUBITEMDRAW;  
        return;  
    }  
    else if (lpnmcd ->nmcd.dwDrawStage == (CDDS_SUBITEM | CDDS_ITEMPREPAINT))  
    {  
        int iItem = lpnmcd->nmcd.dwItemSpec;  
        int iSubItem = lpnmcd->iSubItem;  
        if (iItem >= 0 && iSubItem >= 0)  
        {  
            CRect rSubItem;  
            HDC hDC = lpnmcd->nmcd.hdc;  
            GetSubItemRect(iItem, iSubItem, LVIR_LABEL,rSubItem);  
            if (iSubItem == 0)  
            {  
                rSubItem.left = 0;  
            }  
              
            bool bSelected = false;  
			bool bFocus = false;  
			
			if (GetItemState(iItem, LVIS_SELECTED))  
			{  
				bSelected = true;  
				//if (GetSelectSubItem()==iSubItem)
				//	bFocus = true; 
			}  

			
		
            //CWnd *pWndFocus = GetFocus();  
            //if (IsChild(pWndFocus) || pWndFocus == this)  
            //{  
            //    bFocus = true;  
            //}  
            rSubItem.NormalizeRect();  
            CDC dc;  
            dc.Attach(lpnmcd->nmcd.hdc);  
            DrawSubItem(&dc,iItem,iSubItem,rSubItem,bSelected,bFocus);  
            dc.Detach();  
            *pResult =  CDRF_SKIPDEFAULT;  
            return;  
        }  
    }  
    else if (lpnmcd ->nmcd.dwDrawStage == CDDS_POSTPAINT)  
    {  
       // DrawRemainSpace(lpnmcd);  
        *pResult =  CDRF_SKIPDEFAULT;  
        return;  
    }  
       
    *pResult = 0;  
}  
// overwrite:  
void CSkinListCtrl::DrawSubItem(CDC *pDC, int nItem, int nSubItem, CRect &rSubItem, bool bSelected, bool bFocus)  
{  
  

    pDC->SetBkMode(TRANSPARENT);  
    pDC->SetTextColor(RGB(0, 0, 0));  
    CFont font;  
    font.CreateFont(12,   // nHeight  
        0,                         // nWidth  
        0,                         // nEscapement  
        0,                         // nOrientation  
        FW_NORMAL,                 // nWeight  
        FALSE,                     // bItalic  
        FALSE,                     // bUnderline  
        0,                         // cStrikeOut  
        ANSI_CHARSET,              // nCharSet  
        OUT_DEFAULT_PRECIS,        // nOutPrecision  
        CLIP_DEFAULT_PRECIS,       // nClipPrecision  
        DEFAULT_QUALITY,           // nQuality  
        DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily  
        _T("宋体"));  
    pDC->SelectObject(&font);  
    CString strText;  
    strText = GetItemText(nItem, nSubItem);  
    draw_row_bg(pDC, rSubItem, bSelected, bFocus, nItem);  

	//取出扩展格式进行提取设置

	DWORD dwStyle = GetExtendedStyle();
	UINT  uiStyle;


	uiStyle = DT_SINGLELINE| DT_VCENTER| DT_END_ELLIPSIS;
	//居中 居左 居右
	switch(dwStyle&0x0003)
	{
	case LVCFMT_LEFT: uiStyle |= DT_LEFT;
	case LVCFMT_RIGHT: uiStyle |= DT_RIGHT;
	case LVCFMT_CENTER: uiStyle |= DT_CENTER;
	case LVCFMT_JUSTIFYMASK: uiStyle |= DT_LEFT;
	}



	pDC->DrawText(strText, strText.GetLength(), &rSubItem, uiStyle);
   // pDC->DrawText(strText, strText.GetLength(), &rSubItem, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS);  
    
}  
// 画剩余部分  
void CSkinListCtrl::DrawRemainSpace(LPNMLVCUSTOMDRAW lpnmcd)  
{  
    int nTop = lpnmcd->nmcd.rc.top;  
    int nCount = GetItemCount();  
    if (nCount > 0)  
    {  
        CRect rcItem;  
        GetItemRect(nCount - 1, &rcItem, LVIR_LABEL);  
        nTop = rcItem.bottom;  
    }  
    CRect rectClient;  
    GetClientRect(&rectClient);  
    if (nTop < lpnmcd->nmcd.rc.bottom) // 有剩余  
    {  
        CRect rcRemain = lpnmcd->nmcd.rc;  
        rcRemain.top = nTop;  
        rcRemain.right = rectClient.right;  
        int nRemainItem = rcRemain.Height() / LIST_ITEM_HEIGHT;  
        if (rcRemain.Height() % LIST_ITEM_HEIGHT)  
        {  
            nRemainItem++;  
        }  
        int pos = GetScrollPos(SB_HORZ);  
        CDC dc;  
        dc.Attach(lpnmcd->nmcd.hdc);  
        for (int i = 0; i < nRemainItem; ++i)  
        {  
            CRect rcItem;  
            rcItem.top = rcRemain.top + i * LIST_ITEM_HEIGHT;  
            rcItem.left = rcRemain.left;  
            rcItem.right = rcRemain.right;  
            rcItem.bottom = rcItem.top + LIST_ITEM_HEIGHT;  
            int nColumnCount = GetHeaderCtrl()->GetItemCount();  
            CRect  rcSubItem;  
            for (int j = 0; j < nColumnCount; ++j)  
            {  
                GetHeaderCtrl()->GetItemRect(j, &rcSubItem);  
                rcSubItem.top = rcItem.top;  
                rcSubItem.bottom = rcItem.bottom;  
                rcSubItem.OffsetRect(-pos, 0);  
                if(rcSubItem.right < rcRemain.left || rcSubItem.left > rcRemain.right)  
                    continue;  
                draw_row_bg(&dc, rcSubItem, false, false, i + nCount);            
            }  
            /*if (rcSubItem.right<rectClient.right) 
            { 
                rcSubItem.left=rcSubItem.right; 
                rcSubItem.right=rectClient.right; 
                draw_row_bg(&dc, rcSubItem, false, false, i+nCount);     
            }*/  
        }  
        dc.Detach();  
    }  
}  
void CSkinListCtrl::draw_row_bg(CDC *pDC, RECT rc, bool bSelected, bool bFocus,int nRow)  
{   
	bool bOdd = (nRow % 2 == 0 ? true : false);  
	CRect rect = rc;  
	if (rect.Width() == 0)  
	{  
		return;  
	}  

	draw_row_bg(pDC, rc, bSelected,bFocus,bOdd);  
}  
void CSkinListCtrl::draw_row_bg(CDC *pDC, RECT rc, bool bSelected, bool bFocus, bool bOdd)  
{  
    CRect rect = rc;  
    if (rect.Width() == 0)  
    {  
        return;  
    }  
    int nSave = pDC->SaveDC();  
    if (bSelected)  
    {  
        if (bFocus)  
        {  
            CBrush selectBrush;  
            selectBrush.CreateSolidBrush(RGB(203, 223, 239));  
            pDC->FillRect(&rc, &selectBrush);  
        }  
        else  
        {  
            CBrush selectNoFocusBrush;  
            selectNoFocusBrush.CreateSolidBrush(RGB(206, 206, 206));  
            pDC->FillRect(&rc, &selectNoFocusBrush);  
        }  
    }  
    else if (bOdd)  
    {  
        CBrush oddBrush;  
        oddBrush.CreateSolidBrush(RGB(255, 255, 255));  
        pDC->FillRect(&rc, &oddBrush);  
    }  
    else  
    {  
        CBrush normalBrush;  
        normalBrush.CreateSolidBrush(RGB(243, 243, 243));  
        pDC->FillRect(&rc, &normalBrush);  
    }  
  
    // 画竖线  
    CPen pen;  
    pen.CreatePen(PS_SOLID, 1, RGB(218, 218, 218));  
    pDC->SelectObject(&pen);  
    pDC->MoveTo(rc.right - 1, rc.top);  
    pDC->LineTo(rc.right - 1, rc.bottom);  

	pDC->MoveTo(rc.left, rc.bottom - 1);  
	pDC->LineTo(rc.right, rc.bottom - 1);  

    // 画选中的底部分割线  
    if (bSelected)  
    {  
        CPen bottomPen;  
        bottomPen.CreatePen(PS_SOLID, 1, RGB(255, 255, 255));  
        pDC->SelectObject(&bottomPen);  
        pDC->MoveTo(rc.left, rc.bottom - 1);  
        pDC->LineTo(rc.right, rc.bottom - 1);  
    }  
    pDC->RestoreDC(nSave);  
}  





void CSkinListCtrl::Init()  
{  
    LOGFONT logfont;  
    memset(&logfont, 0, sizeof(logfont));  
    logfont.lfWeight = FW_NORMAL;  
    logfont.lfCharSet = GB2312_CHARSET;  
    _tcscpy_s(logfont.lfFaceName, LF_FACESIZE, _T("宋体"));  
    logfont.lfHeight = -(LIST_ITEM_HEIGHT-1);  
    CFont font;  
    font.CreateFontIndirect(&logfont);  
    SetFont(&font);  
    font.Detach();  
}  
void CSkinListCtrl::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)  
{  
    LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);  
    if (pNMLV->uChanged & LVIF_STATE)  
    {  
        if (((pNMLV->uOldState & LVIS_SELECTED) != (pNMLV->uNewState & LVIS_SELECTED))   
            || ((pNMLV->uOldState & LVIS_STATEIMAGEMASK) != (pNMLV->uNewState & LVIS_STATEIMAGEMASK)))  
        {  
            InvalidateItem(pNMLV->iItem);  
        }  
    }  
    *pResult = 0;  
}  
void CSkinListCtrl::InvalidateItem(int nItem)  
{  
    CRect rcClient;  
    GetClientRect(&rcClient);  
    CRect rcItem;  
    GetItemRect(nItem, &rcItem, LVIR_BOUNDS);  
    rcItem.left = rcClient.left;  
    rcItem.right = rcClient.right;  
    InvalidateRect(&rcItem,FALSE);  
}  


void CSkinListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{

	lpMeasureItemStruct->itemHeight = 20;
}

void CSkinListCtrl::PreSubclassWindow()  
{  
    Init();  
    CListCtrl::PreSubclassWindow();  
}  

// 获取当前选择的SubItem
int CSkinListCtrl::GetSelectSubItem(void)
{

	return iSelectedSubItem;

}


// 调整Column 大小
void CSkinListCtrl::AdjustColumnSize(int icx)
{

	LVCOLUMN pColumn1;
	int iColSum;
	UINT* uiX;
	int i;

	iColSum = ((CHeaderCtrl*)GetHeaderCtrl())->GetItemCount();

	uiX     = new UINT[iColSum];
	ZeroMemory(uiX,iColSum+5);
	icx     = icx;


	if (icx < 70*iColSum)
	{

		uiX[0]     =  icx/iColSum;
		for ( i = 1 ; i<(iColSum-1) ; i++)
			uiX[i] =  uiX[0];
		uiX[iColSum-1] =  icx - (uiX[0]*(iColSum-1));

	}
	else if(iColSum>1)
	{
		uiX[0]     =  70;
		uiX[1]     =  (icx - 70)/(iColSum-1) ;

		for ( i = 2 ; i<(iColSum-1) ; i++)
			uiX[i] =  uiX[1];
		if (iColSum>2) 
			uiX[iColSum-1] =  icx - 70 - (uiX[1]*(iColSum-2));


	}
	else
		uiX[0]     =  icx;

	for (i = 0 ; i < iColSum; i ++)
	{
		pColumn1.mask = LVCF_WIDTH;
		if (GetColumn(i,&pColumn1))
		{
			pColumn1.cx = uiX[i];
			SetColumn(i, &pColumn1);
		}
	}

	delete uiX;
}



// 删除所有的列
int CSkinListCtrl::DeleteAllColumn(void)
{
	int iSum;
	BOOL bRet;
	bRet = TRUE;

	iSum =GetColumnCount();

	for (int i = 0 ; i < iSum ; i++)
		bRet &= DeleteColumn(i);

	return bRet;
}

// 获取列的数目
int CSkinListCtrl::GetColumnCount(void)
{
	int iRet = 0;
	CHeaderCtrl* cTemp;
	cTemp = GetHeaderCtrl() ;
	if (cTemp!= NULL)
		iRet = cTemp->GetItemCount();
	return iRet;
}

// 设置选中SubItem 输入为 -1，则表示通过鼠标获取
int CSkinListCtrl::SetSelectedSumItem(int iSubItem)
{

	if (iSubItem == -1)
		iSelectedSubItem = GetHitTestSubItem();
	if (iSelectedSubItem <0)
		iSelectedSubItem = -1;
	return iSelectedSubItem;

}


// 获取电击时获取到的SubItem 返回大于等于 0 正常， -1 为失败，其他值 错误；
int CSkinListCtrl::GetHitTestSubItem(void)
{
	CPoint cpPoint;
	UINT uFlag ;
	int iSum,iWidth,iCurWidth;


	GetCursorPos(&cpPoint);
	CSkinListCtrl::ScreenToClient(&cpPoint);
	CSkinListCtrl::HitTest(cpPoint,&uFlag);
	iSum = GetColumnCount();
	iWidth    = 0;
	iCurWidth = 0;

	for (int i = 0 ; i < iSum ; i++)
	{
		iCurWidth  = GetColumnWidth(i);


		if ((cpPoint.x>=iWidth)&& (cpPoint.x<= (iWidth+= iCurWidth)))
			return i;	
	}

	return -1;

}


void CSkinListCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

//	SetSelectedSumItem(-1);


	*pResult = 0;
}




void CSkinListCtrl::DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/)
{

	// TODO:  添加您的代码以绘制指定项
}

