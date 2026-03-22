#include<stdio.h>
#define N 4
int board[N][N]= {0};

int isSafe(int row,int col)
{
    int i,j;
    for(i=0;i<row;i++)
    {
        if(board[i][col]==1)
            return 0;
    }
    for(i=row,j=col;i>=0 && j>=0;i--,j--)
    {
        if(board[i][j]==1)
            return 0;
    }
    for(i=row,j=col;i>=0 && j<N;i--,j++)
    {
        if(board[i][j]==1)
            return 0;
    }
    return 1;
}

int solve(int row)
{
    if(row==N)
        return 1;
    for(int col=0;col<N;col++)
    {
        if(isSafe(row,col))
        {
            board[row][col]=1;
            if(solve(row+1))
                return 1;
            board[row][col]=0;
        }
    }
    return 0;
}

void printboard()
{
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            if(board[i][j]==1)
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
}

int main()
{
    if(solve(0))
        printboard();
    else
        printf("No solution exists\n");
    return 0;
}