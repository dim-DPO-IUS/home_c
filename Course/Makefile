# Исходные файлы
SRCS = report.c temp_function.c
HEADERS = temp_function.h
# Имя исполняемого файла
TARGET = report
# ===============
# 
# Компилятор и флаги
CC = gcc
# Флаги компиляции:
CFLAGS = -g -std=c99 -Wall
# CFLAGS += -Wextra
# CFLAGS += -Wno-unused-variable
# CFLAGS += -ggdb3 -Og
# 
# Флаги линковки: отладочная информация
LDFLAGS = -g3  #-ggdb3
# 
# Автоматическое определение объектных файлов
OBJS = $(SRCS:.c=.o) 
PREPROCESSED = $(SRCS:.c=.i)# Файлы после препроцессирования
ASSEMBLY = $(SRCS:.c=.s)  # Определение для .s файлов

# Основная цель
all: $(TARGET)

# ============ ПРАВИЛА ============ #

# Основной процесс сборки с выводом команд
$(TARGET): $(OBJS)
	@echo "gcc -o report report.o temp_function.o"
	@$(CC) $(LDFLAGS) $^ -o $@

# Правило для .c -> .o с промежуточными шагами
%.o: %.c $(HEADERS)
	@echo "gcc $(CFLAGS) -E $< -o $(<:.c=.i)"
	@$(CC) $(CFLAGS) -E $< -o $(<:.c=.i)
	
	@echo "gcc $(CFLAGS) -S $(<:.c=.i) -o $(<:.c=.s)"
	@$(CC) $(CFLAGS) -S $(<:.c=.i) -o $(<:.c=.s)
	
	@echo "gcc $(CFLAGS) $(LDFLAGS) -c $<"
	@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

# ============

# Вспомогательные цели
.PHONY: all debug release run rebuild clean print-target preprocess

debug release: all

run: all
	@echo "Запуск программы..."
	@./$(TARGET) || echo "Ошибка при запуске программы"

rebuild: clean all

clean:
	@echo "rm -f *.i *.s *.o  report"
	@rm -f $(PREPROCESSED) $(ASSEMBLY) $(OBJS) $(TARGET)

print-target:
	@echo $(TARGET)

# Препроцессирование исходников без компиляции
preprocess: $(PREPROCESSED)
	@echo "Препроцессирование завершено. Результат в файлах: $(PREPROCESSED)"
