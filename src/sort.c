#include "sort.h"

/* =========================
   Insertion Sort
   ========================= */

SortStats insertionSort(int a[], int n) {
    SortStats stats = {0, 0};

    for (int i = 1; i < n; i++) {
        int key = a[i];
        stats.moves++;

        int j = i - 1;

        while (j >= 0) {
            stats.comparisons++;

            if (a[j] > key) {
                a[j + 1] = a[j];
                stats.moves++;
                j--;
            } else {
                break;
            }
        }

        a[j + 1] = key;
        stats.moves++;
    }

    return stats;
}


/* =========================
   Merge Sort
   ========================= */

static void merge(
    int a[],
    int left,
    int mid,
    int right,
    SortStats *stats
) {
    int temp[right - left + 1];

    int i = left;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= right) {
        stats->comparisons++;

        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }

        stats->moves++;
    }

    while (i <= mid) {
        temp[k++] = a[i++];
        stats->moves++;
    }

    while (j <= right) {
        temp[k++] = a[j++];
        stats->moves++;
    }

    for (int t = 0; t < k; t++) {
        a[left + t] = temp[t];
        stats->moves++;
    }
}


static void mergeSortRecursive(
    int a[],
    int left,
    int right,
    SortStats *stats
) {
    if (left >= right) {
        return;
    }

    int mid = left + (right - left) / 2;

    mergeSortRecursive(a, left, mid, stats);
    mergeSortRecursive(a, mid + 1, right, stats);

    merge(a, left, mid, right, stats);
}


SortStats mergeSort(int a[], int n) {
    SortStats stats = {0, 0};

    if (n > 1) {
        mergeSortRecursive(a, 0, n - 1, &stats);
    }

    return stats;
}


/* =========================
   Heap Sort
   ========================= */

static void heapify(
    int a[],
    int n,
    int i,
    SortStats *stats
) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n) {
        stats->comparisons++;

        if (a[left] > a[largest]) {
            largest = left;
        }
    }

    if (right < n) {
        stats->comparisons++;

        if (a[right] > a[largest]) {
            largest = right;
        }
    }

    if (largest != i) {
        int temp = a[i];
        a[i] = a[largest];
        a[largest] = temp;

        /* swap 1회 = move 3회 */
        stats->moves += 3;

        heapify(a, n, largest, stats);
    }
}


SortStats heapSort(int a[], int n) {
    SortStats stats = {0, 0};

    /* Max Heap 생성 */
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(a, n, i, &stats);
    }

    /* 최댓값을 하나씩 뒤로 이동 */
    for (int i = n - 1; i > 0; i--) {
        int temp = a[0];
        a[0] = a[i];
        a[i] = temp;

        /* swap 1회 = move 3회 */
        stats.moves += 3;

        heapify(a, i, 0, &stats);
    }

    return stats;
}
