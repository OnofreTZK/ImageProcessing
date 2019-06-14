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
Imagem *Sharpening(Imagem *img, Imagem *img2);

//Função para borrar a imagem(Blur Box).
Imagem *Blur(Imagem *img, Imagem *img2);

//Função para realizar a detecção de bordas
Imagem *Bordas(Imagem *img, Imagem *img2);

//Função para aplicar o borrão de Gauss.
Imagem *Gauss(Imagem *img, Imagem *img2);

//Função para aplicar detecção de bordas com o operador de sobel.
Imagem *Sobel(Imagem *img, Imagem *img2);

//Função para rotacionar a imagem 90° para a esquerda.
Imagem *GirarPraEsquerda(Imagem *img1, Imagem *img2);

//Função para rotacionar a imagem 90° para a direita.
Imagem *GirarPraDireita(Imagem *img1, Imagem *img2);

//Função para rotacionar a imagem em 180°.
Imagem *GirarCentoEOitenta(Imagem *img1, Imagem *img2);

//Função para espelhar a imagem na horizontal.
Imagem *EspelharHorizontal(Imagem *img1, Imagem *img2);

//Função para espelhar a imagem na vertical.
Imagem *EspelharVertical(Imagem *img1, Imagem *img2);

#endif