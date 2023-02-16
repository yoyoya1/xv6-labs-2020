#include <kernel/types.h>
#include <kernel/param.h>
#include <user/user.h> 
#include <kernel/stat.h>
 
int
main(int argc, char* argv[]) {
	if (argc < 2) {
		fprintf(2, "You must be input command: ");
		exit(1);
	}
	char c;
	char* p;
	while (read(0, &c, sizeof(char)) == sizeof(char)) {
		char buf[512];
		p = buf;
		if (c != '\n') {
			*p = c;			
			++ p;
		} else {
			p = '\0';			
			char* argv_cop[MAXARG];
			for (int i = 1; i < argc; ++ i) {
				argv_cop[i - 1] = argv[i];				
				if (i == argc - 1) argv_cop[i] = buf;
			}
			if (fork() == 0) {	
				exec(argv[1], argv_cop);
			}
		}
		wait(0);
	}	
	exit(0);
}
