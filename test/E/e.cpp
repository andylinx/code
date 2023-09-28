#include <stdio.h>
int main()
{
	int n, m;

	while (scanf("%d%d", &n, &m) == 2) {
		if ((n == 1 && m == 2) || (n == 2 && m == 1)) printf("YEEEEE!!!");
		else printf("W00000!!!");
		printf("\n");
	}
	return 0;
}
