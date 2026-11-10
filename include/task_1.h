#ifndef TASK_1_INCLUDED
#define TASK_1_INCLUDED

#include <stdbool.h>
void run_task_1(void);
void clear_input(void);
/* ============================================================================
*  КОНСТАНТЫ (enum)
*    - enum — типизирован, работает везде, виден компилятору.
* ============================================================================ */
/*Список констан - описывает пол ученика. Списку присваивается имя по умолчанию Gender*/
typedef enum { 
    MALE, FEMALE 
} Gender;

enum {
    MAX_STUDENT         = 100, /*Максимальное колличество учеников*/
    SIZE_NAME           = 50, /*Максимальная длинна имени/фамилии и отчества*/
    MAX_LESSON          = 10, /*Максимальное колличество уроков*/
};

/*Наша основная рабочая лошадка StudentRecord*/
/*пишем typedef struct, чтобы потом не писать слово struct каждый раз.*/
typedef struct{
    char surname[SIZE_NAME];        /*Фамилия*/
    char first_name[SIZE_NAME];     /*Имя*/
    char second_name[SIZE_NAME];    /*Отчество*/
    Gender gender;                  /*Пол*/
    int class_num;                  /*Класс*/
    int id_student;                 /*id student*/
    int biology[MAX_LESSON];        /*Предмет*/
    int physics[MAX_LESSON];        /*Предмет*/
    int work[MAX_LESSON];           /*Предмет*/
}Student;

/*Массив структур - по сути журнал*/
extern Student journal[MAX_STUDENT]; 

/* Функция которая подсчитает количество учеников в классе
- проходим по структуре до первого незаписанного элемента, возвращаем счетчик.*/
int global_count_student(const Student journal[], int max_size);

/*Функция устанавливающая параметры журнала по дефолту, принимает параметром массив структур, размер макс. имени,
максимальный размер предмета. Ничего не возвращает, а изменяет массив структур. */
void default_journal(Student journal[]);

/*Функция подсчета среднего балла по предмету, передача структуры по указателю const.*/
float get_subject_average(const int grades[], int max_lessons);

/*отладочная функция которая берет студента и печатает его средний балл дважды: целое число и 
float с двумя знаками (%.2f).*/
void print_average(const Student *s);

/*Функция для подсчета общего среднего балла ученика (по всем трем предметам).*/
float get_student_average(const Student *s);





/*Сортировка журнала "Ранжировать учеников в классе по успеваемости... 
у кого средний бал выше - тот находится в верху списка вывода"*/
void sort_journal_by_average(Student journal[], int count);

/*функцию, которая красиво отрисовывает весь журнал.*/
void print_journal(const Student journal[], int count);

/*функция редактирования журнала.*/
void journal_editing(Student journal[], int count);

/*валидация ввода номера студента */
bool validate_num_student(int count, int student_number);

/*валидация ввода номера предмета*/
bool validate_lesson_number(int lesson_number);

/*валидация ввода номера урока*/
bool validate_subject_number(int subject_number);

/*валидация ввода оценки за урок*/
bool validate_lesson_grade(int lesson_grade);

/*Добавление ученика*/
void add_student(Student journal[], int *count); 

/*Валидация ввода пола*/
bool validate_add_gender(int gender);

/* Валидация ввода класса*/
bool validate_add_class(int add_class);

/*Рассчитать зависимость успеваемости ученика от пола*/
void analyze_gender_dependence(const Student journal[], int count); 

#endif /*task_1*/