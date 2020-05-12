#pragma once
void Swap(int* array, int l, int r);

void insertSort(int* array, int n);

void shellSort(int* array, int n);

void selectSort1(int* array, int n);

void selectSort2(int* array, int n);

void shiftDown(int* array, int n, int parent);

void heapSort(int* array, int n);

void bubbleSort(int* array, int n);

int GetMid(int* array, int begin, int end);

int partion1(int* array, int begin, int end);

int partion2(int* array, int begin, int end);

int partion3(int* array, int begin, int end);

void quickSortR(int* array, int begin, int end);

void merge(int* array, int begin, int mid, int end,int* tmp);

void mergeSoerR(int* array, int begin, int end, int* tmp);

void mergeSort(int* array, int n);




