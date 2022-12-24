CC := gcc
CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wvla -Wextra -Wfloat-equal -Wfloat-conversion
LFLAGS = 
OBJS := $(filter-out out/main.o, $(patsubst src/%.c, out/%.o, $(wildcard src/*.c)))

RM := rm

ifeq ($(mode), debug)
	CFLAGS = -std=c99 -Wall -Werror -Wpedantic -Wextra -g -fprofile-arcs -ftest-coverage
	LFLAGS = -fprofile-arcs -ftest-coverage
endif

app.exe : $(OBJS) out/main.o
	$(CC) $(LFLAGS) -o $@ $^

./out/%.o : */%.c ./inc/*.h
	mkdir -p out
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean

clean :
	$(RM) -r out 
	$(RM) *.exe *.txt *gv
