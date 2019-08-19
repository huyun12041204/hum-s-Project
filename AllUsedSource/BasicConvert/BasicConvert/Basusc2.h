
#define NOT_SUPPORTED	-1
#define HZ_NUM			6763
#define SYM_NUM			717
#define CODE_NUM		(HZ_NUM+SYM_NUM)

extern const unsigned short uniAUnicode[CODE_NUM];
extern const unsigned short uniAGbkcode[CODE_NUM];
extern const unsigned short gbkAGbkcode[CODE_NUM];
extern const unsigned short gbkAUnicode[CODE_NUM];


 
 int GBK2UCS(BYTE *ucInput,int iInputLen,BYTE *ucOutput,int *OutputLen);
 
 int UCS2GBK(BYTE *ucInput,int iInputLen,BYTE *ucOutput,int *OutputLen);
 
 