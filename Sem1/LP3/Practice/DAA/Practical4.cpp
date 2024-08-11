#include <bits/stdc++.h>
using namespace std;
int n;

class Solution
{
public:
    bool isSafe(vector<string> &board, int row, int col, int n)
    {
        int dupRow = row;
        int dupCol = col;

        while (row >= 0 && col >= 0)
        {
            if (board[row][col] == 'Q')
                return false;

            row--;
            col--;
        }

        row = dupRow;
        col = dupCol;

        while (col >= 0)
        {
            if (board[row][col] == 'Q')
                return false;

            col--;
        }

        row = dupRow;
        col = dupCol;

        while (row < n && col >= 0)
        {
            if (board[row][col] == 'Q')
                return false;

            row++;
            col--;
        }

        return true;
    }
    void solve(vector<vector<string>> &ans, vector<string> &board, int col, int n)
    {
        if (col >= n)
        {
            ans.push_back(board);
            return;
        }

        for (int row = 0; row < n; row++)
        {
            if (isSafe(board, row, col, n))
            {
                board[row][col] = 'Q';
                solve(ans, board, col + 1, n);
                board[row][col] = '.';
            }
        }
    }
    vector<vector<string>> solveNQueens(int n)
    {
        vector<vector<string>> ans;
        vector<string> board(n);
        string s(n, '.');
        for (int i = 0; i < n; i++)
        {
            board[i] = s;
        }

        solve(ans, board, 0, n);
        return ans;
    }

    bool isSafe2(int row, int col, vector<bool> &rows, vector<bool> &left, vector<bool> &right)
    {
        if (rows[row] == 1 || left[col + row] == 1 || right[col - row + n - 1] == 1)
            return false;

        return true;
    }

    bool solveBranch(vector<vector<int>> &board, vector<bool> &rows, vector<bool> &left, vector<bool> &right, int col)
    {
        if (col >= n)
            return true;

        for (int row = 0; row < n; row++)
        {
            if (isSafe2(row, col, rows, left, right) == 1)
            {
                rows[row] = 1;
                left[col + row] = 1;
                right[col - row + n - 1] = 1;
                board[row][col] = 1;

                if (solveBranch(board, rows, left, right, col + 1) == 1)
                    return true;

                rows[row] = 0;
                left[col + row] = 0;
                right[col - row + n - 1] = 0;
                board[row][col] = 0;
            }
        }
        return false;
    }
};

int main()
{
    cout << "\nEnter size of grid :- ";
    cin >> n;

    if (n >= 12)
    {
        cout << "\nGrid size too large to compute\n";
        return 0;
    }

    cout << "choose: - ";
    int ch;
    cin >> ch;
    Solution obj;
    if (ch == 1)
    {

        vector<vector<string>> ans = obj.solveNQueens(n);

        if (ans.size() == 0)
        {
            cout << "\n Arrangement not found\n";
        }
        else
        {
            for (int i = 0; i < ans.size(); i++)
            {
                cout << "Arrangement " << i + 1 << ":-\n";
                for (int j = 0; j < ans[0].size(); j++)
                {
                    cout << ans[i][j] << "\n";
                }
                cout << "\n\n";
            }
        }
    }
    else
    {
        vector<vector<int>> board(n, vector<int>(n, 0));
        vector<bool> rows(n), left_diagonal(2 * n - 1), right_diagonal(2 * n - 1);

        bool ans = obj.solveBranch(board, rows, left_diagonal, right_diagonal, 0);

        if (ans)
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < n; j++)
                {
                    if (board[i][j])
                        cout << "Q";
                    else
                        cout << ".";
                }
                cout << "\n";
            }
        }
        else
        {
            cout << " Arrangement not found";
        }
    }
}