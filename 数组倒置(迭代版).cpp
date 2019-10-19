#include<iostream>
using namespace std;
void reverse(int* A, int lo, int hi)
{
	while (lo < hi)
		swap(A[lo++], A[hi--]);
}