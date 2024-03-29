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





    Imagem *ImagemCinza(Imagem *img, int count){



    	for(i = 0;i<img->linha;i++){
    		for(j = 0;j<img->coluna;j++){
    			img->pixel[i][j].r = MediaPixel(img->pixel, i, j);
    			img->pixel[i][j].g = MediaPixel(img->pixel, i, j);
    			img->pixel[i][j].b = MediaPixel(img->pixel, i, j);
    		}
    	}  



        //Uma recursao simples com o intuito de eliminar qualquer vestigio de cor.
    	if(count > 1){
    		img = ImagemCinza(img, count - 1);
    	}

    	return img;

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
    					//Condição para ignorar os elementos do kernel que ultrapassam as bordas
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

        LiberaMemoria(img);

    	return img2;
    }




    Imagem *Blur(Imagem *img, Imagem *img2, int count){
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

        LiberaMemoria(img); // Liberando sempre a imagem 1
        
        //Recursão simples para otimizar a borragem.
    	if(count > 1){
    		img2 = Blur(img2, img, count - 1);
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




    Imagem *Gauss(Imagem *img, Imagem *img2, int count){
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

        LiberaMemoria(img);

        //Recursão simples para otimizar o borrão
        if(count > 1){
            img2 = Gauss(img2, img, count - 1);
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

    	/* O Operador de Sobel consiste em aplicar dois filtros de convolução(Horizontal e vertical) e aplicar no
    	pixel central uma formula matematica explicada na documentação */                   


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




    Imagem *GirarPraEsquerda(Imagem *img1, Imagem *img2) {

      //alt e larg recebem os valores da imagem
    	int alt = img1->linha, larg = img1->coluna;

      //a altura da img1 se transforma na largura da img2, e a largura se transforma em altura
    	HeaderInvert(img1, img2);

    	AlocaMatriz(img2);

      //preenche coluna por coluna
    	for (j = 0; j < alt; j++) {
    		for (i = 0; i < larg; i++) {
    			img2->pixel[i][j] = img1->pixel[j][larg - i - 1];
    		}
    	}

    	return img2;
    }




    Imagem *GirarPraDireita(Imagem *img1, Imagem *img2) {

        //alt e larg recebem os valores da imagem
    	int alt = img1->linha, larg = img1->coluna;

        //a altura da img1 se transforma na largura da img2, e a largura se transforma em altura
    	HeaderInvert(img1, img2);

    	AlocaMatriz(img2);

        //preenche coluna por coluna
    	for (j = 0; j < alt; j++) {
    		for (i = 0; i < larg; i++) {

              //alt - j - 1
    			img2->pixel[i][j] = img1->pixel[alt - j - 1][i];
    		}
    	}

    	return img2;
    }




    Imagem *GirarCentoEOitenta(Imagem *img1, Imagem *img2) {

        //Cria a img2 com o mesmo tamanho da img1
    	HeaderCopy(img1, img2);

    	AlocaMatriz(img2);

        //alt e larg recebem os valores da imagem
    	int alt = img1->linha, larg = img1->coluna;

    	for (i = 0; i < alt; i++) {
    		for (j = 0; j < larg; j++) {
                //Matriz 1 é percorrida ao contrário para 'virar' a imagem
    			img2->pixel[i][j].r = img1->pixel[alt-i-1][larg-j-1].r;
    			img2->pixel[i][j].g = img1->pixel[alt-i-1][larg-j-1].g;
    			img2->pixel[i][j].b = img1->pixel[alt-i-1][larg-j-1].b;
    		}
    	}

    	return img2;
    }




    Imagem *EspelharHorizontal(Imagem *img1, Imagem *img2) {

      //alt e larg recebem os valores da imagem
    	int alt = img1->linha, larg = img1->coluna;

      //Cria a img2 com o mesmo tamanho da img1
    	HeaderCopy(img1, img2);

    	AlocaMatriz(img2);

    	for (i = 0; i < alt; i++) {
    		for (j = 0; j < larg; j++) {

    			img2->pixel[alt - i - 1][j].r = img1->pixel[i][j].r;
    			img2->pixel[alt - i - 1][j].g = img1->pixel[i][j].g;
    			img2->pixel[alt - i - 1][j].b = img1->pixel[i][j].b;
    		}
    	}

    	return img2;
    }




    Imagem *EspelharVertical(Imagem *img1, Imagem *img2) {

      //alt e larg recebem os valores da imagem
    	int alt = img1->linha, larg = img1->coluna;

      //Cria a img2 com o mesmo tamanho da img1
    	HeaderCopy(img1, img2);

    	AlocaMatriz(img2);

    	for (i = 0; i < alt; i++) {
    		for (j = 0; j < larg; j++) {

    			img2->pixel[i][larg - j - 1].r = img1->pixel[i][j].r;
    			img2->pixel[i][larg - j - 1].g = img1->pixel[i][j].g;
    			img2->pixel[i][larg - j - 1].b = img1->pixel[i][j].b;
    		}
    	}

    	return img2;
    }

    /* As funções de ampliar e reduzir consistem em fazer a media dos pixels que serão representados em um só,
    esses valores podem variar de acordo com o zoom(neste projeto, infelizmente, não implementamos uma função para
    pegar o valor do zoom com o usuário*/


    Imagem *AmpliarImagem(Imagem *img1, Imagem *img2, int n) {

    	HeaderEnlarge(img1, img2, n);

    	AlocaMatriz(img2);

    	int altura1 = img1->linha, largura1 = img1->coluna;
    	int altura2 = img2->linha, largura2 = img2->coluna;

    	for (i = 0, k = 0; i < altura1 && k < altura2; k++) {

    		if (k % n == 0 && k != 0) {
    			i++;
    		}

    		for (j = 0, l = 0; j < largura1 && l < largura2; l++) {

    			if (l % n == 0 && l != 0) {
    				j++;
    			}

    			img2->pixel[k][l] = img1->pixel[i][j];
    		}
    	}

    	return img2;
    }




    Imagem *ReduzirImagem(Imagem *img1, Imagem *img2) {

    	HeaderReduce(img1, img2);

    	AlocaMatriz(img2);

    	int altura1 = img1->linha, largura1 = img1->coluna;
    	int altura2 = img2->linha, largura2 = img2->coluna;

    	for (i = 0, k = 1; i < altura2 && k < altura1; i++, k += 2) {
    		for (j = 0, l = 1; j < largura2 && l < largura1; j++, l += 2) {

    			img2->pixel[i][j].r = (img1->pixel[k - 1][l - 1].r + img1->pixel[k - 1][l].r + img1->pixel[k][l - 1].r + img1->pixel[k][l].r) / 4;

    			img2->pixel[i][j].g = (img1->pixel[k - 1][l - 1].g + img1->pixel[k - 1][l].g + img1->pixel[k][l - 1].g + img1->pixel[k][l].g) / 4;

    			img2->pixel[i][j].b = (img1->pixel[k - 1][l - 1].b + img1->pixel[k - 1][l].b + img1->pixel[k][l - 1].b + img1->pixel[k][l].b) / 4;

    		}
    	}

    	return img2;
    }