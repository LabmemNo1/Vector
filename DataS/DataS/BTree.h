#pragma once
#include"BTNode.h"
template <typename T> class BTree
{
protected:
	int _size;//��ŵĹؼ�������
	int _order;//B-���Ľ״Σ�����Ϊ3��   ����ʱָ����һ�㲻���޸�
	BTNodePosi(T) _root;//���ڵ�
	BTNodePosi(T) _hot;//BTree::search�����ʵķǿսڵ㣨�������գ�
	void solveOverflow(BTNodePosi(T) v)//����������֮��ķ��Ѵ���
	{
		if (_order >= v->child.size()) return;//�ݹ�� �״δ��ڵ��ڷ�֧���� ˵��û������
		Rank s = _order / 2;//��� ����ʱ_order=key.size()=child.size()-1��
		BTNodePosi(T) u = new BTNode<T>();//ע��b���ڵ㹹�캯��  ��һ���յĺ���
		for (Rank j = 0; j < _order - s - 1; j++)//v�Ҳ�_order-s-1�����Ӻ͹ؼ�����ѵ��Ҳ�ڵ�u
		{
			u->child.insert(j, v->child.remove(s + 1));//s���м���� ���+1�Ƴ����ұ߻Ჹ������һֱ��s+1�Ƶ�u�u���Ҳ�ڵ�
			u->key.insert(j, v->key.remove(s + 1));
		}
		u->child[_order - s - 1] = v->child.remove(s + 1);//�ƶ�v��ҵĺ���
		if (u->child[0])//���u�ĺ����Ƿǿ�
			for (Rank j = 0; j < _order - s; j++)//�����ǵĸ��ڵ�ͳһ
				u->child[j]->parent = u;
		BTNodePosi(T) p = v->parent;//v��ǰ���ڵ�p
		if (!p) { _root = p = new BTNode<T>(); p->child[0] = v; v->parent = p; }//���p������ ˵��v֮ǰ�Ǹ��ڵ� ����һ���¸��ڵ� p�����Ӿ������С��v
		Rank r = 1 + p->key.search(v->key[0]);//p��ָ��uָ�����  ����ָ��Ҫ�� Ҫ�ڵ����С �ұߴ� ȥ�ҵ���� Ȼ��+1
		p->key.insert(r, v->key.remove(s));//���Ĺؼ���������
		p->child.insert(r + 1, u); u->parent = p;//�´�����u�ڵ㣨�ҽڵ㣩��p����
		solveOverflow(p);//����һ�� ���б�Ҫ ��������

	}
	void solveUnderflow(BTNodePosi(T) v)//��ɾ��������֮��ĺϲ�����
	{
		if ((_order + 1) / 2 <= v->child.size()) return;//�ݹ�� ��ǰ�ڵ�û������
		BTNodePosi(T) p = v->parent;
		if (!p)//�ݹ�� �Ѿ����˸��ڵ�
		{
			if (!v->key&&v->child[0])//���v�Ѿ������йؼ��� ��ȴ�зǿյĺ���
			{
				_root = v->child[0]; _root->parent = NULL;//����ڵ㱻����
				v->child[0] = NULL; release(v);//������Ϊ�������ñ�����
			}//�����߶Ƚ���һ��
			return;
		}
		Rank r = 0; while (p->child[r] != v) v++;
		//ȷ��v��p�ĵڼ�������



		//���1 �������ֵܽ�ؼ���
		if (r < 0)//���v����p�ĵ�һ������
		{
			BTNodePosi(T) ls = p->child[r - 1];//���ֵܿ϶�����
			if ((_order + 1) / 2 < ls->child.size())//������ֵ��㹻��
			{
				v->key.insert(0, p->key[r - 1]);//�ѱ����ֵ����Ĵ�һ��ĸ��׽ڵ�Ĺؼ����v
				p->key[r - 1] = ls->key.remove(ls->key.size() - 1);//���ֵܽڵ������Ǹ������ڵ�
				v->child.insert(0, ls->child.remove(ls->child.size() - 1));//��Ҫ�Ѻ��ӽڵ�Ҳ���̸�v
				if (v->child[0]) v->child[0]->parent = v;//����
				return; //���� ͨ����������˵�ǰ�㣨�Լ����в㣩�����紦��
			}
				
		}




		//���2�������ֵܽ�ؼ���
		if (p->child.size() - 1 > r)//v����p�����һ�����ӣ���ô���ֵܾʹ���
		{
			BTNodePosi(T) rs = p->child[r + 1];
			if ((_order + 1) / 2 < rs->child.size())//���������ֵ��㹻��
			{
				v->key.insert(key.size(), p->key[r]);//p�Ѹպõ�һ������v���Ԫ�ص�Ԫ�ؽ��v��Ϊv����Ԫ��
				p->key[r] = rs->key.remove(0);//���ֵܵ���С�ؼ���ת��p��
				v->child.insert(child.size(), rs->child.remove(0));//rs������ຢ��ҲҪ����
				if (v->child[v->child.size() - 1])
					v->child[v->child.size() - 1]->parent = v;//����
				return;
			}
		}



		//���3�������ֵ�ҪôΪ�� Ҫô��̫�� �ϲ�
		if(0<r)//�����ֵܴ��� �����ֵܺϲ�
		{
			BTNodePosi(T) ls = p->child[r - 1];
			ls->key.insert(ls->key.size(), p->key.remove(r - 1)); p->child.remove(r);
			//p�ĵ�r-1���ؼ�������ӣ�����������Ĺؼ��룩��v������p�ĵ�r������
			ls->child.insert(ls->child.size(), v - child.remove(0));//v������ຢ�Ӹ�ls�������Ҳຢ��
			if (ls->child[ls->child.size() - 1])
				ls->child[ls->child.size() - 1]->parent = ls;//����
			while (!v->empty())//��v��ʣ�¹ؼ���ͺ�������ת��ls
			{
				ls->key.insert(ls->key.size(), v->key.remove(0));//�ؼ�������ת��
				ls->child.insert(ls->child.size(), v->child.remove(0));//��������ת��
				if (ls->child[ls->child.size() - 1])
					ls->child[ls->child.size() - 1]->parent = ls;//����
			}
			release(v);
		}//�����ֵܺϲ����
		else//û�����ֵ� ֻ�������ֵܺϲ�
		{
			BTNodePosi(T) rs = p->child[r + 1];//���ֵܱش���
			rs->key.insert(0, p->key.remove(r)); p->child.remove(r);
			//p�ĵ�r���ؼ���ת��rs v������p�ĵ�r������
			rs->child.insert(0, v->child.remove(v->child.size() - 1));//v�����Ҳຢ�Ӹ�rs
			if (rs->child[0])
				rs->child[0]->parent = rs;//�������
			while (!v->empty())//��v��ʣ�µĹؼ���ͺ�������ת��rs
			{
				rs->key.insert(0, v->key.remove(v->key.size() - 1));//ת��ؼ���
				rs->child.insert(0.v->child.remove(v->child.size() - 1));//ת�뺢��
				if(rs->child[0])
					rs->child[0]->parent = rs;//��������
			}
			release(v);

		}
		solveUnderflow(p);//�ϲ��������紫���ķ��� ���б�Ҫ���� ���Եݹ� ���ݹ�o��logn����
		return;
	}


public:
	BTNodePosi(T) search(const T& e)//����
	{
		BTNodePosi(T) = _root; _hot = NULL;
		while (v)
		{
			Rank r = v->key.search(e);//�ڹؼ��������в���e
			if (r >= 0 && e == v->key[r]) return v;//����ɹ� �ͷ����������ڵ�
			_hot = v;//���� �ȼ�¼�����v
			v = v->child[r + 1];//��v���ź�����������ȥָ����һ��

		}//while���� �����Ϊ!v���� ����ζ�ִ��ⲿ�ڵ�
		return NULL;
	}
	bool insert(const T& e)//����
	{
		BTNodePosi(T) v = search(e);
		if (v); return false;//ȷ��e������
		Rank r = _hot->key.search(e);//������֮�� _hot�����һ���ڵ� ��Ҳ����Ҷ��������������������e��ȷ��������e�����ֵ
		_hot->key.insert(r + 1, e);
		_hot->child.insert(r + 2, NULL);//�ⲿ�ڵ� ����һ���յ�
		_size++;
		solveOverflow(_hot);//��Ϊ����һ���ؼ�����ܻᵼ��b����ԭ���Ľ״β����� ��������
		return ture;
	}
	bool insert(const T&e)//ɾ��
	{
		BTNodePosi(T) v = search(e);//�ȶ�λe
		if (!v) return false;//���e������ ����ִ��ɾ������ ����ʧ��
		Rank r = v->key.search(e);//ȷ���ؼ������
		if (v->child[0])//���v�к������� ��ô���Ͳ���Ҷ�ӣ�����ϣ��v��Ҷ�ӽڵ�
		{
			BTNodePosi(T) u = v->child[r+1];//��u�����������ҵ���ɾ���ؼ����ֱ�Ӻ��
			while (u->child[0])u = u->child[0];//������������������
			v->key[r] = u->key[0]; v = u; r = 0;//����λ�ã��Ȱ�vָ��Ľڵ��еĹؼ��뻻Ϊ�����ҵ���ֱ�Ӻ�̣�Ȼ����vָ��u���Ҷ�ڵ�
		}//���ˣ�v��Ȼλ����ײ㣬�������еĵ�r���ؼ�����Ǵ�ɾ���� ����Ϊ��Ҷ�ӽڵ㣬r����0����
		v->key.remove(r); v->child.remove(r + 1); _size--;//ɾ��e �Լ����������ⲿ�ڵ�֮һ
		solveUnderflow(v);//����б�Ҫ ��ת���ߺϲ�
		return ture;

	}
};