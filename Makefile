CXX := clang++
CPPFLAGS += -Iinclude $(shell pkg-config --cflags sdl3)
CXXFLAGS += -std=c++20 -Wall -Wextra
LDLIBS += $(shell pkg-config --libs sdl3)

SOURCES := src/main.cpp src/engine.cpp src/resourceManager.cpp src/vector2.cpp src/gameObject.cpp src/objectFactory.cpp src/components/spriteComponent.cpp src/components/inputComponent.cpp src/components/colliderComponent.cpp
HEADERS := include/engine.h include/resourceManager.h include/vector2.h include/gameObject.h include/component.h include/script.h include/objectFactory.h include/components/spriteComponent.h include/components/inputComponent.h include/components/colliderComponent.h include/scripts/ballscript.h include/scripts/brickscript.h include/scripts/paddlescript.h

Breakout: $(SOURCES) $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(SOURCES) -o $@ $(LDLIBS)
