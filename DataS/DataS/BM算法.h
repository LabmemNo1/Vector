#pragma once
#include<string>
//构造BC表
int* buildBC(char* P)
{
	int *bc = new int[256];//要与字母表等长，这里256随便取得
	for (size_t j = 0; j < 256; j++) bc[j] = -1;//假设所有字符都没有在P中出现过
	for (size_t m = strlen(P), j = 0; j < m; j++)
		bc[P[j]] = j;//画家算法，即使有相同项在不同位置出现，只记录最后一个
	return bc;
}



//构造SS表和GS表
//SS表（最大匹配后缀的长度）
//GS（好后缀） 是i移动的距离
int* buildSS(char* P)
{
	int m = strlen(P); int* ss = new int[m];
	ss[m - 1] = m;//对最后一个字符而言，与之匹配的最长后缀就是整个P串
//以下，从倒数第二个字符开始自右向左扫描P
	for (int lo = m - 1, hi = m - 1, j = lo - 1; j >= 0; j--)
	{
		if ((j > lo) && (ss[m - hi + j - 1] <= j - lo))//情况一
			ss[j] = ss[m - hi + j - 1];//直接用直接计算出的ss[]
		else//情况2
		{
			hi = j; lo = __min(lo, hi);
			while ((0 <= lo) && (P[lo] == P[m - hi + lo - 1]))
				lo--;//逐个比对位于(lo,hi]前段的字符
			ss[j] = hi - lo;
		}
	}
	return ss;

}
int* buildGS(char* P)
{
	int* ss = buildSS(P);
	size_t m = strlen(P); int* gs = new int[m];
	for (size_t j = 0; j < m; j++) gs[j] = m;//初始化
	for (size_t i = 0, j = m - 1; j >= 0; j--)//逆向逐一扫描各字符P[j]
		if (j + 1 == ss[j])//这里意思是第一种情况 p[0,j]==P[m-j+1,m)
			while (i < m - j - 1)//对于P[m-j-1]左侧的每个字符P[i]而言
				gs[i++] = m - j - 1;//P[m-j-1]都是一种选择
	for (size_t j = 0; j < m - 1; j++)//画家算法
		gs[m - ss[j] - 1] = m - j - 1;//m-j-1必然是gs[m-ss[j]-1]值的一种选择
}















int BMmatch(char* P, char* T)
{
	int *bc = buildBC(P); int *gs = buildGS(P);//构建BC表（坏字符表） GS表（好后缀表）
	size_t i = 0;//模式串相对于文本串中，文本串的位置（起始时平齐）
	while (strlen(T) >= strlen(P) + i)//在循环中i是不断变大的
		//意思就是模式串不动的话，文本串在不断左移
	{
		size_t j = strlen(P) - 1;//从P[j]开始比对
		while (P[j] == T[i + j])
			if (0 > --j) break;//if语句里的条件肯定执行，但是break要条件满足才会执行
		//这里就是匹配成功了
		if (0 > j)
			break;//匹配成功
		else//这里else会在上面P[j]!=T[i+j]这个while循环
			//条件不满足时，并且还有前缀没有比对时执行
			i += __max(gs[j], j - bc[T[i + j]]);//位移量根据两个表那个位移量大
	}
	delete []bc;
	delete []gs;
	return i;
}