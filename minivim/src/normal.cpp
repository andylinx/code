#include "virable.h"

void normal_state()
{
	char cc = getch();

	while (cc != 'i' && cc != 27)
		cc = getchar();

	if (cc == 'i') mode_type = 1;
	if (cc == 27) exit_flag = 1;
	return;
}
