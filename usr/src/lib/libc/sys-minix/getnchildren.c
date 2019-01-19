/* CSC2025 modification start */
#include <lib.h>
#include <unistd.h>

int getnchildren(pid_t pid) {
	message m;
	m.m1_i1 = pid;
	
	return _syscall(PM_PROC_NR, GETNCHILDREN, &m); //The input is sanitised in the system call. Just pass everything through here.
}
/* CSC2025 modification end */