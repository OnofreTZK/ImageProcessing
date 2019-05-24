#include "util.h"


int main(int argc, char const *argv[])
{
  
  char cmd[10];
  int control = 1;

  Imagem entrada; // variavel que irá armazenar a imagem.


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
          CriaImagem(&entrada);
    }
    else if(strcmp(cmd, thr) == 0){
     	LerImagem(argv[1], &entrada);
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
    	printf("\n\n~~Programa Encerrado~~\n\n");
    	control = 0;
    }
    else{
    	printf("\n\nComando inválido, tente novamente!\n\n");
    }

  }while(control == 1);

	




	return 0;  
}
