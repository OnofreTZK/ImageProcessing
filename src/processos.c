#include "processos.h"

int i, j; //Declarei globalmente pois sera bastante usado nas operações com matrizes.



unsigned int MediaPixel(Pixel **pixel, int i, int j){
   unsigned int media;

   media = (pixel[i][j].r + pixel[i][j].g + pixel[i][j].b);

   return media/3; 
  }







void ImagemCinza(Imagem *img){

	for(i = 0;i<img->linha;i++){
        for(j = 0;j<img->coluna;j++){
          img->pixel[i][j].r = MediaPixel(img->pixel, i, j);
          img->pixel[i][j].g = MediaPixel(img->pixel, i, j);
          img->pixel[i][j].b = MediaPixel(img->pixel, i, j);
        }
    }  
}
