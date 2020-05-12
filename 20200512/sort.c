#include "sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
void Swap(int* array, int l, int r) {
	int tmp = array[l];
	array[l] = array[r];
	array[r] = tmp;
}
//直接插入排序
void insertSort(int* array, int n) {
	for (int i = 0; i < n - 1; i++) {
		int end = i;
		int key = array[i + 1];
		while (end >= 0 && array[end] > key) {
			array[end + 1] = array[end];
			end--;
		}
		array[end + 1] = key;
	}
}
//希尔排序
void shellSort(int* array, int n) {
	int gap = n;
	while (gap>1) {
		gap /= 2;
		for (int i = 0; i < n - gap; i += gap) {
			int end = i;
			int key = array[end + gap];
			while (end >= 0 && array[end] > key) {
				array[end + gap] = array[end];
				end -= gap;
			}
			array[end + gap] = key;
		}
	}
}

void selectSort1(int* array, int n) {
	for (int i = 0; i < n - 1; i++) {
		int min = i,start = i;
		for (int j = i + 1; j < n; j++) {
			if (array[j] <array[min])
				min = j;
		}
		Swap(array, start, min);
	}
}

void selectSort2(int* array, int n) {
	int begin = 0;
	int end = n - 1;
	while (begin < end) {
		int min = begin;
		int max = begin;
		for (int i = begin + 1; i <= end; i++) {
			if (array[i] < array[min])
				min = i;
			if (array[i] >= array[max])
				max = i;
		}
		Swap(array, begin, min);
		if (max == begin)
			max = min;
		Swap(array, end, max);
		begin++;
		end--;
	}
}

void shiftDown(int* array, int n, int parent) {
	int child = 2 * parent + 1;
	while (child < n) {
		if (child + 1 < n&&array[child + 1] > array[child]) {
			child++;
		}
		if (array[parent] < array[child]) {
			Swap(array, parent, child);
			parent = child;
			child = 2 * parent + 1;
		}
		else
			break;
	}
}

void heapSort(int* array, int n) {
	for (int i = (n - 2) / 2; i >= 0; i--) {
		shiftDown(array, n, i);
	}
	while (n) {
		Swap(array, 0, n - 1);
		n--;
		shiftDown(array, n, 0);
	}
}

void bubbleSort(int* array, int n) {
	while (n) {
		int flag = 1;
		for (int i = 0; i < n - 1; i++) {
			if (array[i + 1] < array[i])
				Swap(array, i, i + 1);
			flag = 0;
		}
		if (flag)
			return;
		n--;
	}
}

int GetMid(int* array, int begin, int end) {
	int mid = begin + (end - begin) / 2;
	if (array[begin] < array[mid]) {
		if (array[mid] < array[end])
			return mid;
		else {
			if (array[begin] > array[end])
				return begin;
			else
				return end;
		}
	}
	else {
		if (array[mid] > array[end])
			return mid;
		else {
			if (array[begin] > array[end])
				return end;
			else
				return begin;
		}
	}
}
//hoare法
int partion1(int* array, int begin, int end) {
	int mid = GetMid(array, begin, end);
	Swap(array, begin, mid);
	int start = begin;
	int key = array[begin];
	while (begin < end) {
		while (begin < end && array[end] >= key) {
			end--;
		}
		while (begin < end && array[begin] <= key) {
			begin++;
		}
		Swap(array, begin, end);
	}
	Swap(array, start, begin);
	return begin;
}
//挖坑填坑法
int partion2(int* array, int begin, int end) {
	int mid = GetMid(array, begin, end);
	Swap(array, begin, mid);
	int key = array[begin];
	while (begin < end) {
		while (begin < end && array[end] >= key)
			end--;
		array[begin] = array[end];
		while (begin < end && array[begin] <= key)
			begin++;
		array[end] = array[begin];
	}
	array[begin] = key;
	return begin;
}
//前后指针法(双索引)
int partion3(int* array, int begin, int end) {
	int mid = GetMid(array, begin, end);
	Swap(array, begin, mid);
	int prev = begin;
	int cur = prev + 1;
	int key = array[begin];
	while (cur <= end) {
		while (array[cur] < key && ++prev != cur) {
			Swap(array, prev, cur);
		}
		cur++;
	}
	Swap(array, begin, prev);
	return prev;
}

void quickSortR(int* array, int begin, int end) {
	if (begin >= end)
		return;
	int keypos = partion3(array, begin, end);
	quickSortR(array, begin, keypos - 1);
	quickSortR(array, keypos + 1, end);
}
//合并
void merge(int* array, int begin, int mid, int end, int* tmp) {
	int begin1 = begin, end1 = mid, begin2 = mid + 1, end2 = end;
	int idx = begin;
	while (begin1 <= end1 && begin2 <= end2) {
		if (array[begin1] <= array[begin2])
			tmp[idx++] = array[begin1++];
		else
			tmp[idx++] = array[begin2++];
	}
	if (begin1 <= end1)
		memcpy(tmp + idx, array + begin1, sizeof(int)*(end1 - begin1 + 1));
	if(begin2 <= end2)
		memcpy(tmp + idx, array + begin2, sizeof(int)*(end2 - begin2 + 1));
	memcpy(array + begin, tmp + begin, sizeof(int)*(end - begin + 1));
}

void mergeSortR(int* array, int begin, int end, int* tmp) {
	if (begin >= end)
		return;
	int mid = begin + (end - begin) / 2;
	mergeSortR(array, begin, mid, tmp);
	mergeSortR(array, mid + 1, end, tmp);
	merge(array, begin, mid, end, tmp);
}

void mergeSort(int* array, int n) {
	int* tmp = (int*)malloc(sizeof(int)*n);
	mergeSortR(array, 0, n-1,tmp);
	free(tmp);
}

