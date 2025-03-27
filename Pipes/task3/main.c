#include "bash.h"

int main()
{
    char input_string[MAX_LEN];
    while(1)
    {       
        fgets(input_string, MAX_LEN, stdin);

        input_string[strcspn(input_string, "\n")] = '\0';
        if(strcmp(input_string, "exit") == 0)
            break;

        int res = execute_program(input_string);
        if(res == EXIT_FAILURE)
        {
            perror("Ошибки при выполнении программы");
            exit(-1);
        }

        printf("\n");
    }
}