#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

struct jogosObtidos{
    char title[50];
    int id;
    struct jogosObtidos* next;
};

struct jogosObtidos* addJogoSelecionado(struct jogosObtidos* head, char title[], int id) { //adiciona os jogos selecionados como fila
    struct jogosObtidos* novoNo = (struct jogosObtidos*)malloc(sizeof(struct jogosObtidos));
    strcpy(novoNo->title, title);
    novoNo->id = id;
    novoNo->next = NULL;
    
    if (head == NULL) {
        return novoNo;
    } else {
        struct jogosObtidos* temp = head;
        
        while (temp->next != NULL) {
            temp = temp->next;
        }
        
        temp->next = novoNo;
        return head;
    }
}

void visualizarBiblioteca(char* usuario, int *sair) {
    FILE* file = fopen("clientes.txt", "r");
    struct jogosObtidos* jogosCliente = NULL;
    
    int opcaoJogo = 0, j = 1;
    
    printf("Jogos:\n\n");

    if (file == NULL) {
        printf("\nBiblioteca Vazia! :/\n");
    } else {
        char linha[500];
        
        while (fgets(linha, sizeof(linha), file) != NULL) {
            size_t posicao = strcspn(linha, "\n");//essa e a proxima linha substituem \n por \0 para indicar um fim de uma linha
            linha[posicao] = '\0';
            char* textoArquivo = strtok(linha, ",");
            
            if (strcmp(textoArquivo, usuario) == 0) {
                for (int i = 0; i < 4; i++) {
                    textoArquivo = strtok(NULL, ",");
                }

                if (textoArquivo != NULL) {
                    char* jogos = strtok(textoArquivo, "-");
                    while (jogos != NULL) {
                        jogosCliente = addJogoSelecionado(jogosCliente, jogos, j);
                        jogos = strtok(NULL, "-");
                        j++;
                    }
                }
            }
        }
        
        struct jogosObtidos* temp = jogosCliente;
        
        while (temp != NULL) {
            printf("[%d] %-20s\n", temp->id, temp->title);
            temp = temp->next;
        }

        temp = jogosCliente;
        printf("\nEscolha algo para jogar:\n");
        scanf("%d", &opcaoJogo);
        while (temp != NULL) {
            if(temp->id == opcaoJogo){
                printf("\nAbrindo %s...\n", temp->title);
                *sair = 1;
                break;
            } else{
            temp = temp->next;
            }
        }

    }
    
    fclose(file);
}

#endif