# HW12/Makefile
TARGET = temp_app
SRCS = temp_api.c main.c  # Все .c-файлы в текущей папке
CFLAGS = -Wall -Wextra -g  # Ключ -g добавляет отладочную информацию

.PHONY: all clean print-target
 
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)

# Чтобы автоматически передать имя бинарника  в tasks.json
print-target:  
	@echo $(TARGET)  