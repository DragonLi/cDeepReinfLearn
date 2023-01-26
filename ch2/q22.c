#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define GENMAX 100
#define STATENO 64
#define ACTIONNO 4
#define ALPHA 0.1
#define GAMMA 0.9
#define EPSILON 0.3
#define SEED 32767
#define REWARD 10

#define GOAL 54
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define LEVEL 512

int rand03();
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
            if (i<=7) qvalue[i][UP]=0;
            if (i>=56) qvalue[i][DOWN]=0;
            if (i%8 == 0) qvalue[i][LEFT]=0;
            if (i%8 == 7) qvalue[i][RIGHT]=0;
        }
    }
    prinfqvalue(qvalue);

    for (i = 0; i < GENMAX; ++i) {
        s=0;
        for (t = 0; t < LEVEL; ++t) {
            a= selecta(s,qvalue);
            fprintf(stderr,"%d: s= %d a=%d\n",t,s,a);
            snext=nexts(s,a);
            qvalue[s][a]= updateq(s,snext,a,qvalue);
            s=snext;
            if (s == GOAL) break;
        }
        fprintf(stderr,"\n");
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
        do {
            a=rand03();
        } while (qvalue[s][a] == 0);
    else
        a= set_a_by_q(s,qvalue);
    return a;
}

int set_a_by_q(int s,double qvalue[][ACTIONNO]){
    double maxq=0;
    int maxaction=0;
    int i;
    for (i = 0; i < ACTIONNO; ++i) {
        if ((qvalue[s][i])>maxq){
            maxq=qvalue[s][i];
            maxaction=i;
        }
    }
    return maxaction;
}

int nexts(int s,int a){
    int next_s_value[]={-8,8,-1,1};
    return s+next_s_value[a];
}

void prinfqvalue(double qvalue[][ACTIONNO]){
    int i,j;
    for (i = 0; i < STATENO; ++i) {
        for (j = 0; j < ACTIONNO; ++j)
            printf("%.3f ",qvalue[i][j]);
        printf("\n");
    }
    printf("\n");
}

double frand(void){
    return (double)rand()/RAND_MAX;
}

int rand03(){
    int rnd;
    while ((rnd=rand())==RAND_MAX);
    return (int)((double)rnd/RAND_MAX*4);
}