#include <proc.h>
#include <stdio.h>
#include <syscall.h>
#include <x86.h>

uint32_t global_test = 0x12345678;

int main(int argc, char **argv)
{
    pid_t pid;
    // printf("Fork.c start \n");
    pid = sys_fork();
    // printf("Fork.c %d\n",pid);
    if (pid == 0) {
	// printf("Fork.c pid==0: %d\n",pid);
        pid = sys_fork();

        if (pid == 0) {
            printf("This is grandchild, global = %p\n", global_test);
        } else {
            printf("Child forks %d, global = %p\n", pid, global_test);
        }
    } else {
        printf("parent forks %d, global = %p\n", pid, global_test);
        global_test = 0x5678;
        printf("parent global_test1 = %p\n", global_test);
    }

    return 0;
}
