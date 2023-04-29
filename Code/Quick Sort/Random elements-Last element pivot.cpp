#include <iostream>
using namespace std;
void generateRandomArray(int arr[], int size) {
for(int i = 0; i < size; i++) {
arr[i] = rand() % size;
}
}
int partition(int arr[], int low, int high) {
int pivot = arr[high];
int i = low - 1;
for(int j = low; j <= high - 1; j++) {
if(arr[j] <= pivot) {
i++;
swap(arr[i], arr[j]);
}
}
swap(arr[i + 1], arr[high]);
return i + 1;
}
void quicksort(int arr[], int low, int high) {
if(low < high) {
int pivot = partition(arr, low, high);
quicksort(arr, low, pivot - 1);
quicksort(arr, pivot + 1, high);
}
}
double measureTime(int size) {
int arr[size];
generateRandomArray(arr, size);
clock_t start = clock();
quicksort(arr, 0, size - 1);
clock_t end = clock();
return (double) (end - start) / CLOCKS_PER_SEC;
}
int main() {
int sizes[] = {1000,2000, 5000,7500, 10000,20000,30000, 50000,75000,
100000};
int numSizes = 10;
for(int i = 0; i < numSizes; i++) {
int size = sizes[i];
double timeTaken = measureTime(size);
cout << "Time taken for size " << size << " is " << timeTaken << "seconds" << endl;
}
return 0;
}