CXX := clang++
CPPFLAGS += -Iinclude $(shell pkg-config --cflags sdl3)
CXXFLAGS += -std=c++17 -Wall -Wextra
LDLIBS += $(shell pkg-config --libs sdl3)

SOURCES := src/main.cpp src/engine.cpp src/resourceManager.cpp 
HEADERS := include/engine.h include/resourceManager.h

Breakout: $(SOURCES) $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SOURCES) -o $@ $(LDLIBS)
