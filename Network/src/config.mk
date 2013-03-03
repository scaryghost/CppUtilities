M_DIR=Network
M_SRCS=InetAddress.cpp Socket.cpp ServerSocket.cpp
SRCS:= $(SRCS) $(addprefix $(M_DIR)/src/,$(M_SRCS))
