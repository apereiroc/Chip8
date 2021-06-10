TARGET = chip8

SRCS  = $(shell find . -type f -name "*.cpp")
HEADS = $(shell find . -type f -name "*.h")
OBJS  = $(SRCS:.cpp=.o)

CXX      = g++
CXXFLAGS = -g -O0 -Wall -std=c++17 $(shell sdl2-config --cflags)
LIBS     = $(shell sdl2-config --libs)

all: $(TARGET)

$(TARGET): $(OBJS) $(HEADS)
	$(CXX) $(CXXFLAGS) $(LIBS) -o $@ $(OBJS)

$(OBJS): $(SRCS) $(HEADS)

run: all
	@./$(TARGET)

clean:
	rm $(TARGET) $(OBJS)
