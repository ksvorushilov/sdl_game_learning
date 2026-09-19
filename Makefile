### cool tutorial on Makefiles - https://makefiletutorial.com/
#compiler
CC = gcc

#output file (Actual target)
TARGET = bin/app.exe

# Source files
SRC = $(wildcard src/*.c)

SDL_SRC = $(wildcard src/sdl/*.c)

NCURSES_SRC = $(wildcard src/ncurses/*.c)

#object files
OBJECT = $(SRC:src/%.c=build/%.o)

SDL_OBJ = $(SDL_SRC:src/sdl/%.c=build/sdl/%.o)

NCURSES_OBJ = $(NCURSES_SRC:src/ncurses/%.c=build/ncurses/%.o)

#dependency objects - .d files that track all .h files included in .c files
DEPS = $(OBJECT:.o=.d)

DEPS_NCURSES = $(NCURSES_OBJ:.o=.d)

DEPS_SDL = $(SDL_OBJ:.o=.d)

#common compiler and linker flags
CFLAGS = -MMD -MP -Wall -Wextra -Wshadow -g -O0
CPPFLAGS = -Iinclude
LDFLAGS = 

#ncurses specific flags
ifeq ($(OS), Windows_NT)

	#compiler flags 
	CFLAGS_NC =  -I/ucrt64/include/ncurses -DNCURSES_STATIC
	
	#linker flags 
	LDFLAGS_NC = -L/ucrt64/lib -static -static-libgcc -static-libstdc++

	LDLIBS_NC = -lncurses

	CFLAGS_SDL = -I/ucrt64/include/SDL2

	LDFLAGS_SDL = -L/ucrt64/lib \
    -static -static-libgcc -static-libstdc++ \
    -lmingw32 -lSDL2main -lSDL2 \
    -lwinmm -limm32 -lole32 -loleaut32 -lversion -luuid -lgdi32 -lsetupapi

	LDLIBS_SDL =


else
	#compiler flags 
	CFLAGS_NC =  -I/usr/include
	
	#linker flags 
	LDFLAGS_NC = 

	LDLIBS_NC = -lncurses -ltinfo

	CFLAGS_SDL = $(shell sdl2-config --cflags)

    LDFLAGS_SDL = $(shell sdl2-config --libs)

	LDLIBS_SDL = -lm

endif


# Include dependency files if they exist
-include $(DEPS)
-include $(DEPS_SDL)
-include $(DEPS_NCURSES)

# Compile .c into .o
build/%.o: src/%.c
	@mkdir -p build 
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

build/sdl/%.o: src/sdl/%.c
	@mkdir -p $(@D) 
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CFLAGS_SDL) -c $< -o $@

build/ncurses/%.o: src/ncurses/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(CFLAGS_NC) -c $< -o $@
   
#mark functions with targets not attached to any filenames
.PHONY: sdl ncurses run clean

sdl: $(OBJECT) $(SDL_OBJ)
	mkdir -p bin
	$(CC) $(OBJECT) $(SDL_OBJ) $(LDFLAGS_SDL) -o $(TARGET) $(LDLIBS_SDL)

ncurses: $(OBJECT) $(NCURSES_OBJ)
	mkdir -p bin
	$(CC) $(OBJECT) $(NCURSES_OBJ) $(LDFLAGS_NC) -o $(TARGET) $(LDLIBS_NC)

#run the program
run:
	./$(TARGET)

# delete executable
clean:
	rm -f $(OBJECT) $(SDL_OBJ) $(NCURSES_OBJ) $(TARGET) \
	$(DEPS) $(DEPS_SDL) $(DEPS_NCURSES)
