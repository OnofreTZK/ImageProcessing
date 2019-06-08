#include "processos.h"
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

            img2->pixel[i][j].r = aux_r;
            img2->pixel[i][j].g = aux_g;
            img2->pixel[i][j].b = aux_b;            
        }
    }

    return img2;
}





Imagem *Blur(Imagem *img, Imagem *img2){
    float filter[3][3] = {{ 0.0625, 0.125, 0.0625},
                          { 0.125, 0.25, 0.125},
                          { 0.0625, 0.125, 0.0625}};

    
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
            
            img2->pixel[i][j].r = aux_r;
            img2->pixel[i][j].g = aux_g;
            img2->pixel[i][j].b = aux_b;            
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
            
            img2->pixel[i][j].r = aux_r;
            img2->pixel[i][j].g = aux_g;
            img2->pixel[i][j].b = aux_b;            
        }
    }

    
    return img2;

}