#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

int min(vector<int>& arr, int n)
{
    int minVal = 1e6;

    #pragma omp parallel for reduction(min:minVal)
    for (int i = 0; i < n;i++)
    {
        cout << "\nThread " << omp_get_thread_num() << " and value is " << arr[i];
        if(minVal>arr[i])
            minVal = arr[i];
    }

    return minVal;
}

int max(vector<int>& arr, int n)
{
    int maxVal = 0;

    #pragma omp parallel for reduction(max:maxVal)
    for (int i = 0; i < n;i++)
    {
        cout << "\nThread " << omp_get_thread_num() << " and value is " << arr[i];
        if(maxVal<arr[i])
            maxVal = arr[i];
    }

    return maxVal;
}

int sum(vector<int>& arr, int n)
{
    int sumVal = 0;

    #pragma omp parallel for reduction(+:sumVal)
    for (int i = 0; i < n;i++)
    {
        cout << "\nThread " << omp_get_thread_num() << " and value is " << arr[i];
        sumVal += arr[i];
    }

    return sumVal;
}

double avg(vector<int>& arr, int n)
{
    return (double)sum(arr, n) / n;
}

int main()
{
    omp_set_num_threads(3);
    int n;
    cout << "\nEnter no of elements:- ";
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n;i++)
    {
        cout << "\nEnter element no " << i + 1 << ":- ";
        cin >> arr[i];
    }

    int ch;
    while(1)
    {
        cout << "\n\n=========== MENU =============\n\n";
        cout << "\n1.Min Value";
        cout << "\n2.Max Value";
        cout << "\n3.Sum Value";
        cout << "\n4.Avg Value";
        cout << "\n0.Exit";
        cout<<"\nEnter your choice:- ";
        cin >> ch;

        switch(ch)
        {
            case 1:
                cout <<"\n"<< min(arr, n);
                break;
            
            case 2:
                cout <<"\n"<< max(arr, n);
                break;
            
            case 3:
                cout <<"\n"<< sum(arr, n);
                break;
            
            case 4:
                cout <<"\n"<< avg(arr, n);
                break;
            
            case 0:
                exit(0);
                break;
            
            default:
                cout <<"\nEnter correct choice";
                break;
        }
    }
}
