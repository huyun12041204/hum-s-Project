#ifdef CCR5_EXPORTS
#define CCR5_API __declspec(dllexport)
#else
#define CCR5_API __declspec(dllimport)
#endif


#define   CT_PTSOK                0
#define   CT_PTSNotSppot         -1


#define   CT_OK               1


#define   CT_Err_PTS           -1
#define   CT_Err_Comfirm       -2


#define   CT_Rece_NoData           0
#define   CT_Rece_Err_Tag       -1
#define   CT_Rece_Err_Procedure -2
#define   CT_Rece_Err_Length    -3


#define   CT_Send_Err_Data      -4
#define   CT_Send_Err_Tag       -5
#define   CT_Send_Err_Procedure -6
#define   CT_Send_Err_Length    -7
#define   CT_Send_Err_CheckSum  -8


#define   Cla  00
#define   Ins  01
#define   P1   02
#define   P2   03
#define   P3   04


#define   CT_CheckSum      1
#define   CT_UnCheckSum    0


#define  CT_Cla_Terminal   0x20
#define  CT_Cla_Card       0x80


#define  CT_Ins_Reset       0x11
#define  CT_Ins_Request     0x12
#define  CT_Ins_GetStatus  0x13
#define  CT_Ins_Eject       0x15  // 弹出

#define ICC_Ins_PTS  0x18

#define ICC_Ins_SURP  0x82
#define ICC_Ins_SUWP  0x81
#define ICC_Ins_SS    0x80
#define ICC_Ins_GT    0x86
#define ICC_Ins_TRAN  0x87


#define CT_Err_P2  -0x6A86
#define CT_Tran_OK 0x9000
#define CT_Tran_T0 0x9001

#define  CT_Err_OpenPort  -0x11
#define  CT_Err_GetT_ATR  -0x12
#define  CT_Err_SendT_PTS -0x13
#define  CT_Err_SetT_PTS  -0x14

#define  CT_Err_GetStatus  -0x20
#define  CT_Err_SetupRead  -0x40
#define  CT_Err_SetupWrite -0x80

//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>










#define   CT_INVALID         -1
#define   CT_Error           -8
#define   CT_TRANS          -10
#define   CT_MEMORY         -11 
#define   CT_HOST          -127  
#define   CT_HTSI          -128


#define   CT_NoResponse      -1
#define   CT_WrongSW         -2



#define  CT_Error_Send     -9
#define  CT_Error_Rece     -10


#define   CT_Rece_NoData           0
#define   CT_Rece_Wrong_Tag       -1
#define   CT_Rece_Wrong_Procedure -2
#define   CT_Rece_Wrong_Length    -3


#define   CT_Send_WrongData        0
#define   CT_Send_Wrong_Tag       -1
#define   CT_Send_Wrong_Procedure -2
#define   CT_Send_Wrong_Length    -3
#define   CT_Send_Wrong_CheckSum  -16


#define   CT_Wrong_Pcb       -3

#define   CT_Wrong_PTS    -4




#define   Error_GetStatuse   -0xf1



#define  CT_BasCla      0x20
#define  CT_SpeCla      0x80

#define  CT_Reset       0x11
#define  ICC_Request     0x12
#define  CT_GetStatuse  0x13
#define  ICC_Eject       0x15  // 弹出



#define  ICC_PTS     0x18
#define  CT_SetupWrite     0x81
#define  CT_SetupRead      0x82

#define CT_Sequence        0x80
#define CT_GetSequence     0x84

#define ICC_ChangeSignal     0x85

#define ICC_GetTime         0x86

#define ICC_Trans           0x87
#define ICC_SendTrans       0x8c

#define  ICC_Trans2CMD      0x89

#define ICC_Trans2CMDClock  0xA0

#define  ICC_GetRes2CMD     0x8A

#define  CT_SetParity      0x88

#define  CT_SetListen      0x8D

#define  CT_GetListenRes    0x8E
#define  CT_SetTrigger     0x8F

#define  CT_Statuse   0x16
#define  CT_Config    0x17
#define  CT_Version   0x19




#define  ICC_OK  00;
#define  ICC_Err -8; 


// Reset CT
#define  P1_SoftRs   00
#define  P1_PowerRs  01
#define  P1_PinRs    81

#define  P2_NoData   00
#define  P2_ATR      01
#define  P2_HisChara 02


//#define  ResetFalse  -0x10
//#define  NoATR       -0x11
//#define  WrongATR    -0x12

//Statuse ICC

#define  Statuse_NoCar 00
#define  Statuse_Ready  03
#define  Statuse_NoCon  01
#define  Statuse_OnVol  05

#define  WrongStatuse  -0xf0

//Setup Read

#define  Basic_Para 01

#define  CLK_H      00
#define  CLK_L      01

#define  Vol_H      02
#define  Vol_L      03


#define  Fac_H      04
#define  Fac_L      05

#define  BWT_H      6
#define  BWT_M      7
#define  BWT_L      8

#define  ICWT_H      9
#define  ICWT_M      10
#define  ICWT_L      11

#define  CWT_H      12
#define  CWT_M      13
#define  CWT_L      14

#define  WWT_H      15
#define  WWT_M      16
#define  WWT_L      17

#define  bit18_      18

#define  StopbitS_H      21
#define  StopbitS_L      22
#define  StopbitR_H      23
#define  StopbitR_L      24

#define  StopbitS        20


#define  StartLOW_H      25
#define  StartLOW_L      26

#define  Length_H      27
#define  Length_L     28

#define  Scanning_H      29
#define  Scanning_L     30


// Setup Write

#define  SetupWriteFalse  -0x20;


// Trans

#define PPSFalse         -0x40
#define PTSICCNotSupport  01
#define PTSNotResponse    02
#define PTSWrongResponse -0x41
#define PTSWrongChara    -0x42


//interrupt

#define Rupt_N         0x10
#define Rupt_R         0xE0





//uiSum 初始负值必须大于0,表示ucNumberList大小
extern "C" CCR5_API  BOOL _stdcall CCR5_GetList(BYTE *ucNumberList,UINT *uiSum);


extern "C" CCR5_API  int _stdcall CCR5_ConnectTerminal(HANDLE *hTermHand,UINT uiPort,BYTE *ucTermPTS,UINT uiPTSLen,
						BYTE *ucTerminalATR,UINT *uiT_ATRLen,BYTE *ucCardStatus,
						BYTE *ucManufacturer,UINT *uiM_Len);

extern "C" CCR5_API  int _stdcall CCR5_DisConnectTerminal(HANDLE hTermHand);

extern "C" CCR5_API  int _stdcall CCR5_SetupTerminal2Default(HANDLE hTermHand);

extern "C" CCR5_API  int _stdcall CCR5_PowerOnCard(HANDLE hTermHand,BYTE *ucCardStatus,BYTE*ucCardATR,UINT *uiATRLen,LONG *LTime = NULL);

extern "C" CCR5_API  int _stdcall CCR5_PowerOffCard(HANDLE hTermHand);

extern "C" CCR5_API  int _stdcall CCR5_SendPTS2Card(HANDLE hTermHand,BYTE* ucPTS,UINT uiPTSLen,
													BYTE* ucRes,UINT *uiResLen);
extern "C" CCR5_API  int _stdcall CCR5_Send2Card(HANDLE hTermHand,BYTE* ucSend,UINT uiSendLen,
												 BYTE* ucRes, UINT *uiResLen,LONG *LTime=NULL,BOOL bProByte = FALSE);

extern "C" CCR5_API  int _stdcall CCR5_ResetCard(HANDLE hTermHand,BYTE *ucCardStatus,BYTE*ucCardATR,
	UINT *uiATRLen,LONG *LTimee=NULL);

extern "C" CCR5_API  int _stdcall CCR5_GetTerminalSetting(HANDLE hTermHand,UINT uiP2,
	BYTE* ucSetting,UINT* uiSettingLen);
extern "C" CCR5_API  int _stdcall CCR5_SetTerminalSetting(HANDLE hTermHand,UINT uiPart,
	UINT uiP2,BYTE* ucSetting,UINT uiSettingLen);

extern "C" CCR5_API  int _stdcall CCR5_RequestICC(HANDLE hTermHand,UINT uiP2,BYTE *ucResp,UINT *uiRespLen);

extern "C" CCR5_API  int _stdcall CCR5_EjectICC(HANDLE hTermHand,UINT uiP2,BYTE *ucResp,UINT *uiRespLen);

extern "C" CCR5_API  int _stdcall CCR5_GetCardStatus(HANDLE hTermHand);
