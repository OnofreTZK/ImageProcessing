#ifndef process_h
#define process_h

#include "imagem.h"
#include <string.h>

//Alteração da imagem para escala em cinza
void ImagemCinza(Imagem *img);

//Função para retornar a media do pixel e processa-lo em uma escala cinza.
unsigned int MediaPixel(Pixel **pixel, int i, int j);

#endif