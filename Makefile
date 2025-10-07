SOURCES = main.c array_list.c

run: build
	./.build/main

build: prepare $(SOURCES)
	gcc -o .build/main $(SOURCES)

prepare:
	mkdir -p .build

clean:
	rm -rf .build

