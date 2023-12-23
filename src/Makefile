.PHONY: check clean
CC=gcc -D_POSIX_C_SOURCE=200809L
CFLAGS=-Wall -Werror -Wextra -ggdb -std=c11
GCOVFLAGS=-fprofile-arcs -ftest-coverage 
OS=$(shell uname -s)
ifeq ($(OS),Linux)
CHECKFLAGS=-lcheck -lsubunit -lrt -lpthread -lm -lgcov --coverage
endif
ifeq ($(OS),Darwin)
CHECKFLAGS=-lcheck -lgcov --coverage 			
endif
STATICLIB=s21_string.a
DIROBJ=./obj
DIRFUNCTESTS=./tests
DIRGCOV=./gcov
DIRGENHTML=./genhtml

all: $(STATICLIB) test gcov_report  

build: all

rebuild: clean all

$(STATICLIB):
	$(CC) $(CFLAGS) -c ./functions/*.c
	ar r $(STATICLIB) *.o
	rm -f *.o

test: $(STATICLIB)
	$(CC) $(CFLAGS) -c ./functions/*.c $(GCOVFLAGS) 
	$(CC) $(CFLAGS) -c ./functions_tests/*.c
	mkdir -p $(DIROBJ)  
	mv -f *.o $(DIROBJ)
	
# Anton:
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_memchr_test.o $(DIROBJ)/s21_memchr.o $(STATICLIB) -o s21_memchr_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_memcmp_test.o $(DIROBJ)/s21_memcmp.o $(STATICLIB) -o s21_memcmp_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_memcpy_test.o $(DIROBJ)/s21_memcpy.o $(STATICLIB) -o s21_memcpy_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_memset_test.o $(DIROBJ)/s21_memset.o $(STATICLIB) -o s21_memset_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_strncat_test.o $(DIROBJ)/s21_strncat.o $(STATICLIB) -o s21_strncat_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_strchr_test.o $(DIROBJ)/s21_strchr.o $(STATICLIB) -o s21_strchr_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_strncmp_test.o $(DIROBJ)/s21_strncmp.o $(STATICLIB) -o s21_strncmp_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_strncpy_test.o $(DIROBJ)/s21_strncpy.o $(STATICLIB) -o s21_strncpy_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_strcspn_test.o $(DIROBJ)/s21_strcspn.o $(STATICLIB) -o s21_strcspn_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_strerror_test.o $(DIROBJ)/s21_strerror.o $(STATICLIB) -o s21_strerror_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_strlen_test.o $(DIROBJ)/s21_strlen.o $(STATICLIB) -o s21_strlen_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_strpbrk_test.o $(DIROBJ)/s21_strpbrk.o $(STATICLIB) -o s21_strpbrk_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_strrchr_test.o $(DIROBJ)/s21_strrchr.o $(STATICLIB) -o s21_strrchr_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_strstr_test.o $(DIROBJ)/s21_strstr.o $(STATICLIB) -o s21_strstr_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_strtok_test.o $(DIROBJ)/s21_strtok.o $(STATICLIB) -o s21_strtok_test $(CHECKFLAGS)

# Alexey:
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_sprintf_test.o $(DIROBJ)/s21_sprintf.o $(STATICLIB) -o s21_sprintf_test $(CHECKFLAGS)

# Artem:
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_sscanf_test.o $(DIROBJ)/s21_sscanf.o $(STATICLIB) -o s21_sscanf_test $(CHECKFLAGS)

	$(CC) $(CFLAGS)  $(DIROBJ)/s21_trim_test.o $(DIROBJ)/s21_trim.o $(STATICLIB) -o s21_trim_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_insert_test.o $(DIROBJ)/s21_insert.o $(STATICLIB) -o s21_insert_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_to_lower_test.o $(DIROBJ)/s21_to_lower.o $(STATICLIB) -o s21_to_lower_test $(CHECKFLAGS)
	$(CC) $(CFLAGS)  $(DIROBJ)/s21_to_upper_test.o $(DIROBJ)/s21_to_upper.o $(STATICLIB) -o s21_to_upper_test $(CHECKFLAGS)

	mkdir -p $(DIRFUNCTESTS)  
	mv -f *_test $(DIRFUNCTESTS) 
	make run_test

run_test:

# Anton:
	$(DIRFUNCTESTS)/s21_memchr_test
	$(DIRFUNCTESTS)/s21_memcmp_test
	$(DIRFUNCTESTS)/s21_memcpy_test
	$(DIRFUNCTESTS)/s21_memset_test
	$(DIRFUNCTESTS)/s21_strncat_test
	$(DIRFUNCTESTS)/s21_strchr_test
	$(DIRFUNCTESTS)/s21_strncmp_test
	$(DIRFUNCTESTS)/s21_strncpy_test
	$(DIRFUNCTESTS)/s21_strcspn_test
	$(DIRFUNCTESTS)/s21_strerror_test
	$(DIRFUNCTESTS)/s21_strlen_test
	$(DIRFUNCTESTS)/s21_strpbrk_test
	$(DIRFUNCTESTS)/s21_strrchr_test
	$(DIRFUNCTESTS)/s21_strstr_test
	$(DIRFUNCTESTS)/s21_strtok_test

# Alexey:
	$(DIRFUNCTESTS)/s21_sprintf_test

# Artem:	
	$(DIRFUNCTESTS)/s21_sscanf_test

	$(DIRFUNCTESTS)/s21_trim_test
	$(DIRFUNCTESTS)/s21_insert_test
	$(DIRFUNCTESTS)/s21_to_lower_test
	$(DIRFUNCTESTS)/s21_to_upper_test

gcov_report:
	mkdir -p $(DIRGCOV)
	gcov ./functions/*.c -o ./
	mv -f *.gcov $(DIRGCOV)
	mv -f *.gcda $(DIRGCOV)
	mv -f *.gcno $(DIRGCOV)
	lcov -d $(DIRGCOV) -c -o ./html.info
	genhtml -o $(DIRGENHTML) html.info
	open $(DIRGENHTML)/index.html
	
check:
	cp ../materials/linters/.clang-format ./
	clang-format -style=Google -n *.h
	clang-format -style=Google -i *.h
	clang-format -style=Google -n ./functions/*.c
	clang-format -style=Google -i ./functions/*.c 
	clang-format -style=Google -n ./functions_tests/*.c ./functions_tests/*.h
	clang-format -style=Google -i ./functions_tests/*.c ./functions_tests/*.h
# cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
# cppcheck --enable=all --suppress=missingIncludeSystem ./functions/*.c 
# cppcheck --enable=all --suppress=missingIncludeSystem ./functions_tests/*.c ./functions_tests/*.h
	rm -f .clang-format

valgrind: clean test

# Anton:
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_memchr_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_memcmp_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_memcpy_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_memset_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_strncat_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_strchr_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_strncmp_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_strncpy_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_strcspn_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_strerror_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_strlen_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_strpbrk_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_strrchr_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_strstr_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_strtok_test

# Alexey:
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_sprintf_test

# Artem:
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_sscanf_test

	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_trim_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_insert_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_to_lower_test
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all $(DIRFUNCTESTS)/s21_to_upper_test

clean:
	rm -f *.a
	rm -f *.gc*
	rm -drf $(DIROBJ)
	rm -drf $(DIRFUNCTESTS)
	rm -drf $(DIRGCOV)
	rm -drf $(DIRGENHTML)
	rm -f *.info
	
