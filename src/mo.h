#ifndef MO_
#define MO_

#include<stdio.h>

#define MO_STR_ENTRY_SIZE 8
#define MO_STR_NUL_SIZE 8
#define MO_STR_EXT_SIZE 32

typedef struct _mo_header{
    unsigned int Magic;
    unsigned int StringNumber;
    unsigned int OffsetTableOfOrigin;
    unsigned int OffsetTableOfTrans;
    unsigned int SizeOfHash;
    unsigned int OffsetOfHash;
} mo_header_t, *p_mo_header_t;

typedef struct _str_info{
    unsigned int LenOfOrigin;
    unsigned int OffsetOfOrigin;
    unsigned int LenOfTrans;
    unsigned int OffsetOfTrans;
} str_info_t, *p_str_info_t;

int ShowMoHeader(FILE * fpMo);
int ShowMoStrInfo(FILE * fpMo, unsigned int StrIndex);
int ShowMoStrContent(FILE * fpMo, unsigned int StrIndex, FILE * fpDst);
int ShowMoAllStr(FILE * fpMo, FILE * fpDst);
int Mo2Po(FILE * fpMo, FILE * fpDst);

#endif // MO_
