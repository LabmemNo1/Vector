#ifndef VECTOR_H
#define VECTOR_H
typedef int Rank;//秩
#define DEFAULT_CAPACITY 3
template <typename T> class Vector //Vector模板类
{
protected:
	Rank _size; int _capacity; T* _elem;//规模 容量 数据区
	void copyForm(T const* A, Rank lo, Rank hi);//复制区间数组	
	void expand();//扩容函数
	void shrink();//缩容函数
	bool bubble(Rank lo, Rank hi);//扫描交换
	bool bubbleSort(Rank lo, Rank hi);//冒泡排序
	Rank max(Rank lo, Rank hi);//
	void selectionSort(Rank lo, Rank hi);//选择排序
	void merge(Rank lo, Rank mi, Rank hi);//归并算法
	void mergeSort(Rank lo, Rank hi);//归并排序
	Rand partiton(Rank lo, Rank hi);//轴点构造
	void quickSort(Rank lo, Rank hi);//快速排序
	void heapSort(Rank lo, Rank hi);//堆排序
public:
	//构造函数
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)//vector的底层构造还是由数组实现的
	{
		_elem = new T[_capacity = c];
		for (_size = 0; size < s; _elem[_size++] = v);
	}
	Vector(T const *A, Rank n) { copyFrom(A, 0, n); }//用一个数组的值来初始化,很常用的构造函数
	Vector(T const *A, Rank lo, Rank hi) { copyFrom(A,lo,hi); }//区间复制
	Vector(Vector<t> const& V) { copyFrom(V._elem, 0, V._size); }//向量的复制
	Vector(Vector<t> const& V, Rank lo, Rank hi) { copyForm(V._elem, lo, hi); }//区间
	//析构函数
	~Vector()
	{
		delete[]_elem;

	}
	//只读访问接口
	Rank size()const { return _size; }
	bool empty()const { return !_size; }
	int disordered() const;//判断向量是否已排序
	Rank find(T const& e) { return find(e, 0, e._size); }//无序向量整体查找
	Rank find(T const& e, Rank lo, Rank hi)const;//无序向量局部查找
	Rank search(T const& e)const//有序向量整体查找
	{
		return(0 >= _size) ? -1 : search(e, 0, _size);
	}
	Rank search(T const& e, Rank lo, Rank hi)const;//有序向量区间查找



	//可写访问接口
	T& operator[](Rank r)const;//重载下标运算符 可以像数组一样引用各元素
	Vector<T>&operator=(Vector<T> const&);//重载赋值运算符，便于直接克隆
	T remove(Rank r);//删除元素
	int remove(Rank lo, Rank hi);
	Rank insert(Rank r, T const& e);
	Rank insert(T const& e) { return insert(_size, e); }
	void sort(Rank lo, Rank hi);//排序
	void sort() { sort(0, _size); }
	void unsort(Rank lo, Rank hi);
	void unsort() { unsort(0, _size); }
	int deduplicate();//无序去重
	int uniquify();//有序去重  //高效的有序去重，无需调用remove函数，只需把后面向量的值往前移除即可
	//遍历
	void traverse(void(*visit)(T&));//使用函数指针
	template <typename VST> void traverse(VST& visit);//使用函数对象






};

























#endif // !VECTOR_H

template<typename T>
inline void Vector<T>::copyForm(T const * A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo < hi)
	{
		_elem[size++] = A[lo++];
	}
}

template<typename T>
inline void Vector<T>::expand()
{
	if (_size < _capacity) return;
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];//左移一位,容量翻倍
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];//复制原向量内容
	delete []oldElem;
}

template<typename T>
inline void Vector<T>::shrink()
{
	if (_capacity < DEFAULT_CAPACITY << 1) return;
	if (_size << 2 > _capacity) return;//25%为阈值
	T* oleElem = elem;
	_elem = new T[_capacity >>= 1;];//右移一位，容量减半
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[]oldElem;
}

template<typename T>
inline bool Vector<T>::bubbleSort(Rank lo, Rank hi)
{
	int n = hi - lo;
	int i = lo;
	for(bool flag=false;flag=!flag;n--)
		for (i;i<hi;i++)
		{
			if (_elem[i - 1] < _elem[i])
			{
				swap(_elem[i - 1], _elem[i]);
				flag = false;
			}
		}
	return true;
}

template<typename T>
inline int Vector<T>::disordered() const
{
	int n = 0;
	for (int i = 0; i < _size; i++)
		if (_elem[i - 1] > _elem[i]) n++;
	return n;
}

template<typename T>
inline Rank Vector<T>::find(T const & e, Rank lo, Rank hi) const
{
	while ((lo < hi--) && (e != _elem[hi]));
	return hi;
}

template<typename T>
inline Rank Vector<T>::search(T const & e, Rank lo, Rank hi) const
{
	return (rand() % 2) ? binSearch(_elem, e, lo, hi) : fibSearch(_elem, e, lo, hi);
}

template<typename T>
inline T & Vector<T>::operator[](Rank r) const
{
	return _elem[r];
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(Vector<T> const &V)//重载赋值运算符是因为向量内部含有动态分配的空间
{
	if (_elem) delete []_elem;
	copyFrom(V._elem, 0, _size);
	return *this;//返回当前对象的引用，以便链式赋值

}

template<typename T>
inline T Vector<T>::remove(Rank r)
{
	T e = _elem[r];
	remove(r, r + 1);
	return e;//返回被删除的元素
}

template<typename T>
inline int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi) return 0;
	while (hi < _size) _elem[lo++] = _elem[hi++];
	_size = lo;//lo已经加上_size个数，现在lo已经是数组的最后一个
	shrink();
	return hi - lo;//返回被删除元素的个数
}

template<typename T>
inline Rank Vector<T>::insert(Rank r, T const & e)
{
	expand();//有必要的话，扩容，防止溢出
	for (int i = _size; i > r; i--) _elem[i] = _elem[i - 1];//自后向前，顺次后移
	_elem[r] = e;
	_size++;
	return r;


}

template<typename T>
inline void Vector<T>::unsort(Rank lo, Rank hi)
{
	T* V = _elem + lo;//将_elem向量视作另一向量V[0,lo-hi]
	for (Rank i = lo - hi; i > 0; i--)
	{
		swap(V[i - 1], V[rand() % 10]);
	}
}

template<typename T>
inline int Vector<T>::deduplicate()//时间复杂度根据find和remove两个函数来，最坏情况n方复杂度
{
	int oldSize = _size;
	Rank i = 1;
	while (i < _size)
		(find(_elem[i], 0, i)) < 0 ? i++ : remove(i);
	return oldSize - _size;//向量规模变化量
}

template<typename T>
inline int Vector<T>::uniquify()//
{
	Rank i = 0, j = 0;
	while (++j < _size)
		if (_elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	_size = ++i;
	shrink();
	return j - i;//返回被删除的元素总数
}

template<typename T>
inline void Vector<T>::traverse(void(*visit)(T &))//用函数指针指定一个函数去对遍历的函数实行操作
{
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}

template<typename T>
template<typename VST>
inline void Vector<T>::traverse(VST& visit)
{
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}
