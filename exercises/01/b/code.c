#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

pid_t zombie_pid = -1;

void handle_signal(int signo) {
    if (zombie_pid == -1) {
        pid_t pid = fork();

        if (pid == 0)
            exit(0);
        else
            zombie_pid = pid;
    } else {
        waitpid(zombie_pid, NULL, 0);
        zombie_pid = -1;
    }
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handle_signal;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    for (int i = 0; i < 3; i++)
        pause();

    return 0;
}
