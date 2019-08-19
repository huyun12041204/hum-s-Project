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

// C_SMS 对话框

class C_SMS : public CDialogEx
{
	DECLARE_DYNAMIC(C_SMS)

public:
	C_SMS(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~C_SMS();

// 对话框数据
	enum { IDD = IDD_ShortMessage_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 短信列表变量
	CListCtrl m_Message_List;

	//短信类别
	int iShortMessageType;

	//把短信都放入的变量
	CString csMessageFileData;

	int InitContrl(void);
	// 初始化各个参数变量
	int InitParameter(void);
	// 读取短信并且加入列表
	int ReadShortMessageList(void);
	// 获取MainFrame 并且给卡片发送指令，相关参数按照MainFrame里处理
	int GetHandle2SendCommand(CString csSend, CString& csResp);
	// 读取GSM段心
	int ReadShortMessageList_GSM(void);
	// 读取USIM短信
	int ReadShortMessageList_3GPP(void);
	// //Select 短信，并且返回 短信总数，和短信长度
	int _SeleteShortMessage_GSM(int* iSMSSum = NULL, int* iSMSLen= NULL);
	// Select 短信，并且返回 短信总数，和短信长度
	int _SeleteShortMessage_3GPP(int* iSMSSum= NULL, int* iSMSLen= NULL);

	// 获取短信中的相关参数，已经换过编码的
	int _TraslateParameterofSMS(CString csSMS, int iParameter,CString& csResp,int* iBatch = NULL,int* iSum= NULL,int* iNum= NULL);
	// 把 所读的所有短信都解释出来， 包括多条的 
	int _TransantionAllMessageData(CString csAllMessage);
	// //把相关的参数都Display出来
	int _SetMessageData2Edit(void);
	// 通过批次短信总数，和短信条数找寻短信
	int _FindMessage(int iBatch, int iSum, int iNum, CString csAllMessage);

	// 通过   时间 日期 批次短信总数，和短信条数找寻短信
	int _FindMessage(CString csDate,CString csTime,int iBatch, int iSum, int iNum, CString csAllMessage);
	int _InsertMessageItem(CString csRecord,CString csAddress,CString csUserData);
	afx_msg void OnNMDblclkMessageList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRead2listButton();

	// 设置短信类别 GSM USM CDMA CSIM
	int SetShortMessageType(int iType);
	afx_msg void OnBnClickedDeletecheckedButton();
	// 删除短信
	int _DeleteMessage();
	int _DeleteMessage_GSM();
	int _DeleteMessage_3GPP();
	// 获取已经被选中的ITEM
	int _GetItemCheck(CString& csItem);
	// 通过Search 找到空白的短信
	int _GetEmptyMessage(CString& csRecord);
	int _GetEmptyMessage_GSM(CString& csRecord,int iExt = 1);
	int _GetEmptyMessage_3GPP(CString& csRecord);
	// 更新到空的记录中
	int _UpdateMessage_GSM(CString csSMSData);
	int _UpdateMessage_3GPP(CString csSMSData);
	afx_msg void OnBnClickedUpdate2fileButton();
	// 根据Edit数据生成短信
	int _GennerateShortMessage(CString& csMessage);
	// 是否为日期和时间格式 XXXX-XX-XX XX:XX:XX
	int _IsDateTimeFormat(CString csData);
	afx_msg void OnEnKillfocusDatetimeEdit();
	afx_msg void OnBnClickedUsesystemtimeCheck();
	afx_msg void OnBnClickedClearsmsButton();
	// 清空号簿文件
	int _ClearMessageFile(void);
	int _ClearMessageFile_GSM(void);
	int _ClearMessageFile_3GPP(void);
	afx_msg void OnBnClickedUsecardsmcCheck();
	// 选择GSM 短信中心号文件
	int SelectSMSP_GSM(int* iSMSPLen)；
	// 选择GSM 短信中心号文件
	int SelectSMSP_3GPP(int* iSMSPLen)；
};
