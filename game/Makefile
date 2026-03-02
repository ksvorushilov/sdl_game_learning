### cool tutorial on Makefiles - https://makefiletutorial.com/
#compiler
CC = gcc

#output file (Actual target)
TARGET = game.exe

# Source files
SOURCE = sdl_test.c font.c slider.c manager.c

#object files
OBJECT = $(SOURCE:.c=.o)

#compiler flags
CFLAGS = -I/ucrt64/include/SDL2

#linker flags
LDFLAGS =  -L/ucrt64/lib \
    -static -static-libgcc -static-libstdc++ \
    -lmingw32 -lSDL2main -lSDL2 \
    -lwinmm -limm32 -lole32 -loleaut32 -lversion -luuid -lgdi32 -lsetupapi

$(TARGET): $(OBJECT)
	$(CC) $(LDFLAGS) $(OBJECT) -o $(TARGET)  
   
#mark functions with targets not attached to any filenames
.PHONY: run clean

#run the program
run:
	./$(TARGET)

# delete executable
clean:
	rm -f $(OBJECT) $(TARGET)
