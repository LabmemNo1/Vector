#pragma once
//优先级队列接口
template <typename T> struct PQ
{
	virtual void insert(T) = 0;//按照比较器确定的优先级次序插入词条
	virtual T getMax() = 0;//取出优先级最高的词条
	virtual T delMax() = 0;//删除优先级最高的词条
};