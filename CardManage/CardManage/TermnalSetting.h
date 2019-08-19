#pragma once


// CTermnalSetting �Ի���

class CTermnalSetting : public CDialogEx
{
	DECLARE_DYNAMIC(CTermnalSetting)

public:
	CTermnalSetting(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTermnalSetting();

// �Ի�������
	enum { IDD = IDD_Terminal_Setting_Dialog };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	int GetTerminalSetting(void);
	HANDLE TerminalHandle;
public:
	void SetTerminalHandle(HANDLE hTerminalHandle);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedApplyButton();
	// ����part1 
	int GeneratePart1Setting(BYTE* ucPart1, int uiPartLen);
};
