#pragma once
#include"Myvector.h"
#include<ctype.h>
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
template <typename T> class Stack: public Vector<T>//继承自向量类
	{
	public :
		void push(T const &e) { this->insert(Vector<T>::size(),e); }
		T pop() { return Vector<T>::remove(Vector<T>::size() -1); }
		T& top() { return (*this)[Vector<T>::size() - 1]; }

};
	void convert(Stack<char> &s, _int64 n,int base)//进制转换函数
	{
		static char digit[] = { '0,','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
		while (n > 0)
		{
			s.push(digit[n%base]);
			n /= base;
		}
	}
	bool paren(const char exp[], int lo, int hi)//括号匹配函数遇见右括号时栈是空的 则不匹配 直接返回false
	{
		Stack<char> s;
		for (int i = lo; i < hi; i++)
		{
			switch (exp[i])
			{
			case '(': case'[':case '{':s.push(exp[i]); break;//遇左括号 进栈
			case ')':if ((s.empty()) || (s.pop() != '(')) return false; break;//遇见右括号，栈顶出栈，如果出栈的不是左括号 直接false
			case ']':if ((s.empty()) || (s.pop() != ']')) return false; break;
			case '}':if ((s.empty()) || (s.pop() != '}')) return false; break;
			default:break;
			}
		}
		return s.empty();
	}














	//以下利用栈实现计算操作
//	void readNumber(char*& p, Stack<float>& stk)//将起始于p的字串解析为数值，并存入操作数栈中
//	{
//		stk.push((float)(*p - '0'));
//		while(isdigit(*(++p)))//后边只要紧跟的是数字
//			stk.push(stk.pop()*10+(*p-'0'));//上一位出栈并且乘以10，加上新的一位进栈
//		if ('.' != (*++p)) return;//不是小数点就出栈
//		float fraction = 1;//否则的话，有小数点存在
//		while (isdigit(*(++p)))
//			stk.push(stk.pop() + (*p - '0') + (fraction /= 10));//利用fraction每次除以10，数位也降低一位
//	}
//
//
//
//	//以下是栈顶运算符和当前操作符栈栈顶运算符的优先级对比实现
//#define N_OPTR 9//运算总数  
//typedef enum{ADD,SUB,MUL,DIV,POW,FAC,L_P,R_P,EOE} Operator;
////运算符优先关系二维表格
//const char pri[N_OPTR][N_OPTR] = {
//	/*						当前运算符                       */
//	/*				 +    -    *    /    ^    !    (    )    \0 */
//	/*	-- + */		'>', '>', '<', '<', '<', '<', '<', '>', '>',
//	/*	|  - */		'>', '>', '<', '<', '<', '<', '<', '>', '>',
//	/*	栈 * */		'>', '>', '>', '>', '<', '<', '<', '>', '>',
//	/*	顶 / */		'>', '>', '>', '>', '<', '<', '<', '>', '>',
//	/*	运 ^ */		'>', '>', '>', '>', '>', '<', '<', '>', '>',
//	/*	算 ! */		'>', '>', '>', '>', '>', '>', ' ', '>', '>',
//	/*	符 ( */		'<', '<', '<', '<', '<', '<', '<', '=', ' ',
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
//char orderBetween(char op1, char op2)//比较两个运算符之间的关系
//{
//	return pri[optr2rank(op1)][optr2rank(op2)];
//}
////以下是计算的主函数
//__int64 facI(int n) { __int64 f = 1; while (n > 1) f *= n--; return f; }//阶乘迭代版
//
//
////calcu函数，执行运算时如何操作
//
//
//float calcu(float a, char op, float b) { //执行二元运算
//	switch (op) {
//	case '+': return a + b;
//	case '-': return a - b;
//	case '*': return a * b;
//	case '/': if (0 == b) exit(-1); return a / b; //注意：如此判浮点数为零可能不安全
//	case '^': return pow(a, b);
//	default: exit(-1);
//	}
//}
//
//float calcu(char op, float b) { //执行一元运算
//	switch (op) {
//	case '!': return (float)facI((int)b); //目前仅有阶乘，可照此方式添加
//	default: exit(-1);
//	}
//}
//
//
//
//
//
//
//float evaluate(char* S, char*& RPN)//逆波兰式还不懂 
//{
//	Stack<float> opnd; Stack<char> optr;//运算数栈 运算符栈
//	optr.push('0');//作为哨兵
//	while (!optr.empty())//只要不为空运算符栈
//	{
//		if (isdigit(*S))
//		{
//			readNumber(S, opnd); //append(RPN, opnd.top());//读入操作数
//		}
//		else//如果是运算符
//			switch (orderBetween(optr.top(), *S))//比较优先级高低
//			{
//			case '<'://如果栈顶优先级小，将新的运算符读入栈中，继续读取下一个字符
//				optr.push(*S); S++;
//				break;
//			case '='://优先级相等的情况(当前运算符为右括号或者尾部哨兵\0)
//				optr.pop(); S++;//运算符脱离栈中 读取下一个字符
//				break;
//			case '>'://如果栈顶运算符优先级大
//				{
//				char op = optr.pop();//栈顶运算符出栈
//				if ('!' == op)//一元运算 栈顶运算数出栈
//					{	
//						float pOpnd = opnd.pop();
//						opnd.push(calcu(op, pOpnd));
//					}
//				else//对于二元运算 栈顶运算数出栈两个
//					{
//					float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop();
//					opnd.push(calcu(pOpnd1, op, pOpnd2));//将后出栈的运算数放在计算的前面
//					}
//				break;
//				}
//			default: exit(-1);
//			}//switch
//	}//while
//	return opnd.pop();
//}