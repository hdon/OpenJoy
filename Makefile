testdiagrams : src/tools/testdiagrams.c
	$(CC) `/usr/bin/sdl-config --cflags --libs` -lSDL_image -lGL -lGLU $^ -o $@

