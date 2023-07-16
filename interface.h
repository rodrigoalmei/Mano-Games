#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef INTERFACE_H
#define INTERFACE_H

void menuInicial_UI() {
    printf(" __________________________________________________________\n");
    printf("|                        MANO GAMES                        |\n");
    printf("|__________________________________________________________|\n");
    printf("|                       [1]LOJA                            |\n");
    printf("|                       [2]ENTRAR                          |\n");
    printf("|                       [3]CADASTRAR                       |\n");
    printf("|__________________________________________________________|\n\n");
}

void menuUsuario_UI() {
    printf(" __________________________________________________________\n");
    printf("|                        MANO GAMES                        |\n");
    printf("|__________________________________________________________|\n");
    printf("|                       [1]LOJA                            |\n");
    printf("|                       [2]BIBLIOTECA                      |\n");
    printf("|                       [3]CARRINHO                        |\n");
    printf("|                       [4]SAIR                            |\n");
    printf("|__________________________________________________________|\n\n");
}

#endif