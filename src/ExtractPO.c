#include"ExtractPO.h"
//#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define STR_MO_ENTRY_SIZE 8

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


int GetMoHeader(FILE * fpMo, p_mo_header_t pMoHeader){
    fseek(fpMo,0,SEEK_SET);
    fread(&pMoHeader->Magic,sizeof(char),4,fpMo);

    fseek(fpMo,8,SEEK_SET);
    fread(&pMoHeader->StringNumber,sizeof(char),4,fpMo);

    fread(&pMoHeader->OffsetTableOfOrigin,sizeof(char),4,fpMo);
    fread(&pMoHeader->OffsetTableOfTrans,sizeof(char),4,fpMo);

    fread(&pMoHeader->SizeOfHash,sizeof(char),4,fpMo);
    fread(&pMoHeader->OffsetOfHash,sizeof(char),4,fpMo);
}

int GetStrInfo(FILE * fpMo, p_str_info_t pStrInfo, unsigned int StrIndex){
    mo_header_t MoHeader;
    GetMoHeader(fpMo, &MoHeader);

    fseek(fpMo, MoHeader.OffsetTableOfOrigin+StrIndex*STR_MO_ENTRY_SIZE, SEEK_SET);
    fread(&pStrInfo->LenOfOrigin, sizeof(char), 4, fpMo);
    fread(&pStrInfo->OffsetOfOrigin, sizeof(char), 4, fpMo);

    fseek(fpMo, MoHeader.OffsetTableOfTrans+StrIndex*STR_MO_ENTRY_SIZE, SEEK_SET);
    fread(&pStrInfo->LenOfTrans, sizeof(char), 4, fpMo);
    fread(&pStrInfo->OffsetOfTrans, sizeof(char), 4, fpMo);
}

int ShowMoHeader(FILE * fpMo){
    mo_header_t MoHeader;
    GetMoHeader(fpMo, &MoHeader);

    printf("magic: 0x%x \tstr_num: %u\n",MoHeader.Magic,MoHeader.StringNumber);
    printf("off_tab_origin: 0x%x \toff_tab_trans: 0x%x\n",
        MoHeader.OffsetTableOfOrigin,MoHeader.OffsetTableOfTrans);
    printf("size_of_hash: 0x%x \toff_of_hash: 0x%x\n",
        MoHeader.SizeOfHash,MoHeader.OffsetOfHash);
}

int ShowMoStrInfo(FILE * fpMo, unsigned int StrIndex){
    str_info_t StrInfo;
    GetStrInfo(fpMo, &StrInfo, StrIndex);

    printf("info of string # %u\n", StrIndex);
    printf("orig_len: %u \t orig_off: 0x%x\n", StrInfo.LenOfOrigin, StrInfo.OffsetOfOrigin);
    printf("trans_len: %u \t trans_off: 0x%x\n", StrInfo.LenOfTrans, StrInfo.OffsetOfTrans);
}