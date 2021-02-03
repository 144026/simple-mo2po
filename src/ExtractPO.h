#ifndef __EXTARCT_PO
#define __EXTARCT_PO

#include<stdio.h>

//int ExtractPoText(FILE * fpMo, FILE * fpPO1);

int ShowMoHeader(FILE * fpMo);
int ShowMoStrInfo(FILE * fpMo, unsigned int StrIndex);
int ShowMoStrContent(FILE * fpMo, unsigned int StrIndex, FILE * fpDst);
int ShowMoAllStr(FILE * fpMo, FILE * fpDst);

#endif
