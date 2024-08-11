#include <bits/stdc++.h>
#include <ctime>
#include <chrono>
using namespace std;
using namespace chrono;

int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[low];
    int i = low + 1, j = high;

    while (true)
    {
        while (i <= j && arr[i] <= pivot)
            i++;

        while (i <= j && arr[j] > pivot)
            j--;

        if (i <= j)
            swap(arr[i], arr[j]);

        else
            break;
    }
    swap(arr[low], arr[j]);
    return j;
}

void deterministicQuickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pivot = partition(arr, low, high);
        cout << pivot << " ";

        deterministicQuickSort(arr, low, pivot - 1);
        deterministicQuickSort(arr, pivot + 1, high);
    }
}

int randomizedPartition(vector<int> &arrCopy, int low, int high)
{
    srand(time(0));
    int random = low + rand() % ((high - low) + 1);
    swap(arrCopy[random], arrCopy[low]);
    return partition(arrCopy, low, high);
}

void randomizedQuickSort(vector<int> &arrCopy, int low, int high)
{
    if (low < high)
    {
        int pivot = randomizedPartition(arrCopy, low, high);
        cout << pivot << " ";
        randomizedQuickSort(arrCopy, low, pivot - 1);
        randomizedQuickSort(arrCopy, pivot + 1, high);
    }
}

int main()
{
    cout << "\nEnter no of elements:- ";
    int size;
    cin >> size;

    vector<int> arr(size), arrCopy(size);

    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
        arrCopy[i] = arr[i];
    }

    high_resolution_clock::time_point start_time;
    high_resolution_clock::time_point end_time;

    duration<double> time_span;

    start_time = high_resolution_clock::now();
    deterministicQuickSort(arr, 0, size - 1);
    end_time = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(end_time - start_time);
    cout << "Deterministic quick sort took " << time_span.count() << " seconds\n";

    start_time = high_resolution_clock::now();
    randomizedQuickSort(arrCopy, 0, size - 1);
    end_time = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(end_time - start_time);
    cout << "Randomized quick sort took " << time_span.count() << " seconds\n";

    cout << "Sorted array is :- \n";

    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";
}