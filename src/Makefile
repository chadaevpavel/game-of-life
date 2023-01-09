TASK=game_of_life
AUXLIBS=

CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -pedantic -g
AUXPATH=
CFILES=$(wildcard *.c)
CFILES+=$(AUXPATH)$(AUXLIBS)
HFILES=$(patsubst %.c,%.h,$(wildcard *.c))
OFILES=$(patsubst %.c,%.o,$(wildcard *.c))
EXECNAME=$(TASK)

UNAME:=$(shell uname)
ifeq ($(UNAME), Linux)
	LFLAGS=-lcheck -lpthread -lsubunit -lrt -lm
endif
ifeq ($(UNAME), Darwin)
	LFLAGS=-lcheck -lpthread -lm
endif

.PHONY: all run build clean rebuild style leaks

all:
	@$(MAKE) --no-print-directory run

run: $(EXECNAME)
	@./$(EXECNAME)

build: $(EXECNAME)

$(EXECNAME): $(OFILES) $(patsubst %.c,%.o,$(AUXLIBS))
	@$(CC) $^ $(LFLAGS) -o $(EXECNAME)

$(OFILES): $(CFILES) $(HFILES)
	@$(CC) $(CFLAGS) -c $(CFILES)

clean:
	@rm -rf *.o $(EXECNAME)

rebuild:
	@$(MAKE) --no-print-directory clean
	@$(MAKE) --no-print-directory build
	@$(MAKE) --no-print-directory run

style:
	@clang-format -i --style=Google *.c *.h

leaks: $(EXECNAME)
	@valgrind --quiet --leak-check=full ./$(EXECNAME)