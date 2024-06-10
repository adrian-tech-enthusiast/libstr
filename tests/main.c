#include <stdlib.h>
#include <stdio.h>
#include "../include/strutils.h"
#include "itos_unit_tests.h"

/**
 * Main Unit Testing controller function.
 *
 * @param int argc
 *   The number of arguments passed by the user in the command line.
 * @param array argv
 *   Array of char, the arguments names.
 *
 * @return int
 *   The constant that represent the exit status.
 */
int main(int argc, char const *argv[]) {
  if (run_itos_unit_tests() == EXIT_FAILURE) {
    // Unit tests failed.
    return EXIT_FAILURE;
  }
  // @todo: Implement unit testing for string tokenizer functions and is_numeric function.
  printf("@todo: Implement unit tests for the StringTokenizer functions and the is_numeric function.\n");
  // Unit tests succeeded.
  return EXIT_SUCCESS;
}
