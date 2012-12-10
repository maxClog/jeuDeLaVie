#ifndef __CONSOLE_H
#define __CONSOLE_H

#include <sys/time.h>
#include <termios.h>
#include <unistd.h>

// indique si un caractère est disponible ou non 
int unix_text_kbhit(void);

// Permet d'activer (1) ou de désactiver (0) le mode brute 
void mode_raw(int activer); 

#endif 
