#ifndef LOGIN_H
#define LOGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

int login(struct Cliente* clienteAtual) {
    FILE *file = fopen("clientes.txt", "r");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }

    char usuario[11];
    char senha[11];
    int encontrado = 0;

    printf("Digite seu nome de usuario:\n");
    scanf("%10s", usuario);
    printf("Digite sua senha:\n");
    scanf("%10s", senha);

    char linha[10000];
    while (fgets(linha, sizeof(linha), file) != NULL) {
        char *textoArquivo = strtok(linha, ",");
        if (strcmp(textoArquivo, usuario) == 0) {
            textoArquivo = strtok(NULL, ",");
            if (strcmp(textoArquivo, senha) == 0) {
                encontrado = 1;

                textoArquivo = strtok(NULL, ",");
                strncpy(clienteAtual->email, textoArquivo, sizeof(clienteAtual->email) - 1);
                clienteAtual->email[sizeof(clienteAtual->email) - 1] = '\0';

                textoArquivo = strtok(NULL, ",");
                strncpy(clienteAtual->carteira, textoArquivo, sizeof(clienteAtual->carteira) - 1);
                clienteAtual->carteira[sizeof(clienteAtual->carteira) - 1] = '\0';

                textoArquivo = strtok(NULL, ",");
                if(textoArquivo == NULL){
                    clienteAtual->jogos[sizeof(clienteAtual->jogos) - 1] = '\0';
                } else{
                    strncpy(clienteAtual->jogos, textoArquivo, sizeof(clienteAtual->jogos) - 1);
                }


                break;
            }
        }
    }

    fclose(file);

    if (encontrado == 1) {
        strncpy(clienteAtual->usuario, usuario, sizeof(clienteAtual->usuario) - 1);
        clienteAtual->usuario[sizeof(clienteAtual->usuario) - 1] = '\0';
        strncpy(clienteAtual->senha, senha, sizeof(clienteAtual->senha) - 1);
        clienteAtual->senha[sizeof(clienteAtual->senha) - 1] = '\0';

        printf("Login realizado com sucesso!\n");
        
        return 1;
        
    } else {
        printf("Usuario nao encontrado.\n");
        return 0;
    }
}


#endif
