# compiler
CC := gcc
# flags for compilation
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wvla -Wextra -Wfloat-equal -Wfloat-conversion
# a list of generated objects
OBJS := out/file_funcs.o out/sort_funcs.o out/flats_funcs.o out/keys_funcs.o out/print_funcs.o out/specific_funcs.o out/efficiency_funcs.o

RM := rm

app.exe : $(OBJS) out/main.o
	$(CC) -o $@ $^

./out/%.o : */%.c ./inc/*.h
	mkdir -p out
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean

clean : 
	$(RM) *.exe out/* 
