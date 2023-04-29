#include <iostream>
#include <chrono>
#include <random>
#include<bits/stdc++.h>
using namespace std;
using namespace std::chrono;
void insertionSort(int arr[], int n) {
for (int i = 1; i < n; i++) {
int key = arr[i];
int j = i - 1;
while (j >= 0 && arr[j] > key) {
arr[j + 1] = arr[j];
j--;
}
arr[j + 1] = key;
}
}
int main() {
// Generate random input arrays of
different sizes
const int numSizes = 10;
int sizes[numSizes] = {1000,2000,
5000,7500,10000,20000,30000, 50000,75000,
100000};
int* arr[numSizes];
for (int i = 0; i < numSizes; i++) {
arr[i] = new int[sizes[i]];
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1,
sizes[i]);
for (int j = 0; j < sizes[i]; j++) {
arr[i][j] = dis(gen);
}
sort(arr[i],arr[i]
+sizes[i],greater<int>());
}
// Measure execution time for each input
size
const int numRuns = 10;
long long times[numSizes][numRuns];
for (int i = 0; i < numSizes; i++) {
for (int j = 0; j < numRuns; j++) {
auto start =
high_resolution_clock::now();
insertionSort(arr[i], sizes[i]);
auto stop =
high_resolution_clock::now();
auto duration =
duration_cast<microseconds>(stop - start);
times[i][j] = duration.count();
}
}
// Print results
cout << "Size\t\tAverage Time (μs)" <<
endl;
for (int i = 0; i < numSizes; i++) {
long long sum = 0;
for (int j = 0; j < numRuns; j++) {
sum += times[i][j];
}
double average =
static_cast<double>(sum) / numRuns;
cout << sizes[i] << "\t\t" << average
<< endl;
delete[] arr[i];
}
return 0;
}
