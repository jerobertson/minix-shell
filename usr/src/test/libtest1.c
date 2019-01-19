/* CSC2025 modification start */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * This method is for testing the library method specified in part 1, "printchildpids".
 */
int main(int argc, char **argv) {
	if (argc < 2) exit(1);
	
	int pid = atoi(argv[1]);
	
	printchildpids(pid);
	
	return 0;
}
/* CSC2025 modification end */