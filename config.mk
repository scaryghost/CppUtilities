CPPC=g++
DIST=dist
LIB:=libcpputilities
MODULES=Network Cli Logging

CPP_FLAGS:=-std=c++0x -Werror -Wall

ifdef DEBUG
    CPP_FLAGS+= -g
    LIB:=$(LIB)_debug
endif
