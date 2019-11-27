#pragma once
#include<string>
class Bitmap
{
private:
	char* M; int N;//比特图存放的空间M[]，容量为N*sizeof(char)*8比特
protected:
	void init(int n) { M = new char[N = (n + 7) / 8]; memset(M, 0, N); }//位图初始化，为了保证容得下全部的位数，我们要+7再除以8(一个字节八位)，然后把每一位置零
public:
	Bitmap(int n = 8) { init(n); }//构造函数 默认值设成8了 方便测试
	Bitmap(char* file,int n=8)//按指定或者这个默认的规模 从指定的文件中读取比特图
	{
		init(n);
		FILE* fp = fopen(file, "r");//打开文件file 以只读方式打开
		fread(M, sizeof(char), N, fp);//存放在M里，块长度是8，N块
		fclose(fp);
	}
	~Bitmap() { delete[]M; M = NULL; }

	//下面是对位图三个关键的操作
	//k>>3可以得到在空间M中k所对应的的秩
	//k&0x07 可以确定k这一比特位在所属字节中的位置
	//0x80>>(k&0x07)得到该比特位在此字节中对应的数值掩码（原理不太懂）
	//对应的字节与掩码做逻辑或运算，可将比特位设置为1；做逻辑与运算可以测试状态；与掩码的反码做位与运算，将比特位设置为0
	
	void set(int k)//将第k位置为true(将整数i加入当前集合)
	{
		expand(k);
		M[k >> 3] |= (0x80 >> (k & 0x07));
	}
	void clear(int k)//将第k位置为false(从当前集合中删除整数i)
	{
		expand(k);
		M[k >> 3] &= ~(0x80 >> (k & 0x07));
	}
	bool test(int k)//测试第k位是不是true
	{
		expand(k);
		return M[k >> 3] &&(0x80 >> (k & 0x07));
	}


	void dump(char* file)//将位图整体导出至指定的文件，以便对此后的新位图批量初始化
	{
		FILE* fp = fopen(file, "w");//为输出操作创造一个空文件
		fwrite(M, sizeof(char), N, fp);
		fclose(fp);
	}
	char* bits2string(int n)//将前n位转换为字符串
	{
		expand(n - 1);//此时可能被访问的最高位为bitmap[n-1]
		char* s = new char[n + 1]; s[n] = '\0';
		for (int i = 0; i < n; i++) s[i] = test(i) ? '1' : '0';
		return s;

	}
	void expand(int k)//扩容操作
	{
		if (k < 8 * N) return;
		int oldN = N; char* oldM = M;
		init(2 * k);//加倍扩容
		memcpy_s(M, N, oldM, oldN); delete[]oldM;//数据转移
		//四个参数：dest-目标地址，numberOfElenments-目标地址的字符个数（可使用sizeof获取），src-源地址，count-需要拷贝的源字符个数（可使用sizeof获取）。
	}



	
};
//Eratosthenes筛法 快速的计算不大于10^8的所有素数  复杂度O(nlogn)
	void Eratosthenes(int n, char* file)
	{
		Bitmap B(n); B.set(0); B.set(1);//0和1不是素数，先置一
		for (int i = 2; i < n; i++)
			if (!B.test(i))//如果这个数是素数 ，也就是布尔值为false
				for (int j = __min(i, 46340)*__min(i, 46340); j < n; j += i)
					B.set(j);//从i*i开始，每次经过i的迭代，全都标记为合数
		B.dump(file);
	}