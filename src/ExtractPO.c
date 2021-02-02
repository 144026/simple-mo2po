#include"ExtractPO.h"
//#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int ShowMoHeader(FILE * fpMo){
    unsigned int magic, str_num;
    unsigned int OffsetTableOfOrigin;
    unsigned int OffsetTableOfTrans;
    unsigned int SizeOfHash, OffsetOfHash;

    fseek(fpMo,0,SEEK_SET);
    fread(&magic,sizeof(char),4,fpMo);

    fseek(fpMo,8,SEEK_SET);
    fread(&str_num,sizeof(char),4,fpMo);

    fread(&OffsetTableOfOrigin,sizeof(char),4,fpMo);
    fread(&OffsetTableOfTrans,sizeof(char),4,fpMo);

    fread(&SizeOfHash,sizeof(char),4,fpMo);
    fread(&OffsetOfHash,sizeof(char),4,fpMo);

    printf("magic: 0x%x \tstr_num: %u\n",magic,str_num);
    printf("off_tab_origin: 0x%x \toff_tab_trans: 0x%x\n",OffsetTableOfOrigin,OffsetTableOfTrans);
    printf("size_of_hash: 0x%x \toff_of_hash: 0x%x\n",SizeOfHash,OffsetOfHash);
}