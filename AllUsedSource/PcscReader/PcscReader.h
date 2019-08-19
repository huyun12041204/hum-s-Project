// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� PCSCREADER_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// PCSCREADER_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef PCSCREADER_EXPORTS
#define PCSCREADER_API __declspec(dllexport)
#else
#define PCSCREADER_API __declspec(dllimport)
#endif




#define PCSCOK             0
#define NoCard            -1
#define NoATR             -2
#define Resetfalse        -3

#define Cla     00
#define Ins     01
#define P1      02
#define P2      03
#define P3      04
#define CmdData 05

#define WarmReset 01
#define ColdReset 02


#include "winscard.h" //PCSC lib


// �����Ǵ� PcscReader.dll ������
class PCSCREADER_API CPcscReader {
public:


protected:
	ULONG         m_pContext;
	SCARDHANDLE   m_pcscHandle; 
	DWORD         dwProtocol;

	unsigned char ucSend[300];
	unsigned char ucResponse[300];
	unsigned char ucSW[2]; 

	int iAutoResponse; 
	int iResponseLen;
	int iSendLen;

public:
	int GetContext();
	int GetPcsclist( LPTSTR *szReaderName);
	int ConnectReader(LPTSTR szReaderName);
	int GetCardATR(unsigned char *ucATR);
	int DisConnectReader();
	//iMod 1 WarmReset 2 ColdReset
    int ResetCard(int iMod);

public:


	int SendCommand(unsigned char* ucpSend,int iSendLength, unsigned char* ucResponse,int* iResLen);
	bool SetAutoGetResponse(int iAuto);
	int GetLastResponse(unsigned char * ucRec);
	int GetLastSW(unsigned char * ucLSW);
	int GetLastSend(unsigned char *ucLSend);

protected:
	void InitParameter(void);
	void PostParameter(void);
	int SendCommand(LPCBYTE lpSend,int iSendLength, unsigned char* ucResponse);

	// GSM ָ���
public:
	int Select_GSM(int iFid);
	int GetResponse_GSM(int iReslen);
	int ReadBinary_GSM(int iP1, int iP2,int iP3);
	int ReadRecord_GSM(int iP1, int iP2,int iP3);
	int Verify_GSM(int iP2,int iP3,LPCBYTE ucPin);

	//UICC ָ���
public:
	int Select_UICC(int iP1,int iP2,int iP3,LPCBYTE ucAID);
	int Select_UICC_FID(LPCBYTE ucFID);
	int Select_UICC_AID(LPCBYTE ucAID,int iAIDLength);
	int Select_UICC_ChildDF(LPCBYTE ucFID);
	int Select_UICC_ParentDF( );

	int GetResponse_UICC(int iReslen);
	int ReadBinary_UICC(int iP1, int iP2,int iP3);
	int ReadRecord_UICC(int iP1, int iP2,int iP3);
	int Verify_UICC(int iP2,int iP3,LPCBYTE ucPin);
	int UpdateRecord_UICC(int iP1, int iP2, int iP3, unsigned char* ucData);



	//����ָ��
public:
	int Set_SM1_Key(unsigned char *ucKey,int iKeyLen);
	int Set_SM1_Encrypt(unsigned char *ucData,int iDataLen);
	int Set_SSF33_SKey(unsigned char *ucKey,int iKeyLen);
	int Set_SSF33_MKey(unsigned char *ucKey,int iKeyLen);
	int Set_SSF33_Encrypt(unsigned char *ucData,int iDataLen);
	int Set_SSF33_Decrypt(unsigned char *ucData,int iDataLen);


    //Mifareָ��
public:
    int Mif_Authenticate(int iMSB = 00,int iLSB=00,int iKeyType=0x60,int iKeyNum=00);
	int Mif_GetUid();
	int Mif_GetReponse(int iReslen);
	int Mif_SelectISD_Unicom(void);
	int Mif_GetChallenge(int iLength);
	int Mif_DeleteOS(void);
	int Mif_OpenChannel(void);
	int Mif_CloseChannel(void);
	int Mif_ReadBinary(int iP1=00, int iP2=01,int iP3=00);
	int Mif_UpdateBinary(int iP1, int iP2, int iP3, unsigned char* ucData);
	int Mif_LoadKey(int iKeyType, int iKeyLen, unsigned char* ucKey);
	int Mif_GetATS(void);
	int Mif_SetTypeA(void);
	int Mif_SetTypeB(void);
	int Mif_Increment(int iBlockNum, unsigned char* ucData);
	int Mif_Decrement(int iBlockNum, unsigned char* ucData);
	int Mif_EchoCmd(int iDataLen, unsigned char* ucData);
	int Mif_SelectEcho(void);
	int Mip_SelectPf(void);
public:

};

