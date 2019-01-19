/* CSC2025 modification start */
#include <lib.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * This method is for testing the system call specified in part 2, "getnchildren".
 */
int main(int argc, char **argv) {
	if (argc < 2)
		exit(1);
	
	int i = atoi(argv[1]);
	
	message m;
	m.m1_i1 = i;
	
	printf("%d\n", _syscall(PM_PROC_NR, GETNCHILDREN, &m));
}
/* CSC2025 modification end */