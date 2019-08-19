
/**********************************************************************
***********************************************************************
****
****      File name:                  UNI_Aut_Utilities.h
****      Creation date (DD.MM.YY):   22.01.01
****      Author:                     fra
****
****      Comment:
****       Header file belonging to UNI_Aut_Utilities.cpp
****
****
****      List of exported functions:
****       s. below
****
****      Revisions:
****       $Log: UNI_Aut_Utilities.h $
****       Revision 1.2  2002/08/09 08:15:39Z  SCHUSTEG
****       New Special Function DecFact
****       Revision 1.1  2001/08/23 07:54:00Z  FrankS
****       Initial revision
****
****
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

#ifndef _UNI_AUT_UTILITIES_
#define _UNI_AUT_UTILITIES_



  #include "Afxtempl.h"//for CArray

  void v_RotateBufferRight(unsigned char*, int, int);
  void v_RotateBufferLeft(unsigned char*, int, int);

  unsigned char uc_ShiftCharRight(unsigned char*);
  unsigned char uc_ShiftCharLeft(unsigned char*);

  unsigned char uc_RotateCharRight(unsigned char, unsigned char);
  unsigned char uc_RotateCharLeft(unsigned char, unsigned char);

  char c_cstring2charPtr(char*, CString);

  CString s_charPtr2cstring(char*, int);

  char c_cstringhex2intPtr(int*, CString);

  CString s_intPtr2CStringHex(int*, int);

  void v_SeparatorParser(CArray<CString, CString&>&, CString, CString);

  void v_IncrementBuffer(unsigned char*, int);

  void v_DecrementBuffer(unsigned char*, int);




#endif