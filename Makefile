include config.mk

SRCS:=
INC_DIRS:=..

MODULE_CONFIG= $(foreach module, $(MODULES), $(module)/src/config.mk)
INC= $(foreach incdir, $(INC_DIRS), -I$(incdir))

include $(MODULE_CONFIG)

OBJS= $(patsubst %.cpp, %.o, $(SRCS))

all: setup $(OBJS)
	ar -cvq $(DIST)/$(LIB).a $(OBJS)

%.o: %.cpp
	$(CPPC) -c $(CPP_FLAGS) $(INC) $< -o $@

setup:
	if [ ! -e $(DIST) ]; then \
	    mkdir $(DIST); \
	fi

doc: setup
	doxygen

clean:
	rm -f -R $(DIST) $(OBJS)
