#ifndef OPENJOY_DIAGRAMS_HEADER_WJF823FH20G8H2G890H2GH89
#define OPENJOY_DIAGRAMS_HEADER_WJF823FH20G8H2G890H2GH89

struct OJ_DiagramElement {
    unsigned int x, y, w, h;
    char * name;
    struct OJ_DiagramElement * next;
};

struct OJ_DiagramElement * OJ_DiagramFromFileName(const char *filename);
struct OJ_DiagramElement * OJ_DiagramCollidePoint(struct OJ_DiagramElement *d, int x, int y);

#endif/*OPENJOY_DIAGRAMS_HEADER_WJF823FH20G8H2G890H2GH89*/

