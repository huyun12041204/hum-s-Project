#pragma once
#include "afxcmn.h"


#define  _DEF_SMS_GSM   01
#define  _DEF_SMS_CDMA  02

#define  _DEF_SMS_USIM  0x10
#define  _DEF_SMS_3GPP  0x10




#define  _DEF_SMS_Status 01 
#define  _DEF_SMS_SCN    02
#define  _DEF_SMS_Patameter 03
#define  _DEF_SMS_Address    04
#define  _DEF_SMS_Date       05
#define  _DEF_SMS_Time       06	
#define  _DEF_SMS_TimeZone   07
#define  _DEF_SMS_UserData   0x8
#define  _DEF_SMS_TranUserData 0x9

// C_SMS �Ի���

class C_SMS : public CDialogEx
{
	DECLARE_DYNAMIC(C_SMS)

public:
	C_SMS(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~C_SMS();

// �Ի�������
	enum { IDD = IDD_ShortMessage_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �����б����
	CListCtrl m_Message_List;

	//�������
	int iShortMessageType;

	//�Ѷ��Ŷ�����ı���
	CString csMessageFileData;

	int InitContrl(void);
	// ��ʼ��������������
	int InitParameter(void);
	// ��ȡ���Ų��Ҽ����б�
	int ReadShortMessageList(void);
	// ��ȡMainFrame ���Ҹ���Ƭ����ָ���ز�������MainFrame�ﴦ��
	int GetHandle2SendCommand(CString csSend, CString& csResp);
	// ��ȡGSM����
	int ReadShortMessageList_GSM(void);
	// ��ȡUSIM����
	int ReadShortMessageList_3GPP(void);
	// //Select ���ţ����ҷ��� �����������Ͷ��ų���
	int _SeleteShortMessage_GSM(int* iSMSSum = NULL, int* iSMSLen= NULL);
	// Select ���ţ����ҷ��� �����������Ͷ��ų���
	int _SeleteShortMessage_3GPP(int* iSMSSum= NULL, int* iSMSLen= NULL);

	// ��ȡ�����е���ز������Ѿ����������
	int _TraslateParameterofSMS(CString csSMS, int iParameter,CString& csResp,int* iBatch = NULL,int* iSum= NULL,int* iNum= NULL);
	// �� ���������ж��Ŷ����ͳ����� ���������� 
	int _TransantionAllMessageData(CString csAllMessage);
	// //����صĲ�����Display����
	int _SetMessageData2Edit(void);
	// ͨ�����ζ����������Ͷ���������Ѱ����
	int _FindMessage(int iBatch, int iSum, int iNum, CString csAllMessage);

	// ͨ��   ʱ�� ���� ���ζ����������Ͷ���������Ѱ����
	int _FindMessage(CString csDate,CString csTime,int iBatch, int iSum, int iNum, CString csAllMessage);
	int _InsertMessageItem(CString csRecord,CString csAddress,CString csUserData);
	afx_msg void OnNMDblclkMessageList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRead2listButton();

	// ���ö������ GSM USM CDMA CSIM
	int SetShortMessageType(int iType);
	afx_msg void OnBnClickedDeletecheckedButton();
	// ɾ������
	int _DeleteMessage();
	int _DeleteMessage_GSM();
	int _DeleteMessage_3GPP();
	// ��ȡ�Ѿ���ѡ�е�ITEM
	int _GetItemCheck(CString& csItem);
	// ͨ��Search �ҵ��հ׵Ķ���
	int _GetEmptyMessage(CString& csRecord);
	int _GetEmptyMessage_GSM(CString& csRecord,int iExt = 1);
	int _GetEmptyMessage_3GPP(CString& csRecord);
	// ���µ��յļ�¼��
	int _UpdateMessage_GSM(CString csSMSData);
	int _UpdateMessage_3GPP(CString csSMSData);
	afx_msg void OnBnClickedUpdate2fileButton();
	// ����Edit�������ɶ���
	int _GennerateShortMessage(CString& csMessage);
	// �Ƿ�Ϊ���ں�ʱ���ʽ XXXX-XX-XX XX:XX:XX
	int _IsDateTimeFormat(CString csData);
	afx_msg void OnEnKillfocusDatetimeEdit();
	afx_msg void OnBnClickedUsesystemtimeCheck();
	afx_msg void OnBnClickedClearsmsButton();
	// ��պŲ��ļ�
	int _ClearMessageFile(void);
	int _ClearMessageFile_GSM(void);
	int _ClearMessageFile_3GPP(void);
	afx_msg void OnBnClickedUsecardsmcCheck();
	// ѡ��GSM �������ĺ��ļ�
	int _SelectSMSP_GSM(int* iSMSPLen);
	// ѡ��GSM �������ĺ��ļ�
	int _SelectSMSP_3GPP(int* iSMSPLen);
	int _GetSMSP_GSM(CString& csSMSP);
	int _GetSMSP_3GPP(CString& csSMSP);
	int _GetSMSP(CString& csSMSP);
	
	
	//// �Ƿ�ȫ��Ϊ���ֻ�����ĸ
	//int _IsAllASC(CString csSMSData);
};

#pragma once
#include "afxcmn.h"

#define  _DEF_PhoneBook_3GPP    01
#define  _DEF_PhoneBook_GSM     02
// C_ADN �Ի���

class C_ADN : public CDialogEx
{
	DECLARE_DYNAMIC(C_ADN)

public:
	C_ADN(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~C_ADN();

	// �Ի�������
	enum { IDD = IDD_AbbreviatedDiallingNumbers_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	// ���غŲ����߷Ǳ��غŲ�
	bool bLocalPhoneBook;
	int  iPhoneBookType;
	// ��ʾ�Ų���List
	CListCtrl m_PhoneBook_List;

	void InitParameter(void);
	// ��ʼ�������ؼ�
	void InitContrl(void);

	// ��ȡMainFrame ���Ҹ� ��Ƭ����ָ� ��ز�������MainFrame �ﴦ��
	int GetHandle2SendCommand(CString csSend, CString& csResp);


	// //ѡ�кŲ��ĳ�ʼĿ¼
	int _SelectPhoneBookDF_3GPP(void);
	// ���뱣֤��ǰĿ¼Ϊ PhoneBook ����£���������ִ�У����� ����
	int _SelectPBREF_3GPP(CString& csResp);
	// ��ȡ pbr �ļ� ��ȡ ADN �ļ��� FID ���� FID ������
	int _GetADNFile_Signt(CString& csFIDList,int iRecNum,int iRecLen);
	int WriteTestADN(void);
	int WriteTestADN_3GPP(void);
	// ��ȡADN ����,�����Ҫ��ѡ�� PBR ֮��
	int _GetANDSum_3GPP(CString csFileList,int iADNFileNum);
	// �Ѿ�����������״̬��
	int SetProgress2StatusBar(int iSum, int iCurrent);

	int ReadSetADN2List(void);
	// ��ʾ �������յģ�ռ�õ�
	void SetPhoneBookDisplay(int iSum, int iUsed);
	// ��ѭGSM ��׼�ĺŲ�
	int WriteTestADN_GSM(void);
	// ��ѭ3GPP �淶����ȡ�Ų�
	int ReadSetADN2List_3GPP(void);
	// ��ѭGSM �淶��ȡ�Ų�
	int ReadSetADN2List_GSM(void);
	// ���� �Ų� ��� GSM USIM ��
	int SetAbbreviatedDiallingNumbersType(int iType);
	afx_msg void OnBnClickedReadphonebookButton();
	afx_msg void OnBnClickedWritetestphonebookButton();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};
