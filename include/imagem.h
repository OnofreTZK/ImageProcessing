#ifndef imagem_h
#define imagem_h


#include "tipos.h"
#include <string.h>


//Função para ler a imagem e salvar os dados em uma struct.
void LerImagem(const char *nome_arquivo, Imagem *img);

//Função para testar se a leitura foi feita com sucesso, não será utilizada na versão final do projeto.
void printaTeste(Imagem *img);

//Função para alocar dinamicamente a matriz que irá receber os pixels.
void AlocaMatriz(Imagem *img);

//Função para gerar a imagem em outro arquivo a partir da struct.
void CriarImagem(const char *nome_arquivo, Imagem *img);

#endif  
