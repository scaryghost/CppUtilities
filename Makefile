include config.mk

SRCS:=
INC_DIRS:=..

MODULE_CONFIG= $(foreach module, $(MODULES), $(module)/src/config.mk)
INC= $(foreach incdir, $(INC_DIRS), -I$(incdir))

include $(MODULE_CONFIG)

OBJS= $(patsubst %.cpp, %.o, $(SRCS))

all: $(DIST) $(DIST)/$(LIB)

$(DIST)/$(LIB): $(OBJS)
	ar -cvru $@ $(OBJS)

%.o: %.cpp
	$(CPPC) -c $(CPP_FLAGS) $(INC) $< -o $@

$(DIST):
	if [ ! -e $(DIST) ]; then \
	    mkdir $(DIST); \
	fi

doc: $(DIST)
	doxygen

publish:
	ant publish

clean:
	rm -f -R $(DIST) $(OBJS)
