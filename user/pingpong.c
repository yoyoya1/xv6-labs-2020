#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>

int
main (int argc, char* argv[]) {
	
	int p1[2], p2[2];
	char buf[512];
	char tmp[512] = {'B'};
	pipe(p1);
	pipe(p2);
	
	if (fork() == 0) {
		close(p1[1]);
		close(p2[0]);
		if (read(p1[0], buf, 1) == 1) 
			printf("<%d>: received ping\n", getpid());
		write(p2[1], buf, 1);
	} else {
		close(p1[0]);
		close(p2[1]);
		write(p1[1], tmp, 1);
		if (read(p2[0], buf, 1) == 1)
			printf("<%d>: received pong\n", getpid());
	}
	exit(0);
}
