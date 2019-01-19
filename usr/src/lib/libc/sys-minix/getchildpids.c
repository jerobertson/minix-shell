/* CSC2025 modification start */
#include <lib.h>
#include <unistd.h>

int getchildpids(pid_t pid, int nchildren, pid_t *childpids) {
	message m;
	m.m1_i1 = pid;
	m.m1_i2 = nchildren;
	m.m1_p1 = (char*) childpids;
	
	return _syscall(PM_PROC_NR, GETCHILDPIDS, &m); //The input is sanitised in the system call. Just pass everything through here.
}
/* CSC2025 modification end */