#include "execute.h"

int main() {
  int status = getParams();
  if (WEXITSTATUS(status) == -1)
    perror("\nОшибки при выполнении программы");

  else
    printf("\nВсе прошло успешно");

  return 0;
}