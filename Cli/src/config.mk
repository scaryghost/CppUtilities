M_DIR:=Cli
M_SRCS:=Arguments.cpp CliBuilder.cpp Option.cpp
M_HEADERS:=cli.h CliBuilder.h Arguments.h CliOptionException.h Option.h

SRCS:= $(SRCS) $(addprefix $(M_DIR)/src/,$(M_SRCS))
EXPORT_HEADERS:=$(EXPORT_HEADERS) $(addprefix $(M_DIR)/,$(M_HEADERS))
