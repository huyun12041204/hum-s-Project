/*
      Name:        DES.C

      Beschreibung:    DES-VerschlÅsselungsroutinen
               (Data Encryption Standard)
                       fÅr IFDSIM

      Autor:           Federspiel
      Bearbeitet am:   20. July 1992

      Modifiziert am:  16. Sept.1997 by aig
                       triple_des Routine: erste Runden bei MAC werden mit SingleDES berechnet,
                                           nur letzte Runde wird mit TripleDES berechnet
      Modifiziert am:  30. Okt.1997 by aig
                       triple_des Routine: auch wenn Datenlaenge Vielfaches von 8 =>
                                           nur letzte Runde wird mit TripleDES berechnet
*/
#include "stdafx.h"
#include "des.h"     
                    /* Standartdefinitionen fÅr DES */

#define XOR     ^

unsigned char     nbswk[64], nbsccdd[2*56];

static unsigned char nbsip[] = {                  /* input permutation table */
/*       1   2   3   4   5   6   7   8        represents [IP?/P]   */
        48, 16, 41,  9, 40,  8, 56, 24,
        59, 27, 62, 30, 34,  2, 35,  3,
        43, 11, 49, 17, 58, 26, 42, 10,
        60, 28, 36,  4, 63, 31, 53, 21,
        52, 20, 57, 25, 45, 13, 37,  5,
        51, 19, 54, 22, 55, 23, 61, 29,
        38,  6, 46, 14, 39,  7, 44, 12,
        47, 15, 32,  0, 33,  1, 50, 18
        };

static unsigned char nbsips[] = {                 /* input permutation table */
/*       2   1   4   3   6   5   8   7         with implied RL swap */
        16, 48,  9, 41,  8, 40, 24, 56,
        27, 59, 30, 62,  2, 34,  3, 35,
        11, 43, 17, 49, 26, 58, 10, 42,
        28, 60,  4, 36, 31, 63, 21, 53,
        20, 52, 25, 57, 13, 45,  5, 37,
        19, 51, 22, 54, 23, 55, 29, 61,
         6, 38, 14, 46,  7, 39, 12, 44,
        15, 47,  0, 32,  1, 33, 18, 50
        };

static unsigned char   nbspc1[] = {             /* permuted choice 1 */
         7, 15, 23, 83, 79, 71, 63,     /* with special offset of 28 */
         6, 14, 22, 82, 78, 70, 62,     /* for the "dd" part of key  */
         5, 13, 21, 81, 77, 69, 61,
         4, 12, 20, 80, 76, 68, 60,
         3, 11, 19, 27, 75, 67, 59,
         2, 10, 18, 26, 74, 66, 58,
         1,  9, 17, 25, 73, 65, 57,
         0,  8, 16, 24, 72, 64, 56
        };

const static unsigned char   nbspc2[] = {        /* permuted choice 2            */
/*       1.  6.  2.  3.  4.  5.            column sequence changed      */
        13,  4, 16, 10, 23,  0,
         2,  9, 27, 14,  5, 20,
        22,  7, 18, 11,  3, 25,
        15,  1,  6, 26, 19, 12,
        68, 82, 79, 58, 64, 74,         /* with special offset of 28    */
        57, 75, 67, 78, 72, 60,         /* for the "dd" part            */
        71, 80, 76, 66, 83, 61,
        73, 59, 69, 77, 63, 56
        };

const static unsigned char   nbsep[] = {         /* represents [E˘P] */
/*       1.  6.  2.  3.  4.  5.      column sequence changed */
        24, 28, 15,  6, 19, 20,
        20,  0, 28, 11, 27, 16,
        16,  4,  0, 14, 22, 25,
        25,  1,  4, 17, 30,  9,
         9, 31,  1,  7, 23, 13,
        13, 18, 31, 26,  2,  8,
         8, 21, 18, 12, 29,  5,
         5, 15, 21, 10,  3, 24
        };

const static unsigned char nbsshift[] = { 1,2,4,6,8,10,12,14,15,17,19,21,23,25,27,28 };

static unsigned char nbss1[] = {
        14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
         0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
         4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
        15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
        };

static unsigned char nbss2[] = {
        15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
         3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
         0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
        13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
        };

static unsigned char nbss3[] = {
        10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
        13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
        13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
         1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
        };

static unsigned char nbss4[] = {
         7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
        13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
        10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
         3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
        };

static unsigned char nbss5[] = {
         2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
        14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
         4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
        11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
        };

static unsigned char nbss6[] = {
        12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
        10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
         9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
         4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
        };

static unsigned char nbss7[] = {
         4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
        13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
         1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
         6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
        };

static unsigned char nbss8[] = {
        13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
         1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
         7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
         2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
        };

static unsigned char *nbss[] = { nbss1,nbss2,nbss3,nbss4,nbss5,nbss6,nbss7,nbss8 };

/**************************************************************/
   static void transform (unsigned char *store, unsigned char *input, unsigned char *kn)
/**************************************************************/
{
 register int   i, sh;
 register unsigned char  **sbox = nbss;
 char           iv;

 for (i=0; i<48; i+=6) {
   iv = (char) (((((((((
          (kn[ nbspc2[i]   ] XOR input[ nbsep[i]   ])  << 1)
        + (kn[ nbspc2[i+1] ] XOR input[ nbsep[i+1] ])) << 1)
        + (kn[ nbspc2[i+2] ] XOR input[ nbsep[i+2] ])) << 1)
        + (kn[ nbspc2[i+3] ] XOR input[ nbsep[i+3] ])) << 1)
        + (kn[ nbspc2[i+4] ] XOR input[ nbsep[i+4] ])) << 1)
        + (kn[ nbspc2[i+5] ] XOR input[ nbsep[i+5] ]);
   sh = (*sbox++)[iv];
   *store++ ^=  sh >> 3;
   *store++ ^= (sh >> 2) & 1;
   *store++ ^= (sh >> 1) & 1;
   *store++ ^=  sh & 1;
   }
}

/***********************************************************/
   static void expand (unsigned char *inp, unsigned char *key, unsigned char *lookup)
/***********************************************************/
{
 register int i, j;
 char         data, keyb;
 unsigned char         *choice = nbspc1;

 for (i = 0; i < 8; i++) {
   keyb = *key++;
   data = *inp++;
   for (j = 0; j < 8; j++) {
       if (j != 7) {
       nbsccdd[28+*choice] = nbsccdd[*choice] =
                                       (char) ((keyb & 0x80) != 0);
       ++choice;
           keyb = (char) (keyb << 1);
       }
       nbswk[*lookup++] = (char) ((data & 0x80) != 0);
       data = (char) (data << 1);
       }
   }
}

/**************************************************/
   static void compress (unsigned char *out, unsigned char *lookup)
/**************************************************/
{
 register int    i, j;

 for (i = 0; i < 8; i++) {
   *out = 0;
   for (j = 0; j < 8; j++) *out = (char) ((*out<<1) + nbswk[*lookup++]);
   ++out;
   }
 return;
}

/**********************************************************/
   static void encrypt (unsigned char *inp, unsigned char *key, unsigned char *outp)  /* 64-bit cycle */
/**********************************************************/
{
 register int    i;

 expand (inp,key,nbsip);
 for (i = 0; i < 16; i++) {
   if (i & 1)   transform (&nbswk[32],&nbswk[0],&nbsccdd[nbsshift[i]]);
   else         transform (&nbswk[0],&nbswk[32],&nbsccdd[nbsshift[i]]);
   }
 compress (outp,nbsips);
 return;
}

/**********************************************************/
   static void decrypt (unsigned char *inp, unsigned char *key, unsigned char *outp)  /* 64-bit cycle */
/**********************************************************/
{
 register int    i;

 for(i = 0; i < 8; i++)  inp[i] = (char) (0xff & inp[i]);
 expand (inp,key,nbsips);

 for (i = 15; i >= 0; --i) {
   if (i & 1)   transform (&nbswk[32],&nbswk[0],&nbsccdd[nbsshift[i]]);
   else         transform (&nbswk[0],&nbswk[32],&nbsccdd[nbsshift[i]]);
   }
 compress (outp,nbsip);
 return;
}

/*****************************************************************/
int des(unsigned char *keyin, unsigned char *input, int length,   /* DES - */
      unsigned char *output, char par1, char par2, char par3)    /* Funktion */
/*****************************************************************/
{
 int  i, j = 0, isoflag = 0;
 unsigned char    in[10] , in2[10], key[10] , chain[10];

 if (par3 == ISO) isoflag++;             /* Mit 0x80 oder 0x00 auffÅllen */
                                         /* wenn Daten kleiner 8 Byte */
 if (par2 != CBC && par2 != ECB) return(-2); /* Fehler im Parameter 2 */
                                 /* CBC: Cipherblock chaining */
                                 /* ECB - electronic code book, Einzelblock */

 switch(par1)                            /* encrypt, decrypt, mac */
 {
   case MAC     : par2 = CBC;            /* message authentication code */
   case ENCRYPT :                        /* encrypt */
   case DECRYPT : break;                 /* decrypt */
   default:    return(-1);               /* Fehler im Parameter 1 */
 }

 for (i = 0 ; i < 8 ; i++)               /* Felder vorbelegen */
 {
   key[i] = keyin[i];                    /* SchlÅssel Åbergeben */
   in[i]  = in2[i] = chain[i] = 0;       /* input + chaining value lîschen */
 }

 while (length)                          /* Blockweise zu 8 Byte abarbeiten */
 {
   for (i = 0; i < 8 ; i++)              /* Eingabe in vielfaches */
   {                                     /* von 8 zerlegen */
       if (length > 0)
       {
           in[i] = input[i + j];
           length--;
       }
       else
       {
           if (par1 == DECRYPT) return(-4);       /* Immer vielfaches von 8 */
           if (isoflag) { in[i]= 0x80; isoflag--; } /* erstes Byte nach ISO */
           else           in[i]= 0;              /* Rest mit Nullen fÅllen  */
       }

       if (par2 == CBC && par1 != DECRYPT) /* M und E */
           in[i]= (char)(in[i]^chain[i]);  /* next block XOR chaining value */
   }
   if (length < 0) length = 0;           /* Mit 0x80 auffÅllen beenden */

   if (par1 == DECRYPT) decrypt(in, key, chain); /* entschlÅsseln */
   else                 encrypt(in, key, chain); /* verschlÅsseln */

   if ( (par2 == CBC) && (par1 == DECRYPT) )
   {
       for (i = 0; i < 8; i++)
       {
           chain[i] = (char) (in2[i] ^ chain[i]); /* next block XOR chaining value */
           in2[i]   = in[i];                      /* Zu entschl. Daten 8 Byte zuvor */
       }
   }

   if (par1 != MAC) for(i = 0; i < 8; i++) output[i + j] = chain[i];
   j += 8;
   if (!length && isoflag && par1 != DECRYPT) length= -1;/* Mit 0x80 auffÅl. */
 }

 if (par1 == MAC)                        /* Summenberechnung */
 {
   for(i = 0; i < 8; i++) output[i] = chain[i];
   return(8);
 }
 else
 {
   if (isoflag && par1 == DECRYPT && j)  /* EntschlÅsseln nach ISO */
   {
       for(i = j - 1; i > j - 9; i--)    /* ohne 0x80 0x00 usw. */
       {
           if (output[i] == 0x80) return(i); /* neue DatenlÑnge zurÅck */
           if (output[i]) break;             /* Abbruch, keine ISO def.*/
       }
   }
 }
 return(j);                              /* VerschlÅsseln, neue DatenlÑnge */
}

/****************************************************************
* tripple_des
* -> brg
*****************************************************************/
int triple_des(unsigned char *keyin, unsigned char *input, int length,      /* Triple-DES - */
               unsigned char *output, char par1, char par2, char par3)      /* Funktion     */
{
 int  i, j = 0, isoflag = 0;
 unsigned char    in[15] , in2[15], chain[15], buffer[15], key_left[15], key_right[15];
 // start 2. modification by aig
 int bNotLastRound = 0;
 if ( ( (length % 8) == 0) && (par3 == ISO) && (par1 == MAC) )
	 bNotLastRound = 1;
 // end 2. modification by aig


 if (par3 == ISO) isoflag++;                    /* Mit 0x80 oder 0x00 auffÅllen */
                                                /* wenn Daten kleiner 8 Byte */
 if (par2 != CBC && par2 != ECB)                /* Fehler im Parameter 2 */
   return(-2);                                  /* CBC: Cipherblock chaining */
                                                /* ECB - electronic code book, Einzelblock */

 switch(par1)                                   /* encrypt, decrypt, mac */
 {
   case MAC     : par2 = CBC;           /* message authentication code */
   case ENCRYPT :                           /* encrypt */
   case DECRYPT : break;                    /* decrypt */
   default:    return(-1);                      /* Fehler im Parameter 1 */
 }

 for (i = 0 ; i < 8 ; i++)                      /* Felder vorbelegen */
 {
   key_left[i] = keyin[i];                      /* SchlÅssel Åbergeben, dabei 16-Byte Schl¸ssel */
   key_right[i] = keyin[i + 8];                 /* in zwei 8-Byte Schl¸ssel aufteilen. */
   in[i]  = in2[i] = chain[i] = 0;              /* input + chaining value lîschen */
 }

 while (length)                                 /* Blockweise zu 8 Byte abarbeiten */
 {
   for (i = 0; i < 8 ; i++)                     /* Eingabe in vielfaches */
   {                                            /* von 8 zerlegen */
       if (length > 0)
       {
           in[i] = input[i + j];
           length--;
       }
       else
       {
           if (par1 == DECRYPT) return(-4);     /* Immer vielfaches von 8 */
           if (isoflag) { in[i]= 0x80; isoflag--; } /* erstes Byte nach ISO */
           else           in[i]= 0;                 /* Rest mit Nullen fÅllen  */
       }

       if (par2 == CBC && par1 != DECRYPT)  /* M und E */
               in[i]= (char)(in[i]^chain[i]);       /* next block XOR chaining value */
   }
   if (length < 0) length = 0;                      /* Mit 0x80 auffÅllen beenden */

   if (par1 == DECRYPT) 
   {
   /* decrypt(in, key, chain);  */                   /* entschlÅsseln */  
    decrypt(in, key_left, chain);                    /* Triple-DES Anpassung */
    encrypt(chain, key_right, buffer);
    decrypt(buffer, key_left, chain); 
   }    
   else 
   {
     /* encrypt(in, key, chain); */                 /* verschlÅsseln */
     encrypt(in, key_left, chain);                  /* Triple-DES Anpassung */
     // start modification by aig
     if (( length == 0) || (par1 != MAC) )//
     { //
		   if (bNotLastRound == 0)
       {
			   decrypt(chain, key_right, buffer);
         encrypt(buffer, key_left, chain); 
       }
		   else
			   bNotLastRound = 0;
     } //end modification aig
   }

   if ( (par2 == CBC) && (par1 == DECRYPT) )
   {
       for (i = 0; i < 8; i++)
       {
           chain[i] = (char) (in2[i] ^ chain[i]); /* next block XOR chaining value */
           in2[i]   = in[i];                      /* Zu entschl. Daten 8 Byte zuvor */
       }
   }

   if (par1 != MAC) for(i = 0; i < 8; i++) output[i + j] = chain[i];
   j += 8;
   if (!length && isoflag && par1 != DECRYPT) length= -1;/* Mit 0x80 auffÅl. */
 }

 if (par1 == MAC)                        /* Summenberechnung */
 {
   for(i = 0; i < 8; i++) output[i] = chain[i];
   return(8);
 }
 else
 {
   if (isoflag && par1 == DECRYPT && j)  /* EntschlÅsseln nach ISO */
   {
       for(i = j - 1; i > j - 9; i--)        /* ohne 0x80 0x00 usw. */
       {
           if (output[i] == 0x80) return(i); /* neue DatenlÑnge zurÅck */
           if (output[i]) break;             /* Abbruch, keine ISO def.*/
       }
   }
 }
 return(j);                                  /* VerschlÅsseln, neue DatenlÑnge */
}


///******************************************************/
//  int hash_des(char *input, int length,                /* DES - Hash */
//      char *output, char round, char pmode, char piso) /* Funktion */
///******************************************************/
//{                                                      /* ECB - Einzelblock */
// int  i, j = 0, isoflag = 0, mode = SINGLE;
//
// static unsigned char key1[10], key2[10];      // Buffer fÅr SchlÅssel
// unsigned char in[10], chain1[10], chain2[10]; // Buffe fÅr  Daten
//
// if (piso  == ISO)    isoflag++;         /* Mit 0x80 oder 0x00 auffÅllen */
//                                         /* wenn Daten kleiner 8 Byte */
// if (pmode == DOUBLE) mode = DOUBLE;     /* HASH Mode single oder double */
//
// if (round == FIRST)                     /* Key initialisieren */
// {
//   for (i = 0 ; i < 8 ; i++)
//   {
//       key1[i] = 0x52;                   /* SchlÅssel Åbergeben */
//       key2[i] = 0x25;
//   }
// }
//
// for (i = 0 ; i < 8 ; i++)               /* Felder vorbelegen */
// {
//   in[i] = chain1[i] = chain2[i] = 0;    /* input + chaining value lîschen */
// }
//
// while (length)                          /* Blockweise zu 8 Byte abarbeiten */
// {
//   for (i = 0; i < 8 ; i++)              /* Eingabe in vielfaches */
//   {                                     /* von 8 zerlegen */
//       if (length > 0)
//       {
//           in[i] = input[i + j];
//           length--;
//       }
//       else
//       {
//           if (isoflag) { in[i]= 0x80; isoflag--; } /* erstes Byte nach ISO */
//           else           in[i]= 0;              /* Rest mit Nullen fÅllen  */
//       }
//   }
//   if (length < 0) length = 0;           /* Mit 0x80 auffÅllen beenden */
//
//   key1[0] = (key1[0] | 0x40) & 0xDF;    /* x10x xxxx */
//   encrypt(in, key1, chain1);            /* verschlÅsseln */
//
//   if (mode == DOUBLE)
//   {
//       key2[0] = (key2[0] | 0x20) & 0xBF;/* x01x xxxx */
//       encrypt(in, key2, chain2);        /* verschlÅsseln */
//   }
//
//   for (i = 0; i < 8; i++)
//   {
//       chain1[i] ^= in[i];               /* Ergebnis mit Input XOR */
//       if (mode == DOUBLE)
//       {
//           chain2[i] ^= in[i];           /* Ergebnis mit Input XOR */
//           if (i < 4)
//           {
//               key1[i] = chain1[i];
//               key2[i] = chain2[i];
//           }
//           else
//           {
//               key1[i] = chain2[i];
//               key2[i] = chain1[i];
//           }
//       }
//       else key1[i] = chain1[i];         /* SchlÅssel Åbergeben */
//   }
//   j += 8;
//   if (!length && isoflag) length= -1;   /* Mit 0x80 auffÅl. */
// }
//
// for(i=0; i < 8; i++) output[i]= key1[i];/* Daten an Ausgabebuffer */
// if (mode == DOUBLE)
// {
//    for(;i<16;i++) output[i]= key2[i-8]; /* Daten an Ausgabebuffer */
// }
// return(i);           /* HASH DatenlÑnge: 8 (SINGLE) / 16 (DOUBLE) */
//}
