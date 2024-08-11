#include <bits/stdc++.h>
using namespace std;

int knapsack(vector<int> &weight, vector<int> &profit, int W, int ind, vector<vector<int>> &dp)
{
    if (ind == 0)
    {
        if (weight[ind] <= W)
            return profit[ind];

        return 0;
    }

    if (dp[ind][W] != -1) //memoization 
        return dp[ind][W];

    int take = 0, notTake;
    notTake = knapsack(weight, profit, W, ind - 1, dp);

    if (weight[ind] <= W)
        take = profit[ind] + knapsack(weight, profit, W - weight[ind], ind - 1, dp);

    return dp[ind][W] = max(take, notTake);
}

int main()
{
    cout << "\n Enter no of items :- ";
    int n;
    cin >> n;

    vector<int> weight(n), profit(n);

    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter weight and profit of item " << i + 1 << ":- ";
        cin >> weight[i] >> profit[i];
    }

    cout << "\nEnter capacity of Knapsack :- ";
    int W;
    cin >> W;

    vector<vector<int>> dp(n, vector<int>(W + 1, -1));

    cout << "Maximum profit can be " << knapsack(weight, profit, W, n - 1, dp);
}