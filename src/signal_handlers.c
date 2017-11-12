#include <stdio.h>
#include <signal.h>
#include "signal_handlers.h"

void catch_sigint(int signalNo)
{
  // TODO: File this!
   printf("\n");
  signal(SIGINT, SIG_IGN);

}

void catch_sigtstp(int signalNo)
{
  // TODO: File this!
 signal (SIGTSTP, SIG_IGN);
}
