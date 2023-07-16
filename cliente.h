#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Cliente {
    char usuario[21];
    char senha[21];
    char email[51];
    char carteira[11];
    char jogos[10000];
};

#endif