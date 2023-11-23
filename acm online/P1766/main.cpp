#include "src.cpp"

#include <iostream>

int usedBlocks = 0;
int usedSpace = 0;
int maxUsedSpace = 0;

int * getNewBlock(int n)
{
	if (n <= 0) return nullptr;
	usedBlocks += n;
	return new int[n * 4096 / sizeof(int)];
}

void freeBlock(const int *block, int n)
{
	if (block == nullptr || n <= 0) return;
	delete[] block;
}

int * allocate(Allocator& allocator, int n)
{
	usedSpace += n;
	if (usedSpace > maxUsedSpace) maxUsedSpace = usedSpace;
	return allocator.allocate(n);
}

void deallocate(Allocator& allocator, int *pointer, int n)
{
	usedSpace -= n;
	allocator.deallocate(pointer, n);
}

bool check(Allocator& allocator)
{
	return (usedBlocks - 1) * 4096 / sizeof(int) / 2 < maxUsedSpace;
}

int main()
{
	Allocator allocator;

	int *a = allocate(allocator, 50);
	int *b = allocate(allocator, 2000);

	deallocate(allocator, b, 2000);
	b = allocate(allocator, 2000); // 会利用先前分配的空间
	// std::cerr << b << std::endl;
	deallocate(allocator, b, 2000);
	// std::cerr << maxUsedSpace << std::endl;
	if (!check(allocator))
		std::cout << "Using too much space" << std::endl;
	else
		std::cout << "Passed" << std::endl;
}
