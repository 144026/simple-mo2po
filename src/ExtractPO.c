#include"ExtractPO.h"
//#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _mo_header
{
    unsigned int magic;
    unsigned int str_num;
    unsigned int OffsetTableOfOrigin;
    unsigned int OffsetTableOfTrans;
    unsigned int SizeOfHash;
    unsigned int OffsetOfHash;
} mo_header_t, *p_mo_header_t;

int GetMoHeader(FILE * fpMo, p_mo_header_t pMoHeader){
    fseek(fpMo,0,SEEK_SET);
    fread(&pMoHeader->magic,sizeof(char),4,fpMo);

    fseek(fpMo,8,SEEK_SET);
    fread(&pMoHeader->str_num,sizeof(char),4,fpMo);

    fread(&pMoHeader->OffsetTableOfOrigin,sizeof(char),4,fpMo);
    fread(&pMoHeader->OffsetTableOfTrans,sizeof(char),4,fpMo);

    fread(&pMoHeader->SizeOfHash,sizeof(char),4,fpMo);
    fread(&pMoHeader->OffsetOfHash,sizeof(char),4,fpMo);
}

int ShowMoHeader(FILE * fpMo){
    mo_header_t MoHeader;
    GetMoHeader(fpMo, &MoHeader);

    printf("magic: 0x%x \tstr_num: %u\n",MoHeader.magic,MoHeader.str_num);
    printf("off_tab_origin: 0x%x \toff_tab_trans: 0x%x\n",
        MoHeader.OffsetTableOfOrigin,MoHeader.OffsetTableOfTrans);
    printf("size_of_hash: 0x%x \toff_of_hash: 0x%x\n",
        MoHeader.SizeOfHash,MoHeader.OffsetOfHash);
}