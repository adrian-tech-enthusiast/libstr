#include <stdlib.h>
#include <string.h>
#include "../include/strutils.h"

/**
 * {@inheritdoc}
 */
struct StringTokenizer *st_create(char *string) {
  if (string == NULL) {
    return NULL;
  }
  size_t length = strlen(string);
  if (length == 0) {
    return NULL;
  }
  size_t size = sizeof(struct StringTokenizer);
  struct StringTokenizer *tokenizer = (struct StringTokenizer *)malloc(size);
  if (tokenizer != NULL) {
    // Init String Tokenizer object properties.
    tokenizer->string = string;
    tokenizer->length = length;
    tokenizer->position = 0;
    tokenizer->incremental_factor = 0;
  }
  return tokenizer;
}

/**
 * {@inheritdoc}
 */
struct StringTokenizer *st_create_empty(const size_t string_size) {
  // Create the empty string.
  char *string = (char *)malloc(string_size + sizeof(""));
  if (string == NULL) {
    return NULL;
  }
  // Init an empty JSON string.
  memset(string, ' ', string_size);
  // Do the normal create.
  struct StringTokenizer *tokenizer = st_create(string);
  if (tokenizer == NULL) {
    free(string);
    return NULL;
  }
  // Set the incremental factor.
  tokenizer->incremental_factor = string_size;
  // Return the tokenizer instance.
  return tokenizer;
}

/**
 * {@inheritdoc}
 */
void st_destroy(struct StringTokenizer *tokenizer) {
  free(tokenizer);
  tokenizer = NULL;
}

/**
 * {@inheritdoc}
 */
void st_next_token(struct StringTokenizer *tokenizer) {
  do {
    // Move the cursor to the next position.
    tokenizer->position++;
  } while (tokenizer->string[tokenizer->position] <= 32 && tokenizer->position <= tokenizer->length);
}

/**
 * {@inheritdoc}
 */
char st_current_token(struct StringTokenizer *tokenizer) {
  return tokenizer->string[tokenizer->position];
}

/**
 * {@inheritdoc}
 */
char *st_sub_string(struct StringTokenizer *tokenizer, const char start_delim, const char end_delim) {
  // Get the current token in the tokenizer.
  char token = tokenizer->string[tokenizer->position];
  // Check the start of the string.
  if (token != start_delim) {
    // Not an string, early exit.
    return NULL;
  }
  // Move to the next token in the tokenizer.
  tokenizer->position++;
  token = tokenizer->string[tokenizer->position];
  // Calculate the length of the string.
  size_t start = tokenizer->position;
  while (token != '\0' && token != end_delim) {
    tokenizer->position++;
    token = tokenizer->string[tokenizer->position];
  }
  size_t end = tokenizer->position;
  size_t length = end - start;
  // Allocate enough space for the sub string.
  char *sub_string = (char *)malloc(length + sizeof(""));
  // Extract the sub string.
  size_t index = 0;
  for (int i = start; i < end; i++) {
    sub_string[index] = tokenizer->string[i];
    index++;
  }
  // Zero/null terminate sub string.
  sub_string[index] = '\0';
  // Returns the extracted substring.
  return sub_string;
}

/**
 * {@inheritdoc}
 */
char *st_slice_string(struct StringTokenizer *tokenizer, const int length) {
  // Ensure the requested lenght is under the limit.
  if (length > (tokenizer->length - tokenizer->position)) {
    return NULL;
  }
  // Allocate enough space for the requested string.
  char *sub_string = (char *)malloc(length + sizeof(""));
  // Extract the sub string.
  size_t index = 0;
  size_t end = tokenizer->position + length;
  while (tokenizer->position <= end) {
    sub_string[index] = tokenizer->string[tokenizer->position];
    tokenizer->position++;
    index++;
  }
  // Zero/null terminate sub string.
  sub_string[index] = '\0';
  // Returns the extracted substring.
  return sub_string;
}

/**
 * {@inheritdoc}
 */
char *st_extract_numbers(struct StringTokenizer *tokenizer) {
  // Get the current token in the tokenizer.
  char token = tokenizer->string[tokenizer->position];
  // Calculate the length of the numeric string.
  size_t start = tokenizer->position;
  while (token != '\0' && is_numeric(token) == 1) {
    tokenizer->position++;
    token = tokenizer->string[tokenizer->position];
  }
  size_t end = tokenizer->position;
  size_t length = end - start;
  // Set the pointer to the previous valid numeric character.
  tokenizer->position--;
  // Check if the string indeed contains numbers.
  if (length == 0) {
    return NULL;
  }
  // Allocate enough space for the string value.
  char *numbers = (char *)malloc(length + sizeof(""));
  // Extract the string.
  size_t index = 0;
  for (int i = start; i <= end; i++) {
    numbers[index] = tokenizer->string[i];
    index++;
  }
  // Zero/null terminate sub string.
  numbers[index] = '\0';
  // Returns the extracted numbers.
  return numbers;
}

/**
 * {@inheritdoc}
 */
double *st_extract_double(struct StringTokenizer *tokenizer) {
  // Extract numbers from string.
  char *numbers = st_extract_numbers(tokenizer);
  if (numbers == NULL) {
    return NULL;
  }
  // Convert the string numbers into a double value.
  size_t size = sizeof(double);
  double *value = (double *)malloc(size);
  *value = strtod(numbers, NULL);
  // Free the memory used for the string numbers.
  free(numbers);
  // Return the double pointer.
  return value;
}

int st_starts_with(struct StringTokenizer *tokenizer, const char *needle) {
  // Save current tokenizer position.
  size_t original_position = tokenizer->position;
  // Get the maximum number of characters to be extracted.
  size_t length = strlen(needle);
  // Extract the slice.
  char *extracted_string = st_slice_string(tokenizer, length);
  // Check if the extraction succeeded.
  if (extracted_string == NULL) {
    tokenizer->position = original_position;
    return 0;
  }
  // Check the extracted value vs the expected value.
  if (strncmp(extracted_string, needle, length) != 0) {
    tokenizer->position = original_position;
    free(extracted_string);
    return 0;
  }
  // Free the memory used for the extracted string.
  free(extracted_string);
  // Returns a success response.
  return 1;
}

/**
 * {@inheritdoc}
 */
int *st_extract_boolean(struct StringTokenizer *tokenizer, const char *bool_value, const int int_value) {
  // Search for the bool string.
  if (st_starts_with(tokenizer, bool_value) == 0) {
    return NULL;
  }
  // Allocate space for the bool value as int.
  int *value = (int *)malloc(sizeof(int));
  // Set the int value.
  *value = int_value;
  // Return the int pointer.
  return value;
}

/**
 * {@inheritdoc}
 */
int st_expand_string(struct StringTokenizer *tokenizer, const size_t size) {
  // Check if we have enough space in the tokenizer buffer to append the requested string.
  if ((tokenizer->position + size) < tokenizer->length) {
    // The buffer already has enough space for the requested string size.
    return 1;
  }
  // Determine the size to add to the buffer.
  size_t add_size = size > tokenizer->incremental_factor ? size : tokenizer->incremental_factor;
  size_t new_length = tokenizer->length + add_size;
  // Add more space to the buffer.
  char *string = (char *)realloc(tokenizer->string, new_length);
  if (string == NULL) {
    // Failed to add more space.
    return 0;
  }
  // Update the buffer string and the length.
  tokenizer->string = string;
  tokenizer->length = new_length;
  tokenizer->incremental_factor = add_size;
  // String size expansion completed.
  return 1;
}

/**
 * {@inheritdoc}
 */
int st_append_string(struct StringTokenizer *tokenizer, const char *string) {
  // Get the length of the string to append.
  size_t length = strlen(string);
  // Check if we have enough space in the tokenizer buffer to append the given string.
  if (st_expand_string(tokenizer, length) == 0) {
    return 0;
  }
  // Copy values to the tokenizer buffer.
  size_t index = 0;
  size_t end = tokenizer->position + length;
  while (tokenizer->position < end) {
    tokenizer->string[tokenizer->position] = string[index];
    tokenizer->position++;
    index++;
  }
  // Append string completed.
  return 1;
}

/**
 * {@inheritdoc}
 */
int st_append_quoted_string(struct StringTokenizer *tokenizer, const char *string) {
  if (st_append_string(tokenizer, "\"") == 0) {
    return 0;
  }
  if (st_append_string(tokenizer, string) == 0) {
    return 0;
  }
  if (st_append_string(tokenizer, "\"") == 0) {
    return 0;
  }
  return 1;
}

/**
 * {@inheritdoc}
 */
int st_append_double(struct StringTokenizer *tokenizer, const double *value) {
  // Buffer to hold the converted double value as a string.
  char string[32];
  // Convert double to string with 6 decimal places precision.
  char *result = gcvt(*value, 6, string);
  if (result == NULL) {
    return 0;
  }
  // Append the string to the tokenizer.
  return st_append_string(tokenizer, string);
}
