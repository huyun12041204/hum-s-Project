
/**********************************************************************
***********************************************************************
****
****      File name:                  UNI_Aut_Algorithm.h
****      Creation date (DD.MM.YY):   22.01.01
****      Author:                     fra
****
****      Comment:
****       Header file belonging to UNI_Aut_Algorithm.cpp
****
****
****      List of exported functions:
****       s. below
****
****      Revisions:
****       $Log: UNI_Aut_Algorithm.h $
****       Revision 1.3  2002/10/18 09:26:03Z  SCHOELEU
****       Implemented classes for BRUT
****       Revision 1.2  2001/09/06 09:25:28Z  FrankS
****       OPind: Changes for analysing OP indicator
****       Revision 1.1  2001/08/23 07:54:24Z  FrankS
****       Initial revision
****
****
***********************************************************************
***********   (C) Copyright Giesecke & Devrient  2001   ***************/


#ifndef _UNI_AUT_ALGORITHM_
#define _UNI_AUT_ALGORITHM_

#include "StdAfx.h"
//#include <AFX.h>
//#include "Afxtempl.h"//for CString


  class CRijndael
  {

  public:

    CRijndael();

    void mv_RijndaelKeySchedule(unsigned char*);
    void mv_RijndaelEncrypt(unsigned char*, unsigned char*);


  private:

    void mv_KeyAdd(unsigned char state[4][4], unsigned char m_aucRoundKeys[11][4][4], int);
    int mi_ByteSub(unsigned char state[4][4]);
    void mv_ShiftRow(unsigned char state[4][4]);
    void mv_MixColumn(unsigned char state[4][4]);

    unsigned char m_aucRoundKeys[11][4][4];
    unsigned char m_aucS[256];
    unsigned char m_aucXtime[256];


  };


  class CMilenage
  {

  public:

    CMilenage();

    void mv_SetOP_c(unsigned char*);
    void mv_SetOP(unsigned char*);
    void mv_SetOPind(CString);
    void mv_SetRot(int*);
    void mv_SetC1(unsigned char*);
    void mv_SetC2(unsigned char*);
    void mv_SetC3(unsigned char*);
    void mv_SetC4(unsigned char*);
    void mv_SetC5(unsigned char*);

    void mv_GetOP_c(unsigned char*);
    void mv_GetOP(unsigned char*);
    void mv_GetRot(int*);
    void mv_GetC1(unsigned char*);
    void mv_GetC2(unsigned char*);
    void mv_GetC3(unsigned char*);
    void mv_GetC4(unsigned char*);
    void mv_GetC5(unsigned char*);

    void mv_f1(unsigned char*,   unsigned char*, unsigned char*, unsigned char*, unsigned char*);
    void mv_f1star(unsigned char*,   unsigned char*, unsigned char*, unsigned char*, unsigned char*);
    void mv_f2345(unsigned char*, unsigned char*, unsigned char*, unsigned char*, unsigned char*, unsigned char*);
    void mv_f5star(unsigned char*, unsigned char*, unsigned char*);
    void mv_ComputeOPc(unsigned char*);


  private:

    void mv_Aux1(unsigned char*, unsigned char*, unsigned char*, unsigned char*, unsigned char*);
    void mv_Aux2(unsigned char*, unsigned char*, unsigned char*, int, unsigned char*);

    CRijndael Rijndael;

    unsigned char m_aucOP_c[16];
    unsigned char m_aucOP[16];
    int m_aiRot[5];
    unsigned char m_aucC1[16];
    unsigned char m_aucC2[16];
    unsigned char m_aucC3[16];
    unsigned char m_aucC4[16];
    unsigned char m_aucC5[16];

    CString m_csOPind;

  };

/*

  class CLiaison
  {

  public:

    CLiaison();

    void mv_f1(unsigned char*,   unsigned char*, unsigned char*, unsigned char*, unsigned char*);
    void mv_f1star(unsigned char*,   unsigned char*, unsigned char*, unsigned char*, unsigned char*);
    void mv_f2345(unsigned char*, unsigned char*, unsigned char*, unsigned char*, unsigned char*, unsigned char*);
    void mv_f5star(unsigned char*, unsigned char*, unsigned char*);


  private:

    void mv_XDOUT(unsigned char*, unsigned char*, unsigned char*);
    void mv_CDOUT(unsigned char*, unsigned char*, unsigned char*);


  };


  class CBRUT
  {

  public:

    CBRUT();

    void mv_f1(unsigned char*,   unsigned char*, unsigned char*, unsigned char*, unsigned char*);
    void mv_f1star(unsigned char*,   unsigned char*, unsigned char*, unsigned char*, unsigned char*);
    void mv_f2345(unsigned char*, unsigned char*, unsigned char*, unsigned char*, unsigned char*, unsigned char*);
    void mv_f5star(unsigned char*, unsigned char*, unsigned char*);
  };



  class CSAM
  {

  public:

    CSAM();

    void mv_f1(unsigned char*,   unsigned char*, unsigned char*, unsigned char*, unsigned char*);
    void mv_f1star(unsigned char*,   unsigned char*, unsigned char*, unsigned char*, unsigned char*);
    void mv_f2345(unsigned char*, unsigned char*, unsigned char*, unsigned char*, unsigned char*, unsigned char*);
    void mv_f5star(unsigned char*, unsigned char*, unsigned char*);
  };

*/

#endif