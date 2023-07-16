#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Headers criados para o projeto
#include "interface.h"
#include "loja.h"
#include "login.h"
#include "cliente.h"
#include "cadastrar.h"
#include "biblioteca.h"
#include "carrinho.h"

int main() {
    struct Cliente clienteAtual;
    int opcao, logado = 0, sair = 0;
    while(sair == 0){
        if(logado == 0){
            menuInicial_UI(); 
            scanf("%d", &opcao);
            switch (opcao) {
                case 1:
                    loja(&clienteAtual, logado);
                    break;
                case 2:
                    logado = login(&clienteAtual);
                    break;
                case 3:
                    cadastrar();
                    break;
            }
        } else {
            menuUsuario_UI();
            scanf("%d", &opcao);
            switch(opcao){
                case 1:
                    loja(&clienteAtual, logado);
                    break;
                case 2:
                    visualizarBiblioteca(clienteAtual.usuario, &sair);
                    break;
                case 3:
                    visualizarCarrinho(&clienteAtual);
                    break;
                case 4:
                    logado=0;
                    break;
            }
        }
    }

    return 0;
}