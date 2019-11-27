#pragma once
//��ȫ�����ģ����
#pragma once
//�򻯶�����㷨��������ʵ�ֶ���ĺ�
#define  InHeap(n, i)      ( ( ( -1 ) < ( i ) ) && ( ( i ) < ( n ) ) ) //�ж�PQ[i]�Ƿ�Ϸ�
#define  Parent(i)         ( ( i - 1 ) >> 1 ) //PQ[i]�ĸ��ڵ㣨floor((i-1)/2)��i����������
#define  LastInternal(n)   Parent( n - 1 ) //���һ���ڲ��ڵ㣨��ĩ�ڵ�ĸ��ף�
#define  LChild(i)         ( 1 + ( ( i ) << 1 ) ) //PQ[i]������
#define  RChild(i)         ( ( 1 + ( i ) ) << 1 ) //PQ[i]���Һ���
#define  ParentValid(i)    ( 0 < i ) //�ж�PQ[i]�Ƿ��и���
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //�ж�PQ[i]�Ƿ���һ�����󣩺���
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //�ж�PQ[i]�Ƿ�����������
#define  Bigger(PQ, i, j)  ( lt( PQ[i], PQ[j] ) ? j : i ) //ȡ���ߣ���ʱǰ�����ȣ�
#define  ProperParent(PQ, n, i) /*���ӣ����ࣩ�����еĴ���*/ \
            ( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
            ( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
            ) \
            ) //���ʱ���ڵ����ȣ���˿ɱ��ⲻ��Ҫ�Ľ���


//���������Ľṹ�����ȼ����еĽӿ�
#include"Myvector.h"
#include"PQ.h"
template <typename T> class PQ_ComplHeap : public PQ<T>,public Vector<T>
	{
protected://�ڲ��ӿ�
	Rank percolateDown(Rank n, Rank i);//����
	Rank percolateUp(Rank i);//����
	void heapify(Rank n);//Floyd�����㷨
public://����ӿ�
	PQ_ComplHeap(){}//Ĭ�Ϲ���
	PQ_ComplHeap(T* A.Rank n) {Vector<T>::copyFrom(A, 0, n); heapify(n); }
	void insert(T e) { Vector<T>::inset(e); percolateUp(_size - 1); };//���뵽ĩβ��Ȼ��ִ������
	T getMax(){return _elem[0]};//�󶥶� ������Ԫ�أ�Ҳ�������ȼ���ߵ�Ԫ�ؼ���
	T delMax();




	};

	template<typename T>
	inline Rank PQ_ComplHeap<T>::percolateDown(Rank n, Rank i)
	{
		Rank j;
		while (i != (j = ProperParent(_elem, n, i)))//ֻҪi�����������������е������
		{
			swap(_elem[i], _elem[j]);
			i = j;
		}
	}

	template<typename T>
	inline Rank PQ_ComplHeap<T>::percolateUp(Rank i)
	{
		while (ParentValid(i))//ֻҪi���и��׾�ѭ��������i���ǶѶ����˳�ѭ��
		{
			Rank j = Parent(i);
			if (_elem[j] > _elem[i]) break;//����������ȼ���i����  ������ѭ��
			swap(_elem[i], _elem[j]); i = j;//���򽻻���ֵ ������ 
		}
		return i;
	}

	

	template<typename T>
	inline T PQ_ComplHeap<T>::delMax()
	{
		T maxElem = _elem[0];//����Ҫɾ���ĶѶ�
		_elem[0] = _elem[--_size];//��ĩ��������
		percolateDown(_size, 0);//���¶Ѷ�ʵʩ����
		return maxElem;
		
	}
template<typename T>
	inline void PQ_ComplHeap<T>::heapify(Rank n)//���¶��ϵ����˽���
	{
		for (int i = LastInternal(n); InHeap(n, i); i--)
		{
			percolateDown(n, i);//���˸��ڲ��ڵ�
			//Ч�ʸߵ�ԭ���ǣ����˽���ѵĻ����߶�Խ�ߣ�����Խ�٣�������ȫ������
			//�У��߶ȸߵ�ԶԶ���ڸ߶ȵ͵ĵĽڵ�
		}
	}
template<typename T>
	inline void Vector<T>::heapSort(Rank lo, Rank hi)
	{
		PQ_ComplHeap<T> H(_elem + lo, hi - lo);//�Դ��������佨��һ����ȫ�����
		while (!H.empty())//ֱ��������Ķ���ѱ��
		{
			_elem[--hi] = H.delMax();//�����Ľ��Ѷ�Ԫ����ĩԪ�ضһ�������
		}
	}