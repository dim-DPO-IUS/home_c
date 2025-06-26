# Исходные файлы
SRCS = main.c temp_api.c
HEADERS = temp_api.h

# Компилятор и флаги
CC = gcc
# Флаги компиляции:
CFLAGS = -Wall -Wextra -std=c11
CFLAGS += -Wno-unused-variable
CFLAGS += -ggdb3 -Og
# Флаги линковки: отладочная информация
LDFLAGS = -ggdb3

# Имя исполняемого файла
TARGET = temp_app

# Автоматическое определение объектных файлов
OBJS = $(SRCS:.c=.o) 

# Основная цель
all: $(TARGET)

# Правило линковки
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# Обобщенное правило компиляции .c файлов в .o
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Вспомогательные цели
.PHONY: all debug release run rebuild clean print-target

debug release: all

run: all
	@echo "Запуск программы..."
	@./$(TARGET) || echo "Ошибка при запуске программы"

rebuild: clean all

clean:
	rm -f $(OBJS) $(TARGET)

print-target:
	@echo $(TARGET)
