#include "calc.h"

int main()
{
    void* lib = dlopen("./libcalculator.so", RTLD_LAZY);
    if (!lib) {
        printf("Не удалось загрузить библиотеку: %s\n", dlerror());
        return -1;
    }

    int (*add)(int, int) = dlsym(lib, "add");
    int (*sub)(int, int) = dlsym(lib, "sub");
    int (*mul)(int, int) = dlsym(lib, "mul");
    int (*div)(int, int) = dlsym(lib, "div");


    int variant = 1;
    int a, b;
    while(variant != 5){
        printf("Выберите пункт меню:\n");
        if (add) 
            printf("1) Сложение\n");
        if (sub) 
            printf("2) Вычитание\n");
        if (mul) 
            printf("3) Умножение\n");
        if (div) 
            printf("4) Деление\n");
        printf("5) Выход\n");
    
        if (!scanf("%d", &variant)) {
            printf("Введите число\n");
            scanf("%*s");
            continue;
        }
        if (variant > 5 || variant < 1) {
            printf("Выберите корректный вариант\n");
            continue;
        }
        if (variant == 5) break;
    
        printf("Введите числа, над которыми надо совершить операцию:\n");
        if (!scanf("%d", &a)) {
            printf("Введите число\n");
            scanf("%*s");
            continue;
        }
        if (!scanf("%d", &b)) {
            printf("Введите число\n");
            scanf("%*s");
            continue;
        }
        if (variant == 4 && b == 0 && div) {
            printf("Нельзя делить на 0\n");
            continue;
        }
    
        switch (variant) {
        case 1:
            if (add) 
                printf("Результат сложения %d и %d = %d\n", a, b, add(a, b));
            else 
                printf("Функция сложения недоступна\n");
            break;

        case 2:
            if (sub) 
                printf("Результат вычитания %d из %d = %d\n", a, b, sub(a, b));
            else 
                printf("Функция вычитания недоступна\n");
            break;
        case 3:
            if (mul) 
                printf("Результат умножения %d на %d = %d\n", a, b, mul(a, b));
            else 
                printf("Функция умножения недоступна\n");
            break;

        case 4:
            if (div)
                printf("Результат деления %d на %d = %d\n", a, b, div(a, b));
            else 
                printf("Функция деления недоступна\n");
            break;

            
        default:
            break;
        }
    }
    dlclose(lib);
    return 0;
}