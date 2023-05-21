#include <stdio.h>
#include <stdlib.h>
#include <cstring>  // Add the header for memcpy
#include <omp.h>

// Sequential Bubble Sort
void bubbleSort(int arr[], int n) {
    // Implementation
}

// Parallel Bubble Sort
void parallelBubbleSort(int arr[], int n) {
    // Implementation
}

// Sequential Merge Sort
void merge(int arr[], int l, int m, int r) {
    // Implementation
}

void sequentialMergeSort(int arr[], int l, int r) {
    // Implementation
}

// Parallel Merge Sort
void parallelMergeSort(int arr[], int l, int r) {
    // Implementation
}

int main() {
    int n = 10000; // Size of the array
    int arr[n], arr_copy[n];

    // Initialize the array with random values
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 1000;
    }

    // Make a copy of the array for comparison
    memcpy(arr_copy, arr, n * sizeof(int));

    // Sequential Bubble Sort
    double start_time = omp_get_wtime();
    bubbleSort(arr, n);
    double end_time = omp_get_wtime();
    double sequential_bubble_sort_time = end_time - start_time;

    // Parallel Bubble Sort
    memcpy(arr, arr_copy, n * sizeof(int));
    start_time = omp_get_wtime();
    parallelBubbleSort(arr, n);
    end_time = omp_get_wtime();
    double parallel_bubble_sort_time = end_time - start_time;

    // Sequential Merge Sort
    memcpy(arr, arr_copy, n * sizeof(int));
    start_time = omp_get_wtime();
    sequentialMergeSort(arr, 0, n-1);
    end_time = omp_get_wtime();
    double sequential_merge_sort_time = end_time - start_time;

    // Parallel Merge Sort
    memcpy(arr, arr_copy, n * sizeof(int));
    start_time = omp_get_wtime();
    parallelMergeSort(arr, 0, n-1);
    end_time = omp_get_wtime();
    double parallel_merge_sort_time = end_time - start_time;

    // Display the execution times
    printf("Sequential Bubble Sort Time: %f seconds\n", sequential_bubble_sort_time);
    printf("Parallel Bubble Sort Time: %f seconds\n", parallel_bubble_sort_time);
    printf("Sequential Merge Sort Time: %f seconds\n", sequential_merge_sort_time);
    printf("Parallel Merge Sort Time: %f seconds\n", parallel_merge_sort_time);

    return 0;
}