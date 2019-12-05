#include <stdlib.h>
#include <signal.h>

void registe_sigaction(int seg, void (*handler)(int));