/* CSC2025 modification start */
#include <stdio.h>
#include <errno.h>
#include "pm.h"
#include "mproc.h"

int do_getnchildren() {
	//Retrieve values from the message.
	int ppid = m_in.m1_i1;
	
	//Check for correct input, return -1 and set errno if bad input was found.
	if (ppid < 1) {
		errno = EINVAL;
		return -1;
	}
	
	//Count the amount of children found in the process table and return this value.
	int n = 0;
	for (int i = 0; i < NR_PROCS; i++) {
		int pid = mproc[i].mp_pid;
		
		if (pid != 0 && mproc[mproc[i].mp_parent].mp_pid == ppid) {
			n++;
		}
	}
	return n;
}
/* CSC2025 modification end */