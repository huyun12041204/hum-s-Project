// ParameterConvert.h : ParameterConvert DLL 的主头文件
//
#include "../../BasicConvert/BasicConvert/BasicConvert.h"
#include "Des.h"
#define ParameterConvert_API extern   "C"   _declspec(dllexport) 
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号

#define  _DEF_Card  0
#define  _DEF_GSM   1
#define  _DEF_CDMA  2
#define  _DEF_DCS          0x8
#define  _DEF_DFIS41       0x9
#define  _DEF_FPCTS        0xA
#define  _DEF_TIAEIA136    0xB
#define  _DEF_TIAEIA95     0x2

#define  _DEF_Tele  0x40
#define  _DEF_USIM  0x10
#define  _DEF_CSIM  0x20
#define  _DEF_ETSI  0x80
#define  _DEF_3GPP  0x10
#define  _DEF_3GPP2 0x20

//#define _DEF_PHONEBOOK       0x11

#define _DEF_PHONEBOOK_LOCA  0x11
#define _DEF_GSMACCESS       0x12
#define _DEF_MExE            0x13
#define _DEF_SoLSA           0x14
#define _DEF_WLAN            0x15
#define _DEF_HNB             0x16
#define _DEF_ProSe           0x17
#define _DEF_ACDC            0x18
#define _DEF_TV              0x19
#define	_DEF_BCAST           0x1A

#define _DEF_GRAPHICS          0x41
#define _DEF_PHONEBOOK_GLOBAL  0x42
#define _DEF_MULTIMEDIA        0x43
#define _DEF_MMSS              0x44
#define _DEF_MCPTT             0x45
#define _DEF_V2X               0x46

//#define _DEF_GSMACCESS     0x11
//#define _DEF_MExE      0x12
//#define _DEF_WLAN      0x13
//#define _DEF_HNB       0x14
//#define _DEF_SoLSA     0x15
//#define	 _DEF_BCAST     0x16




//#define  _DEF_MMSS      0x21 
//
//
//#define _DEF_MMSS       0x41
//#define _DEF_MULTIMEDIA 0x42
#define _DEF_PHONEBOOK  0xF1

// CParameterConvertApp
// 有关此类实现的信息，请参阅 ParameterConvert.cpp
//

class CParameterConvertApp : public CWinApp
{
public:
	CParameterConvertApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
ParameterConvert_API BOOL _TranslateTONNPI(CString csInput,CString&csOutput);
//************************************
// Method:    _TranslateSubNumber
// FullName:  _TranslateSubNumber
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: CString csInput    "0891683110102105F0"
// Parameter: CString & csOutput "+8613010112500"
//Length of BCD number/SSC contents
//TON and NPI
//Dialling Number/SSC String
//************************************
ParameterConvert_API BOOL _TranslateSubNumber(CString csInput,CString& csOutput);
//************************************
// Method:    _ConvertSubNumber
// FullName:  _ConvertSubNumber
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: CString csInput    "+8613010112500"
// Parameter: CString & csOutput "0891683110102105F0"
//************************************
ParameterConvert_API BOOL _ConvertSubNumber(CString csInput,CString&csOutput);

//************************************
// Method:    _TranslateAddress
// FullName:  _TranslateAddress
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: CString csInput    "0D91683110102105F0"
// Parameter: CString & csOutput "+8613010112500"
//************************************
ParameterConvert_API BOOL _TranslateAddress(CString csInput,CString& csOutput);

//************************************
// Method:    _ConvertAddress
// FullName:  _ConvertAddress
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: CString csInput    "+8613010112500"
// Parameter: CString & csOutput "0D91683110102105F0"
//************************************
ParameterConvert_API BOOL _ConvertAddress(CString csInput,CString& csOutput);


//特殊函数
ParameterConvert_API void GenerateExpandedFormatSecurityDescriptor(CString* csData,CString* csDescriptor);

ParameterConvert_API void _GetACFromARR( int iCommand,CString csARR,CString &csOutput,int* Other, bool bIsIns = false );


 ParameterConvert_API void _TransationMNCMCC(CString csMNCMCC,CString&csOutput);

 ParameterConvert_API int _OpenCSVFile(CString csPath,CStdioFile* CSFFile);
 ParameterConvert_API BOOL _GenerateMCCMNCDescription(CString csMCCMNC,CString& csOutput);
 
 ParameterConvert_API BOOL CalculateOddEvenIndication( CString csData );
 ParameterConvert_API BOOL _ConvertMIPUPP(CString csMIPUPP,int iSum,CString& csOutput);
 ParameterConvert_API void _RightShift(CString csData, int iShiftBit,CString& csOutput);
 ParameterConvert_API int _GetMarkNumber(CString csData,CString csMark);
 ParameterConvert_API BOOL _GetDatasInMark(CString csData,CString csMark,int iNumber,CString &csOutput);

 ParameterConvert_API  int _RecogniseMNCLen(int iMCC,int iMNC2Byte);

 ParameterConvert_API void _TranslateAlphaIdentifier(CString csData,CString& csOutput);
 ParameterConvert_API void _ConvertSMSP(CString csAlpID,CString csTPDesAdd
	 ,CString csTSSCA,CString csTPPId,CString csTPDCS,CString csTPVP,CString &csSMSP);
 ParameterConvert_API void _ConvertSMSP(CString csAlpID,CString csTPDesAdd,CString csTSSCA,CString csTPPId,CString csTPDCS,CString csTPVP,CString &csSMSP);
 ParameterConvert_API void _ConvertSMSP28(CString csData,CString &csSMSP);
 ParameterConvert_API void _ConvertSMSP29(CString csData,CString &csSMSP);
 ParameterConvert_API void _Genrate80ADN(CString csAlpha,int iAlphaLen,CString csNumber,CString& csOutput);
 ParameterConvert_API BOOL _TranslatePNN(CString csData,CString &csOutput);
 ParameterConvert_API BOOL _TranslateFileStructure(int iStructure,CString& csText);


 //ParameterConvert_API bool GenerateADFName(CString csAID,CString& csName);
 //ParameterConvert_API bool GenerateDFName(int iFID,int iPreFID,CString& csName);
 //ParameterConvert_API bool GenerateEFNameInMF(int iFID,CString &csName,bool bAb = true);
 //ParameterConvert_API bool GenerateEFNameInTelecom(int iFID,CString &csName,bool bAb = true);
 //ParameterConvert_API bool GenerateEFNameIn3GPP(int iFID,CString &csName,bool bAb = true);
 //ParameterConvert_API bool GenerateEFNameIn3GPP2(int iFID,CString &csName,bool bAb = true);
 //ParameterConvert_API bool GenerateEFNameInGSM(int iFID,CString &csName,bool bAb = true);
 //ParameterConvert_API bool GenerateEFNameInCDMA(int iFID,CString &csName,bool bAb = true);
 //ParameterConvert_API bool GenerateEFNameInPhoneBook(int iFID,CString &csName,bool bAb = true);
 //ParameterConvert_API bool GenerateEFNameInMultiMedia(int iFID,CString &csName,bool bAb = true);
 //ParameterConvert_API bool GenerateEFNameInMMSS(int iFID,CString &csName,bool bAb= true);
 //ParameterConvert_API bool GenerateEFNameInGSMAccess(int iFID,CString &csName,bool bAb= true);
 //ParameterConvert_API bool GenerateEFNameInMExE(int iFID,CString &csName,bool bAb= true);
 //ParameterConvert_API bool GenerateEFNameInWLAN(int iFID,CString &csName,bool bAb= true);
 //ParameterConvert_API bool GenerateEFNameInHNB(int iFID,CString &csName,bool bAb= true);
 //ParameterConvert_API bool GenerateEFNameInSoLSA(int iFID,CString &csName,bool bAb= true);
 //ParameterConvert_API bool GenerateEFNameInBCAST(int iFID,CString &csName,bool bAb= true);
 //ParameterConvert_API bool GenerateEFNameInGRAPHICS(int iFID,CString &csName,bool bAb= true);

 //ParameterConvert_API int Try2GetFileMark(CString csPath,int iPMark = _DEF_Card);
 //ParameterConvert_API bool Try2GenerateFileName(int iMark,int iFID,CString& csName,bool bAb = true);
 
 ParameterConvert_API BOOL _Triple_Des_Encrypt(CString csKey,CString csData,CString&csOutput,int iMod);
 ParameterConvert_API BOOL _Triple_Des_Decrypt(CString csKey,CString csData,CString&csOutput,int iMod = CBC);


 //************************************
 // Method:    GetDFMark
 // FullName:  GetDFMark
 // Access:    public 
 // Returns:   BOOL
 // Qualifier:
 // Parameter: CString csPath
 // Parameter: int iParentMark
 // Parameter: int *iMark
 //************************************
 ParameterConvert_API BOOL GetDFMark(CString csPath,int iParentMark,int* iMark);
 //************************************
 // Method:    GetADFMark
 // FullName:  GetADFMark
 // Access:    public 
 // Returns:   BOOL
 // Qualifier:
 // Parameter: CString csAID 
 // Parameter: int     *iMark
 //************************************
 ParameterConvert_API BOOL GetADFMark(CString csAID,int* iMark);

 ParameterConvert_API BOOL GetDFName(int iMark,CString& csName);
 //************************************
 // Method:    GetFileNameFromReference
 // FullName:  GetFileNameFromReference
 // Access:    public 
 // Returns:   ParameterConvert_API BOOL
 // Qualifier:
 // Parameter: int iFID         FID，或者AID缩写
 // Parameter: int iParentMark  夫DFMark,
 // Parameter: CString & csName 文件名字
 // Parameter: bool bIsAbbr     是否为简称
 //************************************
 ParameterConvert_API BOOL GetFileNameFromReference(int iFID,int iParentMark,CString&csName,bool bIsAbbr = false);