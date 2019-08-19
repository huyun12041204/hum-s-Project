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
};
