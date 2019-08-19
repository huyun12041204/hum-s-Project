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

// CardManageDoc.cpp : CCardManageDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CardManage.h"
#endif

#include "CardManageDoc.h"
#include "CardManageView.h"
#include "MainFrm.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCardManageDoc

IMPLEMENT_DYNCREATE(CCardManageDoc, CDocument)

BEGIN_MESSAGE_MAP(CCardManageDoc, CDocument)
END_MESSAGE_MAP()


// CCardManageDoc ����/����

CCardManageDoc::CCardManageDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CCardManageDoc::~CCardManageDoc()
{
}

BOOL CCardManageDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	SetTitle(_T("���Կ�Ƭ"));
	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CCardManageDoc ���л�

void CCardManageDoc::Serialize(CArchive& ar)
{
	CMainFrame *CurMainFrm;
	CString csTemp;

	CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();

	if (ar.IsStoring())
	{
		if(CurMainFrm->bGetData)
			ar.WriteString(CurMainFrm->csCard);
		//else
			//MessageBox(_T("��Ҫ�Ȼ�ȡ�ļ����ݣ�"));
	}
	else
	{

		CurMainFrm->csCard.Empty();

		while(ar.ReadString(csTemp))
			CurMainFrm->csCard += csTemp;

		CurMainFrm->SetRam2TreeItem();
	}

}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CCardManageDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CCardManageDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:  strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CCardManageDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCardManageDoc ���

#ifdef _DEBUG
void CCardManageDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCardManageDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCardManageDoc ����
