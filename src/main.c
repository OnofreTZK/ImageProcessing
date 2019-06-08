#include "util.h"


int main(int argc, char const *argv[]){
  
 if(argc < 2){
   printf("Nenhuma imagem está sendo utilidada no programa, execute-o passando como parâmetro\n");
   printf("\tEx: ./<nome executavel> <nome_arquivo.ppm>\n");
}
 else{

    char cmd[10]; //comando do usuario.
    int control = 1; //controle do menu.


    Imagem entrada; //variavel que irá armazenar a imagem.
    Imagem Output;
    Imagem Output2;
    Imagem Output3;



    printf("#### PHOTOSHOP20 ####\n\n");



    do{
        printf("\n");
        printf("qual operação deseja fazer na imagem?\n");
        printf("$'cin'\t->\tConverte para escala cinza\n");
        printf("$'thr'\t->\tBinarização da imagem usando thresholding\n");
        printf("$'brd'\t->\tDetectar bordas\n");
        printf("$'blu'\t->\tExecuta blurring\n");
        printf("$'sha'\t->\tExecuta sharpening\n");
        printf("$'rot'\t->\tRotaciona a imagem\n");
        printf("$'amp'\t->\tAmpliar a imagem\n");
        printf("$'red'\t->\tReduzir a imagem\n");
        printf("$'exi' para sair\n");
        printf("\n");

        scanf("%s", cmd); 
        getchar();

        
        char fname[FILENAME_MAX];//Nome do arquivo que sera processado na func getFilename(). 
        

        if(strcmp(cmd, cin) == 0){
            LerImagem(argv[1], &entrada);
            ImagemCinza(&entrada);
            CriarImagem(getFilename(fname, FILENAME_MAX), &entrada);
        }
        else if(strcmp(cmd, thr) == 0){
            LerImagem(argv[1], &entrada);
            ImagemCinza(&entrada);
            Segmentation(&entrada);
            CriarImagem(getFilename(fname, FILENAME_MAX), &entrada);
        }
        else if(strcmp(cmd, brd) == 0){
            LerImagem(argv[1], &entrada);
            ImagemCinza(&entrada);
            Segmentation(&entrada);
            Bordas(&entrada, &Output);
            CriarImagem(getFilename(fname, FILENAME_MAX), &Output);     
        }
        else if(strcmp(cmd, blu) == 0){
            LerImagem(argv[1], &entrada);
            Blur(&entrada, &Output);
            CriarImagem(getFilename(fname, FILENAME_MAX), &Output);
        }
        else if(strcmp(cmd, sha) == 0){
            LerImagem(argv[1], &entrada);
            Blur(&entrada, &Output);
            Sharpening(&Output, &Output2);
            CriarImagem(getFilename(fname, FILENAME_MAX), &Output2);
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


  }
 

    return 0;  
}
