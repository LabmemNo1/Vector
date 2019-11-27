#pragma once
#include<string>
class Bitmap
{
private:
	char* M; int N;//����ͼ��ŵĿռ�M[]������ΪN*sizeof(char)*8����
protected:
	void init(int n) { M = new char[N = (n + 7) / 8]; memset(M, 0, N); }//λͼ��ʼ����Ϊ�˱�֤�ݵ���ȫ����λ��������Ҫ+7�ٳ���8(һ���ֽڰ�λ)��Ȼ���ÿһλ����
public:
	Bitmap(int n = 8) { init(n); }//���캯�� Ĭ��ֵ���8�� �������
	Bitmap(char* file,int n=8)//��ָ���������Ĭ�ϵĹ�ģ ��ָ�����ļ��ж�ȡ����ͼ
	{
		init(n);
		FILE* fp = fopen(file, "r");//���ļ�file ��ֻ����ʽ��
		fread(M, sizeof(char), N, fp);//�����M��鳤����8��N��
		fclose(fp);
	}
	~Bitmap() { delete[]M; M = NULL; }

	//�����Ƕ�λͼ�����ؼ��Ĳ���
	//k>>3���Եõ��ڿռ�M��k����Ӧ�ĵ���
	//k&0x07 ����ȷ��k��һ����λ�������ֽ��е�λ��
	//0x80>>(k&0x07)�õ��ñ���λ�ڴ��ֽ��ж�Ӧ����ֵ���루ԭ��̫����
	//��Ӧ���ֽ����������߼������㣬�ɽ�����λ����Ϊ1�����߼���������Բ���״̬��������ķ�����λ�����㣬������λ����Ϊ0
	
	void set(int k)//����kλ��Ϊtrue(������i���뵱ǰ����)
	{
		expand(k);
		M[k >> 3] |= (0x80 >> (k & 0x07));
	}
	void clear(int k)//����kλ��Ϊfalse(�ӵ�ǰ������ɾ������i)
	{
		expand(k);
		M[k >> 3] &= ~(0x80 >> (k & 0x07));
	}
	bool test(int k)//���Ե�kλ�ǲ���true
	{
		expand(k);
		return M[k >> 3] &&(0x80 >> (k & 0x07));
	}


	void dump(char* file)//��λͼ���嵼����ָ�����ļ����Ա�Դ˺����λͼ������ʼ��
	{
		FILE* fp = fopen(file, "w");//Ϊ�����������һ�����ļ�
		fwrite(M, sizeof(char), N, fp);
		fclose(fp);
	}
	char* bits2string(int n)//��ǰnλת��Ϊ�ַ���
	{
		expand(n - 1);//��ʱ���ܱ����ʵ����λΪbitmap[n-1]
		char* s = new char[n + 1]; s[n] = '\0';
		for (int i = 0; i < n; i++) s[i] = test(i) ? '1' : '0';
		return s;

	}
	void expand(int k)//���ݲ���
	{
		if (k < 8 * N) return;
		int oldN = N; char* oldM = M;
		init(2 * k);//�ӱ�����
		memcpy_s(M, N, oldM, oldN); delete[]oldM;//����ת��
		//�ĸ�������dest-Ŀ���ַ��numberOfElenments-Ŀ���ַ���ַ���������ʹ��sizeof��ȡ����src-Դ��ַ��count-��Ҫ������Դ�ַ���������ʹ��sizeof��ȡ����
	}



	
};
//Eratosthenesɸ�� ���ٵļ��㲻����10^8����������  ���Ӷ�O(nlogn)
	void Eratosthenes(int n, char* file)
	{
		Bitmap B(n); B.set(0); B.set(1);//0��1��������������һ
		for (int i = 2; i < n; i++)
			if (!B.test(i))//�������������� ��Ҳ���ǲ���ֵΪfalse
				for (int j = __min(i, 46340)*__min(i, 46340); j < n; j += i)
					B.set(j);//��i*i��ʼ��ÿ�ξ���i�ĵ�����ȫ�����Ϊ����
		B.dump(file);
	}