#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define SEED    65535
#define LASTNO  1000
#define GU      0
#define CYOKI   1
#define PA      2

int hand(double rate[]);
double frand(void);

int main(int argc,char *argv[]){
    if (argc<4){
        fprintf(stderr,"使用方法 randhandgen (石头的比例)(剪刀的比例)(布的比例)\n");
        exit(1);
    }

    srand(SEED);

    int n;
    double rate[3]={atof(argv[1]),atof(argv[1]),atof(argv[1])};

    for (n=0;n<LASTNO;++n){
        printf("%d\n",hand(rate));
    }

    return 0;
}

int hand(double rate[]){
    double gu,cyoki,pa;
    gu=rate[GU]*frand();
    cyoki=rate[CYOKI]*frand();
    pa=rate[PA]*frand();
    if (gu>cyoki){
        if(gu>pa) return GU;
        else      return PA;
    } else{
        if(cyoki>pa) return CYOKI;
        else         return PA;
    }
}

double frand(void){
    return (double)rand()/RAND_MAX;
}