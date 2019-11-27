#pragma once
#include"ListNode.h"


template <typename T> class List
{
private:
	int _size; ListNodePosi(T) header; ListNodePosi(T) trailer;//规模 头哨兵 尾哨兵

protected:
	//列表创建时初始化
	void init();
	
	
	int clear();//清除链表节点
	
	void copyNodes(ListNodePosi(T) p, int n)//复制列表从位置P起的N项
	{
		init();
		while (n--)
		{
			insertAsLast(p->data);
			p = p->succ;
		}
	}
	void merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m)//归并   列表的归并可以当成在一个列表中完成，不需要第三个，如果后边的比前面大，不管，如果后边的比前边小，插入到前面节点之前
	{
		ListNodePosi(T) pp = p->pred;//保存头节点
		while (m > 0)
		{
			if(n>0&&(p->data)<=(q->data)) 
			{
				if(q==(p=p->succ))//如果这两个相等  跳出就完事了
				break;
				n--;
				}
			else
			{
				insertB(p,L.remove((q=q->succ)->pred));m--;
			}
		

		}
		p = pp->succ;
	}
	void mergeSort(ListNodePosi(T)& p, int n)//从节点p开始的n项归并排序
	{
		if (n < 2) return;
		int m = n >> 1;
		ListNodePosi(T) q = p; for (int i = 0; i < m; i++) q = q->succ;//均分列表 q是二路归并后边的列表
		mergeSort(p, m); mergeSort(q, m - 1);
		merge(p, m, *this, q, m - 1);
	}
	void selectionSort(ListNodePosi(T) p, int n)//从p节点开始的n项选择排序
	{
		ListNodePosi(T) head = p  -> pred; ListNodePosi(T) tail = p;
		for (int i = 0; i < n; i++) tail = tail->succ;
		while (n > 1) {
			insertB(tail, remove(selectMax(head->succ, n)));
				tail = tail->pred;
			n--;
		}
	}
	void insertionSort(ListNodePosi(T) p, int n)//从P节点开始的n项插入排序
	{
		for (int r = 0; r < n; r++)
		{
			insertA(search(p->data, r, p), p->data);//在p的前r项搜索不大于p的数值的第一项，然后search返回那一项的节点，把p的数值插入，然后p指向下一项，删除之前的p
			p->succ;
			remove(p->pred);
		}
	}
public:
	//构造函数
	List() { init(); }
	
	//默认构造
	List(List<T> const &L);//整体复制列表L
	List(List<T> const &L, Rank r, int n);//复制从L从r开始的n项
	List(ListNodePosi(T) p, int n);//复制L从位置p开始的n项
	//析构函数
	~List()
	{
		clear();
		delete header;
		delete trailer;
	}

	T& operator[](Rank r) const;//重载下标运算符，支持循秩访问，但是效率低
	//只读访问接口
	Rank size()const { return _size; }
	bool empty() const { return _size <= 0; }
	
	ListNodePosi(T) first()const { return header->succ; }
	ListNodePosi(T) last()const { return trailer->pred; }
	bool valid(ListNodePosi(T) p)//判断位置p是否对外合法
	{
		return p && (header != p) && (trailer) != p;
	}
	int disordered()const;//判断列表是否已经排序
	ListNodePosi(T) find(T const &e)const//无序列表查找
	{
		return find(e, _size, trailer);
	}
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p)const//无序列表区间查找
	{
		while (0 < n--)
		{
			if (e == (p->pred)->data) return p;
		}
		return nullptr;
	}
	ListNodePosi(T) search(T const &e)const
	{
		return search(e, _size, trailer);
	}
	ListNodePosi(T) search(T const &e, int n, ListNodePosi(T) p)const//有序列表区间查找 在节点p的n个真前驱中，寻找不大于e的最后者
	{
		while (0<n--)
		{
			if ((p = p->pred)->data <= e) break;
		}
		return p;
	}
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n)//在P后面的n-1项中找到最大者
	{
		ListNodePosi(T) Max = p;
		for (ListNodePosi(T) cur = p; n > 1; n--)
		{
			if (((cur = cur->succ)->data) >= (Max->data))
				Max = cur;
		}
		return Max;
	}
	ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); }//整体最大
	//可写访问接口
	ListNodePosi(T) insertAsFirst(T const &e)//把e当做首节点插入
	{
		++_size; return header->insertAsSucc(e);
	}
	ListNodePosi(T) insertAsLast(T const &e)//把e当做末节点插入
	{
		++_size; return trailer->insertAsPred(e);
	}
	ListNodePosi(T) insertA(ListNodePosi(T) p, T const &e)//把e当做p的后继插入; after
	{
		++_size; return p->insertAsSucc(e);
	}
	ListNodePosi(T) insertB(ListNodePosi(T) p, T const &e)//把e当做p的前驱插入 before
	{
		++_size; return p->insertAsPred(e);
	}
	T remove(ListNodePosi(T) p)//删除位置p处的节点，返回被删除节点
	{
		T e = p->data;
		p->pred->succ = p->succ;
		p->succ->pred = p->pred;
		delete p;
		_size--;
		return e;

	}
	void merge(List<T> &L) { merge(first(), size, L, L.first(), L._size); }//全列表归并
	void sort(ListNodePosi(T) p, int n)//列表区间排序
	{
		switch (rand() % 3)
		{
		case 1:insertionSort(p, n); break;
		case 2:selectionSort(p, n); break;
		default:mergeSort(p, n); break;
		}
	}
	void sort() { return sort(header->succ, _size); }//列表整体排序
	int deduplicate()//无序去重
	{
		if (_size < 2) return;
		int oldsize = _size; Rank r = 0;
		ListNodePosi(T) p = header;
		while (trailer != (p = p->succ))
		{
			ListNodePosi(T) q = find(p->data, r, p);
			q ? remove(q) : r++;
		}
		return oldsize - _size;

	}
	int uniquify()//有序去重
	{
		if (_size < 2) return;
		int oldsize = _size;
		ListNodePosi(T) p = first();
		ListNodePosi(T) q ;
		while ((trailer != (q=p->succ)))
		{
			if (q->data != p->data)
				p = q;
			else remove(q);//因为列表的remove操作时间复杂度为o1，所以不像向量


		}
		return oldsize - _size;
	}
	void reverse();//前后倒置

	//遍历
	void travese(void(*visit)(T&))//函数指针借助visit，只读或局部修改
	{
		for (ListNodePosi(T) p = header->succ; p != trailer; p->succ)
			visit(p->data);
	}


	template <typename VST>//操作器
	void traverse(VST&)//借助函数对象机制，可全局性修改
	{
		for (ListNodePosi(T) p = header->succ; p != trailer; p->succ)
			visit(p->data);
	}





};



template<typename T>
inline void List<T>::init()
{
	header = new ListNode<T>;//创建头哨兵节点
	trailer = new ListNode<T>;//创建尾哨兵节点
	header->succ = trailer; header->pred = nullptr;//互联
	trailer->pred = header; trailer->succ = nullptr;//互联
	_size = 0;//记录规模
}

template<typename T>
inline int List<T>::clear()
{
	int oldsize = _size;
	while (0 < _size--) remove(header->succ);
	return oldsize;
}

template <typename T>
inline T& List<T>::operator[](Rank r)const
{
	ListNodePosi(T) p = first();
	while (r-- > 0 )p->succ;
	return p->data;

}

