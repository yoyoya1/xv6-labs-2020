#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>

#define true 1

int 
main(int argc, char* argv[]) {
	close(0);
	int p1[2];
	pipe(p1);
	
	if (fork() == 0) {
		int x;
		int p2[2];
		pipe(p2);
		while (true) {
		      	read(p1[0], &x, sizeof(int));
		      	printf("prime %d\n", x);
			if (fork() != 0 || x == 35) {
				int Value;
				while (true) {
					read(p1[0], &Value, sizeof(int));
					if (Value % x != 0) 
						write(p2[1], &Value, sizeof(int));
					if (Value == 35) break;
				}			
				close(p1[0]);
				close(p2[1]);
				wait(0);
				exit(0);	
			} else {
				p1[0] = p2[0];	
				close(p1[1]);
			}
		}			

	} else {
		for (int i = 2; i <= 35; ++ i) 
			write(p1[1], &i, sizeof(int));
		close(p1[1]);
	}
	exit(0);
}
