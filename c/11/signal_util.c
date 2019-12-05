#include "signal_util.h"
#include "error_util.h"

void registe_sigaction(int seg, void (*handler)(int))
{
    struct sigaction action = {0};
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(seg, &action, NULL) == -1)
    {
        error("registe signal handler failed.");
    }
}