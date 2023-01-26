#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define GENMAX 50
#define STATENO 7
#define ACTIONNO 2
#define ALPHA 0.1
#define GAMMA 0.9
#define EPSILON 0.3
#define SEED 32767
#define REWARD 10

#define GOAL 6
#define UP 0
#define DOWN 1
#define LEVEL 2

int rand0or1();
double frand();
void prinfqvalue(double qvalue[][ACTIONNO]);
int selecta(int s,double qvalue[][ACTIONNO]);
double updateq(int s,int snext,int a,double qvalue[][ACTIONNO]);
int set_a_by_q(int s,double qvalue[][ACTIONNO]);
int nexts(int s,int a);

int main(){
    int i,j;
    int s,snext;
    int t;
    int a;
    double qvalue[STATENO][ACTIONNO];

    srand(SEED);

    for (i = 0; i < STATENO; ++i) {
        for (j = 0; j < ACTIONNO; ++j) {
            qvalue[i][j]=frand();
        }
    }
    prinfqvalue(qvalue);

    for (i = 0; i < GENMAX; ++i) {
        s=0;
        for (t = 0; t < LEVEL; ++t) {
            a= selecta(s,qvalue);
            fprintf(stderr," s= %d a=%d\n",s,a);
            snext=nexts(s,a);
            qvalue[s][a]= updateq(s,snext,a,qvalue);
            s=snext;
        }
        prinfqvalue(qvalue);
    }

    return 0;
}

double updateq(int s,int snext,int a,double qvalue[][ACTIONNO]){
    double qv;
    if (snext == GOAL)
        qv = qvalue[s][a]+ALPHA*(REWARD-qvalue[s][a]);
    else
        qv=qvalue[s][a]+ALPHA*(GAMMA*qvalue[s][set_a_by_q(snext,qvalue)]-qvalue[s][a]);
    return qv;
}

int selecta(int s,double qvalue[][ACTIONNO]){
    int a;
    if (frand() < EPSILON)
        a=rand0or1();
    else
        a= set_a_by_q(s,qvalue);
    return a;
}

int set_a_by_q(int s,double qvalue[][ACTIONNO]){
    if ((qvalue[s][UP] > qvalue[s][DOWN]))
        return UP;
    else return DOWN;
}

int nexts(int s,int a){
    return s*2+1+a;
}

void prinfqvalue(double qvalue[][ACTIONNO]){
    int i,j;
    for (i = 0; i < STATENO; ++i) {
        for (j = 0; j < ACTIONNO; ++j)
            printf("%.3f ",qvalue[i][j]);
        printf("\t");
    }
    printf("\n");
}

double frand(void){
    return (double)rand()/RAND_MAX;
}

int rand0or1(){
    int rnd;
    while ((rnd=rand())==RAND_MAX);
    return (int)((double)rnd/RAND_MAX*2);
}