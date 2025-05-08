CXX := g++
CFLAGS := -Wall -Wextra
TARGET := lemocc
LIBTARGET := liblemonade.so

all:
	python setup.py build
	@echo "Building..."
	@mkdir -p ./build/bin
	@mkdir -p ./build/lib
	$(CXX) -o ./build/bin/lemoncc ./src/lemon.cc $(CFLAGS)
	$(CXX) ./src/BaseLang.cpp ./dist/lib/lemonpy.c -o ./build/lib/$(LIBTARGET) $(CFLAGS) -I/usr/lib/python3.12
	@echo "Done."

clean:
	rm -rf ./build
	rm -rf ./dist
	rm *.vsix

.PHONY: all, clean
