#include<vector>
#include<string>
#include<iostream>
using namespace std;
static size_t RankBinsearch(vector<int> &a, int const &e,size_t &lo, size_t &hi)
{
	
	while (lo < hi) 
	{
		size_t mid = (hi - lo) / 2;
		if (e < a[mid])
		{
			hi = mid;
		}
		else if (a[mid] < e)

		{
			lo = mid + 1;
		}
		else
			return mid;
	}
	return -1;
}
//时间复杂度O（logn）每次耗时o（1）
//迭代器版本

vector<int>::iterator erfen(vector<int> &a,int const &e)
{
	auto begin = a.begin();
	auto end = a.end();
	auto mid = a.begin + (end-begin) / 2;
	while (*mid!=e&&mid!=end)//mid和end相等时等于已经找遍所有元素
	{
		if (e < *mid)
		{
			end = mid;
		}
		else
			begin = mid + 1;
		mid = begin + (end - begin) / 2;
	}
}
//o(1.5logn)