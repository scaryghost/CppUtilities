M_DIR:=IO
M_SRCS:=File.cpp
M_HEADERS:=File.h

SRCS:= $(SRCS) $(addprefix $(M_DIR)/src/,$(M_SRCS))
EXPORT_HEADERS:=$(EXPORT_HEADERS) $(addprefix $(M_DIR)/,$(M_HEADERS))
