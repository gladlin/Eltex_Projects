#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 256

char *findString(char *user_String, char *substring) {
  char *new_string = substring;
  while (*user_String != '\0') {
    if (*user_String == *substring) {
      char *firstLetter = user_String;
      int isSub = 1;
      while (*new_string != '\0') {
        if (*new_string != *user_String) {
          isSub = 0;
          break;
        }

        new_string++;
        user_String++;
      }
      if (isSub)
        return firstLetter;
      user_String = firstLetter;
      new_string = substring;
    }
    user_String++;
  }

  return NULL;
}

int main() {
  char *user_String = malloc(sizeof(char) * MAX_SIZE);
  printf("Enter string, where will be executing search of substring: ");
  scanf("%255s", user_String);

  char *substring = malloc(sizeof(char) * MAX_SIZE);
  printf("\nPrint substring: ");
  scanf("%255s", substring);

  char *result = findString(user_String, substring);
  printf("Result: %s\n", result);
  free(user_String);
  free(substring);
  return 0;
}