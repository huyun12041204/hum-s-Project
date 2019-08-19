#pragma once
#include "CAcroAXDocShim.h"

// cReferenceWnd

class CReferenceWnd : public CDockablePane
{
	DECLARE_DYNAMIC(CReferenceWnd)

public:
	CReferenceWnd();
	virtual ~CReferenceWnd();

	CAcroAXDocShim m_wndPDF;
	CString csFileName;
	BOOL    bInstall;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//************************************
	// Method:    OpenReferenceList
	// FullName:  CReferenceWnd::OpenReferenceList
	// Access:    public 
	// Returns:   BOOL TRUE FALSE
	// Qualifier: 
	// Parameter: CString csName "31.102", "102.221"
	//************************************
	BOOL OpenReferenceList(CString csName);
	//************************************
	// Method:    SetPosition
	// FullName:  CReferenceWnd::SetPosition
	// Access:    public 
	// Returns:   BOOL
	// Qualifier:
	// Parameter: long ulPage  
	// Parameter: unsigned int iPosition 1开头位置,2中间位置,3末尾位置
	//************************************
	BOOL SetPosition(long ulPage, unsigned int iPosition);
	//************************************
	// Method:    GetDFName
	// FullName:  CReferenceWnd::GetDFName
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: CString & csRoute
	//************************************
	int GetDFName(CString &csRoute);


	//************************************
	// Method:    _GetReferenceInformation
	// FullName:  CReferenceWnd::_GetReferenceInformation
	// Access:    public 
	// Returns:   int
	// Qualifier: 当前只能对PHONEBOOL 未定义的4FXX文件进行识别
	// Parameter: CString csAbbreviation "IAP"
	// Parameter: CString & csDOC
	// Parameter: long * ulPage
	// Parameter: unsigned int * uiPosition
	//************************************
	int _GetReferenceInformation(CString csAbbreviation, CString& csDOC, long* ulPage, unsigned int* uiPosition);
	//************************************
	// Method:    GetReferenceInformation
	// FullName:  CReferenceWnd::GetReferenceInformation
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: CString csRoute  目录 "USIM","7FF0","3F00","7F105F3A"
	// Parameter: CString csFID    FID  "6F07"
	// Parameter: long * ulPage    文档的页数  
	// Parameter: unsigned int * uiPosition 所在位置 见SetPosition
	//************************************
	int GetReferenceInformation(CString csRoute, CString csFID, CString& csDOC, long* ulPage, unsigned int* uiPosition);




	//************************************
	// Method:    GetReferenceDOCFileName
	// FullName:  CReferenceWnd::GetReferenceDOCFileName
	// Access:    public 
	// Returns:   int
	// Qualifier: See SpecificationList.csv
	// Parameter: CString csDOC         11.11                   31.102
	// Parameter: CString & csFileName  ts_100977v081400p.pdf   ts_131102v150100p.pdf
	//************************************
	int GetReferencecsSpecificationName(CString csDOC,CString&csSpecificationName);


	//************************************
	// Method:    _OpenReference
	// FullName:  CReferenceWnd::_OpenReference
	// Access:    public 
	// Returns:   int
	// Qualifier: 当前只能对PHONEBOOL 未定义的4FXX文件进行识别
	//            之作为 补充，
	// Parameter: CString csAbbren
	// Parameter: CString csFID
	//************************************
	int _OpenReference(CString csAbbren);
	//************************************
	// Method:    OpenReference
	// FullName:  CReferenceWnd::OpenReference
	// Access:    public 
	// Returns:   int
	// Qualifier:
	// Parameter: CString csRoute See GetReferenceInformation
	// Parameter: CString csFID   See GetReferenceInformation
	//************************************
	int OpenReference(CString csRoute, CString csFID);
	afx_msg void OnParentNotify(UINT message, LPARAM lParam);
};


