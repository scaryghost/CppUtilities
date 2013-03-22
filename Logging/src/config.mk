M_DIR=Logging
M_SRCS=FileHandler.cpp  Level.cpp  Logger.cpp
SRCS:= $(SRCS) $(addprefix $(M_DIR)/src/,$(M_SRCS))
