#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <sys/types.h>

#include "utils.h"

#define BLOCK_SIZE (1024 * 1024)

int main() {
  char *rdisk = "/dev/rdisk4";
  int fd = open(rdisk, O_RDONLY);
  if (fd < 0) {
    perror("open rdisk");
    exit(EXIT_FAILURE);
  }
  
  uint8_t *buf = xmalloc(BLOCK_SIZE);
  off_t offset = 0;
  int cnt = 0;
  while (1) {
    ssize_t n = pread(fd, buf, BLOCK_SIZE, offset);
    if (n < 0) {
      fprintf(stderr, "pread error at offset=%d", offset);
      perror("pread");
      break;
    }
    if (n == 0) {
      break;
    }

    for (ssize_t i = 0; i < n; i++) {
      uint8_t byte = buf[i];
      if (byte == 0) continue;
      // printf("offset %lld: 0x%02X\n", offset + i, byte);
      printf("%02X ", byte);
      if (++cnt > 200) goto end;
    }

    offset += n;
  }

end:;

  free(buf);
  close(fd);

  return 0;
}
