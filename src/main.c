#include"ExtractPO.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LEN 256

int main(int argc, char * argv[]){

    char infile[LEN] = "../trans/main.zh.mo";
    char outfile[LEN] = "../trans";

    FILE * fpr = fopen(infile,"rb+");

    ShowMoHeader(fpr);
    ShowMoStrInfo(fpr, 0);
    return 0;
}
