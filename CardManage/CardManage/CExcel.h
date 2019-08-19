#include "CApplication.h"  
#include "CRange.h"  
#include "CRanges.h"  
#include "CWorkbook.h"  
#include "CWorkbooks.h"  
#include "CWorksheet.h"  
#include "CWorksheets.h"  

#pragma once  
class CExcel  
{  
public:  
	CExcel(void);  
	~CExcel(void);  
	void OpenExcel(CString path);  
	void OpenSheet(CString SheetName);  
	CString GetCellValue(long row,long col);  
	CString GetCellValueByName(CString rowName,CString colName);  
private:  
	CApplication app;  
	CWorkbooks books;  
	CWorkbook book;  
	CWorksheets sheets;  
	CWorksheet sheet;  
	CRange range;  
	LPDISPATCH lpDisp;  
public:
	long GetSheetCount(void);
	BOOL OpenSheet(long lIndix);
	void CloseExcel(void);
	// 获取当前Sheet的列总数
	long GetCellRowCount(void);
	// 获取当前Sheet的行总数
	long GetCellColumnCount(void);
};  

