CXX := g++
CFLAGS := -Wall -Wextra
TARGET := lemocc
LIBTARGET := liblemonade.so
CYFLAGS := -shared -pthread -fPIC -fwrapv -O2 -Wall -fno-strict-aliasing -I/usr/include/python3.12

all:
	python setup.py build
	@echo "Building..."
	@mkdir -p ./build/bin
	@mkdir -p ./build/lib
	$(CXX) -o ./build/bin/lemoncc ./src/lemon.cc $(CFLAGS)
	$(CXX) ./src/Baselang.cpp -o ./build/lib/$(LIBTARGET) $(CYLAGS)
	@echo "Done."

clean:
	rm -rf ./build
	rm -rf ./dist
	rm *.vsix

.PHONY: all, clean
