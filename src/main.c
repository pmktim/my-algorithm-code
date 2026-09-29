/* 실행: make run-c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "sort.h"

#define REPEAT_COUNT 10

/* 배열 복사 */
static void copyArray(int destination[], const int source[], int n) {
    memcpy(destination, source, sizeof(int) * n);
}

/* Random 입력 */
static void makeRandomArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100000;
    }
}

/* Sorted 입력 */
static void makeSortedArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = i;
    }
}

/* Reverse 입력 */
static void makeReverseArray(int a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i] = n - i;
    }
}

/* 정렬 결과 검증 */
static int isSorted(const int a[], int n) {
    for (int i = 1; i < n; i++) {
        if (a[i - 1] > a[i]) {
            return 0;
        }
    }

    return 1;
}

/* 시간 측정 */
static double getTime(void) {
    return (double)clock() / CLOCKS_PER_SEC;
}

/* 정렬 알고리즘 선택 */
static SortStats runSort(
    const char *algorithm,
    int a[],
    int n
) {
    if (strcmp(algorithm, "Insertion") == 0) {
        return insertionSort(a, n);
    }

    if (strcmp(algorithm, "Merge") == 0) {
        return mergeSort(a, n);
    }

    return heapSort(a, n);
}

/* 하나의 실험 조건 실행 */
static void runExperiment(
    FILE *file,
    const char *algorithm,
    const char *inputType,
    int original[],
    int n
) {
    int *a = malloc(sizeof(int) * n);

    if (a == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    double totalTime = 0.0;
    SortStats stats = {0, 0};

    for (int repeat = 0; repeat < REPEAT_COUNT; repeat++) {

        /*
         * 매 반복마다 동일한 original을 다시 복사한다.
         * 따라서 정렬된 결과를 다음 반복에서 재사용하지 않는다.
         */
        copyArray(a, original, n);

        double start = getTime();

        SortStats currentStats =
            runSort(algorithm, a, n);

        double end = getTime();

        totalTime += end - start;

        /*
         * 동일한 입력에서는 comparisons와 moves가 같으므로
         * 첫 번째 실행의 값을 저장한다.
         */
        if (repeat == 0) {
            stats = currentStats;
        }

        if (!isSorted(a, n)) {
            printf("ERROR: %s Sort failed!\n", algorithm);
            free(a);
            return;
        }
    }

    double averageTimeMs =
        (totalTime / REPEAT_COUNT) * 1000.0;

    printf(
        "%-10s %-8s n=%-6d "
        "avg_time=%10.6f ms  "
        "comparisons=%lld  moves=%lld\n",
        algorithm,
        inputType,
        n,
        averageTimeMs,
        stats.comparisons,
        stats.moves
    );

    fprintf(
        file,
        "%s,%s,%d,%.6f,%lld,%lld\n",
        algorithm,
        inputType,
        n,
        averageTimeMs,
        stats.comparisons,
        stats.moves
    );

    free(a);
}

int main(void) {

    /*
     * 고정 seed 사용:
     * 프로그램을 다시 실행해도 같은 난수 순서를 생성한다.
     */
    srand(42);

    int sizes[] = {
        100,
        1000,
        5000,
        10000
    };

    int sizeCount =
        sizeof(sizes) / sizeof(sizes[0]);

    const char *inputTypes[] = {
        "Random",
        "Sorted",
        "Reverse"
    };

    const char *algorithms[] = {
        "Insertion",
        "Merge",
        "Heap"
    };

    FILE *file = fopen("results.csv", "w");

    if (file == NULL) {
        printf("Could not create results.csv\n");
        return 1;
    }

    fprintf(
        file,
        "algorithm,input_type,n,"
        "avg_time_ms,comparisons,moves\n"
    );

    for (int type = 0; type < 3; type++) {

        printf("\n==============================\n");
        printf("%s Input\n", inputTypes[type]);
        printf("==============================\n");

        for (int s = 0; s < sizeCount; s++) {

            int n = sizes[s];

            int *original =
                malloc(sizeof(int) * n);

            if (original == NULL) {
                printf("Memory allocation failed.\n");
                fclose(file);
                return 1;
            }

            if (type == 0) {
                makeRandomArray(original, n);
            }
            else if (type == 1) {
                makeSortedArray(original, n);
            }
            else {
                makeReverseArray(original, n);
            }

            printf("\n--- n = %d ---\n", n);

            for (int alg = 0; alg < 3; alg++) {

                runExperiment(
                    file,
                    algorithms[alg],
                    inputTypes[type],
                    original,
                    n
                );
            }

            free(original);
        }
    }

    fclose(file);

    printf("\nExperiments completed.\n");
    printf(
        "Each timing measurement was repeated %d times.\n",
        REPEAT_COUNT
    );
    printf("Results saved to results.csv\n");

    return 0;
}
