CC = gcc
CXX = g++
ECHO = echo
RM = rm -f

CFLAGS = -Wall -Werror -ggdb -funroll-loops 
CXXFLAGS = -std=c++11 -Wall -Werror -ggdb -funroll-loops   # Add -std=c++11 for C++ files

LDFLAGS = -lncurses

TARGET = order_book
SRCS = orderbook.cpp file1.cpp file2.cpp  # Add all your source files here
HDRS = orderbook.hpp  # Add all your header files here
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(ECHO) Linking $@
	@$(CXX) $^ -o $@ $(LDFLAGS)

-include $(OBJS:.o=.d)

%.o: %.cpp
	@$(ECHO) Compiling $<
	@$(CXX) $(CXXFLAGS) -MMD -MF $*.d -c $<

clean:
	@$(ECHO) Removing all generated files
	@$(RM) *.o $(TARGET) *.d TAGS core vgcore.* gmon.out
