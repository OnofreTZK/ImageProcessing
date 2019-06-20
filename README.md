# Projeto de processamento de imagem - ITP 2019.1

## Desenvolvido por:

* [Tiago Onofre Araujo](https://github.com/OnofreTZK)
* [Vitoria Deon](https://github.com/vickydeon)

### Funcionalidades obrigatórias
   Funcionalidade | Status
   ------------ | -------------
   Ler e criar Imagem | Completo
   Menu de Comandos | Completo
   Escala de cinza | Completo
   Arquivos diferentes para cada processo | Completo
   Binarização | Completo
   Rotacionar  | Completo 
   Ampliar | Completo
   Reduzir | Completo
   Filtros | Completo
   Detecção de bordas | Completo


### Extras implementados

    1. Espelhamento da imagem na horizontal
    1. Espelhamento da imagem na vertical
    1. Filtro Gaussiano 5x5 em 256 partes
    1. Detecção de bordas usando o operador de Sobel

### O que poderia ter sido feito diferente

    * A execução do programa com mais de uma imagem passada como parâmetro
    * Permitir o usuário escolher qual das imagens quer processar
    * Utilizar uma imagem transformada em outro processo sem a necessidade de executar o programa novamente
    * Permitir o usuário escolher o zoom nas funções de reduzir e ampliar
    * Permitir o usuário escolher quantas vezes aplicar cada filtro
    * Implementação de compressão de imagem, transformada de Hough e detecção de objetos
    * Recursividades mais complexas
    * Interface gráfica
    * Verificar se a imagem foi nula

### Compilação
##### Para baixar o código na sua maquina:
```bash
$ git clone https://github.com/OnofreTZK/ITP_photoshop.git
```   
##### Após baixar o repositório, vá até a pasta raiz e:
```bash
# Digite 'make all' para compilar
$ make all
# As seguintes mensagens devem aparecer:

gcc ./src/*.c -Wall -lm -I ./include -o ./bin/proj
proj -> ./bin/proj
Compilado com sucesso! Para executar digite ./proj imagem.ppm
      
# Quando finalizar a execução digite 'make clean' para limpar os arquivo binários
$ make clean
# A seguinte mensagem deve aparecer:
Binários excluidos com sucesso!
```
      
      
