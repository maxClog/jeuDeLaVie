#include "include/console.h" 

int unix_text_kbhit(void)
{
    struct timeval tv = { 0, 0 };
    fd_set readfds;
    
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    
    return select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv) == 1;
}

void mode_raw(int activer)
{
	static struct termios cooked;
	static int raw_actif = 0;

	if (raw_actif == activer)
		return;

	if (activer)
	{
		struct termios raw;

		tcgetattr(STDIN_FILENO, &cooked);

		raw = cooked;
		cfmakeraw(&raw);
		tcsetattr(STDIN_FILENO, TCSANOW, &raw);
	}
	else
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &cooked);
	}

	raw_actif = activer;

	return; 
}
