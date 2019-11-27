#pragma once
//B-��
#include"Myvector.h"
#define BTNodePosi(T) BTNode<T>*


template <typename T> struct BTNode
{
	//��Ա:
	BTNodePosi(T) parent;//���ڵ�
	Vector<T> key;//�ؼ�������
	Vector<BTNodePosi(T)> child;//��������



	//���캯�� ��BTNodeֻ����Ϊ���ڵ㴴������ʼʱ��0���ؼ����һ���պ���ָ�룩
	BTNode() { parent = NULL; child.insert(0, NULL); }//�յĽڵ�
	BTNode(T e,BTNodePosi(T) lc=NULL, BTNodePosi(T) rc = NULL)//����һ���Թؼ���eΪ����b-��
	{
		parent = NULL;
		key.insert(0, e);
		child.insert(0, lc); child.insert(1,rc);
		if (lc) lc->parent = this;
		if (rc) rc->parent = this;
	}
};