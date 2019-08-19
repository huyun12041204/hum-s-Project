// ExpFile.h : ExpFile DLL 的主头文件
//
#define ExpFile_API extern   "C"   _declspec(dllexport) 

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CExpFileApp
// 有关此类实现的信息，请参阅 ExpFile.cpp
//

class CExpFileApp : public CWinApp
{
public:
	CExpFileApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};




ExpFile_API CMFCPropertyGridProperty* ExplainARRRecord(CString csData,int iRecord,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain2F00Data(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainLIData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain2FE2Data(CString csData,BOOL bSubItem = TRUE);


ExpFile_API CMFCPropertyGridProperty* _NewSupportedText(CString csName,bool bStatus = true,bool bEmpty = false,bool bOption = false);

ExpFile_API CMFCPropertyGridProperty* ExplainATI(CString csData,BOOL bOption = FALSE);
ExpFile_API CMFCPropertyGridProperty* _ExplainEXTData(CString csData,int iNumber,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainCFUISD(CString csData);
CMFCPropertyGridProperty* ExplainMWIS(CString csData);
CMFCPropertyGridProperty* ExplainLTAI(CString csLAI);
CMFCPropertyGridProperty* ExplainLAI(CString csLAI);
CMFCPropertyGridProperty* ExplainRAI(CString csRAI);
ExpFile_API CMFCPropertyGridProperty* ExplainMID(CString csData,BOOL bSubItem = TRUE,BOOL bOption = FALSE);
CMFCPropertyGridProperty* ExplainDateTime(CString csTP_SCTS);
ExpFile_API CMFCPropertyGridProperty* ExplainIMSIData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainKeysData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainKeysPSData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainDCKData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainHPPLMNData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainCNLData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* ExplainACMmaxData(CString csData,BOOL bSubItem = TRUE);

ExpFile_API CMFCPropertyGridProperty* NewUSTSubItem(int iService,BOOL bSupport = TRUE,BOOL bOption = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainUSTData(CString csData,BOOL bSubItem = TRUE);

ExpFile_API CMFCPropertyGridProperty* _ExplainADNData(CString csName,CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainACMData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainFDNData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainSMSData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainADNData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainMSISDNData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainSMSPData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainSMSSData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* ExplainCBMIData(CString csData,BOOL bSubItem= TRUE);	
ExpFile_API CMFCPropertyGridProperty* ExplainSPNData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainSMSRData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainCBMIDData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainSDNData(CString csData,int iNumber, BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainEXTData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainBDNData(CString csData,int iNumber, BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainCCP2Data(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainCBMIRData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainSUMEData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainESTData(CString csData, BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainACLData(CString csData, BOOL bSubItem= TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainCMIData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainSTARTHFNata(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainTHRESHOLData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainPLMNwAcTData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainOPLMNwACTData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainHPLMNwACTData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainPSLOCIData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainACCData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainFPLMNData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainLOCIData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainICIData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainOCIData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainICTData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainOCTData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainADData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainVGCSData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainVGCSSData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainVBSData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainVBSSData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplaineMLPPData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplaineAAeMData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainECCData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainHiddenkeyData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainNETPARData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainPNNData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainOPLData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainMBDNData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainMBIData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainMWISData(CString csData,int iNumber,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* ExplainCFISData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainSPDIData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainMMSNData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainMMSICPData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainMMSUPData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainNIAData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainVGCSCAData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainVBSCAData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainGBABPData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainMSKData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainMUKData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainEHPLMNData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainGBANLData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainEHPLMNPIData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainLRPLMNSIData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainNAFKCAData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainSPNIData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainPNNIData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainICE_DNData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainICE_FFData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainNCP_IPData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainEPSLOCIData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainEPSNSCData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainKcIData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainPLMNselData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainSSTData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainKcGPRSData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainLOCIGPRSData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* ExplainBCCHData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* ExplainPhaseData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* ExplainCCPData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainLNDData(CString csData,int iNumber,BOOL bSubItem = TRUE);


//3GPP2

ExpFile_API CMFCPropertyGridProperty* ExplainCOUNTData(CString csData,int iNumber, BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainIMSIMData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainIMSITData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainTMSIData(CString csData,BOOL bSubItem = TRUE);		
ExpFile_API CMFCPropertyGridProperty* ExplainAHData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* ExplainAOPData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainALOCData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainSIDNIDData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainZNREGIData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainSNREGIData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainDISTREGIIData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainACCOLCData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* ExplainTERMData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* ExplainSSCIData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* ExplainACPData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainPRLFileData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainPRLData(CString csData);	
BOOL ExplainAcquisitionRecordsData(CMFCPropertyGridProperty* ParentGroup,int iSum,CString csData,int* iOffbit);

BOOL ExplainSystemRecordsData(CMFCPropertyGridProperty* ParentGroup,int iSum,CString csData,int* iOffbit);




BOOL ExplainCellularAnalogData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL ExplainCellularCDMA_StandardChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL ExplainCellularCDMA_CustomChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL ExplainCellularCDMAPreferredData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL ExplainPCSCDMA_UsingBlocksData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL ExplainPCSCDMA_UsingChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);

ExpFile_API CMFCPropertyGridProperty* ExplainEPRLData(CString csData);

BOOL ExplainExtendedAcquisitionRecordsData(CMFCPropertyGridProperty* ParentGroup,int iSum,CString csData,int* iOffbit);


BOOL _ExplainCellularAnalogData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL _ExplainCellularCDMA_StandardChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL _ExplainCellularCDMA_CustomChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL _ExplainCellularCDMAPreferredData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL _ExplainPCSCDMA_UsingBlocksData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL _ExplainPCSCDMA_UsingChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);


BOOL ExplainJTACSCDMA_StandardChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL ExplainJTACSCDMA_CustomChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL Explain2GHzBand_UsingChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL ExplainGenericAcquisitionRecordforIS2000andIS95Data(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL ExplainGenericAcquisitionRecordforHRPDData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);

BOOL ExplainCommonSubnetRecordData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);

BOOL ExplainExtendedSystemRecordsData(CMFCPropertyGridProperty* ParentGroup,int iSum,CString csData,int* iOffbit);


ExpFile_API CMFCPropertyGridProperty* ExplainUIMIDData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainCSTData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainSPCData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainOTAPASPCData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainNAMLOCKData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainOTAData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainSPData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* ExplainESNMEData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* Explain_LIData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* Explain_SSFCData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_SPNData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_USGINDData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_ADData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_MDNData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_MAXPRLData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* Explain_SPCSData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_ECCData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* Explain_ME3GPDOPCData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_3GPDOPMData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_SIPCAPData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_MIPCAPData(CString csData,BOOL bSubItem = TRUE);

ExpFile_API CMFCPropertyGridProperty* Explain_SIPUPPData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_NAIUPPData(CString csData,int iNumber);

ExpFile_API CMFCPropertyGridProperty* Explain_MIPUPPData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_SIPSPData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_MIPSPData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* Explain_SIPPAPSSData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_NAISSData(CString csData,int iNumber);
ExpFile_API CMFCPropertyGridProperty* Explain_PUZLData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* Explain_MAXPUZLData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_MECRPData(CString csData,BOOL bSubItem = TRUE);

ExpFile_API CMFCPropertyGridProperty* Explain_HRPDCAPData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_HRPDUPPData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_CSSPRData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_ATData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* ExplainEPRLFileData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_BCSMScfgData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_BCSMSprefData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_BCSMStableData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_BCSMSPData(CString csData,int iNumber,BOOL bSubItem = TRUE);

ExpFile_API CMFCPropertyGridProperty* Explain_BAKPARAData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_UpBAKPARAData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_MMSNData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_MMSICPData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_MMSICP(CString csData,int iNumber);
ExpFile_API CMFCPropertyGridProperty* Explain_MMSImplementation(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_Gateway(CString csData);
ExpFile_API CMFCPropertyGridProperty* Explain_InterfacetoCoreNetworkandBearerInformation(CString csData,int iNumber,BOOL bSubItem = TRUE);


ExpFile_API CMFCPropertyGridProperty* Explain_MMSUPData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_MMSUCPData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_AuthCapabilityData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_3GCIKData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* Explain_DCKData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* Explain_GID1Data(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_GID2Data(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_CDMACNLData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_CDMACNL(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_HOMETAGData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_GROUPTAGData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_TABLE_Data(CString csData,int iNumber,int *iOffbit);	
ExpFile_API CMFCPropertyGridProperty* Explain_SPECIFICTAGData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_CallPromptData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* Explain_SFEUIMIDData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_LCSVERData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_PVERData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_LCSCPData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* Explain_AppLabelsData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* Explain_ModelData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_RCData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_CertificatesData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_SMSCAPData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_MIPFlagsData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_SIPUPPExtData(CString csData,BOOL bSubItem = TRUE);		
ExpFile_API CMFCPropertyGridProperty* Explain_MIPUPPExtData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_IPV6CAPData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_TCPConfigData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* Explain_DGCData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_WAPBrowserCPCData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_WAPBCPData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_WAPBrowserBMCData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_WAPBookmarkData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_MMSConfigData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* Explain_JDLData(CString csData,BOOL bSubItem = TRUE);

ExpFile_API CMFCPropertyGridProperty* Explain_LBSXTRAConfigData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_LBSXSURLData(CString csData,BOOL bSubItem = TRUE);	
ExpFile_API CMFCPropertyGridProperty* Explain_LBSV2ConfigData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_LBSV2PDEADDRData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_LBSV2MPCADDRData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_BREWDownloadData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_BREWTSIDData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_BREWSIDData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_BREWAEPData(CString csData,BOOL bSubItem = TRUE);

ExpFile_API CMFCPropertyGridProperty* Explain_CPBCCHData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_InvScanData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_MLPLData(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_MSPLData(CString csData,BOOL bSubItem = TRUE);

BOOL _Explain_MLPLRECSData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);

BOOL _Explain_MSPLIDData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);

BOOL _Explain_MSPLRECSData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);

ExpFile_API CMFCPropertyGridProperty* _Explain_PBRData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_FileInPBRData(CString csFile,CString csName,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_IAPData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_SNEData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_CPP1Data(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_UIDData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_ANRData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_GASData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_AASData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_GRPData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_PBCData(CString csData,int iNumber,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_EMAILData(CString csData,int iNumber,BOOL bSubItem = TRUE);	

ExpFile_API CMFCPropertyGridProperty* Explain_AUTHOPC(CString csData,BOOL bSubItem = TRUE);
ExpFile_API CMFCPropertyGridProperty* Explain_AUTHPAR(CString csData,BOOL bSubItem = TRUE);


BOOL NotAllowEdit( CMFCPropertyGridProperty* Prop);
ExpFile_API CMFCPropertyGridProperty* Explain_FileData_InMF(CString csData,int iFID,int iRecord,BOOL bSub);
ExpFile_API CMFCPropertyGridProperty* Explain_FileData_InTelecom(CString csData,int iFID,int iRecord,BOOL bSub);
ExpFile_API CMFCPropertyGridProperty* Explain_FileData_InMMSS(CString csData,int iFID,int iRecord,BOOL bSub);
ExpFile_API CMFCPropertyGridProperty* Explain_FileData_InGSMACCESS(CString csData,int iFID,int iRecord,BOOL bSub);
ExpFile_API CMFCPropertyGridProperty* Explain_FileData_InPhoneBook(CString csData,int iFID,int iRecord,BOOL bSub);
ExpFile_API CMFCPropertyGridProperty* Explain_FileData_InGSM(CString csData,int iFID,int iRecord,BOOL bSub);
ExpFile_API CMFCPropertyGridProperty* Explain_FileData_InCDMA(CString csData,int iFID,int iRecord,BOOL bSub);
ExpFile_API CMFCPropertyGridProperty* Explain_FileData_In3GPP(CString csData,int iFID,int iRecord,BOOL bSub);
ExpFile_API CMFCPropertyGridProperty* Explain_FileData_In3GPP2(CString csData,int iFID,int iRecord,BOOL bSub);
ExpFile_API BOOL ExpandChildProperty( CMFCPropertyGridProperty* Prop);
ExpFile_API BOOL EnableProperty(CMFCPropertyGridProperty* pGrop,BOOL bEnable);
ExpFile_API CMFCPropertyGridProperty* ExplainFirstNote(CString csName,CString csData,bool* bRet, BOOL bSubItem);

ExpFile_API CMFCPropertyGridProperty* Explain_FileData(CString csData,int iFile = -1,int iMark = -1);


ExpFile_API BOOL ComplileFileData(CMFCPropertyGridProperty* pGrop,int iFID,int iMark,CString &csFileData,int* iOutputLen = NULL);

ExpFile_API BOOL GridPropertyIsChanged(CMFCPropertyGridProperty* pGrop);

ExpFile_API BOOL ComplileARRRecord(CMFCPropertyGridProperty* pGrop,CString &csARR);

//************************************
// Method:    GenerateCommandAC
// FullName:  GenerateCommandAC
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: CMFCPropertyGridProperty * pGrop
// Parameter: CString csCommandName
// Parameter: int iIns
// Parameter: CString & csARR
// 如果为NEVER 时此处返回 FALSE ,并且 input csARR 会为空
//************************************
ExpFile_API BOOL GenerateCommandAC(CMFCPropertyGridProperty* pGrop,CString csCommandName,int iIns,CString& csARR);
//************************************
// Method:    GenerateACDataByAC
// FullName:  GenerateACDataByAC
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: CMFCPropertyGridProperty * pGrop
// Parameter: CString csACValue
// Parameter: CString csAC
// Parameter: CString & csARR
// Example  : 
// if (GenerateACDataByAC(pGrop,_T("A406830101950108"),_T("PIN 01"),csTempARR))
// ....
//************************************
ExpFile_API BOOL GenerateACDataByAC(CMFCPropertyGridProperty* pGrop,CString csACValue,CString csAC,CString& csARR);


ExpFile_API BOOL TransationACName2Data(CString csACName,CString& csARR);

ExpFile_API BOOL ComplilePBRData(CMFCPropertyGridProperty* pGrop,CString &csPBR);

ExpFile_API BOOL ComplileDIRData(CMFCPropertyGridProperty* pGrop,CString &csDIR);

ExpFile_API BOOL ComplileBasicData(CMFCPropertyGridProperty* pGrop,CString &csBasicData);

ExpFile_API BOOL ComplileIMSIData(CMFCPropertyGridProperty* pGrop,CString &cIMSI);

ExpFile_API BOOL ComplileUSTData(CMFCPropertyGridProperty* pGrop,CString &csUST);

ExpFile_API BOOL ComplileSSTData(CMFCPropertyGridProperty* pGrop,CString &csSST);

ExpFile_API BOOL _ComplileADNData(CMFCPropertyGridProperty* pGrop,CString &csADN,int iADNLen);
ExpFile_API BOOL ComplileSPNData(CMFCPropertyGridProperty* pGrop,CString &csSPN);
ExpFile_API BOOL ComplilePNNData (CMFCPropertyGridProperty* pGrop,CString &csPNN);
ExpFile_API BOOL ComplileMIDData(CMFCPropertyGridProperty* pGrop,CString &csMID);
//************************************
// Method:    ComplileLAIData
// FullName:  ComplileLAIData
// Access:    public 
// Returns:   BOOL success TRUE, unsuccess FALSE
// Qualifier:
// Parameter: CMFCPropertyGridProperty * pGrop
// Parameter: CString & csLIA
//************************************
ExpFile_API BOOL ComplileLAIData(CMFCPropertyGridProperty* pGrop,CString &csLIA);
//************************************
// Method:    ComplileLOCIData
// FullName:  ComplileLOCIData
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: CMFCPropertyGridProperty * pGrop
// Parameter: CString & csLOCI
//************************************
ExpFile_API BOOL ComplileLOCIData(CMFCPropertyGridProperty* pGrop,CString &csLOCI);
//************************************
// Method:    ComplileSMSSData
// FullName:  ComplileSMSSData
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: CMFCPropertyGridProperty * pGrop
// Parameter: CString & csSMSS
//************************************
ExpFile_API BOOL ComplileSMSSData(CMFCPropertyGridProperty* pGrop,CString &csSMSS);
//************************************
// Method:    ComplileESTData
// FullName:  ComplileESTData
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: CMFCPropertyGridProperty * pGrop
// Parameter: CString & csEST
//************************************
ExpFile_API BOOL ComplileESTData(CMFCPropertyGridProperty* pGrop,CString &csEST);


//************************************
// Method:    ComplileEXTData
// FullName:  ComplileEXTData
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: CMFCPropertyGridProperty * pGrop
// Parameter: CString & csEXT
//************************************
ExpFile_API  BOOL ComplileEXTData(CMFCPropertyGridProperty* pGrop,CString &csEXT);



//************************************
// Method:    IndexInOption
// FullName:  IndexInOption
// Access:    public 
// Returns:   int index  (0 - XX) or -1 
// Qualifier:
// Parameter: CMFCPropertyGridProperty * pGrop
//************************************
ExpFile_API int IndexInOption(CMFCPropertyGridProperty* pGrop);
//************************************
// Method:    _ComplilePLMNData
// FullName:  _ComplilePLMNData
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: CMFCPropertyGridProperty * pGrop
// Parameter: CString & csPLMN
//************************************
ExpFile_API BOOL _ComplilePLMNData(CMFCPropertyGridProperty* pGrop,CString &csPLMN);

ExpFile_API BOOL ComplileSMSPData(CMFCPropertyGridProperty* pGrop,CString &csSMSP,int iSMSPLen);





