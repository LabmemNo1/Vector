#pragma once
#include"List.h"//��ListΪ����
template <typename T> class Queue :public List<T>
{
public://size empty�Ƚӿڿ�ֱ��ʹ��
	void enqueue(T const &e) { insertAsLast(e); }
	T& front() { return List<T>::first()->data; }
	T dequeue() { return remove(List<T>::first()); }
	

};