#include <stdio.h>
#include <stdlib.h>
#include "../include/strutils.h"

/**
 * {@inheritdoc}
 */
char *itos(int value) {
  // Calculate the length of the string.
  int n = value;
  int length = 1;
  while (n > 9) {
    length++;
    n /= 10;
  }
  // Create the string with the given length.
  size_t size = length * sizeof(char);
  char *number = (char *)malloc(size);
  if (number == NULL) {
    return NULL;
  }
  // @todo: sprintf's approach is slow, look for a faster and more robust solution.
  sprintf(number, "%d", value);
  // Returns the number string.
  return number;
}
