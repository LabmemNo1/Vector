#pragma once
#include"BST.h"
template <typename T> class Splay :public BST<T>
{
protected:

	//两个节点作为孩子和父亲关联的接口
	template <typename NodePosi> inline
		void attachAsLChild(NodePosi p, NodePosi lc) { p->lc = lc; if (lc) lc->parent = p; }
	template <typename NodePosi> inline
		void attachAsRChild(NodePosi p, NodePosi rc) { p->rc = rc; if (rc) rc->parent = p; }



	BinNodePosi(T) splay(BinNodePosi(T) v)//将节点v伸展至根
	{
		if (!v) return NULL;
		BinNodePosi(T) p; BinNodePosi(T) g;//父亲节点和祖父节点
		while ((p = v->parent) && (g = p->parent))//v还有祖父的话，循环一直持续
		{
			BinNodePosi(T) gg = g->parent;//因为每个循环过后v都会以曾祖父作为新的父亲
			if(IsLChild(*v))//zig
				if(IsLChild(*p))//zig-zig还是画图理解吧，比较容易看得出来
				{
					attachAsRChild(v,p);
					attachAsLChild(p, v->rc);
					attachAsRChild(p, g);
					attachAsLChild(g, p->rc);

				}
				else//zig-zag
				{
					attachAsLChild(p, v->rc); attachAsRChild(g, v->lc);
					attachAsLChild(v, g); attachAsRChild(v, p);
				}
			else if (IsRChild(*p))//zag-zag
			{
				attachAsRChild(g, p->lc); attachAsRChild(p, v->lc);
				attachAsLChild(p, g); attachAsLChild(v, p);
			}
			else//zag-zig
			{
				attachAsRChild(p, v->lc); attachAsLChild(g, v->rc);
				attachAsRChild(v, g); attachAsLChild(v, p);
			}
			if (!gg) v->parent = NULL;//如果曾祖父不存在，那么v经历双层伸展后必定为树根
			else//如果存在，那么gg就是v的父亲
				(g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);//根据g来判断v是作为右孩子还是左孩子
			updateHeight(g); updateHeight(p); updateHeight(v);//更新高度
		}//while结束
		//双层伸展结束后，必定有g==NULL，但是p不一定为空，所以可能需要在进行一次单旋
		if (p = v->parent)
		{
			if (IsLChild(*v))
			{
				attachAsLChild(p, v->rc); attachAsRChild(v, p);
			}
			else
			{
				attachAsRChild(p, v->lc); attachAsLChild(v, p);
			}
			updateHeight(p); updateHeight(v);//更新高度
		}
		v->parent = NULL; return v;//调整之后新的树根就是v了。所以返回v以便于上层函数更新树根

	}



public://重写 搜索 插入 和删除。因为都会引起两次旋转（伸展）
	BinNodePosi(T)& search(const T& e)//不再是静态操作
	{
		BinNodePosi(T) p = searchIn(_root, e, _hot = NULL);
		_root = splay(p ? p : _hot);//_hot是搜索的最后一个节点
		return _root;//返回根节点。现在根节点已经是搜索到的节点了
	}
	BinNodePosi(T) insert(const T&e)//把关键码e插入伸展树中
	{
		if (!_root) { _size++; return _root = BinNode<T>(e); }//处理原树为空的退化
		if (e == search(e)->data) return _root;//确保目标节点不存在，因为要插入
		//如果真的不存在的话
		_size++; BinNodePosi(T) t = _root;//创建新节点
		if (_root->data < e)//如果原树根（已经不是最开始的树根，是t）小与新插入的节点 那么就以t为左孩子，t->rc为右孩子
		{
			t->parent = new BinNode<T>(e, NULL, t, t->rc);//一步一步对这些节点进行连接，看着图会比较形象
			if (HasRChild(*t)) { t->rc->parent = _root; t->rc = NULL; }
		}
		else//以t的lc和t作为左右孩子
		{
			t->parent = new BinNode<T>(e, NULL, t->lc, t);//一步一步对这些节点进行连接，看着图会比较形象
			if (HasRChild(*t)) { t->lc->parent = _root; t->lc = NULL; }
		}
		updateHeightAbove(t);//更新t及其祖先高度（实际就_root一个）
		return _root;//返回刚才插入的节点
	}
	bool remove(const T& e)//从伸展树中删除关键码e
	{
		if (!_root || (e != search(e)->data)) return false;//如果空树或者树中没有这个元素  插入失败
		BinNodePosi(T) w = _root;//search后e已经伸展到根了
		if(!HasLChild(*_root))//如果没有左子树，直接删除这个根节点就行
		{
			_root = _root->rc;
			if (_root) _root->parent = NULL;
		}
		else if (!HasRChild(*_root))//对称的 如果没有右子树
		{
			__root = _root->lc;
			if (_root) _root->parent = NULL;
		}
		else//最重要的 左右子树同时存在的情况下 
		{
			BinNodePosi(T) lTree = _root->lc;//先创建一个节点等与左子树
			lTree->parent = NULL; _root->lc = NULL;//暂时将左子树切除掉
			_root = _root->rc; _root->parent = NULL;//现在根是右子树的第一个节点，但是我们要将右子树中最小的节点作为树根
			search(w->data);//所以在右子树一次必定失败的查询，查到的是右子树中最小的节点，现在树根编程右子树最小的节点了
			_root->lc = lTree; lTree->parent = _root;
			
		}
		release(w->data); release(w); _size--;//释放节点更新规模
		if (_root) updateHeight(_root);//若树非空 更新树根高度
		return ture;//删除成功
	}
};