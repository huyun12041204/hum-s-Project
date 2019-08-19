// SH_DLL.cpp : Defines the entry point for the DLL application.
//
#include <stdio.h>
#include "stdafx.h"
#include <math.h>
#include "Basconv.h"
#include "Basusc2.h"
#include "Winsock2.h"
#include "Iptypes.h"
#include "Iphlpapi.h"



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
CString GenerateTLVData(CString csData,int iTag)
{

	CString csTemp;

	_GenerateTLVData( csData,iTag, csTemp);

	return csTemp;

}
CString RepeatCString( CString csData, int iTimes )
{
	CString csTemp;

	_RepeatCString(csData,iTimes,csTemp);

	return csTemp;

}
CString DeleteEnterSpace( CString csInput)
{
	CString csTemp = csInput;
	_DeleteEnterSpace(csTemp);
	return csTemp;
}

//基础CString的函数

CString WipeEmpty( CString csData )
{
	CString csTemp = csData;
	if (!_WipeEmpty(csTemp))
		csTemp.Empty();
	return csTemp;
}


//Hight bit First
// "01" 
//ibit = 1 , return true
//ibit = 8 , return false
bool Getbit(CString csData,int ibit)
{
	if (_Getbit(csData,ibit) == TRUE)return true;
	else return false;
}

//Low bit First
// "01" 
//ibit = 8 , return true
//ibit = 1 , return false 
bool Getbit_E(CString csData,int ibit)
{
	if (_Getbit_E(csData,ibit)== TRUE)return true;
	else return false;
}

//Low bit First
int  Getbit(CString csData,int iStartbit ,int ibitLen)
{
	return _Getbit_E_I(csData,iStartbit,ibitLen);

}
CString Getbit_C(CString csData,int iStartbit ,int ibitLen )
{
	CString csRet;
	if (!_Getbit_E_C(csData,iStartbit,ibitLen,csRet))
		csRet.Empty();
	return csRet;
}

// 0000, 1 ,true, 0100;  0000 , 2 , true, 0200 ; 
// 0000 ,9 ,true, 0001;

bool Setbit(CString& csData,int ibit,bool ibbit)
{
	if (_Setbit(csData,ibit,ibbit))
		return true;
	else
		return false;

}


CString ExchangeAt(CString csInput)
{
	CString csData;
	csData = csInput;
	_ExchangeAt(csData);
	return csData;
}

CString ExchangeByte(CString csInput)
{
	CString csData;
	csData = csInput;
	_ExchangeByte(csData);
	return csData;
}



CString GetTLVData(CString csInput, int iTag)
{
	CString csOutput;
	if (!_GetTLVData(csInput,iTag,csOutput))csOutput.Empty();
	return csOutput;
}
CString GetTLVData(CString csInput, int iTag,int iNum)
{
	CString csOutput;
	if (!__GetTLVData(csInput,iTag,iNum,csOutput))csOutput.Empty();
	return csOutput;
}


CString Int2CString(int iInput,int iLength )
{
	CString csRet;
	_Int2CString(iInput,csRet,iLength);
	return csRet;
}

CString Int2CStringDecimal(int iInput)
{
	CString csRet;
	_Int2CStringDecimal(iInput,csRet);
	return csRet;

}

CString Convert7bit(CString csInput)
{
	CString csTemp;

	if (!_Couvert7bit(csInput,csTemp))
		csTemp.Empty();
	return csTemp;
}
CString Translate7bit(CString csInput)
{
	CString csOutput;
	if (!_Translate7bit(csInput,csOutput)) csOutput.Empty();
	return csOutput;
}


CString ConvertAscii(CString csInput)
{

	CString csTemp;

	if (!_ConvertAscii(csInput,csTemp))
		csTemp.Empty();
	return csTemp;
}
CString TranslateAscii(CString csInput)
{
	CString csOutput;
	if (!_TranslateAscii(csInput,csOutput)) csOutput.Empty();
	return csOutput;
}




CString ConvertUcs2(CString csInput)
{
	CString csTemp;

	if (!_ConvertUcs2(csInput,csTemp))
		csTemp.Empty();
	return csTemp;

}

CString TranslateUcs2(CString csInput)
{
	CString csTemp;

	if (!_TranslateUcs2(csInput,csTemp))
		csTemp.Empty();
	return csTemp;
	
}

CString _TranslateBCD(CString csData)
{

	CString csTemp;

	if (!_TranslateBCD(csData,csTemp))
		csTemp.Empty();
	return csTemp;
}





CString _TransationADNNumber(CString csData)
{
	CString csResult;

	if (!_TranslateSubNumber(csData,csResult))
		csResult.Empty();
	return csResult;
}

CString _ConvertADNNumber(CString csData)
{
	CString csResult;
	if (!_ConvertSubNumber(csData,csResult))
		csResult.Empty();
	return csResult;


}

CString _TransationAddress(CString csData)
{

	CString csResult;
	if (!_TranslateAddress(csData,csResult))
		csResult.Empty();

	return csResult;}

CString _ConvertAddress(CString csData)
{

	CString csResult;
	if (!_ConvertAddress(csData,csResult))
		csResult.Empty();

	return csResult;

}

CString TransationUcs2(CString csData,int iCoding)
{
	CString csTemp;
	if (!__TranslateUcs2(csData, csTemp,iCoding))
		csTemp.Empty();
	return csTemp;
}

CString TransationMNCMCC(CString csMNCMCC)
{

	CString csTemp;
	_TransationMNCMCC(csMNCMCC,csTemp);
	return csTemp;

}

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

CString GetACFromARR( int iCommand,CString csARR,int* Other,bool bIsIns)
{
	CString csOutput;

	csOutput.Empty();

	_GetACFromARR(iCommand,csARR, csOutput,Other,bIsIns);

	return csOutput;

}

CString TransationSupportedText(bool bbit)
{
	CString csResult;

	if (bbit)
		csResult = _T("Supported");
	else
		csResult = _T("Unsupported");
	return csResult;
}



















int _ShiftNumber_P(int iNumber,int idigit)
{

	int *iNum;

	iNum = new int[idigit];

	for (int i = 0 ; i < idigit ; i++)
	{
		if ((iNumber %10) == 9)
			iNum[idigit-1-i] = 0;
		else
			iNum[idigit-1-i] = (iNumber %10)+1;

		iNumber = iNumber/10;
	}

	iNumber = 0;

	for (int i = 0 ; i<idigit ; i++)
		iNumber = iNumber*10+ iNum[i];


	return iNumber;

}

//通用M_S2
CString _TransationMCC_P(CString csMCC_P)
{
	CString csMCC;
	int iMCC;
	iMCC = _CString2Int(csMCC_P.Mid(0,2))+ (_CString2Int(csMCC_P.Mid(2,2))&0x3) *0x100;

	iMCC = _ShiftNumber_P(iMCC,3);

	csMCC.Format(_T("%03d"),iMCC);

	return csMCC;
}

CString _TransationM_11_12(CString csM_11_12_P)
{
	CString csM_11_12;
	int iM_11_12;
	iM_11_12 = (_CString2Int(csM_11_12_P)&0x7F);

	iM_11_12 = _ShiftNumber_P(iM_11_12,2);

	csM_11_12.Format(_T("%02d"),iM_11_12);

	return csM_11_12;
}

CString _TransationM_S1(CString csM_S1_P)
{
	CString csM_S1_1,csM_S1_2,csM_S1_3;
	int iM_S1;

	iM_S1  = _CString2Int(csM_S1_P.Mid(0,2))+ _CString2Int(csM_S1_P.Mid(2,2)) *0x100+ _CString2Int(csM_S1_P.Mid(4,2)) *0x10000;

	csM_S1_1. Format(_T("%03d"),_ShiftNumber_P(iM_S1/0x4000,3));
	csM_S1_2. Format(_T("%d"),(iM_S1%0x4000)/0x400);
	csM_S1_3. Format(_T("%03d"),_ShiftNumber_P( iM_S1%0x400 ,3));

	return csM_S1_1+csM_S1_2+csM_S1_3;

}



CString IMSI_M2IMSI(CString csIMSIM)
{
	return _TransationMCC_P (csIMSIM.Mid(16,4)) +  _TransationM_11_12(csIMSIM.Mid(12,2)) + _TransationMCC_P(csIMSIM.Mid(02,4))+ _TransationM_S1( csIMSIM.Mid(6,6));
}




CString ConvertICCID(CString csICCID)
{
	CString csResult;
	int i;
	csResult.Empty();
	if (csICCID.GetLength()!=20)
	{
		return csResult;
	}

	for ( i=0;i<20;i+=2)
	{
		csResult += csICCID.Mid(i+1,1);
		csResult += csICCID.Mid(i,1);

	}
	return csResult;

}

CString ConvertPIN(CString csPIN)
{
	int iPinlen,iPadlen;
	CString csPading,csResult,csTemp;
	csPading = "FFFFFFFF";

	iPinlen = csPIN.GetLength();
	if (iPinlen<4)
	{
		return csPading+csPading;
	}
	iPadlen = (8-iPinlen);

	for (int i = 0; i<iPinlen; i++)
	{
		csTemp    = _T("3")+csPIN.Mid(i,1);
		csResult +=csTemp;
	}

	return csResult+csPading.Right(iPadlen*2);
}

CString ConvertUIMID(CString csUIMID)
{
	int iLen;
	CString csResult,csTemp;
	csResult.Empty();
	iLen = csUIMID.GetLength()/2;
	if (iLen != 4)
	{
		return csResult;
	}
	csResult.Format(_T("%02X"),iLen);

	for (int i = 0 ;i < iLen ; i++)
	{
		csTemp    = csUIMID.Mid((3-i)*2,2);
		csResult += csTemp;
	}

	return csResult+_T("FFFFFF");

}

CString ConvertIMSI(CString csIMSI)
{
	CString csResult;
	csResult.Empty();
	int iLen;

	iLen = csIMSI.GetLength();

	if (iLen!= 15)
	{
		return csResult;
	}

	csIMSI = _T("809")+csIMSI;

	return ExchangeAt(csIMSI);
}

CString ConvertLASC(CString csData)
{

	CString csResult;

	csResult.Format(_T("%02X"),csData.GetLength());

	csResult += ConvertAscii( csData);

	return csResult;

}

CString ConvertACC(CString csData)
{

	int iACC;
	int iRet;
	iACC = 0x10000;
	iRet = 17-_ttoi(csData);
	iACC = iACC>>(16-_ttoi(csData));

	csData.Format(_T("%04X"),iACC);
	return csData;

}




//使用于 ADN的格式中
CString TranslateAlphaIdentifier(CString csData)
{
	CString csTemp;

	_TranslateAlphaIdentifier(csData,csTemp);

	return csTemp;
}

CString TransationSCA(CString csData)
{
	int iLen;
	CString csSCA;
	iLen = _CString2Int(csData.Mid(0,2))*2-2;

	csSCA.Format(_T("%02X"),iLen);

	csSCA = csSCA + csData.Mid(2,iLen + 2);

	return _TransationADNNumber(csSCA);
}

//使用于SMS的格式中
CString TransationSMSStatus(int iStatus)
{
	CString csDes;
	switch(iStatus)
	{
	case 00:
		csDes = _T("空闲单元(free space)");
		break;
	case 01:
		csDes = _T("MS从网络侧接收的消息；已读出的消息(message received by UE from network; message read)");
		break;
	case 03:
		csDes = _T("MS从网络侧接收的消息；要读出的消息(message received by UE from network; message to be read)");
		break;
	case 7:
		csDes = _T("MS发出的消息，消息将被发送(UE originating message; message to be sent)");
		break;
	case 5:
		csDes = _T("UE originating message; message sent to the network: Status report not requested");
		break;
	case 0xD:
		csDes = _T("UE originating message; message sent to the network: Status report requested but not (yet) received");
		break;
	case 0x15:
		csDes = _T("UE originating message; message sent to the network: Status report requested, received but not stored in EF-SMSR;");
		break;
	case 0x1D:
		csDes = _T("UE originating message; message sent to the network: Status report requested, received and stored in EF-SMSR;");
		break;
	default:
		csDes = _T("RFU (see TS 31.101 [11])");
		break;

	}

	return csDes;

}

CString TransationData(CString csData, int iDCS)
{
	CString csResult;
	switch(iDCS)
	{
	case 0x08:
		csResult = TranslateUcs2(csData);
		break;


	case 0x04:
		csResult = TranslateAscii(csData);
		break;

	case 0x00:
		csResult = Translate7bit(csData);
		break;

	default:
		break;
	}
	return csResult;
}

CString TransationMTI(int iMTI)
{
	CString csResult;
	switch(iMTI&0x3)
	{
	case 00:
		csResult = _T("SMS-DELIVER (in the direction SC to MS)");
		break;
	case 01:
		csResult = _T("SMS-SUBMIT-REPORT (in the direction SC to MS)");
		break;
	case 02:
		csResult = _T("SMS-STATUS-REPORT (in the direction SC to MS)");
		break; 
	case 03:
		csResult = _T("Reserved");
		break; 
	}
	return csResult;
}

CString TransationMMS(int iMMS)
{
	CString csResult;
	if (iMMS&0x1)
		csResult = _T("No more messages are waiting for the MS in this SC");
	else
		csResult = _T("More messages are waiting for the MS in this SC");

	return csResult;
}

CString TransationSRI(int iSRI)
{
	CString csResult;
	if (iSRI&0x1)
		csResult = _T("A status report will be returned to the SME");
	else
		csResult = _T("A status report will not be returned to the SME");

	return csResult;

}

CString TransationUDHI(int iUDHI)
{
	CString csResult;
	if (iUDHI&0x1)
		csResult = _T("The beginning of the TP-UD field contains a Header in addition to the short message");
	else
		csResult = _T("The TP-UD field contains only the short message");

	return csResult;

}

CString TransationRP(int iRP)
{
	CString csResult;
	if (iRP&0x1)
		csResult = _T("TP-Reply-Path parameter is set in this SMS-SUBMIT/DELIVER");
	else
		csResult = _T("TP-Reply-Path parameter is not set in this SMS-SUBMIT/DELIVER");

	return csResult;

}

CString TransationDate(CString csDate)
{
	CString csResult;
	csResult.Empty();
	if (csDate.GetLength()!= 6)
		return csResult;

	if (_CString2Int(csDate) == 0xFFFFFF)
		return csResult;

	
	csResult = ExchangeAt(csDate);

	if (_CString2Int(csResult.Mid(0,2))>= 0x70)
		csResult = _T("19")+csResult;
	else if (_CString2Int(csResult.Mid(0,2)) > 0xA0)
		csResult = _T("FF")+csResult;
	else
		csResult = _T("20")+csResult;

	return csResult.Mid(0,4)+_T("-")+csResult.Mid(4,2)+_T("-")+csResult.Mid(6,2);
}

CString TransationTime(CString csTime)
{
	CString csResult;
	csResult.Empty();
	if (csTime.GetLength()!= 6)
		return csResult;

	if (_CString2Int(csTime) == 0xFFFFFF)
		return csResult;

	csResult = ExchangeAt(csTime);


	return  csResult.Mid(0,2)+_T(":")+csResult.Mid(2,2)+_T(":")+csResult.Mid(4,2);
}

CString TransationAlpha(CString csAlpha)
{

	CString csDCS,csAlphaId;

	csDCS =csAlpha.Mid(0,2);

	csAlphaId = csAlpha.Mid(2,csAlpha.GetLength()-2);

	switch(_CString2Int(csDCS))
	{
	case 0x80:

		csAlphaId = TranslateUcs2(csAlphaId);
		break;
	case 0x04:
		csAlphaId = TranslateAscii(csAlphaId);
		break;
	default:
		csAlphaId = TranslateAscii(csAlpha);
		break;
	}

	return csAlphaId;
}

CString TransationRAUStatus(CString csData)
{
	CString csResult;
	switch(_CString2Int(csData))
	{
	case 00:
		csResult = _T("updated");
		break;
	case 1:
		csResult = _T("not updated");
		break;
	case 2:
		csResult = _T("PLMN not allowed");
		break;
	case 3:
		csResult = _T("Routing Area not allowed");
		break;
	default:
		csResult = _T("reserved");
		break;
	}
	return csResult;
}

CString TransationLOCIStatus(int iData)
{
	CString csResult;
	switch(iData)
	{
	case 00:
		csResult = _T("updated");
		break;
	case 1:
		csResult = _T("not updated");
		break;
	case 2:
		csResult = _T("PLMN not allowed");
		break;
	case 3:
		csResult = _T("Location Area not allowed");
		break;
	default:
		csResult = _T("reserved");
		break;
	}
	return csResult;
}
CString TransationUEMode(CString csData)
{
	CString csResult;

	switch(_CString2Int(csData))
	{
	case 00:
		csResult = _T("normal operation");
		break;
	case 01:
		csResult = _T("normal operation + specific facilities");
		break; 
	case 0x80:
		csResult = _T("type approval operations");
		break;
	case 0x81:
		csResult = _T("type approval operations + specific facilities");
		break; 
	case 0x02:
		csResult = _T("maintenance (off line)");
		break;
	case 0x04:
		csResult = _T("cell test operation");
		break;
	default:
		csResult = _T("RFU");
		break;
	}

	return csResult;
}


CString TransationSSTStatus(bool bit1,bool bit2)
{
	CString csResult;

	if (bit1)
		csResult = _T("Allocated");
	else
		csResult = _T("Not allocated");

	if (bit2)
		csResult += _T(" Activated");
	else
		csResult += _T(" Not activated");

	return csResult;
}









CString TransationLanguageIndicator_TSB58(int iLI)
{
	CString csResult;

	switch (iLI)
	{
	case 0: csResult = _T("Unknown or unspecified");break;
	case 1: csResult = _T("English");break;
	case 2: csResult = _T("French");break;
	case 3: csResult = _T("Spanish");break;
	case 4: csResult = _T("Japanese");break;
	case 5: csResult = _T("Korean");break;
	case 6: csResult = _T("Chinese");break;
	case 7: csResult = _T("Hebrew");break;
	}
	return csResult;
}

CString _TransationApplication(CString csApp)
 {
	 CString csDes;
	 csDes.Empty();
	 if (_Getbit(csApp.Right(02),1))
		 csDes+= _T("Unspecified (all applications use the same profile)");
	 if (_Getbit(csApp.Right(02),2))
		 csDes+= _T("Reserved");
	 if (_Getbit(csApp.Right(02),3))
		 csDes+= _T("WAP Browser");
	 if (_Getbit(csApp.Right(02),4))
		 csDes+= _T("Reserved for CDG");
	 if (_Getbit(csApp.Right(02),5))
		 csDes+= _T("Java");
	 if (_Getbit(csApp.Right(02),6))
		 csDes+= _T("Reserved for CDG");
	 if (_Getbit(csApp.Right(02),7))
		 csDes+= _T("Terminal (tethered mode for terminal access)");


	 return csDes;
 }

CString _TransationAuthenticationMechanism(int iAuMe)
{
	CString csDes;
	switch (iAuMe)
	{
	case 0x1: csDes = _T("CRAM-MD5 (RFC 2195)");break;
	case 0x2: csDes = _T("HTTP DIGEST (MD5) (RFC 2617)");break;
	case 0x4: csDes = _T("HTTP DIGEST (MD5-session) (RFC 2617)");break;
	case 0x8: csDes = _T("HTTP DIGEST (AKA v1-MD5) (RFC 3310)");break;
	case 0x10: csDes = _T("HTTP DIGEST (AKA v1-MD5-session) (RFC 3310)");break;
	case 0x20: csDes = _T("DIGEST-MD5 (SASL DIGEST) (RFC 2831)");break;
	case 0x40: csDes = _T("SASL OTP (RFC 2444)");break;	
	case 0x80: csDes = _T("SASL GSSAPI (RFC 2222)");break;
	default:   csDes = _T("Reserved");break; 
	}
	return csDes;
}







//************************************
// Method:    ConvertMCCMNC
// FullName:  ConvertMCCMNC
// Access:    public 
// Returns:   CString        64F000
// Qualifier:
// Parameter: CString csMCC   460 
// Parameter: CString csMNC   00
//************************************
CString ConvertMCCMNC(CString csMCC,CString csMNC)
{
	if (csMNC.GetLength() == 2)
		csMNC = _T("F")+csMNC;
	return ExchangeAt(csMCC+csMNC);

}



 

 CString TransationMobileIdentity(int iIDType)
 {
	 CString csDes;
	 switch (iIDType)
	 {
	 	case 00:
			csDes = _T("No Identity");
			break;
		case 01:
			csDes = _T("IMSI");
			break; 
		case 02:
			csDes = _T("IMEI");
			break;
		case 03:
			csDes = _T("IMEISV");
			break; 
		case 04:
			csDes = _T("TMSI/P-TMSI");
			break; 
		default:
			csDes = _T("reserved");
			break;
	 }
	 return csDes;
 }

 CString TransationOddEvenIndicationText(BOOL bInput)
 {
	 if (bInput)
		 return _T("odd number of identity digits");
	 else
		 return _T("even number of identity digits");

 }





 //************************************
 // Method:    TransationSMSNotFlagText
 // FullName:  TransationSMSNotFlagText
 // Access:    public 
 // Returns:   CString
 // Qualifier:
 // Parameter: BOOL bInput
 //SMS "Memory Cap. Exceeded" Not. Flag 
 //************************************
 CString TransationSMSNotFlagText(BOOL bInput)
 {
	 if (bInput)
		 return _T("means flag unset; memory capacity available");
	 else
		 return _T("means flag set");
 }

 CString TransationEXTType( int iInput )
 {
	 CString csDes;
	 switch(iInput)
	 {
	 case 00: csDes = _T("Free");break;
	 case 01: csDes = _T("Called Party Subaddress");break;
	 case 02: csDes = _T("Additional data");break;
	 default: csDes = _T("RFU");break;
	 }
	 return csDes;
 }

 CString GetTVData( CString csData, int iTag )
 {
	 CString csTemp;

	 if (!_GetTVData(csData,iTag,csTemp))
		 csTemp.Empty();

	 return csTemp;
 }


 CString RightShift(CString csData, int iShiftBit)
 {
	 CString csTemp;

	 _RightShift(csData,iShiftBit,csTemp);

	 return csTemp;
 }

 //Input 64F010 
 //output 
 CString GenerateMCCMNCDescription(CString csMCCMNC)
 {
	 CString csDes;
	 _GenerateMCCMNCDescription(csMCCMNC,csDes);
	 return csDes;
 }

 CString FormatCString(CString csInput,int iLen)
 {
	 CString csTemp;
	 _FormatCString(csInput,iLen,csTemp);
	 return csTemp;
 }


 CString TranslatePNN( CString csData )
 {
	 CString csTemp;
	 if (!_TranslatePNN(csData,csTemp))
		 csTemp.Empty();
	 return csTemp;
 }


 //************************************
 // Method:    _variant_t2CString
 // FullName:  _variant_t2CString
 // Access:    public 
 // Returns:   CString
 // Qualifier: 
 // Parameter: _variant_t varInput
 // Parameter: UINT uiSize 此处只有当vt = 8209时才会起作用
 // 此处为强制赋值,不会判断格式是否正确
 // __variant_t2CString 根据格式来判断,如果格式不正确,会返回 FALSE
 //************************************
 CString _variant_t2CString( _variant_t varInput )
 {
	 CString csResult;
	 if ((varInput.vt&VT_ARRAY) ==VT_ARRAY)
	 {

		 BYTE*buf;
		 SafeArrayAccessData(varInput.parray,(void**)&buf); 
		 SafeArrayUnaccessData(varInput.parray);
		 csResult = buf;
		 csResult.ReleaseBuffer(((varInput.parray)->rgsabound)->cElements);
	 }
	 else if ((varInput.vt != VT_NULL)&&(varInput.vt != VT_EMPTY))
	 {
		 csResult = varInput;
	 }
	 return csResult;
 }

 int _variant_t2Int(_variant_t varInput)
 {
	 int iRet;
	  switch(varInput.vt)
	  {
	  case VT_BSTR:
		  iRet = _CString2IntDecimal(varInput);break;
	  case VT_EMPTY:
	  case VT_NULL:iRet = 0;break;
	  default: iRet = varInput; break;

	  }

	  return iRet;


 }

 int __variant_t2CString(_variant_t varInput,CString& csOutput,UINT uiSize )
{
	int bRet = TRUE;;
	switch(varInput.vt)
	{

	case (VT_ARRAY|VT_UI1):
		BYTE*buf;
		SafeArrayAccessData(varInput.parray,(void**)&buf); 
		SafeArrayUnaccessData(varInput.parray);
		csOutput = buf;
		csOutput.ReleaseBuffer( ((varInput.parray)->rgsabound->cElements));
		break;
	case VT_BSTR: csOutput = varInput;break;
	default: bRet = FALSE;


	}


	return bRet;
}

int __variant_t2int(_variant_t varInput,int* iOutput)
{
	int iRet = TRUE;
	switch(varInput.vt)
	{
	case VT_I2:
	case VT_I4:
	case VT_I8:
	case VT_INT:
	case VT_UI1:
	case VT_UI2:
	case VT_UI4:
	case VT_UI8:
	case VT_UINT:
		*iOutput = varInput;
	case VT_BSTR:
		if (_IsAllHex((CString) varInput))
			*iOutput = _CString2IntDecimal((CString) varInput);
		else
			iRet = false;
		break;
	default:iRet = FALSE;break;
	}
	return iRet;
}

int __variant_t2BOOL(_variant_t varInput,BOOL* bOutput)
{
	if (varInput.vt == VT_BOOL)
	{
			*bOutput = varInput.boolVal;

		return TRUE;
	}

	return FALSE;
}

_variant_t CString2_variant_t(int iType,CString csInput)
{
	_variant_t varOutput;
	if (iType == VT_BSTR)
	{
		varOutput = csInput;
		varOutput.vt = VT_BSTR;
	}
	else if (iType == (VT_ARRAY|VT_UI1))
	{
		varOutput.vt = iType;
		char ccc;
		SAFEARRAY *pSA;
		_variant_t var;
		int iLen = csInput.GetLength();
		pSA = SafeArrayCreateVector(VT_UI1,0,iLen);
		 SafeArrayUnaccessData(pSA);

		for (LONG i = 0 ; i <iLen; i++)
		{
			ccc = csInput.GetAt(i);
			SafeArrayPutElement(pSA,&i,(void*)(&ccc));
		}
		varOutput.parray = pSA;
	}
	else
		varOutput.vt = VT_EMPTY;
	

	return varOutput;
}

_variant_t Int2_variant_t(int iType,int iInput)
{
	_variant_t varOutput;
	if (VT_BSTR == iType)
	{
		varOutput = Int2CStringDecimal(iInput);
		varOutput.vt = iType;
	}
	else
	{
		varOutput = iInput;
		varOutput.vt = iType;
	}

	return varOutput;

}


UINT uLong2Byte(ULONG32 ulData,BYTE*Byte,UINT uiByteLen)
{
	if (uiByteLen <4)
		return 0;

	for (int i = 0 ; i<4 ;i++)
	{
		Byte[i] = (ulData>> (24-i*8))&0xFF;
	}

	return 4;
}
ULONG32 Byte2uLong(BYTE*Byte,UINT uiByteLen)
{
	ULONG32 ulData = 0;
	if (uiByteLen <4)
		return 0;
	for (int i = 0 ; i<4 ;i++)
		ulData  = (ulData<<(i*8))+Byte[i];

	return ulData;
}