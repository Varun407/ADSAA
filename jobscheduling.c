#include<stdio.h>

struct job{
    int id;
    int deadline;
    int profit;
};

typedef struct job Job;

void sortjobs(Job jobs[],int n)
{
    Job temp;
    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(jobs[i].profit<jobs[j].profit)
            {
                temp=jobs[i];
                jobs[i]=jobs[j];
                jobs[j]=temp;
            }
        }
    }
}

void jobscheduling(Job jobs[],int n)
{
    int slot[n+1];
    int totalprofit=0;
    for(int i=1;i<=n;i++)
    {
        slot[i]=-1;
    }
    for(int i=0;i<n;i++)
    {
        for(int j=jobs[i].deadline;j>0;j--)
        {
            if(slot[j]==-1)
            {
                slot[j]=jobs[i].id;
                totalprofit+=jobs[i].profit;
                break;
            }
        }
    }
    printf("The scheduled jobs are: ");
    for(int i=1;i<=n;i++)
    {
        if(slot[i]!=-1)
        {
            printf("J%d ",slot[i]);

        }

    }
    printf("\nThe total profit is: %d", totalprofit);

}

int main()
{
    Job jobs[]={
        {1,2,100},
        {2,1,19},
        {3,2,27},
        {4,1,25},
        {5,3,15}
    };
    int n=sizeof(jobs)/sizeof(jobs[0]);
    sortjobs(jobs,n);
    jobscheduling(jobs,n);
    return 0;
}
