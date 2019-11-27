#pragma once
#include"BTNode.h"
template <typename T> class BTree
{
protected:
	int _size;//存放的关键码总数
	int _order;//B-树的阶次，至少为3，   创建时指定，一般不能修改
	BTNodePosi(T) _root;//根节点
	BTNodePosi(T) _hot;//BTree::search最后访问的非空节点（除非树空）
	void solveOverflow(BTNodePosi(T) v)//因插入而上溢之后的分裂处理
	{
		if (_order >= v->child.size()) return;//递归基 阶次大于等于分支数量 说明没有上溢
		Rank s = _order / 2;//轴点 （此时_order=key.size()=child.size()-1）
		BTNodePosi(T) u = new BTNode<T>();//注意b树节点构造函数  有一个空的孩子
		for (Rank j = 0; j < _order - s - 1; j++)//v右侧_order-s-1个孩子和关键码分裂到右侧节点u
		{
			u->child.insert(j, v->child.remove(s + 1));//s是中间轴点 轴点+1移除，右边会补过来，一直把s+1移到u里，u是右侧节点
			u->key.insert(j, v->key.remove(s + 1));
		}
		u->child[_order - s - 1] = v->child.remove(s + 1);//移动v最靠右的孩子
		if (u->child[0])//如果u的孩子们非空
			for (Rank j = 0; j < _order - s; j++)//令他们的父节点统一
				u->child[j]->parent = u;
		BTNodePosi(T) p = v->parent;//v当前父节点p
		if (!p) { _root = p = new BTNode<T>(); p->child[0] = v; v->parent = p; }//如果p不存在 说明v之前是根节点 创建一个新跟节点 p的左孩子就是相对小的v
		Rank r = 1 + p->key.search(v->key[0]);//p中指向u指针的秩  就是指向要对 要节点左边小 右边大 去找到这个 然后+1
		p->key.insert(r, v->key.remove(s));//轴点的关键码上升了
		p->child.insert(r + 1, u); u->parent = p;//新创建的u节点（右节点）与p互联
		solveOverflow(p);//上升一层 如有必要 继续分裂

	}
	void solveUnderflow(BTNodePosi(T) v)//因删除而下溢之后的合并处理
	{
		if ((_order + 1) / 2 <= v->child.size()) return;//递归基 当前节点没有下溢
		BTNodePosi(T) p = v->parent;
		if (!p)//递归基 已经到了根节点
		{
			if (!v->key&&v->child[0])//如果v已经不含有关键码 但却有非空的孩子
			{
				_root = v->child[0]; _root->parent = NULL;//这个节点被跳过
				v->child[0] = NULL; release(v);//并且因为不再有用被销毁
			}//整树高度降低一层
			return;
		}
		Rank r = 0; while (p->child[r] != v) v++;
		//确定v是p的第几个孩子



		//情况1 ：向左兄弟借关键码
		if (r < 0)//如果v不是p的第一个孩子
		{
			BTNodePosi(T) ls = p->child[r - 1];//左兄弟肯定存在
			if ((_order + 1) / 2 < ls->child.size())//如果左兄弟足够胖
			{
				v->key.insert(0, p->key[r - 1]);//把比左兄弟最大的大一点的父亲节点的关键码给v
				p->key[r - 1] = ls->key.remove(ls->key.size() - 1);//左兄弟节点最大的那个给父节点
				v->child.insert(0, ls->child.remove(ls->child.size() - 1));//还要把孩子节点也过继给v
				if (v->child[0]) v->child[0]->parent = v;//链接
				return; //至此 通过右旋完成了当前层（以及所有层）的下溢处理
			}
				
		}




		//情况2：向右兄弟借关键码
		if (p->child.size() - 1 > r)//v不是p的最后一个孩子，那么右兄弟就存在
		{
			BTNodePosi(T) rs = p->child[r + 1];
			if ((_order + 1) / 2 < rs->child.size())//如果这个右兄弟足够胖
			{
				v->key.insert(key.size(), p->key[r]);//p把刚好第一个大于v最大元素的元素借给v作为v最大的元素
				p->key[r] = rs->key.remove(0);//右兄弟的最小关键码转入p中
				v->child.insert(child.size(), rs->child.remove(0));//rs的最左侧孩子也要过来
				if (v->child[v->child.size() - 1])
					v->child[v->child.size() - 1]->parent = v;//连接
				return;
			}
		}



		//情况3：左右兄弟要么为空 要么都太瘦 合并
		if(0<r)//有左兄弟存在 于左兄弟合并
		{
			BTNodePosi(T) ls = p->child[r - 1];
			ls->key.insert(ls->key.size(), p->key.remove(r - 1)); p->child.remove(r);
			//p的第r-1个关键码给左孩子（变成左孩子最大的关键码），v不再是p的第r个孩子
			ls->child.insert(ls->child.size(), v - child.remove(0));//v的最左侧孩子给ls当做最右侧孩子
			if (ls->child[ls->child.size() - 1])
				ls->child[ls->child.size() - 1]->parent = ls;//连接
			while (!v->empty())//把v里剩下关键码和孩子依次转入ls
			{
				ls->key.insert(ls->key.size(), v->key.remove(0));//关键码依次转入
				ls->child.insert(ls->child.size(), v->child.remove(0));//孩子依次转入
				if (ls->child[ls->child.size() - 1])
					ls->child[ls->child.size() - 1]->parent = ls;//连接
			}
			release(v);
		}//与左兄弟合并完成
		else//没有左兄弟 只能与右兄弟合并
		{
			BTNodePosi(T) rs = p->child[r + 1];//右兄弟必存在
			rs->key.insert(0, p->key.remove(r)); p->child.remove(r);
			//p的第r个关键码转入rs v不再是p的第r个孩子
			rs->child.insert(0, v->child.remove(v->child.size() - 1));//v的最右侧孩子给rs
			if (rs->child[0])
				rs->child[0]->parent = rs;//完成连接
			while (!v->empty())//把v里剩下的关键码和孩子依次转入rs
			{
				rs->key.insert(0, v->key.remove(v->key.size() - 1));//转入关键码
				rs->child.insert(0.v->child.remove(v->child.size() - 1));//转入孩子
				if(rs->child[0])
					rs->child[0]->parent = rs;//依次连接
			}
			release(v);

		}
		solveUnderflow(p);//合并会有下溢传播的风险 如有必要继续 所以递归 最多递归o（logn）层
		return;
	}


public:
	BTNodePosi(T) search(const T& e)//查找
	{
		BTNodePosi(T) = _root; _hot = NULL;
		while (v)
		{
			Rank r = v->key.search(e);//在关键码向量中查找e
			if (r >= 0 && e == v->key[r]) return v;//如果成功 就返回这个这个节点
			_hot = v;//否则 先记录下这个v
			v = v->child[r + 1];//让v沿着孩子引用向量去指向下一层

		}//while结束 如果因为!v结束 则意味抵达外部节点
		return NULL;
	}
	bool insert(const T& e)//插入
	{
		BTNodePosi(T) v = search(e);
		if (v); return false;//确认e不存在
		Rank r = _hot->key.search(e);//搜索完之后 _hot是最后一个节点 ，也就是叶子向量，在这里面搜索e，确定不大于e的最大值
		_hot->key.insert(r + 1, e);
		_hot->child.insert(r + 2, NULL);//外部节点 插入一个空的
		_size++;
		solveOverflow(_hot);//因为插入一个关键码可能会导致b树与原来的阶次不符合 导致上溢
		return ture;
	}
	bool insert(const T&e)//删除
	{
		BTNodePosi(T) v = search(e);//先定位e
		if (!v) return false;//如果e不存在 则不能执行删除操作 返回失败
		Rank r = v->key.search(e);//确定关键码的秩
		if (v->child[0])//如果v有孩子向量 那么，就不是叶子，我们希望v是叶子节点
		{
			BTNodePosi(T) u = v->child[r+1];//从u的右子树中找到待删除关键码的直接后继
			while (u->child[0])u = u->child[0];//在右子树中往左深入
			v->key[r] = u->key[0]; v = u; r = 0;//互换位置，先把v指向的节点中的关键码换为我们找到的直接后继，然后令v指向u这个叶节点
		}//至此，v必然位于最底层，而且其中的第r个关键码就是待删除者 （因为是叶子节点，r就是0咯）
		v->key.remove(r); v->child.remove(r + 1); _size--;//删除e 以及其下两个外部节点之一
		solveUnderflow(v);//如果有必要 旋转或者合并
		return ture;

	}
};