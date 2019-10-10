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
// BitsAnalyserView.cpp : CBitsAnalyserView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "BitsAnalyser.h"
#endif

#include "BitsAnalyserDoc.h"
#include "BitsAnalyserView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define  Def_Bit_NULL -1 //����Ϊ�յ����
#define  Def_Bit_S  0 //��ʼλ
#define  Def_Bit_DS 1 //����λ 
#define  Def_Bit_DE 8 //����λ 
#define  Def_Bit_F  9 //У��λ
#define  Def_Bit_E 11 //��������λ


bool bBitt[11];  //һ������������10λ

int iPrescale  = 372; //��Ƶ
int iDeviation = 4;  //���ֵ
int iCheckiDeviation = 7 ; //У��λ�����ֵ��
int iStopDeviation   = iPrescale/5;

BYTE bPreBit[10];
BYTE bPreBit0 = 0;//ǰ��һ����bit����


//************************************
// Method:    _Bits2Byte
// FullName:  _Bits2Byte
// Access:    public 
// Returns:   int 
//-1 �� bBits���Ȳ���;
//-2 : ��ʼλΪ �ߵ�ƽ
//-3 : ����λΪ �͵�ƽ
//-4 : У��Ϊ ����
// Qualifier:
// Parameter: bool * bBits
// Parameter: UINT bBitLen
// Parameter: BYTE * bByte
//************************************
#define  _Bits_Success 1

int _Bits2Byte(bool *bBits, UINT bBitLen, BYTE* bByte)
{

	*bByte = 0;
	//λ������ֱ�ӷ���ʧ��
	if (bBitLen<11)
		return -1;

	if (bBits[0] != false)
		return  -2;

	if (bBits[10] == false)
		return  -3;

	//if (bBits[9] == false)
	//	return  -4;

	for (int i = 0; i < 8; i++)
	{
		if (bBitt[i + 1] == 1)
			*bByte |= (1 << (i));
	}

	return _Bits_Success;

}
#define  _CLK_Wait    2
#define  _CLK_Success 1
#define  _CLK_NoData  0
#define  _CLK_Error  -1


int iBitStatue = Def_Bit_S;




int iPreCorrent = 0;




int _CLKDiffData2Byte_2(BYTE* bBit,UINT bBitLen, BYTE *bByte)
{
	int iRet           = _CLK_NoData; //��ʾ��ǰ�洢�˶���Ϊ��bit�� 
	int bBitNumber     = 0 ;   // ���¿��Լ������bit
	int iBitsDeviation = iDeviation;
	int iii;
	int lDiff = 0 ; 

	for (UINT i = 1 ;i < bBitLen ;i++ )
		lDiff = lDiff + (bBit[i]<<8*(i-1));


	bBitNumber = lDiff/iPrescale;
	if ((lDiff%iPrescale) > iPrescale/2)
		bBitNumber += 1;

	for ( iii = 0; iii < bBitNumber; iii++)
	{

		if ((iBitStatue == Def_Bit_S )&&
			(!(bBit[0]>>6)))
		{
			iRet       = _CLK_Wait;
			bBitNumber = 0;
			continue;
		}


		if (iBitStatue < 11)
		{
			
			bBitt[iBitStatue] = (bool)(( bPreBit0 >>6));
			
			iBitStatue += 1;
			
			iRet = _CLK_Wait;
		}
		else
		{
			if (_Bits2Byte(bBitt, 11, bByte)== _Bits_Success)
				iRet = _CLK_Success;
			else
			//�˴���Ҫ������Ӵ��룬��������ʱ�������
				iRet = _CLK_Error;

			iBitStatue = Def_Bit_S;
			ZeroMemory(bBitt, sizeof(bBitt));

			bBitNumber = 0;
			continue;

		}

	}


	bPreBit0 = bBit[0];
__End:	return iRet;

}



CString CLKDiffText(BYTE* bBit,UINT bBitLen)
{
	CString csRes;
	CString csCor;

	long lDiff = 0 ; 
	int iCorrent;
	int iNumber ;

	csRes.Empty();

	for (UINT i = 1 ;i < bBitLen ;i++ )
		lDiff = lDiff*0x100 + bBit[i];

	if (((lDiff+iDeviation )%iPrescale > 2*iDeviation)&&
		((lDiff+iDeviation)/iPrescale)<8)
	{
		lDiff += iPreCorrent;
		csCor.Format(" Corrent :%d",iPreCorrent);
	}
	else
		csCor.Empty();


	iCorrent = lDiff%iPrescale;
	iNumber  = lDiff/iPrescale;



	if (iNumber < 12)
	{
		if (iCorrent> (iPrescale/2))
		{
			iCorrent = iCorrent - iPrescale;
			iNumber +=1;
		}


		//iPreCorrent = iCorrent;
		csRes.Format("ETU:%d Diff:%d",iNumber,iCorrent);
	}
	//else
	//	csRes.Format("CLK:%l",lDiff);


	

	return csRes+csCor;


}

#define  _BYTE_Wait    2
#define  _BYTE_Success 1
#define  _BYTE_NoData  0
#define  _BYTE_Error  -1
#define  _TPDU_NULL  0x00
#define  _TPDU_ATR   0x10
#define  _TPDU_PPS   0x20
#define  _TPDU_TPDU  0x30

#define  _Max_TPDU_Len 0x200
BYTE bPreByte[_Max_TPDU_Len];
UINT iByteLen = 0;
int  iTPDUStatue = _TPDU_NULL;

bool _ATRIsComplete(BYTE* bATR,UINT iATRLen)
{
	UINT iHisLen;
	//��ȻҪ��TS T0
	if (iATRLen < 2)
		return false;
	iHisLen = bATR[1] & 0xF;

	if (iATRLen < 2 + iHisLen)
		return false;

	//�˴�����Ƿ� Txi �Ƿ�������
	int iCheckSum = 0;
	int iLevel    = 0;
	UINT iOffset   = 2;
	BYTE TDi;

	do 
	{
		//ǰһ��TDi
		TDi = bATR[iOffset-1];
		//�������FЭ�飬���ʾ��ҪУ��λ
		if ((iLevel != 0)&&
			((TDi&0xF) == 0xF))
			iCheckSum = 1;


		if (TDi&0x10)
			iOffset += 1;
		if (TDi & 0x20)
			iOffset += 1;
		if (TDi & 0x40)
			iOffset += 1;
		if (TDi & 0x80)
			iOffset += 1;
		if (iOffset>iATRLen)
			return false;
		iLevel++;
	} while (TDi&0x80);

	if ((iOffset+iHisLen+iCheckSum) == iATRLen)
		return true;



	return false;
}

//************************************
// Method:    _PPSIsComplete
// FullName:  _PPSIsComplete
// Access:    public 
// Returns:   bool
// Qualifier: 
// Parameter: BYTE * bPPS
// Parameter: UINT iPPSLen
// ��ǰֻ�ж���T0 Э��
//************************************
bool _PPSIsComplete(BYTE* bPPS, UINT iPPSLen)
{
	if (iPPSLen<7)
		return false;

	if ((bPPS[6] == 0)&&
		(iPPSLen == 7))
		return true;

	if (iPPSLen == 8)
		return true;

	return false;
}

//************************************
// Method:    _PPSIsSuccess
// FullName:  _PPSIsSuccess
// Access:    public 
// Returns:   int ,Prescale
// Qualifier:
// Parameter: BYTE * bPPS
// Parameter: UINT iPPSLen
// Parameter: CString & csSend
// Parameter: CString & csResponse
//************************************
int _PPSIsSuccess(BYTE* bPPS, UINT iPPSLen,
	CString &csSend,CString& csResponse)
{
	int iCurPrescale = 372;
	_UcHex2CString(bPPS, 4, csSend);
	_UcHex2CString(bPPS+4, iPPSLen-4, csResponse);

	if (csSend.Compare(csResponse)==0)
	{
		switch (bPPS[2])
		{
		case 0x94:iCurPrescale = 64; break;
		case 0x95:iCurPrescale = 32; break;
		case 0x96:iCurPrescale = 16; break;
		case 0x97:iCurPrescale = 8; break;
		case 0x18:iCurPrescale = 31; break;
		case 0x11:iCurPrescale = 372; break;
		case 0x10:iCurPrescale = 372; break;
		default:iCurPrescale = 372; break;
		}
		
	}

	return iCurPrescale;
}

bool _TPDUIsComplete(BYTE* bTPDU, UINT iTPDULen,
	CString&csSend,
	CString&csProduce, CString&csACK,
	CString&csData, CString&csLProduce,CString&csSW)
{
	bool bRet = false;
	int iDataLen;
	if (iTPDULen < 7)
		return false;

	//�˴��ж��Ƿ��й����ַ�
	UINT iProduceNumber = 0;
	UINT iLProduceNumber = 0;
	for (UINT i = 5; i< iTPDULen;i++)
	{
		if (bTPDU[i] == 0x60)
			iProduceNumber++;
		else
			break;
	
	}
	if (iTPDULen < (iProduceNumber+7))
		return false;



	//�ж��Ƿ���Ӧ��
	//������Ins 
	// case 1
	if (bTPDU[5+iProduceNumber] != bTPDU[1])
	{
		if (iTPDULen == (iProduceNumber + 7))
		{
			_UcHex2CString(bTPDU, 5, csSend);
			_UcHex2CString(bTPDU+5, iProduceNumber, csProduce);
			csACK.Empty();
			csData.Empty();
			_UcHex2CString(bTPDU + 5+ iProduceNumber, 2, csSW);
			bRet = true;
		}

	}
	//case 2
	else
	{

		if (bTPDU[4] == 0)
			iDataLen = 0x100;
		else
			iDataLen = bTPDU[4];


		for (UINT i =  (6 + iProduceNumber + iDataLen); i< iTPDULen;i++)
		{
			if (bTPDU[i] == 0x60)
				iLProduceNumber++;
			else
				break;

		}

		if ((iDataLen + 8 + iProduceNumber+iLProduceNumber) == iTPDULen)
		{
			_UcHex2CString(bTPDU , 5, csSend);
			_UcHex2CString(bTPDU + 5, iProduceNumber, csProduce);
			_UcHex2CString(bTPDU + 5 + iProduceNumber, 1, csACK);
			_UcHex2CString(bTPDU + 5 + iProduceNumber + 1,  iDataLen, csData);
			_UcHex2CString(bTPDU + 5 + iProduceNumber + 1 + iDataLen,  iLProduceNumber, csLProduce);
			_UcHex2CString(bTPDU + 5 + iProduceNumber + 1 + iDataLen + iLProduceNumber, 2, csSW);
			bRet = true;

		}



	}






	return bRet;
}



bool P3IsLE(BYTE* HEAD)
{
	bool bP3IsLe = false;
	switch(HEAD[1])
	{
	case 0xA4:
		if ((HEAD[2] == 3)&&(HEAD[3] == 4))
			bP3IsLe = true ;
		else
			bP3IsLe = false;
		break;
	case 0x75:
		if ((HEAD[2]&4)== 0)
			bP3IsLe = true ;
		else
			bP3IsLe = false;
		break;
	case 0xCB:
		if ((HEAD[3]&0xDF)== 0)
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

	return bP3IsLe;

}
//************************************
// Method:    ByteData2TPDU
// FullName:  ByteData2TPDU
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: BYTE bByte
// Parameter: BYTE * bTPDU
// Parameter: UINT * uiTPDULen
//************************************
int ByteData2TPDU(BYTE bByte, BYTE *bTPDU,UINT * uiTPDULen,
	              CString&csSend,
	              CString&csProduce,CString&csACK,
	              CString&csData,CString&csLProduce,CString&csSW)
{
	int iRet = _BYTE_Wait;


	bPreByte[iByteLen] = bByte;
	iByteLen += 1;

	switch (iTPDUStatue)
	{
	case _TPDU_NULL:iTPDUStatue = _TPDU_ATR; break;
	case _TPDU_ATR :
		if (_ATRIsComplete(bPreByte, iByteLen))
		{
			iRet = _BYTE_Success|_TPDU_ATR;
			_UcHex2CString(bPreByte, iByteLen, csData);
			
			iTPDUStatue = _TPDU_PPS;
		}
		break;
	case _TPDU_PPS:

		if (bPreByte[0] != 0xFF)
			iTPDUStatue = _TPDU_TPDU;

		if (_PPSIsComplete(bPreByte, iByteLen))
		{
			iRet = _BYTE_Success|_TPDU_PPS;

			iPrescale = _PPSIsSuccess(bPreByte, iByteLen, csSend, csData);

		
		}
		break;
	case _TPDU_TPDU:

		if (_TPDUIsComplete(bPreByte, iByteLen, csSend,csProduce,csACK,csData,csLProduce,csSW))
		{
			iRet = _BYTE_Success|_TPDU_TPDU;

		
		}

		break;

	default:
		break;
	}


	if ((iRet&0xF) == _BYTE_Success)
	{
		*uiTPDULen = iByteLen;
		memcpy(bTPDU, bPreByte, iByteLen);
		ZeroMemory(bPreByte, sizeof(bPreByte));
		iByteLen = 0;
	}
	return iRet;


}
// CBitsAnalyserView

IMPLEMENT_DYNCREATE(CBitsAnalyserView, CView)

BEGIN_MESSAGE_MAP(CBitsAnalyserView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CBitsAnalyserView ����/����

CBitsAnalyserView::CBitsAnalyserView()
{
	// TODO: �ڴ˴���ӹ������

}

CBitsAnalyserView::~CBitsAnalyserView()
{
}

BOOL CBitsAnalyserView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CBitsAnalyserView ����

void CBitsAnalyserView::OnDraw(CDC* /*pDC*/)
{
	CBitsAnalyserDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CBitsAnalyserView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBitsAnalyserView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBitsAnalyserView ���

#ifdef _DEBUG
void CBitsAnalyserView::AssertValid() const
{
	CView::AssertValid();
}

void CBitsAnalyserView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBitsAnalyserDoc* CBitsAnalyserView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBitsAnalyserDoc)));
	return (CBitsAnalyserDoc*)m_pDocument;
}
#endif //_DEBUG


// CBitsAnalyserView ��Ϣ�������


//BOOL CBitsAnalyserView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
//{
//	// TODO: �ڴ����ר�ô����/����û���
//
//	return CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
//}


int CBitsAnalyserView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	GetClientRect(rectDummy);


	const DWORD dwViewStyle =  WS_CHILD|WS_VISIBLE|WS_BORDER|ES_MULTILINE;

	m_wndEdit.Create(dwViewStyle,rectDummy,this,1);
	m_wndEdit.EnableWindow(FALSE);
	m_wndEdit.ShowWindow(FALSE);

	// �����������:
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT |LBS_MULTIPLESEL|
		WS_CHILD|WS_VISIBLE|WS_HSCROLL| 
		WS_VSCROLL|WS_CLIPSIBLINGS|WS_CLIPCHILDREN;
	m_APDUList.Create(dwStyle,rectDummy,this,2);
	m_APDUList.ShowWindow(TRUE);
	//m_APDUList.AddString("TEST");

	UpdateFonts();
	bbitsLen = 0;
	bdiflen  = 0;
	return 0;
}


int CBitsAnalyserView::PrintEdit(BYTE* bInput, UINT uiLen)
{

	CString csPrint;
	m_wndEdit.SetSel(-1,-1);

	_UcHex2CString((BYTE*)bInput,uiLen,csPrint);

	m_wndEdit.ReplaceSel(csPrint);
	return 0;
}


void CBitsAnalyserView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);


	m_wndEdit.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	m_APDUList.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	// TODO: �ڴ˴������Ϣ����������
}





int CBitsAnalyserView::ViewAPDU(BYTE* ucBits , UINT BitsLen)
{	BYTE bBYTE;

	for (UINT k = 0 ; k< BitsLen; k++)
	{

		bbits[bbitsLen] =  ucBits[k];

		if (bbitsLen == 0)
			bdiflen = (bbits[0]&0x7)+1;
		bbitsLen = bbitsLen+1;

		if (bbitsLen  == bdiflen)
		{
	
			if (_CLKDiffData2Byte_2(bbits,bbitsLen,&bBYTE) == _BYTE_Success)
			{

				BYTE bBYTES[300];
				UINT iLen = 0;
				CString csSend,csPro,csACK,csData,csLPro,csSW;
				CString csTPDU;
				CStringArray csInfomation;
				int iRet = ByteData2TPDU(bBYTE,bBYTES,&iLen ,csSend,csPro,csACK,csData,csLPro,csSW);
				if ((iRet&0xF) == _BYTE_Success)
				{

					switch(iRet&0xF0)
					{

					case _TPDU_ATR:

						if (ExplainATR(csData,csInfomation))
						{
							for (int i = 0 ; i < csInfomation.GetCount(); i++)
								m_APDUList.FomatAddString(csInfomation.GetAt(i));
							m_APDUList.FomatAddString(csData,_DEF_APDU_ATR);
						}
						///m_APDUList.FomatAddString(csData,_DEF_APDU_ATR);
						break;
					case _TPDU_PPS:
						m_APDUList.FomatAddString(csSend+csData,_DEF_APDU_PPS);
						break;

					case _TPDU_TPDU:

						//if (P3IsLE(bBYTES))
						//		_ExplainAPDU(csSend,csData + csSW,csInfomation);
						//else
						//	_ExplainAPDU(csSend + csData,csSW,csInfomation);
						

						//for (int i = 0 ; i < csInfomation.GetCount(); i++)
						//	m_APDUList.FomatAddString(csInfomation.GetAt(i));

						m_APDUList.FomatAddString(csSend,_DEF_APDU_HEAD);
						m_APDUList.FomatAddString(csPro ,_DEF_APDU_NULL);
						m_APDUList.FomatAddString(csACK,_DEF_APDU_ACK);
						m_APDUList.FomatAddString(csData,_DEF_APDU_DATA);
						m_APDUList.FomatAddString(csLPro,_DEF_APDU_NULL);
						m_APDUList.FomatAddString(csSW,_DEF_APDU_SW);

						break;

					default:
						_UcHex2CString(bBYTES,iLen,csTPDU);
						m_APDUList.AddString(csTPDU);break;


					}

				   

					//int index = m_APDUList.GetCurSel();

					//KillForc
				//	m_APDUList.SetSel(index,FALSE);
					m_APDUList.SetCaretIndex(m_APDUList.GetCount()-1);
					//CString csTPDU;
					//_UcHex2CString(bBYTES,iLen,csTPDU);
					//m_APDUList.AddString(csTPDU);
					//m_APDUList.SetCaretIndex(m_APDUList.GetCount());
					//if (!csSW.IsEmpty())
					//{
					//	if (((_CString2Int(csSW)&0xF000)!=0x9000)&&
					//		((_CString2Int(csSW)&0xF000)!=0x6000))
					//	{
					//		m_APDUList.AddString("ERR");

					//	}
					//}
				}

				if (iRet < 0)
				{
					CString csErr;
					csErr.Format("Error code : %x",iRet);
					AfxMessageBox(csErr);
				}


			}


			//�˴�ΪReset
			if ((bbits[0]&0x30) != 0x30) 
			{
				iPrescale   = 372;
				iBitStatue  = Def_Bit_S;
				iTPDUStatue = _TPDU_NULL;
				iByteLen = 0;
			}
			bbitsLen = 0;
			bdiflen  = 0;

		}
		else if (bdiflen == 0)
		{

			bbitsLen = 0;
			bdiflen  = 0;
		}

	}
	return 0;
}

void CBitsAnalyserView::UpdateFonts()
{
	m_APDUList.SetFont(&afxGlobalData.fontRegular);
	m_wndEdit.SetFont(&afxGlobalData.fontRegular);

}