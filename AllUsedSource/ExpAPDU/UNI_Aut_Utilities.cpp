
/**********************************************************************
***********************************************************************
****
****      File name:                  UNI_Aut_Utilities.cpp
****      Creation date (DD.MM.YY):   22.01.01
****      Author:                     fra
****
****      Comment:
****       Contains different utilities
****       
****
****      List of exported functions:
****       s. UNI_AUT_Utilities.cpp
****
****      Revisions:
****       $Log: UNI_Aut_Utilities.cpp $
****       Revision 1.2  2002/08/09 08:19:03Z  SCHUSTEG
****       New Special Function DecFact
****       Revision 1.1  2001/08/23 07:54:32Z  FrankS
****       Initial revision
****
****
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/


#include "stdafx.h"//only in combination with GUI needed
#include "Afxtempl.h"//for CArray
#include "math.h"//for pow



/**********************************************************************
***********************************************************************
**
**      Function name:                     uc_ShiftCharLeft
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Shifts char one bit left. If left bit is shifted out, carry
**       flag is set
**
**
**      List of parameters:
**       pucValue     : ptr to char value
**       Return value : carry flag
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

unsigned char uc_ShiftCharLeft(unsigned char* pucValue)
{
  unsigned char ucCarryFlag = 0;

  ucCarryFlag = (*pucValue) & 128;//mask over data
  *pucValue   = (*pucValue) << 1;//shift left

  return ucCarryFlag/128;

}//end uc_ShiftCharLeft


/**********************************************************************
***********************************************************************
**
**      Function name:                     uc_ShiftCharRight
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Shifts char one bit right. If right bit is shifted out, carry
**       flag is set
**
**
**      List of parameters:
**       pucValue     : ptr to char value
**       Return value : carry flag
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

unsigned char uc_ShiftCharRight(unsigned char* pucValue)
{
  unsigned char ucCarryFlag = 0;

  ucCarryFlag = (*pucValue) & 1;//mask over data
  *pucValue   = (*pucValue) >> 1;//shift right

  return ucCarryFlag;

}//end uc_ShiftCharRight


/**********************************************************************
***********************************************************************
**
**      Function name:                     v_RotateBufferLeft
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Rotates bits through buffer.
**
**
**      List of parameters:
**       pucBuffer    : ptr to buffer
**       iBufferLen   : buffer length
**       iPos         : amount of bit rotation
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void v_RotateBufferLeft(unsigned char* pucBuffer, int iBufferLen, int iPos)
{
  int iLoop1;
  int iLoop2;

  unsigned char ucCarry1Flag = 0;
  unsigned char ucCarry2Flag = 0;


  for(iLoop1 = 0; iLoop1 < iPos; iLoop1++)
  {
    
    for(iLoop2 = iBufferLen - 1 ; iLoop2 >= 0; iLoop2--)
    {


      ucCarry2Flag = uc_ShiftCharLeft(pucBuffer + iLoop2);


      pucBuffer[iLoop2] = pucBuffer[iLoop2] | ucCarry1Flag;      

      ucCarry1Flag = ucCarry2Flag;
      ucCarry2Flag = 0;
      
      if(iLoop2 == 0)//last block changes first block
      {
        pucBuffer[iBufferLen - 1] = pucBuffer[iBufferLen - 1] | ucCarry1Flag;
        ucCarry1Flag = 0;

      }
    }    
  }
}//end v_RotateBufferLeft


/**********************************************************************
***********************************************************************
**
**      Function name:                     v_RotateBufferRight
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Rotates bits through buffer.
**
**
**      List of parameters:
**       pucBuffer    : ptr to buffer
**       iBufferLen   : buffer length
**       iPos         : amount of bit rotation
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void v_RotateBufferRight(unsigned char* pucBuffer, int iBufferLen, int iPos)
{
  int iLoop1;
  int iLoop2;

  unsigned char ucCarry1Flag = 0;
  unsigned char ucCarry2Flag = 0;


  for(iLoop1 = 0; iLoop1 < iPos; iLoop1++)
  {
    
    for(iLoop2 = 0; iLoop2 < iBufferLen; iLoop2++)
    {

      
      ucCarry2Flag = uc_ShiftCharRight(pucBuffer + iLoop2);


      pucBuffer[iLoop2] = pucBuffer[iLoop2] | (ucCarry1Flag * 128);



      ucCarry1Flag = ucCarry2Flag;
      ucCarry2Flag = 0;
      
      if(iLoop2 == iBufferLen - 1)//last block changes first block
      {
        pucBuffer[0] = pucBuffer[0] | (ucCarry1Flag * 128);
        ucCarry1Flag = 0;

      }
    }    
  }
}//end v_RotateBufferRight


/**********************************************************************
***********************************************************************
**
**      Function name:                     uc_RotateCharRight
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Rotates bits through char
**
**
**      List of parameters:
**       ucIn         : input char
**       ucPos        : amount of rotation
**       Return value : rotated char
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

unsigned char uc_RotateCharRight(unsigned char ucIn, unsigned char ucPos)
{
  unsigned char ucLoop;
  unsigned char ucResult    = ucIn;
  unsigned char ucCarryFlag = 0;

  for(ucLoop = 0; ucLoop < ucPos; ucLoop++)
  {
  
    ucCarryFlag = ucResult & 1;//mask over data
    ucResult = ucResult >> 1;//shift right

    if(ucCarryFlag == 1)//bit1 shifted out?
      ucResult = ucResult | 128;//then add bit left side  
  }

  return ucResult;
}//end uc_RotateCharRight


/**********************************************************************
***********************************************************************
**
**      Function name:                     uc_RotateCharLeft
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Rotates bits through char
**
**
**      List of parameters:
**       ucIn         : input char
**       ucPos        : amount of rotation
**       Return value : rotated char
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

unsigned char uc_RotateCharLeft(unsigned char ucIn, unsigned char ucPos)
{
  unsigned char ucLoop;
  unsigned char ucResult    = ucIn;
  unsigned char ucCarryFlag = 0;

  for(ucLoop = 0; ucLoop < ucPos; ucLoop++)
  {
  
    ucCarryFlag = ucResult & 128;//mask over data
    ucResult = ucResult << 1;//shift left

    if(ucCarryFlag == 128)//bit8 shifted out?
      ucResult = ucResult | 1;//then add bit right side  
  }

  return ucResult;
}//end uc_RotateCharLeft


/**********************************************************************
***********************************************************************
**
**      Function name:                     c_cstring2charPtr
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Converts CString to char buffer
**
**
**      List of parameters:
**       pcOutput     : ptr to char buffer
**       sInput       : input CString
**       Return value : errorcode (0:ok, 1:error)
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

char c_cstring2charPtr(char* pcOutput, CString sInput)
{
  int iLoop = 0;
  int iStringLen = 0;
//  char acTempBuffer[0x200];

  CArray<char, char&> TempBuffer;

  iStringLen = sInput.GetLength();

  TempBuffer.SetSize(iStringLen);
  
/*
  sInput = "01ef";
     01      ef      <- stringvalue
    /  \    /  \     <- step1: convert string sign to ascii values in char array
   30  31  65  66    
    |   |   |   |    <- step2: convert ascii value to corresponding numeric value in char array
    0   1   e   f    <- numbervalue
     \ /     \ /     <- step3: convert 2byte values to resulting 1byte value saved to passed address
      1       ef
*/

  //1. step  
  sInput.MakeLower();//all hex letters will transformed to lower letters

  for(iLoop = 0; iLoop < iStringLen; iLoop++)
    TempBuffer[iLoop] = sInput[iLoop];



  //2. step
  for(iLoop = 0; iLoop < iStringLen; iLoop++)
  {
    if(TempBuffer[iLoop] >= 0x30 && TempBuffer[iLoop] <= 0x39)
    {
      TempBuffer[iLoop] = TempBuffer[iLoop] - 0x30;
    }
    else
    {
      if(TempBuffer[iLoop] >= 0x61 && TempBuffer[iLoop] <= 0x66)
      {
        TempBuffer[iLoop] = TempBuffer[iLoop] - 0x57;    
      }
      else//digit neither [0;9] nor [a;f]
      {
        return 1;
      }
    }
  }

  //3. step
  for(iLoop = 0; iLoop < iStringLen/2; iLoop++)
  {
      pcOutput[iLoop] = TempBuffer[2*iLoop]*16 + TempBuffer[2*iLoop + 1];
  }

  return 0;

}//end c_cstring2charPtr


/**********************************************************************
***********************************************************************
**
**      Function name:                     s_charPtr2cstring
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Converts char buffer to CString
**
**
**      List of parameters:
**       pcBuffer     : ptr to char buffer
**       iDataLen     : buffer length
**       Return value : CString result
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

CString s_charPtr2cstring(char* pcBuffer, int iDataLen)
{

  int iLoop;
  char acTempArray[3];

  acTempArray[2]  = 0;//string end
  CString sResult = "";


  for(iLoop = 0; iLoop < iDataLen; iLoop++)
  {    
    sprintf(acTempArray, "%2.2x", (unsigned char)pcBuffer[iLoop]);
    sResult += acTempArray;
  } 
  return sResult;

}//end s_charPtr2cstring


/**********************************************************************
***********************************************************************
**
**      Function name:                     c_cstringhex2intPtr
**      Creation date (DD.MM.YY):          25.01.01
**      Author:                            fra
**
**      Comment:
**       Converts CString to int value.
**       Example: "01ef" -> 1ef
**
**
**      List of parameters:
**       piOutput     : ptr to int
**       sInput       : input CString
**       Return value : errorcode (0:ok, 1:error)
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

char c_cstringhex2intPtr(int* piOutput, CString sInput)
{

  int iLoop = 0;
  int iStringLen = 0;


  CArray<char, char&> TempBuffer;

  iStringLen = sInput.GetLength();

  TempBuffer.SetSize(iStringLen);
  

//sInput = "01ef";
//   01      ef      <- stringvalue
//  /  \    /  \     <- step1: convert string sign to ascii values in char array
// 30  31  65  66    
//  |   |   |   |    <- step2: convert ascii value to corresponding numeric value in char array
//  0   1   e   f    <- numbervalue
//   \ /     \ /     <- step3: convert 2byte values to resulting 1byte value saved to passed address
//    1       ef

  //1. step  
  sInput.MakeLower();//all hex letters will transformed to lower letters

  for(iLoop = 0; iLoop < iStringLen; iLoop++)
    TempBuffer[iLoop] = sInput[iLoop];



  //2. step
  for(iLoop = 0; iLoop < iStringLen; iLoop++)
  {
    if(TempBuffer[iLoop] >= 0x30 && TempBuffer[iLoop] <= 0x39)
    {
      TempBuffer[iLoop] = TempBuffer[iLoop] - 0x30;
    }
    else
    {
      if(TempBuffer[iLoop] >= 0x61 && TempBuffer[iLoop] <= 0x66)
      {
        TempBuffer[iLoop] = TempBuffer[iLoop] - 0x57;    
      }
      else//digit neither [0;9] nor [a;f]
      {
        return 1;
      }
    }
  }

  //3. step

  for(iLoop = 0; iLoop < iStringLen; iLoop++)
  {
    *piOutput += TempBuffer[iLoop] * (int)pow((double)16, iStringLen - 1 - iLoop);
      
  }

  return 0;

}//end c_cstringhex2intPtr


/**********************************************************************
***********************************************************************
**
**      Function name:                     s_intPtr2CStringHex
**      Creation date (DD.MM.YY):          25.01.01
**      Author:                            fra
**
**      Comment:
**       Converts int values from buffer to CString
**
**
**      List of parameters:
**       piBuffer     : ptr to int buffer
**       iDataLen     : buffer length
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

CString s_intPtr2CStringHex(int* piBuffer, int iDataLen)
{

  int iLoop;
  char acTempArray[2000];

  memset(acTempArray, 0, 2000);//for string end

  CString sResult = "";


  for(iLoop = 0; iLoop < iDataLen; iLoop++)
  {    
    //sprintf(acTempArray, "%4.4x", piBuffer[iLoop]);
    sprintf(acTempArray, "%x", piBuffer[iLoop]);
    sResult += acTempArray;
  } 

  return sResult;


}//end s_intPtr2CStringHex


/**********************************************************************
***********************************************************************
**
**      Function name:                     v_SeparatorParser
**      Creation date (DD.MM.YY):          12.02.01
**      Author:                            fra
**
**      Comment:
**       A passed string is divided up in substrings, which are originally
**       separated by a separator (e.g. comma).
**
**
**      List of parameters:
**       sInputLine   : input line
**       psOutput     : pointer to array with CStrings
**       sSeparator   : separator e.g. ","
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void v_SeparatorParser(CArray<CString, CString&>& psOutput , CString sInputLine, CString sSeparator)
{

  int iLoop = 0;


  while(sInputLine.Find(sSeparator) != -1)//do as long as there is a separator in the input line
  {
    
    psOutput.SetSize(iLoop + 1);
    psOutput[iLoop] = sInputLine.Left(sInputLine.Find(sSeparator));

    iLoop++;

    sInputLine  = sInputLine.Mid(sInputLine.Find(sSeparator) + 1);//remove first string from input line
  
  };

  psOutput.SetSize(iLoop + 1);
  psOutput[iLoop] = sInputLine;//last string


}//end v_SeparatorParser


/**********************************************************************
***********************************************************************
**
**      Function name:                     v_IncrementBuffer
**      Creation date (DD.MM.YY):          07.03.00
**      Author:                            fra
**
**      Comment:
**       - Task:
**         Increments content of a passed 8byte buffer for 1
**
**      List of parameters:
**       pucBuffer    :  pointer to buffer
**
**       Return value :  void
**
**      Revisions:
**       Date/Time    :  Name
**       Comment to revision
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  1999   ***************/

void v_IncrementBuffer(unsigned char*  pucBuffer, int iBufferLen){

      unsigned char   ucFlag = 0;
      unsigned char   ucLoop;


  pucBuffer[iBufferLen-1] = pucBuffer[iBufferLen-1] +  1;

  if (pucBuffer[iBufferLen-1] == 0)
  {
   ucFlag =1;
   for (ucLoop = 1; ucLoop < iBufferLen; ucLoop++)
    {
       pucBuffer[iBufferLen-1-ucLoop] = pucBuffer[iBufferLen-1-ucLoop] + ucFlag;

       if((pucBuffer[iBufferLen-1-ucLoop] == 0x00) && (ucFlag == 1))
       {
         ucFlag=1;
       }
       else
       {
         break;
       }
    }
  }

}//end v_IncrementBuffer

/**********************************************************************
***********************************************************************
**
**      Function name:                     v_DecrementBuffer
**      Creation date (DD.MM.YY):          07.03.00
**      Author:                            fra
**
**      Comment:
**       - Task:
**         Decrements content of a passed 8byte buffer for 1
**
**      List of parameters:
**       pucBuffer    :  pointer to buffer
**
**       Return value :  void
**
**      Revisions:
**       Date/Time    :  Name
**       Comment to revision
**
**
** 2002-08-09 xSchu: I no nothing about the beauties of Socrates (are there any?)
**					 I just copied the above function and changed Inc into Dec
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  1999   ***************/

void v_DecrementBuffer(unsigned char*  pucBuffer, int iBufferLen){

      unsigned char   ucFlag = 0;
      unsigned char   ucLoop;


  pucBuffer[iBufferLen-1] = pucBuffer[iBufferLen-1] -  1;

  if (pucBuffer[iBufferLen-1] == 0)
  {
   ucFlag =1;
   for (ucLoop = 1; ucLoop < iBufferLen; ucLoop++)
    {
       pucBuffer[iBufferLen-1-ucLoop] = pucBuffer[iBufferLen-1-ucLoop] + ucFlag;

       if((pucBuffer[iBufferLen-1-ucLoop] == 0x00) && (ucFlag == 1))
       {
         ucFlag=1;
       }
       else
       {
         break;
       }
    }
  }

}//end v_DecrementBuffer

