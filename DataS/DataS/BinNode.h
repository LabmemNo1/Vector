#pragma once
#include"Queue.h"
#include<stddef.h>
#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p)?(p)->height:-1)//�ڵ�߶ȣ�������߶�Ϊ-1ͳһ





/*BinNode״̬�����ʵ��ж�*/
#define IsRoot(x) (!(x).parent)//�ǲ��Ǹ��ڵ� ����x��û�и��׽ڵ����ж�
#define IsLChild(x) (!IsRoot(x)&&(&(x)==(x).parent->lc))//�ǲ���һ�����ӣ�
#define IsRChild(x) (!IsRoot(x)&&(&(x)==(x).parent->rc))
#define HasParent(x) (!IsRoot(x))//��û�и��׽ڵ�
#define HasLChild(x) ((x).lc)
#define HasRChild(x) ((x).rc)
#define HasChild(x) (HasLChild(x)||HasRChild(x))
#define HasBothChild(x) (HasLChild(x)&&HasRChild(x))
#define IsLeaf(x) (!HasChild(x))//�ǲ���Ҷ��


/*��BinNode�����ض���ϵ�Ľڵ㼰ָ��*/

#define sibling(p) \
	(IsLChild(*(p))?(p)->parent->rc:(p)->parent->lc)

#define uncle(x) (IsLChild(*((x)->parent))?(x)->parent->parent->rc:(x)->parent->parent->lc)


#define FromParentTo(x) (IsRoot(x) ? _root : (IsRChild(x) ? (x).parent->rc : (x).parent->lc))


typedef enum {RB_RED,RB_BLCAK} RBColor;//�ڵ���ɫ
template <typename T> struct BinNode
{
	
	//��Ա
	T data;//��ֵ
	BinNodePosi(T) parent;
	BinNodePosi(T) lc;
	BinNodePosi(T) rc;//���ڵ� ���Һ���
	
	int height;//�߶�
	int npl;//Null Path Length(��ʽ��)
	RBColor color;//��ɫ���������
	//���캯��
	BinNode():parent(NULL),lc(NULL),rc(NULL),height(0),npl(1),color(RB_RED){}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int h = 0,int l=1,RBColor c=RB_RED):
		data(e),parent(p),lc(lc),rc(rc),height(h),npl(l),color(c){}


	



	//�����ӿ�
	int size();//��ǰ�ڵ���������Ҳ��������Ϊ���������Ĺ�ģ
	



	BinNodePosi(T) insertAsRC(T const &e);//��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
	BinNodePosi(T) insertAsLC(T const &e);//��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
	
	
	BinNodePosi(T) succ();//ȡ��ǰ�ڵ��ֱ�Ӻ��


	template <typename VST> void travLevel(VST&);//������α��� ���¶��ϣ��������
	template <typename VST> void traPre(VST&);//�����������
	template <typename VST> void travIn(VST&);//�����������
	template <typename VST> void travPost(VST&);//�����������
	//�Ƚ���
	bool operator<(BinNode const& bn) { return data < bn.data; }//С��0

	bool operator==(BinNode const& bn) { return data == bn.data; }


};



template <typename T>
inline BinNodePosi(T) BinNode<T>::insertAsLC(T const &e)
{
	return lc = new BinNode(e, this);//����ڵ����һ��e�������ӽڵ����e������һ�����ӽڵ㣬�丸�ڵ�����Լ�
}

template<typename T>
inline BinNodePosi(T) BinNode<T>::succ()//������������е�ֱ�Ӻ��
{
	BinNodePosi(T) s = this;//��¼��̵���ʱ����
	if (rc)//������Һ��ӣ���ô���̱ض�����������
	{
		s = rc;
		while (s->lc)
			s = s->lc;//�������� ���Ľڵ�
	}
	else//���û���Һ��ӣ���ô���������������ڵ��������ڵ�����ӻ����Һ��ӣ������������ô��̾������ĸ��ڵ㣬������Һ��ӣ�����ֱ�Ӻ�̾��ǡ�����ǰ�ڵ���������������е�������ȡ�
	{
		while (s == (s->parent)->rc)
			s = s->parent;
		s = s->parent;
	}
}


template<typename T>
inline int BinNode<T>::size()
{
	

		int s = 1;//�����Լ�
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
	Queue<BinNodePosi(T)> Q;//��������
	Q.enqueue(this);
	while (!Q.empty())
	{
		BinNodePosi(T) x = Q.dequeue();
		visit(x->data);
		if (x->lc) Q.enqueue(x->lc);
		if (x->rc) Q.enqueue(x->rc);
	}

}
