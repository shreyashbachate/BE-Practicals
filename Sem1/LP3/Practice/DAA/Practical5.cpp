#include <bits/stdc++.h>
#include <chrono>
using namespace std;
using namespace chrono;

int partition(vector<int> &arr, int low, int high)
{
    int pivot = arr[low];
    int i = low + 1;
    int j = high;

    while (1)
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

int randomPartition(vector<int> &arr, int low, int high)
{
    srand(time(0));

    int random = low + rand() % (high - low) + 1;
    swap(arr[low], arr[random]);

    return partition(arr, low, high);
}

void randomizedQuickSort(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pivot = randomPartition(arr, low, high);
        cout << pivot << " ";
        randomizedQuickSort(arr, low, pivot - 1);
        randomizedQuickSort(arr, pivot + 1, high);
    }
}

int main()
{
    cout << "\n Enter size of array :- ";
    int n;
    cin >> n;

    vector<int> arr(n), arrCopy(n);

    for (int i = 0; i < n; i++)
    {
        cout << "\n Enter element " << i + 1 << ":- ";
        cin >> arr[i];
        arrCopy[i] = arr[i];
    }

    high_resolution_clock::time_point start_time;
    high_resolution_clock::time_point end_time;
    duration<double> time_span;

    start_time = high_resolution_clock::now();
    deterministicQuickSort(arr, 0, n - 1);
    end_time = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(end_time - start_time);
    cout << "Deterministic Quick Sort took " << time_span.count() << " seconds\n";

    start_time = high_resolution_clock::now();
    randomizedQuickSort(arrCopy, 0, n - 1);
    end_time = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(end_time - start_time);
    cout << "Randomized Quick Sort took " << time_span.count() << " seconds\n";
}