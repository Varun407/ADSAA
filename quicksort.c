#include<stdio.h>
int partition(int a[30],int low,int high)
{
    int i,j,k;
    k=a[low];
    i=low+1;
    j=high;
    do{
        while(i<=high && k>=a[i]) i++;
        while(j>=low && k<a[j]) j--;
        if(i<j)
        {
            int temp=a[i];
            a[i]=a[j];
            a[j]=temp;
        }
    }while(i<j);
    a[low]=a[j];
    a[j]=k;
    return j;
}

void quicksort(int a[30],int low,int high)
{
    int j;
    if(low<high)
    {
        j=partition(a,low,high);
        quicksort(a,low,j-1);
        quicksort(a,j+1,high);
    }
}

int main()
{
    int a[30],n,i;
    printf("Enter the number of elements: ");
    scanf("%d",&n);
    printf("Enter the elements:\n");
    for(i=0;i<n;i++)
        scanf("%d",&a[i]);
    quicksort(a,0,n-1);
    printf("Sorted elements:\n");
    for(i=0;i<n;i++)
        printf("%d ",a[i]);
}