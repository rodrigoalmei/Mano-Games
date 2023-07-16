#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

#ifndef CARRINHO_H
#define CARRINHO_H

void copiarJogos(FILE* file1, FILE* file2);
void limparCarrinho(char* usuario);
int realizarPagamento(float valorTotal, struct Cliente* clienteAtual);
void atualizarCliente(struct Cliente* clienteAtual);
void visualizarCarrinho(struct Cliente* clienteAtual);

void atualizarCliente(struct Cliente* clienteAtual) {
    FILE* arquivoOriginal = fopen("clientes.txt", "r");
    FILE* arquivoTemporario = fopen("temp.txt", "w");

    char linha[10000];
    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL) {
        char copiaLinha[10000];
        strcpy(copiaLinha, linha);

        char* usuario = strtok(copiaLinha, ",");
        if (strcmp(usuario, clienteAtual->usuario) == 0) {
            if (strlen(clienteAtual->jogos) > 0) {  // Verifica se a string de jogos não está vazia
                char* ultimaVirgula = strrchr(linha, ',');
                if (ultimaVirgula != NULL) {
                    *ultimaVirgula = '\0';
                    strcat(linha, ",");
                    strcat(linha, clienteAtual->jogos);
                }
            }
        }
        fprintf(arquivoTemporario, "%s", linha);
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemporario);

    arquivoOriginal = fopen("clientes.txt", "w");
    arquivoTemporario = fopen("temp.txt", "r");

    copiarJogos(arquivoTemporario, arquivoOriginal);

    fclose(arquivoOriginal);
    fclose(arquivoTemporario);
}

void visualizarCarrinho(struct Cliente* clienteAtual) {
    FILE* file = fopen("carrinho.txt", "r");
    float preco, total = 0, cashback;
    int opcaoCarrinho;
    int compraEfetuada = 0;
    char novosJogos[500] = "";
    char jogosAtuais[10001];
    strcat(jogosAtuais, "-");
    strcat(jogosAtuais, clienteAtual->jogos);

    //manter jogos atuais
    size_t length = strlen(jogosAtuais);
    if(length >0){
        jogosAtuais[length - 1] = '\n';
    }

    if (file == NULL) {
        printf("Carrinho Vazio...\n");
    } else {
        char linha[10000];
        while (fgets(linha, sizeof(linha), file) != NULL) {
            char* usuario = strtok(linha, ",");
            if (strcmp(usuario, clienteAtual->usuario) == 0) {
                char* jogo = strtok(NULL, ",");
                while (jogo != NULL) {
                    char* precoTexto = strtok(NULL, ",");
                    if (precoTexto == NULL) {
                        break;
                    }
                    preco = atof(precoTexto);
                    total += preco;
                    strcat(novosJogos, jogo);
                    strcat(novosJogos, "-");  // Alteração: Adiciona um hífen entre os jogos
                    printf("%s - %.2fR$\n", jogo, preco);
                    jogo = strtok(NULL, ",");
                }
            }
        }

        // Remove o último hífen, se existir
        if (strlen(novosJogos) > 0) {
            novosJogos[strlen(novosJogos) - 1] = '\0';
        }

        //adiciona novos atuais nos novos jogos
        strcat(novosJogos, jogosAtuais);

        // Atualiza o campo de jogos do clienteAtual com os novos valores
        strcpy(clienteAtual->jogos, novosJogos);

        printf("\n\nTotal: %.2fR$\n", total);
        cashback = total * 0.1;
        printf("Possivel cashback: %.2fR$\n", cashback);
        printf("----------------------------\n");
        printf("\n[1] Finalizar Compras\n");
        printf("[2] Continuar Comprando\n");
        printf("[3] Limpar Carrinho\n");
        scanf("%d", &opcaoCarrinho);
        switch (opcaoCarrinho) {
            case 1:
                compraEfetuada = realizarPagamento(total, clienteAtual);
                if (compraEfetuada == 1) {
                    atualizarCliente(clienteAtual);
                    limparCarrinho(clienteAtual->usuario);
                } else {
                    printf("Erro na compra\n");
                }
                break;
            case 2:
                break;
            case 3:
                limparCarrinho(clienteAtual->usuario);
                break;
            default:
                break;
        }
    }
    fclose(file);
}

void limparCarrinho(char* usuario) {
    FILE* arquivoOriginal = fopen("carrinho.txt", "r");
    FILE* arquivoTemporario = fopen("temp.txt", "w");

    char linha[10000];
    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL) {
        char copiaLinha[10000];
        strcpy(copiaLinha, linha);
        char* textoArquivo = strtok(copiaLinha, ",");
        if (strcmp(textoArquivo, usuario) != 0) {
            fputs(linha, arquivoTemporario);
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemporario);

    arquivoOriginal = fopen("carrinho.txt", "w");
    arquivoTemporario = fopen("temp.txt", "r");

    copiarJogos(arquivoTemporario, arquivoOriginal);

    fclose(arquivoOriginal);
    fclose(arquivoTemporario);
}

void copiarJogos(FILE* file1, FILE* file2) {
    char linha[10000];
    while (fgets(linha, sizeof(linha), file1) != NULL) {
        if (linha[0] != '\n') {
            fputs(linha, file2);
        }
    }
}

int realizarPagamento(float valorTotal, struct Cliente* clienteAtual) {
    int opcaoPagamento, usarCarteira;
    float carteira = atof(clienteAtual->carteira);
    float tempTotal = valorTotal - carteira;
    int pagamento = 0;

    if (carteira > 0) {
        printf("Voce possui %.2fR$ na sua carteira, deseja utilizar o saldo na sua compra?\n[1]SIM [2]NAO", carteira);
        scanf("%d", &usarCarteira);

        switch (usarCarteira) {
            case 1:
                if (tempTotal < 0) {
                    carteira = tempTotal * -1;
                    tempTotal = 0;
                } else {
                    carteira = 0;
                }
                break;
            case 2:
                break;
            default:
                printf("Opcao invalida. O saldo da carteira nao sera utilizado.\n");
                break;
        }
    }

    if (tempTotal != 0) {
        printf("\nOpcoes de pagamento:\n");
        printf("[1] A vista (PIX, debito ou boleto)\n");
        printf("[2] Cartao de Credito (em ate 12x, com acrescimo de 10%%)\n");
        printf("[3] Cancelar\n");
        printf("Selecione a opção de pagamento: ");
        scanf("%d", &opcaoPagamento);

        switch (opcaoPagamento) {
            case 1:
                carteira += valorTotal * 0.1;
                printf("Pagamento realizado com sucesso! Seu saldo atual e %.2fR$.\n", carteira);
                sprintf(clienteAtual->carteira, "%.2f", carteira);
                atualizarCarteira(clienteAtual);
                pagamento = 1;
                break;
            case 2: {
                int numParcelas;
                printf("Digite a quantidade de parcelas (1 a 12): ");
                scanf("%d", &numParcelas);

                if (numParcelas > 12) {
                    printf("O numero maximo de parcelas e 12. Pagamento nao realizado.\n");
                    break;
                }

                carteira += valorTotal * 0.1;
                sprintf(clienteAtual->carteira, "%.2f", carteira);
                atualizarCarteira(clienteAtual);
                float valorParcela = (tempTotal + tempTotal * 0.1) / numParcelas;

                printf("Pagamento realizado com parcelamento em %d vezes.\nValor de cada parcela: %.2fR$.\n", numParcelas, valorParcela);
                printf("Seu saldo atual e %.2fR$.\n", carteira);
                pagamento = 1;
                break;
            }
            case 3:
                printf("Pagamento cancelado.\n");
                break;
            default:
                printf("Opçao de pagamento invalida.\n");
                break;
        }
    } else {
        carteira += valorTotal * 0.1;
        sprintf(clienteAtual->carteira, "%.2f", carteira);
        atualizarCarteira(clienteAtual);
        printf("Pagamento realizado com sucesso! Seu saldo atual e %.2fR$.\n", carteira);
        pagamento = 1;
    }

    return pagamento;
}

void atualizarCarteira(struct Cliente *clienteAtual) {
    char novosDados[100];
    sprintf(novosDados, "%s,%s,%s,%s,%s", clienteAtual->usuario, clienteAtual->senha, clienteAtual->email, clienteAtual->carteira, clienteAtual->jogos);

    FILE* arquivoOriginal = fopen("clientes.txt", "r");
    FILE* arquivoTemporario = fopen("temp.txt", "w");

    char linha[10000];
    while (fgets(linha, sizeof(linha), arquivoOriginal) != NULL) {
        char copiaLinha[10000];
        strcpy(copiaLinha, linha);
        char* textoArquivo = strtok(copiaLinha, ",");
        if (strcmp(textoArquivo, clienteAtual->usuario) != 0) {
            fputs(linha, arquivoTemporario);
        } else {
            fputs(novosDados, arquivoTemporario);
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemporario);

    arquivoOriginal = fopen("clientes.txt", "w");
    arquivoTemporario = fopen("temp.txt", "r");

    while (fgets(linha, sizeof(linha), arquivoTemporario) != NULL)
        fputs(linha, arquivoOriginal);

    fclose(arquivoOriginal);
    fclose(arquivoTemporario);
}

#endif