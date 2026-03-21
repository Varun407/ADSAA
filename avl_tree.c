#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

typedef struct avlNode *anode;
struct avlNode
{
    int data,height;
    anode left,right;
};

int Max(int a,int b)
{
    return (a>b)?a:b;
}

int Height(anode P)
{
    if(P==NULL)
        return -1;
    else
        return P->height;
}
anode singlerotatewithleft(anode A)
{
    anode B=A->left;
    A->left=B->right;
    B->right=A;
    A->height=Max(Height(A->left),Height(A->right))+1;
    B->height=Max(Height(B->left),Height(B->right))+1;
    return B;
}

anode singlerotatewithright(anode A)
{
    anode B=A->right;
    A->right=B->left;
    B->left=A;
    A->height=Max(Height(A->left),Height(A->right))+1;
    B->height=Max(Height(B->left),Height(B->right))+1;
    return B;
}

anode doublerotatewithleft(anode A)
{
    A->left=singlerotatewithright(A->left);
    return singlerotatewithleft(A);
}

anode doublerotatewithright(anode A)
{
    A->right=singlerotatewithleft(A->right);
    return singlerotatewithright(A);
}

anode avlinsert(int x, anode t)
{
    if(t==NULL)
    {
        t=(anode)malloc(sizeof(struct avlNode));
        if(t==NULL)
        {
            printf("out of space");
        }
        else
        {
            t->data=x;
            t->height=0;
            t->left=t->right=NULL;
        }
    }
    else if(x<t->data)
    {
        t->left=avlinsert(x,t->left);
        if(Height(t->left)-Height(t->right)==2)
         if(x<t->left->data)
          {
            t=singlerotatewithleft(t);
          }
          else
          {
            t=doublerotatewithleft(t);
          }
    }
    else  if(x>t->data)
    {
        t->right=avlinsert(x,t->right);
        if(Height(t->right)-Height(t->left)==2)
         if(x>t->right->data)
            {
                t=singlerotatewithright(t);
            }
            else
            {
                t=doublerotatewithright(t);
            }
    }
    t->height=Max(Height(t->left),Height(t->right))+1;
    return t;
}

anode search(int x,anode t)
{
    while(t!=NULL)
    {
        if(x<t->data)
            t=t->left;
        else if(x>t->data)
            t=t->right;
        else
            break;
    }
    return t;
}

anode findmin(anode t)
{
    if(t!=NULL)
        while(t->left!=NULL)
            t=t->left;
    return t;
}

anode avldelete(int x,anode t)
{
    anode tmp;
    if(t==NULL)
      printf("element not found");
    else if(x<t->data)
        t->left=avldelete(x,t->left);
    else if(x>t->data)
        t->right=avldelete(x,t->right);
    else if(t->left&&t->right)
    {
        tmp=findmin(t->right);
        t->data=tmp->data;
        t->right=avldelete(tmp->data,t->right);
    }
    else
    {
        tmp=t;
        if(t->left==NULL)
            t=t->right;
        else if(t->right==NULL)
            t=t->left;
        free(tmp);
    }
    if(t==NULL)
        return t;
    t->height=Max(Height(t->left),Height(t->right))+1;
    if(Height(t->left)-Height(t->right)>1)
    {
        if(Height(t->left->left)-Height(t->left->right)>=0)
            t=singlerotatewithleft(t);
        else
            t=doublerotatewithleft(t);
    }
    if(Height(t->left)-Height(t->right)<-1)
    {
        if(Height(t->right->left)-Height(t->right->right)<=0)
            t=singlerotatewithright(t);
        else
            t=doublerotatewithright(t);
    }
    return t;
}
void inorderprint(anode root)
{
    if(root!=NULL)
    {
        inorderprint(root->left);
        printf("%d ",root->data);
        inorderprint(root->right);
    }
}
void inorder(anode root,FILE *fp)
{
    if(root!=NULL)
    {
        inorder(root->left,fp);
        fprintf(fp,"%d ",root->data);
        inorder(root->right,fp);
    }
}

int main()
{
    anode root=NULL;
    int choice,x;
    FILE *fin,*fout;
    fin=fopen("input.txt","r");
    if(fin==NULL)
    {
        printf("cannot open file");
        return -1;
    }
    while(fscanf(fin,"%d",&x)==1)
    {
        root=avlinsert(x,root);
    }
    fclose(fin);
    fout=fopen("output.txt","w");
    fprintf(fout,"inorder after file insertion:\n");
    inorder(root,fout);
    fprintf(fout,"\n\n");
    while(1)
    {
        printf("\n1.insert\n2.delete\n3.search\n4.inorder\n5.exit\n");
        printf("enter your choice:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("enter element to insert:");
                scanf("%d",&x);
                root=avlinsert(x,root);
                break;
            case 2:
                printf("enter element to delete:");
                scanf("%d",&x);
                root=avldelete(x,root);
                printf("inorder after deletion:\n");
                inorderprint(root);
                break;
            case 3:
                printf("enter element to search:");
                scanf("%d",&x);
                if(search(x,root)!=NULL)
                    printf("element found\n");
                else
                    printf("element not found\n");
                break;
            case 4:
                fout=fopen("output.txt","w");
                if(fout==NULL)
                {
                    printf("cannot open file");
                    break;
                }
                inorder(root,fout);
                fclose(fout);
                printf("inorder traversal written to output.txt\n");
                break;
            case 5:
                printf("exiting...\n");
                return 0;
            default:
                printf("invalid choice\n");
        }
    }
}