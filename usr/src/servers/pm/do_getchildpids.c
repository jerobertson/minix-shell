/* CSC2025 modification start */
#include <stdio.h>
#include <errno.h>
#include "pm.h"
#include "mproc.h"

int do_getchildpids() {
	//Retrieve values from the message.
	int ppid = m_in.m1_i1;
	int nchildren = m_in.m1_i2;
	pid_t *childpids = m_in.m1_p1;
	
	//Check for correct input, return -1 and set errno if bad input was found.
	if (ppid < 1) {
		errno = EINVAL;
		return -1;
	}
	if (nchildren == 0) {
		return 0;
	}
	
	//Count the number of children in the process table, passing the PID of each into an array called pidsarray.
	int n = 0;
	pid_t pidsarray[nchildren];
	for (int i = 0; i < NR_PROCS; i++) {
		int pid = mproc[i].mp_pid;
		
		if (pid != 0 && mproc[mproc[i].mp_parent].mp_pid == ppid) {
			pidsarray[n] = pid;
			n++;
		}
	}
	
	//Attempt to copy pidsarray to the location specified by the process that called this system call. Return -1 and set errno if it fails.
	int errval = sys_vircopy(SELF, pidsarray, who_e, childpids, sizeof(pidsarray));
	if (errval) {
		errno = errval;
		return -1;
	}
	
	//Otherwise return the number of processes found.
	return n;
}
/* CSC2025 modification end */