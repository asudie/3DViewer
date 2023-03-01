CC=gcc
FLAGS= -Wall -Werror -Wextra
LIBS_LINUX= -lcheck -lm -lpthread -lrt -lsubunit -D_GNU_SOURCE
LIBS_MACOS=  -lcheck

OS = $(shell uname)
ifeq ($(OS), Darwin)
OPEN=open report.html
LIBS=$(LIBS_MACOS)

endif

all: clean run tests gcov_report cpp leaks dvi

run: install
	cd ../build/Viewer3D.app/Contents/MacOS;  ./Viewer3D

install:
	cmake -S . -B ./../build
	cmake --build ./../build
	

dvi:
	 open doc.html

dist:
	cd ..; tar -czvf 3DViewer.tar.gz Viewer3D

tests:
	checkmk clean_mode=1 tests.check > test.c
	$(CC) -g $(FLAGS) test.c parser.c $(LIBS) --coverage
	./a.out

gcov_report: tests
	gcovr --html --html-details -o report.html
	$(OPEN) report.html

cpp:
	clang-format -style=google -i *.c
	clang-format -style=google -i *.h
	clang-format -style=google -n *.c
	clang-format -style=google -n *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.h *.c

leak:
	CK_FORK=no leaks -atExit -- ./a.out



uninstall:
	cd ..; rm -rf build

clean:
	rm -rf CMakeCache.txt CMakeFiles *.out *.gcda *.gcno *.o *.a report.* s21_test test_with_gcov* *.gcov test.c; cd ..; rm -rf build  3DViewer.tar.gz
	
