#! /bin/bash
clang++ -g -I/opt/ssl/include/ -L/opt/ssl/lib/ -lcrypto -std=c++17  $1 #kuzn.cpp
