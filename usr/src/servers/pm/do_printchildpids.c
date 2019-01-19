/* CSC2025 modification start */
#include <stdio.h>
#include <errno.h>
#include "pm.h"
#include "mproc.h"

int do_printchildpids() {
	//Retrieve values from the message.
	int ppid = m_in.m1_i1;
	
	printf("Searching for children of process: %d\n", ppid);
	
	//Check for correct input, return -1 and set errno if bad input was found.
	if (ppid < 1) {
		errno = EINVAL;
		return -1;
	}
	
	//Print the PID of any children found in the process table.
	for (int i = 0; i < NR_PROCS; i++) {
		int pid = mproc[i].mp_pid;
		
		if (pid != 0 && mproc[mproc[i].mp_parent].mp_pid == ppid) {
			printf("%d\n", pid);
		}
	}
	
	return 0;
}
/* CSC2025 modification end */