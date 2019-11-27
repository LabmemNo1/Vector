#pragma once
#include"Stack.h"
#include"Queue.h"
typedef enum{UNDISCOVERED, DISCOVERED, VISITED} VStatus;//顶点状态
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;//边在遍历树种所属的类型


template <typename Tv,typename Te>//顶点类型，边类型
class Graph
{
private:
	void reset()//所有顶点、边的辅助信息复位
	{
		for (int i = 0; i < n; i++)
		{
			status(i) = UNDISCOVERED;
			dTime(i) = fTime(i) = -1;
			parent(i) = -1;
			priority(i) = INT_MAX;
			for (int j = 0; j < n; j++)//所有边
				if (exists(i, j))
					type(i, j) = UNDETERMINED;

		}










	}
	void BFS(int, int&);//（连通域）广度优先搜索算法
	void DFS(int, int&);//(连通域) 深度优先搜索算法
	void BCC(int, int&, Stack<int>&);//(连通域)基于DFS的双连通分量分解算法
	void TSort(int, int&, Stack<Tv>*);//(连通域)基于DFS的拓扑排序算法
	template <typename PU>void PFS(int, PU);//（连通域）优先级搜索框架



public:
	//顶点
	int n;//顶点总数
	virtual int insert(Tv const&) = 0;//纯虚函数  插入顶点 返回编号
	virtual Tv remove(int) = 0;//删除顶点及其关联边，返回该顶点的信息
	virtual Tv& vertex(int) = 0;//顶点v的数据（该顶点的确存在）
	virtual int inDegree(int) = 0;//顶点v的入度
	virtual int outDegree(int) = 0;//顶点v的出度
	virtual int firstNbr(int) = 0;//顶点v的首个邻接结点
	virtual int nextNbr(int, int) = 0;//顶点v的（相对于顶点j的）下一邻接结点
	virtual VStatus& status(int) = 0;//顶点v的状态
	virtual int& dTime(int) = 0;
	virtual int& fTime(int) = 0;
	virtual int& parent(int) = 0;
	virtual int& priority(int) = 0;
	//边
	int e;//边总数
	virtual bool exists(int, int) = 0;//边是否存在
	virtual void insert(Te const&, int, int, int) = 0;//在顶点之前插入权重为w的边e
	virtual Te romove(int, int) = 0;//删除两条顶点之间的边，返回该边的信息
	virtual EType& type(int, int) = 0;//边（v,u）的类型
	virtual Te& edge(int, int) = 0;//边（v，u）的数据
	virtual int& weight(int, int) = 0;//边（v，u）的权重

	//算法
	void bfs(int);//广度优先搜索算法
	void dfs(int);//深度优先搜索算法
	void bcc(int);//基于dfs的双连通分量分解算法
	Stack<Tv>* tSort(int);//基于dfs的拓扑排序算法
	void prim(int);//最小支撑树Prim算法
	void dijkstra(int);//最短路径Dijkstra算法
	template <typename PU> void pfs(int, PU);//优先级搜索框架


	
};

template<typename Tv, typename Te>//类似于树的层次遍历
inline void Graph<Tv, Te>::BFS(int v, int &clock)//对一个顶点进行广度优先遍历 clock计数
{
	Queue<int> Q;
	status(v) = DISCOVERED;
	Q.enqueue(v);
	while (!Q.empty())
	{
		int v = Q.dequeue();
		dTime(v) = ++clock;//计数
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
inline void Graph<Tv, Te>::DFS(int v, int &clock)//深度优先搜索
{
	dTime(v) = ++clock; status(v) = DISCOVERED;
	for (int u = firstNbr(v); u > -1; u = nextNbr(v, u))
	{
		switch(status(u))//视u的状态分别处理
			case UNDISCOVERED://未被发现的状态，往深的地方一直递归下去
				type(v, u) = TREE;
				parent(u) = v;
				DFS(u, clock);//递归
				break;
			case DISCOVERED://如果是已经被发现的状态
				type(v, u) = BACKWARD;//回边 后来发现的边找到了之前已经遍历过的
				break
			default://u已经访问完毕(有向图)，视其程承袭关系分为前后变或跨边
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
	while (s != (v = (++v%n)));//按序号检查 不会超出最大顶点数目 不会等于起点 
}

template<typename Tv, typename Te>
inline void Graph<Tv, Te>::dfs(int s)
{
	reset();
	int clock = 0;
	int v = s;
	do//逐一检查所有顶点
		if (UNDISCOVERED == status(v))
			DFS(v, clock);
	while (s != (v = (++v%n)));
}
