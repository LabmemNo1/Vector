#pragma once
#include"ListNode.h"


template <typename T> class List
{
private:
	int _size; ListNodePosi(T) header; ListNodePosi(T) trailer;//��ģ ͷ�ڱ� β�ڱ�

protected:
	//�б���ʱ��ʼ��
	void init();
	
	
	int clear();//�������ڵ�
	
	void copyNodes(ListNodePosi(T) p, int n)//�����б��λ��P���N��
	{
		init();
		while (n--)
		{
			insertAsLast(p->data);
			p = p->succ;
		}
	}
	void merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m)//�鲢   �б�Ĺ鲢���Ե�����һ���б�����ɣ�����Ҫ�������������ߵı�ǰ��󣬲��ܣ������ߵı�ǰ��С�����뵽ǰ��ڵ�֮ǰ
	{
		ListNodePosi(T) pp = p->pred;//����ͷ�ڵ�
		while (m > 0)
		{
			if(n>0&&(p->data)<=(q->data)) 
			{
				if(q==(p=p->succ))//������������  ������������
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
	void mergeSort(ListNodePosi(T)& p, int n)//�ӽڵ�p��ʼ��n��鲢����
	{
		if (n < 2) return;
		int m = n >> 1;
		ListNodePosi(T) q = p; for (int i = 0; i < m; i++) q = q->succ;//�����б� q�Ƕ�·�鲢��ߵ��б�
		mergeSort(p, m); mergeSort(q, m - 1);
		merge(p, m, *this, q, m - 1);
	}
	void selectionSort(ListNodePosi(T) p, int n)//��p�ڵ㿪ʼ��n��ѡ������
	{
		ListNodePosi(T) head = p  -> pred; ListNodePosi(T) tail = p;
		for (int i = 0; i < n; i++) tail = tail->succ;
		while (n > 1) {
			insertB(tail, remove(selectMax(head->succ, n)));
				tail = tail->pred;
			n--;
		}
	}
	void insertionSort(ListNodePosi(T) p, int n)//��P�ڵ㿪ʼ��n���������
	{
		for (int r = 0; r < n; r++)
		{
			insertA(search(p->data, r, p), p->data);//��p��ǰr������������p����ֵ�ĵ�һ�Ȼ��search������һ��Ľڵ㣬��p����ֵ���룬Ȼ��pָ����һ�ɾ��֮ǰ��p
			p->succ;
			remove(p->pred);
		}
	}
public:
	//���캯��
	List() { init(); }
	
	//Ĭ�Ϲ���
	List(List<T> const &L);//���帴���б�L
	List(List<T> const &L, Rank r, int n);//���ƴ�L��r��ʼ��n��
	List(ListNodePosi(T) p, int n);//����L��λ��p��ʼ��n��
	//��������
	~List()
	{
		clear();
		delete header;
		delete trailer;
	}

	T& operator[](Rank r) const;//�����±��������֧��ѭ�ȷ��ʣ�����Ч�ʵ�
	//ֻ�����ʽӿ�
	Rank size()const { return _size; }
	bool empty() const { return _size <= 0; }
	
	ListNodePosi(T) first()const { return header->succ; }
	ListNodePosi(T) last()const { return trailer->pred; }
	bool valid(ListNodePosi(T) p)//�ж�λ��p�Ƿ����Ϸ�
	{
		return p && (header != p) && (trailer) != p;
	}
	int disordered()const;//�ж��б��Ƿ��Ѿ�����
	ListNodePosi(T) find(T const &e)const//�����б����
	{
		return find(e, _size, trailer);
	}
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T) p)const//�����б��������
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
	ListNodePosi(T) search(T const &e, int n, ListNodePosi(T) p)const//�����б�������� �ڽڵ�p��n����ǰ���У�Ѱ�Ҳ�����e�������
	{
		while (0<n--)
		{
			if ((p = p->pred)->data <= e) break;
		}
		return p;
	}
	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n)//��P�����n-1�����ҵ������
	{
		ListNodePosi(T) Max = p;
		for (ListNodePosi(T) cur = p; n > 1; n--)
		{
			if (((cur = cur->succ)->data) >= (Max->data))
				Max = cur;
		}
		return Max;
	}
	ListNodePosi(T) selectMax() { return selectMax(header->succ, _size); }//�������
	//��д���ʽӿ�
	ListNodePosi(T) insertAsFirst(T const &e)//��e�����׽ڵ����
	{
		++_size; return header->insertAsSucc(e);
	}
	ListNodePosi(T) insertAsLast(T const &e)//��e����ĩ�ڵ����
	{
		++_size; return trailer->insertAsPred(e);
	}
	ListNodePosi(T) insertA(ListNodePosi(T) p, T const &e)//��e����p�ĺ�̲���; after
	{
		++_size; return p->insertAsSucc(e);
	}
	ListNodePosi(T) insertB(ListNodePosi(T) p, T const &e)//��e����p��ǰ������ before
	{
		++_size; return p->insertAsPred(e);
	}
	T remove(ListNodePosi(T) p)//ɾ��λ��p���Ľڵ㣬���ر�ɾ���ڵ�
	{
		T e = p->data;
		p->pred->succ = p->succ;
		p->succ->pred = p->pred;
		delete p;
		_size--;
		return e;

	}
	void merge(List<T> &L) { merge(first(), size, L, L.first(), L._size); }//ȫ�б�鲢
	void sort(ListNodePosi(T) p, int n)//�б���������
	{
		switch (rand() % 3)
		{
		case 1:insertionSort(p, n); break;
		case 2:selectionSort(p, n); break;
		default:mergeSort(p, n); break;
		}
	}
	void sort() { return sort(header->succ, _size); }//�б���������
	int deduplicate()//����ȥ��
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
	int uniquify()//����ȥ��
	{
		if (_size < 2) return;
		int oldsize = _size;
		ListNodePosi(T) p = first();
		ListNodePosi(T) q ;
		while ((trailer != (q=p->succ)))
		{
			if (q->data != p->data)
				p = q;
			else remove(q);//��Ϊ�б��remove����ʱ�临�Ӷ�Ϊo1�����Բ�������


		}
		return oldsize - _size;
	}
	void reverse();//ǰ����

	//����
	void travese(void(*visit)(T&))//����ָ�����visit��ֻ����ֲ��޸�
	{
		for (ListNodePosi(T) p = header->succ; p != trailer; p->succ)
			visit(p->data);
	}


	template <typename VST>//������
	void traverse(VST&)//��������������ƣ���ȫ�����޸�
	{
		for (ListNodePosi(T) p = header->succ; p != trailer; p->succ)
			visit(p->data);
	}





};



template<typename T>
inline void List<T>::init()
{
	header = new ListNode<T>;//����ͷ�ڱ��ڵ�
	trailer = new ListNode<T>;//����β�ڱ��ڵ�
	header->succ = trailer; header->pred = nullptr;//����
	trailer->pred = header; trailer->succ = nullptr;//����
	_size = 0;//��¼��ģ
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

