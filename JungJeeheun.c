#include <stdio.h>
#include <stdlib.h> // rand() 함수 포함 라이브러리
#include <time.h> // time()함수 포함 라이브러리

void random_generated_data(int* array, int size) {
	srand(time(NULL)); // 매번 다른 시드값 생성
	for (int i = 0; i < size; i++) // 배열에 랜덤값 부여
		array[i] = random();
}

float Exchange_sort(int* array, int size) {
	int temp = 0;
	float res;
	clock_t tstart, tend;

	tstart = clock();
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			temp = array[i];
			array[i]; array[j];
			array[j] = temp;
		}
	}
	tend = clock();
	res = (float)(tend - tstart) / CLOCKS_PER_SEC;
	printf("Exchange sort함수의 실행시간: %f\n", res);
	return res;
}

void merge(int* array, int start, int mid, int end) {
	int i = start, j = mid + 1, k = start;
	int* sorted = malloc(sizeof(int) * (end + 1));
	while (i <= mid && j <= end) {
		if (array[i] <= array[j])
			sorted[k++] = array[i++];
		else
			sorted[k++] = array[j++];
	}
	while (i <= mid)
		sorted[k++] = array[i++];
	while (j <= end)
		sorted[k++] = array[j++];
	for (int q = start; q <= end; q++)
		array[q] = sorted[q];
	free(sorted);
}

void mergesort(int* array, int start, int end) {
	int mid;

	if (start < end) {
		mid = (start + end) / 2;
		mergesort(array, start, mid);
		mergesort(array, mid + 1, end);
		merge(array, start, mid, end);
	}
}

float Mergesort(int* array, int start, int end) {
	float res;
	clock_t tstart, tend;

	tstart = clock();
	mergesort(array, start, end);
	tend = clock();
	res = (float)(tend - tstart) / CLOCKS_PER_SEC;
	printf("Mergesort함수의 실행시간: %f\n", res);
	return res;
}

void quicksort(int* array, int left, int right) {
	int L = left, R = right;
	int temp;
	int pivot = array[(left + right) / 2];
	
	while (L <= R) {
		while (array[L] < pivot)
			L++;
		while (array[R] > pivot)
			R--;
		if (L <= R) {
			if (L != R) {
				temp = array[L];
				array[L] = array[R];
				array[R] = temp;
			}
			L++; 
			R--;
		}
	}
	if (left < R)
		quicksort(array, left, R);
	if (L < right)
		quicksort(array, L, right);
}

float Quicksort(int* array, int left, int right) {
	float res;
	clock_t tstart, tend;

	tstart = clock();
	quicksort(array, left, right);
	tend = clock();
	res = (float)(tend - tstart) / CLOCKS_PER_SEC;
	printf("Quicksort함수의 실행시간: %f\n", res);
	return res;
}

void heapify(int* arr, int heapsize) {
	for (int i = 1; i < heapsize; ++i) {
		int child = i;
		do {
			int root = (child - 1) / 2;
			if (arr[root] < arr[child]) {
				int space = arr[root];
				arr[root] = arr[child];
				arr[child] = space;
			}
			child = root;
		} while (child != 0);
	}
}

void heap(int* arr, int* heapsize) {
	int space = arr[0];
	arr[0] = arr[*heapsize - 1];
	arr[*heapsize - 1] = space;
	--(*heapsize);
}

float Heapsort(int* array, int size) {
	int heapsize = size;
	float res;
	clock_t tstart, tend;

	tstart = clock();
	for (int i = 0; i < heapsize; i++) {
		heapify(array, heapsize);
		heap(array, &heapsize);
	}
	tend = clock(); 
	res = (float)(tend - tstart) / CLOCKS_PER_SEC;
	printf("Heapsort함수의 실행시간: %f\n", res);
	return res;
}

float Radix_sort(int* array, int size) {
	int* result = malloc(sizeof(int) * size);
	int maxV = 0;
	int remain = 1;
	float res;
	clock_t tstart, tend;

	tstart = clock();
	for (int i = 0; i < size; i++) {
		if (array[i] > maxV) 
			maxV = array[i];
	}
	while (maxV / remain > 0) { // 1의 자릿수 계산
		int cases[10] = { 0 };
		for (int i = 0; i < size; i++) 
			cases[array[i] / remain % 10]++; // 자릿수 배열 처리
		for (int i = 1; i < 10; i++)
			cases[i] += cases[i - 1]; // 누적 계산 : 결과 배열을 만들기 위해서!	
		for (int i = size - 1; i >= 0; i--) { //같은 자릿수 끼리는 순서를 유지
			result[--cases[array[i] / remain % 10]] = array[i];
		}
		for (int i = 0; i < size; i++) 
			array[i] = result[i]; // 기본 배열 갱신
		remain *= 10;
	}
	tend = clock();
	res = (float)(tend - tstart) / CLOCKS_PER_SEC;
	printf("Radix_sort함수의 실행시간: %f\n", res);
	return res;
}

int main() {
	int datasize[5] = {100, 500, 1000, 5000, 10000}; // random generated data의 갯수
	
	for(int i = 0 ; i < 5; i++) {
		int size = datasize[i]; // sorttime은 각 sorting의 평균을 계산할 그릇
		int* array = malloc(sizeof(int) * size); // random generated data값을 담을 array배열 동적할당
		float E = 0, M = 0, Q = 0, H = 0, R = 0; //각 sorting의 평균을 계산할 그릇

		printf("random generated data의 갯수가 %d일때\n", size);
		for (int test_case = 0; test_case < 5; test_case++) { // test case 총 5번 실행 
			random_generated_data(array, size); //  random generated data값 만들기
			E += Exchange_sort(array, size); // Exchange_sort의 실행시간 출력
			M += Mergesort(array, 0, size - 1); //Mergesort의 실행시간 출력
			Q += Quicksort(array, 0, size - 1); //Quicksort의 실행시간 출력
			H += Heapsort(array, size); //Heapsort의 실행시간 출력
			R += Radix_sort(array, size); //Radix sort의 실행시간 출력
		}
		printf("\n");
		printf("Exchange_sort의 평균 실행시간: %f\n", E / 5);
		printf("Mergesort의 평균 실행시간: %f\n", M/5);
		printf("Quicksort의 평균 실행시간: %f\n", Q / 5);
		printf("Heapsort의 평균 실행시간: %f\n", H/5);
		printf("Radix sort의 평균 실행시간: %f\n\n",R / 5);
		free(array);
	}
	return 0;
}
