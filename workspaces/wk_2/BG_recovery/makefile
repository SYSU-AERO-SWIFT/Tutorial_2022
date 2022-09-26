INCL += $(shell pkg-config --cflags opencv)
LIBS += $(shell pkg-config --libs opencv)
CPPFLAGS += -std=c++11 -g

VPATH += src:build:inc:test

SRCS = recovery.cpp recovery_test.cpp
OBJS = $(SRCS:.cpp=.o)
HEAD = recovery.h
TARGET = demo.out

$(TARGET):$(OBJS)
	g++ $(INCL) $(CPPFLAGS) $^ -o bin/$(TARGET) $(LIBS)
	mv $^ build

%.o:%.cpp $(HEAD)
	g++ $(INCL) $(CPPFLAGS) -c $< -o $@

.PHONY:clean
clean:
	rm -f *.o
	rm -f bin/$(TARGET) build/*.o
