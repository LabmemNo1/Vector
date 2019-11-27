#pragma once
//�����������������Ľڵ���������ݣ�
template <typename K, typename V>struct Entry
{
	K key; V value;
	Entry(K k = K(),V v=V()):key(k),value(v){}//���캯��
	Entry(Entry<K,V>& const e):key(e.key),value(e.value){}//�������캯��
	//���رȽ����е���
	bool operator<(Entry& const e) { return key < e.key; }
	bool operator>(Entry& const e) { return key > e.key; }
	bool operator==(Entry& const e) { return key == e.key; }
	bool operator!=(Entry& const e) { return key != e.key; }

};
