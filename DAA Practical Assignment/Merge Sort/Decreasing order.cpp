#include <iostream>
#include <chrono>
#include <random>
#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
void merge(int array[], int const left, int const mid,
int const right)
{
auto const subArrayOne = mid - left + 1;
auto const subArrayTwo = right - mid;
// Create temp arrays
auto *left array = new int[subArrayOne],
*rightArray = new int[subArrayTwo];
// Copy data to temp arrays leftArray[] and rightArray[]
for (auto i = 0; i < subArrayOne; i++)
leftArray[i] = array[left + i];
for (auto j = 0; j < subArrayTwo; j++)
rightArray[j] = array[mid + 1 + j];
auto indexOfSubArrayOne
= 0, // Initial index of first sub-array
indexOfSubArrayTwo
= 0; // Initial index of second sub-array
int indexOfMergedArray
= left; // Initial index of the merged array
// Merge the temp arrays back into array[left..right]
while (indexOfSubArrayOne < subArrayOne
&& indexOfSubArrayTwo < subArrayTwo) {
if (leftArray[indexOfSubArrayOne]
<= rightArray[indexOfSubArrayTwo]) {
array[indexOfMergedArray]
= leftArray[indexOfSubArrayOne];
indexOfSubArrayOne++;
}
else {
array[indexOfMergedArray]
= rightArray[indexOfSubArrayTwo];
indexOfSubArrayTwo++;
}
indexOfMergedArray++;
}
// Copy the remaining elements of
// left[], if there are any
while (indexOfSubArrayOne < subArrayOne) {
array[indexOfMergedArray]
= leftArray[indexOfSubArrayOne];
indexOfSubArrayOne++;
indexOfMergedArray++;
}
// Copy the remaining elements of
// right[], if there are any
while (indexOfSubArrayTwo < subArrayTwo) {
array[indexOfMergedArray]
= rightArray[indexOfSubArrayTwo];
indexOfSubArrayTwo++;
indexOfMergedArray++;
}
delete[] leftArray;
delete[] rightArray;
}
void mergeSort(int array[], int const begin, int const end)
{
if (begin >= end)
return; // Returns recursively
auto mid = begin + (end - begin) / 2;
mergeSort(array, begin, mid);
mergeSort(array, mid + 1, end);
merge(array, begin, mid, end);
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
sort(arr[i],arr[i]+sizes[i],greater<int>());
}
// Measure execution time for each input size
const int numRuns = 10;
long long times[numSizes][numRuns];
for (int i = 0; i < numSizes; i++) {
for (int j = 0; j < numRuns; j++) {
auto start = high_resolution_clock::now();
mergeSort(arr[i],0,sizes[i] - 1);
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
