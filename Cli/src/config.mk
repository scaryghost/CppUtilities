M_DIR=Cli
M_SRCS=Arguments.cpp CliBuilder.cpp Option.cpp
SRCS:= $(SRCS) $(addprefix $(M_DIR)/src/,$(M_SRCS))
