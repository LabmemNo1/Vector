#pragma once
#include"BST.h"
#define Balanced(x) (stature((x).lc)==stature((x).rc))//����ƽ�����������ҽڵ�߶����
#define BalFac(x) (stature((x).lc)-stature((x).rc))//ƽ������
#define AvlBalanced(x) ((-2<(BalFac(x)))&&((BalFac(x)<2)))//AVLƽ������ ƽ�����Ӿ���ֵ������1

#define tallerChild(x) ( \
   stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : ( /*���*/ \
   stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : ( /*�Ҹ�*/ \
   IsLChild( * (x) ) ? (x)->lc : (x)->rc /*�ȸߣ��븸��xͬ���ߣ�zIg-zIg��zAg-zAg������*/ \
   ) \
   ) \
)
template <typename T>class AVL :public BST<T>
{
public:
	BinNodePosi(T) insert(const T& e)//���루��д��
	{
		BinNodePosi(T) &x = search(e); if (x) return x;//ȷ��������x
		x = new BinNode<T>(e, BST<T>::_hot); BinNodePosi(T) xx = x; BinTree<T>::_size++;

		for (BinNodePosi(T) g = x->parent; g; g = g->parent)//һ��forѭ��ȥ��x��һ��ʧ������Ƚ��
		{
			if (!AvlBalanced(*g))
			{
				FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));//���½���ԭ��
				break;
			}


			else
				updateHeight(g);//ֻ��Ҫ���¸߶�
		}
		return xx;
	}
	bool remove(const T& e)//ɾ�� ����д��
	{
		BinNodePosi(T) &x = search(e); if (!x) return false;
		removeAT(x, _hot); _size--;
		for(BinNodePosi(T) g=_hot;g;g=g->parent)
			if (!AvlBalanced(*g))//�Ͳ���һ����һ������ʧ��Ľڵ㣬�Ͳ���3+4�㷨
			{
				g=FromParentTo(*g)=rotateAt(tallerChild(tallerChild(g)));//�м�ĺ�ָ�������g�����ĸ�����ָ��ģ���������ָ��g
				updataHeight(g);//������Ҫ logn�ε���
			}
		return true;
	}
};

