#pragma once
#include"Entry.h"
template <typename K, typename V> struct Dictionary
{
	//均以纯虚函数形式给出
	virtual int size() const = 0;//词条总数
	virtual bool put(K, V) = 0;//插入词条
	virtual V* get(K K) = 0;//读取词条
	virtual bool remove(K K) = 0;//删除词条
	
};