#pragma once
#include"BST.h"
#define IsBlack(p) (!(p)||(RB_BLACK==(p)->color))  //外部节点也视作是黑节点
#define IsRed(p) (!IsBlck(p)) //非黑即红
#define BlackHeightUpdated(x) (stature((x).lc)==stature((x).rc))&&((x).height==(IsRed(&x)?stature((x).lc):stature((x).lc)+1)) //红黑树高度更新条件
template <typename T> class RedBlack : public BST<T>
{
protected:
	void solveDoubleRed(BinNodePosi(T) x);//双红修正
	void solveDoubleBlack(BinNodePosi(T) x);//双黑修正
	int updateHeight(BinNodePosi(T) x);//更新节点x的高度 注意 红黑树的高度只计算黑节点的高度
public:
	BinNodePosi(T) insert(const T&e);//插入 （重写）
	bool remove(const T&e);//删除 （重写）
	//BST::search()等其它接口可以直接沿用
};









template<typename T>
inline void RedBlack<T>::solveDoubleRed(BinNodePosi(T) x)
{
	if(IsRoot(x*))//如果一定递归到树根 则将其转黑 整树黑高度加一
	{
		_root->color = RB_BLCAK; _root->height++; return;
	}
	BinNodePosi(T) p = x->parent; if (IsBlack(p)) return;//如果p为黑 可以终止 否则
	BinNodePosi(T) g = p->parent;//p为红 那么x祖父就存在，而且肯定是黑色的
	BinNodePosi(T) u = uncle(x);//根据x叔父的颜色 进行不同的调整
	//有两种方式来对黑色叔父节点调整 一种呢判断，染色，第二种旋转，这是根据红黑树与四阶b树的关联性来做的
	//这里只写旋转的方式 因为没有两次zig-zig和zig-zag的判断（同侧异侧判断）
	if (IsBlack(u))
	{//3+4重构
		BinNodePosi(T) gg = g->parent;
		BinNodePosi(T) r = FromParentTo(*g) = rotate(x);
		r->parent = gg;
	}
	else//如果u是红色 我们进行提升调整为一个b-树后，可以看出，就像b-树发生了上溢
		//最后 如p232 所示 我们只需要将g节点调整为红，p和u节点颜色染为黑色即可
	{
		p->color = RB_BLCAK; p->height++;//染为黑色，黑高度+1
		u->color = RB_BLCAK; u->height++;//染为黑色，黑高度+1
		if (!IsRoot(*g)) g->color = RB_RED;//如果g不是根 染为红色 
		solveDoubleRed(g);//可能会存在上溢的传播 继续调整g
	}

	
}

template<typename T>
inline void RedBlack<T>::solveDoubleBlack(BinNodePosi(T) x)
{
	BinNodePosi(T) p = r ? r->parent : _hot; if (!p) return;//r的父亲
	BinNodePosi(T) s = (r == p->lc) ? p->lc : p->rc;//r的兄弟
	if (IsBlack(s))//兄弟s为黑
	{
		BinNodePosi(T) t = NULL;//s的红孩子，左孩子优先，都是黑的就NULL
		if (IsRed(s->rc)) t = s->rc;
		if (IsRed(s->lc)) t = s->lc;
		if (t)//进入s有红孩子的分支，也就是BB-1
		{
			RBColor oldColor = p->color;//先备份p原来的颜色
			//接下来，旋转 3+4重构
			BinNodePosi(T) b = FromParentTo(*p) = rotateAt(t);
			if (HasLChild(*b)) { b->lc->color = RB_BLCAK; updateHeight(b->lc); }//重构后的根节点的左右孩子染黑
			if (HasRChild(*b)) { b->rc->color = RB_RED; updateHeight(b->rc); }
			b->color = oldColor; updateHeight(b);//b的颜色是原来p的颜色
		}
		else//s没有红孩子的情况下
		   //BB-2R和BB-2B
		{
			s->color = RB_BLCAK; s->height--;//这两种情况最终都要把s变红
			if (IsRed(p))//BB-2R
			{
				p->color = RB_BLCAK;//p变黑，双黑修正完成
			}
			else
			{
				p->height--;
				solveDoubleBlack(p);//递归继续修复，可能会发生向上的传播
			}
		}
	}
	else//BB-3 兄弟s为红
	{
		s->color = RB_BLCAK;
		p->color = RB_RED;
		BinNodePosi(T) t = IsLChild(*s) ? s->lc : s->rc;//取t与其父s同侧
		_hot = p; FromParentTo(*p) = rotateAt(t);
		solveDoubleBlack(r);//继续修复，转入BB-1或者BB-2R
	}

		


}

template<typename T>
inline int RedBlack<T>::updateHeight(BinNodePosi(T) x)
{
	x->height = max(stature(x->lc), stature(x->rc));//孩子一般黑深度相等 因为红黑树定义 除非双黑
	return IsBlack(x) ? x->height++ : x->height;
}

template<typename T>
inline BinNodePosi(T) RedBlack<T>::insert(const T & e)
{
	BinNodePosi(T) &x = search(e); if (e) return false;
	x = new BinNode<T>(e, _hot, NULL, NULL, -1); _size++;//创建红节点x 黑高度-1
	solveDoubleRed(x);
}

template<typename T>
inline bool RedBlack<T>::remove(const T & e)
{
	BinNodePosi(T) &x = search(e); if (!x) return false;//确保目标存在
	BinNodePosi(T) r = removeAt(x, this->_hot); if (!(--_size)) return ture;//实施删除 删除后如果为空树 返回
	//以下：如果删除的是根节点，就将其置黑，并更新黑高度
	if(!_hot)//如果删除的节点没有父亲
	{
		BinTree<T>::_root->color = RB_BLCAK; updateHeight(BinTree<T>::_root); return true;
	}
	if (BlackHeightUpdated(*_hot)) return true;//若所有祖先的黑深度依然平衡 就不用调整
	if(IsRed(r))//否则 如果r（r是被删除节点的接替者）是红的，只需要将其变为黑的 黑深度即可平衡
	{
		r->color = RB_BLCAK; r->height++; return true;
	}
	//以下为双黑修正
	solveDoubleBlack(r); return true;


}
