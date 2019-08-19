// ExpAPDU.h : ExpAPDU DLL 的主头文件
#include "..\ParameterConvert\ParameterConvert\ParameterConvert.h"
#include "UNI_Aut_Algorithm.h"




#define ExpAPDU_API extern   "C"   _declspec(dllexport) 



#define  Def_Min_Formate_Length                      50
#define  Def_Max_Formate_Length                      100

#define Def_SIMPLE_Commanddetails                    1
#define Def_SIMPLE_Deviceidentity                    2
#define Def_SIMPLE_Result                            3
#define Def_SIMPLE_Duration                          4
#define Def_SIMPLE_Alphaidentifier                   5
#define Def_SIMPLE_Address                           6
#define Def_SIMPLE_Capabilityconfigurationparameters 7
#define Def_SIMPLE_Subaddress                        8
#define Def_SIMPLE_SSstring                          9
#define Def_SIMPLE_USSDstring                        10
#define Def_SIMPLE_SMSTPDU                           11
#define Def_SIMPLE_CellBroadcastpage                 12
#define Def_SIMPLE_Textstring                        13
#define Def_SIMPLE_Tone                              14
#define Def_SIMPLE_Item                              15
#define Def_SIMPLE_Itemidentifier                    16


#define Def_SIMPLE_Responselength              17
#define Def_SIMPLE_FileList                    18
#define Def_SIMPLE_LocationInformation         19
#define Def_SIMPLE_IMEI                        20
#define Def_SIMPLE_Helprequest                 21
#define Def_SIMPLE_NetworkMeasurementResults   22
#define Def_SIMPLE_DefaultText                 23
#define Def_SIMPLE_ItemsNextActionIndicator    24
#define Def_SIMPLE_Eventlist                   25
#define Def_SIMPLE_Cause                       26
#define Def_SIMPLE_Locationstatus              27
#define Def_SIMPLE_Transactionidentifier       28
#define Def_SIMPLE_BCCHchannellist             29
#define Def_SIMPLE_Iconidentifier              30
#define Def_SIMPLE_ItemIconidentifierlis       31
#define Def_SIMPLE_Cardreaderstatus            32

#define Def_SIMPLE_CardATR                     33
#define Def_SIMPLE_C_APDU                      34
#define Def_SIMPLE_R_APDU                      35
#define Def_SIMPLE_Timeridentifier             36
#define Def_SIMPLE_Timervalue                  37
#define Def_SIMPLE_DateTimeandTimezone         38
#define Def_SIMPLE_Callcontrolrequestedaction  39
#define Def_SIMPLE_ATCommand                   40
#define Def_SIMPLE_ATResponse                  41
#define Def_SIMPLE_BCRepeatIndicator           42
#define Def_SIMPLE_Immediateresponse           43
#define Def_SIMPLE_DTMFstring                  44
#define Def_SIMPLE_Language                    45
#define Def_SIMPLE_TimingAdvance               46
//#define Def_SIMPLE_ItemIconidentifierlis       47
#define Def_SIMPLE_BrowserIdentity             48


#define Def_SIMPLE_URL                         49
#define Def_SIMPLE_Bearer                      50
#define Def_SIMPLE_ProvisioningReferenceFile   51
#define Def_SIMPLE_BrowserTerminationCause     52
#define Def_SIMPLE_Bearerdescription           53
#define Def_SIMPLE_Channeldata                 54
#define Def_SIMPLE_Channeldatalength           55
#define Def_SIMPLE_Channelstatus               56
#define Def_SIMPLE_Buffersize                  57

#define Def_SIMPLE_Cardreaderidentifier        58
//#define Def_SIMPLE_not used                     59
#define Def_SIMPLE_SIMMEinterfacetransportlevel 60
//#define Def_SIMPLE_BrowserTerminationCause     61
#define Def_SIMPLE_Otheraddress                62

#define Def_SIMPLE_AccessTechnology             63
#define Def_SIMPLE_Displayparameters            64

//              Service Record tag 1 '41'
//	'42' or 'C2' Device Filter tag 1 '42'
//	'43' or 'C3' Service Search tag 1 '43'
//	'44' or 'C4' Attribute information tag 1 '44'
//	'45' or 'C5' Service Availability tag 1 '45'
//	'46' or 'C6' Reserved for 3GPP2 (ESN tag) 1 '46'
//	'47' or 'C7' Network Access Name tag 1 '47'
//	'48' or 'C8' Reserved for 3GPP2 (CDMA-SMS-TPDU tag) 1 '48'

#define Def_SIMPLE_ServiceRecord               65
#define Def_SIMPLE_DeviceFilter                66
#define Def_SIMPLE_ServiceSearch               67
#define Def_SIMPLE_AttributeInformation        68
#define Def_SIMPLE_ServiceAvailability         69
#define Def_SIMPLE_ESN                         70
#define Def_SIMPLE_NetworkAccessName           71
#define Def_SIMPLE_CDMASMSTPDU                 72


//   49' or 'C9' Remote Entity Address tag 1 '49'
//	'4A' or 'CA' Reserved for 3GPP (I-WLAN Identifier tag) 1 '4A'
//	'4B' or 'CB' Reserved for 3GPP (I-WLAN Access Status tag) 1 '4B'

#define Def_SIMPLE_RemoteEntityAddress       73
#define Def_SIMPLE_IWLANIdentifier           74
#define Def_SIMPLE_IWLANAccessStatus         75

#define Def_SIMPLE_TextAttribute             80

#define Def_SIMPLE_ItemTextAttributeList            81
#define Def_SIMPLE_PDPContextActivationParameter    82

#define Def_SIMPLE_IMEISV                           98
#define Def_SIMPLE_BatteryState                     99
#define Def_SIMPLE_BrowsingStatus                   100

#define Def_SIMPLE_NetworkSearchMode                101
#define Def_SIMPLE_FrameLayout                      102
#define Def_SIMPLE_FramesInformation                103
#define Def_SIMPLE_FrameIdentifier                  104
#define Def_SIMPLE_UTRANMeasurementQualifier        105
#define Def_SIMPLE_MultimediaMessageReference       106
#define Def_SIMPLE_MultimediaMessageIdentifier      107
#define Def_SIMPLE_MultimediaMessageTransferStatus  108



#define Def_SIMPLE_MEID                             109
#define Def_SIMPLE_MultimediaMessageContentIdentifier 110
#define Def_SIMPLE_MultimediaMessageNotification      111
#define Def_SIMPLE_LastEnvelope                     112
#define Def_SIMPLE_RegistryApplicationData          113
#define Def_SIMPLE_PLMNwAcTList                     114
#define Def_SIMPLE_RoutingAreaInformation           115
#define Def_SIMPLE_UpdateAttachType                 116


//'75' or 'F5' Reserved for 3GPP (Rejection Cause Code Tag) 1 '75'
//	'76' or 'F6' Reserved for 3GPP (Geographical Location
//	Parameters tag)
//	1 '76'
//	'77' or 'F7' Reserved for 3GPP (GAD Shapes tag) 1 '77'
//	'78' or 'F8' Reserved for 3GPP (NMEA sentence tag) 1 '78'
//	'79' or 'F9' Reserved for 3GPP (PLMN List tag) 1 '79'
//	'7A' or 'FA' Broadcast Network Information tag 1 '7A'
//	'7B' or 'FB' ACTIVATE descriptor tag 1 '7B'


#define Def_SIMPLE_RejectionCauseCode                 117
#define Def_SIMPLE_GeographicalLocationParameters     118
#define Def_SIMPLE_GADShapes                          119
#define Def_SIMPLE_NMEASentence                       120
#define Def_SIMPLE_PLMNList                           121
#define Def_SIMPLE_BroadcastNetworkInformation        122
#define Def_SIMPLE_ACTIVATEdescriptor                 123



//7C' or 'FC' Reserved for 3GPP (EPS PDN connection activation
//	parameters tag)
//	1 '7C' Yes
//	'7D' or 'FD' Reserved for 3GPP (Tracking Area Identification tag) 1 '7D' Yes

#define Def_SIMPLE_EPSPDNConnectionActivationParameters     124
#define Def_SIMPLE_TrackingAreaIdentification               125
#define Def_SIMPLE_CSGIDlist                                126
#define Def_SIMPLE_MediaType                                127

#define Def_REFRESH        01
#define Def_MORETIME       02
#define Def_POLLINTERVAL   03
#define Def_POLLINGOFF     04
#define Def_SETUPEVENTLIST 05
#define Def_SETUPCALL    0x10
#define Def_SENDSS       0x11 
#define Def_SENDUSSD     0x12
#define Def_SENDSHORTMESSAGE 0x13
#define Def_SENDDTMF         0x14
#define Def_LAUNCHBROWSER	 0x15
#define Def_PLAYTONE         0x20
#define Def_DISPLAYTEXT      0x21
#define Def_GETINKEY         0x22
#define Def_GETINPUT         0x23
#define Def_SELECTITEM       0x24
#define Def_SETUPMENU        0x25
#define Def_PROVIDELOCALINFORMATION 0x26
#define Def_TIMERMANAGEMENT         0x27
#define Def_SETUPIDLEMODELTEXT      0x28
#define Def_PERFORMCARDAPDU	        0x30
#define Def_POWERONCARD	            0x31
#define Def_POWEROFFCARD	        0x32
#define Def_GETREADERSTATUS	        0x33
#define Def_RUNATCOMMAND	        0x34
#define Def_LANGUAGENOTIFICATION    0x35
#define Def_OPENCHANNEL	            0x40
#define Def_CLOSECHANNEL	        0x41
#define Def_RECEIVEDATA	            0x42
#define Def_SENDDATA	            0x43   
#define Def_GETCHANNELSTATUS        0x44


#define  Def_APDUBASICINFOMATION         1
#define  Def_APDUINFOMATION              2   
#define  Def_OTAINFOMATION               4
#define  Def_DECINFOMATION               8

#define  Def_RC_LENGTH 8
#define  Def_CC_LENGTH 16
#define  Def_DS_LENGTH 96

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CExpAPDUApp
// 有关此类实现的信息，请参阅 ExpAPDU.cpp
//

class CExpAPDUApp : public CWinApp
{
public:
	CExpAPDUApp();
	int iCurrentDF;
	int iPreIns;
	int iPreSPI;
	int iLevel;
	int iOperater;
	CMilenage StMilenage;
	CString csK;
	CString csComput;
	CStringArray csMsgArray;
	CStringArray csCURFMKey;
	CString csDeriveData;
	CString csK1;
	CString csKIc;

// 重写
public:
	virtual BOOL InitInstance();
	BOOL InitParamerter();
	void ResetParameter();
	DECLARE_MESSAGE_MAP()


};

void SetPreCommand(int iCode);
void SetCurrentDF (int iMark);
void ResetParameter();
ExpAPDU_API void SetExplainLevel(int iCode);
ExpAPDU_API BOOL _ExplainSW  (int iSW, CString& csOutput);
ExpAPDU_API BOOL _ExplainIns (int iIns,CString csInput ,CString& csOutput);
ExpAPDU_API BOOL _ExplainAPDU(CString csSend,CString csResp,CStringArray& csOutput);
ExpAPDU_API BOOL _ExplainFetch(CString csFetch,CStringArray& csOutput);
ExpAPDU_API BOOL _ExplainTerminalResponse(CString csTerminalResponse,CStringArray& csOutput);
ExpAPDU_API BOOL _ExplainEvelop(CString csEvelop,CStringArray& csOutput);
ExpAPDU_API BOOL _ExplainTerminalProfile (CString csProfile,CStringArray& csOutput);
ExpAPDU_API BOOL _ExplainBETTLV(CString csBETTLV,CStringArray& csOutput);
ExpAPDU_API BOOL _ExplainProactiveSIMCommand         (CString csProactiveSIMCommand,CStringArray& csOutput);
ExpAPDU_API BOOL _ExplainCommandDetails_SIMPLETLVData(CString csSIMPLETLV,CStringArray&csOutput);
BOOL _ExplainCommandDetails(CString csCommandDetails,CStringArray&csOutput);
BOOL _ExplainDeviceIdentitys(CString csDeviceIdentity,CStringArray&csOutput);
BOOL _ExplainDuration(CString csDuration,CStringArray&csOutput);
BOOL _ExplainResult(CString csResult, CStringArray&csOutput);
BOOL _ExplainAlphaIdentifier(CString csAlphaIdentifier, CStringArray&csOutput);
BOOL _ExplainAddress(CString csAddress, CStringArray&csOutput);
BOOL _ExplainCapabilityConfigurationParameters(CString csInput, CStringArray&csOutput);
BOOL _ExplainSubAddress(CString csInput, CStringArray&csOutput);
BOOL _ExplainSSString(CString csInput, CStringArray&csOutput);
BOOL _ExplainUSSDString(CString csInput, CStringArray&csOutput);
BOOL _ExplainSMSTPDU(CString csInput, CStringArray&csOutput);
BOOL _ExplainSMSDeliver(CString csInput, CStringArray&csOutput);
BOOL _ExplainSMSDeliverReport(CString csInput, CStringArray&csOutput);
BOOL _ExplainSMSCommand(CString csInput, CStringArray&csOutput);
BOOL _ExplainSMSDataCodingScheme(CString csDCS,CStringArray&csOutput);
BOOL _ExplainProtocolIdentifier(CString csPID,CStringArray&csOutput);
BOOL _ExplainUserData(CString csUD,int iDCS,int iUDHI,CStringArray&csOutput);
BOOL _ExplainUserData(CString csInput, CStringArray&csOutput);
BOOL _ExplainSMSSubmit(CString csInput, CStringArray&csOutput);
BOOL _ExplainCellBroadCastPage(CString csInput, CStringArray&csOutput);
BOOL _ExplainTextString(CString csTextString, CStringArray&csOutput);
BOOL _ExplainTone(CString csInput, CStringArray&csOutput);
BOOL _ExplainItem(CString csInput, CStringArray&csOutput);
BOOL _ExplainItemIdentifier(CString csInput, CStringArray&csOutput);
BOOL _ExplainResponseLength(CString csInput, CStringArray&csOutput);
BOOL _ExplainFileList(CString csInput, CStringArray&csOutput);
BOOL _ExplainLocationInformation(CString csInput, CStringArray&csOutput);
BOOL _ExplainIMEI(CString csInput, CStringArray&csOutput);
BOOL _ExplainHelprequest(CString csInput, CStringArray&csOutput);
BOOL _ExplainNetworkMeasurementResults(CString csInput, CStringArray&csOutput);
BOOL _ExplainDefaultText(CString csTextString, CStringArray&csOutput);
BOOL _ExplainItemsNextActionIndicator(CString csInput, CStringArray&csOutput);
BOOL _ExplainEventList(CString csInput, CStringArray&csOutput);
BOOL _ExplainCause(CString csInput, CStringArray&csOutput);
BOOL _ExplainLocationStatus(CString csInput, CStringArray&csOutput);
BOOL _ExplainTransactionIdentifier(CString csInput, CStringArray&csOutput);
BOOL _ExplainBCCHChannelList(CString csInput, CStringArray&csOutput);
BOOL _ExplainTimeValue(CString csInput, CStringArray&csOutput);
CString _TranslateDateTimeAndTimeZone( CString csInput );
BOOL _ExplainDateTimeandTimezone(CString csInput, CStringArray&csOutput);
BOOL _ExplainTemp(CString csName,CString csInput, CStringArray&csOutput);
BOOL _ExplainBCRepeatIndicator(CString csInput, CStringArray&csOutput);
BOOL _ExplainTimingAdvance(CString csInput, CStringArray&csOutput);
BOOL _ExplainBearer(CString csInput, CStringArray&csOutput);
BOOL _ExplainBrowserTerminationCause(CString csInput, CStringArray&csOutput);

BOOL _ExplainBearerDescription(CString csInput, CStringArray&csOutput);
BOOL _ExplainChannelStatus(CString csInput, CStringArray&csOutput);
BOOL _ExplainSIMMEInterfaceTransportLevel(CString csInput, CStringArray&csOutput);
BOOL _ExplainOtherAddress(CString csInput, CStringArray&csOutput);
BOOL _ExplainURL(CString csInput, CStringArray&csOutput);



ExpAPDU_API BOOL _ExplainSelect_UICC(CString csSend,CString csResp,CStringArray&csOutput);
ExpAPDU_API BOOL _ExplainSelect(CString csSend,CString csResp,CStringArray&csOutput);
ExpAPDU_API BOOL _ExplainReadBinary(CString csSend, CStringArray&csOutput);
ExpAPDU_API BOOL _ExplainUpdateBinary(CString csSend, CStringArray&csOutput);
ExpAPDU_API BOOL _ExplainReadRecord(CString csSend, CString csResp, CStringArray&csOutput);
ExpAPDU_API BOOL _ExplainUpdateRecord(CString csSend, CStringArray&csOutput);
ExpAPDU_API BOOL _ExplainSearchRecord(CString csSend, CStringArray&csOutput);
ExpAPDU_API BOOL _ExplainIncrease(CString csSend, CStringArray&csOutput);
ExpAPDU_API BOOL _ExplainDeactiveActive(CString csSend,CStringArray&csOutput);
ExpAPDU_API BOOL _ExplainManageChannel(CString csSend,CStringArray&csOutput);
ExpAPDU_API BOOL _ExplainStatus(CString csSend,CStringArray&csOutput);
 BOOL _ExplainGetResponse(int iPreIns,CString csResp,CStringArray&csOutput);
 BOOL _ExplainSelectResponse(CString csResp,CStringArray&csOutput);
 ExpAPDU_API  BOOL _ExplainAuthenticate(CString csSend,CStringArray&csOutput);
 ExpAPDU_API  BOOL _ExplainAuthenticateResponse(CString csResp,CStringArray&csOutput);
 ExpAPDU_API void SetK(CString csKey);
 ExpAPDU_API BOOL MilenageSetCi(CString csC1,CString csC2,CString csC3,CString csC4,CString csC5);
 ExpAPDU_API BOOL MilenageSetRi(int iR1, int iR2, int iR3, int iR4, int iR5);
 ExpAPDU_API BOOL MilenageSetOPc(CString csOPc);
 ExpAPDU_API BOOL Milenagef2345(CString csK, CString csRand, CString& csRes,CString& csCK, CString& csIK, CString& csAK);
 ExpAPDU_API BOOL Milenagef5star(CString csK, CString csRand,CString& csAKStar);
 ExpAPDU_API BOOL ExplainATR(CString csATR, CStringArray&csOutput);
 BOOL __ExpainCipherUserData(CStringArray& csOutput);
  BOOL __ExpainSigleCipherUserData(CString csInput,CStringArray& csOutput);

 BOOL __ExplainID2SendPatcket(CString csData,CStringArray& csOutput);
 BOOL __ExplainID2ResponsePatcket(CString csData,CStringArray& csOutput);
 BOOL _ExplainID2GetID(CString csResp,CStringArray& csOutput);
 BOOL _ExplainID2GetVendorInfo(CString csResp,CStringArray& csOutput);
 BOOL _ExplainID2SymmetricCrypt(CString csSend,CString csResp,CStringArray& csOutput);

 BOOL _ExplainCDMASMSTPDU(CString csInput, CStringArray&csOutput);
 BOOL _ExplainSMSPointtoPoint(CString csInput, CStringArray&csOutput);
 BOOL _ExplainBearData(CString csInput, CStringArray&csOutput);