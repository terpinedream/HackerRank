#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
  char *data;
};

struct sentence {
  struct word *data;
  int word_count; // denotes number of words in a sentence
};

struct paragraph {
  struct sentence *data;
  int sentence_count; // denotes number of sentences in a paragraph
};

struct document {
  struct paragraph *data;
  int paragraph_count; // denotes number of paragraphs in a document
};

char *str_duplicate(const char *src) {
  char *dst = malloc(strlen(src) + 1);
  strcpy(dst, src);
  return dst;
}

struct document get_document(char *text) {
  struct document doc;
  doc.data = NULL;
  doc.paragraph_count = 0;

  char *text_copy = str_duplicate(text);
  char *para_tok = strtok(text_copy, "\n");

  while (para_tok) {
    doc.data =
        realloc(doc.data, (doc.paragraph_count + 1) * sizeof(struct paragraph));
    struct paragraph *p = &doc.data[doc.paragraph_count];
    p->data = NULL;
    p->sentence_count = 0;

    char *para_copy =
        str_duplicate(para_tok); // duplicate before sentence splitting
    char *sent_tok = strtok(para_copy, ".");

    while (sent_tok) {
      // Skip empty sentences
      while (*sent_tok == '\0') {
        sent_tok = strtok(NULL, ".");
        if (!sent_tok)
          break;
      }
      if (!sent_tok)
        break;

      // Allocate new sentence
      p->data =
          realloc(p->data, (p->sentence_count + 1) * sizeof(struct sentence));
      struct sentence *s = &p->data[p->sentence_count];
      s->data = NULL;
      s->word_count = 0;

      // Duplicate sentence before splitting words
      char *sent_copy2 = str_duplicate(sent_tok);
      char *word_tok = strtok(sent_copy2, " ");
      while (word_tok) {
        s->data = realloc(s->data, (s->word_count + 1) * sizeof(struct word));
        s->data[s->word_count].data = str_duplicate(word_tok);
        s->word_count++;
        word_tok = strtok(NULL, " ");
      }
      free(sent_copy2);

      p->sentence_count++;
      sent_tok = strtok(NULL, ".");
    }

    free(para_copy);
    doc.paragraph_count++;
    para_tok = strtok(NULL, "\n");
  }

  free(text_copy);
  return doc;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc,
                                                      int k, int m, int n) {
  return Doc.data[n - 1].data[m - 1].data[k - 1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k,
                                              int m) {
  return Doc.data[m - 1].data[k - 1];
}

struct paragraph kth_paragraph(struct document Doc, int k) {
  return Doc.data[k - 1];
}

void print_word(struct word w) { printf("%s", w.data); }

void print_sentence(struct sentence sen) {
  for (int i = 0; i < sen.word_count; i++) {
    print_word(sen.data[i]);
    if (i != sen.word_count - 1) {
      printf(" ");
    }
  }
}

void print_paragraph(struct paragraph para) {
  for (int i = 0; i < para.sentence_count; i++) {
    print_sentence(para.data[i]);
    printf(".");
  }
}

void print_document(struct document doc) {
  for (int i = 0; i < doc.paragraph_count; i++) {
    print_paragraph(doc.data[i]);
    if (i != doc.paragraph_count - 1)
      printf("\n");
  }
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

int main() {
  char *text = get_input_text();
  struct document Doc = get_document(text);

  int q;
  scanf("%d", &q);

  while (q--) {
    int type;
    scanf("%d", &type);

    if (type == 3) {
      int k, m, n;
      scanf("%d %d %d", &k, &m, &n);
      struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
      print_word(w);
    }

    else if (type == 2) {
      int k, m;
      scanf("%d %d", &k, &m);
      struct sentence sen = kth_sentence_in_mth_paragraph(Doc, k, m);
      print_sentence(sen);
    }

    else {
      int k;
      scanf("%d", &k);
      struct paragraph para = kth_paragraph(Doc, k);
      print_paragraph(para);
    }
    printf("\n");
  }
}
