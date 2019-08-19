// BasicConvert.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "Basusc2.h"
#include "BasicConvert.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CBasicConvertApp

BEGIN_MESSAGE_MAP(CBasicConvertApp, CWinApp)
END_MESSAGE_MAP()


// CBasicConvertApp 构造

CBasicConvertApp::CBasicConvertApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CBasicConvertApp 对象

CBasicConvertApp theApp;


// CBasicConvertApp 初始化

BOOL CBasicConvertApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}




//CString 操作CString
//************************************
// Method:    _IsValid
// FullName:  _IsValid
// Access:    public 
// Returns:   BOOL
// Qualifier: 
// Parameter: CString csInput 
// Return   : TURE or FALSE 
// Input "F..F" or "0..0" return FALSE  
//************************************
BOOL _IsValid(CString csInput)
{
	int iDataLen,iCurData,i;

	iDataLen = csInput.GetLength();

	for (i=0;i<iDataLen;i++)
	{
		iCurData = _ttoi(csInput.Mid(i,1));

		if ((iCurData!=0x0)&&(iCurData!=0xf))
			return TRUE;
	}
	return FALSE;
}



//************************************
// Method:    UcHex2CString
// FullName:  UcHex2CString
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: BYTE * ucInput ={0x00,0xA4,0x04,0x04,0x02,0x3F,0x00}
// Parameter: int iInputLen  = 7
// Parameter: CString & csOutput = "00A40404023F00" 
//************************************
void _UcHex2CString(BYTE* ucInput,int iInputLen,CString& csOutput)
{

	CString csTemp;
	csTemp.Empty();
	csOutput.Empty();
	for (int i = 0; i<iInputLen ; i++)
	{
		csTemp.Format(_T("%02X"), ucInput[i]);
		csOutput+=csTemp;
	}
	//return TRUE
}

int Ascii2Hex(BYTE *ucSou,int iSouLen,BYTE *ucDes)
{
	int i,iTemp;

	for (i = 0 ; i<iSouLen;i++)
	{
		if (ucSou[i]>='a')
			iTemp = 0x57;
		else
			iTemp = 0x37;

		ucDes[i] = ((ucSou[i]>'9')? (ucSou[i]-iTemp):((ucSou[i])&0x0f));
	}
	return i;

}

//************************************
// Method:    CString2UcHex
// FullName:  CString2UcHex
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: CString csInput = "00A40404023F00"
// Parameter: BYTE * ucOutput = {0x00,0xA4,0x04,0x04,0x02,0x3F,0x00}
// return     7
//************************************
int _CString2UcHex(CString csInput,BYTE* ucOutput)
{

	int iSouLen;
	int i;

	iSouLen = csInput.GetLength();

	BYTE *ucInput = new BYTE [iSouLen];
	BYTE *ucTemp  = new BYTE [iSouLen];
	CString csTemp;
	CString csResult;
	csResult.Empty();

	for ( i= 0 ; i < iSouLen ;i++)
	{
		ucInput[i] = (BYTE)csInput.GetAt(i);
	}

	iSouLen = Ascii2Hex(ucInput,iSouLen,ucTemp);

	for ( i = 0 ; i<iSouLen;i+=2)
	{
		ucOutput[i/2] = ucTemp[i]*0x10 +ucTemp[i+1];
	}

	delete ucInput;
	delete ucTemp;

	return iSouLen/2;

}

int _CString2Int(CString csInput)
{

	int iCyc;
	int iRet;
	int iResult;
	iResult = 0;
	if (csInput.IsEmpty())
		return iResult;

	iRet = csInput.GetLength();

	if ((iRet%2)!=0)
		csInput = _T("0")+csInput;

	BYTE *ucInput = new BYTE [iRet]; 


	iRet = _CString2UcHex(csInput,ucInput);

	for (iCyc= 0 ; iCyc<iRet ;iCyc++)
	{

		iResult = iResult*0x100+ucInput[iCyc];
	}

	return iResult;
}

int _CString2IntDecimal(CString csInput)
{
	int iCyc;
	int iRet;
	int iResult,iTemp;
	iResult = 0;
	if (csInput.IsEmpty())
		return iResult;

	iRet = csInput.GetLength();

	if ((iRet%2)!=0)
		csInput = _T("0")+csInput;

	BYTE *ucInput = new BYTE [iRet]; 


	iRet = _CString2UcHex(csInput,ucInput);

	for (iCyc= 0 ; iCyc<iRet ;iCyc++)
	{
		iTemp   = ucInput[iCyc];
		iTemp   =( iTemp>>4)*10 + (iTemp&0xF);

		iResult = iResult*100+iTemp;
	}

	return iResult;
}

void _Int2CString(int iInput,CString&csOutput,int iLength)
{
	int iDataLen;
	CString csPadding;
	csOutput.Empty();
	if (iLength == 0)
		csOutput.Format(_T("%X"),iInput);
	else	
		csOutput.Format(_T("%0X"),iInput);

	iDataLen = csOutput.GetLength();

	if (iDataLen < iLength)
	{
		 _RepeatCString(_T("0"),iLength - iDataLen,csPadding);
		 csOutput=csPadding+csOutput;
	}	
	else if (iDataLen > iLength)
		csOutput = csOutput.Right(iDataLen);
}

void _Int2CStringDecimal(int iInput,CString&csOutput)
{
	csOutput.Format(_T("%d"),iInput);
}




BOOL _Getbit(CString csData,int ibit)
{
	int iLen;
	int iTemp;

	iLen = csData.GetLength()*4;

	if (ibit > iLen)
		return FALSE;

	ibit = ibit-1;

	iTemp = _CString2Int(csData.Mid((ibit/8)*2,2));

	iTemp = iTemp >> (ibit%8);

	if ((iTemp&0x1)==1)
		return TRUE;
	else
		return FALSE;
}
BOOL _Getbit_E(CString csData,int ibit)
{
	int iLen;
	int iTemp;

	iLen = csData.GetLength()*4;

	if (ibit > iLen)
		return FALSE;

	if ((ibit % 8 ) != 0)
	{
		iTemp = _CString2Int(csData.Mid(((ibit)/8)*2,2));
		iTemp = iTemp >> (8- (ibit%8));
	}
	else
	{
		iTemp = _CString2Int(csData.Mid(((ibit)/8 -1 )*2,2));
	}

	if ((iTemp&0x1)==1)
		return TRUE;
	else
		return FALSE;
}
int  _Getbit_E_I(CString csData,int iStartbit ,int ibitLen)
{
	int iRet;
	if (ibitLen > 32)
		return -1;

	iRet = 0;
	for (int i = 0 ; i < ibitLen ; i ++)
	{
		iRet = iRet *2 + (int) _Getbit_E(csData,(iStartbit+i+1));
	}

	return iRet;

}
BOOL _Getbit_E_C(CString csInput,int iStartbit ,int ibitLen,CString &csOutput)
{

	int iRet,i;
	CString csTemp;
	csOutput .Empty();

	for (i = 0 ; i < ibitLen/8; i++)
	{
		iRet = _Getbit_E_I(csInput,iStartbit+(i*8) ,8);
		if (iRet <0 )
		{
			csOutput.Empty();
			return FALSE;
		}
		csTemp.Format(_T("%02X"),iRet);
		csOutput += csTemp;
	}

	iRet = _Getbit_E_I(csInput,iStartbit+(i*8) ,ibitLen %8);
	if (iRet <0 )
	{
		csOutput.Empty();
		return FALSE;
	}else if (iRet > 0 )
	{
		csOutput.Format(_T("%02X"),iRet);
		csOutput += csTemp;

	}
	return TRUE;
}

//************************************
// Method:    _Setbit
// FullName:  _Setbit
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: CString & csData = 0000 
// Parameter: int ibit           1      2     9
// Parameter: bool bbit          true   true  true
//                               0100   0200  0001
//************************************
BOOL _Setbit(CString& csData,int ibit,bool bbit)
{
	int iBYTE, iOffset,iDataLen,iSet;
	CString csTemp;

	iDataLen= csData.GetLength();

	iOffset = (ibit-1)/8;
	iOffset = iOffset*2;

	if (iOffset > (iDataLen-2)) return FALSE;

	iBYTE = _CString2Int( csData.Mid(iOffset,2));

	ibit = (ibit-1)%8;

	if ((bool)((iBYTE >> ibit )&1) != bbit)
	{

		iSet = 1;
		iSet = iSet<<ibit;
		if (bbit)
			iBYTE = (iBYTE|iSet);
		else
		{
			iSet = !iSet;

			iBYTE = (iBYTE&iSet);
		}

	}


	_Int2CString(iBYTE,csTemp,2);

	csData = csData.Left(iOffset)+csTemp+csData.Right(iDataLen-iOffset-2);

	return TRUE;


}

BOOL __Copy2bit(BYTE *ucDes,BYTE *ucSou,int iCpbLen,int iStartB,int iStartb)
{


	BYTE *ucTemp;
	BOOL bRet;
	int iResLen = 0;
	int iDataLen;

	iDataLen = iCpbLen/8;

	if (iCpbLen%8>0)
		iDataLen = iDataLen+1;

	if (iCpbLen%8 > (8-iStartb))
		iDataLen += 1;


	ucTemp = new BYTE [iDataLen+1];
	ZeroMemory(ucTemp, iDataLen+1);

	bRet   = __RightShift(ucTemp,ucSou,iStartb,iDataLen,&iResLen);

	ucDes[iStartB] |=ucTemp[0];

	memcpy(ucDes+iStartB+1,ucTemp+1,iResLen-1);

	return TRUE;

}

BOOL __RightShift(BYTE *ucOutPut,BYTE *ucInPut,int iShiftBit,int iInPutLen,int* iOutPutLen)
{

	int iCyc;
	for (iCyc = 0;iCyc < iInPutLen ;iCyc++)
	{

		ucOutPut[iCyc]   |=  ucInPut[iCyc]  >> iShiftBit;
		ucOutPut[iCyc+1] = (ucInPut[iCyc] << (0x8-iShiftBit))&0xFF;
	}

	if (iShiftBit!= 0)
		*iOutPutLen = iInPutLen+1;
	else
		*iOutPutLen = iInPutLen;



	return TRUE;
}

//************************************
// Method:    _ConvertBCD
// FullName:  _ConvertBCD
// Access:    public 
// Returns:   BOOL             TRUE                             ;  FALSE 
// Qualifier:
// Parameter: BYTE cInput     '0' - '9', '*', '#', 'a', 'b', 'c';  other
// Parameter: BYTE * cOutput  '0' - '9', '10','11','12','13','14'; ''
//************************************
BOOL _ConvertBCD_B(BYTE cInput,BYTE* cOutput)
{
	BOOL bRet = TRUE;
	*cOutput  = 0;

	if ((cInput < '0')||(cInput>'9'))
	{
		switch(cInput)
		{
		case '*': *cOutput='a';  break; 
		case '#': *cOutput='b';  break; 
		case 'a': *cOutput='c';  break; 
		case 'b': *cOutput='d';  break; 
		case 'c': *cOutput='e';  break; 
		default : bRet = FALSE;  break;
		}
	}
	else
		*cOutput = cInput;

	return bRet;
}

BOOL _ConvertBCD(CString csInput,CString& csOutput)
{
	BYTE cInput,cOutput;
	UINT uiLen;

	csOutput.Empty();
	uiLen = csInput.GetLength();

	csOutput = csInput;

	for (UINT i = 0 ; i < uiLen;i++)
	{
		cInput = csInput.GetAt(i);

		if(_ConvertBCD_B(cInput,&cOutput))
		{
			csOutput.SetAt(i,cOutput);
		}
		else
			return FALSE;

	}

	return TRUE;
}

BOOL _ConvertAscii(CString csInput,CString& csOutput)
{

	int iLen;
	CString csTemp;

	csOutput.Empty();
	if ((csInput.IsEmpty()))
		return FALSE;


	iLen = csInput.GetLength();


	BYTE *ucData = new BYTE[iLen];

	for (int i= 0 ; i < iLen ;i++)
		ucData[i] = (BYTE)csInput.GetAt(i);

	csInput.Empty();
	for (int i = 0;i< iLen;i++)
	{
		csTemp.Format(_T("%02X"),ucData[i]);
		csOutput += csTemp;
	}

	delete ucData;
	return TRUE;

}

BOOL _ConvertUcs2(CString csInput,CString& csOutput)
{
	BOOL bRet = TRUE;
	int iLen,iOutLen;
	BYTE *ucInput;
	BYTE *ucOutput;
	iLen = csInput.GetLength();
	iOutLen = 2*iLen;
	csOutput.Empty();



	ucInput  = new BYTE[iLen];
	ucOutput = new BYTE[iOutLen];
	ZeroMemory(ucInput,iLen);
	ZeroMemory(ucOutput,iOutLen);
	for (int i= 0 ; i < iLen ;i++)
		ucInput[i] = (BYTE)csInput.GetAt(i);
	csOutput.Empty();
	
	if (GBK2UCS(ucInput,iLen,ucOutput,&iOutLen))
		_UcHex2CString(ucOutput,iOutLen,csOutput);
	else
		bRet =  FALSE;

	delete ucInput;
	delete ucOutput;

	return bRet;
}


//************************************
// Method:    __Convert7bit
// FullName:  __Convert7bit 8bit 2 7bit
// Access:    public 
// Returns:   BOOL TURE or FALSE
// Qualifier:
// Parameter: BYTE * ucInput  {0x68,0x75,0x79,0x75.0x6E}
// Parameter: int iInputLen   5
// Parameter: BYTE * ucOutput {0xE8,0x7A,0xBE,0xEE,0x06}
// Parameter: int * iOutput   5
// if ucOutput == NULL; 获取 iOutput 的数据;
// if ucOutput != NULL;*iOutput>= 将要获取的长度,否则 会返回失败
//************************************
BOOL __Convert7bit(BYTE* ucInput,int iInputLen,BYTE *ucOutput,int *iOutput)
{

	int i7bitLen = iInputLen/8 *7 + (iInputLen%8);

	if (ucOutput!= NULL)
	{
		if (*iOutput < i7bitLen)
			return FALSE;	
	}
	else
	{
		*iOutput = i7bitLen;
		return TRUE;
	}


	for (int i = 0 ; i < i7bitLen ;i++)
	{

		ucOutput[i] = (ucInput[i/7*8 + i%7] >> i%7);

		if (i != ( *iOutput-1))
			ucOutput[i] += (ucInput[i/7*8 + i%7 +1 ] << (7-i%7))&0xFF;

	}

	return TRUE;

}

BOOL _Convert7bit(CString csInput,CString& csOutput)
{
	int iLen     = csInput.GetLength();
	int i7bitLen = 0;
	BYTE* ucInput;
	BYTE* ucOutput;
	csOutput.Empty();
	ucInput = new BYTE[iLen/2];

	iLen = _CString2UcHex(csInput,ucInput);

	if (!__Convert7bit(ucInput,iLen,NULL,&i7bitLen))
		return FALSE;

	ucOutput = new BYTE[i7bitLen];

	ZeroMemory(ucOutput,i7bitLen);

	if (!__Convert7bit(ucInput,iLen,ucOutput,&i7bitLen))
		return FALSE;

	_UcHex2CString(ucOutput,i7bitLen,csOutput);

	delete ucInput;
	delete ucOutput;
	return TRUE;

}

BOOL _Couvert7bit(CString csInput,CString& csOutput)
{
	CString csTemp;
	csOutput.Empty();
	if (!_ConvertAscii(csInput,csTemp))
	{
		csOutput.Empty();
		return FALSE;
	}


	if (!_Convert7bit(csTemp,csOutput))
	{
		csOutput.Empty();
		return FALSE;
	}

	return TRUE;
}

//************************************
// Method:    __Translate7bit
// FullName:  __Translate7bit
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: BYTE * ucInput {0xE8,0x7A,0xBE,0xEE,0x06}
// Parameter: int iInputLen   5
// Parameter: BYTE * ucOutput {0x68,0x75,0x79,0x75.0x6E}
// Parameter: int * iOutput   5
// if ucOutput == NULL; 获取 iOutput 的数据;
// if ucOutput != NULL;*iOutput>= 将要获取的长度,否则 会返回失败
//************************************
BOOL __Translate7bit(BYTE* ucInput,int iInputLen,BYTE *ucOutput,int *iOutput)
{
	int i8bitLen = (iInputLen/0x7)*0x8 + iInputLen%0x07;
	if (ucOutput!= NULL)
	{
		if (*iOutput < i8bitLen)
			return FALSE;	
	}
	else
	{
		*iOutput = i8bitLen;
		return TRUE;
	}

	for (int i = 0 ; i < i8bitLen; i++)
	{
		if ((i%8) == 0)
			ucOutput[i] = ucInput[i/8 *7] &0x7F;
		else
			ucOutput[i] = ((ucInput[i - i/8] <<(i%8))+ (ucInput[i - i/8 -1]>>(0x8-(i%8))))&0x7F;
	}

	return TRUE;
}

BOOL _Translate7bit(CString csInput,CString& csOutput)
{
	int iLen     = csInput.GetLength();
	int i8bitLen = 0;
	BYTE* ucInput;
	BYTE* ucOutput;
	csOutput.Empty();

	ucInput = new BYTE[iLen/2];

	iLen = _CString2UcHex(csInput,ucInput);

	if (!__Translate7bit(ucInput,iLen,NULL,&i8bitLen))
		return FALSE;

	ucOutput = new BYTE[i8bitLen];

	ZeroMemory(ucOutput,i8bitLen);

	if (!__Translate7bit(ucInput,iLen,ucOutput,&i8bitLen))
		return FALSE;

	_UcHex2CString(ucOutput,i8bitLen,csOutput);

	delete ucInput;
	delete ucOutput;
	return TRUE;

}


BOOL _TranslateAscii(CString csInput,CString& csOutput)
{
	int iCyc,iRet;

	iRet = csInput.GetLength();
	csOutput.Empty();
	BYTE *ucInput = new BYTE [iRet]; 
	iRet = _CString2UcHex(csInput,ucInput);
	for (iCyc = 0 ; iCyc < iRet ; iCyc++)
		csOutput += (TCHAR)ucInput[iCyc];
	delete ucInput;
	return TRUE;
}

BOOL _TranslateUcs2(CString csInput,CString& csOutput)
{
	int iCyc;
	int iLen;
	int iRet;

	iLen = csInput.GetLength();

	csOutput.Empty();

	BYTE *ucInput  = new BYTE [iLen]; 
	BYTE *ucOutput = new BYTE [iLen]; 

	iLen = _CString2UcHex(csInput,ucInput);

	if (UCS2GBK(ucInput,iLen,ucOutput,&iRet))
	{
		for (iCyc = 0 ; iCyc < iRet ; iCyc++)
			csOutput += (TCHAR)ucOutput[iCyc];
	}

	delete ucInput;
	delete ucOutput;

	return TRUE;
}


BOOL _TranslateBCD(CString csData,CString& csOutput)
{
	CString csTemp;
	int iTemp;

	int iLen;
	iLen = csData.GetLength();
	csOutput.Empty();
	for (int i=0 ; i <iLen; i++ )
	{
		csTemp = csData.Mid(i,1);
		iTemp  = _CString2Int(csTemp);

		switch(iTemp)
		{
		case 10:csOutput += _T("*");break;
		case 11:csOutput += _T("#");break;
		case 12:csOutput += _T("a");break;
		case 13:csOutput += _T("b");break;
		case 14:csOutput += _T("c");break;
		case 15:csOutput += _T("");break;
		default:csOutput+=csTemp;break;
		}
	}

	return TRUE;
}


BOOL _AppendSign(CString& csData,CString csSign,int iNumber,BOOL bInEnd)
{
	CString csTemp;
	int iLen = csData.GetLength();
	iNumber = iNumber*2;

	//if ((csSign.IsEmpty())||((iLen%2)!= 0))
	//	return FALSE;
	if (csSign.IsEmpty())
			return FALSE;

	csTemp.Empty();

	for (int i = 0; i < iLen ; i += iNumber)
	{
		csTemp += csData.Mid(i,iNumber);
		csTemp += csSign;
	}

	if (!bInEnd)
		csData = csTemp.Left(csTemp.GetLength() - csSign.GetLength());

	return TRUE;

}


BOOL _AppendSpace(CString& csData)
{
	return _AppendSign(csData,_T(" "));
}



BOOL _AppendEnter(CString& csData)
{
	return _AppendSign(csData,_T("\r"),16);
}


BOOL _WipeEmpty(CString& csData)
{
	int iLen= csData.GetLength();
	if ((iLen%2)!=0)
		return FALSE;

	for (int i = iLen ; i >= 0 ; i-=2)
	{
		if( _CString2Int(csData.Mid(i-2,2)) ==  0xFF) 
		{
			csData = csData.Left(i);
		}
		else
			break;
	}
	return TRUE;
}


void _ExchangeAt(CString& csData)
{

	int iLen;
	BYTE xcTemp;
	

	iLen = csData.GetLength();

	if ((iLen%2)!=0)
	{
		csData = csData+_T("F");
		iLen  += 1;
	}


	for (int i = 0 ; i< iLen ; i+=2)
	{


		xcTemp = csData.GetAt(i);
		csData.SetAt(i  ,csData.GetAt(i+1));
		csData.SetAt(i+1, xcTemp);

	}

}

//************************************
// Method:    _ExchangeByte
// FullName:  _ExchangeByte
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: CString & csData
//************************************
void _ExchangeByte(CString& csData)
{

	CString csTemp;
	int iLen;

	iLen = csData.GetLength();
	csTemp.Empty();

	for (int i = 0 ; i < iLen ; i+=2)
	{
		csTemp += csData.Mid(iLen - 2 - i  ,2);
	}

	csData = csTemp;

}


void _DeleteEnterSpace( CString& csInput )
{
	csInput.Replace(_T("\n"),_T(""));
	csInput.Replace(_T("\r"),_T(""));
	csInput.Replace(_T(" "),_T(""));
	csInput.Replace(_T("	"),_T(""));
}
void _DeleteNote( CString& csInput )
{
	int iNoteStart,iLineEnd;



	while(csInput.Find(_T("//"))>=0)
	{
		iNoteStart = csInput.Find(_T("//"));

		iLineEnd = csInput.Find(_T("\n"),iNoteStart);
		if (iLineEnd < 0)
			iLineEnd = csInput.Find(_T("\r"),iNoteStart);

		if (iLineEnd<0)
			iLineEnd = csInput.GetLength();
		
		csInput = csInput.Left(iNoteStart)+csInput.Mid(iLineEnd);

	}

}


BOOL __GetTLVData_Ext(CString csInput,int iTag,CString& csOutput)
{
	BOOL bRet = TRUE;
	CString csPreTag,csLen;

	int iOff,iInput,iLen,iPreTag;

	iInput = csInput.GetLength();


	for(iOff = 0 ; iOff < iInput;iOff+=(iLen*2+4))
	{
		iPreTag  =  _CString2Int(csInput.Mid(iOff,2)) ;

		csLen    = csInput.Mid(iOff+2,2);

		iLen     = _CString2Int(csLen);

		if ((iOff + 4 + iLen) > iInput)
		{
			csOutput.Empty();
			bRet = FALSE;
			break; 
		}

		if (iPreTag == iTag)
		{
			csOutput = csInput.Mid(iOff+4,iLen*2);
			break;
		}

	}

	return bRet;
}

BOOL _GetTLVData(CString csInput, int iTag,CString& csOutput)
{
	BOOL bRet = FALSE;
	int iCurTag,iCurLen;
	int iDataLen;
	int iOffset;



	iDataLen = csInput.GetLength();
	iOffset   = 0;


	do 
	{
		iCurTag = _CString2Int(csInput.Mid(iOffset,02));

		iCurLen = _CString2Int(csInput.Mid(iOffset+02,02));

		if (iCurLen==0x81)
		{
			iOffset += 2;
			__GetTLVData_Ext(csInput.Mid(iOffset,iDataLen-iOffset),iCurLen,csOutput);
		}
		else
			 __GetTLVData_Ext(csInput.Mid(iOffset,iDataLen-iOffset),iCurTag,csOutput);

		if (iCurTag == iTag)
		{
			bRet = TRUE;
			break;
		}
		else 
			iOffset += (csOutput.GetLength() + 4);

		csOutput.Empty();

	} while (iOffset < iDataLen);


	return bRet;

}

BOOL __GetTLVData(CString csInput,int iTag ,int iNum,CString& csOutput)
{
	BOOL bRet = FALSE;
	int iCurTag,iCurLen;
	int iDataLen;
	int iOffset;
	int iTime;

	iDataLen = csInput.GetLength();
	iOffset   = 0;
	iTime     = 0;


	do 
	{
		iCurTag = _CString2Int(csInput.Mid(iOffset,02));

		iCurLen = _CString2Int(csInput.Mid(iOffset+02,02));

		if (iCurLen==0x81)
		{
			iOffset += 2;
			 __GetTLVData_Ext(csInput.Mid(iOffset,iDataLen-iOffset),iCurLen,csOutput);
		}
		else
			 __GetTLVData_Ext(csInput.Mid(iOffset,iDataLen-iOffset),iCurTag,csOutput);


		if (iCurTag == iTag)
		{
			iTime += 1;
			if (iTime  == iNum)
			{
				 bRet = TRUE;
				break;
			}
		}

		iOffset += (csOutput.GetLength() + 4);

		csOutput.Empty() ;


	} while (iOffset < iDataLen);

	return bRet;

}

BOOL _Translate81Ucs2(CString csInput , CString& csOutput)
{
	int iStart;
	int iLen;
	int iTemp;
	CString csTemp;
	CString csResult;

	iLen = csInput.GetLength()/2 -1;

	iStart = _CString2Int(csInput.Mid(00,02))*0x80; 

	csResult.Empty();

	for (int i = 0 ; i < iLen ; i ++)
	{
		iTemp = _CString2Int(csInput.Mid((i+1)*2,2));

		if (iTemp&0x80)
		{
			csTemp.Format(_T("%04x"),iStart+ (iTemp&0x7F));

			if (_TranslateUcs2(csTemp,csResult))
				csOutput += csResult;
			

			
		}
		else
		{
			csTemp.Format(_T("%02x"),iTemp);
			if (_TranslateAscii(csTemp,csResult))
				csOutput += csResult;
		}
	}

	return TRUE;
}

BOOL _Translate82Ucs2(CString csInput , CString& csOutput)
{
	int iStart;
	int iLen;
	int iTemp;
	CString csTemp;
	CString csResult;

	iLen = csInput.GetLength()/2 -2;

	iStart = _CString2Int(csInput.Mid(00,04)); 

	csResult.Empty();

	for (int i = 0 ; i < iLen ; i ++)
	{
		iTemp = _CString2Int(csInput.Mid((i+2)*2,2));

		if (iTemp&0x80)
		{
			csTemp.Format(_T("%04x"),iStart+ (iTemp&0x7F));
			if (_TranslateUcs2(csTemp,csResult))
				csOutput += csResult;
		}
		else
		{
			csTemp.Format(_T("%02x"),iTemp);
			if (_TranslateAscii(csTemp,csResult))
				csOutput += csResult;
		}
	}

	return TRUE;
}


BOOL __TranslateUcs2(CString csInput , CString& csOutput,int iCoding)
{

	BOOL bRet;

	switch(iCoding)
	{
	case 0x80:
		bRet = _TranslateUcs2(csInput,csOutput);
		break;
	case 0x81:
		bRet = _Translate81Ucs2(csInput,csOutput);
		break;
	case 0x82:
		bRet = _Translate82Ucs2(csInput,csOutput);
		break;
	default:
		bRet = _TranslateUcs2(csInput,csOutput);
		break;
	}
	return bRet;

}


void GeneratePPS(int iProtocol,int iPTS,unsigned char *ucPPS)
{
	ucPPS[0] = 0xFF;
	ucPPS[1] = 0x10+iProtocol;
	ucPPS[2] = iPTS;
	ucPPS[3] =ucPPS[0]^ucPPS[1]^ucPPS[2];

}


BOOL _CreateDirectory(CString csDir)
{
	CString strSubPath;
	CString strInfo;
	int nCount = 0; 
	int nIndex = 0;

	//查找字符"\\"的个数
	do
	{
		nIndex = csDir.Find(_T("\\"),nIndex) + 1;
		nCount++;
	}while( (nIndex-1) != -1);
	nIndex = 0;
	//检查，并创建目录
	while( (nCount-1) >= 0)
	{
		nIndex = csDir.Find(_T("\\"),nIndex) + 1;
		if( (nIndex - 1) == -1)
		{
			strSubPath = csDir;
		}
		else
			strSubPath = csDir.Left(nIndex);
		if(::CreateDirectory(strSubPath,NULL) == ERROR_PATH_NOT_FOUND)
		{
			//			 if(!::CreateDirectory(strSubPath,NULL))
			return FALSE;
		}
		nCount--;
	};
	return TRUE;


}

int DelayTime(double dTimes)
{
	LARGE_INTEGER   litmp;
	LONGLONG   QPstart,QPend;
	DOUBLE   dfMinus,dfFreq,dfTim;


	QueryPerformanceFrequency(&litmp);
	dfFreq = (DOUBLE)litmp.QuadPart;
	QueryPerformanceCounter(&litmp);
	QPstart = litmp.QuadPart;

	do 
	{
		QueryPerformanceCounter(&litmp);
		QPend = litmp.QuadPart;
		dfMinus = (double)(QPend - QPstart); 
		dfTim = dfMinus/dfFreq;
	} while (dfTim > dTimes);

	return 1;
}

void GetSysDate(CString& csSysData)
{
	SYSTEMTIME sSysTime;
	CString csTemp;
	GetLocalTime(&sSysTime);

	csSysData.Format(_T("%04d"),sSysTime.wYear);
	csTemp.Format(_T("%02d"),sSysTime.wMonth);
	csSysData +=csTemp;
	csTemp.Format(_T("%02d"),sSysTime.wDay);
	csSysData +=csTemp;


}

void GetSysTime(CString &csSysTime)
{
	SYSTEMTIME sSysTime;
	CString csTemp;
	GetLocalTime(&sSysTime);

	csSysTime.Format(_T("%02d"),sSysTime.wHour);
	csTemp.Format(_T("%02d"),sSysTime.wMinute);
	csSysTime +=csTemp;
	csTemp.Format(_T("%02d"),sSysTime.wSecond);
	csSysTime +=csTemp;

}

BOOL GetLocalIP(CString& csIP)   //获取IP地址
{
	char szHostName[128];   
	
	ZeroMemory(szHostName,128);


	WSADATA wsaData;  
	if ( WSAStartup( MAKEWORD(2,0), &wsaData ) != 0 )   
		return FALSE;

	if(   gethostname(szHostName,   128)   ==   0   )   
	{   
		//  结构
		struct   hostent   *   pHost;   
		pHost   =   gethostbyname(szHostName);
		//只取主网卡 ip
		BYTE   *p; 
		p   =(BYTE   *)pHost->h_addr;     
		csIP.Format(_T("%d.%d.%d.%d"),  p[0], p[1],p[2], p[3]);  
	}   
	return  TRUE; 
} 


void GenerateChallenge(int iLen , CString& csChallenge)   
{
	CString csTemp;
	srand( (unsigned)time( NULL ) );
	csChallenge.Empty();

	for (int i = 0 ; i < iLen ; i++)
	{
		_Int2CString(rand(),csTemp,1);
		csChallenge += csTemp;
	}

}

int _GenerateChallenge()
{
	srand( (unsigned)time( NULL ) );
	return rand();
}

BOOL _IsAllAscii(CString csInput)
{
	int iLen;

	iLen = csInput.GetLength();
	for (int i = 0; i <iLen ; i++)
	{
		if (*(csInput.Mid(i,1)) < 0)
			return FALSE;
	}

	return TRUE;
}

BOOL _IsAllHex(CString csInput)
{
	int iLen;
	int iTemp;

	iLen = csInput.GetLength();
	for (int i = 0; i <iLen ; i++)
	{
		iTemp = *(csInput.Mid(i,1));
		if ((iTemp < 0x30)
			|| ((iTemp>0x39)&&(iTemp<0x41)) 
			|| ((iTemp>0x46)&&(iTemp<0x61))
			|| (iTemp>0x66))
			return FALSE;


	}

	return TRUE;
}


void _RepeatCString(CString csData, int iTimes,CString& csOutput)
{
	csOutput.Empty();

	for(int iCyc = 0 ; iCyc < iTimes ; iCyc ++ )
		csOutput += csData;
}


//Tag 01 - 2F, 00 为结束符
BOOL _GetTVData(CString csData, int iTag,CString& csOutput)
{
	CString csResult;
	int iLenbit,iTemp;
	int iStart,iEnd;

	iStart = 0;
	iEnd   = 0;
	csResult .Empty();
	iLenbit = csData.GetLength()*4;

	for (int i = 0 ; i < iLenbit; i += 8)
	{
		iTemp = _Getbit_E_I(csData,i,8);
		if ((iTemp < 0x2F)&&(iTemp>0))
		{

			if ((iStart == 0)&&(iTemp == iTag))
				iStart = i+8;
			else if((iStart > 0)&&((i - iStart)<16))
			{
				iEnd = i;
				break;
			}

		}
		else if (iTemp == 0)
		{
			if (iStart>0)
			{
				iEnd = i;
				break;
			}
		}
	}

	if ((iStart > 0)&& (iEnd == 0 ))
		iEnd = iLenbit;

	
	return _Getbit_E_C(csData,iStart,iEnd-iStart,csOutput);
}



void _GenerateTLVData(CString csData,int iTag,CString& csOutput)
{
	int iLen;
	CString csLen;
	CString csTag;
	iLen = csData.GetLength()/2;
	csTag.Format(_T("%02X"),iTag);
	if (iLen<0x80)
	{
		csLen.Format(_T("%02X"),iLen);
	}
	else if(iLen<0x100)
	{
		csLen.Format(_T("%02X"),iLen);
		csLen = _T("81")+csLen;

	}else if(iLen<0x10000)
	{
		csLen.Format(_T("%04X"),iLen);
		csLen = _T("82")+csLen;
	}
	csOutput = csTag+csLen+csData;
}



//int _GetCSVDataSum(CString csInput)
//{
//	int iRet,iSum,iLen,iStart;
//
//	iStart = 0;
//	iSum   = 0;
//	if (!csInput.IsEmpty())
//	{
//		iLen = csInput.GetLength();
//		do 
//		{
//			iRet    = csInput.Find(_T(","),iStart);
//
//			iStart = iRet + 1;
//			if ((iRet>0)&&(iRet != iLen))
//				iSum += 1;
//		} while (iRet>1);
//	}
//
//
//
//	return iSum;
//
//}
//
//int _GetCSVData(CString csInput,int iNum,CString&csOutput)
//{
//
//	int iRet,iStart,iCurrent,iLen;
//
//	csOutput.Empty();
//
//	iCurrent = 0;
//	iStart   = 0 ;
//
//	if (!csInput.IsEmpty())
//	{
//		iLen = csInput.GetLength();
//		do 
//		{
//			iRet = csInput.Find(_T(","),iStart);
//			iCurrent += 1;
//			if (iCurrent == iNum)
//			{
//				if (iRet>0)
//					csOutput = csInput.Mid(iStart,iRet-iStart);
//				else
//					csOutput = csInput.Mid(iStart,iLen-iStart);
//
//			}
//
//			iStart    = iRet+1;
//		} while (iRet>1);
//
//	}
//
//	if (iCurrent < iNum)
//		return -1;
//
////	_DeleteEnterSpace(csOutput);
//
//	return csOutput.GetLength();
//
//}

int _GetCSVDataSum(CString csInput)
{
	int iRet,iSum,iLen,iStart,uiSignLen;


	iStart = 0;
	iSum   = 0;
	if (!csInput.IsEmpty())
	{
		iLen = csInput.GetLength();
		do 
		{
			//iRet    = csInput.Find(_T(","),iStart);

			if ((csInput.Mid(iStart,1) == _T("\""))&&
				(csInput.Find(_T("\","),iStart)>0))
			{
				iRet   = csInput.Find(_T("\","),iStart);
				uiSignLen = 2;
			}
			else
			{
				iRet   = csInput.Find(_T(","),iStart);
				uiSignLen = 1;
			}

			iStart = iRet + uiSignLen;
			if ((iRet>0)&&(iRet != iLen))
				iSum += 1;
		} while (iRet>1);
	}

	return iSum;

}

int _GetCSVData(CString csInput,int iNum,CString&csOutput)
{

	int iOffset,iStart,iCurrent,iLen;
//	UINT uiSignLen;
	csOutput.Empty();

	iCurrent = 0;
	iStart   = 0 ;

	if (!csInput.IsEmpty())
	{
		iLen = csInput.GetLength();
		do 
		{

			if ((csInput.Mid(iStart,1) == _T("\""))&&
				(csInput.Find(_T("\","),iStart)>0))
			{
				iOffset   = csInput.Find(_T("\","),iStart);
				iOffset += 1;
			}
			else
			{
				iOffset   = csInput.Find(_T(","),iStart);
				//uiSignLen = 1;
			}

			iCurrent += 1;
			if (iCurrent == iNum)
			{
				if (iOffset>=0)
					csOutput = csInput.Mid(iStart,iOffset-iStart);
				else
					csOutput = csInput.Mid(iStart,iLen-iStart);

				iOffset = 0;
			}
			else
				iStart    = iOffset+1;

		} while (iOffset>1);

	}

	if (iCurrent < iNum)
		return -1;

	//	_DeleteEnterSpace(csOutput);
	CString csSigntt = _T("\"\"\"");

	if ((csOutput.Left(03) == csSigntt)&&
		(csOutput.Right(03) == csSigntt)&&
		(csOutput.GetLength()>6))
		csOutput = csOutput.Mid(3,csOutput.GetLength()-6);

	return csOutput.GetLength();

}


int _GetCStringDataSum(CString csData)
{

	int iRet,iSum,iLen,iStart;

	iStart = 0;
	iSum  = 0;
	if (!csData.IsEmpty())
	{
		iLen = csData.GetLength();
		do 
		{
			iRet    = csData.Find(_T(";"),iStart);

			iStart = iRet + 1;
			if ((iRet>0)&&(iRet != iLen))
				iSum += 1;
		} while (iRet>1);
	}
	return iSum;

}

int _GetCStringData(CString csData,int iNum,CString&csOutput)
{

	int iRet,iStart,iCurrent,iLen;

	csOutput.Empty();

	iCurrent = 0;
	iStart   = 0 ;

	if (!csData.IsEmpty())
	{
		iLen = csData.GetLength();
		do 
		{
			iRet = csData.Find(_T(";"),iStart);
			iCurrent += 1;
			if (iCurrent == iNum)
			{
				if (iRet>0)
					csOutput = csData.Mid(iStart,iRet-iStart);
				else
					csOutput = csData.Mid(iStart,iLen-iStart);

			}

			iStart    = iRet+1;
		} while (iRet>1);

	}
		
	_DeleteEnterSpace(csOutput);

	return csOutput.GetLength();

}

BOOL _RecogniseFileData(CString csInput,CString  *csName,CString *csData,int *iDataSum)
{

	int iNameLen;
	int iValueOff,iValueLen;
	iValueOff = 0;
	iValueLen = 0;

	_DeleteEnterSpace(csInput);


	iNameLen = csInput.Find(_T(":"));
	*csName  = csInput.Left(iNameLen);

	if ((csName->Left(1)!=_T("["))||(csName->Right(1)!=_T("]")))
		return FALSE;

	*csName = csName->Mid(1,csName->GetLength()-2);

	*csData = csInput.Right(csInput.GetLength()-iNameLen-1);

	if (csData->Right(1)!=_T(";"))
		return FALSE;

	*iDataSum = _GetCStringDataSum(*csData);

	return TRUE;
}




int _GetCurrentNode(CString csXML,CString *csStart,CString *csEnd,CString *csMid,CString *csRemind)
{
	int iOffset1,iEnd1,iOffset2,iEnd2;
	CString csName;
	int iTemp;

	CString csTemp;

	iOffset1  = csXML.Find(_T("<"));

	if (iOffset1 < 0)
	{
		if (csRemind!= NULL)
			csRemind->Empty();

		return -10;
	}

	if (iOffset1!=0)
	{
		if (csRemind!= NULL)
			*csRemind = csXML.Mid(iOffset1,csXML.GetLength()-iOffset1);
		return 2;
	}

	iEnd1     = csXML.Find(_T(">"))+1;

	*csStart  = csXML.Mid(iOffset1,iEnd1-iOffset1);

	iTemp = csStart->Find(_T("/>"));

	if (iTemp>0)
	{
		if (csRemind!= NULL)
			*csRemind = csXML.Right(csXML.GetLength() - iEnd1);

		return 1;
	}



	iTemp = csStart->Find(_T(" "));

	if (iTemp>0)
	{
		csName = csStart->Mid(1,iTemp-1);
	}
	else
	{
		csName = csStart->Mid(1,csStart->GetLength()-2);
	}


	csTemp = _T("</")+csName+_T(">");

	iOffset2  = csXML.Find(csTemp);

	if (iOffset2<0)
	{
		if (csRemind!= NULL)
			*csRemind = csXML.Right(csXML.GetLength()-iEnd1);

		return -1;
	}


	iEnd2     = iOffset2+csTemp.GetLength();

	*csMid    = csXML.Mid(iEnd1,iOffset2-iEnd1);

	*csEnd    = csTemp;

	if (csRemind!= NULL)
		*csRemind = csXML.Right(csXML.GetLength()-iEnd2);

	return 0;

}

int _GetXMLFirstNode(CString csXML,CString *csNodeName,CString *csNodeData,CString *csRemind,CString *csExtData)
{

	int iRet,iTemp;

	CString csStart, csEnd, csMid,csTemp;



	do 
	{

		iRet =_GetCurrentNode(csXML,&csStart, &csEnd, &csMid, &csTemp);
		csXML = csTemp;
		if (csRemind!=NULL)
			*csRemind = csTemp;



	} while ((iRet != 1)&&(iRet!= 0)&&(!csXML.IsEmpty()));



	switch(iRet)
	{
	case 00:

		csStart     = csStart.Mid(1,csStart.GetLength()-2);
		csEnd       = csEnd.Mid(2,csEnd.GetLength()-3);

		*csNodeName = csStart.Left(csEnd.GetLength());
		if (csExtData != NULL)
			*csExtData  = csStart.Right(csStart.GetLength() - csEnd.GetLength());
		if (*csNodeName!=csEnd)
		{
			return -10;
		}

		*csNodeData = csMid;

		break;
	case 01:

		csStart     = csStart.Mid(1,csStart.GetLength()-3);
		iTemp       = csStart.Find(_T(" "));
		*csNodeName = csStart.Mid(0,iTemp);
		if (csExtData != NULL)
			*csExtData  = csStart.Right(csStart.GetLength() - iTemp);

		csNodeData  ->Empty();

		break;
	default:
		iRet = -1;
		break;
	}



	return iRet;

}

int GetXMLExtData(CString csExt,CString *csParaName,CString *csParaData,int iNum)
{

	int iTemp,iTemp1,iTemp2;
	int iOffset;

	csParaName->Empty();
	csParaData->Empty();

	iOffset = 0;

	for (iTemp = 0 ; iTemp < iNum ; iTemp++)
	{
		iOffset = csExt.Find(_T(" "),iOffset);

		if (iOffset<0)
		{
			return -1;
		}
		iOffset += 1;
	}

	iTemp1 = csExt.Find(_T("\""),iOffset);
	*csParaName = csExt.Mid(iOffset,iTemp1-iOffset);

	iTemp2 = csExt.Find(_T("\""),iTemp1+2);

	*csParaData = csExt.Mid(iTemp1+2,iTemp2-iTemp1-2);

	return 0;
}

BOOL _FindNodeCurrnent(CString csXML,CString csName,CString csParaName,CString csParaData,CString & csOutput)
{

	CString csNodeName,csNodeData,csExt, csRemind;

	CString csExPName,csExPData;
	int iRet,iTemp;
	csOutput.Empty();

	do 
	{
		iRet = _GetXMLFirstNode(csXML,&csNodeName,&csNodeData,&csRemind,&csExt);

		if (iRet < 0)
		{
			csOutput.Empty();
		}
		if(csNodeName == csName)
		{
			iTemp = 1;
			do 
			{

				iRet = GetXMLExtData(csExt,&csExPName,&csExPData,iTemp);

				if (csExPName == csParaName)
				{
					if (csParaData == csExPData)
					{
						csOutput =  csNodeData;
						return TRUE;
					}
				}

				iTemp+=1;

			} while (iRet>=0);

		}

		csXML = csRemind;

	} while (!csXML.IsEmpty());

	return FALSE;




}

BOOL _FindFistNodeCurrnent(CString csXML,CString csName,CString*csOutput,CString *csRemind)
{
	CString csNodeName,csNodeData,csExt,csNodeRemind;
	CString csResult;


	int iRet;

	do 
	{
		iRet = _GetXMLFirstNode(csXML,&csNodeName,&csNodeData,&csNodeRemind,&csExt);

		if (iRet < 0)
		{
			csOutput->Empty();
		}
		if(csNodeName == csName)
		{
			*csOutput = csNodeData;
			if (csRemind!=NULL)
				*csRemind = csNodeRemind;
			return TRUE;
		}

		csXML = csNodeRemind;

	} while (!csXML.IsEmpty());

	csOutput->Empty();

	return FALSE;

}




void _FormatCString(CString csInput,int iLen,CString& csOutput)
{

	int iCurLen = csInput.GetLength();

	if (iCurLen >iLen)
		csOutput = csInput.Right(iLen);
	else
	{
		_RepeatCString(_T("F"),iLen-iCurLen,csOutput);
		csOutput = csInput+ csOutput;
	}
}


BOOL __GetCurrentDIR(CString& csPath)
{
	GetModuleFileName(NULL,csPath.GetBuffer(1000),1000);
	csPath.ReleaseBuffer();
	csPath = csPath.Left((int) csPath.ReverseFind( '\\'));

	if (csPath.IsEmpty())
		return FALSE;
	else
		return TRUE;

}


int _GetExistNumber(CString csData, CString csCode)
{
	int iStart  = 0;
	int iNumber = 0 ;
	int iOffset = 0 ;

	do 
	{
		iOffset = csData.Find(csCode,iStart);

		if (iOffset>0 )
			iNumber++;

		iStart = (iOffset+1);

	} while (iOffset > 0);

	return iNumber;
	
}