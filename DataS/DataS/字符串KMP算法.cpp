#include<string>
//next�����㷨

int* buildNext(char* P)//����ģʽ������
{
	size_t m = strlen(P); int j = 0;
	int *N = new int[m];//next��Ĵ���
	int t = N[0] = -1;
	while (j < m - 1)//��ģʽ����ÿһ���ַ�
	{
		if (0 < j || P[j] == P[t])
		{
			j++; t++;

			//����δ�Ľ��棬���������p[next[j]]��ԭ����P[j]���ʱ��Ӧ�����
			//N[j] = t;//���p[j]==p[t],��next[j+1]=next[j]+1
			//����Ϊ�Ľ���
			N[j] = (P[j] != P[t] ? t : N[t]);//Ӧ��P[j] == P[t]�������������ȣ�������t�������ȣ��ͻ���P[t]��N[t]
		}
		else
			t = N[t];//���p[j]!=p[t],��ônext[j+1]=next[j]+1=next[next[j]]+1���������Դ����ƣ�ֱ��t=N[0]
		//��˵�����ǲ��ϵ�ȡ֮ǰ��Next�ȥѰ�Һ�p[j]��ȵ�һ�Ȼ��t+1������p[j]��Ӧ��next��
	}
	return N;
}
//kmp���㷨
int KMPmatch(char* P, char* T)
{
	int *next = buildNext(P);
	size_t n = strlen(T), i = 0;
	size_t m = strlen(P), j = 0;
	while (j < m&&i < n)
	{
		if (0 > j || T[i] == P[j])//���ж�j��0�Ĺ�ϵ
		{
			i++; j++;
		}
		else
			j = next[j];
	}
	delete[]next;
	return i - j;//�������㷨һ���������㷨��������ı�����λ��
}