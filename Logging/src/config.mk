M_DIR:=Logging
M_SRCS:=FileHandler.cpp  Level.cpp  Logger.cpp
M_HEADERS:=InvalidArgumentException.h Logger.h ConsoleHandler.h \
        FileHandler.h Level.h FileException.h Handler.h logging.h

SRCS:= $(SRCS) $(addprefix $(M_DIR)/src/,$(M_SRCS))
EXPORT_HEADERS:=$(EXPORT_HEADERS) $(addprefix $(M_DIR)/,$(M_HEADERS))
