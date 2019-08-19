// CCR5.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include "CCR5.h"
#include "atlstr.h"

BYTE ucSProcedure = 0x40;	
BYTE urRProcedure = 0x40;
int iFlag = 0;


BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


BYTE ExChangeProcedure_T1( BYTE ucRespPro,int iMode)
{
	BYTE ucResult;
	switch (ucRespPro&0xF0)
	{
	case 0x00:ucResult = (0x40|iMode);break;	
	case 0x40:ucResult = 00|iMode;break;	
	case 0x20:ucResult = 0x90;break;
	case 0x60:ucResult = 0x80;break;
	case 0x80:ucResult = 0x00;break;
	case 0xC0:ucResult = ucRespPro|0x20;break;
	case 0x90:ucResult = 0x40;break;
	default:ucResult = 0x00;break;
	}
	return ucResult;
}

BYTE GetnerateCheckSum(BYTE* ucTempdata,int iDataLen)
{
	BYTE ucCheckSum;
	ucCheckSum = 00;
	for (int i= 0; i< iDataLen ; i++)
	{
		ucCheckSum = ucCheckSum ^ ucTempdata[i];		
	}
	return ucCheckSum;
}

int GetSW4Response(BYTE *ucResp,UINT uiRespLen)
{
	int iRet;
	iRet = ucResp[uiRespLen-2]*0x100+ucResp[uiRespLen-1];
	return iRet;
}

void GetCardResp4T_Resp(BYTE* ucT_Resp,UINT uiT_RespLen,BYTE* ucCardResp,UINT *uiCardLen)
{


	*uiCardLen = 0;
	for (UINT i = 0 ; i < uiT_RespLen  ; i=i+2) //范围需要排除SW 所以 -2 
	{
		if (ucT_Resp[i+1] == 0x80)
		{
			ucCardResp[*uiCardLen] = ucT_Resp[i];
			*uiCardLen  = *uiCardLen +1;
		}
	}

}

BOOL CCR5_OpenComPort(HANDLE *hCmPort,int iComPort,int iBaudrate,int iParityFlag)
{


	DCB dcb;
	COMMTIMEOUTS timeouts;
	CString csComPort;
	csComPort.Format(_T("\\\\.\\COM%d"),iComPort);

	*hCmPort = CreateFile(csComPort,GENERIC_READ|GENERIC_WRITE,0,NULL,OPEN_EXISTING,0,NULL);
	if (*hCmPort == INVALID_HANDLE_VALUE)
		return FALSE;

	GetCommTimeouts(hCmPort,&timeouts);

	timeouts.ReadIntervalTimeout = MAXWORD;
	//timeouts.ReadIntervalTimeout = 1000;
	timeouts.ReadTotalTimeoutMultiplier = 0;
	timeouts.ReadTotalTimeoutConstant = 0;//100;
	timeouts.WriteTotalTimeoutMultiplier = 100;
	timeouts.WriteTotalTimeoutConstant = 2000;


	if (!SetCommTimeouts(*hCmPort,&timeouts))
		return FALSE;

	if (!GetCommState(*hCmPort,&dcb))
		return FALSE;

	dcb.BaudRate = iBaudrate;
	dcb.ByteSize = 8;
	if ( iParityFlag != 0  ) 
	{
		dcb.fParity = TRUE;
		if ( iParityFlag == 2 ) dcb.Parity = EVENPARITY; else dcb.Parity = ODDPARITY;
	}
	else dcb.fParity = false;

	dcb.StopBits = ONESTOPBIT;

	//此处CH340 一定需要先关闭再开
	if (dcb.fDtrControl)
	{
		dcb.fDtrControl = FALSE;
		if (!SetCommState(*hCmPort,&dcb))
			return FALSE;
	}

	dcb.fDtrControl = TRUE;

	if (!SetCommState(*hCmPort,&dcb))
		return FALSE;
	//此处往上

	//以下都为后续添加试验
	//SetupComm(hCmPort,1024,1024);
	//PurgeComm(hCmPort, PURGE_TXCLEAR|PURGE_RXCLEAR|PURGE_RXABORT|PURGE_TXABORT );

	//DWORD dwErr;
	//COMSTAT comstat;
	//BOOL bRet;
	//dwErr = 0;

	//bRet = GetCommState(hCmPort,&dcb);
	//bRet = ClearCommError(hCmPort,&dwErr,&comstat);
	//bRet = ClearCommBreak(hCmPort);



	return TRUE;

}

BOOL Port_Close(HANDLE hCmPort)
{
	if ( hCmPort==NULL ) 
		return FALSE;

	if(!CloseHandle(hCmPort)) 
		return FALSE;

	hCmPort = NULL;

	return TRUE;
}

//此处只设置波特率
BOOL SetBaudRate(HANDLE hCmPort, UINT uiBaudrate)
{
	DCB	dcb;

	if (!GetCommState(hCmPort,&dcb))
		return FALSE;

	dcb.BaudRate = uiBaudrate;

	if (!SetCommState(hCmPort,&dcb))
		return FALSE;

	return TRUE;
}

BOOL ReadCharsFromPort(HANDLE hCmPort, unsigned char *cResp, unsigned int uiRespLen)
{
	DWORD nRecv;
	nRecv = uiRespLen;

	if ( !ReadFile(hCmPort, cResp, uiRespLen, &nRecv,NULL )|| nRecv!=uiRespLen)
	{   
		//read error
		PurgeComm(hCmPort, PURGE_RXCLEAR);
		return FALSE;
	}
	return TRUE;
}

BOOL SendCharsToPort(HANDLE hCmPort, unsigned char *cSend, unsigned int uiSendLen)
{
	DWORD nSent;
	if(WriteFile(hCmPort, cSend, uiSendLen, &nSent, NULL) == 0)
	{
		PurgeComm(hCmPort, PURGE_TXCLEAR);
		return FALSE;	//error
	}
	return TRUE;
}

//只能获取一次在OpenPort
BOOL CCR5_GetTerminalATR(HANDLE hTermHand,BYTE *ucTermATR,UINT *uiSendLen)
{

	*uiSendLen = 0;
	if ( !ReadCharsFromPort(hTermHand, ucTermATR, 03))
		return FALSE;

	if ( !ReadCharsFromPort(hTermHand, ucTermATR+3, ucTermATR[2]))
		return FALSE;

	if ( !ReadCharsFromPort(hTermHand, ucTermATR+3+ucTermATR[2],1))
		return FALSE;

	*uiSendLen = 3+ucTermATR[2];

	return TRUE;
}


//在GetTerminalATR 之后执行
BOOL CCR5_SetTerminalPTS(HANDLE hTermHand,BYTE *ucTermPTS,UINT uiPTSLen,BYTE *ucResPTS,UINT *uiResLen)
{
	BYTE ucHearder[3];
	BYTE ucCheckSum;

	ucHearder[0] = 0xFF;
	ucHearder[1] = 0x01;
	ucHearder[2] = uiPTSLen;

	if (!SendCharsToPort(hTermHand,ucHearder,03))
		return FALSE;
	if (!SendCharsToPort(hTermHand,ucTermPTS,uiPTSLen))
		return FALSE;
	ucCheckSum = GetnerateCheckSum(ucHearder,03)^GetnerateCheckSum(ucTermPTS,uiPTSLen);
	if (!SendCharsToPort(hTermHand,&ucCheckSum,01))
		return FALSE;


	if (!ReadCharsFromPort(hTermHand,ucHearder,03))
		return FALSE;

	if ((ucHearder[0]!=0xFF)||(ucHearder[1]!=01))
		return FALSE;

	if (!ReadCharsFromPort(hTermHand,ucResPTS,ucHearder[2]))
		return FALSE;

	*uiResLen = ucHearder[2];

	if (!ReadCharsFromPort(hTermHand,&ucCheckSum,01))
		return FALSE;

	return TRUE;
}

//在SetTerminalPTS 之后执行
BOOL CCR5_SetTerminalTransmissionParameter(HANDLE hTermHand,BYTE *ucPTS,UINT uPTSLen)
{
	UINT uiBaud;

	uiBaud = ucPTS[1] +(ucPTS[2]&0x7)*0x100;

	switch(uiBaud)
	{
	case 01:
		uiBaud = 1200;
		break;
	case 02:
		uiBaud = 2400;
		break;
	case 04:
		uiBaud = 4800;
		break;
	case 0x08:
		uiBaud = 9600;
		break;
	case 0x10:
		uiBaud = 19200;
		break;
	case 0x20:
		uiBaud = 28800;
		break;
	case 0x40:
		uiBaud = 38400;
		break;
	case 0x80:
		uiBaud = 57600;
		break;
	case 0x100:
		uiBaud = 64000;
		break;
	case 0x200:
		uiBaud = 115200;
		break;
	case 0x400:
		uiBaud = 230400;
		break;
	default:
		return FALSE;
	}
	

	return SetBaudRate(hTermHand,uiBaud);

}

int ReceiveData(HANDLE hTermHand, BYTE ucReceDataTag, BYTE *ucPcb,BYTE * ucpReceDataBuf, unsigned int * uipReceDataLen,int iChecksum)
{

	BYTE ucRecBuf;
	int iTime;

	iTime = 00;

	while(!ReadCharsFromPort(hTermHand, &ucRecBuf, 1))
	{

		iTime++;
		Sleep(50);
		if (iTime>5)
			return CT_Rece_Err_Tag;

	}
	

	 if (ucRecBuf!= ucReceDataTag)
		 return CT_Rece_Err_Tag;

	 if (!ReadCharsFromPort(hTermHand, ucPcb, 1))
		 return CT_Rece_Err_Procedure;

	 if (!ReadCharsFromPort(hTermHand, &ucRecBuf, 1))
		 return CT_Rece_Err_Length;

	 *uipReceDataLen = ucRecBuf;

	 if(!ReadCharsFromPort(hTermHand, ucpReceDataBuf,*uipReceDataLen))
	 {
		 *uipReceDataLen = 0;
		 return CT_Rece_NoData;
	 }

	 if (!ReadCharsFromPort(hTermHand, &ucRecBuf, iChecksum))
		 return CT_Rece_Err_Length;

	 return CT_OK;
}

int SendData(HANDLE hTermHand, BYTE ucSendDataTag,BYTE ucProcedure, BYTE *ucpSendDataBuf, unsigned int uiSendDataLen, int iChecksum)
{
//	BYTE ucSendHead[3],ucChecksum;




	// 分别为Tag Pcb len
	//ucSendHead[0] = ucSendDataTag;
	//ucSendHead[1] = ucProcedure;
	//ucSendHead[2] = uiSendDataLen;



	//if(!SendCharsToPort(hTermHand,ucSendHead,01))
	//	return CT_Send_Err_Tag;
	//if(!SendCharsToPort(hTermHand,ucSendHead+1,01))
	//	return CT_Send_Err_Procedure;
	//if(!SendCharsToPort(hTermHand,ucSendHead+2,01))
	//	return CT_Send_Err_Length;


	//data

	//if(!SendCharsToPort(hTermHand,ucpSendDataBuf,uiSendDataLen))
	//	return CT_Send_Err_Data;
	// checksum


	//ucChecksum = GetnerateCheckSum(ucSendHead,3)^GetnerateCheckSum(ucpSendDataBuf,uiSendDataLen);

	//if(!SendCharsToPort(hTermHand,&ucChecksum,01))
	//	return CT_Send_Err_CheckSum;

	BYTE *ucSend;

	ucSend = new BYTE[uiSendDataLen+4];
	ZeroMemory(ucSend,uiSendDataLen+4);

	ucSend[0] = ucSendDataTag;
	ucSend[1] = ucProcedure;
	ucSend[2] = uiSendDataLen;

	memcpy(ucSend+3,ucpSendDataBuf,uiSendDataLen);
	ucSend[uiSendDataLen+3] = GetnerateCheckSum(ucSend,uiSendDataLen+3);

	if(!SendCharsToPort(hTermHand,ucSend,uiSendDataLen+4))
		return CT_Send_Err_Data;

	return CT_OK;
}

//在SetTerminalTransmissionParameter之后执行
int CCR5_ConfirmTerminal(HANDLE hTermHand)
{

	int iRet;
	BYTE ucReceDataTag,ucProcedure;
	UINT uipReceDataLen;
	iRet = SendData(hTermHand,0x12,0xC0,NULL,00,CT_CheckSum);
	if (iRet!= CT_OK)
		return FALSE;
	ucReceDataTag = 0x21;
	iRet =  ReceiveData(hTermHand,ucReceDataTag,&ucProcedure,NULL,&uipReceDataLen,CT_CheckSum);
	if (iRet!= CT_OK)
		return FALSE;

	if (uipReceDataLen!=0)
		return FALSE;
	return TRUE;

}


int CCR5_SendCommand2ComPort(HANDLE hTermHand, BYTE ucSendDataTag,BYTE ucProcedure, BYTE *ucpSendDataBuf, UINT uiSendDataLen,BYTE ucRespTag,BYTE *ucRProcedure,BYTE *ucpRespDataBuf,UINT* iRespLen)
{
	int iRet;
	iRet  = SendData(hTermHand,ucSendDataTag,ucProcedure,ucpSendDataBuf,uiSendDataLen,CT_CheckSum);

	if (iRet == CT_OK)
		iRet =  ReceiveData( hTermHand, ucRespTag,ucRProcedure,ucpRespDataBuf ,iRespLen,CT_CheckSum); 

	return iRet;
}

int CCR5_SendCommand2Terminal(HANDLE hTermHand,BYTE *ucCommand ,UINT uiCommandLen, BYTE *ucResponse, UINT *uiResponseLen) 
{

	int iRet;
	UINT iSendNum,iSendIndex,iSendOff,iSendLen;
	UINT iRespNum,iRespIndex,iRespOff,iRespLen;
	UINT iMore;
	BYTE ucRespBuf[255];
	BYTE ucRespProcedure;


	ZeroMemory(ucRespBuf,255);

	iSendNum   = uiCommandLen/0xFE+1;
	iSendIndex = 0;
	iSendOff   = 0;
	iRespNum   = 0;
	iRespIndex = 0;
	iRespOff   = 0;
	iRespLen   = 0;
	*uiResponseLen = 0;

	ucRespProcedure = urRProcedure;
	while(iSendNum > iSendIndex)
	{
		iSendLen = (uiCommandLen - iSendOff)>0xFE?0xFE:(uiCommandLen - iSendOff);
		iMore    = (iSendNum -1) == iSendIndex ? 0x00:0x20;
		iRet     = CCR5_SendCommand2ComPort(hTermHand,0x12,ExChangeProcedure_T1(ucRespProcedure,iMore),ucCommand+iSendOff,iSendLen,0x21,&ucRespProcedure,ucResponse ,&iRespLen);
		iSendIndex += 1;
		iSendOff += 0xFE;
	}

	//需要发送一条
	if ((ucRespProcedure&0xC0)==0xC0)
	{
		memcpy(ucRespBuf,ucResponse,iRespLen);
		iSendLen = iRespLen;
		iRespLen = 0 ;
		iRet     = CCR5_SendCommand2ComPort(hTermHand,0x12,0xE3,ucRespBuf,iSendLen,0x21,&ucRespProcedure,ucResponse ,&iRespLen);
	}

	*uiResponseLen = *uiResponseLen +iRespLen;


	while(ucRespProcedure&0x20)
	{
	
		iRet     = CCR5_SendCommand2ComPort(hTermHand,0x12,ExChangeProcedure_T1(ucRespProcedure,iMore),ucRespBuf,00,0x21,&ucRespProcedure,ucResponse+*uiResponseLen ,&iRespLen);
		*uiResponseLen = *uiResponseLen +iRespLen;
	}

	urRProcedure = ucRespProcedure;
		
		
	return CT_OK;	

}


int CCR5_ResetCT_(HANDLE hTermHand,UINT uiP1,UINT uiP2,BYTE *ucResp,UINT *uiRespLen)
{

	int iRet;
	BYTE ucCommand[5];
	ucCommand[Cla] = CT_Cla_Terminal;
	ucCommand[Ins] = CT_Ins_Reset;
	ucCommand[P1]  =  uiP1;
	ucCommand[P2]  =  uiP2;
	ucCommand[P3]  =  00;

	iRet = CCR5_SendCommand2Terminal(hTermHand,ucCommand,5,ucResp,uiRespLen);

	return iRet;
}

int CCR5_RequestICC_(HANDLE hTermHand,UINT uiP2,BYTE *ucResp,UINT *uiRespLen)
{

	int iRet;
	BYTE ucCommand[5];
	ucCommand[Cla] = CT_Cla_Terminal;
	ucCommand[Ins] = CT_Ins_Request;
	ucCommand[P1]  =  01;
	ucCommand[P2]  =  uiP2;
	ucCommand[P3]  =  00;

	iRet = CCR5_SendCommand2Terminal(hTermHand,ucCommand,5,ucResp,uiRespLen);

	return iRet;
}

int CCR5_EjectICC_(HANDLE hTermHand,UINT uiP2,BYTE *ucResp,UINT *uiRespLen)
{

	int iRet;
	BYTE ucCommand[5];
	ucCommand[Cla] = CT_Cla_Terminal;
	ucCommand[Ins] = CT_Ins_Eject;
	ucCommand[P1]  =  01;
	ucCommand[P2]  =  uiP2;
	ucCommand[P3]  =  00;

	iRet = CCR5_SendCommand2Terminal(hTermHand,ucCommand,5,ucResp,uiRespLen);

	return iRet;
}

int CCR5_ResetTerminal(HANDLE hTermHand,UINT uiP1,UINT uiP2,BYTE *ucResp,UINT *uiRespLen)
{

	int iRet;
	BYTE ucCommand[5];
	ucCommand[Cla] = CT_Cla_Terminal;
	ucCommand[Ins] = CT_Ins_Reset;
	ucCommand[P1]  =  uiP1;
	ucCommand[P2]  =  uiP2;
	ucCommand[P3]  =  00;

	iRet = CCR5_SendCommand2Terminal(hTermHand,ucCommand,5,ucResp,uiRespLen);

	return iRet;
}

int CCR5_GetStatus(HANDLE hTermHand,UINT uiP2,BYTE *ucResp,UINT *uiRespLen)
{

	int iRet;
	BYTE ucCommand[5];
	ucCommand[Cla] = CT_Cla_Terminal;
	ucCommand[Ins] = CT_Ins_GetStatus;
	ucCommand[P1]  =  00;
	ucCommand[P2]  =  uiP2;
	ucCommand[P3]  =  00;

	iRet = CCR5_SendCommand2Terminal(hTermHand,ucCommand,5,ucResp,uiRespLen);

	return iRet;
}



//================================================================================


int CCR5_SetupReaderPart(HANDLE hTermHand,UINT uiP2,UINT uiP3,BYTE *ucResp,UINT *uiRespLen)
{
	int iRet;
	BYTE ucCommand[5];
	ucCommand[Cla] = CT_Cla_Card;
	ucCommand[Ins] = ICC_Ins_SURP;
	ucCommand[P1]  =  01;
	ucCommand[P2]  =  uiP2;
	ucCommand[P3]  =  uiP3;

	iRet = CCR5_SendCommand2Terminal(hTermHand,ucCommand,5,ucResp,uiRespLen);

	return iRet;
}


//p2 == 00 /01 p3 0x1F
int CCR5_SetupReaderPart1(HANDLE hTermHand,UINT uiP2,BYTE *ucResp,UINT *uiRespLen)
{
	if (uiP2>1)
		return CT_Err_P2;
	return CCR5_SetupReaderPart(hTermHand,uiP2,0x1F,ucResp,uiRespLen);
}

//p2 == 02-08 p3 0x1C
int CCR5_SetupReaderPart2(HANDLE hTermHand,UINT uiP2,BYTE *ucResp,UINT *uiRespLen)
{
	if ((uiP2<2)||(uiP2>0x8))
		return CT_Err_P2;
	return CCR5_SetupReaderPart(hTermHand,uiP2,0x1C,ucResp,uiRespLen);
}

//p2 == 0x11 p3 0x1C
int CCR5_SetupReaderPart3(HANDLE hTermHand,BYTE *ucResp,UINT *uiRespLen)
{
	return CCR5_SetupReaderPart(hTermHand,0x11,0x01,ucResp,uiRespLen);
}



int CCR5_SetupWritePart(HANDLE hTermHand,UINT uiP2,UINT uiP3,BYTE* ucPart,BYTE *ucResp,UINT *uiRespLen)
{
	int iRet;
	BYTE *ucCommand;

	ucCommand  = new BYTE[uiP3+10];
	ucCommand[Cla] = CT_Cla_Card;
	ucCommand[Ins] = ICC_Ins_SUWP;
	ucCommand[P1]  =  01;
	ucCommand[P2]  =  uiP2;
	ucCommand[P3]  =  uiP3;
	memcpy(ucCommand+5,ucPart,uiP3);
	iRet = CCR5_SendCommand2Terminal(hTermHand,ucCommand,uiP3+5,ucResp,uiRespLen);
	delete ucCommand;

	return iRet;

}

//p2 == 00 /01 p3 0x1F

int CCR5_SetupWritePart1(HANDLE hTermHand,UINT uiP2,BYTE* ucPart,BYTE *ucResp,UINT *uiRespLen)
{
	if (uiP2>1)
		return CT_Err_P2;
	return  CCR5_SetupWritePart( hTermHand, uiP2,0x1F, ucPart, ucResp, uiRespLen);
}

//p2 == 02-08 p3 0x1C
int CCR5_SetupWritePart2(HANDLE hTermHand,UINT uiP2,BYTE* ucPart,BYTE *ucResp,UINT *uiRespLen)
{
	if ((uiP2<2)||(uiP2>0x8))
		return CT_Err_P2;
	return CCR5_SetupWritePart(hTermHand, uiP2,0x1C,ucPart,ucResp,uiRespLen);
}
//p2 == 0x11 p3 0x1C
int CCR5_SetupWritePart3(HANDLE hTermHand,BYTE* ucPart,BYTE *ucResp,UINT *uiRespLen)
{
	return CCR5_SetupWritePart(hTermHand, 0x11,01,ucPart,ucResp,uiRespLen);
}



int CCR5_Sequence(HANDLE hTermHand,UINT uiP2,BYTE *ucResp,UINT *uiRespLen)
{


	int iRet;
	BYTE ucCommand[5];
	ucCommand[Cla] = CT_Cla_Card;
	ucCommand[Ins] = ICC_Ins_SS;
	ucCommand[P1]  =  01;
	ucCommand[P2]  =  uiP2;
	ucCommand[P3]  =  00;

	if ((uiP2<2)||(uiP2>0x8))
		return CT_Err_P2;

	iRet = CCR5_SendCommand2Terminal(hTermHand,ucCommand,5,ucResp,uiRespLen);

	return iRet;
}

int CCR5_GetTiming(HANDLE hTermHand,UINT uiP2,UINT uiP3,BYTE *ucResp,UINT *uiRespLen)
{
	int iRet;
	BYTE ucCommand[5];
	ucCommand[Cla] = CT_Cla_Card;
	ucCommand[Ins] = ICC_Ins_GT;
	ucCommand[P1]  =  01;
	ucCommand[P2]  =  uiP2;
	ucCommand[P3]  =  uiP3;

	if (uiP2>1)
		return CT_Err_P2;

	iRet = CCR5_SendCommand2Terminal(hTermHand,ucCommand,5,ucResp,uiRespLen);

	return iRet;



}

int CCR5_Trans(HANDLE hTermHand,UINT uiP2,UINT uiP3,BYTE*ucSend,BYTE *ucResp,UINT *uiRespLen)
{

	int iRet;
	BYTE *ucCommand;
	int iLen;

	ucCommand  = new BYTE[uiP3+7];
	ucCommand[Cla] = CT_Cla_Card;
	ucCommand[Ins] = ICC_Ins_TRAN;
	ucCommand[P1]  =  01;
	ucCommand[P2]  =  uiP2;

	if (uiP3 > 0xFF)
	{
		ucCommand[P3]  =  00;
		ucCommand[P3+1]  =  uiP3/0x100;
		ucCommand[P3+2]  =  uiP3%0x100;
		iLen = 7;
	}
	else
	{
		ucCommand[P3]  =  uiP3;
		iLen = 5;
		
	}
	memcpy(ucCommand+iLen,ucSend,uiP3);

	iRet = CCR5_SendCommand2Terminal(hTermHand,ucCommand,uiP3+iLen,ucResp,uiRespLen);
	delete ucCommand;

	return iRet;

}


int CCR5_Trans2Card(HANDLE hTermHand,BYTE*ucSend,UINT uiSendLen,
					BYTE *ucResp,UINT *uiRespLen,LONG *LTime)
{


	int iRet;
	UINT uiCyc,uiT_RespLen;
	BYTE *ucT_Send;
	BYTE ucT_Resp[600];

	uiT_RespLen = 0;

	ucT_Send = new BYTE [uiSendLen*2+10];

	ZeroMemory(ucT_Send,uiSendLen*2+10);

	*uiRespLen = 0;

	for (uiCyc = 0 ; uiCyc <uiSendLen; uiCyc++)
	{
		ucT_Send[uiCyc*2] = ucSend[uiCyc];
		ucT_Send[2*uiCyc+1] = 00;
	}


	iRet = CCR5_Trans(hTermHand,0x00,uiSendLen*2,ucT_Send, ucT_Resp,&uiT_RespLen);

	if (LTime != NULL)
		 *LTime = ucT_Resp[uiT_RespLen -5]*0x10000+ucT_Resp[uiT_RespLen-4]*0x100+ucT_Resp[uiT_RespLen-3];


	iRet = GetSW4Response(ucT_Resp,uiT_RespLen);
	if ( iRet == CT_Tran_OK)
	{
		uiT_RespLen = uiT_RespLen -5;
		for (uiCyc = 0 ; uiCyc < (uiT_RespLen / 2); uiCyc++)
		{
			if (ucT_Resp[2*uiCyc+1] == 0x80)
			{
				ucResp[*uiRespLen] = ucT_Resp[uiCyc*2];
				*uiRespLen = *uiRespLen+1;
			}
		}
	}
	return iRet;
}






//================================================================================



//uiSum 初始负值必须大于0,表示ucNumberList大小
CCR5_API BOOL _stdcall CCR5_GetList(BYTE *ucNumberList,UINT *uiSum)
{
	HANDLE hComPort ;
	BYTE ucT_ATR[0x20];
	UINT uiT_ATRLen;
	BOOL bRet;
	int iNumber;
	int iMax;
	iMax    =  *uiSum;
	iNumber = 0;
	*uiSum  = 0;


	for(int   i=1;i <=99;i++) 
	{
		hComPort = INVALID_HANDLE_VALUE;
		ZeroMemory(ucT_ATR,0x20);
		uiT_ATRLen = 0;

		bRet     = CCR5_OpenComPort(&hComPort,i,9600 ,2);
		if (bRet)
		{
			
			bRet = CCR5_GetTerminalATR(hComPort,ucT_ATR,&uiT_ATRLen);
			if (bRet)
			{
				if (iMax>iNumber)
					ucNumberList[iNumber] = i;

				iNumber ++;
			}

		}
		if (hComPort!= INVALID_HANDLE_VALUE)
		{
			bRet = Port_Close(hComPort);
			if (!bRet)
				return FALSE;
		}
	}

	*uiSum = iNumber;

	return TRUE;
}



CCR5_API int _stdcall CCR5_ConnectTerminal(HANDLE *hTermHand,UINT uiPort,BYTE *ucTermPTS,UINT uiPTSLen,
	BYTE *ucTerminalATR,UINT *uiT_ATRLen,BYTE *ucCardStatus,
	BYTE *ucManufacturer,UINT *uiM_Len)
{

	BYTE ucTempData[0xFF];
	UINT uiResLen;

	BOOL bRet;
	int  iRet;
	bRet     = CCR5_OpenComPort(hTermHand,uiPort,9600 ,2);
	if (!bRet)
		return CT_Err_OpenPort;

	ucSProcedure = 0x40;	
	urRProcedure = 0x40;

	bRet     = CCR5_GetTerminalATR(*hTermHand,ucTerminalATR,uiT_ATRLen);
	if (!bRet)
		return CT_Err_GetT_ATR;

	bRet     = CCR5_SetTerminalPTS(*hTermHand,ucTermPTS,uiPTSLen,ucTempData,&uiResLen);
	if (!bRet)
		return CT_Err_SendT_PTS;

	if (memcmp(ucTermPTS,ucTempData,uiResLen)==0)
		bRet = CCR5_SetTerminalTransmissionParameter(*hTermHand,ucTempData,uiResLen);
	if (!bRet)
		return CT_Err_SetT_PTS;


	iRet = CCR5_GetStatus(*hTermHand,0x81,ucTempData,&uiResLen);
	if (iRet != CT_OK)
		return iRet+CT_Err_GetStatus;

	iRet =CCR5_GetStatus(*hTermHand,0x80,ucTempData,&uiResLen);

	if (iRet != CT_OK)
		return iRet+CT_Err_GetStatus;

	if (GetSW4Response(ucTempData,uiResLen) == CT_Tran_OK)
		memcpy(ucCardStatus,ucTempData,1);

	iRet = CCR5_GetStatus(*hTermHand,0x46,ucTempData,&uiResLen);
	if (iRet != CT_OK)
		return iRet+CT_Err_GetStatus;

	iRet =GetSW4Response(ucTempData,uiResLen);
	if ( iRet == CT_Tran_OK)
		memcpy(ucManufacturer,ucTempData,uiResLen-2);

	return iRet;
}

CCR5_API int _stdcall CCR5_DisConnectTerminal(HANDLE hTermHand)
{
	return Port_Close(hTermHand);
}

CCR5_API int _stdcall CCR5_SetupTerminal2Default(HANDLE hTermHand)
{


	BYTE ucPart1[0x30] = {"\x0C\x80\x07\x08\x01\x74\x00\x4b\x00\x00\x25\x80\x00\x00\x2d\x00\x35\x20\x83\x10\x14\x00\xc8\x00\x64\x00\x32\x00\xc8\x04\x4c"};
	BYTE ucResBuf[0x30];
	UINT uiResLen;
	int iRet;

	iRet = CCR5_SetupWritePart1(hTermHand,01,ucPart1,ucResBuf,&uiResLen);
	if (iRet != CT_OK)
		return iRet+CT_Err_SetupWrite;

	iRet = GetSW4Response(ucResBuf,uiResLen);
	if ( iRet != CT_Tran_OK)
		return iRet;


	iRet = CCR5_SetupReaderPart1(hTermHand,00,ucResBuf,&uiResLen);
	if (iRet != CT_OK)
		return iRet+CT_Err_SetupRead;

	iRet = GetSW4Response(ucResBuf,uiResLen);
	if ( iRet != CT_Tran_OK)
		return iRet;



	iRet = CCR5_SetupReaderPart2(hTermHand,02,ucResBuf,&uiResLen);
	if (iRet != CT_OK)
		return iRet+CT_Err_SetupRead;

	iRet = GetSW4Response(ucResBuf,uiResLen);
	if ( iRet != CT_Tran_OK)
		return iRet;


	ZeroMemory(ucPart1,0x1F);
	memcpy(ucPart1,ucResBuf,0x1C);

	iRet = CCR5_SetupWritePart2(hTermHand,02,ucPart1,ucResBuf,&uiResLen);
	if (iRet != CT_OK)
		return iRet+CT_Err_SetupWrite;

	iRet = GetSW4Response(ucResBuf,uiResLen);
	if ( iRet != CT_Tran_OK)
		return iRet;



	iRet = CCR5_SetupReaderPart2(hTermHand,04,ucResBuf,&uiResLen);
	if (iRet != CT_OK)
		return iRet+CT_Err_SetupRead;

	iRet = GetSW4Response(ucResBuf,uiResLen);
	if ( iRet != CT_Tran_OK)
		return iRet;		


	ZeroMemory(ucPart1,0x1F);
	memcpy(ucPart1,ucResBuf,0x1C);

	iRet = CCR5_SetupWritePart2(hTermHand,04,ucPart1,ucResBuf,&uiResLen);
		if (iRet != CT_OK)
			return iRet+CT_Err_SetupWrite;

	iRet = GetSW4Response(ucResBuf,uiResLen);
	if ( iRet != CT_Tran_OK)
		return iRet;


	iRet = CCR5_SetupReaderPart3(hTermHand,ucResBuf,&uiResLen);
	if (iRet != CT_OK)
		return iRet+CT_Err_SetupRead;

	iRet = GetSW4Response(ucResBuf,uiResLen);
	if ( iRet != CT_Tran_OK)
		return iRet;


	ZeroMemory(ucPart1,0x1F);
	memcpy(ucPart1,ucResBuf,0x1C);

	iRet = CCR5_SetupWritePart3(hTermHand,ucPart1,ucResBuf,&uiResLen);
		if (iRet != CT_OK)
			return iRet+CT_Err_SetupWrite;

	iRet = GetSW4Response(ucResBuf,uiResLen);

	return iRet;

}

CCR5_API int _stdcall CCR5_SetPTS2Terminal(HANDLE hTermHand,UINT uiCFactor)
{



	BYTE ucPart1[0x34] ;
	UINT uiPart1Len;

	BYTE ucResBuf[10] ;
	UINT uiResLen;

	int iRet;

	iRet = CCR5_SetupReaderPart1(hTermHand,00,ucPart1,&uiPart1Len);
	if (iRet != CT_OK)
		return iRet+CT_Err_SetupRead;

	iRet = GetSW4Response(ucPart1,uiPart1Len);
	if ( iRet != CT_Tran_OK)
		return 0-iRet;

	uiPart1Len = uiPart1Len -2;

	ucPart1[Fac_H] = uiCFactor/0x100;
	ucPart1[Fac_L] = uiCFactor%0x100;

	ucPart1[18] = ucPart1[18]|0x04;

	iRet = CCR5_SetupWritePart1(hTermHand,01,ucPart1,ucResBuf,&uiResLen);
	if (iRet != CT_OK)
		return iRet+CT_Err_SetupWrite;

	iRet = GetSW4Response(ucResBuf,uiResLen);

	return iRet;

}


CCR5_API int _stdcall CCR5_PowerOnCard(HANDLE hTermHand,BYTE *ucCardStatus,BYTE*ucCardATR,
									   UINT *uiATRLen,LONG *LTime)
{
	BYTE ucResBuf[0x7F];
	UINT uiResLen;
	int iRet;

	iRet = CCR5_GetStatus(hTermHand,0x80,ucResBuf,&uiResLen);
	if (iRet != CT_OK)
		return iRet+CT_Err_GetStatus;

	if ((GetSW4Response(ucResBuf,uiResLen) == CT_Tran_OK)&&(ucCardStatus!=NULL))
		*ucCardStatus = ucResBuf[0];

	switch(ucResBuf[0])
	{
	case  Statuse_OnVol:

		iRet = CCR5_Sequence(hTermHand,03,ucResBuf,&uiResLen);

		if (iRet != CT_OK)
			return iRet+CT_Err_GetStatus;
		if (GetSW4Response(ucResBuf,uiResLen) != CT_Tran_OK)
			return FALSE;
	case Statuse_NoCar:
	case Statuse_Ready:

		iRet = CCR5_Sequence(hTermHand,02,ucResBuf,&uiResLen);

		if (iRet != CT_OK)
			return iRet+CT_Err_GetStatus;
		if (GetSW4Response(ucResBuf,uiResLen) != CT_Tran_OK)
			return FALSE;

		if (LTime!= NULL)
			*LTime = ucResBuf[1]*0x10000+ucResBuf[2]*0x100+ucResBuf[3];

		GetCardResp4T_Resp(ucResBuf+4,uiResLen-5,ucCardATR,uiATRLen);

		break;


	case Statuse_NoCon:
	default:
		return FALSE;
		break;

	}


	iRet = CCR5_GetStatus(hTermHand,0x80,ucResBuf,&uiResLen);
	if (iRet != CT_OK)
		return iRet+CT_Err_GetStatus;

	if ((GetSW4Response(ucResBuf,uiResLen) == CT_Tran_OK)&&(ucCardStatus!=NULL))
		*ucCardStatus = ucResBuf[0];


	if (( ucResBuf[0] == Statuse_OnVol)||( ucResBuf[0] == Statuse_NoCar))
		return TRUE;
	else
		return FALSE;

}

CCR5_API int _stdcall CCR5_PowerOffCard(HANDLE hTermHand)
{

	BYTE ucResBuf[0x7F];
	UINT uiResLen;
	int iRet;

	uiResLen = 0;

	iRet = CCR5_Sequence(hTermHand,03,ucResBuf,&uiResLen);

	if (iRet != CT_OK)
		return iRet+CT_Err_GetStatus;

    iRet = GetSW4Response(ucResBuf,uiResLen);
	if (iRet != CT_Tran_OK)
		return iRet;

	iRet = CCR5_SetPTS2Terminal(hTermHand,372);

	return iRet;

}

CCR5_API int _stdcall CCR5_ResetCard(HANDLE hTermHand,BYTE *ucCardStatus,BYTE*ucCardATR,
	UINT *uiATRLen,LONG *LTime)
{

	BYTE ucResBuf[0x7F];
	UINT uiResLen;
	int iRet;


	iRet = CCR5_GetStatus(hTermHand,0x80,ucResBuf,&uiResLen);
	if (iRet != CT_OK)
		return iRet+CT_Err_GetStatus;

	if ((GetSW4Response(ucResBuf,uiResLen) == CT_Tran_OK)&&(ucCardStatus!=NULL))
		*ucCardStatus = ucResBuf[0];

	switch(ucResBuf[0])
	{
	case  Statuse_NoCar:
	case  Statuse_OnVol:
	case  Statuse_Ready:
		iRet = CCR5_SetPTS2Terminal(hTermHand,372);

		iRet = CCR5_Sequence(hTermHand,04,ucResBuf,&uiResLen);

		if (iRet != CT_OK)
			return iRet+CT_Err_GetStatus;
		if (GetSW4Response(ucResBuf,uiResLen) != CT_Tran_OK)
			return FALSE;

		if (LTime!= NULL)
			*LTime = ucResBuf[1]*0x10000+ucResBuf[2]*0x100+ucResBuf[3];
		
		GetCardResp4T_Resp(ucResBuf+4,uiResLen-5,ucCardATR,uiATRLen);

	case Statuse_NoCon:
	default:
		return FALSE;
		break;


		break;

	}



	iRet = CCR5_GetStatus(hTermHand,0x80,ucResBuf,&uiResLen);
	if (iRet != CT_OK)
		return iRet+CT_Err_GetStatus;

	if ((GetSW4Response(ucResBuf,uiResLen) == CT_Tran_OK)&&(ucCardStatus!=NULL))
		*ucCardStatus = ucResBuf[0];

	if (( ucResBuf[0] == Statuse_OnVol)||( ucResBuf[0] == Statuse_NoCar))
		return TRUE;
	else
		return FALSE;

}

CCR5_API int _stdcall CCR5_SendPTS2Card(HANDLE hTermHand,BYTE* ucPTS,UINT uiPTSLen,BYTE* ucRes,UINT *uiResLen)
{


	int iRet;
	UINT uiCFactor;



	iRet = CCR5_Trans2Card(hTermHand,ucPTS,uiPTSLen,ucRes,uiResLen,NULL);

	if (memcmp(ucPTS,ucRes,*uiResLen)== 0)
	{



		switch(ucPTS[2])
		{	

		case(0x01):  uiCFactor = 372;	break;	/* 372/1 */		/* 9600    */   /* 13.4K	*/
		case(0x11):  uiCFactor = 372;	break;	/* 372/1 */		/* 9600    */   /* 13.4K	*/
		case(0x32):  uiCFactor = 372;	break;
		case(0x53):  uiCFactor = 372;	break;
		case(0x22):  uiCFactor = 279;	break;	/* 558/2 */		/*    */    /*	*/
		case(0x43):  uiCFactor = 279;	break;	
		case(0x92):  uiCFactor = 256;	break;	/* 512/2 */		/* 13.9K   */    /* 19.5K	*/
		case(0xB3):  uiCFactor = 256;	break;
		case(0xD4):  uiCFactor = 256;	break;
		case(0xA3):  uiCFactor = 192;	break;	/* 18.6K   */    /* 26K	*/
		case(0xC4):  uiCFactor = 192;	break;
		case(0x02):  uiCFactor = 186;	break;	/* 372/2 */     /* 19.2K   */   /* 26.8K	*/
		case(0x12):  uiCFactor = 186;	break;	
		case(0x33):  uiCFactor = 186;	break;
		case(0x54):  uiCFactor = 186;	break;
		case(0x93):  uiCFactor = 128;	break;	/* 512/4 */     /* 27.9K   */   /* 39.1K	*/
		case(0xB4):  uiCFactor = 128;	break;
		case(0xC8):  uiCFactor = 128;	break;
		case(0xD5):  uiCFactor = 128;	break;
		case(0xA4):  uiCFactor = 96;		break;	/* 744/8 */     /* 37.2K   */   /* 52K	*/		
		case(0xC5):  uiCFactor = 96;		break;
		case(0x03):  uiCFactor = 93;		break; 	/* 372/4 */		/* 38.4K   */   /* 53.6K */
		case(0x13):  uiCFactor = 93;		break; 	
		case(0x34):  uiCFactor = 93;		break;
		case(0x48):  uiCFactor = 93;		break;
		case(0x55):  uiCFactor = 93;		break;
		case(0x69):  uiCFactor = 93;		break;
		case(0x94):  uiCFactor = 64;		break;	/* 512/8 */     /* 55.8K   */   /* 78.1K	*/	
		case(0xA8):  uiCFactor = 64;		break;
		case(0xB5):  uiCFactor = 64;		break;
		case(0xD6):  uiCFactor = 64;		break;
		case(0x38):  uiCFactor = 62;		break;	/* 744/12 */     /* 57.6K   */   /* 80.6K	*/
		case(0xA5):  uiCFactor = 48;		break;	/* 744/16 */     /* 74.4K   */   /* 104.2K	*/
		case(0xC6):  uiCFactor = 48;		break;
		case(0x95):  uiCFactor = 32;		break;	/* 512/16 */     /* 111.6   */   /* 156.3K	*/	
		case(0xB6):  uiCFactor = 32;		break;
		case(0xD7):  uiCFactor = 32;		break;
		case(0x08):  uiCFactor = 31;		break;  /* 372/12 */     /* 115.2K   */   /* 161.2K	*/
		case(0x18):  uiCFactor = 31;		break;  
		case(0xA6):  uiCFactor = 24;		break;	/* 744/32 */     /* 148.65K  */   /* 208.3K	*/
		case(0xC7):  uiCFactor = 24;		break;
		case(0x96):  uiCFactor = 16;		break;	/* 512/32 */     /* 223.1K   */   /* 312.5K	*/
		case(0xB7):  uiCFactor = 16;		break;
		case(0xA7):  uiCFactor = 12;		break;	/* 744/64 */     /* 297.5K   */   /* 416.7K	*/
		case(0x97):  uiCFactor = 8;		    break;	/* 512/64 */
		default: uiCFactor = 0;return FALSE;
		}



		iRet = CCR5_SetPTS2Terminal (hTermHand,uiCFactor);

	}

	return iRet;
}

CCR5_API int _stdcall CCR5_Send2Card(HANDLE hTermHand,BYTE* ucSend,UINT uiSendLen,
	BYTE* ucRes,UINT *uiResLen,LONG *LTime,BOOL bProByte)
{
	int iRet;
	UINT ui;

	iRet = CCR5_Trans2Card(hTermHand,ucSend,uiSendLen,ucRes,uiResLen,LTime);

	if (iRet == CT_Tran_OK)
	{
		ui = 0;
		//Case 01
		//Case 02
		if (!bProByte)
		{
			if ((uiSendLen == 5)&&(*uiResLen>2))
			{
				while(ucRes[ui] == 0x60)
					ui++;
				if (ucRes[ui] == ucSend[Ins])
					ui+=1;
			}

			//Case 03
			//Case 04
			if ((uiSendLen > 5)&&(*uiResLen>2))
			{

				while(ucRes[ui] == 0x60)
					ui++;
				if (ucRes[ui] == ucSend[Ins])
					ui+=1;
				while(ucRes[ui] == 0x60)
					ui++;
			}
			*uiResLen = *uiResLen - ui;
			memcpy( ucRes,ucRes+ui,*uiResLen);
		}
	}


	//if ((uiSendLen>=5)&&(ucSend[P3]!=00)&&(*uiResLen!=2))
	//{
	//	if (((*uiResLen)>(ucSend[P3]+2))&&(!bProByte))
	//		memcpy( ucRes,ucRes+(*uiResLen-2- *uiResLen),*uiResLen);	
	//}

	return iRet;
}

CCR5_API  int _stdcall CCR5_GetTerminalSetting(HANDLE hTermHand,UINT uiP2,BYTE* ucSetting,UINT* uiSettingLen)
{
	int iRet;

	iRet = CCR5_SetupReaderPart(hTermHand,uiP2,00,ucSetting,uiSettingLen);

	if (iRet != CT_OK)
		return iRet+CT_Err_SetupRead;

	iRet = GetSW4Response(ucSetting,*uiSettingLen);

	return iRet;
}

CCR5_API  int _stdcall CCR5_RequestICC(HANDLE hTermHand,UINT uiP2,BYTE *ucResp,UINT *uiRespLen)
{
	int iRet;

	iRet = CCR5_RequestICC_(hTermHand,uiP2,ucResp,uiRespLen);


	if (iRet != CT_OK)
		return iRet+ICC_Request;

	iRet = GetSW4Response(ucResp,*uiRespLen);

	return iRet;


}

CCR5_API  int _stdcall CCR5_EjectICC(HANDLE hTermHand,UINT uiP2,BYTE *ucResp,UINT *uiRespLen)
{
	int iRet;

	iRet = CCR5_EjectICC_(hTermHand,uiP2,ucResp,uiRespLen);


	if (iRet != CT_OK)
		return iRet+ICC_Eject;

	iRet = GetSW4Response(ucResp,*uiRespLen);

	return iRet;
}

CCR5_API int _stdcall CCR5_SetTerminalSetting(HANDLE hTermHand,UINT uiPart,UINT uiP2,BYTE* ucSetting,UINT uiSettingLen)
{
	int iRet;

	BYTE ucResBuf[10] ;
	UINT uiResLen;

	ZeroMemory(ucResBuf,10);
	uiResLen = 0;

	switch(uiPart)
	{
	case 01:
		if (uiSettingLen >= 0x1F)
			iRet = CCR5_SetupWritePart1(hTermHand,uiP2,ucSetting,ucResBuf,&uiResLen);
		break;	
	case 02:
		if (uiSettingLen >= 0x1C)
			iRet = CCR5_SetupWritePart2(hTermHand,uiP2,ucSetting,ucResBuf,&uiResLen);
		break;
	case 03:
		if (uiSettingLen >= 01)
			iRet = CCR5_SetupWritePart3(hTermHand,ucSetting,ucResBuf,&uiResLen);
		break;
	default:break;
	}

	iRet = GetSW4Response(ucResBuf,uiResLen);

	return iRet;

}

CCR5_API int _stdcall CCR5_GetCardStatus( HANDLE hTermHand )
{
	int iRet;
	BYTE ucResBuf[10] ;
	UINT uiResLen;
	iRet = CCR5_GetStatus(hTermHand,0x80,ucResBuf,&uiResLen);
	if (iRet != CT_OK)
		return iRet+CT_Err_GetStatus;
	else
		return ucResBuf[0];

}