//Jahir Montes 1001635994
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//GTA...The file generator program creates 1 more number than instructed.

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    const int n1 = m - l + 1; //size of left array
    const int n2 = r - m; //size of right array

    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));



    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];


    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    //once either the right or left array have been used completely, just insert everything from the remaining array
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }


    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r) {

        int m = (l + r) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
        greater than key, to one position ahead
        of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// A utility function to print an array of size n
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}


int main(int argc, char** argv)
{
  /////////////////////////////////////////////////////////////////

    //FILE HANDLING

    FILE* fp;
    fp = fopen(argv[1], "r");

    if (fp == NULL)
    {
        printf("File doesn't exist \n");
        exit(1);
    }

    long counter = 0;
    char fileLine[100];
    while (!feof(fp))
    {
        fgets(fileLine, 20, fp);
        counter++;
    }
    long nlines = counter-1;
    printf("\nThere is a total of %ld lines!\n", nlines);

    fseek(fp, 0, SEEK_SET);//set pointer to beginning of FILE

/////////////////////////////////////////////////////////////////
    //set up clocks
    clock_t start, end;
    double ticks;

    //PREPARE FOR MERGE SORT
    //DYNAMICALLY ALLOCATE AMOUNT OF LINES
    int* arr = (int*) malloc(nlines * sizeof(int));

    int conversion;

    counter = 1;

    //READ THROUGH FILE AGAIN AND STORE INFO IN ARRAY
    while (!feof(fp))
    {
        fgets(fileLine, 20, fp);
        conversion = atoi(fileLine);
        arr[counter-1] = conversion;
        counter++;
    }

    #ifdef PRINTARRAY
    printf("\n");
    printArray(arr, nlines);
    #endif

    printf("\nMerge Sort\n");

    start = clock();
    mergeSort(arr, 0, nlines-1);
    end = clock();

    ticks = (double)(end-start);
    printf("\nNet Ticks: %f\n", ticks);


    #ifdef PRINTARRAY
    printf("\n");
    printArray(arr, nlines);
    #endif

    fseek(fp, 0, SEEK_SET);//set pointer to beginning of FILE
    //DELETE ARRAY AND REMAKE IT IN HEAP
    free(arr);

/////////////////////////////////////////////////////////////
    //PREPARE FOR INSERTION SORT

    //DYNAMICALLY ALLOCATE AMOUNT OF LINES
    arr = (int*) malloc(nlines * sizeof(int));

    counter = 1;
    //READ THROUGH FILE AGAIN AND STORE INFO IN ARRAY
    while (!feof(fp))
    {
        fgets(fileLine, 20, fp);
        conversion = atoi(fileLine);
        arr[counter-1] = conversion;
        counter++;
    }

/////////////////////////////////////////////////////////////
    #ifdef PRINTARRAY
    printf("\n");
    printArray(arr, nlines);
    #endif

    printf("\nInsertion Sort\n");
    start = clock();
    insertionSort(arr, nlines);
    end = clock();

    ticks = (double)(end - start);
    printf("\nNet Ticks: %f\n", ticks);

    #ifdef PRINTARRAY
    printf("\n");
    printArray(arr, nlines);
    #endif

    free(arr);
    fclose(fp);
    return 0;
}
