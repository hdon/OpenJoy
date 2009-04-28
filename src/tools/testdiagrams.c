#include <SDL.h>
#include <SDL_image.h>
#include "load_texture.c"

int main(int argc, char **argv) {
    int i;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_SetVideoMode(640, 480, 0, SDL_OPENGL);

    for (i=1; i<argc; i++) {
        load_texture(argv[i]);
    }

    while (1) {
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch(event.type) {
            case SDL_QUIT:
                goto byebye;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == 'q'
                ||  event.key.keysym.sym == SDLK_ESCAPE)
                    goto byebye;
                else {
                    glMatrixMode(GL_PROJECTION);
                    glOrtho(0, 640, 480, 0, 1, -1);
                    glMatrixMode(GL_MODELVIEW);
                    glLoadIdentity();
                    glColor3d(1,1,1);
                    glBegin(GL_QUADS);
                    glVertex2f(160, 360);
                    glVertex2f(480, 360);
                    glVertex2f(480, 120);
                    glVertex2f(160, 120);
                    SDL_GL_SwapBuffers();
                }
        }
    }

    byebye:
    SDL_Quit();
    return 0;
}

