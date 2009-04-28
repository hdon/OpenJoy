#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include "common/diagrams.h"
#include "load_texture.c"
#include "glerror.c"

int main(int argc, char **argv) {
    struct OJ_DiagramElement *diag, *mouseover = NULL;
    GLuint tex[2];
    int i;
    int back = 0, front = 0;

    /* Diagram screen coords */
    int x1 = (640 - 256) / 2;
    int y1 = (480 - 256) / 2;
    int x2 = x1 + 256;
    int y2 = y1 + 256;

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
            case SDL_MOUSEMOTION:
                if (1) {
                    struct OJ_DiagramElement * d;
                    d = OJ_DiagramCollidePoint(diag, event.motion.x-x1, event.motion.y-y1);
                    if (d && d != mouseover) {
                        printf("activated \"%s\"\n", d->name);
                    }
                    mouseover = d;
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
                glVertex2i(x1, y2);
                glTexCoord2i(1, 1);
                glVertex2i(x2, y2);
                glTexCoord2i(1, 0);
                glVertex2i(x2, y1);
                glTexCoord2i(0, 0);
                glVertex2i(x1, y1);
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
                glVertex2i(x1, y2);
                glTexCoord2i(1, 1);
                glVertex2i(x2, y2);
                glTexCoord2i(1, 0);
                glVertex2i(x2, y1);
                glTexCoord2i(0, 0);
                glVertex2i(x1, y1);
                glEnd();

                glDisable(GL_BLEND);
            }
            if (mouseover) {
                double throb = sin(SDL_GetTicks() * 0.007) / 4.0 + 0.75;
                int mx1 = x1  + mouseover->x;
                int my1 = y1  + mouseover->y;
                int mx2 = mx1 + mouseover->w;
                int my2 = my1 + mouseover->h;
                double tx1 = mouseover->x / 256.0;
                double ty1 = mouseover->y / 256.0;
                double tx2 = (mouseover->x + mouseover->w) / 256.0;
                double ty2 = (mouseover->y + mouseover->h) / 256.0;

                glEnable(GL_BLEND);
                glBlendFunc(GL_ONE, GL_ONE);

                glBindTexture(GL_TEXTURE_2D, tex[1]);
                glColor3d(1, throb, throb);

                glBegin(GL_QUADS);
                glTexCoord2d(tx1, ty2);
                glVertex2i  (mx1, my2);
                glTexCoord2d(tx2, ty2);
                glVertex2i  (mx2, my2);
                glTexCoord2d(tx2, ty1);
                glVertex2i  (mx2, my1);
                glTexCoord2d(tx1, ty1);
                glVertex2i  (mx1, my1);
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
        SDL_Delay(10);
    }

    byebye:
    SDL_Quit();
    return 0;
}

