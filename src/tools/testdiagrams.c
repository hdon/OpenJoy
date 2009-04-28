#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include "common/diagrams.h"
#include "load_texture.c"
#include "glerror.c"

int main(int argc, char **argv) {
    struct OJ_DiagramElement *diag;
    GLuint tex[2];
    int i;
    int back = 0, front = 0;

    if (argc >= 4) diag = OJ_DiagramFromFileName(argv[3]);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_SetVideoMode(640, 480, 0, SDL_OPENGL);

    for (i=1; i<argc && i<3; i++) {
        tex[i-1] = load_texture(argv[i]);
    }

    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        switch(event.type) {
            case SDL_QUIT:
                goto byebye;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case 'q':
                    case SDLK_ESCAPE:
                        goto byebye;
                    case '1':
                        back = 1;
                        break;
                    case '2':
                        front = 1;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case '1':
                        back = 0;
                        break;
                    case '2':
                        front = 0;
                        break;
                }
                break;
        }
        do {
            static unsigned int err = 0;
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glDisable(GL_DEPTH_TEST);
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glOrtho(0, 640, 480, 0, 1, -1);
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glEnable(GL_TEXTURE_2D);

            if (back) {
                glBindTexture(GL_TEXTURE_2D, tex[0]);
                glColor3ub(255, 255, 255);

                glBegin(GL_QUADS);
                glTexCoord2i(0, 1);
                glVertex2i(160, 360);
                glTexCoord2i(1, 1);
                glVertex2i(480, 360);
                glTexCoord2i(1, 0);
                glVertex2i(480, 120);
                glTexCoord2i(0, 0);
                glVertex2i(160, 120);
                glEnd();
            }
            if (front) {
                double throb = sin(SDL_GetTicks() * 0.007) / 4.0 + 0.75;
                glEnable(GL_BLEND);
                glBlendFunc(GL_ONE, GL_ONE);

                glBindTexture(GL_TEXTURE_2D, tex[1]);
                glColor3d(throb, throb, throb);

                glBegin(GL_QUADS);
                glTexCoord2i(0, 1);
                glVertex2i(160, 360);
                glTexCoord2i(1, 1);
                glVertex2i(480, 360);
                glTexCoord2i(1, 0);
                glVertex2i(480, 120);
                glTexCoord2i(0, 0);
                glVertex2i(160, 120);
                glEnd();

                glDisable(GL_BLEND);
            }

            glMatrixMode(GL_PROJECTION);
            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();

            SDL_GL_SwapBuffers();

            glError("main", &err);

        } while (0);
    }

    byebye:
    SDL_Quit();
    return 0;
}

