#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../include/strutils.h"

#define NUMERIC_STRING_MAX_SIZE 100
#define NUMERIC_STRING_PRECISION 13

/**
 * {@inheritdoc}
 */
char *itos(int value) {
  // Estimate the buffer size needed for the conversion
  size_t buffer_size = snprintf(NULL, 0, "%d", value) + 1;
  char *str = (char *)malloc(buffer_size);
  if (str == NULL) {
    return NULL; // Memory allocation failed
  }
  // @todo: sprintf's approach is slow, look for a faster and more robust solution.
  snprintf(str, buffer_size, "%d", value);
  return str;
}

/**
 * {@inheritdoc}
 */
char *ldtos(long double value) {
  // Allocate memory for the resulting string.
  char *str = (char *)malloc(NUMERIC_STRING_MAX_SIZE);
  if (str == NULL) {
    return NULL; // Memory allocation failed
  }
  snprintf(str, NUMERIC_STRING_MAX_SIZE, "%.*Lf", NUMERIC_STRING_PRECISION, value);
  return str;
}

/**
 * {@inheritdoc}
 */
long double stold(const char *numeric_string) {
  char *endptr;
  errno = 0; // Reset errno before the call
  long double value = strtold(numeric_string, &endptr);

  if (errno != 0) {
    return 0; // Conversion error occurred
  }
  if (*endptr != '\0') {
    errno = EINVAL; // Not all input was converted
    return 0;
  }
  return value;
}
