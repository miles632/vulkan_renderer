CC = g++
CXXFLAGS = -std=c++20 -I/usr/include -I/usr/local/include/glm -Iinclude
LDFLAGS = -L/usr/lib -lvulkan -lglfw

DEBUG_FLAGS = -g 
RELEASE_FLAGS = -O0 -Wall -Wshadow #-fsanitize=undefined,address
#-Wextra -Wpedantic -Wshadow -fsanitize=undefined,address

SOURCES = main.cpp src/camera.cpp #vk_engine.cpp
OBJECTS = $(SOURCES:.cpp=.o)

EXECUTABLE = final

# Default to release mode if MODE is not passed
CXXFLAGS += $(if $(filter debug,$(MODE)),$(DEBUG_FLAGS),$(RELEASE_FLAGS))

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)
	chmod +x $(EXECUTABLE)

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)

.PHONY: clean all debug release

debug:
	$(MAKE) MODE=debug clean all

release:
	$(MAKE) MODE=release clean all
