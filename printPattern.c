#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  int n;
  scanf("%d", &n);
  // Complete the code to print the pattern.
  int rows = (n * 2) - 1;

  // Initial loops
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < rows; j++) {
      // Initialize variable to loop
      int top = i;
      int left = j;
      int bottom = rows - i - 1;
      int right = rows - j - 1;
      int middle = top;
      // Loops to determine number to print
      if (left < middle)
        middle = left;
      if (bottom < middle)
        middle = bottom;
      if (right < middle)
        middle = right;
      printf("%d ", n - middle);
    }
    printf("\n");
  }
  return 0;
}
