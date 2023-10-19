extern int mode_type, exit_flag;
extern WINDOW *win;
void insert_mode()
{
	char cc = getch();

	while (cc != ':' && cc != 27) {
		wprintw(win, "%c", cc);
		wrefresh(win);
		cc = getch();
	}
	if (cc == ':') mode_type = 2;
	if (cc == 27) mode_type = 0;
	return;
}
