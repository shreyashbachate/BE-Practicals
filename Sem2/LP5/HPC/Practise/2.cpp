#include <bits/stdc++.h>
#include <omp.h>

using namespace std;

void bubbleSort(vector<int> &arr, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
        }
    }
}

void parallelBubbleSort(vector<int> &arr, int n)
{
    for (int i = 0; i < n; i++)
    {
#pragma omp for
        for (int j = 1; j < n; j += 2)
        {
            if (arr[j - 1] > arr[j])
                swap(arr[j - 1], arr[j]);
        }

#pragma omp barrier

#pragma omp for
        for (int j = 2; j < n; j += 2)
        {
            if (arr[j - 1] > arr[j])
                swap(arr[j - 1], arr[j]);
        }
    }
}

void merge(vector<int>& arr, int low,int mid,int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int left[n1];
    int right[n2];

    for (int i = 0; i < n1;i++)
        left[i] = arr[low + i];

    for (int j = 0; j < n2;j++)
        right[j] = arr[mid + j + 1];

    int i = 0, j = 0, k = low;
    while(i<n1 && j<n2)
    {
        if(left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while(i<n1)
    {
        arr[k++] = left[i++];
    }

    while(j<n2)
    {
        arr[k++] = right[j++];
    }
}

void mergeSort(vector<int>&arr, int low,int high)
{
    if(low<high)
    {
        int mid = (low + high) / 2;

        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        merge(arr, low, mid, high);
    }
}

void parallelMergeSort(vector<int>& arr, int low,int high)
{
    if(low<high)
    {
        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, low, mid);
            }
            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, high);
            }
        }
        merge(arr, low, mid, high);
    }
}

int main()
{
    int n;
    double start_time, end_time;
    cout << "\n Enter no of elements :- ";
    cin >> n;

    vector<int> arr(n), arrCopy(n);
    for (int i = 0; i < n; i++)
    {
        cout << "\nEnter element no " << i + 1 << ":- ";
        cin >> arr[i];
        arrCopy[i] = arr[i];
    }
    int ch;
    while (1)
    {
        cout << "\n\n========= MENU ========\n\n";
        cout << "1.Bubble Sort\n";
        cout << "2.Merge Sort\n";
        cout << "0. Exit \n";
        cout << "Enter your choice :- ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            start_time = omp_get_wtime();
            bubbleSort(arr, n);
            end_time = omp_get_wtime();
            cout << "Sequential bubble sort took " << end_time - start_time << " seconds\n";

            for (int i = 0; i < n; i++)
                cout << arr[i] << " ";
            cout << "\n";
            start_time = omp_get_wtime();
            parallelBubbleSort(arrCopy, n);
            end_time = omp_get_wtime();
            cout << "Parallel bubble sort took " << end_time - start_time << " seconds\n";

            for (int i = 0; i < n; i++)
                cout << arrCopy[i] << " ";
            
            break;
        case 2:
            start_time = omp_get_wtime();
            mergeSort(arr, 0,n-1);
            end_time = omp_get_wtime();
            cout << "Merge sort took " << end_time - start_time << " seconds\n";
            for (int i = 0; i < n;i++)
                cout << arr[i] << " \n"[i == n];

            start_time = omp_get_wtime();
            parallelMergeSort(arrCopy, 0,n-1);
            end_time = omp_get_wtime();
            cout << "\nParallel merge sort took " << end_time - start_time << " seconds\n";
            for (int i = 0; i < n;i++)
                cout << arrCopy[i] << " \n"[i == n];
                break;
            case 0:
                exit(0);
            break;

        default:
            cout << "Enter correct choice\n";
            break;
        }
    }
}