/*
 * Problem Statement :- Write a program to solve a 0-1 Knapsack problem using dynamic
 * 						programming or branch and bound strategy.
 *
 * Time complexity  : O(n*c)      (n=>number of elements  c=>capacity of knapsack)
 * Space Complexity : O(n*c)
 */

#include <bits/stdc++.h>
using namespace std;

int knapsackUtil(vector<int> &wt, vector<int> &val, int ind, int W, vector<vector<int>> &dp)
{

    if (ind == 0)
    {
        if (wt[ind] <= W)
        {
            return val[ind];
        }
        else
        {
            return 0;
        }
    }

    if (dp[ind][W] != -1)
    {
        return dp[ind][W];
    }

    int nottake = 0 + knapsackUtil(wt, val, ind - 1, W, dp);

    int take = INT_MIN;
    if (wt[ind] <= W)
    {
        take = val[ind] + knapsackUtil(wt, val, ind - 1, W - wt[ind], dp);
    }

    return dp[ind][W] = max(take, nottake);
}

int knapsack(vector<int> &wt, vector<int> &val, int n, int W)
{

    vector<vector<int>> dp(n, vector<int>(W + 1, -1));
    return knapsackUtil(wt, val, n - 1, W, dp);
}

int knapsack(vector<int> val, vector<int> wt, int W)
{
    int n = wt.size();

    vector<vector<int>> dp(n, vector<int>(W + 1, 0));

    // Base Condition

    // for weights less than or equal to W assign their values
    for (int i = wt[0]; i <= W; i++)
    {
        dp[0][i] = val[0];
    }

    // index 1 to n-1
    for (int ind = 1; ind < n; ind++)
    {
        for (int cap = 0; cap <= W; cap++)
        {

            int notTaken = 0 + dp[ind - 1][cap];

            int taken = INT_MIN;
            if (wt[ind] <= cap)
                taken = val[ind] + dp[ind - 1][cap - wt[ind]];

            dp[ind][cap] = max(notTaken, taken);
        }
    }

    return dp[n - 1][W];
}

int main()
{
    int n, c;

    cout << "\n\t Enter number of elements : ";
    cin >> n;
    cout << "\n\t Enter the capacity of knapsack : ";
    cin >> c;

    vector<int> wt(n, 0), val(n, 0);

    cout << "\n\t Enter the value/cost of all elements : ";
    for (int i = 0; i < n; i++)
        cin >> val[i];

    cout << "\n\t Enter the weight of all elements : ";
    for (int i = 0; i < n; i++)
        cin >> wt[i];

    int max_val = knapsack(val, wt, c);
    cout << "\n\t Maximum total value in the knapsack : " << max_val << endl;
}
