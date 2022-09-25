# test_openCV
# $^ depended,once
# $@ target

INCLUDE = $(shell pkg-config --cflags opencv)
LIBS = $(shell pkg-config --libs opencv)
SOURCE=test_task.cpp Recovery.cpp
TARGET=test_task
OBJS=test_task.o Recovery.o
CXXFLAGS=-I../inc
$(TARGET):$(OBJS)
	g++ -o $(TARGET) $(OBJS) $(INCUDE)$(LIBS)
$(OBJECTS):$(SOURCES)
	g++ -c $(SOURCES)

clean:
	$(RM) $(OBJS) $(TARGET)
.PHONY: clean *clean

