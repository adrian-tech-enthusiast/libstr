#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <errno.h>
#include "../include/strutils.h"

/**
 * {@inheritdoc}
 */
int run_itos_unit_tests() {
  // Define int and expected string values used for testing.
  int int_values[] = {0, -123, 456, 2147483647, -2147483648};
  const char *string_values[] = {"0", "-123", "456", "2147483647", "-2147483648"};
  // Calculate the number of values to test.
  int num_tests = sizeof(int_values) / sizeof(int_values[0]);
  // Show friendly message.
  printf("------------------- itos(x) -------------------\n");
  // Test the values.
  int exit_status = EXIT_SUCCESS;
  for (int i = 0; i < num_tests; i++) {
    int int_value = int_values[i];
    const char *string_value = string_values[i];
    char *result = itos(int_value);
    if (result == NULL) {
      printf("itos(%d) failed: returned NULL.\n", int_value);
      exit_status = EXIT_FAILURE;
      continue;
    }
    if (strcmp(result, string_value) != 0) {
      printf("itos(%d) failed: expected '%s', got '%s'\n", int_value, string_value, result);
      free(result);
      exit_status = EXIT_FAILURE;
      continue;
    }
    // Print success message.
    printf("[Passed] itos(%d) is '%s'.\n", int_value, result);
    free(result);
  }
  printf("\n");
  // Return exist status
  return exit_status;
}

/**
 * {@inheritdoc}
 */
int run_ldtos_unit_tests() {
  // Define long double and expected string values used for testing.
  long double ld_values[] = {0.0000000000000, -123.4561295663786, 789.0123456788999, 118.0472176809648, -118.0472176809648};
  char *string_values[] = {"0.0000000000000", "-123.4561295663786", "789.0123456788999", "118.0472176809648", "-118.0472176809648"};
  // Calculate the number of values to test.
  int num_tests = sizeof(ld_values) / sizeof(ld_values[0]);
  // Show friendly message.
  printf("------------------- ldtos(x) -------------------\n");
  // Test the values.
  int exit_status = EXIT_SUCCESS;
  for (int i = 0; i < num_tests; i++) {
    long double ld_value = ld_values[i];
    const char *string_value = string_values[i];
    char *result = ldtos(ld_value);
    if (result == NULL) {
      printf("[Failed] ldtos(%.13Lf) failed: returned NULL.\n", ld_value);
      exit_status = EXIT_FAILURE;
      continue;
    }
    if (strcmp(result, string_value) != 0) {
      printf("[Failed] ldtos(%.13Lf) failed: expected '%s', got '%s'\n", ld_value, string_value, result);
      free(result);
      exit_status = EXIT_FAILURE;
      continue;
    }
    // Print success message.
    printf("[Passed] ldtos(%.13Lf) is '%s'.\n", ld_value, result);
    free(result);
  }
  printf("\n");
  // Return exist status
  return exit_status;
}

/**
 * Helper function to compare two floating-point numbers.
 *
 * This function compares two floating-point numbers to see if they are within a small
 * epsilon range of each other.
 *
 * @param long double a
 *   The first floating-point number.
 * @param long double b
 *   The second floating-point number.
 * @param long double epsilon
 *   The tolerance range for comparison.
 *
 * @return int
 *   Returns 1 if the numbers are within the epsilon range, otherwise returns 0.
 */
static int compare_floats(long double a, long double b, long double epsilon) {
  return fabsl(a - b) < epsilon;
}

/**
 * {@inheritdoc}
 */
int run_stold_unit_tests() {
  // Define string and expected long double values used for testing.
  const char *string_values[] = {"0.0000000000000", "-123.4561295663786", "789.0123456788999", "118.0472176809648", "-118.0472176809648", "invalid"};
  long double ld_values[] = {0.0000000000000, -123.4561295663786, 789.0123456788999, 118.0472176809648, -118.0472176809648, 0.0L};
  // Calculate the number of values to test.
  int num_tests = sizeof(string_values) / sizeof(string_values[0]);
  // Show friendly message.
  printf("------------------- stold(x) -------------------\n");
  // Test the values.
  int exit_status = EXIT_SUCCESS;
  for (int i = 0; i < num_tests; i++) {
    const char *string_value = string_values[i];
    long double ld_value = ld_values[i];
    long double result = stold(string_value);
    if (errno != 0 && i != 5) {
      // Only "invalid" should set errno.
      printf("[Failed]  stold(\"%s\") failed: expected %.13Lf, got %.13Lf, and errno set to %d.\n", string_value, ld_value, result, errno);
      exit_status = EXIT_FAILURE;
      continue;
    }
    if (i == 5 && errno == 0) {
      printf("[Failed]  stold(\"%s\") failed: expected %.13Lf, got %.13Lf, and expected errno to be set.\n", string_value, ld_value, result);
      exit_status = EXIT_FAILURE;
      continue;
    }
    if (!compare_floats(result, ld_value, 0.0000000000001)) {
      printf("[Failed]  stold(\"%s\") failed: expected %.13Lf, got %.13Lf.\n", string_value, ld_value, result);
      exit_status = EXIT_FAILURE;
      continue;
    }
    // Print success message.
    printf("[Passed]  stold(\"%s\") is %.13Lf.\n", string_value, result);
  }
  printf("\n");
  // Return exist status
  return exit_status;
}

/**
 * {@inheritdoc}
 */
int run_numeric_string_tests() {
  // Run itos(x) unit tests.
  if (run_itos_unit_tests() == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }
  // Run ldtos(x) unit tests.
  if (run_ldtos_unit_tests() == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }
  // Run stold(x) unit tests.
  if (run_stold_unit_tests() == EXIT_FAILURE) {
    return EXIT_FAILURE;
  }
  // Return success status.
  return EXIT_SUCCESS;
}
