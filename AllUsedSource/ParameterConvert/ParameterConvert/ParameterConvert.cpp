// ParameterConvert.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"

#include "ParameterConvert.h"
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

// CParameterConvertApp

BEGIN_MESSAGE_MAP(CParameterConvertApp, CWinApp)
END_MESSAGE_MAP()


// CParameterConvertApp 构造

CParameterConvertApp::CParameterConvertApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CParameterConvertApp 对象

CParameterConvertApp theApp;


// CParameterConvertApp 初始化

BOOL CParameterConvertApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}



BOOL _TransationDiallingNumber(CString csInput, CString& csOutput)
{
	csOutput.Empty();
	if (csInput.GetLength()%2)
	{
		return FALSE;
	}
	_ExchangeAt(csInput);

	_TranslateBCD(csInput,csOutput);

	return TRUE;
}

BOOL _ConvertDiallingNumber(CString csInput, CString& csOutput)
{
	csOutput.Empty();
	if (!_ConvertBCD(csInput,csOutput))
	{
		csOutput.Empty();
		return FALSE;
	}

	if(csOutput.GetLength()%2)
		csOutput = csOutput+_T("F");

	_ExchangeAt(csOutput);

	return TRUE;

}

BOOL _TranslateTONNPI(CString csInput,CString&csOutput)
{
	csOutput.Empty();
	if (csInput.GetLength()!= 2)
		return FALSE;

	if (_CString2Int(csInput) == 0x91)
		csOutput = "+";
	else 
		csOutput.Empty();

	return TRUE;
}

BOOL _ConvertTONNPI(CString csInput,CString&csOutput)
{
	csOutput.Empty();
	if (csInput.IsEmpty())
		csOutput = "81";
	else if (csInput.GetAt(0) == '+')
		csOutput = "91";
	else return FALSE;
	return TRUE;
}


//输入  0891683110102105F0   输出+8613010112500 
//Length of BCD number/SSC contents
//TON and NPI
//Dialling Number/SSC String
BOOL _TranslateSubNumber(CString csInput,CString& csOutput)
{
	CString csTemp;
	int iLen      = _CString2Int (csInput.Left(02));
	int iInputLen = csInput.GetLength();
	csOutput.Empty();
	if (iLen > (iInputLen-2) )
		return FALSE;

	if (_TranslateTONNPI(csInput.Mid(2,2),csTemp))
		csOutput += csTemp;
	else
		return FALSE;

	if (_TransationDiallingNumber(csInput.Mid(4),csTemp))

		csOutput += csTemp;
	else
		return FALSE;

	return TRUE;
}

//+8613010112500 = 0891683110102105F0
BOOL _ConvertSubNumber(CString csInput,CString&csOutput)
{
	CString csTONNPI,csTemp;
	csOutput.Empty();
	int iOffset = 0;
	if (csInput.IsEmpty())
		return FALSE;

	if (csInput.GetAt(0) == '+')
	{
		csTONNPI = csInput.Left(1);
		iOffset  = 1; 
	}
	else
		csTONNPI.Empty();

	if (_ConvertTONNPI(csTONNPI,csTemp))
		csOutput = csTemp;
	else
		return FALSE;


	if (_ConvertDiallingNumber(csInput.Mid(iOffset),csTemp))
		csOutput += csTemp;
	else
		return FALSE;

	csTemp.Format("%02X", csOutput.GetLength()/2);

	csOutput = csTemp+csOutput;



	return TRUE;
}

BOOL _TranslateAddress(CString csInput,CString& csOutput)
{
	int iNibbleNum;
	CString csTemp;
	csOutput.Empty();
	iNibbleNum = _CString2Int(csInput.Mid(0,2));

	if (_TranslateTONNPI(csInput.Mid(2,2),csTemp))
		csOutput += csTemp;
	else
		return FALSE;

	if (_TransationDiallingNumber(csInput.Mid(4),csTemp))
		csOutput += csTemp.Left(iNibbleNum);
	else
		return FALSE;


	return TRUE;
}

BOOL _ConvertAddress(CString csInput,CString& csOutput)
{
	int iNibbleNum;
	csOutput.Empty();
	iNibbleNum = csInput.GetLength();

	CString csTONNPI,csTemp;
	int iOffset = 0;
	if (csInput.GetAt(0) == '+')
	{
		csTONNPI = csInput.Left(1);
		iOffset  = 1; 
	}
	else
		csTONNPI.Empty();

	if (_ConvertTONNPI(csTONNPI,csTemp))
		csOutput = csTemp;
	else
		return FALSE;


	if (_ConvertDiallingNumber(csInput.Mid(iOffset),csTemp))
		csOutput += csTemp;
	else
		return FALSE;

	csTemp.Format("%02X", iNibbleNum-iOffset);

	csOutput = csTemp+csOutput;

	return TRUE;

}


void _ConvertADN12(CString csData,CString& csOutput)
{
	csOutput.Empty();
	if (!_ConvertSubNumber(csData,csOutput))
		csOutput.Empty();
	csOutput +=  _T("FFFFFFFFFFFFFFFFFFFFFFFF");
	csOutput= csOutput.Left(24);
}



void _Genrate80ADN(CString csAlpha,int iAlphaLen,CString csNumber,CString& csOutput)
{
	CString csADN,csPadding;
	csOutput.Empty();
	_RepeatCString(_T("FF"),iAlphaLen,csPadding);
	if (!csAlpha.IsEmpty())
	{
		_ConvertUcs2(csAlpha,csAlpha);
		csAlpha   = _T("80")+csAlpha+csPadding;
		csAlpha   = csAlpha.Left(iAlphaLen*2);
	}
	else
		csAlpha  = csPadding;
	if (csNumber.IsEmpty())
		 _RepeatCString(_T("FF"),12,csNumber);
	else
		 _ConvertADN12(csNumber,csNumber);

	csOutput    = csAlpha+csNumber +_T("FFFF");

}

void _ConvertSMSP(CString csAlpID,CString csTPDesAdd,CString csTSSCA,CString csTPPId,CString csTPDCS,CString csTPVP,CString &csSMSP)
{

	int iParaInd;
	CString csParaInd,csTemp;
	iParaInd = 0xFF;
	csSMSP.Empty();

	if (_IsValid(csTPDesAdd))
		iParaInd = iParaInd&0xFE;

	if (_IsValid(csTSSCA))
		iParaInd = iParaInd&0xFD;

	if (_IsValid(csTPPId))
		iParaInd = iParaInd&0xFB;

	if (_IsValid(csTPDCS))
		iParaInd = iParaInd&0xF7;

	if (_IsValid(csTPVP))
		iParaInd = iParaInd&0xEF;

	csParaInd.Format(_T("%02X"),iParaInd);

	csSMSP = csAlpID+csParaInd;

	csTemp.Empty();
	_ConvertADN12(csTPDesAdd,csTemp);

	csSMSP += csTemp;

	csTemp.Empty();
	_ConvertADN12(csTSSCA,csTemp);

	csSMSP += csTemp;

	csSMSP +=(csTPPId+csTPDCS+csTPVP);
}

void _ConvertSMSP28(CString csData,CString &csSMSP)
{
	_ConvertSMSP(_T("FFFFFFFFFFFFFFFFFFFFFFFF"),_T(""),csData,_T("FF"),_T("FF"),_T("FF"),csSMSP);
}
void _ConvertSMSP29(CString csData,CString &csSMSP)
{
	_ConvertSMSP(_T("FFFFFFFFFFFFFFFFFFFFFFFFFF"),_T(""),csData,_T("FF"),_T("FF"),_T("FF"),csSMSP);
}

/*

int _ShiftNumber_P(int iNumber,int idigit)
{

	int *iNum;

	iNum = new int[idigit];

	for (int i = 0 ; i < idigit ; i++)
	{
		if ((iNumber %10) == 9)
			iNum[idigit-1-i] = 0;
		else
			iNum[idigit-1-i] = (iNumber %10)+1;

		iNumber = iNumber/10;
	}

	iNumber = 0;

	for (int i = 0 ; i<idigit ; i++)
		iNumber = iNumber*10+ iNum[i];

	delete iNum;

	return iNumber;

}

int TransMCC(BYTE *MCC,BYTE *DD)
{

	int iMCC;

	for (int i=0;i<3;i++)
	{
		if (MCC[i]==0)
			MCC[i] = 0xA;
	}

	iMCC = MCC[0]*100+ MCC[1]*10+MCC[2] - 111;

	DD[2]= iMCC/0x1000;
	DD[3]= (iMCC%0x1000) /0x100;
	DD[0]= (iMCC%0x100)/0x10;
	DD[1]= iMCC%0x10;
	return 0;

}

int TransMNC(BYTE *MNC,BYTE *CC)
{

	int iMNC;

	for (int i=0;i<2;i++)
	{
		if (MNC[i]==0)
			MNC[i] = 0xA;
	}

	iMNC = MNC[0]*10+MNC[1] - 11;

	CC[0]= (iMNC/0x10)%0x10;
	CC[1]= iMNC%0x10;
	return 0;

}

int TranMIN2(BYTE *MIN,BYTE *BB)
{
	int iMIN4_6,iMIN7,iMIN8_10;

	for (int i=0;i<10;i++)
	{
		if (MIN[i]==0)
			MIN[i] = 0xA;
	}
	long lBB;


	iMIN4_6  = MIN[3]*100+ MIN[4]*10+ MIN[5]-111;
	iMIN7    = MIN[6];
	iMIN8_10 = MIN[7]*100+ MIN[8]*10+ MIN[9]-111;

	lBB      = iMIN4_6*0x4000+iMIN7*0x400+iMIN8_10;

	BB[0]    =(BYTE)(lBB/0x10)%0x10;
	BB[1]    =(BYTE)lBB%0x10;

	BB[2]    =(BYTE)(lBB/0x1000)%0x10;
	BB[3]    =(BYTE)(lBB/0x100)%0x10;

	BB[4]    =(BYTE)(lBB/0x100000)%0x10;
	BB[5]    =(BYTE)(lBB/0x10000)%0x10;

	return 0;



}

int Imsi2Imsim(BYTE ucImsi[9],BYTE *ucImsim)
{

	int iRet;
	BYTE *AA = new BYTE [4];
	BYTE *BB = new BYTE [6];
	BYTE *CC = new BYTE [2];
	BYTE *DD = new BYTE [4];


	iRet = TransMCC(ucImsi,DD);

	iRet = TransMNC(ucImsi+3,CC);

	iRet = TransMCC(ucImsi+5,AA);

	iRet = TranMIN2(ucImsi+5,BB);

	ucImsim[0]= 0;
	ucImsim[1]= 0;
	memcpy(ucImsim+2,AA,4);
	memcpy(ucImsim+6,BB,6);
	memcpy(ucImsim+12,CC,2);
	ucImsim[14]= 0x8;
	ucImsim[15]= 0;
	memcpy(ucImsim+16,DD,4);

	delete AA;
	delete DD;
	delete CC;
	delete DD;
	return 20;



}

BOOL Imsi2Imsim(CString csIMSI,CString&csIMSI_M)
{
	CString csTemp;
	int iSouLen = csIMSI.GetLength();
	int iImsimLen;
	unsigned char *ucDes = new unsigned char [iSouLen];
	unsigned char *ucImsim = new unsigned char [20];

	iSouLen = CString2UcHex(csIMSI,ucDes);

	iImsimLen = Imsi2Imsim(ucDes,ucImsim);

	if (iImsimLen != 10)
		return FALSE;

	for (int i = 0; i< iImsimLen; i++)
	{
		csTemp.Format(_T("%X"), ucImsim[i]);
		csIMSI_M+=csTemp;
	}

	return TRUE;
}

int _TransationMCC_P(BYTE ucMCC_P[2])
{
	int iMCC;

	iMCC =  ucMCC_P [0]+ (ucMCC_P [1]   &0x3) *0x100;

	iMCC = _ShiftNumber_P(iMCC,3);

	return iMCC;

}

int _TransationM_11_12(BYTE ucM_11_12_P)
{
	int iM_11_12;
	iM_11_12 = (ucM_11_12_P&0x7F);

	iM_11_12 = _ShiftNumber_P(iM_11_12,2);

	return iM_11_12;
}

int _TransationM_S1(BYTE ucM_S1_P[3])
{
	int iM_S1;
	int iM_S1_1,iM_S1_2,iM_S1_3;

	iM_S1 = ucM_S1_P[0] + ucM_S1_P[1] *0x100 + ucM_S1_P[2] *0x10000;

	iM_S1_1 = _ShiftNumber_P(iM_S1/0x4000,3);
	iM_S1_2 = (iM_S1%0x4000)/0x400;
	iM_S1_3 = _ShiftNumber_P( iM_S1%0x400 ,3);


	return iM_S1_1*10000+iM_S1_2*1000+iM_S1_3;

}


int Imsim2Imsi(BYTE ucImsim[10],BYTE *ucImsi)
{

	int iMCC_P1,iM_11_12,iMCC_P2,iM_S1;


	iMCC_P1  = _TransationMCC_P(ucImsim+8)   ;// 3 
	iM_11_12 = _TransationM_11_12(ucImsim[5]);// 2
	iMCC_P2  = _TransationMCC_P(ucImsim+1);   // 3
	iM_S1    = _TransationM_S1(ucImsim+3);    // 7



}


*/



void GenerateExpandedFormatSecurityDescriptor(CString* csData,CString* csDescriptor)
{
	if(csData->IsEmpty())
	{
		*csData       = _T("NEVER");
		*csDescriptor = _T("未定义");
	}
	else
		*csDescriptor = *csData;

}

CString TransationControlReferenceTemplateData(CString csData)
{

	CString csUQB,csKey;
	CString csResult;
	
	 _GetTLVData(csData,0x83,csKey);

	 _GetTLVData(csData,0x95,csUQB);

	if((_CString2Int(csUQB) == 0x08)&&(!csKey.IsEmpty()))
	{
		csKey.MakeUpper();
		csResult = _T("PIN ")+csKey;
	}
	else
	{
		csResult = _T("超出理解范围");
	}

	return csResult;
}
CString TransationMultiControlReferenceTemplateData(CString csData)
{
	int iLen,iOff;
	CString csResult;
	CString csSipData;

	iLen = csData.GetLength();
	iOff = 0 ;

	do
	{
		if( _CString2Int(csData.Mid(iOff,2)) == 0xA4)
		{
			_GetTLVData(csData.Mid(iOff,iLen-iOff),0xA4,csSipData);
			csResult  += TransationControlReferenceTemplateData(csSipData);
		}


		iOff += csSipData.GetLength()+4;

		if(iOff < iLen)
			csResult  += _T(" , ");

	}while(iLen > iOff);


	return csResult;
}
CString TransationSecurityConditionData(int iSTTag,CString csSTData)
{
	CString csResult;
	switch(iSTTag)
	{
	case 0x90:
		csResult = _T("ALWAYS");
		break;
	case 0x97:
		csResult = _T("NEVER");
		break;


	case 0xA4:
		csResult = TransationControlReferenceTemplateData(csSTData);
		break;

	case 0xA0:

		csResult =_T("One of ") + TransationMultiControlReferenceTemplateData(csSTData);



		break;
	case 0xA7:

		csResult =_T("Inversion of ") + TransationMultiControlReferenceTemplateData(csSTData);


		break;

	case 0xAF:

		csResult =_T("Every ") + TransationMultiControlReferenceTemplateData(csSTData);


		break;


	default:
		csResult  = _T("超出理解范围");
		break;
	}

	return csResult;
}

void _GetACFromARR( int iCommand,CString csARR,CString &csOutput,int* Other, bool bIsIns /*= false*/ )
{
	int iAccTag,iSTTag; 
	int iOffset,iARRLen;
	CString csAccData,csSTData;
	iOffset = 0;
	//CString csResult;
	CString csOther;

	iARRLen = csARR.GetLength();
	*Other  = 0;

	do
	{
		iAccTag   = _CString2Int(csARR.Mid(iOffset,2));

		if(iAccTag == 0xFF)
			break;

		_GetTLVData(csARR.Mid(iOffset ,iARRLen-iOffset),iAccTag,csAccData);

		iOffset   += csAccData.GetLength()+4;

		iSTTag   = _CString2Int(csARR.Mid(iOffset,2));

		 _GetTLVData(csARR.Mid(iOffset ,iARRLen-iOffset),iSTTag,csSTData);

		if(iAccTag == 0x80)
		{
			if((iCommand&_CString2Int(csAccData)) == iCommand)
				csOutput += TransationSecurityConditionData(iSTTag,csSTData);
		}
		else if(iAccTag == 0x84)
		{
			if (!bIsIns)
			{
				switch(_CString2Int(csAccData))
				{
				case 0xE2:
					if(iCommand == 0x04)
						csOutput += TransationSecurityConditionData(iSTTag,csSTData);
					break;
				case 0xB3:
				case 0xB2:
				case 0xB1:
				case 0xB0:

					if(iCommand == 0x01)
						csOutput += TransationSecurityConditionData(iSTTag,csSTData);
					break;

				case 0xD6:
				case 0xD7:
				case 0xDC:
				case 0xDD:			
					if(iCommand == 0x02)
						csOutput += TransationSecurityConditionData(iSTTag,csSTData);

					break;

				case 0x40:

					if(iCommand == 0x08)
						csOutput += TransationSecurityConditionData(iSTTag,csSTData);

					break;
				case 0x44:		
					if(iCommand == 0x10)
						csOutput += TransationSecurityConditionData(iSTTag,csSTData);
					break;
				case 0xE6:
				case 0xE8:
					if(iCommand == 0x20)
						csOutput += TransationSecurityConditionData(iSTTag,csSTData);
					break;
				default:
					if(iCommand == 0xFF)
					{
						csOutput += csAccData + TransationSecurityConditionData(iSTTag,csSTData);
					}
					*Other = 1;
					break;

				}

			}
			else if (iCommand == _CString2Int(csAccData))
				csOutput += TransationSecurityConditionData(iSTTag,csSTData);

		}

		iOffset += csSTData.GetLength()+4;
	}while(iARRLen > iOffset);

	if (csOutput.IsEmpty())
	{
		csOutput = _T("DEFAULT");
	}
	//return csResult;

}



void _TransationMCC(CString csMNCMCC,CString&csOutput)
{
	CString csMNC;
	csOutput.Empty();
	csMNC = csMNCMCC.Mid(1,1) + csMNCMCC.Mid(0,1)+csMNCMCC.Mid(3,1);

	if ((_CString2Int(csMNC)!= 0xFFF) &&(_CString2Int(csMNC.Mid(2,1)) == 0xF)) 
		csMNC = csMNC .Mid(0,2);

	csOutput = csMNC;

}
void _TransationMNC(CString csMNCMCC,CString&csOutput)
{
	CString csMCC;
	csOutput.Empty();
	csMCC = csMNCMCC.Mid(5,1) + csMNCMCC.Mid(4,1)+csMNCMCC.Mid(2,1);

	if ((_CString2Int(csMCC)!= 0xFFF) &&(_CString2Int(csMCC.Mid(2,1)) == 0xF)) 
		csMCC = csMCC .Mid(0,2);

	csOutput = csMCC;

}
void _TransationMNCMCC(CString csMNCMCC,CString&csOutput)
{
	CString csMCC,csMNC;
	csOutput.Empty();
	_TransationMNC(csMNCMCC,csMNC);
	_TransationMCC(csMNCMCC,csMCC);

	csOutput = csMCC+csMNC;
}





#define _DEF_MNCMCC_OK 0
#define _DEF_MNCMCC_OPEN_FAILD   -1
#define _DEF_MNCMCC_STATUS_FAILD -2
CString __GetCurrentDIR()
{
	CString csPath;
	GetModuleFileName(NULL,csPath.GetBuffer(1000),1000);
	csPath.ReleaseBuffer();
	csPath = csPath.Left((int) csPath.ReverseFind( '\\'));
	return csPath;

}


//打开MNCMCC CSV 文件
// Return 0 成功， -1 打开文件失败 -2 获取文件状态失败
//************************************
// Method:    _OpenMCCMNCCSVFile
// FullName:  _OpenMCCMNCCSVFile
// Access:    public 
// Returns:   int
// Qualifier:
// Parameter: CString csPath
// Parameter: CStdioFile * CSFFile
//************************************
int _OpenCSVFile(CString csPath,CStdioFile* CSFFile)
{
	CString csData;
	CFileStatus csSta;


	if (!CSFFile->Open(csPath,CFile::shareDenyRead))
		return FALSE;

	if (! CSFFile->GetStatus(csPath,csSta))
	{
		CSFFile->Close();
		return FALSE;
	}

	return TRUE;
}


CString _GetCSVData(CString csData,int iNum)
{
	CString csResult;

	if (_GetCSVData(csData,iNum,csResult) <= 0)
	{
		csResult.Empty();
	}
	return csResult;

	//int iRet,iStart,iCurrent,iLen;
	//CString csResult;
	//csResult.Empty();

	//iCurrent = 0;
	//iStart   = 0 ;

	//if (!csData.IsEmpty())
	//{
	//	iLen = csData.GetLength();
	//	do 
	//	{
	//		iRet = csData.Find(_T(","),iStart);
	//		iCurrent += 1;
	//		if (iCurrent == iNum)
	//		{
	//			if (iRet>=0)
	//				csResult = csData.Mid(iStart,iRet-iStart);
	//			else
	//				csResult = csData.Mid(iStart,iLen-iStart);

	//		}

	//		iStart    = iRet+1;
	//	} while (iRet>1);

	//}
	//return csResult;

}


//获取MNCMCC 信息

// Return 1 成功，
//        0 没有找到
//  -1 打开文件失败 -2 获取文件状态失败
int _GetMCCMNCInformartion(int iMCC,int iMNC,CString& csBrand,CString& csOperator,CString& csStatus,CString& csCountry)
{
	int iRet,iReadRet;
	CStdioFile CSFFile;
	CString csRowData;
	CString csCell1,csCell2,csCell3,csCell4,csCell5;
	bool bHeader;

	iRet = FALSE;
	if (!_OpenCSVFile(__GetCurrentDIR()+_T("\\INF\\MCCMNC.csv"),&CSFFile))
		return FALSE;

	do 
	{
		csRowData.Empty();

		iReadRet = CSFFile.ReadString(csRowData);
		if (iReadRet == FALSE)
			break;

		csCell1 = _GetCSVData(csRowData,1);
		csCell2 = _GetCSVData(csRowData,2);
		csCell3 = _GetCSVData(csRowData,3);
		csCell4 = _GetCSVData(csRowData,4);
		csCell5 = _GetCSVData(csRowData,5);
		bHeader = false;
		if ((csCell5.IsEmpty())&&(csCell4.IsEmpty())&&(csCell3.IsEmpty())&&(csCell2.IsEmpty())&&(!csCell1.IsEmpty()))
			csCountry = csCell1;

		else if ((csCell5==_T("MCC "))&&(csCell4==_T("MNC ")))
			bHeader = true;	
		else
		{
			if ((_CString2Int(csCell1) == iMCC)&&(_CString2Int(csCell2) == iMNC))
			{
				csBrand    = csCell3;
				csOperator = csCell4;
				csStatus   = csCell5;
				iRet       = TRUE;
				break;
			}
		}
	} while (iReadRet>0);

	return iRet;

}


//获取MNCMCC 信息

// Return 1 成功，
//        0 没有找到
//  -1 打开文件失败 -2 获取文件状态失败
int _GetMCCMNCInformartion(CString csMCCMNC,CString& csBrand,CString& csOperator,CString& csStatus,CString& csCountry)
{

	CString csMCC,csMNC;
	CString csTemp;

	_TransationMNCMCC(csMCCMNC,csTemp);

	csMCC = csTemp.Left(3);
	csMNC = csTemp.Right(csTemp.GetLength()-3);

	return _GetMCCMNCInformartion(_CString2Int(csMCC),_CString2Int(csMNC),csBrand,csOperator,csStatus,csCountry);

}

//Input 64F010 
//output 
BOOL _GenerateMCCMNCDescription(CString csMCCMNC,CString& csOutput)
{
	CString csDes,csInfor1,csInfor2,csInfor3,csInfor4;

	if (_GetMCCMNCInformartion(csMCCMNC,csInfor1,csInfor2,csInfor3,csInfor4) ==1)
	{
		csOutput =  _T("国家：")+csInfor4+_T("\n");
		csOutput += _T("品牌：")+csInfor1+_T("\n");
		csOutput += _T("运营商：")+csInfor2+_T("\n");
		csOutput += _T("状态：")+csInfor3+_T("\n");

	}
	else
		csOutput.Empty();

	if (csOutput.IsEmpty())
		return FALSE;

	return TRUE;


	
}


BOOL CalculateOddEvenIndication( CString csData )
{

	int iLen = csData.GetLength();

	BOOL bRet = TRUE;

	for (int i = 1 ; i <= iLen * 8 ; i++)
	{
		if (_Getbit(csData,i))
			bRet= !bRet;

	}

	return bRet;
}



BOOL _ConvertMIPUPP(CString csMIPUPP,int iSum,CString& csOutput)
{
	unsigned char ucResult[0xFF];
	unsigned char ucMipUpp[0xFF];
	unsigned char ucTemp[4];
	BOOL bRet;
	int iCurrentByte,iCurrentBit;
	int iMipLen;
	int iNum;
	iCurrentByte = 0;
	iCurrentBit  = 0;
	int iTemp;
	csOutput.Empty();

	//csMIPUPP = ConvertAcsii(csMIPUPP);

	_ConvertAscii(csMIPUPP,csOutput);
	csMIPUPP = csOutput;
	iMipLen  = _CString2UcHex(csMIPUPP,ucMipUpp);
	ZeroMemory(ucResult,0xFF);


	//RETRY_INFO_INCLUDED: 1个BIT置为“1”
	//MAX_NUM_RETRY： 最多3次重发，2个BIT置为“11”
	//FIRST_RETRY_TIMEOUT： 3个BIT设置为111
	//REREG_THRESHOLD: 6个BIT：011111

	ucResult[0] = 0xFD;
	ucResult[1] = 0xF0;
	//NUM_NAI： 5个，4个bit表示，0101
	ucResult[1] += (iSum&0xF);

	iCurrentByte = 2;
	iCurrentBit  = 0;

	//开始第一条


	for(iNum = 0; iNum<iSum;iNum++)
	{
		//NAI_ENTRY_INDEX


		ZeroMemory(ucTemp,04);

		ucTemp[0] = iNum*0x10;
		bRet = __Copy2bit(ucResult,ucTemp,4,iCurrentByte,iCurrentBit);

		iCurrentBit = iCurrentBit +4;

		if (iCurrentBit>0x8)
		{
			iCurrentBit   =iCurrentBit%0x08;
			iCurrentByte +=1;
		}


		ZeroMemory(ucTemp,04);

		ucTemp[0] = iMipLen;
		bRet = __Copy2bit(ucResult,ucTemp,8,iCurrentByte,iCurrentBit);

		iCurrentByte = iCurrentByte +1;


		bRet = __Copy2bit(ucResult,ucMipUpp,iMipLen*8,iCurrentByte,iCurrentBit);
		iCurrentByte = iCurrentByte+iMipLen;

		ZeroMemory(ucTemp,04);
		//T_BIT
		if (iNum<=2)
			ucTemp[0] = 0x80;
		else
			ucTemp[0] = 0x00;

		bRet = __Copy2bit(ucResult,ucTemp,1,iCurrentByte,iCurrentBit);

		iCurrentBit = iCurrentBit +1;

		if (iCurrentBit>0x8)
		{
			iCurrentBit   =iCurrentBit%0x08;
			iCurrentByte +=1;
		}

		//HOME_ADDRESS：

		ZeroMemory(ucTemp,04);
		iTemp = _CString2UcHex(_T("00000000"),ucTemp);
		bRet  = __Copy2bit(ucResult,ucTemp,iTemp*8,iCurrentByte,iCurrentBit);
		iCurrentByte += iTemp;

		//PRIMARY_HOME_AGENT：
		ZeroMemory(ucTemp,04);
		iTemp = _CString2UcHex(_T("00000000"),ucTemp);
		bRet  = __Copy2bit(ucResult,ucTemp,iTemp*8,iCurrentByte,iCurrentBit);
		iCurrentByte += iTemp;

		//SECONDARY_HOME_AGENT
		ZeroMemory(ucTemp,04);
		iTemp = _CString2UcHex(_T("00000000"),ucTemp);
		bRet  = __Copy2bit(ucResult,ucTemp,iTemp*8,iCurrentByte,iCurrentBit);
		iCurrentByte += iTemp;

		//MN_AAA_AUTH_ALGORITHM
		ZeroMemory(ucTemp,04);
		ucTemp[0] = 0x10;
		bRet  = __Copy2bit(ucResult,ucTemp,4,iCurrentByte,iCurrentBit);


		iCurrentBit = iCurrentBit +4;
		if (iCurrentBit>0x8)
		{
			iCurrentBit   =iCurrentBit%0x08;
			iCurrentByte +=1;
		}


		//MN-AAA-SPI_INDICATOR
		ZeroMemory(ucTemp,04);
		ucTemp[0] = 0x80;
		bRet = __Copy2bit(ucResult,ucTemp,1,iCurrentByte,iCurrentBit);
		iCurrentBit = iCurrentBit +1;
		if (iCurrentBit>0x8)
		{
			iCurrentBit   =iCurrentBit%0x08;
			iCurrentByte +=1;
		}


		//MN-AAA_SPI
		ZeroMemory(ucTemp,04);
		iTemp = _CString2UcHex(_T("00000002"),ucTemp);
		bRet  = __Copy2bit(ucResult,ucTemp,iTemp*8,iCurrentByte,iCurrentBit);
		iCurrentByte += iTemp;

		//MN-HA_AUTH_ALGORITHM

		ZeroMemory(ucTemp,04);
		ucTemp[0] = 0x10;
		bRet  = __Copy2bit(ucResult,ucTemp,4,iCurrentByte,iCurrentBit);

		iCurrentBit = iCurrentBit +4;
		if (iCurrentBit>0x8)
		{
			iCurrentBit   =iCurrentBit%0x08;
			iCurrentByte +=1;
		}



		//MN-HA_SPI_INDICATOR
		ZeroMemory(ucTemp,04);
		ucTemp[0] = 0x80;
		bRet = __Copy2bit(ucResult,ucTemp,1,iCurrentByte,iCurrentBit);
		iCurrentBit = iCurrentBit +1;
		if (iCurrentBit>0x8)
		{
			iCurrentBit   =iCurrentBit%0x08;
			iCurrentByte +=1;
		}


		//MN-HA_SPI
		ZeroMemory(ucTemp,04);
		iTemp = _CString2UcHex(_T("00000002"),ucTemp);
		bRet  = __Copy2bit(ucResult,ucTemp,iTemp*8,iCurrentByte,iCurrentBit);
		iCurrentByte += iTemp;
	}


	if (iCurrentBit!= 0)
		iCurrentByte +=1;
	_UcHex2CString(ucResult,iCurrentByte,csOutput);


	if (csOutput.IsEmpty())
		return FALSE;
	else
		return TRUE;

}

void _RightShift(CString csData, int iShiftBit,CString& csOutput)
{
	BOOL bRet;
	BYTE * ucInPut;
	BYTE * ucOutPut;
	int iInLen,iOutLen;
	CString csResult;

	iInLen = csData.GetLength() /2 ;

	ucInPut   = new BYTE[iInLen];
	ucOutPut = new BYTE[iInLen +1];
	ZeroMemory(ucOutPut,iInLen +1);

	iInLen = _CString2UcHex(csData,ucInPut);

	bRet = __RightShift(ucOutPut,ucInPut,iShiftBit,iInLen,&iOutLen);

	if (bRet)
		_UcHex2CString(ucOutPut,iOutLen,csOutput);
	else
		csOutput.Empty();

	delete ucInPut;
	delete ucOutPut;
}



int _GetMarkNumber(CString csData,CString csMark)
{
	int iLen,iMark,iNum;
	iLen  = csData.GetLength();
	iMark = csMark.GetLength();
	iNum  = 0;
	for (int i = 0; i < iLen ; i++)
	{
		if (csData.Mid(i,iMark) == csMark)
		{
			iNum += 1;
			i    += (iMark -1);
		}
	}

	return iNum;
}

BOOL _GetDatasInMark(CString csData,CString csMark,int iNumber,CString &csOutput)
{
	int iSum,iMark;
	int iOff,iLen;

	iSum = _GetMarkNumber(csData,csMark);
	iMark= csMark.GetLength();
	if (iSum < iNumber)
	{
		csOutput.Empty();
		return FALSE;
	}

	iLen = 0;
	for (int i = 0 ; i < iNumber ; i++)
	{
		iOff = iLen;
		iLen = csData.Find(csMark,iOff)+iMark; 
	}

	iLen = iLen - iOff -iMark;


	csOutput = csData.Mid(iOff,iLen);
	return TRUE;
}




int _RecogniseMNCLen(int iMCC,int iMNC2Byte)
{
	int iRet;
	switch (iMCC)
	{
	case 0x365:
	case 0x344:
	case 0x338:
	case 0x364:
	case 0x342:
	case 0x302:
	case 0x346:
	case 0x732:
	case 0x366:
	case 0x352:
	case 0x310:
	case 0x311:
	case 0x356:
	case 0x360:
	case 0x376:
	case 0x316:
		iRet = 03;
		break;
	case 0x722:
		switch(iMNC2Byte)
		{
		case 0x01:
		case 0x02:
		case 0x07:
		case 0x31:
		case 0x32:
		case 0x33:
		case 0x35:
			iRet = 03;
			break;
		default:
			iRet = 02;
			break;
		}
		break;
	case 0x502:
		if (iMNC2Byte == 0x15)
			iRet = 03;
		else
			iRet = 02;
		break;
	case 0x405:
		switch(iMNC2Byte)
		{
		case 0x75:
		case 0x79:
		case 0x80:
		case 0x81:
		case 0x82:
		case 0x83:
		case 0x84:
		case 0x85:
		case 0x86:
		case 0x87:
		case 0x88:
		case 0x91:
		case 0x92:
			iRet = 03;
			break;
		default:
			iRet = 02;
			break;
		}
		break;
	default:
		iRet = 02;
	}
	return iRet;
}



//使用于 ADN的格式中
void _TranslateAlphaIdentifier(CString csData,CString& csOutput)
{
	//CString csResult;
	int iCoding;
	int iLen;
	int i;
	csOutput.Empty();
	iCoding = _CString2Int(csData.Mid(0,2));
	iLen    = csData.GetLength();

	for ( i = 0 ;i< iLen ; i+= 2)
	{
		if (_CString2Int (csData.Mid(i,2)) == 0xFF)
			iLen = i;
	}

	switch(iCoding)
	{
	case 0x81:
	case 0x82:

		iLen = _CString2Int(csData.Mid(2,2))*2;
		iLen = iLen+ (iCoding&0x7)*2;
		 __TranslateUcs2(csData.Mid(4,iLen),csOutput,iCoding);

		break;
	case 0x80:
		//去除Tag
		//如果一开始取长度时候出现最后一位出现FF,由此处进行补偿长度

		if ((iLen%4) == 0)
			iLen += 2 ;

		 __TranslateUcs2(csData.Mid(2,iLen-2),csOutput,0x80);
		break;
	default:
		_TranslateAscii(csData.Left(iLen),csOutput);
		break;
	}

	
}


BOOL _TranslatePNN(CString csData,CString &csOutput)
{
	CString csElement;
	BOOL bRet;
	csOutput.Empty();
	csElement = csData.Mid(00,02);

	if (_CString2Int(csElement)&0x10)
	{
	    bRet = __TranslateUcs2(csData.Mid(2),csOutput,0x80);
	//	csOutput = _T("80")+csOutput;
	}

	else
	{
		bRet = _Translate7bit(csData.Mid(2,csData.GetLength()-2),csOutput);

		bRet = _TranslateAscii(csOutput,csOutput);
	}

	return bRet;
}

BOOL _TranslateFileStructure(int iStructure,CString& csText)
{

	switch(iStructure&7)
	{
	case 0:csText    = _T("文件类型无信息");break;
	case 1:csText    = _T("透明文件");break;
	case 2:csText    = _T("线性定长文件");break;
	case 3:csText    = _T("线性定长文件,TLV格式");break;
	case 4:csText    = _T("线性不定长文件");break;
	case 5:csText    = _T("线性不定长文件,TLV格式");break;
	case 6:csText    = _T("循环文件");break;
	case 7:csText    = _T("循环文件,TLV格式");break;
	}

	return TRUE;
}



//bool GenerateADFName          (CString csAID,CString& csName)
//{
//	CString csTemp;
//
//	//102220 / 401  Registered application provider IDentifier
//	csTemp= csAID.Left(10);
//	if (csTemp == _T("A000000009"))
//		csName = _T("ETSI");
//	else if (csTemp == _T("A000000087"))
//		csName = _T("3GPP");
//	else if (csTemp == _T("A000000343"))
//		csName = _T("3GPP2");
//	else
//		return false;
//
//	return true;
//}
//bool GenerateDFName           (int iFID,int iPreFID,CString& csName)
//{
//	csName.Empty();
//	switch(iPreFID)
//	{
//	case 0x00:
//		if (iFID == 0x3F00)     csName = _T("MF");
//		break;
//	case 0x3F00:
//		if (iFID == 0x7F10)     csName = _T("TELECOM");
//		else if(iFID == 0x7F20) csName = _T("GSM");
//		else if(iFID == 0x7F25) csName = _T("CDMA");
//		break;
//	case 0x7F10:
//		if (iFID == 0x5F50)     csName = _T("GRAPHICS");
//		else if(iFID == 0x5F3A) csName = _T("PHONEBOOK");
//		else if(iFID == 0x5F3B) csName = _T("MULTIMEDIA");
//		else if(iFID == 0x5F3C)  csName = _T("MMSS");
//		break;
//	case 0x7F20:
//		break;
//	case 0x7F25:
//		break;
//	case 0x10009:
//		break;
//	case 0x10087:
//		if (iFID     == 0x5F3A)  csName = _T("PHONEBOOK");
//		else if(iFID == 0x5F3B)  csName = _T("GSM-ACCESS");
//		else if(iFID == 0x5F3C)  csName = _T("MExE");
//		else if(iFID == 0x5F40)  csName = _T("WLAN");
//		else if(iFID == 0x5F50)  csName = _T("HNB");
//		else if(iFID == 0x5F70)  csName = _T("SoLSA");
//		else if(iFID == 0x5F80)  csName = _T("BCAST");	
//		break;
//	case 0x10343:
//		break;
//	}
//
//	if (csName.IsEmpty())
//		return false;
//	else
//		return true;
//
//}
//bool _GenerateDFName           (int iFID,int iMark,CString& csName)
//{
//	csName.Empty();
//	switch(iMark)
//	{
//
//	case _DEF_Card:
//		if (iFID == 0x7F10)     csName = _T("TELECOM");
//		else if(iFID == 0x7F20) csName = _T("GSM");
//		else if(iFID == 0x7F25) csName = _T("CDMA");
//		else if(iFID == 0x7FF0)   csName = _T("3GPP");
//		else if(iFID == 0x7FF1)   csName = _T("3GPP2");
//		break;
//	case _DEF_Tele:
//		if (iFID == 0x5F50)     csName = _T("GRAPHICS");
//		else if(iFID == 0x5F3A) csName = _T("PHONEBOOK");
//		else if(iFID == 0x5F3B) csName = _T("MULTIMEDIA");
//		else if(iFID == 0x5F3C)  csName = _T("MMSS");
//		break;
//	case _DEF_3GPP:
//		if (iFID     == 0x5F3A)  csName = _T("PHONEBOOK");
//		else if(iFID == 0x5F3B)  csName = _T("GSM-ACCESS");
//		else if(iFID == 0x5F3C)  csName = _T("MExE");
//		else if(iFID == 0x5F40)  csName = _T("WLAN");
//		else if(iFID == 0x5F50)  csName = _T("HNB");
//		else if(iFID == 0x5F70)  csName = _T("SoLSA");
//		else if(iFID == 0x5F80)  csName = _T("BCAST");	
//		break;
//	default:
//		if (iFID == 0x3F00)     csName = _T("MF");
//		break;
//	}
//
//	if (csName.IsEmpty())
//		return false;
//	else
//		return true;
//
//}
//bool GenerateEFNameInMF       (int iFID,CString &csName,bool bAb)
//{
//	bool bRet = true;
//
//	csName.Empty();
//	if (bAb)
//	{
//		switch(iFID)
//		{
//
//		case 0x1F3E:csName = _T("ICCRP");break;
//		case 0xEA04:csName = _T("ICCR");break;
//		case 0x2F00:csName = _T("DIR");break;
//		case 0x2F02:csName = _T("ICCSN");break;
//		case 0x2F05:csName = _T("PL");break;
//		case 0x2F06:csName = _T("ARR");break;
//		case 0x2FE2:csName = _T("ICCID");break;
//		default: bRet = false;break;
//
//		}
//
//	}
//	else
//	{
//
//		switch(iFID)
//		{
//		case 0x1F3E:csName = _T("ICC RP");break;
//		case 0xEA04:csName = _T("ICC R");break;
//		case 0x2F00:csName = _T("Application directory");break;
//		case 0x2F02:csName = _T("ICC serial number");break;
//		case 0x2F05:csName = _T("Preferred languages");break;
//		case 0x2F06:csName = _T("Access rule reference");break;
//		case 0x2FE2:csName = _T("ICC identification");break;
//		default: bRet = false;break;
//		}
//
//	}
//	return bRet;
//}
//bool GenerateEFNameInTelecom  (int iFID,CString &csName,bool bAb)
//{
//	bool bRet = true;
//
//	csName.Empty();
//	if (bAb)
//	{
//		switch(iFID)
//		{
//		case 0x6F06:csName = _T("ARR");break;
//		case 0x6F3A:csName = _T("ADN");break;
//		case 0x6F3B:csName = _T("FDN");break;
//		case 0x6F3C:csName = _T("SMS");break;
//		case 0x6F3D:csName = _T("CCP");break; 
//		case 0x6F40:csName = _T("MSISDN");break;
//		case 0x6F42:csName = _T("SMSP");break;
//		case 0x6F43:csName = _T("SMSS");break;
//		case 0x6F44:csName = _T("LND");break;
//		case 0x6F47:csName = _T("SMSR");break;
//		case 0x6F49:csName = _T("SDN");break;
//		case 0x6F4A:csName = _T("EXT1");break;
//		case 0x6F4B:csName = _T("EXT2");break;
//		case 0x6F4C:csName = _T("EXT3");break;
//		case 0x6F4D:csName = _T("BDN");break;
//		case 0x6F4E:csName = _T("EXT4");break;
//		case 0x6F4F:csName = _T("ECCP");break;
//		case 0x6F54:csName = _T("SUME");break;
//		case 0x6FE0:csName = _T("ICE_DN");break;
//		case 0x6FE1:csName = _T("ICE_FF");break;
//		default: bRet = false;break;
//
//		}
//
//	}
//	else
//	{
//		switch(iFID)
//		{
//		case 0x6F06:csName = _T("Access Rule Reference");break;
//		case 0x6F3A:csName = _T("Abbreviated dialling numbers");break;
//		case 0x6F3B:csName = _T("Fixed Dialling Numbers");break;
//		case 0x6F3C:csName = _T("Short messages");break;
//		case 0x6F40:csName = _T("MSISDN");break;
//		case 0x6F42:csName = _T("Short message service parameters");break;
//		case 0x6F43:csName = _T("SMS status");break;
//		case 0x6F44:csName = _T("Last number dialled");break;
//		case 0x6F47:csName = _T("Short message status reports");break;
//		case 0x6F49:csName = _T("Service Dialling Numbers");break;
//		case 0x6F4A:csName = _T("Extension1");break;
//		case 0x6F4B:csName = _T("Extension2");break;
//		case 0x6F4C:csName = _T("Extension3");break;
//		case 0x6F4D:csName = _T("Barred Dialling Numbers");break;
//		case 0x6F4E:csName = _T("Extension4");break;
//		case 0x6F4F:csName = _T("Extended Capability Configuration Parameter");break;
//		case 0x6F54:csName = _T("SetUpMenu Elements");break;
//		case 0x6FE0:csName = _T("In Case of Emergency – Dialling Number");break;
//		case 0x6FE1:csName = _T("In Case of Emergency – Free Format");break;
//		default: bRet = false;break;
//		}
//
//	}
//	return bRet;
//}
//bool GenerateEFNameIn3GPP     (int iFID,CString &csName,bool bAb)
//{
//	bool bRet = true;
//
//	csName.Empty();
//	if (bAb)
//	{
//		switch(iFID)
//		{
//		case 0x0004:csName = _T("ADF PARA");break;
//		case 0x0040:csName = _T("AUTHOPC");break;
//		case 0x0041:csName = _T("AUTHPAR");break;
//		case 0x00F2:csName = _T("SEQ");break;
//		case 0x6F05:csName = _T("LI");break;
//		case 0x6F06:csName = _T("ARR");break;
//		case 0x6F07:csName = _T("IMSI");break;
//		case 0x6F08:csName = _T("Keys");break;
//		case 0x6F09:csName = _T("KeysPS");break;
//		case 0x6F2C:csName = _T("DCK");break;
//		case 0x6F31:csName = _T("HPPLMN");break;
//		case 0x6F32:csName = _T("CNL ");break;
//		case 0x6F37:csName =  _T("ACMmax "); break;
//		case 0x6F38:csName = _T("UST ");break;
//		case 0x6F39:csName = _T("ACM ");break;
//		case 0x6F3B:csName = _T("FDN "); break;
//		case 0x6F3C:csName = _T("SMS ");break;
//		case 0x6F3E:csName =  _T("GID1 "); break;
//		case 0x6F3F:csName =  _T("GID2 ");break;
//		case 0x6F40:csName = _T("MSISDN ");break;
//		case 0x6F41:csName = _T("PUCT ");break;
//		case 0x6F42:csName = _T("SMSP ");break;
//		case 0x6F43:csName = _T("SMSS ");break;
//		case 0x6F45:csName = _T("CBMI "); break;
//		case 0x6F46:csName = _T("SPN ");break;
//		case 0x6f47:csName = _T("SMSR ");break;
//		case 0x6F48:csName = _T("CBMID ");break;
//		case 0x6F49:csName = _T("SDN ");break;
//		case 0x6F4B:csName = _T("Ext2 ");break;
//		case 0x6F4C:csName = _T("Ext3 "); break;
//		case 0x6F4D:csName = _T("BDN ");break;
//		case 0x6F4E: csName = _T("Ext5 "); break;
//		case 0x6F4F:csName = _T("CCP2 "); break;
//		case 0x6F50:csName = _T("CBMIR ");break;
//		case 0x6F54:csName = _T("SUME ");break;
//		case 0x6F55:csName = _T("Ext4 "); break;
//		case 0x6F56:csName = _T("EST "); break;
//		case 0x6F57:csName = _T("ACL ");break;
//		case 0x6F58:csName = _T("CMI "); break;
//		case 0x6F5B:csName = _T("TART-HFN "); break;
//		case 0x6F5C:csName = _T("THRESHOLD "); break;
//		case 0x6F60:csName = _T("PLMNwAcT ");		break;
//		case 0x6F61:csName = _T("OPLMNwAcT "); break;
//		case 0x6F62:csName = _T("HPLMNwAcT ");break;
//		case 0x6F73:csName = _T("PSLOCI ");break;
//		case 0x6F78:csName = _T("ACC ");break;
//		case 0x6F7B:csName = _T("FPLMNS ");break;
//		case 0x6F7E:csName = _T("LOCI "); break;
//		case 0x6F80:csName = _T("ICI ");break;
//		case 0x6F81:csName = _T("OCI ");break;
//		case 0x6F82:csName = _T("ICT ");break;
//		case 0x6F83:csName = _T("OCT ");break;
//		case 0x6FAD:csName = _T("AD ");break;
//		case 0x6FB1:csName = _T("VGCS ");break;
//		case 0x6FB2:csName = _T("VGCSS "); break;
//		case 0x6FB3:csName = _T("VBS ");break;
//		case 0x6FB4:csName = _T("VBSS ");break;
//		case 0x6FB5:csName = _T("EMLPP ");break;
//		case 0x6FB6:csName = _T("AAeM ");break;
//		case 0x6FB7:csName = _T("ECC ");break;
//		case 0x6FC3:csName = _T("Hiddenkey ");break;
//		case 0x6FC4:csName = _T("NETPAR "); break;
//		case 0x6FC5:csName = _T("PNN ");break;
//		case 0x6FC6:csName = _T("ONL ");break;
//		case 0x6FC7:csName = _T("MDN "); break;
//		case 0x6FC8:csName = _T("Ext6 ");break;
//		case 0x6FC9:csName = _T("MBI ");break;
//		case 0x6FCA:csName = _T("MWIS "); break;
//		case 0x6FCB:csName = _T("CFIS ");break;
//		case 0x6FCC:csName = _T("Ext7 "); break;
//		case 0x6FCD:csName = _T("SPDI "); break;
//		case 0x6FCE:csName = _T("MMSN "); break;
//		case 0x6FCF:csName = _T("Ext8 "); break;
//		case 0x6FD0:csName = _T("MMSICP "); break;
//		case 0x6FD1:csName = _T("MMSUP ");break;
//		case 0x6FD2:csName = _T("MMSUCP ");break;
//		case 0x6FD3:csName = _T("NIA ");break;
//		case 0x6FD4:csName = _T("VGCSCA "); break;
//		case 0x6FD5:csName = _T("VBSCA "); break;
//		case 0x6FD6:csName = _T("GBAP "); break;
//		case 0x6FD7:csName = _T("MSK "); break;
//		case 0x6FD8:csName = _T("MUK "); break;
//		case 0x6FD9:csName = _T("EHPLMN "); break;
//		case 0x6FDA:csName = _T("GBANL "); break;
//		case 0x6FDB:csName = _T("EHPLMNPI ");	break;
//		case 0x6FDC:csName = _T("LRPLMNSI "); break;
//		case 0x6FDD:csName = _T("NAFKCA "); break;
//		case 0x6FDE:csName = _T("SPNI "); break;
//		case 0x6FDF:csName = _T("PNNI ");break;
//		case 0x6FE0:csName = _T("CE_DN ");break;
//		case 0x6FE1:csName = _T("ICE_FF "); break;
//		case 0x6FE2:csName = _T("NCP-IP "); break;
//		case 0x6FE3:csName = _T("EPSLOCI ");	break;
//		case 0x6FE4:csName = _T("EPSNSC "); break;
//		default: bRet = false;break;
//
//		}
//
//	}
//	else
//	{
//
//		switch(iFID)
//		{
//		case 0x6F05:csName = _T("Language indication");break;
//		case 0x6F06:csName = _T("Access rule reference");break;
//		case 0x6F07:csName = _T("International Mobile Subscriber Identity");break;
//		case 0x6F08:csName = _T("Ciphering and Integrity Keys");break;
//		case 0x6F09:csName = _T("Ciphering and integrity keys for packet switched domain");break;
//		case 0x6F2C:csName = _T("De-personalization Control Keys");break;
//		case 0x6F31:csName = _T("Higher Priority PLMN search period");break;
//		case 0x6F32:csName = _T("Co-operative network list ");break;
//		case 0x6F37:csName = _T("ACM maximum value "); break;
//		case 0x6F38:csName = _T("USIM service table ");break;
//		case 0x6F39:csName = _T("Accumulated call meter ");break;
//		case 0x6F3B:csName = _T("Fixed dialling numbers "); break;
//		case 0x6F3C:csName = _T("Short messages ");break;
//		case 0x6F3E:csName =  _T("Group identifier level 1 "); break;
//		case 0x6F3F:csName =  _T("Group identifier level 2 ");break;
//		case 0x6F40:csName = _T("MSISDN storage ");break;
//		case 0x6F41:csName = _T("(Price per Unit and Currency Table ");break;
//		case 0x6F42:csName = _T("Short message service parameters ");break;
//		case 0x6F43:csName = _T("Short message service status ");break;
//		case 0x6F45:csName = _T("Cell Broadcast Message identifier selection "); break;
//		case 0x6F46:csName = _T("Service provider name ");break;
//		case 0x6f47:csName = _T("Short message status reports ");break;
//		case 0x6F48:csName = _T("Cell Broadcast Message Identifier for Data Download ");break;
//		case 0x6F49:csName = _T("Service Dialling Numbers ");break;
//		case 0x6F4B:csName = _T("Extension 2 ");break;
//		case 0x6F4C:csName = _T("Extension 3 "); break;
//		case 0x6F4D:csName = _T("Barred Dialling Numbers ");break;
//		case 0x6F4E: csName = _T("Extension 5 "); break;
//		case 0x6F4F:csName = _T("Capability configuration parameters 2 "); break;
//		case 0x6F50:csName = _T("Cell Broadcast Message Identifier Range selection ");break;
//		case 0x6F54:csName = _T("SetUpMenu Elements ");break;
//		case 0x6F55:csName = _T("Extension 4 "); break;
//		case 0x6F56:csName = _T("Enabled services table "); break;
//		case 0x6F57:csName = _T("Access point name control list ");break;
//		case 0x6F58:csName = _T("Comparison method information "); break;
//		case 0x6F5B:csName = _T("Initialisation value for Hyperframe number "); break;
//		case 0x6F5C:csName = _T("Maximum value of START "); break;
//		case 0x6F60:csName = _T("User controlled PLMN selector with Access Technology ");		break;
//		case 0x6F61:csName = _T("Operator controlled PLMN selector with Access Technology "); break;
//		case 0x6F62:csName = _T("HPLMN selector with Access Technology ");break;
//		case 0x6F73:csName = _T("Packet switched location information ");break;
//		case 0x6F78:csName = _T("Access control class ");break;
//		case 0x6F7B:csName = _T("Forbidden PLMNs ");break;
//		case 0x6F7E:csName = _T("Location information "); break;
//		case 0x6F80:csName = _T("Incoming call information ");break;
//		case 0x6F81:csName = _T("Outgoing call information ");break;
//		case 0x6F82:csName = _T("Incoming call timer ");break;
//		case 0x6F83:csName = _T("Outgoing call timer ");break;
//		case 0x6FAD:csName = _T("Administrative data ");break;
//		case 0x6FB1:csName = _T("Voice Group Call Service ");break;
//		case 0x6FB2:csName = _T("Voice Group Call Service Status "); break;
//		case 0x6FB3:csName = _T("Voice Broadcast Service ");break;
//		case 0x6FB4:csName = _T("Voice Broadcast Service Status ");break;
//		case 0x6FB5:csName = _T("Enhanced Multi Level Pre-emption and Priority ");break;
//		case 0x6FB6:csName = _T("Automatic Answer for eMLPP Service ");break;
//		case 0x6FB7:csName = _T("Emergency Call Codes ");break;
//		case 0x6FC3:csName = _T("Key for hidden phone book entries ");break;
//		case 0x6FC4:csName = _T("Network Parameters "); break;
//		case 0x6FC5:csName = _T("PLMN Network Name ");break;
//		case 0x6FC6:csName = _T("Operator Network List ");break;
//		case 0x6FC7:csName = _T("Mailbox Dialling Numbers "); break;
//		case 0x6FC8:csName = _T("Extension 6 ");break;
//		case 0x6FC9:csName = _T("Mailbox Identifier ");break;
//		case 0x6FCA:csName = _T("Message Waiting Indication Status "); break;
//		case 0x6FCB:csName = _T("Call Forwarding Indication Status ");break;
//		case 0x6FCC:csName = _T("Extension 7 "); break;
//		case 0x6FCD:csName = _T("Service Provider Display Information "); break;
//		case 0x6FCE:csName = _T("MMS Notification "); break;
//		case 0x6FCF:csName = _T("Extension 8 "); break;
//		case 0x6FD0:csName = _T("MMS Issuer Connectivity Parameters "); break;
//		case 0x6FD1:csName = _T("MMS User Preferences ");break;
//		case 0x6FD2:csName = _T("MMS User Connectivity Parameters ");break;
//		case 0x6FD3:csName = _T("Network's indication of alerting ");break;
//		case 0x6FD4:csName = _T("Voice Group Call Service Ciphering Algorithm "); break;
//		case 0x6FD5:csName = _T("Voice Broadcast Service Ciphering Algorithm "); break;
//		case 0x6FD6:csName = _T("GBA Bootstrapping parameters "); break;
//		case 0x6FD7:csName = _T("MBMS Service Keys List "); break;
//		case 0x6FD8:csName = _T("MBMS User Key "); break;
//		case 0x6FD9:csName = _T("Equivalent HPLMN "); break;
//		case 0x6FDA:csName = _T("GBA NAF List "); break;
//		case 0x6FDB:csName = _T("EHPLMN Presentation Indication ");	break;
//		case 0x6FDC:csName = _T("Last RPLMN Selection Indication "); break;
//		case 0x6FDD:csName = _T("NAF Key Centre Address "); break;
//		case 0x6FDE:csName = _T("Service Provider Name Icon "); break;
//		case 0x6FDF:csName = _T("PLMN Network Name Icon ");break;
//		case 0x6FE0:csName = _T("In Case of Emergency – Dialling Number");break;
//		case 0x6FE1:csName = _T("In Case of Emergency – Free Format "); break;
//		case 0x6FE2:csName = _T("Network Connectivity Parameters for UICC IP connections "); break;
//		case 0x6FE3:csName = _T("EPS location information ");	break;
//		case 0x6FE4:csName = _T("EPS NAS Security Context "); break;
//		default: bRet = false;break;
//		}
//
//	}
//	return bRet;
//}
//bool GenerateEFNameIn3GPP2    (int iFID,CString &csName,bool bAb)
//{
//	bool bRet = true;
//
//	csName.Empty();
//	if (bAb)
//	{
//		switch(iFID)
//		{
//
//		case 0x6F06:csName = _T("ARR ");break;
//		case 0x6F21:csName = _T("COUNT "); 	break;
//		case 0x6F22:csName = _T("IMSI_M ");break;
//		case 0x6F23:csName = _T("IMSI_T ");break;
//		case 0x6F24:csName = _T("TMSI ");break;
//		case 0x6F25:csName = _T("AH ");break;
//		case 0x6F26:csName = _T("AOP ");break;
//		case 0x6F27:csName = _T("ALOC ");break;
//		case 0x6F28:csName = _T("CDMAHOME ");break;
//		case 0x6F29:csName = _T("ZNREGI ");break;
//		case 0x6F2A:csName = _T("SNREGI ");break;
//		case 0x6F2B:csName = _T("DISTREGI ");break;
//		case 0x6F2C:csName = _T("ACCOLC ");break;
//		case 0x6F2D:csName = _T("TERM ");break;
//		case 0x6F2E:csName = _T("SSCI ");break;
//		case 0x6F2F:csName = _T("ACP ");break;
//		case 0x6F30:csName = _T("PRL ");break;
//		case 0x6F31:csName = _T("UIMID ");break;
//		case 0x6F32:csName = _T("CST ");break;
//		case 0x6F33:csName = _T("SPC ");break;
//		case 0x6F34:csName = _T("OTAPASPC ");break;
//		case 0x6F35:csName = _T("NAMLOCK ");break;
//		case 0x6F36:csName = _T("OTA ");break;
//		case 0x6F37:csName = _T("SP ");break;
//		case 0x6F38:csName = _T("ESNME ");break;
//		case 0x6F3A:csName = _T("LI ");break;
//		case 0x6F3B:csName = _T("FDN ");break;
//		case 0x6F3C:csName = _T("SMS ");break;
//		case 0x6F3D:csName = _T("SMSP ");break;
//		case 0x6F3E:csName = _T("SMSS ");break;
//		case 0x6F3F:csName = _T("SSFC ");break;
//		case 0x6F41:csName = _T("SPN ");break;
//		case 0x6F42:csName = _T("USGIND ");break;
//		case 0x6F43:csName = _T("AD ");break;
//		case 0x6F44:csName = _T("MDN ");break;
//		case 0x6F45:csName = _T("MAXPRL ");break;
//		case 0x6F46:csName = _T("SPCS ");break;
//		case 0x6F47:csName = _T("ECC ");break;
//		case 0x6F48:csName = _T("ME3GPDOPC ");break;
//		case 0x6F49:csName = _T("3GPDOPM ");break;
//		case 0x6F4A:csName = _T("SIPCAP ");break;
//		case 0x6F4B:csName = _T("MIPCAP ");break;
//		case 0x6F4C:csName = _T("SIPUPP ");break;
//		case 0x6F4D:csName = _T("MIPUPP ");break;
//		case 0x6F4E:csName = _T("SIPSP ");break;
//		case 0x6F4F:csName = _T("MIPSP ");break;
//		case 0x6F50:csName = _T("SIPPAPSS ");break;
//		case 0x6F53:csName = _T("PUZL ");break;
//		case 0x6F54:csName = _T("MAXPUZL ");break;
//		case 0x6F55:csName = _T("MECRP ");break;
//		case 0x6F56:csName = _T("HRPDCAP ");break;
//		case 0x6F57:csName = _T("HRPDUPP ");break;
//		case 0x6F58:csName = _T("CSSPR ");break;
//		case 0x6F59:csName = _T("ATC ");break;
//		case 0x6F5A:csName = _T("EPRL ");break;
//		case 0x6F5B:csName = _T("BCSMScfg ");break;
//		case 0x6F5C:csName = _T("BCSMSpref ");break;
//		case 0x6F5D:csName = _T("BCSMStable ");break;
//		case 0x6F5E:csName = _T("BCSMSP ");break;
//		case 0x6F63:csName = _T("BAKPARA ");break;
//		case 0x6F64:csName = _T("UpBAKPARA ");break;
//		case 0x6F65:csName = _T("MMSN ");break;
//		case 0x6F66:csName = _T("EXT8 ");break;
//		case 0x6F67:csName = _T("MMSICP ");break;
//		case 0x6F68:csName = _T("MMSUP ");break;
//		case 0x6F69:csName = _T("MMSUCP ");break;
//		case 0x6F6A:csName = _T("AuthCapability ");break;
//		case 0x6F6B:csName = _T("3GCIK ");break;
//		case 0x6F6C:csName = _T("DCK ");break;
//		case 0x6F6D:csName = _T("GID1 ");break;
//		case 0x6F6E:csName = _T("GID2 ");break;
//		case 0x6F6F:csName = _T("CDMACNL ");break;
//		case 0x6F70:csName = _T("HOME_TAG ");break;
//		case 0x6F71:csName = _T("GROUP_TAG ");break;
//		case 0x6F72:csName = _T("SPECIFIC_TAG ");break;
//		case 0x6F73:csName = _T("CALL_PROMPT ");break;
//		case 0x6F74:csName = _T("SF_EUIMID ");break;
//		case 0x6F75:csName = _T("EST ");break;
//		case 0x6F76:csName = _T("HiddenKey ");break;
//		case 0x6F77:csName = _T("LCSVER ");break;
//		case 0x6F78:csName = _T("LCSCP ");break;
//		case 0x6F79:csName = _T("SDN ");break;
//		case 0x6F7A:csName = _T("EXT2 ");break;
//		case 0x6F7B:csName = _T("EXT3 ");break;
//		case 0x6F7C:csName = _T("ICI ");break;
//		case 0x6F7D:csName = _T("OCI ");break;
//		case 0x6F7E:csName = _T("EXT5 ");break;
//		case 0x6F7F:csName = _T("CCP2 ");break;
//		case 0x6F80:csName = _T("AppLabels ");break;
//		case 0x6F81:csName = _T("Model ");break;
//		case 0x6F82:csName = _T("RC ");break;
//		case 0x6F83:csName = _T("SMSCAP ");break;
//		case 0x6F84:csName = _T("MIPFlags ");break;
//		case 0x6F85:csName = _T("SIPUPPExt ");break;
//		case 0x6F86:csName = _T("MIPUPPExt ");break;
//		case 0x6F87:csName = _T("IPV6CAP ");break;
//		case 0x6F88:csName = _T("TCPConfig ");break;
//		case 0x6F89:csName = _T("DGC ");break;
//		case 0x6F8A:csName = _T("WAPBrowserCP ");break;
//		case 0x6F8B:csName = _T("WAPBrowserBM ");break;
//		case 0x6F8C:csName = _T("MMSConfig ");break;
//		case 0x6F8D:csName = _T("JDL ");break;
//		case 0x6F8E:csName = _T("LBSXTRAConfig ");break	;
//		case 0x6F8F:csName = _T("LBSXS URL ");break	;
//		case 0x6F90:csName = _T("LBSV2 Config ");break;
//		case 0x6F91:csName = _T("LBSV2 PDEADDR ");break	;
//		case 0x6F92:csName = _T("LBSV2MPCADDR ");break;
//		case 0x6F93:csName = _T("BREWDownload ");break;
//		case 0x6F94:csName = _T("BREWTSID ");break;
//		case 0x6F95:csName = _T("BREWSID ");break;
//		case 0x6F96:csName = _T("BREWAEP ");break;
//		default: bRet = false;break;
//
//		}
//
//	}
//	else
//	{
//
//		switch(iFID)
//		{
//
//		case 0x6F06:csName = _T("Access rule reference ");break;
//		case 0x6F25:csName = _T(" Analog Home SID ");break;
//		case 0x6F26:csName = _T(" Analog Operational Parameters ");break;
//		case 0x6F27:csName = _T(" Analog Location and Registration Indicators ");break;
//		case 0x6F28:csName = _T(" CDMA Home SID, NID ");break;
//		case 0x6F29:csName = _T(" CDMA Zone-Based Registration Indicators ");break;
//		case 0x6F2A:csName = _T(" CDMA System-Network Registration Indicators ");break;
//		case 0x6F2B:csName = _T(" CDMA Distance-Based Registration Indicators ");break;
//		case 0x6F2C:csName = _T(" Access Overload Class ACCOLCp ");break;
//		case 0x6F2D:csName = _T(" Call Termination Mode Preferences ");break;
//		case 0x6F2E:csName = _T(" Suggested 1 Slot Cycle Index ");break;
//		case 0x6F2F:csName = _T(" Analog Channel Preferences ");break;
//		case 0x6F30:csName = _T(" Preferred Roaming List ");break;
//		case 0x6F31:csName = _T(" RUIMID ");break;
//		case 0x6F32:csName = _T(" CSIM Service Table ");break;
//		case 0x6F33:csName = _T(" Service Programming Code ");break;
//		case 0x6F34:csName = _T(" OTAPA/SPC_Enabled ");break;
//		case 0x6F35:csName = _T(" NAM_LOCK ");break;
//		case 0x6F36:csName = _T(" OTASP/OTAPA Features ");break;
//		case 0x6F37:csName = _T(" Service Preferences ");break;
//		case 0x6F38:csName = _T(" ESN_ME ");break;
//		case 0x6F3A:csName = _T(" Language Indication ");break;
//		case 0x6F3B:csName = _T(" Fixed Dialling Numbers ");break;
//		case 0x6F3C:csName = _T(" Short Messages ");break;
//		case 0x6F3D:csName = _T(" Short Message Service Parameters ");break;
//		case 0x6F3E:csName = _T(" SMS Status ");break;
//		case 0x6F3F:csName = _T(" Supplementary Services Feature Code Table ");break;
//		case 0x6F41:csName = _T(" CDMA Home Service Provider Name ");break;
//		case 0x6F42:csName = _T(" UIM_ID/SF_EUIMID Usage Indicator ");break;
//		case 0x6F43:csName = _T(" Administrative Data ");break;
//		case 0x6F44:csName = _T(" Mobile Directory Number ");break;
//		case 0x6F45:csName = _T(" Maximum PRL ");break;
//		case 0x6F46:csName = _T(" SPC Status ");break;
//		case 0x6F47:csName = _T(" Emergency Call Codes) ");break;
//		case 0x6F48:csName = _T(" ME 3GPD Operation Capability ");break;
//		case 0x6F49:csName = _T(" 3GPD Operation Mode ");break;
//		case 0x6F4A:csName = _T(" SimpleIP Capability Parameters ");break;
//		case 0x6F4B:csName = _T(" MobileIP Capability Parameters ");break;
//		case 0x6F4C:csName = _T(" SimpleIP User Profile Parameters ");break;
//		case 0x6F4D:csName = _T(" MobileIP User Profile Parameters ");break;
//		case 0x6F4E:csName = _T(" SimpleIP Status Parameters ");break;
//		case 0x6F4F:csName = _T(" MobileIP Status Parameters ");break;
//		case 0x6F50:csName = _T(" SimpleIP PAP SS Parameters ");break;
//		case 0x6F53:csName = _T(" Preferred User Zone List ");break;
//		case 0x6F54:csName = _T(" Maximum PUZL ");break;
//		case 0x6F55:csName = _T(" ME-specific Configuration Request Parameters ");break;
//		case 0x6F56:csName = _T(" HRPD Access Authentication Capability Parameters ");break;
//		case 0x6F57:csName = _T(" HRPD Access Authentication User Profile Parameters ");break;
//		case 0x6F58:csName = _T(" CUR_SSPR_P_REV ");break;
//		case 0x6F59:csName = _T(" Access Terminal Class ");break;
//		case 0x6F5A:csName = _T(" Extended Preferred Roaming List ");break;
//		case 0x6F5B:csName = _T(" Broadcast Short Message Configuration ");break;
//		case 0x6F5C:csName = _T(" Broadcast Short Message Preference ");break;
//		case 0x6F5D:csName = _T(" Broadcast Short Message Table ");break;
//		case 0x6F5E:csName = _T(" Broadcast Short Message Parameter ");break;
//		case 0x6F63:csName = _T(" Currently used BAK Parameters ");break;
//		case 0x6F64:csName = _T(" Updated BAK Parameters ");break;
//		case 0x6F65:csName = _T(" MMS Notification ");break;
//		case 0x6F66:csName = _T(" Extension 8 ");break;
//		case 0x6F67:csName = _T(" MMS Issuer Connectivity Parameters ");break;
//		case 0x6F68:csName = _T(" MMS User Preferences ");break;
//		case 0x6F69:csName = _T(" MMS User Connectivity Parameters ");break;
//		case 0x6F6A:csName = _T(" Authentication Capability ");break;
//		case 0x6F6B:csName = _T(" 3G Cipher and Integrity Keys ");break;
//		case 0x6F6C:csName = _T(" De-Personalization Control Keys ");break;
//		case 0x6F6D:csName = _T(" Group Identifier Level 1 ");break;
//		case 0x6F6E:csName = _T(" Group Identifier Level 2 ");break;
//		case 0x6F6F:csName = _T(" CDMA Co-operative Network List ");break;
//		case 0x6F70:csName = _T(" Home System Tag ");break;
//		case 0x6F71:csName = _T(" Group Tag List ");break;
//		case 0x6F72:csName = _T(" Specific Tag List ");break;
//		case 0x6F73:csName = _T(" Call Prompt List ");break;
//		case 0x6F74:csName = _T(" Short Form EUIMID");break;
//		case  0x6F75:csName=_T("Enabled Service Table");break;
//		case 0x6F76:csName = _T("  Key for hidden phone book entries");break;
//		case 0x6F77:csName = _T(" LCS Protocol Version ");break;
//		case 0x6F78:csName = _T(" LCS Connectivity Parameter ");break;
//		case 0x6F79:csName = _T(" Service Dialling Numbers ");break;
//		case 0x6F7A:csName = _T(" Extension2 ");break;
//		case 0x6F7B:csName = _T(" Extension3 ");break;
//		case 0x6F7C:csName = _T("Incoming Call Information");break;
//		case 0x6F7D:csName = _T(" Outgoing Call Information ");break;
//		case 0x6F7E:csName = _T(" Extension5 ");break;
//		case 0x6F7F:csName = _T(" Capability Configuration Parameters 2 ");break;
//		case 0x6F80:csName = _T(" Application Labels ");break;
//		case 0x6F81:csName = _T(" Device Model Inbreak");break;
//		case 0x6F82:csName = _T(" Root Certificates ");break;
//		case 0x6F83:csName = _T(" SMS Capabilities ");break;
//		case 0x6F84:csName = _T(" MobileIP Flags ");break;
//		case 0x6F85:csName = _T(" SimpleIP User Profile Parameters Extension ");break;
//		case 0x6F86:csName = _T(" MobileIP User Profile Parameters Extension ");break;
//		case 0x6F87:csName = _T(" IPv6 Capabilities ");break;
//		case 0x6F88:csName = _T(" TCP Configurations ");break;
//		case 0x6F89:csName = _T(" Data Generic Configurations ");break;
//		case 0x6F8A:csName = _T(" WAP Browser Connectivity Parameters ");break;
//		case 0x6F8B:csName = _T(" WAP Browser Bookmarks ");break;
//		case 0x6F8C:csName = _T(" MMS Configuration ");break;
//		case 0x6F8D:csName = _T(" Java Download URL ");break;
//		case 0x6F8E:csName = _T(" LBSXTRAConfig");break;
//		case 0x6F8F:csName = _T(" LBSXS URL");break;
//		case 0x6F90:csName = _T(" LBSV2 Config");break;
//		case 0x6F91:csName = _T(" LBSV2 PDE Address");break;
//		case 0x6F92:csName = _T(" LBS V2 MPC Address");break;
//		case 0x6F93:csName = _T(" BREW Download");break;
//		case 0x6F94:csName = _T(" BREW Teleservice ID");break;
//		case 0x6F95:csName = _T(" BREW User ID");break;
//		case 0x6F96:csName = _T(" BREW AEP");break;
//		default: bRet = false;break;
//		}
//
//	}
//	return bRet;
//}
//bool GenerateEFNameInGSM      (int iFID,CString &csName,bool bAb)
//{
//	bool bRet = true;
//
//	csName.Empty();
//	if (bAb)
//	{
//		switch(iFID)
//		{
//		case 0x6F05:csName = _T("LP");break;
//		case 0x6F06:csName = _T("ARR");break;
//		case 0x6F07:csName = _T("IMSI");break;
//		case 0x6F20:csName=_T("Kc");break;	
//		case 0x6F2C:csName=_T("DCK");break;
//		case 0x6F30:csName=_T("PLMNsel");break;
//		case 0x6F31:csName=_T("HPLMN");break;
//		case 0x6F32:csName=_T("CNL");break;
//		case 0x6F37:csName=_T("ACMmax");break;
//		case 0x6F38:csName=_T("SST");break;
//		case 0x6F39:csName=_T("ACM");break;
//		case 0x6F3E:csName=_T("GID1");break;
//		case 0x6F3F:csName=_T("GID2");break;
//		case 0x6F41:csName=_T("PUCT");break;
//		case 0x6F45:csName=_T("CBMI");break;
//		case 0x6F46:csName=_T("SPN");break;
//		case 0x6F48:csName=_T("CBMID");break;
//		case 0x6F50:csName=_T("CBMIR");break;
//		case 0x6F51:csName=_T("NIA");break;
//		case 0x6F52:csName=_T("KcGPRS");break;
//		case 0x6F53:csName=_T("LOCIGPRS");break;
//		case 0x6F54:csName=_T("SUME");break;
//		case 0x6F60:csName = _T("PLMNwAcT ");		break;
//		case 0x6F61:csName = _T("OPLMNwAcT "); break;
//		case 0x6F62:csName = _T("HPLMNwAcT ");break;
//		case 0x6F74:csName=_T("BCCH");break;
//		case 0x6F78:csName=_T("ACC");break;
//		case 0x6F7B:csName=_T("FPLMNS");break;
//		case 0x6F7E:csName=_T("LOCI");break;
//		case 0x6FAD:csName=_T("AD");break;
//		case 0x6FAE:csName=_T("Phase");break;
//		case 0x6FB1:csName=_T("VGCS");break;
//		case 0x6FB2:csName=_T("VGCSS");break;
//		case 0x6FB3:csName=_T("VBS");break;
//		case 0x6FB4:csName=_T("VBSS");break;
//		case 0x6FB5:csName=_T("EMLPP");break;
//		case 0x6FB6:csName=_T("AAeM");break;
//		case 0x6FB7:csName=_T("ECC");break;	
//		case 0x6FD9:csName = _T("EHPLMN "); break;
//		default: bRet = false;break;
//
//		}
//
//	}
//	else
//	{
//
//		switch(iFID)
//		{
//		case 0x6F05:csName = _T("Language preference");break;
//		case 0x6F06:csName = _T("Access rule reference");break;
//		case 0x6F07:csName = _T("International Mobile Subscriber Identity");break;
//		case 0x6F20:csName=_T("Ciphering key Kc");break;	
//		case 0x6F2C:csName=_T("De-personalization Control Keys");break;
//		case 0x6F30:csName=_T("PLMN selector");break;
//		case 0x6F31:csName=_T("HPLMN search period");break;
//		case 0x6F32:csName=_T("Co-operative Network List");break;
//		case 0x6F37:csName=_T("ACM maximum value");break;
//		case 0x6F38:csName=_T("SIM service table");break;
//		case 0x6F39:csName=_T("Accumulated call meter");break;
//		case 0x6F3E:csName=_T("Group Identifier Level 1");break;
//		case 0x6F3F:csName=_T("Group Identifier Level 2");break;
//		case 0x6F41:csName=_T("Price per unit and currency table");break;
//		case 0x6F45:csName=_T("Cell broadcast message identifier selection");break;
//		case 0x6F46:csName=_T("Service Provider Name");break;
//		case 0x6F48:csName=_T("Cell Broadcast Message Identifier for Data Download");break;
//		case 0x6F50:csName=_T("Cell broadcast message identifier range selection");break;
//		case 0x6F51:csName=_T("Network's Indication of Alerting");break;
//		case 0x6F52:csName=_T("GPRS Ciphering key KcGPRS");break;
//		case 0x6F53:csName=_T("GPRS location information");break;
//		case 0x6F54:csName=_T("SetUpMenu Elements");break;
//		case 0x6F60:csName = _T("User controlled PLMN selector with Access Technology ");		break;
//		case 0x6F61:csName = _T("Operator controlled PLMN selector with Access Technology "); break;
//		case 0x6F62:csName = _T("HPLMN selector with Access Technology ");break;
//		case 0x6F74:csName=_T("Broadcast control channels");break;
//		case 0x6F78:csName=_T("Access control class");break;
//		case 0x6F7B:csName=_T("Forbidden PLMNs");break;
//		case 0x6F7E:csName=_T("Location information");break;
//		case 0x6FAD:csName=_T("Administrative data");break;
//		case 0x6FAE:csName=_T("Phase identification");break;
//		case 0x6FB1:csName=_T("Voice Group Call Service");break;
//		case 0x6FB2:csName=_T("Voice Group Call Service Status");break;
//		case 0x6FB3:csName=_T("Voice Broadcast Service");break;
//		case 0x6FB4:csName=_T("Voice Broadcast Service Status");break;
//		case 0x6FB5:csName=_T("enhanced Multi Level Pre-emption and Priority");break;
//		case 0x6FB6:csName=_T("Automatic Answer for eMLPP Service");break;
//		case 0x6FB7:csName=_T("Emergency Call Codes");break;	
//		case 0x6FD9:csName = _T("Equivalent HPLMN "); break;
//		default: bRet = false;break;
//		}
//
//	}
//	return bRet;
//}
//bool GenerateEFNameInCDMA     (int iFID,CString &csName,bool bAb)
//{
//	bool bRet = true;
//
//	csName.Empty();
//	if (bAb)
//	{
//		switch(iFID)
//		{
//		case 0x6F06:csName=_T("ARR");break;
//		case 0x6F21:csName=_T("COUNT");break;
//		case 0x6F22:csName=_T("IMSI_M");break;
//		case 0x6F23:csName=_T("IMSI_T");break;
//		case 0x6F24:csName=_T("TMSI");break;
//		case 0x6F25:csName=_T("AH");break;
//		case 0x6F26:csName=_T("AOP");break;
//		case 0x6F27:csName=_T("ALOC");break;
//		case 0x6F28:csName=_T("CDMAHOME");break;
//		case 0x6F29:csName=_T("ZNREGI");break;
//		case 0x6F2A:csName=_T("SNREGI");break;
//		case 0x6F2B:csName=_T("DISTREGI");break;
//		case 0x6F2C:csName=_T("ACCOLC");break;
//		case 0x6F2D:csName=_T("TERM");break;
//		case 0x6F2E:csName=_T("SSCI");break;
//		case 0x6F2F:csName=_T("ACP");break;
//		case 0x6F30:csName=_T("PRL");break;
//		case 0x6F31:csName=_T("UIMID");break;
//		case 0x6F32:csName=_T("CPC");break;
//		case 0x6F33:csName=_T("SPC");break;
//		case 0x6F34:csName=_T("OTAPASPC");break;
//		case 0x6F35:csName=_T("NAMLOCK");break;
//		case 0x6F36:csName=_T("OTA");break;
//		case 0x6F37:csName=_T("SP");break;
//		case 0x6F38:csName=_T("ESNME");break;
//		case 0x6F39:csName=_T("UIMV");break;
//		case 0x6F3A:csName=_T("LI");break;
//		case 0x6F3B:csName=_T("FDN");break;
//		case 0x6F3C:csName=_T("SMS");break;
//		case 0x6F3D:csName=_T("SMSP");break;
//		case 0x6F3E:csName=_T("SMSS");break;
//		case 0x6F3F:csName=_T("SSFC");break;
//		case 0x6F41:csName=_T("SPN");break;
//		case 0x6F42:csName=_T("USGIND");break;
//		case 0x6F43:csName=_T("AD");break;
//		case 0x6F44:csName=_T("MDN");break;
//		case 0x6F45:csName=_T("MAXPRL");break;
//		case 0x6F46:csName=_T("SPCS");break;
//		case 0x6F47:csName=_T("ECC");break;
//		case 0x6F48:csName=_T("ME3GPDOPC");break;
//		case 0x6F49:csName=_T("3GPDOPM");break;
//		case 0x6F4A:csName=_T("SIPCAP");break;
//		case 0x6F4B:csName=_T("MIPCAP");break;
//		case 0x6F4C:csName=_T("SIPUPP");break;
//		case 0x6F4D:csName=_T("MIPUPP");break;
//		case 0x6F4E:csName=_T("SIPSP");break;
//		case 0x6F4F:csName=_T("MIPSP");break;
//		case 0x6F50:csName=_T("SIPPAPSS");break;
//		case 0x6F53:csName=_T("PUZL");break;
//		case 0x6F54:csName=_T("MAXPUZL");break;
//		case 0x6F55:csName=_T("MECRP");break;
//		case 0x6F56:csName=_T("HRPDCAP");break;
//		case 0x6F57:csName=_T("HRPDUPP");break;
//		case 0x6F58:csName=_T("CSSPR");break;
//		case 0x6F59:csName=_T("ATC");break;
//		case 0x6F5A:csName=_T("EPRL");break;
//		case 0x6F5B:csName=_T("BCSMScfg");break;
//		case 0x6F5C:csName=_T("BCSMSpref");break;
//		case 0x6F5D:csName=_T("BCSMStable");break;
//		case 0x6F5E:csName=_T("BCSMSP");break;
//		case 0x6F5F:csName=_T("IMPI");break;
//		case 0x6F60:csName=_T("DOMAIN");break;
//		case 0x6F61:csName=_T("IMPU");break;
//		case 0x6F62:csName=_T("PCSCF");break;
//		case 0x6F63:csName=_T("BAKPARA");break;
//		case 0x6F64:csName=_T("UpBAKPARA");break;
//		case 0x6F65:csName=_T("MMSN");break;
//		case 0x6F66:csName=_T("MMSICP");break;
//		case 0x6F67:csName=_T("MMSICP");break;
//		case 0x6F68:csName=_T("EXT8");break;
//		case 0x6F69:csName=_T("MMSUCP");break;
//		case 0x6F6A:csName=_T("AuthCapability");break;
//		case 0x6F6B:csName=_T("3GCIK");break;
//		case 0x6F6C:csName=_T("DCK");break;
//		case 0x6F6D:csName=_T("GID1");break;
//		case 0x6F6E:csName=_T("GID2");break;
//		case 0x6F6F:csName=_T("CDMACNL");break;
//		case 0x6F74:csName=_T("SF_EUIMID");break;
//		case 0x6F76:csName=_T("SMSCAP");break;
//		case 0x6F79:csName=_T("TCPConfig");break;
//		case 0x6F7A:csName=_T("DGC");break;
//		case 0x6F7B:csName=_T("WAPBrowserCP");break;
//		case 0x6F7C:csName=_T("WAPBrowserBM");break;
//		case 0x6F7D:csName=_T("SIPUPPExt");break;
//		case 0x6F7E:csName=_T("MMSConfig");break;
//		case 0x6F7F:csName=_T("JDL");break;
//		case 0x6F81:csName=_T("BREWDownload");break;
//		case 0x6F82:csName=_T("BREWTSID");break;
//		case 0x6F83:csName=_T("BREWAEP");break;
//		case 0x6F84:csName=_T("LBSXTRAConfig");break;
//		case 0x6F85:csName=_T("LBSXSURL");break;
//		case 0x6F86:csName=_T("LBSV2Config");break;
//		case 0x6F87:csName=_T("LBSV2PDEADDR");break;
//		case 0x6F88:csName=_T("LBSV2MPCADDR");break;
//		case 0x6F89:csName=_T("BREWAEP");break;
//		case 0x6F90:csName=_T("Model");break;
//		case 0x6F92:csName=_T("AppLabels");break;
//		default: bRet = false;break;
//
//		}
//
//	}
//	else
//	{
//
//		switch(iFID)
//		{
//		case 0x6F06:csName= _T(" ARR ");break;
//		case 0x6F21:csName= _T(" Call Count ");break;
//		case 0x6F22:csName= _T(" IMSI_M ");break;
//		case 0x6F23:csName= _T(" IMSI_T ");break;
//		case 0x6F24:csName= _T(" TMSI ");break;
//		case 0x6F25:csName= _T(" Analog Home SID ");break;
//		case 0x6F26:csName= _T(" Analog Operational Parameters ");break;
//		case 0x6F27:csName= _T(" Analog Location and Registration Indicators ");break;
//		case 0x6F28:csName= _T(" CDMA Home SID, NID ");	break;
//		case 0x6F29:csName= _T(" CDMA Zone-Based Registration Indicators ");	break;
//		case 0x6F2A:csName= _T(" CDMA System-Network Registration Indicators ");break;
//		case 0x6F2B:csName= _T(" CDMA Distance-Based Registration Indicators ");break;
//		case 0x6F2C:csName= _T(" Access Overload Class ACCOLCp ");break;
//		case 0x6F2D:csName= _T(" Call Termination Mode Preferences ");break;
//		case 0x6F2E:csName= _T(" Suggested 1 Slot Cycle Index ");break;
//		case 0x6F2F:csName= _T(" Analog Channel Preferences ");break;
//		case 0x6F30:csName= _T(" Preferred Roaming List ");break;
//		case 0x6F31:csName= _T(" RUIMID ");break;
//		case 0x6F32:csName= _T(" CMDA Service Table ");break;
//		case 0x6F33:csName= _T(" Service Programming Code ");break;
//		case 0x6F34:csName= _T(" OTAPA/SPC_Enabled ");break;
//		case 0x6F35:csName= _T(" NAM_LOCK ");break;
//		case 0x6F36:csName= _T(" OTASP/OTAPA Features ");break;
//		case 0x6F37:csName= _T(" Service Preferences ");break;
//		case 0x6F38:csName= _T(" ESN_ME ");break;
//		case 0x6F39:csName= _T(" UIM Version "); break;
//		case 0x6F3A:csName= _T(" Language Indication ");break;
//		case 0x6F3B:csName= _T(" Fixed Dialling Numbers ");	break;
//		case 0x6F3C:csName= _T(" Short Messages ");break;
//		case 0x6F3D:csName= _T(" Short Message Service Parameters ");break;
//		case 0x6F3E:csName= _T(" SMS Status ");break;
//		case 0x6F3F:csName= _T(" Supplementary Services Feature Code Table ");break;
//		case 0x6F41:csName= _T(" CDMA Home Service Provider Name ");break;
//		case 0x6F42:csName= _T(" UIM_ID/SF_EUIMID Usage Indicator ");break;
//		case 0x6F43:csName= _T(" Administrative Data ");break;
//		case 0x6F44:csName= _T(" Mobile Directory Number ");break;
//		case 0x6F45:csName= _T(" Maximum PRL ");break;
//		case 0x6F46:csName= _T(" SPC Status ");break;
//		case 0x6F47:csName= _T(" Emergency Call Codes) ");break;
//		case 0x6F48:csName= _T(" ME 3GPD Operation Capability ");break;
//		case 0x6F49:csName= _T(" 3GPD Operation Mode ");break;
//		case 0x6F4A:csName= _T(" SimpleIP Capability Parameters ");break;
//		case 0x6F4B:csName= _T(" MobileIP Capability Parameters ");break;
//		case 0x6F4C:csName= _T(" SimpleIP User Profile Parameters ");break;
//		case 0x6F4D:csName= _T(" MobileIP User Profile Parameters ");break;
//		case 0x6F4E:csName= _T(" SimpleIP Status Parameters ");break;
//		case 0x6F4F:csName= _T(" MobileIP Status Parameters ");break;
//		case 0x6F50:csName= _T(" SimpleIP PAP SS Parameters ");break;
//		case 0x6F53:csName= _T(" Preferred User Zone List ");break;
//		case 0x6F54:csName= _T(" Maximum PUZL ");break;
//		case 0x6F55:csName= _T(" ME-specific Configuration Request Parameters ");break;
//		case 0x6F56:csName= _T(" HRPD Access Authentication Capability Parameters ");break;
//		case 0x6F57:csName= _T(" HRPD Access Authentication User Profile Parameters ");break;
//		case 0x6F58:csName= _T(" CUR_SSPR_P_REV ");break;
//		case 0x6F59:csName= _T(" Access Terminal Class ");break;
//		case 0x6F5A:csName= _T(" Extended Preferred Roaming List ");break;
//		case 0x6F5B:csName= _T(" Broadcast Short Message Configuration ");break;
//		case 0x6F5C:csName= _T(" Broadcast Short Message Preference ");break;
//		case 0x6F5D:csName= _T(" Broadcast Short Message Table ");	break;
//		case 0x6F5E:csName= _T(" Broadcast Short Message Parameter ");	break;
//		case 0x6F5F:csName=_T("IMS private 1 user identity");break;
//		case 0x6F60:csName=_T("Home Network 1 Domain Name");break;
//		case 0x6F61:csName=_T("IMS public 1 user identity");break;
//		case 0x6F62:csName=_T("Proxy Call Session 1 Control Function");break;
//		case 0x6F63:csName= _T(" Currently used BAK Parameters ");	break;
//		case 0x6F64:csName= _T(" Updated BAK Parameters ");	break;
//		case 0x6F65:csName= _T(" MMS Notification ");	break;
//		case 0x6F66:csName=_T("Extension 8");break;
//		case 0x6F67:csName= _T(" MMS Issuer Connectivity Parameters ");break;
//		case 0x6F68:csName= _T(" MMS User Preferences ");break;
//		case 0x6F69:csName=_T("MMS User Connectivity Parameters");break;
//		case 0x6F6A:csName=_T("Authentication Capability");break;
//		case 0x6F6B:csName=_T("3G Cipher and Integrity Keys");break;
//		case 0x6F6C:csName=_T("De-Personalization Control Keys");break;
//		case 0x6F6D:csName= _T(" Group Identifier Level 1 ");break;
//		case 0x6F6E:csName= _T(" Group Identifier Level 2 ");break;
//		case 0x6F6F:csName=_T("CDMA Co-operative Network List");break;
//		case 0x6F74:csName=_T("Short Form EUIMID");break;
//		case 0x6F76:csName= _T(" SMS Capabilities ");break;
//		case 0x6F79:csName= _T(" TCP Configurations ");break;
//		case 0x6F7A:csName= _T(" Data Generic Configurations ");break;
//		case 0x6F7B:csName= _T(" WAP Browser Connectivity Parameters ");break;
//		case 0x6F7C:csName= _T(" WAP Browser Bookmarks ");break;
//		case 0x6F7D:csName= _T(" SimpleIP User Profile Parameters Extension ");break;
//		case 0x6F7E:csName= _T(" MMS Configuration ");break;
//		case 0x6F7F:csName= _T(" Java Download URL ");break;
//		case 0x6F81:csName= _T(" BREW Download");break;
//		case 0x6F82:csName= _T(" BREW Teleservice ID");break;
//		case 0x6F83:csName= _T(" BREW AEP");break;
//		case 0x6F84:csName= _T(" LBSXTRAConfig");break;
//		case 0x6F85:csName= _T(" LBSXS URL");break;
//		case 0x6F86:csName= _T(" LBSV2 Config");break;
//		case 0x6F87:csName= _T(" LBSV2 PDE Address");break;
//		case 0x6F88:csName= _T(" LBS V2 MPC Address");break;
//		case 0x6F89:csName= _T(" BREW AEP");break;
//		case 0x6F90:csName= _T(" Device Model Inbreak")	;
//		case 0x6F92:csName= _T(" Application Labels ");break	;
//
//		default: bRet = false;break;
//		}
//
//	}
//	return bRet;
//}
//
//bool GenerateEFNameInPhoneBook(int iFID,CString &csName,bool bAb)
//{
//
//	bool bRet = true;
//
//	csName.Empty();
//	if (bAb)
//	{
//		switch(iFID)
//		{
//		case 0x4F22:csName = _T("PSC");break;
//		case 0x4F23:csName = _T("CC");break;
//		case 0x4F24:csName = _T("PUID");break;
//		case 0x4F30:csName = _T("PBR");break;
//		default: bRet = false;break;
//
//		}
//
//	}
//	else
//	{
//
//		switch(iFID)
//		{
//		case 0x4F22:csName = _T("Phone book synchronisation counter");break;
//		case 0x4F23:csName = _T("Change counter");break;
//		case 0x4F24:csName = _T("Previous unique identifier");break;
//		case 0x4F30:csName = _T("Phone book reference file");break;
//		default: bRet = false;break;
//		}
//
//	}
//	return bRet;
//}
//
//bool GenerateEFNameInMultiMedia(int iFID,CString &csName,bool bAb)
//{
//	bool bRet = true;
//
//	csName.Empty();
//	if (bAb)
//	{
//		switch(iFID)
//		{
//		case 0x4F47:csName = _T("MML");break;
//		case 0x4F48:csName = _T("MMDF");break;
//		default: bRet = false;break;
//
//		}
//
//	}
//	else
//	{
//
//		switch(iFID)
//		{
//		case 0x4F47:csName = _T("Multimedia Messages List");break;
//		case 0x4F48:csName = _T("Multimedia Messages Data File");break;
//		default: bRet = false;break;
//
//		}
//
//	}
//	return bRet;
//
//}
//bool GenerateEFNameInMMSS      (int iFID,CString &csName,bool bAb)
//{
//	bool bRet = true;
//	csName.Empty();
//	if (bAb)
//	{
//		switch(iFID)
//		{
//		case 0x4F20:csName = _T("MLPL");break;
//		case 0x4F21:csName = _T("MSPL");break;
//		default: bRet = false;break;
//
//		}
//
//	}
//	else
//	{
//
//		switch(iFID)
//		{
//		case 0x4F20:csName = _T("MLPL");break;
//		case 0x4F21:csName = _T("MSPL");break;
//		default: bRet = false;break;
//		}
//
//	}
//	return bRet;
//
//}
//
//bool GenerateEFNameInGSMAccess (int iFID,CString &csName,bool bAb)
//{
//	bool bRet = true;
//	csName.Empty();
//	if (bAb)
//	{
//		switch(iFID)
//		{
//		case 0x4F20:csName = _T("Kc");break;
//		case 0x4F52:csName = _T("KcGPRS");break;
//		case 0x4F63:csName = _T("CPBCCH");break;
//		case 0x4F64:csName = _T("invSCAN");break;
//		default: bRet = false;break;
//
//		}
//
//	}
//	else
//	{
//
//		switch(iFID)
//		{
//		case 0x4F20:csName = _T("GSM Ciphering key Kc");break;
//		case 0x4F52:csName = _T("GPRS Ciphering key KcGPRS");break;
//		case 0x4F63:csName = _T("CPBCCH Information");break;
//		case 0x4F64:csName = _T("Investigation Scan");break;
//		default: bRet = false;break;
//		}
//
//	}
//	return bRet;
//}
//bool GenerateEFNameInMExE      (int iFID,CString &csName,bool bAb)
//{
//	bool bRet = true;
//	csName.Empty();
//	if (bAb)
//	{
//		switch(iFID)
//		{
//		case 0x4F40:csName = _T("MExE-ST");break;
//		case 0x4F41:csName = _T("ORPK");break;
//		case 0x4F42:csName = _T("ARPK");break;
//		case 0x4F43:csName = _T("TPRK");break;
//		default: bRet = false;break;
//
//		}
//
//	}
//	else
//	{
//
//		switch(iFID)
//		{
//		case 0x4F40:csName = _T("MExE Service table");break;
//		case 0x4F41:csName = _T("Operator Root Public Key");break;
//		case 0x4F42:csName = _T("Administrator Root Public Key");break;
//		case 0x4F43:csName = _T("Third Party Root Public Key");break;
//		default: bRet = false;break;
//		}
//
//	}
//	return bRet;
//}
//bool GenerateEFNameInWLAN      (int iFID,CString &csName,bool bAb)
//{
//	bool bRet = true;
//	csName.Empty();
//	if (bAb)
//	{
//		switch(iFID)
//		{
//
//		case 0x4F41:csName = _T("Pseudo");break;
//		case 0x4F42:csName = _T("UPLMNWLAN");break;
//		case 0x4F43:csName = _T("0PLMNWLAN");break;
//		case 0x4F44:csName = _T("UWSIDL");break;
//		case 0x4F45:csName = _T("OWSIDL");break;
//		case 0x4F46:csName = _T("WRI");break;
//		case 0x4F47:csName = _T("HWSIDL");break;
//		case 0x4F48:csName = _T("WEHPLMNPI");break;
//		case 0x4F49:csName = _T("WHPI");break;
//		case 0x4F4A:csName = _T("WLRPLMN");break;
//		case 0x4F4B:csName = _T("HPLMNDAI");break;
//		default: bRet = false;break;
//
//		}
//
//	}
//	else
//	{
//
//		switch(iFID)
//		{
//		case 0x4F41:csName = _T("Pseudonym");break;
//		case 0x4F42:csName = _T("User controlled PLMN selector for I-WLAN Access");break;
//		case 0x4F43:csName = _T("Operator controlled PLMN selector for I-WLAN Access");break;
//		case 0x4F44:csName = _T("User controlled WLAN Specific IDentifier List");break;
//		case 0x4F45:csName = _T("Operator controlled WLAN Specific IDentifierList");break;
//		case 0x4F46:csName = _T("WLAN Reauthentication Identity");break;
//		case 0x4F47:csName = _T("Home I-WLAN Specific Identifier List");break;
//		case 0x4F48:csName = _T("I-WLAN Equivalent HPLMN Presentation Indication");break;
//		case 0x4F49:csName = _T("I-WLAN HPLMN Priority Indication");break;
//		case 0x4F4A:csName = _T("I-WLAN Last Registered PLMN");break;
//		case 0x4F4B:csName = _T("HPLMN Direct Access Indicator");break;
//		default: bRet = false;break;
//		}
//
//	}
//	return bRet;
//
//}
//bool GenerateEFNameInHNB       (int iFID,CString &csName,bool bAb)
//{
//
//	bool bRet = true;
//	csName.Empty();
//	if (bAb)
//	{
//		switch(iFID)
//		{
//		case 0x4F81:csName = _T("ACSGL");break;
//		case 0x4F82:csName = _T("CSGI");break;
//		case 0x4F83:csName = _T("HNBN");break;
//		default: bRet = false;break;
//
//		}
//
//	}
//	else
//	{
//
//		switch(iFID)
//		{
//		case 0x4F81:csName = _T("Allowed CSG Lists");break;
//		case 0x4F82:csName = _T("CSG Indication");break;
//		case 0x4F83:csName = _T("Home (e)NodeB Name");break;
//		default: bRet = false;break;
//		}
//
//	}
//	return bRet;
//}
//
//bool GenerateEFNameInSoLSA     (int iFID,CString &csName,bool bAb)
//{
//	bool bRet = true;
//	csName.Empty();
//	if (bAb)
//	{
//		switch(iFID)
//		{
//		case 0x4F30:csName = _T("SAI");break;
//		case 0x4F31:csName = _T("SLL");break;
//		default: bRet = false;break;
//
//		}
//
//	}
//	else
//	{
//
//		switch(iFID)
//		{
//		case 0x4F30:csName = _T("SAI");break;
//		case 0x4F31:csName = _T("SLL");break;
//		default: bRet = false;break;
//		}
//
//	}
//	return bRet;
//
//}
//bool GenerateEFNameInBCAST     (int iFID,CString &csName,bool bAb)
//{
//	return false;
//}
//bool GenerateEFNameInGRAPHICS  (int iFID,CString &csName,bool bAb)
//{
//	bool bRet = true;
//	csName.Empty();
//	if (bAb)
//	{
//		switch(iFID)
//		{
//		case 0x4F20:csName = _T("IMG");break;
//		default: bRet = false;break;
//
//		}
//
//	}
//	else
//	{
//
//		switch(iFID)
//		{
//		case 0x4F20:csName = _T("IMG");break;
//		default: bRet = false;break;
//		}
//
//	}
//	return bRet;
//}
//
//int Try2GetFileMark(CString csPath,int iPMark)
//{
//	int iLength = csPath.GetLength();
//	int iOffest = 0;
//	int iCurMark = iPMark;
//	int iFID;
//	for (int i = 0 ; i < iLength ; i+=4)
//	{
//		iFID = _CString2Int(csPath.Mid(i,4));
//		switch(iCurMark)
//		{
//		case _DEF_Tele:
//			if     (iFID == 0x5F50) iCurMark = _DEF_Tele;
//			else if(iFID == 0x5F3A) iCurMark = _DEF_PHONEBOOK;
//			else if(iFID == 0x5F3B) iCurMark = _DEF_MULTIMEDIA;
//			else if(iFID == 0x5F3C) iCurMark = _DEF_MMSS;		
//			else iCurMark = _DEF_Tele;	
//			break;
//
//
//		case _DEF_3GPP:
//			switch(iFID)
//			{
//			case 0x5F3B :iCurMark = _DEF_GSMACCESS;break;
//			case 0x5F3C :iCurMark = _DEF_MExE;break;
//			case 0x5F40 :iCurMark = _DEF_WLAN;break;
//			case 0x5F50 :iCurMark = _DEF_HNB;break;
//			case 0x5F70 :iCurMark = _DEF_SoLSA;break;
//			case 0x5F80 :iCurMark = _DEF_BCAST;break;
//			default: iCurMark = _DEF_3GPP;break;
//			}break;
//
//		default:
//			switch(iFID)
//			{
//
//			case 0x7F10:iCurMark  = _DEF_Tele;break;
//			case 0x7F20:iCurMark  = _DEF_GSM;break;
//			case 0x7FF0:iCurMark  = _DEF_3GPP;break;
//			case 0x7FFF:iCurMark  = _DEF_3GPP;break;
//			case 0x7F25:iCurMark  = _DEF_CDMA;break;
//			case 0x7F21:iCurMark  = _DEF_3GPP2;break;
//			default:iCurMark      = _DEF_Card;break;
//
//			}
//			break;
//		}
//	}
//	return iCurMark;
//
//}
//
//bool Try2GenerateFileName(int iMark,int iFID,CString& csName,bool bAb)
//{
//	bool bRet = true;
//	switch(iMark)
//	{
//	case _DEF_Card:bRet =GenerateEFNameInMF(iFID,csName,bAb);break;
//	case _DEF_GSM :bRet =GenerateEFNameInGSM(iFID,csName,bAb);break; 
//	case _DEF_CDMA:bRet =GenerateEFNameInCDMA(iFID,csName,bAb);break;
//	case _DEF_Tele:bRet =GenerateEFNameInTelecom(iFID,csName,bAb);break; 
//	case _DEF_3GPP:bRet =GenerateEFNameIn3GPP(iFID,csName,bAb);break; 
//	case _DEF_3GPP2:bRet =GenerateEFNameIn3GPP2(iFID,csName,bAb);break; 
//	case _DEF_PHONEBOOK:bRet =GenerateEFNameInPhoneBook(iFID,csName,bAb);break; 
//	case _DEF_MULTIMEDIA:bRet =GenerateEFNameInMultiMedia(iFID,csName,bAb);break; 
//	case _DEF_MMSS:bRet =GenerateEFNameInMMSS(iFID,csName,bAb);break; 
//	case _DEF_GSMACCESS:bRet =GenerateEFNameInGSMAccess(iFID,csName,bAb);break; 
//	case _DEF_MExE:bRet =GenerateEFNameInMExE(iFID,csName,bAb);break; 
//	case _DEF_WLAN:bRet =GenerateEFNameInWLAN(iFID,csName,bAb);break; 
//	case _DEF_HNB:bRet =GenerateEFNameInHNB(iFID,csName,bAb);break; 
//	case _DEF_SoLSA:bRet =GenerateEFNameInSoLSA(iFID,csName,bAb);break; 
//	case _DEF_BCAST:bRet =GenerateEFNameInBCAST(iFID,csName,bAb);break; 
//	default:bRet = false;
//	}
//	if (!bRet)
//		bRet = _GenerateDFName(iFID,iMark,csName);
//	return bRet;
//}



BOOL _Triple_Des_Encrypt(CString csKey,CString csData,CString&csOutput,int iMod)
{



	unsigned char *ucKey,*ucData,*ucResult;
	int iKeyLen,iDataLen,iResLen;

	iKeyLen  = csKey.GetLength()/2;
	iDataLen = csData.GetLength()/2;
	iResLen  = iDataLen+0x8;

	ucKey    = new unsigned char[iKeyLen];
	ucData   = new unsigned char[iDataLen];
	ucResult = new unsigned char[iResLen];

	iKeyLen  = _CString2UcHex(csKey,ucKey);
	iDataLen = _CString2UcHex(csData,ucData);

	iResLen = triple_des(ucKey,ucData,iDataLen,ucResult,ENCRYPT,iMod,NOISO);

	delete ucKey;
	delete ucData;

	_UcHex2CString(ucResult,iResLen,csOutput);

	return TRUE;

}
BOOL _Triple_Des_Decrypt(CString csKey,CString csData,CString&csOutput,int iMod)
{



	unsigned char *ucKey,*ucData,*ucResult;
	int iKeyLen,iDataLen,iResLen;

	iKeyLen  = csKey.GetLength()/2;
	iDataLen = csData.GetLength()/2;
	iResLen  = iDataLen+0x8;

	ucKey    = new unsigned char[iKeyLen];
	ucData   = new unsigned char[iDataLen];
	ucResult = new unsigned char[iResLen];

	iKeyLen  = _CString2UcHex(csKey,ucKey);
	iDataLen = _CString2UcHex(csData,ucData);

	iResLen = triple_des(ucKey,ucData,iDataLen,ucResult,DECRYPT,iMod,NOISO);

	delete ucKey;
	delete ucData;

	_UcHex2CString(ucResult,iResLen,csOutput);
	return TRUE;

}




#define  _DEF_GETDIR_FAIL    -1
#define  _DEF_OPENFILE_FAIL  -2

#define  _DEF_DFMARK_NOTDF    2 

BOOL GetDFMark(CString csPath,int iParentMark,int* iMark)
{

	int iLength = csPath.GetLength();
	int iOffest = 0;
	int iCurMark = iParentMark;
	int iFID;
	int iRet = TRUE;

	if ((iLength %4)!=0)
		return FALSE;

	for (int i = 0 ; i < iLength ; i+=4)
	{
		iFID = _CString2Int(csPath.Mid(i,4));
		switch(iCurMark)
		{
		case _DEF_Tele:

			switch(iFID)
			{
			case 0x5F50:iCurMark = _DEF_GRAPHICS;break;
			case 0x5F3A:iCurMark = _DEF_PHONEBOOK_GLOBAL;break;
			case 0x5F3B:iCurMark = _DEF_MULTIMEDIA;break;
			case 0x5F3C:iCurMark = _DEF_MMSS;break;
			case 0x5F3D:iCurMark = _DEF_MCPTT;break;
			case 0x5F3E:iCurMark = _DEF_V2X;break;
			default:    iRet     = _DEF_DFMARK_NOTDF;break;

			}
			break;

		case _DEF_3GPP:
			switch(iFID)
			{
			case 0x5F3A :iCurMark = _DEF_PHONEBOOK_LOCA;break;
			case 0x5F3B :iCurMark = _DEF_GSMACCESS;break;
			case 0x5F3C :iCurMark = _DEF_MExE;break;
			case 0x5F40 :iCurMark = _DEF_WLAN;break;
			case 0x5F50 :iCurMark = _DEF_HNB;break;
			case 0x5F70 :iCurMark = _DEF_SoLSA;break;
			case 0x5F80 :iCurMark = _DEF_BCAST;break;
			case 0x5F90 :iCurMark = _DEF_ProSe;break;
			case 0x5FA0 :iCurMark = _DEF_ACDC;break;
			case 0x5FB0 :iCurMark = _DEF_TV;break;
			default:     iRet     = _DEF_DFMARK_NOTDF;break;
			}break;


		default:
			switch(iFID)
			{
			case 0x3F00:iCurMark  = _DEF_Card;break;
			case 0x7F10:iCurMark  = _DEF_Tele;break;
			case 0x7F20:iCurMark  = _DEF_GSM;break;
			case 0x7FF0:iCurMark  = _DEF_3GPP;break;
			case 0x7FFF:iCurMark  = _DEF_3GPP;break;
			case 0x7F25:iCurMark  = _DEF_CDMA;break;
			case 0x7F21:iCurMark  = _DEF_3GPP2;break;
			default:    iRet      = _DEF_DFMARK_NOTDF;break;

			}
			break;
		}
	}

	*iMark = iCurMark;

	return iRet;

}
BOOL GetADFMark(CString csAID,int* iMark)
{
	int iLen = csAID.GetLength();
	if ((iLen>0x20)||
		(iLen<10))
		return FALSE;
	csAID.MakeUpper();
	
	if (csAID.Mid(0,10).Compare(_T("A000000087")) == 0)
		* iMark = _DEF_3GPP;
	else if (csAID.Mid(0,10).Compare(_T("A000000343")) == 0)
		* iMark = _DEF_3GPP2;
	else if ((csAID.Mid(0,10).Compare(_T("A000000009")) == 0)   )
		* iMark = _DEF_ETSI;
	else
		return FALSE;
	return TRUE;
}
int GetReferenceInformation(CString csRoute, int iFID,CString& csName,CString& csAbbr)
{
	CStdioFile CSFFile;
	int iRet ;
	CString csTemp;
	CString csiRoute,csiFID,csiDOC,csPAGE,csPOSITION;

	if (!__GetCurrentDIR(csTemp))
		return -1;

	if (_OpenCSVFile(csTemp+"\\Reference\\ReferenceList.csv",&CSFFile)!=TRUE)
		return -2;

	iRet = CSFFile.ReadString(csTemp);



	while (iRet)
	{
		iRet = CSFFile.ReadString(csTemp);
		if (iRet == FALSE)
			break;

		if (_GetCSVData(csTemp,1,csiRoute)<0)
			continue;
		if (_GetCSVData(csTemp,2,csiFID)<0)
			continue;


		if ((csRoute == csiRoute)&&
			(iFID == _CString2Int(csiFID)))
		{
			if (_GetCSVData(csTemp,3,csName)<0)
				goto RESULE_FALSE;
			if (_GetCSVData(csTemp,4,csAbbr)<0)
				goto RESULE_FALSE;
			goto RESULE_SUCCESS;		
		}
	}



RESULE_FALSE:
	CSFFile.Close();
	return FALSE;

RESULE_SUCCESS:
	CSFFile.Close();
	return TRUE;
}

BOOL GetDFName(int iMark,CString& csName)
{

	switch(iMark)
	{
	case _DEF_Card            :csName = _T("MF");  break;
	case _DEF_GSM             :csName = _T("GSM");break; 
	case _DEF_CDMA            :csName = _T("CDMA");break; 
	case _DEF_Tele            :csName = _T("TELECOM");break; 
	case _DEF_3GPP            :csName = _T("USIM");break; 
	case _DEF_3GPP2           :csName = _T("CSIM");break; 

	case _DEF_PHONEBOOK_LOCA  :csName = _T("PHONEBOOK");break;
	case _DEF_GSMACCESS       :csName = _T("GSM-ACCESS");break;
	case _DEF_MExE            :csName = _T("MExE");break;
	case _DEF_SoLSA           :csName = _T("SoLSA");break;
	case _DEF_WLAN            :csName = _T("WLAN");break;
	case _DEF_HNB             :csName = _T("HNB");break;
	case _DEF_ProSe           :csName = _T("ProSe");break;
	case _DEF_ACDC            :csName = _T("ACDC");break;
	case _DEF_TV              :csName = _T("TV");break;
	case _DEF_GRAPHICS        :csName = _T("GRAPHICS");break;       
	case _DEF_PHONEBOOK_GLOBAL:csName = _T("PHONEBOOK");break;
	case _DEF_MULTIMEDIA      :csName = _T("MULTIMEDIA");break;  
	case _DEF_MMSS            :csName = _T("MMSS");break;  
	case _DEF_MCPTT           :csName = _T("MCPTT");break; 
	case _DEF_V2X             :csName = _T("V2X");break;
	default                   :csName = _T("");
		                       return FALSE;
	}
	return TRUE;
}

BOOL GetFileNameFromReference(int iFID,int iParentMark,CString&csName,bool bIsAbbr)
{

	CString csFileName,csFileAbbr,csRoute;

	if (!GetDFName(iParentMark,csRoute))
		csRoute.Empty();


	if (GetReferenceInformation(csRoute, iFID,csFileName,csFileAbbr)>0)
	{
		if (bIsAbbr)
			csName = csFileAbbr;
		else
		    csName = csFileName;

		return TRUE;

	}

	return FALSE;
}