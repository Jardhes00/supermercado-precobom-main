CC := gcc
CFLAGS := -Wall -Wextra -std=c11 -MMD -MP -Iinclude
TARGET := build/supermercado_precobom.exe
SOURCES := $(wildcard src/*.c)
OBJECTS := $(patsubst src/%.c,build/%.o,$(SOURCES))
DEPENDENCIES := $(OBJECTS:.o=.d)

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

build/%.o: src/%.c
	@if not exist build mkdir build
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET)

clean:
	@if exist build rmdir /s /q build

-include $(DEPENDENCIES)
