#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int fd;
	char read_buf[64] = {0};
	char write_buf[64] = "write data to kernel \n";
	
	fd = open("/dev/hello_misc", O_RDWR);
	printf("fd is %d \n", fd);
	
	if (fd < 0) {
		perror("open error \n");
		return fd;
	}

	read(fd, read_buf, sizeof(read_buf));
	printf("read from kernel %s \n", read_buf);
	
	write(fd, write_buf, sizeof(write_buf));

	close(fd);
	
	return 0;
}











