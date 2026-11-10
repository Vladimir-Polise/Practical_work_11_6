#include <stdio.h>
#include <windows.h>

/* Если мы компилируем первое задание (флаг -DTASK_1) */
#ifdef TASK_1
    #include "task_1.h"
    void run_task_1(void);
#elif defined(TASK_2)
    #include "task_2.h"
    void run_task_2(void);
#elif defined(TASK_3)
    #include "task_3.h"
    void run_task_3(void);
#endif



int main(void)
{
    SetConsoleOutputCP(65001);
    // SetConsoleCP(65001);         // ← ДОБАВИТЬ: ввод в UTF-8
    #ifdef TASK_1
        run_task_1();
    #elif defined(TASK_2)
        run_task_2();
    #elif defined(TASK_3)
        run_task_3();
    #else
        printf("Ошибка: не выбрано ни одно задание для компиляции!\n");
    #endif

    return 0;
}
