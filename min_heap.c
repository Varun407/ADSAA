#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<limits.h>

struct heap_struct
{
    int max_heap_size;
    int size;
    int * elements;
};

typedef struct heap_struct * PQ;
PQ create_pq(int max_elements)
{
    PQ H=(PQ)malloc(sizeof(struct heap_struct));
    H->max_heap_size=max_elements;
    H->size=0;
    H->elements=(int *)malloc((max_elements+1)*sizeof(int));
    H->elements[0]=INT_MIN;
    return H;
}

int search(PQ H,int x)
{
    int i;
    if(H->size==0 || x<H->elements[1])
        return -1;
    for(i=1;i<=H->size;i++)
    {
        if(x==H->elements[i])
            return i;
    }
    if(i>H->size)
        return -1;
}

void percolate_up(PQ H,int i)
{
    int temp=H->elements[i];
    while(i>1 && H->elements[i/2]>temp)
    {
        H->elements[i]=H->elements[i/2];
        i=i/2;
    }
    H->elements[i]=temp;
}

void percolate_down(PQ H,int i)
{
    int child;
    int temp=H->elements[i];
    for(;i*2<=H->size;i=child)
    {
        child=i*2;
        if((child!=H->size) && (H->elements[child+1]<H->elements[child]))
            child++;
        if(H->elements[child]<temp)
            H->elements[i]=H->elements[child];
        else
            break;
    }
    H->elements[i]=temp;
}

void delete_element(PQ H,int x)
{
    int i=search(H,x);
    if(i>H->size)
    {
        printf("element not found");
        return;
    }
    H->elements[i]=H->elements[H->size--];
    if(i>1 && H->elements[i]<H->elements[i/2])
        percolate_up(H,i);
    else
        percolate_down(H,i);
    printf("element deleted");
}
void insert(int x,PQ H)
{
    int i;
    if(H->size==H->max_heap_size)
    {
        printf("heap is full");
        return;
    }
    else
    {
        i=++H->size;
        H->elements[i]=x;
        percolate_up(H,i);
    }
}

void display(PQ H)
{
    int i;
    if(H->size==0)
        printf("heap is empty");
    else
    {
        for(i=1;i<=H->size;i++)
            printf("%d ",H->elements[i]);
    }
}

int delete_min(PQ H)
{
    int min_element;
    if(H->size==0)
    {
        printf("heap is empty");
        return H->elements[0];
    }
    min_element=H->elements[1];
    H->elements[1]=H->elements[H->size--];
    percolate_down(H,1);
    return min_element;
}

void build_heap(PQ H)
{
    int i;
    for(i=H->size/2;i>0;i--)
        percolate_down(H,i);
}

int main()
{
    PQ H;
    int choice,x;
    H=create_pq(30);
    while(1)
    {
        printf("\n1.INsert\n2.Delete min\n3.Delete element\n4.Search\n5.Display\n6.Build heap\n7.Exit\n");
        printf("enter your choice:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("enter element to insert:");
                scanf("%d",&x);
                insert(x,H);
                break;
            case 2:
                x=delete_min(H);
                if(x!=INT_MIN)
                    printf("deleted element is %d",x);
                break;
            case 3:
                printf("enter element to delete:");
                scanf("%d",&x);
                delete_element(H,x);
                break;
            case 4:
                printf("enter element to search:");
                scanf("%d",&x);
                int pos=search(H,x);
                if(pos>0)
                    printf("element found at %d",pos);
                else
                    printf("element not found");
                break;
            case 5:
                display(H);
                break;
            case 6:
                printf("enter number of elements:");
                scanf("%d",&H->size);
                if(H->size>H->max_heap_size)
                {
                    printf("number of elements exceeds maximum heap size");
                    H->size=0;
                    break;
                }
                printf("enter elements:\n");
                for(int i=1;i<=H->size;i++)
                    scanf("%d",&H->elements[i]);
                build_heap(H);
                printf("heap built successfully");
                break;
            case 7:
                printf("exiting...");
                exit(0);
            default:
                printf("invalid choice");
        }
    }
    return 0;

}