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
void bubbleSort(double arr[], int size, bool flag) {
    if (flag)
    cout <<"Bubble sort algorithm is simple to understand. It works by repeatedly swapping the adjacent elements if they are in wrong order"<<endl;
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j< size-1-i; j++) {
            if (arr[j]>arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
 
}
int partition (double arr[], int low, int high, bool& flag) {
    double pivot = arr[low];
    int i = low;
    if (flag){
        
        cout << "This function takes first(in this case leftmost) element as pivot, places the pivot element at its correct position in sorted array, and places all smaller (smaller than pivot) to left of pivot and all greater elements to right of pivot"<<endl;
        flag = false;
    }
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i], arr[low]);
    return i;
}
void quickSort(double arr[], int low, int high, bool& flag) {
   static bool partitionFlag = true;
    
    if (low < high) {

        double partionIndex = partition(arr, low, high, partitionFlag);
        if (flag){
            cout << "Lomuto partition scheme is optimized quicksort algorithm. Separately sort elements before partition and after partition"<<endl;
            flag = false;
        }
        quickSort(arr, low, partionIndex - 1, flag);
        quickSort(arr, partionIndex + 1, high, flag);
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

void topDownSplitMerge(double arr2[], int indexBegin,int indexEnd, double arr1[], bool& flag) {
 
    if (indexEnd - indexBegin < 2)
        return;

    int iMiddle = (indexEnd + indexBegin) / 2;
    
    if (flag){
        flag = false;
        cout << "Recursively divide on n subarrays and then merge them"<<endl;
    }
    topDownSplitMerge(arr1, indexBegin, iMiddle, arr2, flag);
    topDownSplitMerge(arr1, iMiddle,   indexEnd, arr2, flag);
    topDownMerge(arr2, indexBegin, iMiddle, indexEnd, arr1);
}
void topDownMergeSort(double arr1[],double arr2[], int n, bool flag) {
    if (flag) {
        cout << "Array1 has the items to sort and array2 is a work array"<<endl;
        cout << "Firstly goes duplication of array1 into array2"<<endl;
        cout << "Than sorting progress" << endl;
    }
    copyArray(arr1, 0, n, arr2);
    topDownSplitMerge(arr2, 0, n, arr1, flag);
}
void print(double arr[], int size) {
    
    for (int i = 0; i < size; i++) {
        cout << arr[i]<< ' ';
    }
}
void insertionSortForCombinedSorting(double arr[], int n, int indexBegin, int indexEnd) { // this function can be used in combined sort algorithm instead of bubble sort
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

void combinationMergeSplitAndBubbleSort(double arr2[], int indexBegin,int indexEnd, double arr1[], bool& flag) {
   
    if (indexEnd - indexBegin < 2)
        return;
    
    if (flag){
        cout << "Recursively divide on subarrays and when the size of those subarrays are less than 10 -> uses bubble sort and and after that runs merge function"<<endl;
        flag = false;
    }
  
    int indexMiddle = (indexEnd + indexBegin) / 2;

    if (indexEnd - indexMiddle < 10 || indexMiddle-indexBegin < 10) {
        bubbleSortForCombinedSorting(arr2, indexBegin, indexMiddle, indexMiddle-indexBegin);
        bubbleSortForCombinedSorting(arr2, indexMiddle, indexEnd, indexEnd-indexMiddle);
  //      insertionSortForCombinedSorting(arr2, indexMiddle-indexBegin, indexBegin, indexMiddle );
  //      insertionSortForCombinedSorting(arr2, indexEnd-indexMiddle, indexMiddle, indexEnd );
        topDownMerge(arr2, indexBegin, indexMiddle, indexEnd, arr1);
    }
    
    else {
        combinationMergeSplitAndBubbleSort(arr1, indexBegin,  indexMiddle, arr2, flag);
        combinationMergeSplitAndBubbleSort(arr1, indexMiddle,    indexEnd, arr2, flag);
        topDownMerge(arr2, indexBegin, indexMiddle, indexEnd, arr1);
    }


}
void combinedSort(double arr1[],double arr2[], int n, bool flag) {
    copyArray(arr1, 0, n, arr2);
    if (flag) {
        cout << "Array1 has the items to sort and array2 is a work array"<<endl;
        cout << "Firstly goes duplication of array1 into array2"<<endl;
        cout << "Than sorting progress" << endl;
    }
    combinationMergeSplitAndBubbleSort(arr2, 0, n, arr1, flag);
}
void randomArray(double arr[], int size) {
    for (int i = 0; i < size; i++ ) {
        arr[i] = rand()%1000;
    }
}
void benchmarkTopDownMergeSort() {
    const int size = 100;
    double arr[size];
    
    double arr2[size];
    randomArray(arr, size);
    clock_t start = clock();
    bool flag = false;
    topDownMergeSort(arr, arr2, size,flag);

    clock_t end = clock();
    cout<< "Time: " << ((double)((end-start))/CLOCKS_PER_SEC) << " seconds"<<endl;

}
void benchmarkCombinedSort() {
    const int size = 100;
    double arr[size];
    
    double arr2[size];
    randomArray(arr, size);
    clock_t start = clock();
   bool flag = false;
    combinedSort(arr, arr2, size, flag);
    
    clock_t end = clock();
    cout<< "Time: " << ((double)((end-start))/CLOCKS_PER_SEC) << " seconds"<<endl;
    
}
void benchmarkQuickSort() {
    const int size = 100;
    double arr[size];
    randomArray(arr, size);
    clock_t start = clock();
    bool flag = false;
    quickSort(arr, 0, size,flag);
    clock_t end = clock();
    cout<< "Time: " << ((double)((end-start))/CLOCKS_PER_SEC) << " seconds"<<endl;
    //print(arr, size);
}
void benchmarkBubbleSort() {
    const int size = 100;
    double arr[size];
    randomArray(arr, size);
    clock_t start = clock();
    bool flag = flag;
    bubbleSort(arr, size, flag);
    clock_t end = clock();
    cout<< "Time: " << ((double)((end-start))/CLOCKS_PER_SEC) << " seconds"<<endl;
    //print(arr, size);
}
void benchmarkAlgorithm() {
    const int size = 100;
    double arr[size];
    randomArray(arr, size);
    clock_t start = clock();
    sort(arr, arr+size);
    clock_t end = clock();
    cout<< "Time: " << ((double)((end-start))/CLOCKS_PER_SEC) << " seconds"<<endl;
   // print(arr, size);
}
void demoTopDownMergeSort() {
    const int size = 100;
    double arr[size];
    double arr2[size];
    randomArray(arr, size);
    bool flag = true;
    combinedSort(arr, arr2, size, flag);
    print(arr, size);
    flag = true;
    cout << endl;
    randomArray(arr, size);
    bubbleSort(arr,size, flag);
    print(arr, size);
    cout << endl;
    flag = true;
    randomArray(arr, size);
    topDownMergeSort(arr, arr2, size, flag);
    print(arr, size);
    cout << endl;
      flag = true;
    quickSort(arr, 0, size,flag);
    print(arr, size);
}
int main(int argc, const char * argv[]) {

//    benchmarkTopDownMergeSort();
//    benchmarkBubbleSort();
//    benchmarkQuickSort();
//    benchmarkCombinedSort();
//    benchmarkAlgorithm();
   
    demoTopDownMergeSort();
    
    return 0;
}
