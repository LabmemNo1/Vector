#pragma once
#include"Dictionary.h"
#include"BitMap.h"

template <typename K, typename V>//key,value
class Hashtable:public Dictionary<K,V>
{
	Entry<K, V>** ht;//Ͱ���飬��Ŵ���ָ��
	int M;//Ͱ��������
	int N;//��������
	Bitmap* lazyRemoval;//����ɾ�����
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))
protected:
	int probe4Hit(const K& k);//�عؼ���k��Ӧ�Ĳ��������ҵ���һ������ƥ���Ͱ  ��ɢ�� ���Բ���
	int probe4Free(const K& k);//�عؼ���k��Ӧ�Ĳ��������ҵ��׸����ÿ�Ͱ  
	void rehash();//��ɢ���㷨������Ͱ���飬��֤װ�������ھ���������
public:
	Hashtable(int c = 5);
	~Hashtable()
	{
		for (int i = 0; i < M; i++)//��һ����Ͱ
		{
			if (ht[i]) release(ht[i]);
			release(ht);
			release(lazyRemoval);
		}
	}
	int size() const { return N; }// ��ǰ�Ĵ�����Ŀ
	bool put(K, V);//���루��ֹ��ͬ�Ĵ��������Կ���ʧ�ܣ�
	V* get(K k);//��ȡ
	bool remove(K k);//ɾ��

};



int primeNLT(int c, int n, char* file) { //����file�ļ��еļ�¼����[c, n)��ȡ��С������
	Bitmap B(file, n); //file�Ѿ���λͼ��ʽ����¼��n���ڵ��������������ֻҪ
	while (c < n) //��c��ʼ����λ��
		if (B.test(c)) c++; //���ԣ�����
		else return c; //�����׸����ֵ�����
	return c; //��û������������������n��ʵ���в�����˼򻯴���
}

//��һ�䣬ʹ��˫ƽ����̽�Ļ���M=4k+3���
template<typename K, typename V>
inline Hashtable<K, V>::Hashtable(int c)  
{
	M = primeNLT(c, 1048576, "prime.txt");//��С��c������M
	N = 0; ht = new Entry<K, V>*[M];//����Ͱ���� ��ʼװ������Ϊ0
	memset(ht, 0, sizeof(Entry<K,V>)M);//��ʼ����Ͱ
	lazyRemoval = new Bitmap(M);//����ɾ����Ǳ���ͼ ��ϣ�����һ������
}

template<typename K, typename V>
inline V * Hashtable<K, V>::get(K k)
{
	int r = probe4Hit(k); return ht[r] ? &(ht[r]->value) : NULL;
	
}

template<typename K, typename V>
inline int Hashtable<K, V>::probe4Hit(const K & k)//������̽
{
	int r = hashCode(k) % M;//���ó��෨,����ʼͰ����
	while ((ht[r] && (k != ht[r]->value)) || (!ht[r] && lazilyRemoved(r)))//���while�����Ͱ�ǿ�ֵ��ֵ���ǻ���Ͱ�յ�������ɾ�����
		r = (r + 1) % M;//����������û������ɾ����ǵĿ�Ͱ��������Ŀ��
	return r;
}
template<typename K, typename V>
inline bool Hashtable<K, V>::remove(K k)
{
	int r = probe4Hit(k);//���Ȳ���
	if (!ht[r]) return false;
	release(hr[r]);
	ht[r] = NULL;
	markAsRemoved(r);//��������ɾ����ǣ���ֹ�������ж�
	N--;
	return true;
}
template <typename K,typename V>
bool Hashtable<K, V>::put(K k,V v)
{
	if (ht[probe4Hit(k)]) return false;//�ظ�Ԫ�ز��ز���
	int r = probe4Free(k);//Ϊ�´�����һ����Ͱ
	ht[r] = new Entry<K, V>(k, v); ++N;
	if (N * 2 > M) rehash();//���װ�����Ӵ���50% ��ɢ��
	return true;
} 
template <typename K,typename V>
int Hashtable<K, V>::probe4Free(const K&k)//����Ҳ��������̽������Ӧ����˫ƽ����̽Ч����Ч�ʶ����
{
	int r = hashCode(k) % M;
	while (ht[r]) r = (r + 1) % M;
	return r;
}
template <typename K,typename V>
void Hashtable<K, V>::rehash()
{
	int old_capacity = M; Entry<K, V>** old_ht = ht;
	M = primeNLT(2 * M, 1048576, "prime.txt");//�ӱ�����
	release(lazyRemoval);
	lazyRemoval = new Bitmap(M);//�¿�һ��
	for (int i = 0; i < old_capacity; i++)
		if (old_ht[i])
			put(old_ht[i]->key, old_ht[i]->value);
	release(old_ht);

}