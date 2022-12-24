# compiler
CC := gcc
# flags for compilation
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wvla -Wextra -Wfloat-equal -Wfloat-conversion
# a list of generated objects
OBJS := $(patsubst src/%.c, out/%.o, $(wildcard src/*.c))

RM := rm

app.exe : $(OBJS)
	echo $(OBJS)
	$(CC) -o $@ $^

./out/%.o : */%.c ./inc/*.h
	mkdir -p out
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean

clean : 
	$(RM) *.exe out/* *.txt
