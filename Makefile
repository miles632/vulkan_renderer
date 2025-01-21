CC = g++
CXXFLAGS = -std=c++17 -I/usr/include -I/usr/local/include/glm
LDFLAGS = -L/usr/lib -lvulkan -lglfw

DEBUG_FLAGS = -g -O0
RELEASE_FLAGS = -O2

SOURCES = main.cpp vk_engine.cpp
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
