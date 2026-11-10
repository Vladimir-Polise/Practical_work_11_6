#include "task_1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/*Функция уборщик, очищает ввод с онсоли перед чтением*/
void clear_input(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

/* Создаем глобальный массив один раз и зануляем его*/
Student journal[MAX_STUDENT] = {0}; 

/*В этой функции находится задание 1 - вызывается препроцессором. Флаг при компиляции TASK=1*/
void run_task_1(void){
    srand(time(NULL));
    default_journal(journal);                                   /*заполнили журнал по умолчанию*/
    int choose = 1;
    int count = global_count_student(journal, MAX_STUDENT);     /*посчитали сколько учеников в классе*/
    sort_journal_by_average(journal, count);                    /*ранжирование учеников*/
    print_journal(journal, count);                              /*функцию, которая красиво отрисовывает весь журнал*/
    while (1)  {
        printf("\n--- МЕНЮ ---\n");
        printf("1. Заполнить журнал (редактировать оценки)\n");
        printf("2. Добавить ученика\n");
        printf("3. Рассчитать зависимость успеваемости от пола\n");
        printf("0. Выход\n");
        printf("Ваш выбор: ");

        if (scanf("%d", &choose) != 1) {
            clear_input();                                      /*Если ввели букву*/
            printf("Ошибка: введите число.\n");
            continue;                                           /* Идем в начало цикла*/
        }
        
        switch (choose)  {
            case 1:
                journal_editing(journal, count);            /*Редактирует журнал*/
                sort_journal_by_average(journal, count);    /*Сортирует массив для релевнтнго вывода*/
                print_journal(journal, count);              /*Печатает журнал*/
                break;

            case 2:
                add_student(journal, &count);
                // count = global_count_student(journal, MAX_STUDENT); // Кол-во изменилось!
                sort_journal_by_average(journal, count);
                print_journal(journal, count);
                break;

            case 3:
                analyze_gender_dependence(journal, count);
                break;

            case 0:
            printf("Выход из программы. До свидания!\n");
            return; // Выходим из функции, а значит и из цикла
                break;
            default:
                printf("Неверный выбор. Попробуйте еще раз.\n");
                break;            }
    }
}
/*Функция которая подсчитает количество учеников в классе*/
int global_count_student(const Student journal[], int max_size){
    int count = 0;
    for (int i = 0; i < max_size; i++)  {
        if (journal[i].id_student == 0)  {
            return count;}
        count++;
    }
    return count;
}

/*Функция устанавливающая параметры журнала по дефолту, принимает параметром массив структур. 
Ничего не возвращает, а изменяет ро указателю массив структур. */
void default_journal(Student journal[])  {

    strcpy(journal[0].first_name, "Федор");
    strcpy(journal[0].second_name, "Федорович");
    strcpy(journal[0].surname, "Иванов");
    journal[0].gender = MALE;
    journal[0].class_num = 9; 
    journal[0].id_student = 1;
    for (int i = 0; i < 3; i++)  {
        journal[0].biology[i] = rand() % 4 + 2;
        journal[0].physics[i] = rand() % 4 + 2;
        journal[0].work[i] = rand() % 4 + 2;
    }

    strcpy(journal[1].first_name, "Петр");
    strcpy(journal[1].second_name, "Петрович");
    strcpy(journal[1].surname, "Петров");
    journal[1].gender = MALE;
    journal[1].class_num = 9; 
    journal[1].id_student = 2;
    for (int i = 0; i < 3; i++)  {
        journal[1].biology[i] = rand() % 4 + 2;
        journal[1].physics[i] = rand() % 4 + 2;
        journal[1].work[i] = rand() % 4 + 2;
    }

    strcpy(journal[2].first_name, "Алиса");
    strcpy(journal[2].second_name, "Марковна");
    strcpy(journal[2].surname, "Сидорова");
    journal[2].gender = FEMALE;
    journal[2].class_num = 9; 
    journal[2].id_student = 3;
    for (int i = 0; i < 3; i++)  {
        journal[2].biology[i] = rand() % 4 + 1;
        journal[2].physics[i] = rand() % 4 + 1;
        journal[2].work[i] = rand() % 4 + 1;
    }
    
    strcpy(journal[3].first_name, "Ольга");
    strcpy(journal[3].second_name, "Олеговна");
    strcpy(journal[3].surname, "Смирнова");
    journal[3].gender = FEMALE;
    journal[3].class_num = 9; 
    journal[3].id_student = 4;
    for (int i = 0; i < 3; i++)  {
        journal[3].biology[i] = rand() % 4 + 1;
        journal[3].physics[i] = rand() % 4 + 1;
        journal[3].work[i] = rand() % 4 + 1;
    }
}

/*Функция подсчета среднего балла по предмету, передача структуры по указателю const.*/
float get_subject_average(const int grades[], int max_lessons)  {
    int over_count = 0; /*сумма оценок*/
    int over_index = 0; /*количество уроков без нулей*/
    for (int i = 0; i < max_lessons; i++)  {
        if (grades[i] != 0)  { /*нет валиодации, мы ее предусмотрим в функции заполнения журнала*/
            over_count += grades[i];
            over_index++;
        }
    }

    if (over_index == 0)  {
        return 0.0;    
    }
    
    return ((float)over_count/over_index);
}

/*отладочная функция которая берет студента и печатает его средний балл дважды: целое число и 
float с двумя знаками (%.2f).*/
/* Отладочная функция */
void print_average(const Student *s)  {
    /* Используем s->biology для доступа к полю через указатель */
    float avg = get_student_average(s); 
    
    printf("\nСредний балл по всем предметамм для %s: %d (или %.2f)\n", 
           s->surname, 
           (int)avg,  /* Округляем для вывода int */
           avg);      /* Выводим float с 2 знаками */
}

/*Функция для подсчета общего среднего балла ученика (по всем трем предметам).*/
float get_student_average(const Student *s)  {
    float bio = get_subject_average(s->biology, MAX_LESSON);
    float phys = get_subject_average(s->physics, MAX_LESSON);
    float work = get_subject_average(s->work, MAX_LESSON);
    return (bio + phys + work) / 3.0;
}

/* Функция-компаратор для qsort. Сортирует по убыванию среднего балла */
static int compare_students(const void *a, const void *b) {
    /* Приводим void* к Student* */
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    
    /* Получаем средние баллы */
    float avg1 = get_student_average(s1);
    float avg2 = get_student_average(s2);
    
    /* 
     * qsort ожидает:
     * < 0, если s1 должно быть выше s2
     * > 0, если s1 должно быть ниже s2
     * = 0, если они равны
     * Нам нужно по УБЫВАНИЮ, поэтому если avg1 меньше avg2, возвращаем 1 (s1 идет вниз).
     */
    if (avg1 < avg2) return 1;
    if (avg1 > avg2) return -1;
    return 0;
}

/*Сортировка журнала "Ранжировать учеников в классе по успеваемости... 
у кого средний бал выше - тот находится в верху списка вывода"*/
void sort_journal_by_average(Student journal[], int count)  {
    /* qsort(массив, количество элементов, размер элемента, компаратор) */
    qsort(journal, count, sizeof(Student), compare_students);
}

/*функцию, которая красиво отрисовывает весь журнал.*/
void print_journal(const Student journal[], int count)  {
    /*---------------------------------------------Шапка---------------------------------------------*/
    float subject_average;
    printf("Количество учеников в классе - %-3d из 100 возможных \n", count);  
    printf("Фамилия        Имя     Отчество    Пол     Клас          \n");
    int size_row = 74;
    for (int i = 0; i < size_row; i++)  {  printf("=");  }
    /*---------------------------------------------ФИО/ШШапка предметов------------------------------*/
    for (int i = 0; i < count; i++) {
        printf("\n%d. ",journal[i].id_student);
        printf("%-20s %-12s %-15s", journal[i].surname, journal[i].first_name, journal[i].second_name);
        if (journal[i].gender == MALE)  {
            printf("    муж.");        
        }else{  printf("    жен.");  }
        printf("   %d", journal[i].class_num);
        printf("                   Средн. бал\n");
        printf("        Предмет    ");
        for (int k = 0; k < MAX_LESSON; k++)  { printf("%d   ", k+1); }

    /*---------------------------------------------Биология------------------------------------------*/
        printf("\n    1.  Биология   ");
        for (int j = 0; j < MAX_LESSON; j++)  {
            if (journal[i].biology[j] != 0)  {
                printf("%d   ",journal[i].biology[j]);
            }else  {
                printf("   ");
            }    
        }
        subject_average = get_subject_average(journal[i].biology, MAX_LESSON);
        printf("        %d (или %.2f)",(int)subject_average, subject_average);

    /*---------------------------------------------Физика--------------------------------------------*/
        printf("\n    2.  Физика     ");
        for (int j = 0; j < MAX_LESSON; j++)  {
            if (journal[i].physics[j] != 0)  {
                printf("%d   ",journal[i].physics[j]);
            }else  {
                printf("   ");
            }    
        }
        subject_average = get_subject_average(journal[i].physics, MAX_LESSON);
        printf("        %d (или %.2f)",(int)subject_average, subject_average);

    /*---------------------------------------------Труд----------------------------------------------*/
        printf("\n    3.  Труд       ");
        for (int j = 0; j < MAX_LESSON; j++)  {
            if (journal[i].work[j] != 0)  {
                printf("%d   ",journal[i].work[j]);
            }else  {
                printf("   ");
            }    
        }
        subject_average = get_subject_average(journal[i].work, MAX_LESSON);
        printf("        %d (или %.2f)",(int)subject_average, subject_average);

        printf("\n");
        for (int i = 0; i < size_row; i++)  {  printf("-");  }    
    }    
}

/*валидация ввода номера студента*/
bool validate_num_student(int count, int student_number)  {
    return (student_number > 0) && (student_number <= count);
}
/*валидация ввода номера предмета*/
bool validate_lesson_number(int lesson_number)  {
    return (lesson_number > 0) && (lesson_number <= 3);
}
/*валидация ввода номера урока*/
bool validate_subject_number(int subject_number)  {
    return (subject_number >=1) && (subject_number <= MAX_LESSON);
}
/*валидация ввода оценки за урок*/
bool validate_lesson_grade(int lesson_grade)  {
    return (lesson_grade >= 1) && (lesson_grade <= 5);
}
/*Валидация ввода пола*/
bool validate_add_gender(int gender)  {
    return (gender >= 1) && (gender <= 2);
}
/*Валидация ввода класса*/
bool validate_add_class(int add_class)  {
    return (add_class >= 1) && (add_class <= 11);
}

/*Редактирует журнал*/
void journal_editing(Student journal[], int count) {
    printf("Редактирование журнала...\n");
    /*Обрабатываем запрос на студента*/
    int student_number = 0;
    while (1)  {
        printf("Выберите № Ученика 1....%d\n", count);
        if (scanf("%d", &student_number) != 1)  {
            clear_input();
            printf("Ошибка: не число.\n");
            continue;
        }
        if (!validate_num_student(count, student_number))        {
            printf("Ошибка, введите 1...%d\n", count);
            clear_input();
            continue;
        }
        break;
    }

    /*Обрабатываем запрос на предмет*/
    int lesson_number = 0; 
    while (1)  {
        printf("Выберите № Предмета 1...3\n");
        printf("Выберите Биология - 1\n");
        printf("Выберите Физика   - 2\n");
        printf("Выберите Труд     - 3\n");
        if (scanf("%d", &lesson_number) != 1)  {
            clear_input();
            printf("Ошибка: не число.\n");
            continue;
        }
        if (!validate_lesson_number(lesson_number))        {
            printf("Ошибка, введите 1...3\n");
            clear_input();
            continue;
        }
        break;
    }

    /*Обрабатываем запрос на номер урока*/
    int subject_number = 0; 
    while (1)  {
        printf("Выберите № Урока 1...10\n");
        if (scanf("%d", &subject_number) != 1)  {
            clear_input();
            printf("Ошибка: не число.\n");
            continue;
        }
        if (!validate_subject_number(subject_number))        {
            printf("Ошибка, введите 1...10\n");
            clear_input();
            continue;
        }
        break;
    }

    /*Обработка запроса устанавливающего оценку за урок*/
    int lesson_grade = 0;
    while (1)  {
        printf("Выберите оценку за урок 1...5\n");
        if (scanf("%d", &lesson_grade) != 1)  {
            clear_input();
            printf("Ошибка: не число.\n");
            continue;
        }
        if (!validate_lesson_grade(lesson_grade))        {
            printf("Ошибка, введите 1...5\n");
            clear_input();
            continue;
        }
        break;
    }

    /*Проставыляем оценки в журнал, по предметам*/
    /*Биология*/
    if (lesson_number == 1)  {
        for (int i = 0; i < count; i++)  {
            if (journal[i].id_student == student_number)  {
                journal[i].biology[subject_number - 1] = lesson_grade;
            }
        }
    }

    /*Физика*/
    if (lesson_number == 2)  {
        for (int i = 0; i < count; i++)  {
            if (journal[i].id_student == student_number)  {
                journal[i].physics[subject_number - 1] = lesson_grade;
            }
        }
    }

    /*Труд*/
    if (lesson_number == 3)  {
        for (int i = 0; i < count; i++)  {
            if (journal[i].id_student == student_number)  {
                journal[i].work[subject_number - 1] = lesson_grade;
            }
        }
    }
    
}

/*Добавление ученика*/
void add_student(Student journal[], int *count)  {
    /*- Проверика, есть ли вообще место в массиве (если *count >= MAX_STUDENT, вывести ошибку и выйти).*/
    if (*count >= MAX_STUDENT) {
        printf("Ошибка, в журнале нет места для новой записи %d\n", *count);
        return;
    }
    
    clear_input();
    int new_index = *count; 
    journal[new_index].id_student = new_index + 1;                          // присваиваем йд студенту
    printf("Студенту присвоен ID %d\n", journal[new_index].id_student);
    printf("Введите Фамилию студента (не более - 50 символов) :");
    fgets(journal[new_index].surname, SIZE_NAME, stdin);
    journal[new_index].surname[strcspn(journal[new_index].surname, "\n")] = '\0'; // Убираем \n
    
    printf("\nВведите  Имя студента (не более - 50 символов) :");
    fgets(journal[new_index].first_name, SIZE_NAME, stdin);
    journal[new_index].first_name[strcspn(journal[new_index].first_name, "\n")] = '\0';
    
    printf("\nВведите  Отчество студента (не более - 50 символов) :");
    fgets(journal[new_index].second_name, SIZE_NAME, stdin);
    journal[new_index].second_name[strcspn(journal[new_index].second_name, "\n")] = '\0';
    printf("я принт, я сработал %-20s %-12s %-15s", journal[4].surname, journal[4].first_name, journal[4].second_name);

    /*обработка запроса на пол + валидация ввода*/
    while (1)  {
        printf("\nЗадайте пол студента, введите 1 - 2 :");
        printf("\nМужской - 1");
        printf("\nЖенский - 2");
        int gender = 0;
        if (scanf("%d", &gender) != 1)  {
            clear_input();
            printf("Ошибка: не число.\n");
            continue;
        }
        if (!validate_add_gender(gender))        {
            printf("Ошибка, введите 1...2\n");
            clear_input();
            continue;
        }
        if (gender == 1)  {  journal[new_index].gender = MALE;  }
        if (gender == 2)  {  journal[new_index].gender = FEMALE;  }
        break;
    }

    /*обработка запроса на класс + валидация ввода*/
    while (1)  {
        printf("\nВведите Класс обучения студента 1....11 :");
        int add_class = 0;
        if (scanf("%d", &add_class) != 1)  {
            clear_input();
            printf("Ошибка: не число.\n");
            continue;
        }
        if (!validate_add_class(add_class))  {
            printf("Ошибка, введите 1...11\n");
            clear_input();
            continue;
        }
        journal[new_index].class_num = add_class;
        break;
    }

    /*Подготовка журнала - очистка оценок*/
    for (int i = 0; i < MAX_LESSON; i++)  {
        journal[new_index].biology[i] = 0;
        journal[new_index].physics[i] = 0;
        journal[new_index].work[i]    = 0; 
    }
    /*увеличиваем количество учеников*/
    (*count)++;
    printf("Ученик успешно добавлен!\n");
}

/*Рассчитать зависимость успеваемости ученика от пола*/
void analyze_gender_dependence(const Student journal[], int count)  {
    printf("Рассчитать зависимость успеваемости ученика от пола\n");
    /*ввод и валидация данных */
    int id_studend = 0;             // это его ID
    int index_main_student = 0;     // это его индекс
    while (1)  {
        printf("Введите ID Студента 1...%d\n", count);
        if (scanf("%d", &id_studend) != 1)  {
            clear_input();
            printf("Ошибка: не число.\n");
            continue;
        }
        if (!validate_num_student(count, id_studend))        {
            printf("Ошибка, введите 1...%d\n", count);
            clear_input();
            continue;
        }
        break;
    }
    /*находим главного студента в массиве структур и запоминаем индекс*/
    for (int i = 0; i < count; i++)  {
        if (journal[i].id_student == id_studend)  { index_main_student = i;  }
    }

    float female_sum = 0;                                /*Здесь храним сумму средних баллов девочек*/
    float female_count = 0;                              /*Здесь считаем сколько их*/
    float male_sum = 0;                                  /*Здесь храним сумму средних баллов мальчиков*/
    float male_count = 0;                                /*Здесь считаем сколько их*/
    float male_avg = 0;                                  /*результат вычисления*/
    float female_avg = 0;                                /*результат вычисления*/


    for (int i = 0; i < count; i++){
        if (journal[i].id_student != id_studend)  {
            if (journal[i].gender == MALE)  {
                male_count++;
                male_sum += get_student_average(&journal[i]);
            }

            if (journal[i].gender == FEMALE)  {
                female_count++;
                female_sum += get_student_average(&journal[i]);
            }
        }
    }
    if (male_count != 0)  {
        male_avg = male_sum / male_count; 
    }else{
        male_avg = 0;
    }

    if (female_count != 0)  {
        female_avg = female_sum / female_count; 
    }else  {
        female_avg = 0;
    }

    float target_avg = get_student_average(&journal[index_main_student]);       /*средний балл главного студента*/

    if (target_avg >= female_avg)  {
        printf("Студент %s  %s %s \n", journal[index_main_student].first_name, journal[index_main_student].second_name, 
            journal[index_main_student].surname);
        printf("Учащийся в %d классе, ID - %d\n", journal[index_main_student].class_num, journal[index_main_student].id_student);
        printf("Имеет средний бал по всем предметам - %.3f  \n", target_avg); 
        printf("Превосходит в обучении девушек на %.3f,балла\n", target_avg - female_avg); 
    }else  {
        printf("Студент %s  %s %s \n", journal[index_main_student].first_name, journal[index_main_student].second_name, 
            journal[index_main_student].surname);
        printf("Учащийся в %d классе, ID - %d\n", journal[index_main_student].class_num, journal[index_main_student].id_student);
        printf("Имеет средний бал по всем предметам - %.3f  ", target_avg); 
        printf("И отстает в обучении от девушек на %.3f,балла\n", target_avg - female_avg);
    }

    if (target_avg >= male_avg)  {
        printf("И превосходит в обучении сокурсников на %.3f,балла\n", target_avg - male_avg); 
    }else  {
        printf("И отстает в обучении от сокурсников на %.3f,балла\n", target_avg - male_avg);
    }
    
}