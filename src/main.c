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

    putchar('\n');
    ShowMoStrInfo(fpr, 0);
    ShowMoStrContent(fpr, 0);

    putchar('\n');
    ShowMoStrInfo(fpr, 1);
    ShowMoStrContent(fpr, 1);

    return 0;
}
