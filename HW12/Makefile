# какой компилятор использовать (gcc)
CC = gcc
# флаги компиляции:
# 	-Wall - показывать все предупреждения
# 	-Wextra - дополнительные предупреждения
# 	-std=c11 - использовать стандарт C11
CFLAGS = -Wall -Wextra -std=c11 -Wno-unused-variable
# 	ВРЕМЕННО! это отключит все предупреждения о неиспользуемых переменных
CFLAGS += -Wno-unused-variable

# Имя исполняемого файла
TARGET = temp_app

# Цель по умолчанию - создание программы temp_app
all: $(TARGET)

# Правило: Сборка программы
$(TARGET): main.o temp_api.o
	$(CC) $(CFLAGS) -o $@ $^

# Правило: Компиляция main.c
main.o: main.c temp_api.h
	$(CC) $(CFLAGS) -c $< -o $@

# Правило: Компиляция temp_api.c в temp_api.o
temp_api.o: temp_api.c temp_api.h
	$(CC) $(CFLAGS) -c $< -o $@

# Псевдоцели для совместимости с общим Makefile
debug: all
release: all
run: all
	@echo "Запуск программы..."
	@./$(TARGET) || echo "Ошибка при запуске программы"
rebuild: clean all

# Очистка проекта
clean:
	rm -f *.o $(TARGET)