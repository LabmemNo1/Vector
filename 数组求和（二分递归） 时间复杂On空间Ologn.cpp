#include<iostream>
using namespace std;
int sum(int A[], int lo, int hi)
{
	if (lo == hi)
		return A[lo];
	else
	{
		int mid = (lo + hi) / 2;
		return sum(A, lo, mid) + sum(A, mid + 1, hi);
	}
}