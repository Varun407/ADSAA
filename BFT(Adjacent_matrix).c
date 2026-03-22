#include<stdio.h>
#include<stdlib.h>
#define max 10

typedef int item;
item q[max];
int front,rear;
void addq(int x)
{
    if(rear==max-1)
    {
        printf("Queue overflow\n");
        exit(1);
    }
    rear++;
    q[rear]=x;
}

int deleteq()
{
    if(front==rear)
    {
        printf("Queue underflow\n");
        exit(1);
    }
    front++;
    return q[front];
}

int qempty()
{
    return front==rear;
}
void readadj(int a[10][10],int n)
{
    int u,v;
    printf("Enter the edges (u v) and 0 0 to stop:\n");
    scanf("%d%d",&u,&v);
    while(u!=0 && v!=0)
    {
        a[u][v]=1;
        a[v][u]=1;
        scanf("%d%d",&u,&v);
    }
}

void bfs(int a[10][10],int n,int v)
{
    int i,w,u;
    int visited[10];
    for(i=1;i<=n;i++)
        visited[i]=0;
    front=rear=-1;
    printf("BFS traversal starting from vertex %d:\n",v);
    visited[v]=1;
    addq(v);
    while(!qempty())
    {
      u=deleteq();
      printf("%d ",u);   
      for(w=1;w<=n;w++)
      {
          if(a[u][w]==1 && visited[w]==0)
          {
              visited[w]=1;
              addq(w);
          }
      }
    }
}

int main()
{
    int a[10][10],n,v;
    printf("Enter the number of vertices (max 10): ");
    scanf("%d",&n);
    readadj(a,n);
    printf("Enter the starting vertex for BFS: ");
    scanf("%d",&v);
    bfs(a,n,v);
    return 0;
}