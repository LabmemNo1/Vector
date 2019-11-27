#pragma once
#include"PQ.h"
#include"BinTree.h"
template<typename T>
class PQ_LeftHeap : public PQ<T>, public BinTree<T>//���ڶ�����������ʽ����ʽʵ�ֵ�PQ
{


public:
	PQ_LeftHeap(){}
	PQ_LeftHeap(T* E,int n)//Ӧ�ÿ��ԸĽ� ����ʹ��Floyd�㷨 �����¶��ϵ����˽���
	{
		BinNodePosi(T) r = new BinNode<T>(E[0]);
		for (int i = 1; i < n; i++)
		{

			r->lc = new BinNode<T>(E[i]);
			r->lc->parent = r;
			r = r->lc;
		}
		//��ʼ���� ��ʱ��rӦ����������һ��Ҷ�ӽڵ�
		while (!r)
		{
			if (r->data < r->lc->data)
			{
				swap(r, r->lc);
			}
			r = r->parent;

		}
	}

	void insert(T);//���úϲ�������
	T getMax();
	T delMax();
};


//��ʽ�Ѻϲ�
template<typename T>
static BinNodePosi(T) merge(BinNodePosi(T) a, BinNodePosi(T) b)
{
	if (!a) return b;//�ݹ��
	if (!b) return a;
	if (a->data < b->data) swap(a, b);//�ٶ��Ƚ��������� ȷ��a��b��
	a->rc = merge(a->rc, b);//��a�����Ӷѣ���b�ϲ�
	a->rc->parent = a;//���¸��ӹ�ϵ
	if (!a->lc || a->lc->npl < a->rc->npl)//��ΪҪȷ������ʽ�� �������nplֵ���ұߵ�С
		swap(a->lc, a->rc);//���������Ӷ�
	a->npl = a->rc ? a->rc->npl + 1 : 1;
	return a;//���غϲ���ĶѶ�

}

template<typename T>
inline void PQ_LeftHeap<T>::insert(T e)
{
	BinNodePosi(T) v = new BinNode<T>(e);
	_root = merge(_root, v);//���úϲ��ӿ�
	_root->parent = NULL;
	_size++;
}

template<typename T>
inline T PQ_LeftHeap<T>::getMax()
{
	return _root->data;
}

template<typename T>
inline T PQ_LeftHeap<T>::delMax()//���úϲ���ɾ��
{
	BinNodePosi(T) lHeap = _root->lc;//�����Ӷ�
	BinNodePosi(T) rHeap = _root->rc;

	T e = _root->data;//��������
	delete _root; _size--;//ɾ�����ڵ�

	_root = merge(lHeap, rHeap);//�ϲ������Ӷ�
	if (!_root) _root->parent = NULL;
	return e;//����ԭ�����ڵ����ŵ�����
	
}
