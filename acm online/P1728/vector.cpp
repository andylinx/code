#include <bits/stdc++.h>
using namespace std;
void Init(int **&p, int n)//��ʼ����nΪvector�ĸ���,�����pָ��nullptr
//todo
{
	p = new int *[n + 1];
	p[0] = new int [n + 1];
	for (int i = 0; i <= n; i++) p[0][i] = 0;
	for (int i = 1; i <= n; i++) p[i] = new int [1], p[i][0] = 0;
}
void Add_element(int **&p, int x, int y)//�ڵ�x(1base)��vector�������һ��Ԫ��y
//todo
{
	if (p[0][x] + 1 > p[x][0]) {
		if (p[0][x] == 0) {
			delete []p[x];
			p[x] = new int [2];
			p[x][1] = y;
			p[x][0] = 1;
			p[0][x] = 1;
		} else {
			int *tmp = new int [p[0][x] + 1];
			for (int i = 0; i <= p[0][x]; i++) tmp[i] = p[x][i];
			delete []p[x];
			p[x] = new int [2 * tmp[0] + 1];
			p[x][0] = 2 * tmp[0];
			for (int i = 1; i <= p[0][x]; i++) p[x][i] = tmp[i];
			p[x][++p[0][x]] = y;
			delete []tmp;
		}
	} else {
		p[x][++p[0][x]] = y;
	}
}
int Get_element(int **&p, int x, int k)//��ȡ��x(1base)��vector�е�k��(1-base)Ԫ�ص�ֵ
//todo
{
	return p[x][k];
}
void Clear(int **&p, int n)//���տռ�
//todo
{
	for (int i = 0; i <= n; i++)
		delete []p[i];
	delete []p;
}
int main()
{
	int **p, n = 10;

	Init(p, n);
	int ttt;
	cerr << &ttt << endl;
	// for (int i = 1; i <= 10; i++) printf("%d ", p[0][i]);
	// printf("\n");
	// cerr << &p << endl;
	for (int i = 1; i <= 10; i++) Add_element(p, 9, i);
	// for (int i = 1; i <= 10; i++) printf("%d\n", Get_element(p, 9, i));
	for (int i = 1; i <= 10; i++) Add_element(p, 10, i);
	// for (int i = 1; i <= 10; i++) printf("%d\n", Get_element(p, 10, i));
	int tt;
	cerr << &tt << endl;
	Clear(p, n);
	int aa;
	cerr << &aa << endl;
	return 0;
}
