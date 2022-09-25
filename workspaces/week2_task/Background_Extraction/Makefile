CXX = g++
LDLIBS += `pkg-config --libs opencv`
INC += `pkg-config --cflags opencv`
CPPFLAGS += -g -std=c++11 -Wall -I./
 
TARGET = main
OBJS = BG_main.o BG_Recovery.o
SRCS = BG_main.cpp BG_Recovery.cpp
HEAD = BG_H.hpp
 
$(TARGET):$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDLIBS)
 
%.o:%.c $(HEAD)
	$(CXX) $(INC) $(CPPFLAGS) -c $> -o $@
 
.PHONY:clean
clean:
	rm -r *.o
