#pragma once
//B-树
#include"Myvector.h"
#define BTNodePosi(T) BTNode<T>*


template <typename T> struct BTNode
{
	//成员:
	BTNodePosi(T) parent;//父节点
	Vector<T> key;//关键码向量
	Vector<BTNodePosi(T)> child;//孩子向量



	//构造函数 （BTNode只能作为根节点创建，初始时有0个关键码和一个空孩子指针）
	BTNode() { parent = NULL; child.insert(0, NULL); }//空的节点
	BTNode(T e,BTNodePosi(T) lc=NULL, BTNodePosi(T) rc = NULL)//构造一个以关键码e为根的b-树
	{
		parent = NULL;
		key.insert(0, e);
		child.insert(0, lc); child.insert(1,rc);
		if (lc) lc->parent = this;
		if (rc) rc->parent = this;
	}
};