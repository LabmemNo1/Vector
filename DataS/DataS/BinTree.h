#pragma once
#include"BinNode.h"
#include "Stack.h"
#include<memory>
template <typename T> class BinTree
{
protected:
	int _size; BinNodePosi(T) _root;//规模 根节点
	virtual int updateHeight(BinNodePosi(T) x);//更新节点x的高度
	void updateHeightAbove(BinNodePosi(T) x);//更新节点x及其祖先的高度

public:
	//构造函数
	BinTree():_size(0),_root(NULL){}
	
	~BinTree() { /*if (0<_size) remove(_root);*/ }//析构函数
	int size()const { return _size; }
	bool empty()const { return !_root; }
	BinNodePosi(T) root()const { return _root; }//树根
	BinNodePosi(T) insertAsRoot(T const &e);//插入根节点
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const &e);//e作为x的左孩子插入（原无）
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const &e);//e作为x的右孩子插入（原无）
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &T);//T作为x的左子树接入
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &T);//T作为x的右子树接入
	int remove(BinNodePosi(T) x);//删除以位置x处节点为根的子树，返回该子树原先的规模
	BinTree<T>* secede(BinNodePosi(T) x);//将子树x从当前树种剔除，并将其转换为一颗独立子树

};

template<typename T>
inline int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + max(stature(x->lc), stature(x->rc));
}

template<typename T>
inline void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while (x)
	{
		updateHeight(x);
		x = x->parent;
	}
}

template<typename T>
inline BinNodePosi(T) BinTree<T>::insertAsRoot(T const & e)
{
	_size = 1;
	return _root = new BinNode<T>(e);
}
template<typename T>
inline BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const & e)
{
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lc;
}

template<typename T>
inline BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const & e)
{
	_size++;
	x->insertAsRC(e);
	upadateHeightAbove(x);
	return x->rc;
}
template <typename T,typename VST>
void travPre_R(BinNodePosi(T) x, VST& visit)//二叉树先序遍历（递归版本）
{
	if (!x) return;//递归基，空树返回
	visit(x->data);//先访问根节点
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
}
template <typename T, typename VST>
void travIn_R(BinNodePosi(T) x, VST& visit)//二叉树中序遍历（递归版本）
{
	if (!x) return;//递归基，空树返回
	travPre_R(x->lc, visit);//先访问左孩子
	visit(x->data);
	travPre_R(x->rc, visit);
}
template <typename T, typename VST>
void travPost_R(BinNodePosi(T) x, VST& visit)//二叉树后序遍历（递归版本）
{
	if (!x) return;//递归基，空树返回
	travPre_R(x->lc, visit);//先访问左孩子
	travPre_R(x->rc, visit);
	visit(x->data);
	
	
}

template <typename T, typename VST>
void travPre_I(BinNodePosi(T) x, VST& visit)//二叉树先序遍历（迭代版本1）
{
	Stack<BinNodePosi(T)> S;//利用栈
	if (x) S.push(x);
	while (!S.empty())
	{
		x = S.pop();
		visit(x->data);
		if(x->rc) S.push(x->rc);//栈的先进后出特性。右孩子先入栈
		if(x->lc) S.push(x->lc);
	}
}





template <typename T,typename VST>
static void visitAlongLeftBranch(
	BinNodePosi(T) x, VST &visit, Stack<BinNodePosi(T)> &S
)
{
	while (x)//反复地
	{
		visit(x->data);//访问当前节点
		S.push(x->rc);//右孩子入栈
		x = x->lc;//沿着左侧链下行
	}
}
template <typename T, typename VST>
void travPre_I2(BinNodePosi(T) x, VST &visit)//二叉树先序遍历（迭代版本2）
{
	Stack<BinNodePosi(T)> S;//辅助栈
	while (1)
	{
		visitAlongLeftBranch(x, visit, S);//访问左侧链，将右子树存入栈中
		if (S.empty()) break;//栈空就跳出
		x = S.pop();//弹出最后一个入栈的右子树，然后继续循环，自下而上
	}
}



template <typename T>//二叉树中序遍历 迭代版本
static void goAlongLeftBranch(BinNodePosi(T) x, Stack<BinNodePosi(T)> &S)
{
	while (x)//沿着左侧链不断深入直到最后一个，不断存入栈中
	{
		S.push(x);
		x = x->insertAsLC;//

	}
}
template <typename T, typename VST>
void travIn_I1(BinNodePosi(T) x, VST &visit)
{
	Stack<BinNodePosi(T)> S;//辅助栈
	while (1)
	{
		goAlongLeftBranch(x, S);
		if (S.empty()) break;//空栈跳出
		x = S.pop();//栈顶弹出（栈顶就是最后一个入栈的左孩子）
		visit(x->data);
		x = x->rc;
	}
}

template <typename T>//在以s栈顶节点为根的子树中，找到最高左侧可见叶节点
static void gotoHLVFL(Stack<BinNodePosi(T)> S)//沿途所遇节点依次入栈
{
	while (BinNodePosi(T) x = S.top())//自顶向下，依次检查当前节点
		if (x->lc) //尽可能向左
		{
			if (x->rc) S.push(x->rc);//优先将右孩子存入栈中
			S.push(x->lc);//然后存入左孩子
		}
		else//不得已
			S.push(x->rc);//向右
	S.pop();//弹出栈顶空节点
}
template <typename T,typename VST>
void travPost_I(BinNodePosi(T) x, VST &visit)
{
	Stack<BinNodePosi(T)> S;
	if (x) S.push(x);
	while (!S.empty())//只要栈不空就循环
	{
		if (S.top() != x->parent)//如果栈顶不是上一个元素的父节点，那么就是上一个元素的右兄弟，如果是右兄弟，还要去寻找右兄弟的最高左侧可见叶节点
			gotoHLVFL(S);
		x = S.pop();
		visit(x->data);

	}
}
template <typename T>//删除二叉树中位置x处的节点及其后代，返回被删除节点的数量
int BinTree<T>::remove(BinNodePosi(T) x) {//假定参数合法
	FromParentTo(*x) = NULL;//切断来自父节点的引用
	updateHeightAbove(x->parent);//更新祖先高度
	int n = removeAt(x); _size -= n; return n;//删除子树，更新规模，返回被删除的节点数量
}
template <typename T>
static int removeAt(BinNodePosi(T) x) {
	if (!x) return 0;//递归基，空树
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);
	delete(x);
	
	return n;
}