#ifndef tipos_h
#define tipos_h


#include <stdio.h>
#include <stdlib.h>

//Tipo Pixel
typedef struct{
	int r, g, b; //Estrutura rgb(Red, Green, blue) que compõe um pixel.
}Pixel;


//Tipo imagem
typedef struct{
	char ID[3];
    int linha; 
    int coluna; 
    int max_value;
    Pixel **pixel; //Matriz de pixels.
}Imagem;

#endif

