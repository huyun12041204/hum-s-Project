
// PcscReader.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include "PcscReader.h"


#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
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

#ifdef _MANAGED
#pragma managed(pop)
#endif

int CPcscReader::GetContext()
{
	DWORD lRet = ::SCardEstablishContext(SCARD_SCOPE_USER, NULL, NULL, &m_pContext);

	if (lRet != SCARD_S_SUCCESS)
		return 0;
	else 
		return 1;
}

int CPcscReader::GetPcsclist( LPTSTR *szReaderName)
{
	int iReaderSum;
	LPTSTR szListReader;
	DWORD lRet;

	DWORD dwReadersLength = 1000;
	szListReader = (LPTSTR)new char[dwReadersLength];
	memset(szListReader,0,dwReadersLength);
	iAutoResponse = 0;
	lRet = SCardListReaders(m_pContext, NULL, szListReader, &dwReadersLength);
	if (lRet != SCARD_S_SUCCESS)
	{
		delete szListReader;
		return 0;
	}
	iReaderSum = 0;
	while(*szListReader != 0)
	{
		szReaderName[iReaderSum] = szListReader;
		szListReader = szListReader + lstrlen(szListReader) + 1;
		iReaderSum++;
	}
	return iReaderSum;
}



int CPcscReader::ConnectReader(LPTSTR szReaderName)
{
	DWORD lRet;
	//	lRet = SCardDisconnect(m_pContext, SCARD_UNPOWER_CARD); 
	lRet = SCardConnect(m_pContext,szReaderName,SCARD_SHARE_SHARED,
		SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,	
		&m_pcscHandle,	&dwProtocol);
	if (lRet != SCARD_S_SUCCESS)
		return 1;
	return 0;
}

int CPcscReader::DisConnectReader()
{
	return SCardDisconnect(m_pcscHandle, SCARD_UNPOWER_CARD); 	
}

int CPcscReader::ResetCard(int iMod)
{
	DWORD lRet;
	lRet = SCardReconnect(m_pcscHandle,SCARD_SHARE_SHARED,
		SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1,iMod,&dwProtocol);

	if (lRet!= SCARD_S_SUCCESS)
	{
		return 1;
	}
	return 0;
}




int CPcscReader::GetCardATR(unsigned char *ucATR)
{
	DWORD lRet;
	DWORD ReaderLen,ATRLen,CardStatuse;
	LPSTR szReader;
	ATRLen = 100;
	ReaderLen = 100;

	lRet = SCardStatus(m_pcscHandle,NULL,&ReaderLen,&CardStatuse,&dwProtocol,NULL,&ATRLen);


	szReader = (LPSTR)new char[ReaderLen];
	ZeroMemory(szReader,ReaderLen);
	lRet = SCardStatus(m_pcscHandle,szReader,&ReaderLen,&CardStatuse,&dwProtocol,ucATR,&ATRLen);
	if (lRet != SCARD_S_SUCCESS)
		return 0;

	return ATRLen;
}

int CPcscReader::SendCommand(LPCBYTE lpSend,int iSendLength, unsigned char* ucResponse)
{
	DWORD lRet;
	unsigned long  ulResLen = 258;
	iSendLen = iSendLength;

	switch(dwProtocol)
	{
	case SCARD_PROTOCOL_T0:
		if ((iSendLength!=5)&&(lpSend[4]!=iSendLength-5))
			iSendLength = lpSend[4]+5;

			
		lRet = ::SCardTransmit(m_pcscHandle,SCARD_PCI_T0, lpSend, iSendLen, NULL, ucResponse, &ulResLen);
		break;
	case SCARD_PROTOCOL_T1:
		lRet = ::SCardTransmit(m_pcscHandle,SCARD_PCI_T1, lpSend, iSendLen, NULL, ucResponse, &ulResLen);
		break;
	default:
		break;

	}

	if (lRet != SCARD_S_SUCCESS)
	{
		return 0;
	}
	return ulResLen;
}


int CPcscReader::SendCommand(unsigned char* ucpSend,int iSendLength, unsigned char* ucResponse,int* iResLen)
{


	InitParameter();

	memcpy(ucSend,ucpSend,iSendLength);

	iResponseLen = SendCommand(ucSend,iSendLength,ucResponse);

	*iResLen = iResponseLen;

	PostParameter();
	return iResponseLen;

}


void CPcscReader::InitParameter(void)
{
	ZeroMemory(ucSend,300);
	ZeroMemory(ucResponse,300);
	
}

void CPcscReader::PostParameter(void)
{
	ucSW[0] = ucResponse[iResponseLen-2];
	ucSW[1] = ucResponse[iResponseLen-1];
	// For Auto get response
	if (iAutoResponse)
	{	if (ucSW[0] == 0x9f)
			iResponseLen = GetResponse_GSM(ucSW[1]);
	    if (ucSW[0] == 0x61)
		    iResponseLen = GetResponse_UICC(ucSW[1]);


	}
}


bool CPcscReader::SetAutoGetResponse(int iAuto)
{

	iAutoResponse = iAuto;
	return true;
}

int CPcscReader::GetLastResponse(unsigned char *ucRec)
{

	if ((iResponseLen < 2)||(iResponseLen >300))
	{
//		memcpy(ucRec,ucResponse,iResponseLen);
		return 0;

	}
	memcpy(ucRec,ucResponse,iResponseLen-2);
	return iResponseLen-2;
}

int CPcscReader::GetLastSW(unsigned char *ucLSW)
{

	if ((iResponseLen<2)||(iResponseLen>300))
	{
		return 0;
	}
	memcpy(ucLSW,ucSW,2);
	return ucLSW[0]*0x100+ucLSW[1];
}

int CPcscReader::GetLastSend(unsigned char *ucLSend)
{

	memcpy(ucLSend,ucSend,iSendLen);

	return iSendLen;
}




int CPcscReader::Select_GSM(int iFid)
{
	InitParameter();
	ucSend[Cla] = 0xA0;
	ucSend[Ins] = 0xA4;
	ucSend[P1 ] = 0x00;
	ucSend[P2 ] = 0x00;
	ucSend[P3 ] = 0x02;
	ucSend[CmdData]   = iFid/0x100;
	ucSend[CmdData+1] = iFid%0x100;
	iResponseLen= SendCommand (ucSend,05+ucSend[P3 ],ucResponse);
	PostParameter();
	return iResponseLen;

}

int CPcscReader::GetResponse_GSM(int iReslen)
{
	InitParameter();
	ucSend[Cla] = 0xA0;
	ucSend[Ins] = 0xC0;
	ucSend[P1 ] = 0x00;
	ucSend[P2 ] = 0x00;
	ucSend[P3 ] = iReslen%100;
	iResponseLen= SendCommand (ucSend,05,ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::ReadBinary_GSM(int iP1 = 00, int iP2 = 00,int iP3 = 00)
{

	InitParameter();
	ucSend[Cla] = 0xA0;
	ucSend[Ins] = 0xB0;
	ucSend[P1 ] = iP1;
	ucSend[P2 ] = iP2;
	ucSend[P3 ] = iP3;
	iResponseLen= SendCommand (ucSend,05,ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::ReadRecord_GSM(int iP1 = 00, int iP2 = 00,int iP3 = 00)
{

	InitParameter();
	ucSend[Cla] = 0xA0;
	ucSend[Ins] = 0xB2;
	ucSend[P1 ] = iP1;
	ucSend[P2 ] = iP2;
	ucSend[P3 ] = iP3;
	iResponseLen= SendCommand (ucSend,05,ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::Verify_GSM(int iP2,int iP3,LPCBYTE ucPin)
{
	InitParameter();
	ucSend[Cla] = 0xA0;
	ucSend[Ins] = 0x20;
	ucSend[P1 ] = 00;
	ucSend[P2 ] = iP2;
	ucSend[P3 ] = iP3;
	for (int i = 0 ; i < iP3 ;i++)
	{
		ucSend[i+5] = ucPin[i];
	}
	iResponseLen= SendCommand (ucSend,05+ucSend[P3 ],ucResponse);
	PostParameter();
	return iResponseLen;
}


int CPcscReader::Select_UICC(int iP1,int iP2,int iP3,LPCBYTE ucData)
{
	InitParameter();
	ucSend[Cla] = 0x00;
	ucSend[Ins] = 0xA4;
	ucSend[P1 ] = iP1;
	ucSend[P2 ] = iP2;
	ucSend[P3 ] = iP3;
	for (int i = 0 ; i < iP3 ;i++)
	{
		ucSend[i+5] = ucData[i];
	}

	iResponseLen= SendCommand (ucSend,05+ucSend[P3 ],ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::Select_UICC_FID(LPCBYTE ucFID)
// 此处会有返回结果，并非只返回9000 P2为04
{	
	return Select_UICC(0x00,0x04,0x02,ucFID);
}
int CPcscReader::Select_UICC_AID(LPCBYTE ucAID,int iAIDLength)
// 此处会有返回结果，并非只返回9000 P2为04
{	
	return Select_UICC(0x04,0x04,iAIDLength,ucAID);
}

int CPcscReader::Select_UICC_ChildDF(LPCBYTE ucFID)
// 此处会有返回结果，并非只返回9000 P2为04
{	
	return Select_UICC(0x01,0x04,0x02,ucFID);
}
int CPcscReader::Select_UICC_ParentDF( )
// 此处会有返回结果，并非只返回9000 P2为04
{	
	return Select_UICC(0x03,0x04,0x00,NULL);
}

int CPcscReader::GetResponse_UICC(int iReslen)
{
	InitParameter();
	ucSend[Cla] = 0x00;
	ucSend[Ins] = 0xC0;
	ucSend[P1 ] = 0x00;
	ucSend[P2 ] = 0x00;
	ucSend[P3 ] = iReslen%0x100;
	iResponseLen= SendCommand (ucSend,05,ucResponse);
	PostParameter();
	return iResponseLen;

}


int CPcscReader::ReadBinary_UICC(int iP1 = 00, int iP2 = 00,int iP3 = 00)
{

	InitParameter();
	ucSend[Cla] = 0x00;
	ucSend[Ins] = 0xB0;
	ucSend[P1 ] = iP1;
	ucSend[P2 ] = iP2;
	ucSend[P3 ] = iP3;
	iResponseLen= SendCommand (ucSend,05,ucResponse);
	PostParameter();
	return iResponseLen;
}


int CPcscReader::ReadRecord_UICC(int iP1 = 00, int iP2 = 00,int iP3 = 00)
{

	InitParameter();
	ucSend[Cla] = 0x00;
	ucSend[Ins] = 0xB2;
	ucSend[P1 ] = iP1;
	ucSend[P2 ] = iP2;
	ucSend[P3 ] = iP3;
	iResponseLen= SendCommand (ucSend,05,ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::Verify_UICC(int iP2,int iP3,LPCBYTE ucPin)
{
	InitParameter();
	ucSend[Cla] = 0x00;
	ucSend[Ins] = 0x20;
	ucSend[P1 ] = 00;
	ucSend[P2 ] = iP2;
	ucSend[P3 ] = iP3;
	for (int i = 0 ; i < iP3 ;i++)
	{
		ucSend[i+5] = ucPin[i];
	}
	iResponseLen= SendCommand (ucSend,05+ucSend[P3 ],ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::UpdateRecord_UICC(int iP1, int iP2, int iP3, unsigned char* ucData)
{
	InitParameter();
	ucSend[Cla] = 0x00;
	ucSend[Ins] = 0xDC;
	ucSend[P1 ] = iP1;
	ucSend[P2 ] = iP2;
	ucSend[P3 ] = iP3;
	for (int i = 0 ; i < iP3 ;i++)
	{
		ucSend[i+5] = ucData[i];
	}

	iResponseLen= SendCommand (ucSend,ucSend[P3 ]+05,ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::Set_SM1_Key(unsigned char *ucKey,int iKeyLen)
{
	InitParameter();
	ucSend[Cla] = 00;
	ucSend[Ins] = 0x40;
	ucSend[P1 ] = 01;
	ucSend[P2 ] = 00;
	ucSend[P3 ] = iKeyLen;
	for (int i = 0 ; i < iKeyLen ;i++)
	{
		ucSend[i+5] = ucKey[i];
	}
	iResponseLen= SendCommand (ucSend,05+ucSend[P3 ],ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::Set_SM1_Encrypt(unsigned char *ucData,int iDataLen)
{
	InitParameter();
	ucSend[Cla] = 00;
	ucSend[Ins] = 0x40;
	ucSend[P1 ] = 0x04;
	ucSend[P2 ] = 00;
	ucSend[P3 ] = iDataLen;
	for (int i = 0 ; i < iDataLen ;i++)
	{
		ucSend[i+5] = ucData[i];
	}
	iResponseLen= SendCommand (ucSend,05+ucSend[P3 ],ucResponse);
	PostParameter();
	return iResponseLen;
}



int CPcscReader::Set_SSF33_SKey(unsigned char *ucKey,int iKeyLen)
{
	InitParameter();
	ucSend[Cla] = 00;
	ucSend[Ins] = 0x42;
	ucSend[P1 ] = 01;
	ucSend[P2 ] = 00;
	ucSend[P3 ] = iKeyLen;
	for (int i = 0 ; i < iKeyLen ;i++)
	{
		ucSend[i+5] = ucKey[i];
	}
	iResponseLen= SendCommand (ucSend,05+ucSend[P3 ],ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::Set_SSF33_MKey(unsigned char *ucKey,int iKeyLen)
{
	InitParameter();
	ucSend[Cla] = 00;
	ucSend[Ins] = 0x42;
	ucSend[P1 ] = 02;
	ucSend[P2 ] = 00;
	ucSend[P3 ] = iKeyLen;
	for (int i = 0 ; i < iKeyLen ;i++)
	{
		ucSend[i+5] = ucKey[i];
	}
	iResponseLen= SendCommand (ucSend,05+ucSend[P3 ],ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::Set_SSF33_Encrypt(unsigned char *ucData,int iDataLen)
{
	InitParameter();
	ucSend[Cla] = 00;
	ucSend[Ins] = 0x42;
	ucSend[P1 ] = 0x03;
	ucSend[P2 ] = 00;
	ucSend[P3 ] = iDataLen;
	for (int i = 0 ; i < iDataLen ;i++)
	{
		ucSend[i+5] = ucData[i];
	}
	iResponseLen= SendCommand (ucSend,05+ucSend[P3 ],ucResponse);
	PostParameter();
	return iResponseLen;
}
int CPcscReader::Set_SSF33_Decrypt(unsigned char *ucData,int iDataLen)
{
	InitParameter();
	ucSend[Cla] = 00;
	ucSend[Ins] = 0x42;
	ucSend[P1 ] = 0x04;
	ucSend[P2 ] = 00;
	ucSend[P3 ] = iDataLen;
	for (int i = 0 ; i < iDataLen ;i++)
	{
		ucSend[i+5] = ucData[i];
	}
	iResponseLen= SendCommand (ucSend,05+ucSend[P3 ],ucResponse);
	PostParameter();
	return iResponseLen;
}



int CPcscReader::Mif_Authenticate(int iMSB,int iLSB,int iKeyType,int iKeyNum)
{
	InitParameter();
	
	ucSend[Cla] = 0xFF;
	ucSend[Ins] = 0x86;
	ucSend[P1 ] = 0x00;
	ucSend[P2 ] = 0x00;
	ucSend[P3 ] = 0x05;
	ucSend[P3+1] = 0x01;
	ucSend[P3+2] = iMSB;
	ucSend[P3+3] = iLSB;
	ucSend[P3+4] = iKeyType;
	ucSend[P3+5] = iKeyNum;
	iResponseLen= SendCommand (ucSend,05+ucSend[P3 ],ucResponse);
	PostParameter();
	return iResponseLen;

}

int CPcscReader::Mif_GetReponse(int iReslen)
{
	InitParameter();
	ucSend[Cla] = 0x00;
	ucSend[Ins] = 0xC0;
	ucSend[P1 ] = 0x00;
	ucSend[P2 ] = 0x00;
	ucSend[P3 ] = iReslen%0x100;
	iResponseLen= SendCommand (ucSend,05,ucResponse);
	PostParameter();
	return iResponseLen;

}


int CPcscReader::Mif_SelectISD_Unicom(void)
{
	unsigned char ucUnicom[7] ={0xA0,0x00,0x00,0x01,0x51,0x00,0x00};
    return Select_UICC(04,00,07 ,ucUnicom);
}



int CPcscReader::Mif_GetChallenge(int iLength)
{
	InitParameter();
	ucSend[Cla] = 0x00;
	ucSend[Ins] = 0x84;
	ucSend[P1 ] = 0x00;
	ucSend[P2 ] = 0x00;
	ucSend[P3 ] = iLength;
	iResponseLen= SendCommand (ucSend,05,ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::Mif_DeleteOS(void)
{
	InitParameter();
	ucSend[Cla] = 0x90;
	ucSend[Ins] = 0xBC;
	ucSend[P1 ] = 0x36;
	ucSend[P2 ] = 0xAA;
	ucSend[P3 ] = 0x01;
	iResponseLen= SendCommand (ucSend,05,ucResponse);
	PostParameter();
	return iResponseLen;
}


int CPcscReader::Mif_OpenChannel(void)
{
	InitParameter();
	ucSend[Cla] = 0x00;
	ucSend[Ins] = 0x70;
	ucSend[P1 ] = 0x00;
	ucSend[P2 ] = 0x00;
	ucSend[P3 ] = 0x01;
	iResponseLen= SendCommand (ucSend,05,ucResponse);
	PostParameter();
	return iResponseLen;
}
int CPcscReader::Mif_CloseChannel(void)
{
	InitParameter();
	ucSend[Cla] = 0x00;
	ucSend[Ins] = 0x70;
	ucSend[P1 ] = 0x80;
	ucSend[P2 ] = 0x01;
	ucSend[P3 ] = 0x00;
	iResponseLen= SendCommand (ucSend,05,ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::Mif_GetUid()
{
	InitParameter();
	ucSend[Cla] = 0xFF;
	ucSend[Ins] = 0xCA;
	ucSend[P1 ] = 0x00;
	ucSend[P2 ] = 0x00;
	ucSend[P3 ] = 0x00;
	iResponseLen= SendCommand (ucSend,05,ucResponse);
	PostParameter();
	return iResponseLen;

}


int CPcscReader::Mif_ReadBinary(int iP1, int iP2,int iP3)
{
	InitParameter();
	ucSend[Cla] = 0xFF;
	ucSend[Ins] = 0xB0;
	ucSend[P1 ] = iP1;
	ucSend[P2 ] = iP2;
	ucSend[P3 ] = iP3;
	iResponseLen= SendCommand (ucSend,05,ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::Mif_UpdateBinary(int iP1, int iP2, int iP3, unsigned char* ucData)
{
	InitParameter();
	ucSend[Cla] = 0xFF;
	ucSend[Ins] = 0xD6;
	ucSend[P1 ] = iP1;
	ucSend[P2 ] = iP2;
	ucSend[P3 ] = iP3;
	for (int i = 0 ; i < iP3 ;i++)
	{
		ucSend[i+5] = ucData[i];
	}

	iResponseLen= SendCommand (ucSend,ucSend[P3 ]+05,ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::Mif_LoadKey(int iKeyType, int iKeyLen, unsigned char* ucKey)
{
	InitParameter();
	ucSend[Cla] = 0xFF;
	ucSend[Ins] = 0x82;
	ucSend[P1 ] = 00;
	ucSend[P2 ] = iKeyType;
	ucSend[P3 ] = iKeyLen;
	for (int i = 0 ; i < iKeyLen ;i++)
	{
		ucSend[i+5] = ucKey[i];
	}

	iResponseLen= SendCommand (ucSend,ucSend[P3 ]+05,ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::Mif_GetATS(void)
{
	InitParameter();
	ucSend[Cla] = 0xFF;
	ucSend[Ins] = 0xCC;
	ucSend[P1 ] = 00;
	ucSend[P2 ] = 00;
	ucSend[P3 ] = 01;
	ucSend[P3+1] =0x93;

	iResponseLen= SendCommand (ucSend,ucSend[P3 ]+05,ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::Mif_SetTypeA(void)
{
	InitParameter();
	ucSend[Cla] = 0xFF;
	ucSend[Ins] = 0xCC;
	ucSend[P1 ] = 00;
	ucSend[P2 ] = 00;
	ucSend[P3 ] = 02;
	ucSend[P3+1] =0x95;
	ucSend[P3+2] =0x01;
	iResponseLen= SendCommand (ucSend,ucSend[P3 ]+05,ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::Mif_SetTypeB(void)
{
	InitParameter();
	ucSend[Cla] = 0xFF;
	ucSend[Ins] = 0xCC;
	ucSend[P1 ] = 00;
	ucSend[P2 ] = 00;
	ucSend[P3 ] = 02;
	ucSend[P3+1] =0x95;
	ucSend[P3+2] =0x02;
	iResponseLen= SendCommand (ucSend,ucSend[P3 ]+05,ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::Mif_Increment(int iBlockNum, unsigned char* ucData)
{
	InitParameter();
	ucSend[Cla] = 0xFF;
	ucSend[Ins] = 0xF0;
	ucSend[P1 ] = 0x00;
	ucSend[P2 ] = iBlockNum;
	ucSend[P3 ] = 0x06;
	ucSend[P3+1] = 0xC0;
	ucSend[P3+2] = iBlockNum;
	for (int i = 0 ; i < 4 ;i++)
	{
		ucSend[i+7] = ucData[i];
	}

	iResponseLen= SendCommand (ucSend,ucSend[P3 ]+05,ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::Mif_Decrement(int iBlockNum, unsigned char* ucData)
{
	InitParameter();
	ucSend[Cla] = 0xFF;
	ucSend[Ins] = 0xF0;
	ucSend[P1 ] = 0x00;
	ucSend[P2 ] = iBlockNum;
	ucSend[P3 ] = 0x06;
	ucSend[P3+1] = 0xC1;
	ucSend[P3+2] = iBlockNum;
	for (int i = 0 ; i < 4 ;i++)
	{
		ucSend[i+7] =  ucData[i];
	}

	iResponseLen= SendCommand (ucSend,ucSend[P3 ]+05,ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::Mif_EchoCmd(int iDataLen, unsigned char* ucData)
{
	InitParameter();
	ucSend[Cla] = 0xFF;
	ucSend[Ins] = 0xF0;
	ucSend[P1 ] = 0x00;
	ucSend[P2 ] = 0x00;
	ucSend[P3 ] = iDataLen;
	for (int i = 0 ; i < iDataLen ;i++)
	{
		ucSend[i+5] =  ucData[i];
	}

	iResponseLen= SendCommand (ucSend,ucSend[P3 ]+05,ucResponse);
	PostParameter();
	return iResponseLen;
}

int CPcscReader::Mif_SelectEcho(void)
{
	unsigned char ucEcho[8] ={0xA0,0x00,0x11,0x22,0x33,0x44,0x55,0x66};
	return Select_UICC(04,00,07 ,ucEcho);
}

int CPcscReader::Mip_SelectPf(void)
{
	unsigned char ucPf[0x10] ={0xA0,0x00,0x00,0x03,0x33,0x01,0x01,0x02,0x6D,0x66,0x53,0xD1,0x94,0xF6,0x88,0x4C};
	return Select_UICC(04,00,10 ,ucPf);
}

