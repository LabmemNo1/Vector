#pragma once
#include"BST.h"
#define IsBlack(p) (!(p)||(RB_BLACK==(p)->color))  //�ⲿ�ڵ�Ҳ�����Ǻڽڵ�
#define IsRed(p) (!IsBlck(p)) //�Ǻڼ���
#define BlackHeightUpdated(x) (stature((x).lc)==stature((x).rc))&&((x).height==(IsRed(&x)?stature((x).lc):stature((x).lc)+1)) //������߶ȸ�������
template <typename T> class RedBlack : public BST<T>
{
protected:
	void solveDoubleRed(BinNodePosi(T) x);//˫������
	void solveDoubleBlack(BinNodePosi(T) x);//˫������
	int updateHeight(BinNodePosi(T) x);//���½ڵ�x�ĸ߶� ע�� ������ĸ߶�ֻ����ڽڵ�ĸ߶�
public:
	BinNodePosi(T) insert(const T&e);//���� ����д��
	bool remove(const T&e);//ɾ�� ����д��
	//BST::search()�������ӿڿ���ֱ������
};









template<typename T>
inline void RedBlack<T>::solveDoubleRed(BinNodePosi(T) x)
{
	if(IsRoot(x*))//���һ���ݹ鵽���� ����ת�� �����ڸ߶ȼ�һ
	{
		_root->color = RB_BLCAK; _root->height++; return;
	}
	BinNodePosi(T) p = x->parent; if (IsBlack(p)) return;//���pΪ�� ������ֹ ����
	BinNodePosi(T) g = p->parent;//pΪ�� ��ôx�游�ʹ��ڣ����ҿ϶��Ǻ�ɫ��
	BinNodePosi(T) u = uncle(x);//����x�常����ɫ ���в�ͬ�ĵ���
	//�����ַ�ʽ���Ժ�ɫ�常�ڵ���� һ�����жϣ�Ⱦɫ���ڶ�����ת�����Ǹ��ݺ�������Ľ�b���Ĺ�����������
	//����ֻд��ת�ķ�ʽ ��Ϊû������zig-zig��zig-zag���жϣ�ͬ������жϣ�
	if (IsBlack(u))
	{//3+4�ع�
		BinNodePosi(T) gg = g->parent;
		BinNodePosi(T) r = FromParentTo(*g) = rotate(x);
		r->parent = gg;
	}
	else//���u�Ǻ�ɫ ���ǽ�����������Ϊһ��b-���󣬿��Կ���������b-������������
		//��� ��p232 ��ʾ ����ֻ��Ҫ��g�ڵ����Ϊ�죬p��u�ڵ���ɫȾΪ��ɫ����
	{
		p->color = RB_BLCAK; p->height++;//ȾΪ��ɫ���ڸ߶�+1
		u->color = RB_BLCAK; u->height++;//ȾΪ��ɫ���ڸ߶�+1
		if (!IsRoot(*g)) g->color = RB_RED;//���g���Ǹ� ȾΪ��ɫ 
		solveDoubleRed(g);//���ܻ��������Ĵ��� ��������g
	}

	
}

template<typename T>
inline void RedBlack<T>::solveDoubleBlack(BinNodePosi(T) x)
{
	BinNodePosi(T) p = r ? r->parent : _hot; if (!p) return;//r�ĸ���
	BinNodePosi(T) s = (r == p->lc) ? p->lc : p->rc;//r���ֵ�
	if (IsBlack(s))//�ֵ�sΪ��
	{
		BinNodePosi(T) t = NULL;//s�ĺ캢�ӣ��������ȣ����Ǻڵľ�NULL
		if (IsRed(s->rc)) t = s->rc;
		if (IsRed(s->lc)) t = s->lc;
		if (t)//����s�к캢�ӵķ�֧��Ҳ����BB-1
		{
			RBColor oldColor = p->color;//�ȱ���pԭ������ɫ
			//����������ת 3+4�ع�
			BinNodePosi(T) b = FromParentTo(*p) = rotateAt(t);
			if (HasLChild(*b)) { b->lc->color = RB_BLCAK; updateHeight(b->lc); }//�ع���ĸ��ڵ�����Һ���Ⱦ��
			if (HasRChild(*b)) { b->rc->color = RB_RED; updateHeight(b->rc); }
			b->color = oldColor; updateHeight(b);//b����ɫ��ԭ��p����ɫ
		}
		else//sû�к캢�ӵ������
		   //BB-2R��BB-2B
		{
			s->color = RB_BLCAK; s->height--;//������������ն�Ҫ��s���
			if (IsRed(p))//BB-2R
			{
				p->color = RB_BLCAK;//p��ڣ�˫���������
			}
			else
			{
				p->height--;
				solveDoubleBlack(p);//�ݹ�����޸������ܻᷢ�����ϵĴ���
			}
		}
	}
	else//BB-3 �ֵ�sΪ��
	{
		s->color = RB_BLCAK;
		p->color = RB_RED;
		BinNodePosi(T) t = IsLChild(*s) ? s->lc : s->rc;//ȡt���丸sͬ��
		_hot = p; FromParentTo(*p) = rotateAt(t);
		solveDoubleBlack(r);//�����޸���ת��BB-1����BB-2R
	}

		


}

template<typename T>
inline int RedBlack<T>::updateHeight(BinNodePosi(T) x)
{
	x->height = max(stature(x->lc), stature(x->rc));//����һ��������� ��Ϊ��������� ����˫��
	return IsBlack(x) ? x->height++ : x->height;
}

template<typename T>
inline BinNodePosi(T) RedBlack<T>::insert(const T & e)
{
	BinNodePosi(T) &x = search(e); if (e) return false;
	x = new BinNode<T>(e, _hot, NULL, NULL, -1); _size++;//������ڵ�x �ڸ߶�-1
	solveDoubleRed(x);
}

template<typename T>
inline bool RedBlack<T>::remove(const T & e)
{
	BinNodePosi(T) &x = search(e); if (!x) return false;//ȷ��Ŀ�����
	BinNodePosi(T) r = removeAt(x, this->_hot); if (!(--_size)) return ture;//ʵʩɾ�� ɾ�������Ϊ���� ����
	//���£����ɾ�����Ǹ��ڵ㣬�ͽ����úڣ������ºڸ߶�
	if(!_hot)//���ɾ���Ľڵ�û�и���
	{
		BinTree<T>::_root->color = RB_BLCAK; updateHeight(BinTree<T>::_root); return true;
	}
	if (BlackHeightUpdated(*_hot)) return true;//���������ȵĺ������Ȼƽ�� �Ͳ��õ���
	if(IsRed(r))//���� ���r��r�Ǳ�ɾ���ڵ�Ľ����ߣ��Ǻ�ģ�ֻ��Ҫ�����Ϊ�ڵ� ����ȼ���ƽ��
	{
		r->color = RB_BLCAK; r->height++; return true;
	}
	//����Ϊ˫������
	solveDoubleBlack(r); return true;


}
