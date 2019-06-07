#include "imagem.h"


int i, j; //Declarei globalmente pois sera bastante usado na leitura e escrita das matrizes.



void AlocaMatriz(Imagem *img){

  img->pixel = (Pixel**) malloc(img->linha*sizeof(Pixel*));
  
  for(int i = 0;i<img->linha;i++){
    img->pixel[i] = (Pixel*) malloc(img->coluna*sizeof(Pixel));
  }
}



//Ler os dados do arquivo.ppm e armazena-los em uma struct(onde iremos usar os dados para os processos de manipulação).
void LerImagem(const char *nome_arquivo, Imagem *img){
  
  char Head1[3] = "P3";
  char Head2[2] = "P6";

  FILE *imagem_entrada = fopen(nome_arquivo, "r");

  
  if(imagem_entrada == NULL){
  	printf("Não foi possivel abrir o arquivo! Tente novamente\n\n");
    exit(1);
  }
    else{
      fgets(img->ID, 3, imagem_entrada);
      
        if(strcmp(img->ID, Head1) != 0){
          printf("\nFormato de imagem não comportado, por favor utilive um arquivo '.ppm'\n");
          exit(1);
        }
         else{
            fscanf(imagem_entrada, "%d %d", &img->linha, &img->coluna);
            fscanf(imagem_entrada, "%d", &img->max_value);
      
            AlocaMatriz(img);//Alocando espaço necessário para os pixels.

            for(i = 0;i<img->linha;i++){
              for(j = 0;j<img->coluna;j++){
                fscanf(imagem_entrada, "%hd", &img->pixel[i][j].r);
                fscanf(imagem_entrada, "%hd", &img->pixel[i][j].g);
                fscanf(imagem_entrada, "%hd", &img->pixel[i][j].b);
              }
            }
          }
        }
    
    fclose(imagem_entrada);
}




void CriarImagem(const char *nome_arquivo, Imagem *img){
  
  
  FILE *imagem_saida = fopen(nome_arquivo, "w");

  
  if(imagem_saida == NULL){
    printf("Não foi possivel abrir o arquivo! Tente novamente\n\n");
    exit(1);
  }
    else{
      fprintf(imagem_saida, "%s\n", img->ID);
      fprintf(imagem_saida, "%d %d\n", img->linha, img->coluna);
      fprintf(imagem_saida, "%d\n", img->max_value);

       

       for(i = 0;i<img->linha;i++){
        for(j = 0;j<img->coluna;j++){
          fprintf(imagem_saida, "%hd\n", img->pixel[i][j].r);
          fprintf(imagem_saida, "%hd\n", img->pixel[i][j].g);
          fprintf(imagem_saida, "%hd\n", img->pixel[i][j].b);
        }
       }
    }

    printf("\n\t Imagem gerada com sucesso!\n");

    fclose(imagem_saida);
}





//Está função só está aqui para testes iniciais.
void printaTeste(Imagem *img){
	printf("Teste de leitura:\n");
	printf("\t\t ID: %s\n", img->ID);
	printf("\t\t Linhas: %d\n", img->linha);
	printf("\t\t Colunas: %d\n", img->coluna);
	printf("\t\t Valor Máximo: %d\n", img->max_value);
   

   for(i = 0;i<img->linha;i++){
        for(j = 0;j<img->coluna;j++){
          printf("%hd\n", img->pixel[i][j].r);
          printf("%hd\n", img->pixel[i][j].g);
          printf("%hd\n", img->pixel[i][j].b); 
        }
   }

}
