flags = -Wall -Werror -std=c11

all: bin build bin/verbs bin/test

bin/verbs: build/main.o build/working_with_data.o build/string.o
	gcc $(flags) build/main.o build/working_with_data.o build/string.o -o bin/verbs -lncursesw

build/main.o: src/main.c
	gcc $(flags) -c src/main.c -o build/main.o

build/string.o: src/string.c
	gcc $(flags) -c src/string.c -o build/string.o

build/working_with_data.o: src/working_with_data.c
	gcc $(flags) -c src/working_with_data.c -o build/working_with_data.o

bin/test: build/ftest.o build/test.o build/working_with_data.o build/string.o
	gcc $(flags) build/ftest.o build/test.o build/working_with_data.o build/string.o -o bin/test -lncursesw

build/ftest.o: test/ftest.c
	gcc $(flags) -c test/ftest.c -o build/ftest.o -Ithirdparty	

build/test.o: test/test.c
	gcc $(flags) -c test/test.c -o build/test.o -Ithirdparty -Isrc
	

bin:
	mkdir -p bin

build:
	mkdir -p build

.PHONY: clean

clean:
	rm -rf build bin