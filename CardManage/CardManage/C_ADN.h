#pragma once
#include "afxcmn.h"

#define  _DEF_PhoneBook_3GPP    01
#define  _DEF_PhoneBook_GSM     02
// C_ADN 对话框

class C_ADN : public CDialogEx
{
	DECLARE_DYNAMIC(C_ADN)

public:
	C_ADN(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~C_ADN();

// 对话框数据
	enum { IDD = IDD_AbbreviatedDiallingNumbers_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:

	// 本地号簿或者非本地号簿
	bool bLocalPhoneBook;
	int  iPhoneBookType;
	// 显示号簿的List
	CListCtrl m_PhoneBook_List;

	void InitParameter(void);
	// 初始化各个控件
	void InitContrl(void);

	// 获取MainFrame 并且给 卡片发送指令， 相关参数按照MainFrame 里处理
	int GetHandle2SendCommand(CString csSend, CString& csResp);


	// //选中号簿的初始目录
	int _SelectPhoneBookDF_3GPP(void);
	// 必须保证当前目录为 PhoneBook 情况下，参能正常执行，返回 如上
	int _SelectPBREF_3GPP(CString& csResp);
	// 读取 pbr 文件 获取 ADN 文件的 FID 返回 FID 的总数
	int _GetADNFile_Signt(CString& csFIDList,int iRecNum,int iRecLen);
	int WriteTestADN(void);
	int WriteTestADN_3GPP(void);
	// 获取ADN 总数,这个需要在选择 PBR 之后
	int _GetANDSum_3GPP(CString csFileList,int iADNFileNum);
	// 把具体进度输出到状态栏
	int SetProgress2StatusBar(int iSum, int iCurrent);

	int ReadSetADN2List(void);
	// 显示 总数，空的，占用的
	void SetPhoneBookDisplay(int iSum, int iUsed);
	// 遵循GSM 标准的号簿
	int WriteTestADN_GSM(void);
	// 遵循3GPP 规范来读取号簿
	int ReadSetADN2List_3GPP(void);
	// 遵循GSM 规范读取号簿
	int ReadSetADN2List_GSM(void);
	// 设置 号簿 类别， GSM USIM 等
	int SetAbbreviatedDiallingNumbersType(int iType);
};
