#include <stdio.h>
#include <stdbool.h>

char decodificar_imagem(int imagem_analise[][1024], int linha_inicial, int coluna_inicial, int altura, int largura){
    //Caso Base
    //Guarda o primeiro pixel da imagem ou quadrante analisado
    int pixel_referencia = imagem_analise[linha_inicial][coluna_inicial];
    //Variavel para guardar se é uma sequência uniforme
    bool ehuniforme = true;
    //Percorrer a matriz(imagem original)
    //Percorrer as linhas da matriz 
    for (int i = linha_inicial; i < linha_inicial + altura; i++){
        //Percorrer as colunas da matriz
        for (int j = coluna_inicial; j < coluna_inicial + largura; j++){
            //Se a sequência não for uniforme
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
}