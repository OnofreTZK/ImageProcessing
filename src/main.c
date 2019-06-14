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
    Imagem Output4;
    Imagem Output5;
    Imagem Output6;
    Imagem Output7;
    Imagem Output8;
    Imagem Output9;



    printf("#### PHOTOSHOP20 ####\n\n");



    do{
        printf("\n");
        printf("qual operação deseja fazer na imagem?\n");
        printf("$'cin'\t->\tConverte para escala cinza\n");
        printf("$'thr'\t->\tBinarização da imagem usando thresholding\n");
        printf("$'brd'\t->\tDetectar bordas\n");
        printf("$'sbl'\t->\tDetectar bordas com o operador de sobel\n");
        printf("$'blu'\t->\tExecuta blurring\n");
        printf("$'gss'\t->\tExecuta blurring com filtro gaussiano\n");
        printf("$'sha'\t->\tExecuta sharpening\n");
        printf("$'rot'\t->\tRotaciona a imagem\n");
        printf("$'amp'\t->\tAmpliar a imagem\n");
        printf("$'red'\t->\tReduzir a imagem\n");
        printf("$'esp'\t->\tEspelhar a imagem\n");
        printf("$'exi' para sair\n");
        printf("\n");

        scanf("%s", cmd); 
        getchar();

        
        char fname[FILENAME_MAX];//Nome do arquivo que sera processado na func getFilename(). 
        

        if(strcmp(cmd, cin) == 0){
            LerImagem(argv[1], &entrada);
            ImagemCinza(&entrada);
            CriarImagem(getFilename(fname, FILENAME_MAX), &entrada);
            LiberaMemoria(&entrada);
        }
        else if(strcmp(cmd, thr) == 0){
            LerImagem(argv[1], &entrada);
            ImagemCinza(&entrada);
            Segmentation(&entrada);
            CriarImagem(getFilename(fname, FILENAME_MAX), &entrada);
            LiberaMemoria(&entrada);
        }
        else if(strcmp(cmd, brd) == 0){
            LerImagem(argv[1], &entrada);
            ImagemCinza(&entrada);
            Segmentation(&entrada);
            Bordas(&entrada, &Output);
            LiberaMemoria(&entrada);
            CriarImagem(getFilename(fname, FILENAME_MAX), &Output);
            LiberaMemoria(&Output);     
        }
        else if(strcmp(cmd, sbl) == 0){
            LerImagem(argv[1], &entrada);
            ImagemCinza(&entrada);
            Gauss(&entrada, &Output);
            LiberaMemoria(&entrada);
            Sobel(&Output, &Output2);
            LiberaMemoria(&Output);
            CriarImagem(getFilename(fname, FILENAME_MAX), &Output2);
            LiberaMemoria(&Output2);       
        }
        else if(strcmp(cmd, blu) == 0){
            LerImagem(argv[1], &entrada);
            Blur(&entrada, &Output);
            LiberaMemoria(&entrada);
            Blur(&Output, &Output2);
            LiberaMemoria(&Output);
            Blur(&Output2, &Output3);
            LiberaMemoria(&Output2);
            CriarImagem(getFilename(fname, FILENAME_MAX), &Output3);
            LiberaMemoria(&Output3);
        }
        else if(strcmp(cmd, gss) == 0){
            LerImagem(argv[1], &entrada);
            Gauss(&entrada, &Output);
            LiberaMemoria(&entrada);
            CriarImagem(getFilename(fname, FILENAME_MAX), &Output); 
            LiberaMemoria(&Output);  
        }
        else if(strcmp(cmd, sha) == 0){
            LerImagem(argv[1], &entrada);
            Blur(&entrada, &Output);
            LiberaMemoria(&entrada);
            Blur(&Output, &Output2);
            LiberaMemoria(&Output);
            Blur(&Output2, &Output3);
            LiberaMemoria(&Output2);
            Sharpening(&Output3, &Output4);
            LiberaMemoria(&Output3);
            Sharpening(&Output4, &Output5);
            LiberaMemoria(&Output4);
            CriarImagem(getFilename(fname, FILENAME_MAX), &Output5);
            LiberaMemoria(&Output5);
        }
        else if(strcmp(cmd, rot) == 0){
            LerImagem(argv[1], &entrada);
            
            printf("$'esq'\t->\tGirar 90º para a esquerda\n");
            printf("$'dir'\t->\tGirar 90º para a direita\n");
            printf("$'cto'\t->\tGirar 180º\n");
            printf("\n");

            scanf("%s", cmd);
            getchar();

            if(strcmp(cmd, esq) == 0){
                GirarEsquerda(&entrada);    
            }
            else if(strcmp(cmd, dir) == 0){
                GirarDireita(&entrada);
            }
            else if(strcmp(cmd, cto) == 0){
                GirarCentoEOitenta(&entrada);
            }

            CriarImagem(getFileName(fname, FILENAME_MAX), &Output6);
        }
        else if(strcmp(cmd, amp) == 0){
            LerImagem(argv[1], &entrada);
            AmpliarImagem(&entrada);
            CriarImagem(getFileName(fname, FILENAME_MAX), &Output7);
        }
        else if(strcmp(cmd, red) == 0){
            LerImagem(argv[1], &entrada);
            ReduzirImagem(&entrada);
            CriarImagem(getFileName(fname, FILENAME_MAX), &Output8);
        }
        else if(strcmp(cmd, esp) == 0){
            LerImagem(argv[1], &entrada);

            printf("$'hor'\t->\tEspelhar na horizontal\n");
            printf("$'ver'\t->\tEspelhar na vertical\n");
            printf("\n");

            scanf("%s", cmd);
            getchar();

            if(strcmp(cmd, hor) == 0){
                EspelharHorizontal(&entrada);   
            }
            else if(strcmp(cmd, ver) == 0){
                EspelharVertical(&entrada);
            }

            CriarImagem(getFileName(fname, FILENAME_MAX), &Output9);
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