#ifndef process_h
#define process_h

#include "imagem.h"

//Alteração da imagem para escala em cinza
void ImagemCinza(Imagem *img);

//Função para retornar a media do pixel e processa-lo em uma escala cinza.
int MediaPixel(Pixel **pixel, int i, int j);

//Binarizar a imagem(preto e branco) a partir da escala cinza
void Segmentation(Imagem *img);

//Função para retornar o limiar
int Limiar(Imagem *img, int linha, int coluna);

//Função para 'afiar' a imagem(sharpen).
void Sharpening(Imagem *img);

//Função para borrar a imagem(Blur Box).
void Blur(Imagem *img);

#endif

