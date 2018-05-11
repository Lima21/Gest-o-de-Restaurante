/*
 * File:   main.c
 * Author: Gonçalo Lima e Samuel Rodrigues
 *
 * Created on 21 de Dezembro de 2015, 11:18
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 *
 */


typedef struct ingredientes {

    char nome[50];
    int stock, ano, mes, dia, doses, cod, minimo;
} INGRE;


typedef struct prato {

    int numero, ing, disp;
    float preco;
    char nome[50];
    INGRE ingre[7];

} PRATO;


int menu(INGRE ingre[], int totalI) {
    int i=0;
    int opcao=0;
    printf("   #");
    for(i=0; i < 72; i++) {
        printf("=");
    }
    printf("#\n   # * wok to walk");
    for(i=0; i < 58; i++) {
        printf(" ");
    }
    printf("#\n");
    printf("   #");
    for(i=0; i < 72; i++) {
        printf("-");
    }

    printf("#\n   # * Software de gestão de um Restaurante     ");
    for(i=0; i < 28; i++) {
        printf(" ");
    }
    printf("#");
    printf("\n   #");
    for(i=0; i < 72; i++) {
        printf("=");
    }
    printf("#\n\n");

    printf(" 1. Inserir Ingredientes\n");
    printf(" 2. Listar Ingredientes\n");
    printf(" 3. Listar Ingredientes abaixo do stock\n");
    printf(" 4. Repor Stock\n");
    printf(" 5. Inserir Prato\n");
    printf(" 6. Listar Pratos\n");
    printf(" 7. Compra de Prato\n");
    printf(" 8. Atualizar Preço do Prato\n");
    printf(" 9. Atualizar Preço de todos os Pratos\n");
    printf("10. Mostrar valor em caixa  \n");
    printf("11. Listar os ingredientes com quantidade em stock mais baixa \n");
    printf("12. Listar a informação sobre os pratos por ingrediente \n");
    printf("13. Listar os ingredientes que ultrapassaram o limete de reabastecimento(60 dias)  \n");
    printf("14. Listar ingrediente(s) mais usado(s) \n");

    for(i=0; i < totalI; i++) {
        if(ingre[i].stock < ingre[i].minimo) {
            printf("\nDeverá repor o stock do ingrediente: %s\n", ingre[i].nome);
        }
    }
    printf("Introduza a opção:\n");
    scanf("%i", &opcao);
    return opcao;
}



int inserirIngre(INGRE ingre[], int totalI) {

    int aux=0;

    printf("Insira o código:\n");
    scanf("%i", &aux);
    if(existeCod(ingre, totalI, aux)) {
        printf("\nCódigo já existe!");
        return totalI;
    }
    ingre[totalI].cod = aux;
    printf("Insira o nome do Ingrediente:\n");
    getchar();
    gets(ingre[totalI].nome);
    printf("Insira a quantidade:\n");
    scanf("%i", &ingre[totalI].stock);
    printf("Insira a quantidade mínima:\n");
    scanf("%i", &ingre[totalI].minimo);
    printf("Insira a data (DD/MM/AAAA)\n");
    scanf("%i/%i/%i", &ingre[totalI].dia,&ingre[totalI].mes, &ingre[totalI].ano);
    totalI++;

    return totalI;
}

int existeCod(INGRE ingre[], int totalI, int aux) {
    int i =0;
    for(i=0; i < totalI; i++) {
        if(ingre[i].cod == aux) {
            return 1;
        }
    }
    return 0;
}

void listarIngre(INGRE ingre[], int totalI, int stock) {
    int i=0, maior=0, aux=0, j=0;
    for(i=0; i < totalI; i++) {
        if(strlen(ingre[i].nome) > maior ) {
            maior = strlen(ingre[i].nome);
        }
    }
    printf("Nome");
    aux = maior - 5 ;
    for(j=0; j < aux; j++ ) {
        printf(" ");
    }

    printf("\t\tStock\t#Min#\t###Data###\tCódigo\n");
    for(i=0; i < totalI; i++) {
        if(stock != 0) {
            if(ingre[i].stock < ingre[i].minimo) {

                printf("%s", ingre[i].nome);
                if(strlen(ingre[i].nome) < maior) {

                    aux = maior - strlen(ingre[i].nome);
                    for(j=0; j < aux; j++ ) {
                        printf(" ");
                    }
                }
                printf("\t\t%05i\t", ingre[i].stock);
                printf("%05i\t", ingre[i].minimo);
                printf("%02i/%02i/%04i\t",ingre[i].dia,ingre[i].mes, ingre[i].ano);
                printf("%06i\t\t", ingre[i].cod);
                printf("\n");
            }
        } else {

            printf("%s", ingre[i].nome);
            if(strlen(ingre[i].nome) < maior) {

                aux = maior - strlen(ingre[i].nome);
                for(j=0; j < aux; j++ ) {
                    printf(" ");
                }
            }
            printf("\t\t%05i\t", ingre[i].stock);
            printf("%05i\t", ingre[i].minimo);
            printf("%02i/%02i/%04i\t",ingre[i].dia,ingre[i].mes, ingre[i].ano);
            printf("%06i\t\t", ingre[i].cod);
            printf("\n");
        }
    }
}


void reporStock(INGRE ingre[], int totalI) {
    int opcao=0, i=0;
    printf("Introduza o código do ingrediente que deseja repor o stock:\n");
    scanf("%i", &opcao);
    for(i=0; i < totalI; i++) {
        if(opcao == ingre[i].cod) {
            printf("Introduza a quantidade que deseja adicionar ao ingrediente %s:\n", ingre[i].nome);
            scanf("%i", &opcao);
            ingre[i].stock += opcao;
        }
    }



}

int existeNum(PRATO pratos[], int totalP, int aux) {
    int i =0;
    for(i=0; i < totalP; i++) {
        if(pratos[i].numero == aux) {
            return 1;
        }
    }
    return 0;
}

int criarPrato(PRATO pratos[], int totalP, int totalI, INGRE ingre[]) {
    int aux=0, i=0, j=0, cod=0, stock=0;

    printf("Insira o código do prato:\n");
    scanf("%i", &aux);
    if(existeNum(pratos, totalP, aux)) {
        printf("\nCódigo já existe!");
        return totalP;
    }

    pratos[totalP].numero = aux;
    printf("Insira o nome do Prato:\n");
    getchar();
    gets(pratos[totalP].nome);
    printf("Introduza o Preço:\n");
    scanf("%f", &pratos[totalP].preco);
    printf("Introduza o número de Ingredientes (1-7):\n");
    scanf("%i", &pratos[totalP].ing);
    for(i=0; i < pratos[totalP].ing; i++) {
        printf("\n");
        listarIngre(ingre, totalI, stock);
        printf("\nIngrediente %i:\n", i+1);
        printf("Insira o código do Ingrediente:\n");

        scanf("%i", &cod);
        for(j=0; j < totalI; j++) {
            if(cod == ingre[j].cod) {
                strcpy(pratos[totalP].ingre[i].nome, ingre[j].nome);
                printf("Introduza o nº de doses:\n");
                scanf("%i", &pratos[totalP].ingre[i].doses);

            }
        }
    }
    totalP++;
    return totalP;
}


void listarPrato(PRATO pratos[], int totalP, int totalI, INGRE ingre[]) {

    int i=0, j=0, k=0, aux=0;
    printf("   Estado   \tPreço\tCódigo\tNome\n");
    for(i=0; i < totalP; i++) {
        for(j=0; j < pratos[i].ing; j++) {
            for(k=0; k < totalI; k++) {
                if(strcmp(pratos[i].ingre[j].nome, ingre[k].nome) == 0) {
                    if(pratos[i].ingre[j].doses > ingre[k].stock) {
                        aux = 1;
                    }
                }
            }
        }

        if(aux == 1) {
            printf("Indisponível");
            pratos[i].disp = 0;
        } else {

            printf(" Disponível ");
            pratos[i].disp = 1;
        }
        aux = 0;
        printf("\t%0.2f", pratos[i].preco);
        printf("\t%06i", pratos[i].numero);
        printf("\t%s", pratos[i].nome);
        printf("\n\n");
    }
}

void servirCliente(PRATO pratos[], int totalP, float *dinheiro, int totalI, INGRE ingre[]) {
    int i=0, aux=0, j=0, cod=0, k=0,l=0, m=0, n=0, notas[5], moedas[8], aux2=0;
    float pag=0, preco=0;
    printf("Insira o número de pratos que deseja:\n");
    scanf("%i", &aux);
    for(i=0; i < aux; i++) {
        printf("\nPratos:\n");
        listarPrato(pratos, totalP, totalI, ingre);
        printf("Insira o código do prato:\n");
        scanf("%i", &cod);
        for(j=0; j < totalP; j++) {
            if(pratos[j].numero == cod && pratos[j].disp == 1) {
                aux2 = 1;
                *dinheiro += pratos[j].preco;
                preco += pratos[j].preco;
                for(l=0; l < totalI; l++) {
                    for(m=0; m < totalP; m++) {
                        for(n=0; n < pratos[j].ing; n++) {
                            if(strcmp(ingre[l].nome, pratos[m].ingre[n].nome)==0 && pratos[m].numero == cod) {
                                ingre[l].stock -= pratos[m].ingre[n].doses;

                            }
                        }
                    }
                }
                
            } else {
                printf("Prato Indisponível ou Código errado\n");
                if(aux2 == 0) {
                    return 0;
                }
            }
        }
    }

    for(i=0; i < 8; i++) {
        moedas[i]=0;
    }

    for(i=0; i < 6; i++) {
        notas[i]=0;
    }


    do {
        printf("Preço total: %.2f\nQuantia paga:\n", preco);
        scanf("%f", &pag);

    } while(pag < preco);

    pag -=preco;

    printf("Troco = %.2f\n", pag);

    while(pag >= 100) {
        notas[0] +=1;
        pag-=100;

    }

    while(pag >= 50) {
        notas[1] +=1;
        pag-=50;

    }

    while(pag >= 20) {
        notas[2] +=1;
        pag-=20;

    }

    while(pag >= 10) {
        notas[3] +=1;
        pag-=10;

    }

    while(pag >= 5) {
        notas[4] +=1;
        pag-=5;

    }

    while(pag >= 2) {
        moedas[0] +=1;
        pag-=2;
    }

    while(pag >= 1) {

        moedas[1] +=1;
        pag-=1;
    }

    while(pag >= 0.5) {
        moedas[2] +=1;
        pag-=0.5;
    }

    while(pag >= 0.2) {
        moedas[3] +=1;
        pag-=0.2;
    }
    while(pag >= 0.10) {
        moedas[4] +=1;
        pag-=0.10;
    }

    while(pag >= 0.05) {
        moedas[5] +=1;
        pag-=0.05;
    }

    while(pag >= 0.02) {
        moedas[6] +=1;
        pag-=0.02;
    }

    while(pag >= 0.01) {
        moedas[7] +=1;
        pag-=0.01;
    }

    printf("%i x 100\n%i x 50\n%i x 20\n%i x 10\n%i x 5\n", notas[0], notas[1], notas[2], notas[3], notas[4]);
    printf("%i x 2\n%i x 1\n%i x 0.5\n%i x 0.2\n%i x 0.1\n", moedas[0], moedas[1], moedas[2], moedas[3], moedas[4]);
    printf("%i x 0.05\n%i x 0.02\n%i x 0.01\n", moedas[5], moedas[6], moedas[7]);
}





void atualizarPreco(PRATO pratos[], int totalP) {
    int cod=0, j=0;
    float preco=0;

    printf("Insira o código do prato:\n");
    scanf("%i", &cod);
    for(j=0; j < totalP; j++) {
        if(pratos[j].numero == cod) {
            printf("Preço anterior %f\nNovo preço:\n", pratos[j].preco);
            scanf("%f", &preco);
            pratos[j].preco = preco;
        }
    }
}

void atualizarTodos(PRATO pratos[], int totalP) {
    int cod=0, j=0;
    float preco=0, perc=0;
    printf("Introduza a percentagem sobre a qual quer alterar todos os preços: \n");
    scanf("%f", &perc);
    perc/= 100;
    for(j=0; j < totalP; j++) {
        preco = perc * pratos[j].preco;
        pratos[j].preco += preco;
    }
}

void stockBaixo(INGRE ingre[], int totalI) {
    int i=0, menor=0;
    menor = ingre[0].stock;
    for(i=0; i < totalI; i++) {
        if(ingre[i].stock < menor) {
            menor = ingre[i].stock;
        }
    }

    printf("Ingredientes com stock mais Baixo\n");
    for(i=0; i < totalI; i++) {
        if(ingre[i].stock == menor) {
            printf("%s\n",ingre[i].nome);
        }
    }
}

void pratoIngre(PRATO pratos[], int totalP, int totalI,INGRE ingre[]) {
    int i=0, j=0;
    char n_ingre[100];
    printf("Insira o nome do ingrediente: \n");
    getchar();
    gets(n_ingre);

    printf("\nPratos\n");
    for(i=0; i < totalP; i++) {
        for(j=0; j < pratos[i].ing; j++) {
            if(strcmp(n_ingre,pratos[i].ingre[j].nome)== 0) {
                printf("\n%s\n", pratos[i].nome);
            }
        }
    }
}

rebsStock(INGRE ingre[], int totalI) {
    int  i=0,dia=0, mes=0, ano=0, aux=0, ano1=0, mes1=0, dia1=0, aux2=0, anos[2][13]= {{0,31,28,31,30,31,30,31,31,30,31,30,31}, {0,31,29,31,30,31,30,31,31,30,31,30,31}};

    printf("\nInsira a data de Hoje DD/MM/AAAA\n");
    scanf("%i/%i/%i", &dia, &mes, &ano);
    printf("Ingredientes reabastecidos à mais de 60 dias:\n");
    for(i=0; i < totalI; i++) {
        aux=0;
        ano1 = ingre[i].ano;
        while(ano > ano1) {
            if(ano % 4 == 0 && ano % 100 !=0 || ano % 400==0) {
                aux += 366;
                ano1 +=1;
            } else {
                aux += 365;
                ano1 +=1;
            }
        }

        mes1= ingre[i].mes;
        while(mes > mes1) {
            if(ano % 4 == 0 && ano % 100 !=0 || ano % 400==0) {
                aux += anos[1][mes1];
                mes1 +=1;
            } else {
                aux += anos[0][mes1];
                mes1 +=1;
            }
        }

        while(mes < mes1) {
            if(ano % 4 == 0 && ano % 100 !=0 || ano % 400==0) {
                aux -= anos[1][mes1];
                mes1 -=1;
            } else {
                aux -= anos[0][mes1];
                mes1 -=1;
            }
        }

        dia1 = ingre[i].dia;

        while(dia > dia1) {
            aux+=1;
            dia1 +=1;
        }

        while(dia < dia1) {
            aux-=1;
            dia1 -=1;
        }

        if(aux > 60) {
            printf("\t\t%s\n", ingre[i].nome);
        }
    }
}

void maisUsados(PRATO pratos[],int totalP, int totalI,INGRE ingre[]) {
    int ingredientes[totalI];
    int i=0, j=0, k=0, maior=0;

    for(i=0; i < totalI; i++) {
        ingredientes[i] = 0;
    }

    for(i=0; i < totalI; i++) {
        for(j=0; j < totalP; j++) {
            for(k=0; k < pratos[j].ing; k++) {
                if(strcmp(ingre[i].nome, pratos[j].ingre[k].nome)==0) {
                    ingredientes[i] += 1;
                }
            }
        }
    }

    maior = ingredientes[0];

    for(i=0; i < totalI; i++) {
        if(ingredientes[i] >maior) {
            maior = ingredientes[i];
        }
    }

    for(i=0; i < totalI; i++) {
        if(ingredientes[i]== maior && maior > 0) {
            printf("O ingrediente mais usado é %s\n", ingre[i].nome);
        }
    }
}

int main(int argc, char** argv) {
    int totalI=0, opcao=0, stock=0, totalP=0;
    float dinheiro=0;
    PRATO pratos[100];
    INGRE ingre[100];

    do {
        opcao = menu(ingre, totalI);
        switch(opcao) {
        case 1:
            totalI = inserirIngre(ingre, totalI);
            break;
        case 2:
            stock=0;
            listarIngre(ingre, totalI, stock);
            break;
        case 3:
            stock=1;
            listarIngre(ingre, totalI, stock);
            break;
        case 4:
            stock=0;
            listarIngre(ingre, totalI, stock);
            reporStock(ingre, totalI);
            stock=0;
            listarIngre(ingre, totalI, stock);
            break;
        case 5:
            totalP = criarPrato(pratos,totalP,totalI,ingre);
            break;
        case 6:
            listarPrato(pratos, totalP, totalI, ingre);
            break;
        case 7:
            servirCliente(pratos, totalP, &dinheiro, totalI, ingre);
            break;
        case 8:
            listarPrato(pratos, totalP, totalI, ingre);
            atualizarPreco(pratos, totalP);
            listarPrato(pratos, totalP, totalI, ingre);
            break;
        case 9:
            listarPrato(pratos, totalP, totalI, ingre);
            atualizarTodos(pratos, totalP);
            listarPrato(pratos, totalP, totalI, ingre);
            break;
        case 10:
            printf("Valor em caixa: %.2f \n", dinheiro);
            break;
        case 11:
            stockBaixo(ingre, totalI);
            break;
        case 12:
            stock=0;
            listarIngre(ingre, totalI, stock);
            pratoIngre(pratos, totalP, totalI, ingre);
            break;
        case 13:
            rebsStock(ingre, totalI);
            break;
        case 14:
            maisUsados(pratos, totalP, totalI, ingre);
            break;
        }
    } while(opcao!=0);
    return (EXIT_SUCCESS);
}