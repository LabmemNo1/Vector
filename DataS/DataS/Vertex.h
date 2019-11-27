#pragma once
#include"Myvector.h"
#include"Graph.h"

template <typename Tv> struct Vertex//顶点对象类
{
	Tv data; int inDegree, outDegree; VStatus status;//数据，入度，出度，状态
	int dTime, fTime;//时间标签
	int parent; int priority;//在遍历树中的父节点、优先级数


	//构造函数
	Vertex(Tv const& d=(Tv) 0):
		data(0),inDegree(0),outDegree(0),status(UNDISCOVERED),
		dTime(-1),fTime(-1),parent(-1),priority(INT_MAX){}//暂不考虑权重溢出
};

template <typename Te> struct Edge//边对象
{
	Te data; int weight; EType type;//数据 权重 类型
	Edge(Te const &d,int w):data(d),weight(w),type(UNDETERMINED){}//构造函数
};

template <typename Tv,typename Te>//顶点类型 边类型
class GraphMatrix :public Graph<Tv, Te>//基于向量，以邻接矩阵形式实现的图
{
private:
	Vector<Vertex<Tv>> V;//顶点集（向量）
	Vector<Vector<Edge<Te>* > > E;//边集（邻接矩阵）
public:
	GraphMatrix() { n = e = 0; }//构造
	~GraphMatrix() 析构
	{
		for (int j = 0; j < n; j++)
			for (int i = 0; i < n; i++)
				delete E[j][k];
	}

	//顶点基本操作
	virtual Tv& vertex(int i) { return V[i].data; }//数据
	virtual int inDegree(int i) { return V[i].inDegree; }//入度
	virtual int outDegree(int i) { return V[i].outDegree; }//出度
	virtual VStatus& status(int i) { return V[i].status; }//状态
	virtual int& dTime(int i) { return V[i].dTime; }//时间标签dTime
	virtual int& fTime(int i) { return V[i].fTime; }//时间标签fTime
	virtual int& parent(int i) { return V[i].parent; }//在遍历树中的父亲
	virtual int& priority(int i) { return V[i].priority; }//优先级数
	virtual int firstNbr(int i) { return nextNbr(i, n); }//首个邻接结点 n 尾哨兵
	virtual int nextNbr(int i, int j)//相对于顶点j的下一个邻接结点
	{
		while ((-1 < j) && (!exists(i, --j)))//逆向线性查找
			return j;
	}
	//顶点的动态操作
	virtual int insert(Tv const& vertex)//插入顶点，返回编号
	{
		for (int j = 0; j < n; j++)
			E[j].insert(nullptr);//对每一行向量，我们插入一个空的（潜在的关联边）
		n++;//顶点加一
		E.insert(Vector<Edge<Te>*>(n, n, NULL));//然后我们还要添加一行向量，这里使用我们的Vector的insert操作和构造函数
		return V.insert(Vertex<Tv>(vertex));//顶点向量增加一个顶点 前面几行都是对对应的边集的操作
	}
	virtual Tv remove(int i)//删除第i个顶点及其关联边
	{
		for(int j=0;j<n;j++)//不能直接移除这一行，因为不知道和谁有没有邻接关系
			if (exists(i, j))//这里针对的是所有关于i的出边，也就是与他邻接顶点的入度
			{
				delete E[i][j];
				V[j].inDegree--;
			}
		E.remove(i); n--;//这时候可以移除这一行了
		for (int j = 0; j < n; j++)
		{
			if (exists(j, i))
			{
				delete E[j].remove(i);
				V[j].outDegree--;
			}
		}
		Tv vBak = vertex(i);//备份
		V.remove[i];//从顶点集合中删除
		return vBak;//返回被删除顶点的信息

	}







	//边的确认操作
	virtual bool exists(int i,int j)
	{
		return (i >= 0) && (i < n) && (j >= 0) && (j < n) && (E[i][j] != NULL);//首先 i j要合法，然后只要判断在表中是不是空的就行了
	}
	virtual Te& edge(int i, int j) { return E[i][j]->data; }//边的数据
	virtual EType& type(int i, int j) { return E[i][j]->type; }
	virtual int& weight(int i, int j) { return E[i][j]->weight; }
	//边的动态操作
	virtual void insert(Te const& edge, int w, int i, int j)//插入权重为w的边e=（i，j）
	{
		if (exists(i, j)) return;
		E[i][j] = new Edge(edge, w);//创建边
		e++;//边数+1
		V[i].outDegree++;//出度加1
		V[j].inDegree++;//入度加一
	}
	virtual Te remove(int i, int j)//删除i与j之间的联边
	{
		Te eBak = edge(i, j);//备份数据
		delete E[i][j];
		E[i][j] = nullptr;
		e--;
		V[i].outDegree--;//出度减一
		V[j].inDegree--;//入度减一
		return eBak;
	}
};