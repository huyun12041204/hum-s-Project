// BasicConvert.h : BasicConvert DLL 的主头文件
//
#define BasicConvert_API extern   "C"   _declspec(dllexport) 
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CBasicConvertApp
// 有关此类实现的信息，请参阅 BasicConvert.cpp
//

class CBasicConvertApp : public CWinApp
{
public:
	CBasicConvertApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};



BasicConvert_API BOOL _IsValid(CString csInput);

BasicConvert_API int  _CString2UcHex(CString csInput,BYTE* ucOutput);
BasicConvert_API int  _CString2Int(CString csInput);
BasicConvert_API int  _CString2IntDecimal(CString csInput);

BasicConvert_API void _UcHex2CString(BYTE* ucInput,int iInputLen,CString& csOutput);
BasicConvert_API void _Int2CString(int iInput,CString&csOutput,int iLength);
BasicConvert_API void _Int2CStringDecimal(int iInput,CString&csOutput);
//************************************
// Method:    _Getbit
// FullName:  _Getbit
// Access:    public 
// Returns:   BasicConvert_API BOOL
// Qualifier: BIT8	BIT7	BIT6	BIT5	BIT4	BIT3	BIT2	BIT1
// Parameter: CString csData
// Parameter: int ibit
//************************************
BasicConvert_API BOOL _Getbit(CString csData,int ibit);

//************************************
// Method:    _Getbit_E
// FullName:  _Getbit_E
// Access:    public 
// Returns:   BasicConvert_API BOOL
// Qualifier: BIT1	BIT2	BIT3	BIT4	BIT5	BIT6	BIT7	BIT8
// Parameter: CString csData
// Parameter: int ibit
//************************************
BasicConvert_API BOOL _Getbit_E(CString csData,int ibit);
BasicConvert_API int  _Getbit_E_I(CString csData,int iStartbit ,int ibitLen);
BasicConvert_API BOOL _Getbit_E_C(CString csInput,int iStartbit ,int ibitLen,CString &csOutput);

BasicConvert_API BOOL _Setbit(CString& csData,int ibit,bool bbit);

BasicConvert_API BOOL __Copy2bit(BYTE *ucDes,BYTE *ucSou,int iCpbLen,int iStartB,int iStartb);
BasicConvert_API BOOL __RightShift(BYTE *ucOutPut,BYTE *ucInPut,int iShiftBit,int iInPutLen,int* iOutPutLen);

BasicConvert_API BOOL _ConvertBCD_B(BYTE cInput,BYTE* cOutput);
BasicConvert_API BOOL _ConvertBCD(CString csInput,CString& csOutput);
BasicConvert_API BOOL _ConvertAscii(CString csInput,CString& csOutput);
BasicConvert_API BOOL _ConvertUcs2(CString csInput,CString& csOutput);

//************************************
// Method:    _Couvert7bit
// FullName:  _Couvert7bit
// Access:    public 
// Returns:   BasicConvert_API BOOL
// Qualifier:
// Parameter: CString csInput    "huyun"
// Parameter: CString &csOutput "E87ABEEE06"
//************************************
BasicConvert_API BOOL _Couvert7bit(CString csInput,CString& csOutput);

//************************************
// Method:    _Couvert7bit
// FullName:  _Couvert7bit
// Access:    public 
// Returns:   BasicConvert_API BOOL
// Qualifier:
// Parameter: CString csInput    "E87ABEEE06" 
// Parameter: CString &csOutput  "huyun"
//************************************
BasicConvert_API BOOL _Translate7bit(CString csInput,CString& csOutput);

BasicConvert_API BOOL _TranslateAscii(CString csInput,CString& csOutput);



BasicConvert_API BOOL _TranslateUcs2(CString csInput,CString& csOutput);

BasicConvert_API BOOL _TranslateBCD(CString csData,CString& csOutput);


//************************************
// Method:    _AppendSign
// FullName:  _AppendSign
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: CString & csData "110011"
// Parameter: CString csSign   " "
// Parameter: int iNumber      1 
// Parameter: BOOL bInEnd      FALSE
// Result                      "11 00 11"
// Return                      TRUE
// Remark                      bInEnd = TRUE,csData "11 00 11 "
// if Length of csData is odd ; return FALSE;
// if csSign is empty         ; return FALSE;
//************************************
BasicConvert_API BOOL _AppendSign(CString& csData,CString csSign,int iNumber = 1,BOOL bInEnd = FALSE);




//************************************
// Method:    _AppendSpace
// FullName:  _AppendSpace
// Access:    public 
// Returns:   BasicConvert_API BOOL
// Qualifier:
// Parameter: CString & csData "110011"
// Result                       "11 00 11"
// Return see _AppendSign
//************************************
BasicConvert_API BOOL _AppendSpace(CString& csData);

//************************************
// Method:    _AppendEnter
// FullName:  _AppendEnter
// Access:    public 
// Returns:   BasicConvert_API BOOL
// Qualifier:
// Parameter: CString & csData "0000000000000000000000000000000000000000000000000000000000000000"
// Result     "00000000000000000000000000000000\r00000000000000000000000000000000"
// Return see _AppendSign
//************************************
BasicConvert_API BOOL _AppendEnter(CString& csData);

//************************************
// Method:    _WipeEmpty
// FullName:  _WipeEmpty
// Access:    public 
// Returns:   BasicConvert_API BOOL
// Qualifier:
// Parameter: CString & csData "00FF00FFFFF"
// Result                      "00FF00"
//************************************
BasicConvert_API BOOL _WipeEmpty(CString& csData);
//************************************
// Method:    _ExchangeAt
// FullName:  _ExchangeAt
// Access:    public 
// Returns:   BasicConvert_API void 
// Qualifier:
// Parameter: CString & csData "12345678"
// Result                      "21436587"
//************************************
BasicConvert_API void _ExchangeAt(CString& csData);

//************************************
// Method:    _ExchangeByte
// FullName:  _ExchangeByte
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: CString & csData "12345678"
// Result                      "34127856"
//************************************
BasicConvert_API void _ExchangeByte(CString& csData);


BasicConvert_API BOOL _GetTLVData(CString csInput, int iTag,CString& csOutput);


BasicConvert_API BOOL __GetTLVData(CString csInput,int iTag ,int iNum,CString& csOutput);



//************************************
// Method:    DeleteEnterSpace
// FullName:  DeleteEnterSpace
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: CString csCSTR1 
//************************************
BasicConvert_API void _DeleteEnterSpace( CString& csInput);

//************************************
// Method:    __TranslateUcs2
// FullName:  __TranslateUcs2
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: CString csInput
// Parameter: CString & csOutput
// Parameter: int iCoding
//************************************
BasicConvert_API BOOL __TranslateUcs2(CString csInput , CString& csOutput,int iCoding);



BasicConvert_API void GeneratePPS(int iProtocol,int iPTS,unsigned char *ucPPS);
BasicConvert_API int DelayTime(double dTimes);
BasicConvert_API void GetSysDate(CString& csSysData);
BasicConvert_API void GetSysTime(CString &csSysTime);
BasicConvert_API BOOL GetLocalIP(CString& csIP) ;  
BasicConvert_API void GenerateChallenge(int iLen , CString&csChallenge);   
BasicConvert_API BOOL _IsAllAscii(CString csInput);
BasicConvert_API BOOL _IsAllHex(CString csInput);
BasicConvert_API BOOL _GetTVData(CString csData, int iTag,CString& csOutput);
BasicConvert_API BOOL _CreateDirectory(CString csDir);
BasicConvert_API void _RepeatCString(CString csData, int iTimes,CString& csOutput);
BasicConvert_API void _GenerateTLVData(CString csData,int iTag,CString& csOutput);
BasicConvert_API int _GetCSVDataSum(CString csInput);
BasicConvert_API int _GetCSVData(CString csInput,int iNum,CString&csOutput);
BasicConvert_API int _GetCStringDataSum(CString csData);
BasicConvert_API int _GetCStringData(CString csData,int iNum,CString&csOutput);
BasicConvert_API BOOL _RecogniseFileData(CString csInput,CString *csName,CString *csData,int *iDataSum);
BasicConvert_API int _GetCurrentNode(CString csXML,CString *csStart,CString *csEnd,CString *csMid,CString *csRemind);
BasicConvert_API int _GetXMLFirstNode(CString csXML,CString *csNodeName,CString *csNodeData,CString *csRemind,CString *csExtData);
BasicConvert_API int GetXMLExtData(CString csExt,CString *csParaName,CString *csParaData,int iNum);
BasicConvert_API BOOL _FindNodeCurrnent(CString csXML,CString csName,CString csParaName,CString csParaData,CString & csOutput);
BasicConvert_API BOOL _FindFistNodeCurrnent(CString csXML,CString csName,CString*csOutput,CString *csRemind);
BasicConvert_API void _FormatCString(CString csInput,int iLen,CString& csOutput);
BasicConvert_API BOOL __GetCurrentDIR(CString& csPath);
BasicConvert_API int _GetExistNumber(CString csData, CString csCode);
BasicConvert_API int _GenerateChallenge();
BasicConvert_API void _DeleteNote( CString& csInput );