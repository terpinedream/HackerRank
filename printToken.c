#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  char *s;
  s = malloc(1024 * sizeof(char));
  scanf("%[^\n]", s);
  s = realloc(s, strlen(s) + 1);
  // Write your logic to print the tokens of the sentence here.
  char *delim = " ";
  char *strtok(char *s, const char *delim);
  char *token = strtok(s, delim);

  while (token != NULL) {
    printf("%s\n", token);
    token = strtok(NULL, delim);
  }
  return 0;
}
