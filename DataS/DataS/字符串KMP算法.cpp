#include<string>
//next表构造算法

int* buildNext(char* P)//接受模式串参数
{
	size_t m = strlen(P); int j = 0;
	int *N = new int[m];//next表的创建
	int t = N[0] = -1;
	while (j < m - 1)//对模式串的每一个字符
	{
		if (0 < j || P[j] == P[t])
		{
			j++; t++;

			//这是未改进版，做不到如果p[next[j]]和原来的P[j]相等时的应对情况
			//N[j] = t;//如果p[j]==p[t],则next[j+1]=next[j]+1
			//下面为改进版
			N[j] = (P[j] != P[t] ? t : N[t]);//应对P[j] == P[t]的情况，如果不等，还是用t；如果相等，就换成P[t]的N[t]
		}
		else
			t = N[t];//如果p[j]!=p[t],那么next[j+1]=next[j]+1=next[next[j]]+1····以此类推，直到t=N[0]
		//简单说，就是不断的取之前的Next项，去寻找和p[j]相等的一项，然后t+1，就是p[j]对应的next项
	}
	return N;
}
//kmp主算法
int KMPmatch(char* P, char* T)
{
	int *next = buildNext(P);
	size_t n = strlen(T), i = 0;
	size_t m = strlen(P), j = 0;
	while (j < m&&i < n)
	{
		if (0 > j || T[i] == P[j])//先判断j和0的关系
		{
			i++; j++;
		}
		else
			j = next[j];
	}
	delete[]next;
	return i - j;//和蛮力算法一样，返回算法结束后的文本串的位置
}