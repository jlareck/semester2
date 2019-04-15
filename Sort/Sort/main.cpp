//
//  main.cpp
//  Sort
//
//  Created by Mykola Medynsky on 4/7/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <algorithm>
using namespace std;
void bubbleSort(double arr[], int size) {
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j< size-1-i; j++) {
            if (arr[j]>arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
}
int partition (double arr[], int low, int high) {
    double pivot = arr[low];
    int i = low;
    
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i], arr[low]);
    return i;
}
void quickSort(double arr[], int low, int high) {
    if (low < high) {
        double partionIndex = partition(arr, low, high);
        quickSort(arr, low, partionIndex - 1);
        quickSort(arr, partionIndex + 1, high);
    }
}
void copyArray(double arr1[],int indexBegin,int indexEnd,double arr2[]) {
    for(int i = indexBegin; i < indexEnd; i++)
        arr2[i] = arr1[i];
}
void topDownMerge(double arr1[],int  indexBegin, int indexMiddle, int indexEnd,double arr2[]) {
    int i = indexBegin, j = indexMiddle;
    for (int k = indexBegin; k < indexEnd; k++) {
        if (i < indexMiddle && (j >= indexEnd || arr1[i] <= arr1[j])) {
            arr2[k] = arr1[i];
            i = i + 1;
        } else {
            arr2[k] = arr1[j];
            j = j + 1;
        }
    }
}

void topDownSplitMerge(double arr2[], int indexBegin,int indexEnd, double arr1[]) {
    if(indexEnd - indexBegin < 2)
        return;

    int iMiddle = (indexEnd + indexBegin) / 2;
   
    
    topDownSplitMerge(arr1, indexBegin,  iMiddle, arr2);
    topDownSplitMerge(arr1, iMiddle,    indexEnd, arr2);
    topDownMerge(arr2, indexBegin, iMiddle, indexEnd, arr1);
}
void topDownMergeSort(double arr1[],double arr2[], int n) {
    copyArray(arr1, 0, n, arr2);
    topDownSplitMerge(arr2, 0, n, arr1);
}
void print(double arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i]<< ' ';
    }
}
void insertionSortForCombinedSorting(double arr[], int n, int indexBegin, int indexEnd) {
    int i, j;
    double key;
    for (i = indexBegin+1; i < indexEnd; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= indexBegin && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void bubbleSortForCombinedSorting(double arr[],int indexBegin, int indexEnd, int size) {
    for (int i = indexBegin; i < indexEnd-1; i++) {
        for (int j = indexBegin; j< indexEnd-1; j++) {
            if (arr[j]>arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
}

void combinationMergeSplitAndBubbleSort(double arr2[], int indexBegin,int indexEnd, double arr1[]) {
    int start = clock();
    if(indexEnd - indexBegin < 2)
        return;
    
  
    int indexMiddle = (indexEnd + indexBegin) / 2;

    if (indexEnd - indexMiddle < 10 || indexMiddle-indexBegin < 10) {
//        bubbleSortForCombinedSorting(arr2, indexBegin, indexMiddle, indexMiddle-indexBegin);
//        bubbleSortForCombinedSorting(arr2, indexMiddle, indexEnd, indexEnd-indexMiddle);
        insertionSortForCombinedSorting(arr2, indexMiddle-indexBegin, indexBegin, indexMiddle );
        insertionSortForCombinedSorting(arr2, indexEnd-indexMiddle, indexMiddle, indexEnd );
        topDownMerge(arr2, indexBegin, indexMiddle, indexEnd, arr1);
    }
    
    else {
        combinationMergeSplitAndBubbleSort(arr1, indexBegin,  indexMiddle, arr2);
         combinationMergeSplitAndBubbleSort(arr1, indexMiddle,    indexEnd, arr2);
         topDownMerge(arr2, indexBegin, indexMiddle, indexEnd, arr1);
    }


}
void combinedSort(double arr1[],double arr2[], int n) {
    copyArray(arr1, 0, n, arr2);
    combinationMergeSplitAndBubbleSort(arr2, 0, n, arr1);
}
void randomArray(double arr[], int size) {
    for (int i = 0; i < size; i++ ) {
        arr[i] = rand()%1000;
    }
}
void benchmarkTopDownMergeSort() {
    const int size = 10000;
    double arr[size];
    
    double arr2[size];
    randomArray(arr, size);
    clock_t start = clock();

    topDownMergeSort(arr, arr2, size);

    clock_t end = clock();
    cout<< "Time: " << ((double)((end-start))/CLOCKS_PER_SEC) << " seconds"<<endl;

}
void benchmarkCombinedSort() {
    const int size = 10000;
    double arr[size];
    
    double arr2[size];
    randomArray(arr, size);
    clock_t start = clock();
   
    combinedSort(arr, arr2, size);
    
    clock_t end = clock();
    cout<< "Time: " << ((double)((end-start))/CLOCKS_PER_SEC) << " seconds"<<endl;
    
}
void benchmarkQuickSort() {
    const int size = 10000;
    double arr[size];
    randomArray(arr, size);
    clock_t start = clock();
    quickSort(arr, 0, size);
    clock_t end = clock();
    cout<< "Time: " << ((double)((end-start))/CLOCKS_PER_SEC) << " seconds"<<endl;
    print(arr, size);
}
void benchmarkBubbleSort() {
    const int size = 10000;
    double arr[size];
    randomArray(arr, size);
    clock_t start = clock();
    bubbleSort(arr, size);
    clock_t end = clock();
    cout<< "Time: " << ((double)((end-start))/CLOCKS_PER_SEC) << " seconds"<<endl;
    print(arr, size);
}
void benchmarkAlgorithm() {
    const int size = 10000;
    double arr[size];
    randomArray(arr, size);
    clock_t start = clock();
    sort(arr, arr+size);
    clock_t end = clock();
    cout<< "Time: " << ((double)((end-start))/CLOCKS_PER_SEC) << " seconds"<<endl;
   // print(arr, size);
}
void demoTopDownMergeSort() {
    const int size = 10000;
    double arr[size];
    
    double arr2[size];
    randomArray(arr, size);
    clock_t start = clock();
    clock_t end = clock();
    cout<< "Time: " << ((double)((end-start))/CLOCKS_PER_SEC) << " seconds"<<endl;
    topDownMergeSort(arr, arr2, size);

}
int main(int argc, const char * argv[]) {
//    double arr[5]={5.3 ,10.8, 10.7, 2.9,11};
//    double arrB[5];
//    // bubbleSo rt(arr, 5);
//    // quickSort(arr, 0, 4);
//    topDownMergeSort(arr, arrB, 5);
//    print(arr, 5 );
    benchmarkQuickSort();
    //benchmarkBubbleSort();
   // benchmarkAlgorithm();
    // cout << "Hello, World!\n";
    //benchmarkTopDownMergeSort();
    return 0;
}
