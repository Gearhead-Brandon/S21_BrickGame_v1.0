CC = gcc
CFLAGS = -Wall -Werror -Wextra --std=c11 
NCURSES = -lncursesw
TARGET = tetris
DIR_INSTALL = out
LIBNAME = tetris_lib.a
REPORT = REPORT.html
TEST_FLAGS = -L. $(LIBNAME) $(CHECKFLAGS) $(GLFLAGS) $(GCOVFLAGS) $(NCURSES)

GREEN=\033[0;32m
NC=\033[0m

TEST_SOURCES=$(wildcard unit_tests/*.c)
TEST_TARGETS=$(TEST_SOURCES:unit_tests/%.c=%)

CHECKFLAGS = $(shell pkg-config --cflags --libs check)
GCOVFLAGS  = -fprofile-arcs -ftest-coverage
GLFLAGS    = --coverage

MAIN =  main.c
DIRS = ./brick_game/tetris ./gui

GUI    = gui/cli
TETRIS = brick_game/tetris/source

EXCLUDE_FILES = $(MAIN) $(GUI)/frontend.c $(TETRIS)/ncurses_* "unit_tests/*"
EXCLUDE_REPORT = $(foreach file, $(EXCLUDE_FILES), --exclude $(file)) 

SRC := $(shell find $(DIRS) $(MAIN) -type f -name "*.c")
OBJ := $(patsubst %.c, %.o, $(SRC))

EXCLUDE_OBJ = main.o $(GUI)/frontend.o $(TETRIS)/ncurses.o
OBJ_GCOV := $(filter-out $(EXCLUDE_OBJ),$(OBJ))

##################################__ALL

all: install

##################################__INSTALL 

install: $(OBJ)
	@make uninstall
	$(CC) $(CFLAGS) $(GCOVFLAGS) $(GLFLAGS) $(OBJ) -o $(TARGET) $(NCURSES)
	@rm -rf out && mkdir out
	@mv $(TARGET) out
	@make clean
	@make run
	@make clean

run:
	@cd $(DIR_INSTALL) && ./$(TARGET)

##################################__BUILD OBJECTS FILES

%.o: %.c
	@$(CC) $(CFLAGS) $(GCOVFLAGS) $(GLFLAGS) -c $< -o $@

##################################__UNINSTALL

uninstall:
	@rm -rf out

##################################__LIBRARY

$(LIBNAME): $(OBJ_GCOV)
	@ar rcs $(LIBNAME) $(OBJ_GCOV)

##################################__TEST

test: $(TEST_TARGETS)
	make start_tests

%: unit_tests/%.c $(LIBNAME)
	@$(CC) $< $(TEST_FLAGS) -o $@

start_tests:
	@echo "$(GREEN)Starting unit tests\n"
	@for test in $(TEST_TARGETS); do \
		printf "$(GREEN)\n"; \
		echo $$test; \
        ./$$test; \
    done
#	./pause_test
	@echo "$(NC)"
	@make move_tests
	@make move_trash

##################################__GCOV REPORT

gcov_report: $(LIBNAME) test
	~/.local/bin/gcovr -r . $(EXCLUDE_REPORT) --html --html-details -o $(REPORT)
	@make move_report
	@rm -rf Trash

peer: gcov_report
	@google-chrome Report/$(REPORT)

##################################__DVI

dvi:
	@google-chrome doc/html/index.html

##################################__DIST

dist:
	@if [ -d "$(DIR_INSTALL)" ]; then \
		(cd $(DIR_INSTALL) && tar -cf Tetris.tar . && mv Tetris.tar ../); \
	else \
		echo "Directory $(DIR_INSTALL) does not exist."; \
	fi

##################################__MOVE

move_report:
	@rm -rf Report && mkdir Report && mv *.html *.css Report

move_trash:
	@rm -rf Trash && mkdir Trash
	@find . -type f \( ! -path "./doc/*" ! -path "./Trash/*" ! -path "./Report/*"\
	 \)  \( -name "*.a" -o -name "*.gcno" -o -name "*.gcda" -o -name "*.gcov" \
	-o -name "*.o" \) -exec mv {} Trash/ \;

move_tests:
	@mv *test unit_tests

##################################__CLEAN

clean:
	@find . -type f -not -path "./doc/*" \( -name "*.a" \
	-o -name "*.gcno" -o -name "*.gcda" -o -name "*.gcov" -o -name "*test" \
	-o -name "*.html" -o -name "*.css" \) -exec rm -f {} \;
	@make clean_obj
	@rm -rf Report Trash

clean_obj:
	@find . -type f -name "*.o" -exec rm -f {} \;

##################################__VALGRIND

val: install
	valgrind --tool=memcheck --leak-check=yes  ./out/$(TARGET)

##################################__REBUILD

rebuild:
	make clean
	make