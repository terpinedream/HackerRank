#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readline();

/*
 * Complete the 'isAlphabeticPalindrome' function below.
 *
 * The function is expected to return a BOOLEAN.
 * The function accepts STRING code as parameter.
 */

bool isAlphabeticPalindrome(char *code) {
  if (!code || !*code) {
    return 1;
  }

  int left = 0;
  int right = strlen(code) - 1;

  while (left < right) {
    while (left < right && !((code[left] >= 'A' && code[left] <= 'Z') ||
                             (code[left] >= 'a' && code[left] <= 'z'))) {
      left++;
    }
    while (left < right && !((code[right] >= 'A' && code[right] <= 'Z') ||
                             (code[right] >= 'a' && code[right] <= 'z'))) {
      right--;
    }
    if (left < right) {
      char l = code[left];
      char r = code[right];

      if (l >= 'A' && l <= 'Z') {
        l += 32;
      }
      if (r >= 'A' && r <= 'Z') {
        r += 32;
      }

      if (l != r) {
        return 0;
      }
      left++;
      right--;
    }
  }
  return 1;
}

int main() {
  char *code = readline();

  bool result = isAlphabeticPalindrome(code);

  printf("%d\n", result);

  return 0;
}

char *readline() {
  size_t alloc_length = 1024;
  size_t data_length = 0;

  char *data = malloc(alloc_length);

  while (true) {
    char *cursor = data + data_length;
    char *line = fgets(cursor, alloc_length - data_length, stdin);

    if (!line) {
      break;
    }

    data_length += strlen(cursor);

    if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
      break;
    }

    alloc_length <<= 1;

    data = realloc(data, alloc_length);

    if (!data) {
      data = '\0';

      break;
    }
  }

  if (data[data_length - 1] == '\n') {
    data[data_length - 1] = '\0';

    data = realloc(data, data_length);

    if (!data) {
      data = '\0';
    }
  } else {
    data = realloc(data, data_length + 1);

    if (!data) {
      data = '\0';
    } else {
      data[data_length] = '\0';
    }
  }

  return data;
}
