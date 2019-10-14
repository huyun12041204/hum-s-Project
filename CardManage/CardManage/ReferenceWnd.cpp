// cReferenceWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "CardManage.h"
#include "ReferenceWnd.h"


// cReferenceWnd

IMPLEMENT_DYNAMIC(CReferenceWnd, CDockablePane)

CReferenceWnd::CReferenceWnd()
{

}

CReferenceWnd::~CReferenceWnd()
{
}


BEGIN_MESSAGE_MAP(CReferenceWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PARENTNOTIFY()
END_MESSAGE_MAP()



// cReferenceWnd 消息处理程序



int CReferenceWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CRegKey crkKey;

	if (crkKey.Open(HKEY_CURRENT_USER,_T("Software\\Adobe\\Acrobat Reader"))!= ERROR_SUCCESS)
		bInstall = FALSE;
	else
		bInstall = TRUE;
	crkKey.Close();

	if (!bInstall)
	{
		return -2;
	}

	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect lv_pdfFileRect;
	GetClientRect(lv_pdfFileRect);

	m_wndPDF.Create(_T("&quot;Open PDF File&quot;"),NULL,WS_VISIBLE,lv_pdfFileRect,this,0);
	// TODO:  在此添加您专用的创建代码
	//m_wndPDF.LoadFile(_T("G:\\etsi_ts\\102200_102299\\102221\\15.00.00_60\\ts_102221v150000p.pdf"));

	//m_wndPDF.setCurrentPage(140);
	return 0;

}


void CReferenceWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	if (m_wndPDF.m_hWnd != NULL)
	{
		m_wndPDF.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOACTIVATE | SWP_NOMOVE);
	}

	
}


BOOL CReferenceWnd::OpenReferenceList(CString csName)
{
	BOOL bRet =FALSE ;
	CString csSpecification;

	if (csName.Compare(csFileName) == 0)
		return TRUE;

	CString csDIR ;
	if (!__GetCurrentDIR(csDIR))
		return FALSE;

	if (!GetReferencecsSpecificationName(csName,csSpecification))
		return FALSE;

	bRet = m_wndPDF.LoadFile(csDIR+_T("\\Reference\\")+csSpecification);

	if (bRet)
		csFileName = csName;
	else
		csFileName.Empty();
	m_wndPDF.setLayoutMode(_T("SinglePage"));
	m_wndPDF.setPageMode("none");
	m_wndPDF.setShowToolbar(TRUE);
	m_wndPDF.setView("FitH");


	return bRet;
}


BOOL CReferenceWnd::SetPosition(long ulPage, unsigned int iPosition)
{
	m_wndPDF.setCurrentPage(ulPage);

	if (iPosition>=5)
		m_wndPDF.gotoNextPage();

	//for (UINT i =1 ; i<iPosition ;i++)
		//m_wndPDF.goBackwardStack();
//	int iPos = m_wndPDF.GetScrollPos(SB_VERT);


	//m_wndPDF.setZoomScroll(100,0,iPosition*20);
	//iPos = m_wndPDF.GetScrollLimit(SB_VERT);
	//m_wndPDF.setShowScrollbars(FALSE)
	//CString  csTemp = m_wndPDF.get_src();
	//CString tt   = m_wndPDF.GetVersions();

	//int iPos = m_wndPDF.GetScrollPos(SB_HORZ );

	//m_wndPDF.setZoomScroll(100,5,5);
//	iPos = m_wndPDF.GetScrollLimit(SB_HORZ );
	return TRUE;
}

int _OpenCSVFile(CString csPath,CStdioFile* CSFFile)
{
	CString csData;
	CFileStatus csSta;


	if (!CSFFile->Open(csPath,CFile::shareDenyRead))
		return -1;

	if (! CSFFile->GetStatus(csPath,csSta))
	{
		CSFFile->Close();
		return -2;
	}

	return TRUE;
}

#define  DEF_REFERENCE_ROUTE      1
#define  DEF_REFERENCE_FID        2
#define  DEF_REFERENCE_NAME       3
#define  DEF_REFERENCE_ABBR       4
#define  DEF_REFERENCE_DOC        5
#define  DEF_REFERENCE_PAGE       6
#define  DEF_REFERENCE_POSITION   7

#define  DEF_DFNAME_PATH      1
#define  DEF_DFNAME_NAME      2

#define  DEF_SPECIFICATION_TITLE         1
#define  DEF_SPECIFICATION_FILENAME      2
int CReferenceWnd::GetDFName(CString &csRoute)
{
	int iRet;
	CString csTemp;
	CString csDFName,csPATH;
	CStdioFile CSFFile;
	CString csDIR ;
	if (!__GetCurrentDIR(csDIR))
		return FALSE;

	

	if (_OpenCSVFile(csDIR+"\\Reference\\DFName.csv",&CSFFile) != TRUE)
	{
		MessageBox("打开DF name file 失败");
		return FALSE;
	}

	iRet = CSFFile.ReadString(csTemp);


	while (iRet)
	{
		iRet = CSFFile.ReadString(csTemp);
		if (iRet == FALSE)
			break;

		if (_GetCSVData(csTemp,DEF_DFNAME_PATH,csPATH)<0)
			continue;
		if (_GetCSVData(csTemp,DEF_DFNAME_NAME,csDFName)<0)
			continue;


		if (csRoute == csPATH)
			csRoute = csDFName;

	}

	CSFFile.Close();

	return TRUE;
}


int CReferenceWnd::_GetReferenceInformation(CString csAbbreviation, CString& csDOC, long* ulPage, unsigned int* uiPosition)
{

	CStdioFile CSFFile;
	int iRet ;
	CString csTemp;
	CString csAbbr,csName,csiDOC,csPAGE,csPOSITION;

	if (!__GetCurrentDIR(csTemp))
		return FALSE;

	if (_OpenCSVFile(csTemp+"\\Reference\\ReferenceList.csv",&CSFFile) != TRUE)
	{
		MessageBox("打开Reference list file 失败");
		return FALSE;
	}

	iRet = CSFFile.ReadString(csTemp);

	while (iRet)
	{
		iRet = CSFFile.ReadString(csTemp);
		if (iRet == FALSE)
			break;

		if ((_GetCSVData(csTemp,DEF_REFERENCE_ABBR,csAbbr)<0)
			||(csAbbr.IsEmpty()))
			continue;

		if (_GetCSVData(csTemp,DEF_REFERENCE_NAME,csName)<0)
			continue;
		if (_GetCSVData(csTemp,DEF_REFERENCE_DOC,csiDOC)<0)
			continue;
		if (_GetCSVData(csTemp,DEF_REFERENCE_PAGE,csPAGE)<0)
			continue;
		if (_GetCSVData(csTemp,DEF_REFERENCE_POSITION,csPOSITION)<0)
			continue;


		if ((csAbbr.GetLength()<=csAbbreviation.GetLength())&&
			(csAbbreviation.Mid(0,csAbbr.GetLength()) == csAbbr))
		{
			csDOC       = csiDOC;
			*ulPage     = (long)_CString2IntDecimal(csPAGE); 
			*uiPosition = (unsigned int)_CString2IntDecimal(csPOSITION); 
			if (csiDOC  == _T("31.102"))
				*ulPage +=1;
			else if(csiDOC  == _T("C.S0065-B"))
				*ulPage +=10;

			return TRUE;
		}
	}

	CSFFile.Close();

	return FALSE;

}

int CReferenceWnd::GetReferenceInformation(CString csRoute, CString csFID, CString& csDOC, long* ulPage, unsigned int* uiPosition)
{
	CStdioFile CSFFile;
	int iRet ;
	CString csTemp;
	CString csiRoute,csiFID,csName,csiDOC,csPAGE,csPOSITION;

	if (_OpenCSVFile("\\\\10.102.10.13\\Public\\R_D\\Transfer\\Hu Miaowei\\Reference\\ReferenceList.csv",&CSFFile) != TRUE)
	{
		if (!__GetCurrentDIR(csTemp))
			return FALSE;

		if (_OpenCSVFile(csTemp+"\\Reference\\ReferenceList.csv",&CSFFile) != TRUE)
		{
			MessageBox("打开Reference list file 失败");
			return FALSE;
		}
	}

	iRet = CSFFile.ReadString(csTemp);

	while (iRet)
	{
		iRet = CSFFile.ReadString(csTemp);
		if (iRet == FALSE)
			break;

		if (_GetCSVData(csTemp,DEF_REFERENCE_ROUTE,csiRoute)<0)
			continue;
		if (_GetCSVData(csTemp,DEF_REFERENCE_FID,csiFID)<0)
			continue;
		if (_GetCSVData(csTemp,DEF_REFERENCE_NAME,csName)<0)
			continue;
		if (_GetCSVData(csTemp,DEF_REFERENCE_DOC,csiDOC)<0)
			continue;
		if (_GetCSVData(csTemp,DEF_REFERENCE_PAGE,csPAGE)<0)
			continue;
		if (_GetCSVData(csTemp,DEF_REFERENCE_POSITION,csPOSITION)<0)
			continue;

		if ((csRoute == csiRoute)&&
			(csFID == csiFID))
		{
			csDOC       = csiDOC;
			*ulPage     = (long)_CString2IntDecimal(csPAGE); 
			*uiPosition = (unsigned int)_CString2IntDecimal(csPOSITION); 
			if (csiDOC  == _T("31.102"))
				*ulPage +=1;
			else if(csiDOC  == _T("C.S0065-B"))
				*ulPage +=10;



			return TRUE;
		}
	}

	CSFFile.Close();

	return FALSE;
}

int CReferenceWnd::GetReferencecsSpecificationName(CString csDOC,CString&csSpecificationName)
{
	CStdioFile CSFFile;
	int iRet ;
	CString csTemp;
	if (!__GetCurrentDIR(csTemp))
		return FALSE;
	CString csTitle,csiFileName;
	if (_OpenCSVFile(csTemp+"\\Reference\\SpecificationList.csv",&CSFFile) != TRUE)
	{
		MessageBox("打开Specification List file 失败");
		return FALSE;
	}
	iRet = CSFFile.ReadString(csTemp);
	while (iRet)
	{
		iRet = CSFFile.ReadString(csTemp);
		if (iRet == FALSE)
			break;
		if (_GetCSVData(csTemp,DEF_SPECIFICATION_TITLE,csTitle)<0)
			continue;
		if (_GetCSVData(csTemp,DEF_SPECIFICATION_FILENAME,csiFileName)<0)
			continue;
		if (csDOC == csTitle)
		{
			csSpecificationName = csiFileName;
			return TRUE;
		}
	}
	return FALSE;
}

int CReferenceWnd::_OpenReference(CString csAbbren)
{
	CString csDOC;
	long lPage;
	UINT  uiPosition;

	if (!bInstall)
		return FALSE;

	if ((csAbbren.GetLength()>3)&&
		 csAbbren.Mid(0,3)== _T("EF-"))
		csAbbren = csAbbren.Mid(3);

	if (!_GetReferenceInformation(csAbbren,csDOC,&lPage,&uiPosition))
		return FALSE;

	if (!OpenReferenceList(csDOC))
		return FALSE;

	SetPosition(lPage,uiPosition);

	return TRUE;
}

int CReferenceWnd::OpenReference(CString csRoute, CString csFID)
{
	CString csDOC;
	long lPage;
	UINT  uiPosition;

	if (!bInstall)
		return FALSE;

	if (!GetDFName(csRoute))
		return FALSE;
	if (!GetReferenceInformation(csRoute,csFID,csDOC,&lPage,&uiPosition))
		return FALSE;

	if (!OpenReferenceList(csDOC))
		return FALSE;

	SetPosition(lPage,uiPosition);
	
	return TRUE;
}


void CReferenceWnd::OnParentNotify(UINT message, LPARAM lParam)
{
	//CDockablePane::OnParentNotify(message, lParam);

	// TODO: 在此处添加消息处理程序代码
}

