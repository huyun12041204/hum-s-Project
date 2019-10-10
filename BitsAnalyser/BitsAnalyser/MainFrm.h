// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// MainFrm.h : CMainFrame 类的接口
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
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
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
// 生成的消息映射函数
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

	// //打开USB设备
	usb_dev_handle * Open_Dev(void);
	void __Init(void);

};


