#include <iostream>
#include <cstring>

int n;
// д����������������
int *& funA(int **&p);
void funB(int c[], int **p, int **q);
int main()
{
	int a[100], b[100], c[100];

	std::cin >> n;
	for (int i = 0; i < n; ++i)
		std::cin >> a[i];
	for (int i = 0; i < n; ++i)
		std::cin >> b[i];
	int **p = nullptr;
	int **q = nullptr;
	funA(p) = a;
	funA(q) = b;
	funB(c, p, q);
	for (int i = 0; i < n; ++i)
		std::cout << c[i] << " ";
	delete(p); delete(q);
	return 0;
}

// д�����������Ķ���
int *& funA(int **&p)
{
	p = new(int *);
	return *p;
}
void funB(int c[], int **p, int **q)
{
	for (int i = 0; i < n; i++)
		c[i] = (*((*p) + i)) * (*((*q) + i));
}
