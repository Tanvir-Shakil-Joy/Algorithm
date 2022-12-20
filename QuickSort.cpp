#include<bits/stdc++.h>

using namespace std;

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low-1);
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void QuickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

int main() {
    int n, arr[100];
    ifstream in("quicksort.txt");
    if (in.is_open()) {
        in >> n;
        for (int i=0; i < n; i++) {
            in >> arr[i];
        }
    }
    cout << n << endl;
    for (int i=0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    QuickSort(arr, 0, n-1);
    for (int i=0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    return 0;
}