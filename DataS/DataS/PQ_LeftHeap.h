#pragma once
#include"PQ.h"
#include"BinTree.h"
template<typename T>
class PQ_LeftHeap : public PQ<T>, public BinTree<T>//基于二叉树，以左式堆形式实现的PQ
{


public:
	PQ_LeftHeap(){}
	PQ_LeftHeap(T* E,int n)//应该可以改进 这里使用Floyd算法 来自下而上的下滤建堆
	{
		BinNodePosi(T) r = new BinNode<T>(E[0]);
		for (int i = 1; i < n; i++)
		{

			r->lc = new BinNode<T>(E[i]);
			r->lc->parent = r;
			r = r->lc;
		}
		//开始下滤 这时候r应该是最下面一个叶子节点
		while (!r)
		{
			if (r->data < r->lc->data)
			{
				swap(r, r->lc);
			}
			r = r->parent;

		}
	}

	void insert(T);//利用合并来插入
	T getMax();
	T delMax();
};


//左式堆合并
template<typename T>
static BinNodePosi(T) merge(BinNodePosi(T) a, BinNodePosi(T) b)
{
	if (!a) return b;//递归基
	if (!b) return a;
	if (a->data < b->data) swap(a, b);//假定比较器已重载 确保a比b大
	a->rc = merge(a->rc, b);//将a的右子堆，与b合并
	a->rc->parent = a;//更新父子关系
	if (!a->lc || a->lc->npl < a->rc->npl)//因为要确保是左式堆 如果左孩子npl值比右边的小
		swap(a->lc, a->rc);//交换左右子堆
	a->npl = a->rc ? a->rc->npl + 1 : 1;
	return a;//返回合并后的堆顶

}

template<typename T>
inline void PQ_LeftHeap<T>::insert(T e)
{
	BinNodePosi(T) v = new BinNode<T>(e);
	_root = merge(_root, v);//调用合并接口
	_root->parent = NULL;
	_size++;
}

template<typename T>
inline T PQ_LeftHeap<T>::getMax()
{
	return _root->data;
}

template<typename T>
inline T PQ_LeftHeap<T>::delMax()//利用合并的删除
{
	BinNodePosi(T) lHeap = _root->lc;//左右子堆
	BinNodePosi(T) rHeap = _root->rc;

	T e = _root->data;//备份数据
	delete _root; _size--;//删除根节点

	_root = merge(lHeap, rHeap);//合并左右子堆
	if (!_root) _root->parent = NULL;
	return e;//返回原来根节点里存放的数据
	
}
