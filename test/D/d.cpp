#include <stdio.h>
int val[18] = { 0, 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 };
char s[25];
char ans[11] = { '1', '0', 'X', '9', '8', '7', '6', '5', '4', '3', '2' };
int main()
{
	int T; scanf("%d", &T);

	while (T--) {
		scanf("%s", s + 1);
		int res = 0;
		for (int i = 1; i <= 17; i++)
			res = (res + (s[i] - '0') * val[i]) % 11;
		if (s[18] == ans[res]) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}
