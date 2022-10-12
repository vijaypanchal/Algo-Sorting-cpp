#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include "sorting.h"
#include <cstdio>
#include <locale.h>

using namespace std;
#ifndef USE_CLOCK
#define USE_CLOCK	CLOCK_REALTIME 
#endif

/* Other Options to use as clock
CLOCK_REALTIME   
CLOCK_REALTIME_COARSE  
CLOCK_REALTIME_HR
CLOCK_MONOTONIC
CLOCK_MONOTONIC_RAW
CLOCK_MONOTONIC_COARSE
*/

#define Algo_Sorting

#define MaxSize 10000

create_clock(Algo_Sorting, USE_CLOCK)

typedef void (*f_selectionSort)(int A[], int , int );

template <class T>
void comp_exch(T &A, T&B){
	if(B < A ) {
		T temp;
		temp = A;
		A = B;
		B = temp;
	}
}

template <class T>
void exch(T &A, T&B){	
	T temp;
	temp = A;
	A = B;
	B = temp;
}

template <class T>
void insertionSort(T array_in[], int start, int end){
	for(int i = start + 1; i <= end; i++) {
		for(int j = i; j > start; j--){
			comp_exch(array_in[j-1],array_in[j]);
		}
	}
}

void test_sort_function(int N, f_selectionSort pfunc)
{
	cout << "Size of Array Created is " << N << endl;

	int *Array = new int[N];
	// Creating Random Array of Size N	
	for(int i = 0 ; i < N; i++)
		Array[i] = N*100*(1.0*rand()/RAND_MAX);
	cout << "Array is updated with Random Values " << endl;

	start_clock(Algo_Sorting, USE_CLOCK);
	pfunc(Array,0,N-1);
	stop_clock(Algo_Sorting, USE_CLOCK);
	cout << "Array is sorted with insertionSort " << endl;
	
	taken_clock(Algo_Sorting, USE_CLOCK);
	print_clock(Algo_Sorting, USE_CLOCK);

	delete [] Array;
}

template <class T>
void selectionSort(T a[], int start, int end){
	for(int i = start; i < end ; i++){
		int min = i;
		for(int j = i+1; j <=end; j++){
			if(a[j] < a[min]){
				min = j;
			}
			exch(a[i], a[min]);
		}
	}
}

template <class T>
void insertion_modifiedSort(T a[], int start, int end){
	int i;
	for(i = end; i > start; i--){
		comp_exch(a[i-1], a[i]);
	}
	for(i = start+2; i<=end; i++){
		int j = i;
		T v = a[i];
		while(v < a[j-1]){
			a[j] = a[j-1];
			j--;
		}
		a[j] = v;
	}
}

template <class T>
void bubbleSort(T a[], int start, int end){
	for(int i = start; i < end; i++){
		for(int j = end; j >i; j--){
			comp_exch(a[j-1],a[j]);
		}
	}
}

template <class T>
void shellSort(T a[], int start, int end){
	int h;
	for(h = 1; h <= (end-start)/9; h = 3*h +1);
	for( ; h > 0; h /=3){
		for(int i = start + h;i <= end; i++ ){
			int j = i;
			T v = a[i];
			while(j >= start + h && v < a[j-h]){
				a[j] = a[j-h];
				j -= h;
			}
			a[j] = v;
		}
	}
}

int main(int argc, char**argv)
{
	int N;
	if(argc == 2) 
		N = atoi(argv[1]);
	else 
		N = MaxSize;	
	cout << endl;

	cout << "insertionSort >> test_sort_function (" << N << ")" << endl;
	test_sort_function(N, insertionSort);
	cout << endl;

	cout << "selectionSort >> test_sort_function (" << N << ")" << endl;
	test_sort_function(N, selectionSort);
	cout << endl;
	
	cout << "insertion_modifiedSort >> test_sort_function (" << N << ")" << endl;
	test_sort_function(N, insertion_modifiedSort);
	cout << endl;

	cout << "bubbleSort >> test_sort_function (" << N << ")" << endl;
	test_sort_function(N, bubbleSort);
	cout << endl;
	
	cout << "shellSort >> test_sort_function (" << N << ")" << endl;
	test_sort_function(N, shellSort);
	cout << endl;
	

	return 0;
}
