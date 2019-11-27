#pragma once
#include"Stack.h"
#include"Queue.h"
typedef enum{UNDISCOVERED, DISCOVERED, VISITED} VStatus;//����״̬
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;//���ڱ�����������������


template <typename Tv,typename Te>//�������ͣ�������
class Graph
{
private:
	void reset()//���ж��㡢�ߵĸ�����Ϣ��λ
	{
		for (int i = 0; i < n; i++)
		{
			status(i) = UNDISCOVERED;
			dTime(i) = fTime(i) = -1;
			parent(i) = -1;
			priority(i) = INT_MAX;
			for (int j = 0; j < n; j++)//���б�
				if (exists(i, j))
					type(i, j) = UNDETERMINED;

		}










	}
	void BFS(int, int&);//����ͨ�򣩹�����������㷨
	void DFS(int, int&);//(��ͨ��) ������������㷨
	void BCC(int, int&, Stack<int>&);//(��ͨ��)����DFS��˫��ͨ�����ֽ��㷨
	void TSort(int, int&, Stack<Tv>*);//(��ͨ��)����DFS�����������㷨
	template <typename PU>void PFS(int, PU);//����ͨ�����ȼ��������



public:
	//����
	int n;//��������
	virtual int insert(Tv const&) = 0;//���麯��  ���붥�� ���ر��
	virtual Tv remove(int) = 0;//ɾ�����㼰������ߣ����ظö������Ϣ
	virtual Tv& vertex(int) = 0;//����v�����ݣ��ö����ȷ���ڣ�
	virtual int inDegree(int) = 0;//����v�����
	virtual int outDegree(int) = 0;//����v�ĳ���
	virtual int firstNbr(int) = 0;//����v���׸��ڽӽ��
	virtual int nextNbr(int, int) = 0;//����v�ģ�����ڶ���j�ģ���һ�ڽӽ��
	virtual VStatus& status(int) = 0;//����v��״̬
	virtual int& dTime(int) = 0;
	virtual int& fTime(int) = 0;
	virtual int& parent(int) = 0;
	virtual int& priority(int) = 0;
	//��
	int e;//������
	virtual bool exists(int, int) = 0;//���Ƿ����
	virtual void insert(Te const&, int, int, int) = 0;//�ڶ���֮ǰ����Ȩ��Ϊw�ı�e
	virtual Te romove(int, int) = 0;//ɾ����������֮��ıߣ����ظñߵ���Ϣ
	virtual EType& type(int, int) = 0;//�ߣ�v,u��������
	virtual Te& edge(int, int) = 0;//�ߣ�v��u��������
	virtual int& weight(int, int) = 0;//�ߣ�v��u����Ȩ��

	//�㷨
	void bfs(int);//������������㷨
	void dfs(int);//������������㷨
	void bcc(int);//����dfs��˫��ͨ�����ֽ��㷨
	Stack<Tv>* tSort(int);//����dfs�����������㷨
	void prim(int);//��С֧����Prim�㷨
	void dijkstra(int);//���·��Dijkstra�㷨
	template <typename PU> void pfs(int, PU);//���ȼ��������


	
};

template<typename Tv, typename Te>//���������Ĳ�α���
inline void Graph<Tv, Te>::BFS(int v, int &clock)//��һ��������й�����ȱ��� clock����
{
	Queue<int> Q;
	status(v) = DISCOVERED;
	Q.enqueue(v);
	while (!Q.empty())
	{
		int v = Q.dequeue();
		dTime(v) = ++clock;//����
		for (int u = firstNbr(v); u > -1; u = nextNbr(v, u))
			if(status(u)==UNDISCOVERED)
			{
				status(u) = DISCOVERED;
				Q.enqueue(u);
				type(u, v) = TREE;
				parent(u) = v;
			}
			else
				type(u, v) = CROSS;


			status(v) = VISITED;
	}

}

template<typename Tv, typename Te>
inline void Graph<Tv, Te>::DFS(int v, int &clock)//�����������
{
	dTime(v) = ++clock; status(v) = DISCOVERED;
	for (int u = firstNbr(v); u > -1; u = nextNbr(v, u))
	{
		switch(status(u))//��u��״̬�ֱ���
			case UNDISCOVERED://δ�����ֵ�״̬������ĵط�һֱ�ݹ���ȥ
				type(v, u) = TREE;
				parent(u) = v;
				DFS(u, clock);//�ݹ�
				break;
			case DISCOVERED://������Ѿ������ֵ�״̬
				type(v, u) = BACKWARD;//�ر� �������ֵı��ҵ���֮ǰ�Ѿ���������
				break
			default://u�Ѿ��������(����ͼ)������̳�Ϯ��ϵ��Ϊǰ������
				type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS; break;
	}
	status(v) = VISITED;
	fTime(v) = ++clock;
}

template<typename Tv, typename Te>
inline void Graph<Tv, Te>::bfs(int s)
{
	reset(); int clock = 0; int v = s;
	do
		if (UNDISCOVERED == status(v))
			BFS(v, clock);
	while (s != (v = (++v%n)));//����ż�� ���ᳬ����󶥵���Ŀ ���������� 
}

template<typename Tv, typename Te>
inline void Graph<Tv, Te>::dfs(int s)
{
	reset();
	int clock = 0;
	int v = s;
	do//��һ������ж���
		if (UNDISCOVERED == status(v))
			DFS(v, clock);
	while (s != (v = (++v%n)));
}
