#include "util.h"

int main(int argc, char const *argv[]){

	if(argc < 2){
		printf("Nenhuma imagem está sendo utilizada no programa, execute-o passando como parâmetro\n");
		printf("\tEx: ./<nome executavel> <nome_arquivo.ppm>\n");
	}
	else{

	char cmd[10]; //comando do usuario.
	int control = 1; //controle do menu.


	Imagem entrada; //variavel que irá armazenar a imagem.
	Imagem Output;
	Imagem Output2;
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
		printf("$'rot'\t->\tRotacionar a imagem\n");
		printf("$'amp'\t->\tAmpliar a imagem\n");
		printf("$'red'\t->\tReduzir a imagem\n");
		printf("$'esp'\t->\tEspelhar a imagem\n");
		printf("$'exi' para sair\n");
		printf("\n");

		scanf("%s", cmd); 
		getchar();

		
		char fname[FILENAME_MAX];//Nome do arquivo que sera processado na func getFilename(). 
		
		// A Liberação de memória é feita sempre que uma variável(Imagem) não for mais necessária

		if(strcmp(cmd, cin) == 0){
			LerImagem(argv[1], &entrada);
			ImagemCinza(&entrada, 3);
			CriarImagem(getFilename(fname, FILENAME_MAX), &entrada);
			LiberaMemoria(&entrada);
		}
		else if(strcmp(cmd, thr) == 0){
			LerImagem(argv[1], &entrada);
			ImagemCinza(&entrada, 3);
			Segmentation(&entrada);
			CriarImagem(getFilename(fname, FILENAME_MAX), &entrada);
			LiberaMemoria(&entrada);
		}
		else if(strcmp(cmd, brd) == 0){
			LerImagem(argv[1], &entrada);
			ImagemCinza(&entrada, 3);
			Segmentation(&entrada);
			Bordas(&entrada, &Output);
			LiberaMemoria(&entrada);
			CriarImagem(getFilename(fname, FILENAME_MAX), &Output);
			LiberaMemoria(&Output);     
		}
		else if(strcmp(cmd, sbl) == 0){
			LerImagem(argv[1], &entrada);
			ImagemCinza(&entrada, 3);
			Gauss(&entrada, &Output);
			LiberaMemoria(&entrada);
			Sobel(&Output, &Output2, 2);
			LiberaMemoria(&Output);
			CriarImagem(getFilename(fname, FILENAME_MAX), &Output2);
			LiberaMemoria(&Output2);       
		}
		else if(strcmp(cmd, blu) == 0){
			LerImagem(argv[1], &entrada);
			Blur(&entrada, &Output, 3);
			LiberaMemoria(&entrada);
			CriarImagem(getFilename(fname, FILENAME_MAX), &Output);
			LiberaMemoria(&Output);
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
			Blur(&entrada, &Output, 3);
			LiberaMemoria(&entrada);
			Sharpening(&Output, &Output2, 3);
			LiberaMemoria(&Output);
			CriarImagem(getFilename(fname, FILENAME_MAX), &Output2);
			LiberaMemoria(&Output2); 
		}
		else if(strcmp(cmd, rot) == 0){
			LerImagem(argv[1], &entrada);
			
			printf("\n");
			printf("$'esq'\t->\tGirar 90º para a esquerda\n");
			printf("$'dir'\t->\tGirar 90º para a direita\n");
			printf("$'cto'\t->\tGirar 180º\n");
			printf("\n");

			scanf("%s", cmd);
			getchar();

			if(strcmp(cmd, esq) == 0){
				GirarPraEsquerda(&entrada, &Output6);    
			}
			else if(strcmp(cmd, dir) == 0){
				GirarPraDireita(&entrada, &Output6);
			}
			else if(strcmp(cmd, cto) == 0){
				GirarCentoEOitenta(&entrada, &Output6);
			}
            
            LiberaMemoria(&entrada);
			CriarImagem(getFilename(fname, FILENAME_MAX), &Output6);
			LiberaMemoria(&Output6);
		}
		else if(strcmp(cmd, amp) == 0){
			LerImagem(argv[1], &entrada);
			AmpliarImagem(&entrada, &Output7, 2);
			LiberaMemoria(&entrada);
			CriarImagem(getFilename(fname, FILENAME_MAX), &Output7);
			LiberaMemoria(&Output7);
		}
		else if(strcmp(cmd, red) == 0){
			LerImagem(argv[1], &entrada);
			ReduzirImagem(&entrada, &Output8);
			LiberaMemoria(&entrada);
			CriarImagem(getFilename(fname, FILENAME_MAX), &Output8);
			LiberaMemoria(&Output8);
		}
		else if(strcmp(cmd, esp) == 0){
			LerImagem(argv[1], &entrada);

			printf("$'hor'\t->\tEspelhar na horizontal\n");
			printf("$'ver'\t->\tEspelhar na vertical\n");
			printf("\n");

			scanf("%s", cmd);
			getchar();

			if(strcmp(cmd, hor) == 0){
				EspelharHorizontal(&entrada, &Output9);   
			}
			else if(strcmp(cmd, ver) == 0){
				EspelharVertical(&entrada, &Output9);
			}

            LiberaMemoria(&entrada);
			CriarImagem(getFilename(fname, FILENAME_MAX), &Output9);
			LiberaMemoria(&Output9);
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