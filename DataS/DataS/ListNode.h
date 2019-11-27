#pragma once
//typedef int Rank;
////#define ListNodePosiT ListNode<T>*;
////����ڵ�  
//template <typename T> struct ListNode
//{
//	//��Ա
//	T data; ListNode<T>* pred; ListNode<T>* succ;//��ֵ ǰ�� ��׺
//	//���캯��
//	ListNode() {}
//	ListNode(T e, ListNode<T>* p = nullptr; ListNode<T>* s = nullptr) :data(e), pred(p), succ(s) {}//��ֵ ǰ�� ���
//	//�����ӿ�
//	ListNodePosiT insertAsPred(T const& e)//����ǰ��
//	{
//		ListNode<T>* x = new ListNode(e, pred, this);
//		pred->succ = x; pred = x;
//		return x;//�����½ڵ�λ��
//	}
//	ListNodePosiT insertAsSucc(T const& e)//������   ��ͼ�Ļ��ͺ��������
//	{
//		ListNode<T>* x = new ListNode(e, this, succ);
//		succ->pred = x; succ = x;
//		return x;
//	}
//};
typedef int Rank; //��
#define ListNodePosi(T) ListNode<T>* //�б�ڵ�λ��

template <typename T> struct ListNode { //�б�ڵ�ģ���ࣨ��˫��������ʽʵ�֣�
// ��Ա
	T data; ListNodePosi(T) pred; ListNodePosi(T) succ; //��ֵ��ǰ�������
 // ���캯��
	ListNode() {} //���header��trailer�Ĺ���
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL)
		: data(e), pred(p), succ(s) {} //Ĭ�Ϲ�����
  // �����ӿ�
	ListNodePosi(T) insertAsPred(T const& e) //������ǰ�ڵ�֮ǰ�����½ڵ�
	{
				ListNode<T>* x = new ListNode(e, pred, this);
		pred->succ = x; pred = x;
		return x;//�����½ڵ�λ��
	}
	ListNodePosi(T) insertAsSucc(T const& e) //���浱ǰ�ڵ�֮������½ڵ�
	{
		ListNode<T>* x = new ListNode(e, this, succ);
				succ->pred = x; succ = x;
				return x;
	}
};
