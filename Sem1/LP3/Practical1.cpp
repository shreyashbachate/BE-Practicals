#include <bits/stdc++.h>
using namespace std;
int fibo(int n)
{

    if (n == 0)
    {
        return 0;
    }
    if (n == 1)
    {
        return 1;
    }
    return fibo(n - 1) + fibo(n - 2);
}
void itrFibo(int n)
{
    int fib0 = 0;
    int fib1 = 1;
    cout << fib0 << " " << fib1 << " ";
    for (int i = 2; i <= n; i++)
    {
        int newFib = fib0 + fib1;
        cout << newFib << " ";
        fib0 = fib1;
        fib1 = newFib;
    }
}
int main()
{

    while (1)
    {
        cout << "Enter n :- ";
        int n;
        cin >> n;
        cout << "============ MENU ================\n";
        cout << "1.Recursive\n";
        cout << "2.Iterative\n";
        cout << "3.Exit\n";
        int ch;
        cin >> ch;
        switch (ch)
        {
        case 1:
        {
            int i = 0;
            while (i <= n)
            {
                cout << fibo(i) << " ";
                i++;
            }
            cout << "\n";
            break;
        }
        case 2:
            itrFibo(n);
            cout << "\n";
            break;
        case 0:
            exit(0);
        default:
            cout << "Please enter correct choice\n";
        }
    }
    return 0;
}
