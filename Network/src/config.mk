M_DIR:=Network
M_SRCS:=InetAddress.cpp Socket.cpp ServerSocket.cpp
M_HEADERS:=InetAddress.h ServerSocket.h SocketException.h \
        Socket.h UnknownHostException.h

SRCS:= $(SRCS) $(addprefix $(M_DIR)/src/,$(M_SRCS))
EXPORT_HEADERS:=$(EXPORT_HEADERS) $(addprefix $(M_DIR)/,$(M_HEADERS))
