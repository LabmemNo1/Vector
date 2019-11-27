#pragma once
#include"BST.h"
template <typename T> class Splay :public BST<T>
{
protected:

	//�����ڵ���Ϊ���Ӻ͸��׹����Ľӿ�
	template <typename NodePosi> inline
		void attachAsLChild(NodePosi p, NodePosi lc) { p->lc = lc; if (lc) lc->parent = p; }
	template <typename NodePosi> inline
		void attachAsRChild(NodePosi p, NodePosi rc) { p->rc = rc; if (rc) rc->parent = p; }



	BinNodePosi(T) splay(BinNodePosi(T) v)//���ڵ�v��չ����
	{
		if (!v) return NULL;
		BinNodePosi(T) p; BinNodePosi(T) g;//���׽ڵ���游�ڵ�
		while ((p = v->parent) && (g = p->parent))//v�����游�Ļ���ѭ��һֱ����
		{
			BinNodePosi(T) gg = g->parent;//��Ϊÿ��ѭ������v���������游��Ϊ�µĸ���
			if(IsLChild(*v))//zig
				if(IsLChild(*p))//zig-zig���ǻ�ͼ���ɣ��Ƚ����׿��ó���
				{
					attachAsRChild(v,p);
					attachAsLChild(p, v->rc);
					attachAsRChild(p, g);
					attachAsLChild(g, p->rc);

				}
				else//zig-zag
				{
					attachAsLChild(p, v->rc); attachAsRChild(g, v->lc);
					attachAsLChild(v, g); attachAsRChild(v, p);
				}
			else if (IsRChild(*p))//zag-zag
			{
				attachAsRChild(g, p->lc); attachAsRChild(p, v->lc);
				attachAsLChild(p, g); attachAsLChild(v, p);
			}
			else//zag-zig
			{
				attachAsRChild(p, v->lc); attachAsLChild(g, v->rc);
				attachAsRChild(v, g); attachAsLChild(v, p);
			}
			if (!gg) v->parent = NULL;//������游�����ڣ���ôv����˫����չ��ض�Ϊ����
			else//������ڣ���ôgg����v�ĸ���
				(g == gg->lc) ? attachAsLChild(gg, v) : attachAsRChild(gg, v);//����g���ж�v����Ϊ�Һ��ӻ�������
			updateHeight(g); updateHeight(p); updateHeight(v);//���¸߶�
		}//while����
		//˫����չ�����󣬱ض���g==NULL������p��һ��Ϊ�գ����Կ�����Ҫ�ڽ���һ�ε���
		if (p = v->parent)
		{
			if (IsLChild(*v))
			{
				attachAsLChild(p, v->rc); attachAsRChild(v, p);
			}
			else
			{
				attachAsRChild(p, v->lc); attachAsLChild(v, p);
			}
			updateHeight(p); updateHeight(v);//���¸߶�
		}
		v->parent = NULL; return v;//����֮���µ���������v�ˡ����Է���v�Ա����ϲ㺯����������

	}



public://��д ���� ���� ��ɾ������Ϊ��������������ת����չ��
	BinNodePosi(T)& search(const T& e)//�����Ǿ�̬����
	{
		BinNodePosi(T) p = searchIn(_root, e, _hot = NULL);
		_root = splay(p ? p : _hot);//_hot�����������һ���ڵ�
		return _root;//���ظ��ڵ㡣���ڸ��ڵ��Ѿ����������Ľڵ���
	}
	BinNodePosi(T) insert(const T&e)//�ѹؼ���e������չ����
	{
		if (!_root) { _size++; return _root = BinNode<T>(e); }//����ԭ��Ϊ�յ��˻�
		if (e == search(e)->data) return _root;//ȷ��Ŀ��ڵ㲻���ڣ���ΪҪ����
		//�����Ĳ����ڵĻ�
		_size++; BinNodePosi(T) t = _root;//�����½ڵ�
		if (_root->data < e)//���ԭ�������Ѿ������ʼ����������t��С���²���Ľڵ� ��ô����tΪ���ӣ�t->rcΪ�Һ���
		{
			t->parent = new BinNode<T>(e, NULL, t, t->rc);//һ��һ������Щ�ڵ�������ӣ�����ͼ��Ƚ�����
			if (HasRChild(*t)) { t->rc->parent = _root; t->rc = NULL; }
		}
		else//��t��lc��t��Ϊ���Һ���
		{
			t->parent = new BinNode<T>(e, NULL, t->lc, t);//һ��һ������Щ�ڵ�������ӣ�����ͼ��Ƚ�����
			if (HasRChild(*t)) { t->lc->parent = _root; t->lc = NULL; }
		}
		updateHeightAbove(t);//����t�������ȸ߶ȣ�ʵ�ʾ�_rootһ����
		return _root;//���ظղŲ���Ľڵ�
	}
	bool remove(const T& e)//����չ����ɾ���ؼ���e
	{
		if (!_root || (e != search(e)->data)) return false;//���������������û�����Ԫ��  ����ʧ��
		BinNodePosi(T) w = _root;//search��e�Ѿ���չ������
		if(!HasLChild(*_root))//���û����������ֱ��ɾ��������ڵ����
		{
			_root = _root->rc;
			if (_root) _root->parent = NULL;
		}
		else if (!HasRChild(*_root))//�ԳƵ� ���û��������
		{
			__root = _root->lc;
			if (_root) _root->parent = NULL;
		}
		else//����Ҫ�� ��������ͬʱ���ڵ������ 
		{
			BinNodePosi(T) lTree = _root->lc;//�ȴ���һ���ڵ����������
			lTree->parent = NULL; _root->lc = NULL;//��ʱ���������г���
			_root = _root->rc; _root->parent = NULL;//���ڸ����������ĵ�һ���ڵ㣬��������Ҫ������������С�Ľڵ���Ϊ����
			search(w->data);//������������һ�αض�ʧ�ܵĲ�ѯ���鵽��������������С�Ľڵ㣬�������������������С�Ľڵ���
			_root->lc = lTree; lTree->parent = _root;
			
		}
		release(w->data); release(w); _size--;//�ͷŽڵ���¹�ģ
		if (_root) updateHeight(_root);//�����ǿ� ���������߶�
		return ture;//ɾ���ɹ�
	}
};