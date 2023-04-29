#include <iostream>
#include <chrono>
#include <random>
#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
void heapify(int arr[], int N, int i)
{
// Initialize largest as root
int largest = i;
// left = 2*i + 1
int l = 2 * i + 1;
// right = 2*i + 2
int r = 2 * i + 2;
// If left child is larger than root
if (l < N && arr[l] > arr[largest])
largest = l;
// If right child is larger than largest
// so far
if (r < N && arr[r] > arr[largest])
largest = r;
// If largest is not root
if (largest != i) {
swap(arr[i], arr[largest]);
// Recursively heapify the affected
// sub-tree
heapify(arr, N, largest);
}
}
// Main function to do heap sort
void heapSort(int arr[], int N)
{
// Build heap (rearrange array)
for (int i = N / 2 - 1; i >= 0; i--)
heapify(arr, N, i);
// One by one extract an element
// from heap
for (int i = N - 1; i > 0; i--) {
// Move current root to end
swap(arr[0], arr[i]);
// call max heapify on the reduced heap
heapify(arr, i, 0);
}
}
int main() {
// Generate random input arrays of different sizes
const int numSizes = 10;
int sizes[numSizes] = {1000,2000, 5000,7500,10000,20000,30000,
50000,75000,
100000};
int* arr[numSizes];
for (int i = 0; i < numSizes; i++) {
arr[i] = new int[sizes[i]];
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1, sizes[i]);
for (int j = 0; j < sizes[i]; j++) {
arr[i][j] = dis(gen);
}
// sort(arr[i],arr[i]+sizes[i]);
sort(arr[i],arr[i]+sizes[i],greater<int>());
}
// Measure execution time for each input size
const int numRuns = 10;
long long times[numSizes][numRuns];
for (int i = 0; i < numSizes; i++) {
for (int j = 0; j < numRuns; j++) {
auto start = high_resolution_clock::now();
heapSort(arr[i], sizes[i]);
auto stop = high_resolution_clock::now();
auto duration = duration_cast<microseconds>(stop - start);
times[i][j] = duration.count();
}
}
// Print results
cout << "Size\t\tAverage Time (μs)" << endl;
for (int i = 0; i < numSizes; i++) {
long long sum = 0;
for (int j = 0; j < numRuns; j++) {
sum += times[i][j];
}
double average = static_cast<double>(sum) / numRuns;
cout << sizes[i] << "\t\t" << average << endl;
delete[] arr[i];
}
return 0;
}