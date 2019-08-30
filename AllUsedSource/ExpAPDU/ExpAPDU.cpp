// ExpAPDU.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "ExpAPDU.h"
//#include "UNI_Aut_Algorithm.h"

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

// CExpAPDUApp

BEGIN_MESSAGE_MAP(CExpAPDUApp, CWinApp)
END_MESSAGE_MAP()


// CExpAPDUApp 构造

CExpAPDUApp::CExpAPDUApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CExpAPDUApp 对象

CExpAPDUApp theApp;


// CExpAPDUApp 初始化

BOOL CExpAPDUApp::InitInstance()
{
	CWinApp::InitInstance();


	
	SetRegistryKey(_T("Giesecke&Devrient"));
	InitParamerter();
	return TRUE;
}
BOOL CExpAPDUApp::InitParamerter()
{

	
	;

//	iLevel        = Def_APDUBASICINFOMATION|Def_APDUINFOMATION;

	iLevel        = GetProfileInt("Setting","Level",Def_APDUBASICINFOMATION|Def_APDUINFOMATION);

	//0348
	csKIc         = GetProfileString("Setting\\Key\\0348\\KIc","00");
	if (csKIc.IsEmpty())
		csKIc = _T("11223344556677889900112233445566");

	csKIc         = GetProfileString("Setting\\Key\\0348\\KID","00");
	if (csKIc.IsEmpty())
		csKIc = _T("11223344556677889900112233445566");

	csKIc         = GetProfileString("Setting\\Key\\0348\\KIK","00");
	if (csKIc.IsEmpty())
		csKIc = _T("11223344556677889900112233445566");

	//CMCC
	csK1          = GetProfileString("Setting\\Key\\CMCC","K1");
	if (csK1.IsEmpty())
		csK1 = _T("11111111111111111111111111111111");


	//CUC
	CString csTemp;
	csTemp          = GetProfileString("Setting\\Key\\CUC\\RFM","00");
	if (csTemp.IsEmpty())
		csK1 = _T("D82988A3FBB59A6B7429C911B0E65858");
	csCURFMKey.Add(csTemp);
	csTemp          = GetProfileString("Setting\\Key\\CUC\\RFM","01");
	if (csTemp.IsEmpty())
		csK1 = _T("FE20AA0FADC918ABA3CBD601D9D027F2");
	csCURFMKey.Add(csTemp);
	csTemp          = GetProfileString("Setting\\Key\\CUC\\RFM","02");
	if (csTemp.IsEmpty())
		csK1 = _T("865DA51D9CE035348F834942C6E88EE2");
	csCURFMKey.Add(csTemp);
	csTemp          = GetProfileString("Setting\\Key\\CUC\\RFM","03");
	if (csTemp.IsEmpty())
		csK1 = _T("0E0C60B1F82A741B0D5CE2D29FCD3E24");
	csCURFMKey.Add(csTemp);
	csTemp          = GetProfileString("Setting\\Key\\CUC\\RFM","04");
	if (csTemp.IsEmpty())
		csK1 = _T("46544681A599B3022AB5852A45E93B8C");
	csCURFMKey.Add(csTemp);





	/*csK           = _T("00000000000000000000000000000000");
	csK1          = _T("11111111111111111111111111111111");
	csKIc         = _T("11223344556677889900112233445566");
	csDeriveData  = _T("0011111111111111");
	csCURFMKey .Add("D82988A3FBB59A6B7429C911B0E65858");
	csCURFMKey .Add("FE20AA0FADC918ABA3CBD601D9D027F2");
	csCURFMKey .Add("865DA51D9CE035348F834942C6E88EE2");
	csCURFMKey .Add("0E0C60B1F82A741B0D5CE2D29FCD3E24");
	csCURFMKey .Add("46544681A599B3022AB5852A45E93B8C");*/
	
	ResetParameter();
	return TRUE;
}

void CExpAPDUApp::ResetParameter()
{
	
	iCurrentDF = _DEF_Card;
	iPreIns    = NULL;
	iPreSPI    = NULL;
	iOperater  = NULL ;
	csMsgArray.RemoveAll();


}
void SetPreCommand(int iCode)
{
	theApp.iPreIns  = iCode;
//	((CExpAPDUApp*)AfxGetApp())->iPreIns = iCode;
}
int  GetPreCommand()
{
	return theApp.iPreIns ;
}
void SetCurrentDF(int iMark)
{
	theApp.iCurrentDF = iMark;
}
int  GetCurrentDF()
{
	return theApp.iCurrentDF;
}
void SetExplainLevel(int iCode)
{
	theApp.iLevel = iCode;
}
int  GetExplainLevel()
{
	return theApp.iLevel;
}

BOOL __GetUserDataHead(CString csUD,int iIEITag,CString& csIEI)
{
	CString csUDH = csUD.Mid(2,_CString2Int(csUD.Mid(0,2))*2);

	int iOff = 0;
	int iTag ;


	do 
	{
		csIEI.Empty();
		iTag = _CString2Int(csUDH.Mid(iOff,2));
		if (!_GetTLVData(csUDH,iTag,csIEI))
			return FALSE;

		if (iTag == iIEITag)
			return TRUE;


		iOff += csIEI.GetLength() +4;
	} while (iOff<csUDH.GetLength());

	return FALSE;

}
int GetMessageArrayCount()
{
	return theApp.csMsgArray.GetCount();
}
CString GetMessageArray(int iAt)
{
	return theApp.csMsgArray.GetAt(iAt);
}
void AddMessageArray(CString csMessage)
{
	CString csIEIA;
	int iBatchIn,iBatchCur;
	if (__GetUserDataHead(csMessage,0x00,csIEIA))
	{
		if (GetMessageArrayCount()!= 0)
		{
			iBatchCur = _CString2Int(csIEIA.Mid(0,2));

			__GetUserDataHead(GetMessageArray(0),0x00,csIEIA);

			iBatchIn = _CString2Int(csIEIA.Mid(0,2));

			if (iBatchCur>iBatchIn)
			{
				theApp.csMsgArray.RemoveAll();
			}else if (iBatchCur<iBatchIn)
				return;

		}
			theApp.csMsgArray.Add(csMessage);
	}

}

void SetDeriveData(CString csInput)
{
	theApp.csDeriveData = csInput;
}
void SetK1(CString csInput)
{
	theApp.csK1 = csInput;
}

BOOL __APDUIsComplete(CString csAPDU)
{
	  if (!_IsAllHex(csAPDU))
			 return FALSE;
		int iLen = csAPDU.GetLength();
		if (iLen <10)
			return FALSE;

		if (iLen != (_CString2Int(csAPDU.Mid(8,2))*2   +14 ))
			return FALSE;
		return TRUE;
}

BOOL __P3IsLe(CString csAPDU)
{
	    int iIns,iP1,iP2;
			BOOL bP3IsLe = TRUE;

			iIns       = _CString2Int(csAPDU.Mid(2,2)) ;
			iP1        = _CString2Int(csAPDU.Mid(4,2)) ;
			iP2        = _CString2Int(csAPDU.Mid(6,2)) ;

				switch(iIns)
				{
				case 0xA4:
					if ((iP1 == 3)&&(iP2 == 4))
						bP3IsLe = TRUE ;
					else
						bP3IsLe = FALSE;
					break;
				case 0x75:
					if ((iP1&4)== 0)
						bP3IsLe = TRUE ;
					else
						bP3IsLe = FALSE;
					break;
				case 0xCB:
					if ((iP2&0xDF)== 0)
						bP3IsLe = TRUE ;
					else
						bP3IsLe = FALSE;
					break;
				case 0x70:
				case 0x84:
				case 0xF2:
				case 0xC0:
				case 0x12:
				case 0xFA:
				case 0xB2:
				case 0xB0: bP3IsLe = TRUE ;break;
				case 0xF8: bP3IsLe = TRUE ;break;
				default:   bP3IsLe = FALSE;break;
				}

				return bP3IsLe;

}

BOOL _ExplainSW              (int iSW, CString& csOutput)
{
	BOOL bRet = TRUE;
	CString csTemp;
	switch(iSW/0x100)
	{
	case 0x6F:csOutput = _T("内部问题");        break;
	case 0x6D:csOutput = _T("不能识别指令");    break;
	case 0x6C:csOutput = _T("P3错误");          break;
	case 0x6B:csOutput = _T("P1P2错误");        break;
	case 0x67:csOutput = _T("P3错误");          break;
	case 0x6E:csOutput = _T("Class错误");       break;
	case 0x63:
		csTemp.Format(_T("%d"),(iSW&0xF));
		csOutput = _T("PIN剩余次数")+csTemp;         break;
	case 0x62:	
		switch(iSW&0xFF)
		{
		case 0x83 :csOutput = _T("文件无效"); break;
		case 0x82 :csOutput = _T("没有找记录");  break;
		default:csOutput = _T("失败");  
			bRet = FALSE;break;
		}
		break;
	case 0x68:
		switch(iSW&0xFF)
		{
		case 0x81 :csOutput = _T("不支持逻辑通道"); break;
		case 0x82 :csOutput = _T("安全状态不满足");  break;
		default:csOutput += _T("失败");  
			bRet = FALSE;break;
		}		
		break;
	case 0x69:
		switch(iSW&0xFF)
		{
		case 0x81 :csOutput = _T("命令与文件结构矛盾"); break;
		case 0x82 :csOutput = _T("安全状态不满足");  break;
		case 0x83 :csOutput = _T("鉴权/PIN被锁死");  break;
		case 0x84 :csOutput = _T("引用的数据无效");  break;
		case 0x85 :csOutput = _T("使用的条件不满足");  break;
		case 0x86 :csOutput = _T("没有选择的EF");  break;
		default:csOutput = _T("失败");  
			bRet = FALSE;break;
		}		
		break;
	case 0x6A:
		switch(iSW&0xFF)
		{
		case 0x80 :csOutput = _T("数据字段中的参数错误"); break;
		case 0x81 :csOutput = _T("功能不被支持"); break;
		case 0x82 :csOutput = _T("找不到文件");  break;
		case 0x83 :csOutput = _T("找不到记录");  break;
		case 0x86 :csOutput = _T("错误的参数P1-P2");  break;
		case 0x87 :csOutput = _T("Lc与P1-P2不一致");  break;
		default:csOutput = _T("失败");  
			bRet = FALSE;break;
		}	
		break;
	case 0x98:
		switch(iSW&0xFF)
		{
		case 0x40 :csOutput = _T("鉴权/PIN被锁死"); break;
		case 0x04 :csOutput = _T("鉴权/PIN错误"); break;
		case 0x50 :csOutput = _T("INCREASE不能被执行，已达到最大值");  break;
		case 0x62 :csOutput = _T("鉴权错误,输入数据有误");  break;
		default:csOutput = _T("失败"); 
			bRet = FALSE; break;
		}	
		break;
	case 0x91:csOutput = _T("成功,后续有主动式指令"); break;
	case 0x61:csOutput = _T("成功"); break;
	case 0x9F:csOutput = _T("成功"); break;
	default:
		if (iSW == 0x9000)
			csOutput = _T("成功");
		else
		{
			csOutput = _T("失败");
			bRet = FALSE;
		}
		break;
	}
	return bRet;
}
BOOL _ExplainIns             (int iIns,CString csInput ,CString& csOutput)
{
	BOOL bRet = TRUE;
	//_AppendSpace(csInput);
	switch(iIns)
	{

	case 0xC:csOutput = _T("Erase Record  ");break;
	case 0xE:
	case 0xF:csOutput = _T("Erase Bianry  ");break;

	case 0x10:csOutput = _T("Terminal Profile  ");break;
	case 0x12:csOutput = _T("Fetch ");break;
	case 0x14:csOutput = _T("Terminal Response ");break;

	case 0xC0:csOutput = _T("Get Response");break;
	case 0xC2:csOutput = _T("Envelope ");break;

	case 0x04:csOutput = _T("Deactive File  ");break;
	case 0x44:csOutput = _T("Active File ");break;

	case 0x46:csOutput = _T("Generate Asymmetric Key Pair ");break;

	case 0x17:csOutput = _T("Verify PS");break;
	case 0x20:csOutput = _T("Verify PIN  ");break;

	case 0x22:csOutput = _T("Manage Security Environment  ");break;

	case 0x24:csOutput = _T("Change PIN  ");break;
	case 0x26:csOutput = _T("Disable PIN ");break;
	case 0x28:csOutput = _T("Enable PIN  ");break;
	case 0x2A:csOutput = _T("Preform Security Operation ");break;
	case 0x2C:csOutput = _T("Unblock PIN ");break;

	case 0x70:csOutput = _T("Manage Channel ");break;
	case 0x73:csOutput = _T("Manage Secure Channel ");break;
	case 0x75:csOutput = _T("Transact Data ");break;

	case 0x82:csOutput = _T("External Authentiate ");break;
	
	case 0x86:
	case 0x87:csOutput = _T("General Authentiate ");break;

	case 0x88:
	case 0x89:csOutput = _T("Authentiate ");break;

	case 0xA2:csOutput = _T("Search File ");break;
	case 0xA4:csOutput = _T("Select File ")+csInput;break;


	case 0xAA:csOutput = _T("Termainl Capability ");break;

	case 0xB0:
	case 0xB1:csOutput = _T("Read Binary ");break;

	case 0xB2:
	case 0xB3:csOutput = _T("Read Record ");break;


	case 0xCA:csOutput = _T("Get Data ");break;

	case 0xCB:csOutput = _T("Retrieve Data ");break;

	case 0xDA:csOutput = _T("Put Data ");break;

	case 0xDB:csOutput = _T("Set Data ");break;

	case 0xD0:
	case 0xD1:csOutput = _T("Write Binary  ");break;

	case 0xD2:csOutput = _T("Write Record  ");break;

	case 0xD6:
	case 0xD7:csOutput = _T("Update Binary  ");break;

	case 0xDC:
	case 0xDD:csOutput = _T("Update Record  ");break;



	case 0xE0:csOutput = _T("Create File  ");break;
	case 0xE2:csOutput = _T("Append Record  ");break;
	case 0xE4:csOutput = _T("Erase File  ");break;

	case 0xE6:csOutput = _T("Termainate DF ");break;
	case 0xE8:csOutput = _T("Termainate EF ");break;

	case 0xF2:csOutput = _T("Status");break;
	case 0xFA:csOutput = _T("Sleep ");break;

	case 0xFE:csOutput = _T("Termainate Card Usage ");break;


	case 0xF6:csOutput = _T("ID2 SymmetricCrypt");break;
	case 0xF8:csOutput = _T("ID2 GetID");break;
	case 0xFC:csOutput = _T("ID2 GetVendorInfo");break;

	default:  
		csOutput = _T("Untempered ");;
		bRet = FALSE;break;
	}

	if (bRet != FALSE)
		csOutput += _T(":");

	return bRet;
}
BOOL _ExplainAPDU            (CString csSend,CString csResp,CStringArray& csOutput)
{
	int iLevel = GetExplainLevel();

	CString csCommandInfo;
	CString csResultInfo ;
	int iIns = 00;
	int iSW  = 00;
	int iCla = 00;
	 
	csOutput.RemoveAll();

	if ((iLevel&Def_APDUBASICINFOMATION) == FALSE)
		return TRUE;

	iCla = _CString2Int(csSend.Mid(0,2));
	iIns = _CString2Int(csSend.Mid(2,2));
	if (csResp.GetLength()>=4)
		iSW  = _CString2Int(csResp.Right(4));
	if (_ExplainIns(iIns,csSend.Mid(10),csCommandInfo) == FALSE)
		return -1;
	if (_ExplainSW(iSW,csResultInfo) == FALSE)
		return -2;

	csOutput.Add(csCommandInfo+csResultInfo);


	if ((Def_APDUINFOMATION&iLevel) == 0)
		return TRUE;

	BOOL bRet = FALSE;


	switch(iIns)
	{
	case 0x10:bRet = _ExplainTerminalProfile(csSend.Mid(10),csOutput); break;
	case 0x12:bRet = _ExplainFetch(csResp,csOutput);                   break;
	case 0x14:bRet = _ExplainTerminalResponse(csSend.Mid(10),csOutput);break;
	case 0xA4:bRet = _ExplainSelect(csSend,csResp,csOutput);           break;
	case 0xC2:bRet = _ExplainEvelop(csSend.Mid(10),csOutput);          break;
	case 0xB0:bRet = _ExplainReadBinary(csSend, csOutput);             break;
	case 0xD6:bRet = _ExplainUpdateBinary(csSend, csOutput);           break;
	case 0xB2:bRet = _ExplainReadRecord(csSend, csResp, csOutput);             break;
	case 0xDC:bRet = _ExplainUpdateRecord(csSend, csOutput);           break;
	case 0xA2:bRet = _ExplainSearchRecord(csSend, csOutput);           break; 
	case 0x32:bRet = _ExplainIncrease(csSend,csOutput);                break;
	case 0x04:
	case 0x44:bRet = _ExplainDeactiveActive(csSend,csOutput);          break;
	case 0x70:bRet = _ExplainManageChannel(csSend,csOutput);           break;
	case 0xF2:
		if (iCla == 0xF0)
		{
		}
		else
			bRet = _ExplainStatus(csSend,csOutput);                  break;
	case 0xC0:bRet = _ExplainGetResponse(GetPreCommand(),csResp,csOutput);       break;
	case 0x88:bRet = _ExplainAuthenticate(csSend,csOutput);           break;

	case 0xF6:bRet = _ExplainID2SymmetricCrypt(csSend,csResp,csOutput); break;
	case 0xF8:bRet = _ExplainID2GetID(csResp,csOutput); break;
	case 0xFC:bRet = _ExplainID2GetVendorInfo(csResp,csOutput); break;
	default:bRet = FALSE;
	}



	//此处用于GetResponse处理；
	SetPreCommand(iIns);
	return bRet;
}
BOOL _ExplainFetch           (CString csFetch,CStringArray& csOutput)
{
	//CString ProSIMCom;
	//CString csDetails;
	//if (!_GetTLVData(csFetch,0xD0,ProSIMCom))
	//	return FALSE;

	////获取 Command details
	//if (!_GetTLVData(ProSIMCom,0x01,csDetails))
	//	if(!_GetTLVData(ProSIMCom,0x81,csDetails))
	//		return FALSE;

	return _ExplainBETTLV(csFetch,csOutput);
}
BOOL _ExplainTerminalResponse(CString csTerminalResponse,CStringArray& csOutput)
{

	return _ExplainProactiveSIMCommand(csTerminalResponse,csOutput);
}
BOOL _ExplainEvelop          (CString csEvelop,CStringArray& csOutput)
{
	return _ExplainBETTLV(csEvelop,csOutput);
}
BOOL _ExplainTerminalProfile (CString csProfile,CStringArray& csOutput)
{

	int iLen  = csProfile.GetLength()*4;
	bool bSup = false;
	CString csText,csSupport,csDes;

	for (int i = 1 ; i <= iLen ; i ++)
	{
		csText.Empty();
		csDes .Empty();
		if (_Getbit(csProfile,i))
			csSupport = _T( " \\- Supported");
		else
			csSupport = _T( " \\- Unsupported");



		switch(i)
		{
		case 1: csText= _T("Profile download");break;
		case 2: csText= _T("SMS-PP data download");break;
		case 3: csText= _T("Cell Broadcast data download");break;
		case 4: csText= _T("Menu selection");break;
		case 5: csText= _T("'9EXX' response code");
			    csDes = _T("'9EXX' response code for SIM data download error");
			    break;
		case 6: csText= _T("Timer expiration");break;
		case 7: csText= _T("USSD string data object");
		    	csDes = _T("USSD string data object supported in Call Control");
		    	break;			 
		case 8: csText= _T("Envelope Call Control");break;
			    csDes = _T("Envelope Call Control always sent to the SIM during automatic redial mode");
			    break;
		case 9: csText= _T("Command result");break;
		case 10: csText= _T("Call Control by SIM");break;

		case 11: csText= _T("Cell identity");break;
		     	 csDes = _T("Cell identity included in Call Control by SIM");
			     break;
		case 12: csText= _T("MO short message control by SIM");break;
		case 13: csText= _T("Handling of the alpha");break;
		case 14: csText= _T("UCS2 Entry supported");break;
		case 15: csText= _T("UCS2 Display supported");break;
		case 16: csText= _T("Display of the extension text");break;

		case 17: csText= _T("Proactive SIM：DISPLAY TEXT");break;
		case 18: csText= _T("Proactive SIM：GET INKEY");break;
		case 19: csText= _T("Proactive SIM：GET INPUT");break;
		case 20: csText= _T("Proactive SIM：MORE TIME");break;
		case 21: csText= _T("Proactive SIM：PLAY TONE");break;
		case 22: csText= _T("Proactive SIM：POLL INTERVAL");break;
		case 23: csText= _T("Proactive SIM：POLLING OFF");break;
		case 24: csText= _T("Proactive SIM：REFRESH");break;

		case 25: csText= _T("Proactive SIM：SELECT ITEM");break;
		case 26: csText= _T("Proactive SIM：SEND MESSAGE");break;
		case 27: csText= _T("Proactive SIM：SEND SS");break;
		case 28: csText= _T("Proactive SIM：SEND USSD");break;
		case 29: csText= _T("Proactive SIM：SET UP CALL");break;
		case 30: csText= _T("Proactive SIM：SET UP MENU");break;
		case 31: csText= _T("Proactive SIM：PROVIDE");
		      	 csDes = _T("PROVIDE LOCAL INFORMATION (MCC, MNC,LAC, Cell ID & IMEI)");
		    	 break;
		case 32: csText= _T("Proactive SIM：PROVIDE");
		         csDes = _T("PROVIDE LOCAL INFORMATION (NMR)");
		      	 break;

		case 33: csText= _T("Proactive SIM：SETUP EVENTLIST");break;
		case 34: csText= _T("Event：MT call");break;
		case 35: csText= _T("Event：Call connected");break;
		case 36: csText= _T("Event：Call disconnected");break;
		case 37: csText= _T("Event：Location status");break;
		case 38: csText= _T("Event：User activity");break;
		case 39: csText= _T("Event：Idle screen available");break;
		case 40: csText= _T("Event：Card reader status");break;

		case 41: csText= _T("Event：Language selection");break;
		case 42: csText= _T("Event：Browser Termination");break;
		case 43: csText= _T("Event：Data available");break;
		case 44: csText= _T("Event：Channel status");break;

		case 49: csText= _T("Proactive SIM：POWER ON CARD");break;
		case 50: csText= _T("Proactive SIM：POWER OFF CARD");break;
		case 51: csText= _T("Proactive SIM：PERFORM CARDAPDU");break;
		case 52: csText= _T("Proactive SIM：GET READERSTATUS");
			     csDes = _T("GET READER STATUS (Card reader status)");
		     	 break;
		case 53: csText= _T("Proactive SIM：GET READERSTATUS");
		    	 csDes = _T("GET READER STATUS (Card reader identifier)");
		         break;
		case 57: csText= _T("Proactive SIM：TIMER MANAGEMENT");
			csDes = _T("TIMER MANAGEMENT (start, stop)");
			break;
		case 58: csText= _T("Proactive SIM：TIMER MANAGEMENT");
		    	 csDes = _T("TIMER MANAGEMENT (get current value)");
			     break;
		case 59: csText= _T("Proactive SIM：PROVIDE");
			     csDes = _T("PROVIDE LOCAL INFORMATION (date,time and time zone)");
			     break;
		case 60: csText= _T("Binary choice in GET INKEY");break;
		case 61: csText= _T("SET UP IDLE MODE TEXT");break;
		case 62: csText= _T("RUN AT COMMAND");break;
		case 63: csText= _T("2nd alpha identifier");
			csDes = _T("2nd alpha identifier in SET UP CALL");
			break;
		case 64: csText= _T("2nd CCP");
			csDes = _T("2nd capability configuration parameter");
			break;		


		case 65: csText= _T("Sustained DISPLAY TEXT ");break;
		case 66: csText= _T("SEND DTMF command");break;
		case 67: csText= _T("Proactive SIM：PROVIDE");
			csDes = _T("PROVIDE LOCAL INFORMATION (CCH Channel List coding)");
			break;
		case 68: csText= _T("Proactive SIM：PROVIDE");
			csDes = _T("PROVIDE LOCAL INFORMATION (language)");
			break;
		case 69: csText= _T("Proactive SIM：PROVIDE ");
			csDes = _T("PROVIDE LOCAL INFORMATION (Timing Advance)");
			break;
		case 70: csText= _T("Proactive SIM：LANGUAGE N");
			     csDes = _T("LANGUAGE NOTIFICATION");
			     break;

		case 71: csText= _T("Proactive SIM：LAUNCH BROWSER");break;

		case 73: csText= _T("Soft keys for SELECT ITEM ");break;
		case 74: csText= _T("Soft Keys for SET UP MENU");break;

		case 80: csText= _T("Max num of soft keys available \\- ");
			      _Getbit_E_C(csProfile,80,8,csSupport);
				  csSupport += _T("       ");
				  csDes = _T("Maximum number of soft keys available \\- ");
			     break;

		case 89: csText= _T("Proactive SIM：OPEN CHANNEL");break;
		case 90: csText= _T("Proactive SIM：CLOSE CHANNEL");break;
		case 91: csText= _T("Proactive SIM：RECEIVE DATA");break;
		case 92: csText= _T("Proactive SIM：SEND DATA");break;
		case 93: csText= _T("Proactive SIM：CHANNEL STATUS");
			     csDes = _T("GET CHANNEL STATUS ");
			     break;

		case 97: csText= _T("CSD supported by ME");break;
		case 98: csText= _T("GPRS supported by ME");break;
		case 102: csText= _T("Number of channels");
		       	  csDes = _T("Number of channels supported by ME ");
			      break;

		case 105: csText= _T("Number of characters \\- ");
			              _Getbit_E_C(csProfile,105,4,csSupport);
						  csSupport += _T("       ");
						  csDes = _T("Number of characters supported down the ME display ");
						  break;


		case 112: csText= _T("Screen Sizing Parameters");break;

		case 113: 
			csText= _T("Number of characters \\- ");
			 _Getbit_E_C(csProfile,113,7,csSupport);
			 csSupport += _T("       ");
			csDes = _T("Number of characters supported across the ME display ");
			break;
			
		case 120: csText= _T("Variable size fonts");break;

		case 121: csText= _T("Display can be resized");break;
		case 122: csText= _T("Text Wrapping");break;
		case 123: csText= _T("Text Scrolling");break;

		case 128: csText= _T("Width reduction");break;

		case 129: csText= _T("TCP");break;
		case 130: csText= _T("UDP");break;
		}

		if (!csText.IsEmpty())
		{
			csText = csText + csSupport;
			if (!csDes.IsEmpty())
				csText = csText + _T(" (") + csDes + _T(")")  ;

			csOutput.Add(csText);
	
		}

	}

	return TRUE;
}

BOOL _ExplainBETTLV(CString csBETTLV,CStringArray& csOutput)
{
	CString csBET;
	BOOL bRet = TRUE;
	int iTag = _CString2Int(csBETTLV.Left(02));
	switch(iTag)
	{
	case 0xD1:csOutput.Add(_T("SMS-PP download"));   break;
	case 0xD2:csOutput.Add(_T("Cell Broadcast download"));  break;
	case 0xD3:csOutput.Add(_T("Menu Selection"));       break;    
	case 0xD4:csOutput.Add(_T("Call control"));      break;       
	case 0xD5:csOutput.Add(_T("MO Short message control"));  break;
	case 0xD6:csOutput.Add(_T("Event download"));         break;   
	case 0xD7:csOutput.Add(_T("Timer expiration"));       break;  
	case 0xDF:csOutput.Add( _T("Reserved for TIA/EIA-136")); break;
	case 0xD0:csOutput.Add(_T("Proactive SIM command")); break;
	default:bRet = FALSE;                               break;
	}

	if (bRet == TRUE)
	{
		if (_GetTLVData(csBETTLV,iTag,csBET))
			bRet = _ExplainProactiveSIMCommand(csBET,csOutput);
		else
			bRet = FALSE;
	}

	return bRet;
}

BOOL _ExplainProactiveSIMCommand(CString csProactiveSIMCommand,CStringArray& csOutput)
{
	int iTag;
	BOOL bRet = TRUE;
	CString csRemind = csProactiveSIMCommand;
	CString csSIMPLE,csSIMPLETLV;
	do 
	{
		iTag = _CString2Int(csRemind.Left(2))   ;
		if (!_GetTLVData(csRemind,iTag,csSIMPLE))
		{
			bRet = FALSE;
			break;
		}
		_GenerateTLVData(csSIMPLE,iTag,csSIMPLETLV);

		if (!_ExplainCommandDetails_SIMPLETLVData(csSIMPLETLV,csOutput))
		{
			bRet = FALSE;
			break;
		}
		csRemind = csRemind.Mid(csSIMPLETLV.GetLength());

	} while (!csRemind.IsEmpty());

	return bRet;
}

BOOL _ExplainCommandDetails_SIMPLETLVData(CString csSIMPLETLV,CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	int iTag = _CString2Int(csSIMPLETLV.Left(2)) ;
	CString csSIMPLE;
	
	if (!_GetTLVData(csSIMPLETLV,iTag,csSIMPLE))
		return FALSE;
	switch(iTag&0x7F)
	{
	case  Def_SIMPLE_Commanddetails                   :bRet = _ExplainCommandDetails(csSIMPLE,csOutput); break;
	case  Def_SIMPLE_Deviceidentity                   :bRet = _ExplainDeviceIdentitys(csSIMPLE,csOutput);break; 
	case  Def_SIMPLE_Result                           :bRet = _ExplainResult(csSIMPLE,csOutput);break; 
	case  Def_SIMPLE_Duration                         :bRet = _ExplainDuration(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Alphaidentifier                  :bRet = _ExplainAlphaIdentifier(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Address                          :bRet = _ExplainAddress(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Capabilityconfigurationparameters:bRet = _ExplainCapabilityConfigurationParameters(csSIMPLE,csOutput);break; 
	case  Def_SIMPLE_Subaddress                       :bRet = _ExplainSubAddress(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_SSstring                         :bRet = _ExplainSSString(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_USSDstring                       :bRet = _ExplainUSSDString(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_SMSTPDU                          :bRet = _ExplainSMSTPDU(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_CellBroadcastpage                :bRet = _ExplainCellBroadCastPage(csSIMPLE,csOutput);break; 
	case  Def_SIMPLE_Textstring                       :bRet = _ExplainTextString(csSIMPLE,csOutput);break; 
	case  Def_SIMPLE_Tone                             :bRet = _ExplainTone(csSIMPLE,csOutput);break; 
	case  Def_SIMPLE_Item                             :bRet = _ExplainItem(csSIMPLE,csOutput);break; 
	case  Def_SIMPLE_Itemidentifier                   :bRet = _ExplainItemIdentifier(csSIMPLE,csOutput);break; 
	case  Def_SIMPLE_Responselength                   :bRet = _ExplainResponseLength(csSIMPLE,csOutput);break; 
	case  Def_SIMPLE_FileList                         :bRet = _ExplainFileList(csSIMPLE,csOutput);break; 
	case  Def_SIMPLE_LocationInformation              :bRet = _ExplainLocationInformation(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_IMEI                             :bRet = _ExplainIMEI(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Helprequest                      :bRet = _ExplainHelprequest(csSIMPLE,csOutput);break; 
	case  Def_SIMPLE_NetworkMeasurementResults        :bRet = _ExplainNetworkMeasurementResults(csSIMPLE,csOutput);break; 
	case  Def_SIMPLE_DefaultText                      :bRet = _ExplainDefaultText(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_ItemsNextActionIndicator         :bRet = _ExplainItemsNextActionIndicator(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Eventlist                        :bRet = _ExplainEventList(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Cause                            :bRet = _ExplainCause(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Locationstatus                   :bRet = _ExplainLocationStatus(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Transactionidentifier            :bRet = _ExplainTransactionIdentifier(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_BCCHchannellist                  :bRet = _ExplainBCCHChannelList(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Iconidentifier                   :bRet = _ExplainTemp(_T("Icon Identifier"),csSIMPLE,csOutput);break;
	case  Def_SIMPLE_ItemIconidentifierlis            :bRet = _ExplainTemp(_T("Item Icon Identifier list"),csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Cardreaderstatus                 :bRet = _ExplainTemp(_T("Card reader status"),csSIMPLE,csOutput);break;
	case  Def_SIMPLE_CardATR	                      :bRet = _ExplainTemp(_T("Card ATR"),csSIMPLE,csOutput);break;
	case  Def_SIMPLE_C_APDU                           :bRet = _ExplainTemp(_T("C-APDU"),csSIMPLE,csOutput);break;
	case  Def_SIMPLE_R_APDU                           :bRet = _ExplainTemp(_T("R-APD"),csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Timeridentifier                  :bRet = _ExplainTemp(_T("Time Identifier"),csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Timervalue                       :bRet = _ExplainTimeValue(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_DateTimeandTimezone              :bRet = _ExplainDateTimeandTimezone(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Callcontrolrequestedaction       :
	case  Def_SIMPLE_ATCommand                        :bRet = _ExplainTemp(_T("AT Command"),csSIMPLE,csOutput);break;
	case  Def_SIMPLE_ATResponse                       :bRet = _ExplainTemp(_T("AT Response"),csSIMPLE,csOutput);break;
	case  Def_SIMPLE_BCRepeatIndicator                :bRet = _ExplainBCRepeatIndicator(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Immediateresponse                :bRet = _ExplainTemp(_T("Immediate response"),csSIMPLE,csOutput);break;
	case  Def_SIMPLE_DTMFstring                       :bRet = _ExplainTemp(_T("DTMF string"),csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Language                         :bRet = _ExplainTemp(_T("Language"),csSIMPLE,csOutput);break;
	case  Def_SIMPLE_TimingAdvance                    :bRet = _ExplainTimingAdvance(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_BrowserIdentity                  :bRet = _ExplainTemp(_T("Browser Identity"),csSIMPLE,csOutput);break;
	case  Def_SIMPLE_URL                              :bRet = _ExplainURL(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Bearer                           :bRet = _ExplainBearer(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_ProvisioningReferenceFile        :bRet = _ExplainTemp(_T("Provisioning File Reference"),csSIMPLE,csOutput);break;
	case  Def_SIMPLE_BrowserTerminationCause          :bRet = _ExplainBrowserTerminationCause(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Bearerdescription                :bRet = _ExplainBearerDescription(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Channeldata                      :bRet = _ExplainTemp(_T("Channel data"),csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Channeldatalength                :bRet = _ExplainTemp(_T("Channel data length"),csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Channelstatus                    :bRet = _ExplainChannelStatus(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Buffersize                       :bRet = _ExplainTemp(_T("Buffer size"),csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Cardreaderidentifier             :bRet = _ExplainTemp(_T("Card reader identifier"),csSIMPLE,csOutput);break;        
	case  Def_SIMPLE_SIMMEinterfacetransportlevel     :bRet = _ExplainSIMMEInterfaceTransportLevel(csSIMPLE,csOutput);break;
	case  Def_SIMPLE_Otheraddress                     :bRet = _ExplainOtherAddress(csSIMPLE,csOutput);break;
	//case  Def_SIMPLE_NetworkAccessName                :bRet = _ExplainTemp(_T("Network Access Name"),csSIMPLE,csOutput);break;

	case Def_SIMPLE_AccessTechnology             :bRet = _ExplainTemp(_T("Access Technology "),csSIMPLE,csOutput);break;
	case Def_SIMPLE_Displayparameters            :bRet = _ExplainTemp(_T("Display Parameters"),csSIMPLE,csOutput);break;

	case Def_SIMPLE_ServiceRecord               :bRet = _ExplainTemp(_T("Service Record"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_DeviceFilter                :bRet = _ExplainTemp(_T("Device Filter"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_ServiceSearch               :bRet = _ExplainTemp(_T("Service Search "),csSIMPLE,csOutput);break;
	case Def_SIMPLE_AttributeInformation        :bRet = _ExplainTemp(_T("Attribute Information  "),csSIMPLE,csOutput);break;
	case Def_SIMPLE_ServiceAvailability         :bRet = _ExplainTemp(_T("Service Availability"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_ESN                         :bRet = _ExplainTemp(_T("ESN"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_NetworkAccessName           :bRet = _ExplainTemp(_T("Network Access Name"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_CDMASMSTPDU                 :bRet = _ExplainCDMASMSTPDU(csSIMPLE,csOutput);break;


	case Def_SIMPLE_RemoteEntityAddress       :bRet = _ExplainTemp(_T("Remote Entity Address"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_IWLANIdentifier           :bRet = _ExplainTemp(_T("I WLAN Identifier"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_IWLANAccessStatus         :bRet = _ExplainTemp(_T("I WLAN AccessStatus"),csSIMPLE,csOutput);break;

	case Def_SIMPLE_TextAttribute             :bRet = _ExplainTemp(_T("Text Attribute"),csSIMPLE,csOutput);break;

	case Def_SIMPLE_ItemTextAttributeList            :bRet = _ExplainTemp(_T("Item Text AttributeList "),csSIMPLE,csOutput);break;
	case Def_SIMPLE_PDPContextActivationParameter    :bRet = _ExplainTemp(_T("PDP Context Activation Parameter"),csSIMPLE,csOutput);break;

	case Def_SIMPLE_IMEISV                           :bRet = _ExplainTemp(_T("IMEI SV "),csSIMPLE,csOutput);break;
	case Def_SIMPLE_BatteryState                     :bRet = _ExplainTemp(_T("Battery State"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_BrowsingStatus                   :bRet = _ExplainTemp(_T("Browsing Status"),csSIMPLE,csOutput);break;

	case Def_SIMPLE_NetworkSearchMode                :bRet = _ExplainTemp(_T("Network Search Mode"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_FrameLayout                      :bRet = _ExplainTemp(_T("Frame Layout"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_FramesInformation                :bRet = _ExplainTemp(_T("Frames Information "),csSIMPLE,csOutput);break;
	case Def_SIMPLE_FrameIdentifier                  :bRet = _ExplainTemp(_T("Frame Identifier"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_UTRANMeasurementQualifier        :bRet = _ExplainTemp(_T("UTRAN Measurement Qualifier"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_MultimediaMessageReference       :bRet = _ExplainTemp(_T("Multimedia Message Reference"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_MultimediaMessageIdentifier      :bRet = _ExplainTemp(_T("Multimedia Message Identifier "),csSIMPLE,csOutput);break;
	case Def_SIMPLE_MultimediaMessageTransferStatus  :bRet = _ExplainTemp(_T("Multimedia Message Transfer Status"),csSIMPLE,csOutput);break;

	case Def_SIMPLE_MEID                             :bRet = _ExplainTemp(_T("MEID"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_MultimediaMessageContentIdentifier :bRet = _ExplainTemp(_T("Multimedia Message Content Identifier"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_MultimediaMessageNotification      :bRet = _ExplainTemp(_T("Multimedia Message Notification "),csSIMPLE,csOutput);break;
	case Def_SIMPLE_LastEnvelope                     :bRet = _ExplainTemp(_T("Last Envelope"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_RegistryApplicationData          :bRet = _ExplainTemp(_T("Registry Application Data"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_PLMNwAcTList                     :bRet = _ExplainTemp(_T("PLMNwAcT List "),csSIMPLE,csOutput);break;
	case Def_SIMPLE_RoutingAreaInformation           :bRet = _ExplainTemp(_T("Routing Area Information "),csSIMPLE,csOutput);break;
	case Def_SIMPLE_UpdateAttachType                 :bRet = _ExplainTemp(_T("Update Attach Type "),csSIMPLE,csOutput);break;


	case Def_SIMPLE_RejectionCauseCode                 :bRet = _ExplainTemp(_T("Rejection Cause Code"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_GeographicalLocationParameters     :bRet = _ExplainTemp(_T("Geographical Location Parameters"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_GADShapes                          :bRet = _ExplainTemp(_T("GAD Shapes"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_NMEASentence                       :bRet = _ExplainTemp(_T("NMEA Sentence"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_PLMNList                           :bRet = _ExplainTemp(_T("PLMN List"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_BroadcastNetworkInformation        :bRet = _ExplainTemp(_T("Broadcast Network Information"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_ACTIVATEdescriptor                 :bRet = _ExplainTemp(_T("ACTIVATE Descriptor"),csSIMPLE,csOutput);break;


	case Def_SIMPLE_EPSPDNConnectionActivationParameters :bRet = _ExplainTemp(_T("EPS PDN Connection Activation Parameters"),csSIMPLE,csOutput);break;
	case Def_SIMPLE_TrackingAreaIdentification           :bRet = _ExplainTemp(_T("Tracking Area Identification "),csSIMPLE,csOutput);break;          
	case Def_SIMPLE_CSGIDlist                            :bRet = _ExplainTemp(_T("CSGID List "),csSIMPLE,csOutput);break;               
	case Def_SIMPLE_MediaType                            :bRet = _ExplainTemp(_T("Media Type"),csSIMPLE,csOutput);break;         
	default: bRet = FALSE;break;
	       
	}

	return bRet;
}
BOOL _TranslateProactiveSIMCommandType( int iCommandType, CString &csTypeText )
{
	BOOL bRet = TRUE;
	switch(iCommandType)
	{
	case  Def_REFRESH   :              csTypeText+= _T("(Refresh)");break;
	case  Def_MORETIME :               csTypeText+= _T("(More Time)");break;
	case  Def_POLLINTERVAL :           csTypeText+= _T("(Poll Interval)");break;
	case  Def_POLLINGOFF :             csTypeText+= _T("(Polling Off)");break;
	case  Def_SETUPEVENTLIST :         csTypeText+= _T("(Setup EvenList)");break;
	case  Def_SETUPCALL :              csTypeText+= _T("(Setup Call)");break;
	case  Def_SENDSS :                 csTypeText+= _T("(Send SS)");break;
	case  Def_SENDUSSD :               csTypeText+= _T("(Send USSD)");break;
	case  Def_SENDSHORTMESSAGE :       csTypeText+= _T("(Send Short Message)");break;
	case  Def_SENDDTMF :               csTypeText+= _T("(Send DTMF)");break;
	case  Def_LAUNCHBROWSER	 :         csTypeText+= _T("(Launch Browser)");break;
	case  Def_PLAYTONE :               csTypeText+= _T("(Play Tone)");break;
	case  Def_DISPLAYTEXT :            csTypeText+= _T("(Display Text)");break;
	case  Def_GETINKEY :               csTypeText+= _T("(Get In Key)");break;
	case  Def_GETINPUT :               csTypeText+= _T("(Get Input)");break;
	case  Def_SELECTITEM :             csTypeText+= _T("(Select Item)");break;
	case  Def_SETUPMENU :              csTypeText+= _T("(Setup Menu)");break;
	case  Def_PROVIDELOCALINFORMATION :csTypeText+= _T("(Provide Local Information)");break;
	case  Def_TIMERMANAGEMENT :        csTypeText+= _T("(Timer Management)");break;
	case  Def_SETUPIDLEMODELTEXT :     csTypeText+= _T("(Setup Idle Model Text)");break;
	case  Def_PERFORMCARDAPDU	 :     csTypeText+= _T("(Perform Card APDU)");break;
	case  Def_POWERONCARD	 :         csTypeText+= _T("(Power On Card)");break;
	case  Def_POWEROFFCARD	 :         csTypeText+= _T("(Power Off Card)");break;
	case  Def_GETREADERSTATUS	 :     csTypeText+= _T("(Get Reader Status)");break;
	case  Def_RUNATCOMMAND	 :         csTypeText+= _T("(Run Command)");break;
	case  Def_LANGUAGENOTIFICATION :   csTypeText+= _T("(Language Notification)");break;
	case  Def_OPENCHANNEL	 :         csTypeText+= _T("(Open Channel)");break;
	case  Def_CLOSECHANNEL	 :         csTypeText+= _T("(Close Channel)");break;
	case  Def_RECEIVEDATA	 :         csTypeText+= _T("(Receive Data)");break;
	case  Def_SENDDATA	 :             csTypeText+= _T("(Send Data)");break;
	case  Def_GETCHANNELSTATUS :       csTypeText+= _T("(Get Channel Status)");break;
	default:bRet = FALSE;break;
	}
	return bRet;
}
BOOL _TranslateProactiveSIMCommandQualifier(int iCommandType,int iCommandQualifier,CString &csQualifierText)
{
	BOOL bRet = TRUE;
	switch(iCommandType)
	{
	case  Def_REFRESH   :
		switch(iCommandQualifier)
		{
		case 00:csQualifierText+= _T("(SIM Initialization and Full File Change Notification)");break;
		case 01:csQualifierText+= _T("(File Change Notification)");break;
		case 02:csQualifierText+= _T("(SIM Initialization and File Change Notification)");break;
		case 03:csQualifierText+= _T("(SIM Initialization)");break;
		case 04:csQualifierText+= _T("(SIM Reset)");break;
		default:csQualifierText+= _T("(reserved values)");break;	
		}break;
	case  Def_SETUPCALL :             
		switch(iCommandQualifier)
		{
		case 00:csQualifierText+= _T("(set up call, but only if not currently busy on another call)");break;
		case 01:csQualifierText+= _T("(set up call, but only if not currently busy on another call, with redial)");break;
		case 02:csQualifierText+= _T("(set up call, putting all other calls (if any) on hold)");break;
		case 03:csQualifierText+= _T("(set up call, putting all other calls (if any) on hold, with redial");break;
		case 04:csQualifierText+= _T("(set up call, disconnecting all other calls (if any))");break;
		case 05:csQualifierText+= _T("(set up call, disconnecting all other calls (if any), with redial)");break;
		default:csQualifierText+= _T("(reserved values)");break;	
		}break;
	case  Def_SENDSHORTMESSAGE :   
		if (iCommandQualifier&1)
			csQualifierText+= _T("(SMS packing by the ME required)");
		else
			csQualifierText+= _T("(packing not required)");
		break;
	case  Def_DISPLAYTEXT :           
		if (iCommandQualifier&1)
			csQualifierText+= _T("(high priority)");
		else
			csQualifierText+= _T("(normal priority)");
		if ((iCommandQualifier&0x80) == 0x80)
			csQualifierText+= _T("(wait for user to clear message)");
		else
			csQualifierText+= _T("(clear message after a delay)");
		break;
	case  Def_GETINKEY :              
		if ((iCommandQualifier&1) == 1)
			csQualifierText+= _T("(alphabet set)");
		else
			csQualifierText+= _T("(digits (0 9, *, # and +) only)");
		if ((iCommandQualifier&2) == 2)
			csQualifierText+= _T("(UCS2 alphabet)");
		else
			csQualifierText+= _T("(SMS default alphabet)");
		break;
		if ((iCommandQualifier&4) == 4)
			csQualifierText+= _T("(character sets defined by bit 1 and bit 2 are disabled and the \"Yes/No\" response is requested)");
		else
			csQualifierText+= _T("(character sets defined by bit 1 and bit 2 are enabled)");
		break;	
		if ((iCommandQualifier&0x80) == 0x80)
			csQualifierText+= _T("(help information available)");
		else
			csQualifierText+= _T("(no help information available)");
		break;	
	case  Def_GETINPUT :               
		
		if ((iCommandQualifier&1) == 1)
			csQualifierText+= _T("(alphabet set)");
		else
			csQualifierText+= _T("(digits (0 9, *, # and +) only)");
		if ((iCommandQualifier&2) == 2)
			csQualifierText+= _T("(UCS2 alphabet");
		else
			csQualifierText+= _T("(SMS default alphabet)");
		break;
		if ((iCommandQualifier&4) == 4)
			csQualifierText+= _T("(user input shall not be revealed in any way)");
		else
			csQualifierText+= _T("(ME may echo user input on the display)");
		break;	
		if ((iCommandQualifier&8) == 8)
			csQualifierText+= _T("(user input to be in SMS packed format)");
		else
			csQualifierText+= _T("user input to be in unpacked format)");
		break;	
		if ((iCommandQualifier&0x80) == 0x80)
			csQualifierText+= _T("(help information available)");
		else
			csQualifierText+= _T("(no help information available)");	
		break;
	
	case  Def_SELECTITEM :
		if ((iCommandQualifier&1) == 1)
			csQualifierText+= _T("(presentation type is specified in bit 2)");
		else
			csQualifierText+= _T("(presentation type is not specified)");
		if ((iCommandQualifier&2) == 2)
			csQualifierText+= _T("(presentation as a choice of navigation options if bit 1 is \'1\')");
		else
			csQualifierText+= _T("(presentation as a choice of data values if bit 1 = \'1\')");
		break;
		if ((iCommandQualifier&4) == 4)
			csQualifierText+= _T("(selection  using soft key preferred)");
		else
			csQualifierText+= _T("(no selection preference) ");
		break;	
		if ((iCommandQualifier&0x80) == 0x80)
			csQualifierText+= _T("(help information available)");
		else
			csQualifierText+= _T("(no help information available)");	
		break;
	case  Def_SETUPMENU :           
		
		if ((iCommandQualifier&1) == 1)
			csQualifierText+= _T("(selection  using soft key preferred)");
		else
			csQualifierText+= _T("(no selection preference)");
		if ((iCommandQualifier&0x80) == 0x80)
			csQualifierText+= _T("help information available)");
		else
			csQualifierText+= _T("(no help information available)");	
		break;
	case  Def_PROVIDELOCALINFORMATION :
		switch(iCommandQualifier)
		{
		case 00:csQualifierText+= _T("(Location Information (MCC, MNC, LAC and Cell Identity)");break;
		case 01:csQualifierText+= _T("(IMEI of the ME)");break;
		case 02:csQualifierText+= _T("(Network Measurement results)");break;
		case 03:csQualifierText+= _T("(Date, time and time zone");break;
		case 04:csQualifierText+= _T("(Language setting)");break;
		case 05:csQualifierText+= _T("(Timing Advance");break;
		default:csQualifierText+= _T("(Reserved)");break;	
		}break;
	case  Def_GETREADERSTATUS	 :    
		if ((iCommandQualifier&1) == 1)
			csQualifierText+= _T("(Card reader identifier)");
		else
			csQualifierText+= _T("(Card reader status)");
		break;
	case  Def_TIMERMANAGEMENT :  
		switch(iCommandQualifier&3)
		{
		case 00:csQualifierText+= _T("(start)");break;
		case 01:csQualifierText+= _T("(deactivate)");break;
		case 02:csQualifierText+= _T("(get current value)");break;
		case 03:csQualifierText+= _T("(RFU)");break;
		}break;
	case  Def_LANGUAGENOTIFICATION	 :         
		if ((iCommandQualifier&1) == 1)
			csQualifierText+= _T("(specific language notification)");
		else
			csQualifierText+= _T("(non-specific language notification)");
		break;
	
	case  Def_LAUNCHBROWSER	 :         
		switch(iCommandQualifier)
		{
		case 00:csQualifierText+= _T("(launch browser, if not already launched)");break;
		case 01:csQualifierText+= _T("(not used)");break;
		case 02:csQualifierText+= _T("(use the existing browser (the browser shall not use the active existing secured session))");break;
		case 03:csQualifierText+= _T("(close the existing browser session and launch new browser session");break;
		case 04:csQualifierText+= _T("(not used)");break;
		default:csQualifierText+= _T("(RFU)");break;	
		}break;
	case  Def_OPENCHANNEL	 :         
		if ((iCommandQualifier&1) == 1)
			csQualifierText+= _T("(immediate link establishment)");
		else
			csQualifierText+= _T("(on demand link establishment)");
		if ((iCommandQualifier&2) == 2)
			csQualifierText+= _T("(automatic reconnection)");
		else
			csQualifierText+= _T("(no automatic reconnection)");
		break;
	case  Def_SENDDATA	 :
		if ((iCommandQualifier&1) == 1)
			csQualifierText+= _T("(Send data immediately)");
		else
			csQualifierText+= _T("(store data in Tx buffer)");
		break;
	default:bRet = FALSE;break;
	}
	return bRet;
}
BOOL _ExplainCommandDetails(CString csCommandDetails,CStringArray&csOutput)
{
	CString csTypeText,csQualifierText;
	CString csPreText;
	BOOL bRet = TRUE;
	int iCommandType = _CString2Int(csCommandDetails.Mid(02,02));

	csPreText = _T("Command Number \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csCommandDetails.Mid(00,02));

	csPreText = _T("Command Type \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csTypeText= csPreText +csCommandDetails.Mid(02,02);

	csPreText = _T("Command Qualifier \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csQualifierText =csPreText+csCommandDetails.Mid(04,02);

	if(_TranslateProactiveSIMCommandType(iCommandType, csTypeText))
		_TranslateProactiveSIMCommandQualifier(iCommandType,_CString2Int(csCommandDetails.Mid(04,02)),csQualifierText);
	else
		bRet = FALSE;

	csOutput.Add(csTypeText);
	csOutput.Add(csQualifierText);

	return bRet;
}
BOOL _TranslateDeviceIdentity(int iDeviceIdentity,CString&DeviceTxext)
{
	//-	'01' = Keypad
	//	-	'02' = Display
	//	-	'03' = Earpiece
	//	-	'10' to '17' = Additional Card Reader x (0 to 7). Value assigned by ME.
	//	-	'21' to '27' = Channel x (1 to 7). Value assigned by ME (if class "e" is supported).
	//	-	'81' = SIM
	//	-	'82' = ME
	//	-	'83' = Network
	BOOL bRet= TRUE;
	switch(iDeviceIdentity)
	{
	case 1:DeviceTxext = _T("(Keypad)");break;
	case 2:DeviceTxext = _T("(Display)");break;
	case 3:DeviceTxext = _T("(Earpiece)");break;

	case 0x81:DeviceTxext = _T("(SIM)");break;
	case 0x82:DeviceTxext = _T("(ME)");break;
	case 0x83:DeviceTxext = _T("(Network)");break;
	default:
		if ((iDeviceIdentity>0xF)&&(iDeviceIdentity<0x18))
		{
		
			_Int2CString(iDeviceIdentity&0x7,DeviceTxext,1);
			DeviceTxext = _T("(Additional Card Reader ")+
				          DeviceTxext+
						  _T(".Value assigned by ME.)");
		}else if ((iDeviceIdentity>0x20)&&(iDeviceIdentity<0x28))
		{
			_Int2CString(iDeviceIdentity&0x7,DeviceTxext,1);
			DeviceTxext = _T("(Channel ")+
				          DeviceTxext+
						  _T(". Value assigned by ME (if class \"e\" is supported).)");
		}
		else
			bRet = FALSE;

	}

	return bRet;
}
BOOL _ExplainDeviceIdentitys(CString csDeviceIdentity,CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	if (csDeviceIdentity.GetLength()!= 4)
		return FALSE;

	if (!_TranslateDeviceIdentity(_CString2Int(csDeviceIdentity.Mid(0,2)),csText))
		csText.Empty();

	csPreText = _T("Source device identity \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csDeviceIdentity.Mid(0,2)+ csText);
	if (!_TranslateDeviceIdentity(_CString2Int(csDeviceIdentity.Mid(2,2)),csText))
		csText.Empty();
	csPreText = _T("Destination device identity \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csDeviceIdentity.Mid(2,2)+ csText);

	return bRet;
}
BOOL _ExplainDuration(CString csDuration,CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	if (csDuration.GetLength()!= 4)
		return FALSE;

	csPreText = _T("Time unit \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	switch(_CString2Int(csDuration.Left(2)))
	{
	case 0:csText =_T("Minutes");break;
	case 1:csText =_T("Seconds");break;
	case 2:csText =_T("Tenths of seconds");break;
	default:csText =_T("reserved");break;
	}
	csOutput.Add(csPreText+csDuration.Mid(0,2)+ csText);

	csPreText = _T("Time interval \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);

	_Int2CStringDecimal(_CString2Int(csDuration.Mid(2,2)),csText);
	csOutput.Add(csPreText+csText);

	return bRet;

}
BOOL _ExplainResult(CString csResult, CStringArray&csOutput)
{

	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	csPreText = _T("Result \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	/*'  00' = Command performed successfully;
	-	'01' = Command performed with partial comprehension;
	-	'02' = Command performed, with missing information;
	-	'03' = REFRESH performed with additional EFs read;
	-	'04'= Command performed successfully, but requested icon could not be displayed;
	-	'05' = Command performed, but modified by call control by SIM;
	-	'06' = Command performed successfully, limited service;
	-	'07' = Command performed with modification (if class "e" is supported);
	-	'10' = Proactive SIM session terminated by the user;
	-	'11' = Backward move in the proactive SIM session requested by the user;
	-	'12' = No response from user;
	-	'13' = Help information required by the user;
	-	'14' = USSD or SS transaction terminated by the user.
	Results '0X' and '1X' indicate that the command has been performed.
	-	'20' = ME currently unable to process command;
	-	'21' = Network currently unable to process command;
	-	'22' = User did not accept the proactive command;
	-	'23' = User cleared down call before connection or network release;
	-	'24' = Action in contradiction with the current timer state;
	-	'25' = Interaction with call control by SIM, temporary problem;
	-	'26' = Launch browser generic error code.
	Results '2X' indicate to the SIM that it may be worth re-trying the command at a later opportunity.
	-	'30' = Command beyond ME's capabilities;
	-	'31' = Command type not understood by ME;
	-	'32' = Command data not understood by ME;
	-	'33' = Command number not known by ME;
	-	'34' = SS Return Error;
	-	'35' = SMS RP-ERROR;
	-	'36' = Error, required values are missing;
	-	'37' = USSD Return Error;
	-	'38' = MultipleCard commands error, if class "a" is supported;
	-	'39' = Interaction with call control by SIM or MO short message control by SIM, permanent problem;
	-	'3A' = Bearer Independent Protocol error (if class "e" is supported).*/

	switch(_CString2Int(csResult.Left(2)))
	{
	case 0:csText =_T("Command performed successfully");break;
	case 1:csText =_T("Command performed with partial comprehension");break;
	case 2:csText =_T("Command performed, with missing information");break;
	case 3:csText =_T("REFRESH performed with additional EFs read");break;
	case 4:csText =_T("Command performed successfully, but requested icon could not be displayed");break;
	case 5:csText =_T("Command performed, but modified by call control by SIM");break;
	case 6:csText =_T("Command performed successfully, limited service");break;
	case 7:csText =_T("Command performed with modification (if class \"e\" is supported)");break;
	case 0x10:csText =_T("Proactive SIM session terminated by the user");break;
	case 0x11:csText =_T("Backward move in the proactive SIM session requested by the user");break;
	case 0x12:csText =_T("No response from user");break;
	case 0x13:csText =_T("Help information required by the user");break;
	case 0x14:csText =_T("USSD or SS transaction terminated by the user");break;
	case 0x20:csText =_T("ME currently unable to process command");break;
	case 0x21:csText =_T("Network currently unable to process command");break;
	case 0x22:csText =_T("User did not accept the proactive command");break;
	case 0x23:csText =_T("User cleared down call before connection or network release");break;
	case 0x24:csText =_T("Action in contradiction with the current timer state");break;
	case 0x25:csText =_T("Interaction with call control by SIM, temporary problem");break;
	case 0x26:csText =_T("Launch browser generic error code");break;
	case 0x30:csText =_T("Command beyond ME's capabilities");break;
	case 0x31:csText =_T("Command type not understood by ME");break;
	case 0x32:csText =_T("Command data not understood by ME");break;
	case 0x33:csText =_T("Command number not known by ME");break;
	case 0x34:csText =_T("SS Return Error");break;
	case 0x35:csText =_T("SMS RP-ERROR");break;
	case 0x36:csText =_T("Error, required values are missing");break;
	case 0x37:csText =_T("USSD Return Error");break;
	case 0x38:csText =_T("MultipleCard commands error, if class \"a\" is supported");break;
	case 0x39:csText =_T("Interaction with call control by SIM or MO short message control by SIM, permanent problem");break;
	case 0x3A:csText =_T("Bearer Independent Protocol error (if class \"e\" is supported)");break;
	default:csText =_T("reserved");break;
	}
	csText= _T("(")+csText+_T(")");
	csOutput.Add(csPreText+csResult+csText);
	return bRet;
}
BOOL _ExplainAlphaIdentifier(CString csAlphaIdentifier, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	csPreText = _T("Alpha Identifier \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	_TranslateAlphaIdentifier(csAlphaIdentifier,csText);
	csText= _T("(")+csText+_T(")");
	csOutput.Add(csPreText+csAlphaIdentifier+csText);
	return bRet;

}
BOOL _ExplainAddress(CString csAddress, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	csPreText = _T("Address \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csText.Format("%2X",csAddress.GetLength());
	_TranslateAddress(csText+csAddress,csText);
	csOutput.Add(csPreText+csText);

	//csPreText = _T("TON and NPI \\- ");
	////__APDUExplainFormat(csPreText,Def_Min_Formate_Length);

	//_TranslateTONNPI(csAddress.Left(02),csText);
	//csText= _T("(")+csText+_T(")");
	//csOutput.Add(csPreText+csAddress.Left(02)+csText);

	//csPreText = _T("Dialling number string \\- ");
	////__APDUExplainFormat(csPreText,Def_Min_Formate_Length);

	//_TranslateAddress(csAddress.Mid(02),csText);
	//csText= _T("(")+csText+_T(")");
	//csOutput.Add(csPreText+csAddress.Mid(02)+csText);

	return bRet;

}
BOOL _ExplainCapabilityConfigurationParameters(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	csPreText = _T("Capability Configuration Parameters \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);
	return bRet;
}
BOOL _ExplainSubAddress(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	csPreText = _T("Sub Address \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);
	return bRet;

}
BOOL _ExplainSSString(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	csPreText = _T("SS String \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);
	return bRet;

}
BOOL _ExplainUSSDString(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	csPreText = _T("USSD String \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);
	return bRet;

}




BOOL _ExplainSMSTPDU(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	csPreText = _T("SMSTPDU \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);

	switch(_CString2Int(csInput.Mid(0,2))&0x3)
	{
	case 0:bRet =_ExplainSMSDeliver(csInput,csOutput);break;
	case 2:bRet =_ExplainSMSCommand(csInput,csOutput);break;
	case 1:bRet =_ExplainSMSSubmit(csInput,csOutput);break;
	}

	return bRet;

}
BOOL _ExplainSMSDeliver(CString csInput, CStringArray&csOutput)
{

	BOOL bRet = TRUE;
	CString csPreText;
	CString csText;
	int iOALen;
	int iDCS,iUDHI;
	csPreText = _T("TP-MTI \\- ");

	_Int2CString(_Getbit(csInput,2)*2 +_Getbit(csInput,1) ,csText,2);
	csText = csText + _T("(SMS-DELIVER)");
	csOutput.Add(csPreText+csText);

	csPreText = _T("TP-MMS \\- ");

	if ( _Getbit(csInput,3))
		csText = _T("1(No more messages are waiting for the MS in this SC)");
	else
		csText = _T("0(More messages are waiting for the MS in this SC)");

	csOutput.Add(csPreText+csText);



	csPreText = _T("TP-SRI \\- ");

	if ( _Getbit(csInput,6))
		csText = _T("1(A status report shall be returned to the SME)");
	else
		csText =_T("0(A status report shall not be returned to the SME)");

	csOutput.Add(csPreText+csText);


	csPreText = _T("TP-UDHI \\- ");

	if ( _Getbit(csInput,7))
		csText = _T("1(The beginning of the TP-UD field contains a Header in addition to the short message)");
	else
		csText = _T("0(The TP-UD field contains only the short message)");
	csOutput.Add(csPreText+csText);

	iUDHI = (int)_Getbit(csInput,7);

	csPreText = _T("TP-RP \\- ");

	if ( _Getbit(csInput,8))
		csText = _T("1(TP-Reply-Path parameter is set in this SMS-SUBMIT/DELIVER)");
	else
		csText = _T("0(TP-Reply-Path parameter is not set in this SMS-SUBMIT/DELIVER)");
	csOutput.Add(csPreText+csText);

	csPreText = _T("TP-OA \\- ");

	iOALen = _CString2Int(csInput.Mid(2,2))+4;
	if (iOALen%2)
		iOALen= iOALen+1;
	_TranslateAddress(csInput.Mid(2,iOALen),csText);
	csText = csInput.Mid(2,iOALen) +_T("(")+csText+ _T(")");
	csOutput.Add(csPreText+csText);

	//csPreText = _T("TP-PID \\- ");

	//csOutput.Add(csPreText+ csInput.Mid(iOALen+2,2));
	bRet = _ExplainProtocolIdentifier(csInput.Mid(iOALen+2,2),csOutput);

	//csPreText = _T("TP-DCS \\- ");
	//csOutput.Add(csPreText+ csInput.Mid(iOALen+4,2));
	iDCS = _CString2Int(csInput.Mid(iOALen+4,2));
	bRet =  _ExplainSMSDataCodingScheme(csInput.Mid(iOALen+4,2),csOutput);

	csPreText = _T("TP-SCTS \\- ");

	csText = csInput.Mid(iOALen+6,14);
	csText = _TranslateDateTimeAndTimeZone(csText);
	csText = _T("(")+csText+_T(")");

	csOutput.Add(csPreText+ csInput.Mid(iOALen+6,14)+csText);


	csPreText = _T("TP-UDL \\- ");

	csOutput.Add(csPreText+ csInput.Mid(iOALen+20,2));

	bRet = _ExplainUserData(csInput.Mid(iOALen+22), iDCS, iUDHI,csOutput);

	return bRet;
}
BOOL _ExplainSMSDeliverReport(CString csInput, CStringArray&csOutput)
{
	
	return TRUE;

}
BOOL _ExplainSMSStatusReport(CString csInput, CStringArray&csOutput)
{
	return TRUE;

}

BOOL _ExplainSMSCommand(CString csInput, CStringArray&csOutput)
{
	return TRUE;

}

BOOL _ExplainUserDataHead(CString csUDH,CStringArray&csOutput,BOOL&bCPI,BOOL&bRPI)
{
	bCPI = FALSE;
	bRPI = FALSE;
	int iOff = 0;
	int iTag ;
	CString csIEI;


	do 
	{
		csIEI.Empty();
		iTag = _CString2Int(csUDH.Mid(iOff,2));
		if (!_GetTLVData(csUDH,iTag,csIEI))
			return FALSE;
		if (iTag == 00)
		{
			if (csIEI.GetLength() ==  6)
			{
				csOutput.Add(_T("Reference Number \\- ")+csIEI.Mid(0,2));
				csOutput.Add(_T("Maximum Number \\- ")  +csIEI.Mid(2,2));
				csOutput.Add(_T("Sequence Number \\- ") +csIEI.Mid(4,2));
			}
			else
			{
				csOutput.Add(_T("Concatenated Short Messages \\- ")+csIEI);
				csOutput.Add(_T("Go to see 23.040//9.2.3.24.1 Concatenated Short Messages"));
			}
		}
		if (iTag == 0x70)
			bCPI = TRUE;

		if (iTag == 0x71)
			bRPI = TRUE;

		iOff += csIEI.GetLength() +4;
	} while (iOff<csUDH.GetLength());
	return TRUE;
}

BOOL _ExplainCUCOTACatalogList(CString csCalalogList,CStringArray&csOutput)
{
	CStringArray csTemp;
	CString csText;
	int iNumber = 1;
	int iOffset = 0;
	int iNameLen;
	int iLength = csCalalogList.GetLength();

	do 
	{
		iNameLen = _CString2Int(csCalalogList.Mid(iOffset+2,2));

		csTemp.Add(_T("大类数据 \\- ")+ csCalalogList.Mid(iOffset,6+iNameLen*2));

		csTemp.Add(_T("大类索引ID \\- ")+ csCalalogList.Mid(iOffset,2));
		iOffset += 2;

		if (csCalalogList.Mid(iOffset+2,2) == _T("80"))
			_TranslateUcs2(csCalalogList.Mid(iOffset+4,iNameLen*2-2),csText);
		else
			_TranslateAscii(csCalalogList.Mid(iOffset+2,iNameLen*2),csText);
		csTemp.Add(_T("大类名称 \\- ")+ csText);

		iOffset += 2;
		iOffset += iNameLen*2;


		switch(_CString2Int(csCalalogList.Mid(iOffset,2)))
		{
		case 0:csText = _T("添加");break;
		case 1:csText = _T("删除");break;
	    case 2:csText = _T("更名");break;
		case 3:csText = _T("禁用");break;
		case 4:csText = _T("启用");break;
		default:csText = csCalalogList.Mid(iOffset,2);break;

		}
		csTemp.Add(_T("操作类型 \\- ")+ csText);
		iOffset+= 2;


	} while (iLength>(iOffset+2));

	if (iLength = iOffset)
	{
		csOutput.Append(csTemp);
		return TRUE;
	}
	else
		return FALSE;

}
BOOL _ExplainCUCOTAMenuList(CString csMenuList,CStringArray&csOutput)
{
	CStringArray csTemp;
	CString csText;
	int iNumber = 1;
	int iOffset = 0;
	int iNameLen;
	int iLength = csMenuList.GetLength();


	while (iLength>(iOffset+10))
	{
		iNameLen = _CString2Int(csMenuList.Mid(iOffset+10,2));

		csTemp.Add(_T("列表数据 \\- ")+ csMenuList.Mid(iOffset,12+iNameLen*2));

		csTemp.Add(_T("菜单索引AID \\- ")+ csMenuList.Mid(iOffset,6));
		iOffset += 6;
		csTemp.Add(_T("所需空间 \\- ")+ csMenuList.Mid(iOffset,4));
		iOffset += 4;	

		if (csMenuList.Mid(iOffset+2,2) == _T("80"))
			_TranslateUcs2(csMenuList.Mid(iOffset+4,iNameLen*2-2),csText);
		else
			_TranslateAscii(csMenuList.Mid(iOffset+2,iNameLen*2),csText);
		csTemp.Add(_T("菜单名称 \\- ")+ csText);


		iOffset += 2;
		iOffset += iNameLen*2;

	} 

	if (iLength == iOffset)
	{
		csOutput.Append(csTemp);
		return TRUE;
	}
	else
		return FALSE;
}
BOOL _ExplainCUCOTAUpLoadCommand(CString csCommand,CStringArray&csOutput)
{
	BOOL iRet = TRUE;
	int iCommand,iCommandLen,iOffset;
	CString csText;
	CString csComPara;
	iCommand = _CString2Int( csCommand.Mid(0,2));

	if (!_GetTLVData(csCommand,iCommand,csComPara))
		return FALSE;
	iCommandLen = csComPara.GetLength();
	switch(iCommand)
	{
	case 1:
		if (csComPara.GetLength()== 8)
		{
			csOutput.Add(_T("用户STK卡注册 \\- ")+csCommand);
			csOutput.Add(_T("卡片发行批号 \\- ") + csComPara.Mid(0,2));
			csOutput.Add(_T("可用空间 \\- ")     + csComPara.Mid(2,6));
		}
		else
			iRet = FALSE;
		break;
	case 2:
		if (csComPara.GetLength()== 4)
		{
			csOutput.Add(_T("用户MO获取可下载列表 \\- ")+csCommand);
			csOutput.Add(_T("大类索引 \\- ") + csComPara.Mid(0,2));
			csOutput.Add(_T("当前列表页码 \\- ")+ csComPara.Mid(2,2));
		}
		else
			iRet = FALSE;
		break;

	case 3:
		if (csComPara.GetLength()== 12)
		{
			csOutput.Add(_T("用户MO菜单下载 \\- ")+csCommand);
			csOutput.Add(_T("菜单索引 \\- ") + csComPara.Mid(0,6));
			csOutput.Add(_T("可用空间 \\- ")+ csComPara.Mid(6,6));
		}
		else
			iRet = FALSE;
		break;
	case 4:
		if ((csComPara.GetLength()%6) == 0)
		{
			csOutput.Add(_T("用户MO菜单删除 \\- ")+csCommand);
			csOutput.Add(_T("短信总数 \\- ") + csComPara.Mid(0,2));
			csOutput.Add(_T("短信索引 \\- ")+ csComPara.Mid(2,2));
			csOutput.Add(_T("本条短信中删除的菜单索引总数 \\- ")+ csComPara.Mid(4,2));

			if ((_CString2Int(csComPara.Mid(4,2))*6 + 6) == iCommandLen)
			{

				for(int i = 1 ; i <=_CString2Int(csComPara.Mid(4,2)) ;i++)
				{
					csText.Format("%d",i);
					csOutput.Add(_T("删除的菜单索引")+csText+_T(" \\- ")+ csComPara.Mid(6*i,6));
				}

			}
			else
				iRet = FALSE;

		}
		else
			iRet = FALSE;

		break;

	case 5:


		csOutput.Add(_T("STK卡状态查询响应 \\- ")+csCommand);
		csOutput.Add(_T("短信总数 \\- ") + csComPara.Mid(0,2));
		csOutput.Add(_T("短信索引 \\- ")+ csComPara.Mid(2,2));
		csOutput.Add(_T("本条短信中删除的菜单索引总数 \\- ")+ csComPara.Mid(4,2));

		if ((_CString2Int( csComPara.Mid(4,2) ) *2 +6)> iCommandLen)
			goto _Return_FALSE;

		iOffset = 6;

		for(int i = 1 ; i <=_CString2Int(csComPara.Mid(4,2)) ;i++)
		{
			csText.Format("%d",i);
			csOutput.Add(_T("大类索引")+csText+_T(" \\- ")+ csComPara.Mid(iOffset,2));
			iOffset += 2;
		}

		csOutput.Add(_T("本条短信菜单索引总数 \\- ")+ csComPara.Mid(iOffset,2));

		if ((_CString2Int( csComPara.Mid(iOffset,2) )*6 +iOffset+2)> iCommandLen)
			goto _Return_FALSE;


		for(int i = 1 ; i <=_CString2Int(csComPara.Mid(iOffset,2)) ;i++)
		{
			csText.Format("%d",i);
			csOutput.Add(_T("菜单索引")+csText+_T(" \\- ")+ csComPara.Mid(iOffset-4+i*6,6));
		}

		break;
	case 6:
		if ((csComPara.GetLength()<30)&&(csComPara.GetLength()>10))
		{
			csOutput.Add(_T("用户MO菜单搜索 \\- ")+csCommand);
			csOutput.Add(_T("大类索引 \\- ") + csComPara.Mid(0,2));
			csOutput.Add(_T("当前请求页码 \\- ")+ csComPara.Mid(2,2));	

			if (csComPara.Mid(4,2) == _T("80"))
				_TranslateUcs2(csComPara.Mid(6),csText);
			else if (csComPara.Mid(4,2) == _T("04"))
				_TranslateAscii(csComPara.Mid(6),csText);
			else
				csText =  csComPara.Mid(4);		
			csOutput.Add(_T("关键字 \\- ")+csText);
		}
		else
			iRet = FALSE;
		break;

	case 7:
		if ((csComPara.GetLength()%10) == 6)
		{
			csOutput.Add(_T("用户MO菜单使用次数通知 \\- ")+csCommand);
			csOutput.Add(_T("短信总数 \\- ") + csComPara.Mid(0,2));
			csOutput.Add(_T("短信索引 \\- ")+ csComPara.Mid(2,2));
			csOutput.Add(_T("本条短信菜单索引总数 \\- ")+ csComPara.Mid(4,2));

			if ((_CString2Int(csComPara.Mid(4,2))*10 + 6) == iCommandLen)
			{
				for(int i = 1 ; i <=_CString2Int(csComPara.Mid(4,2)) ;i++)
				{
					csText.Format("%d",i);
					csOutput.Add(_T("菜单索引")+csText+_T(" \\- ")+ csComPara.Mid(10*(i-1)+6,6));
					csOutput.Add(_T("菜单索引")+csText+_T("使用次数 \\- ")+ csComPara.Mid(10*(i-1)+6+6,4));
				}
			}
			else
				iRet = FALSE;

		}
		else
			iRet = FALSE;

		break;

	case 8:
		if (csComPara.GetLength()== 4)
		{
			csOutput.Add(_T("远程文件更新确认 \\- ") +csCommand);
			csOutput.Add(_T("远程文件更新批次 \\- ") + csComPara.Mid(0,2));
			csOutput.Add(_T("更新结果 \\- ")         + csComPara.Mid(2,2));
		}
		else
			iRet = FALSE;
		break;
	default: return FALSE;
	}


	return TRUE;
_Return_FALSE:
	return FALSE;

}
BOOL _ExplainCUCOTAUpLoad(CString csUD,CStringArray&csOutput)
{
	CStringArray csTemp;
	CString csCommand;

	if (csUD.GetLength()<52)
		return FALSE;
	csTemp.Add(_T("卡商代码及协议版本号 \\- ")+ csUD.Mid(0,2));
	csTemp.Add(_T("用户品牌标识 \\- ")+ csUD.Mid(2,4));
	csTemp.Add(_T("卡片ICCID \\- ")+ csUD.Mid(6,16));
	csTemp.Add(_T("序列号 \\- ")+ csUD.Mid(22,10));
	csTemp.Add(_T("随机数 \\- ")+ csUD.Mid(32,8));
	csTemp.Add(_T("MAC \\- ")   + csUD.Mid(40,8));

	csCommand = csUD.Mid(48);

	if (_ExplainCUCOTAUpLoadCommand(csCommand,csTemp))
	{
		csOutput.Append(csTemp);
		return TRUE;
	}
	else return FALSE;

}
BOOL _ExplainCUCOTADownLoadCommandDeleteMenu( CString csCommand, CStringArray &csOutput )
{
	CString csText;
	CString csComPara;
	int iCommandLen;
	BOOL iRet = TRUE;
	_GetTLVData(csCommand,_CString2Int(csCommand.Mid(0,2)),csComPara);
	iCommandLen = csComPara.GetLength();
	if ((csComPara.GetLength()%6) == 4)
	{

		csOutput.Add(_T("菜单删除 \\- ")+csCommand);

		if (_Getbit(csComPara,1))
			csText = _T("MT业务删除 ");
		else
			csText = _T("网上删除 ");

		if (_Getbit(csComPara,2))
			csText += _T("删除列出项");
		else
			csText += _T("删除所有业务");
		csText = _T("(")+csText+_T(")");

		csOutput.Add(_T("命令细节 \\- ")+csComPara.Mid(0,2)+csText);

		csOutput.Add(_T("删除的菜单索引总数 \\- ")+csComPara.Mid(2,2));

		if (iCommandLen == (_CString2Int(csComPara.Mid(2,2))*6+4))
		{
			for (int i = 0 ; i < _CString2Int(csComPara.Mid(2,2)) ; i ++)
			{
				csText.Format("%d",i+1);
				csOutput.Add(_T("删除的菜单索引")+csText+_T(" \\- ")+ csComPara.Mid(6*i+4,6));
			}
		}
		else
			iRet = FALSE;
	}
	else
		iRet = FALSE;		

	return iRet;
}
BOOL _ExplainCUCOTADownLoadCommandSearch( CString csCommand, CStringArray &csOutput )
{
	CString csText;
	CString csComPara;
	int iCommandLen;
	int iTemp;
	BOOL iRet;
	_GetTLVData(csCommand,_CString2Int(csCommand.Mid(0,2)),csComPara);
	iCommandLen = csComPara.GetLength();

	csOutput.Add(_T("菜单搜索结果 \\- ")+csCommand);
	csOutput.Add(_T("大类索引 \\- ")+csComPara.Mid(0,2));

	iTemp = _CString2Int(csComPara.Mid(2,2))*2;
	if (iCommandLen< iTemp+10)
		return FALSE;
	csOutput.Add(_T("关键字 \\- ")+csComPara.Mid(4,iTemp));
	csOutput.Add(_T("匹配记录总页数 \\- ")+csComPara.Mid(4+iTemp,2));
	csOutput.Add(_T("当前页码 \\- ")+csComPara.Mid(6+iTemp,2));
	csOutput.Add(_T("列表数据总数 \\- ")+csComPara.Mid(8+iTemp,2));
	//csOutput.Add(_T("列表数据 \\- ")+csComPara.Mid(10+iTemp));
	iRet = _ExplainCUCOTAMenuList(csComPara.Mid(10+iTemp),csOutput);
	return iRet;
}
//包含随机数和序列号方向和Command
BOOL _ExplainCUCOTADownLoadCommand(CString csCommand,CStringArray&csOutput)
{

	BOOL iRet = TRUE;
	int iCommand,iCommandLen;
	CString csText;
	CString csComPara;
	iCommand = _CString2Int( csCommand.Mid(0,2));
	if (!_GetTLVData(csCommand,iCommand,csComPara))
		return FALSE;
	iCommandLen = csComPara.GetLength();
	switch(iCommand)
	{
	case 1:
		if (iCommandLen== 00)
			csOutput.Add(_T("用户注册确认 \\- ")+csCommand);
		else
			iRet = FALSE;
		break;
	case 2:
		if (iCommandLen>=4)
		{
			csOutput.Add(_T("列表更新 \\- ")+csCommand);
			csOutput.Add(_T("当前列表页码 \\- ")+csComPara.Mid(0,2));
			csOutput.Add(_T("列表数据总数 \\- ")+csComPara.Mid(2,2));
			//csOutput.Add(_T("列表数据 \\- ")+csComPara.Mid(4));
			iRet = _ExplainCUCOTAMenuList(csComPara.Mid(4),csOutput);
		}
		else
			iRet = FALSE;
		break;

	case 3:
		if (iCommandLen>20)
		{
			csOutput.Add(_T("菜单下载 \\- ")+csCommand);
			csOutput.Add(_T("菜单索引 \\- ")+csComPara.Mid(0,6));
			csOutput.Add(_T("下载任务批次 \\- ")+csComPara.Mid(6,2));
			csOutput.Add(_T("短信总数 \\- ")+csComPara.Mid(8,2));
			csOutput.Add(_T("短信索引 \\- ")+csComPara.Mid(10,2));
			csOutput.Add(_T("应用数据空间 \\- ")+csComPara.Mid(12,4));
			csOutput.Add(_T("应用数据地址偏移 \\- ")+csComPara.Mid(16,4));
			csOutput.Add(_T("应用数据 \\- ")+csComPara.Mid(20));
		}
		else
			iRet = FALSE;
		break;
	case 4:iRet = _ExplainCUCOTADownLoadCommandDeleteMenu(csCommand,csOutput);break;
	case 5:
		if (iCommandLen== 00)
			csOutput.Add(_T("卡内状态查询请求 \\- ")+csCommand);
		else
			iRet = FALSE;
		break;
	case 6:iRet = _ExplainCUCOTADownLoadCommandSearch(csCommand,csOutput);break;
	case 7:
		if (iCommandLen== 00)
			csOutput.Add(_T("菜单使用次数查询 \\- ")+csCommand);
		else
			iRet = FALSE;
		break;

	case 9:
		csOutput.Add(_T("远程大类管理 \\- ")+csCommand);
		csOutput.Add(_T("大类总数 \\- ")+csComPara.Mid(0,2));
		iRet = _ExplainCUCOTACatalogList(csComPara.Mid(2),csOutput);
		break;
	case 10:
		if (iCommandLen >= 20)
		{
			csOutput.Add(_T("菜单更新 \\- ")+csCommand);
			csOutput.Add(_T("菜单索引AID \\- ")+csComPara.Mid(0,6));
			csOutput.Add(_T("批次 \\- ")+csComPara.Mid(6,2));
			csOutput.Add(_T("短信总数 \\- ")+csComPara.Mid(8,2));
			csOutput.Add(_T("短信索引 \\- ")+csComPara.Mid(10,2));
			csOutput.Add(_T("应用数据所需空间 \\- ")+csComPara.Mid(12,4));
			csOutput.Add(_T("应用数据地址偏移 \\- ")+csComPara.Mid(16,4));
			csOutput.Add(_T("应用数据 \\- ")+csComPara.Mid(20));
		}
		else
			iRet = FALSE;
		break;


	case 11:
		if (iCommandLen >= 20)
		{
			csOutput.Add(_T("变量菜单下载 \\- ")+csCommand);
			csOutput.Add(_T("菜单索引 \\- ")+csComPara.Mid(0,6));
			csOutput.Add(_T("批次 \\- ")+csComPara.Mid(6,2));
			csOutput.Add(_T("短信总数 \\- ")+csComPara.Mid(8,2));
			csOutput.Add(_T("短信索引 \\- ")+csComPara.Mid(10,2));
			csOutput.Add(_T("变量菜单数据空间 \\- ")+csComPara.Mid(12,4));
			csOutput.Add(_T("变量菜单数据地址偏移 \\- ")+csComPara.Mid(16,4));
			csOutput.Add(_T("变量菜单数据 \\- ")+csComPara.Mid(20));
		}
		else
			iRet = FALSE;
		break;
	}

	return TRUE;
}
BOOL _ExplainCUCOTADownLoad(CString csCommand,CStringArray&csOutput)
{

	CStringArray csTemp;

	if (csCommand.GetLength()<14)
		return FALSE;

	csTemp.Add(_T("随机数 \\- ")+ csCommand.Mid(0,8));


	csTemp.Add(_T("序列号类型标识 \\- ")+ csCommand.Mid(8,2));	
	if (_ExplainCUCOTADownLoadCommand(csCommand.Mid(10),csTemp))
	{
		csOutput.Append(csTemp);
		return TRUE;
	}

	return FALSE;

}

BOOL _ExplainCUCRFMDownLoad( CString csCommand,CStringArray&csOutput)
{

	CStringArray csTemp;

	if (csCommand.GetLength()<8)
		return FALSE;

	csTemp.Add(_T("随机数 \\- ")+ csCommand.Mid(0,8));

	csTemp.Add(_T("Secured Data \\- ")+ csCommand.Mid(8));

	csOutput.Append(csTemp);
	return TRUE;

}


BOOL _ExplainCMCCSIMAUTH( CString csCommand,CStringArray&csOutput)
{
	CStringArray csTemp;
	CString csComPara;
	int iCommandTag = _CString2Int(csCommand.Mid(0,2));
	if (!_GetTLVData(csCommand,iCommandTag,csComPara))
		return FALSE;
	if (csCommand.GetLength() != csComPara.GetLength()+4)
		return FALSE;
	int iCommandLen = csComPara.GetLength();
	int iLen,iOff;
	switch(iCommandTag)
	{
	case 0x2D:
		if (iCommandLen != 26)
			return FALSE;
		csTemp.Add(_T("快捷确认操作 \\- 卡信息上报响应"));
		csTemp.Add(_T("应用协议版本号 \\- ")+ csComPara.Mid(0,2));
		csTemp.Add(_T("TransactionID \\- ")+ csComPara.Mid(2,16));
		csTemp.Add(_T("MAC \\- ")+ csComPara.Mid(18,8));
		break;
	case 0x2C:
		if (iCommandLen < 28)
			return FALSE;
		csTemp.Add(_T("快捷确认操作 \\- 口令重置请求"));
		csTemp.Add(_T("应用协议版本号 \\- ")+ csComPara.Mid(0,2));
		csTemp.Add(_T("TransactionID \\- ")+ csComPara.Mid(2,16));

		iLen = _CString2Int( csComPara.Mid(18,2));
		if (iCommandLen < (28+ iLen+2))
			return FALSE;

		csTemp.Add(_T("认证平台接入号 \\- ")+ csComPara.Mid(20,iLen+2));
		csTemp.Add(_T("MAC \\- ")+ csComPara.Mid(20+iLen+2,8));
		break;

	case 0x2B:
		if (iCommandLen < 32)
			return FALSE;

		csTemp.Add(_T("快捷确认操作 \\- 确认请求"));
		csTemp.Add(_T("应用协议版本号 \\- ")+ csComPara.Mid(0,2));
		csTemp.Add(_T("TransactionID \\- ")+ csComPara.Mid(2,16));
		csTemp.Add(_T("认证类型标识 \\- ")+ csComPara.Mid(18,2));
		iLen = _CString2Int( csComPara.Mid(20,2));

		if (iCommandLen < (32+ iLen*2))
			return FALSE;

		csTemp.Add(_T("认证数据内容 \\- ")+ csComPara.Mid(22,iLen*2));
		iOff = iLen*2 +22;
		iLen = _CString2Int( csComPara.Mid(iOff,2));
		iOff += 2;

		if (iCommandLen < (iOff+ iLen+2+8))
			return FALSE;

		csTemp.Add(_T("认证平台接入号 \\- ")+ csComPara.Mid(iOff,iLen+2));
		csTemp.Add(_T("MAC \\- ")+ csComPara.Mid(iOff+iLen+2,8));

		break;



	case 0x0D:
		if (iCommandLen != 70)
			return FALSE;
		csTemp.Add(_T("快捷确认操作 \\- 卡信息上报请求"));
		csTemp.Add(_T("应用协议版本号 \\- ")+ csComPara.Mid(0,2));
		csTemp.Add(_T("TransactionID \\- ")+ csComPara.Mid(2,16));
		csTemp.Add(_T("空卡序列号 \\- ")+ csComPara.Mid(20,20));
		csTemp.Add(_T("ICCID \\- ")+ csComPara.Mid(42,20));
		csTemp.Add(_T("MAC \\- ")+ csComPara.Mid(62,8));
		break;

	case 0x0C:
		if (iCommandLen != 26)
			return FALSE;
		csTemp.Add(_T("快捷确认操作 \\- 口令重置响应"));
		csTemp.Add(_T("应用协议版本号 \\- ")+ csComPara.Mid(0,2));
		csTemp.Add(_T("TransactionID \\- ")+ csComPara.Mid(2,16));
		csTemp.Add(_T("MAC \\- ")+ csComPara.Mid(18,8));
		break;
	case 0x0B:
		if (iCommandLen != 28)
			return FALSE;
		csTemp.Add(_T("快捷确认操作 \\- 确认响应"));
		csTemp.Add(_T("应用协议版本号 \\- ")+ csComPara.Mid(0,2));
		csTemp.Add(_T("TransactionID \\- ")+ csComPara.Mid(2,16));
		csTemp.Add(_T("确认标识 \\- ")+ csComPara.Mid(18,2));
		csTemp.Add(_T("MAC \\- ")+ csComPara.Mid(20,8));
		break;
	default:return FALSE;
	}

	csOutput.Append( csTemp);
	return TRUE;
}


BOOL _ExplainCMCCOTAUpLoadCommand(CString csCommand,CStringArray&csOutput)
{

	BOOL iRet = TRUE;
	int iCommand,iCommandLen,iOffset;
	CString csText;
	CString csComPara;
	iCommand = _CString2Int( csCommand.Mid(0,2));

	if (!_GetTLVData(csCommand,iCommand,csComPara))
		return FALSE;
	iCommandLen = csComPara.GetLength();
	switch(iCommand)
	{
	case 1:
		if (csComPara.GetLength()== 12)
		{
			csOutput.Add(_T("MO下载请求 \\- ")+csCommand);
			csOutput.Add(_T("卡片发行批号 \\- ") + csComPara.Mid(0,6));
			csOutput.Add(_T("可用空间 \\- ")     + csComPara.Mid(6,6));
		}
		else
			iRet = FALSE;
		break;
	case 2:
		if (csComPara.GetLength()== 4)
		{
			csOutput.Add(_T("主动列表更新请求 \\- ")+csCommand);
			csOutput.Add(_T("当前列表页码 \\- ") + csComPara.Mid(0,2));
			csOutput.Add(_T("目录索引 \\- ")+ csComPara.Mid(2,2));
		}
		else
			iRet = FALSE;
		break;
	case 3:
		if ((csComPara.GetLength()%6) == 0)
		{
			csOutput.Add(_T("服务删除通知 \\- ")+csCommand);
			csOutput.Add(_T("短信总数 \\- ") + csComPara.Mid(0,2));
			csOutput.Add(_T("短信索引 \\- ")+ csComPara.Mid(2,2));
			csOutput.Add(_T("本条短信中删除的菜单索引总数 \\- ")+ csComPara.Mid(4,2));

			if ((_CString2Int(csComPara.Mid(4,2))*6 + 6) == iCommandLen)
			{

				for(int i = 1 ; i <=_CString2Int(csComPara.Mid(4,2)) ;i++)
				{
					csText.Format("%d",i);
					csOutput.Add(_T("删除的菜单索引")+csText+_T(" \\- ")+ csComPara.Mid(6*i,6));
				}

			}
			else
				iRet = FALSE;

		}
		else
			iRet = FALSE;

		break;
	case 4:
		if (csComPara.GetLength()== 8)
		{
			csOutput.Add(_T("用户STK卡注册 \\- ")+csCommand);
			csOutput.Add(_T("卡片发行批号 \\- ") + csComPara.Mid(0,2));
			csOutput.Add(_T("可用空间 \\- ")     + csComPara.Mid(2,6));
		}
		else
			iRet = FALSE;
		break;

	case 5:
		csOutput.Add(_T("信息同步响应 \\- ")+csCommand);
		csOutput.Add(_T("短信总数 \\- ") + csComPara.Mid(0,2));
		csOutput.Add(_T("短信索引 \\- ")+ csComPara.Mid(2,2));
		csOutput.Add(_T("目录索引总数 \\- ")+ csComPara.Mid(4,2));

		if ((_CString2Int( csComPara.Mid(4,2) ) *2 +6)> iCommandLen)
			return FALSE;

		iOffset = 6;

		for(int i = 1 ; i <=_CString2Int(csComPara.Mid(4,2)) ;i++)
		{
			csText.Format("%d",i);
			csOutput.Add(_T("目录索引")+csText+_T(" \\- ")+ csComPara.Mid(iOffset,2));
			iOffset += 2;
		}

		csOutput.Add(_T("本条短信菜单索引总数 \\- ")+ csComPara.Mid(iOffset,2));

		if ((_CString2Int( csComPara.Mid(iOffset,2) )*6 +iOffset+2)> iCommandLen)
			return FALSE;
		for(int i = 1 ; i <=_CString2Int(csComPara.Mid(iOffset,2)) ;i++)
		{
			csText.Format("%d",i);
			csOutput.Add(_T("服务索引")+csText+_T(" \\- ")+ csComPara.Mid(iOffset-4+i*6,6));
		}
		csOutput.Add(_T("COS版本号 \\- ")+ csComPara.Right(4));
		break;

	case 6: 
		
		csOutput.Add(_T("卡端大数据量信息接收确认 \\- ")+csCommand);
		if (iCommandLen < 6)
			return FALSE;

		csOutput.Add(_T("批次 \\- ") + csComPara.Mid(0,2));
		csOutput.Add(_T("接收完成情况标识 \\- ")+ csComPara.Mid(2,2));
		csOutput.Add(_T("未收到短信条数 \\- ")+ csComPara.Mid(4,2));

		if ((_CString2Int(csComPara.Mid(4,2))*2 + 6)> iCommandLen)
			return FALSE;
		csOutput.Add(_T("未收到短信编号 \\- ")+ csComPara.Mid(6));	
		break;
	case 7:

		if (iCommandLen <6)
			return FALSE;

		csOutput.Add(_T("应用搜索请求 \\- ")+csCommand);
		csOutput.Add(_T("当前请求页码 \\- ")+csComPara.Mid(0,2));
		csOutput.Add(_T("目录索引 \\- ")+csComPara.Mid(2,2));

		if (iCommandLen< _CString2Int(csComPara.Mid(4,2))*2+6)
			return FALSE;
		csOutput.Add(_T("关键字 \\- ")+csComPara.Mid(6,_CString2Int(csComPara.Mid(4,2))*2));


		break;
	case 8:
		if (iCommandLen == 4)
		{
			csOutput.Add(_T("远程文件更新确认 \\- ")+csCommand);
			csOutput.Add(_T("远程文件更新报文的批次 \\- ")+csComPara.Mid(0,2));
			csOutput.Add(_T("远程文件更新结果 \\- ")+csComPara.Mid(2,2));
		}
		else
			return FALSE;

		break;
	case 9:

		csOutput.Add(_T("9.	主动获取品牌信息 \\- ")+csCommand);

		break;

	case 10:

		if (iCommandLen == 8)
		{
			csOutput.Add(_T("应用开通/关闭请求 \\- ")+csCommand);
			csOutput.Add(_T("应用索引 \\- ")+csComPara.Mid(0,6));
			csOutput.Add(_T("操作类型 \\- ")+csComPara.Mid(6,2));
		}
		else
			return FALSE;

		break;

	case 11:

		if (iCommandLen == 2)
		{
			csOutput.Add(_T("BIP PUSH请求响应 \\- ")+csCommand);
			csOutput.Add(_T("请求计数器 \\- ")+csComPara);
		}
		else
			return FALSE;

		break;

	case 12:

		csOutput.Add(_T("程序补丁管理确认 \\- ")+csCommand);

		break;

	case 13:

		if (iCommandLen >= 6)
		{
			csOutput.Add(_T("远程管理命令确认 \\- ")+csCommand);
			csOutput.Add(_T("命令类型 \\- ")+csComPara.Mid(0,2));
			csOutput.Add(_T("应用个数/目录个数 \\- ")+csComPara.Mid(2,2));
			csOutput.Add(_T("处理结果 \\- ")+csComPara.Mid(4));
			//csOutput.Add(_T("处理结果 \\- ")+csComPara.Mid(4));
		}
		else
			return FALSE;


		break;

	default: return FALSE;


	}

	return TRUE;
}
BOOL _ExplainCMCCOTAUpLoad(CString csUD,CStringArray&csOutput)
{
	CStringArray csTemp;
	CString csCommand;

	if (csUD.GetLength()<52)
		return FALSE;
	csTemp.Add(_T("卡商代码及协议版本号 \\- ")+ csUD.Mid(0,2));
	csTemp.Add(_T("用户品牌标识 \\- ")+ csUD.Mid(2,2));
	csTemp.Add(_T("卡片序列号 \\- ")+ csUD.Mid(4,16));
	csTemp.Add(_T("序列号 \\- ")+ csUD.Mid(20,10));
	csTemp.Add(_T("随机数 \\- ")+ csUD.Mid(30,8));
	csTemp.Add(_T("MAC \\- ")   + csUD.Mid(38,8));

	csCommand = csUD.Mid(46);

	if (_ExplainCMCCOTAUpLoadCommand(csCommand,csTemp))
	{
		csOutput.Append(csTemp);
		return TRUE;
	}
	else return FALSE;

}


BOOL _ExplainCMCCOTADownLoadCommandDelete( CString csCommand, CStringArray &csOutput )
{
	CString csText;
	CString csComPara;
	int iCommandLen;
	BOOL iRet = TRUE;
	_GetTLVData(csCommand,_CString2Int(csCommand.Mid(0,2)),csComPara);
	iCommandLen = csComPara.GetLength();
	if ((csComPara.GetLength()%6) == 4)
	{

		csOutput.Add(_T("业务删除 \\- ")+csCommand);

		if (_Getbit(csComPara,1))
			csText = _T("MT业务删除 ");
		else
			csText = _T("网上删除 ");

		if (_Getbit(csComPara,2))
			csText += _T("删除列出项");
		else
			csText += _T("删除所有业务");
		csText = _T("(")+csText+_T(")");

		csOutput.Add(_T("命令细节 \\- ")+csComPara.Mid(0,2)+csText);

		csOutput.Add(_T("删除的服务索引总数 \\- ")+csComPara.Mid(2,2));

		if (iCommandLen == (_CString2Int(csComPara.Mid(2,2))*6+4))
		{
			for (int i = 0 ; i < _CString2Int(csComPara.Mid(2,2)) ; i ++)
			{
				csText.Format("%d",i+1);
				csOutput.Add(_T("删除的服务索引")+csText+_T(" \\- ")+ csComPara.Mid(6*i+4,6));
			}
		}
		else
			iRet = FALSE;
	}
	else
		iRet = FALSE;		

	return iRet;
}

BOOL _ExplainCMCCOTAMenuList(CString csMenuList,CStringArray&csOutput)
{
	CStringArray csTemp;
	CString csText;
	int iNumber = 1;
	int iOffset = 0;
	int iNameLen;
	int iLength = csMenuList.GetLength();


	while (iLength>(iOffset+10))
	{
		iNameLen = _CString2Int(csMenuList.Mid(iOffset+10,2));

		csTemp.Add(_T("列表数据 \\- ")+ csMenuList.Mid(iOffset,12+iNameLen*2));

		csTemp.Add(_T("菜单索引AID \\- ")+ csMenuList.Mid(iOffset,6));
		iOffset += 6;
		csTemp.Add(_T("所需空间 \\- ")+ csMenuList.Mid(iOffset,4));
		iOffset += 4;	

		if (csMenuList.Mid(iOffset+2,2) == _T("80"))
			_TranslateUcs2(csMenuList.Mid(iOffset+4,iNameLen*2-2),csText);
		else
			_TranslateAscii(csMenuList.Mid(iOffset+2,iNameLen*2),csText);
		csTemp.Add(_T("菜单名称 \\- ")+ csText);


		iOffset += 2;
		iOffset += iNameLen*2;

		switch(_CString2Int(csMenuList.Mid(iOffset,2)))
		{
		case 0:csText = _T("删除");break;
		case 1:csText = _T("添加");break;
		case 2:csText = _T("修改");break;
		default:csText = csMenuList.Mid(iOffset,2);break;

		}
		csTemp.Add(_T("操作类型 \\- ")+ csText);
		iOffset += 2;

	} 

	if (iLength == iOffset)
	{
		csOutput.Append(csTemp);
		return TRUE;
	}
	else
		return FALSE;
}
BOOL _ExplainCMCCOTADownLoadCommandSearch( CString csCommand, CStringArray &csOutput )
{
	CString csText;
	CString csComPara;
	int iCommandLen;
	int iTemp;
	BOOL iRet;
	_GetTLVData(csCommand,_CString2Int(csCommand.Mid(0,2)),csComPara);
	iCommandLen = csComPara.GetLength();

	csOutput.Add(_T("应用搜索结果 \\- ")+csCommand);
	csOutput.Add(_T("目录索引 \\- ")+csComPara.Mid(0,2));

	iTemp = _CString2Int(csComPara.Mid(2,2))*2;
	if (iCommandLen< iTemp+10)
		return FALSE;
	csOutput.Add(_T("关键字 \\- ")+csComPara.Mid(4,iTemp));
	csOutput.Add(_T("匹配记录总页数 \\- ")+csComPara.Mid(4+iTemp,2));
	csOutput.Add(_T("当前页码 \\- ")+csComPara.Mid(6+iTemp,2));
	csOutput.Add(_T("列表数据总数 \\- ")+csComPara.Mid(8+iTemp,2));
	//csOutput.Add(_T("列表数据 \\- ")+csComPara.Mid(10+iTemp));
	iRet = _ExplainCUCOTAMenuList(csComPara.Mid(10+iTemp),csOutput);
	return iRet;
}
BOOL _ExplainCMCCOTACatalogList(CString csCalalogList,CStringArray&csOutput)
{
	CStringArray csTemp;
	CString csText;
	int iNumber = 1;
	int iOffset = 0;
	int iNameLen;
	int iLength = csCalalogList.GetLength();

	do 
	{
		iNameLen = _CString2Int(csCalalogList.Mid(iOffset+2,2));

		csTemp.Add(_T("目录数据 \\- ")+ csCalalogList.Mid(iOffset,6+iNameLen*2));

		csTemp.Add(_T("目录索引ID \\- ")+ csCalalogList.Mid(iOffset,2));
		iOffset += 2;

		if (csCalalogList.Mid(iOffset+2,2) == _T("80"))
			_TranslateUcs2(csCalalogList.Mid(iOffset+4,iNameLen*2-2),csText);
		else
			_TranslateAscii(csCalalogList.Mid(iOffset+2,iNameLen*2),csText);
		csTemp.Add(_T("目录名称 \\- ")+ csText);

		iOffset += 2;
		iOffset += iNameLen*2;


		switch(_CString2Int(csCalalogList.Mid(iOffset,2)))
		{
		case 0:csText = _T("启用");break;
		case 1:csText = _T("禁用");break;
		case 2:csText = _T("添加");break;
		case 3:csText = _T("删除");break;
		case 4:csText = _T("更名");break;
		default:csText = csCalalogList.Mid(iOffset,2);break;

		}
		csTemp.Add(_T("操作类型 \\- ")+ csText);
		iOffset+= 2;


	} while (iLength>(iOffset+2));

	if (iLength = iOffset)
	{
		csOutput.Append(csTemp);
		return TRUE;
	}
	else
		return FALSE;

}
//包含随机数和序列号方向和Command
BOOL _ExplainCMCCOTADownLoadCommand(CString csCommand,CStringArray&csOutput)
{

	BOOL iRet = TRUE;
	int iCommand,iCommandLen;
	CString csText;
	CString csComPara;
	iCommand = _CString2Int( csCommand.Mid(0,2));
	if (!_GetTLVData(csCommand,iCommand,csComPara))
		return FALSE;
	iCommandLen = csComPara.GetLength();
	switch(iCommand)
	{
	case 1:

		if (iCommandLen>22)
		{
			csOutput.Add(_T("信息下载  \\- ")+csCommand);
			csOutput.Add(_T("服务索引 \\- ")+csComPara.Mid(0,6));
			csOutput.Add(_T("批次 \\- ")+csComPara.Mid(6,2));
			csOutput.Add(_T("短信总数 \\- ")+csComPara.Mid(8,2));
			csOutput.Add(_T("短信索引 \\- ")+csComPara.Mid(10,2));
			csOutput.Add(_T("续传标识 \\- ")+csComPara.Mid(12,2));
			csOutput.Add(_T("应用数据空间 \\- ")+csComPara.Mid(14,4));
			csOutput.Add(_T("应用数据地址偏移 \\- ")+csComPara.Mid(18,4));
			csOutput.Add(_T("应用数据 \\- ")+csComPara.Mid(22));
		}
		else
			iRet = FALSE;
		break;

	case 2:
		if (iCommandLen>=6)
		{
			csOutput.Add(_T("列表更新 \\- ")+csCommand);
			csOutput.Add(_T("当前列表页码 \\- ")+csComPara.Mid(0,2));
			csOutput.Add(_T("命令细节 \\- ")+csComPara.Mid(2,2));
			csOutput.Add(_T("列表数据总数 \\- ")+csComPara.Mid(4,2));
			iRet = _ExplainCMCCOTAMenuList(csComPara.Mid(4),csOutput);
		}
		else
			iRet = FALSE;
		break;

	case 3:
		if (iCommandLen>=2)
		{
			csOutput.Add(_T("PUSH更新 \\- ")+csCommand);
			csOutput.Add(_T("列表数据总数 \\- ")+csComPara.Mid(0,2));
			csOutput.Add(_T("列表数据 \\- ")+csComPara.Mid(2));
		}
		else
			iRet = FALSE;
		break;

	case 4:
		if (iCommandLen== 00)
			csOutput.Add(_T("用户注册确认 \\- ")+csCommand);
		else
			iRet = FALSE;
		break;
		
	case 5:
		if (iCommandLen== 00)
			csOutput.Add(_T("信息同步请求 \\- ")+csCommand);
		else
			iRet = FALSE;
		break;
	case 6: iRet = _ExplainCMCCOTADownLoadCommandDelete(csCommand,csOutput);break;
	case 7:

		if ((iCommandLen%3) ==1)
		{
			csOutput.Add(_T("远程业务启用/禁用 \\- ")+csCommand);
			csOutput.Add(_T("服务索引总数 \\- ")+csComPara.Mid(0,2));
			csOutput.Add(_T("服务索引 \\- ")+csComPara.Mid(2));
		}
		else
			iRet = FALSE;
		break;
	case 8:

		csOutput.Add(_T("远程目录管理 \\- ")+csCommand);
		csOutput.Add(_T("目录总数 \\- ")+csComPara.Mid(0,2));
		iRet = _ExplainCMCCOTACatalogList(csComPara.Mid(2),csOutput);
		break;


	case 9:

		if (iCommandLen>22)
		{
			csOutput.Add(_T("远程业务更新  \\- ")+csCommand);
			csOutput.Add(_T("服务索引 \\- ")+csComPara.Mid(0,6));
			csOutput.Add(_T("批次 \\- ")+csComPara.Mid(6,2));
			csOutput.Add(_T("短信总数 \\- ")+csComPara.Mid(8,2));
			csOutput.Add(_T("短信索引 \\- ")+csComPara.Mid(10,2));
			csOutput.Add(_T("续传标识 \\- ")+csComPara.Mid(12,2));
			csOutput.Add(_T("应用数据空间 \\- ")+csComPara.Mid(14,4));
			csOutput.Add(_T("应用数据地址偏移 \\- ")+csComPara.Mid(18,4));
			csOutput.Add(_T("应用数据 \\- ")+csComPara.Mid(22));
		}
		else
			iRet = FALSE;
		break;
	
	case 10:
	

		if (iCommandLen>14)
		{
			csOutput.Add(_T("交互应用  \\- ")+csCommand);
			csOutput.Add(_T("批次 \\- ")+csComPara.Mid(6,2));
			csOutput.Add(_T("短信总数 \\- ")+csComPara.Mid(8,2));
			csOutput.Add(_T("短信索引 \\- ")+csComPara.Mid(10,2));
			csOutput.Add(_T("应用数据空间 \\- ")+csComPara.Mid(14,4));
			csOutput.Add(_T("应用数据地址偏移 \\- ")+csComPara.Mid(18,4));
			csOutput.Add(_T("应用数据 \\- ")+csComPara.Mid(22));
		}
		else
			iRet = FALSE;
		break;
	case 11:iRet = _ExplainCMCCOTADownLoadCommandSearch(csCommand,csOutput);break;
	case 12:
		if (iCommandLen==4)
		{
			csOutput.Add(_T("BIP PUSH请求/结束  \\- ")+csCommand);
			csOutput.Add(_T("请求/结束标志 \\- ")+csComPara.Mid(0,2));
			csOutput.Add(_T("请求计数器 \\- ")+csComPara.Mid(2,2));
		}
		else
			iRet = FALSE;
		break;
	case 13:
		if ((iCommandLen%3)==1)
		{
			csOutput.Add(_T("应用开通/关闭  \\- ")+csCommand);
			csOutput.Add(_T("应用索引总数 \\- ")+csComPara.Mid(0,2));

			for (int i = 1 ; i <= _CString2Int(csComPara.Mid(0,2));i++)
			{
				csText.Format("%d",i);
				csOutput.Add(_T("应用索引")+csText+_T(" \\- ") +csComPara.Mid(0,2));
			}
		}
		else
			iRet = FALSE;
		break;
	case 14:
		csOutput.Add(_T("用户注册请求  \\- ")+csCommand);
		break;
	case 15:
		csOutput.Add(_T("短信接入号或BIP接入IP更新  \\- ")+csCommand);
		csOutput.Add(_T("更新类别 \\- ")+csComPara.Mid(0,2));
		csOutput.Add(_T("接入号/IP地址  \\- ")+csComPara.Mid(2));
		break;
	case 16:
		csOutput.Add(_T("弹出应用 \\- ")+csCommand);
		csOutput.Add(_T("应用索引 \\- ")+csComPara);
		break;
	default: return FALSE;
	}

	return TRUE;
}
BOOL _ExplainCMCCOTADownLoad(CString csCommand,CStringArray&csOutput)
{

	CStringArray csTemp;

	if (csCommand.GetLength()<14)
		return FALSE;

	csTemp.Add(_T("随机数 \\- ")+ csCommand.Mid(0,8));


	csTemp.Add(_T("计数器类型标识 \\- ")+ csCommand.Mid(8,2));	
	if (_ExplainCMCCOTADownLoadCommand(csCommand.Mid(10),csTemp))
	{
		csOutput.Append(csTemp);
		return TRUE;
	}

	return FALSE;

}
BOOL _ExplainCMCCRFMDownLoad( CString csCommand,CStringArray&csOutput)
{

	CStringArray csTemp;

	if (csCommand.GetLength()<8)
		return FALSE;

	csTemp.Add(_T("随机数 \\- ")+ csCommand.Mid(0,8));

	csTemp.Add(_T("Secured Data \\- ")+ csCommand.Mid(8));

	csOutput.Append(csTemp);
	return TRUE;

}


void _ExplainChinaOperaterPrivate( int iTAR, CStringArray &csOutput, CString csSM, int iOff )
{
	if ((theApp.iLevel&Def_OTAINFOMATION) == 0)
		return;

	if (theApp.iOperater == 0x55)
	{
		csOutput.Add(_T("运营商判断 \\- 中国联通"));
		if(iTAR == 0xB00010)
		{
			csOutput.Add(_T("操作 \\- OTA下载"));
			_ExplainCUCOTADownLoad(csSM.Mid(iOff),csOutput);
		}
		if(iTAR == 0xB0001F)
		{
			csOutput.Add(_T("操作 \\- 远程文件管理RFM"));
			_ExplainCUCRFMDownLoad(csSM.Mid(iOff),csOutput);
		}	
	}

	if (theApp.iOperater == 0x43)
	{
		csOutput.Add(_T("运营商判断 \\- 中国移动"));
		if(iTAR == 0xB00010)
		{
			csOutput.Add(_T("操作 \\- OTA下载"));
			_ExplainCMCCOTADownLoad(csSM.Mid(iOff),csOutput);
		}
		if(iTAR == 0xB0001F)
		{
			csOutput.Add(_T("操作 \\- 远程文件管理RFM"));
			_ExplainCMCCRFMDownLoad(csSM.Mid(iOff),csOutput);
		}
		if(iTAR == 0xB000F1)
		{
			csOutput.Add(_T("操作 \\- 现场写卡 获取卡片信息"));
		}

		if(iTAR == 0xB000F2)
		{
			csOutput.Add(_T("操作 \\- 现场写卡/两不一快 写卡操作"));	
		}
		if(iTAR == 0xB000B0)
		{
			csOutput.Add(_T("操作 \\- 物联网写卡"));
		}
	}
}


BOOL _ExplainCommandSecuredPacket8bitNote1(CString csSM,CStringArray&csOutput)
{

	CString PreTest;
	int iSPI,iCHL;
	int iOff = 0;
	int iSMLen = csSM.GetLength();
	int iTAR;
	iCHL = _CString2Int(csSM.Mid(4,2));

	iSPI = _CString2Int(csSM.Mid(6,4));
	theApp.iPreSPI = iSPI;//此处保存用来Response Packet使用
	iTAR = _CString2Int(csSM.Mid(14,6));

	iOff = 20;

	//SPI 只是是密文,不需要再密文下解析
	iSPI= iSPI>>8;

	if ((iSPI&0x18) != 00)
	{
		if ((iOff+10)>iSMLen)
			return FALSE;

		csOutput.Add(_T("Counter (CNTR) \\- ")+csSM.Mid(iOff,10));
		iOff += 10;
	}
	csOutput.Add(_T("Padding counter (PCNTR) \\- ")+csSM.Mid(iOff,2));
	iOff += 2;

	if ((iCHL*2+6)>iSMLen)
		return FALSE;

	if ((iSPI&0x03) == 1)
	{
		csOutput.Add(_T("Redundancy Check \\- ")+csSM.Mid(iOff,iCHL*2+6-iOff));
	}else if ((iSPI&0x03) == 2)
	{
		csOutput.Add(_T("Cryptographic Checksum \\- ")+csSM.Mid(iOff,iCHL*2+6-iOff));
	}
	else if ((iSPI&0x03) == 3)
	{
		csOutput.Add(_T("Digital Signature \\- ")+csSM.Mid(iOff,iCHL*2+6-iOff));	
	}
	iOff = iCHL*2+6;

	csOutput.Add(_T("Secured Data \\- ")+csSM.Mid(iOff));

	_ExplainChinaOperaterPrivate(iTAR,csOutput,csSM,iOff);

	return TRUE;

}


BOOL _ExplainCommandSecuredPacket8bit(CString csSM,CStringArray&csOutput)
{

	CString PreTest;
	int iSPI,iCHL;
	int iOff = 0;
	int iSMLen = csSM.GetLength();
	int iTAR;

	csOutput.Add(_T("Command Packet Length (CPL) \\- ")+csSM.Mid(0,4));
	csOutput.Add(_T("Command Header Length (CHL) \\- ")+csSM.Mid(4,2));
	iCHL = _CString2Int(csSM.Mid(4,2));

	csOutput.Add(_T("Security Parameter Indicator (SPI) \\- ")+csSM.Mid(6,4));
	iSPI = _CString2Int(csSM.Mid(6,4));
	theApp.iPreSPI = iSPI;//此处保存用来Response Packet使用

	csOutput.Add(_T("Ciphering Key Identifier (KIc) \\- ")+csSM.Mid(10,2));
	csOutput.Add(_T("Key Identifier (KID) \\- ")          +csSM.Mid(12,2));
	csOutput.Add(_T("Toolkit Application Reference (TAR) \\- ")+csSM.Mid(14,6));
	iTAR = _CString2Int(csSM.Mid(14,6));

	iOff = 20;

	//SPI 只是是密文,不需要再密文下解析
	iSPI= iSPI>>8;

	if ((iSPI&0x4) == 0x4)
		return TRUE;

	return _ExplainCommandSecuredPacket8bitNote1(csSM,csOutput);


	/*if ((iSPI&0x18) != 00)
	{
	if ((iOff+10)>iSMLen)
	return FALSE;

	csOutput.Add(_T("Counter (CNTR) \\- ")+csSM.Mid(iOff,10));
	iOff += 10;
	}
	csOutput.Add(_T("Padding counter (PCNTR) \\- ")+csSM.Mid(iOff,2));
	iOff += 2;

	if ((iCHL*2+6)>iSMLen)
	return FALSE;

	if ((iSPI&0x03) == 1)
	{
	csOutput.Add(_T("Redundancy Check \\- ")+csSM.Mid(iOff,iCHL*2+6-iOff));
	}else if ((iSPI&0x03) == 2)
	{
	csOutput.Add(_T("Cryptographic Checksum \\- ")+csSM.Mid(iOff,iCHL*2+6-iOff));
	}
	else if ((iSPI&0x03) == 3)
	{
	csOutput.Add(_T("Digital Signature \\- ")+csSM.Mid(iOff,iCHL*2+6-iOff));	
	}
	iOff = iCHL*2+6;

	csOutput.Add(_T("Secured Data \\- ")+csSM.Mid(iOff));

	_ExplainChinaOperaterPrivate(iTAR,csOutput,csSM,iOff);

	return TRUE;*/

}

BOOL _ExplainResponseSecuredPacket8bit(CString csSM,CStringArray&csOutput)
{

	int iRHL;
	int iOff = 0;
	int iSMLen = csSM.GetLength();

	csOutput.Add(_T("Response Packet Length (RPL) \\- ")+csSM.Mid(0,4));
	csOutput.Add(_T("Response Header Length (RHL) \\- ")+csSM.Mid(4,2));
	iRHL = _CString2Int(csSM.Mid(4,2));
	csOutput.Add(_T("Toolkit Application Reference (TAR) \\- ")+csSM.Mid(6,6));

	iOff = 12;
	if (((theApp.iPreSPI>>8)&0x18) != 00)
	{
		if ((iOff+10)>iSMLen)
			return FALSE;
		csOutput.Add(_T("Counter (CNTR) \\- ")+csSM.Mid(iOff,10));
		iOff += 10;
	}
	csOutput.Add(_T("Padding counter (PCNTR) \\- ")+csSM.Mid(iOff,2));
	iOff += 2;
	csOutput.Add(_T("Response Status Code Octet \\- ")+csSM.Mid(iOff,2));
	iOff += 2;

	if ((iRHL*2+6)>iSMLen)
		return FALSE;

	if ((theApp.iPreSPI&0x0C) == 4)
	{
		csOutput.Add(_T("Redundancy Check \\- ")+csSM.Mid(iOff,iRHL*2+6-iOff));
	}else if ((theApp.iPreSPI&0x0C) == 8)
	{
		csOutput.Add(_T("Cryptographic Checksum \\- ")+csSM.Mid(iOff,iRHL*2+6-iOff));
	}
	else if ((theApp.iPreSPI&0x0C) == 0xC)
	{
		csOutput.Add(_T("Digital Signature \\- ")+csSM.Mid(iOff,iRHL*2+6-iOff));	
	}
	iOff = iRHL*2+6;

	csOutput.Add(_T("Additional Response Data \\- ")+csSM.Mid(iOff));

	//_ExplainChinaOperaterPrivate(iTAR, csOutput, csSM, iOff);


	return TRUE;
}

BOOL _ExplainSMSDataCodingScheme(CString csDCS,CStringArray&csOutput)
{
	CString csDes;
	int iDCS = _CString2Int(csDCS);
	csOutput.Add(_T("TP-DCS \\- ") + csDCS);
	switch(iDCS>>4)
	{
	case 00: 
	case 01:	
	case 02:
	case 03:
		if ((iDCS>>5)&1)
			csOutput.Add( _T("Bit 5 = 1, indicates the text is compressed using the GSM standard compression algorithm."));
		else
			csOutput.Add( _T("Bit 5 = 0, indicates the text is uncompressed"));
		if ((iDCS>>4)&1)
			csOutput.Add( _T("Bit 4 = 1,indicates that bits 1 to 0 have a message class meaning"));
		else
			csOutput.Add( _T("Bit 4 = 0, indicates that bits 1 to 0 are reserved and have no message class meaning"));

		switch((iDCS>>2)&3)
		{
		case 0:csOutput.Add( _T("Bit 3 Bit 2 = 0 0,Default alphabet"));break;
		case 1:csOutput.Add( _T("Bit 3 Bit 2 = 0 1,8 bit"));break;
		case 2:csOutput.Add( _T("Bit 3 Bit 2 = 1 0,UCS2 (16bit)"));break;
		case 3:csOutput.Add( _T("Bit 3 Bit 2 = 1 0,Reserved"));break;
		}
		if ((iDCS>>4)&1)
		{
			switch(iDCS&3)
			{
			case 0:csOutput.Add( _T("Bit 1 Bit 0 = 0 0,Class 0"));break;
			case 1:csOutput.Add( _T("Bit 1 Bit 0 = 0 1,Class 1 Default meaning: ME-specific"));break;
			case 2:csOutput.Add( _T("Bit 1 Bit 0 = 1 0,Class 2 SIM specific message"));break;
			case 3:csOutput.Add( _T("Bit 1 Bit 0 = 1 0,Class 3 Default meaning: TE specific (see GSM TS 07.05)"));break;
			}
		}
		break;
	case 0xC:
	case 0xD:
	case 0xE:

		if ((iDCS>>4) == 0xC)
			csOutput.Add(_T("Message Waiting Indication Group：Discard Message"));
		else if ((iDCS>>4) == 0xD)
			csOutput.Add(_T("Message Waiting Indication Group：Store Message"));
		else if ((iDCS>>4) == 0xE)
		{
			csOutput.Add(_T("Message Waiting Indication Group：Store Message;"));
			csOutput.Add(_T("UserData is coded in the uncompressed UCS2 alphabet;"));
		}
		if ((iDCS>>3)&1)
		{
			csOutput.Add(_T("Bit 3 = 1,Set Indication Inactive"));
		}
		else
		{
			csOutput.Add(_T("Bit 3 = 0,Set Indication Active"));
			switch(iDCS&3)
			{
			case 0:csOutput.Add( _T("Bit 1 Bit 0 = 0 0,Voicemail Message Waiting"));break;
			case 1:csOutput.Add( _T("Bit 1 Bit 0 = 0 1,Fax Message Waiting"));break;
			case 2:csOutput.Add( _T("Bit 1 Bit 0 = 1 0,Electronic Mail Message Waiting"));break;
			case 3:csOutput.Add( _T("Bit 1 Bit 0 = 1 0,Other Message Waiting*"));break;
			}
		}
		break;
	case 0xF:
		if ((iDCS>>2)&1)
			csOutput.Add( _T("Bit 2 =  1,8-bit data"));
		else
			csOutput.Add( _T("Bit 2 = 0,Default alphabet"));
		switch(iDCS&3)
		{
		case 0:csOutput.Add( _T("Bit 1 Bit 0 = 0 0,Class 0"));break;
		case 1:csOutput.Add( _T("Bit 1 Bit 0 = 0 1,Class 1 Default meaning: ME-specific"));break;
		case 2:csOutput.Add( _T("Bit 1 Bit 0 = 1 0,Class 2 SIM specific message"));break;
		case 3:csOutput.Add( _T("Bit 1 Bit 0 = 1 0,Class 3 Default meaning: TE specific (see GSM TS 07.05)"));break;
		}
		break;
	}

	return TRUE;
}
BOOL _ExplainProtocolIdentifier(CString csPID,CStringArray&csOutput)
{
	int iPID = _CString2Int(csPID);
	CString csText;


	if ((iPID>>6) == 0)
	{
		if ((iPID>>5)&1)
		{
			switch(iPID&0x1F)
			{
			case 0:csText = _T("implicit - device type is specific to this SC, or can be concluded on the basis of the address");break;
			case 1:csText = _T("telex (or teletex reduced to telex format)");break;
			case 2:csText = _T("group 3 telefax");break;
			case 3:csText = _T("group 4 telefax");break;
			case 4:csText = _T("voice telephone (i.e. conversion to speech)");break;
			case 5:csText = _T("ERMES (European Radio Messaging System)");break;
			case 6:csText = _T("National Paging system (known to the SC)");break;
			case 7:csText = _T("Videotex (T.100/T.101)");break;
			case 8:csText = _T("teletex, carrier unspecified");break;
			case 9:csText = _T("teletex, in PSPDN");break;
			case 10:csText = _T("teletex, in CSPDN");break;
			case 11:csText = _T("teletex, in analog PSTN");break;
			case 12:csText = _T("teletex, in digital ISDN");break;
			case 13:csText = _T("UCI (Universal Computer Interface, ETSI DE/PS 3 01-3)");break;
			case 14:
			case 15:csText = _T("(reserved, 2 combinations)");break;

			case 16:csText = _T("a message handling facility (known to the SC)");break;
			case 17:csText = _T("any public X.400-based message handling system");break;
			case 18:csText = _T("Internet Electronic Mail");break;
			case 19:
			case 20:
			case 21:
			case 22:
			case 23:csText = _T("(reserved, 5 combinations)");break;
			case 0x31:csText = _T("A GSM mobile station. The SC converts the SM from the received TP-Data-Coding-Scheme to any data coding scheme supported by that MS (e.g. the default).");break;
			default:csText = _T("values specific to each SC, usage based on mutual agreement between the SME and the SC (7combinations available for each SC)");break;
			}
		}
		else
			csText = _T("no interworking");
	} else if((iPID>>6) == 1)
	{
		switch(iPID&0x3F)
		{
		case 0: csText = _T("Short Message Type 0");break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			csText.Format("%d",iPID&0x3F);
			csText = _T("Replace Short Message Type ")+csText;	
			break;
		case 0x1F: csText = _T("Return Call Message");break;
		case 0x3D: csText = _T("ME Data download");break;
		case 0x3E: csText = _T("ME De-personalization Short Message");break;
		case 0x3F: csText = _T("SIM Data download");break;
		}
	}


	if (!csText.IsEmpty())
		csText = _T("(")+csText+_T(")");

	csOutput.Add(_T("TP-PID \\- ")+ csPID + csText);
	return TRUE;
}




BOOL _ExplainUserData(CString csUD,int iDCS,int iUDHI,CStringArray&csOutput)
{
	BOOL iRet = TRUE;
	CString csPreText = _T("TP-UD \\- ");
	csOutput.Add(csPreText+ csUD);
	CString csUDH;
	CString csSM ;
	csUDH.Empty();
	//if (iUDHI == 0)
	//{
	//	switch(iDCS)
	//	{
	//	case 0:iRet = _Translate7bit(csUD,csPreText);csUD= csPreText;
	//	case 4:iRet = _TranslateAscii(csUD,csPreText);break;
	//	case 8:iRet = _TranslateUcs2(csUD,csPreText);break;
	//	default:iRet = FALSE;break;
	//	}
	//	if (iRet)
	//		csOutput.Add(csPreText);	

	//}
//	else
	if (iUDHI)
	{
		//UDL < UDHL
		BOOL bCPL,bRPL;
		//if (_CString2Int(csUD.Mid(0))*2 > csUD.GetLength())
		//	return FALSE;
		csUDH = csUD.Mid(2,_CString2Int(csUD.Mid(0,2))*2);
		if (!_ExplainUserDataHead(csUDH,csOutput,bCPL,bRPL))
			return FALSE;
		csSM = csUD.Mid(2+csUDH.GetLength());
		if (bCPL)
		{
			iRet = _ExplainCommandSecuredPacket8bit(csSM,csOutput);
		}
		else if (bRPL)
			iRet = _ExplainResponseSecuredPacket8bit(csSM,csOutput);
		else
			csOutput.Add(_T("Secured Data \\- ")+ csSM);

		if (GetExplainLevel()& Def_DECINFOMATION)
		{
			if (csUDH.GetLength() <=4)
				theApp.csMsgArray.Add(csSM);
			else
				AddMessageArray(csUD);


			__ExpainCipherUserData(csOutput);

		}


	}
	else
	{

		if (theApp.iLevel& Def_OTAINFOMATION)
		{
			if (theApp.iOperater == 0x55)
			{
				if (_ExplainCUCOTAUpLoad( csUD,csOutput))
					return TRUE;
			}
			if (theApp.iOperater == 0x43)
			{
				if (_ExplainCMCCSIMAUTH(csUD,csOutput))
					return TRUE;
				if (_ExplainCMCCOTAUpLoad( csUD,csOutput))
					return TRUE;
			}
		}

		switch(iDCS)
		{
		case 0:iRet = _Translate7bit(csUD,csPreText);csUD= csPreText;
		case 4:iRet = _TranslateAscii(csUD,csPreText);break;
		case 8:iRet = _TranslateUcs2(csUD,csPreText);break;
		default:iRet = FALSE;break;
		}
		if (iRet)
			csOutput.Add(csPreText);	
	}


	return iRet;
}



BOOL _ExplainSMSSubmit(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csPreText;
	CString csText;
	int iVPF;
	int iDALen;
	//此处用来解释UD使用
	int iDCS,iUDHI;
	csPreText = _T("TP-MTI \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	_Int2CString(_Getbit(csInput,2)*2 +_Getbit(csInput,1) ,csText,2);
	csText = csText + _T("(SMS-SUBMIT)");
	csOutput.Add(csPreText+csText);

	csPreText = _T("TP-RD \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	if ( _Getbit(csInput,3))
		csText = _T("1(the SC to reject an SMS-SUBMIT for an SM still held)");
	else
	    csText = _T("0(the SC to accept an SMS-SUBMIT for an SM still held)");

	csOutput.Add(csPreText+csText);

	csPreText = _T("TP-VPF \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	iVPF =  _Getbit(csInput,5)*2 +_Getbit(csInput,4);
	switch(iVPF)
	{
	case 0:csText = _T("0(TP-VP field not present)");break;
	case 2:csText = _T("2(TP-VP field present - relative format)");break;
	case 1:csText = _T("1(TP-VP field present - enhanced format)");break;
	case 3:csText = _T("3(TP-VP field present - absolute format)");break;
	}
	csOutput.Add(csPreText+csText);

	csPreText = _T("TP-SRR \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	if ( _Getbit(csInput,6))
		csText = _T("1(A status report is requested)");
	else
		csText =_T("0(A status report is not requested)");

	csOutput.Add(csPreText+csText);


	csPreText = _T("TP-UDHI \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	iUDHI = (int)_Getbit(csInput,7);
	if ( _Getbit(csInput,7))
		csText = _T("1(The beginning of the TP-UD field contains a Header in addition to the short message)");
	else
		csText = _T("0(The TP-UD field contains only the short message)");
	csOutput.Add(csPreText+csText);

	csPreText = _T("TP-RP \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	if ( _Getbit(csInput,8))
		csText = _T("1(TP-Reply-Path parameter is set in this SMS-SUBMIT/DELIVER)");
	else
		csText = _T("0(TP-Reply-Path parameter is not set in this SMS-SUBMIT/DELIVER)");
	csOutput.Add(csPreText+csText);



	csPreText = _T("TP-MR \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csText = csInput.Mid(2,2);
	csOutput.Add(csPreText+csText);

	csPreText = _T("TP-DA \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	iDALen = _CString2Int(csInput.Mid(4,2))+4;
	if (iDALen%2)
		iDALen= iDALen+1;
	_TranslateAddress(csInput.Mid(4,iDALen),csText);
	csText = csInput.Mid(4,iDALen) +_T("(")+csText+ _T(")");
	csOutput.Add(csPreText+csText);

	//csPreText = _T("TP-PID \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	//csOutput.Add(csPreText+ csInput.Mid(iDALen+4,2));
	bRet = _ExplainProtocolIdentifier(csInput.Mid(iDALen+4,2),csOutput);

	//csPreText = _T("TP-DCS \\- ");
	////__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	//csOutput.Add(csPreText+ csInput.Mid(iDALen+6,2));


	bRet =  _ExplainSMSDataCodingScheme(csInput.Mid(iDALen+6,2),csOutput);
	iDCS = _CString2Int(csInput.Mid(iDALen+6,2));


	int iVPLen = 0;
	if (iVPF != 0)
	{
		csPreText = _T("TP-VP \\- ");
		//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
		if (iVPF == 3)
			iVPLen = 7;
		else
			iVPLen = 1;
		csOutput.Add(csPreText+ csInput.Mid(iDALen+8,iVPLen*2));
	}

	csPreText = _T("TP-UDL \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+ csInput.Mid(iDALen+8+iVPLen*2,2));

	//csPreText = _T("TP-UD \\- ");
	////__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	//csOutput.Add(csPreText+ csInput.Mid(iDALen+10+iVPLen*2));
	bRet = _ExplainUserData(csInput.Mid(iDALen+10+iVPLen*2),iDCS,iUDHI,csOutput);

	return bRet;

}

BOOL _ExplainSMSSubmitReport(CString csInput, CStringArray&csOutput)
{
	return TRUE;

}


BOOL _ExplainCellBroadCastPage(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csPreText;
	csPreText = _T("Cell Broad Cast Page \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);
	return bRet;


}


BOOL _ExplainTextString(CString csTextString, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	CString csTemp;
	int iCode;
	csPreText = _T("Text String \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csTextString);

	csPreText = _T("Text Code \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	iCode = _CString2Int(csTextString.Left(2));
	switch(iCode )
	{
	case 0x00: csText = _T("7-bit coded alphabet ");break;
	case 0x04: csText = _T("Ascii");break;
    case 0x08: csText = _T("UCS2");break;
	default: csText.Empty();
	}
	csText= _T("(")+csText+_T(")");
	
	csOutput.Add(csPreText+csTextString.Left(2)+csText);

	csPreText = _T("Text \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	switch(iCode)
	{
	case 0x00: if (_Translate7bit(csTextString.Mid(2),csTemp))
	{
		if (!_TranslateAscii(csTemp,csText))
			bRet = FALSE;
	}
	break;
	case 0x04: 
		if (!_TranslateAscii(csTextString.Mid(2),csText))
			bRet = FALSE;
		break;
	case 0x08: 
		if (!_TranslateUcs2(csTextString.Mid(2),csText))
			bRet = FALSE;
		break;
	default: csText.Empty();
	}
	csText= _T("(")+csText+_T(")");

	csOutput.Add(csPreText+csText);
	return bRet;


}
BOOL _ExplainTone(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	csPreText = _T("Tone \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);

	switch(_CString2Int(csInput))
	{
	case 1 : csText= _T("Dial tone");break;
	case 2 : csText= _T("Called subscriber busy");break;
	case 3 : csText= _T("Congestion");break;
	case 4 : csText= _T("Radio path acknowledge");break;
	case 5 : csText= _T("Radio path not available / Call dropped");break;
	case 6 : csText= _T("Error / Special information");break;
	case 7 : csText= _T("Call waiting tone");break;
	case 8 : csText= _T("Ringing tone");break;
	case 16 : csText= _T("General beep");break;
	case 17 : csText= _T("Positive acknowledgement tone");break;
	case 18 : csText= _T("Negative acknowledgement or error tone");break;
	default:csText= _T("reserved");break;
	}
	csText= _T("(")+csText+_T(")");
	csOutput.Add(csPreText+csInput+csText);
	return bRet;
}

BOOL _ExplainItem(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	//csPreText = _T("Item \\- ");
	////__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	//csOutput.Add(csPreText+csInput);

	csPreText = _T("Identifier of item \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput.Mid(0,2));

	csPreText = _T("Text string of item \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	_TranslateAlphaIdentifier(csInput.Mid(2),csText);
	csText= _T("(")+csText+_T(")");
	csOutput.Add(csPreText+csInput.Mid(2)+csText);
	return bRet;
}

BOOL _ExplainItemIdentifier(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	csPreText = _T("Item Identifier \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);
	return bRet;
}
BOOL _ExplainResponseLength(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;

	if (csInput.GetLength()<4)
		return FALSE;

	csPreText = _T("Response length \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);

	csPreText = _T("Minimum length of response \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput.Mid(0,2));

	csPreText = _T("Maximum  length of response \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput.Mid(2,2));

	return bRet;
}

BOOL _ExplainFileList(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	csPreText = _T("File List \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);

	csPreText = _T("Number of files \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput.Mid(0,2));

	csPreText = _T("Files \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput.Mid(2));

	return bRet;
}


BOOL _ExplainLocationInformation(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;

	//if (csInput.GetLength()!= 14)
	//	return FALSE;


	csPreText = _T("Location Information \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);



	csPreText = _T("MCC & MNC \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	

	if (_GenerateMCCMNCDescription(csInput.Mid(0,6),csText))
		csText = _T("(")+csText+_T(")");
	csOutput.Add(csPreText+csInput.Mid(0,6));

	csPreText = _T("LAC \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput.Mid(6,4));

	csPreText = _T("Cell ID \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput.Mid(10,4));


	return bRet;
}

BOOL _ExplainIMEI(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	csPreText = _T("IMEI \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);
	return bRet;
}
BOOL _ExplainHelprequest(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	//CString csText;
	//CString csPreText;
	//csPreText = _T("Help Request \\- ");
	////__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	//csOutput.Add(csPreText+csInput);

	csOutput.Add(_T("Help Request"));
	return bRet;
}
BOOL _ExplainNetworkMeasurementResults(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csPreText;
	csPreText = _T("Network Measurement Results \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);

	return bRet;
}
BOOL _ExplainDefaultText(CString csTextString, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	CString csTemp;
	int iCode;
	csPreText = _T("Default Text  \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csTextString);

	csPreText = _T("Text Code \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	iCode = _CString2Int(csTextString.Left(2));
	switch(iCode )
	{
	case 0x00: csText = _T("7-bit coded alphabet ");break;
	case 0x04: csText = _T("Ascii");break;
	case 0x08: csText = _T("UCS2");break;
	default: csText.Empty();
	}
	csText= _T("(")+csText+_T(")");

	csOutput.Add(csPreText+csTextString.Left(2)+csText);

	csPreText = _T("Text \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	switch(iCode)
	{
	case 0x00: if (_Translate7bit(csTextString.Mid(2),csTemp))
			   {
				   if (!_TranslateAscii(csTemp,csText))
					   bRet = FALSE;
			   }
			   break;
	case 0x04: 
		if (!_TranslateAscii(csTextString.Mid(2),csText))
			bRet = FALSE;
		break;
	case 0x08: 
		if (!_TranslateUcs2(csTextString.Mid(2),csText))
			bRet = FALSE;
		break;
	default: csText.Empty();
	}
	csText= _T("(")+csText+_T(")");

	csOutput.Add(csPreText+csTextString.Left(2)+csText);
	return bRet;
}
BOOL _ExplainItemsNextActionIndicator(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csPreText;
	csPreText = _T("Items Next Action Indicator \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);
	return bRet;
}
BOOL _ExplainEventList(CString csInput, CStringArray&csOutput)
{

	BOOL bRet = TRUE;
	CString csPreText;
	CString csText;
	csPreText = _T("EventList \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	
	csText.Empty();
	for (int i = 0 ; i < csInput.GetLength() ; i+=2)
	{
		switch(_CString2Int(csInput.Mid(i,2)))
		{
		case 0: csText += _T("MT call");break;
	    case 1: csText += _T("Call connected");break;
	    case 2: csText += _T("Call disconnected");break;
	    case 3: csText += _T("Location status");break;
		case 4: csText += _T("User activity");break;
		case 5: csText += _T("Idle screen available");break;
		case 6: csText += _T("Card reader status(if class \"a\" is supported)");break;
		case 7: csText += _T("Language selection");break;
		case 8: csText += _T("Browser Termination(if class \"c\" is supported)");break;
		case 9: csText += _T("Data available(if class \"e\" is supported)");break;
		case 10: csText += _T("Channel status(if class \"e\" is supported)");break;
		}
		csText+= _T(";");
	}

	csText = _T("(")+csText+_T(")");

	csOutput.Add(csPreText+csInput+csText);
	return bRet;



}
BOOL _ExplainCause(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csPreText;
	csPreText = _T("Cause \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);
	return bRet;
}
BOOL _ExplainLocationStatus(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	csPreText = _T("Location status \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);

	switch(_CString2Int(csInput))
	{

	case 0 : csText= _T("Normal service");break;
	case 1 : csText= _T("Limited service");break;
	case 2 : csText= _T("No service");break;
	default: csText= _T("reserved");break;
	}
	csText= _T("(")+csText+_T(")");
	csOutput.Add(csPreText+csInput+csText);
	return bRet;
}
BOOL _ExplainTransactionIdentifier(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csPreText;
	csPreText = _T("Transaction identifier \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);

	return bRet;
}
BOOL _ExplainBCCHChannelList(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csPreText;
	csPreText = _T("BCCH channel list \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);

	return bRet;

}
BOOL _ExplainCardStatus(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	int iStatus = _CString2Int( csInput);
	CString csText;
	CString csPreText;
	csPreText = _T("Card Status \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);

	csPreText = _T("Identity of card reader \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	_Int2CStringDecimal(iStatus&7,csText);
	csOutput.Add(csPreText+ csText);

	csPreText.Empty();
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	if (iStatus&8)
		csText =_T("Card reader is removable");
	else
		csText =_T("Card reader is not removable");
	csOutput.Add(csPreText+ csText);
	csPreText.Empty();
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	if (iStatus&16)
		csText =_T("Card reader is present");
	else
		csText =_T("Card reader is not present");
	csOutput.Add(csPreText+ csText);
	csPreText.Empty();
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	if (iStatus&32)
		csText =_T("Card reader present is ID-1 size");
	else
		csText =_T("Card reader present is not ID-1 size");
	csOutput.Add(csPreText+ csText);
	csPreText.Empty();
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	if (iStatus&64)
		csText =_T("Card is present in reader ");
	else
		csText =_T("No card present ");
	csOutput.Add(csPreText+ csText);
		
	csPreText.Empty();
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	if (iStatus&128)
		csText =_T("Card in reader is powered");
	else
		csText =_T("No card powered");
	csOutput.Add(csPreText+ csText);

	return bRet;

}
BOOL _ExplainTimeValue(CString csInput, CStringArray&csOutput)
{

	BOOL bRet = TRUE;
	CString csPreText;
	CString csText = csInput;
	csPreText = _T("Time Value \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	_ExchangeAt(csText);
	csText = csText.Mid(0,2)+_T(" \\- ")+csText.Mid(2,2)+_T(" \\- ")+csText.Mid(4,2);
	csText = _T("(")+csText+_T(")");

	csOutput.Add(csPreText+csInput+csText);

	return bRet;
}

CString _TranslateDateTimeAndTimeZone( CString csInput )
{
	CString csText = csInput;
	_ExchangeAt(csText);

	if (_CString2Int(csText.Mid(0,2))>= 0x70)
		csText = _T("19")+csText;
	else if (_CString2Int(csInput.Mid(0,2)) > 0xA0)
		csText = _T("FF")+csText;
	else
		csText = _T("20")+csText;



	csText = csText.Mid(0,4)+_T("-")+
		csText.Mid(4,2)+_T("-")+
		csText.Mid(6,2)+_T(" ")+
		csText.Mid(8,2)+_T(" - ")+
		csText.Mid(10,2)+_T(" - ")+
		csText.Mid(12,2)+_T(" ");
	csText+= csInput.Right(2);
	return csText;
}

BOOL _ExplainDateTimeandTimezone(CString csInput, CStringArray&csOutput)
{

	BOOL bRet = TRUE;
	if (csInput.GetLength() != 14)

		return FALSE;
	CString csPreText;
	CString csText = csInput;
	csPreText = _T("Date Time and Timezone \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csText = _TranslateDateTimeAndTimeZone(csText);

	csText = _T("(")+csText+_T(")");

	csOutput.Add(csPreText+csInput+csText);

	return bRet;
}
BOOL _ExplainTemp(CString csName,CString csInput, CStringArray&csOutput)
{

	BOOL bRet = TRUE;
	CString csPreText;
	csPreText = csName+_T(" \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);

	return bRet;
}
BOOL _ExplainBCRepeatIndicator(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	csPreText = _T("BC Repeat Indicator \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);

	switch(_CString2Int(csInput))
	{
	case 1 : csText= _T("Alternate mode");break;
	case 2 : csText= _T("Sequential mode");break;
	default: csText= _T("reserved");break;
	}
	csText= _T("(")+csText+_T(")");
	csOutput.Add(csPreText+csInput+csText);
	return bRet;
}
BOOL _ExplainTimingAdvance(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	csPreText = _T("Timing Advance \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);

	switch(_CString2Int(csInput.Mid(0,2)))
	{
	case 0 : csText= _T("ME is in the idle state");break;
	case 1 : csText= _T("ME is not in idle state");break;
	default: csText= _T("reserved values");break;
	}
	csText= _T("(")+csText+_T(")");
	csOutput.Add(csPreText+csInput+csText);
	return bRet;
}
BOOL _ExplainBearer(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csPreText;
	CString csText;
	csPreText = _T("List of bearers in order of priority requested \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);

	csText.Empty();
	for (int i = 0 ; i < csInput.GetLength() ; i+=2)
	{
		switch(_CString2Int(csInput.Mid(i,2)))
		{
		case 0: csText += _T("SMS");break;
		case 1: csText += _T("CSD");break;
		case 2: csText += _T("USSD");break;
		case 3: csText += _T("GPRS");break;
		default:  csText += _T("RFU");break;
		}
		csText+= _T(";");
	}

	csText = _T("(")+csText+_T(")");

	csOutput.Add(csPreText+csInput+csText);
	return bRet;



}
BOOL _ExplainBrowserTerminationCause(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	csPreText = _T("Browser Termination Cause \\- ");
	////__APDUExplainFormat(csPreText,Def_Min_Formate_Length);

	switch(_CString2Int(csInput.Mid(0,2)))
	{
	case 0 : csText= _T("User Termination");break;
	case 1 : csText= _T("Error Termination");break;
	default: csText= _T("reserved");break;
	}
	csText= _T("(")+csText+_T(")");
	csOutput.Add(csPreText+csInput+csText);
	return bRet;
}

BOOL _ExplainBearerDescription(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;


	csPreText = _T("Bearer description \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
		csOutput.Add(csPreText+csInput);

	csPreText = _T("Bearer type \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	switch(_CString2Int(csInput.Mid(0,2)))
	{
	case 1 : csText= _T("CSD");break;
	case 2 : csText= _T("GPRS");break;
	case 3 : csText= _T("default bearer for requested transport layer");break;
	default: csText= _T("reserved");break;
	}
	csText= _T("(")+csText+_T(")");
	csOutput.Add(csPreText+csInput+csText);


	csPreText = _T("Bearer description \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput.Mid(2));
	return bRet;
}


BOOL _ExplainChannelStatus(CString csInput, CStringArray&csOutput)
{

	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;
	csPreText = _T("Channel status \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);

	csText.Format("Channel identifier %d;",_CString2Int(csInput.Mid(0,2))&0x7);

	if (_Getbit(csInput,8))
		csText += _T(" Link established; ");
	else
		csText += _T(" Link not established; ");


	switch(_CString2Int(csInput.Mid(2,2)))
	{
	case 0: csText+= _T("No further info can be given");break;
	case 1: csText+= _T("Error Termination");break;
	case 2: csText+= _T("Rx buffer full");break;  
	case 3: csText+= _T("Rx buffer empty");break;  
	case 4: csText+= _T("Tx buffer empty");break;  
	case 5: csText+= _T("Link dropped");break;  
	default:csText+= _T("reserved");break;
	}
	csText= _T("(")+csText+_T(")");
	csOutput.Add(csPreText+csInput+csText);

	


	return bRet;
}

BOOL _ExplainSIMMEInterfaceTransportLevel(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;


	csPreText = _T("SIM/ME interface transport level \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);

	csPreText = _T("Transport protocol type \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	switch(_CString2Int(csInput.Mid(0,2)))
	{
	case 1 : csText= _T("UDP");break;
	case 2 : csText= _T("TCP");break;
	default: csText= _T("reserved");break;
	}
	csText= _T("(")+csText+_T(")");
	csOutput.Add(csPreText+csInput+csText);


	csPreText = _T("Port number \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput.Mid(2));
	return bRet;

}
BOOL _ExplainOtherAddress(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csPreText;


	csPreText = _T("Other Address \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	csOutput.Add(csPreText+csInput);

	csPreText = _T("Type of address \\- ");
	//__APDUExplainFormat(csPreText,Def_Min_Formate_Length);
	switch(_CString2Int(csInput.Mid(0,2)))
	{
	case 0x21 : csText= _T("IPv4");break;
	case 0x97 : csText= _T("IPv6");break;
	default: csText= _T("reserved");break;
	}
	csText= _T("(")+csText+_T(")");
	csOutput.Add(csPreText+csInput.Mid(0,2)+csText);


	csPreText = _T("Address \\- ");
	
	csOutput.Add(csPreText+csInput.Mid(2));
	return bRet;

}
BOOL _ExplainURL(CString csInput, CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	CString csText;
	CString csTemp;
	CString csPreText;
	csPreText = _T("URL \\- ");

	_Translate7bit(csInput,csTemp);
	bRet = _TranslateAscii(csTemp,csText);
	csText= _T("(")+csText+_T(")");
	csOutput.Add(csPreText+csInput);
	return bRet;
}

BOOL _ExplainSelectP1(int iP1,CStringArray&csOutput)
{
	BOOL  bRet = TRUE;
	CString csText;
	switch(iP1)
	{

	case 0:
		csText = _T("Select MF, DF or EF");
		break;
	case 1:
		csText =_T("Select child DF");
		break;
	case 2:
		csText =_T("Select EF under the current DF");
		break;
	case 3:
		csText =_T("Select parent DF of the current DF");
		break;
	case 4:
		csText =_T("Select by DF name");
		break;
	case 8:
		csText =_T("Select from the MF");
		break;
	case 9:
		csText =_T("Select from the current DF");
		break;
	default: bRet = FALSE;break;

	}
	if (bRet)
	{
		csOutput.Add(_T("P1 \\- ")+csText);
	}
	return bRet;
}
BOOL _ExplainSelectP2(int iP2,CStringArray&csOutput)
{
	BOOL  bRet = TRUE;
	CString csText; 

	switch(iP2&3)
	{

	case 0:csText=_T("First or only occurrence");break;
	case 1:csText=_T("Last occurrence");break;
	case 2:csText=_T("Next occurrence");break;
	case 3:csText=_T("Previous occurrence");break;
	default: bRet = FALSE;break;
	}

	if (bRet)
		csOutput.Add(_T("P2 \\- ")+csText);

	switch(iP2&12)
	{

	case 0:
		csOutput.Add(_T("Return FCI template, optional use of FCI tag and length"));
		break;
	case 4:
		csOutput.Add(_T("Return FCP template, mandatory use of FCP tag and length"));
		break;
	case 8:
		csOutput.Add(_T("Return FMD template, mandatory use of FMD tag and length"));
		break;
	case 12:
		csOutput.Add(_T("No response data if Le field absent, or proprietary if Le field present"));
		break;
	default: bRet = FALSE;break;
	}

	if (iP2&0x40)
		csOutput.Add(_T("Termination file"));
	else
		csOutput.Add(_T("Activation/Reset file"));


	return bRet;
}

BOOL __AddFileName(CString csText,CStringArray&csOutput)
{
	csText = _T(" (")+csText+_T(")");
	CString csTemp;
	int iOff;
	if (csOutput.GetCount() < 1)
		return FALSE;
	csTemp = csOutput.GetAt(0);
	iOff   = csTemp.Find(_T(":"));

	if ((!csTemp.IsEmpty())&&
		(iOff>0))
	{
		csTemp = csTemp.Mid(0,iOff)+ csText + csTemp.Mid(iOff);

		csOutput.SetAt(0,csTemp);

		return TRUE;
	}
	return FALSE;
}
BOOL _ExplainSelectData(int iP1,CString csData,CStringArray&csOutput)
{
	
	BOOL  bRet = TRUE;
	CString csText;
	//int iFID;
	int iMarkTemp = _DEF_Card;
	int iFileMark;

 	switch(iP1)
	{
	case 0:
		iMarkTemp = GetCurrentDF();
		if (_CString2Int( csData )== 0x3F00)
		{
			csText    = _T("MF");
			iMarkTemp = _DEF_Card;
		}
		else if (GetFileNameFromReference(_CString2Int(csData), iMarkTemp, csText, true))
		{
			if ((GetDFMark(csData, iMarkTemp, &iFileMark) == TRUE) ||
				(GetDFMark(csData, iMarkTemp & 0xF0, &iFileMark) == TRUE))
			{
				iMarkTemp = iFileMark;
				bRet = TRUE;
			}
				

		}
		else if(((GetDFMark(csData,iMarkTemp,&iFileMark)== TRUE)&&
		    	  GetDFName(iFileMark,csText))                    ||
				((GetDFMark(csData,iMarkTemp&0xF0,&iFileMark)== TRUE)&&
				  GetDFName(iFileMark,csText)))
		{
				iMarkTemp = iFileMark ;
				bRet = TRUE;   
		}
	
		else
			bRet = FALSE;
		if (bRet)
			SetCurrentDF(iMarkTemp);
		break;

	case 1:
		//iMarkTemp = GetCurrentDF();
		//bRet      = Try2GenerateFileName(iMarkTemp,_CString2Int(csData),csText);
		//bRet      = Try2GenerateFileName(iMarkTemp,_CString2Int(csData.Right(4)),csText);
		//if (bRet)
		//	SetCurrentDF(iMarkTemp);

		iMarkTemp = GetCurrentDF();
		if(GetDFMark(csData,iMarkTemp,&iFileMark)&&
			GetDFName(iFileMark,csText))
		{
			iMarkTemp = iFileMark ;
			bRet = TRUE;
		}
		if (bRet)
			SetCurrentDF(iMarkTemp);
		break;
	case 2:
		iMarkTemp = GetCurrentDF();
		//bRet      = Try2GenerateFileName(iMarkTemp,_CString2Int(csData),csText);
		break;
	case 3:
		iMarkTemp = GetCurrentDF();
		SetCurrentDF(iMarkTemp&0xF0);
		break;
	case 4:
		//if (GenerateADFName(csData,csText))
		//{
		if((GetADFMark(csData,&iMarkTemp))&&
		   (GetDFName(iMarkTemp,csText)))
		{
			csOutput.Add(_T("Select DF name  \\- ")+csText);
			//if (csText.Compare(_T("3GPP"))  == 0)
			//	SetCurrentDF(_DEF_3GPP);
			//else if(csText.Compare(_T("3GPP2"))  == 0)
			//	SetCurrentDF(_DEF_3GPP2);
			//else if(csText.Compare(_T("3GPP2")) == 0)
			//	SetCurrentDF(_DEF_ETSI);
			//else
			//	SetCurrentDF(_DEF_Card);
			SetCurrentDF(iMarkTemp);
		}
		break;
	case 9:
		if ((GetDFMark(csData, GetCurrentDF(),&iMarkTemp))&&
			(GetDFName(iMarkTemp,csText)))
			bRet = TRUE;
		if (bRet)
			SetCurrentDF(iMarkTemp);
	case 8:
		/*iMarkTemp = Try2GetFileMark(csData,iMarkTemp);
		bRet      = Try2GenerateFileName(iMarkTemp,_CString2Int(csData.Right(4)),csText);*/
		if ((GetDFMark(csData,_DEF_Card,&iMarkTemp))&&
			(GetDFName(iMarkTemp,csText)))
			bRet = TRUE;
		if (bRet)
			SetCurrentDF(iMarkTemp);
		break;	
	}
	if ((bRet)&&(!csText.IsEmpty()))
		bRet = __AddFileName(csText,csOutput);

	return bRet;
}

BOOL _ExplainSelect_UICC(CString csSend,CString csResp,CStringArray&csOutput)
{
	CString csFile = csSend.Mid(10);
	int iP1,iP2,iP3;
	iP1 = _CString2Int(csSend.Mid(4,2));
	iP2 = _CString2Int(csSend.Mid(6,2));
	iP3 = _CString2Int(csSend.Mid(8,2));
	if (!_ExplainSelectData(iP1,csSend.Mid(10),csOutput))
		return FALSE;
	if(!_ExplainSelectP1(iP1,csOutput))
		return FALSE;
	if(!_ExplainSelectP2(iP2,csOutput))
		return FALSE;

	


	return TRUE;

}

BOOL _ExplainSelect(CString csSend,CString csResp,CStringArray&csOutput)
{
	BOOL bRet = FALSE;
	if (_CString2Int(csSend.Mid(0,2)) == 0x00)
	{
		bRet = _ExplainSelect_UICC( csSend, csResp,csOutput);
	}
	return bRet;
}

BOOL _ExplainReadBinary_UICC(CString csSend, CStringArray&csOutput)
{
	int iP1,iP2,iOffset,iLength;
	BOOL bRet = TRUE; 
	CString csText;
	iP1     = _CString2Int(csSend.Mid(4,2));
	iP2     = _CString2Int(csSend.Mid(6,2));

	if (iP1&0x80)
	{
		_Int2CStringDecimal(iP1&0x1F,csText);
		csOutput.Add(_T("SFI \\- ")+ csText);
		iOffset = iP2;
	}
	else
		iOffset = iP1*0x100+iP2;

	_Int2CStringDecimal(iOffset,csText);
	csOutput.Add(_T("Read Offset \\- ")+ csText);

	iLength = _CString2Int(csSend.Mid(8,2));
	if (iLength == 00)
		iLength += 0x100;
	_Int2CStringDecimal(iLength,csText);
	csOutput.Add(_T("Read Length \\- ")+ csText);

	return bRet;

}

BOOL _ExplainReadBinary(CString csSend, CStringArray&csOutput)
{
	BOOL bRet = FALSE;
	if (_CString2Int(csSend.Mid(0,2)) == 0x00)
	{
		bRet = _ExplainReadBinary_UICC( csSend,csOutput);
	}
	return bRet;

}

BOOL _ExplainUpdateBinary_UICC(CString csSend, CStringArray&csOutput)
{
	BOOL bRet = TRUE; 
	int iP1,iP2,iOffset,iLength;
	CString csText;

	iP1     = _CString2Int(csSend.Mid(4,2));
	iP2     = _CString2Int(csSend.Mid(6,2));


	if (iP1&0x80)
	{
		_Int2CStringDecimal(iP1&0x1F,csText);
		csOutput.Add(_T("SFI \\- ")+ csText);
		iOffset = iP2;
	}
	else
		iOffset = iP1*0x100+iP2;

	_Int2CStringDecimal(iOffset,csText);
	csOutput.Add(_T("Update Offset \\- ")+ csText);

	iLength = _CString2Int(csSend.Mid(8,2));
	if (iLength == 00)
		iLength += 0x100;
	_Int2CStringDecimal(iLength,csText);
	csOutput.Add(_T("Update Length \\- ")+ csText);

	return bRet;

}

BOOL _ExplainUpdateBinary(CString csSend, CStringArray&csOutput)
{
	BOOL bRet = FALSE;
	if (_CString2Int(csSend.Mid(0,2)) == 0x00)
	{
		bRet = _ExplainUpdateBinary_UICC( csSend,csOutput);
	}
	return bRet;

}

BOOL _ExplainReadRecord_UICC(CString csSend, CString csResp, CStringArray&csOutput)
{
	BOOL bRet = TRUE; 
	int iP1,iP2,iP3;
	CString csText;
	CString csP1;

	iP1 = _CString2Int(csSend.Mid(4,2));
	iP2 = _CString2Int(csSend.Mid(6,2));
	iP3 = _CString2Int(csSend.Mid(8,2));

	if ((iP1 == 0xFF)&&(iP2 == 0xFF))
	{
		if (__ExplainID2ResponsePatcket(csResp.Mid(0,csResp.GetLength()-4),csOutput))
			return TRUE;

	}


	if (iP1 == 0)
		csText = _T("Record number \\- References the current record");
	else
	{
		_Int2CStringDecimal(iP1,csP1);
		csText =_T("Record number \\- ")+csP1;
	}
	csOutput.Add(csText);

	if (iP2>7)
	{
		_Int2CStringDecimal(iP2>>3,csText);
		csOutput.Add(_T("SFI \\- ")+csText);
	}


	switch(iP2&7)
	{
	case 0:csText  = _T("First Record ");break;
	case 1:csText  = _T("Last Record ");break;
	case 2:csText  = _T("Next Record ");break;
	case 3:csText  = _T("Previous Record ");break;
	case 4:csText  = _T("Absolute/Current");break;
	case 5:csText  = _T("All records from P1 up to the last");break;
	case 6:csText  = _T("All records from the last up to P1");break;
	case 7:csText  = _T("For future use");
		bRet = FALSE;break;
	}

	csOutput.Add(_T("Mode \\- ")+csText);

	_Int2CStringDecimal(iP3,csText);

	csOutput.Add(_T("Record Length \\- ")+csText);

	return bRet;

}

ExpAPDU_API BOOL _ExplainReadRecord(CString csSend, CString csResp, CStringArray&csOutput)
{
	BOOL bRet = FALSE;
	if (_CString2Int(csSend.Mid(0,2)) == 0x00)
	{
		bRet = _ExplainReadRecord_UICC( csSend, csResp,csOutput);
	}
	return bRet;

}

BOOL _ExplainUpdateRecord_UICC(CString csSend, CStringArray&csOutput)
{
	BOOL bRet = TRUE; 
	int iP1,iP2,iP3;
	CString csText;
	CString csP1;

	iP1 = _CString2Int(csSend.Mid(4,2));
	iP2 = _CString2Int(csSend.Mid(6,2));
	iP3 = _CString2Int(csSend.Mid(8,2));

	//解析ID2
	if ((iP1 == 0xFF)&&(iP2 == 0xFF))
	{
		if (__ExplainID2SendPatcket(csSend.Mid(10),csOutput))
			return TRUE;
		csText = csOutput.GetAt(0);
		csOutput.RemoveAll();
		csOutput.Add(csText);

	}






	if (iP1 == 0)
		csText = _T("Record number:References the current record");
	else
	{
		_Int2CStringDecimal(iP1,csP1);
		csText =_T("Record number \\- ")+csP1;
	}
	csOutput.Add(csText);

	if (iP2>7)
	{
		_Int2CStringDecimal(iP2>>3,csText);
		csOutput.Add(_T("SFI \\- ")+csText);
	}

	switch(iP2&7)
	{
	case 0:csText = _T("First Record ");break;
	case 1:csText = _T("Last Record ");break;
	case 2:csText = _T("Next Record ");break;
	case 3:csText = _T("Previous Record ");break;
	case 4:csText = _T("Absolute/Current mode");break;
	default:bRet = FALSE;break;
	}

	csOutput.Add(_T("Update Mode \\- ")+csText);

	_Int2CStringDecimal(iP1,csText);

	csOutput.Add(_T("Record Length \\- ")+csText);

	return TRUE;

}
BOOL _ExplainUpdateRecord(CString csSend, CStringArray&csOutput)
{
	BOOL bRet = FALSE;
	if (_CString2Int(csSend.Mid(0,2)) == 0x00)
	{
		bRet = _ExplainUpdateRecord_UICC( csSend,csOutput);
	}
	return bRet;

}
BOOL _ExplainSearchRecord_UICC(CString csSend, CStringArray&csOutput)
{
	BOOL bRet = TRUE; 
	int iP1,iP2,iP3,i1stCode;
	CString csText;
	CString csP1;

	iP1 = _CString2Int(csSend.Mid(4,2));
	iP2 = _CString2Int(csSend.Mid(6,2));
	iP3 = _CString2Int(csSend.Mid(8,2));
	i1stCode = _CString2Int(csSend.Mid(10,2));

	if (iP1 == 0)
		csText = _T("Record Number:References the current record");
	else
	{
		_Int2CStringDecimal(iP1,csP1);
		csText =_T("Record Number: ")+csP1;
	}
	csOutput.Add(csText);

	if (iP2>7)
	{
		_Int2CStringDecimal(iP2>>3,csText);
		csOutput.Add(_T("SFI \\- ")+csText);
	}

	switch(iP2&7)
	{
	case 4:csText = _T("Simple search;Start forward search form record indicated in P1");break;
	case 5:csText = _T("Simple search;Start backward search form record indicated in P1");break;
	case 6:csText = _T("Enhanced search;");



		switch( i1stCode&7 )
		{
			case 4:csText += _T("Start forward search form record indicated in P1;");break;
			case 5:csText += _T("Start backward search form record indicated in P1;");break;
			case 6:csText += _T("Start forward search from next record;");break;
			case 7:csText += _T("Start backward search form previous record;");break;
		}

		if (i1stCode&0x8)
			csText += _T("The search starts in the record from the offset (absolute position) given in the second byte of the search indication");
		else
			csText += _T("The search starts in the record after the first occurrence of the value contained in the second byte of the search indication");
		break;

	case 7:csText = _T("Proprietary search");
		break;
	}


	//switch(iP2&7)
	//{
	//case 0:csText = _T("Simple search forward from first occurrence");break;
	//case 1:csText = _T("Simple search backward from last occurrence");break;
	//case 2:csText = _T("Simple search forward from next occurrence");break;
	//case 3:csText = _T("Simple search backward from previous occurrence");break;
	//case 4:csText = _T("Enhanced search ");
	//	i1stCode  = _CString2Int(csSend.Mid(10,2));

	//	switch( i1stCode&7 )
	//	{
	//	case 0:csText += _T("forward from first occurrence");break;
	//	case 1:csText += _T("backward from last occurrence");break;
	//	case 2:csText += _T("forward from next occurrence");break;
	//	case 3:csText += _T("backward from previous occurrence");break;
	//	case 4:csText += _T("forward from P1");break;
	//	case 5:csText += _T("backward from P1");break;
	//	case 6:csText += _T("forward from next record");break;
	//	case 7:csText += _T("backward from previous record");break;

	//	}
	//	if (i1stCode&4)
	//		csText += _T(", Record identifier in P1,");
	//	else
	//		csText += _T(", Record number in P1,");
	//	if (i1stCode&8)
	//		csText += _T(" The subsequent byte is an offset (start from that position)");
	//	else
	//		csText += _T(" The subsequent byte is a value (start after the first occurrence)");

	//	break;

	//default:csText = _T("Reserved for future use");
	//	bRet = FALSE;break;
	//}

	csOutput.Add(_T("Mode \\- ")+csText);

	_Int2CStringDecimal(iP1,csText);

	csOutput.Add(_T("Search Length \\- ")+csText);

	return bRet;

}
BOOL _ExplainSearchRecord(CString csSend, CStringArray&csOutput)
{
	BOOL bRet = FALSE;
	if (_CString2Int(csSend.Mid(0,2)) == 0x00)
	{
		bRet = _ExplainSearchRecord_UICC( csSend,csOutput);
	}
	return bRet;

}
BOOL _ExplainIncrease_UICC(CString csSend, CStringArray&csOutput)
{
	int iP1;

	CString csText;
	iP1     = _CString2Int(csSend.Mid(4,2));

	if (iP1&0x80)
	{
		_Int2CStringDecimal(iP1&0x1F,csText);
		csOutput.Add(_T("SFI: ")+ csText);
	}

	return TRUE;

}
BOOL _ExplainIncrease(CString csSend, CStringArray&csOutput)
{
	int iP1;

	CString csText;
	iP1     = _CString2Int(csSend.Mid(4,2));

	if (iP1&0x80)
	{
		_Int2CStringDecimal(iP1&0x1F,csText);
		csOutput.Add(_T("Increate by SFI, SFI is ")+ csText);
	}

	return TRUE;

}
BOOL _ExplainDeactiveActive_UICC(CString csSend,CStringArray&csOutput)
{
	BOOL bRet = TRUE; 
	int iP1,iP3;
	CString csText;

	iP1 = _CString2Int( csSend.Mid(4,2));
	iP3 = _CString2Int( csSend.Mid(8,2));

	switch(iP1)
	{
	case 0:
		if (iP3 == 0)
			csText = _T("Current EF");
		else
			csText = _T("Select EF by file id");
		break;
	case 1:csText = _T("Select by path from MF");break;
	case 2:csText = _T("Select by path from current DF");break;
	default:csText = _T("RFU");
		bRet = FALSE;break;

	}
	csOutput.Add(_T("Mode \\- ")+csText);
	return bRet;
}
BOOL _ExplainDeactiveActive(CString csSend,CStringArray&csOutput)
{
	BOOL bRet = FALSE;
	if (_CString2Int(csSend.Mid(0,2)) == 0x00)
	{
		bRet = _ExplainDeactiveActive_UICC( csSend,csOutput);
	}
	return bRet;
}
BOOL _ExplainManageChannel(CString csSend,CStringArray&csOutput)
{
	BOOL bRet = TRUE; 
	int iP1;
	CString csText;
	iP1 = _CString2Int( csSend.Mid(4,2));

	switch(iP1)
	{
	case 00    :csText=_T("Open logical channel");break;	
	case 0x80  :csText=_T("Close logical channel");break;
	default    :bRet = FALSE;break;
	}
	csOutput.Add(_T("Operation \\- ")+csText);
	return bRet;
}
BOOL _ExplainStatus_UICC(CString csSend,CStringArray&csOutput)
{
	BOOL bRet = TRUE; 
	int iP1,iP2;
	CString csText;
	iP1 = _CString2Int( csSend.Mid(4,2));
	iP2 = _CString2Int( csSend.Mid(6,2));

	switch(iP1)
	{
	case 0:csText = _T("No indication");break;
	case 1:csText = _T("Current application is initialized in the terminal");break;
	case 2:csText = _T("The terminal will initiate the termination of the current application");break;
	default:bRet = FALSE;
	}

	csOutput.Add(_T("P1 \\- ")+csText);

	switch(iP2)
	{
	case 0:csText = _T("Response parameters and data are identical to the response parameters and data of the SELECT command");break;
	case 1:csText = _T("The DF name TLV-object of the currently selected application is returned");break;
	case 0xC:csText = _T("No data returned");break;
	default:bRet = FALSE;
	}
	csOutput.Add(_T("P2 \\- ")+csText);
	return bRet;
}
BOOL _ExplainStatus(CString csSend,CStringArray&csOutput)
{
	BOOL bRet = FALSE;
	if (_CString2Int(csSend.Mid(0,2)) == 0x80)
		bRet = _ExplainStatus_UICC( csSend,csOutput);
	return bRet;
}
BOOL _ExplainGetResponse(int iPreIns,CString csResp,CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	//去除SW 便于分辨数据类别
	csResp = csResp.Mid(0,csResp.GetLength()-4);
	switch(iPreIns)
	{
	//case 0x32:
	//	break;
	//case 0x84:
	//	break;
	case 0x88:bRet = _ExplainAuthenticateResponse(csResp,csOutput);break;
	case 0xA4:bRet = _ExplainSelectResponse(csResp,csOutput);break;
	case 0xC0:
		break;
	}

	return bRet;
}


BOOL _Explain80Data(CString cs80Data,CStringArray&csOutput)
{
	CString csText;
	if (cs80Data.IsEmpty())
		return FALSE;

	_Int2CStringDecimal(_CString2Int(cs80Data),csText);

	csOutput.Add(_T("File Size \\- ")+csText);

	return TRUE;
}
BOOL _Explain81Data(CString cs81Data,CStringArray&csOutput)
{
	if (cs81Data.IsEmpty())
		return FALSE;
	CString csText;
	_Int2CStringDecimal(_CString2Int(cs81Data),csText);
	csOutput.Add(_T("Total file size \\- ")+csText);

	return TRUE;
}
BOOL _Explain82Data(CString cs82Data,CStringArray&csOutput)
{
	CString csText;
	int iDes;
	if (cs82Data.IsEmpty())
		return FALSE;

	iDes = _CString2Int(cs82Data.Mid(0,2));

	if (iDes&0x80)
		 csText = _T("Shareable file");
	else
	     csText = _T("Not shareable file");

	csOutput.Add(_T("File Descriptor \\- ")+csText);

	switch(iDes&0x38)
	{
	case 0x38:csOutput.Add(_T("DF or ADF"));break;
	case 0:   csOutput.Add(_T("Working EF"));break;
	case 0x8: csOutput.Add(_T("Internal EF"));break;
	default:  csOutput.Add(_T("RFU"));break;
	}

	switch(iDes&0x7)
	{
	case 0:   csOutput.Add(_T("No information given"));break;
	case 1:   csOutput.Add(_T("Transparent structure"));break;
	case 2:   csOutput.Add(_T("Linear fixed structure"));break;
	case 6:   csOutput.Add(_T("Cyclic structure"));break;
	default:  csOutput.Add(_T("RFU"));break;
	}

	if (cs82Data.GetLength()>=8)
	{
		_Int2CStringDecimal(_CString2Int(cs82Data.Mid(4,4)),csText);
		csOutput.Add(_T("Record Length \\- ")+ csText);
	}

	if (cs82Data.GetLength()>=10)
	{
		_Int2CStringDecimal(_CString2Int(cs82Data.Mid(8,2)),csText);
		csOutput.Add(_T("Number of records \\- ")+ csText);
	}

	return TRUE;
}
BOOL _Explain83Data(CString cs83Data,CStringArray&csOutput)
{
	if (cs83Data.GetLength() != 4)
		return FALSE;

	csOutput.Add(_T("File Identifier \\- ")+cs83Data);

	CString csText;
	int iMarkTemp = GetCurrentDF();
	int iFID = _CString2Int(cs83Data);
	//if (Try2GenerateFileName(iMarkTemp,iFID,csText))
	if (GetFileNameFromReference(iFID,iMarkTemp,csText))
		csOutput.Add(_T("File Name \\- ")+csText);
	return TRUE;
}
BOOL _Explain84Data(CString cs84Data,CStringArray&csOutput)
{
	if ((cs84Data.GetLength() <10)||
		(cs84Data.GetLength() >32))
		return FALSE;

	csOutput.Add(_T("DF name (AID) \\- ")+cs84Data);

	return TRUE;
}
BOOL _Explain85Data(CString cs85Data,CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	return bRet;
}
BOOL _Explain88Data(CString cs88Data,CStringArray&csOutput)
{
	CString csText;
	if (cs88Data.IsEmpty())
		return FALSE;
	int iTemp = _CString2Int(cs88Data);

		
	iTemp     = iTemp>>3;
	_Int2CStringDecimal(iTemp,csText);
	csOutput.Add(_T("SFI \\- ")+csText);


	return TRUE;
}
BOOL _Explain8AData(CString cs8AData,CStringArray&csOutput)
{
	CString csText;
	if (cs8AData.IsEmpty())
		return FALSE;
	int iTemp = _CString2Int(cs8AData);


	switch(iTemp&0xF)
	{
	case 0:csText = _T("No information given");         break;
	case 1:csText = _T("Creation state");               break;
	case 3:csText = _T("Initialization state");         break;
	case 5:
	case 7:csText = _T("Operational state activated");  break;
	case 4:
	case 6:csText = _T("Operational state deactivated");break;
	case 8:csText = _T("RFU");                          break;
	default:csText = _T("Termination state");           break;

	}

	csOutput.Add(_T("Proprietary \\- ")+csText);

	return TRUE;
}
BOOL _Explain8BData(CString cs8BData,CStringArray&csOutput)
{
	if (cs8BData.GetLength()!=6)
		return FALSE;

	csOutput.Add(_T("Security attributes \\- Referenced to expanded format"));
	csOutput.Add(_T("ARR Record \\- ")+cs8BData);

	return TRUE;
}
BOOL _Explain8CData(CString cs8CData,CStringArray&csOutput)
{

	if (cs8CData.IsEmpty())
		return FALSE;

	csOutput.Add(_T("Security attributes \\- Compact format"));
	csOutput.Add(_T("AM \\- ")+cs8CData.Mid(0,2));
	csOutput.Add(_T("SC \\- ")+cs8CData.Mid(2));

	return TRUE;

}
BOOL _Explain8DData(CString cs82Data,CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	return bRet;
}
BOOL _Explain8EData(CString cs8CData,CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	return bRet;
}
BOOL _ExplainA580Data(CString cs80Data,CStringArray&csOutput)
{
	CString csText;
	int iTemp; 
	if (cs80Data.IsEmpty())
		return FALSE;

	iTemp = _CString2Int(cs80Data);

	if (iTemp&1)
	{
		csOutput.Add(_T("Clock Stop \\- Allowed"));

		switch(iTemp&0xC)
		{
		case 0xC:csOutput.Add(_T("RFU"));                  break;
		case 0x8:csOutput.Add(_T("Low level preferred"));  break;
		case   4:csOutput.Add(_T("High level preferred")); break;
		case   0:csOutput.Add(_T("No preferred level"));   break;
		}
	}
	else
		csOutput.Add(_T("Clock Stop \\- Not allowed"));

	csText = _T("Supply Voltage \\- ");

	if (iTemp&0x10)
	{
		csOutput.Add(csText+ _T("Class A"));
		csText.Empty();
	}

	if (iTemp&0x20)
	{
		csOutput.Add(csText+ _T("Class B"));
		csText.Empty();
	}

	if (iTemp&0x40)
	{
		csOutput.Add(csText+ _T("Class C"));
		csText.Empty();
	}

	return TRUE;
}
BOOL _ExplainA581Data(CString cs81Data,CStringArray&csOutput)
{

	if (cs81Data.IsEmpty())
		return FALSE;

	csOutput.Add(_T("Application power consumption \\- ")+ cs81Data.Mid(0,2));
	csOutput.Add(_T("Power consumption reference frequency \\- ")+ cs81Data.Mid(2,2));
	return TRUE;
}
BOOL _ExplainA582Data(CString cs82Data,CStringArray&csOutput)
{
	if (cs82Data.IsEmpty())
		return FALSE;

	csOutput.Add(_T("Application minimum clock frequency \\- ")+ cs82Data.Mid(0,2));
	return TRUE;
}
BOOL _ExplainA583Data(CString cs83Data,CStringArray&csOutput)
{
	if (cs83Data.IsEmpty())
		return FALSE;

	csOutput.Add(_T("Amount of available memory \\- ")+ cs83Data);
	return TRUE;
}
BOOL _ExplainA584Data(CString cs84Data,CStringArray&csOutput)
{
	if (cs84Data.IsEmpty())
		return FALSE;

	csOutput.Add(_T("File details \\- ")+ cs84Data);
	return TRUE;
}
BOOL _ExplainA585Data(CString cs85Data,CStringArray&csOutput)
{ 
	if (cs85Data.IsEmpty())
		return FALSE;

	csOutput.Add(_T("Reserved File size \\- ")+ cs85Data);
	return TRUE;
}
BOOL _ExplainA586Data(CString cs86Data,CStringArray&csOutput)
{
	if (cs86Data.IsEmpty())
		return FALSE;

	csOutput.Add(_T("Maximum file size \\- ")+ cs86Data);
	return TRUE;
}
BOOL _ExplainA587Data(CString cs87Data,CStringArray&csOutput)
{

	CString csText;
	if (cs87Data.IsEmpty())
		return FALSE;

	if (_CString2Int(cs87Data.Mid(0,2))&1 )
	{
		csText = _T("Supported");
	}else
		csText = _T("Not supported");


	csOutput.Add(_T("Supported system commands \\- ")+ csText);
	return TRUE;
}
BOOL _ExplainA588Data(CString cs88Data,CStringArray&csOutput)
{

	CString csText;
	
	if (cs88Data.IsEmpty())
		return FALSE;

	switch(_CString2Int(cs88Data.Mid(0,2))&7)
	{
	case 0:csText = _T("Standard temperature range");break;
	case 1:csText = _T("class A");break;
	case 2:csText = _T("class B");break;
	case 3:csText = _T("class C");break;
	default:csText = _T("RFU");break;
	}
	csOutput.Add("Temperature \\- "+ csText);

	if (_CString2Int(cs88Data.Mid(0,2))&8)
		csText = _T("Not supported");
	else
		csText = _T("Supported");

	csOutput.Add(_T("High humidity \\- ")+ csText);

	return TRUE;
}
BOOL _ExplainA5Data(CString csA5Data,CStringArray&csOutput)
{
	CString csTemp;
	if (csA5Data.IsEmpty())
		return FALSE;

	if (_GetTLVData(csA5Data,0x80 ,csTemp))
		_ExplainA580Data(csTemp,csOutput);
	if (_GetTLVData(csA5Data,0x81 ,csTemp))
		_ExplainA581Data(csTemp,csOutput);
	if (_GetTLVData(csA5Data,0x82 ,csTemp))
		_ExplainA582Data(csTemp,csOutput);
	if (_GetTLVData(csA5Data,0x83 ,csTemp))
		_ExplainA583Data(csTemp,csOutput);
	if (_GetTLVData(csA5Data,0x84 ,csTemp))
		_ExplainA584Data(csTemp,csOutput);
	if (_GetTLVData(csA5Data,0x85 ,csTemp))
		_ExplainA585Data(csTemp,csOutput);
	if (_GetTLVData(csA5Data,0x86 ,csTemp))
		_ExplainA586Data(csTemp,csOutput);
	if (_GetTLVData(csA5Data,0x87 ,csTemp))
		_ExplainA587Data(csTemp,csOutput);
	if (_GetTLVData(csA5Data,0x88 ,csTemp))
		_ExplainA588Data(csTemp,csOutput);
	return TRUE;
}
BOOL _ExplainABData(CString csABData,CStringArray&csOutput)
{
	if (csABData.IsEmpty())
		return FALSE;

	csOutput.Add(_T("Security Attributes \\- Expanded format"));
	csOutput.Add(_T("Security Rule \\- ") + csABData);

	return TRUE;
}
BOOL _ExplainC6Data(CString csC6Data,CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	return bRet;
}
BOOL _ExplainACData(CString cs81Data,CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	return bRet;
}
BOOL _ExplainFCP(CString csFCP,CStringArray&csOutput)
{
	BOOL bRet;

	CString csTemp;
	if (_GetTLVData(csFCP,0x80,csTemp))
	{
		bRet = _Explain80Data(csTemp,csOutput);
	}
	if (_GetTLVData(csFCP,0x81,csTemp))
	{
		bRet = _Explain81Data(csTemp,csOutput);
	}
	if (_GetTLVData(csFCP,0x82,csTemp))
	{
		bRet = _Explain82Data(csTemp,csOutput);
	}

	if (_GetTLVData(csFCP,0x83,csTemp))
	{
		bRet = _Explain83Data(csTemp,csOutput);
	}

	if (_GetTLVData(csFCP,0x84,csTemp))
	{
		bRet = _Explain83Data(csTemp,csOutput);
	}

	if (_GetTLVData(csFCP,0xA5,csTemp))
	{
		bRet = _ExplainA5Data(csTemp,csOutput);
	}

	if (_GetTLVData(csFCP,0x8A,csTemp))
	{
		bRet = _Explain8AData(csTemp,csOutput);
	}

	if (_GetTLVData(csFCP,0x8B,csTemp))
	{
		bRet = _Explain8BData(csTemp,csOutput);
	}
	if (_GetTLVData(csFCP,0x8C,csTemp))
	{
		bRet = _Explain8CData(csTemp,csOutput);
	}
	if (_GetTLVData(csFCP,0xAB,csTemp))
	{
		bRet = _ExplainABData(csTemp,csOutput);
	}
	if (_GetTLVData(csFCP,0xC6,csTemp))
	{
		bRet = _ExplainC6Data(csTemp,csOutput);
	}
	if (_GetTLVData(csFCP,0x81,csTemp))
	{
		bRet = _Explain81Data(csTemp,csOutput);
	}
	if (_GetTLVData(csFCP,0x88,csTemp))
	{
		bRet = _Explain88Data(csTemp,csOutput);
	}
	//cs80Value = GetTLVData(csFCI,0x80);
	//cs81Value = GetTLVData(csFCI,0x81);
	//cs82Value = GetTLVData(csFCI,0x82);
	//cs83Value = GetTLVData(csFCI,0x83);
	//cs84Value = GetTLVData(csFCI,0x84);
	//cs85Value = GetTLVData(csFCI,0x85);
	//cs86Value = GetTLVData(csFCI,0x86);
	//cs87Value = GetTLVData(csFCI,0x87);
	//cs88Value = GetTLVData(csFCI,0x88);
	//cs8AValue = GetTLVData(csFCI,0x8A);
	//cs8BValue = GetTLVData(csFCI,0x8B);
	//cs8CValue = GetTLVData(csFCI,0x8C);
	//cs8DValue = GetTLVData(csFCI,0x8D);
	//cs8EValue = GetTLVData(csFCI,0x8E);
	//csA0Value = GetTLVData(csFCI,0xA0);
	//csA1Value = GetTLVData(csFCI,0xA1);
	//csA2Value = GetTLVData(csFCI,0xA2);
	//csABValue = GetTLVData(csFCI,0xAB);
	//csACValue = GetTLVData(csFCI,0xAC);*/

	 //   File Descriptor '82' 11.1.1.4.3 M
		//File Identifier '83' 11.1.1.4.4 C1
		//DF name (AID) '84' 11.1.1.4.5 C2
		//Proprietary information 'A5' 11.1.1.4.6 C3
		//Life Cycle Status Integer '8A' 11.1.1.4.9 M
		//Security attributes '8B', '8C' or 'AB' 11.1.1.4.7 C4
		//PIN Status Template DO 'C6' 11.1.1.4.10 M
		//Total file size '81' 11.1.1.4.2 O

	return TRUE;
}
BOOL _ExplainSelectResponse(CString csResp,CStringArray&csOutput)
{
	BOOL bRet = TRUE;
	int iTag;
	CString csTemp;
	
	iTag = _CString2Int(csResp.Mid(0,2));

	switch(iTag)
	{
	case 0x62:
		_GetTLVData(csResp,0x62,csTemp);
		bRet = _ExplainFCP(csTemp,csOutput);break;
	default:break;
	}

	return bRet;


}


BOOL __XOR(CString csInput1,CString csInput2,CString& csOutput)
{

	CString csTemp;
	int iLen1 = csInput1.GetLength();
	int iLen2 = csInput2.GetLength();
	if (iLen1!= iLen2)
		return FALSE;
	if (iLen1%2 != 0)
		return FALSE;
	csOutput.Empty();

	for (int i=0 ; i < iLen1 ; i+= 2)
	{
		csTemp.Empty();
		_Int2CString( _CString2Int(csInput1.Mid(i,2))^_CString2Int(csInput2.Mid(i,2)),csTemp,2);
		csOutput += csTemp;

	}
	return TRUE;

}

BOOL _ExplainSQN(CString csSQN,CStringArray&csOutput)
{
	if (csSQN.GetLength()!=12)
		return FALSE;

	CString csText;
	int iIndex = _CString2Int(csSQN.Right(2))&0x1F;

	_Int2CString(iIndex,csText,2);
	csOutput.Add(_T("Seq Index \\- ")+csText);

	_RightShift(csSQN,5,csText);

	csOutput.Add(_T("Seq \\- ")+csText.Left(12));

	return TRUE;

}

BOOL _ExplainAKSQN(CString csInput,CString csK,
	               CString csRand,CStringArray&csOutput)
{
	CString csRes,csCK,csIK,csAK;
	CString csSQN; 
	if (!Milenagef2345(csK,csRand,csRes,csCK,csIK,csAK))
		return FALSE;

	csOutput.Add(_T("AK \\- ")+csAK);

	if (!__XOR(csInput, csAK, csSQN))
		return FALSE;

	csOutput.Add(_T("SQN \\- ")+csSQN);

	_ExplainSQN(csSQN,csOutput);

	return TRUE;
	

}

BOOL _ExplainAKStarSQNMax(CString csInput,CString csK,
	CString csRand,CStringArray&csOutput)
{
	CString csAK;
	CString csSQN; 
	if (!Milenagef5star(csK,csRand,csAK))
		return FALSE;

	csOutput.Add(_T("AKStar \\- ")+csAK);

	if (!__XOR(csInput, csAK, csSQN))
		return FALSE;

	csOutput.Add(_T("SQNMax \\- ")+csSQN);

	_ExplainSQN(csSQN,csOutput);

	return TRUE;


}
BOOL _ExplainAuthenticate(CString csSend,CStringArray&csOutput)
{
	int iRandLen;
	int iAuthLen;
	CString csText;
	BOOL bRet = TRUE;
	int iP2 = _CString2Int(csSend.Mid(6,2));
	csText = _T("Authentication context \\- ");
	switch(iP2&7)
	{
	case 0:csOutput.Add(csText+_T("GSM context"));
	       csOutput.Add( _T("Rand \\- ")+csSend.Mid(12,_CString2Int(csSend.Mid(10,2))*2));
		   break;
	case 1:csOutput.Add(csText+_T("3G context"));
	       iRandLen = _CString2Int(csSend.Mid(10,2));
		   //此处存储Random 用于计算结果
		   theApp.csComput = csSend.Mid(12,iRandLen*2);
	       csOutput.Add( _T("Rand \\- ")+csSend.Mid(12,iRandLen*2));
		   iAuthLen = _CString2Int(csSend.Mid(12+iRandLen*2,2));
		   csOutput.Add( _T("AUTN \\- ")+csSend.Mid(14+iRandLen*2,iAuthLen*2));
		   csOutput.Add( _T("AK xor SQN \\- ")+csSend.Mid(14+iRandLen*2,12));
		   _ExplainAKSQN(csSend.Mid(14+iRandLen*2,12) ,theApp.csK ,csSend.Mid(12,iRandLen*2),csOutput);

		   csOutput.Add( _T("AMF \\- ")+csSend.Mid(26+iRandLen*2,4));
		   csOutput.Add( _T("MAC \\- ")+csSend.Mid(30+iRandLen*2,16));



		break;
	case 2:csOutput.Add(csText+_T("VGCS/VBS context"));break;
	case 4:csOutput.Add(csText+_T("GBA context"));break;
	default:bRet = FALSE;
	}


	return bRet;
}

BOOL _ExplainAuthenticateGSMResponse(CString csResp,CStringArray&csOutput)
{

	int iSresLen,iKcLen;

	if (csResp.GetLength()!= 28)
		return FALSE;

	iSresLen = _CString2Int(csResp.Mid(0,2));

	csOutput.Add(_T("Sres \\- ")+ csResp.Mid(2,iSresLen*2));

	iKcLen  = _CString2Int(csResp.Mid(iSresLen*2+2,2));

	csOutput.Add(_T("Kc \\- ")+ csResp.Mid(iSresLen*2+4,iKcLen*2));

	return TRUE;
}

BOOL _ExplainAuthenticate3GResponse(CString csResp,CStringArray&csOutput)
{
	BOOL bRet = TRUE;

	switch(_CString2Int(csResp.Mid(0,2)))
	{
	case 0xDC:
		if (csResp.GetLength()!=32)
			return FALSE;
		csOutput.Add(_T("AKStar xor SQNMax \\- ")+ csResp.Mid(4,12));

		_ExplainAKStarSQNMax(csResp.Mid(4,12),theApp.csK, theApp.csComput,csOutput);
		csOutput.Add(_T("MacS \\- ")+ csResp.Mid(16,16));
		break;

	case 0xDB:
		if ((csResp.GetLength()!=106)&&(csResp.GetLength()!=90))
			return FALSE;
		csOutput.Add(_T("Xres \\- ")+ csResp.Mid(4,16));
		csOutput.Add(_T("CK \\- ") + csResp.Mid(22,32));
		csOutput.Add(_T("IK \\- ") + csResp.Mid(56,32));
		if (csResp.GetLength() >= 106)
			csOutput.Add(_T("Kc \\- ") + csResp.Mid(90,16));
		break;
	default:bRet = FALSE;break;
	}

	return bRet;
}

BOOL _ExplainAuthenticateResponse(CString csResp,CStringArray&csOutput)
{
	BOOL bRet;
	switch(csResp.GetLength())
	{
	case 28: bRet = _ExplainAuthenticateGSMResponse(csResp,csOutput); break;
	case 32:
	case 106:
	case 90: bRet = _ExplainAuthenticate3GResponse(csResp,csOutput); break;
	default:bRet = FALSE;

	}
	return bRet;

}

void SetK(CString csKey)
{
	theApp.csK = csKey;
}
 BOOL MilenageSetCi(CString csC1,CString csC2,CString csC3,CString csC4,CString csC5)
{
	int iRet;
	BYTE ucC1[16]; 
	BYTE ucC2[16]; 
	BYTE ucC3[16]; 
	BYTE ucC4[16]; 
	BYTE ucC5[16]; 


	iRet = _CString2UcHex(csC1,ucC1);
	iRet = _CString2UcHex(csC2,ucC2);
	iRet = _CString2UcHex(csC3,ucC3);
	iRet = _CString2UcHex(csC4,ucC4);
	iRet = _CString2UcHex(csC5,ucC5);
	if (iRet != 16)
		return FALSE;


	theApp.StMilenage.mv_SetC1(ucC1);
	theApp.StMilenage.mv_SetC2(ucC2);
	theApp.StMilenage.mv_SetC3(ucC3);
	theApp.StMilenage.mv_SetC4(ucC4);
	theApp.StMilenage.mv_SetC5(ucC5);

	return TRUE;

}
 BOOL MilenageSetRi(int iR1, int iR2, int iR3, int iR4, int iR5)
{
	int iRot[5];
	iRot[0] = iR1;
	iRot[1] = iR2;
	iRot[2] = iR3;
	iRot[3] = iR4;
	iRot[4] = iR5;
	theApp.StMilenage.mv_SetRot(iRot);
	return TRUE;

}
 BOOL MilenageComputeOPc(CString& csOPc)
{	int iRet;
	BYTE pucOP_c[16];

	iRet = _CString2UcHex(csOPc,pucOP_c);
	if (iRet != 16)
		return FALSE;

	theApp.StMilenage.mv_ComputeOPc(pucOP_c);
	_UcHex2CString(pucOP_c,16,csOPc);
	return TRUE;
}
 BOOL MilenageSetOPInd(CString csOpInd)
{
	theApp.StMilenage.mv_SetOPind(csOpInd);
	return TRUE;
}
 BOOL MilenageSetOP(CString csOp)
{
	BYTE pucOP[16];
	if (_CString2UcHex(csOp,pucOP)!= 16)
		return FALSE;
	theApp.StMilenage.mv_SetOP(pucOP);
	MilenageSetOPInd("OP");
	return TRUE;
}
 BOOL MilenageSetOPc(CString csOPc)
{
	BYTE pucOPc[16];
	if (_CString2UcHex(csOPc,pucOPc)!= 16)
		return FALSE;
	theApp.StMilenage.mv_SetOP_c(pucOPc);
	MilenageSetOPInd("OP_c");
	return TRUE;
}
 BOOL Milenagef1(CString csK, CString csRand,
	                        CString csSQN, CString csAMF,
							CString& csMACA)
{
	BYTE pucK[16];
	BYTE pucRand[16];
	BYTE pucSQN[6];
	BYTE pucAMF[2];
	BYTE pucMAC_A[8];

	_CString2UcHex(csK,pucK);
	_CString2UcHex(csRand,pucRand);
	_CString2UcHex(csSQN,pucSQN);
	_CString2UcHex(csAMF,pucAMF);

	theApp.StMilenage.mv_f1( pucK, pucRand, pucSQN, pucAMF, pucMAC_A);

	_UcHex2CString(pucMAC_A,8,csMACA);

	return TRUE;
}

 BOOL Milenagef2345(CString csK,   CString csRand, 
	                           CString& csRes,CString& csCK, 
							   CString& csIK, CString& csAK)
{
	BYTE pucK[16];
	BYTE pucRand[16];

	BYTE pucRes[8];
	BYTE pucCK[16];
	BYTE pucIK[16];
	BYTE pucAK[6];

	_CString2UcHex(csK,pucK);
	_CString2UcHex(csRand,pucRand);

	theApp.StMilenage.mv_f2345( pucK, pucRand, pucRes, pucCK, pucIK, pucAK );

	_UcHex2CString(pucRes,8,csRes);
	_UcHex2CString(pucCK,16,csRes);
	_UcHex2CString(pucIK,16,csRes);
	_UcHex2CString(pucAK,6,csAK);
	return TRUE;
}

 BOOL Milenagef5star(CString csK, CString csRand,CString& csAKStar)
 {
	// unsigned char * pucK, unsigned char * pucRand, unsigned char * pucAK
	 BYTE pucK[16];
	 BYTE pucRand[16];
	 BYTE pucAK[6];

	 _CString2UcHex(csK,pucK);
	 _CString2UcHex(csRand,pucRand);

	 theApp.StMilenage.mv_f5star( pucK, pucRand, pucAK );
	 _UcHex2CString(pucAK,6,csAKStar);
	 return TRUE;
 }

 BOOL RecogniseChipInformation(CString csInput,CString  &csName,CString &csCode,CString &csATR,CString &csRemark,CString &csMF)
 {

	 int iNameLen,iInfoSum;
	 CString csTemp;

	 _DeleteEnterSpace(csInput);
	 //取出名字

	 iNameLen = csInput.Find(_T(":"));
	 csName  = csInput.Left(iNameLen);

	 if ((csName.Left(1)!=_T("["))||(csName.Right(1)!=_T("]")))
		 return FALSE;
	 csName = csName.Mid(1,csName.GetLength()-2);


	 //取出相对应的数据
	 csTemp = csInput.Right(csInput.GetLength()-iNameLen-1);
	 if (csTemp.Right(1)!=_T(";"))
		 return FALSE;

	 //取出Code相对应的相关数据
	 iInfoSum = 0;

	 iInfoSum = _GetCStringDataSum(csTemp);



	 switch(iInfoSum)
	 {
	 default:
	 case 04:  _GetCStringData(csTemp,4,csMF);
	 case 03:  _GetCStringData(csTemp,3,csRemark);
	 case 02:  _GetCStringData(csTemp,2,csATR);
	 case 01:  _GetCStringData(csTemp,1,csCode);
	 case 00: break;
	 }
	 return TRUE;
 }

 int OpenChipInformationList(CString csPath,CStdioFile* CSFFile)
 {

	 CString csData;
	 CFileStatus csSta;


	 if (!CSFFile->Open(csPath,CFile::shareDenyRead))
		 return -1;

	 if (! CSFFile->GetStatus(csPath,csSta))
	 {
		 CSFFile->Close();
		 return -2;
	 }
	 //读取文件头

	 if( (!CSFFile->ReadString(csData))||(csData!=_T("#chip list#")))
	 {
		 CSFFile->Close();
		 return -3;
	 }

	 return 0;
 }
 int Get_Chip_Information(int iChipCode,int iInfoCode,CString &csInformation)
 {
	 CString csFileData;
	 CString csName,csCode,csATR,csRemark,csMF;
	 int iRet;
	 CStdioFile CSFFile;


	 iRet = OpenChipInformationList(_T("INF\\chip.txt"),&CSFFile) ;

	 if (iRet!= 0)
		 return iRet;

	 do 
	 {
		 //读取文件内容
		 csFileData.Empty();
		 iRet = CSFFile.ReadString(csFileData);
		 if (iRet == FALSE)
			 break;
		 if (RecogniseChipInformation(csFileData, csName,csCode,csATR,csRemark,csMF))
		 {
			 if (_CString2Int(csCode) == iChipCode)
			 {
				 switch(iInfoCode)
				 {
				 case 01:csInformation = csName;break;	
				 case 02:csInformation = csCode;break;
				 case 03:csInformation = csATR;break;
				 case 04:csInformation = csRemark;break;
				 case 05:csInformation = csMF;break;
				 default:csInformation.Empty();
				 }
				 break;
			 }
		 }
	 } while (iRet);


	 CSFFile.Close();

	 return iRet;
 }




 BOOL  ExpainCardCapabilities(CString csCardCapabilities,CStringArray&csOutput)
  {
	  int iCapLen =csCardCapabilities.GetLength();
	  CString csText;
	  int iCapabilitie;

	  if (iCapLen>=2)
	  {
		  csText = _T("DF selection \\- ");
		  iCapabilitie = _CString2Int(csCardCapabilities.Mid(0,2));
		  if (iCapabilitie&0x80)
		  {
			  csOutput.Add(csText+_T("By full DF name"));
			  csText.Empty();
		  }
		  if (iCapabilitie&0x40)
		  {
			  csOutput.Add(csText+_T("By partial DF name"));
			  csText.Empty();
		  }
		  if (iCapabilitie&0x20)
		  {
			  csOutput.Add(csText+_T("By path"));
			  csText.Empty();
		  }
		  if (iCapabilitie&0x10)
		  {
			  csOutput.Add(csText+_T("By file identifier"));
			  csText.Empty();
		  }
		  if (iCapabilitie&0x8)
		  {
			  csOutput.Add(csText+_T("Implicit DF selection"));
			  csText.Empty();
		  }
		  if (iCapabilitie&0x4)
		  {
			  csOutput.Add(csText+_T("Short EF identifier supported"));
			  csText.Empty();
		  }
		  if (iCapabilitie&2)
		  {
			  csOutput.Add(csText+_T("Record number supported"));
			  csText.Empty();
		  }
		  if (iCapabilitie&1)
		  {
			  csOutput.Add(csText+_T("Record identifier supported"));
			  csText.Empty();
		  }
	  }

	  if (iCapLen>=4)
	  {
	
		  iCapabilitie = _CString2Int(csCardCapabilities.Mid(2,2));
	  
		  csText = _T("EFs of TLV structure supported \\- ");
		  if (iCapabilitie&0x80)
			  csOutput.Add(csText+_T("Supported"));
		  else
			  csOutput.Add(csText+_T("Unsupported"));
		  csText = _T("Behaviour of write functions \\- ");

		  switch(iCapabilitie&0x60)
		  {
		  case 0:  csOutput.Add(csText+_T("One-time write"));break;
		  case 0x20:  csOutput.Add(csText+_T("Proprietary"));break;
		  case 0x40:  csOutput.Add(csText+_T("Write OR"));break;
		  case 0x60:  csOutput.Add(csText+_T("Write AND"));break;
		  }

		  csText = _T("Value 'FF' for the first byte of BER-TLV tag fields \\- ");
		  if (iCapabilitie&0x80)
			  csOutput.Add(csText+_T("Valid"));
		  else
			  csOutput.Add(csText+_T("Invalid"));

		  _Int2CStringDecimal(iCapabilitie&0xF,csText);
		  csOutput.Add(_T("Data unit size in quartets \\- 2^")+csText);

	  }

	  if (iCapLen>=6)
	  {
		  iCapabilitie = _CString2Int(csCardCapabilities.Mid(4,2));

		  csText = _T("Command chaining \\- ");
		  if (iCapabilitie&0x80)
			  csOutput.Add(csText+_T("Supported"));
		  else
			  csOutput.Add(csText+_T("Unsupported"));

		  csText = _T("Extended Lc and Le fields \\- ");
		  if (iCapabilitie&0x80)
			  csOutput.Add(csText+_T("Supported"));
		  else
			  csOutput.Add(csText+_T("Unsupported"));

		  csText = _T("Logical channel number assignment \\- ");

		  if (iCapabilitie&0x10)
		  {
			  csOutput.Add(csText+_T("By the card"));
			  csText.Empty();
		  }
		  if (iCapabilitie&0x8)
		  {
			  csOutput.Add(csText+_T("By the interface device"));
			  csText.Empty();
		  }
		  if (!csText.IsEmpty())
		  {
			  csOutput.Add(csText+_T("No logical channel"));
		  }

		
		  _Int2CStringDecimal((iCapabilitie&7)+1,csText);
		  csOutput.Add(_T("Maximum number of logical channels \\- ")+csText);



	  }

	  return TRUE;

  }
 BOOL  ExpainCardServiceDatas(CString csCardServiceDatas,CStringArray&csOutput)
{
	int iCardServiceDatas;
	iCardServiceDatas = _CString2Int(csCardServiceDatas);
	CString csText; 
	csText = _T("Application Selection \\- ");
	if (iCardServiceDatas&0x80)
	{
		csOutput.Add(csText+_T("By full DF name"));
		csText.Empty();
	}
	if (iCardServiceDatas&0x40)
		csOutput.Add(csText+_T("By partial DF name"));

	csText = _T("BER-TLV Data Objects Available \\- ");
	if (iCardServiceDatas&0x20)
	{
		csOutput.Add(csText+ _T("In EF.DIR"));
		csText.Empty();
	}
	if (iCardServiceDatas&0x10)
		csOutput.Add(csText+_T("In EF.ATR"));

	if ((iCardServiceDatas&0xE)== 8)
		csOutput.Add(_T("EF.DIR and EF.ATR access services \\- By the READ BINARY command (transparent structure)"));
	if ((iCardServiceDatas&0xE)== 0)
		csOutput.Add(_T("EF.DIR and EF.ATR access services \\- By the READ RECORD (S) command (record structure)"));
	if ((iCardServiceDatas&0xE)== 2)
		csOutput.Add(_T("EF.DIR and EF.ATR access services \\- By the GET DATA command (TLV structure)"));
	if (iCardServiceDatas&0x1)
		csOutput.Add(_T("Card With MF \\- Without"));
	else
		csOutput.Add(_T("Card With MF \\- With"));

	return TRUE;
}
 BOOL  ExpainCardIssuersDatas(CString csCardIssuersDatas,CStringArray&csOutput)
  {
	  if (csCardIssuersDatas.GetLength()!= 14)
		  return FALSE;
	  CString csTemp;

	  _TranslateAscii(csCardIssuersDatas.Mid(0,4),csTemp);

	  csOutput.Add(_T("Card Manufacturer \\- ")+csCardIssuersDatas.Mid(0,4)+_T("(") +csTemp+ _T(")"));
	  csTemp.Empty();
	  if ( Get_Chip_Information(_CString2Int(csCardIssuersDatas.Mid(4,2)),1,csTemp)>0)
	  {
		  csTemp =_T("(") +csTemp+ _T(")");
	  }else
		  csTemp.Empty();

	  csOutput.Add(_T("Cipher Code \\- ")+csCardIssuersDatas.Mid(4,2)+csTemp);

	  csTemp.Format("%d.%02d",_CString2Int(csCardIssuersDatas.Mid(6,2)),_CString2Int(csCardIssuersDatas.Mid(8,2)));
	  csTemp = _T("(")+csTemp+_T(")");
	  csOutput.Add(_T("Cos Version \\- ")+csCardIssuersDatas.Mid(6,4) +csTemp);

	  csOutput.Add(_T("Operator \\- ")   +csCardIssuersDatas.Mid(10,2));
	  //此处设置运营商，留用
	  theApp.iOperater = _CString2Int(csCardIssuersDatas.Mid(10,2));
	  csOutput.Add(_T("Card Type \\- ")   +csCardIssuersDatas.Mid(12,2));
	  return TRUE;
  }
 BOOL  ExpainOptionalDataElements(CString csOptionalDataElements,CStringArray&csOutput)
  {
	  int iOffset  = 0 ;
	  int iDataLen = csOptionalDataElements.GetLength();
	  int iHeader,iEleLen;
	  CString csElement,csText;
	  do 
	  {
		  iHeader   = _CString2Int(csOptionalDataElements.Mid(iOffset,1)) ;
		  iEleLen   = _CString2Int(csOptionalDataElements.Mid(iOffset+1,1)) ;
		  iOffset  += 2;

		  if ((iOffset+iEleLen*2)> iDataLen)
			  return FALSE;

		  csElement = csOptionalDataElements.Mid(iOffset,iEleLen*2);

		  switch(iHeader)
		  {
		  case 1:csText = _T("Country code and optional national data \\- ")+csElement; 
			     csOutput.Add(csText);break;
		  case 2:csText = _T("Issuer identification number and optional issuer data \\- ")+csElement;
			     csOutput.Add(csText);break;
		  case 3:csText = _T("Card service data \\- ")+csElement;
			     csOutput.Add(csText);
				 ExpainCardServiceDatas(csElement,csOutput);
				 break;
		  case 4:csText = _T("Initial access data \\- ")+csElement;
			     csOutput.Add(csText);break;
		  case 5:csText = _T("Card issuer's data \\- ")+csElement;
			     csOutput.Add(csText);
				 ExpainCardIssuersDatas(csElement,csOutput);
				 break;
		  case 6:csText = _T("Pre-issuing data \\- ")+csElement;
			     csOutput.Add(csText);break;
		  case 7:csText = _T("Card capabilities \\- ")+csElement;
			     csOutput.Add(csText);
				 ExpainCardCapabilities(csElement,csOutput);
				 break;
		  case 8:csText = _T("Card capabilities \\- ")+csElement;
			     csOutput.Add(csText);break;
		  default:return FALSE;break;
		  }

		   iOffset  += iEleLen*2;
		 


	  } while (iDataLen>iOffset);

	  return TRUE;


  }
 BOOL  ExpainHistoryData(CString csHistoryData,CStringArray&csOutput)
 {
	 BOOL iRet = TRUE;
	 int iHisLen = csHistoryData.GetLength()/2;
	 int iOffset = 0 ;
	 CString csTemp;
	 int iCib;
	 csTemp = csHistoryData.Mid(iOffset,2);
	 iOffset+= 2;
	 iCib   = _CString2Int(csTemp);

	 if (((iCib&0xF0) == 0 )||
		 ((iCib&0xF0) == 0x10 )||
		 ((iCib&0xF0) == 0x80 ))

	 {
		  csOutput.Add(_T("Category Indicator \\- ")+ csTemp);
	 }
	 else
		 return FALSE;
	

	 switch(iCib)
	 {
	 case 0x10:
	
		 csOutput.Add(_T("DIR data reference \\- ")+ csHistoryData.Mid(2));break;
	 case 00:
		 if (!ExpainOptionalDataElements(csHistoryData.Mid(2,csHistoryData.GetLength()-6),csOutput))
			 iRet = FALSE;
		 csOutput.Add(_T("Status Indicator \\- ")+ csHistoryData.Right(6));break;
	 case 0x80:
		 
		 if (!ExpainOptionalDataElements(csHistoryData.Mid(2),csOutput))
			 iRet = FALSE;
		 break;
	 default: iRet = FALSE;break;
	 }

	 return iRet;

 }


 BOOL ExpainTDi(CString csATR,int& iOffset,int iLevel ,CStringArray&csOutput,int* iCheckSum)
 {
	 CString csText,csDesc;
	 CString csTDx = csATR.Mid(iOffset,2);
	 int iTDx      = _CString2Int(csTDx);
	 int iATRLen   = csATR.GetLength();

	 if (iLevel == 0 )
	 {
		 csOutput.Add(_T("T0 \\- ")+ csTDx);
		 *iCheckSum = FALSE;
	 }
	 else
	 {
		 csText.Format("%d",iLevel);

		 _Int2CStringDecimal(_CString2Int(csTDx.Mid(1,1)),csDesc);
		csDesc = _T("(T")+csDesc+_T(")");

		 csOutput.Add(_T("TD")+csText+_T(" \\- ")+csTDx + csDesc);
		 if ((iTDx&0xF) != 0)
			 *iCheckSum = TRUE;
	 }
	 iOffset += 2;


	 iLevel = iLevel+1;
	 csText.Format("%d",iLevel);

	 if (iTDx&0x10)
	 {
		 if (iATRLen<=iOffset)
			 return FALSE;

		 if (iLevel == 1)
			 csDesc = _T("(Encodes FI and DI)");
		 else if((iTDx&0xF) == 0xF)
		 {
			  csDesc = _T("(Encodes XI and UI)");

		 }
		 else
			 csDesc.Empty();

		 csOutput.Add(_T("TA")+csText+_T(" \\- ")+csATR.Mid(iOffset,2)+csDesc);
		 iOffset += 2;
	 }


	 if (iTDx&0x20)
	 {
		 if (iATRLen<=iOffset)
			 return FALSE;
		 if((iTDx&0xF) == 0xF)
			 csDesc = _T("(Encodes GI)");
		 else
			 csDesc.Empty();
		 csOutput.Add(_T("TB")+csText+_T(" \\- ")+csATR.Mid(iOffset,2)+csDesc);
		 iOffset += 2;
	 }

	 if (iTDx&0x40)
	 {
		 if (iATRLen<=iOffset)
			 return FALSE;
		 if (iLevel == 1)
			 csDesc = _T("(Encodes N)");
		 else
			 csDesc.Empty();
		 csOutput.Add(_T("TC")+csText+_T(" \\- ")+csATR.Mid(iOffset,2)+csDesc);
		 iOffset += 2;
	 }

	 if (iTDx&0x80)
	 {
		 if (iATRLen<=iOffset)
			 return FALSE;
		 if (ExpainTDi(csATR,iOffset,iLevel,csOutput,iCheckSum) == FALSE)
			 return FALSE;

	 }

	 return TRUE;

 }
 BOOL ExplainATR(CString csATR, CStringArray&csOutput)
 {
	 theApp.ResetParameter();

	 if ((theApp.iLevel&Def_APDUINFOMATION) == 0)
		 return TRUE;

	 int iATRLen = csATR.GetLength()/2;
	 int iOffset = 0;
	 int iCheckSum;
	 int iHisLen;
	 CString csTemp;
 	 csOutput.Add(_T("TS \\- ")+csATR.Mid(iOffset,2));
	 iOffset+= 2;
	 csTemp = csATR.Mid(iOffset,2);
	 iHisLen = _CString2Int(csTemp)&0xF;
	 if ( ExpainTDi(csATR,iOffset,0,csOutput,&iCheckSum) == FALSE)
		 return FALSE;

	 if (iATRLen< iOffset/2+iHisLen )
		 return FALSE;

	 csTemp = csATR.Mid(iOffset,iHisLen*2);

	 
	 csOutput.Add(_T("Histroy Data \\- ")+csATR.Mid(iOffset,iHisLen*2));
	 ExpainHistoryData(csATR.Mid(iOffset,iHisLen*2),csOutput);
	 iOffset+= iHisLen*2;
	 if (iATRLen < (iOffset/2+iCheckSum))
		 return FALSE;
	 if (iCheckSum)
		 csOutput.Add(_T("TCK \\- ")+csATR.Mid(iOffset,2));

	 return TRUE;
	
 }

 
 
 CString __GetCUCRFMCipher(CString csSMData)
 {
	 return csSMData.Mid(20,20)+csSMData.Mid(48);
 }
 CString __GetTAR(CString csSMData)
 {
	 return csSMData.Mid(14,6);
 }
 int __GetSPI(CString csSMData)
 {
	 return _CString2Int(csSMData.Mid(6,4));
 }
 int __GetKIc(CString csSMData)
 {
	 return _CString2Int(csSMData.Mid(10,2));
 }
 int __GetKID(CString csSMData)
 {
	 return _CString2Int(csSMData.Mid(12,2));
 }
 CString __GetRandom(CString csSMData)
 {
	 return csSMData.Mid(40,8);
 }

 CString __GenerateSessionKey(CString csRandom, CString csKey,CString csICCID)
 {
	 CString csDerivedKeyR , csDerivedKeyL, csTemp;
	 CString csSessionKeyR, csSessionKeyL;

	 _Triple_Des_Encrypt(csKey,csICCID,csDerivedKeyR,ECB);
	 __XOR(csICCID,_T("FFFFFFFFFFFFFFFF"),csTemp);
	  _Triple_Des_Encrypt(csKey,csTemp,csDerivedKeyL,ECB);

	  csRandom = csRandom+_T("20202020");
	  _Triple_Des_Encrypt(csDerivedKeyR+ csDerivedKeyL,csRandom,csSessionKeyR,ECB);
	 
	  __XOR(csRandom,_T("FFFFFFFFFFFFFFFF"),csTemp);
	  _Triple_Des_Encrypt(csDerivedKeyR+ csDerivedKeyL,csTemp,csSessionKeyL,ECB);

	  return csSessionKeyR.Mid(0,16)+ csSessionKeyL.Mid(0,16);

 }


 BOOL __ExpainCipherUserData(CStringArray& csOutput)
 {
	 CString csIEIA,csSM;
	 CString csSMDataAll,csSMCur;
	 int iCount = GetMessageArrayCount();
	 CString csUDH;
	 int j,i;

	 bool bDeciper = false;
	 csSMDataAll.Empty();




	 for ( i = 0 ; i <iCount; i++ )
	 {

		 for ( j = 0 ; j < iCount;j++)
		 {
			 if (!__GetUserDataHead(GetMessageArray(j),0x0,csIEIA))
				 return FALSE;

			 if (!csIEIA.IsEmpty())
			 {
				 if  (_CString2Int(csIEIA.Mid(2,2))!= iCount )
					 return FALSE;

				 if (_CString2Int(csIEIA.Mid(4,2))== i+1)
				 {
					 csSMCur = GetMessageArray(j);
					 csUDH   = csSMCur.Mid(2,_CString2Int(csSMCur.Mid(0,2))*2);
					 csSMCur = csSMCur.Mid(csUDH.GetLength()+2);
					 csSMDataAll+= csSMCur;
				 }
			 }
			 else
				 csSMDataAll =  GetMessageArray(j);
		 }

	 }




	 theApp.csMsgArray.RemoveAll();
	 csSMDataAll.MakeUpper();

	 if(theApp.iOperater == 0x55)
	 {
		 if (__GetTAR(csSMDataAll) == _T("B0001F"))
		 {
			 CString csKey;
			 CString csRandom = __GetRandom(csSMDataAll); 
			 csSM.Empty();
			 csKey   = theApp.csCURFMKey.GetAt((_CString2Int(csRandom.Right(2))&7)%5);

			 _Triple_Des_Decrypt(__GenerateSessionKey(csRandom,csKey,theApp.csDeriveData),__GetCUCRFMCipher(csSMDataAll),csSM);

			 csOutput.Add(_T("解密 数据 \\- ")+csSM);
			 csOutput.Add(_T("解密 Counter \\- ")+csSM.Mid(0,10));
			 csOutput.Add(_T("解密 PCNTR \\- ")+csSM.Mid(10,2));
			 csOutput.Add(_T("解密 MAC \\- ")+csSM.Mid(12,8));
			 csOutput.Add(_T("解密 Secured Data \\- ")+csSM.Mid(20));

			   return TRUE;
		 }

		 
	 }
	 else if(theApp.iOperater == 0x43)
	 {

		 if (__GetTAR(csSMDataAll) == _T("B000F2"))
		 {

			 _Triple_Des_Decrypt(theApp.csK1,csSMDataAll.Mid(20),csSM);

			 csOutput.Add(_T("解密 数据 \\- ")+csSM);
			 csOutput.Add(_T("解密 Counter \\- ")+csSM.Mid(0,10));
			 csOutput.Add(_T("解密 PCNTR \\- ")+csSM.Mid(10,2));
			 csOutput.Add(_T("解密 MAC \\- ")+csSM.Mid(12,8));
			 csOutput.Add(_T("解密 Secured Data \\- ")+csSM.Mid(20));
			 csOutput.Add(_T("写卡 Random \\- ")+csSM.Mid(22,16));

			 csSM = csSM.Mid(40,_CString2Int(csSM.Mid(38,2))*2);
			 
		 }

		 if (__GetTAR(csSMDataAll) == _T("B000B0"))
		 {
			 _Triple_Des_Decrypt(theApp.csKIc,csSMDataAll.Mid(20),csSM);

			 csOutput.Add(_T("解密 数据 \\- ")+csSM);
			 csOutput.Add(_T("解密 Counter \\- ")+csSM.Mid(0,10));
			 csOutput.Add(_T("解密 PCNTR \\- ")+csSM.Mid(10,2));
			 csOutput.Add(_T("解密 MAC \\- ")+csSM.Mid(12,8));
			 csOutput.Add(_T("解密 Secured Data \\- ")+csSM.Mid(20));
			
			 csOutput.Add(_T("解密 Protocol Version \\- ")+csSM.Mid(20,2));
			 csOutput.Add(_T("解密 命令类型 \\- ")+csSM.Mid(22,2));

			 csSM = csSM.Mid(24);

		 }


		 if ( _GetTLVData(csSM,1,csSMCur))
			 csOutput.Add(_T("写卡 ICCID \\- ")+csSMCur);

		 if ( _GetTLVData(csSM,2,csSMCur))
			 csOutput.Add(_T("写卡 IMSI \\- ")+csSMCur);

		 if ( _GetTLVData(csSM,3,csSMCur))
			 csOutput.Add(_T("写卡 SMSP \\- ")+csSMCur);

		 if ( _GetTLVData(csSM,4,csSMCur))
			 csOutput.Add(_T("写卡 PIN1 \\- ")+csSMCur);

		 if ( _GetTLVData(csSM,5,csSMCur))
			 csOutput.Add(_T("写卡 PIN2 \\- ")+csSMCur);

		 if ( _GetTLVData(csSM,6,csSMCur))
			 csOutput.Add(_T("写卡 PUK1 \\- ")+csSMCur);

		 if ( _GetTLVData(csSM,7,csSMCur))
			 csOutput.Add(_T("写卡 PUK2 \\- ")+csSMCur);

		 if ( _GetTLVData(csSM,8,csSMCur))
			 csOutput.Add(_T("写卡 Ki \\- ")+csSMCur);

		 if ( _GetTLVData(csSM,9,csSMCur))
			 csOutput.Add(_T("写卡 索引随机数 \\- ")+csSMCur);

		 if ( _GetTLVData(csSM,10,csSMCur))
			 csOutput.Add(_T("写卡 伪Ki \\- ")+csSMCur);

		 if ( _GetTLVData(csSM,11,csSMCur))
			 csOutput.Add(_T("写卡 K \\- ")+csSMCur);

		 if ( _GetTLVData(csSM,12,csSMCur))
			 csOutput.Add(_T("写卡 OPc \\- ")+csSMCur);

		  return TRUE;

	 }

	 else if(theApp.iOperater == 84)
	 {


		 if (__GetTAR(csSMDataAll) == _T("CA0101"))
		 {

			 _Triple_Des_Decrypt(_T("EA1E7659805B7B7D6843E85F790EDC98"),csSMDataAll.Mid(20),csSM);

			 csOutput.Add(_T("解密 数据 \\- ")+csSM);
			 csOutput.Add(_T("解密 Counter \\- ")+csSM.Mid(0,10));
			 csOutput.Add(_T("解密 PCNTR \\- ")+csSM.Mid(10,2));
			 csOutput.Add(_T("解密 MAC \\- ")+csSM.Mid(12,16));
			 csOutput.Add(_T("解密 命令数据 \\- ")+csSM.Mid(28));	
			 return TRUE;
		 }

	 }

	return _ExplainCommandSecuredPacket8bitNote1(csSM,csOutput);

	
 }


 BOOL __ExpainSigleCipherUserData( CString csInput,CStringArray& csOutput )
 {
	 return TRUE;
 }

 BOOL __ExplainID2EncryptDecrypt(CString csData,CStringArray& csOutput)
  {
	  
	  int iOff = 0 ;
	  CString csBlock =  csData.Mid(iOff,2);

	  csOutput.Add(_T("Block No \\- ")+ csBlock);

	  iOff +=2;

	  if (_CString2Int(csBlock) == 0 )
	  {
		  if (csData.GetLength()<14)
			  return FALSE;

		  switch(_CString2Int(csData.Mid(iOff,2)))
		  {
		  case 0: csOutput.Add(_T("Cascade \\- 非最后一个数据块"));break;
		  case 1: csOutput.Add(_T("Cascade \\- 最后一个数据块"));break;
		  default: return FALSE;
		  }

		  iOff +=2;

		  switch(_CString2Int(csData.Mid(iOff,2)))
		  {
		  case 0x51: csOutput.Add(_T("Mode \\- 加密模式"));break;
		  case 0x52: csOutput.Add(_T("Mode \\- 解密模式"));break;
		  default: return FALSE;
		  }

		  iOff +=2;

		  switch(_CString2Int(csData.Mid(iOff,2)))
		  {
		  case 0x00: csOutput.Add(_T("Algorithm \\- 3DES CBC PKCS5 Padding"));break;
		  case 0x02: csOutput.Add(_T("Algorithm \\- 3DES ECB PKCS5 Padding"));break;
		  default: return FALSE;
		  }

		  iOff +=2;
		  csOutput.Add(_T("Key Index \\- ")+csData.Mid(iOff,2));

		  iOff +=2;
		  csOutput.Add(_T("Length \\- ")+csData.Mid(iOff,4));

		  iOff +=4;
	  }
 

	  csOutput.Add(_T("Data \\- ")+csData.Mid(iOff));

	  return TRUE;
  }


 BOOL __ExplainID2SendPatcket(CString csData,CStringArray& csOutput)
 {
	 int iMode = _CString2Int(csData.Mid(0,2));
	 BOOL bRet = TRUE;
	 csOutput.Add(_T("ID2 指令 \\- 发送数据"));
	 switch(iMode)
	 {
	 case 0x51: 
		 csOutput.Add(_T("ID2 指令 \\- 3DES加解密运算"));
		 bRet = __ExplainID2EncryptDecrypt(csData.Mid(2,csData.GetLength()-6),csOutput);break;
	 case 0x52: csOutput.Add(_T("ID2 指令 \\- 取厂商标识ID值"));break;
	 case 0x53: csOutput.Add(_T("ID2 指令 \\- 取随机数"));break;
	 default:   bRet = FALSE;
	 }

	 if (bRet)
	 {
		 csOutput.Add(_T("CheckSum \\- ")+ csData.Right(4));
	 }

	 return bRet;

 }


  BOOL __ExplainID2ResponsePatcket(CString csData,CStringArray& csOutput)
  {
	  if (csData.GetLength()<2)
		  return FALSE;
	  csOutput.Add(_T("ID2 指令 \\- 获取数据"));
	  csOutput.Add(_T("Response \\- ")+ csData.Left(csData.GetLength()-4));
	  csOutput.Add(_T("CheckSum \\- ")+ csData.Right(4));
	  return TRUE;
  }

  BOOL _ExplainID2GetID(CString csResp,CStringArray& csOutput)
  {

	  if (csResp.GetLength()<6)
	  {
		  return FALSE;
	  }

	  csOutput.Add(_T("ID2 指令 \\- Get ID"));
	  csOutput.Add(_T("厂商标识 \\- ") + csResp.Mid(0,4));
	  csOutput.Add(_T("Length \\- ")   + csResp.Mid(4,2));
	  csOutput.Add(_T("ID \\- ")   +  csResp.Mid(6));
	  return TRUE;
  }

  BOOL _ExplainID2GetVendorInfo(CString csResp,CStringArray& csOutput)
  {

	  if (csResp.GetLength()!=40)
	  {
		  return FALSE;
	  }

	  csOutput.Add(_T("ID2 指令 \\- Get Vendor Information"));
	  csOutput.Add(_T("厂商标示 \\- ") + csResp.Mid(0,4));
	  csOutput.Add(_T("版本信息 \\- ") + csResp.Mid(4,16));
	  csOutput.Add(_T("配置选项 \\- ")   + csResp.Mid(20,8));
	  csOutput.Add(_T("可用空间 \\- ")   +  csResp.Mid(28,4));
	  csOutput.Add(_T("扩展为   \\- ")   +  csResp.Mid(32));
	  return TRUE;
  }


  BOOL _ExplainID2SymmetricCrypt(CString csSend,CString csResp,CStringArray& csOutput)
  {
	  CString csText;
	  int iOff = 10;
	  int iP1 = _CString2Int(csSend.Mid(4,2));
	  int iP2 = _CString2Int(csSend.Mid(6,2));
	  int iAlgo = 0;
	  csOutput.Add(_T("ID2 指令 \\- Symmetric Crypt"));

	  csOutput.Add(_T("P1(块号) \\- ")+csSend.Mid(4,2));

	  if (iP2 == 0)
		  csOutput.Add(_T("P2 \\- 00 (最后一条处理数据)"));
	  else if (iP2 == 1)
		  csOutput.Add(_T("P2 \\- 01(级联待处理数据)"));
	  else 
	  {
		  csOutput.Add(_T("P2 \\- 错误"));
		  return FALSE;
	  }

	  if (iP1 == 0)
	  {

		  switch(_CString2Int(csSend.Mid(iOff,2)))
		  {
		  case 0x51: csText = _T("加密操作");break;
		  case 0x52: csText = _T("解密操作");break;
		  case 0x53: csText = _T("计算MAC");break;
		  case 0x54: csText = _T("验证MAC");break;
		  default:return FALSE;
		  }
		  csOutput.Add(_T("模式 \\- ")+csText);
		  iOff += 2;
		  iAlgo = _CString2Int(csSend.Mid(iOff,2));
		  switch(iAlgo)
		  {
		  case 0x00: csText = _T("DES_CBC_NOPADDING");break;
		  case 0x01: csText = _T("DES_ECB_NOPADDING");break;
		  case 0x02: csText = _T("AES_CBC_NOPADDING");break;
		  case 0x03: csText = _T("AES_ECB_NOPADDING");break;
		  case 0x04: csText = _T("DES_CBC_ISO9797_M1");break;
		  case 0x05: csText = _T("DES_CBC_ISO9797_M2");break;
		  case 0x06: csText = _T("AES_CBC_ISO9797_M1");break;
		  case 0x07: csText = _T("AES_ECB_ISO9797_M2");break;

		  case 0x10: csText = _T("SM4_CBC_NOPADDING");break;
		  case 0x11: csText = _T("SM4_ECB_NOPADDING");break;
		  case 0x12: csText = _T("SM7_CBC_NOPADDING");break;
		  case 0x13: csText = _T("SM7_ECB_NOPADDING");break;
		  case 0x14: csText = _T("SM4_CBC_ISO9797_M1");break;
		  case 0x15: csText = _T("SM4_CBC_ISO9797_M2");break;
		  case 0x16: csText = _T("SM7_CBC_ISO9797_M1");break;
		  case 0x17: csText = _T("SM7_ECB_ISO9797_M2");break;
		  default:return FALSE;
		  }
		  csOutput.Add(_T("模式 \\- ")+csText);
		  iOff += 2;

		  csOutput.Add(_T("KID \\- ")+csSend.Mid(iOff,2));
		  iOff += 2;

		  csOutput.Add(_T("Length \\- ")+csSend.Mid(iOff,4));
		  iOff += 4;

	  }


	  csOutput.Add(_T("Data \\- ")+csSend.Mid(iOff));


	  return TRUE;

  }


  BOOL _ExplainCDMASMSTPDU(CString csInput, CStringArray&csOutput)
  {
	  BOOL bRet = TRUE;
	  CString csText;
	  CString csPreText;
	  csPreText = _T("CDMA SMS TPDU \\- ");
	  csOutput.Add(csPreText+csInput);




	  switch(_CString2Int(csInput.Mid(0,2))&0x3)
	  {
	  case 0:bRet =_ExplainSMSPointtoPoint(csInput.Mid(2),csOutput);break;
	  //case 1:bRet =_ExplainSMSBroadcast(csInput,csOutput);break;
	  //case 2:bRet =_ExplainSMSAcknowledge(csInput,csOutput);break;
	  }

	  return bRet;

  }
  BOOL _ExplainUserData(CString csInput, CStringArray&csOutput)
  {
	  csOutput.Add( _T("User Data \\- ")+csInput);


	  CString csSubParam;
	  CString csResult;



	  int iOffset = 0;
	  //if ( ! _GetTLVData(csInput,0x1,csSubParam))
		 // return FALSE;
	
	  _RightShift(csInput,3,csResult);

	   csSubParam = csResult.Mid(iOffset,2);
	   csOutput.Add( _T("MSG ENCODING \\- ")+csSubParam);
	   iOffset += 2;
	   
	   if (_CString2Int( csSubParam) == 1)
	   {
		   csSubParam = csResult.Mid(iOffset,2);
		   csOutput.Add( _T("MESSAGE TYPE \\- ")+csSubParam);
		   iOffset += 2;
	   }

	   csSubParam = csResult.Mid(iOffset,2);
	   csOutput.Add( _T("NUM FIELDS \\- ")+csSubParam);
	   iOffset += 2;


	   if (csResult.GetLength() < 2*_CString2Int(csSubParam)+iOffset )
	   {
		   return FALSE;
	   }

	   csSubParam = csResult.Mid(iOffset,2*_CString2Int(csSubParam));
	   csOutput.Add( _T("CHARi \\- ")+csSubParam);

	   _ExplainUserData(csSubParam,0x04,01,csOutput);

	  return TRUE;
  }
  BOOL _ExplainBearData(CString csInput, CStringArray&csOutput)
  {

	  csOutput.Add( _T("Bearer Data \\- ")+csInput);

	  BOOL bRet = TRUE;
	  int iOffset = 0;
	  CString csParam;
	  int iTag;

	  do 
	  {

		  iTag    =  _CString2Int(csInput.Mid(iOffset,2));
		  _GetTLVData(csInput,iTag,csParam);

		  switch(iTag)
		  {
		  case 00: bRet &= _ExplainTemp(_T("Message Identifier"),csParam,csOutput) ;break;
		  case 01: bRet &= _ExplainUserData(csParam,csOutput) ;break;
		  case 02: bRet &= _ExplainTemp(_T("User Response Code"),csParam,csOutput) ;break;
		  case 03: bRet &= _ExplainTemp(_T("Message Center Time Stamp"),csParam,csOutput) ;break;
		  case 04: bRet &= _ExplainTemp(_T("Validity Period – Absolute"),csParam,csOutput) ;break;
		  case 05: bRet &= _ExplainTemp(_T("Validity Period – Relative"),csParam,csOutput) ;break;
		  case 06: bRet &= _ExplainTemp(_T("Deferred Delivery Time - Absolute"),csParam,csOutput) ;break;
		  case 07: bRet &= _ExplainTemp(_T("Deferred Delivery Time - Relative"),csParam,csOutput) ;break;
		  case 8: bRet &= _ExplainTemp(_T("Priority Indicator"),csParam,csOutput) ;break;
		  case 9: bRet &= _ExplainTemp(_T("Privacy Indicator"),csParam,csOutput) ;break;
		  case 10: bRet &= _ExplainTemp(_T("Reply Option"),csParam,csOutput) ;break;
		  case 11: bRet &= _ExplainTemp(_T("Number of Messages"),csParam,csOutput) ;break;
		  case 12: bRet &= _ExplainTemp(_T("Alert on Message Delivery"),csParam,csOutput) ;break;
		  case 13: bRet &= _ExplainTemp(_T("Language Indicator"),csParam,csOutput) ;break;
		  case 14: bRet &= _ExplainTemp(_T("Call-Back Number"),csParam,csOutput) ;break;
		  case 15: bRet &= _ExplainTemp(_T("Message Display Mode"),csParam,csOutput) ;break;
		  case 16: bRet &= _ExplainTemp(_T("Multiple Encoding User Data"),csParam,csOutput) ;break;
		  }

		  iOffset += csParam.GetLength()+4;
	  } while (iOffset <csInput.GetLength());


	  return bRet;


  }


  BOOL _ExplainSMSPointtoPoint(CString csInput, CStringArray&csOutput)
	{
		 BOOL bRet = TRUE;
		int iOffset = 0;
		csOutput.Add( _T("Message Type \\- 00"));
		CString csParam;
		int iTag;


		do 
		{

			iTag    =  _CString2Int(csInput.Mid(iOffset,2));
			_GetTLVData(csInput,iTag,csParam);

			switch(iTag)
			{
			case 00: bRet &= _ExplainTemp(_T("Teleservice Identifier"),csParam,csOutput) ;break;
			case 01: bRet &= _ExplainTemp(_T("Service Category"),csParam,csOutput) ;break;
			case 02: bRet &= _ExplainTemp(_T("Originating Address"),csParam,csOutput) ;break;
			case 03: bRet &= _ExplainTemp(_T("Originating Subaddress"),csParam,csOutput) ;break;
			case 04: bRet &= _ExplainTemp(_T("Destination Address"),csParam,csOutput) ;break;
			case 05: bRet &= _ExplainTemp(_T("Destination Subaddress"),csParam,csOutput) ;break;
			case 06: bRet &= _ExplainTemp(_T("Bearer Reply Option"),csParam,csOutput) ;break;
			case 07: bRet &= _ExplainTemp(_T("Cause Codes"),csParam,csOutput) ;break;
			case 0x8: bRet &= _ExplainBearData(csParam,csOutput) ;break;
			}

			iOffset += csParam.GetLength()+4;

		} while (iOffset <csInput.GetLength());

		
		return bRet ;
	
	}



