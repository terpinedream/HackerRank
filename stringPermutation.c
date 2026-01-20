#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(int i, int j, char **s) {
  char *tmp = s[i];
  s[i] = s[j];
  s[j] = tmp;
}

int find_next_fix(int n, char **s) {
  for (int k = 1; k < n; k++) {
    if (strcmp(s[0], s[k]) < 0) {
      swap(0, k, s);
      return 1;
    }
  }
  return 0;
}

void restore_sequence(int n, char **s) {
  for (int k = 1; k < n; k++) {
    swap(k - 1, k, s);
  }
}

int next_permutation(int n, char **s) {
  /**
   * Complete this method
   * Return 0 when there is no next permutation and 1 otherwise
   * Modify array s to its next permutation
   */
  if (n == 1)
    return 0;
  if (next_permutation(n - 1, s + 1))
    return 1;
  if (find_next_fix(n, s))
    return 1;
  restore_sequence(n, s);
  return 0;
}

int main() {
  char **s;
  int n;
  scanf("%d", &n);
  s = calloc(n, sizeof(char *));
  for (int i = 0; i < n; i++) {
    s[i] = calloc(11, sizeof(char));
    scanf("%s", s[i]);
  }
  do {
    for (int i = 0; i < n; i++)
      printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
  } while (next_permutation(n, s));
  for (int i = 0; i < n; i++)
    free(s[i]);
  free(s);
  return 0;
}
