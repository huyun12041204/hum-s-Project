#include "ParameterConvert/ParameterConvert/ParameterConvert.h"



//
//int _GetMarkNumber(CString csData,CString csMark);
//CString _GetDatasInMark(CString csData,CString csMark,int iNumber);



int _ShiftNumber_P(int iNumber,int idigit);


CString _TransationMCC_P(CString csMCC_P);
CString _TransationM_11_12(CString csM_11_12_P);
CString _TransationM_S1(CString csM_S1_P);

CString IMSI_M2IMSI(CString csIMSIM);
//CString Imsim2Imsi(CString csIMSIM);
//CString Imsi2Imsim(CString csIMSI);
CString ConvertICCID(CString csICCID);
CString ConvertPIN(CString csPIN);
CString ConvertUIMID(CString csUIMID);
CString ConvertIMSI(CString csIMSI);
CString ConvertLASC(CString csUPP);
CString ConvertACC(CString csData);



CString TranslateAlphaIdentifier(CString csData);

CString TransationSMSStatus(int iStatus);
CString TransationData(CString csData, int iDCS);
CString TransationMTI(int iMTI);
CString TransationMMS(int iMMS);
CString TransationSRI(int iSRI);
CString TransationUDHI(int iUDHI);
CString TransationRP(int iRP);
CString TransationDate(CString csDate);
CString TransationTime(CString csTime);

CString TransationSCA(CString csData);

CString TransationAlpha(CString csAlpha);

CString TransationRAUStatus(CString csData);
CString TransationLOCIStatus(int iData);
CString TransationSSTStatus(bool bit1,bool bit2);
//CString TransationSupportedText(bool bbit);

CString TransationUEMode(CString csData);


 CString TransationLanguageIndicator_TSB58(int iLI);

 CString _TransationApplication(CString csApp);

 CString _TransationAuthenticationMechanism(int iAuMe);










 //  input 460 01  , out 64F010
 CString ConvertMCCMNC(CString csMCC,CString csMNC);




 
 //************************************
 // Method:    TransationMobileIdentity
 // FullName:  TransationMobileIdentity
 // Access:    public 
 // Returns:   CString  "No Identity" ..
 // Qualifier: 
 // Parameter: int iIDType  0     ..
 //************************************
 CString TransationMobileIdentity(int iIDType);
 //************************************
 // Method:    TransationOddEvenIndicationText
 // FullName:  TransationOddEvenIndicationText
 // Access:    public 
 // Returns:   CString "odd number of identity digits" or "even number of identity digits"
 // Qualifier:
 // Parameter: BOOL bInput
 //************************************
 CString TransationOddEvenIndicationText(BOOL bInput);


 //************************************
 // Method:    CalculateOddEvenIndication
 // FullName:  CalculateOddEvenIndication
 // Access:    public 
 // Returns:   BOOL           FALSE   TRUE  FALSE
 // Qualifier:
 // Parameter: CString csData 01      00     03
 //************************************

  //************************************
 // Method:    TransationSMSNotFlagText
 // FullName:  TransationSMSNotFlagText
 // Access:    public 
 // Returns:   CString
 // Qualifier:
 // Parameter: BOOL bInput
 //SMS "Memory Cap. Exceeded" Not. Flag 
 //************************************
 CString TransationSMSNotFlagText(BOOL bInput);

 //************************************
 // Method:    TransationEXTType
 // FullName:  TransationEXTType
 // Access:    public 
 // Returns:   CString
 // Parameter: int iInput
 //************************************
 CString TransationEXTType(int iInput);

 void GenerateExpandedFormatSecurityDescriptor(CString* csData,CString* csDescriptor);






 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//


 CString RepeatCString(CString csData, int iTimes);

 CString DeleteEnterSpace( CString csInput);
 CString WipeEmpty( CString csData );
 bool Getbit(CString csData,int ibit);
 int Getbit(CString csData,int iStartbit ,int ibitLen);
 bool Getbit_E(CString csData,int ibit);
 CString Getbit_C(CString csData,int iStartbit ,int ibitLen );
 bool Setbit(CString& csData,int ibit,bool ibbit);
 CString ExchangeAt(CString csInput);
 CString ExchangeByte(CString csInput);
 //************************************
 // Method:    Int2CString
 // FullName:  Int2CString
 // Access:    public 
 // Returns:   CString
 // Qualifier:
 // Parameter: int iInput
 // Parameter: int iLength CString的长度
 //************************************
 CString Int2CString(int iInput,int iLength = 0);
 CString Int2CStringDecimal(int iInput);

 CString GetTLVData(CString csInput, int iTag);
 CString GetTLVData(CString csInput, int iTag,int iNum);

 CString Translate7bit(CString csInput);
 CString Convert7bit(CString csInput);

 CString TranslateAscii(CString csInput);
 CString ConvertAscii(CString csInput);

 CString TranslateUcs2(CString csInput);
 CString ConvertUcs2(CString csInput);

 CString _TranslateBCD(CString csData);

 //输入  0891683110102105F0   输出+8613010112500 
 CString _TransationADNNumber(CString csData);

 //输入 +8613010112500 输出0891683110102105F0
 CString _ConvertADNNumber(CString csData);

 //输入  0781018016F1  输出1008611 
 CString _TransationAddress(CString csData);
 //输入1008611    输出 0781018016F1
 CString _ConvertAddress(CString csData);

 CString TransationUcs2(CString csData,int iCoding);

 CString TransationMNCMCC(CString csMNCMCC);

 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 //****************************************************************************//
 CString TransationSupportedText(bool bbit);

 CString GetACFromARR( int iCommand,CString csARR,int* Other,bool bIsIns = false );

  CString GenerateMCCMNCDescription(CString csMCCMNC);

  CString RightShift(CString csData, int iShiftBit);

  CString TranslatePNN(CString csData);


   //************************************
 // Method:    FormatCString
 // FullName:  FormatCString
 // Access:    public 
 // Returns:   CString         "34"     "1234FF"    
 // Qualifier:
 // Parameter: CString csInput "1234"   "1234" 
 // Parameter: int iLen          02       06
 //************************************
  CString FormatCString(CString csInput,int iLen);

  CString GenerateTLVData(CString csData,int iTag);

  CString _variant_t2CString(_variant_t varInput);
  int _variant_t2Int(_variant_t varInput);



  //************************************
  // Method:    __variant_t2CString
  // FullName:  __variant_t2CString
  // Access:    public 
  // Returns:   int
  // Qualifier: 只有格式正确的时候才能有返回 TRUE； 否则都为 FALSE
  // Parameter: _variant_t varInput
  // Parameter: CString & csOutput
  //************************************
  int __variant_t2CString(_variant_t varInput,CString& csOutput,UINT uiSize = 0);
  int __variant_t2int(_variant_t varInput,int* iOutput);
  int __variant_t2BOOL(_variant_t varInput,BOOL* bOutput);
  _variant_t CString2_variant_t(int iType,CString csInput);
  _variant_t Int2_variant_t(int iType,int iInput);
  UINT uLong2Byte(ULONG32 ulData,BYTE*Byte,UINT uiByteLen = 4);