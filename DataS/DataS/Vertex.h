#pragma once
#include"Myvector.h"
#include"Graph.h"

template <typename Tv> struct Vertex//���������
{
	Tv data; int inDegree, outDegree; VStatus status;//���ݣ���ȣ����ȣ�״̬
	int dTime, fTime;//ʱ���ǩ
	int parent; int priority;//�ڱ������еĸ��ڵ㡢���ȼ���


	//���캯��
	Vertex(Tv const& d=(Tv) 0):
		data(0),inDegree(0),outDegree(0),status(UNDISCOVERED),
		dTime(-1),fTime(-1),parent(-1),priority(INT_MAX){}//�ݲ�����Ȩ�����
};

template <typename Te> struct Edge//�߶���
{
	Te data; int weight; EType type;//���� Ȩ�� ����
	Edge(Te const &d,int w):data(d),weight(w),type(UNDETERMINED){}//���캯��
};

template <typename Tv,typename Te>//�������� ������
class GraphMatrix :public Graph<Tv, Te>//�������������ڽӾ�����ʽʵ�ֵ�ͼ
{
private:
	Vector<Vertex<Tv>> V;//���㼯��������
	Vector<Vector<Edge<Te>* > > E;//�߼����ڽӾ���
public:
	GraphMatrix() { n = e = 0; }//����
	~GraphMatrix() ����
	{
		for (int j = 0; j < n; j++)
			for (int i = 0; i < n; i++)
				delete E[j][k];
	}

	//�����������
	virtual Tv& vertex(int i) { return V[i].data; }//����
	virtual int inDegree(int i) { return V[i].inDegree; }//���
	virtual int outDegree(int i) { return V[i].outDegree; }//����
	virtual VStatus& status(int i) { return V[i].status; }//״̬
	virtual int& dTime(int i) { return V[i].dTime; }//ʱ���ǩdTime
	virtual int& fTime(int i) { return V[i].fTime; }//ʱ���ǩfTime
	virtual int& parent(int i) { return V[i].parent; }//�ڱ������еĸ���
	virtual int& priority(int i) { return V[i].priority; }//���ȼ���
	virtual int firstNbr(int i) { return nextNbr(i, n); }//�׸��ڽӽ�� n β�ڱ�
	virtual int nextNbr(int i, int j)//����ڶ���j����һ���ڽӽ��
	{
		while ((-1 < j) && (!exists(i, --j)))//�������Բ���
			return j;
	}
	//����Ķ�̬����
	virtual int insert(Tv const& vertex)//���붥�㣬���ر��
	{
		for (int j = 0; j < n; j++)
			E[j].insert(nullptr);//��ÿһ�����������ǲ���һ���յģ�Ǳ�ڵĹ����ߣ�
		n++;//�����һ
		E.insert(Vector<Edge<Te>*>(n, n, NULL));//Ȼ�����ǻ�Ҫ���һ������������ʹ�����ǵ�Vector��insert�����͹��캯��
		return V.insert(Vertex<Tv>(vertex));//������������һ������ ǰ�漸�ж��ǶԶ�Ӧ�ı߼��Ĳ���
	}
	virtual Tv remove(int i)//ɾ����i�����㼰�������
	{
		for(int j=0;j<n;j++)//����ֱ���Ƴ���һ�У���Ϊ��֪����˭��û���ڽӹ�ϵ
			if (exists(i, j))//������Ե������й���i�ĳ��ߣ�Ҳ���������ڽӶ�������
			{
				delete E[i][j];
				V[j].inDegree--;
			}
		E.remove(i); n--;//��ʱ������Ƴ���һ����
		for (int j = 0; j < n; j++)
		{
			if (exists(j, i))
			{
				delete E[j].remove(i);
				V[j].outDegree--;
			}
		}
		Tv vBak = vertex(i);//����
		V.remove[i];//�Ӷ��㼯����ɾ��
		return vBak;//���ر�ɾ���������Ϣ

	}







	//�ߵ�ȷ�ϲ���
	virtual bool exists(int i,int j)
	{
		return (i >= 0) && (i < n) && (j >= 0) && (j < n) && (E[i][j] != NULL);//���� i jҪ�Ϸ���Ȼ��ֻҪ�ж��ڱ����ǲ��ǿյľ�����
	}
	virtual Te& edge(int i, int j) { return E[i][j]->data; }//�ߵ�����
	virtual EType& type(int i, int j) { return E[i][j]->type; }
	virtual int& weight(int i, int j) { return E[i][j]->weight; }
	//�ߵĶ�̬����
	virtual void insert(Te const& edge, int w, int i, int j)//����Ȩ��Ϊw�ı�e=��i��j��
	{
		if (exists(i, j)) return;
		E[i][j] = new Edge(edge, w);//������
		e++;//����+1
		V[i].outDegree++;//���ȼ�1
		V[j].inDegree++;//��ȼ�һ
	}
	virtual Te remove(int i, int j)//ɾ��i��j֮�������
	{
		Te eBak = edge(i, j);//��������
		delete E[i][j];
		E[i][j] = nullptr;
		e--;
		V[i].outDegree--;//���ȼ�һ
		V[j].inDegree--;//��ȼ�һ
		return eBak;
	}
};