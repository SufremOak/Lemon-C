#!/usr/bin/env bash

set -e

read -p "This will install Lemon-C on your system, do you want to proceed? [y/N]:" $choose

if [$choose == Yy]; then
  git clone https://github.com/sufremoak/lemon-c /tmp/lemon-install
  cd /tmp/lemon-install

  if [! command -v "gcc" 2 /dev/null ] &>1; then
    echo "Gcc is required!"
    exit 1
  else
    mkdir -p /usr/local/lemonc/{bin,include,lib}
    gcc src/sys/cstd.openstd.cpp -std=c++11 -o /usr/local/lemonc/bin/lemonc++2 -I/tmp/lemon-install/include -Wall -shared
    # gcc src/sys/gsstdobjc.m -std=objc -o /usr/local/lemonc/lib/libgnustep.so.1 -shared
    cp -r include/*.h /usr/local/lemonc/include/
    if [! command -v "just" 2 /dev/null ] &>1; then
      if [! command -v "cargo" 2 /dev/null] &>1; then
        echo "please install rust!"
        exit 1
      else
        cargo install just
      fi
    else
      just && just install
    fi
  fi
else
  exit 1
fi
