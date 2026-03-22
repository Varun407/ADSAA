#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#define V 4

struct Node{
    int dest;
    int weight;
    struct Node* next;
};
typedef struct Node * nptr;

nptr newNode(int dest,int weight)
{
    nptr node=(nptr)malloc(sizeof(struct Node));
    node->dest=dest;
    node->weight=weight;
    node->next=NULL;
    return node;
}

void addedge(nptr adj[],int src,int dest,int weight)
{
    nptr node=newNode(dest,weight);
    node->next=adj[src];
    adj[src]=node;
    node=newNode(src,weight);
    node->next=adj[dest];
    adj[dest]=node;
}

int mindistance(int dist[],int visited[])
{
    int min=INT_MAX,min_index=-1;
    for(int v=0;v<V;v++)
    {
        if(!visited[v] && dist[v]<min)
        {
            min=dist[v];
            min_index=v;
        }
    }
    return min_index;
}

void dijkstra(nptr adj[],int src)
{
    int dist[V];
    int visited[V];
    for(int i=0;i<V;i++)
    {
        dist[i]=INT_MAX;
        visited[i]=0;
    }
    dist[src]=0;
    for(int count=0;count<V-1;count++)
    {
        int u=mindistance(dist,visited);
        visited[u]=1;
        nptr temp=adj[u];
        while(temp!=NULL)
        {
            int v=temp->dest;
            int weight=temp->weight;
            if(!visited[v] && dist[u]+weight<dist[v])
            {
                dist[v]=dist[u]+weight;
            }
            temp=temp->next;
        }
    }
    printf("Vertex \t Distance from Source\n");
    for(int i=0;i<V;i++)
    {
        printf("%d \t\t %d\n",i,dist[i]);
    }
}

int main()
{
    nptr adj[V];
    for(int i=0;i<V;i++)
    {
        adj[i]=NULL;
    }
    addedge(adj,0,1,2);
    addedge(adj,0,2,4);
    addedge(adj,0,3,1);
    addedge(adj,1,3,7);
    addedge(adj,2,3,3);
    dijkstra(adj,0);
    return 0;
}