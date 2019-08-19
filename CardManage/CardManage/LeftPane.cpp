// LeftPane.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "LeftPane.h"
#include "MainFrm.h"

// CLeftPane

IMPLEMENT_DYNAMIC(CLeftPane, CDockablePane)

CLeftPane::CLeftPane()
{

	EnableAutomation();
}

CLeftPane::~CLeftPane()
{
}

//void CLeftPane::OnFinalRelease()
//{
//	// 释放了对自动化对象的最后一个引用后，将调用
//	// OnFinalRelease。基类将自动
//	// 删除该对象。在调用该基类之前，请添加您的
//	// 对象所需的附加清理代码。
//
//	CDockablePane::OnFinalRelease();
//}


BEGIN_MESSAGE_MAP(CLeftPane, CDockablePane)
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_StartUp_Menu, &CLeftPane::OnStartupMenu)
	ON_COMMAND(ID_USIM, &CLeftPane::OnUsim)
	ON_COMMAND(ID_Select_Application, &CLeftPane::OnSelectApplication)
	ON_UPDATE_COMMAND_UI(ID_Select_Application, &CLeftPane::OnUpdateSelectApplication)
END_MESSAGE_MAP()



void CLeftPane::OnContextMenu(CWnd* pWnd, CPoint point)
{
	//if (GetSelectGroup() == NULL)
	//	return ;


	//CMenu menu;
	//menu.LoadMenu(IDR_APP_LIST_MENU);
	//CMenu* pSumMenu = menu.GetSubMenu(0);

	////if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	//if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CFrameWndEx)))

	//{
	//	CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

	//	if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
	//		return;

	//	((CFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
	//	//UpdateDialogControls(this, FALSE);

	//}

	//SetFocus();
}


int CLeftPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();


	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if(!m_AppcationList.Create(dwStyle, rectDummy,this, 2))
	{
		TRACE0("\n");
		return -1;    
	}



	LONG lStyle;
	lStyle = GetWindowLong(m_AppcationList.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	//lStyle |= LVS_LIST; //设置style
	SetWindowLong(m_AppcationList.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle1 = m_AppcationList.GetExtendedStyle();
	dwStyle1 |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//	dwStyle |= LVS_EX_HEADERDRAGDROP;
	dwStyle1 |= LVS_EX_CHECKBOXES;


	m_AppcationList.SetExtendedStyle(dwStyle1); //设置扩展风格
	//先删除所有的内容
	m_AppcationList.DeleteAllItems();
	m_AppcationList.DeleteAllColumn();


	m_AppcationList.InsertColumn(_DEF_Application_Name_Column       ,_T("应用名称"),LVCFMT_LEFT,20);
	m_AppcationList.InsertColumn(_DEF_Application_Path_Column       ,_T("路径")  ,LVCFMT_LEFT,20);
	m_AppcationList.InsertColumn(_DEF_Application_Descriptor_Column ,_T("描述"),LVCFMT_LEFT,20);

	/*const DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if(!m_ListBox.Create(dwStyle, rectDummy,this, 2))
	{
	TRACE0("\n");
	return -1;    
	}


	m_ListBox.EnableHeaderCtrl(FALSE);
	m_ListBox.EnableDescriptionArea();
	m_ListBox.SetVSDotNetLook();
	m_ListBox.MarkModifiedProperties();*/

	return 0;
}


void CLeftPane::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rectTree;
	//m_ListBox.GetWindowRect(rectTree);

	m_AppcationList.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}


void CLeftPane::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

}


void CLeftPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	//m_ListBox.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_AppcationList.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_AppcationList.AdjustColumnSize(cx);
}


BOOL CLeftPane::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CDockablePane::PreTranslateMessage(pMsg);
}


void CLeftPane::UpdateFonts()
{
	//m_ListBox.SetFont(&afxGlobalData.fontRegular);

	m_AppcationList.SetFont(&afxGlobalData.fontRegular);


}

void CLeftPane::AddNewApplication(CString csName,CString csPath,CString csDescriptor)
{

	//CMFCPropertyGridProperty* pGroup1 =  new CMFCPropertyGridProperty(csName);

	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("应用目录"), csPath, csDescriptor));

	//m_ListBox.AddProperty(pGroup1);
	int iNextItem = m_AppcationList.GetItemCount();
	m_AppcationList.InsertItem(iNextItem,csName);
	m_AppcationList.SetItemText(iNextItem,_DEF_Application_Path_Column,csPath);
	m_AppcationList.SetItemText(iNextItem,_DEF_Application_Descriptor_Column,csDescriptor);
}


void CLeftPane::TransationAppList(CString csApplist)
{
	int iSum;
	CString csApp;
	int iName,iPath,iDesc;
	iSum = _GetCStringDataSum(csApplist);

	m_AppcationList.DeleteAllItems();

	for(int i = 0 ; i < iSum ; i++)
	{
		_GetCStringData(csApplist,i+1,csApp);
		iName = csApp.Find(_T(":"),0);
		iPath = csApp.Find(_T(":"),iName+1);
		iDesc = csApp.Find(_T(":"),iPath+1);
		AddNewApplication(csApp.Mid(0,iName),csApp.Mid(iName+1,iPath-iName-1),csApp.Mid(iPath+1,iDesc-iPath-1));

	}


	/*int iSum;
	CString csApp;
	int iName,iPath,iDesc;
	iSum = _GetCStringDataSum(csApplist);
	m_ListBox.RemoveAll();
	m_ListBox.RedrawWindow();

	for(int i = 0 ; i < iSum ; i++)
	{

	csApp = _GetCStringData(csApplist,i+1);
	iName = csApp.Find(_T(":"),0);
	iPath = csApp.Find(_T(":"),iName+1);
	iDesc = csApp.Find(_T(":"),iPath+1);

	AddNewApplication(csApp.Mid(0,iName),csApp.Mid(iName+1,iPath-iName-1),csApp.Mid(iPath+1,iDesc-iPath-1));
	}*/
}

void CLeftPane::OnStartupMenu()
{
	CString csDF;
	CMainFrame *CurMainFrm;

	if(GetApplicationName(csDF))
	{
		CurMainFrm =(CMainFrame*)AfxGetApp()->GetMainWnd();
		CurMainFrm->StartUpCurrentApplicaiton(csDF);
	}

}

void CLeftPane::OnUsim()
{
	CMainFrame *CurMainFrm;
	CurMainFrm =(CMainFrame*)AfxGetApp()->GetMainWnd();
	CurMainFrm->OnUsim();
}

//CMFCPropertyGridProperty* CLeftPane::GetSelectGroup(void)
//{
//	//CMFCPropertyGridProperty* pGroup1;
//	//CPoint cpPoint;
//	//GetCursorPos(&cpPoint);
//
//	//m_ListBox.ScreenToClient(&cpPoint);
//	//pGroup1 = m_ListBox.HitTest(cpPoint);
//
//	//if (pGroup1!= NULL)
//	//	m_ListBox.SetCurSel(pGroup1);
//	
//	return pGroup1;
//}


void CLeftPane::OnSelectApplication()
{
	CString csDF,csResp;
	CMainFrame *CurMainFrm;
	if(GetApplicationName(csDF))
	{
		CurMainFrm =(CMainFrame*)AfxGetApp()->GetMainWnd();
		CurMainFrm->_TestCaseSelectFile(csDF,csResp,CurMainFrm->bIsUICC,csDF.GetLength()>4);
	}
}


void CLeftPane::OnUpdateSelectApplication(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}


BOOL CLeftPane::GetApplicationName(CString& csName)
{
	/*CString csTAG;
	int iCount;
	CMFCPropertyGridProperty* CurrentGroup;
	CMFCPropertyGridProperty* SubGroup;

	CurrentGroup = m_ListBox.GetCurSel();

	if(CurrentGroup == NULL)
	return FALSE;
	csName.Empty();


	csTAG = CurrentGroup->GetName();


	if (csTAG == _T("应用目录"))
	{
	csName = CurrentGroup->GetValue();
	}
	else
	{
	iCount = CurrentGroup->GetSubItemsCount();

	for (int i = 0 ; i < iCount; i++)
	{
	SubGroup = CurrentGroup->GetSubItem(i);

	csTAG   = SubGroup->GetName();
	if (csTAG == _T("应用目录"))
	csName     = SubGroup->GetValue();	
	}
	}*/

	//if (csName.IsEmpty())
	//	return FALSE;
	//else
		return TRUE;
}
// C:\自写程序\CardManage\CardManage\LeftPane.cpp : 实现文件
//
// CPINStatus

IMPLEMENT_DYNAMIC(CPINStatus, CDockablePane)

CPINStatus::CPINStatus()
{

}

CPINStatus::~CPINStatus()
{
}


BEGIN_MESSAGE_MAP(CPINStatus, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CPINStatus 消息处理程序




int CPINStatus::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if(!m_wndPinShow.Create(dwStyle, rectDummy,this, 2))
	{
		TRACE0("\n");
		return -1;    
	}

	Init_PINStatus();
	return 0;
}


void CPINStatus::OnSize(UINT nType, int cx, int cy)
{

	CDockablePane::OnSize(nType, cx, cy);
	m_wndPinShow.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	m_wndPinShow.AdjustColumnSize(cx);

}


void CPINStatus::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect rectTree;
	m_wndPinShow.GetWindowRect(rectTree);
	ScreenToClient(rectTree);
	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));

}


// 安装Pin是否校验的状态
bool CPINStatus::Insatll_PinVerifyStatus(UINT uiVerSta)
{

	if (uiVerSta&1)
		m_wndPinShow.SetItemText(_DEF_PIN1_Item,_DEF_PIN_Verifyed_Column,_T("TRUE"));
	else
		m_wndPinShow.SetItemText(_DEF_PIN1_Item,_DEF_PIN_Verifyed_Column,_T("FALSE"));

	if ((uiVerSta>>1)&1)
		m_wndPinShow.SetItemText(_DEF_PIN2_Item,_DEF_PIN_Verifyed_Column,_T("TRUE"));
	else
		m_wndPinShow.SetItemText(_DEF_PIN2_Item,_DEF_PIN_Verifyed_Column,_T("FALSE"));

	if ((uiVerSta>>9)&1)
		m_wndPinShow.SetItemText(_DEF_PINA_Item,_DEF_PIN_Verifyed_Column,_T("TRUE"));
	else
		m_wndPinShow.SetItemText(_DEF_PINA_Item,_DEF_PIN_Verifyed_Column,_T("FALSE"));


	/*CMFCPropertyGridProperty* Prop1;
	Prop1 = m_PinShow.GetProperty(0);
	
	if (uiVerSta&1)
	{
		Prop1->GetSubItem(0)->SetValue((_variant_t)true);
		Prop1->GetSubItem(0)->SetOriginalValue((_variant_t)true);
	}
	else
	{
		Prop1->GetSubItem(0)->SetValue((_variant_t)false);
		Prop1->GetSubItem(0)->SetOriginalValue((_variant_t)false);
	}

	Prop1 = m_PinShow.GetProperty(1);
	if ((uiVerSta>>1)&1)
	{
		Prop1->GetSubItem(0)->SetValue((_variant_t)true);
		Prop1->GetSubItem(0)->SetOriginalValue((_variant_t)true);
	}
	else
	{
		Prop1->GetSubItem(0)->SetValue((_variant_t)false);
		Prop1->GetSubItem(0)->SetOriginalValue((_variant_t)false);
	}

	Prop1 = m_PinShow.GetProperty(2);

	if ((uiVerSta>>9)&1)
	{
		Prop1->GetSubItem(0)->SetValue((_variant_t)true);
		Prop1->GetSubItem(0)->SetOriginalValue((_variant_t)true);
	}
	else
	{
		Prop1->GetSubItem(0)->SetValue((_variant_t)false);
		Prop1->GetSubItem(0)->SetOriginalValue((_variant_t)false);
	}
	*/

	return true;
}


bool CPINStatus::Init_PINStatus()
{

	LONG lStyle;
	lStyle = GetWindowLong(m_wndPinShow.m_hWnd, GWL_STYLE);//获取当前窗口style
	lStyle &= ~LVS_TYPEMASK; //清除显示方式位
	lStyle |= LVS_REPORT; //设置style
	//lStyle |= LVS_LIST; //设置style
	SetWindowLong(m_wndPinShow.m_hWnd, GWL_STYLE, lStyle);//设置style

	DWORD dwStyle = m_wndPinShow.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	//dwStyle |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	//	dwStyle |= LVS_EX_HEADERDRAGDROP;
	dwStyle |= LVS_EX_CHECKBOXES;


	m_wndPinShow.SetExtendedStyle(dwStyle); //设置扩展风格
	//先删除所有的内容
	m_wndPinShow.DeleteAllItems();
	m_wndPinShow.DeleteAllColumn();


	m_wndPinShow.InsertColumn(_DEF_PIN_Name_Column    ,_T("PIN Name"),LVCFMT_LEFT,20);
	m_wndPinShow.InsertColumn(_DEF_PIN_Remind_Column  ,_T("Remind")  ,LVCFMT_LEFT,20);
	m_wndPinShow.InsertColumn(_DEF_PIN_Verifyed_Column,_T("Verifyed"),LVCFMT_LEFT,20);
	m_wndPinShow.InsertColumn(_DEF_PIN_Disabled_Column,_T("Disabled"),LVCFMT_LEFT,20);

	m_wndPinShow.InsertItem(_DEF_PIN1_Item,_T("PIN1"));
	m_wndPinShow.SetItemText(_DEF_PIN1_Item,_DEF_PIN_Remind_Column,_T("3"));
	m_wndPinShow.SetItemText(_DEF_PIN1_Item,_DEF_PIN_Verifyed_Column,_T("FALSE"));
	m_wndPinShow.SetItemText(_DEF_PIN1_Item,_DEF_PIN_Disabled_Column,_T("FALSE"));

	m_wndPinShow.InsertItem(_DEF_PUK1_Item,_T("PUK1"));	
	m_wndPinShow.SetItemText(_DEF_PUK1_Item,_DEF_PIN_Remind_Column,_T("3"));
	//m_wndPinShow.SetItemText(_DEF_PUK1_Item,_DEF_PIN_Verifyed_Column,_T("FALSE"));
	//m_wndPinShow.SetItemText(_DEF_PUK1_Item,_DEF_PIN_Disabled_Column,_T("FALSE"));
		
		
	m_wndPinShow.InsertItem(_DEF_PIN2_Item,_T("PIN2/81"));		
	m_wndPinShow.SetItemText(_DEF_PIN2_Item,_DEF_PIN_Remind_Column,_T("3"));
	m_wndPinShow.SetItemText(_DEF_PIN2_Item,_DEF_PIN_Verifyed_Column,_T("FALSE"));
	//m_wndPinShow.SetItemText(_DEF_PIN2_Item,_DEF_PIN_Disabled_Column,_T("FALSE"));

	m_wndPinShow.InsertItem(_DEF_PUK2_Item,_T("PUK2/81"));
	m_wndPinShow.SetItemText(_DEF_PUK2_Item,_DEF_PIN_Remind_Column,_T("3"));
	//m_wndPinShow.SetItemText(_DEF_PUK2_Item,_DEF_PIN_Verifyed_Column,_T("FALSE"));
	//m_wndPinShow.SetItemText(_DEF_PUK2_Item,_DEF_PIN_Disabled_Column,_T("FALSE"));
		
	m_wndPinShow.InsertItem(_DEF_PINA_Item,_T("PIN4/ADM"));			
	m_wndPinShow.SetItemText(_DEF_PINA_Item,_DEF_PIN_Remind_Column,_T("3"));
	m_wndPinShow.SetItemText(_DEF_PINA_Item,_DEF_PIN_Verifyed_Column,_T("FALSE"));
	//m_wndPinShow.SetItemText(_DEF_PINA_Item,_DEF_PIN_Disabled_Column,_T("FALSE"));	

	

		
		
		
		/*CMFCPropertyGridProperty* Prop1;
	Prop1 = new CMFCPropertyGridProperty(_T("PIN 01"),0,1);
	Prop1->AddSubItem(new CMFCPropertyGridProperty(_T("Verified") ,(_variant_t) false ,_T("是否校验过PIN01")));
	Prop1->AddSubItem(new CMFCPropertyGridProperty(_T("Disable"),(_variant_t) false,_T("Disable PIN01")));
	Prop1->AddSubItem(new CMFCPropertyGridProperty(_T("剩余次数"), _T("3"),_T("剩余校验次数")));
	NotAllowEdit(Prop1);
	m_PinShow.AddProperty(Prop1);

	Prop1 = new CMFCPropertyGridProperty(_T("PIN 02/81"),0,TRUE);
	Prop1->AddSubItem(new CMFCPropertyGridProperty(_T("Verified") ,(_variant_t)false ,_T("是否校验过PIN81")));
	Prop1->AddSubItem(new CMFCPropertyGridProperty(_T("剩余次数"), _T("3"),_T("剩余校验次数")));
	NotAllowEdit(Prop1);
	m_PinShow.AddProperty(Prop1);

	Prop1 = new CMFCPropertyGridProperty(_T("PIN 04/0A"),0,TRUE);
	Prop1->AddSubItem(new CMFCPropertyGridProperty(_T("Verified") ,(_variant_t)false ,_T("是否校验过PIN0")));
	Prop1->AddSubItem(new CMFCPropertyGridProperty(_T("剩余次数"), _T("3"),_T("剩余校验次数")));
	NotAllowEdit(Prop1);
	m_PinShow.AddProperty(Prop1);

	Prop1 = new CMFCPropertyGridProperty(_T("PUK 01"),0,TRUE);
	Prop1->AddSubItem(new CMFCPropertyGridProperty(_T("剩余次数"), _T("10"),_T("剩余校验次数")));
	NotAllowEdit(Prop1);
	m_PinShow.AddProperty(Prop1);

	Prop1 = new CMFCPropertyGridProperty(_T("PUK 81"),0,TRUE);
	Prop1->AddSubItem(new CMFCPropertyGridProperty(_T("剩余次数"), _T("10"),_T("剩余校验次数")));
	NotAllowEdit(Prop1);
	m_PinShow.AddProperty(Prop1);*/


	return true;
}

bool CPINStatus::SetPin1Disable(bool bSet)
{
	if (bSet)
	{
		m_wndPinShow.SetItemText(_DEF_PIN1_Item,_DEF_PIN_Verifyed_Column,_T("TRUE"));
		m_wndPinShow.SetItemText(_DEF_PIN1_Item,_DEF_PIN_Disabled_Column,_T("TRUE"));
	}
	else
	{
		m_wndPinShow.SetItemText(_DEF_PIN1_Item,_DEF_PIN_Verifyed_Column,_T("TRUE"));
		m_wndPinShow.SetItemText(_DEF_PIN1_Item,_DEF_PIN_Disabled_Column,_T("FALSE"));
	}

	//CMFCPropertyGridProperty* Prop1;
	//Prop1 = m_PinShow.GetProperty(0);

	//Prop1->GetSubItem(1)->SetValue((_variant_t)bSet);
	//Prop1->GetSubItem(1)->SetOriginalValue((_variant_t)bSet);

	return true;
}

bool CPINStatus::NotAllowEdit(CMFCPropertyGridProperty* Prop)
{

	/*if (Prop->IsAllowEdit())
	Prop->AllowEdit(FALSE);
	Prop->Enable(FALSE);

	int iSum = Prop->GetSubItemsCount();
	for (int i = 0 ; i < iSum ; i ++)
	NotAllowEdit( Prop->GetSubItem(i));*/
	return true;
}


bool CPINStatus::SetPinPukRemaindNumber(int iRemainNumber,int iNumber, bool bIsPin)
{

	if (bIsPin)
	{
		switch(iNumber)
		{
		case 01:
			m_wndPinShow.SetItemText(_DEF_PIN1_Item,_DEF_PIN_Remind_Column,Int2CStringDecimal(iRemainNumber));
			break;
		case 02:
		case 0x81:
			m_wndPinShow.SetItemText(_DEF_PIN2_Item,_DEF_PIN_Remind_Column,Int2CStringDecimal(iRemainNumber));
			break;
		case 04:
		case 0xA:
			m_wndPinShow.SetItemText(_DEF_PINA_Item,_DEF_PIN_Remind_Column,Int2CStringDecimal(iRemainNumber));
			break;

		}


	}
	else
	{

		switch(iNumber)
		{
		case 01:
			m_wndPinShow.SetItemText(_DEF_PUK1_Item,_DEF_PIN_Remind_Column,Int2CStringDecimal(iRemainNumber));
			break;
		case 02:
		case 0x81:
			m_wndPinShow.SetItemText(_DEF_PUK2_Item,_DEF_PIN_Remind_Column,Int2CStringDecimal(iRemainNumber));
			break;

		}

	}




	/*CString csRemaind;
	csRemaind.Format("%d",iRemainNumber);
	if (iNumber == 01)
	{
	if (bIsPin)
	m_PinShow.GetProperty(0)->GetSubItem(2)->SetValue(csRemaind);
	else
	m_PinShow.GetProperty(3)->GetSubItem(0)->SetValue(csRemaind);
	}
	if (iNumber == 0x02)
	{
	if (bIsPin)
	m_PinShow.GetProperty(1)->GetSubItem(1)->SetValue(csRemaind);
	else
	m_PinShow.GetProperty(4)->GetSubItem(0)->SetValue(csRemaind);
	}

	if (iNumber == 0x81)
	{
	if (bIsPin)
	m_PinShow.GetProperty(1)->GetSubItem(1)->SetValue(csRemaind);
	else
	m_PinShow.GetProperty(4)->GetSubItem(0)->SetValue(csRemaind);
	}
	if (iNumber == 0xA)
	{

	m_PinShow.GetProperty(1)->GetSubItem(1)->SetValue(csRemaind);

	}
	if (iNumber == 0x4)
	{

	m_PinShow.GetProperty(1)->GetSubItem(1)->SetValue(csRemaind);

	}*/


	return true;
}
