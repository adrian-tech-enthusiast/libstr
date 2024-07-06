#ifndef NUMERIC_STRING_UNIT_TESTS_H
#define NUMERIC_STRING_UNIT_TESTS_H

/**
 * Runs all the unit tests for numeric string functions.
 *
 * @return int
 *   Returns EXIT_SUCCESS if all tests pass, otherwise returns EXIT_FAILURE.
 */
int run_numeric_string_tests();

/**
 * Run unit tests for the itos() function.
 *
 * This function tests the itos function with a set of predefined integers and their
 * corresponding string representations. It compares the output of itos with the expected
 * string values and prints the results.
 *
 * @return int
 *   Returns EXIT_SUCCESS if all tests pass, otherwise returns EXIT_FAILURE.
 */
int run_itos_unit_tests();

/**
 * Run unit tests for the ldtos() function.
 *
 * This function tests the ldtos function with a set of predefined long doubles and their
 * corresponding string representations. It compares the output of ldtos with the expected
 * string values and prints the results.
 *
 * @return int
 *   Returns EXIT_SUCCESS if all tests pass, otherwise returns EXIT_FAILURE.
 */
int run_ldtos_unit_tests();

/**
 * Run unit tests for the stold() function.
 *
 * This function tests the stold function with a set of predefined strings and their
 * corresponding long double values. It compares the output of stold with the expected
 * long double values and prints the results.
 *
 * @return int
 *   Returns EXIT_SUCCESS if all tests pass, otherwise returns EXIT_FAILURE.
 */
int run_stold_unit_tests();

#endif // NUMERIC_STRING_UNIT_TESTS_H