# ============================================================================
#  Makefile для 11_6_Practical_work
#  Сборка: MSYS2 MINGW64 + GCC
#
#  Использование (из MSYS2 MINGW64 в корне проекта):
#    make run TASK=1  — собрать и запустить Задание 1
#    make run TASK=2  — собрать и запустить Задание 2
#    make app TASK=3  — только собрать Задание 3
#    make clean       — удалить bin/ и obj/
# ============================================================================

CC      = gcc
RM      = rm -f
MKDIR   = mkdir -p

# --- Пути проекта ---
SRC_DIR     = src
INC_DIR     = include
BIN_DIR     = bin/Debug

# --- Выбор задания (по умолчанию 1) ---
# Если запустить просто `make`, соберется TASK=1
TASK ?= 1

# --- Флаги компиляции ---
# -DTASK_$(TASK) передает макрос в препроцессор (например, -DTASK_1)
# -I$(INC_DIR) указывает, где искать заголовочные файлы
CFLAGS  = -Wall -Wextra -g \
          -DTASK_$(TASK) \
          -I$(INC_DIR)

# --- Исходники и бинарники ---
# Хитрость: Makefile сам подставит номер задания в имя файла (task_1.c, task_2.c)
APP_SRC     = $(SRC_DIR)/main.c $(SRC_DIR)/task_$(TASK).c
APP_BIN     = $(BIN_DIR)/11_6_Practical_work_task_$(TASK).exe

.PHONY: all app run rebuild clean

# По умолчанию — собрать приложение
all: app

# --- Приложение ---
app: $(APP_BIN)

$(APP_BIN): $(APP_SRC) $(INC_DIR)/task_$(TASK).h
	@$(MKDIR) $(BIN_DIR)
	$(CC) $(CFLAGS) $(APP_SRC) -o $@
	@echo "==> Built: $@ (Task $(TASK))"

# --- Запуск приложения ---
run: app
	@echo "==> Running Task $(TASK)..."
	@./$(APP_BIN)

# --- Пересборка / очистка ---
rebuild: clean all

clean:
	@$(RM) -r bin obj
	@echo "==> Cleaned"