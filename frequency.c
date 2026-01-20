#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

  /* Enter your code here. Read input from STDIN. Print output to STDOUT */

  // Initialize array size 1000
  char s[1000];
  // Initialize array for output
  int freq[10] = {0};

  // Get input
  scanf("%[^\n]", s);
  // Loop by len of input
  for (int i = 0; i < strlen(s); i++) {
    // Check values against nums 0-9
    if (s[i] >= '0' && s[i] <= '9') {
      freq[s[i] - '0']++; // Add count at index
    }
  }
  // Loop thru to print count
  for (int i = 0; i < 10; i++) {
    printf("%d ", freq[i]);
  }

  return 0;
}
