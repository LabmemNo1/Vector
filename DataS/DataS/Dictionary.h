#pragma once
#include"Entry.h"
template <typename K, typename V> struct Dictionary
{
	//���Դ��麯����ʽ����
	virtual int size() const = 0;//��������
	virtual bool put(K, V) = 0;//�������
	virtual V* get(K K) = 0;//��ȡ����
	virtual bool remove(K K) = 0;//ɾ������
	
};