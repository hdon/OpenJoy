#include "common/diagrams.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>

struct OJ_DiagramElement * OJ_DiagramFromFileName(const char *filename) {
    char name[128];
    struct OJ_DiagramElement *d, *e;
    FILE * f;
    
    f = fopen(filename, "r");
    if (f == NULL) {
        return NULL;
    }

    d = NULL;
    while (feof(f) == 0) {
        int n, x, y, w, h;
        n = fscanf(f, "%d %d %d %d %s\n", &x, &y, &w, &h, &name);
        printf("scanned %d %d %d %d \"%s\"\n", x, y, w, h, name);
        
        if (n < 0) {
            fprintf(stderr, __FILE__"%d: fscanf() error %d: %s\n",
                __LINE__, errno, strerror(errno));
            return NULL;
        }
        if (n != 5) {
            return d;
        }

        if (d == NULL) {
            /* Initialize tail-end of linked list */
            d = malloc(sizeof(struct OJ_DiagramElement));
            d->next = NULL;
        } else {
            e = d;
            d = malloc(sizeof(struct OJ_DiagramElement));
            d->next = e;
        }

        d->x = x;
        d->y = y;
        d->w = w;
        d->h = h;
        d->name = strdup(name);
    }

    return d;
}

struct OJ_DiagramElement * OJ_DiagramCollidePoint(struct OJ_DiagramElement *d, int x, int y) {
    while (d) {
        if (x>=d->x && y>=d->y && x<(d->x+d->w) && y<(d->y+d->h))
            return d;
        d = d->next;
    }
    return NULL;
}

