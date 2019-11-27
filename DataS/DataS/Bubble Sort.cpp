#pragma once
#pragma warning(disable : 4996)
#include<iostream>
#include"BitMap.h"
//#include"Stack.h"
#include"BinTree.h"
//#include"AVL.h"
//#include"Splay.h"
//#include"Myvector.h"
//#include"Fib.h"
#include"List.h"
#include<vector>
using namespace std;

_int64 fibI(int n)
{
	_int64 f = 1, g = 0;
	while (n-- > 0)
	{
		g += f;
		f = g - f;
	}
	return g;
}


int main() {
	////bubble sort √∞≈›≈≈–Ú
	///*const int n=5;
	//int a[n] = {5,8,9,1,3};
	//int x = n;
	//for(bool flag=false;flag=!flag;x--)
	//	for (int i = 1; i < n; i++) {
	//		if (a[i - 1] > a[i]) {
	//			swap(a[i - 1], a[i]);
	//			flag = false;
	//		}
	//	}
	//for (int j = 0; j != 5; j++)
	//	cout << a[j] << endl;
	//system("pause");
	//return 0;*/
	//Fib fib(10);
	//int s = fib.get();
	//cout << s << endl;







	//Vector<int> A ;
	//A.insert(5);
	//A.insert(3);
	//A.insert(1);
	//A.insert(8);
	//cout << A[0]<< A[1] << A[2] << A[3] << endl;
	//A.mergeSort(0,3);
	//cout << A[0] << A[1] << A[2] << A[3] << endl;
	//Stack<int> s;

	//cout << fibb(11) << endl;
	//List<int> s;
	//s.insertAsLast(5);
	//cout << s[0] << endl;
	
	//int x = 5;
	//s.insertAsLC(s.root(),x);









//
//BinTree<int> s;
//s.insertAsRoot(1);
//cout << s.root()->data << endl;
//s.remove(s.root());
//cout << s.root()->data << endl;
	//char* s = "prime.txt";
	//Eratosthenes(1048576, s);
	int j = 5;
	if (--j < 0);
		cout << j << endl;
	

	system("pause");

}

