#pragma once
#include"Myvector.h"
#include<ctype.h>
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
template <typename T> class Stack: public Vector<T>//�̳���������
	{
	public :
		void push(T const &e) { this->insert(Vector<T>::size(),e); }
		T pop() { return Vector<T>::remove(Vector<T>::size() -1); }
		T& top() { return (*this)[Vector<T>::size() - 1]; }

};
	void convert(Stack<char> &s, _int64 n,int base)//����ת������
	{
		static char digit[] = { '0,','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
		while (n > 0)
		{
			s.push(digit[n%base]);
			n /= base;
		}
	}
	bool paren(const char exp[], int lo, int hi)//����ƥ�亯������������ʱջ�ǿյ� ��ƥ�� ֱ�ӷ���false
	{
		Stack<char> s;
		for (int i = lo; i < hi; i++)
		{
			switch (exp[i])
			{
			case '(': case'[':case '{':s.push(exp[i]); break;//�������� ��ջ
			case ')':if ((s.empty()) || (s.pop() != '(')) return false; break;//���������ţ�ջ����ջ�������ջ�Ĳ��������� ֱ��false
			case ']':if ((s.empty()) || (s.pop() != ']')) return false; break;
			case '}':if ((s.empty()) || (s.pop() != '}')) return false; break;
			default:break;
			}
		}
		return s.empty();
	}














	//��������ջʵ�ּ������
//	void readNumber(char*& p, Stack<float>& stk)//����ʼ��p���ִ�����Ϊ��ֵ�������������ջ��
//	{
//		stk.push((float)(*p - '0'));
//		while(isdigit(*(++p)))//���ֻҪ������������
//			stk.push(stk.pop()*10+(*p-'0'));//��һλ��ջ���ҳ���10�������µ�һλ��ջ
//		if ('.' != (*++p)) return;//����С����ͳ�ջ
//		float fraction = 1;//����Ļ�����С�������
//		while (isdigit(*(++p)))
//			stk.push(stk.pop() + (*p - '0') + (fraction /= 10));//����fractionÿ�γ���10����λҲ����һλ
//	}
//
//
//
//	//������ջ��������͵�ǰ������ջջ������������ȼ��Ա�ʵ��
//#define N_OPTR 9//��������  
//typedef enum{ADD,SUB,MUL,DIV,POW,FAC,L_P,R_P,EOE} Operator;
////��������ȹ�ϵ��ά���
//const char pri[N_OPTR][N_OPTR] = {
//	/*						��ǰ�����                       */
//	/*				 +    -    *    /    ^    !    (    )    \0 */
//	/*	-- + */		'>', '>', '<', '<', '<', '<', '<', '>', '>',
//	/*	|  - */		'>', '>', '<', '<', '<', '<', '<', '>', '>',
//	/*	ջ * */		'>', '>', '>', '>', '<', '<', '<', '>', '>',
//	/*	�� / */		'>', '>', '>', '>', '<', '<', '<', '>', '>',
//	/*	�� ^ */		'>', '>', '>', '>', '>', '<', '<', '>', '>',
//	/*	�� ! */		'>', '>', '>', '>', '>', '>', ' ', '>', '>',
//	/*	�� ( */		'<', '<', '<', '<', '<', '<', '<', '=', ' ',
//	/*	|  ) */		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
//	/*	--\0 */		'<', '<', '<', '<', '<', '<', '<', ' ', '='
//
//
//
//
//};
//Operator optr2rank(char op)
//{
//	switch (op)
//	{
//	case '+':return ADD;
//	case '-':return SUB;
//	case '*':return MUL;
//	case '/':return DIV;
//	case '^':return POW;
//	case '!':return FAC;
//	case '(':return L_P;
//	case ')':return R_P;
//	case '\0':return EOE;
//	default:exit(-1);
//	}
//}
//char orderBetween(char op1, char op2)//�Ƚ����������֮��Ĺ�ϵ
//{
//	return pri[optr2rank(op1)][optr2rank(op2)];
//}
////�����Ǽ����������
//__int64 facI(int n) { __int64 f = 1; while (n > 1) f *= n--; return f; }//�׳˵�����
//
//
////calcu������ִ������ʱ��β���
//
//
//float calcu(float a, char op, float b) { //ִ�ж�Ԫ����
//	switch (op) {
//	case '+': return a + b;
//	case '-': return a - b;
//	case '*': return a * b;
//	case '/': if (0 == b) exit(-1); return a / b; //ע�⣺����и�����Ϊ����ܲ���ȫ
//	case '^': return pow(a, b);
//	default: exit(-1);
//	}
//}
//
//float calcu(char op, float b) { //ִ��һԪ����
//	switch (op) {
//	case '!': return (float)facI((int)b); //Ŀǰ���н׳ˣ����մ˷�ʽ���
//	default: exit(-1);
//	}
//}
//
//
//
//
//
//
//float evaluate(char* S, char*& RPN)//�沨��ʽ������ 
//{
//	Stack<float> opnd; Stack<char> optr;//������ջ �����ջ
//	optr.push('0');//��Ϊ�ڱ�
//	while (!optr.empty())//ֻҪ��Ϊ�������ջ
//	{
//		if (isdigit(*S))
//		{
//			readNumber(S, opnd); //append(RPN, opnd.top());//���������
//		}
//		else//����������
//			switch (orderBetween(optr.top(), *S))//�Ƚ����ȼ��ߵ�
//			{
//			case '<'://���ջ�����ȼ�С�����µ����������ջ�У�������ȡ��һ���ַ�
//				optr.push(*S); S++;
//				break;
//			case '='://���ȼ���ȵ����(��ǰ�����Ϊ�����Ż���β���ڱ�\0)
//				optr.pop(); S++;//���������ջ�� ��ȡ��һ���ַ�
//				break;
//			case '>'://���ջ����������ȼ���
//				{
//				char op = optr.pop();//ջ���������ջ
//				if ('!' == op)//һԪ���� ջ����������ջ
//					{	
//						float pOpnd = opnd.pop();
//						opnd.push(calcu(op, pOpnd));
//					}
//				else//���ڶ�Ԫ���� ջ����������ջ����
//					{
//					float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop();
//					opnd.push(calcu(pOpnd1, op, pOpnd2));//�����ջ�����������ڼ����ǰ��
//					}
//				break;
//				}
//			default: exit(-1);
//			}//switch
//	}//while
//	return opnd.pop();
//}