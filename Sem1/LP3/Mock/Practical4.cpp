#include <bits/stdc++.h>

using namespace std;
int n;
class Solution
{
public:
    bool isSafe1(int row, int col, vector<string> board, int n)
    {
        int duprow = row;
        int dupcol = col;

        while (row >= 0 && col >= 0)
        {
            if (board[row][col] == 'Q')
                return false;
            row--;
            col--;
        }

        col = dupcol;
        row = duprow;
        while (col >= 0)
        {
            if (board[row][col] == 'Q')
                return false;

            col--;
        }
        

        row = duprow;
        col = dupcol;
        while (row < n && col >= 0)
        {
            if (board[row][col] == 'Q')
                return false;

            row++;
            col--;
        }
        return true;
    }

public:
    void solve(int col, vector<string> &board, vector<vector<string>> &ans, int n)
    {
        if (col == n)
        {
            ans.push_back(board);
            return;
        }
        for (int row = 0; row < n; row++)
        {
            if (isSafe1(row, col, board, n))
            {
                board[row][col] = 'Q';
                solve(col + 1, board, ans, n);
                board[row][col] = '.';
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> ans;
        vector<string> board(n);
        string s(n, '.');
        for (int i = 0; i < n; i++)
        {
            board[i] = s;
        }
        solve(0, board, ans, n);
        return ans;
    }
};
int main()
{
    Solution obj;

    cout << "Enter size of grid : ";
    cin >> n;
    cout << endl;
    if (n >= 12)
    {
        cout << "Grid size too large!" << endl
             << endl;
        return 0;
    }

    vector<vector<string>> ans = obj.solveNQueens(n);
    if (ans.size() == 0)
        cout << "No Arrangements possible!" << endl;
    else
    {
        for (int i = 0; i < ans.size(); i++)
        {
            cout << "Arrangement " << i + 1 << "\n";
            for (int j = 0; j < ans[0].size(); j++)
            {
                cout << ans[i][j];
                cout << endl;
            }
            cout << endl;
            cout << endl;
        }
    }

    return 0;
}