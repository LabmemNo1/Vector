#ifndef VECTOR_H
#define VECTOR_H
typedef int Rank;//��
#define DEFAULT_CAPACITY 3
template <typename T> class Vector //Vectorģ����
{
protected:
	Rank _size; int _capacity; T* _elem;//��ģ ���� ������
	void copyForm(T const* A, Rank lo, Rank hi);//������������	
	void expand();//���ݺ���
	void shrink();//���ݺ���
	bool bubble(Rank lo, Rank hi);//ɨ�轻��
	bool bubbleSort(Rank lo, Rank hi);//ð������
	Rank max(Rank lo, Rank hi);//
	void selectionSort(Rank lo, Rank hi);//ѡ������
	void merge(Rank lo, Rank mi, Rank hi);//�鲢�㷨
	void mergeSort(Rank lo, Rank hi);//�鲢����
	Rand partiton(Rank lo, Rank hi);//��㹹��
	void quickSort(Rank lo, Rank hi);//��������
	void heapSort(Rank lo, Rank hi);//������
public:
	//���캯��
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)//vector�ĵײ㹹�컹��������ʵ�ֵ�
	{
		_elem = new T[_capacity = c];
		for (_size = 0; size < s; _elem[_size++] = v);
	}
	Vector(T const *A, Rank n) { copyFrom(A, 0, n); }//��һ�������ֵ����ʼ��,�ܳ��õĹ��캯��
	Vector(T const *A, Rank lo, Rank hi) { copyFrom(A,lo,hi); }//���临��
	Vector(Vector<t> const& V) { copyFrom(V._elem, 0, V._size); }//�����ĸ���
	Vector(Vector<t> const& V, Rank lo, Rank hi) { copyForm(V._elem, lo, hi); }//����
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
	T* oleElem = elem;
	_elem = new T[_capacity >>= 1;];//����һλ����������
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
