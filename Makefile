TARGET = chip8

SRCS  = $(shell find . -type f -name "*.cpp")
HEADS = $(shell find . -type f -name "*.h")
OBJS  = $(SRCS:.cpp=.o)

CXX = g++
CXXFLAGS = -g -O0 -std=c++17

all: $(TARGET)

$(TARGET): $(OBJS) $(HEADS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

$(OBJS): $(SRCS) $(HEADS)

run: all
	@./$(TARGET)

clean:
	rm $(TARGET) $(OBJS)