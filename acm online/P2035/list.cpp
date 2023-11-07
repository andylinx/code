#include <iostream>
#include <cstdio>

using namespace std;

namespace LIST {
struct NODE {
	int	val;
	NODE *	pre, *nxt;
};

NODE *head = nullptr, *tail = nullptr;
int len = 0;

void Pre()
{
	// TODO
}

NODE *move(int i)
{
	// TODO
}

void insert(int i, int x)
{
	// TODO
}

void remove(int i)
{
	// TODO
}

int Get_length()
{
	// TODO
}

int Query(int i)
{
	// TODO
}

void Print()
{
	// TODO
}

void Clear()
{
	// TODO
}
}
int n;

int main()
{
	cin >> n;
	int op, x, p, ans;
	LIST::Pre();
	for (int _ = 0; _ < n; ++_) {
		cin >> op;
		switch (op) {
		case 0:
			ans = LIST::Get_length();
			cout << ans << endl;
			break;
		case 1:
			cin >> p >> x;
			LIST::insert(p, x);
			break;
		case 2:
			cin >> p;
			ans = LIST::Query(p);
			cout << ans << endl;
			break;
		case 3:
			cin >> p;
			LIST::remove(p);
			break;
		case 4:
			LIST::Print();
			break;
		}
	}
	// LIST::Clear();
	return 0;
}
