### cool tutorial on Makefiles - https://makefiletutorial.com/
#compiler
CC = gcc

#output file (Actual target)
TARGET = snake.exe

# Source files
SOURCE = main.c font.c game_loop.c menu_loop.c manager.c snake.c collision.c 

#object files
OBJECT = $(SOURCE:.c=.o)

#dependency objects - .d files that track all .h files included in .c files
DEPS = $(OBJECT:.o=.d)

#compiler flags
CFLAGS = -I/ucrt64/include/SDL2 -MMD -MP -Wall -Wextra -Wshadow

#linker flags
LDFLAGS =  -L/ucrt64/lib \
    -static -static-libgcc -static-libstdc++ \
    -lmingw32 -lSDL2main -lSDL2 \
    -lwinmm -limm32 -lole32 -loleaut32 -lversion -luuid -lgdi32 -lsetupapi

# Main target
$(TARGET): $(OBJECT)
	$(CC) $(LDFLAGS) $(OBJECT) -o $(TARGET)  

# Include dependency files if they exist
-include $(DEPS)

# Compile .c into .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
   
#mark functions with targets not attached to any filenames
.PHONY: run clean

#run the program
run:
	./$(TARGET)

# delete executable
clean:
	rm -f $(OBJECT) $(TARGET) $(DEPS)
