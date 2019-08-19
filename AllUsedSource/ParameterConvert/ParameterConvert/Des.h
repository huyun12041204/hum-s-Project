
//#include "stdafx.h"                         
/* Parameter 1, encrypt, decrypt, mac */
 #define  ENCRYPT   'E'          /* Encrypt, verschl�sseln */
 #define  DECRYPT   'D'          /* Decrypt, entschl�sseln */
 #define  MAC       'M'          /* message authentication code, Pr�fsumme */

                                 /* Parameter 2, CBC oder ECB */
 #define  CBC       'C'          /* CBC - Cipherblock chaining */
 #define  ECB       'E'          /* ECB - electronic code book, Einzelblock */

                                 /* Parameter 3, Berechnung nach ISO */
 #define  ISO       'I'          /* ISO: Rest mit 0x80 auff�llen */
 #define  NOISO     'N'          /* oder Rest mit 0x00 auff�llen */

 #define  SINGLE    'S'          /* DES HASH Funktion */
 //#define  DOUBLE    'D'          /* SINGLE oder DOUBLE length 8 / 16 */

 #define  FIRST     'F'          /* DES-Schl�ssel neu laden */
 #define  NEXT      'N'          /* DES-Schl�ssel ist letzter HASH-Wert */

/**********************************************************************/

int des(unsigned char *key, unsigned char *input, int len, unsigned char *output, char par1, char par2, char par3);

int triple_des(unsigned char *keyin, unsigned char *input, int length, unsigned char *output, char par1, char par2, char par3); 

int hash_des(char *input, int length, char *output, char round, char pmode, char piso);

