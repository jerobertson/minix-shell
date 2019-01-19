/* CSC2025 modification start */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * This method is for testing the library method specified in part 3, "getchildpids".
 * It makes use of the method "getnchildren" to specify the size of the array.
 */
int main(int argc, char **argv) {
	if (argc < 2) exit(1);
	
	int pid = atoi(argv[1]);
	int nchildren = getnchildren(pid);
	pid_t childpids[nchildren];
	
	printf("total children: %d\nchild list: ", getchildpids(pid, nchildren, childpids));
	for (int i = 0; i < nchildren; i++) {
		printf("%d, ", childpids[i]);
	}
	printf("\n");
	
	return 0;
}
/* CSC2025 modification end */