#include "processos.h"
#define RedW 0.3
#define GreenW 0.59
#define BlueW 0.11
#define VMax 255

int i, j; //Declarei globalmente pois sera bastante usado nas operações com matrizes.



int MediaPixel(Pixel **pixel, int i, int j){
   int media;

   media = ((RedW*pixel[i][j].r) + (GreenW*pixel[i][j].g) + (BlueW*pixel[i][j].b));

   return media; 
  } 




void ImagemCinza(Imagem *img){
 
 int opti;
  
 for(opti = 0;opti<7;opti++){  
     for(i = 0;i<img->linha;i++){
         for(j = 0;j<img->coluna;j++){
             img->pixel[i][j].r = MediaPixel(img->pixel, i, j);
             img->pixel[i][j].g = MediaPixel(img->pixel, i, j);
             img->pixel[i][j].b = MediaPixel(img->pixel, i, j);
         }
      }  
   }
}




void Segmentation(Imagem *img){
  
  int v_limiar;
  printf("\nInsira do valor do limiar:\n");
  scanf(" %d", &v_limiar);
  getchar();

  for(i = 0;i<img->linha;i++){
  	for(j = 0;j<img->coluna;j++){
  		//Checagem de cada pixel em relacao ao limiar para atribuicao de 0 ou 255 em cada rgb.
  		if(img->pixel[i][j].r > v_limiar){
           img->pixel[i][j].r = VMax;
           img->pixel[i][j].g = VMax;
           img->pixel[i][j].b = VMax; 			
  		}
  		else{
           img->pixel[i][j].r = 0;
           img->pixel[i][j].g = 0; 
           img->pixel[i][j].b = 0;  
  		}
  	 }
   }
}
