#include "main.h"

/**
  * main -  prints the PID of the current proccess
  *
  * Return: 0 (success)
  */

int main(void)
{
    pid_t pid;

    pid = getpid();

    printf("%u\n", pid);
    return (0);
}
