int * getNewBlock(int n);
void freeBlock(const int *block, int n);
#include <bits/stdc++.h>
class Allocator {
public:
Allocator()
{
	cnt = remain_sz = 0;
	sz.clear();
	gs.clear();
	stp.clear();
}

~Allocator()
{
	for (auto u:gs)
		freeBlock(u.first, u.second);
}


int * allocate(int n)
{
	// std::cerr << n << std::endl;
	if (remain_sz >= n) {
		remain_sz -= n;
		int *ans = now;
		now += n;
		lst = ans;
		sz[st] -= n;
		stp[ans] = st;
		return ans;
	} else {
		int len = ceil(1.0 * n / 1024);
		// std :: cerr << len << std ::endl;
		st = getNewBlock(len);
		gs[st] = len;
		int *ans = st;
		now = st + n;
		sz[st] = len * 1024 - n;
		remain_sz = sz[st];
		lst = ans;
		stp[st] = ans;
		return ans;
	}
}
void deallocate(int *pointer, int n)
{
	int *stpos = stp[pointer];

	sz[stpos] += n;

	if (pointer == lst) {
		remain_sz += n;
		now -= n;
	} else {
		if (sz[stpos] == gs[stpos] * 1024) {
			freeBlock(stpos, gs[stpos]);
			sz.erase(stpos); gs.erase(stpos);
		}
	}
}

private:
int cnt, remain_sz;
int *now, *lst, *st;
std::map <int *, int> sz, gs;
std::map <int *, int *> stp;
};
