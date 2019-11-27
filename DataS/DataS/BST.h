#pragma once
//二叉搜索树
#include"BinTree.h"
template <typename T>class BST :public BinTree<T>
{

protected:
	BinNodePosi(T) _hot;//命中节点的父亲
	BinNodePosi(T) connect34(//按照3+4结构，联结三个节点及四棵子树
		BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
		BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3)
	{
		a->lc = T0; if (T0) T0->parent = a;//a的连接
		a->rc = T1; if (T1) T1->parent = a; updateHeight(a);//更新高度

		c->lc = T2; if (T2) T2->parent = c;//c的连接
		c->rc = T3; if (T3) T3->parent = c; updateHeight(b);//更新高度

		b->lc = a; a->parent = b;
		b->rc = c; c->parent = b; updateHeight(c);//更新高度
	}
	BinNodePosi(T) rotateAt(BinNodePosi(T) v)//对x及其父亲 祖父做统一旋转调整
	{
		BinNodePosi(T) p = v->parent; BinNodePosi(T) g = p->parent;
		if(IsLChild(*p))
			if (IsLChild(*v))//zig-zig
			{
				p->parent = g->parent;//向上连接 上层向下的连接由上层函数完成
				return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);	
			}
			else//zig-zag
			{
				v->parent = g->parent;
				return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
			}
		else//zag
			if (IsRChild(*v))//zag-zag
			{
				p->parent = g->parent;
				return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
			}
			else//zag-zig
			{
				v->parent = g->parent;
				return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
			}

	}
public:
	virtual BinNodePosi(T) & search(const T& e);//查找
	virtual BinNodePosi(T) insert(const T& e);//插入
	virtual bool remove(const T& e);//删除

	
};
template <typename T>
static BinNodePosi(T) &searchIn(BinNodePosi(T) &v,const T& e,BinNodePosi(T) &hot)
{
	if (!v || (e == v->data)) return v;//递归基，如果v是空节点或者e等于v的数据域
	hot = v;//如果没有到达递归基，一般情况下，记录下当前节点
	return searchIn(((e<v->data)?v->lc:v->rc), e, hot);//尾递归，e小于v就往左，大于v往右，类似于向量的二分查找

}

template<typename T>
inline BinNodePosi(T)& BST<T>::search(const T & e)
{
	return searchIn(BinTree<T>::_root, e, _hot = nullptr);
}

template<typename T>
inline BinNodePosi(T) BST<T>::insert(const T & e)
{
	BinNodePosi(T) &x = search(e); if (x) return x;//首先确认目标不存在 （因为我们假定不存在雷同元素）
	//如果不存在
	x = new BinNode<T>(e,_hot);
	BinTree<T>::_size++;
	updateHeightAbove(x);//更新高度
	return x;

}
template <typename T>
static BinNodePosi(T) removeAT(BinNodePosi(T) &x, BinNodePosi(T) &hot)//每个节点要连接他的后代和父亲，记住这一点
{
	BinNodePosi(T) w = x;
	BinNodePosi(T) succ = NULL;//被删除节点的接替者
	if (!(x->lc)) succ = x = x->rc;//如果左子树不存在替换为右子树
	else if (!(x->rc)) succ = x = x->lc;//对称
	else//左右子树都存在的话
	{
		w = w->succ();//找到succ的直接后继（在中序遍历序列下的后继）
		swap(x->data, w->data);//交换数据
		BinNodePosi(T) u = w->parent;
		(u == x ?  u->rc : u->lc) = succ = w->rc;//如果是左右子树只有一棵的那种三个节点的树，在中序遍历中就是下一个就是右边
		//上面一行就是连接三个节点 succ替代被删除的节点（在succ中肯定是右子树），然后succ节点连接被删除节点的父亲。

	}
	hot = w->parent;//hot是被删除者的父亲
	succ->parent = hot;//接替者父亲是hot
	release(w->data);
	release(w);
	return succ;
}

template<typename T>
inline bool BST<T>::remove(const T & e)
{

	BinNodePosi(T) x = search(e);
	if(!x) return false;//如果没有这个数据了 删不掉
	removeAt(x, _hot);
	BinTree<T>::_size--;
	updateHeightAbove(_hot);//更新高度 从被删节点的父亲更新
	return true;
}
