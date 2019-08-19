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

// CardManage.h : CardManage Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "Basconv.h"

// CCardManageApp:
// �йش����ʵ�֣������ CardManage.cpp
//

class CCardManageApp : public CWinAppEx
{
public:
	CCardManageApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	CString GetSettingName(int iSettingCode);
	// ��װ����
	int InstallFont(void);
// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()


	int LoadBuiltSetting();
	int SaveCardConnectSetting();
	int SaveStartSetting();
};

extern CCardManageApp theApp;
