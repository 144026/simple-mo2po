#include"ExtractPO.h"
#include<stdlib.h>

// read MO file header info
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

// read len & offset of a string by its index
int GetStrInfo(FILE * fpMo, p_str_info_t pStrInfo, unsigned int StrIndex){
    mo_header_t MoHeader;
    GetMoHeader(fpMo, &MoHeader);

    fseek(fpMo, MoHeader.OffsetTableOfOrigin+StrIndex*MO_STR_ENTRY_SIZE, SEEK_SET);
    fread(&pStrInfo->LenOfOrigin, sizeof(char), 4, fpMo);
    fread(&pStrInfo->OffsetOfOrigin, sizeof(char), 4, fpMo);

    fseek(fpMo, MoHeader.OffsetTableOfTrans+StrIndex*MO_STR_ENTRY_SIZE, SEEK_SET);
    fread(&pStrInfo->LenOfTrans, sizeof(char), 4, fpMo);
    fread(&pStrInfo->OffsetOfTrans, sizeof(char), 4, fpMo);
}

// print MO file header info to stdout
int ShowMoHeader(FILE * fpMo){
    mo_header_t MoHeader;
    GetMoHeader(fpMo, &MoHeader);

    printf("magic: 0x%x \tstr_num: %u\n",MoHeader.Magic,MoHeader.StringNumber);
    printf("off_tab_origin: 0x%x \toff_tab_trans: 0x%x\n",
        MoHeader.OffsetTableOfOrigin,MoHeader.OffsetTableOfTrans);
    printf("size_of_hash: 0x%x \toff_of_hash: 0x%x\n",
        MoHeader.SizeOfHash,MoHeader.OffsetOfHash);
}

// print len & offset of a string to stdout, by its index
int ShowMoStrInfo(FILE * fpMo, unsigned int StrIndex){
    str_info_t StrInfo;
    GetStrInfo(fpMo, &StrInfo, StrIndex);

    printf("info of string # %u\n", StrIndex);
    printf("orig_len: %u \t orig_off: 0x%x\n", StrInfo.LenOfOrigin, StrInfo.OffsetOfOrigin);
    printf("trans_len: %u \t trans_off: 0x%x\n", StrInfo.LenOfTrans, StrInfo.OffsetOfTrans);
}

// write the content of a string(orig & trans) to a FILE
int ShowMoStrContent(FILE * fpMo, unsigned int StrIndex, FILE * fpDst){
    str_info_t StrInfo;
    GetStrInfo(fpMo, &StrInfo, StrIndex);

    char * pOrigin = (char*)malloc(MO_STR_NUL_SIZE+StrInfo.LenOfOrigin*sizeof(char));
    fseek(fpMo, StrInfo.OffsetOfOrigin, SEEK_SET);
    fread(pOrigin, sizeof(char), MO_STR_NUL_SIZE+StrInfo.LenOfOrigin, fpMo);
    fprintf(fpDst, "%s\n", pOrigin);

    char * pTrans = (char*)malloc(MO_STR_NUL_SIZE+StrInfo.LenOfTrans*sizeof(char));
    fseek(fpMo, StrInfo.OffsetOfTrans, SEEK_SET);
    fread(pTrans, sizeof(char), MO_STR_NUL_SIZE+StrInfo.LenOfTrans, fpMo);
    fprintf(fpDst, "%s\n", pTrans);

    free(pOrigin);
    free(pTrans);
}

// write the content of ALL strings(orig & trans) to a FILE
int ShowMoAllStr(FILE * fpMo, FILE * fpDst){
    mo_header_t MoHeader;
    GetMoHeader(fpMo, &MoHeader);

    for(int i=0; i<MoHeader.StringNumber; ++i){
        ShowMoStrContent(fpMo, i, fpDst);
    }
}

// change a string read from MO file, into the format of PO file
int MoStr2PoStr(char * MoStr, char * PoStr){
    int MoIndex=0;
    int PoIndex=0;
    while('\0' != MoStr[MoIndex]){
        if('\n' == MoStr[MoIndex]){
            PoStr[PoIndex++]='"';
            PoStr[PoIndex++]=MoStr[MoIndex++];
            PoStr[PoIndex++]='"';
        }
        else if('"' == MoStr[MoIndex]){
            PoStr[PoIndex++]='\\';
            PoStr[PoIndex++]=MoStr[MoIndex++];
        }
        else{
            PoStr[PoIndex++]=MoStr[MoIndex++];
        }
    }
    PoStr[PoIndex]='\0';
}

// read MO file, output a PO file
int Mo2Po(FILE * fpMo, FILE * fpDst){
    mo_header_t MoHeader;
    GetMoHeader(fpMo, &MoHeader);

    for(int i=0; i<MoHeader.StringNumber; ++i){
        str_info_t StrInfo;
        GetStrInfo(fpMo, &StrInfo, i);

        //read original string
        char * pOrigin = (char*)malloc(MO_STR_NUL_SIZE+StrInfo.LenOfOrigin*sizeof(char));
        fseek(fpMo, StrInfo.OffsetOfOrigin, SEEK_SET);
        fread(pOrigin, sizeof(char), MO_STR_NUL_SIZE+StrInfo.LenOfOrigin, fpMo);

        //read translated string
        char * pTrans = (char*)malloc(MO_STR_NUL_SIZE+StrInfo.LenOfTrans*sizeof(char));
        fseek(fpMo, StrInfo.OffsetOfTrans, SEEK_SET);
        fread(pTrans, sizeof(char), MO_STR_NUL_SIZE+StrInfo.LenOfTrans, fpMo);

        //change original string to PO-file format, write to ouput file
        char * pTemp = (char*)malloc(MO_STR_EXT_SIZE+MO_STR_NUL_SIZE+StrInfo.LenOfOrigin*sizeof(char));
        MoStr2PoStr(pOrigin, pTemp);
        fprintf(fpDst, "msgid \"%s\"\n", pTemp);
        free(pOrigin);
        free(pTemp);

        //change translated string to PO-file format, write to ouput file
        pTemp = (char*)malloc(MO_STR_EXT_SIZE+MO_STR_NUL_SIZE+StrInfo.LenOfTrans*sizeof(char));
        MoStr2PoStr(pTrans, pTemp);
        fprintf(fpDst, "msgstr \"%s\"\n\n", pTemp);
        free(pTrans);
        free(pTemp);
    }
}
