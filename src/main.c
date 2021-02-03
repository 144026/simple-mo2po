#include"ExtractPO.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LEN 256

int main(int argc, char * argv[]){

    char infile[LEN] = "../trans/main.zh.mo";
    char outfile[LEN] = "../trans/out.mo";

    FILE * fpr = fopen(infile,"rb+");
    FILE * fpw = fopen(outfile,"wb+");

    ShowMoHeader(fpr);
    ShowMoAllStr(fpr, fpw);

    return 0;
}
