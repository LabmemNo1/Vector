#pragma once
#include"BinNode.h"
#include "Stack.h"
#include<memory>
template <typename T> class BinTree
{
protected:
	int _size; BinNodePosi(T) _root;//��ģ ���ڵ�
	virtual int updateHeight(BinNodePosi(T) x);//���½ڵ�x�ĸ߶�
	void updateHeightAbove(BinNodePosi(T) x);//���½ڵ�x�������ȵĸ߶�

public:
	//���캯��
	BinTree():_size(0),_root(NULL){}
	
	~BinTree() { /*if (0<_size) remove(_root);*/ }//��������
	int size()const { return _size; }
	bool empty()const { return !_root; }
	BinNodePosi(T) root()const { return _root; }//����
	BinNodePosi(T) insertAsRoot(T const &e);//������ڵ�
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const &e);//e��Ϊx�����Ӳ��루ԭ�ޣ�
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const &e);//e��Ϊx���Һ��Ӳ��루ԭ�ޣ�
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &T);//T��Ϊx������������
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &T);//T��Ϊx������������
	int remove(BinNodePosi(T) x);//ɾ����λ��x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ
	BinTree<T>* secede(BinNodePosi(T) x);//������x�ӵ�ǰ�����޳���������ת��Ϊһ�Ŷ�������

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
void travPre_R(BinNodePosi(T) x, VST& visit)//����������������ݹ�汾��
{
	if (!x) return;//�ݹ������������
	visit(x->data);//�ȷ��ʸ��ڵ�
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
}
template <typename T, typename VST>
void travIn_R(BinNodePosi(T) x, VST& visit)//����������������ݹ�汾��
{
	if (!x) return;//�ݹ������������
	travPre_R(x->lc, visit);//�ȷ�������
	visit(x->data);
	travPre_R(x->rc, visit);
}
template <typename T, typename VST>
void travPost_R(BinNodePosi(T) x, VST& visit)//����������������ݹ�汾��
{
	if (!x) return;//�ݹ������������
	travPre_R(x->lc, visit);//�ȷ�������
	travPre_R(x->rc, visit);
	visit(x->data);
	
	
}

template <typename T, typename VST>
void travPre_I(BinNodePosi(T) x, VST& visit)//��������������������汾1��
{
	Stack<BinNodePosi(T)> S;//����ջ
	if (x) S.push(x);
	while (!S.empty())
	{
		x = S.pop();
		visit(x->data);
		if(x->rc) S.push(x->rc);//ջ���Ƚ�������ԡ��Һ�������ջ
		if(x->lc) S.push(x->lc);
	}
}





template <typename T,typename VST>
static void visitAlongLeftBranch(
	BinNodePosi(T) x, VST &visit, Stack<BinNodePosi(T)> &S
)
{
	while (x)//������
	{
		visit(x->data);//���ʵ�ǰ�ڵ�
		S.push(x->rc);//�Һ�����ջ
		x = x->lc;//�������������
	}
}
template <typename T, typename VST>
void travPre_I2(BinNodePosi(T) x, VST &visit)//��������������������汾2��
{
	Stack<BinNodePosi(T)> S;//����ջ
	while (1)
	{
		visitAlongLeftBranch(x, visit, S);//�����������������������ջ��
		if (S.empty()) break;//ջ�վ�����
		x = S.pop();//�������һ����ջ����������Ȼ�����ѭ�������¶���
	}
}



template <typename T>//������������� �����汾
static void goAlongLeftBranch(BinNodePosi(T) x, Stack<BinNodePosi(T)> &S)
{
	while (x)//�����������������ֱ�����һ�������ϴ���ջ��
	{
		S.push(x);
		x = x->insertAsLC;//

	}
}
template <typename T, typename VST>
void travIn_I1(BinNodePosi(T) x, VST &visit)
{
	Stack<BinNodePosi(T)> S;//����ջ
	while (1)
	{
		goAlongLeftBranch(x, S);
		if (S.empty()) break;//��ջ����
		x = S.pop();//ջ��������ջ���������һ����ջ�����ӣ�
		visit(x->data);
		x = x->rc;
	}
}

template <typename T>//����sջ���ڵ�Ϊ���������У��ҵ�������ɼ�Ҷ�ڵ�
static void gotoHLVFL(Stack<BinNodePosi(T)> S)//��;�����ڵ�������ջ
{
	while (BinNodePosi(T) x = S.top())//�Զ����£����μ�鵱ǰ�ڵ�
		if (x->lc) //����������
		{
			if (x->rc) S.push(x->rc);//���Ƚ��Һ��Ӵ���ջ��
			S.push(x->lc);//Ȼ���������
		}
		else//������
			S.push(x->rc);//����
	S.pop();//����ջ���սڵ�
}
template <typename T,typename VST>
void travPost_I(BinNodePosi(T) x, VST &visit)
{
	Stack<BinNodePosi(T)> S;
	if (x) S.push(x);
	while (!S.empty())//ֻҪջ���վ�ѭ��
	{
		if (S.top() != x->parent)//���ջ��������һ��Ԫ�صĸ��ڵ㣬��ô������һ��Ԫ�ص����ֵܣ���������ֵܣ���ҪȥѰ�����ֵܵ�������ɼ�Ҷ�ڵ�
			gotoHLVFL(S);
		x = S.pop();
		visit(x->data);

	}
}
template <typename T>//ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ������
int BinTree<T>::remove(BinNodePosi(T) x) {//�ٶ������Ϸ�
	FromParentTo(*x) = NULL;//�ж����Ը��ڵ������
	updateHeightAbove(x->parent);//�������ȸ߶�
	int n = removeAt(x); _size -= n; return n;//ɾ�����������¹�ģ�����ر�ɾ���Ľڵ�����
}
template <typename T>
static int removeAt(BinNodePosi(T) x) {
	if (!x) return 0;//�ݹ��������
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);
	delete(x);
	
	return n;
}