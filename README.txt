Introdução às Técnicas de Programação - 2019.1
Professor: Gustavo Girão
Alunos: Tiago Onofre e Vitoria Deon

NOTA: Do lado de cada funcionalidade está o nome de quem implementou.

* Todas as funcionalidades básicas foram atendidas:
- Ler e criar imagens (Tiago)
- Menu de comandos (Tiago e Vitoria)
- Escala de cinza com recursão (Tiago) 
- Arquivos diferentes para cada processo (Tiago) 
- Rotacionar (Vitoria) 
- Ampliar (Vitoria)
- Reduzir (Vitoria)
- Filtros (Tiago)
    * Os filtros de Blurring e Gauss possuem recursão
- Detecção de bordas (Tiago)
- Makefile (Tiago)
- Documentação (Tiago e Vitoria)

* Extras implementados:
- Espelhamento da imagem na horizontal (Vitoria)
- Espelhamento da imagem na vertical (Vitoria)
- Filtro Gaussiano 5x5 em 256 partes (Tiago)
- Detecção de bordas usando o operador de Sobel (Tiago)

* O que poderia ter sido feito diferente
 - Interface gráfica com o intuito de tornar mais "amigável" a um usuário comum.
 - A possibilidade de passar mais de uma imagem na execução e possibilitar a escolha de qual imagem usar
 no processo desejado.
 - Utilizar uma imagem que ja foi transformada pelo programa em outro processo.
 - Permitir o usuário escolher o valor do zoom nas funções de reduzir e ampliar(parâmetriza-las).
 - Permitir o usuário escolher quantas vezes aplicar determinado filtro.
 - Recursividades mais complexas.
 - Implementar um verificador caso a imagem gerada fosse nula.
 - Implementação de extras mais complexos(Transformada de Hough, detecção de objetos e compressão de imagens).

* Compilação e execução
Não foram usadas bibliotecas externas, apenas a biblioteca matemática nativa(-lm)

Estando na pasta raiz do projeto, digite no terminal:

$ make all

Deve aparecer as seguintes mensagens:

gcc ./src/*.c -Wall -lm -I ./include -o ./bin/proj
proj -> ./bin/proj
Compilado com sucesso! Para executar digite ./proj imagem.ppm

após a finalizar a execução digite:

$ make clean

a seguinte mensagem deve aparecer:

Binários excluidos com sucesso! 




