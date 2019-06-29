//
//  main.cpp
//  multithreadingMergeSort
//
//  Created by Mykola Medynsky on 6/14/19.
//  Copyright © 2019 Mykola Medynskyi. All rights reserved.
//

#include <iostream>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#define MAX 20

#define THREAD_MAX 4

using namespace std;

int arr[MAX];
int part = 0;

void merge(int low, int mid, int high)
{
    int* left = new int[mid - low + 1];
    int* right = new int[high - mid];

    int size1 = mid - low + 1, size2 = high - mid, i, j;

    for (i = 0; i < size1; i++)
        left[i] = arr[i + low];

    for (i = 0; i < size2; i++)
        right[i] = arr[i + mid + 1];
    
    int k = low;
    i = j = 0;
    
    while (i < size1 && j < size2) {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < size1) {
        arr[k++] = left[i++];
    }

    while (j < size2) {
        arr[k++] = right[j++];
    }
}

void merge_sort(int low, int high)
{

    int mid = low + (high - low) / 2;
    if (low < high) {
        

        merge_sort(low, mid);
        

        merge_sort(mid + 1, high);
        
 
        merge(low, mid, high);
    }
}

// thread function for multi-threading
void* merge_sort(void *arg)
{
    int thread_part = part++;
    
    cout << "Thread enter "<< thread_part<<endl;

    int low = thread_part * (MAX / 4);
    int high = (thread_part + 1) * (MAX / 4) - 1;
    

    int mid = low + (high - low) / 2;
    if (low < high) {
        merge_sort(low, mid);
        merge_sort(mid + 1, high);
        merge(low, mid, high);
    }
    //sleep(rand()%5);
    
    cout << "Thread leave"<< thread_part<<endl;
    
    return 0;
}


int main()
{

    for (int i = 0; i < MAX; i++)
        arr[i] = rand() % 100;
    

    clock_t start, end;
    
    start = clock();
    pthread_t threads[THREAD_MAX];


    for (int i = 0; i < THREAD_MAX; i++)
        pthread_create(&threads[i], NULL, merge_sort, (void*)NULL);
    

    for (int i = 0; i < 4; i++){
        cout << "Join enter" << i <<endl;
        pthread_join(threads[i], NULL);
        cout << "Join finish" << i <<endl;
    }
    cout << "Join leave" <<endl;

    merge(0, (MAX / 2 - 1) / 2, MAX / 2 - 1);
    merge(MAX / 2, MAX/2 + (MAX-1-MAX/2)/2, MAX - 1);
    merge(0, (MAX - 1)/2, MAX - 1);
    
    end = clock();
    

    cout << "Sorted array: ";
    for (int i = 0; i < MAX; i++)
        cout << arr[i] << " ";
    

    cout << "Time taken: " << (end - start) / (double)CLOCKS_PER_SEC << endl;
    
    return 0;
}

