#pragma once
//词条（二叉搜索树的节点包含的数据）
template <typename K, typename V>struct Entry
{
	K key; V value;
	Entry(K k = K(),V v=V()):key(k),value(v){}//构造函数
	Entry(Entry<K,V>& const e):key(e.key),value(e.value){}//拷贝构造函数
	//重载比较器判等器
	bool operator<(Entry& const e) { return key < e.key; }
	bool operator>(Entry& const e) { return key > e.key; }
	bool operator==(Entry& const e) { return key == e.key; }
	bool operator!=(Entry& const e) { return key != e.key; }

};
