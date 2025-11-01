#include <stdio.h>
#include <stdbool.h>

void decodificar_imagem(int imagem_analise[][1024], int linha_inicial, int coluna_inicial, int altura, int largura){
    //Caso Base
    //Guarda o primeiro pixel da imagem ou quadrante analisado
    int pixel_referencia = imagem_analise[linha_inicial][coluna_inicial];
    //Variavel para guardar se � uma sequ�ncia uniforme
    bool ehuniforme = true;
    //Percorrer a matriz(imagem original)
    //Percorrer as linhas da matriz 
    for (int i = linha_inicial; i < linha_inicial + altura; i++){
        //Percorrer as colunas da matriz
        for (int j = coluna_inicial; j < coluna_inicial + largura; j++){
            //Se a sequ�ncia n�o for uniforme
            if (pixel_referencia != imagem_analise[i][j]){
                ehuniforme = false;
                break; //Para o loop j ao encontrar um pixel diferente
            }
        }
        //Se encontrou um pixel diferente
        if (ehuniforme == false){
            break; //Para o loop i ao encontrar um pixel diferente
        }
    }
    //Se a sequ�ncia n�o for uniforme
    if (ehuniforme == false){
        //Imprime 'X' sequ�ncia mista
        printf("X");
        //Dividir a matriz em 4 quadrantes (matrizes menores) utilizando  recurs�o
        //declarar as alturas e larguras
        //altura para Q1 e Q2, superiores
        int a1 = (altura + 1) / 2; //Se altura for impar, deixa a maior parte para cima
        //altura para Q3 e Q4, inferiores
        int a2 = altura / 2; //Pega o inteiro que sobra de a1
        //largura para Q1 e Q3, esquerdos
        int l1 = (largura + 1) / 2; //Se largura for impar, deixa a maior parte para esquerda
        //largura para Q2 e Q4, direitos
        int l2 = largura / 2;

        //chamadas recursivas para todos os quadrantes

        //Verificar se as variaveis de altura e largura s�o maiores do que 0, para cada quadrante 

        if (a1 > 0 && l1 > 0){ //se a altura superior e a largura esquerda forem maiores do que 0
            //Quadrante 1 (superior esquerdo), come�a da linha e coluna inicial, at� a1 e l1 (altura superior e largura esquerda)
            decodificar_imagem(imagem_analise, linha_inicial, coluna_inicial, a1, l1);
        }
        if (a1 > 0 && l2 > 0){ //se a altura superior e a largura direita forem maiores do que 0
            //Quadrante 2 (superior direito), come�a da linha inicial e coluna inicial + l1 (largura da esquerda), at� a1 e l2 (altura superior e largura direita)
            decodificar_imagem(imagem_analise, linha_inicial, coluna_inicial + l1, a1, l2);
        }
        if (a2 > 0 && l1 > 0){ //se a altura inferior e a largura esquerda forem maiores do que 0
            //Quadrante 3 (inferior esquerdo), come�a da linha inicial + a1 (altura superior) e coluna inicial, at� a2 e l1 (altura inferior e largura esquerda)
            decodificar_imagem(imagem_analise,linha_inicial + a1, coluna_inicial, a2, l1);
        }
        if (a2 > 0 && l2 > 0){ //se a altura inferior e a largura direita forem maiores do que 0
            //Quadrante 4 (inferior direito), come�a da linha inicial + a1 e coluna inicial + l1, at� a2 e l2 (altura inferior e largura direita)
            decodificar_imagem(imagem_analise, linha_inicial + a1, coluna_inicial + l1, a2, l2);
        }
    }
    //Se a sequ�ncia for uniforme
    else{
        if (pixel_referencia == 0){ //Se for somente 0
            printf("B"); //Imprime branco
        }
        else{ //Se for somente 1
            printf("P"); //Imprime preto
        }
    }
}