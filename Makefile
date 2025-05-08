CXX := g++
CFLAGS := -Wall -Wextra
TARGET := lemocc
LIBTARGET := liblemonade.so

checkbuild:
	@mkdir -p ./build ./dist
	@echo "Checked and ensured ./build and ./dist directories exist."

all:
	cython ./lib/lemonpy.pyx
	$(CXX) -o ./build/bin/lemoncc ./src/lemon.cc $(CFLAGS)
	$(CXX) ./src/BaseLang.cc ./dist/lemonpy.c -o ./build/lib/$(LIBTARGET) $(CFLAGS) -I/usr/lib/python3.12
	@echo "Done."

clean:
	rm -rf ./build
	rm -rf ./dist
	rm *.vsix

.PHONY: all, clean, checkbuild
