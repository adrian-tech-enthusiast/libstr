#ifndef STRING_TOKENIZER_H
#define STRING_TOKENIZER_H

#include <stdlib.h>

/**
 * Struct definition for tokenizing a given string.
 */
struct StringTokenizer {

  /**
   * Pointer to the raw string.
   */
  char *string;

  /**
   * The length of the raw string.
   */
  size_t length;

  /**
   * The current position on the string.
   */
  size_t position;

  /**
   * The incremental factor for the string.
   */
  size_t incremental_factor;
};

/**
 * Create a new StringTokenizer instance.
 *
 * @param char *string
 *   The string to be tokenized.
 *
 * @return struct StringTokenizer*
 *   Pointer to the StringTokenizer instance, or NULL on failure.
 */
struct StringTokenizer *st_create(char *string);

/**
 * Create a StringTokenizer instance from an empty string of the given size.
 *
 * @param const size_t string_size
 *   The size of the string.
 *
 * @return struct StringTokenizer*
 *   Pointer to the StringTokenizer instance, or NULL on failure.
 */
struct StringTokenizer *st_create_empty(const size_t string_size);

/**
 * Frees the memory associated with a StringTokenizer instance.
 *
 * @param struct StringTokenizer* tokenizer
 *   Pointer to the tokenizer instance.
 */
void st_destroy(struct StringTokenizer *tokenizer);

/**
 * String tokenizer, Moves the cursor forward to the next valid character.
 *
 * @param struct StringTokenizer* tokenizer
 *   Pointer to the tokenizer instance.
 */
void st_next_token(struct StringTokenizer *tokenizer);

/**
 * String tokenizer, returns the current token element.
 *
 * @param struct StringTokenizer* tokenizer
 *   Pointer to the tokenizer instance.
 *
 * @return char
 *   The current token character.
 */
char st_current_token(struct StringTokenizer *tokenizer);

/**
 * String tokenizer, extracts a substring between the given delimiters.
 *
 * @param struct StringTokenizer* tokenizer
 *   Pointer to the tokenizer instance.
 * @param const char start_delim
 *   The start character on the basis of which the split will be done.
 * @param const char end_delim
 *   The end character on the basis of which the split will be done.
 *
 * @return char*
 *   Pointer to the extracted substring, or NULL on failure.
 */
char *st_sub_string(struct StringTokenizer *tokenizer, const char start_delim, const char end_delim);

/**
 * String tokenizer, extracts a slice of the string.
 *
 * @param struct StringTokenizer* tokenizer
 *   Pointer to the tokenizer instance.
 * @param const int length
 *   The length of the substring.
 *
 * @return char*
 *   Pointer to the extracted substring, or NULL on failure.
 */
char *st_slice_string(struct StringTokenizer *tokenizer, const int length);

/**
 * String tokenizer, extracts numbers from the string.
 *
 * @param struct StringTokenizer* tokenizer
 *   Pointer to the tokenizer instance.
 *
 * @return char*
 *   Pointer to the extracted numbers substring, or NULL on failure
 */
char *st_extract_numbers(struct StringTokenizer *tokenizer);

/**
 * String tokenizer, extracts a double value from the string.
 *
 * Extract numbers from string and converts them into to a floating-point
 * number (type double).
 *
 * @param struct StringTokenizer* tokenizer
 *   Pointer to the tokenizer instance.
 *
 * @return double*
 *   Pointer to the extracted double value, or NULL on failure.
 */
double *st_extract_double(struct StringTokenizer *tokenizer);

/**
 * String tokenizer, extracts a boolean value from the string.
 *
 * @param struct StringTokenizer* tokenizer
 *   Pointer to the tokenizer instance.
 * @param const char* bool_value
 *   The string representation of the boolean value.
 * @param const int int_value
 *   The integer representation of the boolean value.
 *
 * @return int*
 *   Pointer to the extracted boolean value as an int, or NULL on failure.
 */
int *st_extract_boolean(struct StringTokenizer *tokenizer, const char *bool_value, const int int_value);

/**
 * String tokenizer, Checks if the tokenizer starts with a given substring.
 *
 * @param struct StringTokenizer* tokenizer
 *   Pointer to the tokenizer instance.
 * @param const char *needle
 *   The substring to search for.
 *
 * @return int
 *   Returns 1 if the tokenizer starts with a given substring, otherwise 0.
 */
int st_starts_with(struct StringTokenizer *tokenizer, const char *needle);

/**
 * Checks if the tokenizer buffer has enough space for the requested string size.
 *
 * This function will try to reallocate more space if needed.
 *
 * @param struct StringTokenizer* tokenizer
 *   Pointer to the tokenizer instance.
 * @param const size_t size
 *   The requested string size to check.
 *
 * @return int
 *   Returns 1 if the tokenizer has enough space for the requested size, otherwise 0.
 */
int st_expand_string(struct StringTokenizer *tokenizer, const size_t size);

/**
 * String tokenizer, appends the given string to the tokenizer buffer.
 *
 * @param struct StringTokenizer* tokenizer
 *   Pointer to the tokenizer instance.
 * @param const char *string
 *   The string to append.
 *
 * @return int
 *   Returns 1 when the string was append, otherwise 0.
 */
int st_append_string(struct StringTokenizer *tokenizer, const char *string);

/**
 * String tokenizer, appends the given string to the tokenizer buffer, wrapped in double quotes.
 *
 * This function wraps the given string in double-quotes.
 *
 * @param struct StringTokenizer* tokenizer
 *   Pointer to the tokenizer instance.
 * @param const char *string
 *   The string to append.
 *
 * @return int
 *   Returns 1 when the string was append, otherwise 0.
 */
int st_append_quoted_string(struct StringTokenizer *tokenizer, const char *string);

/**
 * String tokenizer, appends the given double value to the tokenizer buffer, wrapped in double quotes.
 *
 * This function wraps the given string in double-quotes.
 *
 * @param struct StringTokenizer* tokenizer
 *   Pointer to the tokenizer instance.
 * @param const double *value
 *   The double value to append.
 *
 * @return int
 *   Returns 1 when the string was append, otherwise 0.
 */
int st_append_double(struct StringTokenizer *tokenizer, const double *value);

#endif /* STRING_TOKENIZER_H */

#ifndef IS_NUMERIC_H
#define IS_NUMERIC_H

/**
 * Determines if a character is a numeric token.
 *
 * @param const char token
 *   The character to validate.
 *
 * @return int
 *   Returns 1 if value is a number or a numeric string, 0 otherwise.
 */
static inline int is_numeric(const char token) {
  if (token == '-' || token == '+') {
    return 1;
  }
  if (token >= '0' && token <= '9') {
    return 1;
  }
  if (token == '.') {
    return 1;
  }
  if (token == 'e' || token == 'E') {
    return 1;
  }
  return 0;
}

#endif /* IS_NUMERIC_H */

#ifndef INTEGER_TO_STRING_H
#define INTEGER_TO_STRING_H

/**
 * Converts an integer into a numeric string.
 *
 * @param int value
 *   The integer value to convert.
 *
 * @return char*
 *   A pointer to the resulting numeric string, or NULL on failure.
 */
char *itos(int value);

#endif /* INTEGER_TO_STRING_H */
