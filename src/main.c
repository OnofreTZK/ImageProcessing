#include "util.h"


//Função para o usuário nomear o arquivo para cada operação.
const char *getFilename(char *buffer, size_t bf_size) {
    printf("\nInsira o nome do arquivo acrescentando '.ppm':\n\tEx: 'nome_arquivo.ppm'\n\n");

    char *ch = fgets(buffer, bf_size, stdin);

    for(int i = 0; i < bf_size; i++) {
        if( *(buffer+i) != '\0' && *(ch+i) == '\n') {
            *(buffer+i) = '\0'; //Substituição do '\n' pelo '\0'
        }
    }
    return buffer;
}





int main(int argc, char const *argv[]){
  
 if(argc < 2){
   printf("Nenhuma imagem está sendo utilidada no programa, execute-o passando como parâmetro\n");
   printf("\tEx: ./<nome executavel> <nome_arquivo.ppm>\n");
}
 else{

    char cmd[10]; //comando do usuario.
    int control = 1; //controle do menu.


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
        else if(strcmp(cmd, blu) == 0){
            LerImagem(argv[1], &entrada);
            Blur(&entrada);
            Blur(&entrada);
            Blur(&entrada);
            CriarImagem(getFilename(fname, FILENAME_MAX), &entrada);
        }
        else if(strcmp(cmd, sha) == 0){
            LerImagem(argv[1], &entrada);
            Blur(&entrada);
            Sharpening(&entrada);
            CriarImagem(getFilename(fname, FILENAME_MAX), &entrada);
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
