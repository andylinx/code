#include <stdio.h>
int main()
{
	int T; scanf("%d", &T);

	while (T--) {
		unsigned int x;
		scanf("%u", &x);
		printf("%u\n", (x >> 16) + (x << 16));
	}
	return 0;
}
