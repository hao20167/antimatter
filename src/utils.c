#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

void* xmalloc(size_t sz) {
  void *ret = malloc(sz);
  if (ret == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  return ret;
}
