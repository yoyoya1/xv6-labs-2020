#include <kernel/types.h>
#include <kernel/stat.h>
#include <user/user.h>
#include <kernel/fs.h>

void 
find(char* path, char* FileName) {
	int fd_r;
	char buf[512], *p;
	struct dirent de;
	struct stat st;
	char* Fi = ".";
	char* Se = "..";
	
	if ((fd_r = open(path, 0)) < 0) {
		fprintf(2, "find: cannot open %s\n", path);
		return;
	}	
	while (read(fd_r, &de, sizeof(de)) == sizeof(de)) {
		if (de.inum == 0)
			continue;
		if (!strcmp(de.name, Fi) || !strcmp(de.name, Se))
			continue;
		
		strcpy(buf, path);
		p = buf + strlen(buf);
		*p++ = '/';
		memmove(p, de.name, DIRSIZ);
		
		if (stat(buf, &st) < 0) {
			fprintf(2, "find: cannot open %s\n", buf);
			return;
		}
		switch(st.type) {
		case T_FILE:
			if (strcmp(de.name, FileName) == 0) 
				printf("%s\n", buf);
			break;
		case T_DIR:
			find(buf, FileName);
		}
	}
	return; 
}

int 
main(int argc, char* argv[]) {
	int fd;
	char buf[512], *p;
	char* path = ".";
	struct stat st;
	if (argc < 2) {
		fprintf(2, "find: you need to appoint directory or file to find\n");
		exit(1);
	}
	if ((fd = open(argv[1], 0)) < 0) {
		fprintf(2, "find: cannot open %s\n", argv[1]);
		exit(1);
	}
	if (fstat(fd, &st) < 0) {
		fprintf(2, "find: cannot stat %s\n", argv[1]);
		close(fd);
		exit(1);
	}
	switch(st.type) {
	case T_FILE:
		for (int i = 1; i < argc; ++ i)
			find(path, argv[i]);
		break;
		
	case T_DIR:
		if (strcmp(path, argv[1]) == 0) {
			memmove(buf, argv[1], strlen(argv[1])+1);
	 	} else {	
			strcpy(buf, path);
			p = buf + strlen(buf);
			*p++ = '/';
			memmove(p, argv[1], strlen(argv[1])+1);
		}
		for (int i = 2; i < argc; ++ i)
			find(buf, argv[i]);
		break;	
	}
	close(fd);
	exit(0);
}
