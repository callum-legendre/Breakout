CXX := clang++
CPPFLAGS += -Iinclude $(shell pkg-config --cflags sdl3)
CXXFLAGS += -std=c++20 -Wall -Wextra
LDLIBS += $(shell pkg-config --libs sdl3)

SOURCES := src/main.cpp src/engine.cpp src/resourceManager.cpp src/vector2.cpp src/gameObject.cpp
HEADERS := include/engine.h include/resourceManager.h include/vector2.h include/gameObject.h include/component.h include/script.h

Breakout: $(SOURCES) $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SOURCES) -o $@ $(LDLIBS)
