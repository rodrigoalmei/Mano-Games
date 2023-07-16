#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"

#ifndef CADASTRAR_H
#define CADASTRAR_H

void validarSenha(struct Cliente *s); // Protótipo da função validarSenha

void cadastrar() {
    struct Cliente novoCliente;
    FILE *file = fopen("clientes.txt", "a");

    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    printf("Digite seu nome de usuario:\n");
    scanf("%10s", novoCliente.usuario);
    fprintf(file, "\n%s,", novoCliente.usuario); // Adiciona o usuário no arquivo

    printf("Digite sua senha:\n");
    scanf("%10s", novoCliente.senha);
    validarSenha(&novoCliente);
    fprintf(file, "%s,", novoCliente.senha); // Adiciona a senha no arquivo

    printf("Digite seu email:\n");
    scanf("%40s", novoCliente.email);
    fprintf(file, "%s,0,", novoCliente.email); // Adiciona o email no arquivo com quebra de linha

    fclose(file);
}

void validarSenha(struct Cliente *s){ //checar se a senha tem numero, letra maiuscula, minuscula e caracter especial
    int minuscula = 0, maiuscula = 0, numero = 0, especial = 0, i = 0;
    while(s -> senha[i] != '\0'){
        if(s -> senha[i] == 'A' || s -> senha[i] == 'B' || s -> senha[i] == 'C' || s -> senha[i] == 'D' || s -> senha[i] == 'E' || s -> senha[i] == 'F' || s -> senha[i] == 'G' || s -> senha[i] == 'H' || s -> senha[i] == 'I' || s -> senha[i] == 'J' || s -> senha[i] == 'K' || s -> senha[i] == 'L' || s -> senha[i] == 'M' || s -> senha[i] == 'N' || s -> senha[i] == 'O' || s -> senha[i] == 'P' || s -> senha[i] == 'Q' || s -> senha[i] == 'R' || s -> senha[i] == 'S' || s -> senha[i] == 'T' || s -> senha[i] == 'U' || s -> senha[i] == 'V' || s -> senha[i] == 'W' || s -> senha[i] == 'X' || s -> senha[i] == 'Y' || s -> senha[i] ==  'Z'){
            maiuscula++;
        } else if(s -> senha[i] == 'a' || s -> senha[i] == 'b' || s -> senha[i] == 'c' || s -> senha[i] == 'd' || s -> senha[i] == 'e' || s -> senha[i] == 'f' || s -> senha[i] == 'g' || s -> senha[i] == 'h' || s -> senha[i] == 'i' || s -> senha[i] == 'j' || s -> senha[i] == 'k' || s -> senha[i] == 'l' || s -> senha[i] == 'm' || s -> senha[i] == 'n' || s -> senha[i] == 'o' || s -> senha[i] == 'p' || s -> senha[i] == 'q' || s -> senha[i] == 'r' || s -> senha[i] == 's' || s -> senha[i] == 't' || s -> senha[i] == 'u' || s -> senha[i] == 'v' || s -> senha[i] == 'w' || s -> senha[i] == 'x' || s -> senha[i] == 'y' || s -> senha[i] == 'z'){
            minuscula++;
        } else if(s -> senha[i] == '1' || s -> senha[i] == '2' || s -> senha[i] == '3' || s -> senha[i] == '4' || s -> senha[i] == '5' || s -> senha[i] == '6' || s -> senha[i] == '7' || s -> senha[i] == '8' || s -> senha[i] == '9'){
            numero++;
        } else if(s -> senha[i] == '*' || s -> senha[i] == '_' || s -> senha[i] == '-' || s -> senha[i] == '\\' || s -> senha[i] == '/' || s -> senha[i] == '!' || s -> senha[i] == '@' || s -> senha[i] == '#' || s -> senha[i] == '$' || s -> senha[i] =='%' || s -> senha[i] == '(' || s -> senha[i] == ')' || s -> senha[i] == '+' || s -> senha[i] == '=' || s -> senha[i] == '[' || s -> senha[i] == ']' || s -> senha[i] == '{' || s -> senha[i] == '}'){
            especial++;
        } else{
            printf("Sua senha possui caracteres invalidos! Tente novamente:\n");
            scanf("%s", s->senha);
            validarSenha(s);
        }
        i++;
    }
    if(minuscula == 0 || maiuscula == 0 || numero == 0 || especial == 0){
        printf("Senha invalida! Certifique-se de que sua senha possui pelo menos: 1 caracter minusculo, 1 caracter maiusculo, 1 numero e 1 caracter especial.\nTente novamente:\n");
        scanf("%s", s->senha);
        validarSenha(s);
    }
}

#endif