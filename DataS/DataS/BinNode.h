#pragma once
#include"Queue.h"
#include<stddef.h>
#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p)?(p)->height:-1)//节点高度，与空树高度为-1统一





/*BinNode状态与性质的判断*/
#define IsRoot(x) (!(x).parent)//是不是根节点 根据x有没有父亲节点来判断
#define IsLChild(x) (!IsRoot(x)&&(&(x)==(x).parent->lc))//是不是一个左孩子？
#define IsRChild(x) (!IsRoot(x)&&(&(x)==(x).parent->rc))
#define HasParent(x) (!IsRoot(x))//有没有父亲节点
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x)||HasRChild(x))
#define HasBothChild(x) (HasLChild(x)&&HasRChild(x))
#define IsLeaf(x) (!HasChild(x))//是不是叶子


/*与BinNode具有特定关系的节点及指针*/

#define sibling(p) \
	(IsLChild(*(p))?(p)->parent->rc:(p)->parent->lc)

#define uncle(x) (IsLChild(*((x)->parent))?(x)->parent->parent->rc:(x)->parent->parent->lc)


#define FromParentTo(x) (IsRoot(x) ? _root : (IsRChild(x) ? (x).parent->rc : (x).parent->lc))


typedef enum {RB_RED,RB_BLCAK} RBColor;//节点颜色
template <typename T> struct BinNode
{
	
	//成员
	T data;//数值
	BinNodePosi(T) parent;
	BinNodePosi(T) lc;
	BinNodePosi(T) rc;//父节点 左右孩子
	
	int height;//高度
	int npl;//Null Path Length(左式堆)
	RBColor color;//颜色（红黑树）
	//构造函数
	BinNode():parent(NULL),lc(NULL),rc(NULL),height(0),npl(1),color(RB_RED){}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int h = 0,int l=1,RBColor c=RB_RED):
		data(e),parent(p),lc(lc),rc(rc),height(h),npl(l),color(c){}


	



	//操作接口
	int size();//当前节点后代总数，也就是以其为根的子树的规模
	



	BinNodePosi(T) insertAsRC(T const &e);//作为当前节点的右孩子插入新节点
	BinNodePosi(T) insertAsLC(T const &e);//作为当前节点的左孩子插入新节点
	
	
	BinNodePosi(T) succ();//取当前节点的直接后继


	template <typename VST> void travLevel(VST&);//子树层次遍历 自下而上，自左而右
	template <typename VST> void traPre(VST&);//子树先序遍历
	template <typename VST> void travIn(VST&);//子树中序遍历
	template <typename VST> void travPost(VST&);//子树后序遍历
	//比较器
	bool operator<(BinNode const& bn) { return data < bn.data; }//小于0

	bool operator==(BinNode const& bn) { return data == bn.data; }


};



template <typename T>
inline BinNodePosi(T) BinNode<T>::insertAsLC(T const &e)
{
	return lc = new BinNode(e, this);//向左节点插入一个e就是向孩子节点插入e，创建一个孩子节点，其父节点就是自己
}

template<typename T>
inline BinNodePosi(T) BinNode<T>::succ()//中序遍历序列中的直接后继
{
	BinNodePosi(T) s = this;//记录后继的临时变量
	if (rc)//如果有右孩子，那么其后继必定在右子树中
	{
		s = rc;
		while (s->lc)
			s = s->lc;//右子树中 最靠左的节点
	}
	else//如果没有右孩子，那么分两种情况，这个节点是他父节点的左孩子还是右孩子，如果是左孩子那么后继就是他的父节点，如果是右孩子，他的直接后继就是“将当前节点包含于其左子树中的最低祖先”
	{
		while (s == (s->parent)->rc)
			s = s->parent;
		s = s->parent;
	}
}


template<typename T>
inline int BinNode<T>::size()
{
	

		int s = 1;//算上自己
		if (lc) s += lc->size();
		if (rc) s += rc->size();
		return s;

	

}
template <typename T>
inline BinNodePosi(T) BinNode<T>::insertAsRC(T const &e)
{
	return rc= new BinNode(e, this);
}

template<typename T>
template<typename VST>
inline void BinNode<T>::travLevel(VST &visit)
{
	Queue<BinNodePosi(T)> Q;//辅助队列
	Q.enqueue(this);
	while (!Q.empty())
	{
		BinNodePosi(T) x = Q.dequeue();
		visit(x->data);
		if (x->lc) Q.enqueue(x->lc);
		if (x->rc) Q.enqueue(x->rc);
	}

}
