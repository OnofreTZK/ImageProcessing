#include "util.h"


int main(int argc, char const *argv[])
{
  
  char cmd[10]; //comando do usuario.
  int control = 1; //controle do menu.
  
  char fname[FILENAME_MAX]; 

  Imagem entrada; //variavel que irá armazenar a imagem.


  printf("#### PHOTOSHOP20 ####\n\n");
  


  do{
    
    printf("\n");
    printf("qual operação deseja fazer na imagem?\n");
    printf("$'cin'\t->\tConverte para escala cinza\n");
    printf("$'thr'\t->\tBinarização da imagem usando thresholding\n");
    printf("$'blu'\t->\tExecuta blurring\n");
    printf("$'sha'\t->\tExecuta sharpening\n");
    printf("$'rot'\t->\tRotaciona a imagem\n");
    printf("$'amp'\t->\tAmpliar a imagem\n");
    printf("$'red'\t->\tReduzir a imagem\n");
    printf("$'exi' para sair\n");
    printf("\n");

    scanf("%s", cmd); 
    getchar();

    

    if(strcmp(cmd, cin) == 0){
      LerImagem(argv[1], &entrada);
      ImagemCinza(&entrada);
      
      printf("\nInsira o nome do arquivo acrescentando '.ppm':\n\tEx: 'nome_arquivo.ppm'\n\n");
      
      char *ch = fgets(fname, FILENAME_MAX, stdin);

          if(ch){
   
            while (*ch != '\0' && *ch != '\n') {
              ch++;
            }
  
          }
          else if (*ch == '\n'){                  
            *ch = '\0';
          }
      
      

      CriarImagem(fname, &entrada);
    }
    else if(strcmp(cmd, thr) == 0){
     	LerImagem(argv[1], &entrada);
      ImagemCinza(&entrada);
      Segmentation(&entrada);
      
      printf("\nInsira o nome do arquivo acrescentando '.ppm':\n\tEx: 'nome_arquivo.ppm'\n\n");
      
      char *ch = fgets(fname, FILENAME_MAX, stdin);

          if(ch){
   
            while (*ch != '\0' && *ch != '\n') {
              ch++;
            }
  
          }
          else if (*ch == '\n'){                  
            *ch = '\0';
          }
      
      

      CriarImagem(fname, &entrada);
    }
    else if(strcmp(cmd, blu) == 0){
      LerImagem(argv[1], &entrada);
    }
    else if(strcmp(cmd, sha) == 0){
      LerImagem(argv[1], &entrada);
    }
    else if(strcmp(cmd, rot) == 0){
    	LerImagem(argv[1], &entrada);
    }
    else if(strcmp(cmd, amp) == 0){
    	LerImagem(argv[1], &entrada);
    }
    else if(strcmp(cmd, red) == 0){
    	LerImagem(argv[1], &entrada);
    }
    else if(strcmp(cmd, exi) == 0){
        printf("~~~~~~~~~~~~~~~~~~~~~~~\n");
    	printf("\nPrograma Encerrado\n\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~\n");
    	control = 0;
    }
    else{
    	printf("\n\nComando inválido, tente novamente!\n\n");
    }

  }while(control == 1);

	




	return 0;  
}
