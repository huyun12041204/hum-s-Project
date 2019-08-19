#pragma once


// CTermnalSetting 对话框

class CTermnalSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CTermnalSetting)

public:
	CTermnalSetting(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTermnalSetting();

// 对话框数据
	enum { IDD = IDD_Terminal_Setting_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	int GetTerminalSetting(void);
	HANDLE TerminalHandle;
public:
	void SetTerminalHandle(HANDLE hTerminalHandle);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedApplyButton();
	// 生成part1 
	int GeneratePart1Setting(BYTE* ucPart1, int uiPartLen);
};
