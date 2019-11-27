#pragma once
#include"Stack.h"
//��������ջʵ�ּ������
void readNumber(char*& p, Stack<float>& stk)//����ʼ��p���ִ�����Ϊ��ֵ�������������ջ��
{
	stk.push((float)(*p - '0'));
	while (isdigit(*(++p)))//���ֻҪ������������
		stk.push(stk.pop() * 10 + (*p - '0'));//��һλ��ջ���ҳ���10�������µ�һλ��ջ
	if ('.' != (*++p)) return;//����С����ͳ�ջ
	float fraction = 1;//����Ļ�����С�������
	while (isdigit(*(++p)))
		stk.push(stk.pop() + (*p - '0') + (fraction /= 10));//����fractionÿ�γ���10����λҲ����һλ
}



//������ջ��������͵�ǰ������ջջ������������ȼ��Ա�ʵ��
#define N_OPTR 9//��������  
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator;
//��������ȹ�ϵ��ά���
const char pri[N_OPTR][N_OPTR] = {
	/*						��ǰ�����                       */
	/*				 +    -    *    /    ^    !    (    )    \0 */
	/*	-- + */		'>', '>', '<', '<', '<', '<', '<', '>', '>',
	/*	|  - */		'>', '>', '<', '<', '<', '<', '<', '>', '>',
	/*	ջ * */		'>', '>', '>', '>', '<', '<', '<', '>', '>',
	/*	�� / */		'>', '>', '>', '>', '<', '<', '<', '>', '>',
	/*	�� ^ */		'>', '>', '>', '>', '>', '<', '<', '>', '>',
	/*	�� ! */		'>', '>', '>', '>', '>', '>', ' ', '>', '>',
	/*	�� ( */		'<', '<', '<', '<', '<', '<', '<', '=', ' ',
	/*	|  ) */		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
	/*	--\0 */		'<', '<', '<', '<', '<', '<', '<', ' ', '='




};
Operator optr2rank(char op)
{
	switch (op)
	{
	case '+':return ADD;
	case '-':return SUB;
	case '*':return MUL;
	case '/':return DIV;
	case '^':return POW;
	case '!':return FAC;
	case '(':return L_P;
	case ')':return R_P;
	case '\0':return EOE;
	default:exit(-1);
	}
}
char orderBetween(char op1, char op2)//�Ƚ����������֮��Ĺ�ϵ
{
	return pri[optr2rank(op1)][optr2rank(op2)];
}
//�����Ǽ����������
__int64 facI(int n) { __int64 f = 1; while (n > 1) f *= n--; return f; }//�׳˵�����


//calcu������ִ������ʱ��β���


float calcu(float a, char op, float b) { //ִ�ж�Ԫ����
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': if (0 == b) exit(-1); return a / b; //ע�⣺����и�����Ϊ����ܲ���ȫ
	case '^': return pow(a, b);
	default: exit(-1);
	}
}

float calcu(char op, float b) { //ִ��һԪ����
	switch (op) {
	case '!': return (float)facI((int)b); //Ŀǰ���н׳ˣ����մ˷�ʽ���
	default: exit(-1);
	}
}





void append(char*& rpn, float opnd)//�����������ӵ���׺���ʽ��ߣ�rpn��
{
	int n = strlen(rpn);
	char buf[64];
	if (opnd != (float)(int)opnd) sprintf(buf, "%.2f \0", opnd);//�����ʽ ��תΪint��תΪfloat С�������һ�������Ǹ��� if����
	else sprintf(buf, "%d \0", (int)opnd);
	rpn = (char*)realloc(rpn, sizeof(char)*(n + strlen(buf) + 1));//��չ�ռ�
	strcat(rpn, buf);

}
void append(char*& rpn, char optr)//����������ӵ���׺���ʽ��ߣ�rpn��
{
	int n = strlen(rpn);
	rpn = (char*)realloc(rpn, sizeof(char)*(n  + 3));
	sprintf(rpn + n, "%c", optr);
	rpn[n + 2] = '\0';
}





float evaluate(char* S, char*& RPN)//ͬʱת��Ϊ�沨�����ʽ
{
	Stack<float> opnd; Stack<char> optr;//������ջ �����ջ
	optr.push('0');//��Ϊ�ڱ�
	while (!optr.empty())//ֻҪ��Ϊ�������ջ
	{
		if (isdigit(*S))
		{
			readNumber(S, opnd); append(RPN, opnd.top());//���������
		}
		else//����������
			switch (orderBetween(optr.top(), *S))//�Ƚ����ȼ��ߵ�
			{
			case '<'://���ջ�����ȼ�С�����µ����������ջ�У�������ȡ��һ���ַ�
				optr.push(*S); S++;
				break;
			case '='://���ȼ���ȵ����(��ǰ�����Ϊ�����Ż���β���ڱ�\0)
				optr.pop(); S++;//���������ջ�� ��ȡ��һ���ַ�
				break;
			case '>'://���ջ����������ȼ���
			{
				char op = optr.pop(); append(RPN,op);//ջ���������ջ
				if ('!' == op)//һԪ���� ջ����������ջ
				{
					float pOpnd = opnd.pop();
					opnd.push(calcu(op, pOpnd));
				}
				else//���ڶ�Ԫ���� ջ����������ջ����
				{
					float pOpnd2 = opnd.pop(), pOpnd1 = opnd.pop();
					opnd.push(calcu(pOpnd1, op, pOpnd2));//�����ջ�����������ڼ����ǰ��
				}
				break;
			}
			default: exit(-1);
			}//switch
	}//while
	return opnd.pop();
}