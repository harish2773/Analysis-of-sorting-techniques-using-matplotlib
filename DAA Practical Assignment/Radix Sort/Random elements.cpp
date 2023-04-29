#include <iostream>
#include <chrono>
#include <random>
#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
int getMax(int arr[], int n)
{
int mx = arr[0];
for (int i = 1; i < n; i++)
if (arr[i] > mx)
mx = arr[i];
return mx;
}
// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(int arr[], int n, int expo)
{
int output[n]; // output array
int i, count[10] = { 0 };
// Store count of occurrences in count[]
for (i = 0; i < n; i++)
count[(arr[i] / expo) % 10]++;
// Change count[i] so that count[i] now contains actual
// position of this digit in output[]
for (i = 1; i < 10; i++)
count[i] += count[i - 1];
// Build the output array
for (i = n - 1; i >= 0; i--) {
output[count[(arr[i] / expo) % 10] - 1] = arr[i];
count[(arr[i] / expo) % 10]--;
}
// Copy the output array to arr[], so that arr[] now
// contains sorted numbers according to current digit
for (i = 0; i < n; i++)
arr[i] = output[i];
}
// The main function to that sorts arr[] of size n using
// Radix Sort
void radixsort(int arr[], int n)
{
// Find the maximum number to know number of digits
int m = getMax(arr, n);
// Do counting sort for every digit. Note that instead
// of passing digit number, exp is passed. exp is 10^i
// where i is current digit number
for (int expo = 1; m / expo > 0; expo *= 10)
countSort(arr, n, expo);
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
//sort(arr[i],arr[i]+sizes[i],greater<int>());
}
// Measure execution time for each input size
const int numRuns = 10;
long long times[numSizes][numRuns];
for (int i = 0; i < numSizes; i++) {
for (int j = 0; j < numRuns; j++) {
auto start = high_resolution_clock::now();
radixsort(arr[i], sizes[i]);
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
