#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"mo.h"

#define LEN 256

int main(int argc, char * argv[]){

	if(3 != argc){
		fprintf(stderr,"usage: %s <input_mo_filename> <output_po_filename>\n",argv[0]);
		fprintf(stderr,"example: %s main.zh.mo out.po\n",argv[0]);
		exit(1);
	}

    FILE * fpr = fopen(argv[1],"rb+");
	if(NULL == fpr){
		fprintf(stderr,"can't open %s\n",argv[1]);
		exit(2);
	}

    FILE * fpw = fopen(argv[2],"wb+");
	if(NULL == fpr){
		fprintf(stderr,"can't open %s\n",argv[2]);
		exit(3);
	}

    ShowMoHeader(fpr);
    Mo2Po(fpr, fpw);

    return 0;
}
