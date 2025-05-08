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
	g++ -std=c++17 src/lemoncc.cpp -o ./build/bin/lemoncc
	$(CXX) ./src/Baselang.cpp -o ./build/lib/$(LIBTARGET) $(CYLAGS)
	@echo "Done."

clean:
	rm -rf ./build
	rm -rf ./dist
	rm *.vsix

install:
	sudo mkdir -p /usr/include/lemonc
	sudo cp -r ./src/Baselang.h /usr/include/lemonc/
	sudo cp -r ./src/lemond.h /usr/include/lemonc/
	sudo cp -r ./include/Lemon.h /usr/include/lemonc/

.PHONY: all, clean
