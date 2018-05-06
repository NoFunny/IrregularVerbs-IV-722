flags = -Wall

all: bin build bin/verbs

bin/verbs: build/main.o build/dictionary.o build/string.o
	gcc $(flags) build/main.o build/dictionary.o build/string.o -o bin/verbs

build/main.o: src/main.c
	gcc $(flags) -c src/main.c -o build/main.o

build/string.o: src/string.c
	gcc $(flags) -c src/string.c -o build/string.o

build/dictionary.o: src/dictionary.c
	gcc $(flags) -c src/dictionary.c -o build/dictionary.o

bin:
	mkdir -p bin

build:
	mkdir -p build

.PHONY: clean

clean:
	rm -rf build bin