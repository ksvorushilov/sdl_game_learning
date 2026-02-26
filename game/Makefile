build:
	gcc -o game.exe sdl_test.c font.c -I/ucrt64/include/SDL2 \
    -L/ucrt64/lib \
    -static -static-libgcc -static-libstdc++ \
    -lmingw32 -lSDL2main -lSDL2 \
    -lwinmm -limm32 -lole32 -loleaut32 -lversion -luuid -lgdi32 -lsetupapi

run:
	./game.exe
