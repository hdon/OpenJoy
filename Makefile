testdiagrams : src/tools/testdiagrams.c src/common/diagrams.c
	$(CC) -Isrc `/usr/bin/sdl-config --cflags --libs` -lSDL_image -lGL -lGLU $^ -o $@

