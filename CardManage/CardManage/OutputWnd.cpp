m_pszData
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

#include "stdafx.h"
#include "CardManage.h"
#include "OutputWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "Basconv.h"

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

	// 创建选项卡窗口:
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_3D_VS2005, rectDummy, this, 1,CMFCTabCtrl::LOCATION_BOTTOM))
	{
		TRACE0("未能创建输出选项卡窗口\n");
		return -1;      // 未能创建
	}

	// 创建输出窗格:
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT |LBS_MULTIPLESEL|
		                  WS_CHILD|WS_VISIBLE|WS_HSCROLL| 
						  WS_VSCROLL|WS_CLIPSIBLINGS|WS_CLIPCHILDREN;

	if (!m_wndOutputOper.Create(dwStyle, rectDummy, &m_wndTabs, 2) ||
		!m_wndOutputAPDU.Create(dwStyle, rectDummy, &m_wndTabs, 3) ||
		!m_wndOutputAll.Create(dwStyle, rectDummy, &m_wndTabs,  4))
	{
		TRACE0("未能创建输出窗口\n");
		return -1;      // 未能创建
	}



//	UpdateFonts();

	CString strTabName;
	BOOL bNameValid;

	// 将列表窗口附加到选项卡:
	bNameValid = strTabName.LoadString(IDS_BUILD_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputOper, strTabName, (UINT)0);
	bNameValid = strTabName.LoadString(IDS_DEBUG_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputAPDU, strTabName, (UINT)1);
	bNameValid = strTabName.LoadString(IDS_FIND_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputAll, strTabName, (UINT)2);

	SetImageList();
	// 使用一些虚拟文本填写输出选项卡(无需复杂数据)
	return 0;
}
void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// 选项卡控件应覆盖整个工作区:
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
void COutputWnd::UpdateFonts()
{	

	m_wndOutputOper.SetFont(&afxGlobalData.fontRegular);
	m_wndOutputAPDU.SetFont(&afxGlobalData.fontRegular);
	m_wndOutputAll.SetFont(&afxGlobalData.fontRegular);

}
void COutputWnd::Print2Output(CString csLog,CString csSend,CString csResp)
{


	if (!csLog.IsEmpty())
	{
		m_wndOutputOper.FomatAddString(csLog);
	    m_wndOutputAll.FomatAddString(csLog);
	}


	if (!csSend.IsEmpty())
	{
		PrintAPDU(csSend,csResp);
		//if (csSend.Left(1) == _T("$"))
		//{
		//	//m_wndOutputAPDU.AddString(_T("ATR : ")+csResp);
		//	//m_wndOutputAll.AddString (_T("ATR : ")+csResp);
		//	
		//}
		//else 
		//{
		//	_AppendSpace(csSend);	
		//	_AppendSpace(csResp);
		//	m_wndOutputAPDU.AddString(_T("Send : ")+csSend);
		//	m_wndOutputAPDU.AddString(_T("Resp : ")+csResp);
		//	m_wndOutputAll.AddString(_T("Send : ")+csSend);
		//	m_wndOutputAll.AddString(_T("Resp : ")+csResp);
	
		//}
	}



	//int iRet;
	//iRet = m_wndOutputAll .SetCaretIndex(m_wndOutputAll .GetCount());
	//iRet = m_wndOutputAPDU.SetCaretIndex(m_wndOutputAPDU.GetCount());
	//iRet = m_wndOutputOper.SetCaretIndex(m_wndOutputOper.GetCount());
}
void COutputWnd::PrintTime2Output(long lTime)
{

	if (lTime > 0)
	{
		CString csTime;
		csTime.Format("Time : %d us",lTime);
		m_wndOutputAll.AddString(csTime);
		m_wndOutputAll.SetCaretIndex(m_wndOutputAll.GetCount());
	}

	//m_wndOutputAll.AddString(_T("---------------------------------------------------------------------------------------"));
	//m_wndOutputAll.AddString(_T("---------------------------------------------------------------------------------------"));

}
void COutputWnd::ResetContent()
{
	m_wndOutputOper.ResetContent();
	m_wndOutputAPDU.ResetContent();
	m_wndOutputAll .ResetContent();

}
void COutputWnd::PrintAPDU(CString csSend,CString csResp)
{


	if (!csSend.IsEmpty())
	{
		if (csSend.Left(1) == _T("$"))
		{
			PrintATRInformation(csResp);
			m_wndOutputAPDU.FomatAddString(csResp,_DEF_APDU_ATR);
			m_wndOutputAll .FomatAddString(csResp,_DEF_APDU_ATR);

		}
		else 
		{
			_DeleteEnterSpace(csSend);
			_DeleteEnterSpace(csResp);
			PrintInformation(csSend,csResp);
			m_wndOutputAPDU.FomatAddString(csSend,_DEF_APDU_SEND);
			m_wndOutputAPDU.FomatAddString(csResp,_DEF_APDU_RESP);
			m_wndOutputAll .FomatAddString(csSend,_DEF_APDU_SEND);
			m_wndOutputAll .FomatAddString(csResp,_DEF_APDU_RESP);
		}
	}

	int iRet;
	iRet = m_wndOutputAll .SetCaretIndex(m_wndOutputAll .GetCount());
	iRet = m_wndOutputAPDU.SetCaretIndex(m_wndOutputAPDU.GetCount());
	iRet = m_wndOutputOper.SetCaretIndex(m_wndOutputOper.GetCount());

}
void COutputWnd::PrintInformation( CString csSend,CString csResp )
{
	CStringArray csInformation;
	CString csText;

	if (_ExplainAPDU(csSend,csResp,csInformation) < 0)
	{
	}
	int iCount = csInformation.GetCount();
	for (int i = 0 ; i < iCount; i++)
	{
		csText = csInformation.GetAt(i);
		if (i==0)
			m_wndOutputOper.FomatAddString(csText);
		m_wndOutputAll .FomatAddString(csText);	
	}
}
void COutputWnd:: PrintATRInformation(CString csATR)
{

	CStringArray csInformation;
	CString csText;
	if (ExplainATR(csATR,csInformation))
	{
		int iCount = csInformation.GetCount();
		for (int i = 0 ; i < iCount; i++)
		{
			csText = csInformation.GetAt(i);
			//m_wndOutputOper.FomatAddString(csText);	
			m_wndOutputAll .FomatAddString(csText);	
		}

	}
	
}
void COutputWnd::SetImageList()
{


	m_OutputImages.DeleteImageList();

	//	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

	UINT uiBmpId = IDB_BITMAP3;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("无法加载位图: %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_OutputImages.Create(12, bmpObj.bmHeight, nFlags, 0, 0);
	m_OutputImages.Add(&bmp, RGB(0, 0, 0));

	m_wndOutputAll.SetImageList(&m_OutputImages);
	m_wndOutputOper.SetImageList(&m_OutputImages);
	m_wndOutputAPDU.SetImageList(&m_OutputImages);
}


/////////////////////////////////////////////////////////////////////////////
// COutputList1



BEGIN_MESSAGE_MAP(COutputList, CListBoxXI)
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
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputList 消息处理程序

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
		MessageBox(_T("复制失败"));

}
void COutputList::OnEditClear()
{
	CWnd* pWnd = this->GetParent() ->GetParent();
	CMainFrame* pMain = (CMainFrame*) AfxGetApp()->GetMainWnd();
	if (pWnd == (pMain->GetOutputWnd()))
		((COutputWnd*)pWnd) ->ResetContent();
	else
		ResetContent();


	MessageBox(_T("清除完成"));

}
void COutputList::OnEditSave()
{
	CString csFileName;
	CString csFileData;
	CStdioFile CSFFile;
	int iIndex,iIndexLen;
	CFileDialog CFDataFile(FALSE,_T("*.txt|.txt"),NULL,4|2,_T("文本文件(*.txt)|*.txt||"));


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
			MessageBox(_T("保存失败"));

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
	CString csCur;
	int iCount = 0 ;
	switch(iNT)
	{

	case _DEF_APDU_ATR: 
	case _DEF_APDU_PPS: 
	case _DEF_APDU_SEND:
	case _DEF_APDU_RESP:
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
		iCount+= FomatDesription(csName,csInfo,csArray);
	
		break;
	}


	for ( int i= 0 ; i <iCount;i++)
	{
		//没有发现: 则表示为后续
		csCur = csArray.GetAt(i);
		if (csCur.Find(_T(":"))<0)
		    AddString(csCur,0);
		else
			AddString(csArray.GetAt(i),iNT);

		  
	}

	if ((iNT == _DEF_APDU_RESP)||
		(iNT == _DEF_APDU_ATR)||
		(iNT == _DEF_APDU_PPS))
		AddString(_T("---------------------------------------------------------------------------------------"),-1);


}
void COutputList::FomatATR(CString csText)
{
	CString csFomat;
	csFomat = _T("ATR: ");
	csText  = csFomat+csText;
}
int  COutputList::FomatAPDU(CString csText,CStringArray& csArray,int iNT)
{
	CString csFomat,csTemp,csSW;
	int iCount;
	if (iNT == _DEF_APDU_RESP)
	{
		csTemp  = csText.Right(4);
		_AppendSpace(csTemp);
		csSW    =  _T("SW:  ")+csTemp;
		csText  = csText.Left(csText.GetLength() -4);
	}

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
			case _DEF_APDU_ATR: csFomat = _T("ATR:");break;
			case _DEF_APDU_SEND:csFomat = _T("Send:");break;
			case _DEF_APDU_RESP:csFomat = _T("Resp:");break;
			case _DEF_APDU_PPS: csFomat = _T("PPS:");break;
			}
			csFomat = csFomat+GetSpaceText (_DEF_NAME_LENGTH-GetTextWidth(csFomat));
		}
		else if(i == 1)
			csFomat = GetSpaceText (GetTextWidth( csFomat ));

		csTemp = csText.Mid(i*64,64);
		_AppendSpace(csTemp);
		csArray.Add(csFomat+csTemp);
	}
	if (iNT == _DEF_APDU_RESP)
	{
		csArray.Add(csSW);
		iCount ++;
	}

	return iCount;
}
int COutputList::FomatDesription(CString csName, CString csText,CStringArray& csArray)
{
	int iNum= 0;
	int iOff = 0;
	int iLength = csText.GetLength();
	int iSign   =0x40; 

	if (_IsAllHex(csText))
	{
		CString csEmptyName;
		csEmptyName.Empty();
		_APDUExplainFormat(csEmptyName);

		do 
		{
			if (iNum == 0)
				csArray.Add(csName+csText.Mid(iNum*0x40,0x40));
			else
				csArray.Add(csEmptyName+csText.Mid(iNum*0x40,0x40));

			iOff += 0x40;
			iNum += 1;
		} while (iLength > iOff);
		return iNum;
	}
	else
	{
		csArray.Add(csName+csText);
		return 1;
	}

	

	

	/*CString csFormat = _T(" ");
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
	} while (iLength > iOff);*/

	//return iNum;
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

UINT COutputList::ItemFromPoint(CPoint pt, BOOL& bOutside)
{
	UINT iItem = CListBox::ItemFromPoint(pt,bOutside);
	UINT iTop  = GetTopIndex();
	iTop       = iTop/0xFFFF;



	return iTop*0xFFFF + iItem;
}
void COutputList::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//此处需要加入Focus 否则滚轮会失效， 
	//必须把当前控件作为焦点
	SetFocus();

	BOOL bOut;
	int iSelItem = ItemFromPoint(point,bOut);

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
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CListBox::OnLButtonDblClk(nFlags, point);
	OnEditCopy();
}
BOOL COutputList::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

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
	//	 MessageBox("处错误!");

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
	long lSight = GetTextWidth(" ");
	//调试无法获取CDC 所以无法计算宽度,
	if (lSight== 0)
		lSight = 8;

	return  RepeatCString(_T(" "), lTextWidth/ lSight);
}
#include "stdafx.h"
//#include "CardManage.h"
#include "OutputWnd.h"


// CGetFlashWnd
                              
IMPLEMENT_DYNAMIC(CGetFlashWnd, CDockablePane)

CGetFlashWnd::CGetFlashWnd()
{

}

CGetFlashWnd::~CGetFlashWnd()
{
}


BEGIN_MESSAGE_MAP(CGetFlashWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int CGetFlashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	// 创建输出窗格:
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT |LBS_MULTIPLESEL|
		                  WS_CHILD|WS_VISIBLE|WS_HSCROLL| 
	                      WS_VSCROLL|WS_CLIPSIBLINGS|WS_CLIPCHILDREN;


	if (!m_wndGetFlash.Create(dwStyle, rectDummy, this, 1))

	{
		TRACE0("未能创建输出窗口\n");
		return -1;      // 未能创建
	}



	UpdateFonts();
	return 0;
}

void CGetFlashWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	// 选项卡控件应覆盖整个工作区:
	m_wndGetFlash.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}

void CGetFlashWnd::AdjustHorzScroll(CListBox& wndListBox)
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


void CGetFlashWnd::UpdateFonts()
{	

	m_wndGetFlash.SetFont(&afxGlobalData.fontRegular);

}

void CGetFlashWnd::SetFlashData(CString csInput)
{
	csFlashdata = csInput;
}

void CGetFlashWnd::ResetOffset()
{
	uiOffset = 0;
}

BOOL CGetFlashWnd::GetAPDUFromData(CString csText, CString& csSend, CString &csResp,int* iOffset)
{
	int iIns,iP1,iP2,iP3,iPro;
	CString csSendHead;
	CString csDataFeild;
	bool bP3IsLe;

	if ((10+*iOffset) > csText.GetLength())
		return FALSE;
	csSendHead = csText.Mid(*iOffset,10);
	iIns       = _CString2Int(csSendHead.Mid(2,2)) ;
	iP1        = _CString2Int(csSendHead.Mid(4,2)) ;
	iP2        = _CString2Int(csSendHead.Mid(6,2)) ;
	iPro       = _CString2Int(csText.Mid(*iOffset+10,2));
			
	if (iPro != iIns)
	{
		csSend = csSendHead;
		csResp = csText.Mid(*iOffset+10,4);
		*iOffset += 14;
		//return TRUE;
	}else
	{
		*iOffset  +=12;

		iP3        = _CString2Int(csSendHead.Mid(8,2)) ;
		if (iP3 == 00)
			iP3 = 0x100;
		if ((iP3*2+*iOffset+4) > csText.GetLength())
			return FALSE;
		csDataFeild= csText.Mid(*iOffset,iP3*2);

		*iOffset  +=iP3*2;
		csResp     = csText.Mid(*iOffset,4);
		*iOffset  +=4;
		csSend     = csSendHead;

		switch(iIns)
		{
		case 0xA4:
			if ((iP1 == 3)&&(iP2 == 4))
				bP3IsLe = true ;
			else
				bP3IsLe = false;
			break;
		case 0x75:
			if ((iP1&4)== 0)
				bP3IsLe = true ;
			else
				bP3IsLe = false;
			break;
		case 0xCB:
			if ((iP2&0xDF)== 0)
				bP3IsLe = true ;
			else
				bP3IsLe = false;
			break;
		case 0x70:
		case 0x84:
		case 0xF2:
		case 0xC0:
		case 0x12:
		case 0xFA:
		case 0xB2:
		case 0xB0: bP3IsLe = true ;break;
		case 0xF8: bP3IsLe = true ;break;
		default:   bP3IsLe = false;break;
		}

		if (bP3IsLe)
			csResp = csDataFeild+csResp;
		else
			csSend = csSend + csDataFeild;

		
	}

	return TRUE;
}

void CGetFlashWnd::DisplayFlashData(CString csInput)
{
	int iOffset = uiOffset ;
	int iLength = csInput.GetLength();
	int iTime;
	CString csClass;
	CString csTime;
	CString csCommand;
	CString csRespons;
	CStringArray csInfomation;
	int iCommandLen;
	
	if (iOffset == 0)
		m_wndGetFlash.ResetContent();
	
	float fTime;
	

	do 
	{
		csInfomation.RemoveAll();

		if (iLength<(iOffset+6))
			return;

		csTime = csInput.Mid(iOffset,6);
		iOffset+= 6;
		iTime   = _CString2Int(csTime);
		fTime   = (float)((iTime*655));
		fTime   = fTime/100000;
		iTime   = (int)fTime/60;
		csTime.Format("%d:%.2f",iTime,(float)(fTime - iTime*60));
		
		csClass = csInput.Mid(iOffset,2);
		if (iLength < (iOffset+2))
			return;


		switch(_CString2Int(csClass))
		{
		case 0x3B:
			


			iOffset+= 2;
			if (iLength<(iOffset+2))
				return;

			iCommandLen = _CString2Int(csInput.Mid(iOffset,2))*2;
			iOffset+= 2;
			if (iLength<(iOffset+iCommandLen))
				return;

			csCommand = csInput.Mid(iOffset,iCommandLen);
			if (ExplainATR(csCommand,csInfomation))
			{
				for (int i = 0 ; i < csInfomation.GetCount(); i++)
					m_wndGetFlash.FomatAddString(csInfomation.GetAt(i));
			}
			iOffset += iCommandLen;
			m_wndGetFlash.AddString(_T("Time: ")+csTime);
			m_wndGetFlash.FomatAddString(csCommand,_DEF_APDU_ATR);

	

			break;
		case 0xFF:
			iOffset+= 2;
			if (iLength<(iOffset+2))
				return;
			iCommandLen = _CString2Int(csInput.Mid(iOffset,2))*2;
			iOffset+= 2;
			if (iLength<(iOffset+iCommandLen))
				return;
			csCommand = csInput.Mid(iOffset,iCommandLen);
			m_wndGetFlash.AddString(_T("Time: ")+csTime);
			m_wndGetFlash.FomatAddString(csCommand,_DEF_APDU_PPS);
			iOffset+= iCommandLen;
			break;
		default:
			if (GetAPDUFromData(csInput,csCommand,csRespons,&iOffset))
			{

				_ExplainAPDU(csCommand,csRespons,csInfomation);
				
				for (int i = 0 ; i < csInfomation.GetCount(); i++)
					m_wndGetFlash.FomatAddString(csInfomation.GetAt(i));
				m_wndGetFlash.AddString(_T("Time: ")+csTime);
				m_wndGetFlash.FomatAddString(csCommand,_DEF_APDU_SEND);
				m_wndGetFlash.FomatAddString(csRespons,_DEF_APDU_RESP);
			}
			else
				return;
		}


	
		m_wndGetFlash.SetCaretIndex(m_wndGetFlash.GetCount());
		
		uiOffset = iOffset;
	} while (iOffset<(iLength-16));

		
}

void CGetFlashWnd::RemoveAll(CString csAPDU)
{
	m_wndGetFlash.ResetContent();
}


void CGetFlashWnd::__DisplayFlashData(CString csAPDU)
{

	CString csClass;
	CString csCommand;
	CString csRespons;
	CStringArray csInfomation;

	csInfomation.RemoveAll();

	csClass = csAPDU.Mid(00,2);

	switch(_CString2Int(csClass))
	{
	case 0x3B:

		if (ExplainATR(csAPDU,csInfomation))
		{
			for (int i = 0 ; i < csInfomation.GetCount(); i++)
				m_wndGetFlash.FomatAddString(csInfomation.GetAt(i));
		}
		m_wndGetFlash.FomatAddString(csAPDU,_DEF_APDU_ATR);

		break;
	case 0xFF:
		m_wndGetFlash.FomatAddString(csAPDU,_DEF_APDU_PPS);
		break;
	default:



		if (__P3IsLe(csAPDU))
		{
			csCommand = csAPDU.Mid(0,10);
			csRespons = csAPDU.Mid(10);
		}
		else 
		{	csCommand = csAPDU.Left(csAPDU.GetLength() -4);
		    csRespons = csAPDU.Right(4);
		}
		
		if (_ExplainAPDU(csCommand,csRespons,csInfomation))
		{

			for (int i = 0 ; i < csInfomation.GetCount(); i++)
				m_wndGetFlash.FomatAddString(csInfomation.GetAt(i));
			m_wndGetFlash.FomatAddString(csCommand,_DEF_APDU_SEND);
			m_wndGetFlash.FomatAddString(csRespons,_DEF_APDU_RESP);
		}
	}


	
	m_wndGetFlash.SetCaretIndex(m_wndGetFlash.GetCount());



}

// CGetFlashWnd 消息处理程序
BOOL COutputList::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值


	BOOL bRet =CListBox::OnMouseWheel(nFlags, zDelta, pt);

	return bRet;
}
