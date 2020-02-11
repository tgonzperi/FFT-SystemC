#include <sys/types.h>
#include <sys/mman.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CHENILLARD_BASEADDR 0x76200000

int main(int argc, char *argv[])
{
	int fd;
	void *ptr;

	fd = open(                       "/dev/mem"                        ,                                 O_RDWR                                        );
	if(fd          <                1){
		perror(argv[0]);
		return -1;
}

ptr= mmap(NULL, 128, PROT_READ|PROT_WRITE, MAP_SHARED, fd, CHENILLARD_BASEADDR);
*((unsigned int*)(ptr)) = 1;
*((unsigned int*)(ptr+4)) = 7;

munmap(ptr,128);
printf("mati culo *");
return 0;
}
