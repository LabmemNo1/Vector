#ifndef VECTOR_H
#define VECTOR_H
#include"Fib.h"
typedef int Rank;//��
#define DEFAULT_CAPACITY 3
template <typename T> class Vector //Vectorģ����
{
public:
	Rank _size; int _capacity; T* _elem;//��ģ ���� ������
	void copyForm(T const* A, Rank lo, Rank hi);//������������	
	void expand();//���ݺ���
	void shrink();//���ݺ���
	Rank bubble(Rank lo, Rank hi);//ɨ�轻��
	void bubbleSort(Rank lo, Rank hi);//ð������
	Rank max(Rank lo, Rank hi);//
	void selectionSort(Rank lo, Rank hi);//ѡ������
	void merge(Rank lo, Rank mi, Rank hi);//�鲢�㷨
	void mergeSort(Rank lo, Rank hi);//�鲢����
	Rank partiton(Rank lo, Rank hi);//��㹹��
	void quickSort(Rank lo, Rank hi);//��������
	void heapSort(Rank lo, Rank hi);//������
public:
	//���캯��
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)//vector�ĵײ㹹�컹��������ʵ�ֵ�
	{
		_elem = new T[_capacity = c];
		for (_size = 0; _size < s; _elem[_size++] = v);
	}
	Vector(T const *A, Rank n) { copyFrom(A, 0, n); }//��һ�������ֵ����ʼ��,�ܳ��õĹ��캯��
	Vector(T const *A, Rank lo, Rank hi) { copyFrom(A,lo,hi); }//���临��
	Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); }//�����ĸ���
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copyForm(V._elem, lo, hi); }//����
	//��������
	~Vector()
	{
		delete[]_elem;

	}
	//ֻ�����ʽӿ�
	Rank size()const { return _size; }
	bool empty()const { return !_size; }
	int disordered() const;//�ж������Ƿ�������
	Rank find(T const& e) { return find(e, 0, e._size); }//���������������
	Rank find(T const& e, Rank lo, Rank hi)const;//���������ֲ�����
	Rank search(T const& e)const//���������������
	{
		return(0 >= _size) ? -1 : search(e, 0, _size);
	}
	Rank search(T const& e, Rank lo, Rank hi)const;//���������������
	static Rank binSearch(T* A, T const& e, Rank lo, Rank hi);
	static Rank fibSearch(T* A, T const& e, Rank lo, Rank hi);


	//��д���ʽӿ�
	T& operator[](Rank r)const;//�����±������ ����������һ�����ø�Ԫ��
	Vector<T>&operator=(Vector<T> const&);//���ظ�ֵ�����������ֱ�ӿ�¡
	T remove(Rank r);//ɾ��Ԫ��
	int remove(Rank lo, Rank hi);
	Rank insert(Rank r, T const& e);
	Rank insert(T const& e) { return insert(_size, e); }
	void sort(Rank lo, Rank hi);//����
	void sort() { sort(0, _size); }
	void unsort(Rank lo, Rank hi);
	void unsort() { unsort(0, _size); }
	int deduplicate();//����ȥ��
	int uniquify();//����ȥ��  //��Ч������ȥ�أ��������remove������ֻ��Ѻ���������ֵ��ǰ�Ƴ�����
	//����
	void traverse(void(*visit)(T&));//ʹ�ú���ָ��
	template <typename VST> void traverse(VST& visit);//ʹ�ú�������






};

























 // !VECTOR_H

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
	_elem = new T[_capacity <<= 1];//����һλ,��������
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];//����ԭ��������
	delete []oldElem;
}

template<typename T>
inline void Vector<T>::shrink()
{
	if (_capacity < DEFAULT_CAPACITY << 1) return;
	if (_size << 2 > _capacity) return;//25%Ϊ��ֵ
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];//����һλ����������
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[]oldElem;
}

template<typename T>
inline Rank Vector<T>::bubble(Rank lo, Rank hi)
{
	Rank last = lo;
	while (++lo < hi)
	{
		if (_elem[lo - 1] > _elem[lo])
		{
			
			swap(_elem[lo - 1], _elem[lo]);
			last = lo;
		}
	}
	return last;
}

template<typename T>
inline void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
	while (lo < (hi = bubble(lo, hi)));
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
inline static Rank Vector<T>::binSearch(T *A, T const & e, Rank lo, Rank hi)
{
	//�汾A ����֧����������ã�Ȼ�������µĸ��ӶȲ���
	/*while (lo < hi)
	{
		Rank mi = (lo + hi) >> 1;
		if (e < A[mi]) hi = mi;
		else if (A[mi] < e) lo = mi + 1;
		else return mi;

	}
	return -1;*/
	//�汾B ����֧�������ж��е㣬ÿ�η�ֻ֧�Ƚ�һ��
	/*while (1 < hi - lo)
	{
		mid = (hi + lo) >> 1;
		(e < A[mid]) ? hi = mid : lo = mid;
	}
	return (e == A[lo]) ? lo : -1;*/
	//�汾C  ���ص���������
	while (lo < hi)
	{
		Rank mi = (lo + hi) << 1;
		(e < A[mi]) ? hi = mi : lo = mi + 1;//���߶��ǿ�����
	}
	return --lo;
}

template<typename T>
inline Rank Vector<T>::fibSearch(T * A, T const & e, Rank lo, Rank hi)
{
	Fib fib(hi - lo);
	while (lo < hi)
	{
		while (hi - lo < fib.get()) fib.prev();
		Rank mi = lo + fib.get() - 1;
		if (e < A[mi]) hi = mi;
		else if (A[mi] < e) lo = mi + 1;
		else return mi;

	}
	return -1;
}

template<typename T>
inline T & Vector<T>::operator[](Rank r) const
{
	return _elem[r];
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(Vector<T> const &V)//���ظ�ֵ���������Ϊ�����ڲ����ж�̬����Ŀռ�
{
	if (_elem) delete []_elem;
	copyFrom(V._elem, 0, _size);
	return *this;//���ص�ǰ��������ã��Ա���ʽ��ֵ

}

template<typename T>
inline T Vector<T>::remove(Rank r)
{
	T e = _elem[r];
	remove(r, r + 1);
	return e;//���ر�ɾ����Ԫ��
}

template<typename T>
inline int Vector<T>::remove(Rank lo, Rank hi)
{
	if (lo == hi) return 0;
	while (hi < _size) _elem[lo++] = _elem[hi++];
	_size = lo;//lo�Ѿ�����_size����������lo�Ѿ�����������һ��
	shrink();
	return hi - lo;//���ر�ɾ��Ԫ�صĸ���
}

template<typename T>
inline Rank Vector<T>::insert(Rank r, T const & e)
{
	expand();//�б�Ҫ�Ļ������ݣ���ֹ���
	for (int i = _size; i > r; i--) _elem[i] = _elem[i - 1];//�Ժ���ǰ��˳�κ���
	_elem[r] = e;
	_size++;
	return r;


}

template<typename T>
inline void Vector<T>::sort(Rank lo, Rank hi)
{
	switch (rand() % 5)
		case 1:bubbleSort(lo, hi); break;
		case 2:selectionSort(lo, hi); break;
		case 3:mergeSort(lo, hi); break;
		case 4:heapSort(lo, hi); break;
		default:quickSort(lo, hi); break;
}

template<typename T>
inline void Vector<T>::unsort(Rank lo, Rank hi)
{
	T* V = _elem + lo;//��_elem����������һ����V[0,lo-hi]
	for (Rank i = lo - hi; i > 0; i--)
	{
		swap(V[i - 1], V[rand() % 10]);
	}
}

template<typename T>
inline int Vector<T>::deduplicate()//ʱ�临�Ӷȸ���find��remove����������������n�����Ӷ�
{
	int oldSize = _size;
	Rank i = 1;
	while (i < _size)
		(find(_elem[i], 0, i)) < 0 ? i++ : remove(i);
	return oldSize - _size;//������ģ�仯��
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
	return j - i;//���ر�ɾ����Ԫ������
}

template<typename T>
inline void Vector<T>::traverse(void(*visit)(T &))//�ú���ָ��ָ��һ������ȥ�Ա����ĺ���ʵ�в���
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

template<typename T>
inline void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	T* A = _elem + lo; //�ϲ��������
	int lb = mi - lo; T* B = new T[lb];//ǰ��������_elem[lo,mi)Ԫ��һ��������һ��������Ķ�̬����
	for (Rank i = 0; i < lb; B[i] = A[i++]);//����ǰ������
	int lc = hi - mi; T* C = _elem+mi;//��������_elem[mi,hi) ָ�����_elem��ָ��
	for (Rank i = 0, j = 0, k = 0; (j < lb )|| (k < lc);)//���forѭ��д���е��ƣ����Ǿ���һ���Աȣ������������Ԫ���ĸ�Ԫ��С����A���
		//��ߵ�(j < lb )|| (k < lc)��˼�ǣ�ֻҪ��һ�������ﻹ��Ԫ�ء��Ͳ�ֹͣѭ��
	{
		if ((j < lb) && (k >= lc || B[j] <= C[k])) A[i++] = B[j++];
		if ((k < lc) && (j >= lb || C[k] < B[j])) A[i++] = C[k++];
	}
	delete[]B;//�������ͷ�new��B
}

template<typename T>
inline void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if (hi - lo < 2) return;
	int mi = (lo + hi) >> 1;
	mergeSort(lo, mi); mergeSort(mi, hi);
	merge(lo, mi, hi);
	
}





//template <typename T>   
//void Vector<T>::merge(Rank lo, Ran mi, Rank hi)
//{
//	T* A = _elem + lo;
//	int b = mi - lo; T* B = new T[lb];
//	int c = hi - mi; T* C = _elem + mi;
//	for (Rank i = 0; i < lb; B[i] = A[i++]);
//	for (Rank i = 0, j = 0, k = 0; (j < lb || k < lc))
//	{
//		if ((j < lb) && (k >= lc || (B[j] <= C[k]))) A[i++] = B[j++];
//	}
//}
#endif