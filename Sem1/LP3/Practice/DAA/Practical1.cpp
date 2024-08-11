#include <bits/stdc++.h>
using namespace std;
int cnt = 0;
int recursive(int n)
{
    cnt++;
    if (n <= 1)
        return n;

    return recursive(n - 1) + recursive(n - 2);
}

int iterative(int n)
{
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

int main()
{
    cout << "============ MENU =============\n";
    cout << "1.Recursive\n2.Iterative\nChoose:- ";
    int ch;
    cin >> ch;

    switch (ch)
    {
    case 1:
        cout << "\nEnter n :- ";
        int n;
        cin >> n;
        cout << recursive(n) << "\n";
        cout << cnt << "\n";
        break;
    case 2:
        cout << "\nEnter n :- ";
        cin >> n;
        cout << iterative(n) << "\n";
        break;
    }
}