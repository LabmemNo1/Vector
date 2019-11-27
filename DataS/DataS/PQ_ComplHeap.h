#pragma once
//完全二叉堆模版类
#pragma once
//简化二叉堆算法的描述及实现定义的宏
#define  InHeap(n, i)      ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) ) //判断PQ[i]是否合法
#define  Parent(i)         ( ( i - 1 ) >> 1 ) //PQ[i]的父节点（floor((i-1)/2)，i无论正负）
#define  LastInternal(n)   Parent( n - 1 ) //最后一个内部节点（即末节点的父亲）
#define  LChild(i)         ( 1 + ( ( i ) << 1 ) ) //PQ[i]的左孩子
#define  RChild(i)         ( ( 1 + ( i ) ) << 1 ) //PQ[i]的右孩子
#define  ParentValid(i)    ( 0 < i ) //判断PQ[i]是否有父亲
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //判断PQ[i]是否有一个（左）孩子
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //判断PQ[i]是否有两个孩子
#define  Bigger(PQ, i, j)  ( lt( PQ[i], PQ[j] ) ? j : i ) //取大者（等时前者优先）
#define  ProperParent(PQ, n, i) /*父子（至多）三者中的大者*/ \
            ( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
            ( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
            ) \
            ) //相等时父节点优先，如此可避免不必要的交换


//借助向量的结构和优先级队列的接口
#include"Myvector.h"
#include"PQ.h"
template <typename T> class PQ_ComplHeap : public PQ<T>,public Vector<T>
	{
protected://内部接口
	Rank percolateDown(Rank n, Rank i);//下滤
	Rank percolateUp(Rank i);//上滤
	void heapify(Rank n);//Floyd建堆算法
public://对外接口
	PQ_ComplHeap(){}//默认构造
	PQ_ComplHeap(T* A.Rank n) {Vector<T>::copyFrom(A, 0, n); heapify(n); }
	void insert(T e) { Vector<T>::inset(e); percolateUp(_size - 1); };//插入到末尾，然后执行上滤
	T getMax(){return _elem[0]};//大顶堆 返回首元素，也就是优先级最高的元素即可
	T delMax();




	};

	template<typename T>
	inline Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i)
	{
		Rank j;
		while (i != (j = ProperParent(_elem, n, i)))//只要i不是他的两个孩子中的最大者
		{
			swap(_elem[i], _elem[j]);
			i = j;
		}
	}

	template<typename T>
	inline Rank PQ_ComplHeap<T>::percolateUp(Rank i)
	{
		while (ParentValid(i))//只要i还有父亲就循环，否则i就是堆顶，退出循环
		{
			Rank j = Parent(i);
			if (_elem[j] > _elem[i]) break;//如果父亲优先级比i大了  就跳出循环
			swap(_elem[i], _elem[j]); i = j;//否则交换数值 更新秩 
		}
		return i;
	}

	

	template<typename T>
	inline T PQ_ComplHeap<T>::delMax()
	{
		T maxElem = _elem[0];//备份要删除的堆顶
		_elem[0] = _elem[--_size];//用末词条代替
		percolateDown(_size, 0);//对新堆顶实施下滤
		return maxElem;
		
	}
template<typename T>
	inline void PQ_ComplHeap<T>::heapify(Rank n)//自下而上的下滤建堆
	{
		for (int i = LastInternal(n); InHeap(n, i); i--)
		{
			percolateDown(n, i);//下滤各内部节点
			//效率高的原因是，下滤建造堆的话，高度越高，花费越少，而在完全二叉树
			//中，高度高的远远多于高度低的的节点
		}
	}
template<typename T>
	inline void Vector<T>::heapSort(Rank lo, Rank hi)
	{
		PQ_ComplHeap<T> H(_elem + lo, hi - lo);//以待排序区间建成一个完全二叉堆
		while (!H.empty())//直到待排序的二叉堆变空
		{
			_elem[--hi] = H.delMax();//反复的将堆顶元素与末元素兑换后下滤
		}
	}