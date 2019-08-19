
/**********************************************************************
***********************************************************************
****
****      File name:                  UNI_Aut_Algorithm.cpp
****      Creation date (DD.MM.YY):   22.01.01
****      Author:                     fra
****
****      Comment:
****       - Contains functions for calculating f1, f1*, f2, f3, f4, f5, f5*
****         according to [Milenage].
****         A sample implementation of the example 3GPP authentication and
****         key agreement functions f1, f1*, f2, f3, f4, f5 and f5* according 
****         to [Milenage]. This is a byte-oriented implementation of the 
****         functions, and of the block cipher kernel function Rijndael.
****         The functions f2, f3, f4 and f5 share the same inputs and have
****         been coded together as a single function. f1, f1* and f5* are
****         all coded separately.
****       - Contains functions for calculating f1, f1*, f2, f3, f4, f5, f5*
****         according to [Liaison].
****
****
****      List of exported functions:
****       s. UNI_Aut_Milenage.h
****
****      Revisions:
****       $Log: UNI_Aut_Algorithm.cpp $
****       Revision 1.6  2002/11/12 15:00:07Z  SCHOELEU
****       Added some special behaviour for BRUT handling
****       Revision 1.5  2002/11/11 14:20:11Z  SCHOELEU
****       fixed a problem
****       Revision 1.4  2002/10/18 10:45:25Z  SCHOELEU
****       Implemented classes for BRUT
****       Revision 1.3  2001/10/04 06:52:27Z  FrankS
****       Editorial changes
****       Revision 1.2  2001/09/06 09:22:46Z  FrankS
****       OPind: Changes for analysing OP indicator
****       Revision 1.1  2001/08/23 07:54:46Z  FrankS
****       Initial revision
****
****
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

#include "StdAfx.h"
#include "UNI_Aut_Algorithm.h"
#include "UNI_Aut_Utilities.h"


/**********************************************************************
***********************************************************************
**
**      Function name:                     CMilenage
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Constructor. No longer needed, but the possibility to use 
**       an *.ini file to set OP, r1...r5, c1...c5 remains commented out
**
**
**      List of parameters: none
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

CMilenage::CMilenage(){

  //default setting: OP is given and OP_c must be calculated, otherwise: m_csOPind = "OP_c"
  m_csOPind = "OP";

}//end CMilenage


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_SetOP_c
**      Creation date (DD.MM.YY):          06.09.01
**      Author:                            fra
**
**      Comment:
**       Set member variables
**
**
**      List of parameters:
**       pucInput     : ptr to passed OP_c data (input, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_SetOP_c(unsigned char* pucInput)
{
  memcpy(m_aucOP_c, pucInput, 16);

}//end mv_SetOP_c



/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_SetOP
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Set member variables
**
**
**      List of parameters:
**       pucInput     : ptr to passed OP data (input, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_SetOP(unsigned char* pucInput)
{
  memcpy(m_aucOP, pucInput, 16);

}//end mv_SetOP


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_SetOPind
**      Creation date (DD.MM.YY):          06.09.01
**      Author:                            fra
**
**      Comment:
**       Set member variables
**
**
**      List of parameters:
**       csInput      : CString to indicate whether OP or OP_c is used
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_SetOPind(CString csInput)
{

  m_csOPind = csInput;

}//end mv_SetOPind


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_SetRot
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Set member variables
**
**
**      List of parameters:
**       piInput      : ptr to passed Rot data (input, 6 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_SetRot( int* piInput)
{ 
  int iLoop;

  for(iLoop = 0; iLoop < 5; iLoop++)//memcpy not possible as size(int) != 1byte
    m_aiRot[iLoop] = piInput[iLoop];
 
}//end mv_SetRot


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_SetC1
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Set member variables
**
**
**      List of parameters:
**       pucInput     : ptr to passed C1 data (input, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_SetC1(unsigned char* pucInput)
{
  memcpy(m_aucC1, pucInput, 16);

}//end mv_SetC1


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_SetC2
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Set member variables
**
**
**      List of parameters:
**       pucInput     : ptr to passed C2 data (input, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_SetC2(unsigned char* pucInput)
{
  memcpy(m_aucC2, pucInput, 16);

}//end mv_SetC2


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_SetC3
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Set member variables
**
**
**      List of parameters:
**       pucInput     : ptr to passed C3 data (input, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_SetC3(unsigned char* pucInput)
{
  memcpy(m_aucC3, pucInput, 16);

}//end mv_SetC3


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_SetC4
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Set member variables
**
**
**      List of parameters:
**       pucInput     : ptr to passed C4 data (input, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_SetC4(unsigned char* pucInput)
{
  memcpy(m_aucC4, pucInput, 16);

}//end mv_SetC4


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_SetC5
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Set member variables
**
**
**      List of parameters:
**       pucInput     : ptr to passed C5 data (input, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_SetC5(unsigned char* pucInput)
{
  memcpy(m_aucC5, pucInput, 16);

}//end mv_SetC5


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_GetOP_c
**      Creation date (DD.MM.YY):          06.09.01
**      Author:                            fra
**
**      Comment:
**       Get member variables
**
**
**      List of parameters:
**       pucOutput    : ptr to destiny (output, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_GetOP_c(unsigned char* pucOutput)
{
  memcpy(pucOutput, m_aucOP_c, 16);

}//end mv_GetOP_c


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_GetOP
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Get member variables
**
**
**      List of parameters:
**       pucOutput    : ptr to destiny (output, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_GetOP(unsigned char* pucOutput)
{
  memcpy(pucOutput, m_aucOP, 16);

}//end mv_GetOP


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_GetRot
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Get member variables
**
**
**      List of parameters:
**       piOutput    : ptr to destiny (output, 6 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_GetRot(int* piOutput)
{ 
  int iLoop;

  for(iLoop = 0; iLoop < 5; iLoop++)//memcpy not possible as size(int) != 1byte
    piOutput[iLoop] = m_aiRot[iLoop];
 
}//end mv_GetRot


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_GetC1
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Get member variables
**
**
**      List of parameters:
**       pucOutput    : ptr to destiny (output, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_GetC1(unsigned char* pucOutput)
{
  memcpy(pucOutput, m_aucC1, 16);

}//end mv_GetC1


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_GetC2
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Get member variables
**
**
**      List of parameters:
**       pucOutput    : ptr to destiny (output, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_GetC2(unsigned char* pucOutput)
{
  memcpy(pucOutput, m_aucC2, 16);

}//end mv_GetC2


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_GetC3
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Get member variables
**
**
**      List of parameters:
**       pucOutput    : ptr to destiny (output, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_GetC3(unsigned char* pucOutput)
{
  memcpy(pucOutput, m_aucC3, 16);

}//end mv_GetC3


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_GetC4
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Get member variables
**
**
**      List of parameters:
**       pucOutput    : ptr to destiny (output, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_GetC4(unsigned char* pucOutput)
{
  memcpy(pucOutput, m_aucC4, 16);

}//end mv_GetC4


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_GetC5
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Get member variables
**
**
**      List of parameters:
**       pucOutput    : ptr to destiny (output, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_GetC5(unsigned char* pucOutput)
{
  memcpy(pucOutput, m_aucC5, 16);

}//end mv_GetC5


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_Aux1
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Auxiliary function
**
**
**      List of parameters:
**       pucK         : ptr to subscriber key (input, 16 byte)
**       pucRand      : ptr to random number (input, 16 byte)
**       pucSQN       : ptr to sequence number (input, 6 byte)
**       pucAMF       : ptr to authentication management field (input, 2 byte)
**       pucResult    : ptr to result (output, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_Aux1(unsigned char* pucK, unsigned char* pucRand, unsigned char* pucSQN,
                        unsigned char* pucAMF, unsigned char* pucResult)
{

  unsigned char ucLoop;

//  unsigned char aucOP_C[16];
  unsigned char aucBasis[16];
  unsigned char aucConcat[16];
  unsigned char aucPreRotate[16];
  unsigned char aucPostRotate[16];
  unsigned char aucRijndaelInput[16];
  unsigned char aucRijndaelOutput[16];


  //OPc = Ek(OP) -> aucOP_C
  Rijndael.mv_RijndaelKeySchedule(pucK);

  if(m_csOPind != "OP_c")// OP_c not given
  {
    mv_ComputeOPc(m_aucOP_c);
  }


  //Ek(RAND^OPc) -> aucBasis
  for (ucLoop=0; ucLoop<16; ucLoop++)
    aucRijndaelInput[ucLoop] = pucRand[ucLoop] ^ m_aucOP_c[ucLoop];
  Rijndael.mv_RijndaelEncrypt(aucRijndaelInput, aucBasis);


  //SQN||AMF||SQN||AMF -> aucConcat
  for (ucLoop=0; ucLoop<6; ucLoop++)
  {
    aucConcat[ucLoop]   = pucSQN[ucLoop];
    aucConcat[ucLoop+8] = pucSQN[ucLoop];
  }
  for (ucLoop=0; ucLoop<2; ucLoop++)
  {
    aucConcat[ucLoop+6]  = pucAMF[ucLoop];
    aucConcat[ucLoop+14] = pucAMF[ucLoop];
  }


  //aucConcat ^ OPc -> aucPreRotate
  for (ucLoop=0; ucLoop<16; ucLoop++)
    aucPreRotate[ucLoop] = aucConcat[ucLoop] ^ m_aucOP_c[ucLoop];


  //rot(aucPreRotate, r1=m_aiRot[0]) -> aucPostRotate
  memcpy(aucPostRotate, aucPreRotate, 16);
  //v_RotateBufferRight(aucPostRotate, 16, m_aiRot[0]);
  v_RotateBufferLeft(aucPostRotate, 16, m_aiRot[0]);


  //Ek(aucBasis ^ aucPostRotate ^ m_aucC1 -> aucRijndaelOutput)
  for (ucLoop=0; ucLoop<16; ucLoop++)
    aucRijndaelInput[ucLoop] = aucBasis[ucLoop] ^ aucPostRotate[ucLoop] ^ m_aucC1[ucLoop];
  Rijndael.mv_RijndaelEncrypt(aucRijndaelInput, aucRijndaelOutput);


  //aucRijndaelOutput ^ OPc -> pucResult
  for (ucLoop=0; ucLoop<16; ucLoop++)
    pucResult[ucLoop] = aucRijndaelOutput[ucLoop] ^ m_aucOP_c[ucLoop];

}//end mv_Aux1


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_Aux2
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Auxiliary function
**
**
**      List of parameters:
**       pucK         : ptr to subscriber key (input, 16 byte)
**       pucRand      : ptr to random number (input, 16 byte)
**       pucResult    : ptr to result (output, 16 byte)
**       iR           : amount of bitrotation (input)
**       pucC         : ptr to constant buffer (input, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_Aux2(unsigned char* pucK, unsigned char* pucRand, unsigned char* pucResult, 
                        int iR, unsigned char* pucC)
{

  unsigned char ucLoop;

  //unsigned char aucOP_C[16];
  unsigned char aucBasis[16];
  unsigned char aucPreRotate[16];
  unsigned char aucPostRotate[16];
  unsigned char aucRijndaelInput[16];
  unsigned char aucRijndaelOutput[16];


  //OPc = Ek(OP) -> aucOP_C
  Rijndael.mv_RijndaelKeySchedule(pucK);

  if(m_csOPind != "OP_c")// OP_c not given
  {
    mv_ComputeOPc(m_aucOP_c);
  }


  //Ek(RAND^OPc) -> aucBasis
  for (ucLoop=0; ucLoop<16; ucLoop++)
    aucRijndaelInput[ucLoop] = pucRand[ucLoop] ^ m_aucOP_c[ucLoop];
  Rijndael.mv_RijndaelEncrypt(aucRijndaelInput, aucBasis);


  //aucBasis ^ OPc -> aucPreRotate
  for (ucLoop=0; ucLoop<16; ucLoop++)
    aucPreRotate[ucLoop] = aucBasis[ucLoop] ^ m_aucOP_c[ucLoop];


  //rot(aucPreRotate, ri=iR) -> aucPostRotate
  memcpy(aucPostRotate, aucPreRotate, 16);
  v_RotateBufferLeft(aucPostRotate, 16, iR);


  //Ek(aucPostRotate ^ pucC -> aucRijndaelOutput)
  for (ucLoop=0; ucLoop<16; ucLoop++)
    aucRijndaelInput[ucLoop] = aucPostRotate[ucLoop] ^ pucC[ucLoop];
  Rijndael.mv_RijndaelEncrypt(aucRijndaelInput, aucRijndaelOutput);


  //aucRijndaelOutput ^ OPc -> pucResult
  for (ucLoop=0; ucLoop<16; ucLoop++)
    pucResult[ucLoop] = aucRijndaelOutput[ucLoop] ^ m_aucOP_c[ucLoop];

}//end mv_Aux2


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_f1
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Computes network authentication code MAC-A from key K, random
**       challenge RAND, sequence number SQN and authentication management field AMF
**       Original version of function taken from [Milenage]
**
**      List of parameters:
**       pucK         : ptr to subscriber key (input, 16 byte)
**       pucRand      : ptr to random number (input, 16 byte)
**       pucSQN       : ptr to sequence number (input, 6 byte)
**       pucAMF       : ptr to authentication management field (input, 2 byte)
**       pucMAC_A     : ptr to MAC_A (output, 8 byte) = f1
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_f1(unsigned char* pucK,   unsigned char* pucRand, unsigned char* pucSQN,
                      unsigned char* pucAMF, unsigned char* pucMAC_A)
{

  unsigned char aucResult[16];  

  mv_Aux1(pucK, pucRand, pucSQN, pucAMF, aucResult);

  memcpy(pucMAC_A, aucResult, 8);


}//end mv_f1


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_f1star
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Computes resynch authentication code MAC-S from key K, random
**       challenge RAND, sequence number SQN and authentication management field AMF
**       Original version of function taken from [Milenage]
**
**      List of parameters:
**       pucK         : ptr to subscriber key (input, 16 byte)
**       pucRand      : ptr to random number (input, 16 byte)
**       pucSQN       : ptr to sequence number (input, 6 byte)
**       pucAMF       : ptr to resynch authentication management field (input, 2 byte)
**       pucMAC_S     : ptr to MAC_S (output, 8 byte) = f1star
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_f1star(unsigned char* pucK,   unsigned char* pucRand, unsigned char* pucSQN,
                          unsigned char* pucAMF, unsigned char* pucMAC_S)
{
  unsigned char aucResult[16];  

  mv_Aux1(pucK, pucRand, pucSQN, pucAMF, aucResult);

  memcpy(pucMAC_S, aucResult + 8, 8);

}//end mv_f1star


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_f2345
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Takes key K and random challenge RAND, and returns response RES,
**       confidentiality key CK, integrity key IK and anonymity key AK
**       Original version of function taken from [Milenage]
**
**      List of parameters:
**       pucK         : ptr to subscriber key (input, 16 byte)
**       pucRand      : ptr to random number (input, 16 byte)
**       pucRes       : ptr to response (output, 8 byte) = f2
**       pucCK        : ptr to confidentiality key (output, 16 byte) = f3
**       pucIK        : ptr to integrity key (output, 16 byte) = f4
**       pucAK        : ptr to anonymity key (output, 6 byte) = f5
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_f2345(unsigned char* pucK,   unsigned char* pucRand,
                         unsigned char* pucRes, unsigned char* pucCK, unsigned char* pucIK, unsigned char* pucAK )
{
  unsigned char aucResult[16];  

  //r2 => m_aiRot[1], c2 => m_aucC2
  mv_Aux2(pucK, pucRand, aucResult, m_aiRot[1], m_aucC2);
  memcpy(pucRes, aucResult + 8, 8);//f2
  memcpy(pucAK, aucResult, 6);//f5


  //r3 => m_aiRot[2], c3 => m_aucC3
  mv_Aux2(pucK, pucRand, aucResult, m_aiRot[2], m_aucC3);
  memcpy(pucCK, aucResult, 16);//f3


  //r4 => m_aiRot[3], c4 => m_aucC4
  mv_Aux2(pucK, pucRand, aucResult, m_aiRot[3], m_aucC4);
  memcpy(pucIK, aucResult, 16);//f4


}//end mv_f2345


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_f5star
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Takes key K and random challenge RAND, and returns resynch
**       anonymity key AK
**       Original version of function taken from [Milenage]
**
**      List of parameters:
**       pucK         : ptr to subscriber key (input, 16 byte)
**       pucRand      : ptr to random number (input, 16 byte)
**       pucAK        : ptr to resynch anonymity key (output, 6 byte) = f5star
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_f5star(unsigned char* pucK, unsigned char* pucRand, unsigned char* pucAK)
{
  unsigned char aucResult[16];  

  //r5 => m_aiRot[4], c5 => m_aucC5
  mv_Aux2(pucK, pucRand, aucResult, m_aiRot[4], m_aucC5);

  memcpy(pucAK, aucResult, 6);

}//end mv_f5star


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_ComputeOPc
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Function to compute OPc from OP and K. Assumes key schedule has
**       already been performed.
**       Original version of function taken from [Milenage]
**
**      List of parameters:
**       pucOP_c      : ptr to OPc (input and output, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CMilenage::mv_ComputeOPc(unsigned char* pucOP_c)
{
  unsigned char ucLoop;

  Rijndael.mv_RijndaelEncrypt( m_aucOP, pucOP_c );

  for (ucLoop=0; ucLoop<16; ucLoop++)
    pucOP_c[ucLoop] ^= m_aucOP[ucLoop];

  return;

}//end mv_ComputeOPc

/***************  END CMILENAGE CLASS MEMBERS  ************************
***********************************************************************
***********************************************************************
***********************************************************************
***********************************************************************
**********************************************************************/

/**********************************************************************
***********************************************************************
***********************************************************************
***********************************************************************
***********************************************************************
***************  BEGIN CRIJNDAEL CLASS MEMBERS  **********************/





/**********************************************************************
***********************************************************************
**
**      Function name:                     CRijndael
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Constructor. Initialise round subkeys and S box
**       Original version of function taken from [Milenage]
**
**      List of parameters: none
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

CRijndael::CRijndael(){

//Notice: Do not change format of following 2 data blocks

  memcpy(m_aucS,
"\x63\x7c\x77\x7b\xf2\x6b\x6f\xc5\x30\x01\x67\x2b\xfe\xd7\xab\x76\
\xca\x82\xc9\x7d\xfa\x59\x47\xf0\xad\xd4\xa2\xaf\x9c\xa4\x72\xc0\
\xb7\xfd\x93\x26\x36\x3f\xf7\xcc\x34\xa5\xe5\xf1\x71\xd8\x31\x15\
\x04\xc7\x23\xc3\x18\x96\x05\x9a\x07\x12\x80\xe2\xeb\x27\xb2\x75\
\x09\x83\x2c\x1a\x1b\x6e\x5a\xa0\x52\x3b\xd6\xb3\x29\xe3\x2f\x84\
\x53\xd1\x00\xed\x20\xfc\xb1\x5b\x6a\xcb\xbe\x39\x4a\x4c\x58\xcf\
\xd0\xef\xaa\xfb\x43\x4d\x33\x85\x45\xf9\x02\x7f\x50\x3c\x9f\xa8\
\x51\xa3\x40\x8f\x92\x9d\x38\xf5\xbc\xb6\xda\x21\x10\xff\xf3\xd2\
\xcd\x0c\x13\xec\x5f\x97\x44\x17\xc4\xa7\x7e\x3d\x64\x5d\x19\x73\
\x60\x81\x4f\xdc\x22\x2a\x90\x88\x46\xee\xb8\x14\xde\x5e\x0b\xdb\
\xe0\x32\x3a\x0a\x49\x06\x24\x5c\xc2\xd3\xac\x62\x91\x95\xe4\x79\
\xe7\xc8\x37\x6d\x8d\xd5\x4e\xa9\x6c\x56\xf4\xea\x65\x7a\xae\x08\
\xba\x78\x25\x2e\x1c\xa6\xb4\xc6\xe8\xdd\x74\x1f\x4b\xbd\x8b\x8a\
\x70\x3e\xb5\x66\x48\x03\xf6\x0e\x61\x35\x57\xb9\x86\xc1\x1d\x9e\
\xe1\xf8\x98\x11\x69\xd9\x8e\x94\x9b\x1e\x87\xe9\xce\x55\x28\xdf\
\x8c\xa1\x89\x0d\xbf\xe6\x42\x68\x41\x99\x2d\x0f\xb0\x54\xbb\x16", 256);


//This array does the multiplication by x in GF(2^8)
  memcpy(m_aucXtime,
"\x00\x02\x04\x06\x08\x0a\x0c\x0e\x10\x12\x14\x16\x18\x1a\x1c\x1e\
\x20\x22\x24\x26\x28\x2a\x2c\x2e\x30\x32\x34\x36\x38\x3a\x3c\x3e\
\x40\x42\x44\x46\x48\x4a\x4c\x4e\x50\x52\x54\x56\x58\x5a\x5c\x5e\
\x60\x62\x64\x66\x68\x6a\x6c\x6e\x70\x72\x74\x76\x78\x7a\x7c\x7e\
\x80\x82\x84\x86\x88\x8a\x8c\x8e\x90\x92\x94\x96\x98\x9a\x9c\x9e\
\xa0\xa2\xa4\xa6\xa8\xaa\xac\xae\xb0\xb2\xb4\xb6\xb8\xba\xbc\xbe\
\xc0\xc2\xc4\xc6\xc8\xca\xcc\xce\xd0\xd2\xd4\xd6\xd8\xda\xdc\xde\
\xe0\xe2\xe4\xe6\xe8\xea\xec\xee\xf0\xf2\xf4\xf6\xf8\xfa\xfc\xfe\
\x1b\x19\x1f\x1d\x13\x11\x17\x15\x0b\x09\x0f\x0d\x03\x01\x07\x05\
\x3b\x39\x3f\x3d\x33\x31\x37\x35\x2b\x29\x2f\x2d\x23\x21\x27\x25\
\x5b\x59\x5f\x5d\x53\x51\x57\x55\x4b\x49\x4f\x4d\x43\x41\x47\x45\
\x7b\x79\x7f\x7d\x73\x71\x77\x75\x6b\x69\x6f\x6d\x63\x61\x67\x65\
\x9b\x99\x9f\x9d\x93\x91\x97\x95\x8b\x89\x8f\x8d\x83\x81\x87\x85\
\xbb\xb9\xbf\xbd\xb3\xb1\xb7\xb5\xab\xa9\xaf\xad\xa3\xa1\xa7\xa5\
\xdb\xd9\xdf\xdd\xd3\xd1\xd7\xd5\xcb\xc9\xcf\xcd\xc3\xc1\xc7\xc5\
\xfb\xf9\xff\xfd\xf3\xf1\xf7\xf5\xeb\xe9\xef\xed\xe3\xe1\xe7\xe5", 256);

}//end CRijndael


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_RijndaelKeySchedule
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Rijndael key schedule function. Takes 16-byte key and creates
**       all Rijndael's internal subkeys ready for encryption.
**       Original version of function taken from [Milenage]
**
**      List of parameters:
**       pucKey       : ptr to individual key(input, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CRijndael::mv_RijndaelKeySchedule(unsigned char* pucKey)
{
  unsigned char ucRoundConst;
  int iLoop1, iLoop2;


  //first round key equals key
  for (iLoop1 = 0; iLoop1 < 16; iLoop1++)
    m_aucRoundKeys[0][iLoop1 & 0x03][iLoop1>>2] = pucKey[iLoop1];

  ucRoundConst = 1;

  //now calculate round keys
  for (iLoop1 = 1; iLoop1 < 11; iLoop1++)
  {
    m_aucRoundKeys[iLoop1][0][0] = m_aucS[m_aucRoundKeys[iLoop1-1][1][3]] ^ m_aucRoundKeys[iLoop1-1][0][0] ^ ucRoundConst;
    m_aucRoundKeys[iLoop1][1][0] = m_aucS[m_aucRoundKeys[iLoop1-1][2][3]] ^ m_aucRoundKeys[iLoop1-1][1][0];
    m_aucRoundKeys[iLoop1][2][0] = m_aucS[m_aucRoundKeys[iLoop1-1][3][3]] ^ m_aucRoundKeys[iLoop1-1][2][0];
    m_aucRoundKeys[iLoop1][3][0] = m_aucS[m_aucRoundKeys[iLoop1-1][0][3]] ^ m_aucRoundKeys[iLoop1-1][3][0];

    for (iLoop2 = 0; iLoop2 <4; iLoop2++)
    {
      m_aucRoundKeys[iLoop1][iLoop2][1] = m_aucRoundKeys[iLoop1-1][iLoop2][1] ^ m_aucRoundKeys[iLoop1][iLoop2][0];
      m_aucRoundKeys[iLoop1][iLoop2][2] = m_aucRoundKeys[iLoop1-1][iLoop2][2] ^ m_aucRoundKeys[iLoop1][iLoop2][1];
      m_aucRoundKeys[iLoop1][iLoop2][3] = m_aucRoundKeys[iLoop1-1][iLoop2][3] ^ m_aucRoundKeys[iLoop1][iLoop2][2];
    }

    //update round constant
    ucRoundConst = m_aucXtime[ucRoundConst];
  }

}//end mv_RijndaelKeySchedule


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_KeyAdd
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Round key addition function
**       Original version of function taken from [Milenage]
**
**      List of parameters:
**       state          : ptr to array for state
**       m_aucRoundKeys : ptr to array for round keys
**       iRound         : round
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CRijndael::mv_KeyAdd(unsigned char state[4][4], unsigned char m_aucRoundKeys[11][4][4], int iRound)
{
  int iLoop1, iLoop2;

  for (iLoop1=0; iLoop1<4; iLoop1++)
    for (iLoop2=0; iLoop2<4; iLoop2++)
      state[iLoop1][iLoop2] ^= m_aucRoundKeys[iRound][iLoop1][iLoop2];

}//end mv_KeyAdd


/**********************************************************************
***********************************************************************
**
**      Function name:                     mi_ByteSub
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Byte substitution transformation
**       Original version of function taken from [Milenage]
**
**      List of parameters:
**       state       : ptr to array for state
**       Return value : 0
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

int CRijndael::mi_ByteSub(unsigned char state[4][4])
{
  int iLoop1, iLoop2;

  for (iLoop1 = 0; iLoop1 < 4; iLoop1++)
    for (iLoop2 = 0; iLoop2 < 4; iLoop2++)
      state[iLoop1][iLoop2] = m_aucS[state[iLoop1][iLoop2]];

  return 0;
}//end mi_ByteSub


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_ShiftRow
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Row shift transformation
**       Original version of function taken from [Milenage]
**
**      List of parameters:
**       state       : ptr to array for state
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CRijndael::mv_ShiftRow(unsigned char state[4][4])
{
  unsigned char ucTemp;

  //left rotate row 1 by 1
  ucTemp = state[1][0];
  state[1][0] = state[1][1];
  state[1][1] = state[1][2];
  state[1][2] = state[1][3];
  state[1][3] = ucTemp;

  //left rotate row 2 by 2
  ucTemp = state[2][0];
  state[2][0] = state[2][2];
  state[2][2] = ucTemp;
  ucTemp = state[2][1];
  state[2][1] = state[2][3];
  state[2][3] = ucTemp;

  //left rotate row 3 by 3
  ucTemp = state[3][0];
  state[3][0] = state[3][3];
  state[3][3] = state[3][2];
  state[3][2] = state[3][1];
  state[3][1] = ucTemp;

}//end mv_ShiftRow


/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_MixColumn
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       mv_MixColumn transformation
**       Original version of function taken from [Milenage]
**
**      List of parameters:
**       state       : ptr to array for state
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CRijndael::mv_MixColumn(unsigned char state[4][4])
{
  unsigned char ucTemp, ucTmp, ucTmp0;
  int iLoop;

  //do one column at a time
  for (iLoop = 0; iLoop < 4;iLoop++)
  {
    ucTemp = state[0][iLoop] ^ state[1][iLoop] ^ state[2][iLoop] ^ state[3][iLoop];
    ucTmp0 = state[0][iLoop];

    //m_aucXtime array does multiply by x in GF2^8
    ucTmp = m_aucXtime[state[0][iLoop] ^ state[1][iLoop]];
    state[0][iLoop] ^= ucTemp ^ ucTmp;

    ucTmp = m_aucXtime[state[1][iLoop] ^ state[2][iLoop]];
    state[1][iLoop] ^= ucTemp ^ ucTmp;

    ucTmp = m_aucXtime[state[2][iLoop] ^ state[3][iLoop]];
    state[2][iLoop] ^= ucTemp ^ ucTmp;

    ucTmp = m_aucXtime[state[3][iLoop] ^ ucTmp0];
    state[3][iLoop] ^= ucTemp ^ ucTmp;
  }

}//end mv_MixColumn



/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_RijndaelEncrypt
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Rijndael encryption function. Takes 16-byte input and creates
**       16-byte output (using round keys already derived from 16-byte
**       key).
**       Original version of function taken from [Milenage]
**
**      List of parameters:
**       pucInput     : ptr to input buffer(16 byte)
**       pucOutput    : ptr to output buffer(16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/

void CRijndael::mv_RijndaelEncrypt(unsigned char* pucInput, unsigned char* pucOutput)
{
  unsigned char aucState[4][4];
  int iLoop, iR;

  //initialise aucState array from input byte string
  for (iLoop = 0; iLoop < 16; iLoop++)
    aucState[iLoop & 0x3][iLoop>>2] = pucInput[iLoop];

  //add first round_key
  mv_KeyAdd(aucState, m_aucRoundKeys, 0);

  //do lots of full rounds
  for (iR = 1; iR <= 9; iR++)
  {
    mi_ByteSub(aucState);
    mv_ShiftRow(aucState);
    mv_MixColumn(aucState);
    mv_KeyAdd(aucState, m_aucRoundKeys, iR);
  }

  //final round
  mi_ByteSub(aucState);
  mv_ShiftRow(aucState);
  mv_KeyAdd(aucState, m_aucRoundKeys, iR);

  //produce output byte string from aucState array
  for (iLoop = 0; iLoop < 16; iLoop++)
  {
    pucOutput[iLoop] = aucState[iLoop & 0x3][iLoop>>2];
  }


}//end mv_RijndaelEncrypt


/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/



/**********************************************************************
***********************************************************************
**
**      Function name:                     CLiaison
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Constructor. No longer needed, but the possibility to use
**       an *.ini file to set OP, r1...r5, c1...c5 remains commented out
**
**
**      List of parameters: none
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/
/*
CLiaison::CLiaison(){



}//end CLiaison

*/

/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_XDOUT
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Auxiliary function
**
**
**      List of parameters:
**       pucK         : ptr to subscriber key (input, 16 byte)
**       pucRand      : ptr to random number (input, 16 byte)
**       pucXDOUT     : ptr to XDOUT (output, 16 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/
/*
void CLiaison::mv_XDOUT(unsigned char* pucK, unsigned char* pucRand, unsigned char* pucXDOUT)
{

  int iLoop;

  for(iLoop = 0; iLoop < 16; iLoop++)
    pucXDOUT[iLoop] =  pucK[iLoop] ^ pucRand[iLoop];

}//end mv_XDOUT
*/
/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_CDOUT
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Auxiliary function
**
**
**      List of parameters:
**       pucSQN       : ptr to sequence number (input, 6 byte)
**       pucAMF       : ptr to authentication management field (input, 2 byte)
**       pucCDOUT     : ptr to CDOUT(output, 8 byte)
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/
/*
void CLiaison::mv_CDOUT(unsigned char* pucSQN, unsigned char* pucAMF, unsigned char* pucCDOUT)
{

  memcpy(pucCDOUT, pucSQN, 6);
  memcpy(pucCDOUT + 6, pucAMF, 2);

}//end mv_CDOUT

*/

/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_f1
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Computes network authentication code MAC from key K, random
**       challenge RAND, sequence number SQN and authentication management field AMF
**
**      List of parameters:
**       pucK         : ptr to subscriber key (input, 16 byte)
**       pucRand      : ptr to random number (input, 16 byte)
**       pucSQN       : ptr to sequence number (input, 6 byte)
**       pucAMF       : ptr to authentication management field (input, 2 byte)
**       pucMAC       : ptr to MAC  (output, 8 byte) = f1
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/
/*
void CLiaison::mv_f1(unsigned char* pucK, unsigned char* pucRand, unsigned char* pucSQN, unsigned char* pucAMF, unsigned char* pucMAC)
{

  int iLoop;

  unsigned char aucXDOUT[16];
  unsigned char aucCDOUT[8];

  mv_XDOUT(pucK, pucRand, aucXDOUT);
  mv_CDOUT(pucSQN, pucAMF, aucCDOUT);


  for(iLoop = 0; iLoop < 8; iLoop++)
    pucMAC[iLoop] =  aucXDOUT[iLoop] ^ aucCDOUT[iLoop];

}//end mv_f1
*/

/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_f1star
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Computes resynch authentication code MAC-S from key K, random
**       challenge RAND, sequence number SQN and authentication management field AMF
**
**      List of parameters:
**       pucK         : ptr to subscriber key (input, 16 byte)
**       pucRand      : ptr to random number (input, 16 byte)
**       pucSQN       : ptr to sequence number (input, 6 byte)
**       pucAMF       : ptr to resynch authentication management field (input, 2 byte)
**       pucMAC_S     : ptr to MAC_S (output, 8 byte) = f1star
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/
/*
void CLiaison::mv_f1star(unsigned char* pucK, unsigned char* pucRand, unsigned char* pucSQN, unsigned char* pucAMF, unsigned char* pucMAC_S)
{

  int iLoop;

  unsigned char aucXDOUT[16];
  unsigned char aucCDOUT[8];

  mv_XDOUT(pucK, pucRand, aucXDOUT);
  mv_CDOUT(pucSQN, pucAMF, aucCDOUT);


  for(iLoop = 0; iLoop < 8; iLoop++)
    pucMAC_S[iLoop] =  aucXDOUT[iLoop] ^ aucCDOUT[iLoop];


}//end mv_f1star
*/

/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_f2345
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Takes key K and random challenge RAND, and returns response RES,
**       confidentiality key CK, integrity key IK and anonymity key AK
**
**      List of parameters:
**       pucK         : ptr to subscriber key (input, 16 byte)
**       pucRand      : ptr to random number (input, 16 byte)
**       pucRes       : ptr to response (output, 16 byte) = f2
**       pucCK        : ptr to confidentiality key (output, 16 byte) = f3
**       pucIK        : ptr to integrity key (output, 16 byte) = f4
**       pucAK        : ptr to anonymity key (output, 6 byte) = f5
**       Return value : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/
/*
void CLiaison::mv_f2345 (unsigned char* pucK, unsigned char* pucRand,
            unsigned char* pucRes, unsigned char* pucCK, unsigned char* pucIK, unsigned char* pucAK)
{


  unsigned char aucXDOUT[16];

  mv_XDOUT(pucK, pucRand, aucXDOUT);



  memcpy(pucRes, aucXDOUT, 16);//bit 0-127

  memcpy(pucCK, aucXDOUT + 1, 15);//bit 8-127
  memcpy(pucCK + 15, aucXDOUT, 1);//bit 0-7

  memcpy(pucIK, aucXDOUT + 2, 14);//bit 16-127
  memcpy(pucIK + 14, aucXDOUT, 2);//bit 0-15

  memcpy(pucAK, aucXDOUT + 3, 6);//bit 24-71


}//end mv_f2345
*/

/**********************************************************************
***********************************************************************
**
**      Function name:                     mv_f5star
**      Creation date (DD.MM.YY):          22.01.01
**      Author:                            fra
**
**      Comment:
**       Takes key K and random challenge RAND, and returns resynch
**       anonymity key AK
**
**      List of parameters:
**       pucK          : ptr to subscriber key (input, 16 byte)
**       pucRand       : ptr to random number (input, 16 byte)
**       pucAK         : ptr to resynch anonymity key (output, 6 byte) = f5star
**       Return value  : void
**
**
**      Revisions:
**       Date/Time    :
**
**
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/
/*
void CLiaison::mv_f5star(unsigned char* pucK, unsigned char* pucRand, unsigned char* pucAK)
{
  
  unsigned char aucXDOUT[16];

  mv_XDOUT(pucK, pucRand, aucXDOUT);

  memcpy(pucAK, aucXDOUT + 3, 6);//bit 24-71

}//end mv_f5star

*/


/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/
/**********************************************************************/











