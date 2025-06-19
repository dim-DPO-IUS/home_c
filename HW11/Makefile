# какой компилятор использовать (gcc)
CC = gcc
# флаги компиляции:
# 	-Wall - показывать все предупреждения
# 	-Wextra - дополнительные предупреждения
# 	-std=c11 - использовать стандарт C11
CFLAGS = -Wall -Wextra -std=c11
# Цель: по умолчанию - создание программы temp_app
all: temp_app
# Правило: Сборка программы из объектных файлов
# 	$@ - имя цели (temp_app)
# 	$^ - все зависимости (main.o temp_api.o)
temp_app: main.o temp_api.o
	$(CC) $(CFLAGS) -o $@ $^
# Правило: Компиляция main.c в main.o
main.o: main.c temp_api.h
	$(CC) $(CFLAGS) -c main.c
# Правило: Компиляция temp_api.c в temp_api.o
temp_api.o: temp_api.c temp_api.h
	$(CC) $(CFLAGS) -c temp_api.c
# Цель: очистка проекта - удаляет все .o файлы и саму программу
clean:
	rm -f *.o temp_app