
#define  _DEF_Card  0
#define  _DEF_GSM   1
#define  _DEF_CDMA  2
#define  _DEF_DCS      0x8
#define  _DEF_DFIS41   0x9
#define  _DEF_FPCTS    0xA
#define  _DEF_TIAEIA136    0xB
#define  _DEF_TIAEIA95     0x2

#define  _DEF_Tele  0x40
#define  _DEF_USIM  0x10
#define  _DEF_CSIM  0x20
#define  _DEF_ETSI  0x80
#define  _DEF_3GPP  0x10
#define  _DEF_3GPP2 0x20

#define _DEF_GSMACCESS 0x11
#define _DEF_MExE      0x12
#define _DEF_WLAN      0x13
#define _DEF_HNB       0x14
#define _DEF_SoLSA     0x15
#define	_DEF_BCAST     0x16


#define _DEF_MMSS       0x41
#define _DEF_MULTIMEDIA 0x42
#define _DEF_PHONEBOOK  0x43


CString GetACFromARR(int iCommand,CString csARR,int* Other);

void GenerateExpandedFormatSecurityDescriptor(CString* csData,CString* csDescriptor);




CMFCPropertyGridProperty* ExplainARRRecord(CString csData,CString csName,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* Explain2F00Data(CString csData,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainLIData(CString csData,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* Explain2FE2Data(CString csData,BOOL bSubItem = TRUE);

CMFCPropertyGridProperty* ExplainATI(CString csData);
CMFCPropertyGridProperty* _ExplainEXTData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainCFUISD(CString csData);
CMFCPropertyGridProperty* ExplainMWIS(CString csData);
CMFCPropertyGridProperty* ExplainLTAI(CString csLAI);
CMFCPropertyGridProperty* ExplainLAI(CString csLAI);
CMFCPropertyGridProperty* ExplainRAI(CString csRAI);
CMFCPropertyGridProperty* ExplainMID(CString csData,BOOL bSubItem = TRUE,BOOL bOption = FALSE);
CMFCPropertyGridProperty* ExplainDateTime(CString csTP_SCTS);
CMFCPropertyGridProperty* ExplainIMSIData(CString csData,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainKeysData(CString csData,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainKeysPSData(CString csData,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainDCKData(CString csData);
CMFCPropertyGridProperty* ExplainHPPLMNData(CString csData,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainCNLData(CString csData);	
CMFCPropertyGridProperty* ExplainACMmaxData(CString csData,BOOL bSubItem = TRUE);

CMFCPropertyGridProperty* NewUSTSubItem(int iService,BOOL bSupport = TRUE,BOOL bOption = TRUE);
CMFCPropertyGridProperty* ExplainUSTData(CString csData,BOOL bSubItem = TRUE);

CMFCPropertyGridProperty* _ExplainADNData(CString csName,CString csData,int iNumber,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainACMData(CString csData,int iNumber,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainFDNData(CString csData,int iNumber,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainSMSData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainADNData(CString csData,int iNumber,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainMSISDNData(CString csData,int iNumber,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainSMSPData(CString csData,int iNumber,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainSMSSData(CString csData,BOOL bSubItem = TRUE);	
CMFCPropertyGridProperty* ExplainCBMIData(CString csData);	
CMFCPropertyGridProperty* ExplainSPNData(CString csData,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainSMSRData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainCBMIDData(CString csData);
CMFCPropertyGridProperty* ExplainSDNData(CString csData,int iNumber, BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainEXTData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainBDNData(CString csData,int iNumber, BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainCCP2Data(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainCBMIRData(CString csData);
CMFCPropertyGridProperty* ExplainSUMEData(CString csData);
CMFCPropertyGridProperty* ExplainESTData(CString csData, BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainACLData(CString csData);
CMFCPropertyGridProperty* ExplainCMIData(CString csData);
CMFCPropertyGridProperty* ExplainSTARTHFNata(CString csData);
CMFCPropertyGridProperty* ExplainTHRESHOLData(CString csData);
CMFCPropertyGridProperty* ExplainPLMNwAcTData(CString csData);
CMFCPropertyGridProperty* ExplainOPLMNwACTData(CString csData);
CMFCPropertyGridProperty* ExplainHPLMNwACTData(CString csData);
CMFCPropertyGridProperty* ExplainPSLOCIData(CString csData);
CMFCPropertyGridProperty* ExplainACCData(CString csData);
CMFCPropertyGridProperty* ExplainFPLMNData(CString csData);
CMFCPropertyGridProperty* ExplainLOCIData(CString csData,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainICIData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainOCIData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainICTData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainOCTData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainADData(CString csData);
CMFCPropertyGridProperty* ExplainVGCSData(CString csData);
CMFCPropertyGridProperty* ExplainVGCSSData(CString csData);
CMFCPropertyGridProperty* ExplainVBSData(CString csData);
CMFCPropertyGridProperty* ExplainVBSSData(CString csData);
CMFCPropertyGridProperty* ExplaineMLPPData(CString csData);
CMFCPropertyGridProperty* ExplaineAAeMData(CString csData);
CMFCPropertyGridProperty* ExplainECCData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainHiddenkeyData(CString csData);
CMFCPropertyGridProperty* ExplainNETPARData(CString csData);
CMFCPropertyGridProperty* ExplainPNNData(CString csData,int iNumber,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainOPLData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainMBDNData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainMBIData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainMWISData(CString csData,int iNumber);	
CMFCPropertyGridProperty* ExplainCFISData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainSPDIData(CString csData);
CMFCPropertyGridProperty* ExplainMMSNData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainMMSICPData(CString csData);
CMFCPropertyGridProperty* ExplainMMSUPData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainNIAData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainVGCSCAData(CString csData);
CMFCPropertyGridProperty* ExplainVBSCAData(CString csData);
CMFCPropertyGridProperty* ExplainGBABPData(CString csData);
CMFCPropertyGridProperty* ExplainMSKData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainMUKData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainEHPLMNData(CString csData);
CMFCPropertyGridProperty* ExplainGBANLData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainEHPLMNPIData(CString csData);
CMFCPropertyGridProperty* ExplainLRPLMNSIData(CString csData);
CMFCPropertyGridProperty* ExplainNAFKCAData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainSPNIData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainPNNIData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainICE_DNData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainICE_FFData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainNCP_IPData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainEPSLOCIData(CString csData);
CMFCPropertyGridProperty* ExplainEPSNSCData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainKcIData(CString csData);
CMFCPropertyGridProperty* ExplainPLMNselData(CString csData);
CMFCPropertyGridProperty* ExplainSSTData(CString csData,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* ExplainKcGPRSData(CString csData);
CMFCPropertyGridProperty* ExplainLOCIGPRSData(CString csData);	
CMFCPropertyGridProperty* ExplainBCCHData(CString csData);	
CMFCPropertyGridProperty* ExplainPhaseData(CString csData);	
CMFCPropertyGridProperty* ExplainCCPData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainLNDData(CString csData,int iNumber,BOOL bSubItem = TRUE);


//3GPP2

CMFCPropertyGridProperty* ExplainCOUNTData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainIMSIMData(CString csData);	
CMFCPropertyGridProperty* ExplainIMSITData(CString csData);	
CMFCPropertyGridProperty* ExplainTMSIData(CString csData);		
CMFCPropertyGridProperty* ExplainAHData(CString csData);	
CMFCPropertyGridProperty* ExplainAOPData(CString csData);
CMFCPropertyGridProperty* ExplainALOCData(CString csData);
CMFCPropertyGridProperty* ExplainSIDNIDData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainZNREGIData(CString csData,int iNumber);
CMFCPropertyGridProperty* ExplainSNREGIData(CString csData);
CMFCPropertyGridProperty* ExplainDISTREGIIData(CString csData);
CMFCPropertyGridProperty* ExplainACCOLCData(CString csData);	
CMFCPropertyGridProperty* ExplainTERMData(CString csData);	
CMFCPropertyGridProperty* ExplainSSCIData(CString csData);	
CMFCPropertyGridProperty* ExplainACPData(CString csData);	
CMFCPropertyGridProperty* ExplainPRLFileData(CString csData);
CMFCPropertyGridProperty* ExplainPRLData(CString csData);	
BOOL ExplainAcquisitionRecordsData(CMFCPropertyGridProperty* ParentGroup,int iSum,CString csData,int* iOffbit);

BOOL ExplainSystemRecordsData(CMFCPropertyGridProperty* ParentGroup,int iSum,CString csData,int* iOffbit);




BOOL ExplainCellularAnalogData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL ExplainCellularCDMA_StandardChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL ExplainCellularCDMA_CustomChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL ExplainCellularCDMAPreferredData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL ExplainPCSCDMA_UsingBlocksData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);
BOOL ExplainPCSCDMA_UsingChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);

CMFCPropertyGridProperty* ExplainEPRLData(CString csData);

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


CMFCPropertyGridProperty* ExplainUIMIDData(CString csData);	
CMFCPropertyGridProperty* ExplainCSTData(CString csData);
CMFCPropertyGridProperty* ExplainSPCData(CString csData);
CMFCPropertyGridProperty* ExplainOTAPASPCData(CString csData);
CMFCPropertyGridProperty* ExplainNAMLOCKData(CString csData);
CMFCPropertyGridProperty* ExplainOTAData(CString csData);
CMFCPropertyGridProperty* ExplainSPData(CString csData);	
CMFCPropertyGridProperty* ExplainESNMEData(CString csData);		
CMFCPropertyGridProperty* Explain_LIData(CString csData);		
CMFCPropertyGridProperty* Explain_SSFCData(CString csData);		
CMFCPropertyGridProperty* Explain_SPNData(CString csData);
CMFCPropertyGridProperty* Explain_USGINDData(CString csData);
CMFCPropertyGridProperty* Explain_ADData(CString csData);
CMFCPropertyGridProperty* Explain_MDNData(CString csData);	
CMFCPropertyGridProperty* Explain_MAXPRLData(CString csData);	
CMFCPropertyGridProperty* Explain_SPCSData(CString csData);	
CMFCPropertyGridProperty* Explain_ECCData(CString csData);		
CMFCPropertyGridProperty* Explain_ME3GPDOPCData(CString csData);
CMFCPropertyGridProperty* Explain_3GPDOPMData(CString csData);
CMFCPropertyGridProperty* Explain_SIPCAPData(CString csData);
CMFCPropertyGridProperty* Explain_MIPCAPData(CString csData);

CMFCPropertyGridProperty* Explain_SIPUPPData(CString csData);
CMFCPropertyGridProperty* Explain_NAIUPPData(CString csData,int iNumber);

CMFCPropertyGridProperty* Explain_MIPUPPData(CString csData);
CMFCPropertyGridProperty* Explain_SIPSPData(CString csData);
CMFCPropertyGridProperty* Explain_MIPSPData(CString csData);	
CMFCPropertyGridProperty* Explain_SIPPAPSSData(CString csData);	
CMFCPropertyGridProperty* Explain_NAISSData(CString csData,int iNumber);
CMFCPropertyGridProperty* Explain_PUZLData(CString csData);	
CMFCPropertyGridProperty* Explain_MAXPUZLData(CString csData);	
CMFCPropertyGridProperty* Explain_MECRPData(CString csData);	

CMFCPropertyGridProperty* Explain_HRPDCAPData(CString csData);
CMFCPropertyGridProperty* Explain_HRPDUPPData(CString csData);
CMFCPropertyGridProperty* Explain_CSSPRData(CString csData);
CMFCPropertyGridProperty* Explain_ATData(CString csData);
CMFCPropertyGridProperty* ExplainEPRLFileData(CString csData);
CMFCPropertyGridProperty* Explain_BCSMScfgData(CString csData);
CMFCPropertyGridProperty* Explain_BCSMSprefData(CString csData);	
CMFCPropertyGridProperty* Explain_BCSMStableData(CString csData,int iNumber);
CMFCPropertyGridProperty* Explain_BCSMSPData(CString csData,int iNumber);

CMFCPropertyGridProperty* Explain_BAKPARAData(CString csData,int iNumber);	
CMFCPropertyGridProperty* Explain_UpBAKPARAData(CString csData,int iNumber);	
CMFCPropertyGridProperty* Explain_MMSNData(CString csData,int iNumber);	
CMFCPropertyGridProperty* Explain_MMSICPData(CString csData);
CMFCPropertyGridProperty* Explain_MMSICP(CString csData,int iNumber);
CMFCPropertyGridProperty* Explain_MMSImplementation(CString csData);
CMFCPropertyGridProperty* Explain_Gateway(CString csData);
CMFCPropertyGridProperty* Explain_InterfacetoCoreNetworkandBearerInformation(CString csData,int iNumber);	


CMFCPropertyGridProperty* Explain_MMSUPData(CString csData);
CMFCPropertyGridProperty* Explain_MMSUCPData(CString csData);
CMFCPropertyGridProperty* Explain_AuthCapabilityData(CString csData,int iNumber);
CMFCPropertyGridProperty* Explain_3GCIKData(CString csData);	
CMFCPropertyGridProperty* Explain_DCKData(CString csData);	
CMFCPropertyGridProperty* Explain_GID1Data(CString csData);	
CMFCPropertyGridProperty* Explain_GID2Data(CString csData);	
CMFCPropertyGridProperty* Explain_CDMACNLData(CString csData);	
CMFCPropertyGridProperty* Explain_CDMACNL(CString csData,int iNumber);	
CMFCPropertyGridProperty* Explain_HOMETAGData(CString csData);	
CMFCPropertyGridProperty* Explain_GROUPTAGData(CString csData);	
CMFCPropertyGridProperty* Explain_TABLE_Data(CString csData,int iNumber,int *iOffbit);	
CMFCPropertyGridProperty* Explain_SPECIFICTAGData(CString csData);	
CMFCPropertyGridProperty* Explain_CallPromptData(CString csData);	
CMFCPropertyGridProperty* Explain_SFEUIMIDData(CString csData);	
CMFCPropertyGridProperty* Explain_LCSVERData(CString csData);	
CMFCPropertyGridProperty* Explain_PVERData(CString csData);
CMFCPropertyGridProperty* Explain_LCSCPData(CString csData);	
CMFCPropertyGridProperty* Explain_AppLabelsData(CString csData);	
CMFCPropertyGridProperty* Explain_ModelData(CString csData);
CMFCPropertyGridProperty* Explain_RCData(CString csData);
CMFCPropertyGridProperty* Explain_CertificatesData(CString csData,int iNumber);
CMFCPropertyGridProperty* Explain_SMSCAPData(CString csData);	
CMFCPropertyGridProperty* Explain_MIPFlagsData(CString csData);	
CMFCPropertyGridProperty* Explain_SIPUPPExtData(CString csData);		
CMFCPropertyGridProperty* Explain_MIPUPPExtData(CString csData);
CMFCPropertyGridProperty* Explain_IPV6CAPData(CString csData);
CMFCPropertyGridProperty* Explain_TCPConfigData(CString csData);	
CMFCPropertyGridProperty* Explain_DGCData(CString csData);	
CMFCPropertyGridProperty* Explain_WAPBrowserCPCData(CString csData);
CMFCPropertyGridProperty* Explain_WAPBCPData(CString csData,int iNumber);
CMFCPropertyGridProperty* Explain_WAPBrowserBMCData(CString csData);
CMFCPropertyGridProperty* Explain_WAPBookmarkData(CString csData,int iNumber);
CMFCPropertyGridProperty* Explain_MMSConfigData(CString csData);	
CMFCPropertyGridProperty* Explain_JDLData(CString csData);	

CMFCPropertyGridProperty* Explain_LBSXTRAConfigData(CString csData);	
CMFCPropertyGridProperty* Explain_LBSXSURLData(CString csData);		
CMFCPropertyGridProperty* Explain_LBSV2ConfigData(CString csData);
CMFCPropertyGridProperty* Explain_LBSV2PDEADDRData(CString csData);
CMFCPropertyGridProperty* Explain_LBSV2MPCADDRData(CString csData);	
CMFCPropertyGridProperty* Explain_BREWDownloadData(CString csData);	
CMFCPropertyGridProperty* Explain_BREWTSIDData(CString csData);	
CMFCPropertyGridProperty* Explain_BREWSIDData(CString csData);	
CMFCPropertyGridProperty* Explain_BREWAEPData(CString csData);

CMFCPropertyGridProperty* Explain_CPBCCHData(CString csData);
CMFCPropertyGridProperty* Explain_InvScanData(CString csData);
CMFCPropertyGridProperty* Explain_MLPLData(CString csData);

CMFCPropertyGridProperty* Explain_MSPLData(CString csData);
BOOL _Explain_MLPLRECSData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);

BOOL _Explain_MSPLIDData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);

BOOL _Explain_MSPLRECSData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit);

CMFCPropertyGridProperty* _Explain_PBRData(CString csData,int iNumber,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* Explain_FileInPBRData(CString csFile,CString csName,BOOL bSubItem = TRUE);
CMFCPropertyGridProperty* Explain_IAPData(CString csData,int iNumber);
CMFCPropertyGridProperty* Explain_SNEData(CString csData,int iNumber);
CMFCPropertyGridProperty* Explain_CPP1Data(CString csData,int iNumber);
CMFCPropertyGridProperty* Explain_UIDData(CString csData,int iNumber);	
CMFCPropertyGridProperty* Explain_ANRData(CString csData,int iNumber);	
CMFCPropertyGridProperty* Explain_GASData(CString csData,int iNumber);	
CMFCPropertyGridProperty* Explain_AASData(CString csData,int iNumber);	
CMFCPropertyGridProperty* Explain_GRPData(CString csData,int iNumber);		
CMFCPropertyGridProperty* Explain_PBCData(CString csData,int iNumber);	
CMFCPropertyGridProperty* Explain_EMAILData(CString csData,int iNumber);	

CMFCPropertyGridProperty* Explain_AUTHOPC(CString csData);
CMFCPropertyGridProperty* Explain_AUTHPAR(CString csData);


BOOL NotAllowEdit(CMFCPropertyGridProperty* Prop);
BOOL ExpandChildProperty(CMFCPropertyGridProperty* Prop);
BOOL EnableProperty(CMFCPropertyGridProperty* pGrop,BOOL bEnable);
CMFCPropertyGridProperty* ExplainFirstNote(CString csName,CString csData,bool* bRet);

CMFCPropertyGridProperty* Explain_FileData(CString csData,int iFile = -1,int iMark = -1);


BOOL ComplileFileData(CMFCPropertyGridProperty* pGrop,int iFID,int iMark,CString &csFileData,int* iOutputLen = NULL);

BOOL GridPropertyIsChanged(CMFCPropertyGridProperty* pGrop);

BOOL ComplileARRRecord(CMFCPropertyGridProperty* pGrop,CString &csARR);

BOOL GenerateACDataByAC(CMFCPropertyGridProperty* pGrop,CString csACValue,CString csAC,CString& csARR);

BOOL ComplilePBRData(CMFCPropertyGridProperty* pGrop,CString &csPBR);

BOOL ComplileDIRData(CMFCPropertyGridProperty* pGrop,CString &csDIR);

BOOL ComplileBasicData(CMFCPropertyGridProperty* pGrop,CString &csBasicData);

BOOL ComplileIMSIData(CMFCPropertyGridProperty* pGrop,CString &cIMSI);

BOOL ComplileUSTData(CMFCPropertyGridProperty* pGrop,CString &csUST);

BOOL ComplileSSTData(CMFCPropertyGridProperty* pGrop,CString &csSST);

BOOL _ComplileADNData(CMFCPropertyGridProperty* pGrop,CString &csADN,int iADNLen);
BOOL ComplileSPNData(CMFCPropertyGridProperty* pGrop,CString &csSPN);
BOOL ComplilePNNData (CMFCPropertyGridProperty* pGrop,CString &csPNN);
BOOL ComplileSMSPData(CMFCPropertyGridProperty* pGrop,CString &csSMSP,int iSMSPLen= 0x28);
BOOL ComplileMIDData(CMFCPropertyGridProperty* pGrop,CString &csMID);
//************************************
// Method:    ComplileLAIData
// FullName:  ComplileLAIData
// Access:    public 
// Returns:   BOOL success TRUE, unsuccess FALSE
// Qualifier:
// Parameter: CMFCPropertyGridProperty * pGrop
// Parameter: CString & csLIA
//************************************
BOOL ComplileLAIData(CMFCPropertyGridProperty* pGrop,CString &csLIA);
//************************************
// Method:    ComplileLOCIData
// FullName:  ComplileLOCIData
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: CMFCPropertyGridProperty * pGrop
// Parameter: CString & csLOCI
//************************************
BOOL ComplileLOCIData(CMFCPropertyGridProperty* pGrop,CString &csLOCI);
//************************************
// Method:    ComplileSMSSData
// FullName:  ComplileSMSSData
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: CMFCPropertyGridProperty * pGrop
// Parameter: CString & csSMSS
//************************************
BOOL ComplileSMSSData(CMFCPropertyGridProperty* pGrop,CString &csSMSS);
//************************************
// Method:    ComplileESTData
// FullName:  ComplileESTData
// Access:    public 
// Returns:   BOOL
// Qualifier:
// Parameter: CMFCPropertyGridProperty * pGrop
// Parameter: CString & csEST
//************************************
BOOL ComplileESTData(CMFCPropertyGridProperty* pGrop,CString &csEST);