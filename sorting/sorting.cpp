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

#define MaxSize 1000

create_clock(Algo_Sorting, USE_CLOCK)

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
void sort_insertion(T array_in[], int start, int end){
	for(int i = start + 1; i <= end; i++) {
		for(int j = i; j > start; j--){
			comp_exch(array_in[j-1],array_in[j]);
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

	cout << "Size of Array Created is " << N << endl;

	int *Array = new int[N];
	// Creating Random Array of Size N	
	for(int i = 0 ; i < N; i++)
		Array[i] = N*100*(1.0*rand()/RAND_MAX);
	cout << "Array is updated with Random Values " << endl;

	start_clock(Algo_Sorting, USE_CLOCK);
	sort_insertion(Array,0,N-1);
	stop_clock(Algo_Sorting, USE_CLOCK);
	cout << "Array is sorted with sort_insertion " << endl;
	
	taken_clock(Algo_Sorting, USE_CLOCK);
	print_clock(Algo_Sorting, USE_CLOCK);

	delete [] Array;

	return 0;
}
