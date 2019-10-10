// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://msdn.microsoft.com/officeui��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "OutputWnd.h"
#include "lusb0_usb.h"
#include "BitsAnalyserView.h"

#define MY_VID            0x1483
#define MY_PID            0x5751

// Device configuration and interface id.


#ifndef _USB_IN_

#define _USB_IN_
#define MY_CONFIG 1
#define MY_INTF 0

// Device endpoint(s)
#define EP_IN    0x81
#define EP_OUT   0x01
#define BUF_SIZE 256
#define Max_Size 1024*1024*100

#define Command_Head_Length 5
#define Command_TimeOut     5000

#define _Command_Mode 1

#endif



class CMainFrame : public CFrameWndEx
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CMFCRibbonBar     m_wndRibbonBar;
	CMFCRibbonApplicationButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;


	COutputWnd           m_wndOutput;


	CWinThread * GetBitThread;
	CWinThread * ViewBitThread;
public:
	CMFCRibbonProgressBar*   m_Progress;
	CMFCRibbonBaseElement*   m_ProgressData; 
// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

	afx_msg void OnConnectButton();
	afx_msg void OnDisconnectButton();
	afx_msg void OnUpdateConnected(CCmdUI* pCmdUI);
	afx_msg LRESULT OnUpdateProgress(WPARAM /* wParam*/,LPARAM /* LParam*/);
	DECLARE_MESSAGE_MAP()

	
	BOOL CreateDockingWindows();
	void SetDockingWindowIcons(BOOL bHiColorIcons);
public:

	// //��USB�豸
	usb_dev_handle * Open_Dev(void);
	void __Init(void);

};


