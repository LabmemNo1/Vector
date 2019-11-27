#pragma once
//����������
#include"BinTree.h"
template <typename T>class BST :public BinTree<T>
{

protected:
	BinNodePosi(T) _hot;//���нڵ�ĸ���
	BinNodePosi(T) connect34(//����3+4�ṹ�����������ڵ㼰�Ŀ�����
		BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
		BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3)
	{
		a->lc = T0; if (T0) T0->parent = a;//a������
		a->rc = T1; if (T1) T1->parent = a; updateHeight(a);//���¸߶�

		c->lc = T2; if (T2) T2->parent = c;//c������
		c->rc = T3; if (T3) T3->parent = c; updateHeight(b);//���¸߶�

		b->lc = a; a->parent = b;
		b->rc = c; c->parent = b; updateHeight(c);//���¸߶�
	}
	BinNodePosi(T) rotateAt(BinNodePosi(T) v)//��x���丸�� �游��ͳһ��ת����
	{
		BinNodePosi(T) p = v->parent; BinNodePosi(T) g = p->parent;
		if(IsLChild(*p))
			if (IsLChild(*v))//zig-zig
			{
				p->parent = g->parent;//�������� �ϲ����µ��������ϲ㺯�����
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
	virtual BinNodePosi(T) & search(const T& e);//����
	virtual BinNodePosi(T) insert(const T& e);//����
	virtual bool remove(const T& e);//ɾ��

	
};
template <typename T>
static BinNodePosi(T) &searchIn(BinNodePosi(T) &v,const T& e,BinNodePosi(T) &hot)
{
	if (!v || (e == v->data)) return v;//�ݹ�������v�ǿսڵ����e����v��������
	hot = v;//���û�е���ݹ����һ������£���¼�µ�ǰ�ڵ�
	return searchIn(((e<v->data)?v->lc:v->rc), e, hot);//β�ݹ飬eС��v�����󣬴���v���ң������������Ķ��ֲ���

}

template<typename T>
inline BinNodePosi(T)& BST<T>::search(const T & e)
{
	return searchIn(BinTree<T>::_root, e, _hot = nullptr);
}

template<typename T>
inline BinNodePosi(T) BST<T>::insert(const T & e)
{
	BinNodePosi(T) &x = search(e); if (x) return x;//����ȷ��Ŀ�겻���� ����Ϊ���Ǽٶ���������ͬԪ�أ�
	//���������
	x = new BinNode<T>(e,_hot);
	BinTree<T>::_size++;
	updateHeightAbove(x);//���¸߶�
	return x;

}
template <typename T>
static BinNodePosi(T) removeAT(BinNodePosi(T) &x, BinNodePosi(T) &hot)//ÿ���ڵ�Ҫ�������ĺ���͸��ף���ס��һ��
{
	BinNodePosi(T) w = x;
	BinNodePosi(T) succ = NULL;//��ɾ���ڵ�Ľ�����
	if (!(x->lc)) succ = x = x->rc;//����������������滻Ϊ������
	else if (!(x->rc)) succ = x = x->lc;//�Գ�
	else//�������������ڵĻ�
	{
		w = w->succ();//�ҵ�succ��ֱ�Ӻ�̣���������������µĺ�̣�
		swap(x->data, w->data);//��������
		BinNodePosi(T) u = w->parent;
		(u == x ?  u->rc : u->lc) = succ = w->rc;//�������������ֻ��һ�õ����������ڵ����������������о�����һ�������ұ�
		//����һ�о������������ڵ� succ�����ɾ���Ľڵ㣨��succ�п϶�������������Ȼ��succ�ڵ����ӱ�ɾ���ڵ�ĸ��ס�

	}
	hot = w->parent;//hot�Ǳ�ɾ���ߵĸ���
	succ->parent = hot;//�����߸�����hot
	release(w->data);
	release(w);
	return succ;
}

template<typename T>
inline bool BST<T>::remove(const T & e)
{

	BinNodePosi(T) x = search(e);
	if(!x) return false;//���û����������� ɾ����
	removeAt(x, _hot);
	BinTree<T>::_size--;
	updateHeightAbove(_hot);//���¸߶� �ӱ�ɾ�ڵ�ĸ��׸���
	return true;
}
