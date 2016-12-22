#include <stdio.h>
#include <stdlib.h>

void seqsearch(int n, const int S[], int x, int location, int *count);
void binsearch(int n, const int S[], int x, int location, int *count);
int fib(int n, int *count);
int fib2(int n, int *count);
void mergesort(int n, int S[], int *count);
void copy(int A[], int a, int b, int B[], int c, int d);
void merge(int h, int m, const int U[], const int V[], int S[], int *count);
void quicksort(int low, int high, int S[], int *count);
void partition(int low, int high, int *pivotpoint, int S[], int *count);

int main(void) {
	int n[4] = { 0, 10, 100, 1000 }; // 입력할 n의 크기
	int fibo[4] = { 0, 5, 10, 15 }; // 수보나치 수열 함수의 입력할 n의 크기
	int sort[4] = { 0, 8, 32, 128 };
	int S[1001] = { 0 };
	int count = 0; // 횟수
	int x = 1;
	int location = 0;
	int i;
	int a;
	
	for (i = 1000; i > 0; i--)
		S[1001-i] = i;

	for (i = 1; i <= 3; i++) {
		count = 0;
		seqsearch(n[i], S, x, location, &count);
		printf("The count of seqsearch(n = %d) : %d\n", n[i], count);
	}
	
	printf("\n");

	for (i = 1; i <= 3; i++) {
		count = 0;
		binsearch(n[i], S, x, location, &count);
		printf("The count of binary search(n=%d) : %d\n", n[i], count);
	}

	printf("\n");

	for (i = 1; i <= 3; i++) {
		count = 0;
		fib(fibo[i], &count);
		printf("The count of fib(n = %d) : %d\n", fibo[i], count);
	}
	
	printf("\n");

	for (i = 1; i <= 3; i++) {
		count = 0;
		fib2(fibo[i], &count);
		printf("The count of fib2(n = %d) : %d\n", fibo[i], count);
	}

	printf("\n");

	for (i = 1000; i > 0; i--)
		S[1001 - i] = i;

	for (i = 1; i <= 3; i++) {
		count = 0;
		mergesort(sort[i], S, &count);
		printf("The count of mergesort(n = %d) : %d\n", sort[i], count);
	}

	printf("\n");
	
	for (i = 1000; i > 0; i--)
		S[1001 - i] = i;

	for (i = 1; i <= 3; i++) {
		count = 0;
		quicksort(1, sort[i], S, &count);
		printf("The count of quicksort(n = %d) : %d\n", sort[i], count);
	}

	return 0;
}
void seqsearch(int n, const int S[], int x, int location, int *count) {
	location = 1;
	while (location <= n && S[location] != x) {
		location++;
		(*count)++;
	}
	if (location > n)
		location = 0;
}

void binsearch(int n, const int S[], int x, int location, int *count) {
	int low, high, mid;

	low = 1; high = n;
	location = 0;
	while (low <= high && location == 0) {
		mid = (low + high) / 2;
		(*count)++;
		if (x == S[mid])
			location = mid;
		else if (x < S[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
}

int fib(int n, int *count) {
	(*count)++;
	
	if (n <= 1)
		return n;
	else
		return fib(n - 1, count) + fib(n - 2, count);
}

int fib2(int n, int *count)
{	
	int i, fn;
	int *f = (int*)malloc(sizeof(int) * (n + 1));

	f[0] = 0;
	if (n > 0) {
		f[1] = 1;
		for (i = 2; i <= n; i++) {
			f[i] = f[i - 1] + f[i - 2];
			(*count)++;
		}
	}
	fn = f[n];
	free(f);
	return fn;
}

void mergesort(int n, int S[], int *count) {
	if (n > 1) {
		int i;
		const int h = n / 2, m = n - h;
		int *U = (int*)malloc(sizeof(int) * (h + 1));
		int *V = (int*)malloc(sizeof(int) * (m + 1));
		(*count)++;
		
		for (i = 1; i <= h; i++)
			U[i] = S[i];
		for (i = 1; i <= m; i++)
			V[i] = S[i + h];
		mergesort(h, U, count);
		mergesort(m, V, count);
		merge(h, m, U, V, S, count);
	}
}

void copy(int A[], int a, int b, int B[], int c, int d) {
	while (1) {
		B[c] = A[a];
		if (a == b && c == d)
			break;
		c++;
		a++;
	}
}

void merge(int h, int m, const int U[], const int V[], int S[], int *count) {
	int i, j, k, a;
	i = 1; j = 1; k = 1;
	while (i <= h && j <= m) {
		if (U[i] < V[j]) {
			S[k] = U[i];
			i++;
		}
		else {
			S[k] = V[j];
			j++;
		}
		k++;
		(*count)++;
	}
	if (i > h)
		copy(V, j, m, S, k, h + m);
	else
		copy(U, i, h, S, k, h + m);
}

void quicksort(int low, int high, int S[], int *count) {
	int pivotpoint = 0;

	if (high > low) {
		partition(low, high, &pivotpoint, S, count);
		quicksort(low, pivotpoint - 1, S, count);
		quicksort(pivotpoint + 1, high, S, count);
	}
}

void partition(int low, int high, int *pivotpoint, int S[], int *count) {
	int i, j;
	int temp;
	int pivotitem;

	pivotitem = S[low];
	j = low;
	for(i = low+1; i <= high; i++)
		if (S[i] < pivotitem) {
			j++;
			temp = S[j];
			S[j] = S[i];
			S[i] = temp;
			(*count)++;
		}
	*pivotpoint = j;
	
	temp = S[low];
	S[low] = S[*pivotpoint];
	S[*pivotpoint] = temp;
}