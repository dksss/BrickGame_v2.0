CURRENT_DIR := $(shell pwd)
FLAGS := -Wall -Werror -Wextra

# C
GCC := gcc
GCCFLAGS := $(FLAGS) -std=c11

# C++
GXX := g++
GXXFLAGS := $(FLAGS) -std=c++17

# SRCs DIRs
FRONT_CLI_DIR := ./gui/cli
FRONT_DESKTOP_DIR := ./gui/desktop

TESTS_DIR := ../tests
TESTS_SRC := $(TESTS_DIR)/*.cc

BACK_TETRIS_DIR := ./brick_game/tetris
TETRIS_SRC := $(BACK_TETRIS_DIR)/*.c

BACK_SNAKE_DIR := ./brick_game/snake
SNAKE_MODEL_DIR := $(BACK_SNAKE_DIR)/model
SNAKE_MODEL_SRC := $(SNAKE_MODEL_DIR)/*/*.cc
SNAKE_CONTROLLER_DIR := $(BACK_SNAKE_DIR)/controller
SNAKE_CONTROLLER_SRC := $(SNAKE_CONTROLLER_DIR)/*.cc

# INSTALL DIR
INSTALL_PATH := $(CURRENT_DIR)/../..
TARGET_DIR := $(INSTALL_PATH)/BrickGame_v2_0_by_jodyvole

# OTHER DIRs FOR MAKE TARGETS
BUILD_DIR := ../build
DIST_DIR := ../dist
DOCS_DIR := ../docs

# Other aliases
TEST_LIBS := -lgtest -lgtest_main
COVERAGE_FLAGS := -fprofile-arcs -ftest-coverage

DOCS_DIR := ../docs


OS := $(shell uname -s)
ifeq ($(OS), Darwin)
	OPEN := open
else ifeq ($(OS), Linux)
	OPEN := google-chrome
endif


.PHONY: all install_cli install_desktop build uninstall html open_docs valgrind gcov_report dist

all: install_cli install_desktop

install_cli: build
	mkdir $(TARGET_DIR)
	$(GCC) $(GCCFLAGS) -c $(FRONT_CLI_DIR)/*.c $(FRONT_CLI_DIR)/game_loops/*.c
	$(GXX) $(GXXFLAGS) -c $(FRONT_CLI_DIR)/*.cc $(FRONT_CLI_DIR)/game_loops/*.cc
	$(GXX) $(GXXFLAGS) -o BrickGame_cli *.o -lncurses -L$(BUILD_DIR) -l:tetris.a -l:snake.a
	rm *.o
	mv BrickGame_cli $(TARGET_DIR)
	@echo
	@echo "=========[ The cli game is in \033[33m~$(TARGET_DIR)\033[0m ]======"
	@echo

# Перед вызовом этой цели необходимо выполнить предыдущую (install_cli)
install_desktop:
	@cd gui/desktop && mkdir build && cd build && cmake .. && make
	@mv gui/desktop/build/BrickGame_desktop $(TARGET_DIR)
	@rm -rf gui/desktop/build
	@echo
	@echo "=========[ The desktop game is in \033[33m~$(TARGET_DIR)\033[0m ]======"
	@echo

uninstall:
	@rm $(TARGET_DIR)/*
	@rmdir $(TARGET_DIR)
	@echo
	@echo "\033[32m=============[ Uninstall complete ]==================\033[0m"
	@echo

tetris.a:
	$(GCC) $(GCCFLAGS) $(TETRIS_SRC) -c
	ar rcs $@ *.o
	ranlib $@
	rm *.o

snake.a:
	$(GXX) $(GXXFLAGS) $(SNAKE_MODEL_SRC) $(SNAKE_CONTROLLER_SRC) -c
	ar rcs $@ *.o
	ranlib $@
	rm *.o

build: tetris.a snake.a
	mkdir $(BUILD_DIR)
	mv $^ $(BUILD_DIR)

tests:
	$(GXX) $(GXXFLAGS) -o $@ $(TESTS_SRC) $(SNAKE_MODEL_SRC) $(SNAKE_CONTROLLER_SRC) $(TEST_LIBS)
	@./$@

valgrind: tests
	CK_FORK=no valgrind -s  --track-origins=yes --tool=memcheck --leak-check=full \
	--show-leak-kinds=all --log-file=RESULT_VALGRIND.txt ./$<
	rm *.score $<

gcov_report:
	$(GXX) $(GXXFLAGS) $(COVERAGE_FLAGS) -o tests_coverage $(TESTS_SRC) \
	$(SNAKE_MODEL_SRC) $(SNAKE_CONTROLLER_SRC) $(TEST_LIBS)
	./tests_coverage
	lcov -t "Snake_backend_tests" -o coverage.info --no-external -c -d .
	genhtml -o report coverage.info
	rm *.info *.gcda *.gcno
	rm snake.score tests_coverage
	$(OPEN) report/index.html

dist:
	mkdir $(DIST_DIR)
	tar cf $(DIST_DIR)/BrickGame_v_2_0.tar ../src ../tests ../materials ../README.md

# dvi
html:
	doxygen

open_documentation:
	$(OPEN) $(DOCS_DIR)/html/index.html

check_style:
	@clang-format --style=file:"../materials/linters/.clang-format" -n \
	$(BACK_TETRIS_DIR)/*.h $(BACK_TETRIS_DIR)/*.c \
	$(SNAKE_CONTROLLER_DIR)/*.h $(SNAKE_CONTROLLER_DIR)/*.cc \
	$(SNAKE_MODEL_DIR)/*/*.h $(SNAKE_MODEL_DIR)/*/*.cc \
	$(TESTS_DIR)/*.h $(TESTS_DIR)/*.cc \
	$(FRONT_CLI_DIR)/*.h $(FRONT_CLI_DIR)/game_loops/*.h \
	$(FRONT_CLI_DIR)/*.c $(FRONT_CLI_DIR)/*.cc $(FRONT_CLI_DIR)/game_loops/*.cc \
	$(FRONT_DESKTOP_DIR)/*.h $(FRONT_DESKTOP_DIR)/*.cc \
	$(FRONT_DESKTOP_DIR)/*/*.h $(FRONT_DESKTOP_DIR)/*/*.cc

clean:
	rm -rf report ../dist ../docs ../build
	rm snake.score tests RESULT_VALGRIND.txt