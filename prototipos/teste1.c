#include <stdio.h>

char decodificar_imagem(int imagem_analise[][1024], int linha_inicial, int coluna_inicial, int altura, int largura){
    //Guarda o primeiro pixel da imagem ou quadrante analisado
    int pixel_referencia = imagem_analise[linha_inicial][coluna_inicial];
    //Percorrer a matriz(imagem original)
    //Percorrer as linhas da matriz 
    for (int i = linha_inicial; i < linha_inicial + altura; i++){
        //Percorrer as colunas da matriz
        for (int j = coluna_inicial; j < coluna_inicial + largura; j++){
            //Se a sequência for uniformemente '0'
            if (pixel_referencia == 0){
                //Retorna B (branco)
                return 'B';
            }
            //Se a sequência for uniformemente '1'
            if (pixel_referencia == 1){
                //Retorna P (preto)
                return 'P';
            }
            //Senão for uma sequência uniforme
            else{
                //Retorna X
                return 'X';
            }
        }
    }
    


}