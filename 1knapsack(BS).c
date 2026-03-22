#include<stdio.h>

int maxprofit=0;

void knapsack(int i,int weight,int profit,int n,int w,int val[],int wt[])
{
   if(weight>w)
   {
      return;
    }
    if(profit>maxprofit)
    {
       maxprofit=profit;
    }
    for(int j=1;j<n;j++)
    {
        knapsack(j+1,weight+wt[j],profit+val[j],n,w,val,wt);
    }
}

int main()
{
    int n=4,w=5;
    int wt[]={2,1,3,2};
    int val[]={12,10,20,15};
    knapsack(0,0,0,n,w,val,wt);
    printf("Maximum profit is %d",maxprofit);
    return 0;
}