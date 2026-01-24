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
char *ltrim(char *);
char *rtrim(char *);

int parse_int(char *);

/*
 * Complete the 'findSmallestMissingPositive' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY orderNumbers as parameter.
 */

int findSmallestMissingPositive(int orderNumbers_count, int *orderNumbers) {
  int n = orderNumbers_count;
  for (int i = 0; i < n; i++) {
    while (orderNumbers[i] >= 1 && orderNumbers[i] <= n &&
           orderNumbers[orderNumbers[i] - 1] != orderNumbers[i]) {

      int correct_idx = orderNumbers[i] - 1;
      int tmp = orderNumbers[i];
      orderNumbers[i] = orderNumbers[correct_idx];
      orderNumbers[correct_idx] = tmp;
    }
  }
  for (int i = 0; i < n; i++) {
    if (orderNumbers[i] != i + 1) {
      return i + 1;
    }
  }
  return n + 1;
}

int main() {
  int orderNumbers_count = parse_int(ltrim(rtrim(readline())));

  int *orderNumbers = malloc(orderNumbers_count * sizeof(int));

  for (int i = 0; i < orderNumbers_count; i++) {
    int orderNumbers_item = parse_int(ltrim(rtrim(readline())));

    *(orderNumbers + i) = orderNumbers_item;
  }

  int result = findSmallestMissingPositive(orderNumbers_count, orderNumbers);

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

char *ltrim(char *str) {
  if (!str) {
    return '\0';
  }

  if (!*str) {
    return str;
  }

  while (*str != '\0' && isspace(*str)) {
    str++;
  }

  return str;
}

char *rtrim(char *str) {
  if (!str) {
    return '\0';
  }

  if (!*str) {
    return str;
  }

  char *end = str + strlen(str) - 1;

  while (end >= str && isspace(*end)) {
    end--;
  }

  *(end + 1) = '\0';

  return str;
}

int parse_int(char *str) {
  char *endptr;
  int value = strtol(str, &endptr, 10);

  if (endptr == str || *endptr != '\0') {
    exit(EXIT_FAILURE);
  }

  return value;
}
