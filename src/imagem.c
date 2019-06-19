#include "imagem.h"


int i, j; //Declarei globalmente pois sera bastante usado na leitura e escrita das matrizes.



void AlocaMatriz(Imagem *img){

  img->pixel = (Pixel**) malloc(img->linha*sizeof(Pixel*));
  
  for(int i = 0; i < img->linha; i++){
    img->pixel[i] = (Pixel*) malloc(img->coluna*sizeof(Pixel));
  }
}




void LiberaMemoria(Imagem *img){
  
  for(i = 0;i < img->linha; i++){
    free(img->pixel[i]);
  }

  free(img->pixel);
}



//Ler os dados do arquivo.ppm e armazena-los em uma struct(onde iremos usar os dados para os processos de manipulação).
void LerImagem(const char *nome_arquivo, Imagem *img){
  
  char Head1[3] = "P3";

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
            fscanf(imagem_entrada, "%d %d", &img->coluna, &img->linha);
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




void HeaderCopy(Imagem *img, Imagem *img2){

    strcpy(img2->ID, img->ID);
    img2->linha = img->linha;
    img2->coluna = img->coluna;
    img2->max_value = img->max_value;
}




void HeaderInvert(Imagem *img, Imagem *img2){

    strcpy(img2->ID, img->ID);
    img2->linha = img->coluna;
    img2->coluna = img->linha;
    img2->max_value = img->max_value;
}




void HeaderEnlarge(Imagem *img, Imagem *img2, int n) {

  strcpy(img2->ID, img->ID);
  img2->linha = img->linha*n;
  img2->coluna = img->coluna*n;
  img2->max_value = img->max_value;
}




void HeaderReduce(Imagem *img, Imagem *img2) {

  strcpy(img2->ID, img->ID);
  img2->linha = img->linha/2;
  img2->coluna = img->coluna/2;
  img2->max_value = img->max_value;
}




//Função para o usuário nomear o arquivo para cada operação.
const char *getFilename(char *buffer, size_t bf_size) {
    printf("\nInsira o nome do arquivo:\n\t`->Não é necessário colocar '.ppm' o programa faz isso automaticamente.\n\n");
  
      char *ch = fgets(buffer, bf_size, stdin);

      for(i = 0; i < bf_size; i++) {
          if( *(buffer+i) != '\0' && *(ch+i) == '\n') {
              *(buffer+i) = '\0'; //Substituição do '\n' pelo '\0'
          }
      }
      
      char valid[5] = ".ppm";

      strcat(buffer, valid);

      return buffer;
    
}




void CriarImagem(const char *nome_arquivo, Imagem *img){
  
  
  FILE *imagem_saida = fopen(nome_arquivo, "w");

  
  if(imagem_saida == NULL){
    printf("Não foi possivel abrir o arquivo! Tente novamente\n\n");
    exit(1);
  }
    else{
      fprintf(imagem_saida, "%s\n", img->ID);
      fprintf(imagem_saida, "%d %d\n", img->coluna, img->linha);
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