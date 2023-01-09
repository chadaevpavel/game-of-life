TASK=game_of_life

CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 -pedantic -g
TESTSPATH=../tests/

CMAINFILE=game_of_life.c
OMAINFILE=$(patsubst %.c,%.o,$(CMAINFILE))

CFUNCFILES=gol_functions.c
HFUNCFILES=$(patsubst %.c,%.h,$(CFUNCFILES))
OFUNCFILES=$(patsubst %.c,%.o,$(CFUNCFILES))

CTESTFILES=gol_tests.c
HTESTFILES=$(patsubst %.c,%.h,$(CTESTFILES))
OTESTFILES=$(patsubst %.c,%.o,$(CTESTFILES))

EXECNAME=$(TASK)
TESTEXECNAME=$(TASK)_tests

UNAME:=$(shell uname)
ifeq ($(UNAME), Linux)
	LFLAGS=-lcheck -lpthread -lsubunit -lrt -lm
endif
ifeq ($(UNAME), Darwin)
	LFLAGS=-lcheck -lpthread -lm
endif

.PHONY: all run test build clean rebuild style leaks

all:
	@$(MAKE) --no-print-directory run

run: $(EXECNAME)
	@./$(EXECNAME) ../patterns/lake.txt

test: $(TESTEXECNAME)
	@./$(TESTEXECNAME)

build: $(EXECNAME)

$(EXECNAME): $(OMAINFILE) $(OFUNCFILES)
	@$(CC) $^ -lncurses -o $(EXECNAME)

$(TESTEXECNAME): $(OFUNCFILES) $(OTESTFILES)
	@$(CC) $^ $(LFLAGS) -o $(TESTEXECNAME)

$(OMAINFILE): $(CMAINFILE) $(CFUNCFILES) $(HFUNCFILES)
	@$(CC) $(CFLAGS) -c $(CMAINFILE) $(CFUNCFILES)

$(OFUNCFILES): $(CFUNCFILES) $(HFUNCFILES)
	@$(CC) $(CFLAGS) -c $(CFUNCFILES)

$(OTESTFILES): $(TESTSPATH)$(CTESTFILES) $(TESTSPATH)$(HTESTFILES) $(CFUNCFILES) $(HFUNCFILES)
	@$(CC) $(CFLAGS) -c $(TESTSPATH)$(CTESTFILES) $(CFUNCFILES)

clean:
	@rm -rf *.o $(EXECNAME)
	@rm -rf $(TESTSPATH)*.o $(TESTEXECNAME)

rebuild:
	@$(MAKE) --no-print-directory clean
	@$(MAKE) --no-print-directory build

style:
	@clang-format -i --style=Google *.c *.h

leaks: $(EXECNAME)
	@valgrind --quiet --leak-check=full ./$(EXECNAME) ../patterns/lake.txt