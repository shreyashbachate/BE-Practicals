#include <iostream>
#include <vector>
#include <thread>

using namespace std;
void merge(std::vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> left_arr(n1);
    std::vector<int> right_arr(n2);
    for (int i = 0; i < n1; i++)
    {
        left_arr[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++)
    {
        right_arr[i] = arr[mid + 1 + i];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
    {
        if (left_arr[i] <= right_arr[j])
        {
            arr[k] = left_arr[i];
            i++;
        }
        else
        {
            arr[k] = right_arr[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        arr[k] = left_arr[i];
        i++;
        k++;
    }
    while (j < n2)
    {
        arr[k] = right_arr[j];
        j++;
        k++;
    }
}
void merge_sort(std::vector<int> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
void multithreaded_merge_sort(std::vector<int> &arr, int left, int right, int depth)
{
    if (left < right)
    {
        if (depth == 0)
        {
            merge_sort(arr, left, right);
        }
        else
        {
            int mid = left + (right - left) / 2;
            thread left_thread(multithreaded_merge_sort, std::ref(arr), left, mid, depth - 1);
            thread right_thread(multithreaded_merge_sort, std::ref(arr), mid + 1, right, depth - 1);
            left_thread.join();
            right_thread.join();
            merge(arr, left, mid, right);
        }
    }
}
int main()
{
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    // Merge Sort
    merge_sort(arr, 0, arr.size() - 1);
    std::cout << "Sorted array using Merge Sort: ";
    for (int num : arr)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Multithreaded Merge Sort
    std::vector<int> arr2 = {12, 11, 13, 5, 6, 7};
    int num_threads = 2; // Adjust the number of threads as needed
    multithreaded_merge_sort(arr2, 0, arr2.size() - 1, num_threads);
    std::cout << "Sorted array using Multithreaded Merge Sort: ";
    for (int num : arr2)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    return 0;
}