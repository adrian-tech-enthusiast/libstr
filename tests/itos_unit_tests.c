#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/strutils.h"

/**
 * {@inheritdoc}
 */
int run_itos_unit_tests() {
  // Test case 1: Convert integer 30 to string
  char *a_converted_str = itos(30);
  char a_expected_str[] = "30";
  if (strcmp(a_converted_str, a_expected_str) != 0) {
    perror("Error: Converted int 30 does not match expected string '30'.");
    free(a_converted_str);
    return EXIT_FAILURE;
  }
  // Test case 2: Convert integer 6582 to string
  char *b_converted_str = itos(6582);
  char b_expected_str[] = "6582";
  if (strcmp(b_converted_str, b_expected_str) != 0) {
    perror("Error: Converted int 6582 does not match expected string '6582'.\n");
    free(a_converted_str);
    free(b_converted_str);
    return EXIT_FAILURE;
  }
  // Print success message.
  printf("[Passed] itos.\n");
  // Free the memory.
  free(a_converted_str);
  free(b_converted_str);
  // Return success status
  return EXIT_SUCCESS;
}
