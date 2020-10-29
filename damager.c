#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define CHUNK_SIZE 8

int set_offset(int filesize, int pre_offset);

int main(int argc, char *argv[]) {

  int fd, offset, val, dev;
  off_t fp;
  void *junk;
  struct stat pt;

  
  //debes pasar un argumento
  if (argc < 2) {
    printf("You must pass a file path as argument\n");
    return 1;
  }

  printf("Working with file \"%s\"\n", argv[1]);

  fd = open(argv[1], O_RDWR, 0);

  fstat(fd, &pt);

  printf("The size of the file is %ld bytes\n", pt.st_size);

  //busco valores aleatorios menores al tamaño del archivo
  offset = rand() % pt.st_size;
  offset = set_offset(pt.st_size, offset);
  printf("The offsetwas set to %d\n", offset);

  //escribo datos aleatorios
  dev = open("/dev/random", O_RDONLY, 0);
  read(dev, &junk, CHUNK_SIZE);
  close(dev);
  val = pwrite(fd, &junk, 8, offset);
  if (val > 0) {
    printf("writen %d bytes of garbage on file\n", val);
  }
  else {
    fprintf(stderr, "error %d\n", val);
    return 1;
  }
  
  fsync(fd);
  close(fd);
    
}

set_offset(int filesize, int pre_offset) {

  if (pre_offset + CHUNK_SIZE > filesize) {
    return filesize - CHUNK_SIZE;
  }
  return pre_offset;
}
