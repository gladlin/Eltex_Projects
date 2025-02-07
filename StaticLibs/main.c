#include <stdio.h>
#include "function/calc.h"

int main()
{
    int variant = 1;
    int a, b;
    while(variant != 5){
        printf("Выберите пункт меню:\n1)Сложение\n2)Вычитание\n3)Умножение\n4)Деление\n5)Выход\n");
        if(!scanf("%d", &variant))
        {
            printf("Введите число\n");
            scanf("%*s"); //очистка мусора из буфера после некорректного ввода
            continue;
        }
        if (variant > 5 || variant < 1)
        {
            printf("Выберите корректный вариант\n");
            continue;
        }
        if(variant == 5)
            break;
        printf("Введите числа, над которыми надо совершить операцию:\n");
        if(!scanf("%d", &a))
        {
            printf("Введите число\n");
            scanf("%*s");
            continue;
        }
        if(!scanf("%d", &b))
        {
            printf("Введите число\n");
            scanf("%*s");
            continue;
        }
        if(variant == 4 && b == 0)
        {
            printf("Нельзя делить на 0\n");
            continue;
        }
        switch (variant)
        {
        case 1:
            printf("Результат сложения %d и %d = %d\n", a, b, add(a, b));
            break;

        case 2:
            printf("Результат вычитания %d из %d = %d\n", a, b, sub(a, b));
            break;
        
        case 3:
            printf("Результат умножения %d на %d = %d\n", a, b, mul(a, b));
            break;
        
        case 4:
            printf("Результат деления %d на %d = %d\n", a, b, div(a, b));
            break;
        
        default:
            break;
        }
    }
    return 0;
}
