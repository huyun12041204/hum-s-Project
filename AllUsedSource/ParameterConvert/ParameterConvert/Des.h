
//#include "stdafx.h"                         
/* Parameter 1, encrypt, decrypt, mac */
 #define  ENCRYPT   'E'          /* Encrypt, verschlÅsseln */
 #define  DECRYPT   'D'          /* Decrypt, entschlÅsseln */
 #define  MAC       'M'          /* message authentication code, PrÅfsumme */

                                 /* Parameter 2, CBC oder ECB */
 #define  CBC       'C'          /* CBC - Cipherblock chaining */
 #define  ECB       'E'          /* ECB - electronic code book, Einzelblock */

                                 /* Parameter 3, Berechnung nach ISO */
 #define  ISO       'I'          /* ISO: Rest mit 0x80 auffÅllen */
 #define  NOISO     'N'          /* oder Rest mit 0x00 auffÅllen */

 #define  SINGLE    'S'          /* DES HASH Funktion */
 //#define  DOUBLE    'D'          /* SINGLE oder DOUBLE length 8 / 16 */

 #define  FIRST     'F'          /* DES-SchlÅssel neu laden */
 #define  NEXT      'N'          /* DES-SchlÅssel ist letzter HASH-Wert */

/**********************************************************************/

int des(unsigned char *key, unsigned char *input, int len, unsigned char *output, char par1, char par2, char par3);

int triple_des(unsigned char *keyin, unsigned char *input, int length, unsigned char *output, char par1, char par2, char par3); 

int hash_des(char *input, int length, char *output, char round, char pmode, char piso);

