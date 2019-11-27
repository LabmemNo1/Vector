#pragma once
#include"BST.h"
#define Balanced(x) (stature((x).lc)==stature((x).rc))//理想平衡条件，左右节点高度相等
#define BalFac(x) (stature((x).lc)-stature((x).rc))//平衡因子
#define AvlBalanced(x) ((-2<(BalFac(x)))&&((BalFac(x)<2)))//AVL平衡条件 平衡因子绝对值不大于1

#define tallerChild(x) ( \
   stature( (x)->lc ) > stature( (x)->rc ) ? (x)->lc : ( /*左高*/ \
   stature( (x)->lc ) < stature( (x)->rc ) ? (x)->rc : ( /*右高*/ \
   IsLChild( * (x) ) ? (x)->lc : (x)->rc /*等高：与父亲x同侧者（zIg-zIg或zAg-zAg）优先*/ \
   ) \
   ) \
)
template <typename T>class AVL :public BST<T>
{
public:
	BinNodePosi(T) insert(const T& e)//插入（重写）
	{
		BinNodePosi(T) &x = search(e); if (x) return x;//确保不存在x
		x = new BinNode<T>(e, BST<T>::_hot); BinNodePosi(T) xx = x; BinTree<T>::_size++;

		for (BinNodePosi(T) g = x->parent; g; g = g->parent)//一个for循环去找x第一个失衡的祖先借点
		{
			if (!AvlBalanced(*g))
			{
				FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));//重新接入原树
				break;
			}


			else
				updateHeight(g);//只需要更新高度
		}
		return xx;
	}
	bool remove(const T& e)//删除 （重写）
	{
		BinNodePosi(T) &x = search(e); if (!x) return false;
		removeAT(x, _hot); _size--;
		for(BinNodePosi(T) g=_hot;g;g=g->parent)
			if (!AvlBalanced(*g))//和插入一样，一但发现失衡的节点，就采用3+4算法
			{
				g=FromParentTo(*g)=rotateAt(tallerChild(tallerChild(g)));//中间的宏指向的是与g相连的父亲所指向的，让他还是指向g
				updataHeight(g);//可能需要 logn次调整
			}
		return true;
	}
};

