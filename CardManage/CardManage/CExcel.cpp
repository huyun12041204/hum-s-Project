
#include "StdAfx.h"  
#include "CExcel.h"  


CExcel::CExcel(void)  
{  
	if(!app.CreateDispatch(_T("Excel.Application"),NULL))  
	{  
		AfxMessageBox(_T("启动Excel服务器失败!"));  
	}  
	app.put_Visible(FALSE);
	app.put_UserControl(TRUE);

	lpDisp = NULL;  
}  
CExcel::~CExcel(void)  
{  
	
	app.ReleaseDispatch();  
	books.ReleaseDispatch();  
	book.ReleaseDispatch();  
	sheets.ReleaseDispatch();  
	sheet.ReleaseDispatch();  
	range.ReleaseDispatch();  
	
}  
void CExcel::OpenExcel(CString path)  
{  
	books.AttachDispatch(app.get_Workbooks());  
	COleVariant varPath(path);  
	book.AttachDispatch(books.Add(varPath));  
	sheets.AttachDispatch(book.get_Sheets(),TRUE);  
}  
void CExcel::OpenSheet(CString SheetName)  
{  
	
	COleVariant var2(SheetName);  
	sheet.AttachDispatch(sheets.get_Item(var2),TRUE);  
}  
CString CExcel::GetCellValue(long row,long col)  
{  
	_variant_t varRow(row);  
	_variant_t varCol(col);  
	COleVariant value;  

	range.AttachDispatch(sheet.get_Cells(),TRUE);  
	value=range.get_Item(varRow,varCol);                    //返回的类型是VT_DISPATCH 这是一个指针  
	range.AttachDispatch(value.pdispVal,TRUE);  
	VARIANT value2=range.get_Text();  
	CString strValue= (CString)value2.bstrVal;  
	return strValue;  
}  
CString CExcel::GetCellValueByName(CString rowName,CString colName)  
{  
	COleVariant value;  
	CString strValue;  
	long row=0,col=0;  
	long re_row=0,re_col=0;  
	range.AttachDispatch(sheet.get_Cells(),TRUE);  
	for (row=1,col=1;col<range.get_Column();col++)  
	{  
		value=range.get_Item(_variant_t(row),_variant_t(col));                  //返回的类型是VT_DISPATCH 这是一个指针  
		range.AttachDispatch(value.pdispVal,TRUE);  
		VARIANT value2=range.get_Text();  
		CString strValue=(CString)value2.bstrVal;  
		if (strValue==colName)  
		break;  
	}  
	re_col=col;  
	for (row=1,row=1;row<range.get_Row();row++)  
	{  
		value=range.get_Item(_variant_t(row),_variant_t(col));                  //返回的类型是VT_DISPATCH 这是一个指针  
		range.AttachDispatch(value.pdispVal,TRUE);  
		VARIANT value2=range.get_Text();  
		CString strValue=(CString)value2.bstrVal;  
		if (strValue==rowName)        
			break;  
	}  
	re_row=row;  
	return GetCellValue(re_row,re_col);  
}  


long CExcel::GetSheetCount(void)
{
	//sheets.AttachDispatch(book.get_Sheets());  

	return sheets.get_Count();
}

BOOL CExcel::OpenSheet(long lIndix)
{
	
	COleVariant var2(lIndix);  
	sheet.AttachDispatch(sheets.get_Item(var2)); 

	return TRUE;
	//return CString();
}

void CExcel::CloseExcel(void)
{
	book.Close(COleVariant((short)FALSE),COleVariant(book.get_Name()),COleVariant((short)FALSE));
	books.Close();
	app.Quit();
}


// 获取当前Sheet的列总数
long CExcel::GetCellRowCount(void)
{

	range.AttachDispatch(sheet.get_Cells(),TRUE);  
	return range.get_Row();
}

// 获取当前Sheet的行总数
long CExcel::GetCellColumnCount(void)
{
	range.AttachDispatch(sheet.get_Cells(),TRUE);  
	return range.get_Column();
}
