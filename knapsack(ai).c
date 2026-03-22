#include<stdio.h>

int maxprofit = 0;

void knapsack(int i, int weight, int profit, int n, int w, int val[], int wt[])
{
    // Base case: reached end of items or weight exceeds capacity
    if(i >= n || weight > w)
    {
        // Update maxprofit if current profit is better
        if(profit > maxprofit && weight <= w)
        {
            maxprofit = profit;
        }
        return;
    }
    
    // Option 1: Exclude current item
    knapsack(i + 1, weight, profit, n, w, val, wt);
    
    // Option 2: Include current item (if weight doesn't exceed capacity)
    if(weight + wt[i] <= w)
    {
        knapsack(i + 1, weight + wt[i], profit + val[i], n, w, val, wt);
    }
}

int main()
{
    int n = 4, w = 5;
    int wt[] = {2, 1, 3, 2};
    int val[] = {12, 10, 20, 15};
    
    knapsack(0, 0, 0, n, w, val, wt);
    printf("Maximum profit is %d\n", maxprofit);
    
    return 0;
}