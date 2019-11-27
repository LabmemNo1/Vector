#pragma once
#include"Dictionary.h"
#include"BitMap.h"

template <typename K, typename V>//key,value
class Hashtable:public Dictionary<K,V>
{
	Entry<K, V>** ht;//桶数组，存放词条指针
	int M;//桶数组容量
	int N;//词条数量
	Bitmap* lazyRemoval;//懒惰删除标记
#define lazilyRemoved(x) (lazyRemoval->test(x))
#define markAsRemoved(x) (lazyRemoval->set(x))
protected:
	int probe4Hit(const K& k);//沿关键码k对应的查找链，找到第一个词条匹配的桶  闭散列 线性查找
	int probe4Free(const K& k);//沿关键码k对应的查找链，找到首个可用空桶  
	void rehash();//重散列算法：扩充桶数组，保证装填因子在警戒线以下
public:
	Hashtable(int c = 5);
	~Hashtable()
	{
		for (int i = 0; i < M; i++)//逐一检查各桶
		{
			if (ht[i]) release(ht[i]);
			release(ht);
			release(lazyRemoval);
		}
	}
	int size() const { return N; }// 当前的词条数目
	bool put(K, V);//插入（禁止雷同的词条，所以可能失败）
	V* get(K k);//读取
	bool remove(K k);//删除

};



int primeNLT(int c, int n, char* file) { //根据file文件中的记录，在[c, n)内取最小的素数
	Bitmap B(file, n); //file已经按位图格式，记录了n以内的所有素数，因此只要
	while (c < n) //从c开始，逐位地
		if (B.test(c)) c++; //测试，即可
		else return c; //返回首个发现的素数
	return c; //若没有这样的素数，返回n（实用中不能如此简化处理）
}

//插一句，使用双平方试探的话，M=4k+3最好
template<typename K, typename V>
inline Hashtable<K, V>::Hashtable(int c)  
{
	M = primeNLT(c, 1048576, "prime.txt");//不小于c的素数M
	N = 0; ht = new Entry<K, V>*[M];//开辟桶数组 初始装填因子为0
	memset(ht, 0, sizeof(Entry<K,V>)M);//初始化各桶
	lazyRemoval = new Bitmap(M);//懒惰删除标记比特图 哈希表就是一个集合
}

template<typename K, typename V>
inline V * Hashtable<K, V>::get(K k)
{
	int r = probe4Hit(k); return ht[r] ? &(ht[r]->value) : NULL;
	
}

template<typename K, typename V>
inline int Hashtable<K, V>::probe4Hit(const K & k)//线性试探
{
	int r = hashCode(k) % M;//采用除余法,从起始桶出发
	while ((ht[r] && (k != ht[r]->value)) || (!ht[r] && lazilyRemoved(r)))//这个while是如果桶非空值但值不是或者桶空但有懒惰删除标记
		r = (r + 1) % M;//除非遇到了没有懒惰删除标记的空桶或者命中目标
	return r;
}
template<typename K, typename V>
inline bool Hashtable<K, V>::remove(K k)
{
	int r = probe4Hit(k);//首先查找
	if (!ht[r]) return false;
	release(hr[r]);
	ht[r] = NULL;
	markAsRemoved(r);//设置懒惰删除标记，防止查找链中断
	N--;
	return true;
}
template <typename K,typename V>
bool Hashtable<K, V>::put(K k,V v)
{
	if (ht[probe4Hit(k)]) return false;//重复元素不必插入
	int r = probe4Free(k);//为新词条找一个空桶
	ht[r] = new Entry<K, V>(k, v); ++N;
	if (N * 2 > M) rehash();//如果装填因子大于50% 重散列
	return true;
} 
template <typename K,typename V>
int Hashtable<K, V>::probe4Free(const K&k)//这里也是线性试探，不过应该是双平方试探效果和效率都最好
{
	int r = hashCode(k) % M;
	while (ht[r]) r = (r + 1) % M;
	return r;
}
template <typename K,typename V>
void Hashtable<K, V>::rehash()
{
	int old_capacity = M; Entry<K, V>** old_ht = ht;
	M = primeNLT(2 * M, 1048576, "prime.txt");//加倍扩容
	release(lazyRemoval);
	lazyRemoval = new Bitmap(M);//新开一个
	for (int i = 0; i < old_capacity; i++)
		if (old_ht[i])
			put(old_ht[i]->key, old_ht[i]->value);
	release(old_ht);

}