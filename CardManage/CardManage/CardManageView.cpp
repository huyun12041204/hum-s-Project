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

// CardManageView.cpp : CCardManageView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CardManage.h"
#endif
#include "CardManageDoc.h"
#include "CardManageView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCardManageView

IMPLEMENT_DYNCREATE(CCardManageView, CView)

BEGIN_MESSAGE_MAP(CCardManageView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, &CCardManageView::OnPropertyChanged)
END_MESSAGE_MAP()

// CCardManageView ����/����
CMFCPropertyGridProperty* CCardManageView::CreateBasicLife2PropList(CString csValue)
{
	CMFCPropertyGridProperty* pGroup;
	CString csDisplay,csDescriptor;
	if (!csValue.IsEmpty())
	{
		switch(_CString2Int(csValue))
		{
		case 0x00:csDisplay  = _T("����Ϣ");break;
		case 0x01:csDisplay    = _T("����״̬");break;
		case 0x03:csDisplay    = _T("��ʼ��״̬");break;
		case 0x07:
		case 0x05:csDisplay    = _T("����״̬������");break;
		case 0x06:
		case 0x04:csDisplay    = _T("����״̬��ȥ����");break;
		case 0x0D:
		case 0x0E:
		case 0x0F:csDisplay    = _T("��ֹ");break;
		case 0x02:
		case 0x08:
		case 0x09:
		case 0x0A:
		case 0x0B:
		case 0x0C:csDisplay    = _T("RFU");break;
		default:csDisplay    = _T("ר��");break;
		}
		csDescriptor = _T("��������״̬��Ϣ");
		pGroup = new CMFCPropertyGridProperty(_T("��������״̬��Ϣ"),csDisplay, csDescriptor);
	}
	else
	{
		pGroup = new CMFCPropertyGridProperty(_T("��������״̬��Ϣ"),_T("����Ϣ"), _T("����Ϣ"));
	}


	pGroup->AddOption(_T("����Ϣ"));
	pGroup->AddOption(_T("����״̬"));
	pGroup->AddOption(_T("��ʼ��״̬"));
	pGroup->AddOption(_T("����״̬������"));
	pGroup->AddOption(_T("����״̬��ȥ����"));
	pGroup->AddOption(_T("��ֹ"));

	pGroup->AddOption(_T("RFU"));
	pGroup->AddOption(_T("ר��"));	
	pGroup->AllowEdit(FALSE);
	return pGroup;
}

CMFCPropertyGridProperty* CCardManageView::CreateBasicSecurity2PropList(int iTag,CString csValue)
{
	CMFCPropertyGridProperty* pGroup;
	CString csDis; 
	if (!csValue.IsEmpty())
	{
		pGroup = new CMFCPropertyGridProperty(_T("��ȫ����"),0,TRUE);
		switch (iTag)
		{
		case 0x8B:pGroup->AddSubItem(CreateBasicACType2PropList(_T("������չ��ʽ")));break;
		case 0x8C:pGroup->AddSubItem(CreateBasicACType2PropList(_T("���ո�ʽ")));break;
		case 0xAB:pGroup->AddSubItem(CreateBasicACType2PropList(_T("��չ��ʽ")));break;
		}
		pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("����") ,csValue, csValue));
	}
	else
		pGroup = NULL;

	return pGroup;
}

CMFCPropertyGridProperty* CCardManageView::CreateBasicACType2PropList(CString csType)
{
	CMFCPropertyGridProperty* pGroup;

	pGroup =  new CMFCPropertyGridProperty(_T("��ȫ���") ,csType, csType);
	pGroup->AddOption(_T("������չ��ʽ"));
	pGroup->AddOption(_T("���ո�ʽ"));
	pGroup->AddOption(_T("��չ��ʽ"));
	pGroup->AllowEdit(FALSE);

	return pGroup;

}

CMFCPropertyGridProperty* CCardManageView::CreateBasicFileDes2PropList(CString csDes)
{
	CMFCPropertyGridProperty *pGroup;
	CMFCPropertyGridProperty *pSubGroup;
	CString csDisplay,csDescriptor;
	int iFileDes = _CString2Int(csDes.Mid(00,02));

	pGroup = new CMFCPropertyGridProperty(_T("�ļ�������"),0,TRUE);

	//�ļ��������ֽ�

	if (iFileDes&0x40)
		csDisplay    = _T("�����ļ�");
	else
		csDisplay    = _T("�ǹ����ļ�");
	csDescriptor = _T("Shareable file / Not shareable file");
		
	pSubGroup = new CMFCPropertyGridProperty(_T("�ļ�������"),csDisplay, _T("File accessibility :")+ csDescriptor);

	pSubGroup->AddOption(_T("�����ļ�"));
	pSubGroup->AddOption(_T("�ǹ����ļ�"));
	pSubGroup->AllowEdit(FALSE);

	pGroup->AddSubItem(pSubGroup);


	switch(iFileDes&0x38)
	{
	case 0x00:
		csDisplay = _T("�����ļ�");
		break;
	case 0x08:
		csDisplay = _T("�ڲ��ļ�");
		break;
	case 0x38:
		csDisplay = _T("Ŀ¼");
		break;
	default:
		csDisplay = _T("EF category : RFU");
		break;
	}
	csDescriptor = _T("Working EF / Internal EF / DF / Proprietary categories of EFs");

	pSubGroup = new CMFCPropertyGridProperty(_T("�ļ�����"),csDisplay, csDescriptor);

	pSubGroup->AddOption( _T("�����ļ�"));
	pSubGroup->AddOption( _T("�ڲ��ļ�"));
	pSubGroup->AddOption( _T("Ŀ¼"));
	pSubGroup->AddOption( _T("RFU"));
	pSubGroup->AllowEdit(FALSE);
	pGroup->AddSubItem(pSubGroup);


	if ((iFileDes&0x38)!= 0x38)
	{
		switch(iFileDes&0x7)
		{
		case 00:
			csDisplay    = _T("�ļ���������Ϣ");
			break;
		case 01:
			csDisplay    = _T("͸���ļ�");
			break;
		case 02:
			csDisplay    = _T("���Զ����ļ�");
			break;
		case 03:
			csDisplay    = _T("���Զ����ļ�,TLV��ʽ");
			break;
		case 04:
			csDisplay    = _T("���Բ������ļ�");
			break;
		case 05:
			csDisplay    = _T("���Բ������ļ�,TLV��ʽ");
			break;
		case 06:
			csDisplay    = _T("ѭ���ļ�");
			break;
		case 0x07:
			csDisplay    = _T("ѭ���ļ�,TLV��ʽ");
			break;
		}
	}
	else
	{
		csDisplay    = _T("");
	}

	csDescriptor = _T("File structure");

	pSubGroup = new CMFCPropertyGridProperty(_T("�ļ��ṹ"),csDisplay, csDescriptor);

	pSubGroup->AddOption(_T("�ļ���������Ϣ"));
	pSubGroup->AddOption(_T("͸���ļ�"));
	pSubGroup->AddOption(_T("���Զ����ļ�"));
	pSubGroup->AddOption(_T("���Զ����ļ�,TLV��ʽ"));
	pSubGroup->AddOption(_T("���Բ������ļ�"));
	pSubGroup->AddOption(_T("���Բ������ļ�,TLV��ʽ"));

	pSubGroup->AddOption(_T("ѭ���ļ�"));
	pSubGroup->AddOption(_T("ѭ���ļ�,TLV��ʽ"));

	pSubGroup->AddOption(_T("TLV structure for BER-TLV data objects"));
	pSubGroup->AddOption(_T("TLV structure for BER-TLV data objects"));
	pSubGroup->AddOption(_T("����Ϣ"));
	pSubGroup->AllowEdit(FALSE);
	if ((iFileDes&0x38)== 0x38)
		pSubGroup->Show(FALSE);


	pGroup->AddSubItem(pSubGroup);

	if (csDes.GetLength() >4)
	{
		csDisplay.Format("%02X",_CString2Int(csDes.Mid(04,04)));
		csDescriptor.Format("%d",_CString2Int(csDes.Mid(04,04)));

		pGroup->AddSubItem(new CMFCPropertyGridProperty(_T("��¼����"),csDisplay ,_T("�ļ�������¼����: ")+csDescriptor+_T("(10����)")));

		csDisplay.Format("%02X",_CString2Int(csDes.Mid(0x08,csDes.GetLength()-0x08)));
		csDescriptor.Format("%d",_CString2Int(csDes.Mid(0x08,csDes.GetLength()-0x08)));

		pGroup->AddSubItem( new CMFCPropertyGridProperty(_T( "��¼��Ŀ" ), csDisplay,  _T("�ļ����м�¼����: ")+csDescriptor+_T("(10����)")  ));
	}
	else
	{
		pSubGroup = new CMFCPropertyGridProperty(_T("��¼����"),_T(""));
		pSubGroup->Show(FALSE);
		pGroup->AddSubItem(pSubGroup);
		pSubGroup = new CMFCPropertyGridProperty(_T("��¼��Ŀ"),_T(""));
		pSubGroup->Show(FALSE);
		pGroup->AddSubItem(pSubGroup);

	}



	pGroup->Expand(TRUE);

	return pGroup;
		
}

CMFCPropertyGridProperty* CCardManageView::CreateBasicInformation2PropList(CString csFCI)
{
	CString cs80Value,cs81Value,cs82Value,cs83Value,cs84Value,cs85Value;
	CString cs86Value,cs87Value,cs88Value,cs8AValue,cs8BValue,cs8CValue;
	CString cs8DValue,cs8EValue,csA0Value,csA1Value,csA2Value;
	CString csABValue,csACValue;

	CString csDisplay,csDescriptor;
	CMFCPropertyGridProperty* pGroup;

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("������Ϣ"));

	csFCI  =  GetTLVData(csFCI,0x62);
	if (csFCI.IsEmpty())
		return pGroup1;

	cs80Value = GetTLVData(csFCI,0x80);
	cs81Value = GetTLVData(csFCI,0x81);
	cs82Value = GetTLVData(csFCI,0x82);
	cs83Value = GetTLVData(csFCI,0x83);
	cs84Value = GetTLVData(csFCI,0x84);
	cs85Value = GetTLVData(csFCI,0x85);
	cs86Value = GetTLVData(csFCI,0x86);
	cs87Value = GetTLVData(csFCI,0x87);
	cs88Value = GetTLVData(csFCI,0x88);
	cs8AValue = GetTLVData(csFCI,0x8A);
	cs8BValue = GetTLVData(csFCI,0x8B);
	cs8CValue = GetTLVData(csFCI,0x8C);
	cs8DValue = GetTLVData(csFCI,0x8D);
	cs8EValue = GetTLVData(csFCI,0x8E);
	csA0Value = GetTLVData(csFCI,0xA0);
	csA1Value = GetTLVData(csFCI,0xA1);
	csA2Value = GetTLVData(csFCI,0xA2);
	csABValue = GetTLVData(csFCI,0xAB);
	csACValue = GetTLVData(csFCI,0xAC);





	//FID

	pGroup = new CMFCPropertyGridProperty(_T("�ļ���ʶ"),cs83Value, _T("File identifier :")+ cs83Value);
	if(cs83Value.IsEmpty())
		pGroup->Show(FALSE);
	pGroup1->AddSubItem(pGroup);

	//AID

	pGroup = new CMFCPropertyGridProperty(_T("AID"),cs84Value,_T("DF Name"));
	if(cs84Value.IsEmpty())
		pGroup->Show(FALSE);
	pGroup1->AddSubItem(pGroup);


	//�ļ�����
	pGroup1->AddSubItem(CreateBasicFileDes2PropList(cs82Value));
	
	//��ȫ����

	if (!cs8BValue.IsEmpty())
		pGroup1->AddSubItem(CreateBasicSecurity2PropList(0x8B,cs8BValue));
	else if (!cs8CValue.IsEmpty())
		pGroup1->AddSubItem(CreateBasicSecurity2PropList(0x8C,cs8CValue));
	else if (!csABValue.IsEmpty())
		pGroup1->AddSubItem(CreateBasicSecurity2PropList(0xAB,csABValue));


	//��������״̬��Ϣ


	pGroup1->AddSubItem (CreateBasicLife2PropList(cs8AValue));




	
	if(cs88Value.IsEmpty())
	{
		pGroup= new CMFCPropertyGridProperty(_T("���ļ���ʾ"),_T(""));
		pGroup->Show(FALSE);
	}
	else
	{
		csDisplay.Format("%02X",_CString2Int(cs88Value)/0x8);
		csDescriptor.Format("%02d",_CString2Int(cs88Value)/0x8);
		pGroup = new CMFCPropertyGridProperty(_T("���ļ���ʾ"),csDisplay, _T("SFI : ")+csDescriptor+_T("(10����)"));
	}
	pGroup1->AddSubItem(pGroup);




	if(cs80Value.IsEmpty())
	{
		pGroup= new CMFCPropertyGridProperty(_T("�ļ���С"),_T(""));
		pGroup->Show(FALSE);
	}
	else
	{
		csDisplay.Format("%02X",_CString2Int(cs80Value));
		csDescriptor.Format("%02d",_CString2Int(cs80Value));
		pGroup = new CMFCPropertyGridProperty(_T("�ļ���С"),csDisplay, _T("�ļ���С : ")+csDescriptor+_T("(10����)"));
	}
	pGroup1->AddSubItem(pGroup);


	if(cs81Value.IsEmpty())
	{
		pGroup= new CMFCPropertyGridProperty(_T("���ļ���С"),_T(""));
		pGroup->Show(FALSE);
	}
	else
	{
		csDisplay.Format("%02X",_CString2Int(cs81Value));
		csDescriptor.Format("%02d",_CString2Int(cs81Value));
		pGroup = new CMFCPropertyGridProperty(_T("���ļ���С"),csDisplay, _T("���ļ���С : ")+csDescriptor+_T("(10����)"));
	}
	pGroup1->AddSubItem(pGroup);

	return pGroup1;
	

}

CMFCPropertyGridProperty* CCardManageView::CreateACCell(CString csCell)
{
	CMFCPropertyGridProperty* pGroup;
	pGroup =new CMFCPropertyGridProperty(csCell,_T(""),csCell);
	pGroup->AddOption("ALWAYS");
	pGroup->AddOption("PIN 01");
	pGroup->AddOption("PIN 81");
	pGroup->AddOption("PIN 0A");
	pGroup->AddOption("NEVER");
	pGroup->AddOption("....");
	pGroup->AllowEdit(FALSE);

	return pGroup;
}

CMFCPropertyGridProperty* CCardManageView::CreateAC2PropList( )
{
	
	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("�ļ�Ȩ��"));

	pGroup2->AddSubItem(CreateACCell(_T("READ,SEARCH")));
	pGroup2->AddSubItem(CreateACCell(_T("UPDATE,ERASE")));
	pGroup2->AddSubItem(CreateACCell(_T("APPEND,WRITE")));
	pGroup2->AddSubItem(CreateACCell(_T("DEACTIVATE FILE")));
	pGroup2->AddSubItem(CreateACCell(_T("ACTIVATE FILE")));
	pGroup2->AddSubItem(CreateACCell(_T("TERMINATE EF")));
	pGroup2->AddSubItem(CreateACCell(_T("DELETE FILE")));
	return pGroup2;
}

CMFCPropertyGridProperty* CCardManageView::CreateFile2PropList(CString csFCI)
{
	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("�ļ�����"));
	CString csFileInformation;
	CString csFileNumber,csFileRecord;
	int iFileType;
	csFCI               = GetTLVData(csFCI,0x62);
	csFileInformation   = GetTLVData(csFCI,0x82);

	iFileType = _CString2Int(csFileInformation.Mid(00,02));


	int iSum ; 
	CString csNumber;


	if(((iFileType&07) == 02)||((iFileType&07) == 06))
	{
		csFileRecord = csFileInformation.Mid(04,04);
		csFileNumber = csFileInformation.Mid(0x08,02);

		iSum = _CString2Int(csFileNumber);

		for (int iNumber = 1 ; iNumber <= iSum; iNumber ++)
		{
			csNumber.Format("%02d",iNumber);
			pGroup3->AddSubItem(new CMFCPropertyGridProperty(csNumber, (_variant_t) _T(""), _T("")));
		}

	}
	else if ((iFileType&07) == 01)
	{
		pGroup3->AddSubItem(new CMFCPropertyGridProperty(_T("����"), (_variant_t) _T(""), _T("")));
	}

	pGroup3->AllowEdit(FALSE);
	//pGroup3->Show(FALSE);
	return pGroup3;

	//m_wndPropList.AddProperty(pGroup3);
}

CMFCPropertyGridProperty* CCardManageView::CreateA52PropList(CString csFCI)
{
	CString cs80Value,cs81Value,cs82Value,cs83Value,csA5Value;
	CString csDisplay,csDescriptor;
	

	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("ר������"));

	csA5Value = GetTLVData(csFCI,0x62);
	csA5Value = GetTLVData(csA5Value,0xA5);

	if(!csA5Value.IsEmpty())
	{



		cs80Value = GetTLVData(csA5Value,0x80);
		cs81Value = GetTLVData(csA5Value,0x81);
		cs82Value = GetTLVData(csA5Value,0x82);
		cs83Value = GetTLVData(csA5Value,0x83);

		if (!cs80Value.IsEmpty())
		{
			CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("UICC ����"),1,TRUE);
			//UICC ����
			switch(_CString2Int(cs80Value)&0x0D)
			{
			case 00:
				csDisplay    = _T("������ʱ��ֹͣģʽ");
				csDescriptor = _T("������ʱ��ֹͣģʽ");
				break; 
			case 01:
				csDisplay    = _T("����ʱ��ֹͣģʽ������ѡ��ƽ");
				csDescriptor = _T("����ʱ��ֹͣģʽ������ѡ��ƽ");
				break; 
			case 04:
				csDisplay    = _T("������ʱ��ֹͣģʽ�������ڸߵ�ƽ");
				csDescriptor = _T("����ʹ�øߵ�ƽģʽ��ʱ��ֹͣ");
				break; 
			case 05:
				csDisplay    = _T("����ʱ��ֹͣģʽ����ѡ�ߵ�ƽ");
				csDescriptor = _T("����ʱ��ֹͣģʽ����ѡ�ߵ�ƽ");
			case 0x08:
				csDisplay    = _T("������ʱ��ֹͣģʽ �����ڵ͵�ƽ");
				csDescriptor = _T("����ʹ�õ͵�ƽģʽ��ʱ��ֹͣ");
				break; 
			case 0x09:
				csDisplay    = _T("����ʱ��ֹͣģʽ����ѡ�͵�ƽ");
				csDescriptor = _T("����ʱ��ֹͣģʽ����ѡ�͵�ƽ");
				break;
			default:
				break;
			}
			pGroup41->AddSubItem(new CMFCPropertyGridProperty(_T("ʱ��ֹͣ"),csDisplay,csDescriptor));
			//csDisplay    = _T("��ѹ���");
			//csDescriptor = _T("��ѹ");
			csDescriptor.Empty();
			csDisplay.Empty();
			if(_CString2Int(cs80Value)&0x10)
			{
				csDisplay   += _T(" A"); 
				csDescriptor+= _T(" 5V"); 
			}
			if(_CString2Int(cs80Value)&0x20)
			{
				csDisplay   += _T(" B"); 
				csDescriptor+= _T(" 3V"); 
			}
			if(_CString2Int(cs80Value)&0x40)
			{
				csDisplay   += _T(" C"); 
				csDescriptor+= _T(" 1.8V"); 
			}

			if (csDisplay.IsEmpty())
			{
				csDisplay = _T("��֧�����е�ѹ");
				csDescriptor= _T("��֧�����е�ѹ");

			}

			pGroup41->AddSubItem(new CMFCPropertyGridProperty(_T("�����ѹ"),csDisplay,csDescriptor));
			pGroup4->AddSubItem(pGroup41);
		}

		
		if (!cs81Value.IsEmpty())
		{

			CMFCPropertyGridProperty* pGroup42 = new CMFCPropertyGridProperty(_T("Ӧ�ù���"),0,TRUE);

			switch(_CString2Int(cs81Value.Mid(00,02))&0x7)
			{
			case 01:
				csDisplay    = _T("A");
				csDescriptor = _T("5V");
				break;
			case 02:
				csDisplay    = _T("B");
				csDescriptor = _T("3V");
				break;
			case 04:
				csDisplay    = _T("C");
				csDescriptor = _T("1.8V");
				break;
			default:
				csDisplay   = _T("��������ֵ");
				csDescriptor= _T("�ο�ATR�еı������ ��ǰ��������");

				break;
			}

			pGroup42->AddSubItem(new CMFCPropertyGridProperty(_T("��������ʱ�Ĺ������"),csDisplay,csDescriptor));

			if ((_CString2Int(cs81Value.Mid(02,02)) >0x3C)||(_CString2Int(cs81Value.Mid(02,02)) <01))
			{
				csDisplay = _T("��������ֵ");
				csDescriptor= _T("��ֵӦ���� 01 - 3C������������");
			}
			else
			{
				csDisplay = cs81Value;
				csDescriptor = cs81Value;
			}
			pGroup42->AddSubItem(new CMFCPropertyGridProperty(_T("Ӧ�ù���"),csDisplay,csDescriptor));

			if( _CString2Int(cs81Value.Mid(04,02)) <0x0A)
			{
				csDisplay = _T("��������ֵ");
				csDescriptor= _T("��ֵӦ���� 0A - FF������������");
			}
			else
			{
				csDisplay.Format("%d.%d",_CString2Int(cs81Value.Mid(04,02))/10,_CString2Int(cs81Value.Mid(04,02))%10);
				csDescriptor = csDisplay + _T("(��λMHz,�ֱ���0.1)(10����)");

			}
			pGroup42->AddSubItem(new CMFCPropertyGridProperty(_T("���Ĳο�Ƶ��"),csDisplay,csDescriptor));

			pGroup4->AddSubItem(pGroup42);

		}

		if (!cs82Value.IsEmpty())
		{
			if( _CString2Int(cs82Value.Mid(04,02)) <0x0A)
			{
				csDisplay = _T("��������ֵ");
				csDescriptor= _T("��ֵӦ���� 0A - FF������������");
			}
			else
			{
				csDisplay.Format("%d.%d",_CString2Int(cs81Value.Mid(04,02))/10,_CString2Int(cs81Value.Mid(04,02))%10);
				csDescriptor = csDisplay + _T("(��λMHz,�ֱ���0.1)(10����)");

			}

			 pGroup4->AddSubItem(new CMFCPropertyGridProperty (_T("��СӦ��ʱ��Ƶ��"),csDisplay,csDescriptor));
		}

		if (!cs83Value.IsEmpty())
		{
			pGroup4->AddSubItem(new CMFCPropertyGridProperty(_T("�����ڴ�Ĵ�С"),cs83Value,cs83Value));
		}
	}

	//m_wndPropList.AddProperty(pGroup4);
	pGroup4->AllowEdit(FALSE);

	return pGroup4;
}

CMFCPropertyGridProperty* CCardManageView::CreateC62PropList(CString csFCI)
{
	CString csC6Value;
	CString csPSDO,csDO,csPIN,csDisplay,csDescriptor;
	int iOff,iLen,iNum;

	iOff = 0;

	csC6Value = GetTLVData(csFCI,0x62);
	csC6Value = GetTLVData(csC6Value,0xC6);	
	CMFCPropertyGridProperty* pGroup5 = new CMFCPropertyGridProperty(_T("PIN��״̬"));

	if (!csC6Value.IsEmpty())
	{
		iLen   = csC6Value.GetLength();
		csPSDO = GetTLVData(csC6Value,0x90);
		csDO   = GetTLVData(csC6Value,0x95);

		if (!csPSDO.IsEmpty())
		{
			iOff += 6;
		}
		else
			return pGroup5;
		if (!csDO.IsEmpty())
		{
			iOff += 6;
		}
		csPIN.Empty();

		iNum  = (iLen- iOff)/6;

		for (int i = 0 ; i <iNum  ; i++)
		{
			csPIN = GetTLVData(csC6Value.Mid(iOff,iLen-iOff),0x83);

			if (!csPIN.IsEmpty())
			{
				if (((_CString2Int(csPSDO)<<i)&0x80) == 0x80)
				{
					csDisplay = _T("Enable"); 
					csDescriptor= _T("����"); 

				}
				else
				{
					csDisplay = _T("Disable"); 
					csDescriptor= _T("δ����"); 
				}


				pGroup5->AddSubItem(new CMFCPropertyGridProperty(_T("PIN ")+csPIN,csDisplay,csDescriptor));

			}
			else
			{
				csDisplay = _T("C6 ���ݲ����޷����");
				csDescriptor = _T("C6 ���ݲ��ִ��ڴ��󣬻�����������");
				pGroup5->AddSubItem(new CMFCPropertyGridProperty(_T("PIN "),csDisplay,csDescriptor));
			}

			iOff += 6;

			

		}

	}
	return pGroup5;
}

CMFCPropertyGridProperty* CCardManageView::_CreateBasicInformation2PropList(CString csFCI)
{
	CString csFID;

	int iFileType,iFileStru;
	CString csDisplay, csDescriptor;


	
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("������Ϣ"));
	CMFCPropertyGridProperty* pGroup;
	
	//FID
	csFID  = csFCI.Mid(0x08,04);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("�ļ���ʶ"),csFID, _T("File identifier :")+ csFID));

	iFileType = _CString2Int(csFCI.Mid(12,02));
	
	switch (iFileType)
	{
	case 00:

		csDisplay    = _T("����");
	//	csDescriptor = _T("����");
		break;
	case 01:
		csDisplay    = _T("MF");
	//	csDescriptor = _T("MF");
		break;
	case 02:
		csDisplay    = _T("DF");
	//	csDescriptor = _T("DF");
		break;
	case 04:
		csDisplay    = _T("EF");
	//	csDescriptor = _T("EF");
		break;
	default:
		break;
	}

	pGroup = new CMFCPropertyGridProperty(_T("�ļ����:"),csDisplay, _T("(GSM 11.11 see subclause 9.3):"));
	
	pGroup->AddOption(_T("MF"));
	pGroup->AddOption(_T("DF"));
	pGroup->AddOption(_T("EF"));
	pGroup->AllowEdit(FALSE);
	pGroup1->AddSubItem(pGroup);

	if (iFileType == 04)
	{
		iFileStru = _CString2Int(csFCI.Mid(26,02));
		switch (iFileStru)
		{
		case 00:
			csDisplay    = _T("͸���ļ�");
			//csDescriptor = _T("transparent");
			break;
		case 01:
			csDisplay    = _T("���Զ����ļ�");
			//csDescriptor = _T("linear fixed");
			break;
		case 03:
			csDisplay    = _T("ѭ���ļ�");
		//	csDescriptor = _T("cyclic");
			break;
		default:
			csDisplay    = _T("δ֪�ļ�");
		//	csDescriptor = _T("See you boss");
			break;
		}

		pGroup = new CMFCPropertyGridProperty(_T("�ļ��ṹ:"),csDisplay, _T(" (GSM 11.11 see subclause 9.3):"));

		pGroup->AddOption(_T("͸���ļ�"));
		pGroup->AddOption(_T("���Զ����ļ�"));
		pGroup->AddOption(_T("ѭ���ļ�"));
		pGroup->AllowEdit(FALSE);
		pGroup1->AddSubItem(pGroup);




	//	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("�ļ��ṹ:"),csDisplay, _T("Type of file  (GSM 11.11 see subclause 9.3):")+ csDescriptor));




		//�ļ���С
		csDisplay    = csFCI.Mid(04,04);
		csDescriptor = _T("͸��EF���ļ����峤�ȣ����Զ�����ѭ����EF����¼������¼���� / File size(for transparent EF: the length of the body part of the EF) (for linear fixed or cyclic EF: record length multiplied by the number of records of the EF)");
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("�ļ���С:"),csDisplay, csDescriptor));

		//�ļ�״̬

		switch (_CString2Int(csFCI.Mid(22,02))&0x05)
		{
		case 00:
			csDisplay    = _T("�ļ���Ч,���ļ���Чʱ����д���ܲ�����!");
		//	csDescriptor = _T("invalidatednot readable or updatable when invalidated!");
			break;
		case 01:
			csDisplay    = _T("�ļ���Ч,���ļ���Чʱ����д���ܲ�����!");
		//	csDescriptor = _T("not invalidated,readable and updatable when invalidated!");
			break;
		case 04:
			csDisplay    = _T("�ļ���Ч,���ļ���Чʱ����д��������!");
		//	csDescriptor = _T("invalidated,not readable or updatable when invalidated!");
			break;
		case 05:
			csDisplay    = _T("�ļ���Ч,���ļ���Чʱ����д��������!");
		//	csDescriptor = _T("not invalidated,readable and updatable when invalidated!");
			break;
		}


		pGroup = new CMFCPropertyGridProperty(_T("�ļ�״̬:"),csDisplay, _T(" (GSM 11.11 see subclause 9.3):"));

		pGroup->AddOption(_T("�ļ���Ч,���ļ���Чʱ����д���ܲ�����!"));
		pGroup->AddOption(_T("�ļ���Ч,���ļ���Чʱ����д���ܲ�����!"));
		pGroup->AddOption(_T("�ļ���Ч,���ļ���Чʱ����д��������!"));
		pGroup->AddOption(_T("�ļ���Ч,���ļ���Чʱ����д��������!"));
		pGroup->AllowEdit(FALSE);
		pGroup1->AddSubItem(pGroup);



	//	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("�ļ�״̬:"),csDisplay,  csDescriptor));

		if(iFileStru!=0)
		{
			csDisplay    = csFCI.Mid(28,02);
			csDescriptor = csFCI.Mid(28,02);
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("�ļ���¼����:"),csDisplay,  csDescriptor));
		}
	}
	else if ((iFileType == 01)||(iFileType == 02))
	{
		csDisplay    = csFCI.Mid(04,04);
		csDescriptor = _T("����ѡ���Ŀ¼���棬���ǲ������DF��EF�ġ�");
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Ŀ¼����:"),csDisplay,  csDescriptor));


		switch (_CString2Int(csFCI.Mid(26,02))&13)
		{
		case 00:csDisplay    =_T("������ʱ��ֹͣ");break;
		case 01:csDisplay    =_T("����ʱ��ֹͣ����û�����ȼ�");break;
		case 04:   csDisplay    =_T("������ʱ��ֹͣ�������ڵ͵�ƽ��"); break;
		case 05:   csDisplay    =_T("����ʱ��ֹͣ���ߵ�ƽ����");break;
		case 0x08: csDisplay    =_T("������ʱ��ֹͣ�������ڵ͵�ƽ��"); break;
		case 0x09: csDisplay    =_T("����ʱ��ֹͣ���͵�ƽ����");break;

		}

		pGroup = new CMFCPropertyGridProperty(_T("ʱ��ֹͣ:"),csDisplay, _T(" (GSM 11.11 see subclause 9.3):"));

		pGroup->AddOption(_T("������ʱ��ֹͣ"));
		pGroup->AddOption(_T("������ʱ��ֹͣ�������ڵ͵�ƽ��"));
		pGroup->AddOption(_T("������ʱ��ֹͣ�������ڸߵ�ƽ��"));
		pGroup->AddOption(_T("����ʱ��ֹͣ����û�����ȼ�"));
		pGroup->AddOption(_T("����ʱ��ֹͣ���͵�ƽ����"));
		pGroup->AddOption(_T("����ʱ��ֹͣ���ߵ�ƽ����"));
		pGroup->AllowEdit(FALSE);
		pGroup1->AddSubItem(pGroup);



	//	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("ʱ��ֹͣ:"),csDisplay,  csDescriptor));





		if (_CString2Int(csFCI.Mid(26,02))&2)
		{
			csDisplay    =_T("13/4MHZ");
			//csDescriptor =_T("13/4MHZ");
		}
		else
		{
			csDisplay    =_T("13/8MHZ");
		//	csDescriptor =_T("13/8MHZ");
		}

		pGroup = new CMFCPropertyGridProperty(_T("���м�Ȩ�㷨ʹ��Ƶ��:"),csDisplay, _T("  (GSM 11.11 see subclause 9.3):"));

		pGroup->AddOption(_T("13/4MHZ"));
		pGroup->AddOption(_T("13/8MHZ"));
		pGroup->AllowEdit(FALSE);
		pGroup1->AddSubItem(pGroup);

//		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("���м�Ȩ�㷨ʹ��Ƶ��:"),csDisplay,  csDescriptor));

		if (_CString2Int(csFCI.Mid(26,02))&0x80)
		{
			csDisplay    =_T("Disable");
			
		//	csDescriptor =_T("Enable");
		}
		else
		{
			csDisplay    =_T("Enable");
			//csDescriptor =_T("Disable");
		}

		pGroup = new CMFCPropertyGridProperty(_T("CHV1:"),csDisplay, _T(" (GSM 11.11 see subclause 9.3):"));

		pGroup->AddOption(_T("Enable"));
		pGroup->AddOption(_T("Disable"));
		pGroup->AllowEdit(FALSE);
		pGroup1->AddSubItem(pGroup);

		//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("CHV1:"),csDisplay,  csDescriptor));


		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Ŀ¼�µ�DF����:"),csFCI.Mid(28,02),  csDescriptor));
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Ŀ¼�µ�EF����:"),csFCI.Mid(30,02),  csDescriptor));



		//PIN1
		CMFCPropertyGridProperty* pGroup11 = new CMFCPropertyGridProperty(_T("CHV1״̬"),0,TRUE);

		if (_CString2Int(csFCI.Mid(36,02))&0x80)
		{
			csDisplay    =_T("�Ѿ���ʼ��");
		//	csDescriptor =_T("�Ѿ���ʼ��");
		}
		else
		{
			csDisplay    =_T("û�г�ʼ��");
		//	csDescriptor =_T("û�г�ʼ��");
		}


		pGroup = new CMFCPropertyGridProperty(_T("��ʼ��:"),csDisplay, _T(" (GSM 11.11 see subclause 9.3):"));

		pGroup->AddOption(_T("�Ѿ���ʼ��"));
		pGroup->AddOption(_T("û�г�ʼ��"));
		pGroup->AllowEdit(FALSE);
		pGroup11->AddSubItem(pGroup);

		//pGroup11->AddSubItem(new CMFCPropertyGridProperty(_T("��ʼ��:"),csDisplay, csDescriptor));


		csDisplay.Format("%d",_CString2Int(csFCI.Mid(36,02))&0xF);

		csDescriptor = csFCI.Mid(37,01);
		pGroup11->AddSubItem(new CMFCPropertyGridProperty(_T("ʣ�����:"),csDisplay, csDescriptor));

		pGroup1->AddSubItem(pGroup11);

		CMFCPropertyGridProperty* pGroup12 = new CMFCPropertyGridProperty(_T("PUK1״̬"),0,TRUE);




	
		//PIN2
		if (_CString2Int(csFCI.Mid(38,02))&0x80)
		{
			csDisplay    =_T("�Ѿ���ʼ��");
			csDescriptor =_T("�Ѿ���ʼ��");
		}
		else
		{
			csDisplay    =_T("û�г�ʼ��");
			csDescriptor =_T("û�г�ʼ��");
		}

		pGroup = new CMFCPropertyGridProperty(_T("��ʼ��:"),csDisplay, _T("  (GSM 11.11 see subclause 9.3):"));

		pGroup->AddOption(_T("�Ѿ���ʼ��"));
		pGroup->AddOption(_T("û�г�ʼ��"));
		pGroup->AllowEdit(FALSE);
		pGroup12->AddSubItem(pGroup);
	//	pGroup12->AddSubItem(new CMFCPropertyGridProperty(_T("��ʼ��:"),csDisplay, csDescriptor));


		csDisplay.Format("%d",_CString2Int(csFCI.Mid(38,02))&0xF);

		csDescriptor = csFCI.Mid(39,01);

		pGroup12->AddSubItem(new CMFCPropertyGridProperty(_T("ʣ�����:"),csDisplay, csDescriptor));

		pGroup1->AddSubItem(pGroup12);





		CMFCPropertyGridProperty* pGroup13 = new CMFCPropertyGridProperty(_T("CHV2״̬"),0,TRUE);

		if (_CString2Int(csFCI.Mid(40,02))&0x80)
		{
			csDisplay    =_T("�Ѿ���ʼ��");
			csDescriptor =_T("�Ѿ���ʼ��");
		}
		else
		{
			csDisplay    =_T("û�г�ʼ��");
			csDescriptor =_T("û�г�ʼ��");
		}

		pGroup = new CMFCPropertyGridProperty(_T("��ʼ��:"),csDisplay, _T(" (GSM 11.11 see subclause 9.3):"));

		pGroup->AddOption(_T("�Ѿ���ʼ��"));
		pGroup->AddOption(_T("û�г�ʼ��"));
		pGroup->AllowEdit(FALSE);
		pGroup13->AddSubItem(pGroup);

	//	pGroup13->AddSubItem(new CMFCPropertyGridProperty(_T("��ʼ��:"),csDisplay, csDescriptor));


		csDisplay.Format("%d",_CString2Int(csFCI.Mid(40,02))&0xF);

		csDescriptor = csFCI.Mid(41,01);
		pGroup13->AddSubItem(new CMFCPropertyGridProperty(_T("ʣ�����:"),csDisplay, csDescriptor));

		pGroup1->AddSubItem(pGroup13);




		CMFCPropertyGridProperty* pGroup14 = new CMFCPropertyGridProperty(_T("PUK2״̬"),0,TRUE);

		if (_CString2Int(csFCI.Mid(42,02))&0x80)
		{
			csDisplay    =_T("�Ѿ���ʼ��");
			csDescriptor =_T("�Ѿ���ʼ��");
		}
		else
		{
			csDisplay    =_T("û�г�ʼ��");
			csDescriptor =_T("û�г�ʼ��");
		}

	//	pGroup14->AddSubItem(new CMFCPropertyGridProperty(_T("��ʼ��:"),csDisplay, csDescriptor));

		pGroup = new CMFCPropertyGridProperty(_T("��ʼ��:"),csDisplay, _T(" (GSM 11.11 see subclause 9.3):"));

		pGroup->AddOption(_T("�Ѿ���ʼ��"));
		pGroup->AddOption(_T("û�г�ʼ��"));
		pGroup->AllowEdit(FALSE);
		pGroup14->AddSubItem(pGroup);
		csDisplay.Format("%d",_CString2Int(csFCI.Mid(42,02))&0xF);

		csDescriptor = csFCI.Mid(43,01);
		pGroup14->AddSubItem(new CMFCPropertyGridProperty(_T("ʣ�����:"),csDisplay, csDescriptor));

		pGroup1->AddSubItem(pGroup14);



	}


	
	
	return pGroup1;



}

CString TransactionAC(CString csAC)
{
	CString csResult;
	switch(_CString2Int(+csAC))
	{
	case 0:
		csResult = _T("ALWAYS");
		break;
	case 0xF:
		csResult = _T("NEVER");
		break;
	default:
		csResult = _T("CHV 0")+csAC;
		break;
	}
	return csResult;
}

CMFCPropertyGridProperty* CCardManageView::_CreateACCell(CString csCell,CString csValue)
{
	CMFCPropertyGridProperty* pGroup;
	pGroup =new CMFCPropertyGridProperty(csCell,csValue,csCell);
	pGroup->AddOption("ALWAYS");
	pGroup->AddOption("CHV 01");
	pGroup->AddOption("CHV 02");
	pGroup->AddOption("CHV 04");
	pGroup->AddOption("NEVER");
	pGroup->AddOption("....");
	pGroup->AllowEdit(FALSE);

	return pGroup;
}

CMFCPropertyGridProperty* CCardManageView::_CreateAC2PropList(CString csFCI)
{
	CString csDisplay;
	int iFileType;
	iFileType = _CString2Int(csFCI.Mid(12,02));
	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("�ļ�Ȩ��"));

	if(iFileType == 4)
	{
		csDisplay  = TransactionAC (csFCI.Mid(16,1));
		pGroup2->AddSubItem(_CreateACCell(_T("READ"),csDisplay));
		csDisplay = TransactionAC (csFCI.Mid(17,1));
		pGroup2->AddSubItem(_CreateACCell(_T("UPDATE"),csDisplay));
		csDisplay =TransactionAC (csFCI.Mid(18,1));
		pGroup2->AddSubItem(_CreateACCell(_T("INCREASE"),csDisplay));
		csDisplay = TransactionAC (csFCI.Mid(20,1));
		pGroup2->AddSubItem(_CreateACCell(_T("REHABILITATE"),csDisplay));
		csDisplay = TransactionAC (csFCI.Mid(21,1));	
		pGroup2->AddSubItem(_CreateACCell(_T("INVALIDATE"),csDisplay));
	}

	return pGroup2;

}

CMFCPropertyGridProperty* CCardManageView::_CreateFile2PropList(CString csFCI)
{
	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("�ļ�����"));
	int iFileType,iFileStru;
	int iSize, iRecLen,iRecNum;
	CString csNumber;


	iFileType = _CString2Int(csFCI.Mid(12,02));

	if (iFileType!= 04)
		return pGroup3;

	iFileStru = _CString2Int(csFCI.Mid(26,02));


	if (iFileStru == 0)
	{
		pGroup3->AddSubItem(new CMFCPropertyGridProperty(_T("����"),  _T(""), _T("")));
	}
	else if((iFileStru == 1)||(iFileStru == 3))
	{
		iSize   = _CString2Int(csFCI.Mid(04,04));
		iRecLen = _CString2Int(csFCI.Mid(28,02));
		iRecNum = iSize/iRecLen;

		for (int iNumber = 1 ; iNumber <= iRecNum; iNumber ++)
		{
			csNumber.Format("%02d",iNumber);
			pGroup3->AddSubItem(new CMFCPropertyGridProperty(csNumber,  _T(""), _T("")));
		}



	}
	pGroup3->AllowEdit(FALSE);

	return pGroup3;

}

void CCardManageView::SetFCI2PropList(CString csFCI)
{
	m_wndPropList.RemoveAll();

	if (csFCI.IsEmpty())
		return ;

	m_wndPropList.AddProperty(CreateBasicInformation2PropList(csFCI));
	m_wndPropList.AddProperty(CreateAC2PropList());

	m_wndPropList.AddProperty(CreateA52PropList(csFCI));
	m_wndPropList.AddProperty(CreateC62PropList(csFCI));

	m_wndPropData.RemoveAll();
	m_wndPropData.AddProperty(CreateFile2PropList(csFCI));

}

void CCardManageView::_SetFCI2PropList(CString csFCI)
{
	m_wndPropList.RemoveAll();
	if (csFCI.IsEmpty())
		return ;
	m_wndPropList.AddProperty(_CreateBasicInformation2PropList(csFCI));

	m_wndPropList.AddProperty(_CreateAC2PropList(csFCI));

	m_wndPropData.RemoveAll();
	m_wndPropData.AddProperty(_CreateFile2PropList(csFCI));



}

void CCardManageView::SetFile2PropList(CString csData)
{
	int iSum,iNum,iSipLen;
	int iLength,iOffset;
	CString csDes;

	CMFCPropertyGridProperty* pGroup3 = m_wndPropData.GetProperty(0);

	pGroup3->Show(TRUE);

	iSum = pGroup3->GetSubItemsCount();
	if (iSum == 0)
		return;

	iOffset = 0;
	iLength = csData.GetLength();
	iSipLen = iLength/iSum;
	for ( iNum = 0 ; iNum < iSum ; iNum += 1)
	{
		pGroup3->GetSubItem(iNum)->SetValue(csData.Mid(iNum*iSipLen,iSipLen));

		csDes  = csData.Mid(iNum*iSipLen,iSipLen);
		_AppendEnter(csDes);
		pGroup3->GetSubItem(iNum)->SetDescription(csDes);
	}
	

}

void CCardManageView::SetFileRecord2ProList(int iNumber,CString csRecord)
{
	CMFCPropertyGridProperty* pGroup = m_wndPropData.GetProperty(0);
	pGroup->Show(TRUE);

	int iSum = pGroup->GetSubItemsCount();

	iNumber = iNumber-1;
	if (iSum <= iNumber)
		return;

	pGroup->GetSubItem(iNumber)->SetValue(csRecord);
	//ExplainFileRecord(iNumber, csRecord);
	_AppendEnter(csRecord);
	pGroup->GetSubItem(iNumber)->SetDescription(csRecord);

	

}
void CCardManageView::ExplainFileRecord2ProList(int iNumber,CString csRecord)
{
	CMFCPropertyGridProperty* pGroup = m_wndPropData.GetProperty(0);


	//pGroup->Show(TRUE);

	//int iSum = pGroup->GetSubItemsCount();

	//iNumber = iNumber-1;
	//if (iSum <= iNumber)
	//	return;

	//pGroup->GetSubItem(iNumber)->SetValue(csRecord);
	//_AppendEnter(csRecord);
	//pGroup->GetSubItem(iNumber)->SetDescription(csRecord);

}




void CCardManageView::SetExpandedFormatSecurity2PropList(CString csData,bool bDF)
{
	CString csDisplay,csDescriptor;
	CMFCPropertyGridProperty* pGroup2 =  m_wndPropList.GetProperty(1);
	int iOther;


	if(!bDF)
	{
		csDisplay = GetACFromARR (01,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csDisplay,&csDescriptor);
		//pGroup2->AddSubItem(new CMFCPropertyGridProperty(,csDisplay,csDescriptor));	

		pGroup2->GetSubItem(0)->SetName(_T("READ,SEARCH"));
		pGroup2->GetSubItem(0)->SetValue(csDisplay);
		pGroup2->GetSubItem(0)->SetOriginalValue(csDisplay);
		pGroup2->GetSubItem(0)->SetDescription(csDescriptor);

		csDisplay = GetACFromARR (02,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csDisplay,&csDescriptor);
		//pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("UPDATE,ERASE"),csDisplay,csDescriptor));
		pGroup2->GetSubItem(1)->SetName(_T("UPDATE,ERASE"));
		pGroup2->GetSubItem(1)->SetValue(csDisplay);
		pGroup2->GetSubItem(1)->SetOriginalValue(csDisplay);
		pGroup2->GetSubItem(1)->SetDescription(csDescriptor);


		csDisplay = GetACFromARR (04,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csDisplay,&csDescriptor);
		pGroup2->GetSubItem(2)->SetName(_T("APPEND,WRITE"));
		pGroup2->GetSubItem(2)->SetValue(csDisplay);
		pGroup2->GetSubItem(2)->SetOriginalValue(csDisplay);
		pGroup2->GetSubItem(2)->SetDescription(csDescriptor);




		//pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("APPEND,WRITE"),csDisplay,csDescriptor));
		csDisplay = GetACFromARR (0x8,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csDisplay,&csDescriptor);

		pGroup2->GetSubItem(3)->SetName(_T("DEACTIVATE FILE"));
		pGroup2->GetSubItem(3)->SetValue(csDisplay);
		pGroup2->GetSubItem(3)->SetOriginalValue(csDisplay);
		pGroup2->GetSubItem(3)->SetDescription(csDescriptor);

		//pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("DEACTIVATE FILE"),csDisplay,csDescriptor));
		csDisplay = GetACFromARR (0x10,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csDisplay,&csDescriptor);
		pGroup2->GetSubItem(4)->SetName(_T("ACTIVATE FILE"));
		pGroup2->GetSubItem(4)->SetValue(csDisplay);
		pGroup2->GetSubItem(4)->SetOriginalValue(csDisplay);
		pGroup2->GetSubItem(4)->SetDescription(csDescriptor);

		//pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("ACTIVATE FILE"),csDisplay,csDescriptor));



		csDisplay = GetACFromARR (0x20,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csDisplay,&csDescriptor);

		pGroup2->GetSubItem(5)->SetName(_T("TERMINATE EF"));
		pGroup2->GetSubItem(5)->SetValue(csDisplay);
		pGroup2->GetSubItem(5)->SetOriginalValue(csDisplay);
		pGroup2->GetSubItem(5)->SetDescription(csDescriptor);
		//pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("TERMINATE EF"),csDisplay,csDescriptor));
		csDisplay = GetACFromARR (0x40,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csDisplay,&csDescriptor);

		pGroup2->GetSubItem(6)->SetName(_T("DELETE FILE"));
		pGroup2->GetSubItem(6)->SetValue(csDisplay);
		pGroup2->GetSubItem(6)->SetOriginalValue(csDisplay);
		pGroup2->GetSubItem(6)->SetDescription(csDescriptor);
		//pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("DELETE FILE"),csDisplay,csDescriptor));
	}
	else
	{
		csDisplay = GetACFromARR (0x1,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csDisplay,&csDescriptor);
		//pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("DELETE FILE"),csDisplay,csDescriptor));
		pGroup2->GetSubItem(0)->SetName(_T("DELETE FILE"));
		pGroup2->GetSubItem(0)->SetValue(csDisplay);
		pGroup2->GetSubItem(0)->SetOriginalValue(csDisplay);
		pGroup2->GetSubItem(0)->SetDescription(csDescriptor);



		csDisplay = GetACFromARR (0x2,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csDisplay,&csDescriptor);
		//pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("CREATE FILE(EF creation)"),csDisplay,csDescriptor));
		pGroup2->GetSubItem(1)->SetName(_T("CREATE FILE(EF creation)"));
		pGroup2->GetSubItem(1)->SetValue(csDisplay);
		pGroup2->GetSubItem(1)->SetOriginalValue(csDisplay);
		pGroup2->GetSubItem(1)->SetDescription(csDescriptor);




		csDisplay = GetACFromARR (0x4,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csDisplay,&csDescriptor);
		//pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("CREATE FILE(DF creation)"),csDisplay,csDescriptor));
		pGroup2->GetSubItem(2)->SetName(_T("CREATE FILE(DF creation)"));
		pGroup2->GetSubItem(2)->SetValue(csDisplay);
		pGroup2->GetSubItem(2)->SetOriginalValue(csDisplay);
		pGroup2->GetSubItem(2)->SetDescription(csDescriptor);




		csDisplay = GetACFromARR (0x8,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csDisplay,&csDescriptor);
		//pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("DEACTIVATE FILE"),csDisplay,csDescriptor));
		pGroup2->GetSubItem(3)->SetName(_T("DEACTIVATE FILE"));
		pGroup2->GetSubItem(3)->SetValue(csDisplay);
		pGroup2->GetSubItem(3)->SetOriginalValue(csDisplay);
		pGroup2->GetSubItem(3)->SetDescription(csDescriptor);




		csDisplay = GetACFromARR (0x10,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csDisplay,&csDescriptor);
		//pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("ACTIVATE FILE"),csDisplay,csDescriptor));
		pGroup2->GetSubItem(4)->SetName(_T("ACTIVATE FILE"));
		pGroup2->GetSubItem(4)->SetValue(csDisplay);
		pGroup2->GetSubItem(4)->SetOriginalValue(csDisplay);
		pGroup2->GetSubItem(4)->SetDescription(csDescriptor);


		csDisplay = GetACFromARR (0x20,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csDisplay,&csDescriptor);
		pGroup2->GetSubItem(5)->SetName(_T("TERMINATE CARD USAGE (MF), TERMINATE DF"));
		pGroup2->GetSubItem(5)->SetValue(csDisplay);
		pGroup2->GetSubItem(5)->SetOriginalValue(csDisplay);
		pGroup2->GetSubItem(5)->SetDescription(csDescriptor);

		//pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("TERMINATE CARD USAGE (MF), TERMINATE DF"),csDisplay,csDescriptor));
		csDisplay = GetACFromARR (0x40,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csDisplay,&csDescriptor)	;
		//pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("DELETE FILE (self)"),csDisplay,csDescriptor));

		pGroup2->GetSubItem(6)->SetName(_T("DELETE FILE (self)"));
		pGroup2->GetSubItem(6)->SetValue(csDisplay);
		pGroup2->GetSubItem(6)->SetOriginalValue(csDisplay);
		pGroup2->GetSubItem(6)->SetDescription(csDescriptor);

	}

	if(iOther)
	{
		csDisplay = GetACFromARR (0xFF,csData,&iOther);

		pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("Command ")+ csDisplay.Mid(00,02),csDisplay.Right(csDisplay.GetLength()-2),csDisplay.Right(csDisplay.GetLength()-2)));
	}

	m_wndPropList.ExpandAll();

}

void CCardManageView::InitPropList()
{


	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();




	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("������Ϣ"));

	m_wndPropList.AddProperty(pGroup1);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("�ļ�Ȩ��"));

	m_wndPropList.AddProperty(pGroup2);

	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("�ļ�����"));

	//pGroup3->AllowEdit(FALSE);

	m_wndPropList.AddProperty(pGroup3);




}

int CCardManageView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	GetClientRect(rectDummy);


	if (!m_wndPropTabs.Create(CMFCTabCtrl::STYLE_3D_VS2005 , rectDummy, this, IDC_CardManageViewTab,CMFCTabCtrl::LOCATION_BOTTOM))
	{
		TRACE0("δ�ܴ�������ѡ�����\n");
		return -1;      // δ�ܴ���
	}
	// �������:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN|WS_TABSTOP ;


	if (!m_wndPropList.Create(dwViewStyle, rectDummy,  &m_wndPropTabs, IDC_CardManagePropList))
	{
		TRACE0("δ�ܴ�����������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndPropData.Create(dwViewStyle, rectDummy,  &m_wndPropTabs, IDC_CardManagePropData))
	{
		TRACE0("δ�ܴ�����������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndPropExplain.Create(dwViewStyle, rectDummy, &m_wndPropTabs, IDC_CardManagePropExplain))
	{
		TRACE0("δ�ܴ�����������\n");
		return -1;      // δ�ܴ���
	}



	InitPropList();

	InitPropExpain();

	InitPropData();



	m_wndPropTabs.AddTab(&m_wndPropList, _T("�ļ�����"), (UINT)0);

	m_wndPropTabs.AddTab(&m_wndPropData, _T("�ļ�����"), (UINT)1);

	m_wndPropTabs.AddTab(&m_wndPropExplain, _T("�ļ�����"), (UINT)2);

	m_wndPropTabs.SetActiveTab(0);

	csPBR.Empty();
	iPBRLen = 0 ;



	return 0;
	
}

void CCardManageView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
		return;


	CRect rectClient;
	GetClientRect(rectClient);
//	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top , rectClient.Width(), rectClient.Height()-24, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
//	m_wndPropList.RedrawWindow();
//	.SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);



}

void CCardManageView::OnSize(UINT nType, int cx, int cy)
{
 	CView::OnSize(nType, cx, cy);

	m_wndPropTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	AdjustLayout();

}

BOOL CCardManageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	BOOL bRet;
	bRet = CView::PreCreateWindow(cs);

	return bRet;
}


// CCardManageView ����

void CCardManageView::OnDraw(CDC* pDC)
{
	CCardManageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_wndPropTabs.RedrawWindow();
	m_wndPropList.RedrawWindow();
	m_wndPropExplain.RedrawWindow();






}

void CCardManageView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCardManageView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCardManageView ���

#ifdef _DEBUG
void CCardManageView::AssertValid() const
{
	CView::AssertValid();
}

void CCardManageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCardManageDoc* CCardManageView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCardManageDoc)));
	return (CCardManageDoc*)m_pDocument;
}
#endif //_DEBUG


// //01 Read, 02 Update,03 Increate,04 Deactive,05 Active 

int CCardManageView::GetAC(int iOperate,bool bUICC)
{
	int iSum;
	int iResult;
	CString csAC;
	CMFCPropertyGridProperty* pGroup2;
	iSum = m_wndPropList.GetPropertyCount();
	if (iSum < 2 )
		return 0;

	pGroup2 = m_wndPropList.GetProperty(1);

	if (!bUICC)
	{
		if (iOperate==4)
			iOperate = 5;
		else if(iOperate==5)
			iOperate = 4;
		
	}

	if (pGroup2->GetSubItemsCount() < 5)
		return 0;

	csAC = pGroup2->GetSubItem(iOperate-1)->GetValue();
	_DeleteEnterSpace(csAC);

	if((csAC == _T("Always")||csAC == _T("ALWAYS")))
		iResult = 0;
	else if ((csAC == _T("NEVER"))||(csAC == _T("Never")))
		iResult = 0xF;
	else if(csAC.Left(03) == _T("PIN"))
	{
		csAC = csAC.Mid(03,02);
		iResult = _CString2Int(csAC);
	}
	else if (csAC.Left(03) == _T("CHV"))
	{
		csAC = csAC.Mid(03,csAC.GetLength()-3);
		iResult = _CString2Int(csAC);
	}
	else
		iResult = 0xF;
	return iResult;
	
}



// ����Ϊ����������
void CCardManageView::InitPropExpain(void)
{
	m_wndPropExplain.EnableHeaderCtrl(FALSE);
	m_wndPropExplain.EnableDescriptionArea();
	m_wndPropExplain.SetVSDotNetLook();
	m_wndPropExplain.MarkModifiedProperties();

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("�ļ�����"));
	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("���ݽ���"));
	m_wndPropExplain.AddProperty(pGroup1);
	m_wndPropExplain.AddProperty(pGroup2);

}

void CCardManageView::ExplainFile(int iFID,int iMark)
{
	if ((iFID == 0x00)&&
		(iMark == 0x00))
	{
		iFID  = __iFID;
		iMark = __iMARK;
	}
	else
	{
		ResetPBR();
	}
	m_wndPropExplain.RemoveAll();

	ExplainFID(iFID,iMark);

}

void CCardManageView::ExplainFileRecord(int iNumber, CString csRecord)
{

	CMFCPropertyGridProperty*  pSub;
	CMFCPropertyGridProperty* pGroup2;
	pGroup2 = m_wndPropExplain.GetProperty(1);


	switch(__iMARK)
	{
	case _DEF_Card:pSub = Explain_FileData_InMF(csRecord,__iFID,iNumber,TRUE);break;
		//GSM
	case _DEF_GSM: pSub = Explain_FileData_InGSM(csRecord,__iFID,iNumber,TRUE);break;
		//USIM
	case _DEF_3GPP:pSub = Explain_FileData_In3GPP(csRecord,__iFID,iNumber,TRUE);break;
		//CSIM
	case _DEF_3GPP2:pSub = Explain_FileData_In3GPP2(csRecord,__iFID,iNumber,TRUE);break;
		//CDMA
	case _DEF_CDMA:pSub = Explain_FileData_InCDMA(csRecord,__iFID,iNumber,TRUE);break;
		//Telecom
	case _DEF_Tele:pSub = Explain_FileData_InTelecom(csRecord,__iFID,iNumber,TRUE);break;
	case _DEF_GSMACCESS:pSub = Explain_FileData_InGSMACCESS(csRecord,__iFID,iNumber,TRUE);break;
	case _DEF_MMSS:pSub = Explain_FileData_InMMSS(csRecord,__iFID,iNumber,TRUE);break;
	case _DEF_PHONEBOOK:pSub = Explain_FileData_InPhoneBook(csRecord,__iFID,iNumber,TRUE);break;
	default:pSub = NULL;break;
	}

	
	if (pSub != NULL)
		//pGroup2->RemoveSubItem()
		pGroup2->AddSubItem(pSub);

	//m_wndPropExplain.GetProperty()
	//m_wndPropExplain.AddProperty(pGroup2);
	//pGroup2->Redraw();
	//m_wndPropExplain
	//m_wndPropExplain.RedrawWindow();
}



bool CCardManageView::ExplainFID(int iFID, int iMark)
{
	bool bRet;

	//�˴�Ԥ�ȴ洢����;
	__iFID  = iFID;
	__iMARK = iMark;

	switch(iMark)
	{
	case _DEF_Card:
		bRet =ExplainCard(iFID);
		break;
		//GSM
	case _DEF_GSM:
		bRet = ExplainGSM(iFID);
		break;

		//USIM
	case _DEF_3GPP:
		bRet = Explain3GPP(iFID);

		break;
		//CSIM
	case _DEF_3GPP2:
		bRet = Explain3GPP2(iFID);

		break;
		//CDMA
	case _DEF_CDMA:
		bRet = ExplainCDMA(iFID);
		break;
		//Telecom
	case _DEF_Tele:
		bRet = ExplainTelecom(iFID);
		break;

	case _DEF_GSMACCESS:
		bRet = ExplainGSMACCESS(iFID);
		break;

	case _DEF_MMSS:
		bRet = ExplainMMSS(iFID);
		break;

	case _DEF_PHONEBOOK:
		bRet = ExplainPhonebook(iFID);
		break;

	default:
		bRet = 0;
		break;
	}

	return bRet;
}

bool CCardManageView::ExplainGSM(int iFID)
{
	CString csName;
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup2;
	CMFCPropertyGridProperty*  pSub;
	int iRet,iCyc;

	pGroup1 = new CMFCPropertyGridProperty(_T("�ļ�����"));
	pGroup2 = new CMFCPropertyGridProperty(_T("���ݽ���"));

	iRet = GetRecordNumber4PropList();


	for (iCyc = 0 ; iCyc < iRet ; iCyc++)
	{
		pSub = Explain_FileData_InGSM(GetData4PropList(iCyc),iFID,iCyc+ (iRet>1),TRUE);
		if (pSub != NULL)
			pGroup2->AddSubItem(pSub);
	}
	
	if (!GetFileNameFromReference(iFID,_DEF_GSM,csName))
		csName = _T("Unknow");

	//if (!GenerateEFNameInGSM(iFID,csName,false))
	//	csName = _T("Unknow");
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("File Name"),csName,csName));
	m_wndPropExplain.AddProperty(pGroup1);
	ExpandChildProperty(pGroup2);
	m_wndPropExplain.AddProperty(pGroup2);

	return true;
}

bool CCardManageView::ExplainUSIM(int iFID)
{
	

	return Explain3GPP(iFID);
}

bool CCardManageView::ExplainCSIM(int iFID)
{
	return Explain3GPP2(iFID);
}

bool CCardManageView::ExplainCDMA(int iFID)
{
	CString csName;
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup2;
	CMFCPropertyGridProperty*  pSub;
	int iRet,iCyc;

	pGroup1 = new CMFCPropertyGridProperty(_T("�ļ�����"));
	pGroup2 = new CMFCPropertyGridProperty(_T("���ݽ���"));

	iRet = GetRecordNumber4PropList();


	for (iCyc = 0 ; iCyc < iRet ; iCyc++)
	{
		pSub = Explain_FileData_InCDMA(GetData4PropList(iCyc),iFID,iCyc+ (iRet>1),TRUE);
		if (pSub != NULL)
			pGroup2->AddSubItem(pSub);
	}

	//if (!GenerateEFNameInCDMA(iFID,csName,false))
	//	csName = _T("Unknow");
	if (!GetFileNameFromReference(iFID,_DEF_CDMA,csName))
		csName = _T("Unknow");
		
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("File name"),csName,csName));
	m_wndPropExplain.AddProperty(pGroup1);
	ExpandChildProperty(pGroup2);
	m_wndPropExplain.AddProperty(pGroup2);
	return true;
}

bool CCardManageView::Explain3GPP(int iFID)
{
	CString csName;
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup2;
	CMFCPropertyGridProperty*  pSub;
	int iRet,iCyc;

	pGroup1 = new CMFCPropertyGridProperty(_T("�ļ�����"));
	pGroup2 = new CMFCPropertyGridProperty(_T("���ݽ���"));

	iRet = GetRecordNumber4PropList();
	
	for (iCyc = 0 ; iCyc < iRet ; iCyc++)
	{
		pSub = Explain_FileData_In3GPP(GetData4PropList(iCyc),iFID,iCyc+ (iRet>1),TRUE);
		if (pSub != NULL)
			pGroup2->AddSubItem(pSub);
	}
	//if (!GenerateEFNameIn3GPP(iFID,csName,false))
	//	csName = _T("Unknow");

    if (!GetFileNameFromReference(iFID,_DEF_3GPP,csName))
		csName = _T("Unknow");
   
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("File Name"),csName,csName));
	m_wndPropExplain.AddProperty(pGroup1);
	ExpandChildProperty(pGroup2);
	m_wndPropExplain.AddProperty(pGroup2);
	return true;
}

bool CCardManageView::Explain3GPP2(int iFID)
{
	CString csName;
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup2;
	CMFCPropertyGridProperty* pSub;
	int iRet,iCyc;

	pGroup1 = new CMFCPropertyGridProperty(_T("�ļ�����"));
	pGroup2 = new CMFCPropertyGridProperty(_T("���ݽ���"));

	iRet = GetRecordNumber4PropList();

	for (iCyc = 0 ; iCyc < iRet ; iCyc++)
	{
		pSub = Explain_FileData_In3GPP2(GetData4PropList(iCyc),iFID,iCyc+ (iRet>1),TRUE);
		if (pSub != NULL)
			pGroup2->AddSubItem(pSub);
	}
		

	//if (!GenerateEFNameIn3GPP2(iFID,csName,false))
	//	csName = _T("Unknow");

	if (!GetFileNameFromReference(iFID,_DEF_3GPP2,csName))
		csName = _T("Unknow");
		
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("File name"),csName,csName));
	m_wndPropExplain.AddProperty(pGroup1);
	ExpandChildProperty(pGroup2);
	m_wndPropExplain.AddProperty(pGroup2);
	return true;
}

bool CCardManageView::ExplainCard(int iFID)
{
	CString csName;
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup2;
	CMFCPropertyGridProperty*  pSub;
	int iRet,iCyc;

	pGroup1 = new CMFCPropertyGridProperty(_T("�ļ�����"));
	pGroup2 = new CMFCPropertyGridProperty(_T("���ݽ���"));

	iRet = GetRecordNumber4PropList();


	for (iCyc = 0 ; iCyc < iRet ; iCyc++)
	{
		pSub = Explain_FileData_InMF(GetData4PropList(iCyc),iFID,iCyc+ (iRet>1),TRUE);
		if (pSub != NULL)
			pGroup2->AddSubItem(pSub);
	}

	//if (!GenerateEFNameInMF(iFID,csName,false))
	//	csName = _T("Unknow");

	if (!GetFileNameFromReference(iFID,_DEF_Card,csName))
		csName = _T("Unknow");
		
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("File name"),csName,csName));
	m_wndPropExplain.AddProperty(pGroup1);
	ExpandChildProperty(pGroup2);
	m_wndPropExplain.AddProperty(pGroup2);
	return true;
}

bool CCardManageView::ExplainTelecom(int iFID)
{
	CString csName;
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup2;
	CMFCPropertyGridProperty*  pSub;
	int iRet,iCyc;
	iRet = GetRecordNumber4PropList();
	pGroup1 = new CMFCPropertyGridProperty(_T("�ļ�����"));
	pGroup2 = new CMFCPropertyGridProperty(_T("���ݽ���"));

	for (iCyc = 0 ; iCyc < iRet ; iCyc++)
	{
		pSub = Explain_FileData_InTelecom(GetData4PropList(iCyc),iFID,iCyc+ (iRet>1),TRUE);
		if (pSub != NULL)
			pGroup2->AddSubItem(pSub);
	}

	//if (!GenerateEFNameInTelecom(iFID,csName,false))
	//	csName = _T("Unknow");

	if (!GetFileNameFromReference(iFID,_DEF_Tele,csName))
		csName = _T("Unknow");
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("File name"),csName,csName));
	m_wndPropExplain.AddProperty(pGroup1);
	ExpandChildProperty(pGroup2);
	m_wndPropExplain.AddProperty(pGroup2);
	return true;

}

bool CCardManageView::ExplainMMSS(int iFID)
{
	CString csName;
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup2;
	CMFCPropertyGridProperty*  pSub;
	int iRet;
	iRet = GetRecordNumber4PropList();
	pGroup1 = new CMFCPropertyGridProperty(_T("�ļ�����"));
	pGroup2 = new CMFCPropertyGridProperty(_T("���ݽ���"));


	pSub = Explain_FileData_InMMSS(GetData4PropList(0),iFID,0,FALSE);
	if (pSub != NULL)
		pGroup2->AddSubItem(pSub);


	//if (!GenerateEFNameInMMSS(iFID,csName,false))
	//	csName = _T("Unknow");

	if (!GetFileNameFromReference(iFID,_DEF_MMSS,csName))
		csName = _T("Unknow");

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("File name"),csName,csName));
	m_wndPropExplain.AddProperty(pGroup1);
	ExpandChildProperty(pGroup2);
	m_wndPropExplain.AddProperty(pGroup2);

	return true;
}

bool CCardManageView::ExplainPhonebook(int iFID)
{
	CString csName,csAbbreviation,csTemp;
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup2;
	int iRet,iNumber,iCyc;
	iNumber = GetRecordNumber4PropList();
	pGroup1 = new CMFCPropertyGridProperty(_T("�ļ�����"));
	pGroup2 = new CMFCPropertyGridProperty(_T("���ݽ���"));

	CMainFrame * CurMainFrm =( CMainFrame *) AfxGetApp()->GetMainWnd();

	if (iFID == 0x4F30)
	{
		csAbbreviation = _T("PBR");
		csName         = _T("Phone Book Reference");
		for (iCyc = 0 ; iCyc < iNumber ; iCyc++)
			pGroup2->AddSubItem(Explain_PBRData(GetData4PropList(iCyc),iCyc+1));
	}
	else if((iFID&0xFF00) == 0x4F00)
	{
		iRet = ExplainPhonebookFile(iFID);

		switch(iRet&0xFF)
		{
		case 0xC0:
			csTemp.Format("%02d",iRet/0x100+1);
			csAbbreviation = _T("AND ")+csTemp;
			csName         = _T("Abbreviated dialling numbers")+csTemp;
			for (iCyc = 0 ; iCyc < iNumber ; iCyc++)
				pGroup2->AddSubItem(ExplainADNData(GetData4PropList(iCyc),iCyc+1));
			break;
		case 0xC1:
			csTemp.Format("%02d",iRet/0x100+1);
			csAbbreviation = _T("IAP ")+csTemp;
			csName         = _T("Index Administration Phone book")+csTemp;
			for (iCyc = 0 ; iCyc < iNumber ; iCyc++)
				pGroup2->AddSubItem(Explain_IAPData(GetData4PropList(iCyc),iCyc+1));
			break;
		case 0xC2:
			csTemp.Format("%02d",iRet/0x100+1);
			csAbbreviation = _T("EXT ");
			csName         = _T("Extension");
			for (iCyc = 0 ; iCyc < iNumber ; iCyc++)
				pGroup2->AddSubItem(ExplainEXTData(GetData4PropList(iCyc),iCyc+1));
			break;
		case 0xC3:
			csTemp.Format("%02d",iRet/0x100+1);
			csAbbreviation = _T("SNE ")+csTemp;
			csName         = _T("Second Name Entry")+csTemp;
			for (iCyc = 0 ; iCyc < iNumber ; iCyc++)
				pGroup2->AddSubItem(Explain_SNEData(GetData4PropList(iCyc),iCyc+1));
			break;
		case 0xC4:
			csTemp.Format("%02d",iRet/0x100+1);
			csAbbreviation = _T("ANR ")+csTemp;
			csName         = _T("Additional Number")+csTemp;
			for (iCyc = 0 ; iCyc < iNumber ; iCyc++)
				pGroup2->AddSubItem(Explain_ANRData(GetData4PropList(iCyc),iCyc+1));
			break;
		case 0xC5:
			csTemp.Format("%02d",iRet/0x100+1);
			csAbbreviation = _T("PBC ")+csTemp;
			csName         = _T("Phone Book Control")+csTemp;
			for (iCyc = 0 ; iCyc < iNumber ; iCyc++)
				pGroup2->AddSubItem(Explain_PBCData(GetData4PropList(iCyc),iCyc+1));
			break;
		case 0xC6:
			csTemp.Format("%02d",iRet/0x100+1);
			csAbbreviation = _T("GRP ")+csTemp;
			csName         = _T("Grouping file")+csTemp;
			for (iCyc = 0 ; iCyc < iNumber ; iCyc++)
				pGroup2->AddSubItem(Explain_GRPData(GetData4PropList(iCyc),iCyc+1));
			break;
		case 0xC7:
			csTemp.Format("%02d",iRet/0x100+1);
			csAbbreviation = _T("AAS ");
			csName         = _T("Additional number Alpha String");
			for (iCyc = 0 ; iCyc < iNumber ; iCyc++)
				pGroup2->AddSubItem(Explain_AASData(GetData4PropList(iCyc),iCyc+1));
			break;
		case 0xC8:
			csTemp.Format("%02d",iRet/0x100+1);
			csAbbreviation = _T("GAS ");
			csName         = _T("Grouping information Alpha String");
			for (iCyc = 0 ; iCyc < iNumber ; iCyc++)
				pGroup2->AddSubItem(Explain_GASData(GetData4PropList(iCyc),iCyc+1));
			break;
		case 0xC9:
			csTemp.Format("%02d",iRet/0x100+1);
			csAbbreviation = _T("UID ")+csTemp;
			csName         = _T("Unique Identifier")+csTemp;
			for (iCyc = 0 ; iCyc < iNumber ; iCyc++)
				pGroup2->AddSubItem(Explain_UIDData(GetData4PropList(iCyc),iCyc+1));
			break;
		case 0xCA:
			csTemp.Format("%02d",iRet/0x100+1);
			csAbbreviation = _T("EMAIL ")+csTemp;
			csName         = _T("EMAIL")+csTemp;
			for (iCyc = 0 ; iCyc < iNumber ; iCyc++)
				pGroup2->AddSubItem(Explain_EMAILData(GetData4PropList(iCyc),iCyc+1));
			break;

		case 0xCB:
			csTemp.Format("%02d",iRet/0x100+1);
			csAbbreviation = _T("CPP ");
			csName         = _T("Capability Configuration Parameters ");
			for (iCyc = 0 ; iCyc < iNumber ; iCyc++)
				pGroup2->AddSubItem(Explain_CPP1Data(GetData4PropList(iCyc),iCyc+1));
				break;
		default:
			break;
		}

	}



	CurMainFrm->ChangeFileDesInClassTree(_T( "7F10||5F3A||" )+ Int2CString(iFID,4),csAbbreviation);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("File Name"),csAbbreviation,csName));
	m_wndPropExplain.AddProperty(pGroup1);
	ExpandChildProperty(pGroup2);
	m_wndPropExplain.AddProperty(pGroup2);



	return true;
}

bool CCardManageView::ExplainGSMACCESS(int iFID)
{
	CString csName,csAbbreviation;
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup2;
	CMFCPropertyGridProperty*  pSub;
	int iRet;
	iRet = GetRecordNumber4PropList();
	pGroup1 = new CMFCPropertyGridProperty(_T("�ļ�����"));
	pGroup2 = new CMFCPropertyGridProperty(_T("���ݽ���"));

	pSub = Explain_FileData_InGSMACCESS(GetData4PropList(0),iFID,0,FALSE);
	if (pSub != NULL)
		pGroup2->AddSubItem(pSub);


	//if (!GenerateEFNameInGSMAccess(iFID,csName,false))
	//	csName = _T("Unknow");

	if (!GetFileNameFromReference(iFID,_DEF_GSMACCESS,csName))
		csName = _T("Unknow");

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("File name"),csName,csName));
	m_wndPropExplain.AddProperty(pGroup1);
	m_wndPropExplain.AddProperty(pGroup2);
	return true;
}

int CCardManageView::GetRecordNumber4PropList(void)
{
	CString csName;
	int iSum;
	iSum = m_wndPropData.GetPropertyCount();
	if (iSum < 1)
		return -1;
	CMFCPropertyGridProperty* pGroup;

	//�ļ�����8
	pGroup = m_wndPropData.GetProperty(0);

	csName = pGroup->GetName();
	//if (csName != _T("�ļ�����"))
	//	return -2;

	iSum = pGroup->GetSubItemsCount() ;
	if (iSum<1 )
		return -4;
	return iSum;
}

CString CCardManageView::GetData4PropList(int iNumber)
{
	CString csResult;
	csResult.Empty();
	int iSum;
	iSum = m_wndPropData.GetPropertyCount();
	if (iSum < 1)
		return csResult;
	CMFCPropertyGridProperty* pGroup;
	CMFCPropertyGridProperty* pGroup1;
	//�ļ�����8
	pGroup = m_wndPropData.GetProperty(0);


	iSum = pGroup->GetSubItemsCount() ;
	if (iSum<=iNumber )
		return csResult;


	pGroup1  = pGroup->GetSubItem(iNumber);

	csResult = pGroup1->GetValue();

	return csResult;
}
void CCardManageView::ResetPBR(void)
{

	iPBRLen = 0;
	csPBR.Empty();
}


int  CCardManageView::ExplainPhonebookFile(int iFID)
{
	CString csFCI,csDate,csTemp,csTemp1;
	int iRecLen,iNumber,iType;
	CMainFrame *CurMainFrm;
	CurMainFrm =(CMainFrame*)AfxGetApp()->GetMainWnd();
	iType = 0;
	bool bSelOther = false;
	if ((csPBR.IsEmpty()) || (iPBRLen == 0))
	{
		bSelOther = true;
		if (!CurMainFrm->_TestCaseSelectFile(_T("4F30"), csFCI, CurMainFrm->bIsUICC))
		{
			return iType;
		}
		else
		{

			csDate = CurMainFrm->_TestCaseReadCurrentFileData_UICC(csFCI);
			iRecLen = CurMainFrm->_GetRecordLength(csFCI);
			iNumber = CurMainFrm->_GetRecordNumber(csFCI);
			iPBRLen = iRecLen;
			csPBR = csDate;
			iType = 0;
		}
	}
	else
		iNumber = csPBR.GetLength() / (2 * iPBRLen);



	for (int i = 0; i < iNumber; i++)
	{

		csTemp = csPBR.Mid(i * iPBRLen * 2, iPBRLen * 2);
		_WipeEmpty(csTemp);
		csTemp1 = GetTLVData(csTemp, 0xA8);
		if (!csTemp1.IsEmpty())
		{
			for (int j = 0xC0; j < 0xCF; j++)
			{
				if ((_CString2Int(GetTLVData(csTemp1, j)) / 0x100) == iFID)
					iType = i * 0x100 + j;
			}
		}
		csTemp1 = GetTLVData(csTemp, 0xA9);
		if (!csTemp1.IsEmpty())
		{
			for (int j = 0xC0; j < 0xCF; j++)
			{
				if ((_CString2Int(GetTLVData(csTemp1, j)) / 0x100) == iFID)
					iType = i * 0x100 + j;
			}
		}
		csTemp1 = GetTLVData(csTemp, 0xAA);
		if (!csTemp1.IsEmpty())
		{
			for (int j = 0xC0; j < 0xCF; j++)
			{
				if ((_CString2Int(GetTLVData(csTemp1, j)) / 0x100) == iFID)
					iType = i * 0x100 + j;
			}
		}

	}
	if (bSelOther)
	{
		csTemp.Format("%02x", iFID);

		CurMainFrm->_TestCaseSelectFile(csTemp, csFCI, CurMainFrm->bIsUICC);
	}


	return iType;
}



CMFCPropertyGridProperty* CCardManageView::Explain_PBRData(CString csData,int iNumber)
{
	CMFCPropertyGridProperty *pGroup1;
	CString csNumber;
	CString csPresence,csFile,csName,csPath;

	csPath = _T( "7F10||5F3A||" );

	CMainFrame*CurMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();

	pGroup1 = new CMFCPropertyGridProperty(_T("PBR ")+csNumber,0,1);

	csNumber.Format("%02d",iNumber);

	_WipeEmpty(csData);
	if (csData.IsEmpty())
		return pGroup1;



	csPresence = GetTLVData(csData,0xA8);
	csFile     = GetTLVData(csPresence,0xC0);

	if (!csFile.IsEmpty())
	{
		csName  = _T("ADN ")+csNumber;

		CurMainFrm->ChangeFileDesInClassTree(csPath+ csFile.Mid(0,4),csName);

		pGroup1->AddSubItem(Explain_FileInPBRData(csFile,csName));
	}

	csFile     = GetTLVData(csPresence,0xC1);
	if (!csFile.IsEmpty())
	{

		csName  = _T("IAP ")+csNumber;

		CurMainFrm->ChangeFileDesInClassTree(csPath+ csFile.Mid(0,4),csName);

		pGroup1->AddSubItem(Explain_FileInPBRData(csFile,csName));
	}

	csFile     = GetTLVData(csPresence,0xC4);
	if (!csFile.IsEmpty())
	{
		csName  = _T("ANR ")+csNumber;

		CurMainFrm->ChangeFileDesInClassTree(csPath+ csFile.Mid(0,4),csName);

		pGroup1->AddSubItem(Explain_FileInPBRData(csFile,csName));
	}

	csFile     = GetTLVData(csPresence,0xC5);
	if (!csFile.IsEmpty())
	{
		csName  = _T("PBC ")+csNumber;

		CurMainFrm->ChangeFileDesInClassTree(csPath+ csFile.Mid(0,4),csName);

		pGroup1->AddSubItem(Explain_FileInPBRData(csFile,csName));
	}

	csFile     = GetTLVData(csPresence,0xC6);
	if (!csFile.IsEmpty())
	{
		csName  = _T("GRP ")+csNumber;

		CurMainFrm->ChangeFileDesInClassTree(csPath+ csFile.Mid(0,4),csName);

		pGroup1->AddSubItem(Explain_FileInPBRData(csFile,csName));
	}
	csFile     = GetTLVData(csPresence,0xC9);
	if (!csFile.IsEmpty())
	{
		csName  = _T("UID ")+csNumber;

		CurMainFrm->ChangeFileDesInClassTree(csPath+ csFile.Mid(0,4),csName);

		pGroup1->AddSubItem(Explain_FileInPBRData(csFile,csName));
	}

	csFile     = GetTLVData(csPresence,0xCA);
	if (!csFile.IsEmpty())
	{
		csName  = _T("EMAIL ")+csNumber;

		CurMainFrm->ChangeFileDesInClassTree(csPath+ csFile.Mid(0,4),csName);

		pGroup1->AddSubItem(Explain_FileInPBRData(csFile,csName));
	}


	csPresence = GetTLVData(csData,0xA9);

	csFile     = GetTLVData(csPresence,0xC3);
	if (!csFile.IsEmpty())
	{
		csName  = _T("SNE ")+csNumber;

		CurMainFrm->ChangeFileDesInClassTree(csPath+ csFile.Mid(0,4),csName);

		pGroup1->AddSubItem(Explain_FileInPBRData(csFile,csName));
	}
	csFile     = GetTLVData(csPresence,0xC4);
	if (!csFile.IsEmpty())
	{
		csName  = _T("ANR ")+csNumber;

		CurMainFrm->ChangeFileDesInClassTree(csPath+ csFile.Mid(0,4),csName);

		pGroup1->AddSubItem(Explain_FileInPBRData(csFile,csName));
	}
	csFile     = GetTLVData(csPresence,0xCA);
	if (!csFile.IsEmpty())
	{
		csName  = _T("EMAIL ")+csNumber;

		CurMainFrm->ChangeFileDesInClassTree(csPath+ csFile.Mid(0,4),csName);

		pGroup1->AddSubItem(Explain_FileInPBRData(csFile,csName));
	}

	csPresence = GetTLVData(csData,0xAA);
	csFile     = GetTLVData(csPresence,0xC2);
	if (!csFile.IsEmpty())
	{
		csName  = _T("EXT ");

		CurMainFrm->ChangeFileDesInClassTree(csPath+ csFile.Mid(0,4),csName);

		pGroup1->AddSubItem(Explain_FileInPBRData(csFile,csName));
	}

	csFile     = GetTLVData(csPresence,0xC7);
	if (!csFile.IsEmpty())
	{
		csName  = _T("AAS ");

		CurMainFrm->ChangeFileDesInClassTree(csPath+ csFile.Mid(0,4),csName);

		pGroup1->AddSubItem(Explain_FileInPBRData(csFile,csName));
	}
	csFile     = GetTLVData(csPresence,0xC8);
	if (!csFile.IsEmpty())
	{
		csName  = _T("GAS ");

		CurMainFrm->ChangeFileDesInClassTree(csPath+ csFile.Mid(0,4),csName);

		pGroup1->AddSubItem(Explain_FileInPBRData(csFile,csName));
	}

	csFile     = GetTLVData(csPresence,0xCB);
	if (!csFile.IsEmpty())
	{
		csName  = _T("CPP ");

		CurMainFrm->ChangeFileDesInClassTree(csPath+ csFile.Mid(0,4),csName);

		pGroup1->AddSubItem(Explain_FileInPBRData(csFile,csName));
	}

	return pGroup1;
}

// �޸�����
int CCardManageView::UpdateFonts(void)
{
	 m_wndPropList.SetFont(&afxGlobalData.fontRegular);
	 m_wndPropExplain.SetFont(&afxGlobalData.fontRegular);
	return 0;
}

afx_msg LRESULT CCardManageView::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{

	if (ExcutionPropChanged(wParam,(CMFCPropertyGridProperty*)lParam) < 0)
	{
		AfxMessageBox("ִ���޸Ĳ���ʧ��");
	}
	return 0;
}




BEGIN_MESSAGE_MAP(CTabSel, CMFCTabCtrl)
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, &CTabSel::OnPropertyChanged)
END_MESSAGE_MAP()

// CTabSel ��Ϣ�������
afx_msg LRESULT CTabSel::OnPropertyChanged(WPARAM wParam, LPARAM lParam)
{

	GetOwner()->SendMessage(AFX_WM_PROPERTY_CHANGED,wParam, lParam);
	return 0;
}

// C:\��д����\CardManage\CardManage\CardManageView.cpp : ʵ���ļ�
//


// CInput2Prop �Ի���

IMPLEMENT_DYNAMIC(CInput2Prop, CDialogEx)

CInput2Prop::CInput2Prop(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInput2Prop::IDD, pParent)
{

	iMin = 0;
	iMax = 100;
	bLarge = false;

}

CInput2Prop::~CInput2Prop()
{
}



void CInput2Prop::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	SetDlgItemText(IDC_Input_Edit,csDefault);
}


void CInput2Prop ::SetInputDataSize(UINT uiMin,UINT uiMax)
{
	iMin = uiMin;
	iMax = uiMax;
	if (iMax> 100)
		bLarge = true;
	else
		bLarge = false;
}
CString CInput2Prop ::GetInputData()
{
	return csDefault;
}
void CInput2Prop ::SetInputData(CString csInput)
{
	csDefault = csInput;

}
void CInput2Prop::OnBnClickedOk()
{
	CString csInput;
	GetDlgItemText(IDC_Input_Edit,csInput);
	_DeleteEnterSpace(csInput);
	UINT iLength = csInput.GetLength();


	if ((iLength>iMax)||(iLength<iMin))
		MessageBox(_T("�������ݴ�С����"));
	else
	{
		GetDlgItemText(IDC_Input_Edit,csDefault);
		CDialogEx::OnOK();
	}

}
BOOL CInput2Prop::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
int CInput2Prop::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	

	if (CDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


BEGIN_MESSAGE_MAP(CInput2Prop, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInput2Prop::OnBnClickedOk)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// �ļ�FCI���޸�



int CCardManageView::ExcutionPropChanged(WPARAM wParam,CMFCPropertyGridProperty* lParam)
{
	int iRet ;
	iRet = ExcutionUICCChange(wParam,lParam);

	return 0;
}

int CCardManageView::ExcutionPropListChanged(CMFCPropertyGridProperty* lParam)
{

	BYTE ucPath[10];
	ZeroMemory(ucPath ,10);
	int iRet = GetPropertyCourtPath(IDC_CardManagePropList,lParam,ucPath);


	return 0;
}
// UICC�µ��޸�
int CCardManageView::ExcutionUICCChange(WPARAM wParam,CMFCPropertyGridProperty* lParam)
{
	BYTE ucPath[10];
	ZeroMemory(ucPath,10);
	//int iLen = 0;
	int iLen = GetPropertyCourtPath((int)wParam,lParam,ucPath);
	int iRet;
	if (iLen <= 0)
		return iLen;

	switch(ucPath[0])
	{
	case 00:
		iRet = ExcutionUICCBasInfo((int)wParam,lParam,ucPath);
		break;
	case 01:
		iRet = ExcutionUICCFileAC((int)wParam,lParam,ucPath);
		break;
	case 02:
		iRet = ExcutionUICCFileData((int)wParam,lParam,ucPath);
		break;
	case 03:

		break;
	case 04:

		break;
	default:
		break;
	}



	m_wndPropList.RedrawWindow();
	return 0;
}



// ��ȡ��ǰ�ڸ��ϵĵڼ�����֧�ĵڼ���֧
int CCardManageView::GetPropertyCourtPath(int iID,CMFCPropertyGridProperty* lParam,BYTE* ucPath)
{
	int iLen;
	CMFCPropertyGridCtrl *PropCtrl;
	CMFCPropertyGridProperty* lParent[10];
	int iSum;

	ZeroMemory(ucPath,sizeof(ucPath));

	lParent [0 ] = lParam;
//	PropCtrl = (CMFCPropertyGridCtrl *)m_wndPropTabs.GetDlgItem(iID);
	PropCtrl = &m_wndPropList;
	for (iLen = 1 ; iLen < 10 ; iLen += 1)
	{
		lParent[iLen] = lParent[iLen-1]->GetParent();
		if (lParent[iLen] == NULL)
			break;
	}

	iSum = PropCtrl->GetPropertyCount();

	for (int j = 0 ; j < iSum ;j ++)
	{
		
		if (m_wndPropList.GetProperty(j) == lParent[iLen-1])
			ucPath[0] = j; break; 
	}

	for (int i = 1 ;i  < iLen ; i ++)
	{
		iSum = lParent[iLen-i]->GetSubItemsCount();
		for (int k = 0 ; k < iSum ; k++)
		{
			if (lParent[iLen-i]->GetSubItem(k) == lParent[iLen-1-i]  )
				ucPath[i] = k;
		}
	}

	return iLen;
}

int CCardManageView::ExcutionUICCBasInfo(int wParam, CMFCPropertyGridProperty* lParam, BYTE* ucPath)
{
	int iRet;
	switch(ucPath[1])
	{
	//�޸��ļ�����
	case 02:
		iRet = ExcutionUICCFileDes(wParam,lParam,ucPath);
		break;
	//�޸İ�ȫ����
	case 03:
		iRet = ExcutionUICCFileSec(wParam,lParam,ucPath);
		break;
	case 04:

		break;
	case 05:

		break;

	default:
		break;
	}
	return 0;
}

int CCardManageView::ExcutionUICCFileAC(int wParam, CMFCPropertyGridProperty* lParam, BYTE* ucPath)
{

	return 0;
}

int CCardManageView::ExcutionUICCFileData(int wParam, CMFCPropertyGridProperty* lParam, BYTE* ucPath)
{

	return 0;
}

int CCardManageView::ExcutionUICCFileDes(int wParam, CMFCPropertyGridProperty* lParam, BYTE* ucPath)
{
	int iRet;
	switch(ucPath[2])
	{
	case 00: break;
	case 01 :iRet = ExcutionFileType(lParam);break;
	case 02 :iRet = ExcutionFileStructure(lParam); break;
	default:break;
	}
	return 0;
}

int CCardManageView::ExcutionUICCFileSec(int wParam, CMFCPropertyGridProperty* lParam, BYTE* ucPath)
{

	return 0;
}
// �޸�UICC�µ��ļ�����
int CCardManageView::ExcutionFileType(CMFCPropertyGridProperty* lParam)
{
	CString csValue = lParam->GetValue();

	CMFCPropertyGridProperty* lParent;

	lParent = lParam->GetParent();

	if(csValue == _T("Ŀ¼"))
	{
		lParent->GetSubItem(2)->Show(FALSE);
		lParent->GetSubItem(3)->Show(FALSE);
		lParent->GetSubItem(4)->Show(FALSE);
	}
	else if(csValue == _T("RFU"))
	{
		lParent->GetSubItem(2)->Show(TRUE);
		lParent->GetSubItem(3)->Show(TRUE);
		lParent->GetSubItem(4)->Show(TRUE);
	}
	else
	{
		lParent->GetSubItem(2)->Show(TRUE);
		//lParent->GetSubItem(3)->Show(TRUE);
		//lParent->GetSubItem(4)->Show(TRUE);

	}


	lParent->Redraw();
	return 0;
}
// �޸�UICC�µ��ļ��ṹ
int CCardManageView::ExcutionFileStructure(CMFCPropertyGridProperty* lParam)
{
	CString csValue = lParam->GetValue();

	CMFCPropertyGridProperty* lParent;

	lParent = lParam->GetParent();

	
	if((csValue == _T("͸���ļ�"))||(csValue == _T("�ļ���������Ϣ"))||(!lParam->IsVisible()))
	{
		lParent->GetSubItem(3)->Show(FALSE);
		lParent->GetSubItem(4)->Show(FALSE);
	}
	else
	{
		lParent->GetSubItem(3)->Show(TRUE);
		lParent->GetSubItem(4)->Show(TRUE);
	}
	lParent->Redraw();
	return 0;
}


int CCardManageView::InitPropData(void)
{
	m_wndPropData.EnableHeaderCtrl(FALSE);
	m_wndPropData.EnableDescriptionArea();
	m_wndPropData.SetVSDotNetLook();
	m_wndPropData.MarkModifiedProperties();




	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("�ļ�����"));

	m_wndPropData.AddProperty(pGroup1);
	return 0;
}







