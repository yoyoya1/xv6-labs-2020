
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main (int argc, char* argv[]) {
	
	int i;
	if (argc < 2) {
		fprintf(2, "fatal : Sorry, You need to print the time of sleep !\n");
		exit(1);
	}	
	if (argc > 2) {
		fprintf(2, "fatal : Sorry, Your param[in] too much !\n");
		exit(1);
	}
	for ( i = 1; i < argc; ++ i ) {
		int _time = atoi(argv[i]);	
		sleep(_time);
	}	
	exit(0);
}
