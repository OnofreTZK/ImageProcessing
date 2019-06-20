    
#ifndef imagem_h
#define imagem_h


#include "tipos.h"
#include <string.h>


//Função para ler a imagem e salvar os dados em uma struct.
void LerImagem(const char *nome_arquivo, Imagem *img);

//Função para alocar dinamicamente a matriz que irá receber os pixels.
void AlocaMatriz(Imagem *img);

//Função para liberar a memoria alocada nas matrizes.
void LiberaMemoria(Imagem *img);

//Função para gerar a imagem em outro arquivo a partir da struct.
void CriarImagem(const char *nome_arquivo, Imagem *img);

//Função para copiar o header de uma imagem para outra.
void HeaderCopy(Imagem *img, Imagem *img2);

//Função para inverter as linhas e colunas da imagem 1 para a 2.
void HeaderInvert(Imagem *img, Imagem *img2);

//Função para dobrar o tamanho da matriz.
void HeaderEnlarge(Imagem *img, Imagem *img2, int n);

//Função para diminuir o tamanho da matriz.
void HeaderReduce(Imagem *img, Imagem *img2);

//Função para o usuário nomear um arquivo para cada operação.
const char *getFilename(char *buffer, size_t bf_size);


#endif  
