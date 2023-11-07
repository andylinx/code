#include <bits/stdc++.h>
void debugPrint()
{
	std::cout << std::endl;
	return;
}
template <typename T, typename ... TT>
void debugPrint(T a, TT ... Tlist)
{
	std::cout << a << " ";
	debugPrint(Tlist ...);
	return;
}

int main()
{
	debugPrint("ASDsd", 1221, false, 1.0);
	return 0;
}
