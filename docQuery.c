#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

char *kth_word_in_mth_sentence_of_nth_paragraph(char ****document, int k, int m,
                                                int n) {
  return document[n - 1][m - 1][k - 1];
}

char **kth_sentence_in_mth_paragraph(char ****document, int k, int m) {
  return document[m - 1][k - 1];
}

char ***kth_paragraph(char ****document, int k) { return document[k - 1]; }

char ****get_document(char *text) {
  // Count paragraphs
  int paragraph_count = 1;
  for (int i = 0; text[i]; i++) {
    if (text[i] == '\n') {
      paragraph_count++;
    }
  }
  // Allocate document
  char ****document = malloc(paragraph_count * sizeof(char ***));

  // Make modifiable copy
  char *text_copy = malloc(strlen(text) + 1);
  strcpy(text_copy, text);

  char *para_token = strtok(text_copy, "\n");
  int p = 0;

  while (para_token) {
    // Count sentences
    int sentence_count = 0;
    for (int i = 0; para_token[i]; i++) {
      if (para_token[i] == '.') {
        sentence_count++;
      }
    }
    char ***paragraph = malloc(sentence_count * sizeof(char **));

    int s = 0;
    int start = 0;

    for (int i = 0;; i++) {
      if (para_token[i] == '.' || para_token[i] == '\0') {
        int len = i - start;
        char *sentence_text = malloc(len + 1);
        strncpy(sentence_text, para_token + start, len);
        sentence_text[len] = '\0';

        // Count words
        int word_count = 1;
        for (int j = 0; sentence_text[j]; j++) {
          if (sentence_text[j] == ' ') {
            word_count++;
          }
        }
        char **sentence = malloc(word_count * sizeof(char *));

        int w = 0;
        int ws = 0;
        for (int j = 0;; j++) {
          if (sentence_text[j] == ' ' || sentence_text[j] == '\0') {
            int wlen = j - ws;
            sentence[w] = malloc(wlen + 1);
            strncpy(sentence[w], sentence_text + ws, wlen);
            sentence[w][wlen] = '\0';
            w++;
            if (sentence_text[j] == '\0') {
              break;
            }
            ws = j + 1;
          }
        }
        paragraph[s++] = sentence;
        free(sentence_text);

        if (para_token[i] == '\0') {
          break;
        }
        start = i + 1;
      }
    }
    document[p++] = paragraph;
    para_token = strtok(NULL, "\n");
  }
  return document;
}

char *get_input_text() {
  int paragraph_count;
  scanf("%d", &paragraph_count);

  char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
  memset(doc, 0, sizeof(doc));
  getchar();
  for (int i = 0; i < paragraph_count; i++) {
    scanf("%[^\n]%*c", p[i]);
    strcat(doc, p[i]);
    if (i != paragraph_count - 1)
      strcat(doc, "\n");
  }

  char *returnDoc = (char *)malloc((strlen(doc) + 1) * (sizeof(char)));
  strcpy(returnDoc, doc);
  return returnDoc;
}

void print_word(char *word) { printf("%s", word); }

void print_sentence(char **sentence) {
  int word_count;
  scanf("%d", &word_count);
  for (int i = 0; i < word_count; i++) {
    printf("%s", sentence[i]);
    if (i != word_count - 1)
      printf(" ");
  }
}

void print_paragraph(char ***paragraph) {
  int sentence_count;
  scanf("%d", &sentence_count);
  for (int i = 0; i < sentence_count; i++) {
    print_sentence(*(paragraph + i));
    printf(".");
  }
}

int main() {
  char *text = get_input_text();
  char ****document = get_document(text);

  int q;
  scanf("%d", &q);

  while (q--) {
    int type;
    scanf("%d", &type);

    if (type == 3) {
      int k, m, n;
      scanf("%d %d %d", &k, &m, &n);
      char *word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
      print_word(word);
    }

    else if (type == 2) {
      int k, m;
      scanf("%d %d", &k, &m);
      char **sentence = kth_sentence_in_mth_paragraph(document, k, m);
      print_sentence(sentence);
    }

    else {
      int k;
      scanf("%d", &k);
      char ***paragraph = kth_paragraph(document, k);
      print_paragraph(paragraph);
    }
    printf("\n");
  }
}
