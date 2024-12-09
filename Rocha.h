#ifndef ROCHA_H
#define ROCHA_H

typedef struct {
    int idRocha;
    int pesoI;
    int valorI;
} Rocha;

void InicializaRocha(Rocha* rch, int idRocha, int pesoI, int valorI);
int comparar_rochas(const void *a, const void *b);

#endif