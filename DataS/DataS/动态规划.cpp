#include<string>
#include<vector>
using namespace std;
int max(int a, int b)
{
	return a > b ? a : b;
}

int lcs(string &x, string &y, int m, int n)
{
	int biggest = 0;
	//vector的二维数组，动态规划表
	vector<vector<int> > table(m + 1, vector<int>(n + 1));
	for (int i = 0; i < m + 1; ++i)
		for (int j = 0; j < n + 1; ++j)
		{
			if (i == 0 || j == 0)
				table[i][j] = 0;
			else if (x[j - 1] == y[i - 1])//减而制之
				table[i][j] = table[i - 1][j - 1] + 1;
			else
				table[i][j] = max(table[i - 1][j], table[i][j - 1]);


		}
	return table[m][n];
}
