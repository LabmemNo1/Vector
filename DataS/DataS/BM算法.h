#pragma once
#include<string>
//����BC��
int* buildBC(char* P)
{
	int *bc = new int[256];//Ҫ����ĸ��ȳ�������256���ȡ��
	for (size_t j = 0; j < 256; j++) bc[j] = -1;//���������ַ���û����P�г��ֹ�
	for (size_t m = strlen(P), j = 0; j < m; j++)
		bc[P[j]] = j;//�����㷨����ʹ����ͬ���ڲ�ͬλ�ó��֣�ֻ��¼���һ��
	return bc;
}



//����SS���GS��
//SS�����ƥ���׺�ĳ��ȣ�
//GS���ú�׺�� ��i�ƶ��ľ���
int* buildSS(char* P)
{
	int m = strlen(P); int* ss = new int[m];
	ss[m - 1] = m;//�����һ���ַ����ԣ���֮ƥ������׺��������P��
//���£��ӵ����ڶ����ַ���ʼ��������ɨ��P
	for (int lo = m - 1, hi = m - 1, j = lo - 1; j >= 0; j--)
	{
		if ((j > lo) && (ss[m - hi + j - 1] <= j - lo))//���һ
			ss[j] = ss[m - hi + j - 1];//ֱ����ֱ�Ӽ������ss[]
		else//���2
		{
			hi = j; lo = __min(lo, hi);
			while ((0 <= lo) && (P[lo] == P[m - hi + lo - 1]))
				lo--;//����ȶ�λ��(lo,hi]ǰ�ε��ַ�
			ss[j] = hi - lo;
		}
	}
	return ss;

}
int* buildGS(char* P)
{
	int* ss = buildSS(P);
	size_t m = strlen(P); int* gs = new int[m];
	for (size_t j = 0; j < m; j++) gs[j] = m;//��ʼ��
	for (size_t i = 0, j = m - 1; j >= 0; j--)//������һɨ����ַ�P[j]
		if (j + 1 == ss[j])//������˼�ǵ�һ����� p[0,j]==P[m-j+1,m)
			while (i < m - j - 1)//����P[m-j-1]����ÿ���ַ�P[i]����
				gs[i++] = m - j - 1;//P[m-j-1]����һ��ѡ��
	for (size_t j = 0; j < m - 1; j++)//�����㷨
		gs[m - ss[j] - 1] = m - j - 1;//m-j-1��Ȼ��gs[m-ss[j]-1]ֵ��һ��ѡ��
}















int BMmatch(char* P, char* T)
{
	int *bc = buildBC(P); int *gs = buildGS(P);//����BC�����ַ��� GS���ú�׺��
	size_t i = 0;//ģʽ��������ı����У��ı�����λ�ã���ʼʱƽ�룩
	while (strlen(T) >= strlen(P) + i)//��ѭ����i�ǲ��ϱ���
		//��˼����ģʽ�������Ļ����ı����ڲ�������
	{
		size_t j = strlen(P) - 1;//��P[j]��ʼ�ȶ�
		while (P[j] == T[i + j])
			if (0 > --j) break;//if�����������϶�ִ�У�����breakҪ��������Ż�ִ��
		//�������ƥ��ɹ���
		if (0 > j)
			break;//ƥ��ɹ�
		else//����else��������P[j]!=T[i+j]���whileѭ��
			//����������ʱ�����һ���ǰ׺û�бȶ�ʱִ��
			i += __max(gs[j], j - bc[T[i + j]]);//λ���������������Ǹ�λ������
	}
	delete []bc;
	delete []gs;
	return i;
}