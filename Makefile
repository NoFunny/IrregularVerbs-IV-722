flags = -Wall -Werror -std=c11

all: bin build bin/verbs

bin/verbs: build/main.o build/dictionary.o build/string.o build/interface.o
	gcc $(flags) build/main.o build/dictionary.o build/string.o build/interface.o -o bin/verbs -lncurses

build/main.o: src/main.c
	gcc $(flags) -c src/main.c -o build/main.o

build/string.o: src/string.c
	gcc $(flags) -c src/string.c -o build/string.o

build/dictionary.o: src/dictionary.c
	gcc $(flags) -c src/dictionary.c -o build/dictionary.o

build/interface.o: src/interface.c
	gcc $(flags) -c src/interface.c -o build/interface.o

bin:
	mkdir -p bin

build:
	mkdir -p build

.PHONY: clean

clean:
	rm -rf build bin