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

#include "stdafx.h"

#include "OutputWnd.h"
#include "Resource.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

COutputWnd::COutputWnd()
{
}

COutputWnd::~COutputWnd()
{
}

BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// ����ѡ�����:
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("δ�ܴ������ѡ�����\n");
		return -1;      // δ�ܴ���
	}

	// �����������:
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;

	if (!m_wndOutputBuild.Create(dwStyle, rectDummy, &m_wndTabs, 2) ||
		!m_wndOutputDebug.Create(dwStyle, rectDummy, &m_wndTabs, 3) ||
		!m_wndOutputFind.Create(dwStyle, rectDummy, &m_wndTabs, 4))
	{
		TRACE0("δ�ܴ����������\n");
		return -1;      // δ�ܴ���
	}

	UpdateFonts();

	CString strTabName;
	BOOL bNameValid;

	// ���б��ڸ��ӵ�ѡ�:
	bNameValid = strTabName.LoadString(IDS_BUILD_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputBuild, strTabName, (UINT)0);
	bNameValid = strTabName.LoadString(IDS_DEBUG_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputDebug, strTabName, (UINT)1);
	bNameValid = strTabName.LoadString(IDS_FIND_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputFind, strTabName, (UINT)2);

	// ʹ��һЩ�����ı���д���ѡ�(���踴������)
	FillBuildWindow();
	FillDebugWindow();
	FillFindWindow();

	return 0;
}

void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// ѡ��ؼ�Ӧ��������������:
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void COutputWnd::AdjustHorzScroll(CListBox& wndListBox)
{
	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&afxGlobalData.fontRegular);

	int cxExtentMax = 0;

	for (int i = 0; i < wndListBox.GetCount(); i ++)
	{
		CString strItem;
		wndListBox.GetText(i, strItem);

		cxExtentMax = max(cxExtentMax, dc.GetTextExtent(strItem).cx);
	}

	wndListBox.SetHorizontalExtent(cxExtentMax);
	dc.SelectObject(pOldFont);
}

void COutputWnd::FillBuildWindow()
{
	m_wndOutputBuild.AddString(_T("�����������ʾ�ڴ˴���"));
	m_wndOutputBuild.AddString(_T("�������ʾ���б���ͼ������"));
	m_wndOutputBuild.AddString(_T("�������Ը�����Ҫ��������ʾ��ʽ..."));
}

void COutputWnd::FillDebugWindow()
{
	m_wndOutputDebug.AddString(_T("�����������ʾ�ڴ˴���"));
	m_wndOutputDebug.AddString(_T("�������ʾ���б���ͼ������"));
	m_wndOutputDebug.AddString(_T("�������Ը�����Ҫ��������ʾ��ʽ..."));
}

void COutputWnd::FillFindWindow()
{
	m_wndOutputFind.AddString(_T("�����������ʾ�ڴ˴���"));
	m_wndOutputFind.AddString(_T("�������ʾ���б���ͼ������"));
	m_wndOutputFind.AddString(_T("�������Ը�����Ҫ��������ʾ��ʽ..."));
}

void COutputWnd::UpdateFonts()
{
	m_wndOutputBuild.SetFont(&afxGlobalData.fontRegular);
	m_wndOutputDebug.SetFont(&afxGlobalData.fontRegular);
	m_wndOutputFind.SetFont(&afxGlobalData.fontRegular);
}

/////////////////////////////////////////////////////////////////////////////
// COutputList1

BEGIN_MESSAGE_MAP(COutputList, CListBox)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_VIEW_OUTPUTWND, OnViewOutput)
	ON_COMMAND(ID_EDIT_Save, &COutputList::OnEditSave)
	ON_CONTROL_REFLECT(LBN_DBLCLK, &COutputList::OnLbnDblclk)
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()	
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputList ��Ϣ�������

void COutputList::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_OUTPUT_POPUP);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	//if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CFrameWndEx)))

	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}

	SetFocus();
}
void COutputList::OnEditCopy()
{
	int iIndex,iLen;
	CString csCopyData;
	CString csTemp;

	iIndex = GetCurSel();
	if (iIndex<1)
		return;

	int nCount = GetSelCount();
	CArray<int,int> aryListBoxSel;

	aryListBoxSel.SetSize(nCount);
	GetSelItems(nCount, aryListBoxSel.GetData()); 
	AFXDUMP(aryListBoxSel);

	//int iSum = GetSelCount();
	csCopyData.Empty();
	for (int i = 0 ; i < nCount ; i++)
	{
		csTemp.Empty();
		iLen   = GetTextLen(aryListBoxSel.GetAt(i));
		GetText(aryListBoxSel.GetAt(i),csTemp.GetBuffer(iLen));
		csTemp.ReleaseBuffer();
		csTemp += _T("\r\n");
		csCopyData += csTemp;
	}



	if(OpenClipboard())
	{
		HGLOBAL clipbuffer;
		char * buffer;
		EmptyClipboard();
		clipbuffer = GlobalAlloc(GMEM_DDESHARE, csCopyData.GetLength()+1); 
		buffer = (char*)GlobalLock(clipbuffer); 
		memcpy(buffer, csCopyData,csCopyData.GetLength()); 
		GlobalUnlock(clipbuffer); 
		SetClipboardData(CF_TEXT,clipbuffer);
		CloseClipboard();

	}
	else
		MessageBox(_T("����ʧ��"));

}
void COutputList::OnEditClear()
{
	//CWnd* pWnd = this->GetParent() ->GetParent();
	//CMainFrame* pMain = (CMainFrame*) AfxGetApp()->GetMainWnd();
	//if (pWnd == (pMain->GetOutputWnd()))
	//	((COutputWnd*)pWnd) ->ResetContent();
	//else
		ResetContent();


	MessageBox(_T("������"));

}
void COutputList::OnEditSave()
{
	CString csFileName;
	CString csFileData;
	CStdioFile CSFFile;
	int iIndex,iIndexLen;
	CFileDialog CFDataFile(FALSE,_T("*.txt|.txt"),NULL,4|2,_T("�ı��ļ�(*.txt)|*.txt||"));


	if ( CFDataFile.DoModal() == IDOK)
	{
		csFileName = CFDataFile.GetPathName();
		if (CSFFile.Open(csFileName,CFile::modeCreate|CFile::modeWrite))
		{

			iIndex = GetCount();

			for (int i= 0 ;i <iIndex; i++ )
			{
				iIndexLen = GetTextLen(i); 
				GetText(i,csFileData.GetBuffer(iIndexLen));
				csFileData.ReleaseBuffer();
				CSFFile.WriteString(csFileData);
				CSFFile.WriteString(_T("\n"));
			}
			CSFFile.Close();
		}
		else
			MessageBox(_T("����ʧ��"));

	}
}
void COutputList::OnViewOutput()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();

	}
}
int  COutputList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{

	if (CListBox::OnCreate(lpCreateStruct) == -1)
		return -1;


	return 0;
}
void COutputList::_APDUExplainFormat(CString&csText,int iFormatLength)
{

	long lWidth = GetTextWidth(csText); 

	if (lWidth > iFormatLength)
		return ;
	else
		csText = csText+GetSpaceText(iFormatLength - lWidth);


}
void COutputList::FomatAddString(CString csText,int iNT)
{

	CStringArray csArray;
	int iCount = 0 ;
	switch(iNT)
	{

	case _DEF_APDU_ATR: 
	case _DEF_APDU_PPS: 
	case _DEF_APDU_HEAD:
	case _DEF_APDU_ACK:
	case _DEF_APDU_NULL:
	case _DEF_APDU_DATA:
	case _DEF_APDU_SW:
		_DeleteEnterSpace(csText);
		iCount = FomatAPDU(csText,csArray,iNT); 
		break;
	case _DEF_DESCRIPTTION:
		int iRet = csText.Find(_T(":"));
		CString csName;
		CString csInfo;
		if (iRet>0)
		{
			csName = csText.Mid(0,iRet+1);
			csInfo = csText.Mid(iRet+1);
			_APDUExplainFormat(csName);
		}
		else 
		{
			iRet = csText.Find(_T(" \\- "));
			if (iRet > 0)
			{
				csName = csText.Mid(0,iRet+1);
				csName = GetSpaceText (_DEF_NAME_LENGTH)+csName;
				csInfo = csText.Mid(iRet+4);
			}
			else
			{

				csInfo = csText;
			}	

			_APDUExplainFormat(csName);
		}
		iCount+= FomatDesription(csName+csInfo,csArray);

		break;
	}


	for ( int i= 0 ; i <iCount;i++)
		AddString(csArray.GetAt(i));


	if ((iNT == _DEF_APDU_SW)||
		(iNT == _DEF_APDU_ATR)||
		(iNT == _DEF_APDU_PPS))
		AddString(_T("---------------------------------------------------------------------------------------"));


}



int  COutputList::FomatAPDU(CString csText,CStringArray& csArray,int iNT)
{
	CString csFomat,csTemp,csSW;
	int iCount;


	if (!csText.IsEmpty())
		iCount  = csText.GetLength()/64 +(csText.GetLength()%64 != 0);
	else
		iCount  = 0;

	for (int i = 0 ; i < iCount; i++)
	{
		if (i == 0)
		{
			switch(iNT)
			{
			case _DEF_APDU_ATR: csFomat = _T("ATR  : ");break;
			case _DEF_APDU_HEAD:csFomat = _T("HEAD : ");break;
			case _DEF_APDU_NULL:csFomat = _T("NULL : ");break;
	    	case _DEF_APDU_ACK:csFomat  = _T("ACK  : ");break;
			case _DEF_APDU_DATA:csFomat = _T("DATA : ");break;
			case _DEF_APDU_SW  :csFomat = _T("SW   : ");break;
			case _DEF_APDU_PPS: csFomat = _T("PPS  : ");break;
			}
			csFomat = csFomat+GetSpaceText (_DEF_NAME_LENGTH-GetTextWidth(csFomat));
		}
		else if(i == 1)
			csFomat = GetSpaceText (GetTextWidth( csFomat ));

		csTemp = csText.Mid(i*64,64);
		_AppendSpace(csTemp);
		csArray.Add(csFomat+csTemp);
	}
	//if (iNT == _DEF_APDU_RESP)
	//{
	//	csArray.Add(csSW);
	//	iCount ++;
	//}

	return iCount;
}
int  COutputList::FomatDesription(CString csText,CStringArray& csArray)
{

	CString csFormat = _T(" ");
	CString csFText;
	int iOff = 0;
	int iLength;
	int iNum= 0;
	_RepeatCString(csFormat,_DEF_FORMATE_LENGTH,csFText);
	csFormat = csText.Left(_DEF_FORMATE_LENGTH);
	csText   = csText.Mid(_DEF_FORMATE_LENGTH);
	iLength  = csText.GetLength();

	do 
	{
		csArray.Add(csFormat+csText.Mid(iOff ,69));
		iOff += 69;
		csFormat = csFText;
		iNum += 1;
	} while (iLength > iOff);

	return iNum;
}
void COutputList::RemvoeAllSelect()
{


	int nCount = GetSelCount();

	if (nCount <= 0)
		return ;

	CArray<int,int> aryListBoxSel;

	aryListBoxSel.SetSize(nCount);
	GetSelItems(nCount, aryListBoxSel.GetData()); 
	AFXDUMP(aryListBoxSel);


	for (int i = 0 ; i < nCount ; i++)
	{
		SetSel(aryListBoxSel.GetAt(i),FALSE);
	}

}
void COutputList::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//�˴���Ҫ����Focus ������ֻ�ʧЧ�� 
	//����ѵ�ǰ�ؼ���Ϊ����
	SetFocus();

	BOOL bOut;
	int iSelItem;
	iSelItem = CListBox::ItemFromPoint(point,bOut);
	if (bOut)
	{
		RemvoeAllSelect();
		return;
	}

	if ((::GetKeyState(VK_CONTROL)>=0)&&((::GetKeyState(VK_SHIFT)>=0)))
		RemvoeAllSelect();

	if ((::GetKeyState(VK_SHIFT)<0))
	{
		int iFirstSel = GetSelectFistItem();
		int iLastSel  = GetSelectLastItem();

		if (iSelItem < iFirstSel)
			for (int i = iFirstSel ; i >= iSelItem ; i--)
				SetSel(i,TRUE);

		if (iLastSel < iSelItem)
			for (int i = iLastSel ; i <= iSelItem ; i++)
				SetSel(i,TRUE);
		TabSelectItem(iSelItem,TRUE);
		return ;
	}

	//if ((::GetKeyState(VK_CONTROL)<0))
	//{
	//}

	BOOL bSeled = GetSel(iSelItem);
	SetSel(iSelItem,!bSeled);

	if (::GetKeyState(VK_MENU) >= 0)
		TabSelectItem(iSelItem,!bSeled);




}
int  COutputList::PreSelect(int iIndex, BOOL bSel)
{



	CString csTemp;
	int iLen ; 
	int i = 0;
	do 
	{
		i ++ ;
		csTemp.Empty();
		iLen = GetTextLen(iIndex-i);
		GetText(iIndex-i,csTemp.GetBuffer(iLen));
		csTemp.ReleaseBuffer();

		SetSel(iIndex-i,bSel);
		if (csTemp.Find(":")>0)
			return TRUE;

	} while ((iIndex-i)>0);


	return FALSE;
}
int  COutputList::PostSelect(int iIndex, BOOL bSel)
{
	CString csTemp;
	int iLen ; 
	int i = 0;
	int iCount = GetCount();
	while ((iIndex+i+1)<iCount)
	{
		i ++ ;
		csTemp.Empty();
		iLen = GetTextLen(iIndex+i);

		GetText(iIndex+i,csTemp.GetBuffer(iLen));
		csTemp.ReleaseBuffer();
		if ((csTemp.Find(":")<=0)&&
			(csTemp.Compare(_T("---------------------------------------------------------------------------------------")) != 0))
		{
			SetSel(iIndex+i,bSel);
		}
		else
			return TRUE;

	} 


	return FALSE;



}
void COutputList::TabSelectItem(int iIndex, BOOL bSel /*= TRUE*/)
{

	if (iIndex<0)
		return ;
	CString csTemp;
	int iLen   = GetTextLen(iIndex);
	GetText(iIndex,csTemp.GetBuffer(iLen));
	csTemp.ReleaseBuffer();
	if (csTemp.Compare(_T("---------------------------------------------------------------------------------------")) == 0)
		return;
	if ((csTemp.Find(":")<0)&&(iIndex>0))
		PreSelect(iIndex, bSel);

	PostSelect(iIndex, bSel);

}
int  COutputList::GetSelectFistItem()
{
	int nCount = GetSelCount();
	if (nCount <=0)
		return -1;

	CArray<int,int> aryListBoxSel;
	aryListBoxSel.SetSize(nCount);
	GetSelItems(nCount, aryListBoxSel.GetData()); 
	AFXDUMP(aryListBoxSel);
	return aryListBoxSel.GetAt(0);
}
int  COutputList::GetSelectLastItem()
{
	int nCount = GetSelCount();
	if (nCount <=0)
		return -1;

	CArray<int,int> aryListBoxSel;
	aryListBoxSel.SetSize(nCount);
	GetSelItems(nCount, aryListBoxSel.GetData()); 
	AFXDUMP(aryListBoxSel);
	return aryListBoxSel.GetAt(nCount-1);
}
void COutputList::OnLbnDblclk()
{
	OnEditCopy();
}
void COutputList::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CListBox::OnLButtonDblClk(nFlags, point);
	OnEditCopy();
}
BOOL COutputList::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	bool bReDone = false;
	if (pMsg->message == WM_KEYDOWN)
	{
		if (::GetKeyState(VK_CONTROL)<0)
		{
			switch(pMsg->wParam) 
			{
			case 'C':OnEditCopy();
				bReDone = true;break;
			default:break;
			}
		}

		if (bReDone)
			return TRUE;
	}

	return CListBox::PreTranslateMessage(pMsg);
}
void COutputList::AdjustHorzScroll()
{
	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&afxGlobalData.fontRegular);

	int cxExtentMax = 0;

	for (int i = 0; i < CListBox::GetCount(); i ++)
	{
		CString strItem;
		CListBox::GetText(i, strItem);
		cxExtentMax = max(cxExtentMax, dc.GetTextExtent(strItem).cx);
	}

	CListBox::SetHorizontalExtent(cxExtentMax+20);
	dc.SelectObject(pOldFont);
}
void COutputList::OnSetFocus(CWnd* pOldWnd)
{
	CListBox::OnSetFocus(pOldWnd);

	AdjustHorzScroll();
}
long COutputList::GetTextWidth( CString csText )
{
	return csText.GetLength()*16;
	//if (csText.IsEmpty())
	//	return 0;
	//CDC* pdc = GetDC();

	//if (pdc == NULL)
	//{
	//	 MessageBox("������!");

	//	 return csText.GetLength()*16;

	//}

	//CSize __Size;
	//CFont *pOldfont = pdc->SelectObject(GetFont());


	//__Size = pdc->GetTextExtent(csText);

	//pdc->SelectObject(pOldfont);
	//return __Size.cx;
}
CString COutputList::GetSpaceText(long lTextWidth)
{
	CString csResult;
	long lSight = GetTextWidth(" ");
	//�����޷���ȡCDC �����޷�������,
	if (lSight== 0)
		lSight = 8;

	_RepeatCString(_T(" "),lTextWidth/ lSight,csResult);

	return  csResult;
}
