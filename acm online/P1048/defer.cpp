#include <bits/stdc++.h>

class Defer
{
Defer()
{
}
private:
std::vector <std::function<void()> > func_pointer;
public:

template<typename F>
Defer (F && f)
{
	func_pointer.push_back(f);
}
template<typename F>
void operator ()(F && f)
{
	func_pointer.push_back(f);
}
~Defer()
{
	for (int id = func_pointer.size() - 1; id >= 0; id--)
		func_pointer[id]();
}
};

void hello()
{
	std::cout << "Hello world!" << std::endl;
}

int main()
{
	int *p = new int [2];
	Defer defer([&](){
		    delete [] p;
		});

	defer([&](){
		std::cout << p[0] << " " << p[1] << std::endl;
	});
	defer([&](){
		p[0] = 0, p[1] = 1;
	});
	defer(hello);
	p[0] = 2, p[1] = 3;
	return 0;
}
