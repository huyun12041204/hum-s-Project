// ExpFile.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "ExpFile.h"

#include "..\..\Basconv.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CExpFileApp

BEGIN_MESSAGE_MAP(CExpFileApp, CWinApp)
END_MESSAGE_MAP()


// CExpFileApp 构造

CExpFileApp::CExpFileApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CExpFileApp 对象

CExpFileApp theApp;


// CExpFileApp 初始化

BOOL CExpFileApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

CMFCPropertyGridProperty* CreateACCell(CString csCell, bool bOption= true)
{
	CMFCPropertyGridProperty* pGroup;
	pGroup =new CMFCPropertyGridProperty(csCell,_T(""),csCell);
	if(bOption)
	{
		pGroup->AddOption(_T("ALWAYS"));
		pGroup->AddOption(_T("PIN 01"));
		pGroup->AddOption(_T("PIN 81"));
		pGroup->AddOption(_T("PIN 0A"));
		pGroup->AddOption(_T("NEVER"));
		pGroup->AddOption(_T("DEFAULT"));
		pGroup->AddOption(_T("PIN 01|PIN 0A"));
		pGroup->AddOption(_T("PIN 01|PIN 81"));
		pGroup->AddOption(_T("PIN 81|PIN 0A"));
		pGroup->AddOption(_T("PIN 01|PIN 81|PIN 0A"));
		pGroup->AddOption(_T("PIN 01&PIN 0A"));
		pGroup->AddOption(_T("PIN 01&PIN 81"));
		pGroup->AddOption(_T("PIN 81&PIN 0A"));
		pGroup->AddOption(_T("PIN 01&PIN 81&PIN 0A"));
		pGroup->AddOption(_T("!PIN 01"));
		pGroup->AddOption(_T("!PIN 81"));
		pGroup->AddOption(_T("!PIN 0A"));

	//	pGroup->AddOption("....");
	}
	pGroup->AllowEdit(FALSE);

	return pGroup;
}

CMFCPropertyGridProperty* ExplainARRRecord(CString csData,int iRecord,BOOL bSubItem)
{
	int iOther;
	CString csDes,csValue;
	CString csName = _T("ARR ");

	CMFCPropertyGridProperty* pGroup1;

	if((bSubItem)&&(iRecord >0))
	   csName = csName + Int2CStringDecimal(iRecord);

	if (csData.IsEmpty())
	{
		pGroup1 = new CMFCPropertyGridProperty(csName,"Empty","Not read");
	}
	else
	{
		pGroup1 = new CMFCPropertyGridProperty(csName,FALSE,bSubItem);
		csValue =  GetACFromARR(0x01,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csValue,&csDes);
		pGroup1->AddSubItem(CreateACCell(_T("READ"),!bSubItem));
		pGroup1->GetSubItem(0)->SetValue(csValue);
		pGroup1->GetSubItem(0)->SetOriginalValue(csValue);
		pGroup1->GetSubItem(0)->SetDescription(csDes);


		csValue =  GetACFromARR(0x02,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csValue,&csDes);
		pGroup1->AddSubItem(CreateACCell(_T("UPDATE"),!bSubItem));
		pGroup1->GetSubItem(1)->SetValue(csValue);
		pGroup1->GetSubItem(1)->SetOriginalValue(csValue);
		pGroup1->GetSubItem(1)->SetDescription(csDes);


		csValue =  GetACFromARR(0x04,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csValue,&csDes);
		pGroup1->AddSubItem(CreateACCell(_T("APPEND "),!bSubItem));
		pGroup1->GetSubItem(2)->SetValue(csValue);
		pGroup1->GetSubItem(2)->SetOriginalValue(csValue);
		pGroup1->GetSubItem(2)->SetDescription(csDes);


		csValue =  GetACFromARR(0x08,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csValue,&csDes);
		pGroup1->AddSubItem(CreateACCell(_T("DEACTIVATE"),!bSubItem));
		pGroup1->GetSubItem(3)->SetValue(csValue);
		pGroup1->GetSubItem(3)->SetOriginalValue(csValue);
		pGroup1->GetSubItem(3)->SetDescription(csDes);

		csValue =  GetACFromARR(0x10,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csValue,&csDes);
		//	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("ACTIVATE")  , csValue,csDes));
		pGroup1->AddSubItem(CreateACCell(_T("ACTIVATE"),!bSubItem));
		pGroup1->GetSubItem(4)->SetValue(csValue);
		pGroup1->GetSubItem(4)->SetOriginalValue(csValue);
		pGroup1->GetSubItem(4)->SetDescription(csDes);


		csValue =  GetACFromARR(0x20,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csValue,&csDes);
		//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("TERMINATE") , csValue,csDes));
		pGroup1->AddSubItem(CreateACCell(_T("TERMINATE"),!bSubItem));
		pGroup1->GetSubItem(5)->SetValue(csValue);
		pGroup1->GetSubItem(5)->SetOriginalValue(csValue);
		pGroup1->GetSubItem(5)->SetDescription(csDes);

		csValue =  GetACFromARR(0x40,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csValue,&csDes);
		//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("DELETE")    , csValue,csDes));
		pGroup1->AddSubItem(CreateACCell(_T("DELETE"),!bSubItem));
		pGroup1->GetSubItem(6)->SetValue(csValue);
		pGroup1->GetSubItem(6)->SetOriginalValue(csValue);
		pGroup1->GetSubItem(6)->SetDescription(csDes);


		csValue =  GetACFromARR(0x32,csData,&iOther,true);
		GenerateExpandedFormatSecurityDescriptor(&csValue,&csDes);

		pGroup1->AddSubItem(CreateACCell(_T("INCREASE"),!bSubItem));
		pGroup1->GetSubItem(7)->SetValue(csValue);
		pGroup1->GetSubItem(7)->SetOriginalValue(csValue);
		pGroup1->GetSubItem(7)->SetDescription(csDes);


		csValue =  GetACFromARR(0x88,csData,&iOther);
		GenerateExpandedFormatSecurityDescriptor(&csValue,&csDes);
		pGroup1->AddSubItem(CreateACCell(_T("AUTHENTICATE"),!bSubItem));
		pGroup1->GetSubItem(8)->SetValue(csValue);
		pGroup1->GetSubItem(8)->SetOriginalValue(csValue);
		pGroup1->GetSubItem(8)->SetDescription(csDes);
	}


	





	return pGroup1;
}

CMFCPropertyGridProperty* Explain2F00Data(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("目录信息"),0,bSubItem);
	CString csAppData;
	CString csTemp;

	csAppData = GetTLVData(csData,0x61);
	if (csAppData.IsEmpty())
		return pGroup1;

	//AID
	csTemp= GetTLVData(csAppData,0x4F);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("AID"),csTemp,csTemp));
	}


	//Application label
	csTemp= GetTLVData(csAppData,0x50);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Application label"),TranslateAscii(csTemp),csTemp));
	}


	return pGroup1;

}

CMFCPropertyGridProperty* ExplainLIData(CString csData,BOOL bSubItem)
{	
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("语言代码"),0,bSubItem);
	int iLen;
	CString csTemp;
	CString csNthLanguage;

	iLen = csData.GetLength();

	for (int i = 0 ; i < iLen ; i += 4)
	{
		csTemp.Format(_T("%02d"),(i/4 +1));

		if ((iLen -1)<4)
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(csTemp,_T("Same Mistake"),_T("长度有误")));
		else
		{
			csNthLanguage = csData.Mid(i,4);
			if (_CString2Int(csNthLanguage) == 0xFFFF)
				pGroup1->AddSubItem(new CMFCPropertyGridProperty(csTemp,csNthLanguage,_T("Unused language")));
			else
				pGroup1->AddSubItem(new CMFCPropertyGridProperty(csTemp,csNthLanguage,TranslateAscii(csNthLanguage)));
		}

	}

	//ISO 639: "Codes for the representation of names of languages"

	return pGroup1;
}

bool ExplainCMCC(CMFCPropertyGridProperty* ParentGroup, CString csData)
{
	CString csTemp;
	CString csDes;
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("运营商编号"),_T("中国移动"),_T("00")));
	csTemp = csData.Mid(0,1);
	switch(_CString2Int(csTemp))
	{
	case 00:
		csTemp = _T("159");
		break;
	case 01:
		csTemp = _T("158");
		break;
	case 02:
		csTemp = _T("150");
		break;
	case 03:
		csTemp = _T("151");
		break;
	case 4:
	case 5:
	case 6:
	case 0x7:
	case 0x8:
	case 0x9:
		csTemp = _T("13")+csTemp;
		break;
	case 0xA:
		csTemp = _T("157");
		break;
	case 0xB:
		csTemp = _T("188");
		break;
	case 0xC:
		csTemp = _T("152");
		break;
	case 0xD:
		csTemp = _T("147");
		break;
	case 0xE:
		csTemp = _T("187");
		break;
	}

	csDes = csTemp+csData.Mid(1,1);
	csTemp = csData.Mid(0,2);

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("号段"),csDes,csTemp));

	csTemp = csData.Mid(2,2);

	switch(_CString2Int(csTemp))
	{
	case 01:
		csDes = _T("北京");
		break;
	case 2:
		csDes = _T("天津");
		break;
	case 3:
		csDes = _T("河北");
		break;
	case 4:
		csDes = _T("山西");
		break;
	case 5:
		csDes = _T("内蒙古");
		break;
	case 6:
		csDes = _T("辽宁");
		break;
	case 7:
		csDes = _T("吉林");
		break;
	case 8:
		csDes = _T("黑龙江");
		break;
	case 9:
		csDes = _T("上海");
		break;
	case 0x10:
		csDes = _T("江苏");
		break;
	case 0x11:
		csDes = _T("浙江");
		break;
	case 0x12:
		csDes = _T("安徽");
		break;
	case 0x13:
		csDes = _T("福建");
		break;
	case 0x14:
		csDes = _T("江西");
		break;
	case 0x15:
		csDes = _T("山东");
		break;
	case 0x16:
		csDes = _T("河南");
		break;
	case 0x17:
		csDes = _T("湖北");
		break;
	case 0x18:
		csDes = _T("湖南");
		break;
	case 0x19:
		csDes = _T("广东");
		break;
	case 0x20:
		csDes = _T("广西");
		break;
	case 0x21:
		csDes = _T("海南");
		break;
	case 0x22:
		csDes = _T("四川");
		break;
	case 0x23:
		csDes = _T("贵州");
		break;
	case 0x24:
		csDes = _T("云南");
		break;
	case 0x25:
		csDes = _T("西藏");
		break;
	case 0x26:
		csDes = _T("陕西");
		break;
	case 0x27:
		csDes = _T("甘肃");
		break;
	case 0x28:
		csDes = _T("青海");
		break;
	case 0x29:
		csDes = _T("宁夏");
		break;
	case 0x30:
		csDes = _T("新疆");
		break;
	case 0x31:
		csDes = _T("重庆");
		break;
	default:
		csDes = _T("其他省份");
		break;
	}

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("省份"),csDes,csTemp));

	csTemp = csData.Mid(4,2);
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("年份"),csTemp,csTemp));
	csTemp = csData.Mid(6,1);
	switch(_CString2Int(csTemp))
	{
	case 00:
		csDes = _T("雅斯拓");
		break;
	case 01:
		csDes = _T("GEMPLUS");
		break;
	case 2:
		csDes = _T("武汉天喻");
		break;
	case 3:
		csDes = _T("江西捷德 ");
		break;
	case 4:
		csDes = _T("珠海东信和平");
		break;
	case 5:
		csDes = _T("大唐微电子通");
		break;
	case 6:
		csDes = _T("航天九州通");
		break;
	case 7:
		csDes = _T("北京握奇");
		break;
	case 8:
		csDes = _T("东方英卡");
		break;
	case 9:
		csDes = _T("北京华虹");
		break;
	case 10:
		csDes = _T("上海柯斯");
		break;
	default:
		break;
	}
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("SIM卡供应商代码"),csDes,csTemp));

	csTemp = csData.Mid(7,6);
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("SIM用户识别码"),csTemp,csTemp));

	csTemp = csData.Mid(13,1);
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("校验位"),csTemp,csTemp));

	return true;
}
bool ExplainCUC(CMFCPropertyGridProperty* ParentGroup, CString csData)
{
	CString csTemp;
	CString csDes;
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("运营商编号"),_T("中国联通"),_T("01")));
	csTemp = csData.Mid(0,2);
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("年份"),csTemp,csTemp));

	csTemp = csData.Mid(2,1);
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("中国联通ICCID默认"),csTemp,_T("默认为8")));

	csTemp = csData.Mid(3,2);
	switch(_CString2Int(csTemp))
	{
	case 0x10:
		csDes = _T("内蒙古");
		break;
	case 0x11:
		csDes = _T("北京");
		break;
	case 0x13:
		csDes = _T("天津");
		break;
	case 0x17:
		csDes = _T("山东");
		break;
	case 0x18:
		csDes = _T("河北");
		break;
	case 0x19:
		csDes = _T("山西");
		break;
	case 0x30:
		csDes = _T("安徽");
		break;
	case 0x31:
		csDes = _T("上海");
		break;
	case 0x34:
		csDes = _T("江苏");
		break;
	case 0x36:
		csDes = _T("浙江");
		break;
	case 0x38:
		csDes = _T("福建");
		break;
	case 0x50:
		csDes = _T("海南");
		break;
	case 0x51:
		csDes = _T("广东");
		break;
	case 0x59:
		csDes = _T("广西");
		break;
	case 0x70:
		csDes = _T("青海 ");
		break;
	case 0x71:
		csDes = _T("湖北");
		break;
	case 0x74:
		csDes = _T("湖南");
		break;
	case 0x75:
		csDes = _T("江西");
		break;
	case 0x76:
		csDes = _T("河南");
		break;
	case 0x79:
		csDes = _T("西藏");
		break;
	case 0x81:
		csDes = _T("四川");
		break;
	case 0x83:
		csDes = _T("重庆");
		break;
	case 0x84:
		csDes = _T("陕西");
		break;
	case 0x85:
		csDes = _T("贵州");
		break;
	case 0x86:
		csDes = _T("云南");
		break;
	case 0x87:
		csDes = _T("甘肃 ");
		break;
	case 0x88:
		csDes = _T("宁夏");
		break;
	case 0x89:
		csDes = _T("新疆");
		break;
	case 0x90:
		csDes = _T("吉林");
		break;
	case 0x91:
		csDes = _T("辽宁");
		break;
	case 0x97:
		csDes = _T("黑龙江");
		break;

	default:
		csDes = _T("其他省份");
		break;
	}
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("省份编码"),csDes,csTemp));

	csTemp = csData.Mid(5,8);
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("卡商生产的顺序编码"),csTemp,csTemp));

	csTemp = csData.Mid(13,1);
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("校验位"),csTemp,csTemp));

	return true;
}
bool ExplainCTC(CMFCPropertyGridProperty* ParentGroup, CString csData)
{
	CString csTemp;
	CString csDes;
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("运营商编号"),_T("中国电信"),_T("03")));
	csTemp = csData.Mid(0,2);
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("年份"),csTemp,csTemp));
	csTemp = csData.Mid(2,1);
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("保留位"),csTemp,csTemp));
	csTemp = csData.Mid(3,3);
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("本地网地区代码"),csTemp,csTemp));

	csTemp = csData.Mid(6,7);
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("流水号"),csTemp,csTemp));
	csTemp = csData.Mid(13,1);
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty(_T("校验位"),csTemp,csTemp));
	return true;
}

CMFCPropertyGridProperty* Explain2FE2Data(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("ICCID"),0,bSubItem);
	CString csICCID;
	CString csTemp,csDes;

	if (csData.GetLength()!= 20)
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty( _T("内容"),csData,_T("长度有误")));
		return pGroup1;
	}

	csICCID = ExchangeAt(csData);

	if (_CString2Int (csICCID.Mid(00,02)) == 0xFF)
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("内容"),csData,_T("数据内容为空或者错误！")));
		return pGroup1;
	}
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("数据"),csICCID,csData));

	csTemp = csICCID.Mid(00,02);

	if (_CString2Int(csTemp)  == 0x89)
		csDes = _T("电信用途");
	else
		csDes = _T("非电信用途");

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("国际编码"),csDes,csTemp));


	csTemp= csICCID.Mid(02,02);

	if (_CString2Int(csTemp)  == 0x86)
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("国家编码"),_T("中国"),csTemp ));
	else
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("国家编码"),_T("其他国家"),_T("由于国家代码以及后续都可以为私定，所以后续不做解释")));
		return pGroup1;
	}

	csTemp= csICCID.Mid(04,02);
	int iOpe;

	iOpe = _CString2Int(csTemp);

	switch(iOpe)
	{
	case 00:
		ExplainCMCC(pGroup1,csICCID.Mid(6,14));
		break;
	case 01:
		ExplainCUC(pGroup1,csICCID.Mid(6,14));
		break;
	case 03:
		ExplainCTC(pGroup1,csICCID.Mid(6,14));
		break;
	default:

		break;
	}

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainFirstNote(CString csName,CString csData,bool* bRet, BOOL bSubItem = TRUE)
{

	CMFCPropertyGridProperty* pGroup1;
	if (WipeEmpty(csData).IsEmpty())
	{
		pGroup1 = new CMFCPropertyGridProperty(csName,_T("N/A") ,_T("N/A"));
		* bRet = false;
	}
	else

	{
		pGroup1 = new CMFCPropertyGridProperty(csName,0,bSubItem);
		* bRet = true ;
	}
	return pGroup1;

}

CMFCPropertyGridProperty* _ExplainEXTData(CString csData,int iNumber,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1;
	CString csNumber,csDes;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("_Extension")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;


	if (csData.GetLength() >4 )
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension"), _T("长度应该大于4") ,csData));
	}
	else
	{
		if (_CString2Int(csData.Mid(0,2))&1)
			csDes = _T("被叫用户子地址(Called Party Subaddress)");
		if (_CString2Int(csData.Mid(0,2))&1)
			csDes = _T("溢出数据(Additional data)");

		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Record type"), csData.Mid(0,2) ,csDes));

		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension data"),  csData.Mid(2,csData.GetLength()-4) ,csData.Mid(2,csData.GetLength()-4)));

		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Identifier"),csData.Right(02) ,_T("下一个记录的号码，‘FF’表示链接的结束。") ));

	}

	return pGroup1;
}

CMFCPropertyGridProperty* _NewSupportedText( CString csName,bool bStatus /*= true*/,bool bEmpty /*= false*/,bool bOption /*= false*/ )
{


	CMFCPropertyGridProperty* pGroup11;
	CString csText = TransationSupportedText(bStatus);
	if (bEmpty)
		pGroup11 = new CMFCPropertyGridProperty ( csName, _T(""), _T(""));
	else
		pGroup11 = new CMFCPropertyGridProperty ( csName,csText ,csText);

	if (bOption)
	{
		pGroup11->AddOption(TransationSupportedText(false));
		pGroup11->AddOption(TransationSupportedText(true));
	}
	pGroup11->AllowEdit(FALSE);
	return pGroup11;
}

CMFCPropertyGridProperty* ExplainATI( CString csData,BOOL bOption /*= FALSE*/ )
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("PLMN Access Technology Identifier"),0,1);
	bool bEmpty,bbOption;


	bEmpty   = (_CString2Int(csData)==0xFFFF)?true:false;
	bbOption = bOption                      ?true:false;
	pGroup1->AddSubItem(_NewSupportedText( _T("E-UTRAN"),        Getbit(csData,7)  ,bEmpty,bbOption));
	pGroup1->AddSubItem(_NewSupportedText( _T("UTRAN"),          Getbit(csData,8)  ,bEmpty,bbOption));
	pGroup1->AddSubItem(_NewSupportedText( _T("cdma2000 1xRTT"), Getbit(csData,13) ,bEmpty,bbOption));
	pGroup1->AddSubItem(_NewSupportedText( _T("cdma2000 HRPD"),  Getbit(csData,14) ,bEmpty,bbOption));
	pGroup1->AddSubItem(_NewSupportedText( _T("GSM COMPACT"),    Getbit(csData,15) ,bEmpty,bbOption));
	pGroup1->AddSubItem(_NewSupportedText( _T("GSM"),            Getbit(csData,16) ,bEmpty,bbOption));

	pGroup1->SetDescription(csData);

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainCFUISD(CString csData)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("CFU indicator status"),0,1);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Voicemail"),       TransationSupportedText( Getbit(csData,1)) ,csData));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Fax"),             TransationSupportedText( Getbit(csData,2)) ,csData));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Electronic Mail"), TransationSupportedText( Getbit(csData,3)) ,csData));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Other"),           TransationSupportedText( Getbit(csData,4)) ,csData));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Videomail"),       TransationSupportedText( Getbit(csData,5)) ,csData));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainMWIS(CString csData)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("MWIS"),0,1);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Voicemail"),       TransationSupportedText( Getbit(csData,1)) ,csData));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Fax"),             TransationSupportedText( Getbit(csData,2)) ,csData));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Electronic Mail"), TransationSupportedText( Getbit(csData,3)) ,csData));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Other"),           TransationSupportedText( Getbit(csData,4)),csData));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Videomail"),       TransationSupportedText( Getbit(csData,5)) ,csData));

	return pGroup1;

}

CMFCPropertyGridProperty* ExplainLAI(CString csLAI)
{



	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("LAI"),0,1);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MNCMCC"), TransationMNCMCC(csLAI.Mid(0,6)) ,GenerateMCCMNCDescription(csLAI.Mid(0,6)) ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("LAC"),csLAI.Mid(6,4) ,csLAI.Mid(6,4)));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainLTAI(CString csLAI)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Last visited registered Tracking Area Identity"),0,1);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MNCMCC"), TransationMNCMCC(csLAI.Mid(0,6)) ,GenerateMCCMNCDescription(csLAI.Mid(0,6)) ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("TAC"),csLAI.Mid(6,4) ,csLAI.Mid(6,4)));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainRAI(CString csRAI)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("RAI"),0,1);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MNCMCC"), TransationMNCMCC(csRAI.Mid(0,6)) , GenerateMCCMNCDescription(csRAI.Mid(0,6))    ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("LAC"),csRAI.Mid(6,4) ,csRAI.Mid(6,4)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("RAC"),csRAI.Mid(10,4) ,csRAI.Mid(10,4)));
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainMID( CString csData,BOOL bSubItem /*= TRUE*/,BOOL bOption /*= FALSE*/ )
{
	CString csTemp;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Mobile Identity"),0,bSubItem);
	CMFCPropertyGridProperty* pGroup11;

	pGroup11 = new CMFCPropertyGridProperty ( _T("Mobile Identity IEI"),csData.Mid(0,2),csData.Mid(0,2));
	pGroup1->AddSubItem(pGroup11);

	csTemp = csData.Mid(2,2);

	pGroup11 = new CMFCPropertyGridProperty (_T("Length of mobile identity contents"),_T(""),csTemp);
	if (!WipeEmpty(csTemp))
	{
		pGroup11->SetValue(csTemp);
		pGroup11->SetOriginalValue(csTemp);
	}

	pGroup11->Enable(FALSE);
	pGroup1->AddSubItem(pGroup11);


	csTemp = csData.Mid(4,2);
	pGroup11 = new CMFCPropertyGridProperty (_T("Type of identity"),_T(""),csTemp);

	pGroup11->SetValue        (TransationMobileIdentity(_CString2Int(csTemp)&0x7));
	pGroup11->SetOriginalValue(TransationMobileIdentity(_CString2Int(csTemp)&0x7));
	pGroup11->AllowEdit(FALSE);

	if (bOption)
	{
		pGroup11->AddOption(TransationMobileIdentity(0));
		pGroup11->AddOption(TransationMobileIdentity(1));
		pGroup11->AddOption(TransationMobileIdentity(2));
		pGroup11->AddOption(TransationMobileIdentity(3));
		pGroup11->AddOption(TransationMobileIdentity(4));
		pGroup11->AddOption(TransationMobileIdentity(5));
	}
	pGroup1->AddSubItem(pGroup11);

	pGroup11 = new CMFCPropertyGridProperty (_T("Odd/even indication"),_T(""),csTemp);

	pGroup11->SetValue        (TransationOddEvenIndicationText(Getbit(csData,20)));
	pGroup11->SetOriginalValue(TransationOddEvenIndicationText(Getbit(csData,20)));
	pGroup11->AllowEdit(FALSE);
	if (bOption)
	{
		pGroup11->AddOption(TransationOddEvenIndicationText(FALSE));
		pGroup11->AddOption(TransationOddEvenIndicationText(TRUE));
	}
	pGroup11->Enable(FALSE);
	pGroup1->AddSubItem(pGroup11);


//	pGroup1->AddSubItem( new CMFCPropertyGridProperty ( _T("Odd/even indication"),TransationSupportedText(_Getbit(csData,20)) ,csDes));

	pGroup1->AddSubItem( new CMFCPropertyGridProperty (_T("Identity"),csData.Mid(4,1) + csData.Mid(7,1) +csData.Mid(6,1) ,csData.Mid(4,1) + csData.Mid(7,1) +csData.Mid(6,1)));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainDateTime(CString csTP_SCTS)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Date&Time"),0,1);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Date"), TransationDate(csTP_SCTS.Mid(0,6)) ,csTP_SCTS.Mid(0,6)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Time"),TransationTime(csTP_SCTS.Mid(6,6)) ,csTP_SCTS.Mid(6,6)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("TimeZone"),WipeEmpty (csTP_SCTS.Mid(12,2)),csTP_SCTS.Mid(12,2)));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainIMSIData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("IMSI"),0,bSubItem);
	CString csIMSI,csMCC,csMNC;
	int iMNCLen;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MCC MNC"),_T(""),_T("")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MSIN"),_T(""),_T("")));

	if (_CString2Int(csData.Mid(0,2))!= 0x08)
	{
		pGroup1->GetSubItem(0)->SetValue(_T("数据长度错误"));
			pGroup1->GetSubItem(0)->SetDescription(csData);
		pGroup1->GetSubItem(1)->SetValue(_T("数据长度错误"));

		pGroup1->GetSubItem(1)->SetDescription(csData);
	}
	else
	{
		csIMSI  = ExchangeAt(csData.Mid(2,16));
		csIMSI  = csIMSI.Mid(1,15);
		iMNCLen = _RecogniseMNCLen(_CString2Int(csIMSI.Mid(0,3)),_CString2Int(csIMSI.Mid(3,2)));
		csMCC  = csIMSI.Mid(0,3);
		csMNC  = csIMSI.Mid(3,iMNCLen);

		pGroup1->GetSubItem(0)->SetValue(csMCC+csMNC);
		pGroup1->GetSubItem(0)->SetDescription(GenerateMCCMNCDescription(ConvertMCCMNC( csMCC,csMNC)));

		pGroup1->GetSubItem(1)->SetValue(csIMSI.Mid(3+iMNCLen,10));
		pGroup1->GetSubItem(1)->SetDescription(csIMSI.Mid(3+iMNCLen,10));

	}



	//CString csIMSI;
	//CString csTemp;
	//int iMNCLen;

	//csTemp = csData.Mid(0,2);
	//if (_CString2Int(csTemp)!= 0x08)
	//{
	//	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("数值"),_T("数据为空,或者长度有误！"),csData));
	//	return pGroup1;
	//}
	//csIMSI = _ExchangeAt(csData.Mid(2,16));
	//csIMSI = csIMSI.Mid(1,15);
	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MCC"),csIMSI.Mid(0,3),csIMSI.Mid(0,3)));

	//iMNCLen = _RecogniseMNCLen(_CString2Int(csIMSI.Mid(0,3)),_CString2Int(csIMSI.Mid(3,2)));

	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MNC"),csIMSI.Mid(3,iMNCLen),csIMSI.Mid(3,iMNCLen)));

	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MSIN"),csIMSI.Mid(3+iMNCLen,10),csIMSI.Mid(3+iMNCLen,10)));
	
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainKeysData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("CK IK"),0,bSubItem);

	//if (csData.GetLength() != 66)
	//{
	//	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("CK IK"),csData,_T("数据有问题")));

	//	return pGroup1;
	//}
	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("KSI"),csData.Mid(0,2),csData.Mid(0,2)));
	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("CK"),csData.Mid(2,32),csData.Mid(2,32)));
	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("IK"),csData.Mid(34,32),csData.Mid(34,32)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("KSI"),_T(""),_T("")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("CK"),_T(""),_T("")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("IK"),_T(""),_T("")));

	if (csData.GetLength() == 66)
	{
		pGroup1->GetSubItem(0)->SetValue(csData.Mid(0,2));
		pGroup1->GetSubItem(1)->SetValue(csData.Mid(2,32));
		pGroup1->GetSubItem(2)->SetValue(csData.Mid(34,32));
	}

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainKeysPSData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("CKPS IKPS"),0,bSubItem);

	//if (csData.GetLength() != 66)
	//{
	//	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("CKPS IKPS"),csData,_T("数据有问题")));

	//	return pGroup1;
	//}

	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("KSIPS"),csData.Mid(0,2),csData.Mid(0,2)));
	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("CKPS"),csData.Mid(2,32),csData.Mid(2,32)));
	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("IKPS"),csData.Mid(34,32),csData.Mid(34,32)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("KSIPS"),_T(""),_T("")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("CKPS"),_T(""),_T("")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("IKPS"),_T(""),_T("")));

	if (csData.GetLength() == 66)
	{
		pGroup1->GetSubItem(0)->SetValue(csData.Mid(0,2));
		pGroup1->GetSubItem(1)->SetValue(csData.Mid(2,32));
		pGroup1->GetSubItem(2)->SetValue(csData.Mid(34,32));
	}

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainDCKData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Depersonalisation Control Keys"),0,bSubItem);

	if (csData.GetLength() != 32)
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Depersonalisation Control Keys)"),csData,_T("数据有问题")));

		return pGroup1;
	}

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("network de-personalization control key"),csData.Mid(0,8),csData.Mid(0,8)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("network subset de-personalization control key"),csData.Mid(8,8),csData.Mid(8,8)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("service provider de-personalization control key"),csData.Mid(16,8),csData.Mid(16,8)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("corporate de-personalization control key"),csData.Mid(24,8),csData.Mid(24,8)));
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainHPPLMNData(CString csData,BOOL bSubItem)
{

	int iTemp;
	CString csTemp;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Higher Priority PLMN search period"),0,bSubItem);

	if (csData.GetLength() != 2)
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Higher Priority PLMN search period"),csData,_T("数据有问题")));

		return pGroup1;
	}

	if (_CString2Int(csData) == 0)
	{
		csTemp = _T("No higher priority PLMN search attempts");
	}
	else
	{
		iTemp = _CString2Int(csData);
		csTemp.Format(_T("%d"),iTemp);
		csTemp= csTemp + _T("n minutes");
	}

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Time interval"),csTemp,csData));


	return pGroup1;
}

CMFCPropertyGridProperty* ExplainCNLData(CString csData,BOOL bSubItem )
{
	int iLen;
	CString csTemp;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Co-operative Network List"),0,bSubItem);

	if (csData.GetLength()%12 != 0)
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Co-operative Network List"),csData,_T("数据有问题")));

		return pGroup1;
	}
	iLen = csData.GetLength();

	for(int i =0 ; i < iLen ; i+= 12)
	{
		csTemp.Format(_T("%02d"),(i/12) +1);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(csTemp,csData.Mid(i,12),csData.Mid(i,12)));
	}
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainACMmaxData(CString csData,BOOL bSubItem)
{
	int iTemp;
	CString csTemp;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("ACM maximum value"),0,bSubItem);

	if (csData.GetLength() != 6)
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("ACM maximum value"),csData,_T("数据有问题")));

		return pGroup1;
	}

	iTemp = _CString2Int(csData);

	csTemp.Format(_T("%d"),iTemp);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Maximum value"),csTemp,csData));

	return pGroup1;
}

CMFCPropertyGridProperty* NewUSTSubItem( int iService,BOOL bSupport /*= true*/,BOOL bOption /*= true*/ )
{
	CMFCPropertyGridProperty* pGroup;
	CString csTemp[89];

	csTemp[0] = _T("Local Phone Book");
	csTemp[1] = _T("Fixed Dialling Numbers (FDN)");
	csTemp[2] = _T("Extension 2");
	csTemp[3] = _T("Service Dialling Numbers (SDN)");
	csTemp[4] = _T("Extension3");
	csTemp[5] = _T("Barred Dialling Numbers (BDN)");
	csTemp[6] = _T("Extension4");
	csTemp[7] = _T("Outgoing Call Information (OCI and OCT)");

	csTemp[8] = _T("Incoming Call Information (ICI and ICT)");
	csTemp[9] = _T("Short Message Storage (SMS)");
	csTemp[10] = _T("Short Message Status Reports (SMSR)");
	csTemp[11] = _T("Short Message Service Parameters (SMSP)");
	csTemp[12] = _T("Advice of Charge (AoC)");
	csTemp[13] = _T("Capability Configuration Parameters 2 (CCP2)");
	csTemp[14] = _T("Cell Broadcast Message Identifier");
	csTemp[15] = _T("Cell Broadcast Message Identifier Ranges");

	csTemp[16] = _T("Group Identifier Level 1");
	csTemp[17] = _T("Group Identifier Level 2");
	csTemp[18] = _T("Service Provider Name");
	csTemp[19] = _T("User controlled PLMN selector with Access Technology");
	csTemp[20] = _T("MSISDN");
	csTemp[21] = _T("Image (IMG)");
	csTemp[22] = _T("Support of Localised Service Areas (SoLSA)");
	csTemp[23] = _T("Enhanced Multi-Level Precedence and Pre-emption Service");

	csTemp[24] = _T("Automatic Answer for eMLPP");
	csTemp[25] = _T("RFU");
	csTemp[26] = _T("GSM Access");
	csTemp[27] = _T("Data download via SMS-P");
	csTemp[28] = _T("Data download via SMS-CB");
	csTemp[29] = _T("Call Control by USIM");
	csTemp[30] = _T("MO-SMS Control by USIM");
	csTemp[31] = _T("RUN AT COMMAND command");

	csTemp[32] = _T("shall be set to '1'");
	csTemp[33] = _T("Enabled Services Table");
	csTemp[34] = _T("APN Control List (ACL)");
	csTemp[35] = _T("Depersonalisation Control Keys");
	csTemp[36] = _T("Co-operative Network List");
	csTemp[37] = _T("GSM security context");
	csTemp[38] = _T("CPBCCH Information");
	csTemp[39] = _T("Investigation Scan");

	csTemp[40] = _T("MExE");
	csTemp[41] = _T("Operator controlled PLMN selector with Access Technology");
	csTemp[42] = _T("HPLMN selector with Access Technology");
	csTemp[43] = _T("Extension 5");
	csTemp[44] = _T("PLMN Network Name");
	csTemp[45] = _T("Operator PLMN List");
	csTemp[46] = _T("Mailbox Dialling Numbers");
	csTemp[47] = _T("Message Waiting Indication Status");

	csTemp[48] = _T("Call Forwarding Indication Status");
	csTemp[49] = _T("Reserved and shall be ignored");
	csTemp[50] = _T("Service Provider Display Information");
	csTemp[51] = _T("Multimedia Messaging Service (MMS)");
	csTemp[52] = _T("Extension 8");
	csTemp[53] = _T("Call control on GPRS by USIM");
	csTemp[54] = _T("MMS User Connectivity Parameters");
	csTemp[55] = _T("Network's indication of alerting in the MS (NIA)");

	csTemp[56] = _T("VGCS Group Identifier List (EFVGCS and EFVGCSS");
	csTemp[57] = _T("VBS Group Identifier List (EFVBS and EFVBSS)");
	csTemp[58] = _T("Pseudonym");
	csTemp[59] = _T("User Controlled PLMN selector for I-WLAN access");
	csTemp[60] = _T("Operator Controlled PLMN selector for I-WLAN access");
	csTemp[61] = _T("User controlled WSID list");
	csTemp[62] = _T("Operator controlled WSID list");
	csTemp[63] = _T("VGCS security");

	csTemp[64] = _T("VBS security");
	csTemp[65] = _T("WLAN Reauthentication Identity");
	csTemp[66] = _T("Multimedia Messages Storag");
	csTemp[67] = _T("Generic Bootstrapping Architecture (GBA)");
	csTemp[68] = _T("MBMS security");
	csTemp[69] = _T("Data download via USSD and USSD application mode");
	csTemp[70] = _T("Equivalent HPLMN");
	csTemp[71] = _T("Additional TERMINAL PROFILE after UICC activation");

	csTemp[72] = _T("Equivalent HPLMN Presentation Indication");
	csTemp[73] = _T("Last RPLMN Selection Indication");
	csTemp[74] = _T("OMA BCAST Smart Card Profile");
	csTemp[75] = _T("GBA-based Local Key Establishment Mechanism");
	csTemp[76] = _T("Terminal Applications");
	csTemp[77] = _T("Service Provider Name Icon");
	csTemp[78] = _T("PLMN Network Name Icon");
	csTemp[79] = _T("Connectivity Parameters for USIM IP connections");

	csTemp[80] = _T("Home I-WLAN Specific Identifier List");
	csTemp[81] = _T("I-WLAN Equivalent HPLMN Presentation Indication");
	csTemp[82] = _T("I-WLAN HPLMN Priority Indication");
	csTemp[83] = _T("I-WLAN Last Registered PLMN");
	csTemp[84] = _T("EPS Mobility Management Information");
	csTemp[85] = _T("Allowed CSG Lists and corresponding indications");
	csTemp[86] = _T("Call control on EPS PDN connection by USIM");
	csTemp[87] = _T("HPLMN Direct Access");
	csTemp[88] = _T("eCall Data");

	bool bSet;
	if (bSupport)
		bSet = true;
	else
		bSet =false;
	
	pGroup = new CMFCPropertyGridProperty(csTemp[iService-1],TransationSupportedText(bSet),_T("Service n°")+Int2CStringDecimal(iService));

	if (bOption)
	{
		pGroup->AddOption(TransationSupportedText(true));
		pGroup->AddOption(TransationSupportedText(false));
	}


	return pGroup;

}

CMFCPropertyGridProperty* ExplainUSTData(CString csData,BOOL bSubItem)
{
	
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("USIM Service Table"),0,bSubItem);
	int ibitLen = csData.GetLength()*4;

	ibitLen = ibitLen> 89 ? 89 : ibitLen;

	for (int i = 1 ; i <=ibitLen ; i++ )
	{
		pGroup1->AddSubItem(NewUSTSubItem(i,Getbit(csData,i)));
	}

	/*pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Local Phone Book"), TransationSupportedText( _Getbit(csData,1)) ,_T("Service n°1")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Fixed Dialling Numbers (FDN)"),TransationSupportedText( _Getbit(csData,2)),_T("Service n°2")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension 2"),TransationSupportedText( _Getbit(csData,3)),_T("Service n°3")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Service Dialling Numbers (SDN)"),TransationSupportedText( _Getbit(csData,4)),_T("Service n°4")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension3"),TransationSupportedText( _Getbit(csData,5)),_T("Service n°5")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Barred Dialling Numbers (BDN)"),TransationSupportedText( _Getbit(csData,6)),_T("Service n°6")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension4"),TransationSupportedText( _Getbit(csData,7)),_T("Service n°7")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Outgoing Call Information (OCI and OCT)"),TransationSupportedText( _Getbit(csData,8)),_T("Service n°8")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Incoming Call Information (ICI and ICT)"),TransationSupportedText( _Getbit(csData,9)),_T("Service n°9")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Short Message Storage (SMS)"),TransationSupportedText( _Getbit(csData,10)),_T("Service n°10")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Short Message Status Reports (SMSR)"),TransationSupportedText( _Getbit(csData,11)),_T("Service n°11")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Short Message Service Parameters (SMSP)"),TransationSupportedText( _Getbit(csData,12)),_T("Service n°12")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Advice of Charge (AoC)"),TransationSupportedText( _Getbit(csData,13)),_T("Service n°13")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Capability Configuration Parameters 2 (CCP2)"),TransationSupportedText( _Getbit(csData,14)),_T("Service n°14")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Cell Broadcast Message Identifier"),TransationSupportedText( _Getbit(csData,15)),_T("Service n°15")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Cell Broadcast Message Identifier Ranges"),TransationSupportedText( _Getbit(csData,16)),_T("Service n°16")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Group Identifier Level 1"),TransationSupportedText( _Getbit(csData,17)),_T("Service n°17")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Group Identifier Level 2"),TransationSupportedText( _Getbit(csData,18)),_T("Service n°18")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Service Provider Name"),TransationSupportedText( _Getbit(csData,19)),_T("Service n°19")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("User controlled PLMN selector with Access Technology"),TransationSupportedText( _Getbit(csData,20)),_T("Service n°20")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MSISDN"),TransationSupportedText( _Getbit(csData,21)),_T("Service n°21")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Image (IMG)"),TransationSupportedText( _Getbit(csData,22)),_T("Service n°22")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Support of Localised Service Areas (SoLSA)"),TransationSupportedText( _Getbit(csData,23)),_T("Service n°23")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Enhanced Multi-Level Precedence and Pre-emption Service"),TransationSupportedText( _Getbit(csData,24)),_T("Service n°24")));


	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Automatic Answer for eMLPP"),TransationSupportedText( _Getbit(csData,25)),_T("Service n°25")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("RFU"),TransationSupportedText( _Getbit(csData,26)),_T("Service n°26")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("GSM Access"),TransationSupportedText( _Getbit(csData,27)),_T("Service n°27")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Data download via SMS-PP"),TransationSupportedText( _Getbit(csData,28)),_T("Service n°28")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Data download via SMS-CB"),TransationSupportedText( _Getbit(csData,29)),_T("Service n°29")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Call Control by USIM"),TransationSupportedText( _Getbit(csData,30)),_T("Service n°30")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MO-SMS Control by USIM"),TransationSupportedText( _Getbit(csData,31)),_T("Service n°31")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("RUN AT COMMAND command"),TransationSupportedText( _Getbit(csData,32)),_T("Service n°32")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("shall be set to '1'"),TransationSupportedText( _Getbit(csData,33)),_T("Service n°33")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Enabled Services Table"),TransationSupportedText( _Getbit(csData,34)),_T("Service n°34")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("APN Control List (ACL)"),TransationSupportedText( _Getbit(csData,35)),_T("Service n°35")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Depersonalisation Control Keys"),TransationSupportedText( _Getbit(csData,36)),_T("Service n°36")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Co-operative Network List"),TransationSupportedText( _Getbit(csData,37)),_T("Service n°37")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("GSM security context"),TransationSupportedText( _Getbit(csData,38)),_T("Service n°38")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("CPBCCH Information"),TransationSupportedText( _Getbit(csData,39)),_T("Service n°39")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Investigation Scan"),TransationSupportedText( _Getbit(csData,40)),_T("Service n°40")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MExE"),TransationSupportedText( _Getbit(csData,41)),_T("Service n°41")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Operator controlled PLMN selector with Access Technology"),TransationSupportedText( _Getbit(csData,42)),_T("Service n°42")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("HPLMN selector with Access Technology"),TransationSupportedText( _Getbit(csData,43)),_T("Service n°43")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension 5"),TransationSupportedText( _Getbit(csData,44)),_T("Service n°44")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("PLMN Network Name"),TransationSupportedText( _Getbit(csData,45)),_T("Service n°45")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Operator PLMN List"),TransationSupportedText( _Getbit(csData,46)),_T("Service n°46")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Mailbox Dialling Numbers"),TransationSupportedText( _Getbit(csData,47)),_T("Service n°47")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Message Waiting Indication Status"),TransationSupportedText( _Getbit(csData,48)),_T("Service n°48")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Call Forwarding Indication Status"),TransationSupportedText( _Getbit(csData,49)),_T("Service n°49")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Reserved and shall be ignored"),TransationSupportedText( _Getbit(csData,50)),_T("Service n°50")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Service Provider Display Information"),TransationSupportedText( _Getbit(csData,51)),_T("Service n°51")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Multimedia Messaging Service (MMS)"),TransationSupportedText( _Getbit(csData,52)),_T("Service n°52")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension 8"),TransationSupportedText( _Getbit(csData,53)),_T("Service n°53")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Call control on GPRS by USIM"),TransationSupportedText( _Getbit(csData,54)),_T("Service n°54")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MMS User Connectivity Parameters"),TransationSupportedText( _Getbit(csData,55)),_T("Service n°55")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Network's indication of alerting in the MS (NIA)"),TransationSupportedText( _Getbit(csData,56)),_T("Service n°56")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("VGCS Group Identifier List (EFVGCS and EFVGCSS)"),TransationSupportedText( _Getbit(csData,57)),_T("Service n°57")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("VBS Group Identifier List (EFVBS and EFVBSS)"),TransationSupportedText( _Getbit(csData,58)),_T("Service n°58")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Pseudonym"),TransationSupportedText( _Getbit(csData,59)),_T("Service n°59")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("User Controlled PLMN selector for I-WLAN access"),TransationSupportedText( _Getbit(csData,60)),_T("Service n°60")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Operator Controlled PLMN selector for I-WLAN access"),TransationSupportedText( _Getbit(csData,61)),_T("Service n°61")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("User controlled WSID list"),TransationSupportedText( _Getbit(csData,62)),_T("Service n°62")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Operator controlled WSID list"),TransationSupportedText( _Getbit(csData,63)),_T("Service n°63")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("VGCS security"),TransationSupportedText( _Getbit(csData,64)),_T("Service n°64")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("VBS security"),TransationSupportedText( _Getbit(csData,65)),_T("Service n°65")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("WLAN Reauthentication Identity"),TransationSupportedText( _Getbit(csData,66)),_T("Service n°66")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Multimedia Messages Storage"),TransationSupportedText( _Getbit(csData,67)),_T("Service n°67")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Generic Bootstrapping Architecture (GBA)"),TransationSupportedText( _Getbit(csData,68)),_T("Service n°68")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MBMS security"),TransationSupportedText( _Getbit(csData,69)),_T("Service n°69")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Data download via USSD and USSD application mode"),TransationSupportedText( _Getbit(csData,70)),_T("Service n°70")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Equivalent HPLMN"),TransationSupportedText( _Getbit(csData,71)),_T("Service n°71")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Additional TERMINAL PROFILE after UICC activation"),TransationSupportedText( _Getbit(csData,72)),_T("Service n°72")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Equivalent HPLMN Presentation Indication"),TransationSupportedText( _Getbit(csData,73)),_T("Service n°73")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Last RPLMN Selection Indication"),TransationSupportedText( _Getbit(csData,74)),_T("Service n°74")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("OMA BCAST Smart Card Profile"),TransationSupportedText( _Getbit(csData,75)),_T("Service n°75")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("GBA-based Local Key Establishment Mechanism"),TransationSupportedText( _Getbit(csData,76)),_T("Service n°76")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Terminal Applications"),TransationSupportedText( _Getbit(csData,77)),_T("Service n°77")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Service Provider Name Icon"),TransationSupportedText( _Getbit(csData,78)),_T("Service n°78")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("PLMN Network Name Icon"),TransationSupportedText( _Getbit(csData,79)),_T("Service n°79")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Connectivity Parameters for USIM IP connections"),TransationSupportedText( _Getbit(csData,80)),_T("Service n°80")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Home I-WLAN Specific Identifier List"),TransationSupportedText( _Getbit(csData,81)),_T("Service n°81")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("I-WLAN Equivalent HPLMN Presentation Indication"),TransationSupportedText( _Getbit(csData,82)),_T("Service n°82")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("I-WLAN HPLMN Priority Indication"),TransationSupportedText( _Getbit(csData,83)),_T("Service n°83")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("I-WLAN Last Registered PLMN"),TransationSupportedText( _Getbit(csData,84)),_T("Service n°84")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("EPS Mobility Management Information"),TransationSupportedText( _Getbit(csData,85)),_T("Service n°85")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Allowed CSG Lists and corresponding indications"),TransationSupportedText( _Getbit(csData,86)),_T("Service n°86")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Call control on EPS PDN connection by USIM"),TransationSupportedText( _Getbit(csData,87)),_T("Service n°87")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("HPLMN Direct Access"),TransationSupportedText( _Getbit(csData,88)),_T("Service n°88")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("eCall Data"),TransationSupportedText( _Getbit(csData,89)),_T("Service n°89")));
	*/
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainACMData(CString csData,int iNumber,BOOL bSubItem)
{
	CString csNumber;

	if (bSubItem)
		csNumber.Format(_T("%02d"),iNumber);

	CMFCPropertyGridProperty* pGroup1 ;
	pGroup1 = new CMFCPropertyGridProperty(_T("Accumulated Call Meter ")+csNumber,0,bSubItem);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Value"),csData,csData));
	pGroup1->SetDescription(_T("该文件包含了当前的呼叫和以前的呼叫的单位总和。注：这种信息为用户提供计费通知，可作为计算呼叫费用的基础。"));
		
	
	return pGroup1;
}

CMFCPropertyGridProperty* _ExplainADNData(CString csName,CString csData,int iNumber,BOOL bSubItem)
{
	CString csAlpha,csADN,csTemp;
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup11;

	CString csNumber;
	if (bSubItem)
		csNumber.Format(_T("%02d"),iNumber);

	if (csData.IsEmpty())
	{
		pGroup1 = new CMFCPropertyGridProperty(csName+csNumber,"Empty","数据未读取或者读取失败");
		return pGroup1;
	}


	pGroup1 = new CMFCPropertyGridProperty(csName+csNumber,0,bSubItem);

	csAlpha = csData.Left(csData.GetLength() - 28);
	csADN   = csData.Mid(csAlpha.GetLength(),24);

	pGroup11 = new CMFCPropertyGridProperty(_T("Alpha Identifier"),_T(""),csAlpha);

	if (!WipeEmpty(csAlpha).IsEmpty())
	{
		csAlpha = TranslateAlphaIdentifier(csAlpha);
		pGroup11->SetValue(csAlpha);
		pGroup11->SetOriginalValue(csAlpha);
	}
	pGroup1->AddSubItem(pGroup11);

	pGroup11 = new CMFCPropertyGridProperty(_T("Phone Number"),_T(""),csADN);

	if (!WipeEmpty(csADN).IsEmpty())
	{
		csADN = _TransationADNNumber(csADN);
		pGroup11->SetValue(csADN);
		pGroup11->SetOriginalValue(csADN);
	}



	pGroup1->AddSubItem(pGroup11);

	csTemp = csData.Right(04).Left(02);
	pGroup11 = new CMFCPropertyGridProperty(_T("Capability/Configuration2 Record Identifier"),_T(""),csTemp);

	if (!WipeEmpty(csTemp).IsEmpty())
	{
		pGroup11->SetValue(csTemp);
		pGroup11->SetOriginalValue(csTemp);
	}

	pGroup1->AddSubItem(pGroup11);


	csTemp = csData.Right(02);

	pGroup11 = new CMFCPropertyGridProperty(_T("Extension2 Record Identifier"),_T(""),csTemp);

	if (!WipeEmpty(csTemp).IsEmpty())
	{
		pGroup11->SetValue(csTemp);
		pGroup11->SetOriginalValue(csTemp);
	}

	pGroup1->AddSubItem(pGroup11);

	return pGroup1;

}

CMFCPropertyGridProperty* ExplainFDNData(CString csData,int iNumber,BOOL bSubItem)
{

	return _ExplainADNData(_T("FDN "),csData,iNumber,bSubItem);
	/*CString csAlpha,csADN,csTemp;
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup11;

	CString csNumber;
	if (bSubItem)
	csNumber.Format(_T("%02d"),iNumber);

	pGroup1 = new CMFCPropertyGridProperty(_T("FDN ")+csNumber,0,bSubItem);

	csAlpha = csData.Left(csData.GetLength() - 28);
	csADN   = csData.Mid(csAlpha.GetLength(),24);

	pGroup11 = new CMFCPropertyGridProperty(_T("Alpha Identifier"),_T(""),csAlpha);

	if (!_WipeEmpty(csAlpha).IsEmpty())
	{
	csAlpha = TransationAlphaIdentifier(csAlpha);
	pGroup11->SetValue(csAlpha);
	pGroup11->SetOriginalValue(csAlpha);
	}
	pGroup1->AddSubItem(pGroup11);

	pGroup11 = new CMFCPropertyGridProperty(_T("Phone Number"),_T(""),csADN);

	if (!_WipeEmpty(csADN).IsEmpty())
	{
	csADN = _TransationADNNumber(csADN);
	pGroup11->SetValue(csADN);
	pGroup11->SetOriginalValue(csADN);
	}



	pGroup1->AddSubItem(pGroup11);

	csTemp = csData.Right(04).Left(02);
	pGroup11 = new CMFCPropertyGridProperty(_T("Capability/Configuration2 Record Identifier"),_T(""),csTemp);

	if (!_WipeEmpty(csTemp).IsEmpty())
	{
	pGroup11->SetValue(csTemp);
	pGroup11->SetOriginalValue(csTemp);
	}

	pGroup1->AddSubItem(pGroup11);


	csTemp = csData.Right(02);

	pGroup11 = new CMFCPropertyGridProperty(_T("Extension2 Record Identifier"),_T(""),csTemp);

	if (!_WipeEmpty(csTemp).IsEmpty())
	{
	pGroup11->SetValue(csTemp);
	pGroup11->SetOriginalValue(csTemp);
	}

	pGroup1->AddSubItem(pGroup11);

	return pGroup1;*/
}

CMFCPropertyGridProperty* ExplainSMSData(CString csData,int iNumber,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup11;


	
	CString csStatus,csDes,csNumber;
	CString csTS_SCA,csTP_DA,csTP_PID,csTP_DCS,csTP_SCTS,csTP_UDL,csTP_UD;
	CString csTemp;
	int iTS_SCALen,iOffset,iTP_DALen,iTP_MTI;

	iTP_MTI = 0;

	if (bSubItem)
		csNumber.Format(_T("%02d"),iNumber);

	if (csData.IsEmpty())
	{
		pGroup1 = new CMFCPropertyGridProperty("SMS "+csNumber,"Empty","数据未读取或者读取失败");
		return pGroup1;
	}
	
	pGroup1 = new CMFCPropertyGridProperty(_T("SMS ")+csNumber,0,bSubItem);

	csStatus = csData.Mid(0,2);
	pGroup11 = new CMFCPropertyGridProperty(_T("Status"),_T(""),csStatus);
	if (!WipeEmpty(csStatus).IsEmpty())
	{
		csDes = TransationSMSStatus(_CString2Int(csStatus));
		pGroup11->SetValue(csDes);
		pGroup11->SetOriginalValue(csDes);
	}

	iOffset = 4;

	pGroup1->AddSubItem(pGroup11);
	pGroup11 = new CMFCPropertyGridProperty(_T("Short Message Center"),_T(""),_T(""));

	if ((!WipeEmpty(csData).IsEmpty())&&(_CString2Int(csStatus) != 0))
	{
		iTS_SCALen = _CString2Int(csData.Mid(2,2));
		csTS_SCA   = csData.Mid(2,iTS_SCALen*2+2);
		pGroup11->SetDescription(csTS_SCA);
		csTS_SCA   = _TransationADNNumber(csTS_SCA);
		pGroup11->SetValue(csTS_SCA);	
		pGroup11->SetOriginalValue(csTS_SCA);
	}

	pGroup1->AddSubItem(pGroup11);
	pGroup11 = new CMFCPropertyGridProperty(_T("TP-MTI, TP-MMS, TP-SRI, TP-UDHI, TP-RP"),0,1);


	if ((!WipeEmpty(csData).IsEmpty())&&(_CString2Int(csStatus) != 0))
	{
		iOffset   += iTS_SCALen*2 ;

		iTP_MTI = _CString2Int(csData.Mid(iOffset,2));
		pGroup11->AddSubItem(new CMFCPropertyGridProperty(_T("TP-MTI"),(_variant_t) (iTP_MTI&3),TransationMTI(iTP_MTI)));
		pGroup11->AddSubItem(new CMFCPropertyGridProperty(_T("TP-MMS"),(_variant_t) ((iTP_MTI>>2)&1),TransationMMS(iTP_MTI>>2)));
		pGroup11->AddSubItem(new CMFCPropertyGridProperty(_T("TP-SRI"),(_variant_t) ((iTP_MTI>>5)&1),TransationSRI(iTP_MTI>>5)));
		pGroup11->AddSubItem(new CMFCPropertyGridProperty(_T("TP-UDHI"),(_variant_t) ((iTP_MTI>>6)&1),TransationUDHI(iTP_MTI>>6)));
		pGroup11->AddSubItem(new CMFCPropertyGridProperty(_T("TP-RP"),(_variant_t) ((iTP_MTI>>7)&1),TransationRP(iTP_MTI>>7)));

		iOffset   += 2;
	}

	pGroup1->AddSubItem(pGroup11);
	pGroup11 = new CMFCPropertyGridProperty(_T("Message Reference"),_T("") ,_T(""));

	if ((!WipeEmpty(csData).IsEmpty())&&(_CString2Int(csStatus) != 0)&&(iTP_MTI&1))
	{

		csDes = csData.Mid(iOffset,2);
		pGroup11->SetValue(csDes);
		pGroup11->SetDescription(csDes);
		pGroup11->SetOriginalValue(csDes);
		iOffset   += 2;
	}
	pGroup1->AddSubItem(pGroup11);

	pGroup11 = new CMFCPropertyGridProperty(_T("Destination Address"),_T("") ,_T(""));
	if ((!WipeEmpty(csData).IsEmpty())&&(_CString2Int(csStatus) != 0))
	{

		iTP_DALen = _CString2Int(csData.Mid(iOffset,2));
		csTP_DA   = csData.Mid(iOffset,iTP_DALen + 4+ (iTP_DALen%2));
		csDes     = _TransationAddress(csTP_DA);

		pGroup11->SetValue(csDes);
		pGroup11->SetDescription(csTP_DA);
		pGroup11->SetOriginalValue(csDes);
		iOffset += iTP_DALen +4 + iTP_DALen%2;
	}

	pGroup1->AddSubItem(pGroup11);



	csTP_PID = csData.Mid(iOffset, 2);
	iOffset += 2;	
	csTP_DCS = csData.Mid(iOffset, 2);
	iOffset += 2;	

	csTP_SCTS = csData.Mid(iOffset, 14);

	if ((iTP_MTI&3)!=1)
	{
		pGroup11 = ExplainDateTime(csTP_SCTS);
		iOffset += 14;
	}
	pGroup1->AddSubItem(pGroup11);


	pGroup11 = new CMFCPropertyGridProperty(_T("Message"),_T("") ,_T(""));

	if ((!WipeEmpty(csData).IsEmpty())&&(_CString2Int(csStatus) != 0))
	{

		csTP_UDL = csData.Mid(iOffset, 2);
		iOffset += 2;
		csTP_UD = csData.Mid(iOffset, _CString2Int(csTP_UDL)*2);

		//此处判断多条级联的情况
		if ((iTP_MTI>>2)&1)
			csTP_UD = csTP_UD.Mid(12,csTP_UD.GetLength()-12);

		pGroup11->SetValue(TransationData(csTP_UD,_CString2Int(csTP_DCS)));
		pGroup11->SetOriginalValue(TransationData(csTP_UD,_CString2Int(csTP_DCS)));


		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Message"),TransationData(csTP_UD,_CString2Int(csTP_DCS)),csTP_UD));
	}
	

	return pGroup1;

}

CMFCPropertyGridProperty* ExplainADNData(CString csData,int iNumber,BOOL bSubItem)
{
	return _ExplainADNData(_T("ADN "),csData,iNumber,bSubItem);
}

CMFCPropertyGridProperty* ExplainMSISDNData(CString csData,int iNumber,BOOL bSubItem)
{

	return _ExplainADNData(_T("MSISDN "),csData,iNumber,bSubItem);
	/*CMFCPropertyGridProperty* pGroup1;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("MSISDN")+csNumber,csData,&bRet);
	if (!bRet)
		return pGroup1;

	CString csAlpha,csADN;

	csAlpha = csData.Left(csData.GetLength() - 28);
	csADN   = csData.Mid(csAlpha.GetLength(),24);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Alpha Identifier"), TransationAlphaIdentifier(csAlpha) ,csAlpha));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Phone Number"), _TransationADNNumber(csADN) ,csADN));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Capability/Configuration2 Record Identifier"),csData.Right(04).Left(02) ,csData.Right(04).Left(02)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension2 Record Identifier"), csData.Right(02) ,csData.Right(02)));*/

//	return pGroup1;
}

CMFCPropertyGridProperty* ExplainSMSPData(CString csData,int iNumber,BOOL bSubItem)
{

	CString csAlpha,csADN,csTemp;
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup11;
	int iAlphaLen,iPI,iOffset;

	CString csNumber;
	if (bSubItem)
		csNumber.Format(_T("%02d"),iNumber);

	pGroup1 = new CMFCPropertyGridProperty(_T("SMSP")+csNumber,0,bSubItem);


	csAlpha   = csData.Left(csData.GetLength() - 56);
	iAlphaLen = csAlpha.GetLength();
	pGroup11  = new CMFCPropertyGridProperty(_T("Alpha Identifier"), _T("") ,csAlpha);

	if (!WipeEmpty(csAlpha).IsEmpty())
	{
		csAlpha = TranslateAlphaIdentifier(csAlpha);
		pGroup11->SetValue(csAlpha);
		pGroup11->SetOriginalValue(csAlpha);
	}
	pGroup1->AddSubItem(pGroup11);

	iOffset = iAlphaLen;

	iPI     = _CString2Int( csData.Mid(iOffset,2));
	iOffset+= 2;


	csADN   = csData.Mid(iOffset,24);
	pGroup11= new CMFCPropertyGridProperty(_T("TP-Destination Address"), _T("") ,csADN);
	iOffset+= 24;
	if ((!WipeEmpty(csADN).IsEmpty())&&((iPI&1)!=1))
	{
		csADN = _TransationADNNumber(csADN);
		pGroup11->SetValue(csADN);
		pGroup11->SetOriginalValue(csADN);
	}
	pGroup1->AddSubItem(pGroup11);


	csADN   = csData.Mid(iOffset,24);
	pGroup11= new CMFCPropertyGridProperty(_T("TS-Service Centre Address"), _T("") ,csADN);
	iOffset+= 24;
	if ((!WipeEmpty(csADN).IsEmpty())&&((iPI&2)!=2))
	{
		csADN = _TransationADNNumber(csADN);
		pGroup11->SetValue(csADN);
		pGroup11->SetOriginalValue(csADN);
	}
	pGroup1->AddSubItem(pGroup11);


	csTemp   = csData.Mid(iOffset,2);
	pGroup11= new CMFCPropertyGridProperty(_T("TP-Protocol Identifier"), _T("") ,csTemp);
	iOffset+= 2;

	if ((iPI&4)!=4)
	{
		pGroup11->SetValue(csTemp);
		pGroup11->SetOriginalValue(csTemp);		
	}
	pGroup1->AddSubItem(pGroup11);



	csTemp   = csData.Mid(iOffset,2);
		pGroup11= new CMFCPropertyGridProperty(_T("TP-Data Coding Scheme"), _T("") ,csTemp);
	iOffset+= 2;

	if ((iPI&4)!=4)
	{
		pGroup11->SetValue(csTemp);
		pGroup11->SetOriginalValue(csTemp);		
	}
	pGroup1->AddSubItem(pGroup11);


	csTemp   = csData.Mid(iOffset,2);
		pGroup11= new CMFCPropertyGridProperty(_T("TP-Validity Period"), _T("") ,csTemp);
	iOffset+= 2;

	if ((iPI&4)!=4)
	{
		pGroup11->SetValue(csTemp);
		pGroup11->SetOriginalValue(csTemp);		
	}
	pGroup1->AddSubItem(pGroup11);


	return pGroup1;
}

CMFCPropertyGridProperty* ExplainSMSSData( CString csData,BOOL bSubItem /*= TRUE*/ )
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("SMSS "),0,bSubItem);
	CMFCPropertyGridProperty* pGroup11;

	pGroup11 = new CMFCPropertyGridProperty(_T("Last Used TP-MR"), csData.Mid(00,02) ,csData.Mid(00,02));
	pGroup1->AddSubItem(pGroup11);

	pGroup11 = new CMFCPropertyGridProperty(_T("SMS Memory Cap. Exceeded Not. Flag"), _T("") ,csData.Mid(02,02));

	pGroup11->SetValue        ( TransationSMSNotFlagText(Getbit(csData,9)) );
	pGroup11->SetOriginalValue( TransationSMSNotFlagText(Getbit(csData,9)) );
	if (!bSubItem)
	{
		pGroup11->AddOption(TransationSMSNotFlagText(FALSE));
		pGroup11->AddOption(TransationSMSNotFlagText(TRUE));
	}
	pGroup11->AllowEdit(FALSE);
	pGroup1->AddSubItem(pGroup11);
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainCBMIData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Cell Broadcast Message identifier selection "),0,bSubItem);

	int iLen;
	CString csTemp;
	iLen = csData.GetLength();

	for (int i = 0 ;  i < iLen/4; i++)
	{
		csTemp.Format(_T("%02d"),i+1);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("CB Message Identifier ")+csTemp, csData.Mid(i*4,4) ,csData.Mid(i*4,4)));
	}



	return pGroup1;
}

CMFCPropertyGridProperty* ExplainSPNData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Service Provider Name"),0,bSubItem);

	CString csDes;
	int iCond,i;
	iCond = _CString2Int(csData.Mid(0,2));

	if (iCond&1)
		csDes =_T("要求显示已登记的PLMN : display of registered PLMN name required when registered PLMN is either HPLMN or a PLMN in the service provider PLMN list(see EFSPDI).");

	else 
		csDes =_T("不要求显示已登记的PLMN : display of registered PLMN name not required when registered PLMN is either HPLMN or a PLMN in the service provider PLMN list (see EFSPDI).");

	if (iCond&2)
		csDes +=_T("display of the service provider name is not required when registered PLMN is neither HPLMN nor a PLMN in the service provider PLMN list(see EFSPDI).");

	else 
		csDes +=_T("display of the service provider name is required when registered PLMN is neither HPLMN nor a PLMN in the service provider PLMN list(see EF).");

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Display Condition"), csData.Mid(0,2) , csDes));
	for ( i = 0 ; i < csData.GetLength() ;i+=2)
	{
		if (_CString2Int(csData.Mid(i,2)) == 0xFF)
			break;
	}

	if (csData.Mid(2,2) == _T("80"))
		csDes = TransationUcs2(csData.Mid(4,i-4),0x80);
	else if (csData.Mid(2,2) == _T("00"))
		csDes = Translate7bit(csData.Mid(4,i-4));
	else
		csDes =  TranslateAscii(csData.Mid(2,i-2)) ;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Service Provider Name"),csDes  , csData.Right(csData.GetLength()-2)));


	return pGroup1;

}

CMFCPropertyGridProperty* ExplainSMSRData( CString csData,int iNumber,BOOL bSubItem /*= TRUE*/ )
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("SMSR "),0,bSubItem);
	CMFCPropertyGridProperty* pGroup11;

	pGroup11 = new CMFCPropertyGridProperty(_T("SMS record identifier"), csData.Mid(00,02) ,csData.Mid(00,02));
	pGroup1->AddSubItem(pGroup11);

	pGroup11 = new CMFCPropertyGridProperty(_T("SMS status report"), csData.Mid(2,58) , csData.Mid(2,58));
	pGroup1->AddSubItem(pGroup11);
	return pGroup1;


	/*CMFCPropertyGridProperty* pGroup1;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Short message status reports")+csNumber,csData,&bRet);
	if (!bRet)
		return pGroup1;

	if (csData.GetLength() != 60)
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Short message status reports"), _T("文件长度错误") ,_T("Record length: 30 bytes")));

	}
	else
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("SMS record identifier"), csData.Mid(0,2) ,_T("'00' - empty record,'01' to 'FF' - record number of the corresponding SMS in EFSMS.")));

		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("SMS status report"), csData.Mid(2,58) , csData.Mid(2,58)));
	}


	return pGroup1;*/

}

CMFCPropertyGridProperty* ExplainCBMIDData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Cell Broadcast Message Identifier for Data Download "),0,bSubItem);

	int iLen;
	CString csTemp;
	iLen = csData.GetLength();

	for (int i = 0 ;  i < iLen/4; i++)
	{
		csTemp.Format(_T("%02d"),i+1);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("CB Message Identifier ")+csTemp, csData.Mid(i*4,4) ,csData.Mid(i*4,4)));
	}



	return pGroup1;
}

CMFCPropertyGridProperty* ExplainSDNData(CString csData,int iNumber, BOOL bSubItem /*= TRUE*/)
{

	return _ExplainADNData(_T("SDN "),csData,iNumber,bSubItem);
	/*CString csAlpha,csADN;
	CMFCPropertyGridProperty* pGroup1;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("SDN")+csNumber,csData,&bRet);
	if (!bRet)
	return pGroup1;

	csAlpha = csData.Left(csData.GetLength() - 28);
	csADN   = csData.Mid(csAlpha.GetLength(),24);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Alpha Identifier"), TransationAlphaIdentifier(csAlpha) ,csAlpha));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Phone Number"), _TransationADNNumber(csADN) ,csADN));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Capability/Configuration2 Record Identifier"),csData.Right(04).Left(02) ,csData.Right(04).Left(02)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension3 Record Identifier"), csData.Right(02) ,csData.Right(02)));

	return pGroup1;*/
}

CMFCPropertyGridProperty* ExplainEXTData( CString csData,int iNumber,BOOL bSubItem /*= TURE*/ )
{


	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Extension "),0,bSubItem);
	CMFCPropertyGridProperty* pGroup11;

	pGroup11 = new CMFCPropertyGridProperty(_T("Record type"), _T("") ,csData.Mid(00,02));


	pGroup11->SetValue(TransationEXTType(_CString2Int(csData.Mid(00,02))));
	pGroup11->SetOriginalValue(TransationEXTType(_CString2Int(csData.Mid(00,02))));
	

	if (!bSubItem)
	{
		pGroup11->AddOption(TransationEXTType(0));
		pGroup11->AddOption(TransationEXTType(1));
		pGroup11->AddOption(TransationEXTType(2));
		pGroup11->AddOption(TransationEXTType(3));

	}

	pGroup1->AddSubItem(pGroup11);

	pGroup11 = new CMFCPropertyGridProperty(_T("Extension data"), csData.Mid(2,22) , csData.Mid(2,22));
	pGroup1->AddSubItem(pGroup11);

	pGroup11 = new CMFCPropertyGridProperty(_T("Identifier"),csData.Mid(24,2) ,csData.Mid(24,2));
	pGroup1->AddSubItem(pGroup11);

	return pGroup1;



	/*CString csDes;
	CMFCPropertyGridProperty* pGroup1;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Extension")+csNumber,csData,&bRet);
	if (!bRet)
	return pGroup1;

	if (csData.GetLength() != 26)
	{
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension"), _T("长度应该为13") ,csData));
	}
	else
	{
	if (_CString2Int(csData.Mid(0,2))&1)
	csDes = _T("被叫用户子地址(Called Party Subaddress)");
	if (_CString2Int(csData.Mid(0,2))&1)
	csDes = _T("溢出数据(Additional data)");

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Record type"), csData.Mid(0,2) ,csDes));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension data"),  csData.Mid(2,22) , csData.Mid(2,22)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Identifier"),csData.Right(02) ,_T("下一个记录的号码，‘FF’表示链接的结束。") ));

	}*/




	return pGroup1;
}

CMFCPropertyGridProperty* ExplainBDNData(CString csData,int iNumber, BOOL bSubItem /*= TRUT*/)
{
	CString csAlpha,csADN;
	CMFCPropertyGridProperty* pGroup1;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("BDN")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	csAlpha = csData.Left(csData.GetLength() - 28);
	csADN   = csData.Mid(csAlpha.GetLength(),24);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Alpha Identifier"), TranslateAlphaIdentifier(csAlpha) ,csAlpha));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Phone Number"), _TransationADNNumber(csADN) ,csADN));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Capability/Configuration2 Record Identifier"),csData.Right(06).Left(02) ,csData.Right(06).Left(02)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension4 Record Identifier"), csData.Right(04).Left(02) ,csData.Right(04).Left(02)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Comparison Method Pointer"), csData.Right(02) ,csData.Right(02)));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainCCP2Data(CString csData,int iNumber, BOOL bSubItem /*= TRUT*/)
{
	CString csDes;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Bearer capability information element ")+csNumber,0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(csNumber, csData ,csData));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainCBMIRData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Cell Broadcast Message Identifier Range selection "),0,bSubItem);

	int iLen;
	CString csTemp;
	iLen = csData.GetLength();

	for (int i = 0 ;  i < iLen/4; i++)
	{
		csTemp.Format(_T("%02d"),i+1);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("CB Message Identifier Range ")+csTemp, csData.Mid(i*4,4) ,csData.Mid(i*4,4)));
	}

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainSUMEData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("SetUpMenu Elements"),0,bSubItem);

	if (csData.Mid(0,2)!= _T("85"))
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Alpha"), _T(""),csData));
	}
	else
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Title Alpha Identifier"), _T("85"),_T("Alpha")));


		csDes =GetTLVData(csData,0x85);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Title Icon Identifier"), TransationAlpha(csDes),csDes));

	}

	return pGroup1;


}

CMFCPropertyGridProperty* ExplainESTData(CString csData, BOOL bSubItem /*= TRUE*/)
{


	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Enabled Services Table"),0,bSubItem);

	pGroup1->AddSubItem(_NewSupportedText(_T("Fixed Dialling Numbers (FDN)") , Getbit(csData,1),false,!bSubItem));
	pGroup1->AddSubItem(_NewSupportedText(_T("Barred Dialling Numbers (BDN)"), Getbit(csData,2),false,!bSubItem));
	pGroup1->AddSubItem(_NewSupportedText(_T("APN Control List (ACL)")       , Getbit(csData,3),false,!bSubItem));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainACLData( CString csData, BOOL bSubItem/*= TRUE*/ )
{
	CString csAPN;
	CString csNumber;
	int iSum;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Access Point Name Control List"),0,bSubItem);
	iSum =_CString2Int(csData.Left(02));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Number of APNs"),(_variant_t) iSum ,csData));


	for (int i = 0 ; i < iSum ; i++)
	{
		csNumber.Format(_T("%02d"),i+1);
		csAPN = csData.Mid(2,csData.GetLength()-2);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("APN ")+csNumber,GetTLVData(csAPN,0xDD,i+1) ,GetTLVData(csAPN,0xDD,i+1)));

	}

	return pGroup1;

}

CMFCPropertyGridProperty* ExplainCMIData(CString csData, BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Comparison Method Information"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Alpha Identifier"),TransationAlpha(csData.Left(csData.GetLength()-2)) ,csData.Left(csData.GetLength()-2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Comparison Method Identifier"),csData.Right(02) ,csData.Right(02)));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainSTARTHFNata(CString csData, BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Initialisation values for Hyperframe number"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("START_CS"),csData.Left(06) ,csData.Left(06)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("START_PS"),csData.Right(06),csData.Right(06)));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainTHRESHOLData(CString csData, BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Maximum value of START"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Maximum value of STARTCS or STARTPS"),csData ,csData));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainPLMNwAcTData( CString csData,BOOL bSubItem /*= TRUE*/ )
{
	int iLen;
	CString csResult;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("User controlled PLMN selector with Access Technology"),0,bSubItem);

	iLen = csData.GetLength();

	for (int i = 0 ; i < iLen ;i+=10)
	{
		csResult.Format(_T("%02d"),i/10+1);

		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("PLMN " +csResult),TransationMNCMCC(csData.Mid(i,6))  ,GenerateMCCMNCDescription(csData.Mid(i,6))));

		//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("PLMN Access Technology Identifier "+csResult),csData.Mid(i+6,4) ,csData.Mid(i+6,4)));

		pGroup1->AddSubItem(ExplainATI(csData.Mid(i+6,4),!bSubItem));
	}


	return pGroup1;
}

CMFCPropertyGridProperty* ExplainOPLMNwACTData(CString csData,BOOL bSubItem /*= TRUE*/ )
{
	int iLen;
	CString csResult;
	CString csSub;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Operator controlled PLMN selector with Access Technology"),0,bSubItem);
	iLen = csData.GetLength();
	for (int i = 0 ; i < iLen ;i+=10)
	{
		csResult.Format(_T("%02d"),i/10+1);

		csSub = csData.Mid(i,6);
		csSub.MakeUpper();
		if (csSub.Compare(_T("FFFFFF")) != 0)
		{
			pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("PLMN " +csResult),TransationMNCMCC(csSub)  ,GenerateMCCMNCDescription(csSub)));
			pGroup1->AddSubItem(ExplainATI(csData.Mid(i+6,4),!bSubItem));
		}

	}
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainHPLMNwACTData(CString csData,BOOL bSubItem /*= TRUE*/ )
{
	int iLen;
	CString csResult;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("HPLMN selector with Access Technology"),0,bSubItem);
	iLen = csData.GetLength();
	for (int i = 0 ; i < iLen ;i+=10)
	{
		csResult.Format(_T("%02d"),i/10+1);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("PLMN " +csResult),TransationMNCMCC(csData.Mid(i,6))  ,GenerateMCCMNCDescription(csData.Mid(i,6))));
		pGroup1->AddSubItem(ExplainATI(csData.Mid(i+6,4),!bSubItem));
	}
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainPSLOCIData(CString csData, BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Packet Switched location information"),0,bSubItem);

	pGroup1->AddSubItem(ExplainMID(csData.Mid(0,8)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("P-TMSI signature"),csData.Mid(8,6) ,csData.Mid(8,6)));
	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("RAI"),csData.Mid(14,12) ,csData.Mid(14,12)));

	pGroup1->AddSubItem (ExplainRAI(csData.Mid(14,12)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Routing Area update status"),TransationRAUStatus (csData.Mid(26,2)) ,csData.Mid(26,2)));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainACCData(CString csData, BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Access Control Class"),csData,csData);
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainFPLMNData(CString csData, BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Forbidden PLMNs"),0,bSubItem);
	CString csResult;
	int iLen = csData.GetLength();

	for (int i = 0 ; i < iLen ;i+=6)
	{
		csResult.Format(_T("%02d"),i/6+1);

		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("PLMN " +csResult),TransationMNCMCC(csData.Mid(i,6)) ,GenerateMCCMNCDescription(csData.Mid(i,6))));

	}
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainLOCIData(CString csData,BOOL bSubItem)
{
	int iLen;
	CString csResult;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Location Information"),0,bSubItem);
	CMFCPropertyGridProperty* pGroup11;

	iLen = csData.GetLength();


	//pGroup11 = ExplainMID(csData.Mid(0,8),TRUE,!bSubItem);

	pGroup11 = new CMFCPropertyGridProperty(_T("TMSI"),csData.Mid(0,8) ,csData.Mid(0,8));
	pGroup1->AddSubItem(pGroup11);

	pGroup11 = ExplainLAI(csData.Mid(8,10));
	pGroup1->AddSubItem(pGroup11);

	pGroup11 = new CMFCPropertyGridProperty(_T("RFU"),csData.Mid(18,2) ,csData.Mid(18,2));
	pGroup11->Enable(FALSE);
	pGroup1->AddSubItem(pGroup11);

	pGroup11 = new CMFCPropertyGridProperty(_T("Location update status"),
		TransationLOCIStatus(_CString2Int (csData.Mid(20,2)))  ,csData.Mid(20,2));
	
    
	if (!bSubItem)
	{
		pGroup11->AddOption(TransationLOCIStatus(0));
		pGroup11->AddOption(TransationLOCIStatus(1));
    	pGroup11->AddOption(TransationLOCIStatus(2));
		pGroup11->AddOption(TransationLOCIStatus(3));
		pGroup11->AddOption(TransationLOCIStatus(4));
	}
	pGroup1->AddSubItem(pGroup11);

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainICIData(CString csData,int iNumber,BOOL bSubItem)
{
	CString csAlpha,csADN,csDes;
	int iAlphaLen;

	CMFCPropertyGridProperty* pGroup1;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Incoming Call Information")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	csAlpha   = csData.Mid( 0,csData.GetLength() - 56);
	iAlphaLen = csAlpha.GetLength();
	pGroup1->AddSubItem(new CMFCPropertyGridProperty( _T("Alpha Identifier"),TranslateAlphaIdentifier(csAlpha),csAlpha));

	csADN = csData.Mid(iAlphaLen,24);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Incoming Call Number"), _TransationADNNumber(csADN) ,csADN));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Capability/Configuration2 Record Identifier"),WipeEmpty(csData.Mid(iAlphaLen+24,2)) ,csData.Mid(iAlphaLen+24,2)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension5 Record Identifier"), WipeEmpty( csData.Mid(iAlphaLen+26,2)) ,csData.Mid(iAlphaLen+26,2)));

	pGroup1->AddSubItem(ExplainDateTime(csData.Mid(iAlphaLen+28,14)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Incoming call duration"),csData.Mid(iAlphaLen+42,6) ,csData.Mid(iAlphaLen+42,6)));

	if (_CString2Int(csData.Mid(iAlphaLen+48,2))&1)
		csDes = _T("Not Answered");
	else
		csDes = _T("Answered");

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Incoming call status"), csDes,csData.Mid(iAlphaLen+48,2)));

	if (_CString2Int(csData.Mid(iAlphaLen+50,2))&1)
		csDes = _T("Local Phone Book (USIM Specific)");
	else
		csDes = _T("Global Phone Book (DFTELECOM)");

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Link to phone book entry"),csDes ,csData.Mid(iAlphaLen+50,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("PBR Record"),WipeEmpty(csData.Mid(iAlphaLen+52,2)) ,csData.Mid(iAlphaLen+52,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("ADN Record"),WipeEmpty(csData.Mid(iAlphaLen+54,2)) ,csData.Mid(iAlphaLen+54,2)));



	return pGroup1;
}

CMFCPropertyGridProperty* ExplainOCIData(CString csData,int iNumber,BOOL bSubItem)
{
	CString csAlpha,csADN,csDes;
	int iAlphaLen;

	CMFCPropertyGridProperty* pGroup1;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Outgoing Call Information")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	csAlpha   = csData.Mid( 0,csData.GetLength() - 54);
	iAlphaLen = csAlpha.GetLength();

	pGroup1->AddSubItem(new CMFCPropertyGridProperty( _T("Alpha Identifier"),TranslateAlphaIdentifier(csAlpha),csAlpha));

	csADN = csData.Mid(iAlphaLen,24);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Outgoing Call Number"), _TransationADNNumber(csADN) ,csADN));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Capability/Configuration2 Record Identifier"),WipeEmpty (csData.Mid(iAlphaLen+24,2)) ,csData.Mid(iAlphaLen+24,2)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension5 Record Identifier"), WipeEmpty(csData.Mid(iAlphaLen+26,2)) ,csData.Mid(iAlphaLen+26,2)));

	pGroup1->AddSubItem(ExplainDateTime(csData.Mid(iAlphaLen+28,14)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Outgoing call duration"),csData.Mid(iAlphaLen+42,6) ,csData.Mid(iAlphaLen+42,6)));



	if (_CString2Int(csData.Mid(iAlphaLen+48,2))&1)
		csDes = _T("Local Phone Book (USIM Specific)");
	else
		csDes = _T("Global Phone Book (DFTELECOM)");

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Link to phone book entry"),csDes ,csData.Mid(iAlphaLen+48,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("PBR Record"),WipeEmpty(csData.Mid(iAlphaLen+50,2)) ,csData.Mid(iAlphaLen+50,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("ADN Record"),WipeEmpty(csData.Mid(iAlphaLen+52,2)) ,csData.Mid(iAlphaLen+52,2)));


	return pGroup1;
}

CMFCPropertyGridProperty* ExplainICTData(CString csData,int iNumber,BOOL bSubItem)
{
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Accumulated call timer value ")+csNumber,csData,csData);
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainOCTData(CString csData,int iNumber,BOOL bSubItem)
{
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Outgoing Call Timer ")+csNumber,csData,csData);
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainADData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Administrative Data"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("UE operation mode"), TransationUEMode (csData.Mid(0,2)) ,csData));

	if (_CString2Int(csData.Mid(0,2))&1)
	{
		if (_CString2Int(csData.Mid(4,2))&1)
			csDes = _T("ciphering indicator feature enabled");
		else
			csDes = _T("ciphering indicator feature disabled");
	}

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Additional information"), csData.Mid(2,4) ,csDes));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("length of MNC in the IMSI"),csData.Mid(6,2),csData.Mid(6,2)));


	return pGroup1;
}

CMFCPropertyGridProperty* ExplainVGCSData(CString csData,BOOL bSubItem)
{

	int iLen;
	CString csNumber;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Voice Group Call Service"),0,bSubItem);

	iLen = csData.GetLength();


	for (int i = 0 ; i < iLen ; i += 8)
	{
		csNumber.Format(_T("%02d"),i+1);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Group ID ")+csNumber ,csData.Mid(i,8),csData.Mid(i,8)));
	}

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainVGCSSData(CString csData,BOOL bSubItem)
{
	CString csID;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Voice Group Call Service Status"),0,bSubItem);

	for (int i=0;i<56;i++)
	{
		csID.Format(_T("%02d"),i);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Group ID ")+csID,TransationSupportedText( Getbit(csData,i+1)) , _T("0 means - Group ID deactivated,1 means - Group ID activated")));

	}

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainVBSData(CString csData,BOOL bSubItem)
{
	int iLen;
	CString csNumber;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Voice Broadcast Service"),0,bSubItem);
	iLen = csData.GetLength();
	for (int i = 0 ; i < iLen ; i += 8)
	{
		csNumber.Format(_T("%02d"),i+1);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Group ID ")+csNumber ,csData.Mid(i,8),csData.Mid(i,8)));
	}
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainVBSSData(CString csData,BOOL bSubItem)
{
	CString csID;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Voice Broadcast Service Status"),0,bSubItem);

	for (int i=0;i<56;i++)
	{
		csID.Format(_T("%02d"),i);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Group ID ")+csID,TransationSupportedText( Getbit(csData,i+1)) ,_T("0 means - Group ID deactivated,1 means - Group ID activated")));

	}

	return pGroup1;
}

CMFCPropertyGridProperty* ExplaineMLPPData(CString csData,BOOL bSubItem)
{
	CString csID;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("enhanced Multi Level Precedence and Pre-emption"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Priority levels"),csData.Mid(0,2),csData.Mid(0,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Fast call set-up conditions"),csData.Mid(2,2),csData.Mid(2,2)));
	return pGroup1;
}

CMFCPropertyGridProperty* ExplaineAAeMData(CString csData,BOOL bSubItem)
{
	CString csID;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Automatic Answer for eMLPP Service"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Automatic answer priority levels"),csData,csData));
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainECCData(CString csData,int iNumber,BOOL bSubItem)
{
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Emergency Call Codes ")+csNumber,0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty( _T("Emergency Call Code"),csData.Mid(0,6),csData.Mid(0,6)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Emergency Call Code Alpha Identifier"),csData.Mid(6,csData.GetLength()-8),csData.Mid(6,csData.GetLength()-8)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Emergency Service Category"),csData.Right(2),csData.Right(2)));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainHiddenkeyData(CString csData,BOOL bSubItem /*== TRUE*/)
{
	CString csID;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Key for hidden phone book entries"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Hidden Key"),csData,csData));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainNETPARData(CString csData,BOOL bSubItem /*== TRUE*/)
{
	CString csID;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Network Parameters"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("GSM Cell Information Tag"),csData,csData));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainPNNData(CString csData,int iNumber,BOOL bSubItem)
{

	CString csPNN;
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup11;

	CString csNumber;
	if (bSubItem)
		csNumber.Format(_T("%02d"),iNumber);

	pGroup1  = new CMFCPropertyGridProperty(_T("PLMN Network Name ")+csNumber,0,bSubItem);


	pGroup11 = new CMFCPropertyGridProperty(_T("Full name for network"),_T(""),_T(""));
	csPNN = GetTLVData(csData,0x43);
	if (!csPNN.IsEmpty())
	{
		pGroup11->SetValue(TranslatePNN(csPNN));
		pGroup11->SetOriginalValue(TranslatePNN(csPNN));
		pGroup11->SetDescription(csPNN);
	}
	pGroup1 ->AddSubItem(pGroup11);

	pGroup11 = new CMFCPropertyGridProperty(_T("Short name for network"),_T(""),_T(""));
	csPNN = GetTLVData(csData,0x45);
	if (!csPNN.IsEmpty())
	{
		pGroup11->SetValue(TranslatePNN(csPNN));
		pGroup11->SetOriginalValue(TranslatePNN(csPNN));
		pGroup11->SetDescription(csPNN);
	}
	pGroup1 ->AddSubItem(pGroup11);

	pGroup11 = new CMFCPropertyGridProperty(_T("PLMN Additional Information"),_T(""),_T(""));
	csPNN = GetTLVData(csData,0x80);
	if (!csPNN.IsEmpty())
	{
		pGroup11->SetValue(TranslatePNN(csPNN));
		pGroup11->SetOriginalValue(TranslatePNN(csPNN));
		pGroup11->SetDescription(csPNN);
	}
	pGroup1 ->AddSubItem(pGroup11);

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainOPLData(CString csData,int iNumber,BOOL bSubItem)
{
	CString csDes;

	CMFCPropertyGridProperty* pGroup1;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Operator PLMN List")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MNCMCC"),TransationMNCMCC( csData.Mid(0,6) ), GenerateMCCMNCDescription(csData.Mid(0,6))));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("LAC/TAC"),csData.Mid(6,8),csData.Mid(6,8)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("PLMN Network Name Record Identifier"),csData.Mid(14,2),csData.Mid(14,2)));


	return pGroup1;
}

CMFCPropertyGridProperty* ExplainMBDNData(CString csData,int iNumber,BOOL bSubItem)
{
	CString csAlpha,csADN;

	CMFCPropertyGridProperty* pGroup1;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Mailbox Dialling Numbers")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;


	csAlpha = csData.Left(csData.GetLength() - 28);
	csADN   = csData.Mid(csAlpha.GetLength(),24);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Alpha Identifier"), TranslateAlphaIdentifier(csAlpha) ,csAlpha));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Phone Number"), _TransationADNNumber(csADN) ,csADN));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Capability/Configuration2 Record Identifier"),csData.Right(04).Left(02) ,csData.Right(04).Left(02)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension6 Record Identifier"), csData.Right(02) ,csData.Right(02)));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainMBIData(CString csData,int iNumber,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Mailbox Identifier")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Voicemail"), csData.Mid(0,2) ,csData.Mid(0,2)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Fax"),csData.Mid(2,2) ,csData.Mid(2,2)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Electronic Mail"),csData.Mid(4,2) ,csData.Mid(4,2)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Other"),csData.Mid(6,2) ,csData.Mid(6,2)));

	if (csData.GetLength()>8)
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Videomail"), csData.Mid(8,2) ,csData.Mid(8,2)));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainMWISData(CString csData,int iNumber,BOOL bSubItem)

{
	CString csAlpha,csADN;
	CMFCPropertyGridProperty* pGroup1;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Message Waiting Indication Status")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(ExplainMWIS(csData.Mid(0,2)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Voicemail Messages Waiting"), csData.Mid(2,2) ,csData.Mid(2,2)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Fax Messages Waiting"),csData.Mid(2,2) ,csData.Mid(4,2)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Electronic Mail Messages Waiting"),csData.Mid(6,2) ,csData.Mid(6,2)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Other Messages Waiting"),csData.Mid(8,2) ,csData.Mid(8,2)));

	if (csData.GetLength()>10)
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Number of Videomail Messages waiting"), csData.Mid(10,2) ,csData.Mid(10,2)));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainCFISData(CString csData,int iNumber,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	CString csAlpha,csADN;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Call Forwarding Indication Status")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;


	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MSP number"), csData.Mid(0,2) , csData.Mid(0,2)));

	pGroup1->AddSubItem(ExplainCFUISD(csData.Mid(2,2)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Phone Number"), _TransationADNNumber(csData.Mid(4,24)) ,csData.Mid(4,24)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Capability/Configuration2 Record Identifier"),csData.Right(04).Left(02) ,csData.Right(04).Left(02)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension6 Record Identifier"), csData.Right(02) ,csData.Right(02)));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainSPDIData(CString csData,BOOL bSubItem /*== TRUE*/)
{
	CString csID;
	CString csPLMN;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Service Provider Display Information"),0,bSubItem);

	csPLMN = GetTLVData(csData,0xA3);

	csPLMN = GetTLVData(csPLMN,0x80);
	CMFCPropertyGridProperty* pGroup11 = new CMFCPropertyGridProperty(_T("Service provider PLMN list"),0,1);


	if (!csPLMN.IsEmpty())
	{
		for (int i = 0 ; i  < csPLMN.GetLength()/3;i++)
		{
			csID .Format(_T("%02d"),i+1);
			pGroup11->AddSubItem(new CMFCPropertyGridProperty(_T("PLMN ")+ csID,TransationMNCMCC(csPLMN.Mid(i*6,6)), GenerateMCCMNCDescription( csPLMN.Mid(i*6,6))));
		}
	}

	pGroup1->AddSubItem(pGroup11);
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainMMSNData(CString csData,int iNumber,BOOL bSubItem /*== TRUE*/)
{
	CMFCPropertyGridProperty* pGroup1;
	CString csNumber,csDes;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("MMS Notification")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem( new CMFCPropertyGridProperty(_T("MMS Status"),csData.Mid(0,4) ,csData.Mid(0,4) ));
	pGroup1->AddSubItem( new CMFCPropertyGridProperty(_T("MMS Implementation"),csData.Mid(4,2) ,csData.Mid(4,2) ));
	pGroup1->AddSubItem( new CMFCPropertyGridProperty(_T("MMS Notification"),csData.Mid(csData.GetLength()-8,2),csData.Mid(csData.GetLength()-8,2) ));
	pGroup1->AddSubItem( new CMFCPropertyGridProperty(_T("Extension file record number"),csData.Right(02),csData.Right(02) ));


	return pGroup1;

}

CMFCPropertyGridProperty* ExplainMMSICPData(CString csData,BOOL bSubItem /*== TRUE*/)
{


	CMFCPropertyGridProperty* pGroup1;

	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("MMS Issuer Connectivity Parameters"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	int iNumber = 1;



	while (!GetTLVData(csData,0xAB,iNumber).IsEmpty())
	{
		pGroup1->AddSubItem(Explain_MMSICP(GetTLVData(csData,0xAB,iNumber),iNumber));	
		iNumber++;
	}



	return pGroup1;
}

CMFCPropertyGridProperty* ExplainMMSUPData(CString csData,int iNumber,BOOL bSubItem /*== TRUE*/)
{
	CMFCPropertyGridProperty* pGroup1;
	CString csNumber,csDes;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("MMS User Preferences")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	csDes = GetTLVData(csData,0x80);
	pGroup1->AddSubItem( new CMFCPropertyGridProperty(_T("MMS Implementation"),csDes ,csDes ));
	csDes = GetTLVData(csData,0x81);
	pGroup1->AddSubItem( new CMFCPropertyGridProperty(_T("MMS User preference profile name"),csDes ,csDes ));
	csDes = GetTLVData(csData,0x82);
	pGroup1->AddSubItem( new CMFCPropertyGridProperty(_T("MMS User Preference information"),csDes ,csDes ));

	return pGroup1;

}

CMFCPropertyGridProperty* ExplainNIAData(CString csData,int iNumber,BOOL bSubItem /*== TRUE*/)
{
	CMFCPropertyGridProperty* pGroup1;
	CString csNumber,csDes;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Network's Indication of Alerting")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Alerting category"),csData.Mid(0,2),csData.Mid(0,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Informative text"),csData.Mid(2,csData.GetLength()-2),csData.Mid(2,csData.GetLength()-2)));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainVGCSCAData(CString csData,BOOL bSubItem /*== TRUE*/)
{

	int iLen =  csData.GetLength();
	CString csTemp;

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Voice Group Call Service Ciphering Algorithm"),0,bSubItem);

	for (int i = 0 ; i < iLen ; i+=2 )
	{
		csTemp.Format(_T("%02d"),i/2+1);

		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("VGCS Group ciphering algorithm identifier for V_Ki of Group ")+csTemp,csData.Mid(i,2),csData.Mid(i,2)));
	}





	return pGroup1;
}

CMFCPropertyGridProperty* ExplainVBSCAData(CString csData,BOOL bSubItem /*== TRUE*/)
{

	int iLen =  csData.GetLength();
	CString csTemp;

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Voice Broadcast Service Ciphering Algorithm"),0,bSubItem);

	for (int i = 0 ; i < iLen ; i+=2 )
	{
		csTemp.Format(_T("%02d"),i/2+1);

		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("VBS Group ciphering algorithm identifier for V_Ki of Group ")+csTemp,csData.Mid(i,2),csData.Mid(i,2)));
	}





	return pGroup1;
}

CMFCPropertyGridProperty* ExplainGBABPData(CString csData,BOOL bSubItem /*== TRUE*/)
{


	int iLen ,iOffset ;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("GBA Bootstrapping parameters"),0,bSubItem);

	iLen = _CString2Int( csData.Mid(0,2));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty( _T("RAND"), csData.Mid(2,iLen*2)));

	iOffset = iLen *2 +2;

	iLen = _CString2Int( csData.Mid(iOffset,2));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty( _T("B-TID"), csData.Mid(iOffset+2,iLen*2)));


	iOffset = iOffset + iLen*2 +2;

	iLen = _CString2Int( csData.Mid(iOffset,2));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty( _T("Key lifetime"), csData.Mid(iOffset+2,iLen*2)));




	return pGroup1;
}

CMFCPropertyGridProperty* ExplainMSKData(CString csData,int iNumber,BOOL bSubItem /*== TRUE*/)
{
	CMFCPropertyGridProperty* pGroup1;
	int iSum;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("MBMS Service Keys List")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Key Domain ID "),csData.Mid(0,6),csData.Mid(0,6)));

	iSum = _CString2Int(csData.Mid(06,02));

	for (int i = 0 ; i < iSum ; i++)
	{
		csNumber.Format(_T("%02d"),i);
		pGroup1->AddSubItem( new CMFCPropertyGridProperty (_T("MSK ID ")+csNumber,csData.Mid(4+ i*8,4),csData.Mid(4+ i*8,4)  ));
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Time Stamp Counter ")+csNumber,csData.Mid(8+ i*8,4),csData.Mid(8+ i*8,4) ) );

	}
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainMUKData(CString csData,int iNumber,BOOL bSubItem /*== TRUE*/)
{
	CMFCPropertyGridProperty* pGroup1;
	CString csNumber,csTemp;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("MBMS User Key")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;


	csTemp  = GetTLVData(csData,0xA0);

	if (!csTemp.IsEmpty())
	{

		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MUK IDr value "),GetTLVData(csTemp,0x80),GetTLVData(csTemp,0x80)));
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MUK IDi Value "),GetTLVData(csTemp,0x82),GetTLVData(csTemp,0x82)));

	}


	csTemp  = GetTLVData(csData,0x81);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Time Stamp Counter "),csTemp,csTemp));

	}



	return pGroup1;
}

CMFCPropertyGridProperty* ExplainEHPLMNData(CString csData,BOOL bSubItem)
{


	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Equivalent HPLMN"),0,bSubItem);
	int iLen;
	CString csNumber;

	iLen = csData.GetLength();

	for (int i = 0 ; i <  iLen; i += 6)
	{

		csNumber .Format(_T("%2d"),i/6 +1);
		pGroup1->AddSubItem( new CMFCPropertyGridProperty (_T("EHPLMN ")+csNumber ,TransationMNCMCC(csData.Mid(i,6)) , GenerateMCCMNCDescription(csData.Mid(i,6)) ));

	}



	return pGroup1;
}

CMFCPropertyGridProperty* ExplainGBANLData(CString csData,int iNumber,BOOL bSubItem)
{

	CString csNumber,csTemp;
	csNumber.Format(_T("%02d"),iNumber);


	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("GBA NAF List ")+csNumber,0,bSubItem);


	csTemp  = GetTLVData(csData,0x80);

	if (!csTemp.IsEmpty())
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NAF_ID "),csTemp,csTemp));

	csTemp  = GetTLVData(csData,0x81);

	if (!csTemp.IsEmpty())
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("B-TID "),csTemp,csTemp));




	return pGroup1;
}

CMFCPropertyGridProperty* ExplainEHPLMNPIData(CString csData,BOOL bSubItem /*== TRUE*/)
{
	CString csDes;

	switch (_CString2Int(csData))
	{
	case 00 :
		csDes = _T("No preference for the display mode");
		break;
	case 01:
		csDes = _T("Display the highest-priority available EHPLMN only");
		break;
	case 02:
		csDes = _T("Display all the available EHPLMNs");
		break;
	default:
		csDes = _T("RFU");
		break;
	}


	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Equivalent HPLMN Presentation Indication"),csData,csDes);



	return pGroup1;
}

CMFCPropertyGridProperty* ExplainLRPLMNSIData(CString csData,BOOL bSubItem /*== TRUE*/)
{
	CString csDes;

	switch (_CString2Int(csData))
	{
	case 00 :
		csDes = _T("The UE shall attempt registration on the last RPLMN as described in TS 23.122");
		break;
	case 01:
		csDes = _T("The UE shall attempt registration on the home network as described in TS 23.122");
		break;
	default:
		csDes = _T("RFU");
		break;
	}


	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("(Last RPLMN Selection Indication"),csData,csDes);



	return pGroup1;
}

CMFCPropertyGridProperty* ExplainNAFKCAData(CString csData,int iNumber,BOOL bSubItem /*== TRUE*/)
{

	CString csNumber,csTemp;
	csNumber.Format(_T("%02d"),iNumber);


	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("NAF Key Centre Address ")+csNumber,0,bSubItem);


	csTemp  = GetTLVData(csData,0x80);

	if (!csTemp.IsEmpty())
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NAF Key Centre "),csTemp,csTemp));


	return pGroup1;
}

CMFCPropertyGridProperty* ExplainSPNIData(CString csData,int iNumber,BOOL bSubItem /*== TRUE*/)
{

	CString csNumber,csTemp;
	csNumber.Format(_T("%02d"),iNumber);


	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Service Provider Name Icon ")+csNumber,0,bSubItem);


	csTemp  = GetTLVData(csData,0x80);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Icon Qualifier "),csTemp.Mid(0,2),csTemp.Mid(0,2)));
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Icon Link "),csTemp.Mid(2,csTemp.GetLength()-2),csTemp.Mid(2,csTemp.GetLength()-2)));
	}

	csTemp  = GetTLVData(csData,0x81);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Icon Qualifier "),csTemp.Mid(0,2),csTemp.Mid(0,2)));
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Icon Link "),csTemp.Mid(2,csTemp.GetLength()-2),csTemp.Mid(2,csTemp.GetLength()-2)));
	}
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainPNNIData(CString csData,int iNumber,BOOL bSubItem /*== TRUE*/)
{

	CString csNumber,csTemp;
	csNumber.Format(_T("%02d"),iNumber);


	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("PLMN Network Name Icon ")+csNumber,0,bSubItem);


	csTemp  = GetTLVData(csData,0x80);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Icon Qualifier "),csTemp.Mid(0,2),csTemp.Mid(0,2)));
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Icon Link "),csTemp.Mid(2,csTemp.GetLength()-2),csTemp.Mid(2,csTemp.GetLength()-2)));
	}

	csTemp  = GetTLVData(csData,0x81);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Icon Qualifier "),csTemp.Mid(0,2),csTemp.Mid(0,2)));
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Icon Link "),csTemp.Mid(2,csTemp.GetLength()-2),csTemp.Mid(2,csTemp.GetLength()-2)));
	}
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainICE_DNData(CString csData,int iNumber,BOOL bSubItem /*== TRUE*/)
{
	CString csAlpha,csADN;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("In Case of Emergency – Dialling Number ")+csNumber,0,bSubItem);


	csAlpha = csData.Left(csData.GetLength() - 28);
	csADN   = csData.Mid(csAlpha.GetLength(),24);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Alpha Identifier"), TranslateAlphaIdentifier(csAlpha) ,csAlpha));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Phone Number"), _TransationADNNumber(csADN) ,csADN));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Capability/Configuration1 Record Identifier"),csData.Right(04).Left(02) ,csData.Right(04).Left(02)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension1 Record Identifier"), csData.Right(02) ,csData.Right(02)));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainICE_FFData(CString csData,int iNumber,BOOL bSubItem /*== TRUE*/)
{

	CString csNumber,csTemp;
	csNumber.Format(_T("%02d"),iNumber);


	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("In Case of Emergency – Free Format ")+csNumber,0,bSubItem);


	csTemp  = GetTLVData(csData,0x80);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("ICE Free Format Label "),csTemp,csTemp));
	}

	csTemp  = GetTLVData(csData,0x81);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("ICE Free Format Content "),csTemp,csTemp));
	}
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainNCP_IPData(CString csData,int iNumber,BOOL bSubItem /*== TRUE*/)
{

	CString csNumber,csTemp;
	csNumber.Format(_T("%02d"),iNumber);


	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("In Case of Emergency – Free Format ")+csNumber,0,bSubItem);

	csTemp  = GetTLVData(csData,0x83);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Data Destination Address Range "),csTemp,csTemp));
	}

	csTemp  = GetTLVData(csData,0x80);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Access Point Name "),csTemp,csTemp));
	}

	csTemp  = GetTLVData(csData,0x81);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Login "),csTemp,csTemp));
	}
	csTemp  = GetTLVData(csData,0x82);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Password "),csTemp,csTemp));
	}



	csTemp  = GetTLVData(csData,0x84);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Bearer Description "),csTemp,csTemp));
	}
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainEPSLOCIData(CString csData,BOOL bSubItem /*== TRUE*/)
{
	CString csDes;

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("EPS location information"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("GUTI"), csData.Mid(0,24),  csData.Mid(0,24) ) );

	pGroup1->AddSubItem(ExplainLTAI(csData.Mid(24,10))) ;

	//	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Last visited registered TAI"), csData.Mid(24,10),  csData.Mid(24,10) ) );

	switch (_CString2Int(csData.Mid(34,2)))
	{
	case 0:
		csDes = _T("UPDATED");
		break;
	case 1:
		csDes = _T("NOT UPDATED");
		break;
	case 2:
		csDes = _T("ROAMING NOT ALLOWED");
		break;
	default:
		csDes = _T("reserved.");
		break;
	}


	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("EPS update status"),csDes,csData.Mid(34,2)) );

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainEPSNSCData(CString csData,int iNumber,BOOL bSubItem /*== TRUE*/)
{

	CString csNumber,csNass,csTemp;
	csNumber.Format(_T("%02d"),iNumber);

	//	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("EPS NAS Security Context ")+csNumber,0,1);
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("EPS NAS Security Context ")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	csNass  = GetTLVData(csData,0xA0);

	csTemp  = GetTLVData(csNass,0x80);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Key set identifier KSIASME "),csTemp,csTemp));
	}

	csTemp  = GetTLVData(csNass,0x81);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("ASME key (KASME) "),csTemp,csTemp));
	}

	csTemp  = GetTLVData(csNass,0x82);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Uplink NAS count "),csTemp,csTemp));
	}

	csTemp  = GetTLVData(csNass,0x83);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Uplink NAS count "),csTemp,csTemp));
	}

	csTemp  = GetTLVData(csNass,0x84);

	if (!csTemp.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Identifiers of selected NAS integrity and encryption algorithms "),csTemp,csTemp));
	}

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainKcIData(CString csData,BOOL bSubItem /*== TRUE*/)
{
	CString csDes;

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Ciphering key Kc"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Ciphering key Kc"), csData.Mid(0,16),  csData.Mid(0,16) ) );

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Ciphering key sequence number n"), csData.Mid(16,2),  csData.Mid(16,2) ) );
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainPLMNselData(CString csData,BOOL bSubItem /*== TRUE*/)
{
	CString csNumber;

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("PLMN selector"),0,bSubItem);


	for (int i = 0 ; i < csData.GetLength();i += 6)
	{
		csNumber.Format(_T("%02d"),i/3+1);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("PLMN ")+csNumber, TransationMNCMCC(csData.Mid(i,6)), GenerateMCCMNCDescription(csData.Mid(i,6))));
	}

	return pGroup1;
}

CMFCPropertyGridProperty* NewSSTSubItem(int iService,BOOL bSupport,BOOL bEnable,BOOL bOption)
{
	CMFCPropertyGridProperty* pGroup;
	CString csTemp[42];

	csTemp[0] = _T("CHV1 disable function");
	csTemp[1] = _T("Abbreviated Dialling Numbers (ADN)");
	csTemp[2] = _T("Fixed Dialling Numbers (FDN)");
	csTemp[3] = _T("Short Message Storage (SMS)");

	csTemp[4] = _T("Advice of Charge (AoC)");
	csTemp[5] = _T("Capability Configuration Parameters (CCP)");
	csTemp[6] = _T("PLMN selector");
	csTemp[7] = _T("RFU");

	csTemp[8] = _T("MSISDN");
	csTemp[9] = _T("Extension1");
	csTemp[10] = _T("Extension2");
	csTemp[11] = _T("Short Message Service Parameters (SMSP)");

	csTemp[12] = _T("Last Number Dialled (LND)");
	csTemp[13] = _T("Cell Broadcast Message Identifier");
	csTemp[14] = _T("Group Identifier Level 1");
	csTemp[15] = _T("Group Identifier Level 2");


	csTemp[16] = _T("Service Provider Name");
	csTemp[17] = _T("Service Dialling Numbers (SDN)");
	csTemp[18] = _T("Extension3");
	csTemp[19] = _T("RFU");


	csTemp[20] = _T("VGCS Group Identifier List (EFVGCS and EFVGCSS)");
	csTemp[21] = _T("VBS Group Identifier List (EFVBS and EFVBSS)");
	csTemp[22] = _T("Enhanced Multi Level Precedence and Pre emption Service");
	csTemp[23] = _T("Automatic Answer for eMLPP");


	csTemp[24] = _T("Data download via SMS CB");
	csTemp[25] = _T("Data download via SMS PP");
	csTemp[26] = _T("Menu selection");
	csTemp[27] = _T("Call control");


	csTemp[28] = _T("Proactive SIM");
	csTemp[29] = _T("Cell Broadcast Message Identifier Ranges");
	csTemp[30] = _T("Barred Dialling Numbers (BDN)");
	csTemp[31] = _T("Extension4");

	csTemp[32] = _T("De personalization Control Keys");
	csTemp[33] = _T("Co operative Network List");
	csTemp[34] = _T("Short Message Status Reports");
	csTemp[35] = _T("Network's indication of alerting in the MS ");

	csTemp[36] = _T("Mobile Originated Short Message control by SIM");
	csTemp[37] = _T("GPRS");
	csTemp[38] = _T("Image (IMG)");
	csTemp[39] = _T("SoLSA (Support of Local Service Area)");

	csTemp[40] = _T("USSD string data object supported in Call Control");
	csTemp[41] = _T("RUN AT COMMAND command");


	bool bBSupport,bBEnable;
	if (bSupport)
		bBSupport = true;
	else
		bBSupport = false;
	if (bEnable)
		bBEnable = true;
	else
		bBEnable = false;

	pGroup = new CMFCPropertyGridProperty(csTemp[iService-1], TransationSSTStatus((bool)bBSupport, (bool)bBEnable),_T("Service n°")+Int2CStringDecimal(iService));
	if (bOption)
	{
		pGroup->AddOption(TransationSSTStatus( true, true));
		pGroup->AddOption(TransationSSTStatus( false, false));
		pGroup->AddOption(TransationSSTStatus( true, false));
		pGroup->AddOption(TransationSSTStatus( false, true));
	}

	return pGroup;

}

CMFCPropertyGridProperty* ExplainSSTData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("SIM service table"),0,bSubItem);

	int ibitLen = csData.GetLength()*2;

	ibitLen = ibitLen> 42 ? 42 : ibitLen;

	for (int i= 1; i<= ibitLen ;i++)
	{
		pGroup1->AddSubItem(NewSSTSubItem(i,Getbit(csData,2*i-1),Getbit(csData,2*i),!bSubItem));
	}


	/*pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("CHV1 disable function"),              TransationSSTStatus( _Getbit(csData,1), _Getbit(csData,2)) ,_T("Service n°1")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Abbreviated Dialling Numbers (ADN)"), TransationSSTStatus( _Getbit(csData,3), _Getbit(csData,4)),_T("Service n°2")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Fixed Dialling Numbers (FDN)"),       TransationSSTStatus( _Getbit(csData,5), _Getbit(csData,6)),_T("Service n°3")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Short Message Storage (SMS)"),        TransationSSTStatus( _Getbit(csData,7), _Getbit(csData,8)),_T("Service n°4")));



	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Advice of Charge (AoC)"),                   TransationSSTStatus( _Getbit(csData,9), _Getbit(csData,10)),_T("Service n°5")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Capability Configuration Parameters (CCP)"),TransationSSTStatus( _Getbit(csData,11), _Getbit(csData,12)),_T("Service n°6")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("PLMN selector"),                            TransationSSTStatus( _Getbit(csData,13), _Getbit(csData,14)),_T("Service n°7")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("RFU"),                                      TransationSSTStatus( _Getbit(csData,15), _Getbit(csData,16)),_T("Service n°8")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MSISDN"),     TransationSSTStatus( _Getbit(csData,17), _Getbit(csData,18)),_T("Service n°9")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension1"), TransationSSTStatus( _Getbit(csData,19), _Getbit(csData,20)),_T("Service n°10")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension2"), TransationSSTStatus( _Getbit(csData,21), _Getbit(csData,22)),_T("Service n°11")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Short Message Service Parameters (SMSP)"), TransationSSTStatus( _Getbit(csData,23), _Getbit(csData,24)),_T("Service n°12")));


	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Last Number Dialled (LND)")   ,      TransationSSTStatus( _Getbit(csData,25), _Getbit(csData,26)),_T("Service n°13")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Cell Broadcast Message Identifier"), TransationSSTStatus( _Getbit(csData,27), _Getbit(csData,28)),_T("Service n°14")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Group Identifier Level 1"),          TransationSSTStatus( _Getbit(csData,29), _Getbit(csData,30)),_T("Service n°15")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Group Identifier Level 2"),          TransationSSTStatus( _Getbit(csData,31), _Getbit(csData,32)),_T("Service n°16")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Service Provider Name"),          TransationSSTStatus( _Getbit(csData,33), _Getbit(csData,34)),_T("Service n°17")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Service Dialling Numbers (SDN)"), TransationSSTStatus( _Getbit(csData,35), _Getbit(csData,36)),_T("Service n°18")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension3"),                     TransationSSTStatus( _Getbit(csData,37), _Getbit(csData,38)),_T("Service n°19")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("RFU"),                            TransationSSTStatus( _Getbit(csData,39), _Getbit(csData,40)),_T("Service n°20")));


	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("VGCS Group Identifier List (EFVGCS and EFVGCSS)"),         TransationSSTStatus( _Getbit(csData,41), _Getbit(csData,42)),_T("Service n°21")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("VBS Group Identifier List (EFVBS and EFVBSS)"),            TransationSSTStatus( _Getbit(csData,43), _Getbit(csData,44)),_T("Service n°22")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Enhanced Multi Level Precedence and Pre emption Service"), TransationSSTStatus( _Getbit(csData,45), _Getbit(csData,46)),_T("Service n°23")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Automatic Answer for eMLPP"),                              TransationSSTStatus( _Getbit(csData,47), _Getbit(csData,48)),_T("Service n°24")));


	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Data download via SMS CB"), TransationSSTStatus( _Getbit(csData,49), _Getbit(csData,50)),_T("Service n°25")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Data download via SMS PP"), TransationSSTStatus( _Getbit(csData,51), _Getbit(csData,52)),_T("Service n°26")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Menu selection"),           TransationSSTStatus( _Getbit(csData,53), _Getbit(csData,54)),_T("Service n°27")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Call control"),             TransationSSTStatus( _Getbit(csData,55), _Getbit(csData,56)),_T("Service n°28")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Proactive SIM"),                            TransationSSTStatus( _Getbit(csData,57), _Getbit(csData,58)),_T("Service n°29")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Cell Broadcast Message Identifier Ranges"), TransationSSTStatus( _Getbit(csData,59), _Getbit(csData,60)),_T("Service n°30")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Barred Dialling Numbers (BDN)"),            TransationSSTStatus( _Getbit(csData,61), _Getbit(csData,62)),_T("Service n°31")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension4"),                               TransationSSTStatus( _Getbit(csData,63), _Getbit(csData,64)),_T("Service n°32")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("De personalization Control Keys"),             TransationSSTStatus( _Getbit(csData,65), _Getbit(csData,66)),_T("Service n°33")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Co operative Network List"),                   TransationSSTStatus( _Getbit(csData,67), _Getbit(csData,68)),_T("Service n°34")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Short Message Status Reports"),               TransationSSTStatus( _Getbit(csData,69), _Getbit(csData,70)),_T("Service n°35")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Network's indication of alerting in the MS "), TransationSSTStatus( _Getbit(csData,71), _Getbit(csData,72)),_T("Service n°36")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Mobile Originated Short Message control by SIM "), TransationSSTStatus( _Getbit(csData,73), _Getbit(csData,74)),_T("Service n°37")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("GPRS"),                                            TransationSSTStatus( _Getbit(csData,75), _Getbit(csData,76)),_T("Service n°38")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Image (IMG)"),                                     TransationSSTStatus( _Getbit(csData,77), _Getbit(csData,78)),_T("Service n°39")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("SoLSA (Support of Local Service Area)"),           TransationSSTStatus( _Getbit(csData,79), _Getbit(csData,80)),_T("Service n°40")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("USSD string data object supported in Call Control"), TransationSSTStatus( _Getbit(csData,81), _Getbit(csData,82)),_T("Service n°41")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("RUN AT COMMAND command"),                           TransationSSTStatus( _Getbit(csData,83), _Getbit(csData,84)),_T("Service n°42")));*/ 

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainKcGPRSData(CString csData,BOOL bSubItem /*== TRUE*/)
{
	CString csDes;

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Ciphering key Kc"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Ciphering key KcGPRS"), csData.Mid(0,16),  csData.Mid(0,16) ) );

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Ciphering key sequence number n for GPRS"), csData.Mid(16,2),  csData.Mid(16,2) ) );
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainLOCIGPRSData(CString csData,BOOL bSubItem /*== TRUE*/)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("GPRS location information"),0,bSubItem);

	pGroup1->AddSubItem(ExplainMID(csData.Mid(0,8)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("P-TMSI signature"),csData.Mid(8,6) ,csData.Mid(8,6)));
	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("RAI"),csData.Mid(14,12) ,csData.Mid(14,12)));

	pGroup1->AddSubItem (ExplainRAI(csData.Mid(14,12)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Routing Area update status"),TransationRAUStatus (csData.Mid(26,2)) ,csData.Mid(26,2)));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainBCCHData(CString csData,BOOL bSubItem /*== TRUE*/)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Broadcast control channels"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("BCCH information"), csData,  csData) );

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainPhaseData(CString csData,BOOL bSubItem /*== TRUE*/)
{
	CString csDes;

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Phase identification"),0,bSubItem);

	if (_CString2Int(csData) == 00 )
	{
		csDes = _T("phase 1");
	}else if (_CString2Int(csData) == 02 )
	{
		csDes = _T("phase 2");
	}
	else if (_CString2Int(csData) == 03 )
	{
		csDes = _T("phase 2 and PROFILE DOWNLOAD required");
	}


	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("SIM Phase"), csDes,  csData) );

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainCCPData(CString csData,int iNumber,BOOL bSubItem /*== TRUE*/)
{

	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Capability configuration parameters ")+csNumber,0,bSubItem);


	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Bearer capability information element "),csData.Mid(0,20),csData.Mid(0,20)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Bytes reserved   "),csData.Mid(20,4),csData.Mid(20,4)));

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainLNDData( CString csData,int iNumber,BOOL bSubItem /*== TRUE*/ )
{

	return _ExplainADNData(_T("LDN "),csData,iNumber,bSubItem);
}


 CMFCPropertyGridProperty* ExplainCOUNTData(CString csData,int iNumber, BOOL bSubItem /*= TRUE*/)
{	
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Call Count ")+csNumber,0,bSubItem);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("COUNTs-p"), csData,  csData) );

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainIMSIMData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("IMSI_M"),0,bSubItem);
	if (!csData.IsEmpty())
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("IMSI_M_CLASSp"),                      csData.Mid(0,2),  csData.Mid(0,2)));
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("IMSI_M_S2"),                          csData.Mid(2,4),  _TransationMCC_P(csData.Mid(2,4)) ));
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("IMSI_M_S1"),                          csData.Mid(6,6),  _TransationM_S1(csData.Mid(6,6)) ));
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("IMSI_M_11_12p"),                      csData.Mid(12,2), _TransationM_11_12(csData.Mid(12,2)) ));
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("IMSI_M_PROGRAMMED") ,(_variant_t) Getbit(csData.Mid(14,2),8)     ,csData.Mid(14,2)));
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("IMSI_M_ADDR_NUMp") , (_variant_t) (_CString2Int(csData.Mid(14,2))&0x7), csData.Mid(14,2)));
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MCC_Mp"),                             csData.Mid(16,4),   _TransationMCC_P(csData.Mid(16,4))));
		NotAllowEdit(pGroup1);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("IMSI"),                               IMSI_M2IMSI (csData),  csData));
	}
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainIMSITData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("IMSI_T"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("IMSI_T_CLASSp"),                      csData.Mid(0,2),  csData.Mid(0,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("IMSI_T_S2"),                          csData.Mid(2,4),  _TransationMCC_P(csData.Mid(2,4)) ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("IMSI_T_S1"),                          csData.Mid(6,6),  _TransationM_S1(csData.Mid(6,6)) ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("IMSI_T_11_12p"),                      csData.Mid(12,2), _TransationM_11_12(csData.Mid(12,2)) ));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("IMSI_T_PROGRAMMED") ,(_variant_t)  Getbit(csData.Mid(14,2),8)     ,csData.Mid(14,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("IMSI_T_ADDR_NUMp") , (_variant_t) (_CString2Int(csData.Mid(14,2))&0x7), csData.Mid(14,2)));


	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MCC_Tp"),                             csData.Mid(16,4),   _TransationMCC_P(csData.Mid(16,4))));
//	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("IMSI"),                               Imsim2Imsi (csData),  csData));


	return pGroup1;
}

CMFCPropertyGridProperty* ExplainTMSIData(CString csData,BOOL bSubItem)
{
	int iZoneLen;

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("TMSI"),0,bSubItem);

	iZoneLen =  (_CString2Int(csData.Mid(0,2))&0xF)*2;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("ASSIGNING_TMSI_ZONE"),ExchangeByte(csData.Mid(2,iZoneLen)) ,csData.Mid(2,16) ));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("TMSI_CODE"),ExchangeByte(csData.Mid(18,8)) ,csData.Mid(18,8) ));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("TMSI_EXP_TIME"),ExchangeByte(csData.Mid(26,6)) ,csData.Mid(26,6) ));


	return pGroup1;
}

CMFCPropertyGridProperty* ExplainAHData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Analog Home SID"),ExchangeByte(csData),csData);

	return pGroup1;
}

CMFCPropertyGridProperty* ExplainAOPData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Analog Operational 1 Parameters"),0,bSubItem);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Group ID") ,  (_variant_t)((_CString2Int( csData )&0x2C)>>2),  csData));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Local use mark") ,(_variant_t)Getbit(csData,2) ,csData));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Extended address") ,TransationSupportedText( Getbit(csData,1)),csData ));
	return pGroup1;
}

CMFCPropertyGridProperty* ExplainALOCData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Analog Location and Registration I ndicators"),0,bSubItem);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NXTREG") ,      ExchangeByte(csData.Mid(0,6)) ,csData.Mid(0,6) ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SID") ,         ExchangeByte(csData.Mid(6,4)) ,csData.Mid(6,4) ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("LOCAID,PUREG") ,ExchangeByte(csData.Mid(10,4)),csData.Mid(10,4)));
	return pGroup1;

}

CMFCPropertyGridProperty* ExplainSIDNIDData(CString csData,int iNumber,BOOL bSubItem)
{
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("CDMA Home SID, NID ")+csNumber,0,bSubItem);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SID") ,       ExchangeByte(csData.Mid(0,4)) ,csData.Mid(0,4) ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NID") ,       ExchangeByte(csData.Mid(4,4)) ,csData.Mid(4,8) ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Band Class") ,(_variant_t)_CString2Int(csData.Mid(8,2)),csData.Mid(8,2)));
	return pGroup1;

}

CMFCPropertyGridProperty* ExplainZNREGIData(CString csData,int iNumber,BOOL bSubItem)
{
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("CDMA Zone-Based Registration I 1 ndicators ")+csNumber,0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("REG_ZONE") ,  ExchangeByte(csData.Mid(0,4)) ,csData.Mid(0,4) ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SID") ,       ExchangeByte(csData.Mid(4,4)) ,csData.Mid(4,4) ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NID") ,       ExchangeByte(csData.Mid(8,4)) ,csData.Mid(8,4) ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Band Class") ,ExchangeByte(csData.Mid(12,4)),csData.Mid(12,2)));
	return pGroup1;

}

CMFCPropertyGridProperty* ExplainSNREGIData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("CDMA Zone-Based Registration I 1 ndicators "),0,bSubItem);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("N 'size of SID/NID list (N=1)'") , csData.Mid(0,2) ,csData.Mid(0,2) ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SID") ,       ExchangeByte(csData.Mid(2,4)) ,csData.Mid(2,4) ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NID") ,       ExchangeByte(csData.Mid(6,4)) ,csData.Mid(6,4) ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("RFU") ,ExchangeByte(csData.Mid(10,4)),csData.Mid(10,4)));
	return pGroup1;

}

CMFCPropertyGridProperty* ExplainDISTREGIIData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("CDMA Distance-Based Registration Indicators "),0,bSubItem);


	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("BASE_LAT_REG") ,   ExchangeByte(csData.Mid(0,6)) ,csData.Mid(0,6) ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("BASE_LONG_REG") ,  ExchangeByte(csData.Mid(6,6)) ,csData.Mid(6,6) ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("REG_DIST_REG") ,   ExchangeByte(csData.Mid(12,4)),csData.Mid(12,4)));
	return pGroup1;  

}

CMFCPropertyGridProperty* ExplainACCOLCData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Access Overload 1 Class ACCOLCp "),0,bSubItem);


	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Access overload class") ,csData ,csData));
	return pGroup1;  

}

CMFCPropertyGridProperty* ExplainTERMData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Call Termination Mode Preferences "),0,bSubItem);


	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MOB_TERM_FOR_NID") ,TransationSupportedText( Getbit(csData,1)) ,csData));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MOB_TERM_FOR_SID") ,TransationSupportedText( Getbit(csData,2)) ,csData));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MOB_TERM_HOME")    ,TransationSupportedText( Getbit(csData,3)) ,csData));
	return pGroup1;  

}

CMFCPropertyGridProperty* ExplainSSCIData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Suggested Slot Cycle Index "),csData,csData);

	return pGroup1;  

}

CMFCPropertyGridProperty* ExplainACPData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Analog Channel Preferences"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Analog Initial Paging Channel")                   ,  ExchangeByte(csData.Mid(0,4)) ,csData.Mid(0,4)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Analog First Dedicated Control Channel System A") ,  ExchangeByte(csData.Mid(4,4)) ,csData.Mid(4,4)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Analog First Dedicated Control Channel System B") ,  ExchangeByte(csData.Mid(8,4)) ,csData.Mid(8,4)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Number of Dedicated Control Channel to Scan")     ,  ExchangeByte(csData.Mid(12,4)),csData.Mid(12,2)));

	return pGroup1;  

}


CMFCPropertyGridProperty* ExplainPRLFileData(CString csData,BOOL bSubItem)
{

	int iOffset,iLen;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Preferred Roaming Data"),0,bSubItem);

	iLen = _CString2Int(csData.Mid(0,4))*2;

	pGroup1->AddSubItem(ExplainPRLData( csData.Mid(0,iLen)));

	iOffset = iLen;

	iLen = _CString2Int(csData.Mid(iOffset,4))*2;

	pGroup1->AddSubItem( ExplainEPRLData( csData.Mid(iOffset,iLen)));


	return pGroup1;  

}
CMFCPropertyGridProperty* ExplainPRLData(CString csData)
{
	CString csTemp;
	int iOffset ;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Preferred Roaming List"),0,1);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("PR_LIST_SIZE"), (_variant_t)_CString2Int(csData.Mid(0,4)),csData.Mid(0,4)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("PR_LIST_ID")  , csData.Mid(4,4) ,csData.Mid(4,4)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("PREF_ONLY") ,  (_variant_t) Getbit(csData.Mid(8,2),8) ,csData.Mid(8,2)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("DEF_ROAM_IND")     ,(_variant_t) Getbit(csData,33,8),Getbit_C(csData,33,8)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_ACQ_RECS")     , (_variant_t) Getbit(csData,41,9),Getbit_C(csData,41,9)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_SYS_RECS")     ,  (_variant_t) Getbit(csData,50,14),Getbit_C(csData,50,14)));

	iOffset = 64;

	CMFCPropertyGridProperty* pGroup11 = new CMFCPropertyGridProperty(_T("AcquisitionRecords"),0,1);

	BOOL bRet;
	bRet = ExplainAcquisitionRecordsData(pGroup11, Getbit(csData,41,9) ,csData,&iOffset);

	CMFCPropertyGridProperty* pGroup12 = new CMFCPropertyGridProperty(_T("SystemRecords"),0,1);
	bRet = ExplainSystemRecordsData     (pGroup12, Getbit(csData,50,14) ,csData,&iOffset);

	pGroup1->AddSubItem(pGroup11);
	pGroup1->AddSubItem(pGroup12);

	if ((iOffset%8) != 0)
	{
		iOffset  = iOffset + 8 - (iOffset%8);
	}

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("CheckSum"), Getbit_C(csData,iOffset,16),_T("CheckSum")));
	return pGroup1;  

}

BOOL ExplainAcquisitionRecordsData(CMFCPropertyGridProperty* ParentGroup,int iSum,CString csData,int* iOffbit)
{
	BOOL bRet;

	CMFCPropertyGridProperty* pGroup1;
	int iACQ_Record_Type;
	CString csNumber;



	for (int i = 0; i < iSum ; i++)
	{

		iACQ_Record_Type = Getbit(csData,*iOffbit,4);


		csNumber.Format(_T("%02d"),i+1);

		pGroup1 = new CMFCPropertyGridProperty (csNumber,0,1);


		switch ( iACQ_Record_Type)
		{
		case 1:
			bRet = ExplainCellularAnalogData(pGroup1,csData,iOffbit);
			break;
		case 2:
			bRet = ExplainCellularCDMA_StandardChannelsData(pGroup1,csData,iOffbit);
			break;
		case 3:
			bRet = ExplainCellularCDMA_CustomChannelsData(pGroup1,csData,iOffbit);
			break;
		case 4:
			bRet = ExplainCellularCDMAPreferredData(pGroup1,csData,iOffbit);
			break;
		case 5:
			bRet = ExplainPCSCDMA_UsingBlocksData(pGroup1,csData,iOffbit);
			break;
		case 6:
			bRet = ExplainPCSCDMA_UsingChannelsData(pGroup1,csData,iOffbit);
			break;
		default:
			return FALSE;
			break;
		}

		ParentGroup->AddSubItem(pGroup1);

	}







	return TRUE;

}
BOOL ExplainCellularAnalogData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{
	CString csDes;
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("ACQ_TYPE")    ,  (_variant_t) Getbit(csData,* iOffbit,4),  _T("Cellular Analog")   ));
	*iOffbit =  *iOffbit+4;

	switch(Getbit(csData,* iOffbit,2))
	{
	case  00:
		csDes = _T("System A");
		break;

	case 01:
		csDes = _T("System B");
		break;
	case 02:
		csDes = _T("Reserved");
		break;
	case 03:
		csDes = _T("System A or B");
		break;
	default:
		break;
	}

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("A_B") ,  csDes , Getbit_C(csData,* iOffbit,2)));

	*iOffbit =  *iOffbit+2;

	return TRUE;
}
BOOL ExplainCellularCDMA_StandardChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{
	CString csDes;
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("ACQ_TYPE")    ,  (_variant_t) Getbit(csData,* iOffbit,4),  _T("Cellular CDMA (Standard Channels)")   ));
	*iOffbit =  *iOffbit+4;

	switch(Getbit(csData,* iOffbit,2))
	{
	case  00:
		csDes = _T("System A");
		break;

	case 01:
		csDes = _T("System B");
		break;
	case 02:
		csDes = _T("Reserved");
		break;
	case 03:
		csDes = _T("System A or B");
		break;
	default:
		break;
	}

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("A_B") ,  csDes , Getbit_C(csData,* iOffbit,2)));

	*iOffbit =  *iOffbit+2;

	switch(Getbit(csData,* iOffbit,2))
	{
	case  00:
		csDes = _T("Reserved");
		break;

	case 01:
		csDes = _T("Primary CDMA Channel");
		break;
	case 02:
		csDes = _T("Secondary CDMA Channel");
		break;
	case 03:
		csDes = _T("Primary or Secondary CDMA Channel");
		break;
	default:
		break;
	}

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("PRI_SEC") ,  csDes , Getbit_C(csData,* iOffbit,2)));

	*iOffbit =  *iOffbit+2;

	return TRUE;
}
BOOL ExplainCellularCDMA_CustomChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{

	int iNumber;
	CString csNumber;

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("ACQ_TYPE")    ,  (_variant_t) Getbit(csData,* iOffbit,4),  _T("Cellular CDMA System Acquisition (Custom Channels) Record")   ));

	*iOffbit =  *iOffbit+4;

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_CHANS")    ,  (_variant_t) Getbit(csData,* iOffbit,5),Getbit_C(csData,*iOffbit,5)));

	iNumber =  Getbit(csData,* iOffbit,5);
	*iOffbit =  *iOffbit+5;

	for (int i = 0 ; i < iNumber ; i++)
	{
		csNumber.Format(_T("%02d"),i+1);

		ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("CHANS ")+ csNumber   ,  (_variant_t) Getbit(csData,* iOffbit,11),Getbit_C(csData,*iOffbit,11)));
		*iOffbit=  *iOffbit+11;

	}

	return TRUE;
}
BOOL ExplainCellularCDMAPreferredData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{
	CString csDes;
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("ACQ_TYPE")    ,  (_variant_t) Getbit(csData,* iOffbit,4),  _T("Cellular CDMA Preferred")   ));
	*iOffbit =  *iOffbit+4;

	switch(Getbit(csData,* iOffbit,2))
	{
	case  00:
		csDes = _T("System A");
		break;

	case 01:
		csDes = _T("System B");
		break;
	case 02:
		csDes = _T("Reserved");
		break;
	case 03:
		csDes = _T("System A or B");
		break;
	default:
		break;
	}

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("A_B") ,  csDes , Getbit_C(csData,* iOffbit,2)));

	*iOffbit =  *iOffbit+2;

	return TRUE;
}
BOOL ExplainPCSCDMA_UsingBlocksData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{
	int iNumber;
	CString csNumber;
	CString csDes;

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("ACQ_TYPE")    ,  (_variant_t) Getbit(csData,* iOffbit,4),  _T("PCS CDMA System Acquisition (Using Blocks)")   ));

	*iOffbit =  *iOffbit+4;

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_CHANS")    ,  (_variant_t) Getbit(csData,* iOffbit,3),Getbit_C(csData,*iOffbit,3)));

	iNumber =  Getbit(csData,* iOffbit,3);
	*iOffbit =  *iOffbit+3;

	for (int i = 0 ; i < iNumber ; i++)
	{
		csNumber.Format(_T("%02d"),i+1);


		switch(Getbit(csData,* iOffbit,3))
		{
		case 00:
			csDes = _T("Block A");
			break;
		case 01:
			csDes = _T("Block B");
			break; 
		case 02:
			csDes = _T("Block C");
			break;
		case 03:
			csDes = _T("Block D");
			break;
		case 04:
			csDes = _T("Block E");
			break; 
		case 05:
			csDes = _T("Block F");
			break;
		case 06:
			csDes = _T("Reserved");
			break;
		case 07:
			csDes = _T("Any Block");
			break; 
		}



		ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("CHANS ")+ csNumber ,  csDes,Getbit_C(csData,*iOffbit,3)));
		*iOffbit=  *iOffbit+3;

	}

	return TRUE;



}
BOOL ExplainPCSCDMA_UsingChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{
	int iNumber;
	CString csNumber;

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("ACQ_TYPE")    ,  (_variant_t) Getbit(csData,* iOffbit,4),  _T("PCS CDMA System Acquisition (Using Channels) Record")   ));

	*iOffbit =  *iOffbit+4;

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_CHANS")    ,  (_variant_t) Getbit(csData,* iOffbit,5),Getbit_C(csData,*iOffbit,5)));

	iNumber =  Getbit(csData,* iOffbit,5);
	*iOffbit =  *iOffbit+5;

	for (int i = 0 ; i < iNumber ; i++)
	{
		csNumber.Format(_T("%02d"),i+1);

		ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("CHANS ")+ csNumber   ,  (_variant_t) Getbit(csData,* iOffbit,11),Getbit_C(csData,*iOffbit,11)));
		*iOffbit=  *iOffbit+11;

	}

	return TRUE;
}
BOOL ExplainSystemRecordsData(CMFCPropertyGridProperty* ParentGroup,int iSum,CString csData,int* iOffbit)
{
	CString csNumber;
	int iFref_Neg;
	CMFCPropertyGridProperty* pGroup1;

	for (int i = 0; i < iSum ; i++)
	{

		csNumber.Format(_T("%02d"),i+1);

		pGroup1 = new CMFCPropertyGridProperty (csNumber,0,1);

		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SID")    ,  (_variant_t) Getbit(csData,* iOffbit,15),  Getbit_C(csData,* iOffbit,15)   ));
		* iOffbit = * iOffbit+15;
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NID_INCL")    ,  (_variant_t) Getbit(csData,* iOffbit,2),  Getbit_C(csData,* iOffbit,2)   ));
		* iOffbit = * iOffbit+2;

		if ( Getbit(csData,(*iOffbit)-2,2) == 1)
		{
			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NID")    ,  (_variant_t) Getbit(csData,* iOffbit,16),  Getbit_C(csData,* iOffbit,16)   ));
			* iOffbit = * iOffbit+16;
		}
		else
		{
			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NID")    ,  _T("N/A"),  _T("N/A")  ));
		}


		iFref_Neg =Getbit(csData,* iOffbit,1);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("PREF_NEG")    ,  (_variant_t) Getbit(csData,* iOffbit,1),  Getbit_C(csData,* iOffbit,1)   ));
		* iOffbit = * iOffbit+1;


		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("GEO")    ,  (_variant_t) Getbit(csData,* iOffbit,1),  Getbit_C(csData,* iOffbit,1)   ));
		* iOffbit = * iOffbit+1;

		if (iFref_Neg)
		{
			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("PRI")    ,  (_variant_t) Getbit(csData,* iOffbit,1),  Getbit_C(csData,* iOffbit,1)   ));
			* iOffbit = * iOffbit+1;
		}
		else
		{
			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("PRI")    ,  _T("N/A"),  _T("N/A")  ));
		}

		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("ACQ_INDEX")    ,  (_variant_t) Getbit(csData,* iOffbit,9),  Getbit_C(csData,* iOffbit,9)   ));
		* iOffbit = * iOffbit+9;

		if (iFref_Neg)
		{
			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("ROAM_IND")    ,  (_variant_t) Getbit(csData,* iOffbit,8),  Getbit_C(csData,* iOffbit,8)   ));
			* iOffbit = * iOffbit+8;
		}
		else
		{
			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("ROAM_IND")    ,  _T("N/A"),  _T("N/A")  ));
		}

		ParentGroup->AddSubItem(pGroup1);

	}



	return TRUE;
}

CMFCPropertyGridProperty* ExplainEPRLData(CString csData)
{
	CString csTemp;
	int iOffset ;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Preferred Roaming List"),0,1);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("PR_LIST_SIZE"), (_variant_t)Getbit(csData,0,16),csData.Mid(0,4)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("PR_LIST_ID")  , Getbit_C(csData,16,16) ,csData.Mid(4,4)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("CUR_SSPR_P_REV") ,  (_variant_t) Getbit(csData,32,8),csData.Mid(16,2)));


	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("PREF_ONLY") ,  (_variant_t) Getbit(csData,40,1) ,csData.Mid(8,2)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("DEF_ROAM_IND")     ,(_variant_t) Getbit(csData,41,8),Getbit_C(csData,33,8)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_ACQ_RECS")     , (_variant_t) Getbit(csData,49,9),Getbit_C(csData,41,9)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_COMMON_SUBNET_RECS") , (_variant_t) Getbit(csData,58,9),Getbit_C(csData,41,9)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_SYS_RECS")     ,  (_variant_t) Getbit(csData,67,14),Getbit_C(csData,50,14)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("RESERVED")     ,  (_variant_t) Getbit(csData,81,7),Getbit_C(csData,50,14)));




	iOffset = 88;

	CMFCPropertyGridProperty* pGroup11 = new CMFCPropertyGridProperty(_T("ExtendeAcquisitionRecords"),0,1);

	BOOL bRet;
	bRet = ExplainExtendedAcquisitionRecordsData(pGroup11, Getbit(csData,49,9) ,csData,&iOffset);

	pGroup1->AddSubItem(pGroup11);


	CMFCPropertyGridProperty* pGroup12 = new CMFCPropertyGridProperty(_T("CommonSubnetTable"),0,1);

	//bRet = ExplainCommonSubnetRecordData(pGroup12,csData,&iOffset);


	pGroup1->AddSubItem(pGroup12);

	CMFCPropertyGridProperty* pGroup13 = new CMFCPropertyGridProperty(_T("ExtendedSystemTable"),0,1);

	bRet = ExplainExtendedSystemRecordsData(pGroup13,Getbit(csData,67,14) ,csData,&iOffset);


	pGroup1->AddSubItem(pGroup13);

	return pGroup1;  

}

BOOL ExplainExtendedAcquisitionRecordsData(CMFCPropertyGridProperty* ParentGroup,int iSum,CString csData,int* iOffbit)
{
	BOOL bRet;

	CMFCPropertyGridProperty* pGroup1;
	int iACQ_Record_Type;
	CString csNumber;



	for (int i = 0; i < iSum ; i++)
	{

		iACQ_Record_Type = Getbit(csData,*iOffbit,8);

		csNumber.Format(_T("%02d"),i+1);

		pGroup1 = new CMFCPropertyGridProperty (csNumber,0,1);


		switch ( iACQ_Record_Type)
		{
		case 1:
			bRet = _ExplainCellularAnalogData(pGroup1,csData,iOffbit);
			break;
		case 2:
			bRet = _ExplainCellularCDMA_StandardChannelsData(pGroup1,csData,iOffbit);
			break;
		case 3:
			bRet = _ExplainCellularCDMA_CustomChannelsData(pGroup1,csData,iOffbit);
			break;
		case 4:
			bRet = _ExplainCellularCDMAPreferredData(pGroup1,csData,iOffbit);
			break;
		case 5:
			bRet = _ExplainPCSCDMA_UsingBlocksData(pGroup1,csData,iOffbit);
			break;
		case 6:
			bRet = _ExplainPCSCDMA_UsingChannelsData(pGroup1,csData,iOffbit);
			break;
		case 7:
			bRet = ExplainJTACSCDMA_StandardChannelsData(pGroup1,csData,iOffbit);
			break;
		case 8:
			bRet = ExplainJTACSCDMA_CustomChannelsData(pGroup1,csData,iOffbit);
			break;
		case 9:
			bRet = Explain2GHzBand_UsingChannelsData(pGroup1,csData,iOffbit);
			break;
		case 10:
			bRet = ExplainGenericAcquisitionRecordforIS2000andIS95Data(pGroup1,csData,iOffbit);
			break;
		case 11:
			bRet = ExplainGenericAcquisitionRecordforHRPDData(pGroup1,csData,iOffbit);
			break;
		default:
			return FALSE;
			break;
		}

		ParentGroup->AddSubItem(pGroup1);

	}



	return TRUE;

}




BOOL _ExplainCellularAnalogData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{

	CString csDes;
	int iLen ;
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("ACQ_TYPE")    ,  (_variant_t) Getbit(csData,* iOffbit,8),  _T("Cellular Analog")   ));
	*iOffbit =  *iOffbit+8;

	iLen = Getbit(csData,* iOffbit,8);
	*iOffbit =  *iOffbit+8;

	switch(Getbit(csData,* iOffbit,2))
	{
	case  00:
		csDes = _T("System A");
		break;

	case 01:
		csDes = _T("System B");
		break;
	case 02:
		csDes = _T("Reserved");
		break;
	case 03:
		csDes = _T("System A or B");
		break;
	default:
		break;
	}

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("A_B") ,  csDes , Getbit_C(csData,* iOffbit,2)));

	*iOffbit =  *iOffbit+2;

	*iOffbit =  *iOffbit+6;

	return TRUE;
}
BOOL _ExplainCellularCDMA_StandardChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{
	int iLen;
	CString csDes;
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("ACQ_TYPE")    ,  (_variant_t) Getbit(csData,* iOffbit,8),  _T("Cellular CDMA (Standard Channels)")   ));
	*iOffbit =  *iOffbit+8;

	iLen = Getbit(csData,* iOffbit,8);
	*iOffbit =  *iOffbit+8;


	switch(Getbit(csData,* iOffbit,2))
	{
	case  00:
		csDes = _T("System A");
		break;

	case 01:
		csDes = _T("System B");
		break;
	case 02:
		csDes = _T("Reserved");
		break;
	case 03:
		csDes = _T("System A or B");
		break;
	default:
		break;
	}

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("A_B") ,  csDes , Getbit_C(csData,* iOffbit,2)));

	*iOffbit =  *iOffbit+2;

	switch(Getbit(csData,* iOffbit,2))
	{
	case  00:
		csDes = _T("Reserved");
		break;

	case 01:
		csDes = _T("Primary CDMA Channel");
		break;
	case 02:
		csDes = _T("Secondary CDMA Channel");
		break;
	case 03:
		csDes = _T("Primary or Secondary CDMA Channel");
		break;
	default:
		break;
	}

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("PRI_SEC") ,  csDes , Getbit_C(csData,* iOffbit,2)));

	*iOffbit =  *iOffbit+2;

	*iOffbit =  *iOffbit+4;

	return TRUE;
}
BOOL _ExplainCellularCDMA_CustomChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{
	int iLen;
	int iNumber;
	CString csNumber;

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("ACQ_TYPE")    ,  (_variant_t) Getbit(csData,* iOffbit,8),  _T("Cellular CDMA System Acquisition (Custom Channels) Record")   ));

	*iOffbit =  *iOffbit+8;

	iLen = Getbit(csData,* iOffbit,8);
	*iOffbit =  *iOffbit+8;


	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_CHANS")    ,  (_variant_t) Getbit(csData,* iOffbit,5),Getbit_C(csData,*iOffbit,5)));

	iNumber =  Getbit(csData,* iOffbit,5);
	*iOffbit =  *iOffbit+5;

	for (int i = 0 ; i < iNumber ; i++)
	{
		csNumber.Format(_T("%02d"),i+1);

		ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("CHANS ")+ csNumber   ,  (_variant_t) Getbit(csData,* iOffbit,11),Getbit_C(csData,*iOffbit,11)));
		*iOffbit=  *iOffbit+11;

	}

	if ((*iOffbit%8) != 0)
		*iOffbit=  *iOffbit + (8 - (*iOffbit%8));



	return TRUE;
}
BOOL _ExplainCellularCDMAPreferredData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{
	CString csDes;
	int iLen;
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("ACQ_TYPE")    ,  (_variant_t) Getbit(csData,* iOffbit,8),  _T("Cellular CDMA Preferred")   ));
	*iOffbit =  *iOffbit+8;

	iLen = Getbit(csData,* iOffbit,8);
	*iOffbit =  *iOffbit+8;


	switch(Getbit(csData,* iOffbit,2))
	{
	case  00:
		csDes = _T("System A");
		break;

	case 01:
		csDes = _T("System B");
		break;
	case 02:
		csDes = _T("Reserved");
		break;
	case 03:
		csDes = _T("System A or B");
		break;
	default:
		break;
	}

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("A_B") ,  csDes , Getbit_C(csData,* iOffbit,2)));

	*iOffbit =  *iOffbit+2;

	*iOffbit =  *iOffbit+6;
	return TRUE;
}
BOOL _ExplainPCSCDMA_UsingBlocksData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{
	int iNumber;
	CString csNumber;
	CString csDes;
	int iLen;

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("ACQ_TYPE")    ,  (_variant_t) Getbit(csData,* iOffbit,8),  _T("PCS CDMA System Acquisition (Using Blocks)")   ));

	*iOffbit =  *iOffbit+8;

	iLen = Getbit(csData,* iOffbit,8);
	*iOffbit =  *iOffbit+8;


	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_CHANS")    ,  (_variant_t) Getbit(csData,* iOffbit,3),Getbit_C(csData,*iOffbit,3)));

	iNumber =  Getbit(csData,* iOffbit,3);
	*iOffbit =  *iOffbit+3;

	for (int i = 0 ; i < iNumber ; i++)
	{
		csNumber.Format(_T("%02d"),i+1);


		switch(Getbit(csData,* iOffbit,3))
		{
		case 00:
			csDes = _T("Block A");
			break;
		case 01:
			csDes = _T("Block B");
			break; 
		case 02:
			csDes = _T("Block C");
			break;
		case 03:
			csDes = _T("Block D");
			break;
		case 04:
			csDes = _T("Block E");
			break; 
		case 05:
			csDes = _T("Block F");
			break;
		case 06:
			csDes = _T("Reserved");
			break;
		case 07:
			csDes = _T("Any Block");
			break; 
		}

		ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("CHANS ")+ csNumber ,  csDes,Getbit_C(csData,*iOffbit,3)));
		*iOffbit=  *iOffbit+3;

	}

	if ((*iOffbit%8) != 0)
		*iOffbit=  *iOffbit + (8 - (*iOffbit%8));

	return TRUE;


}
BOOL _ExplainPCSCDMA_UsingChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{
	int iNumber;
	CString csNumber;
	int iLen;

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("ACQ_TYPE")    ,  (_variant_t) Getbit(csData,* iOffbit,8),  _T("PCS CDMA System Acquisition (Using Channels) Record")   ));


	*iOffbit =  *iOffbit+8;

	iLen = Getbit(csData,* iOffbit,8);
	*iOffbit =  *iOffbit+8;


	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_CHANS")    ,  (_variant_t) Getbit(csData,* iOffbit,5),Getbit_C(csData,*iOffbit,5)));

	iNumber =  Getbit(csData,* iOffbit,5);
	*iOffbit =  *iOffbit+5;

	for (int i = 0 ; i < iNumber ; i++)
	{
		csNumber.Format(_T("%02d"),i+1);

		ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("CHANS ")+ csNumber   ,  (_variant_t) Getbit(csData,* iOffbit,11),Getbit_C(csData,*iOffbit,11)));
		*iOffbit=  *iOffbit+11;

	}

	if ((*iOffbit%8) != 0)
		*iOffbit=  *iOffbit + (8 - (*iOffbit%8));

	return TRUE;
}


BOOL ExplainJTACSCDMA_StandardChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{

	CString csDes;
	int iLen;

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("ACQ_TYPE")    ,  (_variant_t) Getbit(csData,* iOffbit,8),  _T("JTACS CDMA System Acquisition (Standard Channels) Record")   ));


	*iOffbit =  *iOffbit+8;

	iLen = Getbit(csData,* iOffbit,8);
	*iOffbit =  *iOffbit+8;


	switch(Getbit(csData,* iOffbit,2))
	{
	case  00:
		csDes = _T("System A");
		break;

	case 01:
		csDes = _T("System B");
		break;
	case 02:
		csDes = _T("Reserved");
		break;
	case 03:
		csDes = _T("System A or B");
		break;
	default:
		break;
	}

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("A_B") ,  csDes , Getbit_C(csData,* iOffbit,2)));

	*iOffbit =  *iOffbit+2;

	switch(Getbit(csData,* iOffbit,2))
	{
	case  00:
		csDes = _T("Reserved");
		break;

	case 01:
		csDes = _T("Primary CDMA Channel");
		break;
	case 02:
		csDes = _T("Secondary CDMA Channel");
		break;
	case 03:
		csDes = _T("Primary or Secondary CDMA Channel");
		break;
	default:
		break;
	}

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("PRI_SEC") ,  csDes , Getbit_C(csData,* iOffbit,2)));

	*iOffbit =  *iOffbit+2;

	*iOffbit =  *iOffbit+4;

	return TRUE;
}
BOOL ExplainJTACSCDMA_CustomChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{
	int iNumber;
	CString csNumber;
	CString csDes;
	int iLen;
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("ACQ_TYPE")    ,  (_variant_t) Getbit(csData,* iOffbit,8),  _T("JTACS CDMA System Acquisition (Custom Channels) Record")   ));
	*iOffbit =  *iOffbit+8;

	iLen = Getbit(csData,* iOffbit,8);
	*iOffbit =  *iOffbit+8;


	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_CHANS")    ,  (_variant_t) Getbit(csData,* iOffbit,5),Getbit_C(csData,*iOffbit,5)));

	iNumber =  Getbit(csData,* iOffbit,5);
	*iOffbit =  *iOffbit+5;

	for (int i = 0 ; i < iNumber ; i++)
	{
		csNumber.Format(_T("%02d"),i+1);

		ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("CHANS ")+ csNumber   ,  (_variant_t) Getbit(csData,* iOffbit,11),Getbit_C(csData,*iOffbit,11)));
		*iOffbit=  *iOffbit+11;

	}

	if ((*iOffbit%8) != 0)
		*iOffbit=  *iOffbit + (8 - (*iOffbit%8));

	return TRUE;
}
BOOL Explain2GHzBand_UsingChannelsData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{
	int iNumber,iLen;
	CString csNumber;
	CString csDes;
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("ACQ_TYPE")    ,  (_variant_t) Getbit(csData,* iOffbit,8),  _T("2 GHz Band CDMA System Acquisition (Using Channels) Record")   ));
	*iOffbit =  *iOffbit+8;

	iLen = Getbit(csData,* iOffbit,8);
	*iOffbit =  *iOffbit+8;


	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_CHANS")    ,  (_variant_t) Getbit(csData,* iOffbit,5),Getbit_C(csData,*iOffbit,5)));

	iNumber =  Getbit(csData,* iOffbit,5);
	*iOffbit =  *iOffbit+5;

	for (int i = 0 ; i < iNumber ; i++)
	{
		csNumber.Format(_T("%02d"),i+1);

		ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("CHANS ")+ csNumber   ,  (_variant_t) Getbit(csData,* iOffbit,11),Getbit_C(csData,*iOffbit,11)));
		*iOffbit=  *iOffbit+11;

	}

	if ((*iOffbit%8) != 0)
		*iOffbit=  *iOffbit + (8 - (*iOffbit%8));

	return TRUE;



}
BOOL ExplainGenericAcquisitionRecordforIS2000andIS95Data(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{
	int iLen;
	CString csNumber;
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("ACQ_TYPE")    ,  (_variant_t) Getbit(csData,* iOffbit,8),  _T("Generic Acquisition Record for IS-2000 and IS-95")   ));

	*iOffbit =  *iOffbit+8;

	iLen = Getbit(csData,* iOffbit,8);
	*iOffbit =  *iOffbit+8;

	for (int i = 0 ; i < iLen ; i+=2)
	{
		csNumber.Format(_T("%02d"),i+1);

		ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("BAND_CLASS ")+csNumber    ,  (_variant_t) Getbit(csData,* iOffbit,5),Getbit_C(csData,*iOffbit,5)));
		*iOffbit =  *iOffbit+5;
		ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("CHANNEL_NUMBER ")+csNumber   ,  (_variant_t) Getbit(csData,* iOffbit,11),Getbit_C(csData,*iOffbit,11)));
		*iOffbit =  *iOffbit+11;

	}


	return TRUE;
}
BOOL ExplainGenericAcquisitionRecordforHRPDData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{




	int iLen;
	CString csNumber;
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("ACQ_TYPE")    ,  (_variant_t) Getbit(csData,* iOffbit,8),  _T("Generic Acquisition Record for HRPD")   ));

	*iOffbit =  *iOffbit+8;

	iLen = Getbit(csData,* iOffbit,8);
	*iOffbit =  *iOffbit+8;

	for (int i = 0 ; i < iLen ; i+=2)
	{
		csNumber.Format(_T("%02d"),i+1);

		ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("BAND_CLASS ")+csNumber    ,  (_variant_t) Getbit(csData,* iOffbit,5),Getbit_C(csData,*iOffbit,5)));
		*iOffbit =  *iOffbit+5;
		ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("CHANNEL_NUMBER ")+csNumber   ,  (_variant_t) Getbit(csData,* iOffbit,11),Getbit_C(csData,*iOffbit,11)));
		*iOffbit =  *iOffbit+11;

	}

	return TRUE;
}

BOOL ExplainCommonSubnetRecordData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{
	int iLen;

	iLen = Getbit(csData,*iOffbit,8)&0xF;
	*iOffbit += 8;
	ParentGroup->AddSubItem(  new CMFCPropertyGridProperty ( _T("SUBNET_COMMON"), Getbit_C(csData,*iOffbit,8*iLen) ,   Getbit_C(csData,*iOffbit,8*iLen)  ));

	iOffbit += 8*iLen;

	return TRUE;
}

BOOL ExplainExtendedSystemRecordsData(CMFCPropertyGridProperty* ParentGroup,int iSum,CString csData,int* iOffbit)
{
	int iLen,iType,iNidIncl,iSubIncl,iSubLen,iPref_Neg,iAssInc;
	CString csNumber,csDes;
	CMFCPropertyGridProperty* pGroup1;
	int iOribit;

	for (int i = 0; i < iSum ; i++)
	{

		csNumber.Format(_T("%02d"),i+1);

		pGroup1=new CMFCPropertyGridProperty(_T("Extended System Record ")+csNumber,0,1);

		iOribit = *iOffbit ;


		iLen = Getbit(csData,*iOffbit,5);

		*iOffbit += 5;



		iType = Getbit(csData,*iOffbit,4);


		if (iType == 0)
			csDes = _T("IS-2000 and IS-95 Systems");
		else if (iType == 1)
			csDes = _T("HRPD System");

		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SYS_RECORD_TYPE") , csDes ,Getbit_C(csData,*iOffbit,4)));

		*iOffbit += 4;

		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Preferred/negative system") ,  (_variant_t) Getbit(csData,*iOffbit,1) ,Getbit_C(csData,*iOffbit,1)));
		iPref_Neg = Getbit(csData,*iOffbit,1);
		*iOffbit += 1;


		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Geographical region indicator") ,  (_variant_t) Getbit(csData,*iOffbit,1) ,Getbit_C(csData,*iOffbit,1)));
		*iOffbit += 1;

		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Relative priority indicator") ,  (_variant_t) Getbit(csData,*iOffbit,1) ,Getbit_C(csData,*iOffbit,1)));
		*iOffbit += 1;

		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Acquisition record index") ,  (_variant_t) Getbit(csData,*iOffbit,9) ,Getbit_C(csData,*iOffbit,9)));
		*iOffbit += 9;



		if (iType == 0)	
		{
			*iOffbit += 1;

			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NID included") ,  (_variant_t) Getbit(csData,*iOffbit,2) ,Getbit_C(csData,*iOffbit,2)));

			iNidIncl = Getbit(csData,*iOffbit,2);
			*iOffbit += 2;

			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SID") ,  (_variant_t) Getbit(csData,*iOffbit,15) ,Getbit_C(csData,*iOffbit,15)));
			*iOffbit += 15;


			if (iNidIncl == 1)
			{
				pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NID") ,  (_variant_t) Getbit(csData,*iOffbit,16) ,Getbit_C(csData,*iOffbit,16)));
				*iOffbit += 16;
			}
			else if (iNidIncl == 0)
			{
				pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NID") ,  (_variant_t) 65535 ,_T("N/A") ));
			}
			else if (iNidIncl == 2)
			{
				pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NID") ,  (_variant_t) 0 ,_T("N/A") ));
			}


		}
		else if (iType == 1)	
		{

			*iOffbit += 3;

			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SUBNET_COMMON_INCLUDED") ,  (_variant_t) Getbit(csData,*iOffbit,1) ,Getbit_C(csData,*iOffbit,1)));

			iSubIncl = Getbit(csData,*iOffbit,1);

			*iOffbit += 1;

			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SUBNET_LSB_LENGTH") ,  (_variant_t) Getbit(csData,*iOffbit,7) ,Getbit_C(csData,*iOffbit,7)));
			iSubLen =  Getbit(csData,*iOffbit,7);

			*iOffbit += 7;

			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SUBNET_LSB") ,   Getbit_C(csData,*iOffbit,iSubLen) ,Getbit_C(csData,*iOffbit,iSubLen)));

			*iOffbit += (iSubLen);

			if (iSubIncl == 1)
			{
				pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SUBNET_COMMON_OFFSET") ,  (_variant_t) Getbit(csData,*iOffbit,12) ,Getbit_C(csData,*iOffbit,12)));
				*iOffbit += 12;
			}

		}


		//if ((*iOffbit%8) != 0 ) 
		//{
		//	*iOffbit += (8 -  (*iOffbit%8) );
		//}






		if (iPref_Neg)
		{
			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("ROAM_IND") ,  (_variant_t) Getbit(csData,*iOffbit,8) ,Getbit_C(csData,*iOffbit,8)));
			*iOffbit += 8;
		}
		else
		{
			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("ROAM_IND") , _T("N/A") ,_T("N/A") ));

		}

		iAssInc = Getbit(csData,*iOffbit,1);
		*iOffbit += 1;
		if (iAssInc)
		{
			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("ASSOCIATION_TAG") ,(_variant_t) Getbit(csData,*iOffbit,8) ,Getbit_C(csData,*iOffbit,8)));
			*iOffbit += 8;

			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("PN_ASSOCIATION") ,(_variant_t) Getbit(csData,*iOffbit,1) ,Getbit_C(csData,*iOffbit,1)));
			*iOffbit += 1;

			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("DATA_ASSOCIATION") ,(_variant_t) Getbit(csData,*iOffbit,1) ,Getbit_C(csData,*iOffbit,1)));
			*iOffbit += 1;

		}
		else
		{
			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("ASSOCIATION_TAG") , _T("N/A") ,_T("N/A") ));

			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("PN_ASSOCIATION")  ,_T("N/A") ,_T("N/A") ));

			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("DATA_ASSOCIATION"),_T("N/A") ,_T("N/A") ));

		}



		ParentGroup->AddSubItem(pGroup1);


		*iOffbit = iOribit+ iLen*8;


	}



	return TRUE;
}


CMFCPropertyGridProperty* ExplainUIMIDData(CString csData,BOOL bSubItem )
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("RUIMID"),0,bSubItem);

	CString csUMID;

	csUMID = csData.Mid(2, _CString2Int(csUMID.Left(02))*2);

	csUMID = ExchangeByte(csUMID);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("UMID") , csUMID,csData));

	return pGroup1;  

}

CMFCPropertyGridProperty* ExplainCSTData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("CSIM Service Table"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Local Phone Book"), (_variant_t) Getbit(csData,1) ,_T("Service n°1")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Fixed Dialling Numbers (FDN)"),(_variant_t) Getbit(csData,2),_T("Service n°2")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension 2"),(_variant_t) Getbit(csData,3),_T("Service n°3")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Service Dialling Numbers (SDN)"),(_variant_t) Getbit(csData,4),_T("Service n°4")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension3"),(_variant_t) Getbit(csData,5),_T("Service n°5")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Short Message Storage (SMS)"),(_variant_t) Getbit(csData,6),_T("Service n°6")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Short Message Parameters"),(_variant_t) Getbit(csData,7),_T("Service n°7")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("HRPD"),(_variant_t) Getbit(csData,8),_T("Service n°8")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Service Category Program for BC-SMS"),(_variant_t) Getbit(csData,9),_T("Service n°9")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("CDMA Home Service Provider Name"),(_variant_t) Getbit(csData,10),_T("Service n°10")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Data Download via SMS Broadcast"),(_variant_t) Getbit(csData,11),_T("Service n°11")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Data Download via SMS-PP"),(_variant_t) Getbit(csData,12),_T("Service n°12")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Call Control"),(_variant_t) Getbit(csData,13),_T("Service n°13")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("3GPD-SIP"),(_variant_t) Getbit(csData,14),_T("Service n°14")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("3GPD-MIP"),(_variant_t) Getbit(csData,15),_T("Service n°15")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("AKA"),(_variant_t) Getbit(csData,16),_T("Service n°16")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("IP-based Location Services (LCS)"),(_variant_t) Getbit(csData,17),_T("Service n°17")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("BCMCS"),(_variant_t) Getbit(csData,18),_T("Service n°18")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Multimedia Messaging Service (MMS)"),(_variant_t) Getbit(csData,19),_T("Service n°19")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension 8"),(_variant_t) Getbit(csData,20),_T("Service n°20")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("MMS User Connectivity Parameters"),(_variant_t) Getbit(csData,21),_T("Service n°21")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Application Authentication"),(_variant_t) Getbit(csData,22),_T("Service n°22")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Group Identifier Level 1"),(_variant_t) Getbit(csData,23),_T("Service n°23")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Group Identifier Level 2"),(_variant_t) Getbit(csData,24),_T("Service n°24")));


	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("De-Personalization Control Keys"),(_variant_t) Getbit(csData,25),_T("Service n°25")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Cooperative Network List"),(_variant_t) Getbit(csData,26),_T("Service n°26")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Outgoing Call Information (OCI)"),(_variant_t) Getbit(csData,27),_T("Service n°27")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Incoming Call Information (ICI)"),(_variant_t) Getbit(csData,28),_T("Service n°28")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension 5"),(_variant_t) Getbit(csData,29),_T("Service n°29")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Multimedia Storage"),(_variant_t) Getbit(csData,30),_T("Service n°30")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Image (EFIMG)"),(_variant_t) Getbit(csData,31),_T("Service n°31")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Enabled Services Table"),(_variant_t) Getbit(csData,32),_T("Service n°32")));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Capability Configuration Parameters (CCP)"),(_variant_t) Getbit(csData,33),_T("Service n°33")));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("SF_EUIMID-based EUIMID"),(_variant_t) Getbit(csData,34),_T("Service n°34")));

	return pGroup1;  

}

CMFCPropertyGridProperty* ExplainSPCData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Service Programming Code"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Service Programming Code"),ExchangeByte(csData) ,csData));

	return pGroup1;  

}
CMFCPropertyGridProperty* ExplainOTAPASPCData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Service Programming Code"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("OTAPA_Enable")    ,(_variant_t)Getbit(csData,1) ,csData));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("PC_Change_Enable"),(_variant_t)Getbit(csData,5) ,csData));
	return pGroup1;  

}

CMFCPropertyGridProperty* ExplainNAMLOCKData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("NAM_LOCK"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("NAM_LOCK_STATE") ,(_variant_t)Getbit(csData,1) ,csData));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("NAM_LOCK"),(_variant_t)Getbit(csData,2) ,csData));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("OTA_MODE"),(_variant_t)Getbit(csData,3) ,csData));
	return pGroup1;  

}


CMFCPropertyGridProperty* ExplainOTAData(CString csData,BOOL bSubItem)
{
	CString csNumber;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("OTASP/OTAPA Features"),0,1);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("number of OTASP/OTAPA features") ,(_variant_t)_CString2Int(csData.Mid(0,2)) ,csData.Mid(0,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("NAM Download (DATA_P_REV) ID") ,csData.Mid(2,2) ,csData.Mid(2,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("DATA_P_REV") ,csData.Mid(4,2) ,csData.Mid(4,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Key Exchange (A_KEY_P_REV) ID") ,csData.Mid(6,2) ,csData.Mid(6,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("A_KEY_P_REV") ,csData.Mid(8,2) ,csData.Mid(8,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("System Selection for Preferred Roaming(SSPR_P_REV) ID") ,csData.Mid(10,2) ,csData.Mid(10,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("SSPR_P_REV") ,csData.Mid(12,2) ,csData.Mid(12,2)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Service Programming Lock(SPL_P_REV) ID") ,csData.Mid(14,2) ,csData.Mid(14,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("SPL_P_REV") ,csData.Mid(16,2) ,csData.Mid(16,2)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Over-The-Air Parameter Admin(OTAPA_P_REV) ID"), csData.Mid(18,2) ,csData.Mid(18,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("PUZL_P_REV") ,csData.Mid(20,2) ,csData.Mid(20,2)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("3G Packet Data (3GPD) ID") ,csData.Mid(22,2) ,csData.Mid(22,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("3GPD") ,csData.Mid(24,2) ,csData.Mid(24,2)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Secure MODE(SECURE_MODE_P_REV) ID") ,csData.Mid(22,2) ,csData.Mid(22,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("SECURE_MODE_P_REV") ,csData.Mid(24,2) ,csData.Mid(24,2)));

	for (int i = 1 ; i <= Getbit(csData,0,8); i ++)
	{
		csNumber.Format(_T("%02d"),i);

		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Feature ")+csNumber ,csData.Mid(24+i*2,2) ,csData.Mid(24+i*2,2)));
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Protocol Revision for Feature ")+csNumber ,csData.Mid(26+i*2,2) ,csData.Mid(26+i*2,2)));
	}


	return pGroup1;  

}

CMFCPropertyGridProperty* ExplainSPData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Service Preferences"),0,bSubItem);
	CString csDes;

	switch(Getbit(csData,5,3))
	{
	case 00:
		csDes = _T("No preference");
		break;
	case 01:
		csDes = _T("A preferred");
		break;
	case 02:
		csDes = _T("B preferred");
		break;
	case 05:
		csDes = _T("A only");
		break;
	case 06:
		csDes = _T("B only");
		break;
	default:csDes = _T("RFU");break;
	}


	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("System A/B preference") ,csDes ,Getbit_C(csData,5,3)));

	switch(Getbit(csData,1,3))
	{
	case 00:
		csDes = _T("No preference");
		break;
	case 01:
		csDes = _T("Analog preferred");
		break;
	case 02:
		csDes = _T("CDMA preferred");
		break;
	case 05:
		csDes = _T("Analog only");
		break;
	case 06:
		csDes = _T("CDMA only");
		break;
	default:csDes = _T("RFU");break;
	}
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Analog/CDMA preference"),csDes ,Getbit_C(csData,1,3)));
	return pGroup1;  

}

CMFCPropertyGridProperty* ExplainESNMEData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("ESNME"),0,bSubItem);

	CString csESNME;

	csESNME = csData.Mid(2, _CString2Int(csESNME.Left(02))*2);

	csESNME = ExchangeByte(csESNME);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("ESNME") , csESNME,csData));

	return pGroup1;  

}

CMFCPropertyGridProperty* Explain_LIData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Language Indication"),0,bSubItem);

	int iLen;

	CString csDes;
	CString csTemp;


	iLen = csData.GetLength();


	for (int i = 0 ; i < iLen; i+=2)
	{
		csTemp.Format(_T("%02d"),i/2 +1);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("language code")+csTemp ,TransationLanguageIndicator_TSB58( _CString2Int (csData.Mid(i,2))),csData.Mid(i,2)));	

	}
	return pGroup1;  

}

CMFCPropertyGridProperty* Explain_SSFCData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Supplementary Services 1 Feature Code Table"),0,bSubItem);

	CString csDes;
	int iOffset; 
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Number of Feature Codes"),csData.Mid( 0,2), csData.Mid( 0,2)));

	iOffset = 2;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Activate Call Delivery"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));

	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("De-activate Call Delivery"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Register new Call Forwarding – Busy (CFB) forward-to number"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Register Call Forwarding – Busy (CFB) to voicemail"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("De-register Call Forwarding – Busy (CFB)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Activate Call Forwarding – Busy (CFB)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("De-activate Call Forwarding – Busy (CFB)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4 )));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Register new Call Forwarding – Default (CFD) forward-to number"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Register Call Forwarding – Default (CFD) to voicemail"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("De-register Call Forwarding – Default (CFD)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Activate Call Forwarding – Default (CFD)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("De- activate Call Forwarding – Default (CFD)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Register new Call Forwarding – No Answer (CFNA) forward-to number"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Register Call Forwarding – No Answer (CFNA) to voice mail"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("De-register Call Forwarding – Unconditional (CFU)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Activate Call Forwarding – Unconditional (CFU)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("De-activate Call Forwarding – Unconditional (CFU)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Activate Call Waiting (CW)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("De-activate Call Waiting (CW)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Temporarily De-activate Call Waiting (Cancel CallWaiting - CCW)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Temporarily Activate Calling Number Identification Restriction (CNIR) (per-call blocking)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Temporarily De-activate Calling Number Identification Restriction (CNIR) (per-call allowed)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Invoke Conference Calling (CC)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Invoke Drop Last Conference Calling (CC) Party"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Activate Do Not Disturb (DND"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("De-activate Do Not Disturb (DND)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Activate Message Waiting Notification (MWN) AlertPip Tone "),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("De-activate Message Waiting Notification (MWN) Alert Pip Tone"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Activate Message Waiting Notification (MWN) PipTone "),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("De-activate Message Waiting Notification (MWN) Pip Tone"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Temporarily De-activate Message WaitingNotification (MWN) Pip Tone (Cancel MWN -CMWN) "),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Invoke Priority Access and Channel Assignment (PACA)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Invoke Voice Message Retrieval (VMR)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Activate Calling Name Presentation (CNAP)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("De-activate Calling Name Presentation (CNAP)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Activate Calling Name Restriction (CNAR)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("De-activate Calling Name Restriction (CNAR)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Activate Automatic Callback (AC)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("De-activate Automatic Callback (AC)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Activate Automatic Recall (AR)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("De-activate Automatic Recall (AR)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Register new network registered User Selectable Call Forwarding (USCF) directory number"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Activate Rejection of Undesired Annoying Calls (RUAC)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("De-activate Rejection of Undesired Annoying Calls (RUAC)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Invoke Advice of Charge (AOC)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Invoke Call Trace (COT)"),csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
	iOffset += 4;

	for (int i = 0 ;i < (_CString2Int (csData.Mid( 0,2)) - 51) ; i ++  )
	{
		csDes.Format(_T("%02d"),i+1);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("FCN ")+csDes,csData.Mid( iOffset,4), csData.Mid( iOffset,4)));
		iOffset += 4;
	}

	return pGroup1;  

}

CMFCPropertyGridProperty* Explain_SPNData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("CDMA Home Service Provider Name"),0,bSubItem);

	CString csDes;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Display Condition") ,(_variant_t) Getbit(csData,1),_T("Display of registered system")));	

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Character Encoding") , Getbit_C(csData,11,5),csData.Mid(2,2)));	

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Language Indicator") ,TransationLanguageIndicator_TSB58( _CString2Int (csData.Mid(4,2))),csData.Mid(4,2)));	

	csDes = WipeEmpty(csData.Mid(6,32));
	if(Getbit(csData,11,5) == 04)
	{
		csDes = TransationUcs2(csDes,0x80);
	}

	if(Getbit(csData,11,5) == 02)
	{
		//csDes = Convert7bit(csDes);
		csDes = Translate7bit(csDes);
	}

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Service Provider Name") , csDes ,csData.Mid(6,64)));	

	return pGroup1;  

}

CMFCPropertyGridProperty* Explain_USGINDData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("UIM_ID/SF_EUIMID Usage Indicator"),0,bSubItem);

	CString csDes;

	if (Getbit(csData,1))
		csDes = _T("UIM_ID is used for CAVE Authentication and MS Identification");
	else
		csDes = _T("ESN_ME is used for CAVE Authentication and MS Identification");

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("UIM ID Usage Indicator") ,csDes ,csData));	

	if (Getbit(csData,2))
		csDes = _T("SF_EUIMID is used for MS Identification");
	else
		csDes = _T("MEID is used for MS Identification");

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SF_EUIMID Usage Indicator") , csDes ,csData));	


	return pGroup1;  

}

CMFCPropertyGridProperty* Explain_ADData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Administrative Data"),0, bSubItem);


	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MS operation mode") ,csData.Mid(0,2) ,csData));	

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Additional information") , csData.Mid(2,4) ,csData));	


	return pGroup1; 

}

CMFCPropertyGridProperty* Explain_MDNData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Mobile Directory Number"),0, bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Number of digits") ,(_variant_t) Getbit(csData,4,4) ,csData));	

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MDN") ,    csData.Mid(2,16).Left(Getbit(csData,4,4)) ,csData.Mid(2,16)));	

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NUMBER_TYPE and NUMBER_PLAN") , csData.Mid(18,2) ,csData.Mid(18,2)));	

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("PI and SI") , csData.Mid(20,2) ,csData.Mid(20,2)));	

	return pGroup1; 

}

CMFCPropertyGridProperty* Explain_MAXPRLData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Maximum PRL)"),0, bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MAX_PR_LIST_SIZE for EFPRL") , (_variant_t) Getbit(csData,0,16) ,csData.Mid(0,4)));	



	if (csData.GetLength() >4)
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MAX_PR_LIST_SIZE for EFEPRL") ,(_variant_t) Getbit(csData,16,16) ,csData.Mid(4,4)));	

	}






	return pGroup1; 



}

CMFCPropertyGridProperty* Explain_SPCSData(CString csData,BOOL bSubItem)
{

	CString csDes;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("SPC Status"),0,bSubItem);

	if (Getbit(csData,1))
		csDes = _T("SPC is set to any value other than the default value");
	else
		csDes = _T("SPC is set to default value");

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SPC Status") , csDes ,csData));	


	return pGroup1; 



}

CMFCPropertyGridProperty* Explain_ECCData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Emergency Call Codes"),0,bSubItem);
	int iLen = csData.GetLength();
	CString csNumber;

	for (int i =0 ; i <(iLen/3) ; i++ )
	{
		csNumber.Format(_T("%02d"),i+1);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Emergency Call Code ")+csNumber , ExchangeByte(csData.Mid(i*3,3)) , csData.Mid(i*3,3)));	
	}

	return pGroup1; 
}

CMFCPropertyGridProperty* Explain_ME3GPDOPCData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("ME 3GPD 1 Operation Capability"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SimpleIP") ,                      (_variant_t) Getbit(csData,1),csData ));	
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MobileIP") ,                      (_variant_t) Getbit(csData,2) ,csData ));	
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MobileIP with SimpleIP fallback"),(_variant_t) Getbit(csData,3) ,csData ));	

	return pGroup1; 
}

CMFCPropertyGridProperty* Explain_3GPDOPMData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("3GPD Operation Mode"),0,bSubItem);

	switch(Getbit(csData,6,2))
	{
	case 00: csDes = _T("SimpleIP only");break;
	case 01: csDes = _T("MobileIP with SimpleIP Fallback");break;
	case 02: csDes = _T("MobileIP only");break;
	case 03: csDes = _T("RESERVED");break;
	default: break;
	}

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Operation Mode") ,csDes,csData ));	

	return pGroup1; 
}

CMFCPropertyGridProperty* Explain_SIPCAPData(CString csData,BOOL bSubItem)
{
	CString csDes;

	CMFCPropertyGridProperty* pGroup1;

	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("SimpleIP Capability Parameters"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MAX_NUM_NAI")    ,(_variant_t) Getbit(csData,0 ,4),Getbit_C(csData,0 ,4) ));	
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MAX_NAI_LENGTH") ,(_variant_t) Getbit(csData,4 ,8),Getbit_C(csData,4 ,8) ));	
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MAX_SS_LENGTH")  ,(_variant_t) Getbit(csData,12,5),Getbit_C(csData,12 ,5) ));	

	if(Getbit(csData,17,1) == 1)
		csDes += _T("CHAP mode");

	if (Getbit(csData,18,1) == 1)
		csDes += _T("PAP mode");

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("AUTH_ALGORITHM") ,csDes,Getbit_C(csData , 17 ,8) ));	

	return pGroup1; 
}

CMFCPropertyGridProperty* Explain_MIPCAPData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("MobileIP Capability Parameters"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MAX_NUM_NAI")          ,(_variant_t) Getbit(csData,0 ,4),Getbit_C(csData,0 ,4) ));	
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MAX_NAI_LENGTH")       ,(_variant_t) Getbit(csData,4 ,8),Getbit_C(csData,4 ,8) ));	
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MAX_MN-AAA_SS_LENGTH") ,(_variant_t) Getbit(csData,12,5),Getbit_C(csData,12 ,5) ));	


	if (Getbit(csData,17,1))
		csDes = _T("(MN-AAA) supported");
	else
		csDes = _T("(MN-AAA) not supported");

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MN-AAA_AUTH_ALGORITHM"),csDes ,Getbit_C(csData , 17 ,8) ));	

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MAX_MN-HA_SS_LENGTH")  ,(_variant_t) Getbit(csData,25,5),Getbit_C(csData,25 ,5) ));	

	if (Getbit(csData,30,1))
		csDes = _T("(MN-HA) supported");
	else
		csDes = _T("(MN-HA) not supported");

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MN-HA_AUTH_ALGORITHM") ,csDes,Getbit_C(csData , 30 ,8) ));	

	return pGroup1; 
}

CMFCPropertyGridProperty* Explain_SIPUPPData(CString csData,BOOL bSubItem)
{
	CString csDes;
	int iNumber,iLen,iOffbit;
	CMFCPropertyGridProperty* pGroup1;

	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("SimpleIP User Profile Parameters"),csData,&bRet,bSubItem);
	if (!bRet)
		return pGroup1;

	iNumber = 1;
	iOffbit = 8;

	for (iNumber = 1; iNumber <= Getbit(csData,iOffbit,4) ; iNumber ++ )
	{

		iLen = Getbit(csData,iOffbit+ 8,8)*2 +4;
		pGroup1 ->AddSubItem (Explain_NAIUPPData(Getbit_C(csData,iOffbit,iLen*4) ,iNumber));

		iOffbit += iLen*4;
	}


	switch( Getbit(csData,iOffbit,4) )
	{
	case 00:csDes = _T("None");break;
	case 01:csDes = _T("PPP CHAP");break;
	case 02:csDes = _T("PPP PAP");break;
	case 03:csDes = _T("PPP CHAP to PAP fallback");break;
	default:csDes = _T("RESERVED");break;
	}


	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("AUTH_ALGORITHM") ,csDes,Getbit_C(csData,iOffbit,4) ));	


	return pGroup1; 
}

CMFCPropertyGridProperty* Explain_NAIUPPData(CString csData,int iNumber)
{

	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("NAI ")+csNumber,0,1);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_NAI")        ,(_variant_t) Getbit(csData,0,4), Getbit_C(csData,0,4)   ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NAI_ENTRY_INDEX"),(_variant_t) Getbit(csData,4,4), Getbit_C(csData,4,4)   ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NAI_LENGTH")     ,(_variant_t) Getbit(csData,8,8), Getbit_C(csData,8,8)   ));
	iNumber =  Getbit(csData,8,8);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NAI"), TranslateAscii(Getbit_C(csData,16,iNumber*8)), Getbit_C(csData,16,iNumber*8) ));



	return pGroup1; 
}

CMFCPropertyGridProperty* Explain_MIPUPPData(CString csData,BOOL bSubItem)
{
	CString csDes,csNum;
	int iNumber,iLen,iOffbit,iSum;
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup11;

	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("MobileIP User Profile Parameters"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;





	iNumber = 1;
	iOffbit = 8;

	if (Getbit(csData,iOffbit,1) == 1)
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MAX_NUM_RETRY") ,      (_variant_t)Getbit(csData,iOffbit+1 ,2),Getbit_C(csData,iOffbit+1 ,2) ));	
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("FIRST_RETRY_TIMEOUT") ,(_variant_t)Getbit(csData,iOffbit+2 ,3),Getbit_C(csData,iOffbit+2 ,3) ));	
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("REREG_THRESHOLD") ,    (_variant_t)Getbit(csData,iOffbit+8 ,6),Getbit_C(csData,iOffbit+8 ,6) ));	
		iOffbit += 12;

	}
	else
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MAX_NUM_RETRY")       ,_T("N/A") ,_T("N/A"))  );	
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("FIRST_RETRY_TIMEOUT") ,_T("N/A"),_T("N/A") ));	
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("REREG_THRESHOLD")     ,_T("N/A"),_T("N/A") ));	
		iOffbit += 1;
	}

	iSum = Getbit(csData,iOffbit,4);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_NAI")     ,(_variant_t)iSum,Getbit_C(csData,iOffbit ,4) ));	
	iOffbit += 4;


	for (iNumber = 1; iNumber <= iSum ; iNumber ++ )
	{

		csNum.Format(_T("%02d"),Getbit(csData,iOffbit,4));
		iOffbit += 4;

		pGroup11 = new CMFCPropertyGridProperty(_T("NAI ")+csNum,0,1);

		iLen = Getbit(csData,iOffbit,8);
		pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("NAI_LENGTH") ,(_variant_t)iLen,Getbit_C(csData,iOffbit ,8) ));	
		iOffbit += 8;

		pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("NAI") ,TranslateAscii(Getbit_C(csData,iOffbit ,8*iLen)),Getbit_C(csData,iOffbit ,8*iLen) ));	
		iOffbit += 8*iLen;

		pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("T_BIT") ,(_variant_t)Getbit(csData,iOffbit,1),Getbit_C(csData,iOffbit ,1) ));	
		iOffbit +=1 ;

		pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("HOME_ADDRESS") ,Getbit_C(csData,iOffbit,32),Getbit_C(csData,iOffbit ,32) ));	
		iOffbit +=32 ;

		pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("PRIMARY_HOME_AGENT") ,Getbit_C(csData,iOffbit,32),Getbit_C(csData,iOffbit ,32) ));	
		iOffbit +=32 ;

		pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("SECONDARY_HOME_AGENT") ,Getbit_C(csData,iOffbit,32),Getbit_C(csData,iOffbit ,32) ));	
		iOffbit +=32 ;


		switch( Getbit(csData,iOffbit,4) )
		{
		case 00:csDes = _T("None");break;
		case 01:csDes = _T("MD5");break;
		default:csDes = _T("RESERVED");break;
		}

		pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("MN-AAA_AUTH_ALGORITHM") ,csDes,Getbit_C(csData,iOffbit ,4) ));	
		iOffbit +=4 ;

		if (Getbit(csData,iOffbit,1) == 1)
		{
			pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("MN-AAA_SPI") ,Getbit_C(csData,iOffbit+1 ,32),Getbit_C(csData,iOffbit+1 ,32) ));	
			iOffbit +=33 ;
		} 
		else
		{
			pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("MN-AAA_SPI") ,_T("N/A"),_T("N/A") ));	
			iOffbit +=1 ;
		}

		switch( Getbit(csData,iOffbit,4) )
		{
		case 00:csDes = _T("None");break;
		case 01:csDes = _T("MD5");break;
		default:csDes = _T("RESERVED");break;
		}

		pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("MN-HA_AUTH_ALGORITHM") ,csDes,Getbit_C(csData,iOffbit ,4) ));	
		iOffbit +=4 ;

		if (Getbit(csData,iOffbit,1) == 1)
		{
			pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("MN-HA_SPI_INDICATOR") ,Getbit_C(csData,iOffbit+1 ,32),Getbit_C(csData,iOffbit+1 ,32) ));	
			iOffbit +=33 ;
		} 
		else
		{
			pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("MN-HA_SPI") ,_T("N/A"),_T("N/A") ));	
			iOffbit +=1 ;
		}

		pGroup1->AddSubItem(pGroup11);
	}




	return pGroup1; 
}

CMFCPropertyGridProperty* Explain_SIPSPData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1;

	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("SimpleIP Status Parameters"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("ACT_NAI_ENTRY_INDEX") ,(_variant_t)Getbit(csData,0 ,4),Getbit_C(csData,0 ,4) ));	




	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_MIPSPData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;

	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("MimpleIP Status Parameters"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("ACT_NAI_ENTRY_INDEX") ,(_variant_t)Getbit(csData,0 ,4),Getbit_C(csData,0 ,4) ));	

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_ADD_ACT_NAI") ,(_variant_t)Getbit(csData,4 ,4),Getbit_C(csData,4 ,4) ));	

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("ADD_ACT_NAI_ENTRY_INDEX") ,(_variant_t)Getbit(csData,8 ,4),Getbit_C(csData,8 ,4) ));	


	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_SIPPAPSSData(CString csData,BOOL bSubItem)
{
	int iNumber,iLen,iOffbit,iSum;
	CMFCPropertyGridProperty* pGroup1;

	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("SimpleIP PAP SS Parameters"),csData.Mid(2,csData.GetLength()-2),&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	iSum = Getbit(csData,8 ,4);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_NAI") ,(_variant_t)Getbit(csData,8 ,4),Getbit_C(csData,8 ,4) ));

	iOffbit = 12;
	for (iNumber  = 1 ; iNumber <= iSum ; iNumber ++)
	{
		iLen = Getbit(csData ,iOffbit+4,5);
		pGroup1->AddSubItem( Explain_NAISSData( Getbit_C(csData, iOffbit, iLen*8+9 )  ,iNumber));
		iOffbit +=  (iLen*8+9) ;
	}




	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_NAISSData(CString csData,int iNumber)
{
	int iLen;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("NAI ")+csNumber,0,1);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NAI_ENTRY_INDEX") ,(_variant_t) Getbit(csData,0,4), Getbit_C(csData,0,4)   ));
	iLen =  Getbit(csData,4,5);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SS_LENGTH"),(_variant_t) iLen, Getbit_C(csData,4,5)   ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SS")     , TranslateAscii( Getbit_C(csData,9,iLen*8)), Getbit_C(csData,9,iLen*8)));

	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_PUZLData(CString csData,BOOL bSubItem)
{
	int iNumber,iOffbit,iSum, iLen;
	CMFCPropertyGridProperty* pGroup1;

	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Preferred User Zone List"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	iSum = Getbit(csData,0,8);

	iOffbit = 8;

	for (iNumber = 1 ; iNumber <= iSum ; iNumber++)
	{

		iOffbit += 7;
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("LAST_SEGMENT") ,(_variant_t) Getbit(csData,iOffbit,1), Getbit_C(csData,iOffbit,1)));
		iOffbit += 1;		
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SEGMENT_INDEX") ,(_variant_t) Getbit(csData,iOffbit,12), Getbit_C(csData,iOffbit,12)));
		iOffbit += 12;		
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SEGMENT_OFFSET") ,(_variant_t) Getbit(csData,iOffbit,12), Getbit_C(csData,iOffbit,12)));
		iOffbit += 12;		
		iLen = Getbit(csData,iOffbit,8);
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SEGMENT_SIZE") ,(_variant_t) iLen, Getbit_C(csData,iOffbit,8)));
		iOffbit += 8;	
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SEGMENT_DATA") ,Getbit_C(csData,iOffbit,iLen*8), Getbit_C(csData,iOffbit,iLen*8)));
		iOffbit += 8*iLen;	
	}

	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_MAXPUZLData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Preferred User Zone List"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MAX_UZ_LIST_SIZE") ,(_variant_t) Getbit(csData,0,24) , Getbit_C(csData,0,24)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MAX_UZ")           ,(_variant_t) Getbit(csData,24,16), Getbit_C(csData,24,16)));

	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_MECRPData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("ME-specific Configuration Request Parameters"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SCM")    , Getbit_C(csData,0,8), Getbit_C(csData,0,8)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MAX_UZ") , Getbit_C(csData,8,8), Getbit_C(csData,8,8)));


	if(Getbit(csData,1))
		csDes = _T("Local Control for Analog");
	if(Getbit(csData,2))
		csDes = _T("Local Control for CDMA");


	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Local Control") , csDes, Getbit_C(csData,16,8)));		
	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_HRPDCAPData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("HRPD Access Authentication Capability Parameters"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MAX_NAI_LENGTH")    , (_variant_t)Getbit(csData,0,8), Getbit_C(csData,0,8)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MAX_UZ") ,(_variant_t) Getbit(csData,8,5), Getbit_C(csData,8,5)));


	if(Getbit(csData,0,1) == 1)
		csDes = _T("CHAP mode");
	if(Getbit(csData,2))
		csDes = _T("N/A");


	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Local Control") , csDes, Getbit_C(csData,16,1)));		
	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_HRPDUPPData(CString csData,BOOL bSubItem)
{
	CString csDes;
	int iLen;
	CMFCPropertyGridProperty* pGroup1;

	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("HRPD Access Authentication User Profile Parameters"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;


	iLen = Getbit(csData, 8,8);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NAI_LENGTH") ,(_variant_t) iLen,Getbit_C(csData,8,8) ));	

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NAI") ,TranslateAscii(Getbit_C(csData,16 ,8*iLen)) ,Getbit_C(csData,16 ,8*iLen) ));	


	switch( Getbit(csData,8*iLen+16,4) )
	{
	case 00:csDes = _T("None");break;
	case 01:csDes = _T("PPP CHAP");break;
	default:csDes = _T("RESERVED");break;
	}


	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("AUTH_ALGORITHM") ,csDes,Getbit_C(csData,8*iLen+16,4) ));	


	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_CSSPRData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1;

	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("CUR_SSPR_P_REV"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("CUR_SSPR_P_REV") ,csData,csData ));	
	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_ATData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1;

	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Access Terminal Class"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Access Terminal Class") ,(_variant_t)Getbit(csData,6,2),csData ));	
	return pGroup1; 
}
CMFCPropertyGridProperty* ExplainEPRLFileData(CString csData,BOOL bSubItem)
{

	int iOffset,iLen;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Extended Preferred Roaming List"),0,bSubItem);

	iLen = _CString2Int(csData.Mid(0,4))*2;

	pGroup1->AddSubItem(ExplainPRLData( csData.Mid(0,iLen)));

	iOffset = iLen;

	iLen = _CString2Int(csData.Mid(iOffset,4))*2;

	pGroup1->AddSubItem( ExplainEPRLData( csData.Mid(iOffset,iLen)));


	return pGroup1;  

}
CMFCPropertyGridProperty* Explain_BCSMScfgData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	CString csDes;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Broadcast Short Message Configuration"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	switch(Getbit(csData,6,2))
	{
	case 00:csDes = _T("Disallow");break;
	case 01:csDes = _T("Allow Table Only");break;
	case 02:csDes = _T("Allow All");break;
	case 03:csDes = _T("Reserved");break;
	}

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("(Operator Broadcast Configuration") ,(_variant_t)Getbit(csData,6,2),csData ));	
	return pGroup1; 

}
CMFCPropertyGridProperty* Explain_BCSMSprefData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	CString csDes;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Broadcast Short Message Preference"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	switch(Getbit(csData,6,2))
	{
	case 00:csDes = _T("Deactivate");break;
	case 01:csDes = _T("Activate Table Only");break;
	case 02:csDes = _T("Activate All");break;
	case 03:csDes = _T("Reserved");break;
	}

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("(User Broadcast Configuration") ,(_variant_t)Getbit(csData,6,2),csData ));	
	return pGroup1; 

}
CMFCPropertyGridProperty* Explain_BCSMStableData(CString csData,int iNumber,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1;
	CString csNumber,csDes;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Broadcast Short Message Table ")+csNumber,csData.Mid(2,csData.GetLength()-2),&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	if (Getbit(csData,1))
		csDes = _T("Used space");
	else
		csDes = _T("Free space");

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Status")          ,csDes, Getbit_C(csData,7,1)   ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Service Category"), ExchangeByte(Getbit_C(csData,8,16)) , Getbit_C(csData,8,16)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Language")        ,TransationLanguageIndicator_TSB58( Getbit(csData,24,8)), Getbit_C(csData,24,8)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Max Messages")    , (_variant_t) Getbit(csData,32,8) , Getbit_C(csData,32,8)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Alert Option")    , (_variant_t) Getbit(csData,44,4) , Getbit_C(csData,44,4)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Label Encoding")  , (_variant_t) Getbit(csData,48,8) , Getbit_C(csData,48,8)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Label")  , csData.Mid(14,csData.GetLength() - 14)     , csData.Mid(14,csData.GetLength() - 14)));


	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_BCSMSPData(CString csData,int iNumber,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1;
	CString csNumber,csDes;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Broadcast Short Message Parameter ")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	if (Getbit(csData,1))
		csDes = _T("selected");
	else
		csDes = _T("Not selected");

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Select")  ,csDes, Getbit_C(csData,7,1)));

	switch(Getbit(csData,14,2))
	{
	case 00: csDes = _T("Normal");break;
	case 01: csDes = _T("Interactive");break;
	case 02: csDes = _T("Urgent");break;
	case 03: csDes = _T("Emergency");break;
	}
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Priority"),csDes , Getbit_C(csData,14,2)));
	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_BAKPARAData(CString csData,int iNumber,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Currently used BAK Parameters ")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	int iLen,iRecord,iOffbit;
	iLen = csData.GetLength();
	iOffbit = 0;
	iRecord = Getbit(csData,iOffbit,8);
	iOffbit += 8 ;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("BCMCS_Flow_ID")  ,Getbit_C(csData,iOffbit,iRecord*8), Getbit_C(csData,iOffbit,iRecord*8)));
	iOffbit += 8*iRecord ;
	iRecord = Getbit(csData,iOffbit,8);
	iOffbit += 8 ;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("BAK_ID") ,Getbit_C(csData,iOffbit,iRecord*8), Getbit_C(csData,iOffbit,iRecord*8)));
	iOffbit += 8*iRecord ;
	iRecord = Getbit(csData,iOffbit,8);
	iOffbit += 8 ;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("BAK_Expire") ,Getbit_C(csData,iOffbit,iRecord*8), Getbit_C(csData,iOffbit,iRecord*8)));
	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_UpBAKPARAData(CString csData,int iNumber,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Updated BAK Parameters ")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	int iLen,iRecord,iOffbit;
	iLen = csData.GetLength();
	iOffbit = 0;
	iRecord = Getbit(csData,iOffbit,8);
	iOffbit += 8 ;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("BCMCS_Flow_ID")  ,Getbit_C(csData,iOffbit,iRecord*8), Getbit_C(csData,iOffbit,iRecord*8)));
	iOffbit += 8*iRecord ;
	iRecord = Getbit(csData,iOffbit,8);
	iOffbit += 8 ;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("BAK_ID") ,Getbit_C(csData,iOffbit,iRecord*8), Getbit_C(csData,iOffbit,iRecord*8)));
	iOffbit += 8*iRecord ;
	iRecord = Getbit(csData,iOffbit,8);
	iOffbit += 8 ;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("BAK_Expire") ,Getbit_C(csData,iOffbit,iRecord*8), Getbit_C(csData,iOffbit,iRecord*8)));
	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_MMSNData(CString csData,int iNumber,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup11;
	CMFCPropertyGridProperty* pGroup12;
	CString csNumber,csDes;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("MMS Notification ")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;


	pGroup11 = new CMFCPropertyGridProperty (_T("MMS Status"),0, 1);	
	if (Getbit(csData,1))
		csDes = _T("Used space");
	else
		csDes = _T("Free space");
	pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("Status") ,csDes, Getbit_C(csData,7,1)));

	if (Getbit(csData,2))
		csDes = _T("Notification read");
	else
		csDes = _T("Notification not read");
	pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("Notification") ,csDes, Getbit_C(csData,7,2)));

	if (Getbit(csData,1))
	{
		switch (Getbit(csData,4,2))
		{
		case 00:csDes = _T("MM not retrieved");break;
		case 01:csDes = _T("MM retrieved");break;	
		case 02:csDes = _T("MM rejected");break;
		case 03:csDes = _T("MM forwarded");break;		
		}
		pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("MM") ,csDes, Getbit_C(csData,4,2)));
	}

	pGroup1->AddSubItem(pGroup11);

	pGroup12 = new CMFCPropertyGridProperty (_T("MMS Implementation") ,0, 1);

	if (Getbit(csData,23,1))
		csDes = _T("supported");
	else
		csDes = _T("not supported");
	pGroup12->AddSubItem(new CMFCPropertyGridProperty(_T("WAP implementation"),csDes, Getbit_C(csData,23,1) ) );

	if (Getbit(csData,22,1))
		csDes = _T("supported");
	else
		csDes = _T("not supported");

	pGroup12->AddSubItem(new CMFCPropertyGridProperty(_T("M-IMAP implementation"),csDes, Getbit_C(csData,22,1) ) );


	if (Getbit(csData,21,1))
		csDes = _T("supported");
	else
		csDes = _T("not supported");
	pGroup12->AddSubItem(new CMFCPropertyGridProperty(_T("SIP implementation"),csDes, Getbit_C(csData,21,1) ) );

	pGroup1->AddSubItem(pGroup12);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MMS Notification") ,csData.Mid(6, csData.GetLength() -8), csData.Mid(6, csData.GetLength() -8)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Extension file record number") ,csData.Left(02), csData.Left(02)));

	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_MMSICPData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;

	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("MMS Issuer Connectivity Parameters"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	int iNumber = 1;



	while (!GetTLVData(csData,0xAB,iNumber).IsEmpty())
	{
		pGroup1->AddSubItem(Explain_MMSICP(GetTLVData(csData,0xAB,iNumber),iNumber));	
		iNumber++;
	}



	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_MMSICP(CString csData,int iNumber)
{
	CString csNumber;
	CString csValue;
	CMFCPropertyGridProperty* pGroup1;

	bool bRet = false;
	csNumber.Format(_T("%02d"),iNumber);
	pGroup1 = ExplainFirstNote(_T("MMS Issuer Connectivity Parameters ")+csNumber,csData,&bRet,TRUE);
	if (!bRet)
		return pGroup1;
	csValue = GetTLVData(csData,0x80);
	if (!csValue.IsEmpty())
	{
		pGroup1->AddSubItem(Explain_MMSImplementation( csValue ));	
	}
	csValue = GetTLVData(csData,0x81);
	if (!csValue.IsEmpty())
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MMS Relay/Server") ,TranslateAscii( csValue ),csValue ));	


	for (int i = 1 ; !GetTLVData(csData,0x82,i).IsEmpty();i++ )
	{
		pGroup1->AddSubItem(Explain_InterfacetoCoreNetworkandBearerInformation(GetTLVData(csData,0x82,i),i));	
	}

	csValue = GetTLVData(csData,0x83);
	if (!csValue.IsEmpty())
		pGroup1->AddSubItem(Explain_Gateway(csValue));	

	csValue = GetTLVData(csData,0x84);
	if (!csValue.IsEmpty())
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MMS Authentication Mechanism") ,_TransationAuthenticationMechanism( _CString2Int(csValue) ),csValue ));	

	csValue = GetTLVData(csData,0x85);
	if (!csValue.IsEmpty())
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MMS Authentication ID") , csValue,csValue ));	
	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_MMSImplementation(CString csData,BOOL bSubItem)
{

	CString csDes;
	CMFCPropertyGridProperty* pGroup1;

	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("MMS Issuer Connectivity Parameters "),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;


	csDes = _T("WAP implementation of MMS as defined in TS 23.140");
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("WAP implementation") ,(_variant_t) Getbit(csData,1),csDes));

	csDes = _T("Reserved for 3GPP2: M-IMAP implementation of MMS as defined in X.S0016-000-A v1.0 [45]");
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("M-IMAP implementation") ,(_variant_t) Getbit(csData,2),csDes));

	csDes = _T("Reserved for 3GPP2: SIP implementation of MMS as defined in X.S0016-000-A v1.0 [45]");
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SIP implementation") ,(_variant_t) Getbit(csData,3),csDes));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_InterfacetoCoreNetworkandBearerInformation(CString csData,int iNumber,BOOL bSubItem)
{

	CString csDes,csValue,csNumber;
	CMFCPropertyGridProperty* pGroup1;

	bool bRet = false;

	csNumber.Format(_T("%02d"),iNumber);
	pGroup1 = ExplainFirstNote(_T("Interface to Core Network and Bearer Information ")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	
	

	if (!_GetTVData(csData,0x10,csValue))
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Bearer") , _T("N/A"),csValue));
	else
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Bearer") , csValue,csValue));

	
	if (!_GetTVData(csData,0x8,csValue))
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Address") , _T("N/A"),csValue));
	else
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Address") , csValue,csValue));


	
	if (!_GetTVData(csData,0x9,csValue))
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Type of Address") , _T("N/A"),csValue));
	else

		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Type of Address") ,csValue,csValue));

	_GetTVData(csData,0x25,csValue);

	if (!_GetTVData(csData,0x9,csValue))
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Speed") , _T("N/A"),csValue));
	else
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Speed") ,TranslateAscii(csValue),csValue));


	if (_GetTVData(csData,0xA,csValue))
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Call type") , _T("N/A"),csValue));
	else
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Call type") ,csValue,csValue));


	if (_GetTVData(csData,0xC,csValue))
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Authentication type") , _T("N/A"),csValue));
	else
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Authentication type") ,csValue,csValue));

	if (_GetTVData(csData,0xD,csValue))
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Authentication id") , _T("N/A"),csValue));
	else
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Authentication id") ,TranslateAscii(csValue),csValue));

	if (_GetTVData(csData,0xE,csValue))
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Authentication password") , _T("N/A"),csValue));
	else
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Authentication password") ,TranslateAscii(csValue),csValue));
	return pGroup1;
}
CMFCPropertyGridProperty* Explain_Gateway(CString csData)
{

	CString csDes,csValue;
	CMFCPropertyGridProperty* pGroup1;

	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Gateway "),csData,&bRet);
	if (!bRet)
		return pGroup1;

	 

	if (!_GetTVData(csData,0x20,csValue))
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Address") , _T("N/A"),csValue));
	else
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Address") , TranslateAscii(csValue),csValue));


	if (!_GetTVData(csData,0x21,csValue))
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Type of Address") , _T("N/A"),csValue));
	else

		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Type of Address") ,csValue,csValue));

	

	if (!_GetTVData(csData,0x23,csValue))
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Port") , _T("N/A"),csValue));
	else
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Port") ,TranslateAscii(csValue),csValue));

	

	if (!_GetTVData(csData,0x24,csValue))
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Service") , _T("N/A"),csValue));
	else
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Service") ,csValue,csValue));

	

	if (!_GetTVData(csData,0x19,csValue))
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Authentication type") , _T("N/A"),csValue));
	else
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Authentication type") ,csValue,csValue));

	
	if (!_GetTVData(csData,0x1A,csValue))
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Authentication id") , _T("N/A"),csValue));
	else
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Authentication id") ,TranslateAscii(csValue),csValue));


	if (!_GetTVData(csData,0x1B,csValue))
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Authentication password") , _T("N/A"),csValue));
	else
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Authentication password") ,TranslateAscii(csValue),csValue));
	return pGroup1;
}
CMFCPropertyGridProperty* Explain_MMSUPData(CString csData,BOOL bSubItem)
{
	CString csValue;
	CMFCPropertyGridProperty* pGroup1;

	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("MMS User Preference"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	csValue = GetTLVData(csData,0x80);
	if (!csValue.IsEmpty())
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MMS Implementation") ,csValue,csValue ));	

	csValue = GetTLVData(csData,0x81);
	if (!csValue.IsEmpty())
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MMS User preference profile name") ,csValue,csValue ));	

	csValue = GetTLVData(csData,0x82);
	if (!csValue.IsEmpty())
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MMS User Preference information") ,csValue,csValue ));	

	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_MMSUCPData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;

	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("MMS User Connectivity Parameters"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	int iNumber = 1;
	while (!GetTLVData(csData,0xAB,iNumber).IsEmpty())
	{
		pGroup1->AddSubItem(Explain_MMSICP(GetTLVData(csData,0xAB,iNumber),iNumber));	
		iNumber++;
	}
	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_AuthCapabilityData(CString csData,int iNumber,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Authentication Capability ")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	CString csDes;

	if (Getbit(csData,0,8) == 0)
		csDes = _T("MMS");
	else
		csDes = _T("Reserved");

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Application ID")  ,csDes, Getbit_C(csData,0,8)));

	switch (Getbit(csData,8,8))
	{
	case 0x1: csDes = _T("CRAM-MD5 (RFC 2195)");break;
	case 0x2: csDes = _T("HTTP DIGEST (MD5) (RFC 2617)");break;
	case 0x4: csDes = _T("HTTP DIGEST (MD5-session) (RFC 2617)");break;
	case 0x8: csDes = _T("HTTP DIGEST (AKA v1-MD5) (RFC 3310)");break;
	case 0x10: csDes = _T("HTTP DIGEST (AKA v1-MD5-session) (RFC 3310)");break;
	case 0x20: csDes = _T("DIGEST-MD5 (SASL DIGEST) (RFC 2831)");break;
	case 0x40: csDes = _T("SASL OTP (RFC 2444)");break;	
	case 0x80: csDes = _T("SASL GSSAPI (RFC 2222)");break;
	default:   csDes = _T("Wrong Data");break; 
	}
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Authentication Capability") ,csDes, Getbit_C(csData,8,8)));


	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_3GCIKData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("3G Cipher and Integrity Keys"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Cipher key CK")   ,csData.Mid(0,32),csData.Mid(0,32)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Integrity key IK"),csData.Mid(32,32),csData.Mid(32,32)));

	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_DCKData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("De-Personalization Control Keys"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Network Type 1")  ,csData.Mid(0,8) ,csData.Mid(0,8)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Network Type 2")  ,csData.Mid(8,8) ,csData.Mid(8,8)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Service Provider"),csData.Mid(16,8),csData.Mid(16,8)));		
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Corporate")       ,csData.Mid(24,8),csData.Mid(24,8)));		
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("HRPD Network")    ,csData.Mid(32,8),csData.Mid(32,8)));		
	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_GID1Data(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Group Identifier Level 1"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("CSIM group identifier(s)")  ,csData ,csData));

	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_GID2Data(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Group Identifier Level 2"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("CSIM group identifier(s)")  ,csData ,csData));

	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_CDMACNLData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("CDMA Co-operative Network List)"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	CString csNumber;
	int iLen = csData.GetLength();
	for (int i = 0 ; i < iLen; i+=14)
	{

		pGroup1->AddSubItem (Explain_CDMACNL ( csData.Mid(i,14)  , (i/14)+1 ));
	}



	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_CDMACNL(CString csData,int iNumber,BOOL bSubItem)
{

	CString csNumber;
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Element ")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("MCCMNC")  ,csData.Mid(0,6) ,csData.Mid(0,6)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("International Roaming based MIN")  ,csData.Mid(6,4) ,csData.Mid(6,4)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Service Provider")  ,csData.Mid(10,2) ,csData.Mid(10,2)));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Corporate")  ,csData.Mid(12,2) ,csData.Mid(12,2)));	

	return pGroup1; 
}
CMFCPropertyGridProperty* Explain_HOMETAGData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Home System Tag)"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;


	if(Getbit(csData,0,1))
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("CALL_PRMPT")  ,(_variant_t)Getbit(csData,1,5), Getbit_C(csData,1,5)));
	}
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("TAG_ENCODING")  ,(_variant_t)Getbit(csData,6,5), Getbit_C(csData,6,5)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("TAG_LEN")       ,(_variant_t)Getbit(csData,11,5), Getbit_C(csData,11,5)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("TAG")       ,   Getbit_C (csData,16,Getbit(csData,11,5)*8),  Getbit_C (csData,16,Getbit(csData,11,5)*8)));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_GROUPTAGData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Group Tag List)"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	int iOffbit;

	iOffbit = 0;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("GROUP_TAG_LIST_SIZE"),(_variant_t)Getbit(csData,iOffbit,16), Getbit_C(csData,iOffbit,16)));
	iOffbit += 16;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("GROUP_TAG_LIST_ID")  ,Getbit_C(csData,iOffbit,16), Getbit_C(csData,iOffbit,16)));
	iOffbit += 16;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("TAG_P_REV")          ,(_variant_t)Getbit(csData,iOffbit,8), Getbit_C(csData,iOffbit,8)));
	iOffbit += 8;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("DEF_TAG_ENCODING")   ,(_variant_t)Getbit(csData,iOffbit,8), Getbit_C(csData,iOffbit,8)));
	iOffbit += 8;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_GROUP_TAG_RECS") ,(_variant_t)Getbit(csData,iOffbit,8), Getbit_C(csData,iOffbit,8)));
	iOffbit += 8;

	for (int i = 1 ; i <= Getbit(csData,48,8) ; i ++)
	{
		pGroup1->AddSubItem( Explain_TABLE_Data(csData,i,&iOffbit ));
	}

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("GROUP_TAG_CRC"),Getbit_C (csData,iOffbit,16),  Getbit_C (csData,iOffbit,16)));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_TABLE_Data(CString csData,int iNumber,int *iOffbit)
{
	CString csNumber;
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	csNumber .Format(_T("%02d"),iNumber);
	pGroup1 = ExplainFirstNote(_T("Group Tag List Parameter ")+csNumber,csData,&bRet);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("CUR_TAG_P_REV" ),(_variant_t)Getbit(csData, *iOffbit,8), Getbit_C(csData, *iOffbit,8)));
	*iOffbit += 15;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("LAST_SEGMENT")  ,(_variant_t)Getbit(csData, *iOffbit,1), Getbit_C(csData, *iOffbit,1)));
	*iOffbit += 1;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SEGMENT_OFFSET"),(_variant_t)Getbit(csData, *iOffbit,16), Getbit_C(csData, *iOffbit,16)));
	*iOffbit += 16;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SEGMENT_SIZE")  ,(_variant_t)Getbit(csData, *iOffbit,8), Getbit_C(csData, *iOffbit,8)));
	*iOffbit += 8;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SEGMENT_DATA")  ,Getbit_C(csData, *iOffbit,8*Getbit(csData,*iOffbit - 8,8)), Getbit_C(csData, *iOffbit,8*Getbit(csData,*iOffbit - 8,8))));
	*iOffbit += 8*Getbit(csData,*iOffbit - 8 ,8);
	return pGroup1;
}
CMFCPropertyGridProperty* Explain_SPECIFICTAGData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Group Tag List)"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	int iOffbit;

	iOffbit = 0;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SPEC_TAG_LIST_SIZE"),(_variant_t)Getbit(csData,iOffbit,16), Getbit_C(csData,iOffbit,16)));
	iOffbit += 16;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("SPEC_TAG_LIST_ID")  ,Getbit_C(csData,iOffbit,16), Getbit_C(csData,iOffbit,16)));
	iOffbit += 16;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("TAG_P_REV")          ,(_variant_t)Getbit(csData,iOffbit,8), Getbit_C(csData,iOffbit,8)));
	iOffbit += 8;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("DEF_TAG_ENCODING")   ,(_variant_t)Getbit(csData,iOffbit,8), Getbit_C(csData,iOffbit,8)));
	iOffbit += 8;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_SPEC_TAG_RECS") ,(_variant_t)Getbit(csData,iOffbit,14), Getbit_C(csData,iOffbit,14)));
	iOffbit += 16;

	for (int i = 1 ; i <= Getbit(csData,48,8) ; i ++)
	{
		pGroup1->AddSubItem( Explain_TABLE_Data(csData,i,&iOffbit ));
	}

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("GROUP_TAG_CRC"),Getbit_C (csData,iOffbit,16),  Getbit_C (csData,iOffbit,16)));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_CallPromptData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Call Prompt List)"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	int iOffbit;

	iOffbit = 0;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("CALL_PRMPT_LIST_SIZE"),(_variant_t)Getbit(csData,iOffbit,16), Getbit_C(csData,iOffbit,16)));
	iOffbit += 16;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("CALL_PRMPT_LIST_ID")  ,Getbit_C(csData,iOffbit,16), Getbit_C(csData,iOffbit,16)));
	iOffbit += 16;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("TAG_P_REV")          ,(_variant_t)Getbit(csData,iOffbit,8), Getbit_C(csData,iOffbit,8)));
	iOffbit += 8;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("DEF_TAG_ENCODING")   ,(_variant_t)Getbit(csData,iOffbit,8), Getbit_C(csData,iOffbit,8)));
	iOffbit += 8;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_SPEC_TAG_RECS") ,(_variant_t)Getbit(csData,iOffbit,14), Getbit_C(csData,iOffbit,14)));
	iOffbit += 16;

	for (int i = 1 ; i <= Getbit(csData,48,8) ; i ++)
	{
		pGroup1->AddSubItem( Explain_TABLE_Data(csData,i,&iOffbit ));
	}

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("GROUP_TAG_CRC"),Getbit_C (csData,iOffbit,16),  Getbit_C (csData,iOffbit,16)));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_SFEUIMIDData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Short Form EUIMID)"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("EUIMID)"), ExchangeByte(csData),csData));
	return pGroup1;
}
CMFCPropertyGridProperty* Explain_LCSVERData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("LCS Protocol Version"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	for (int i=0 ; i< csData.GetLength(); i++)
		pGroup1->AddSubItem(Explain_PVERData(csData.Mid(i,8)));
	return pGroup1;
}
CMFCPropertyGridProperty* Explain_PVERData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Protocol Version Parameter"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("S-SAFE Protocol version"), csData.Mid(0,2),csData.Mid(0,2)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("TLS Session-A Protocol version"), csData.Mid(2,4),csData.Mid(2,4)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("TLS Session-B Protocol version"), csData.Mid(6,2),csData.Mid(6,2)));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_LCSCPData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("(LCS Connectivity Parameter"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	CString csTemp;

	csTemp = GetTLVData(csData,0x80);
	if (!csTemp.IsEmpty())
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("H-PS address (IPv4)"), csTemp,csData));

	csTemp = GetTLVData(csData,0x81);
	if (!csTemp.IsEmpty())
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("H-PS address (IPv6)"), csTemp,csData));

	csTemp = GetTLVData(csData,0x82);
	if (!csTemp.IsEmpty())
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("H-PS address (URL) Tag"),csTemp,csData));



	return pGroup1;
}
CMFCPropertyGridProperty* Explain_AppLabelsData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup11;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("LCS Connectivity Parameter"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Character Encoding"),(_variant_t)Getbit(csData,3,5),Getbit_C(csData,3,5)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Language Indicator"),TransationLanguageIndicator_TSB58 (Getbit(csData,8,8)),Getbit_C(csData,8,8)));

	pGroup11 = new CMFCPropertyGridProperty(_T("Application Labels Present"),0,1);

	if (Getbit(csData,31,1))
		pGroup11->AddSubItem( new CMFCPropertyGridProperty(_T("MMS label"),_T("present") ,Getbit_C(csData,31,1)));
	if (Getbit(csData,30,1))
		pGroup11->AddSubItem( new CMFCPropertyGridProperty(_T("Browser label"),_T("present") ,Getbit_C(csData,30,1)));
	if (Getbit(csData,28,1))
		pGroup11->AddSubItem( new CMFCPropertyGridProperty(_T("Java label"),_T("present") ,Getbit_C(csData,28,1)));
	pGroup1->AddSubItem(pGroup11);




	for (int i= 8; i < csData.GetLength() ; i += 64)
	{
		csDes.Format(_T("%02d"),i/32 +1 );
		pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Application Label")+csDes ,csData.Mid(i,64),  TranslateAscii( WipeEmpty (csData.Mid(i,64))) ));
	}


	return pGroup1;
}
CMFCPropertyGridProperty* Explain_ModelData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Device Model Information"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Character Encoding"),(_variant_t)Getbit(csData,3,5),Getbit_C(csData,3,5)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Language Indicator"),TransationLanguageIndicator_TSB58 (Getbit(csData,8,8)),Getbit_C(csData,8,8)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Model Information"),csData.Mid(4,64),csData.Mid(4,64)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Manufacturer Name"),csData.Mid(68,64),csData.Mid(68,64)));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Software Version Information"),csData.Mid(132,120),csData.Mid(132,120)));	

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_RCData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Root Certificates"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;


	for (int i = 1 ;!GetTLVData(csData,0x80,i).IsEmpty();i++ )
		pGroup1->AddSubItem(Explain_CertificatesData(GetTLVData(csData,0x80,i),i));



	return pGroup1;
}
CMFCPropertyGridProperty* Explain_CertificatesData(CString csData,int iNumber,BOOL bSubItem)
{
	CString csNumber,csDes;
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;

	csNumber.Format(_T("%02d"),iNumber);
	pGroup1 = ExplainFirstNote(_T("Root Certificates ")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	switch (Getbit(csData,0,8))
	{
	case 0:csDes=  _T("DER Encoded Binary X.509");break;
	case 1:csDes=  _T("Base64 Encoded X.509");break;
	case 2:csDes=  _T("PKCS #7");break;
	case 3:csDes=  _T("PKCS #12");break;
	default:break;
	}
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Certificate Type"),csDes,Getbit_C(csData,0,8)));	
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Certificate Information"),csData.Mid(02,csData.GetLength()-6),csData.Mid(02,csData.GetLength()-6)));	
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Applications"),_TransationApplication(csData.Left(04)),csData.Left(04)));	
	return pGroup1;
}
CMFCPropertyGridProperty* Explain_SMSCAPData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup11;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("SMS Capabilities"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	if (Getbit(csData,0,8) == 0)
		csDes = _T("Disable");
	else
		csDes.Format(_T("%02d"),Getbit(csData,0,8));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("SMS Retry Period"),csDes+_T("(Seconds)"),Getbit_C(csData,0,8)));

	csDes.Format(_T("%02d"),Getbit(csData,8,8));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("SMS Retry Interval"),csDes+_T("(Seconds)"),Getbit_C(csData,8,8)));

	pGroup11 = new CMFCPropertyGridProperty(_T("SMS Flags"),0,1);


	csDes.Empty();
	if (Getbit(csData.Mid(4,2),1))
		pGroup11->AddSubItem(  new CMFCPropertyGridProperty(_T("Send On Access (Allow MO SMS to be sent over Access Channel)"),(_variant_t) Getbit(csData.Mid(4,2),1),csData.Mid(4,2)));
	if (Getbit(csData.Mid(4,2),2))
		pGroup11->AddSubItem(  new CMFCPropertyGridProperty(_T("Send On Traffic (Allow MO SMS to be sent over Traffic Channel)"),(_variant_t) Getbit(csData.Mid(4,2),2),csData.Mid(4,2)));
	if (Getbit(csData.Mid(4,2),3))
		pGroup11->AddSubItem(  new CMFCPropertyGridProperty(_T("Send as Standard EMS (Network supports standard EMS per [8])"),(_variant_t) Getbit(csData.Mid(4,2),3),csData.Mid(4,2)));
	pGroup1->AddSubItem(pGroup11);


	switch(Getbit(csData,24,8))
	{
	case 00: csDes = _T("Device Default");break;
	case 01: csDes = _T("Service Option 6");break;
	case 02: csDes = _T("Service Option 14");break;
	default: csDes = _T("Reserved for future use");break;
	}

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("SMS Preferred Service Option"),csDes,csData.Left(02)));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_MIPFlagsData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("MobileIP Flags"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	if (Getbit(csData,1))
		pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("Mobile IP 2002bis MN HA Authentication"),(_variant_t) Getbit(csData,1),csData));
	if (Getbit(csData,2))
		pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("Mobile IP Pre Rev 6 handoff optimization"),(_variant_t)Getbit(csData,2),csData));
	if (Getbit(csData,3))
		pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("Mobile IP PPP Re-sync during hand-down from 1xEV-DO Rev 0 to 1x"),(_variant_t) Getbit(csData,3),csData));
	if (Getbit(csData,4))
		pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("Mobile IP Re-registration only if data has been transferred since last registration in order to extend Mobile IP address lifetime"),(_variant_t) Getbit(csData,4),csData));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_SIPUPPExtData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("SimpleIP User Profile Parameters Extension"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	int iNumber, iOffbit;


	iOffbit = 0;
	iNumber = Getbit( csData,iOffbit,4);
	iOffbit += 4;
	for (int i = 0 ; i < iNumber ; i ++)
	{

		pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("INDEX"),(_variant_t)Getbit(csData,iOffbit,4),Getbit_C(csData,iOffbit,4)));
		iOffbit += 4;
		pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("APPLICATIONS"),_TransationApplication (Getbit_C(csData,iOffbit,32)),Getbit_C(csData,iOffbit,32)));
		iOffbit += 32;

		switch(Getbit(csData,iOffbit,4))
		{
		case 00:csDes = _T("Highest priority category");break;
		case 01:csDes = _T("Second highest priority category (lower than 0; higher than 2 and others)");break;
		case 02:csDes = _T("Third highest priority category (lower than 0 or 1; higher than 3 and others)");break;
		case 255: csDes = _T("Lowest priority");break;
		default:
			csDes.Format(_T("%d"),Getbit(csData,iOffbit,4)+1);
			csDes = csDes+ _T("st highest priority category");
			break;
		}

		pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("PRIORITY"),csDes,Getbit_C(csData,iOffbit,4)));
		iOffbit += 8;


		switch(Getbit(csData,iOffbit,4))
		{
		case 00:csDes = _T("Low Speed: Low speed service options only");break;
		case 01:csDes = _T("Medium Speed: F-SCH with service option 33 only");break;
		case 02:csDes = _T("High Speed: F-SCH and R-SCH with service option 33");break;
		default:csDes = _T("Reserved for future use");break;
		}
		pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("DATA_RATE_MODE"),csDes,Getbit_C(csData,iOffbit,4)));
		iOffbit += 4;

		switch(Getbit(csData,iOffbit,4))
		{
		case 00:csDes = _T("Hybrid 1x/1xEV-DO");break;
		case 01:csDes = _T("1x only");break;
		case 02:csDes = _T("1xEV-DO only");break;
		default:csDes = _T("Reserved for future use");break;
		}
		pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("DATA_BEARER"),csDes,Getbit_C(csData,iOffbit,4)));
		iOffbit += 4;
	}


	return pGroup1;
}
CMFCPropertyGridProperty* Explain_MIPUPPExtData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("MobileIP User Profile Parameters Extension"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	int iNumber, iOffbit;


	iOffbit = 0;
	iNumber = Getbit( csData,iOffbit,4);
	iOffbit += 4;
	for (int i = 0 ; i < iNumber ; i ++)
	{

		pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("INDEX"),(_variant_t)Getbit(csData,iOffbit,4),Getbit_C(csData,iOffbit,4)));
		iOffbit += 4;
		pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("APPLICATIONS"),_TransationApplication (Getbit_C(csData,iOffbit,32)),Getbit_C(csData,iOffbit,32)));
		iOffbit += 32;

		switch(Getbit(csData,iOffbit,4))
		{
		case 00:csDes = _T("Highest priority category");break;
		case 01:csDes = _T("Second highest priority category (lower than 0; higher than 2 and others)");break;
		case 02:csDes = _T("Third highest priority category (lower than 0 or 1; higher than 3 and others)");break;
		case 255: csDes = _T("Lowest priority");break;
		default:
			csDes.Format(_T("%d"),Getbit(csData,iOffbit,4)+1);
			csDes = csDes+ _T("st highest priority category");
			break;
		}

		pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("PRIORITY"),csDes,Getbit_C(csData,iOffbit,4)));
		iOffbit += 8;


		switch(Getbit(csData,iOffbit,4))
		{
		case 00:csDes = _T("Low Speed: Low speed service options only");break;
		case 01:csDes = _T("Medium Speed: F-SCH with service option 33 only");break;
		case 02:csDes = _T("High Speed: F-SCH and R-SCH with service option 33");break;
		default:csDes = _T("Reserved for future use");break;
		}
		pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("DATA_RATE_MODE"),csDes,Getbit_C(csData,iOffbit,4)));
		iOffbit += 4;

		switch(Getbit(csData,iOffbit,4))
		{
		case 00:csDes = _T("Hybrid 1x/1xEV-DO");break;
		case 01:csDes = _T("1x only");break;
		case 02:csDes = _T("1xEV-DO only");break;
		default:csDes = _T("Reserved for future use");break;
		}
		pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("DATA_BEARER"),csDes,Getbit_C(csData,iOffbit,4)));
		iOffbit += 4;
	}


	return pGroup1;
}
CMFCPropertyGridProperty* Explain_IPV6CAPData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty*  pGroup11;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("IPv6 Capabilities"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	int iOffbit;


	iOffbit = 0;
	csDes .Format( _T("%d"),Getbit(csData,iOffbit,16)*100);
	csDes = csDes + _T("ms");
	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("Initial neighbor solicitation delay time"),csDes,Getbit_C(csData,iOffbit,16)));
	iOffbit += 16;
	csDes .Format( _T("%d"),Getbit(csData,iOffbit,16)*100);
	csDes = csDes + _T("ms");
	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("Solicitation interval"),csDes,Getbit_C(csData,iOffbit,16)));
	iOffbit += 16;
	csDes .Format( _T("%d"),Getbit(csData,iOffbit,16)*100);
	csDes = csDes + _T("ms");
	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("Re-solicitation interval"),csDes,Getbit_C(csData,iOffbit,16)));
	iOffbit += 16;

	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("Maximum solicitation attempts"),csDes,Getbit_C(csData,iOffbit,16)));
	iOffbit += 16;

	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("Maximum re-solicitation attempts"),csDes,Getbit_C(csData,iOffbit,16)));
	iOffbit += 16;

	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("Pre-RA expiry re-solicitation time"),csDes,Getbit_C(csData,iOffbit,16)));
	iOffbit += 16;

	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("IID Information"),csDes,Getbit_C(csData,iOffbit,16)));
	iOffbit += 64;

	pGroup11 = new CMFCPropertyGridProperty(_T("IPv6 Flags"),0,1);

	pGroup11->AddSubItem(  new CMFCPropertyGridProperty(_T("Use IPv6"),                      (_variant_t) Getbit(csData.Right(02),1),csData.Right(02)));
	pGroup11->AddSubItem(  new CMFCPropertyGridProperty(_T("Failover from IPv6 to IPv4"),    (_variant_t) Getbit(csData.Right(02),2),csData.Right(02)));
	pGroup11->AddSubItem(  new CMFCPropertyGridProperty(_T("PDSN as proxy IPv6 DNS server"), (_variant_t) Getbit(csData.Right(02),3),csData.Right(02)));
	pGroup1->AddSubItem(pGroup11);
	return pGroup1;
}
CMFCPropertyGridProperty* Explain_TCPConfigData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("TCP Configurations"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("TCP Graceful close of dormant connections"),(_variant_t)Getbit(csData,1),csData.Left(02)));

	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("TCP Keep-Alive Idle Timer"),(_variant_t)Getbit(csData,8,8),csData.Right(02)));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_DGCData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Data Generic Configurations"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("Data dormant timer"),(_variant_t)Getbit(csData,0,8),Getbit_C(csData,0,8)));



	switch(Getbit(csData,8,8))
	{
	case 0:  csDes = _T("Packet Zone ID");break;
	case 1:  csDes = _T("Packet Zone ID plus SID");break;
	case 2:  csDes = _T("Packet Zone ID plus SID and NID");break;
	default: csDes = _T("Reserved for future use");break;
	}
	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("EPZID Type Information"),csDes,Getbit_C(csData,0,8)));

	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("Hysteresis Activation Time"),(_variant_t)Getbit(csData,16,8),Getbit_C(csData,16,8)));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_WAPBrowserCPCData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("WAP Browser Connectivity Parameters"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	int iNumber = 1;

	while (!GetTLVData(csData,0xAC,iNumber).IsEmpty())
	{
		pGroup1->AddSubItem( Explain_WAPBCPData(GetTLVData(csData,0xAC,iNumber),iNumber) );
		iNumber ++;
	}

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_WAPBCPData(CString csData,int iNumber,BOOL bSubItem)
{

	CString csDes,csNumber;
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	csNumber.Format(_T("%02d"),iNumber);
	pGroup1 = ExplainFirstNote(_T("WAP Browser Connectivity Parameters ")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;


	pGroup1->AddSubItem( Explain_Gateway(GetTLVData(csData,0x83)));
	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("HomeURL"),TranslateAscii(GetTLVData(csData,0x80)),GetTLVData(csData,0x80)));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_WAPBrowserBMCData(CString csData,BOOL bSubItem)
{
	CString csDes;
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("WAP Browser Bookmarks"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	int iNumber = 1;

	while (!GetTLVData(csData,0xAD,iNumber).IsEmpty())
	{
		pGroup1->AddSubItem( Explain_WAPBookmarkData(GetTLVData(csData,0xAD,iNumber),iNumber) );
		iNumber ++;
	}

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_WAPBookmarkData(CString csData,int iNumber,BOOL bSubItem)
{

	CString csDes,csNumber;
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	csNumber.Format(_T("%02d"),iNumber);
	pGroup1 = ExplainFirstNote(_T("WAP Browser Connectivity Parameters ")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("URL"),TranslateAscii(GetTLVData(csData,0x80)),GetTLVData(csData,0x80)));
	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("Bookmark Name"), TranslateAscii( GetTLVData(csData,0x81)),GetTLVData(csData,0x83)));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_MMSConfigData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("MMS Configuration"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;


	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("Max Message Size Value"),(_variant_t)Getbit(csData,0,32),Getbit_C(csData,0,32) ));
	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("Retry Times Value")     ,(_variant_t)Getbit(csData,32,8),Getbit_C(csData,32,8) ));
	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("Retry Interval Value")  ,(_variant_t)Getbit(csData,40,8),Getbit_C(csData,40,8) ));
	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("MMSC Timeout Value")    ,(_variant_t)Getbit(csData,48,16),Getbit_C(csData,48,16) ));


	return pGroup1;
}
CMFCPropertyGridProperty* Explain_JDLData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("Java Download URL"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;


	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("Java Download URL"),TranslateAscii( WipeEmpty(csData) ),csData));


	return pGroup1;
}
CMFCPropertyGridProperty* Explain_LBSXTRAConfigData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup11;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("LBSXTRA Configuration"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup11 = new CMFCPropertyGridProperty (_T("XTRA Flags"),0,1);

	pGroup11->AddSubItem(new CMFCPropertyGridProperty(_T("使用gpsOneXTRA"),(_variant_t)_Getbit(csData,1), csData.Left(02)));
	pGroup11->AddSubItem(new CMFCPropertyGridProperty(_T("GPSOneXTRA自动下载"),(_variant_t)_Getbit(csData,2), csData.Left(02)));
	pGroup1->AddSubItem(pGroup11);
	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("GPSOneXTRA下载间隔")     ,(_variant_t)Getbit(csData,8,8),Getbit_C(csData,8,8) ));
	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("GPSOneXTRA下载重试次数") ,(_variant_t)Getbit(csData,16,8),Getbit_C(csData,16,8) ));
	pGroup1->AddSubItem(  new CMFCPropertyGridProperty(_T("GPSOneXTRA下载重试间隔")  ,(_variant_t)Getbit(csData,24,8),Getbit_C(csData,24,8) ));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_LBSXSURLData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("LBS XTRA 服务器URL"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	int iNumber = 1;

	while(!GetTLVData(csData,0x80,iNumber).IsEmpty())
	{

		pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("UDL"), TranslateAscii(GetTLVData(csData,0x80,iNumber)) ,   GetTLVData(csData,0x80,iNumber)  ));
		iNumber ++;
	}
	return pGroup1;
}
CMFCPropertyGridProperty* Explain_LBSV2ConfigData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("LBS V2配置"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;


	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("发送System Parameter Info消息"),(_variant_t) _Getbit(csData,1), csData ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("使用GPS One Seed Position")    ,(_variant_t) _Getbit(csData,2), csData ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("允许使用GPS One动态模式")      ,(_variant_t) _Getbit(csData,3), csData ));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_LBSV2PDEADDRData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("LBS V2 PDE 地址"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	CString csDes;



	switch(Getbit(csData,0,8))
	{
	case 1 : csDes = _T("域名");break;
	case 2 : csDes = _T("IPv4地址");break;
	case 3 : csDes = _T("IPv6地址");break;
	default:break;
	}

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("类别"),csDes, Getbit_C(csData,0,8) ));


	csDes = GetTLVData(csData,Getbit(csData,0,8));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("地址"),TranslateAscii(csDes),csDes));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("端口"),(_variant_t)Getbit(csData, csDes.GetLength()*4 +16 ,16) ,Getbit_C(csData,csDes.GetLength()*4 +16,16)));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_LBSV2MPCADDRData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("LBS V2 MPC 地址"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	CString csDes;



	switch(Getbit(csData,0,8))
	{
	case 1 : csDes = _T("域名");break;
	case 2 : csDes = _T("IPv4地址");break;
	case 3 : csDes = _T("IPv6地址");break;
	default:break;
	}

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("类别"),csDes, Getbit_C(csData,0,8) ));


	csDes = GetTLVData(csData,Getbit(csData,0,8));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("地址"),TranslateAscii(csDes),csDes));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("端口"),(_variant_t)Getbit(csData, csDes.GetLength()*4 +16 ,16) ,Getbit_C(csData,csDes.GetLength()*4 +16,16)));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_BREWDownloadData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	CMFCPropertyGridProperty* pGroup11;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("BREW Download"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	CString csDes;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("运营商ID "),csData.Mid(0,8), csData.Mid(0,8) ));
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("BREW A-Key  "),csData.Mid(8,16), csData.Mid(8,16) ));

	csDes = csData.Mid(24,128);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("BREW下载服务器"),TranslateAscii(WipeEmpty(csDes)) ,csDes ));


	csDes= csData.Mid(152,4);
	pGroup11 = new CMFCPropertyGridProperty (_T("BREW下载标签"),0,1);
	pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("使用A_KEY"),(_variant_t)_Getbit(csDes,1),csDes));
	pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("用MIN作为用户ID（SID）"),(_variant_t)_Getbit(csDes,2),csDes));	
	pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("预付费"),(_variant_t)_Getbit(csDes,3),csDes));
	pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("不自动进行Ack"),(_variant_t)_Getbit(csDes,4),csDes));
	pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("使用用户ID进行应用编码"),(_variant_t)_Getbit(csDes,5),csDes));
	pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("对所有应用进行验证"),(_variant_t)_Getbit(csDes,6),csDes));
	pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("允许RUIM用户删除手机中属于其它用户的应用"),(_variant_t)_Getbit(csDes,7),csDes));
	pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("自动升级"),(_variant_t)_Getbit(csDes,7),csDes));
	pGroup11->AddSubItem(new CMFCPropertyGridProperty (_T("不启动设置了MOD_ACK_DISABLED的应用"),(_variant_t)_Getbit(csDes,7),csDes));
	pGroup1->AddSubItem(pGroup11);
	csDes= csData.Mid(156,2);
	switch(_CString2Int(csData.Mid(156,2)))
	{
	case 00:csDes=_T("不需要认证"); break;
	case 01:csDes=_T("使用用户ID在任何交易开始前，将用户的用户ID（SID）传给ADS"); break;
	case 02:csDes=_T("输入文本口令用户应被提示输入文本口令，它将被传给ADS"); break;
	case 04:csDes=_T("输入数字口令用户应被提示输入数字口令，它将被传给ADS"); break;
	default:break;
	}

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("BREW下载认证策略"),csDes ,csData.Mid(156,2)));


	return pGroup1;
}
CMFCPropertyGridProperty* Explain_BREWTSIDData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("BREW Teleservice ID"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	CString csDes;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("BREW Teleservice ID"),csData, csData ));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_BREWSIDData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("BREW Subscriber ID"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	CString csDes;
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("BREW Subscriber ID"),csData, csData ));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_BREWAEPData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	pGroup1 = ExplainFirstNote(_T("BREW Application Execution Policy"),csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;
	CString csDes;

	switch(Getbit(csData,0,8))
	{
	case 0:csDes =_T("PPOLICY_BREW"); break;
	case 1:csDes =_T("PPOLICY_CARRIER"); break;
	case 2:csDes =_T("PPOLICY_BREW_AND_CARRIER	"); break;
	case 3:csDes =_T("PPOLICY_BREW_OR_CARRIER	"); break;
	default:csDes =_T(" RFU。"); break;
	}

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("BREW Application Execution Policy"),csDes, csData ));

	return pGroup1;
}


CMFCPropertyGridProperty* Explain_CPBCCHData(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup2;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("CPBCCH Information"),0,bSubItem);

	int iLen;
	CString csDes;
	CString csTemp;
	iLen = csData.GetLength();
	for (int i = 0 ; i < iLen; i+=4)
	{
		csTemp.Format(_T("%02d"),i/4 +1);

		pGroup2 = new CMFCPropertyGridProperty(_T("Element ")+csTemp+ _T("of CPBCCH carrier list"),0,1);

		csDes = csData.Mid(i,4);
		pGroup2->AddSubItem(new CMFCPropertyGridProperty (_T("ARFCN"),(_variant_t)( _CString2Int(csDes)&0x3F) ,csDes));


		if (Getbit(csDes,03))
			csDes = _T("High");
		else
			csDes = _T("Low");
		pGroup2->AddSubItem(new CMFCPropertyGridProperty (_T("Band indicator"), csDes ,csDes));

		pGroup1->AddSubItem(pGroup2);	

	}
	return pGroup1;  

}
CMFCPropertyGridProperty* Explain_InvScanData(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Investigation Scan"),0,bSubItem);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("In limited service mode"),(_variant_t) Getbit(csData,1) ,csData));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("After successful PLMN selection"),(_variant_t)Getbit(csData,2) ,csData));

	return pGroup1;

}
CMFCPropertyGridProperty* Explain_MLPLData(CString csData)
{
	int iOffset;
	CString csNumber;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("MLPL"));
	CMFCPropertyGridProperty* pGroup2;

	pGroup1->AddSubItem (new CMFCPropertyGridProperty(_T("MLPL_SIZE")     ,(_variant_t) Getbit(csData,0,16),Getbit_C(csData,0,16)));
	pGroup1->AddSubItem (new CMFCPropertyGridProperty(_T("CUR_MMSS_P_REV"),(_variant_t) Getbit(csData,16,8),Getbit_C(csData,16,8)));
	pGroup1->AddSubItem (new CMFCPropertyGridProperty(_T("MLPL_VER_ID"),(_variant_t) Getbit(csData,24,16),Getbit_C(csData,24,16)));
	pGroup1->AddSubItem (new CMFCPropertyGridProperty(_T("MLPL_ID"),(_variant_t) Getbit(csData,40,8),Getbit_C(csData,40,8)));
	pGroup1->AddSubItem (new CMFCPropertyGridProperty(_T("NUM_MLPL_RECS"),(_variant_t) Getbit(csData,48,8),Getbit_C(csData,48,8)));
	iOffset = 56;

	for (int i= 0 ; i <  Getbit(csData,48,8); i++)
	{
		csNumber.Format(_T("%02d"),i+1);
		pGroup2 = new CMFCPropertyGridProperty(_T("MLPL_RECS ")+csNumber,0,1);
		if (_Explain_MLPLRECSData(pGroup2,csData,&iOffset))
			pGroup1->AddSubItem(pGroup2);


	}

	return pGroup1;

}
BOOL _Explain_MLPLRECSData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{
	CString csDes;
	CString csTemp;

	csDes =  Getbit_C(csData,*iOffbit,8);
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("LOC_PARAM_TYPE"),csDes,csDes));

	*iOffbit = *iOffbit+8;

	if (Getbit(csDes,1))
	{

		csTemp = Getbit_C(csData,*iOffbit,12);
		//	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("MCC"),_Getbit_C(csData,*iOffbit,12) ,_Getbit_C(csData,*iOffbit,12)));

		ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("MCC"),csData.Mid(*iOffbit/4,3) ,csData.Mid(*iOffbit/4,3)));

		*iOffbit = *iOffbit+12;
	}

	if (Getbit(csDes,2))
	{
		csTemp = Getbit_C(csData,*iOffbit,12);
		ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("MNC"),csData.Mid(*iOffbit/4,3) ,csData.Mid(*iOffbit/4,3)));
		*iOffbit = *iOffbit+12;
	}
	if (Getbit(csDes,3))
	{
		csTemp = Getbit_C(csData,*iOffbit,8);
		ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_SYS_LOC_TAG"),Getbit_C(csData,*iOffbit,8) ,Getbit_C(csData,*iOffbit,12)));
		*iOffbit = *iOffbit+8;

		ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("SYS_TYPE"),Getbit_C(csData,*iOffbit,8) ,Getbit_C(csData,*iOffbit,12)));


		switch(Getbit(csData,*iOffbit,8))
		{
		case 00:
			csDes = _T("cdma2000_AI");
			break;
		case 01:
			csDes = _T("3GPP_AI");
			break;
		case 02:
			csDes = _T("WiMax");
			break;
		case 03:
			csDes = _T("cdma2000_1x");
			break;
		case 04:
			csDes = _T("cdma2000_HRPD");
			break;
		case 05:
			csDes = _T("GERAN(GSM)");
			break;
		case 06:
			csDes = _T("UTRAN(UMTS)");
			break;
		case 07:
			csDes = _T("EUTRAN(LTE)");
			break;
		default:
			csDes = _T("Reserved for future standardization");
			break;

		}
		*iOffbit = *iOffbit+8;
		ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("SYS_LOC_TAG_SIZE"),csDes,Getbit_C(csData,*iOffbit,12)));
		*iOffbit = *iOffbit+8;
		switch(Getbit(csData,*iOffbit-16,8))
		{
		case 00:
		case 03:

			*iOffbit += 1;
			ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("SID"),Getbit_C(csData,*iOffbit,15) ,Getbit_C(csData,*iOffbit,15)));
			*iOffbit += 15;
			ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("NID_START"),Getbit_C(csData,*iOffbit,16) ,Getbit_C(csData,*iOffbit,16)));
			*iOffbit += 16;
			ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("NID_RANGE"),Getbit_C(csData,*iOffbit,8) ,Getbit_C(csData,*iOffbit,8)));
			*iOffbit += 8;
			break;
		case 01:
		case 05:
		case 06:
		case 07:
			ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("PLMN_START"),Getbit_C(csData,*iOffbit,24) ,Getbit_C(csData,*iOffbit,24)));
			*iOffbit += 24;
			ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("PLMN_RANGE"),Getbit_C(csData,*iOffbit,8) ,Getbit_C(csData,*iOffbit,8)));
			*iOffbit += 8;
			break;
		case 04:

			csDes = Getbit_C(csData,*iOffbit,8);
			ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("PLMN_START"), csDes ,csDes));
			*iOffbit += 8;

			ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("PLMN_RANGE"),Getbit_C(csData,*iOffbit,_CString2Int(csDes)) ,Getbit_C(csData,*iOffbit,_CString2Int(csDes))));
			*iOffbit += _CString2Int(csDes);
			if((*iOffbit%8)!= 0)
				*iOffbit += (8 - (*iOffbit%8) );
			break;

		default:
			csDes = _T("Reserved for future standardization");
			break;

		}

	}

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("MSPL_INDEX"),(_variant_t)Getbit(csData,*iOffbit,8) ,Getbit_C(csData,*iOffbit,8)));
	*iOffbit += 8;	
	return TRUE;
}
CMFCPropertyGridProperty* Explain_MSPLData(CString csData, BOOL bSubItem)
{
	int iOffset;
	CString csNumber;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("MLPL"),0,bSubItem);
	CMFCPropertyGridProperty* pGroup2;

	pGroup1->AddSubItem (new CMFCPropertyGridProperty(_T("MSPL_SIZE")     ,(_variant_t) Getbit(csData,0,16),Getbit_C(csData,0,16)));
	pGroup1->AddSubItem (new CMFCPropertyGridProperty(_T("CUR_MMSS_P_REV"),(_variant_t) Getbit(csData,16,8),Getbit_C(csData,16,8)));
	pGroup1->AddSubItem (new CMFCPropertyGridProperty(_T("MSPL_VER_ID")   ,(_variant_t) Getbit(csData,24,16),Getbit_C(csData,24,16)));
	pGroup1->AddSubItem (new CMFCPropertyGridProperty(_T("NUM_MSPL_ID")   ,(_variant_t) Getbit(csData,40,8),Getbit_C(csData,40,8)));
	iOffset = 48;
	for (int i= 0 ; i <  Getbit(csData,40,8); i++)
	{
		csNumber.Format(_T("%02d"),i+1);
		pGroup2 = new CMFCPropertyGridProperty(_T("MSPL_ID ")+csNumber,0,1);
		if (_Explain_MSPLIDData(pGroup2,csData,&iOffset))
			pGroup1->AddSubItem(pGroup2);
	}
	if ((iOffset%8)!=0)
		iOffset = (iOffset/8 +1 )*8;
	pGroup1->AddSubItem (new CMFCPropertyGridProperty(_T("MSPL_CRC"), Getbit_C(csData,iOffset,16),Getbit_C(csData,iOffset,16)));
	return pGroup1;
}
BOOL _Explain_MSPLIDData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{
	int iNumber;
	CString csTemp,csNumber;

	CMFCPropertyGridProperty* pGroup2;

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("MSPL_ID"),(_variant_t)Getbit(csData,*iOffbit,8),Getbit_C(csData,*iOffbit,8)));
	*iOffbit = *iOffbit+8;

	iNumber = Getbit(csData,*iOffbit,8);
	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("NUM_MSPL_RECS"),(_variant_t)iNumber,Getbit_C(csData,*iOffbit,8)));

	*iOffbit = *iOffbit+8;


	for (int i= 0 ; i < iNumber; i++)
	{
		csNumber.Format(_T("%02d"),i+1);
		pGroup2 = new CMFCPropertyGridProperty(_T("MSPL_RECS ")+csNumber,0,1);
		if (_Explain_MSPLRECSData(pGroup2,csData,iOffbit))
			ParentGroup->AddSubItem(pGroup2);
	}

	return TRUE;
}
BOOL _Explain_MSPLRECSData(CMFCPropertyGridProperty* ParentGroup,CString csData,int* iOffbit)
{
	CString csDes;
	CString csTemp,csNumber;

	switch(Getbit(csData,*iOffbit,8))
	{
	case 00:
		csDes = _T("cdma2000_AI");
		break;
	case 01:
		csDes = _T("3GPP_AI");
		break;
	case 02:
		csDes = _T("WiMax");
		break;
	case 03:
		csDes = _T("cdma2000_1x");
		break;
	case 04:
		csDes = _T("cdma2000_HRPD");
		break;
	case 05:
		csDes = _T("GERAN(GSM)");
		break;
	case 06:
		csDes = _T("UTRAN(UMTS)");
		break;
	case 07:
		csDes = _T("EUTRAN(LTE)");
		break;
	default:
		csDes = _T("Reserved for future standardization");
		break;

	}

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("SYS_TYPE"),csDes,Getbit_C(csData,*iOffbit,8)));
	*iOffbit+= 8;

	switch(Getbit(csData,*iOffbit,4))
	{
	case 00:
		csDes = _T("Home only");
		break;
	case 01:
		csDes = _T("Home + Preferred");
		break;
	case 0xF:
		csDes = _T("Any");
		break;
	default:
		csDes = _T("Reserved");
		break;

	}
	csTemp.Format(_T("%02x"),Getbit(csData,*iOffbit,4));

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("PRI_CLASS"),csDes,csTemp));
	*iOffbit+= 4;

	if (Getbit(csData,*iOffbit,1))
		csDes = _T("More ");
	else
		csDes = _T("Same ");

	csTemp.Format(_T("%02x"),Getbit(csData,*iOffbit,1));

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("SYS_PRI"),csDes,csTemp));
	*iOffbit+= 1;

	switch(Getbit(csData,*iOffbit,3))
	{
	case 00:
		csDes = _T("1 minute");
		break;
	case 01:
		csDes = _T("2 minute");
		break;
	case 02:
		csDes = _T("4 minute");
		break;
	case 03:
		csDes = _T("8 minute");
		break;
	case 04:
		csDes = _T("16 minute");
		break;
	case 05:
		csDes = _T("24 minute");
		break;
	case 06:
		csDes = _T("32 minute");
		break;
	case 07:
		csDes = _T("64 minute");
		break;
	}
	csTemp.Format(_T("%02x"),Getbit(csData,*iOffbit,3));

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("HIGHER_PRI_SRCH_TIME"),csDes,csTemp));
	*iOffbit+= 3;

	if (Getbit(csData,*iOffbit,1))
		csDes = _T("Exist");
	else
		csDes = _T("Absent");
	csTemp.Format(_T("%02x"),Getbit(csData,*iOffbit,1));

	ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("NETWORK_CAP_IND"),csDes,csTemp));

	if (Getbit(csData,*iOffbit,1))
	{
		if (Getbit(csData,*iOffbit+1,6) == 0)
			csDes = _T("Voice and Data");
		else
			csDes = _T("Reserved");
		csTemp.Format(_T("%02x"),Getbit(csData,*iOffbit,6));
		ParentGroup->AddSubItem(new CMFCPropertyGridProperty (_T("NETWORK_CAP"),(_variant_t)Getbit(csData,*iOffbit+1,6),csTemp));
		*iOffbit+= 6;
	}
	*iOffbit+= 1;

	return TRUE;
}


CMFCPropertyGridProperty* _Explain_PBRData(CString csData,CString csName,BOOL bSubItem)
{
	CMFCPropertyGridProperty *pGroup1;
	CMFCPropertyGridProperty *pGroup11;

	CString csPresence,csFile;
	UINT uiANRExist   = 0;
	UINT uiEmailExist = 0;
	UINT uiSNEExist   = 0;

	pGroup1 = new CMFCPropertyGridProperty(_T("PBR "),FALSE,bSubItem);

	if (WipeEmpty(csData).IsEmpty())
		return pGroup1;

	pGroup11 = new CMFCPropertyGridProperty(_T("Type1 File "),FALSE,bSubItem);



	csPresence = GetTLVData(csData,0xA8);
	csFile     = GetTLVData(csPresence,0xC0);
	csName  = _T("ADN ");
	pGroup11->AddSubItem(Explain_FileInPBRData(csFile,csName));


	csFile     = GetTLVData(csPresence,0xC1);
	csName  = _T("IAP ");
	pGroup11->AddSubItem(Explain_FileInPBRData(csFile,csName));

	csFile     = GetTLVData(csPresence,0xC3);
	csName  = _T("SNE ");
	pGroup11->AddSubItem(Explain_FileInPBRData(csFile,csName));
	if (!csFile.IsEmpty())
		uiANRExist = 1;

		
	
	csFile     = GetTLVData(csPresence,0xC4);
	csName  = _T("ANR ");
	pGroup11->AddSubItem(Explain_FileInPBRData(csFile,csName));
	if (!csFile.IsEmpty())
		uiANRExist = 1;


	csFile     = GetTLVData(csPresence,0xC5);
	csName  = _T("PBC ");
	pGroup11->AddSubItem(Explain_FileInPBRData(csFile,csName));


	csFile     = GetTLVData(csPresence,0xC6);
	csName  = _T("GRP ");
	pGroup11->AddSubItem(Explain_FileInPBRData(csFile,csName));

	csFile     = GetTLVData(csPresence,0xC9);
	csName  = _T("UID ");
	pGroup11->AddSubItem(Explain_FileInPBRData(csFile,csName));

	csFile     = GetTLVData(csPresence,0xCA);
	csName  = _T("EMAIL ");
	pGroup11->AddSubItem(Explain_FileInPBRData(csFile,csName));
	if (!csFile.IsEmpty())
		uiEmailExist = 1;


	pGroup1->AddSubItem(pGroup11);

	pGroup11 = new CMFCPropertyGridProperty(_T("Type2 File "),FALSE,bSubItem);



	csPresence = GetTLVData(csData,0xA9);
	csFile     = GetTLVData(csPresence,0xC3);
	csName  = _T("SNE ");
	pGroup11->AddSubItem(Explain_FileInPBRData(csFile,csName));
	if (!csFile.IsEmpty())
		uiSNEExist += 2;




	csFile     = GetTLVData(csPresence,0xC4);
	csName  = _T("ANR ");
	pGroup11->AddSubItem(Explain_FileInPBRData(csFile,csName));
	if (!csFile.IsEmpty())
		uiANRExist += 2;


	csFile     = GetTLVData(csPresence,0xCA);
	csName     = _T("EMAIL ");
	pGroup11->AddSubItem(Explain_FileInPBRData(csFile,csName));
	pGroup1->AddSubItem(pGroup11);
	if (!csFile.IsEmpty())
		uiEmailExist += 2;


	pGroup11 = new CMFCPropertyGridProperty(_T("Type3 File "),FALSE,bSubItem);

	csPresence = GetTLVData(csData,0xAA);
	csFile     = GetTLVData(csPresence,0xC2);
	csName     = _T("EXT ");
	pGroup11->AddSubItem(Explain_FileInPBRData(csFile,csName));


	csFile     = GetTLVData(csPresence,0xC7);
	csName     = _T("AAS ");
	pGroup11->AddSubItem(Explain_FileInPBRData(csFile,csName));

	csFile     = GetTLVData(csPresence,0xC8);
	csName     = _T("GAS ");
	pGroup11->AddSubItem(Explain_FileInPBRData(csFile,csName));


	csFile     = GetTLVData(csPresence,0xCB);
	csName     = _T("CPP ");
	pGroup11->AddSubItem(Explain_FileInPBRData(csFile,csName));
	pGroup1->AddSubItem(pGroup11);


	if ((uiEmailExist == 1)||(uiEmailExist == 3))
		EnableProperty(pGroup1->GetSubItem(1)->GetSubItem(2),FALSE);
	else if(uiEmailExist == 2)
		EnableProperty(pGroup1->GetSubItem(0)->GetSubItem(7),FALSE);

	if ((uiSNEExist == 1)||(uiSNEExist == 3))
		 EnableProperty(pGroup1->GetSubItem(1)->GetSubItem(0),FALSE);
	else if(uiSNEExist == 2)
		 EnableProperty(pGroup1->GetSubItem(0)->GetSubItem(2),FALSE);

	if ((uiANRExist == 1)||(uiANRExist == 3))
		 EnableProperty(pGroup1->GetSubItem(1)->GetSubItem(1),FALSE);
	else if(uiANRExist == 2)
		 EnableProperty(pGroup1->GetSubItem(0)->GetSubItem(3),FALSE);


	return pGroup1;
}



CMFCPropertyGridProperty* Explain_FileInPBRData(CString csFile,CString csName,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup;
	CMFCPropertyGridProperty* pGroup1;
	CString csValue;
	pGroup = new CMFCPropertyGridProperty(csName,FALSE,bSubItem);
	int iDataLen;
	iDataLen = csFile.GetLength();
	pGroup->AddSubItem(new CMFCPropertyGridProperty (_T("FID"),_T(""),_T("")));
	pGroup->AddSubItem(new CMFCPropertyGridProperty (_T("SFI"),_T(""),_T("")));


	if (iDataLen >= 4)
	{
		csValue = csFile.Mid(0,4);
		pGroup1 = pGroup->GetSubItem(0);
		pGroup1->SetValue(csValue);
		pGroup1->SetOriginalValue(csValue);
		pGroup1->SetDescription(csValue);
	}

	if (iDataLen >= 6)
	{
		csValue = csFile.Mid(4,2);
		pGroup1 = pGroup->GetSubItem(1);
		pGroup1->SetValue(csValue);
		pGroup1->SetOriginalValue(csValue);
		pGroup1->SetDescription(csValue);
	}
	return pGroup;
}
CMFCPropertyGridProperty* Explain_IAPData(CString csData,int iNumber,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);

	pGroup1 = ExplainFirstNote(_T("IAP ")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Index Administration Phone book"),csData, csData ));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_SNEData(CString csData,int iNumber,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	CString csNumber,csTemp;
	csNumber.Format(_T("%02d"),iNumber);

	pGroup1 = ExplainFirstNote(_T("SNE ")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	csTemp = csData.Mid(0,csData.GetLength()-4);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Alpha Identifier of Second Name"),TranslateAlphaIdentifier(csTemp), csTemp ));

	csTemp = csData.Mid(csTemp.GetLength(),2);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("ADN file SFI"),csTemp, csTemp ));

	csTemp = csData.Right(02);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("ADN file Record Identifier"),csTemp, csTemp ));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_CPP1Data(CString csData,int iNumber,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);

	pGroup1 = ExplainFirstNote(_T("Bearer capability information element ")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Bearer capability information element"),csData, csData ));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_UIDData(CString csData,int iNumber,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);

	pGroup1 = ExplainFirstNote(_T("UID")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Unique Identifier (UID) of Phone Book Entry"),csData, csData ));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_ANRData(CString csData,int iNumber,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	CString csNumber,csTemp;
	csNumber.Format(_T("%02d"),iNumber);

	pGroup1 = ExplainFirstNote(_T("Additional Number")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Additional Number Record identifier"),csData.Mid(0,2), csData.Mid(0,2) ));

	csTemp   = csData.Mid(2,24);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Phone Number"), _TransationADNNumber(csTemp) ,csTemp));

	csTemp   = csData.Mid(26,2);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Capability/Configuration1 Record Identifier"), csTemp ,csTemp));
	csTemp   = csData.Mid(28,2);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Extension1 Record Identifier"), csTemp ,csTemp));
	csTemp   = csData.Mid(30,2);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("ADN file SFI"), csTemp ,csTemp));
	csTemp   = csData.Mid(32,2);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("ADN file Record Identifier"), csTemp ,csTemp));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_GASData(CString csData,int iNumber,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	CString csNumber,csTemp;
	csNumber.Format(_T("%02d"),iNumber);

	pGroup1 = ExplainFirstNote(_T("Grouping information Alpha String")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Alpha text string"),TranslateAlphaIdentifier(csData), csData));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_AASData(CString csData,int iNumber,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);

	pGroup1 = ExplainFirstNote(_T("Additional number Alpha String")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Alpha text string"),TranslateAlphaIdentifier(csData), csData));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_GRPData(CString csData,int iNumber,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	CString csNumber;
	csNumber.Format(_T("%02d"),iNumber);

	pGroup1 = ExplainFirstNote(_T("Grouping file")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Group Name Identifier"),csData, csData));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_PBCData(CString csData,int iNumber,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	CString csNumber,csTemp;
	csNumber.Format(_T("%02d"),iNumber);

	pGroup1 = ExplainFirstNote(_T("Phone Book Control")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;

	if (Getbit(csData,1))
		csTemp = _T("Modified phonebook entry");
	else
		csTemp = _T("No change");
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Entry Control Information"),csTemp, csData.Left(02)));

	if (csData.Mid(2,2) == _T("00"))
		csTemp = _T("the phone book entry is not hidden");
	else
		csTemp = _T("the phone book entry is hidden.")+csData.Mid(2,2)+_T("is the record number in EFDIR of the associated USIM application");
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Entry Control Information"),csTemp,csData.Mid(2,2)));


	return pGroup1;
}
CMFCPropertyGridProperty* Explain_EMAILData(CString csData,int iNumber,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup1;
	bool bRet = false;
	CString csNumber,csTemp;
	csNumber.Format(_T("%02d"),iNumber);

	pGroup1 = ExplainFirstNote(_T("EMAIL")+csNumber,csData,&bRet, bSubItem);
	if (!bRet)
		return pGroup1;


	csTemp = csData.Mid(0,csData.GetLength()-4);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("E-mail Address"),Translate7bit (csTemp), csTemp ));


	csTemp = csData.Mid(csData.GetLength()-4,2);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("ADN file SFI"),csTemp, csTemp ));

	csTemp = csData.Right(02);

	pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("ADN file Record Identifier"),csTemp, csTemp ));

	return pGroup1;
}
CMFCPropertyGridProperty* Explain_AUTHOPC(CString csData,BOOL bSubItem)
{

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("OPC/OP 参数"),0,bSubItem);
	CString csTemp,csDis;
	if (csData.GetLength()<0x22)
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Error"),_T("文件长度不正确"), _T("") ));
	}else
	{	
		csTemp = csData.Mid(0,2);
		if (_CString2Int(csTemp) == 00)
			csDis = _T("OPC");
		if (_CString2Int(csTemp) == 01)
			csDis = _T("OP");
		pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("OP/OPC"),csDis, csTemp ));
		csTemp =csData.Mid(2,0x20); 
		pGroup1->AddSubItem(new CMFCPropertyGridProperty (csDis,csTemp, csTemp));

		if (csData.GetLength()>=54)
		{
			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("RI"),csData.Mid(0x22,10), csData.Mid(0x22,10)));
			pGroup1->AddSubItem(new CMFCPropertyGridProperty (_T("Simple CI"),csData.Mid(0x2C,10), csData.Mid(0x2C,10)));
		}
	}
	pGroup1->Expand();
	NotAllowEdit(pGroup1);
	return pGroup1;
}
CMFCPropertyGridProperty* Explain_AUTHPAR(CString csData,BOOL bSubItem)
{
	CMFCPropertyGridProperty* pGroup;
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Milenage 参数"),0,bSubItem);
	CString csTemp,csDis;
	if (csData.GetLength()<30)
	{
		pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Error"),_T("文件长度不正确"), _T("") ));
	}else
	{	
		csTemp =csData.Mid(0,2);
		if ( _CString2Int(csTemp)==01  )
			csDis = _T("Milenage");
		else
			csDis = _T("Unknow");
		pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Type of Algorithm"),csDis, csTemp ));


		csTemp =csData.Mid(2,2); 
		pGroup = new CMFCPropertyGridProperty(_T("Milenage Parameters"),0,1);

		if (Getbit_E(csTemp,1))
			csDis = _T("Received SQN concealed ");
		else
			csDis = _T("Receiverd SQN unconcealed ");

		pGroup->AddSubItem(new CMFCPropertyGridProperty ( _T("Received SQN"),csDis, csTemp ));

		if (Getbit_E(csTemp,2))
			csDis = _T("Response SQN concealed ");
		else
			csDis = _T("Response SQN unconcealed ");

		pGroup->AddSubItem(new CMFCPropertyGridProperty ( _T("Response SQN"),csDis, csTemp ));

		if (Getbit_E(csTemp,3))
			csDis = _T("zero is used in response of resynchronize");
		else
			csDis = _T("AMF is used in response of resynchronize ");

		pGroup->AddSubItem(new CMFCPropertyGridProperty ( _T("Use AMF in  response of resynchronize"),csDis, csTemp ));	

		pGroup1->AddSubItem(pGroup);

		csTemp =csData.Mid(4,2); 
		pGroup = new CMFCPropertyGridProperty(_T("SQN options"),0,1);

		if (Getbit_E(csTemp,1))
			csDis = _T("Supported");
		else
			csDis = _T("Unsupported");

		pGroup->AddSubItem(new CMFCPropertyGridProperty ( _T("SQN > SQN_MS(INDEX)"),csDis, csTemp ));

		if (Getbit_E(csTemp,2))
			csDis = _T("Supported");
		else
			csDis = _T("Unsupported");

		pGroup->AddSubItem(new CMFCPropertyGridProperty ( _T("SQN + L > SQN_MS"),csDis, csTemp ));

		if (Getbit_E(csTemp,3))
			csDis = _T("Supported");
		else
			csDis = _T("Unsupported");

		pGroup->AddSubItem(new CMFCPropertyGridProperty ( _T("SQN <= SQN_MS + delta"),csDis, csTemp ));	

		if (Getbit_E(csTemp,4))
			csDis = _T("Supported");
		else
			csDis = _T("Unsupported");

		pGroup->AddSubItem(new CMFCPropertyGridProperty ( _T("SQN > SQN_MS"),csDis, csTemp ));	

		pGroup1->AddSubItem(pGroup);

		csTemp= csData.Mid(06,12);

		pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("L"),RightShift(csTemp,5).Left(12), csTemp ));

		csTemp= csData.Mid(18,30);

		pGroup1->AddSubItem(new CMFCPropertyGridProperty ( _T("Delta"),RightShift(csTemp,5).Left(12), csTemp ));

	}

	NotAllowEdit(pGroup1);
	pGroup1->Expand();
	return pGroup1;
}

BOOL NotAllowEdit(CMFCPropertyGridProperty* Prop)
{

	if (Prop == NULL)
		return FALSE;

	if (Prop->IsAllowEdit())
		Prop->AllowEdit(FALSE);
	//	Prop->Enable(FALSE);

	int iSum = Prop->GetSubItemsCount();
	for (int i = 0 ; i < iSum ; i ++)
		NotAllowEdit( Prop->GetSubItem(i));
	return TRUE;
}


CMFCPropertyGridProperty* Explain_FileData_InMF(CString csData,int iFID,int iRecord,BOOL bSub)
{
	CMFCPropertyGridProperty* pGroup = NULL;
	switch (iFID)
	{

	case 0x2F00:
		 pGroup = Explain2F00Data(csData,bSub);break;
	case 0x2F05:
		 pGroup = ExplainLIData(csData,bSub);break;
	case 0x2F06:
		pGroup  = ExplainARRRecord(csData,iRecord,bSub);break;
	case 0x2FE2:
		pGroup  = Explain2FE2Data(csData,bSub);break;
	default:
		break;
	}

	return pGroup;
}

CMFCPropertyGridProperty* Explain_FileData_InTelecom(CString csData,int iFID,int iRecord,BOOL bSub)
{
	CMFCPropertyGridProperty* pGroup = NULL;

	switch (iFID)
	{
	case 0x6F06: pGroup  = ExplainARRRecord(csData,iRecord,bSub);break;
	case 0x6F3A: pGroup  = ExplainADNData(csData,iRecord,bSub);break;
	case 0x6F3B: pGroup  = ExplainFDNData(csData,iRecord,bSub);break;
	case 0x6F3C: pGroup  = ExplainSMSData(csData,iRecord,bSub);break;
	case 0x6F3D: pGroup  = ExplainCCPData(csData,iRecord,bSub);break;
	case 0x6F40: pGroup  = ExplainMSISDNData(csData,iRecord,bSub);break;
	case 0x6F42: pGroup  = ExplainSMSPData(csData,iRecord,bSub);break;
	case 0x6F43: pGroup  = ExplainSMSSData(csData,bSub);break;
	case 0x6F44: pGroup  = ExplainLNDData(csData,iRecord,bSub);break;
	case 0x6F47: pGroup  = ExplainSMSRData(csData,iRecord,bSub);break;
	case 0x6F49: pGroup  = ExplainSDNData(csData,iRecord,bSub);break;
	case 0x6F4A: pGroup  = ExplainEXTData(csData,iRecord,bSub);break;
	case 0x6F4B: pGroup  = ExplainEXTData(csData,iRecord,bSub);break;
	case 0x6F4C: pGroup  = ExplainEXTData(csData,iRecord,bSub);break;
	case 0x6F4D: pGroup  = ExplainBDNData(csData,iRecord,bSub);break;
	case 0x6F4E: pGroup  = ExplainEXTData(csData,iRecord,bSub);break;
	case 0x6F4F: pGroup  = ExplainCCP2Data(csData,iRecord,bSub);break;
	default:break;
	}
	return pGroup;
}

CMFCPropertyGridProperty* Explain_FileData_InMMSS(CString csData,int iFID,int iRecord,BOOL bSub)
{
	CMFCPropertyGridProperty* pGroup = NULL;
	switch (iFID)
	{
	case 0x4F20:pGroup = Explain_MSPLData(csData,bSub);break;
	case 0x4F21:pGroup = Explain_MSPLData(csData,bSub);break;
	}
	return pGroup;
}

CMFCPropertyGridProperty* Explain_FileData_InGSMACCESS(CString csData,int iFID,int iRecord,BOOL bSub)
{
	CMFCPropertyGridProperty* pGroup = NULL;
	switch (iFID)
	{

	case 0x4F20:
		pGroup =ExplainKcIData(csData) ;
		break;
	case 0x4F52:
		pGroup =ExplainKcGPRSData(csData) ;
		break;
	case 0x4F63:
		pGroup =Explain_CPBCCHData(csData) ;
		break;
	case 0x4F64:
		pGroup =Explain_InvScanData(csData) ;
		break;
	}
	return pGroup;
}

CMFCPropertyGridProperty* Explain_FileData_InPhoneBook(CString csData,int iFID,int iRecord,BOOL bSub)
{
	CMFCPropertyGridProperty* pGroup = NULL;
	switch (iFID)
	{
	case 0x4F30:
		pGroup = _Explain_PBRData( csData,_T("PBR"),bSub);break;
	}
	return pGroup;
}



CMFCPropertyGridProperty* Explain_FileData_InGSM(CString csData,int iFID,int iRecord,BOOL bSub)
{
	CMFCPropertyGridProperty* pGroup = NULL;
	CString csRecord;


	switch (iFID)
	{

	case 0x6F05:pGroup  = ExplainLIData(csData,bSub);break;
	case 0x6F06:pGroup  = ExplainARRRecord(csData,iRecord,bSub);break;
	case 0x6F07:pGroup  = ExplainIMSIData(csData,bSub);break;
	case 0x6F20:pGroup  = ExplainKcIData(csData,bSub);break;
	case 0x6F2C:
		break;
	case 0x6F30:pGroup  = ExplainPLMNselData(csData,bSub);break;
	case 0x6F31:pGroup  = ExplainHPPLMNData(csData,bSub);break;
	case 0x6F32:pGroup  = ExplainCNLData(csData,bSub);break;
	case 0x6F37:pGroup  = ExplainACMmaxData(csData,bSub);break;
	case 0x6F38:pGroup  = ExplainSSTData(csData,bSub);break;
	case 0x6F39:pGroup  = ExplainACMData(csData,iRecord,bSub);break;
	case 0x6F3E:
		break;
	case 0x6F3F:
		break;
	case 0x6F41:
		break;
	case 0x6F45:pGroup  = ExplainCBMIData(csData,bSub);break;
	case 0x6F46:pGroup  = ExplainSPNData(csData,bSub);break;
	case 0x6F48:pGroup  = ExplainCBMIDData(csData,bSub);break;
	case 0x6F50:pGroup  = ExplainCBMIRData(csData,bSub);break;
	case 0x6F51:pGroup  = ExplainNIAData(csData,iRecord,bSub);break;
	case 0x6F52:pGroup  = ExplainKcGPRSData(csData,bSub);break;
	case 0x6F53:pGroup  = ExplainCBMIRData(csData,bSub);break;
	case 0x6F54:pGroup  = ExplainSUMEData(csData,bSub);break;
	case 0x6F60:pGroup  = ExplainPLMNwAcTData(csData,bSub);break;
	case 0x6F61:pGroup  = ExplainOPLMNwACTData(csData,bSub);break;
	case 0x6F62:pGroup  = ExplainHPLMNwACTData(csData,bSub);break;
	case 0x6F74:pGroup  = ExplainBCCHData(csData,bSub);break;
	case 0x6F78:pGroup  = ExplainACCData(csData,bSub);break;
	case 0x6F7B:pGroup  = ExplainFPLMNData(csData,bSub);break;
	case 0x6F7E:pGroup  = ExplainLOCIData(csData,bSub);break;
	case 0x6FAD:pGroup  = ExplainADData(csData,bSub);break;
	case 0x6FAE:pGroup  = ExplainPhaseData(csData,bSub);break;
	case 0x6FB1:pGroup  = ExplainVGCSData(csData,bSub);break;
	case 0x6FB2:pGroup  = ExplainVGCSSData(csData,bSub);break;
	case 0x6FB3:pGroup  = ExplainVBSData(csData,bSub);break;
	case 0x6FB4:pGroup  = ExplainVBSSData(csData,bSub);break;
	case 0x6FB5:pGroup  = ExplaineMLPPData(csData,bSub);break;
	case 0x6FB6:pGroup  = ExplaineAAeMData(csData,bSub);break;
	case 0x6FB7:pGroup  = ExplainECCData(csData,iRecord,bSub);break;
	case 0x6FD9:pGroup  = ExplainEHPLMNData(csData,bSub);break;
	default:
		break;
	}
	return pGroup;
}

CMFCPropertyGridProperty* Explain_FileData_InCDMA(CString csData,int iFID,int iRecord,BOOL bSub)
{
	CMFCPropertyGridProperty* pGroup = NULL;
	CString csRecord;


	switch(iFID)
	{

		case 0x6F06:pGroup  = ExplainARRRecord(csData,iRecord,bSub);break;

		case 0x6F21:pGroup=ExplainCOUNTData(csData,iRecord, bSub);break;

		case 0x6F22:pGroup=ExplainIMSIMData(csData,bSub);break;

		case 0x6F23:pGroup=ExplainIMSITData(csData,bSub);break;

		case 0x6F24:pGroup=ExplainTMSIData(csData,bSub);break;

		case 0x6F25:pGroup=ExplainAHData(csData,bSub);break;

		case 0x6F26:pGroup=ExplainAOPData(csData,bSub);break;

		case 0x6F27:pGroup=ExplainALOCData(csData,bSub);break;

		case 0x6F28:pGroup=ExplainSIDNIDData(csData,iRecord,bSub);break;

		case 0x6F29:pGroup=ExplainZNREGIData(csData,iRecord,bSub);break;

		case 0x6F2A:pGroup=ExplainSNREGIData(csData,bSub);break;

		case 0x6F2B:pGroup=ExplainDISTREGIIData(csData,bSub);break;

		case 0x6F2C:pGroup=ExplainACCOLCData(csData,bSub);break;

		case 0x6F2D:pGroup=ExplainTERMData(csData,bSub);break;

		case 0x6F2E:
			pGroup=ExplainSSCIData(csData,bSub);break;

		case 0x6F2F:
			pGroup=ExplainACPData(csData,bSub);break;

		case 0x6F30:
			pGroup=ExplainPRLFileData(csData,bSub);break;

		case 0x6F31:
			pGroup=ExplainUIMIDData(csData,bSub);break;

		case 0x6F32:

		case 0x6F33:
			pGroup=ExplainSPCData(csData,bSub);break;

		case 0x6F34:
			pGroup=ExplainOTAPASPCData(csData,bSub);break;

		case 0x6F35:
			pGroup=ExplainNAMLOCKData(csData,bSub);break;

		case 0x6F36:

		case 0x6F37:
			pGroup=ExplainSPData(csData,bSub);break;

		case 0x6F38:
			pGroup=ExplainESNMEData(csData,bSub);break;

		case 0x6F39:

		case 0x6F3A:
			pGroup=Explain_LIData(csData,bSub);break;

		case 0x6F3B:
			pGroup=ExplainFDNData(csData,iRecord,bSub);break;

		case 0x6F3C:

		case 0x6F3D:

		case 0x6F3E:

		case 0x6F3F:
			pGroup=Explain_SSFCData(csData,bSub);break;

		case 0x6F41:
			pGroup=Explain_SPNData(csData,bSub);break;

		case 0x6F42:
			pGroup=Explain_USGINDData(csData,bSub);break;

		case 0x6F43:
			pGroup=Explain_ADData(csData,bSub);break;

		case 0x6F44:
			pGroup=Explain_MDNData(csData,bSub);break;

		case 0x6F45:
			pGroup=Explain_MAXPRLData(csData,bSub);break;

		case 0x6F46:
			pGroup=Explain_SPCSData(csData,bSub);break;

		case 0x6F47:
			pGroup=Explain_ECCData(csData,bSub);break;

		case 0x6F48:
			pGroup=Explain_ME3GPDOPCData(csData,bSub);break;

		case 0x6F49:
			pGroup=Explain_3GPDOPMData(csData,bSub);break;

		case 0x6F4A:
			pGroup=Explain_SIPCAPData(csData,bSub);break;

		case 0x6F4B:
			pGroup=Explain_MIPCAPData(csData,bSub);break;

		case 0x6F4C:
			pGroup=Explain_SIPUPPData(csData,bSub);break;

		case 0x6F4D:
			pGroup=Explain_MIPUPPData(csData,bSub);break;

		case 0x6F4E:
			pGroup=Explain_SIPSPData(csData,bSub);break;

		case 0x6F4F:
			pGroup=Explain_MIPSPData(csData,bSub);break;

		case 0x6F50:
			pGroup=Explain_SIPPAPSSData(csData,bSub);break;

		case 0x6F53:
			pGroup=Explain_PUZLData(csData,bSub);break;

		case 0x6F54:
			pGroup=Explain_MAXPUZLData(csData,bSub);break;

		case 0x6F55:
			pGroup=Explain_MECRPData(csData,bSub);break;

		case 0x6F56:
			pGroup=Explain_HRPDCAPData(csData,bSub);break;

		case 0x6F57:
			pGroup=Explain_HRPDUPPData(csData,bSub);break;

		case 0x6F58:
			pGroup=Explain_CSSPRData(csData,bSub);break;

		case 0x6F59:
			pGroup=Explain_ATData(csData,bSub);break;

		case 0x6F5A:
			pGroup=ExplainEPRLFileData(csData,bSub);break;

		case 0x6F5B:
			pGroup=Explain_BCSMScfgData(csData,bSub);break;

		case 0x6F5C:
			pGroup=Explain_BCSMSprefData(csData,bSub);break;

		case 0x6F5D:
			pGroup=Explain_BCSMStableData(csData,iRecord,bSub);break;

		case 0x6F5E:

			pGroup=Explain_BCSMSPData(csData,iRecord,bSub);break;

		case 0x6F63:

			pGroup=Explain_BAKPARAData(csData,iRecord,bSub);break;

		case 0x6F64:

			pGroup=Explain_UpBAKPARAData(csData,iRecord,bSub);break;

		case 0x6F65:

			pGroup=Explain_MMSNData(csData,iRecord,bSub);break;

		case 0x6F67:
			pGroup=Explain_MMSICPData(csData,bSub);break;

		case 0x6F68:
			pGroup=Explain_MMSUPData(csData,bSub);break;

		case 0x6F6D:
			pGroup=Explain_GID1Data(csData,bSub);break;

		case 0x6F6E:
			pGroup=Explain_GID2Data(csData,bSub);break;

		case 0x6F76:
			pGroup=Explain_SMSCAPData(csData,bSub);break;

		case 0x6F79:
			pGroup=Explain_TCPConfigData(csData,bSub);break;

		case 0x6F7A:
			pGroup=Explain_DGCData(csData,bSub);break;

		case 0x6F7B:pGroup=Explain_WAPBrowserCPCData(csData,bSub);break;

		case 0x6F7C:
			pGroup=Explain_WAPBrowserBMCData(csData,bSub);break;

		case 0x6F7D:
			pGroup=Explain_SIPUPPExtData(csData,bSub);break;

		case 0x6F7E:
			pGroup=Explain_MMSConfigData(csData,bSub);break;

		case 0x6F7F:
			pGroup=Explain_JDLData(csData,bSub);break;

		case 0x6F81:
			pGroup=Explain_BREWDownloadData(csData,bSub);break;

		case 0x6F82:
			pGroup=Explain_BREWTSIDData(csData,bSub);break;

		case 0x6F83:
			pGroup=Explain_BREWAEPData(csData,bSub);break;

		case 0x6F84:
			pGroup=Explain_LBSXTRAConfigData(csData,bSub);break;

		case 0x6F85:pGroup=Explain_LBSXSURLData(csData,bSub);break;
		case 0x6F86:pGroup=Explain_LBSV2ConfigData(csData,bSub);break;
		case 0x6F87:pGroup=Explain_LBSV2PDEADDRData(csData,bSub);break;
		case 0x6F88:pGroup=Explain_LBSV2MPCADDRData(csData,bSub);break;
		case 0x6F89:pGroup=Explain_BREWAEPData(csData,bSub);break;
		case 0x6F90:pGroup=Explain_ModelData(csData,bSub);break;
		case 0x6F92:pGroup=Explain_AppLabelsData(csData,bSub);break;
		default:break;
	}

	return pGroup;
}


CMFCPropertyGridProperty* Explain_FileData_In3GPP(CString csData,int iFID,int iRecord,BOOL bSub)
{
	CMFCPropertyGridProperty* pGroup = NULL;
	CString csRecord;

	if (iRecord <= 0)
		csRecord.Empty();
	else
		csRecord = Int2CStringDecimal(iRecord);


	switch (iFID)
	{
	case 0x0040:pGroup  = Explain_AUTHOPC(csData,bSub);break;
	case 0x0041:pGroup  = Explain_AUTHPAR(csData,bSub);break;
	case 0x6F05:pGroup  = ExplainLIData(csData,bSub);break;
	case 0x6F06:pGroup  = ExplainARRRecord(csData,iRecord,bSub);break;
	case 0x6F07:pGroup  = ExplainIMSIData(csData,bSub);break;
	case 0x6F08:pGroup  = ExplainKeysData(csData,bSub);break;
	case 0x6F09:pGroup  = ExplainKeysPSData(csData,bSub);break;
	case 0x6F2C:pGroup  = ExplainDCKData(csData,bSub);break;
	case 0x6F31:pGroup  = ExplainHPPLMNData(csData,bSub);break;
	case 0x6F32:pGroup  = ExplainCNLData(csData,bSub);break;
	case 0x6F37:pGroup  = ExplainACMmaxData(csData,bSub);break;;
	case 0x6F38:pGroup  = ExplainUSTData(csData,bSub);break;
	case 0x6F39:pGroup  = ExplainACMData(csData,iRecord,bSub);break;
	case 0x6F3B:pGroup  = ExplainFDNData(csData,iRecord,bSub);break;
	case 0x6F3C:pGroup  = ExplainSMSData(csData,iRecord,bSub);break;
	case 0x6F3E:break;
	case 0x6F3F:break;
	case 0x6F40:pGroup  = ExplainMSISDNData(csData,iRecord,bSub);break;
	case 0x6F41:break;
	case 0x6F42:pGroup  = ExplainSMSPData(csData,iRecord,bSub);break;
	case 0x6F43:pGroup  = ExplainSMSSData(csData,bSub);break;
	case 0x6F45:pGroup  = ExplainCBMIData(csData,bSub);break;
	case 0x6F46:pGroup  = ExplainSPNData(csData,bSub);break;
	case 0x6f47:pGroup  = ExplainSMSRData(csData,iRecord,bSub);break;
	case 0x6F48:pGroup  = ExplainCBMIDData(csData,bSub);break;
	case 0x6F49:pGroup  = ExplainSDNData(csData,iRecord,bSub);break;
	case 0x6F4B:pGroup  = ExplainEXTData(csData,iRecord,bSub);break;
	case 0x6F4C:pGroup  = ExplainEXTData(csData,iRecord,bSub);break;
	case 0x6F4D:pGroup  = ExplainBDNData(csData,iRecord,bSub);break;
	case 0x6F4E:pGroup  = ExplainEXTData(csData,iRecord,bSub);break;
	case 0x6F4F:pGroup  = ExplainCCP2Data(csData,iRecord,bSub);break;
	case 0x6F50:pGroup  = ExplainCBMIRData(csData,bSub);break;
	case 0x6F54:pGroup  = ExplainSUMEData(csData,bSub);break;
	case 0x6F55:pGroup  = ExplainEXTData(csData,iRecord,bSub);break;
	case 0x6F56:pGroup  = ExplainESTData(csData,bSub);break;
	case 0x6F57:pGroup  = ExplainACLData(csData,bSub);break;
	case 0x6F58:pGroup  = ExplainCMIData(csData,bSub);break;
	case 0x6F5B:pGroup  = ExplainSTARTHFNata(csData,bSub);break;
	case 0x6F5C:pGroup  = ExplainTHRESHOLData(csData,bSub);break;
	case 0x6F60:pGroup  = ExplainPLMNwAcTData(csData,bSub);break;
	case 0x6F61:pGroup  = ExplainOPLMNwACTData(csData,bSub);break;
	case 0x6F62:pGroup  = ExplainHPLMNwACTData(csData,bSub);break;
	case 0x6F73:pGroup  = ExplainPSLOCIData(csData,bSub);break;
	case 0x6F78:pGroup  = ExplainACCData(csData,bSub);break;
	case 0x6F7B:pGroup  = ExplainFPLMNData(csData,bSub);break;
	case 0x6F7E:pGroup  = ExplainLOCIData(csData,bSub);break;
	case 0x6F80:pGroup  = ExplainICIData(csData,iRecord,bSub);break;
	case 0x6F81:pGroup  = ExplainOCIData(csData,iRecord,bSub);break;
	case 0x6F82:pGroup  = ExplainICTData(csData,iRecord,bSub);break;
	case 0x6F83:pGroup  = ExplainOCTData(csData,iRecord,bSub);break;
	case 0x6FAD:pGroup  = ExplainADData(csData,bSub);break;
	case 0x6FB1:pGroup  = ExplainVGCSData(csData,bSub);break;
	case 0x6FB2:pGroup  = ExplainVGCSSData(csData,bSub);break;
	case 0x6FB3:pGroup  = ExplainVBSData(csData,bSub);break;
	case 0x6FB4:pGroup  = ExplainVBSSData(csData,bSub);break;
	case 0x6FB5:pGroup  = ExplaineMLPPData(csData,bSub);break;
	case 0x6FB6:pGroup  = ExplaineAAeMData(csData,bSub);break;
	case 0x6FB7:pGroup  = ExplainECCData(csData,iRecord,bSub);break;
	case 0x6FC3:pGroup  = ExplainHiddenkeyData(csData,bSub);break;
	case 0x6FC4:pGroup  = ExplainNETPARData(csData,bSub);break;
	case 0x6FC5:pGroup  = ExplainPNNData(csData,iRecord,bSub);break;
	case 0x6FC6:pGroup  = ExplainOPLData(csData,iRecord,bSub);break;
	case 0x6FC7:pGroup  = ExplainMBDNData(csData,iRecord,bSub);break;
	case 0x6FC8:pGroup  = ExplainEXTData(csData,iRecord,bSub);break;
	case 0x6FC9:pGroup  = ExplainMBIData(csData,iRecord,bSub);break;
	case 0x6FCA:pGroup  = ExplainMWISData(csData,iRecord,bSub);break;
	case 0x6FCB:pGroup  = ExplainCFISData(csData,iRecord,bSub);break;
	case 0x6FCC:pGroup  = ExplainEXTData(csData,iRecord,bSub);break;
	case 0x6FCD:pGroup  = ExplainSPDIData(csData,bSub);break;
	case 0x6FCE:pGroup  = ExplainMMSNData(csData,iRecord,bSub);break;
	case 0x6FCF:pGroup  = _ExplainEXTData(csData,iRecord);break;
	case 0x6FD0:pGroup  = ExplainMMSICPData(csData,bSub);break;
	case 0x6FD1:pGroup  = ExplainMMSUPData(csData,iRecord,bSub);break;
	case 0x6FD2:break;
	case 0x6FD3:pGroup  = ExplainNIAData(csData,iRecord,bSub);break;
	case 0x6FD4:pGroup  = ExplainVGCSCAData(csData,bSub);break;
	case 0x6FD5:pGroup  = ExplainVBSCAData(csData,bSub);break;
	case 0x6FD6:pGroup  = ExplainGBABPData(csData,bSub);break;
	case 0x6FD7:pGroup  = ExplainMSKData(csData,iRecord,bSub);break;
	case 0x6FD8:pGroup  = ExplainMUKData(csData,iRecord,bSub);break;;
	case 0x6FD9:pGroup  = ExplainEHPLMNData(csData,bSub);break;
	case 0x6FDA:pGroup  = ExplainGBANLData(csData,iRecord,bSub);break;
	case 0x6FDB:pGroup  = ExplainEHPLMNPIData(csData,bSub);break;
	case 0x6FDC:pGroup  = ExplainLRPLMNSIData(csData,bSub);break;
	case 0x6FDD:pGroup  = ExplainNAFKCAData(csData,iRecord,bSub);break;
	case 0x6FDE:pGroup  = ExplainSPNIData(csData,iRecord,bSub);break;
	case 0x6FDF:pGroup  = ExplainPNNIData(csData,iRecord,bSub);break;
	case 0x6FE0:pGroup  = ExplainICE_DNData(csData,iRecord,bSub);break;
	case 0x6FE1:pGroup  = ExplainICE_FFData(csData,iRecord,bSub);break;
	case 0x6FE2:pGroup  = ExplainNCP_IPData(csData,iRecord,bSub);break;
	case 0x6FE3:pGroup  = ExplainEPSLOCIData(csData,bSub);break;
	case 0x6FE4:pGroup  = ExplainEPSNSCData(csData,iRecord,bSub);break;
	default:break;
	}
	return pGroup;
}

CMFCPropertyGridProperty* Explain_FileData_In3GPP2(CString csData,int iFID,int iRecord,BOOL bSub)
{
	CMFCPropertyGridProperty* pGroup = NULL;

	switch (iFID)
	{
	case 0x6F06:pGroup  = ExplainARRRecord(csData,iRecord,bSub);break;
	case 0x6F21:pGroup=ExplainCOUNTData(csData,iRecord, TRUE);break;
	case 0x6F22:pGroup=ExplainIMSIMData(csData,bSub);break;
	case 0x6F23:pGroup=ExplainIMSITData(csData,bSub);break;
	case 0x6F24:pGroup=ExplainTMSIData(csData,bSub);break;
	case 0x6F25:pGroup=ExplainTMSIData(csData,bSub);break;
	case 0x6F26:pGroup=ExplainTMSIData(csData,bSub);break;
	case 0x6F27:pGroup=ExplainALOCData(csData,bSub);break;
	case 0x6F28:pGroup=ExplainSIDNIDData(csData,iRecord,bSub);break;
	case 0x6F29:pGroup=ExplainZNREGIData(csData,iRecord,bSub);break;
	case 0x6F2A:pGroup=ExplainSNREGIData(csData,bSub);break;
	case 0x6F2B:pGroup=ExplainDISTREGIIData(csData,bSub);break;
	case 0x6F2C:pGroup=ExplainACCOLCData(csData,bSub);break;
	case 0x6F2D:pGroup=ExplainTERMData(csData,bSub);break;
	case 0x6F2E:pGroup=ExplainSSCIData(csData,bSub);break;
	case 0x6F2F:pGroup=ExplainACPData(csData,bSub);break;
	case 0x6F30:pGroup=ExplainPRLFileData(csData,bSub);break;
	case 0x6F31:pGroup=ExplainUIMIDData(csData,bSub);break;
	case 0x6F32:pGroup=ExplainCSTData(csData,bSub);break;
	case 0x6F33:pGroup=ExplainSPCData(csData,bSub);break;
	case 0x6F34:pGroup=ExplainOTAPASPCData(csData,bSub);break;
	case 0x6F35:pGroup=ExplainNAMLOCKData(csData,bSub);break;
	case 0x6F36:pGroup=ExplainOTAData(csData,bSub);break;
	case 0x6F37:pGroup=ExplainSPData(csData,bSub);break;
	case 0x6F38:pGroup=ExplainESNMEData(csData,bSub);break;
	case 0x6F3A:pGroup=Explain_LIData(csData,bSub);break;
	case 0x6F3B:pGroup=ExplainFDNData(csData,iRecord,bSub);break;
	case 0x6F3C:break;
	case 0x6F3D:break;
	case 0x6F3E:break;
	case 0x6F3F:pGroup=Explain_SSFCData(csData,bSub);break;
	case 0x6F41:pGroup=Explain_SPNData(csData,bSub);break;
	case 0x6F42:pGroup=Explain_USGINDData(csData,bSub);break;
	case 0x6F43:pGroup=Explain_ADData(csData,bSub);break;
	case 0x6F44:pGroup=Explain_MDNData(csData,bSub);break;
	case 0x6F45:pGroup=Explain_MAXPRLData(csData,bSub);break;
	case 0x6F46:pGroup=Explain_SPCSData(csData,bSub);break;
	case 0x6F47:pGroup=Explain_ECCData(csData,bSub);break;
	case 0x6F48:pGroup=Explain_ME3GPDOPCData(csData,bSub);break;
	case 0x6F49:pGroup=Explain_3GPDOPMData(csData,bSub);break;
	case 0x6F4A:pGroup=Explain_SIPCAPData(csData,bSub);break;
	case 0x6F4B:pGroup=Explain_MIPCAPData(csData,bSub);break;
	case 0x6F4C:pGroup=Explain_SIPUPPData(csData,bSub);break;
	case 0x6F4D:pGroup=Explain_MIPUPPData(csData,bSub);break;
	case 0x6F4E:pGroup=Explain_SIPSPData(csData,bSub);break;
	case 0x6F4F:pGroup=Explain_MIPSPData(csData,bSub); 	break;
	case 0x6F50:pGroup=Explain_SIPPAPSSData(csData,bSub); 	break;
	case 0x6F53:pGroup=Explain_PUZLData(csData,bSub); break;
	case 0x6F54:pGroup=Explain_MAXPUZLData(csData,bSub); break;
	case 0x6F55:pGroup=Explain_MECRPData(csData,bSub); break;
	case 0x6F56:pGroup=Explain_HRPDCAPData(csData,bSub); break;
	case 0x6F57:pGroup=Explain_HRPDUPPData(csData,bSub); 	break;
	case 0x6F58:pGroup=Explain_CSSPRData(csData,bSub); 	break;
	case 0x6F59:pGroup=Explain_ATData(csData,bSub); break;
	case 0x6F5A:pGroup=ExplainEPRLFileData(csData,bSub); break;
	case 0x6F5B:pGroup=Explain_BCSMScfgData(csData,bSub); break;
	case 0x6F5C:pGroup=Explain_BCSMSprefData(csData,bSub); break;
	case 0x6F5D:pGroup=Explain_BCSMStableData(csData,iRecord,bSub);
	case 0x6F5E:pGroup=Explain_BCSMSPData(csData,iRecord,bSub);
	case 0x6F63:pGroup=Explain_BAKPARAData(csData,iRecord,bSub);break;
	case 0x6F64:pGroup=Explain_UpBAKPARAData(csData,iRecord,bSub);break;
	case 0x6F65:pGroup=Explain_MMSNData(csData,iRecord,bSub);break;
	case 0x6F66:pGroup=ExplainEXTData(csData,iRecord,bSub);break;
	case 0x6F67:pGroup=Explain_MMSICPData(csData,bSub); break;
	case 0x6F68:pGroup=Explain_MMSUPData(csData,bSub); break;
	case 0x6F69:pGroup=Explain_MMSUCPData(csData,bSub); break;
	case 0x6F6A:pGroup=Explain_AuthCapabilityData(csData,iRecord,bSub);break;
	case 0x6F6B:pGroup=Explain_3GCIKData(csData,bSub); break;
	case 0x6F6C:pGroup=Explain_DCKData(csData,bSub); break;
	case 0x6F6D:pGroup=Explain_GID1Data(csData,bSub); break;
	case 0x6F6E:pGroup=Explain_GID2Data(csData,bSub); break;
	case 0x6F6F:pGroup=Explain_CDMACNLData(csData,bSub); break;
	case 0x6F70:pGroup=Explain_HOMETAGData(csData,bSub);break;
	case 0x6F71:pGroup=Explain_GROUPTAGData(csData,bSub);break;
	case 0x6F72:pGroup=Explain_SPECIFICTAGData(csData,bSub);break;
	case 0x6F73:pGroup=Explain_CallPromptData(csData,bSub);break;
	case 0x6F74:pGroup=Explain_SFEUIMIDData(csData,bSub);break;
	case 0x6F75:pGroup=ExplainESTData(csData,bSub);break;
	case 0x6F76:pGroup=ExplainHiddenkeyData(csData,bSub);break;
	case 0x6F77:pGroup=Explain_LCSVERData(csData,bSub);break;
	case 0x6F78:pGroup=Explain_LCSCPData(csData,bSub);break;
	case 0x6F79:pGroup=ExplainSDNData(csData,iRecord,bSub);break;
	case 0x6F7A:pGroup=ExplainEXTData(csData,iRecord,bSub);break;
	case 0x6F7B:pGroup=ExplainEXTData(csData,iRecord,bSub);break;
	case 0x6F7C:pGroup=ExplainICIData(csData,iRecord,bSub);break;
	case 0x6F7D:pGroup=ExplainOCIData(csData,iRecord,bSub);break;
	case 0x6F7E:pGroup=ExplainEXTData(csData,iRecord,bSub);break;
	case 0x6F7F:pGroup=ExplainCCP2Data(csData,iRecord,bSub);break;
	case 0x6F80:pGroup=Explain_AppLabelsData(csData,bSub);break;
	case 0x6F81:pGroup=Explain_ModelData(csData,bSub);break;
	case 0x6F82:pGroup=Explain_RCData(csData,bSub);break;
	case 0x6F83:pGroup=Explain_SMSCAPData(csData,bSub);break;
	case 0x6F84:pGroup=Explain_MIPFlagsData(csData,bSub);break;
	case 0x6F85:pGroup=Explain_SIPUPPExtData(csData,bSub);break;
	case 0x6F86:pGroup=Explain_MIPUPPExtData(csData,bSub);break;
	case 0x6F87:pGroup=Explain_IPV6CAPData(csData,bSub);break;
	case 0x6F88:pGroup=Explain_TCPConfigData(csData,bSub);break;
	case 0x6F89:pGroup=Explain_DGCData(csData,bSub);break;
	case 0x6F8A:pGroup=Explain_WAPBrowserCPCData(csData,bSub);break;
	case 0x6F8B:pGroup=Explain_WAPBrowserBMCData(csData,bSub);break;
	case 0x6F8C:pGroup=Explain_MMSConfigData(csData,bSub);break;
	case 0x6F8D:pGroup=Explain_JDLData(csData,bSub);break;
	case 0x6F8E:pGroup=Explain_LBSXTRAConfigData(csData,bSub);break	;
	case 0x6F8F:pGroup=Explain_LBSXSURLData(csData,bSub);break	;
	case 0x6F90:pGroup=Explain_LBSV2ConfigData(csData,bSub);break	;
	case 0x6F91:pGroup=Explain_LBSV2PDEADDRData(csData,bSub);break	;
	case 0x6F92:pGroup=Explain_LBSV2MPCADDRData(csData,bSub);	break	;
	case 0x6F93:pGroup=Explain_BREWDownloadData(csData,bSub);	break	;
	case 0x6F94:pGroup=Explain_BREWTSIDData(csData,bSub);break;
	case 0x6F95:pGroup=Explain_BREWSIDData(csData,bSub);break;
	case 0x6F96:pGroup=Explain_BREWAEPData(csData,bSub);break;
	default:break;
	}

	return pGroup;
}


CMFCPropertyGridProperty* Explain_FileData(CString csData,int iFile,int iMark)
{
	CMFCPropertyGridProperty* pGroup;


	switch(iMark)
	{
	case _DEF_Card:pGroup = Explain_FileData_InMF(csData,iFile,0,FALSE);break;
	case _DEF_3GPP:
	case _DEF_ETSI :pGroup = Explain_FileData_In3GPP(csData,iFile,0,FALSE);break;
	case _DEF_3GPP2:pGroup = Explain_FileData_In3GPP2(csData,iFile,0,FALSE);break;
	case _DEF_GSM:  pGroup = Explain_FileData_InGSM(csData,iFile,0,FALSE);break;
	case _DEF_CDMA:  pGroup = Explain_FileData_InCDMA(csData,iFile,0,FALSE);break;
	case _DEF_Tele: pGroup = Explain_FileData_InTelecom(csData,iFile,0,FALSE);break;
	case _DEF_MMSS: pGroup = Explain_FileData_InMMSS(csData,iFile,0,FALSE);break;
	case _DEF_GSMACCESS:  pGroup = Explain_FileData_InGSMACCESS(csData,iFile,0,FALSE);break;
	case _DEF_PHONEBOOK:  pGroup = Explain_FileData_InPhoneBook(csData,iFile,0,FALSE);break;
	}


	return pGroup;
}


//只用于展开解释器里面
BOOL ExpandChildProperty(CMFCPropertyGridProperty* Prop)
{
	CMFCPropertyGridProperty * Prop1;
	int iSum = Prop ->GetSubItemsCount();

	if (iSum == 1)
	{
		for (int i = 0 ; i < iSum ; i++)
		{
			Prop1 = Prop->GetSubItem(i);
			if ((Prop1->GetSubItemsCount()>0))
				Prop1->Expand();
		}
	}



	return TRUE;
}

BOOL EnableProperty(CMFCPropertyGridProperty* pGrop,BOOL bEnable)
{
	BOOL bRet = TRUE;
	int iSubItemSum;

	iSubItemSum = pGrop->GetSubItemsCount();

	for (int i = 0 ; i <iSubItemSum; i++ )
		bRet &= EnableProperty(pGrop->GetSubItem(i),bEnable);

	 pGrop->Enable(bEnable);

	return bRet;
}


//以下为Compile 文件内容


BOOL ComplileFileData(CMFCPropertyGridProperty* pGrop,int iFID,int iMark,CString &csFileData,int* iOutputLen)
{
	BOOL bRet = FALSE;
	switch(iFID)
	{
	case 0x2F00: bRet = ComplileDIRData(pGrop,csFileData);break;
	case 0x2F05: bRet = ComplileBasicData(pGrop,csFileData);break;
	case 0x6F05: bRet = ComplileBasicData(pGrop,csFileData);break;
	case 0x6F07: bRet = ComplileIMSIData(pGrop,csFileData);break;

	case 0x6F08: 
	case 0x6F09: 
		if ((iMark == _DEF_3GPP)
		||(iMark == _DEF_ETSI))	
			bRet = ComplileBasicData(pGrop,csFileData);break;

	case 0x6F38:
		if ((iMark == _DEF_3GPP)
		||(iMark == _DEF_ETSI))	
			bRet = ComplileUSTData(pGrop,csFileData);
		else if (iMark== _DEF_GSM)
			bRet = ComplileSSTData(pGrop,csFileData);
		break;

	case 0x6F3A:
	case 0x6F3B:
	case 0x6F40:
	case 0x6F44:
	case 0x6F49:
	case 0x6F4D:
		if ((iMark == _DEF_3GPP)
			||(iMark == _DEF_ETSI)
			||(iMark == _DEF_Tele))	

		{
			if (iOutputLen == NULL)
				bRet = _ComplileADNData(pGrop,csFileData,28);
			else
				bRet = _ComplileADNData(pGrop,csFileData,*iOutputLen);
		}

		break;

	case 0x6F42:
		if (iOutputLen == NULL)
			bRet = ComplileSMSPData(pGrop,csFileData,0x28);
		else
			bRet = ComplileSMSPData(pGrop,csFileData,*iOutputLen);
		break;
	case 0x6F43:
		if ((iMark == _DEF_Tele)
			||(iMark == _DEF_3GPP)
			||(iMark == _DEF_ETSI))	
			bRet = ComplileSMSSData(pGrop,csFileData);break;

	case 0x6F46:

		if ((iMark == _DEF_Tele)
			||(iMark == _DEF_3GPP)
			||(iMark == _DEF_ETSI))	
			bRet = ComplileSPNData(pGrop,csFileData);break;
	case 0x6F47:

		if ((iMark == _DEF_GSM)
			||(iMark == _DEF_Tele)
			||(iMark == _DEF_3GPP)
			||(iMark == _DEF_ETSI))	
			bRet = ComplileBasicData(pGrop,csFileData);break;

	case 0x6F4A:
	case 0x6F4B:
	case 0x6F4E:
		if ((iMark == _DEF_3GPP)
			||(iMark == _DEF_ETSI)
			||(iMark == _DEF_Tele))	
			bRet = ComplileEXTData(pGrop,csFileData);break;

	case 0x6F56:

		if ((iMark == _DEF_GSM)
			||(iMark == _DEF_3GPP)
			||(iMark == _DEF_ETSI))	
			bRet = ComplileESTData(pGrop,csFileData);break;

	case 0x6F60:
		if ((iMark == _DEF_GSM)
			||(iMark == _DEF_3GPP)
			||(iMark == _DEF_ETSI))	
			bRet =_ComplilePLMNData(pGrop,csFileData);break;
	case 0x6F61:
		if ((iMark == _DEF_GSM)
			||(iMark == _DEF_3GPP)
			||(iMark == _DEF_ETSI))	
			bRet =_ComplilePLMNData(pGrop,csFileData);break;
	case 0x6F62:
		if ((iMark == _DEF_GSM)
			||(iMark == _DEF_3GPP)
			||(iMark == _DEF_ETSI))	
			bRet =_ComplilePLMNData(pGrop,csFileData);break;

		

	case 0x6F7E:
		if ((iMark == _DEF_GSM)
			||(iMark == _DEF_3GPP)
			||(iMark == _DEF_ETSI))	
			bRet = ComplileLOCIData(pGrop,csFileData);break;

	case 0x6FC5:

		if ((iMark == _DEF_3GPP)
			||(iMark == _DEF_ETSI))	
			bRet = ComplilePNNData(pGrop,csFileData);break;
	
	case 0x2F06:
	case 0x6F06:
	case 0x4F06: bRet = ComplileARRRecord(pGrop,csFileData); break;
	case 0x4F30:
		if (iMark == _DEF_PHONEBOOK)
			bRet =  ComplilePBRData(pGrop,csFileData);
		break;

	default:break;

	}

	if (!_IsAllHex(csFileData))
	{
		csFileData.Empty();
		bRet = FALSE;
	}

	return bRet;


}

BOOL GridPropertyIsChanged(CMFCPropertyGridProperty* pGrop)
{
	int iSubItem,iTemp;
	BOOL bRet = FALSE;

	iSubItem = pGrop->GetSubItemsCount();

	if (iSubItem == 0)
	{
		if (pGrop->GetValue() == pGrop->GetOriginalValue())
			return TRUE;
	}

	for (iTemp = 0 ; iTemp < iSubItem ; iTemp++)
		bRet |= GridPropertyIsChanged(pGrop->GetSubItem(iTemp));


	return bRet;
}

BOOL ComplileARRRecord(CMFCPropertyGridProperty* pGrop,CString &csARR)
{
	BOOL bRet;
	CString csTempARR;
	csARR.Empty();
	bRet = GridPropertyIsChanged(pGrop);

	if (bRet == FALSE)
		return FALSE;

	if (GenerateACDataByAC(pGrop,_T("9000"),_T("ALWAYS"),csTempARR))
		csARR += csTempARR;

	if (GenerateACDataByAC(pGrop,_T("A406830101950108"),_T("PIN 01"),csTempARR))
		csARR += csTempARR;


	if (GenerateACDataByAC(pGrop,_T("A406830181950108"),_T("PIN 81"),csTempARR))
		csARR += csTempARR;


	if (GenerateACDataByAC(pGrop,_T("A40683010A950108"),_T("PIN 0A"),csTempARR))
		csARR += csTempARR;

	if (GenerateACDataByAC(pGrop,_T("A010A406830101950108A406830181950108"),_T("PIN 01|PIN 81"),csTempARR))
		csARR += csTempARR;

	if (GenerateACDataByAC(pGrop,_T("A010A406830101950108A40683010A950108"),_T("PIN 01|PIN 0A"),csTempARR))
		csARR += csTempARR;

	if (GenerateACDataByAC(pGrop,_T("A010A406830181950108A406830181950108"),_T("PIN 81|PIN 0A"),csTempARR))
		csARR += csTempARR;

	if (GenerateACDataByAC(pGrop,_T("A018A406830101950108A406830181950108A406830181950108"),_T("PIN 01|PIN 81|PIN 0A"),csTempARR))
		csARR += csTempARR;

	if (GenerateACDataByAC(pGrop,_T("AF10A406830101950108A406830181950108"),_T("PIN 01&PIN 81"),csTempARR))
		csARR += csTempARR;

	if (GenerateACDataByAC(pGrop,_T("AF10A406830101950108A40683010A950108"),_T("PIN 01&PIN 0A"),csTempARR))
		csARR += csTempARR;

	if (GenerateACDataByAC(pGrop,_T("AF10A406830181950108A406830181950108"),_T("PIN 81&PIN 0A"),csTempARR))
		csARR += csTempARR;

	if (GenerateACDataByAC(pGrop,_T("AF18A406830101950108A406830181950108A406830181950108"),_T("PIN 01&PIN 81&PIN 0A"),csTempARR))
		csARR += csTempARR;




	if (GenerateCommandAC(pGrop,_T("INCREASE"),0x32,csTempARR))
		csARR += csTempARR;

	if (GenerateCommandAC(pGrop,_T("AUTHENTICATE"),0x88,csTempARR))
		csARR += csTempARR;

	if (GenerateACDataByAC(pGrop,_T("9700"),_T("NEVER"),csTempARR))
		csARR += csTempARR;


	return bRet;
}

BOOL TransationACName2Data(CString csACName,CString& csARR)
{
	csARR.Empty();
	if (csACName == _T("ALWAYS"))
		csARR = _T("9000");
	if (csACName == _T("PIN 01"))
		csARR = _T("A406830101950108");
	if (csACName == _T("PIN 81"))
		csARR = _T("A406830181950108");
	if (csACName == _T("PIN 0A"))
		csARR = _T("A40683010A950108");
	if (csACName == _T("PIN 01|PIN 81"))
		csARR = _T("A010A406830101950108A406830181950108");
	if (csACName == _T("PIN 01|PIN 0A"))
		csARR = _T("A010A406830101950108A40683010A950108");
	if (csACName == _T("PIN 81|PIN 0A"))
		csARR = _T("A010A406830181950108A406830181950108");
	if (csACName == _T("PIN 01|PIN 81|PIN 0A"))
		csARR = _T("A018A406830101950108A406830181950108A406830181950108");
	if (csACName == _T("PIN 01&PIN 81"))
		csARR = _T("AF10A406830101950108A406830181950108");
	if (csACName == _T("PIN 01&PIN 0A"))
		csARR = _T("AF10A406830101950108A40683010A950108");
	if (csACName == _T("PIN 81&PIN 0A"))
		csARR = _T("AF10A406830181950108A406830181950108");
	if (csACName == _T("PIN 01&PIN 81&PIN 0A"))
		csARR = _T("AF18A406830101950108A406830181950108A406830181950108");

	if (csARR.IsEmpty())
		return FALSE;
	else
		return TRUE;

}

BOOL GenerateCommandAC( CMFCPropertyGridProperty* pGrop,CString csCommandName,int iIns,CString& csARR )
{
	int iSum;
	CString csName,csValue;
	CMFCPropertyGridProperty* pSubItem;
	csARR.Empty();
	//标题不是ARR 则返回
	csName = pGrop->GetName();
	if(csName!= _T("ARR"))
		return FALSE;

	iSum = pGrop->GetSubItemsCount();


	for (int i = 0 ; i< iSum ; i++)
	{
		pSubItem = pGrop->GetSubItem(i);
		csName   = pSubItem->GetName();
		csValue  = pSubItem->GetValue();

		if (csCommandName == csName)
		{
			if (TransationACName2Data(csValue,csARR))
				csARR = GenerateTLVData(Int2CString(iIns,02),0x84)+csARR;	
		}
	}
	if (csARR.IsEmpty())
		return FALSE;
	else
		return TRUE;
}

BOOL GenerateACDataByAC(CMFCPropertyGridProperty* pGrop,CString csACValue,CString csAC,CString& csARR)
{
	int iSum,iCommand; 
	CString csName,csValue;
	CMFCPropertyGridProperty* pSubItem;

	csARR.Empty();
	iSum = pGrop->GetSubItemsCount();
	//小于七个判断不是ARR
	if (iSum < 7)
		return FALSE;
	//标题不是ARR 则返回
	csName = pGrop->GetName();
	if(csName!= _T("ARR"))
		return FALSE;



	iCommand = 0;


	for (int i = 0 ; i< 7 ; i++)
	{
		pSubItem = pGrop->GetSubItem(i);

		csName   = pSubItem->GetName();
		csValue  = pSubItem->GetValue();

		if (csAC == csValue )
			iCommand += (int)1 << i;		
	}

	if (iCommand != 0)
	{
		csARR = _T("8001")+Int2CString(iCommand,2);
		csARR = csARR + csACValue;
		return TRUE;
	}

	return FALSE;

}

BOOL ComplilePBRData(CMFCPropertyGridProperty* pGrop,CString &csPBR)
{
	
	CMFCPropertyGridProperty* pSubItem;
	CMFCPropertyGridProperty* pSubItem1;
	CString csFIDValue,csSFIValue,csA8Data,csA9Data,csAAData;
	int iA8Tag[8] = {0xC0,0xC1,0xC3,0xC4,0xC5,0xC6,0xC9,0xCA};
	int iA9Tag[3] = {0xC3,0xC4,0xCA};
	int iAATag[4] = {0xC2,0xC7,0xC8,0xCB};
	int iSum,i;
	csPBR.Empty();
	iSum = pGrop->GetSubItemsCount();

	if (iSum != 3)
		return FALSE;



	//Type1
	pSubItem = pGrop->GetSubItem(0);
	iSum = pSubItem->GetSubItemsCount() ;

	if (iSum != 8)
		return FALSE;

	csA8Data.Empty();

	for ( i = 0 ; i < iSum ; i ++)
	{
		pSubItem1   = pSubItem->GetSubItem(i);
		csFIDValue  = pSubItem1->GetSubItem(0)->GetValue();
		csSFIValue  = pSubItem1->GetSubItem(1)->GetValue();
		if (!csFIDValue.IsEmpty())
			csA8Data = csA8Data+GenerateTLVData(csFIDValue+csSFIValue,iA8Tag[i]);
		
	}

	csPBR = csPBR + GenerateTLVData(csA8Data,0xA8);



	//Type2
	pSubItem = pGrop->GetSubItem(1);
	iSum = pSubItem->GetSubItemsCount() ;

	if (iSum != 3)
		return FALSE;

	csA9Data.Empty();

	for ( i = 0 ; i < iSum ; i ++)
	{
		pSubItem1   = pSubItem->GetSubItem(i);
		csFIDValue  = pSubItem1->GetSubItem(0)->GetValue();
		csSFIValue  = pSubItem1->GetSubItem(1)->GetValue();
		if (!csFIDValue.IsEmpty())
			csA9Data = csA9Data+GenerateTLVData(csFIDValue+csSFIValue,iA9Tag[i]);

	}

	csPBR = csPBR + GenerateTLVData(csA9Data,0xA9);




	//Type3
	pSubItem = pGrop->GetSubItem(2);
	iSum = pSubItem->GetSubItemsCount() ;

	if (iSum != 4)
		return FALSE;

	for ( i = 0 ; i < iSum ; i ++)
	{
		pSubItem1   = pSubItem->GetSubItem(i);
		csFIDValue  = pSubItem1->GetSubItem(0)->GetValue();
		csSFIValue  = pSubItem1->GetSubItem(1)->GetValue();
		if (!csFIDValue.IsEmpty())
			csAAData = csAAData+GenerateTLVData(csFIDValue+csSFIValue,iAATag[i]);

	}

	csPBR = csPBR + GenerateTLVData(csAAData,0xAA);



	return TRUE;
}

BOOL ComplileDIRData(CMFCPropertyGridProperty* pGrop,CString &csDIR)
{

	int iSubItemSum;
	CString csValue;

	iSubItemSum = pGrop ->GetSubItemsCount();
	if (iSubItemSum != 2)
		return FALSE;

	csValue = pGrop->GetSubItem(0)->GetValue();
	csDIR   = GenerateTLVData(csValue,0x4F);
	csValue = pGrop->GetSubItem(1)->GetValue();
	csDIR  += GenerateTLVData(ConvertAscii(csValue),0x50);
	csDIR   = GenerateTLVData(csDIR,0x61);
	return TRUE;
}

BOOL ComplileBasicData(CMFCPropertyGridProperty* pGrop,CString &csBasicData)
{
	int iSubItemSum;
	CString csValue;
	csValue.Empty();

	iSubItemSum = pGrop->GetSubItemsCount();

	for (int i=0; i < iSubItemSum;i++)
	{
		csValue = pGrop->GetSubItem(i)->GetValue();
		csBasicData += csValue;
	}

	return TRUE;
}

BOOL ComplileIMSIData(CMFCPropertyGridProperty* pGrop,CString &csIMSI)
{
	BOOL bRet ;

	bRet = ComplileBasicData(pGrop,csIMSI);

	if ((bRet)&&(csIMSI.GetLength() == 15)&&(_IsAllHex(csIMSI)))
	{
		csIMSI = _T("9")+ csIMSI;
		csIMSI = _T("08")+ ExchangeAt(csIMSI);
		return TRUE; 
	}
	else 
		return FALSE; 


}


BOOL ComplileUSTData(CMFCPropertyGridProperty* pGrop,CString &csUST)
{

	int iSum,iUSTLen;
	bool bRet ;
	iSum    = pGrop->GetSubItemsCount();

	iUSTLen = iSum/8 + (((iSum%8) == 0 )?0:1);


	csUST = RepeatCString(_T("00"),iUSTLen);

	for (int i = 1; i<= iSum ; i++)
	{
		if( (CString)pGrop->GetSubItem(i-1)->GetValue() == _T("Supported"))
			bRet = Setbit(csUST,i,true);
		else
			bRet = Setbit(csUST,i,false);

		 
	}

	return (BOOL)bRet;

}


BOOL ComplileSSTData(CMFCPropertyGridProperty* pGrop,CString &csSST)
{

	int iSum,iSSTLen;
	CString csValue;
	bool bRet ;
	iSum    = pGrop->GetSubItemsCount();

	iSSTLen = iSum/4 + (((iSum%4) == 0 )?0:1);


	csSST = RepeatCString(_T("00"),iSSTLen);

	for (int i = 1; i<= iSum ; i++)
	{
		csValue = pGrop->GetSubItem(i-1)->GetValue();

		if (csValue.Left(9) == _T("Allocated"))
			bRet = Setbit(csSST,2*i-1,true);
		else
			bRet = Setbit(csSST,2*i-1,false);


		if (csValue.Right(9) == _T("Activated"))
			bRet = Setbit(csSST,2*i,true);
		else
			bRet = Setbit(csSST,2*i,false);
	 
	}

	return (BOOL)bRet;

}



BOOL _ComplileADNData(CMFCPropertyGridProperty* pGrop,CString &csADN,int iADNLen)
{
	CString csAlpha,csNumber,csCRI,csERI;
	int iSum = pGrop->GetSubItemsCount();

	if (iSum != 4) 
		return FALSE;

	//生成 Alpha

	csAlpha  = pGrop->GetSubItem(0)->GetValue();
	csNumber = pGrop->GetSubItem(1)->GetValue();
	csCRI    = pGrop->GetSubItem(2)->GetValue();
	csERI    = pGrop->GetSubItem(3)->GetValue();

	_Genrate80ADN(csAlpha,iADNLen - 14,csNumber,csADN);

	csADN = csADN.Left(iADNLen*2-4)+csCRI+csERI;


	return TRUE;
}

BOOL ComplileSPNData(CMFCPropertyGridProperty* pGrop,CString &csSPN)
{
	CString csDC;
	CString csValue;

	if (pGrop->GetSubItemsCount() != 2)
		return FALSE;

	csDC    = pGrop->GetSubItem(0)->GetValue();
	csValue = pGrop->GetSubItem(1)->GetValue();

	if (_IsAllAscii(csValue))
		csSPN = ConvertAscii(csValue);
	else
		csSPN = _T("80")+ConvertUcs2(csValue);

	csSPN = csDC+csSPN;
	return TRUE;
}



BOOL ComplilePNNData(CMFCPropertyGridProperty* pGrop,CString &csPNN)
{

	int iSum = pGrop->GetSubItemsCount();

	if (iSum != 3) 
		return FALSE;
	CString csTemp;
	CString csCbits;
	csPNN.Empty();

	csTemp = pGrop->GetSubItem(0)->GetValue();
	if (!csTemp.IsEmpty())
	{
		if (_IsAllAscii(csTemp))
		{
			csCbits = Int2CString(0x80+csTemp.GetLength()%8,02);
			csTemp = Convert7bit(csTemp);
			csTemp = csCbits +csTemp;
		}
		else
			csTemp = _T("10")+ConvertUcs2(csTemp);

		csPNN += GenerateTLVData(csTemp,0x43) ;

	}

	csTemp = pGrop->GetSubItem(1)->GetValue();
	if (!csTemp.IsEmpty())
	{
		if (_IsAllAscii(csTemp))
		{
			csCbits = Int2CString(0x80+csTemp.GetLength()/2%8,02);
			csTemp = Convert7bit(csTemp);
			csTemp = csCbits +csTemp;
		}
		else
			csTemp = _T("10")+ConvertUcs2(csTemp);

		csPNN += GenerateTLVData(csTemp,0x45) ;

	}		
	csTemp = pGrop->GetSubItem(2)->GetValue();
	if (!csTemp.IsEmpty())
	{
		if (_IsAllAscii(csTemp))
		{

			csCbits = Int2CString(0x80+csTemp.GetLength()/2%8,02);
			csTemp = Convert7bit(csTemp);	
			csTemp = csCbits +csTemp;
		}
		else
			csTemp = _T("10")+ConvertUcs2(csTemp);

		csPNN += GenerateTLVData(csTemp,0x50) ;

	}	


	return TRUE;

}


BOOL ComplileSMSPData(CMFCPropertyGridProperty* pGrop,CString &csSMSP,int iSMSPLen)
{

	int iSum = pGrop->GetSubItemsCount();

	if (iSum != 6) 
		return FALSE;

	CString csAlpha,csADN,csTemp2,csTemp3,csTemp4,csTemp5;

	csSMSP.Empty();

	csAlpha = pGrop->GetSubItem(0)->GetValue();
	if (!csAlpha.IsEmpty())
	{
		csAlpha = _T("80")+ConvertUcs2(csAlpha);
		csAlpha = csAlpha +  RepeatCString(_T("FF"),iSMSPLen - 28);
		csAlpha = csAlpha.Left(iSMSPLen*2 - 56);


	}else
		csAlpha = RepeatCString(_T("FF"),iSMSPLen - 28);

	csADN   = pGrop->GetSubItem(1)->GetValue();
	csTemp2 = pGrop->GetSubItem(2)->GetValue();
	csTemp3 = pGrop->GetSubItem(3)->GetValue();
	csTemp4 = pGrop->GetSubItem(4)->GetValue();
	csTemp5 = pGrop->GetSubItem(5)->GetValue();

	_ConvertSMSP(csAlpha,csADN,csTemp2,csTemp3,csTemp4,csTemp5,csSMSP);

	return TRUE;

}


BOOL ComplileMIDData(CMFCPropertyGridProperty* pGrop,CString &csMID)
{
	CString csTemp,csLen,csType;
	int iType;
	if (pGrop->GetSubItemsCount() != 5)
		return FALSE;
	iType = 7;
	csTemp = pGrop->GetSubItem(0)->GetValue();

	csTemp = FormatCString(csTemp,2);

	csMID  = csTemp;


	csTemp = pGrop->GetSubItem(4)->GetValue();

	csLen  = Int2CString(csTemp.GetLength(),02);

	//csType = pGrop->GetSubItem(2)->GetValue();

	//iProSum= pGrop->GetSubItem(2)->GetOptionCount();
	//for (int i = 0 ; i<iProSum ;i++ )
	//{
	//	if (csType == pGrop->GetSubItem(2)->GetOption(i))
	//		iType = i;	
	//}

	iType = IndexInOption(pGrop->GetSubItem(2));

	if ((iType >4)||(iType<0))
		iType = 7;

	if (CalculateOddEvenIndication(csTemp))
		iType =iType+0x8;

	csTemp = ExchangeAt(Int2CString(iType,1)+csTemp);

	csMID = csMID+csLen + csTemp;

	return TRUE;
}

BOOL ComplileLAIData(CMFCPropertyGridProperty* pGrop,CString &csLIA)
{
	CString csTemp;
	if (pGrop->GetSubItemsCount() != 2)
		return FALSE;

	csTemp = pGrop->GetSubItem(0)->GetValue();


	csLIA = ConvertMCCMNC(csTemp.Left(03),csTemp.Mid(03));

	csLIA = csLIA+ FormatCString((CString)pGrop->GetSubItem(1)->GetValue(),4);

	return TRUE;
}


BOOL ComplileLOCIData(CMFCPropertyGridProperty* pGrop,CString &csLOCI)
{
	CString csTemp;
	int iStatus = 0xFF;

	if (pGrop->GetSubItemsCount() != 4)
		return FALSE;

	//if (!ComplileMIDData(pGrop->GetSubItem(0),csTemp))
	//	return FALSE;

	csTemp = pGrop->GetSubItem(0)->GetValue();
	
	csLOCI = csTemp;

	if (!ComplileLAIData(pGrop->GetSubItem(1),csTemp))
		return FALSE;

	csLOCI = csLOCI+csTemp;

	//RFU
	csLOCI = csLOCI+_T("FF");

	//int iProSum = pGrop->GetSubItem(3)->GetOptionCount();

	//csTemp = pGrop->GetSubItem(3)->GetValue();
	//for (int i =0 ; i < iProSum; i++)
	//{
	//	if (csTemp == pGrop->GetSubItem(3)->GetOption(i))
	//		iStatus = i;	
	//}

	iStatus = IndexInOption(pGrop->GetSubItem(3));

	if ((iStatus>3)||(iStatus<0))
		iStatus = 0xFF;

	csLOCI = csLOCI + Int2CString(iStatus,2);


	return TRUE;





}

BOOL ComplileSMSSData(CMFCPropertyGridProperty* pGrop,CString &csSMSS)
{
	if (pGrop->GetSubItemsCount() != 2)
		return FALSE;
	csSMSS = FormatCString((CString)pGrop->GetSubItem(0)->GetValue(),2);

	if (IndexInOption(pGrop->GetSubItem(1)) == 0)
		csSMSS = csSMSS+_T("FE");
	else
		csSMSS = csSMSS+_T("FF");

	return TRUE;
}


BOOL ComplileESTData(CMFCPropertyGridProperty* pGrop,CString &csEST)
{
	csEST = _T("00");
	BOOL bRet;

	if (pGrop ->GetSubItemsCount() != 3)
	{
		return FALSE;
	}

	for (int i = 0 ; i <3 ; i++)
	{
		if ((CString)pGrop->GetSubItem(i)->GetValue() ==(CString)pGrop->GetSubItem(i)->GetOption(0))
			bRet = Setbit(csEST,i+1,false);
		else
			bRet = Setbit(csEST,i+1,true);
	}
	return bRet;
}


BOOL ComplileEXTData(CMFCPropertyGridProperty* pGrop,CString &csEXT)
{
	int iRet;
	CString csTemp;
	if (pGrop->GetSubItemsCount() != 3)
		return FALSE;

	csEXT.Empty();

	iRet = IndexInOption(pGrop->GetSubItem(0));

	if ((iRet < 0)||(iRet>=3))
		iRet = 0xFF;
	csEXT = Int2CString(iRet,02);


	csTemp = pGrop->GetSubItem(1)->GetValue();

	csEXT = csEXT+ FormatCString(csTemp,22);

	csTemp = pGrop->GetSubItem(2)->GetValue();

	csEXT =csEXT+ FormatCString(csTemp,02);


	return TRUE;


}


int IndexInOption(CMFCPropertyGridProperty* pGrop)
{
	int iSum;
	CString csTemp;

	iSum   = pGrop->GetOptionCount();
	csTemp = pGrop ->GetValue();

	for (int i = 0 ; i < iSum; i++)
		if (pGrop->GetOption(i) == csTemp) 
			return i;
	return -1;
}

BOOL _ComplileATIData(CMFCPropertyGridProperty* pGrop,CString &csATI)
{
	int  iRet;
	bool bRet;
	csATI = _T("0000");

	iRet = IndexInOption(pGrop->GetSubItem(0));

	if (iRet == 0)
		bRet = Setbit(csATI,7,false);
	else
		bRet = Setbit(csATI,7,true);

	iRet = IndexInOption(pGrop->GetSubItem(1));

	if (iRet == 0)
		bRet = Setbit(csATI,8,false);
	else
		bRet = Setbit(csATI,8,true);

	iRet = IndexInOption(pGrop->GetSubItem(2));
	if (iRet == 0)
		bRet = Setbit(csATI,13,false);
	else
		bRet = Setbit(csATI,13,true);

	iRet = IndexInOption(pGrop->GetSubItem(3));

	if (iRet == 0)
		bRet = Setbit(csATI,14,false);
	else
		bRet = Setbit(csATI,14,true);

	iRet = IndexInOption(pGrop->GetSubItem(4));

	if (iRet == 0)
		bRet = Setbit(csATI,15,false);
	else
		bRet = Setbit(csATI,15,true);

	iRet = IndexInOption(pGrop->GetSubItem(5));

	if (iRet == 0)
		bRet = Setbit(csATI,16,false);
	else
		bRet = Setbit(csATI,16,true);


	return TRUE;
}


BOOL _ComplilePLMNData(CMFCPropertyGridProperty* pGrop,CString &csPLMN)
{
	int iSum;
	CString csTemp;

	csPLMN.Empty();
	iSum = pGrop->GetSubItemsCount();

	if ((iSum%2)== 1)
		return FALSE;

	for (int i = 0 ; i < iSum ; i+=2)
	{
		csTemp = pGrop->GetSubItem(i)->GetValue();
		csPLMN = csPLMN+  ConvertMCCMNC(csTemp.Left(03),csTemp.Mid(03));

		if (_ComplileATIData(pGrop->GetSubItem(i+1),csTemp))
			csPLMN = csPLMN+csTemp;
		else
			return FALSE;
	}

	return TRUE;
}



