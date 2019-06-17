# Makefile do projeto de processamento de imagem - ITP 2019.1   

# pastas do projeto
SRCDIR = ./src
INCDIR = ./include
BINDIR = ./bin

#  compilador e flags
CC = gcc
CFLAGS = -Wall -lm

# nome do projeto (executavel)
PROJ_NAME = proj

all: proj

proj: bin_folder
	$(CC) $(SRCDIR)/*.c $(CFLAGS) -I $(INCDIR) -o $(BINDIR)/$(PROJ_NAME)
	@ln -sfv $(BINDIR)/$(PROJ_NAME) $(PROJ_NAME) # cria um link simbólico
	@echo "Compilado com sucesso! Para executar digite ./$(PROJ_NAME) imagem.ppm"

bin_folder:
	@mkdir -p $(BINDIR)

clean:
	@rm -f $(PROJ_NAME)
	@rm -rf $(BINDIR)
	@echo "Binários excluidos com sucesso!"





