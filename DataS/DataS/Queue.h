#pragma once
#include"List.h"//以List为基类
template <typename T> class Queue :public List<T>
{
public://size empty等接口可直接使用
	void enqueue(T const &e) { insertAsLast(e); }
	T& front() { return List<T>::first()->data; }
	T dequeue() { return remove(List<T>::first()); }
	

};