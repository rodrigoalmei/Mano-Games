#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

#ifndef LOJA_H
#define LOJA_H

void adicionarCarrinho(char* usuario);
void copiarConteudo(FILE* file1, FILE* file2);
void bubbleSortPorPreco(float precos[], int avaliacoes[], char nomes[][50], int tamanho);
void bubbleSortPorAvaliacao(float precos[], int avaliacoes[], char nomes[][50], int tamanho);
void printJogos(float precos[], int avaliacoes[], char nomes[][50], int tamanho, FILE* arquivo);

void adicionarCarrinho(char* usuario) {
    FILE* listaJogos = fopen("jogos-ordenados.txt", "r");
    FILE* carrinho = fopen("carrinho.txt", "r");
    FILE* carrinhoTemp = fopen("temp.txt", "w");

    printf("Selecione o numero do jogo desejado: ");
    char jogoOpcao[3];
    scanf("%2s", jogoOpcao);

    char jogo[1000];
    char title[100];
    char preco[7];

    // Buscar informações do jogo selecionado
    while (fgets(jogo, sizeof(jogo), listaJogos) != NULL) {
        size_t posicao = strcspn(jogo, "\n");
        jogo[posicao] = '\0';
        char* textoArquivo = strtok(jogo, "-");

        if (strcmp(textoArquivo, jogoOpcao) == 0) {
            if (textoArquivo != NULL) {
                textoArquivo = strtok(NULL, "-");
                strcpy(title, textoArquivo);
                textoArquivo = strtok(NULL, "-");
                strcpy(preco, textoArquivo);
                break;
            }
        }
    }

    int usuarioEncontrado = 0; // Variável para verificar se o usuário está presente no carrinho

    // Verificar se o usuário já está presente no carrinho
    char linha[1000];
    while (fgets(linha, sizeof(linha), carrinho) != NULL) {
        char copiaLinha[1000];
        strcpy(copiaLinha, linha);
        char* textoArquivo = strtok(copiaLinha, ",");
        if (strcmp(textoArquivo, usuario) == 0) {
            size_t posicao = strcspn(linha, "\n");
            linha[posicao] = '\0';
            fputs(linha, carrinhoTemp);
            fprintf(carrinhoTemp, ",%s,%s\n", title, preco);
            usuarioEncontrado = 1;
        } else {
            fputs(linha, carrinhoTemp);
        }
    }

    // Se o usuário não estiver presente no carrinho, adicionar uma nova linha com seu nome
    if (!usuarioEncontrado) {
        fprintf(carrinhoTemp, "%s", usuario);
        fprintf(carrinhoTemp, ",%s,%s\n", title, preco);
    }

    fclose(listaJogos);
    fclose(carrinho);
    fclose(carrinhoTemp);

    carrinho = fopen("carrinho.txt", "w");
    carrinhoTemp = fopen("temp.txt", "r");

    copiarConteudo(carrinhoTemp, carrinho);

    fclose(carrinho);
    fclose(carrinhoTemp);
}

void copiarConteudo(FILE* file1, FILE* file2) {
    char linha[10000];

    while (fgets(linha, sizeof(linha), file1) != NULL) {
        fputs(linha, file2);
    }
}

void bubbleSortPorPreco(float precos[], int avaliacoes[], char nomes[][50], int tamanho) {
    int i, j;
    float temp_preco;
    int temp_avaliacao;
    char temp_nome[50];

    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - i - 1; j++) {
            if (precos[j] > precos[j + 1]) {
                temp_preco = precos[j];
                precos[j] = precos[j + 1];
                precos[j + 1] = temp_preco;

                temp_avaliacao = avaliacoes[j];
                avaliacoes[j] = avaliacoes[j + 1];
                avaliacoes[j + 1] = temp_avaliacao;

                strcpy(temp_nome, nomes[j]);
                strcpy(nomes[j], nomes[j + 1]);
                strcpy(nomes[j + 1], temp_nome);
            }
        }
    }
}

void bubbleSortPorAvaliacao(float precos[], int avaliacoes[], char nomes[][50], int tamanho) {
    int i, j;
    float temp_preco;
    int temp_avaliacao;
    char temp_nome[50];

    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - i - 1; j++) {
            if (avaliacoes[j] < avaliacoes[j + 1]) {
                temp_preco = precos[j];
                precos[j] = precos[j + 1];
                precos[j + 1] = temp_preco;

                temp_avaliacao = avaliacoes[j];
                avaliacoes[j] = avaliacoes[j + 1];
                avaliacoes[j + 1] = temp_avaliacao;

                strcpy(temp_nome, nomes[j]);
                strcpy(nomes[j], nomes[j + 1]);
                strcpy(nomes[j + 1], temp_nome);
            }
        }
    }
}

void printJogos(float precos[], int avaliacoes[], char nomes[][50], int tamanho, FILE* arquivo) {
    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d-%s-%.2f-%d\n", i + 1, nomes[i], precos[i], avaliacoes[i]);
    }
}

void loja(struct Cliente* clienteAtual, int logado) {
    FILE* arquivo;
    FILE* arquivoTemp;
    char nome[50];
    float preco;
    int avaliacao;
    int opcao, carrinhoOpcao;
    int tamanho = 0;

    arquivo = fopen("jogos.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    float* precos = malloc(sizeof(float) * 20);
    int* avaliacoes = malloc(sizeof(int) * 20);
    char nomes[20][50];

    while (fscanf(arquivo, "%[^,], %f, %d\n", nome, &preco, &avaliacao) == 3) {
        strcpy(nomes[tamanho], nome);
        precos[tamanho] = preco;
        avaliacoes[tamanho] = avaliacao;
        tamanho++;
    }

    fclose(arquivo);

    printf("Escolha uma opcao:\n");
    printf("1. Ordenar por preco\n");
    printf("2. Ordenar por nota\n");
    scanf("%d", &opcao);

    if (opcao == 1) {
        bubbleSortPorPreco(precos, avaliacoes, nomes, tamanho);
        printf("Jogos ordenados por preco:\n");
        for (int i = 0; i < tamanho; i++) {
            printf("[%d] - %s - %.2fR$ - Nota: %d\n", i + 1, nomes[i], precos[i], avaliacoes[i]);
        }
        arquivoTemp = fopen("jogos-ordenados.txt", "w");
        printJogos(precos, avaliacoes, nomes, tamanho, arquivoTemp);
        fclose(arquivoTemp);
    } else if (opcao == 2) {
        bubbleSortPorAvaliacao(precos, avaliacoes, nomes, tamanho);
        printf("Jogos ordenados por nota:\n");
        for (int i = 0; i < tamanho; i++) {
            printf("[%d] - %s - %.2fR$ - Nota: %d\n", i + 1, nomes[i], precos[i], avaliacoes[i]);
        }
        arquivoTemp = fopen("jogos-ordenados.txt", "w");
        printJogos(precos, avaliacoes, nomes, tamanho, arquivoTemp);
        fclose(arquivoTemp);
    } else {
        printf("Opcao invalida.\n");
    }

    printf("\nDeseja adicionar itens ao carrinho?\n[1]SIM [2]NAO ");
    scanf("%d", &carrinhoOpcao);
    if(carrinhoOpcao == 1){
        if(logado == 1){
            adicionarCarrinho(clienteAtual->usuario);
        } else{
        printf("Entre na sua conta para poder comprar!\n");
        }
    } else if(logado == 2){
        printf("Opcao invalida!\n");
    }

    free(precos);
    free(avaliacoes);
}

#endif