INCL += $(shell pkg-config --cflags opencv)
LIBS += $(shell pkg-config --libs opencv)
CPPFLAGS += -std=c++11 -g

VPATH += src:build:inc

SRCS = recovery.cpp recovery_main.cpp
OBJS = $(SRCS:.cpp=.o)
HEAD = recovery.h
TARGET = demo

$(TARGET):$(OBJS)
	g++ $(INCL) $(CPPFLAGS) $^ -o bin/$(TARGET) $(LIBS)
	mv -f $^ build

%.o:%.cpp $(HEAD)
	g++ $(INCL) $(CPPFLAGS) -c $< -o $@

.PHONY:clean
clean:
	rm -f *.o
	rm -f bin/$(TARGET) build/*.o 
