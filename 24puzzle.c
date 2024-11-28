#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define epsilon 0.001
#define equal(a,b) (a)-(b)<epsilon&&(a)-(b)>-epsilon
int flag[4]={1,1,1,1};
double a[4];
double method[6];
char oprator[3];
int add(double *p, double *new){
    for(int i=0;i<4;i++){
        if(equal(*new,p[i])){
            flag[i]++;
            return i;
        }
    }
    for(int i=0;i<4;i++){
        if(!flag[i]){
            double temp;
            temp=p[i];
            p[i]=*new;
            *new=temp;
            flag[i]++;
            return i;
        }
    }
}
void search(double *p,int n){
    if(n==1){
        int k=-1;
        while(!flag[++k]);
        if(equal(p[k],24)){
            for(int i=0;i<3;i++){
                printf("step%d: %.2lf %c %.2lf -> ",i+1,method[2*i],oprator[i],method[2*i+1]);
            }
            printf(" 24\n");
        }
        return;
    }
    for(int i=0;i<4;i++){
        if(!flag[i]) continue;
        flag[i]--;
        for(int j=i;j<4;j++){
            if(!flag[j]) continue;
            flag[j]--;
            int k=0;
            double new;
            method[(4-n)*2]=p[i];
            method[(4-n)*2+1]=p[j];
            double temp=p[j];

            new=p[i]+temp;
            oprator[4-n]='+';
            k=add(p,&new);
            search(p,n-1);
            flag[k]--;
            p[k]=new;

            new=p[i]-temp;
            oprator[4-n]='-';
            k=add(p,&new);
            search(p,n-1);
            flag[k]--;
            p[k]=new;
            
            new=p[i]*temp;
            oprator[4-n]='*';
            k=add(p,&new);
            search(p,n-1);
            flag[k]--;
            p[k]=new;

            if(!equal(temp,0)){
                new=p[i]/temp;
                oprator[4-n]='/';
                k=add(p,&new);
                search(p,n-1);
                flag[k]--;
                p[k]=new;
            }
            flag[j]++;
            p[j]=temp;
        }
        flag[i]++;
    }

}
int main(){
    for(int i=0;i<4;i++){
        scanf("%lf",&a[i]);
    }
    for(int i=0;i<4;i++){
        if(!flag[i]) continue;
        for(int j=i+1;j<4;j++){
            if(a[j]==a[i]){
                flag[i]++;
                flag[j]--;
            }
        }
    }
    search(a,4);
    return 0;
}