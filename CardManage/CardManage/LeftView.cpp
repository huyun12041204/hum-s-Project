`// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// LeftView.cpp : CLeftView 类的实现
//

#include "stdafx.h"
#include "CardManage.h"
#include "MainFrm.h"
#include "CardManageDoc.h"
#include "LeftView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif





// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CView)
BEGIN_MESSAGE_MAP(CLeftView, CView)
		ON_WM_CREATE()
		ON_WM_SIZE()
		ON_COMMAND(ID_Class_Sort, OnClassSort)
		ON_UPDATE_COMMAND_UI_RANGE(ID_Class_Sort,ID_Class_Delete,OnUpdateToolBar)
		ON_COMMAND(ID_Class_Add_Catalog, OnClassAddCatalog)
		ON_COMMAND(ID_Class_Add_File, OnClassAddFile)
		ON_COMMAND(ID_Class_Delete,OnClassDelete)
		ON_COMMAND(ID_Class_Delete_Empty, OnClassDeleteEmpty)
		ON_COMMAND(ID_Class_Calculate, OnClassCalculate)
		ON_COMMAND(ID_Class_Map, OnClassMap)
		ON_COMMAND(ID_Class_Open, OnClassOpen)
		ON_COMMAND(ID_Class_Save, OnClassSave)




END_MESSAGE_MAP()

int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	int iRet;
	iRet = CView::OnCreate(lpCreateStruct);

	//m_wndClassView = (CTreeCtrl*) &GetTreeCtrl();

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndClassCtrl.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("未能创建类视图\n");
		return -1;      // 未能创建
	}

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_ClassBarTool);
	m_wndToolBar.LoadToolBar(IDR_ClassBarTool, 0, 0, TRUE /* 已锁定*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
//	DWORD  dstyle = m_wndToolBar.GetPaneStyle();
//	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS| (~CBRS_BORDER_3D));
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	OnChangeVisualStyle();
	bool bRet = true;

	if (!OpenProfileSetting())
		bRet = Initialize_ClassView(0);
	if (!bRet)
		MessageBox("Initialize ClassView failed!");

	hHistoryItem = NULL;
	return iRet;
}

bool CLeftView::OpenProfileSetting()
{
	CString csProfile = _T("Settings\\Start");
	CString csName    = _T("Def_ModulePathExist");
	CString csTemp;
	if (((CCardManageApp*)AfxGetApp())->GetProfileInt(csProfile,csName,0) == 0)
		return false;
	csName = ((CCardManageApp*)AfxGetApp())->GetSettingName(Def_ModulePath);
	if (!GetTempletData(AfxGetApp()->GetProfileString(csProfile,csName),csTemp))
		return false;
	if (!Install_Templet(csTemp))
		return false;
		

	return true;
}

void CLeftView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);	
	AdjustLayout();
}
void CLeftView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndClassCtrl.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);

}
void CLeftView::OnDraw(CDC* /*pDC*/)
{
	// TODO: 在此添加专用代码和/或调用基类
}
BOOL CLeftView::DeleteAllItems()
{
	return m_wndClassCtrl.DeleteAllItems();
}
HTREEITEM CLeftView::DeleteFileItem(HTREEITEM hItem)
{
	HTREEITEM hNextItem;

	hNextItem = m_wndClassCtrl.GetNextItem(hItem,TVGN_NEXT);

	m_wndClassCtrl.DeleteItem(hItem);

	return hNextItem;
}
HTREEITEM CLeftView::GetRootItem()
{
	return m_wndClassCtrl.GetRootItem();
}
HTREEITEM CLeftView ::GetChildItem(HTREEITEM hItem)
{
	return m_wndClassCtrl.GetChildItem(hItem);
}
HTREEITEM CLeftView ::GetNextItem(HTREEITEM hItem,UINT nCode)
{
	return m_wndClassCtrl.GetNextItem(hItem,nCode);
}
HTREEITEM CLeftView ::GetSelectedItem()
{
	return m_wndClassCtrl.GetSelectedItem();
}
void CLeftView::SelectedItem(HTREEITEM hItem)
{
	m_wndClassCtrl.SelectItem(hItem);
}
bool CLeftView ::_IsDFItem(HTREEITEM hItem)
{
	int nImage,nSelectedImage;
	nImage         = -1;
	nSelectedImage = -1;
	m_wndClassCtrl.GetItemImage(hItem,nImage,nSelectedImage);


	if((nImage != _LV_EF)&&(nImage != _LV_EFAbsent)&&(nImage>=0))
		return true;
	else
		return false;
}
bool CLeftView ::_IsCheckItem(HTREEITEM hItem)
{
	if (m_wndClassCtrl.GetCheck(hItem))
		return true;
	else
		return false;
	
}
CString CLeftView::_GetItemPath(HTREEITEM hItem)
{
	CString csFile;
	CString csTemp;

	do 
	{
		//csTemp = m_wndClassView.GetItemText(hItem);
		csTemp = _GetItemFID(hItem);
		if(csTemp.IsEmpty())
			csTemp = _GetItemAID(hItem);

		csFile = csTemp+ _T("||") + csFile;

		hItem  = m_wndClassCtrl.GetNextItem(hItem,TVGN_PARENT);

	} while (hItem);

	return csFile;
}
CString CLeftView::_GetItemText(HTREEITEM hItem)
{
	return m_wndClassCtrl.GetItemText(hItem);
}
CString CLeftView::_GetItemFID(HTREEITEM hItem)
{
	CString csText;
	int iOffset;

	csText = m_wndClassCtrl.GetItemText(hItem); 

	iOffset = csText.Find(_T("("));

	if (iOffset > 0)
		csText = csText.Left(iOffset);



	if (csText.GetLength() != 4)
		csText.Empty();

	return csText; 
}
CString CLeftView::_GetItemAID(HTREEITEM hItem)
{
	CString csText;
	int iOffset;

	csText = m_wndClassCtrl.GetItemText(hItem); 

	iOffset = csText.Find(_T("("));

	if (iOffset > 0)
		csText = csText.Left(iOffset);

	if ((csText.GetLength() >0x20)||(csText.GetLength() < 10))
		csText.Empty();

	return csText; 

}
CString CLeftView::_GetItemDescription(HTREEITEM hItem)
{
	CString csText;
	int iOffset,iLength;

	csText = m_wndClassCtrl.GetItemText(hItem); 

	iOffset = csText.Find(_T("("));
	iLength = csText.Find(_T(")"));

	if ((iOffset>0)&&(iLength>0))
		csText = csText.Mid(iOffset+1,iLength-iOffset-1);
	

	return csText; 


}


BOOL CLeftView::_GetFileMark(HTREEITEM hItem, int* iFileMark)
{
	int iTempMark = -1;

	CString csPath;
	CString csFile;

	if ((hItem == NULL)||
		(hItem == TVI_ROOT))
		return FALSE;
		

	csPath = _GetItemPath(hItem);

	int iNum  = _GetMarkNumber(csPath,_T("||"));
	*iFileMark = _DEF_Card;


	for (int iCyc = 0; iCyc < iNum ; iCyc ++ )
	{
		if (_GetDatasInMark(csPath,_T("||"),iCyc+1,csFile))
		{
			csFile.MakeUpper();
			//此处为3F00直接忽略
			if ( csFile == _T("3F00"))
				continue;

			if (csFile.GetLength()==4)
			{
				if (GetDFMark(csFile,*iFileMark,&iTempMark) == FALSE)
					return FALSE;
			}
			else if (!GetADFMark(csFile,&iTempMark))
				return FALSE;

			if ((*iFileMark == iTempMark)&&
				((iNum-1)!=iCyc))
				return FALSE;
			*iFileMark = iTempMark;

		}
	}

	return TRUE;
}

//BOOL CLeftView::_GetFileExpectDescription(HTREEITEM hItem, CString& csDescription)
//{
//	int iFileMark = 0;
//	if (_IsDFItem(hItem))
//	{
//		if((_GetFileMark(hItem,&iFileMark))&&
//		   (GetDFName(iFileMark,csDescription)))
//		   return TRUE
//		else
//		   return FALSE;
//	}
//	else
//	{
//		HTREEITEM hPItem = GetNextItem(hItem,TVGN_PARENT);
//		if ( _GetFileMark(hPItem,&iFileMark) )
//		{
//			int iFID = _GetItemFID(hItem);
//			if (GetFileNameFromReference(iFID,iFileMark,csDescription,false))
//				return TRUE;
//		}
//	}
//	return FALSE;
//}

void CLeftView::OnChangeVisualStyle()
{
	m_ClassViewImages.DeleteImageList();

	//	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;
	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILESMALL : IDB_FILESMALL;

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

	m_ClassViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_ClassViewImages.Add(&bmp, RGB(0, 0, 0));//修改底色

	m_wndClassCtrl.SetImageList(&m_ClassViewImages, TVSIL_NORMAL);

	const DWORD dwViewStyle = WS_CHILD |TVS_CHECKBOXES| WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	m_wndClassCtrl.ModifyStyle(m_wndClassCtrl.GetStyle(),dwViewStyle);

	//	m_wndToolBar.CleanUpLockedImages();
	//	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* 锁定*/);
}

int CLeftView::StatisticFileNumber(void)
{

	int iEF = 0 ;
	int iDF = 0 ;

	m_wndClassCtrl.StatisticFile(m_wndClassCtrl.GetRootItem(),iEF,iDF);

	return iEF;


	//return StatisticFileNumberCurrentDIR (m_wndClassView.GetRootItem(),0);
}


int CLeftView::GetFileLayer(HTREEITEM hCurrentItem)
{

	HTREEITEM hPareItem;
	int iLayer;

	iLayer    = 0;
	hPareItem = hCurrentItem;
	do 
	{

		hPareItem = GetNextItem(hPareItem,TVGN_PARENT);
		iLayer += 1;

	} while (hPareItem != NULL);

	return iLayer;
}

int CLeftView::GetFileLayerFID(HTREEITEM hCurrentItem,int iLayer)
{
	CString csFID;
	HTREEITEM hNextItem;
	int iSum = GetFileLayer(hCurrentItem);
	if ( iSum < iLayer)
		return -1;
	int iFID;

	hNextItem = hCurrentItem; 

	for (int i = 0 ; i < (iSum - iLayer) ; i ++)
		hNextItem = GetNextItem(hNextItem,TVGN_PARENT);
	csFID = _GetItemFID(hNextItem);
	if (csFID.IsEmpty())
		csFID = _GetItemAID(hNextItem);

	if (csFID.GetLength()>=10)
		iFID = 0x10000+_CString2Int(csFID.Mid(06,04));
	else
		iFID = _CString2Int(csFID);
	return iFID;
}


void CLeftView::OnSearchfileMenu()
{
	m_wndClassCtrl.OnSearchfileMenu();
}
void CLeftView::OnSearchfilesMenu()
{
	m_wndClassCtrl.OnSearchfilesMenu();
}

bool CLeftView::Initialize_ClassView(int iType)
{
	CString csTemplet,csName;
	m_wndClassCtrl.DeleteAllItems();

	switch(iType)
	{
	case 0x01:csName = _T("CLF\\CTC_Native_301.CLF");break; 
	case 0x02:csName = _T("CLF\\CTC_M2M_2G3G_301.CLF");break;	
	case 0x03:csName = _T("CLF\\CTC_M2M_2G3G4G_301.CLF");break;
	case 0x11:csName = _T("CLF\\CMCC_Native_20A.CLF");break; 
	case 0x12:csName = _T("CLF\\CMCC_M2M_20.CLF");break;	
	case 0x21:csName = _T("CLF\\CUC_Normal1.CLF");break; 
	case 0x22:csName = _T("CLF\\CUC_Normal2.CLF");break;
	case 0xF1:csName = _T("CLF\\GSM.CLF");break;	
	case 0xF2:csName = _T("CLF\\3GPP.CLF");break;	
	case 0xF3:csName = _T("CLF\\3GPP2.CLF");break;	
	case 0xF4:csName = _T("CLF\\CDMA.CLF");break;	
	default:  csName = _T("CLF\\Templet.CLF");break;
	}
	if (!OpenModuleFile(csName,csTemplet))
		return false;
	if (!Install_Templet(csTemplet))
		return false;
	m_wndClassCtrl.SelectItem(m_wndClassCtrl.GetRootItem());
	return true;
}

bool CLeftView::Insert_EF(int iFID, CString csDes , HTREEITEM* hResItem,HTREEITEM hPareItem, int iState)
{
	//HTREEITEM hEFItem,hPPItem;
	//CString csFID;
	//csFID.Format("%04X",iFID);
	//int iPreFID,iPrePFID;
	//CString csPreFID,csPrePFID;

	//if (csDes.IsEmpty())
	//{
	//	hPPItem = GetNextItem(hPareItem,TVGN_PARENT);

	//	if ((hPPItem == TVI_ROOT)||(hPPItem == NULL))
	//	{
	//		csPreFID = _GetItemFID(hPareItem);
	//		if (csPreFID.IsEmpty())
	//		{
	//			csPreFID = _GetItemAID(hPareItem);
	//			iPreFID = _CString2Int(csPreFID.Mid(6,4))+0x10000;
	//		}
	//		else
	//			iPreFID = _CString2Int(csPreFID);

	//		switch(iPreFID)
	//		{
	//		case 0x3F00: 
	//			if (!GenerateEFNameInMF(iFID,csDes))
	//				csDes.Empty();
	//			break;
	//		case 0x10087: 
	//			if (!GenerateEFNameIn3GPP(iFID,csDes))
	//				csDes.Empty();
	//		case 0x10343: 
	//			if (!GenerateEFNameIn3GPP2(iFID,csDes))
	//				csDes.Empty();
	//			break;
	//		default:csDes.Empty();
	//		}
	//	}
	//	else
	//	{
	//		csPrePFID = _GetItemFID(hPPItem);
	//		if (csPrePFID.IsEmpty())
	//		{
	//			csPrePFID = _GetItemAID(hPPItem);
	//			iPrePFID = _CString2Int(csPrePFID.Mid(6,4))+0x10000;
	//		}
	//		else
	//			iPrePFID = _CString2Int(csPrePFID);

	//		csPreFID = _GetItemFID(hPareItem);
	//		if (csPreFID.IsEmpty())
	//		{
	//			csPreFID = _GetItemAID(hPareItem);
	//			iPreFID = _CString2Int(csPreFID.Mid(6,4))+0x10000;
	//		}
	//		else
	//			iPreFID = _CString2Int(csPreFID);


	//		switch(iPrePFID)
	//		{
	//		case 0x3F00:

	//			switch(iPreFID)
	//			{
	//			case 0x7F10:
	//				if (!GenerateEFNameInTelecom(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x7F20:
	//				if (!GenerateEFNameInGSM(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x7F25:
	//				if (!GenerateEFNameInCDMA(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x7FF0:
	//				if (!GenerateEFNameIn3GPP(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x7FF1:
	//				if (!GenerateEFNameIn3GPP2(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x10087: 
	//				if (!GenerateEFNameIn3GPP(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x10343: 
	//				if (!GenerateEFNameIn3GPP2(iFID,csDes))
	//					csDes.Empty();
	//			default:break;
	//				break;
	//			}
	//			break;
	//		case 0x7F10:
	//			switch (iPreFID)
	//			{
	//			case 0x5F5C:
	//				if (!GenerateEFNameInMMSS(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x5F3A:
	//				if (!GenerateEFNameInPhoneBook(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x5F3B:
	//				if (!GenerateEFNameInGSMAccess(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x5F3C:
	//				if (!GenerateEFNameInMMSS(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			default:break;
	//			}

	//			break;
	//		case 0x7F20:

	//			break;
	//		case 0x7F25:

	//			break;
	//		case 0x7FF0:
	//			switch (iPreFID)
	//			{
	//			case 0x5F5C:
	//				if (!GenerateEFNameInMMSS(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x5F3A:
	//				if (!GenerateEFNameInPhoneBook(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x5F3B:
	//				if (!GenerateEFNameInMultiMedia(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x5F3C:
	//				if (!GenerateEFNameInMExE(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x5F40:
	//				if (!GenerateEFNameInWLAN(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x5F50:
	//				if (!GenerateEFNameInGRAPHICS(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x5F70:
	//				if (!GenerateEFNameInSoLSA(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			default:break;
	//			}

	//			break;
	//		case 0x7FF1:

	//			switch (iPreFID)
	//			{
	//			case 0x5F3C:
	//				if (!GenerateEFNameInMMSS(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			default:break;
	//			}

	//			break;
	//		case 0x10087: 
	//			switch (iPreFID)
	//			{
	//			case 0x5F5C:
	//				if (!GenerateEFNameInMMSS(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x5F3A:
	//				if (!GenerateEFNameInPhoneBook(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x5F3B:
	//				if (!GenerateEFNameInGSMAccess(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x5F3C:
	//				if (!GenerateEFNameInMExE(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x5F40:
	//				if (!GenerateEFNameInWLAN(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x5F50:
	//				if (!GenerateEFNameInHNB(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			case 0x5F70:
	//				if (!GenerateEFNameInSoLSA(iFID,csDes))
	//					csDes.Empty();
	//				break;

	//			default:break;
	//			}

	//			break;
	//		case 0x10343: 

	//			switch (iPreFID)
	//			{
	//			case 0x5F3C:
	//				if (!GenerateEFNameInMMSS(iFID,csDes))
	//					csDes.Empty();
	//				break;
	//			default:break;
	//			}
	//			break;


	//		default: csDes.Empty();;
	//		}

	//	}
	//}





	//if (!csDes.IsEmpty())
	//	csFID = csFID + _T("(EF-")+csDes+_T(")");

	//hEFItem = m_wndClassCtrl.InsertItem(csFID,_LV_EF,_LV_EFSelected,hPareItem);



	//if (hEFItem == NULL)
	//	return false;
	//if (hResItem != NULL)
	//	*hResItem = hEFItem;
	//m_wndClassCtrl.Expand(hPareItem,TVE_EXPAND);
	//return ChangeItemState(hEFItem,iState);
    CString csFID = Int2CString(iFID,4);

    if (csDes.IsEmpty())
    {
		int iPMark = 0;
		if ((_GetFileMark(hPareItem,&iPMark))&&
			GetFileNameFromReference(iFID,iPMark,csDes,true))
			csFID = csFID + _T("(EF-")+csDes+_T(")");
		else
			csDes.Empty();
    }

	HTREEITEM hEFItem = m_wndClassCtrl.InsertItem(csFID,_LV_EF,_LV_EFSelected,hPareItem);
	if (hEFItem == NULL)
		return false;
	if (hResItem != NULL)
		*hResItem = hEFItem;
	m_wndClassCtrl.Expand(hPareItem,TVE_EXPAND);
	return ChangeItemState(hEFItem,iState);
}
bool CLeftView::Insert_DF(int iFID, CString csDes , HTREEITEM* hResItem, HTREEITEM hPareItem, int iState)
{
	HTREEITEM hDFItem;

	CString csFID,csTemp;
	int iPreFID;
	csFID.Format("%04X",iFID);
	iPreFID = 0;

	if (iFID == 0x3F00)
		csFID = csFID + _T("(MF)");
	else 
	{
		if (csDes.IsEmpty())
		{
			int iPMark   = _DEF_Card;
			int iFileMark= _DEF_Card;
			if (!_GetFileMark(hPareItem,&iPMark))
				iPMark = _DEF_Card;


			if ((GetDFMark(csFID,iPMark,&iFileMark)== TRUE)&&
				(GetDFName(iFileMark,csTemp)))
				csDes = csTemp;
			else
				csDes.Empty();
		}
		if (!csDes.IsEmpty())
			csFID = csFID + _T("(DF-")+csDes+_T(")");
	}
	
	


	if ((hPareItem == TVI_ROOT)||(hPareItem == NULL))
		hDFItem = m_wndClassCtrl.InsertItem(csFID,_LV_ROOT,_LV_ROOT,hPareItem);
	else
		hDFItem = m_wndClassCtrl.InsertItem(csFID,_LV_DF,_LV_DFSelected,hPareItem);

	if (hDFItem == NULL)
		return false;

	if (hResItem!= NULL)
		*hResItem = hDFItem;

	m_wndClassCtrl.Expand(hPareItem,TVE_EXPAND);

	return ChangeItemState(hDFItem,iState);
}
bool CLeftView::Insert_ADF(CString csAID, CString csDes,  HTREEITEM* hResItem, HTREEITEM hPareItem, int iState)
{

	HTREEITEM hDFItem;
	int iFileMark;
	if ((!csDes.IsEmpty())||
		(!GetADFMark(csAID,&iFileMark))||
		(!GetDFName(iFileMark,csDes)))
	    csDes.Empty();
	if (!csDes.IsEmpty())
		csAID = csAID + _T("(ADF-")+csDes+_T(")");

	if (hPareItem == TVI_ROOT)
		hDFItem = m_wndClassCtrl.InsertItem(csAID,_LV_ROOT,_LV_ROOT,hPareItem);
	else	
		hDFItem = m_wndClassCtrl.InsertItem(csAID,_LV_ADF,_LV_ADFSelected,hPareItem);

	if (hDFItem == NULL)
		return false;

	if (hResItem!= NULL)
		*hResItem = hDFItem;

	m_wndClassCtrl.Expand(hPareItem,TVE_EXPAND);
	return ChangeItemState(hDFItem,iState);
}

bool CLeftView::Insert_TEST(int iFID, CString csDes , HTREEITEM* hResItem, HTREEITEM hPareItem, int iState)
{
	HTREEITEM hDFItem;

	CString csFID,csTemp;
//	int iPreFID;
	csFID.Format("%04X",iFID);

	if (csDes.IsEmpty())
	{

		int iPMark = _DEF_Card;
		int iFileMark= _DEF_Card;
		if (!_GetFileMark(hPareItem,&iPMark))
			iPMark = _DEF_Card;


		if ((GetDFMark(csFID,iPMark,&iFileMark)!=FALSE)&&
			(GetDFName(iFileMark,csTemp)))
		{
			csDes = csTemp;
		}
		else
			csDes.Empty();


		//if (hPareItem != TVI_ROOT)
		//	csTemp = _GetItemFID(hPareItem);
		//else
		//	csTemp = _T("0000");

		//if (csTemp.IsEmpty())
		//{
		//	csTemp= _GetItemAID(hPareItem);
		//	iPreFID = _CString2Int(csTemp.Mid(06,04))+0x10000;
		//}
		//else
		//	iPreFID = _CString2Int(csTemp);

		//if (!GenerateDFName(iFID,iPreFID,csDes))
		//	csDes.Empty();
	}

	hDFItem = m_wndClassCtrl.InsertItem(csFID,_LV_Pro,_LV_Pro,hPareItem);

	if (hDFItem == NULL)
		return false;

	if (hResItem!= NULL)
		*hResItem = hDFItem;

	m_wndClassCtrl.Expand(hPareItem,TVE_EXPAND);

	return ChangeItemState(hDFItem,iState);
}


bool CLeftView::Install_Templet(CString csTemplet,HTREEITEM hRoot)
{
	bool bRet;
	CString csCardData,csDes;
	CString csFID,csFile,csNext,csTempFile,csTempRemind;
	HTREEITEM hCurrentItem = NULL;
	csCardData = csTemplet;
	csDes.Empty();

	

	do 
	{
		if (_GetXMLFirstNode(csCardData,&csFID,&csFile,&csNext,NULL)>=0)
		{
			_FindFistNodeCurrnent(csFile,_T("File")+csFID,&csTempFile,&csTempRemind);
			if (!csTempFile.IsEmpty())
			{
				if (csFID.GetLength()!= 4)
					bRet = Insert_ADF(csFID,csDes,&hCurrentItem,hRoot);
				else
					bRet = Insert_DF(_CString2Int(csFID),csDes,&hCurrentItem,hRoot);
				if (bRet)
				{
					Install_Templet(csTempFile, hCurrentItem);
					m_wndClassCtrl.Expand(hRoot,TVE_EXPAND);
				}

				
			}
			else
				bRet = Insert_EF(_CString2Int(csFID),csDes,NULL,hRoot);

		}
		csCardData = csNext;

	} while (!csCardData.IsEmpty());

		
	
	
	return true;
}
bool CLeftView::GetTempletData(CString& csTemplet)
{
	return OpenModuleFile(_T("\\Templet.Card"),csTemplet);
}
bool CLeftView::GetTempletData(CString csPath, CString& csTemplet)
{

	CString csData;
	CFileStatus csSta;
	CStdioFile CSFFile;
	int iRet;


	iRet = CSFFile.Open(csPath,CFile::shareDenyRead);

	if (!iRet)
		return false;

	iRet = CSFFile.GetStatus(csPath,csSta);
	if (!iRet)
	{
		CSFFile.Close();
		return false;
	}
	do 
	{
		//读取文件内容
		iRet = CSFFile.ReadString(csData);
		csTemplet +=  csData;
		if (iRet == FALSE)
			break;
	} while (iRet);

	CSFFile.Close();
	csModulePath = csPath;
	return true;
}
bool CLeftView::OpenModuleFile(CString csName,CString& csTemplet)
{
	CString csDir;

	__GetCurrentDIR(csDir);

	return GetTempletData(csDir+_T("\\")+csName,csTemplet);
}
bool CLeftView::ChangeItemState(HTREEITEM hItem,int iState)
{
	int iIcon,iIconSel;
	m_wndClassCtrl.GetItemImage(hItem,iIcon,iIconSel);

	switch(iState)
	{
	case _LV_Absent:
		if (iIcon == _LV_DF )
			m_wndClassCtrl.SetItemImage(hItem,_LV_DFAbsent,_LV_DFAbsentSelected);
		else if (iIcon == _LV_ADF)
			m_wndClassCtrl.SetItemImage(hItem,_LV_ADFAbsent,_LV_ADFAbsentSelected);
		else if (iIcon == _LV_EF)
			m_wndClassCtrl.SetItemImage(hItem,_LV_EFAbsent,_LV_EFAbsentSelected);
		else if (iIcon == _LV_Pro)
			m_wndClassCtrl.SetItemImage(hItem,_LV_ProAbsent,_LV_ProAbsent);
		else if (iIcon == _LV_ROOT)
			m_wndClassCtrl.SetItemImage(hItem,_LV_ROOTAbsent,_LV_ROOTAbsent);
		m_wndClassCtrl.SetItemState(hItem,0,TVIS_CUT);
		break;
	case _LV_NoSure:
		m_wndClassCtrl.SetItemState(hItem,TVIS_CUT,TVIS_CUT);
		m_wndClassCtrl.SetItemState(hItem,0,TVIS_BOLD);
		break;
	case _LV_Existed:
		m_wndClassCtrl.SetItemState(hItem,0,TVIS_CUT);
		m_wndClassCtrl.SetItemState(hItem,0,TVIS_BOLD);
		if (iIcon == _LV_DFAbsent )
			m_wndClassCtrl.SetItemImage(hItem,_LV_DF,_LV_DFSelected);
		else if (iIcon == _LV_ADFAbsent )
			m_wndClassCtrl.SetItemImage(hItem,_LV_ADF,_LV_ADFSelected);
		else if (iIcon == _LV_EFAbsent)
			m_wndClassCtrl.SetItemImage(hItem,_LV_EF,_LV_EFSelected);
		else if (iIcon == _LV_ProAbsent )
			m_wndClassCtrl.SetItemImage(hItem,_LV_Pro,_LV_Pro);
		else if (iIcon == _LV_ROOTAbsent )
			m_wndClassCtrl.SetItemImage(hItem,_LV_ROOT,_LV_ROOT);

		break;
	default:
		m_wndClassCtrl.SetItemState(hItem,TVIS_CUT,TVIS_CUT);
		m_wndClassCtrl.SetItemState(hItem,0,TVIS_BOLD);
		break;
	}
	return true;
}


void CLeftView::OnClassSort()
{
	m_wndClassCtrl.Sort(1);
	return;
}
void CLeftView::OnClassAddCatalog()
{
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();


	CurMainFrm->InsatllFile(GetSelectedItem(),true);
	return;
}
void CLeftView::OnClassAddFile()
{	
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CurMainFrm->InsatllFile(GetSelectedItem(),false);
	return;
}
void CLeftView::OnClassDeleteEmpty()
{
	m_wndClassCtrl.DeleteAbsent(1);
	return;
}
void CLeftView::OnClassCalculate()
{

	int iEF = 0;
	int iDF = 0;
	CString csDF,csEF;
	m_wndClassCtrl.StatisticFile(m_wndClassCtrl.GetRootItem(),iEF,iDF);

	csDF.Format("%d",iDF);
	csEF.Format("%d",iEF);

	MessageBox(_T("文件数量: ")+csEF+ _T("\r目录数量: ")+csDF);
	return;
}
void CLeftView::OnClassMap()
{
	CMainFrame *CurMainFrm;
	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	CurMainFrm->NewCheckMapFileListThread();
	CurMainFrm->NewSetStatusThread();
}
void CLeftView::OnClassOpen()
{
	CString csFileName,csFilePath,csFileData;
	CFileDialog CFDataFile(TRUE,_T("*.CLF|.CLF"),NULL,4|1,_T("Card List File(*.CLF)|*.CLF||"));

	if ( CFDataFile.DoModal() == IDOK)
	{
		csFileName = CFDataFile.GetFileTitle();

		csFilePath = CFDataFile.GetPathName();

		if (GetTempletData(csFilePath,csFileData))
		{
			DeleteAllItems();
			Install_Templet(csFileData,GetRootItem());
			m_wndClassCtrl.SelectItem(m_wndClassCtrl.GetRootItem());
		}
		else
		{
			MessageBox(_T("打开文件失败！"));
		}
	}
}
void CLeftView::OnClassSave()
{
	CString csFileName;
	CString csFileData;
	CStdioFile CSFFile;
	CFileDialog CFDataFile(FALSE,_T("*.CLF|.CLF"),NULL,4|2,_T("Card List File(*.CLF)|*.CLF||"));


	if ( CFDataFile.DoModal() == IDOK)
	{
		GenerateTreelistData(GetRootItem(),csFileData);

		csFileName = CFDataFile.GetPathName();

		if (CSFFile.Open(csFileName,CFile::modeCreate|CFile::modeWrite))
		{
			CSFFile.WriteString(csFileData);
			CSFFile.Close();
		}
		else
			MessageBox(_T("保存失败"));

	}
}
void CLeftView::OnClassDelete()
{
	HTREEITEM hItem =m_wndClassCtrl.GetSelectedItem();
	if (hItem != NULL)
		m_wndClassCtrl.DeleteItem(hItem);
	
	
}

void CLeftView::OnUpdateToolBar(CCmdUI *pCmdUI)
{
	extern int  iThread;
	if(iThread == Def_Thread_Free)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

int CLeftView::GenerateTreelistData(HTREEITEM hItem,CString &csResult)
{
	HTREEITEM hNext;
	BOOL bRet;
	CString csFID;
	CString csStart,csEnd,csFormat;

	bRet = TRUE;
	hNext = hItem;
	do 
	{


//		csFID  = _GetItemText(hNext);
		csFID = _GetItemFID(hNext);
		if (csFID.IsEmpty())
			csFID = _GetItemAID(hNext);



		csStart = _T("<")+csFID+_T(">");
		csEnd   = _T("</")+csFID+_T(">");

		csResult += csFormat + csStart;

		if (_IsDFItem(hNext))
		{
			csResult += csFormat + _T("<File")+ csFID  + _T(">");

			GenerateTreelistData(GetNextItem(hNext,TVGN_CHILD),csResult);

			csResult += csFormat + _T("</File")+ csFID + _T(">");

		}

		csResult += csFormat + csEnd;


		hNext = GetNextItem(hNext,TVGN_NEXT);

	} while (hNext != NULL);
	return bRet;
}

bool CLeftView::SetClassTreeEnable(bool bEnable)
{
//	m_wndClassView
//	m_wndClassCtrl
//	if (m_wndClassCtrl.EnableWindow(bEnable))
	//	return true;
	//else
	//	return false;
	return false;
}


// 修改括号内的名字
bool CLeftView::ChangeEFDescription(HTREEITEM hFileItem,CString csDes)
{
	BOOL bRet;

	bRet = FALSE;
	if ((hFileItem != NULL)&&(!csDes.IsEmpty()))
		bRet = m_wndClassCtrl.SetItemText(hFileItem,_GetItemFID(hFileItem)+_T("(EF-")+csDes+_T(")"));

	if (bRet)
		return true;
	else 
		return false;
}
bool CLeftView::ChangeDFDescription(HTREEITEM hFileItem,CString csDes)
{
	BOOL bRet;
	if (hFileItem != NULL)
		bRet = m_wndClassCtrl.SetItemText(hFileItem,_GetItemFID(hFileItem)+_T("DF-")+csDes+_T(")"));

	if (bRet)
		return true;
	else 
		return false;
}
bool CLeftView::ChangeADFDescription(HTREEITEM hFileItem,CString csDes)
{
	BOOL bRet;
	if (hFileItem != NULL)
		bRet = m_wndClassCtrl.SetItemText(hFileItem,_GetItemAID(hFileItem)+_T("ADF-")+csDes+_T(")"));

	if (bRet)
		return true;
	else 
		return false;
}
bool CLeftView::ChangeEFDescription(CString csPath,CString csDes)
{
	return ChangeEFDescription(_GetItem(csPath),csDes);
}



// 通过FID
HTREEITEM CLeftView::_GetItem(int iFID,HTREEITEM hParentItem)
{
	HTREEITEM hChildItem;
	CString csFID;

	if (_CString2Int(_GetItemFID(hParentItem))== iFID)
		return hParentItem;

	hChildItem = m_wndClassCtrl.GetChildItem(hParentItem);

	while(hChildItem!=NULL)
	{

		csFID = _GetItemFID(hChildItem);
		if ((!csFID.IsEmpty())&&(_CString2Int(csFID) == iFID))
			return hChildItem;
		hChildItem = m_wndClassCtrl.GetNextItem(hChildItem,TVGN_NEXT);
	}

	return NULL;
}

HTREEITEM CLeftView::_GetItem(CString  csAID,HTREEITEM hParentItem)
{
	HTREEITEM hChildItem;
	CString csExAID;
	csAID.MakeUpper();
	if (_GetItemAID(hParentItem) == csAID)
		return hParentItem;

	hChildItem = m_wndClassCtrl.GetChildItem(hParentItem);

	while(hChildItem!=NULL)
	{
		
		csExAID = _GetItemAID(hChildItem);
		csExAID.MakeUpper();
		if ((!csExAID.IsEmpty())&&(csExAID.Compare(csAID) == 0))
			return hChildItem;
		hChildItem = m_wndClassCtrl.GetNextItem(hChildItem,TVGN_NEXT);
	}

	return NULL;
}


HTREEITEM CLeftView::_GetItem(CString csPath)
{
	HTREEITEM hFile;
	hFile = GetRootItem();
	int iStart,iEnd;
	iStart = 0 ;


	do 
	{
		iEnd = csPath.Find(_T("||"),iStart);

		if (iEnd < 0)
			iEnd = csPath.GetLength();

		if((iEnd - iStart) == 0x4 ) 
			hFile = _GetItem(_CString2Int(csPath.Mid(iStart,4)),hFile);
		else
			hFile = _GetItem(csPath.Mid(iStart,iEnd- iStart),hFile);

		iStart = iEnd +2;

	} while (iEnd < csPath.GetLength());


	return hFile;
}


BEGIN_MESSAGE_MAP(CClassTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CClassTreeCtrl::OnNMClick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CClassTreeCtrl::OnNMDblclk)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CClassTreeCtrl::OnNMRClick)
	ON_COMMAND(ID_SelectFile_Menu, &CClassTreeCtrl::OnSelectfileMenu)
	ON_UPDATE_COMMAND_UI(ID_SelectFile_Menu, &CClassTreeCtrl::OnUpdateSelectfileMenu)
	ON_COMMAND(ID_ReadFileValue_Menu, &CClassTreeCtrl::OnReadfilevalueMenu)
	ON_UPDATE_COMMAND_UI(ID_ReadFileValue_Menu, &CClassTreeCtrl::OnUpdateReadfilevalueMenu)
	ON_COMMAND(ID_ChangeFileValue_Menu, &CClassTreeCtrl::OnChangefilevalueMenu)
	ON_UPDATE_COMMAND_UI(ID_ChangeFileValue_Menu, &CClassTreeCtrl::OnUpdateChangefilevalueMenu)
	ON_COMMAND(ID_SearchFile_Menu, &CClassTreeCtrl::OnSearchfileMenu)
	ON_UPDATE_COMMAND_UI(ID_SearchFile_Menu, &CClassTreeCtrl::OnUpdateSearchfileMenu)
	ON_COMMAND(ID_SearchFiles_Menu, &CClassTreeCtrl::OnSearchfilesMenu)
	ON_UPDATE_COMMAND_UI(ID_SearchFiles_Menu, &CClassTreeCtrl::OnUpdateSearchfilesMenu)
	ON_COMMAND(ID_Expand_Menu, &CClassTreeCtrl::OnExpandMenu)
	ON_COMMAND(ID_Reduce_Menu, &CClassTreeCtrl::OnReduceMenu)
END_MESSAGE_MAP()

bool CClassTreeCtrl::GetScreenItem(NMHDR *pNMHDR,HTREEITEM* hItem,UINT*uiFlag)
{

	//如果在进程内 返回失败
	if (IsRestricted())
		return false;

	NM_TREEVIEW * pHdr = (NM_TREEVIEW*)pNMHDR;
	CPoint    cpPoint;
	GetCursorPos(&cpPoint);
	CTreeCtrl::ScreenToClient(&cpPoint);
	*hItem = CTreeCtrl::HitTest(cpPoint,uiFlag);

	if (*hItem)
		return true;
	else return false;


}

void CClassTreeCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	HTREEITEM hItem;
	UINT      uFlag;
	if (!GetScreenItem(pNMHDR,&hItem,&uFlag))
		return;


	if (TVHT_ONITEMSTATEICON&uFlag)
		SetItemCheck(hItem,!(CTreeCtrl::GetCheck(hItem)));
	else if (TVHT_ONITEM&uFlag)
	{
		CMainFrame *CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();

		if (CurMainFrm->GetChangeFileDlg()->IsWindowVisible())
		{
			if (SelectItem(hItem))
				CurMainFrm->DClickClassTreeView(hItem,TRUE);
		}
		else
			CurMainFrm->ClickClassTreeView(hItem);

	}
	*pResult = 0;
}
void CClassTreeCtrl::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{

	HTREEITEM hItem;
	UINT      uFlag;
	if (!GetScreenItem(pNMHDR,&hItem,&uFlag))
		return;


	if (TVHT_ONITEMSTATEICON&uFlag)
		SetItemCheck(hItem,!(CTreeCtrl::GetCheck(hItem)));
	else if (TVHT_ONITEM&uFlag)
	{
		CMainFrame *CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();

		CurMainFrm->DClickClassTreeView(hItem,CurMainFrm->GetChangeFileDlg()->IsWindowVisible());

		
	}

	*pResult = 0;
}
void CClassTreeCtrl::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	if (IsRestricted())
		return;
	HTREEITEM hCurrentItem;
	CPoint cpPoint;
	GetCursorPos(&cpPoint);

	CMenu menu;
	menu.LoadMenu(IDR_LEFT_VIEW);
	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;
		if (!pPopupMenu->Create(this, cpPoint.x, cpPoint.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;
		((CFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		CTreeCtrl::ScreenToClient(&cpPoint);
		hCurrentItem =CTreeCtrl::HitTest(cpPoint);
		CTreeCtrl::SelectItem(hCurrentItem);
	}


	SetFocus();
}

bool CClassTreeCtrl::SetItemCheck(HTREEITEM hItem, BOOL bCheck)
{
	SetChildItemCheck(hItem,bCheck);
	SetParentCheck(hItem,bCheck);
	return true;
}
bool CClassTreeCtrl::SetChildItemCheck(HTREEITEM hItem, BOOL bCheck)
{
	HTREEITEM hChildItem;

	hChildItem = CTreeCtrl::GetChildItem(hItem);

	while(hChildItem)
	{
		CTreeCtrl::SetCheck(hChildItem,bCheck);
		SetChildItemCheck(hChildItem,bCheck);
		hChildItem =  CTreeCtrl::GetNextItem(hChildItem,TVGN_NEXT);
	}
	return true;
}
bool CClassTreeCtrl::SetParentCheck(HTREEITEM hItem, BOOL bCheck)
{
	HTREEITEM hParentItem,hNextItem,hPreItem;

	hParentItem =  CTreeCtrl::GetParentItem(hItem);

	if (hParentItem== NULL)
		return  false;

	hNextItem = hItem;


	while((hNextItem!=NULL)&(!bCheck))
	{

		hNextItem =  CTreeCtrl::GetNextItem(hNextItem,TVGN_NEXT);

		if (hNextItem)
			bCheck =  CTreeCtrl::GetCheck(hNextItem);


	}



	hPreItem = hItem;

	while((hPreItem!=NULL)&(!bCheck))
	{
		hPreItem =  CTreeCtrl::GetNextItem(hPreItem,TVGN_PREVIOUS);

		if (hPreItem)
			bCheck =  CTreeCtrl::GetCheck(hPreItem);


	}

	CTreeCtrl::SetCheck(hParentItem,bCheck);
	SetParentCheck(hParentItem,bCheck);
	return true;
}

void CClassTreeCtrl::OnChangefilevalueMenu()
{
	CMainFrame *CurMainFrm;
	CurMainFrm =(CMainFrame*)AfxGetApp()->GetMainWnd();

	CurMainFrm->Changefilevalue();
}
void CClassTreeCtrl::OnUpdateChangefilevalueMenu(CCmdUI *pCmdUI)
{
	extern int iThread;


	if (iThread == Def_Thread_Free)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}
void CClassTreeCtrl::OnSearchfileMenu()
{
	CMainFrame *CurMainFrm;
	CurMainFrm =(CMainFrame*)AfxGetApp()->GetMainWnd();

	CurMainFrm->SearchFile(GetSelectedItem(),false);
}
void CClassTreeCtrl::OnUpdateSearchfileMenu(CCmdUI *pCmdUI)
{
	extern int iThread;

	if (iThread == Def_Thread_Free)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}
void CClassTreeCtrl::OnSearchfilesMenu()
{
	CMainFrame *CurMainFrm;
	CurMainFrm =(CMainFrame*)AfxGetApp()->GetMainWnd();

	CurMainFrm->SearchFile(GetSelectedItem());
}
void CClassTreeCtrl::OnUpdateSearchfilesMenu(CCmdUI *pCmdUI)
{
	extern int iThread;

	if (iThread == Def_Thread_Free)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}

bool CClassTreeCtrl::Sort(int iSort)
{
	return MapSortCurrentItem(TVI_ROOT);
}
bool CClassTreeCtrl::SortCurrentItem(HTREEITEM hItem)
{

	if (CTreeCtrl::SortChildren(hItem))
		return false;
	else
		return true;
}
bool CClassTreeCtrl::MapSortCurrentItem(HTREEITEM hItem)
{
	HTREEITEM hChildItem;

	hChildItem = CTreeCtrl::GetChildItem(hItem);

	while(hChildItem)
	{
		MapSortCurrentItem(hChildItem);
		SortCurrentItem(hChildItem);
		hChildItem =  CTreeCtrl::GetNextItem(hChildItem,TVGN_NEXT);
	}

	return true;
}
bool CClassTreeCtrl::MapDeleteEmpty(HTREEITEM hItem)
{
	HTREEITEM hChildItem,hDeletItem;
	int iNormal,iSelected;

	hChildItem = CTreeCtrl:: GetChildItem(hItem);

	while(hChildItem)
	{
		if (!CTreeCtrl::GetItemImage(hChildItem,iNormal,iSelected))
			return false;
		//if ((iNormal!= _LV_EF)&&(iNormal != _LV_EFAbsent)&&(iNormal != _LV_DFAbsent))

		if ((iNormal == _LV_DF)|| (iNormal == _LV_ADF)|| (iNormal == _LV_ROOT))
			MapDeleteEmpty(hChildItem);
			
		
		hDeletItem = hChildItem;
		hChildItem =  CTreeCtrl::GetNextItem(hChildItem,TVGN_NEXT);
		if ((iNormal == _LV_EFAbsent)||(iNormal == _LV_DFAbsent)||(iNormal == _LV_ADFAbsent))
			CTreeCtrl::DeleteItem(hDeletItem);		
	}

	return true;
}
bool CClassTreeCtrl::DeleteAbsent(int iAbsent)
{
	return MapDeleteEmpty(TVI_ROOT);
}
bool CClassTreeCtrl::StatisticFile(HTREEITEM hItem, int& iEF, int& iDF)
{
	int nImage,nSelectedImage;
	bool bRet;

	do 
	{

		CTreeCtrl::GetItemImage(hItem,nImage,nSelectedImage);

		switch(nImage)
		{
		case _LV_DF:
		case _LV_ADF:
		case _LV_DFAbsent:
		case _LV_ADFAbsent:
		case _LV_ROOT:
		case _LV_ROOTAbsent:
			bRet = StatisticFile(CTreeCtrl::GetChildItem(hItem),iEF,iDF);
			iDF = iDF+1;
			break;
		case _LV_EF:
		case _LV_EFAbsent:
			iEF = iEF+1;
			break;
		}
		hItem =  CTreeCtrl::GetNextItem(hItem,TVGN_NEXT);

	} while (hItem);

	return true;
}




// 设置历史选中项,用于确定在单击Tree 时,如果为重复单击,则不进行操作
void CLeftView::_SetHistoryItem(HTREEITEM hItem)
{
	hHistoryItem = hItem;
}
// 如_SetHistoryItem
HTREEITEM CLeftView::_GetHistoryItem(void)
{
	return hHistoryItem;
}


void CClassTreeCtrl::OnSelectfileMenu()
{
	HTREEITEM hCurrentItem;
	CMainFrame *CurMainFrm;

	hCurrentItem = GetSelectedItem();

	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();

	CurMainFrm->ClickClassTreeView(hCurrentItem);
}


void CClassTreeCtrl::OnUpdateSelectfileMenu(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CClassTreeCtrl::OnReadfilevalueMenu()
{
	HTREEITEM hCurrentItem;
	CMainFrame *CurMainFrm;

	hCurrentItem = GetSelectedItem();

	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
			
	CurMainFrm->DClickClassTreeView(hCurrentItem,CurMainFrm->GetChangeFileDlg()->IsWindowVisible());
}


void CClassTreeCtrl::OnUpdateReadfilevalueMenu(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

bool CClassTreeCtrl::IsRestricted()
{

	extern int  iThread;
	if(iThread == Def_Thread_Free)
		return false;
	else
		return true;
}



void CClassTreeCtrl::ExpandItem(HTREEITEM hItem,UINT uiCode)
{
	HTREEITEM hChildItem;

	if (Expand(hItem,uiCode))
	{
	}

	hChildItem = GetNextItem(hItem,TVGN_CHILD);

	while(hChildItem!=NULL)
	{
	

		ExpandItem( hChildItem, uiCode);

		hChildItem = GetNextItem(hChildItem,TVGN_NEXT);

	}

}


void CClassTreeCtrl::OnExpandMenu()
{
	ExpandItem(GetRootItem(),TVE_EXPAND);

	SelectItem(GetRootItem());
}


void CClassTreeCtrl::OnReduceMenu()
{
	ExpandItem(GetRootItem(),TVE_COLLAPSE);

	Expand(GetRootItem(),TVE_EXPAND);

	SelectItem(GetRootItem());
}
