#ifndef SORT_H
#define SORT_H

/* 정렬 과정에서 측정할 통계 */
typedef struct {
    long long comparisons;
    long long moves;
} SortStats;

/* 삽입 정렬 */
SortStats insertionSort(int a[], int n);

/* 병합 정렬 */
SortStats mergeSort(int a[], int n);

/* 힙 정렬 */
SortStats heapSort(int a[], int n);

#endif /* SORT_H */
