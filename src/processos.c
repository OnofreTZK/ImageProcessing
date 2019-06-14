#include "processos.h"
#include <math.h>
#define RedW 0.3
#define GreenW 0.59
#define BlueW 0.11
#define VMax 255

int i, j, k, l; //Declarei globalmente pois sera bastante usado nas operações com matrizes.



int MediaPixel(Pixel **pixel, int i, int j){
    int media;
    //Método da combinação linear para conversão em escala cinza(a imagem fica mais suave)
    media = ((RedW*pixel[i][j].r) + (GreenW*pixel[i][j].g) + (BlueW*pixel[i][j].b));

    return media; 
} 





void ImagemCinza(Imagem *img){

    int opti; // otimizador para aplicar a escala cinza n vezes com o intuito de eliminar qualquer vestigio de cor.

    for(opti = 0;opti<3;opti++){  
        for(i = 0;i<img->linha;i++){
            for(j = 0;j<img->coluna;j++){
                img->pixel[i][j].r = MediaPixel(img->pixel, i, j);
                img->pixel[i][j].g = MediaPixel(img->pixel, i, j);
                img->pixel[i][j].b = MediaPixel(img->pixel, i, j);
            }
        }  
    }
}




int Limiar(Imagem *img, int linha, int coluna){
    int media = 0;

    for(i = 0; i < linha; i++){
        for(j = 0; j < coluna; j++){
            media += img->pixel[i][j].r;            
            media += img->pixel[i][j].g;
            media += img->pixel[i][j].b;
        }
    }

    return media/((linha*coluna)*3); //A media retornada deve ser o valor de todos os pixels(Linha*coluna)*3 pixels(rgb).
}




void Segmentation(Imagem *img){

    int v_limiar;
    
    v_limiar = Limiar(img, img->linha, img->coluna);// a melhor binarização é feita fazendo a media dos pixels da matriz.

    printf("\n\tlimiar calculado = %d\n", v_limiar);   

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





Imagem *Sharpening(Imagem *img, Imagem *img2){
    int filter[3][3] = {{0, -1, 0},
                        {-1, 5, -1},
                        {0, -1, 0}};

    HeaderCopy(img, img2);

    AlocaMatriz(img2);

    for(i = 0; i < img->linha; i++){
        for(j = 0; j < img->coluna; j++){
            int aux_r = 0, aux_g = 0, aux_b = 0;
            for(k = 0; k<3; k++){
                for(l = 0; l<3; l++){
                    if( i+k-1 == -1 || j+l-1 == -1 || i+k-1 == img->linha || j+l-1 == img->coluna){
                        continue; 
                    }
                   
                   aux_r += (img->pixel[i-1+k][j-1+l].r) * filter[k][l];
                   aux_g += (img->pixel[i-1+k][j-1+l].g) * filter[k][l];
                   aux_b += (img->pixel[i-1+k][j-1+l].b) * filter[k][l];

                }
            }
              if(aux_r > 255){
                aux_r = 255;
            }
            if(aux_r < 0){
                aux_r = 0;
            }
            if(aux_g > 255){
                aux_g = 255;
            }
            if(aux_g < 0){
                aux_g = 0;
            }
            if(aux_b > 255){
                aux_b = 255;
            }
            if(aux_b < 0){
                aux_b = 0;
            }

            img2->pixel[i][j].r = (unsigned short int) (aux_r);
            img2->pixel[i][j].g = (unsigned short int) (aux_g);
            img2->pixel[i][j].b = (unsigned short int) (aux_b);            
        }
    }

    return img2;
}




Imagem *Blur(Imagem *img, Imagem *img2){
    float filter[3][3] = {{ 1, 1, 1},
                          { 1, 1, 1},
                          { 1, 1, 1}};

    
    int aux_r, aux_g, aux_b;
    
    HeaderCopy(img, img2);
    
    AlocaMatriz(img2);
    
        for(i = 0; i < img->linha; i++){
            for(j = 0; j < img->coluna; j++){
                aux_r = 0, aux_g = 0, aux_b = 0;
                for(k = 0; k<3; k++){
                    for(l = 0; l<3; l++){
                    
                        if( i+k-1 == -1 || j+l-1 == -1 || i+k-1 >= img->linha || j+l-1 >= img->coluna){
                            continue; 
                        }
                   
                       aux_r = aux_r + ((img->pixel[i-1+k][j-1+l].r) * filter[k][l])/9;
                       aux_g = aux_g + ((img->pixel[i-1+k][j-1+l].g) * filter[k][l])/9;
                       aux_b = aux_b + ((img->pixel[i-1+k][j-1+l].b) * filter[k][l])/9;
                   
                    }
                }
            
                if(aux_r > 255){
                    aux_r = 255;
                }
                if(aux_r < 0){
                    aux_r = 0;
                }
                if(aux_g > 255){
                    aux_g = 255;
                }
                if(aux_g < 0){
                    aux_g = 0;
                }
                if(aux_b > 255){
                    aux_b = 255;
                }
                if(aux_b < 0){
                    aux_b = 0;
                } 
            
                img2->pixel[i][j].r = (unsigned short int) (aux_r);
                img2->pixel[i][j].g = (unsigned short int) (aux_g);
                img2->pixel[i][j].b = (unsigned short int) (aux_b);            
            }
        }
        
    
    return img2;


}




Imagem *Bordas(Imagem *img, Imagem *img2){
    float filter[3][3] = {{ -1, -1, -1},
                          { -1, 8, -1},
                          { -1, -1, -1}};

    
    int aux_r, aux_g, aux_b;
    
    HeaderCopy(img, img2);
    
    AlocaMatriz(img2);
    
    
        for(i = 0; i < img->linha; i++){
            for(j = 0; j < img->coluna; j++){
                aux_r = 0, aux_g = 0, aux_b = 0;
                for(k = 0; k<3; k++){
                    for(l = 0; l<3; l++){
                    
                        if( i+k-1 == -1 || j+l-1 == -1 || i+k-1 >= img->linha || j+l-1 >= img->coluna){
                            continue; 
                        }
                   
                       aux_r = aux_r + ((img->pixel[i-1+k][j-1+l].r) * filter[k][l]);
                       aux_g = aux_g + ((img->pixel[i-1+k][j-1+l].g) * filter[k][l]);
                       aux_b = aux_b + ((img->pixel[i-1+k][j-1+l].b) * filter[k][l]);
                   
                    }
                }

                if(aux_r > 255){
                    aux_r = 255;
                }
                if(aux_r < 0){
                    aux_r = 0;
                }
                if(aux_g > 255){
                    aux_g = 255;
                }
                if(aux_g < 0){
                    aux_g = 0;
                }
                if(aux_b > 255){
                    aux_b = 255;
                }
                if(aux_b < 0){
                    aux_b = 0;
                } 
            
                img2->pixel[i][j].r = (unsigned short int) (aux_r);
                img2->pixel[i][j].g = (unsigned short int) (aux_g);
                img2->pixel[i][j].b = (unsigned short int) (aux_b);            
            }
        }

        
    

    
    return img2;

}




Imagem *Gauss(Imagem *img, Imagem *img2){
    float filter[5][5] = {{1, 4, 6, 4, 1},
                          {4, 16, 24, 16, 4},
                          {6, 24, 36, 14, 6},
                          {4, 16, 24, 16, 4},
                          {1, 4, 6, 4, 1}};

    
    int aux_r, aux_g, aux_b;
    
    HeaderCopy(img, img2);
    
    AlocaMatriz(img2);
    

        for(i = 0; i < img->linha; i++){
            for(j = 0; j < img->coluna; j++){
                aux_r = 0, aux_g = 0, aux_b = 0;
                for(k = 0; k<5; k++){
                    for(l = 0; l<5; l++){
                    
                        if( i+k-2 < 0 || j+l-2 < 0 || i+k-2 >= img->linha || j+l-2 >= img->coluna){
                            continue; 
                        }
                   
                       aux_r = aux_r + ((img->pixel[i-2+k][j-2+l].r) * filter[k][l])/256;
                       aux_g = aux_g + ((img->pixel[i-2+k][j-2+l].g) * filter[k][l])/256;
                       aux_b = aux_b + ((img->pixel[i-2+k][j-2+l].b) * filter[k][l])/256;
                   
                    }
                }

                if(aux_r > 255){
                    aux_r = 255;
                }
                if(aux_r < 0){
                    aux_r = 0;
                }
                if(aux_g > 255){
                    aux_g = 255;
                }
                if(aux_g < 0){
                    aux_g = 0;
                }
                if(aux_b > 255){
                    aux_b = 255;
                }
                if(aux_b < 0){
                    aux_b = 0;
                } 
            
                img2->pixel[i][j].r = (unsigned short int) (aux_r);
                img2->pixel[i][j].g = (unsigned short int) (aux_g);
                img2->pixel[i][j].b = (unsigned short int) (aux_b);            
            }
        }
     
        
    

    
    return img2;

}




Imagem *Sobel(Imagem *img, Imagem *img2){
    float Sobel_X[3][3] = {{ -1, 0, 1},
                           {-2, 0, 2},
                           { -1, 0, 1}};

    float Sobel_Y[3][3] = {{-1, -2, -1},
                           {0, 0, 0},
                           {1, 2, 1}};                     

    
    int aux_X, aux_Y;
    
    HeaderCopy(img, img2);
    
    AlocaMatriz(img2);
    
    
        for(i = 0; i < img->linha; i++){
            for(j = 0; j < img->coluna; j++){
                aux_X = 0;
                aux_Y = 0;
                for(k = 0; k<3; k++){
                    for(l = 0; l<3; l++){
                    
                        if( i+k-1 == -1 || j+l-1 == -1 || i+k-1 >= img->linha || j+l-1 >= img->coluna){
                            continue; 
                        }
                   
                       aux_X = aux_X + ((img->pixel[i-1+k][j-1+l].r) * Sobel_X[k][l]);
                       aux_Y = aux_Y + ((img->pixel[i-1+k][j-1+l].r) * Sobel_Y[k][l]);
                       
                   
                    }
                }

                if(sqrt((aux_X*aux_X) + (aux_Y*aux_Y)) > VMax){
                    img2->pixel[i][j].r = VMax;
                    img2->pixel[i][j].g = VMax;
                    img2->pixel[i][j].b = VMax;    
                }
                else{
                    img2->pixel[i][j].r = (sqrt((aux_X*aux_X) + (aux_Y*aux_Y)));
                    img2->pixel[i][j].g = (sqrt((aux_X*aux_X) + (aux_Y*aux_Y)));
                    img2->pixel[i][j].b = (sqrt((aux_X*aux_X) + (aux_Y*aux_Y)));    
                }           
            }
        }

        
    

    
    return img2;

}




Imagem *GirarPraEsquerda(Imagem *img1, Imagem *img2){

  //alt e larg recebem os valores da imagem
  int alt = img1->linha, larg = img1->coluna;

  //a altura da img1 se transforma na largura da img2, e a largura se transforma em altura
  HeaderInvert(img1, img2);

  AlocaMatriz(img2);

  for (j = 0; j < alt; j++){
    for (i = 0; i < larg; i++){

      //Acessa o pixel [i][j] de cada matriz
      Pixel *pix1 = PixelDaImagem(img1, i, j);
      Pixel *pix2 = PixelDaImagem(img2, j, larg - i - 1);

      //Invertendo a matriz de fato
      pix2->r = pix1->r;
      pix2->g = pix1->g;
      pix2->b = pix1->b;
    }
  }
  
  return img2;
}




Imagem *GirarPraDireita(Imagem *img1, Imagem *img2){

  //alt e larg recebem os valores da imagem
  int alt = img1->linha, larg = img1->coluna;

  //a altura da img1 se transforma na largura da img2, e a largura se transforma em altura
  HeaderInvert(img1, img2);

  AlocaMatriz(img2);

  for (j = 0; j < alt; j++){
    for (i = 0; i < larg; i++){

      //Acessa o pixel [i][j] de cada matriz
      Pixel *pix1 = PixelDaImagem(img1, i, j);
      Pixel *pix2 = PixelDaImagem(img2, alt - j - 1, i);

      //Invertendo a matriz de fato
      pix2->r = pix1->r;
      pix2->g = pix1->g;
      pix2->b = pix1->b;
    }
  }
  
  return img2;
}




Imagem *GirarCentoEOitenta(Imagem *img1, Imagem *img2){

  //alt e larg recebem os valores da imagem
  int alt = img1->linha, larg = img1->coluna;

  //Cria a img2 com o mesmo tamanho da img1
  HeaderCopy(img1, img2);

  AlocaMatriz(img2);

  for (j = 0; j < alt; j++){
    for (i = 0; i < larg; i++){

      //Acessa o pixel [i][j] de cada matriz
      Pixel *pix1 = PixelDaImagem(img1, i, j);
      Pixel *pix2 = PixelDaImagem(img2, larg - i - 1, alt - j - 1);

      //Invertendo a matriz de fato
      pix2->r = pix1->r;
      pix2->g = pix1->g;
      pix2->b = pix1->b;
    }
  }
  
  return img2;
}




Imagem *EspelharHorizontal(Imagem *img1, Imagem *img2){

  //alt e larg recebem os valores da imagem
  int alt = img1->linha, larg = img1->coluna;

  //Cria a img2 com o mesmo tamanho da img1
  HeaderCopy(img1, img2);

  AlocaMatriz(img2);

  for (j = 0; j < alt; j++){
    for (i = 0; i < larg; i++){

      //Acessa o pixel [i][j] de cada matriz
      Pixel *pix1 = PixelDaImagem(img1, i, j);
      Pixel *pix2 = PixelDaImagem(img2, larg - i - 1, j);

      //Invertendo a matriz de fato
      pix2->r = pix1->r;
      pix2->g = pix1->g;
      pix2->b = pix1->b;
    }
  }
  
  return img2;
}




Imagem *EspelharVertical(Imagem *img1, Imagem *img2){

  //alt e larg recebem os valores da imagem
  int alt = img1->linha, larg = img1->coluna;

  //Cria a img2 com o mesmo tamanho da img1
  HeaderCopy(img1, img2);

  AlocaMatriz(img2);

  for (j = 0; j < alt; j++){
    for (i = 0; i < larg; i++){

      //Acessa o pixel [i][j] de cada matriz
      Pixel *pix1 = PixelDaImagem(img1, i, j);
      Pixel *pix2 = PixelDaImagem(img2, i, alt - j - 1);

      //Invertendo a matriz de fato
      pix2->r = pix1->r;
      pix2->g = pix1->g;
      pix2->b = pix1->b;
    }
  }
  
  return img2;
}