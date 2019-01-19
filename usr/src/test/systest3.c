/* CSC2025 modification start */
#include <lib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * This method is for testing the system call specified in part 3, "getchildpids".
 * It makes use of the method "getnchildren" to specify the size of the array.
 */
int main(int argc, char **argv) {
	if (argc < 2)
		exit(1);
	
	int pid = atoi(argv[1]);
	int n = getnchildren(pid);
	pid_t childpids[n];
	
	message m;
	m.m1_i1 = pid;
	m.m1_i2 = n;
	m.m1_p1 = (char*) childpids;
	
	printf("%d\n", _syscall(PM_PROC_NR, GETCHILDPIDS, &m));
	for (int i = 0; i < n; i++) {
		printf("%d, ", childpids[i]);
	}
	printf("\n");
}
/* CSC2025 modification end */