default:
    mkdir -p ./build/bin
    mkdir -p ./build/include
    rustc ./src/lemoncc.rs -o ./build/bin/lemoncc
    cp -r ./include/*.h ./build/include
    @echo "Build complete. The binary is located at ./build/bin/lemoncc and the headers at ./build/include."
clean:
    rm -rf ./build
    @echo "Cleaned up build artifacts."

install:
    mkdir -p /usr/local/include/{LemonC}
    cp ./build/bin/lemoncc /usr/local/bin/
    cp -r ./build/include/* /usr/local/include/LemonC
    @echo "Installed lemoncc to /usr/local/bin."
    @echo "Installed headers to /usr/local/include/LemonC."
uninstall:
    rm -rf /usr/local/include/LemonC
    rm -f /usr/local/bin/lemoncc
    @echo "Uninstalled lemoncc from /usr/local/bin."
    @echo "Removed headers from /usr/local/include/LemonC."