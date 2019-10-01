# Makefile do projeto de processamento de imagem - ITP 2019.1   

# pastas do projeto
SRCDIR = ./src
INCDIR = ./include
BINDIR = ./bin
OBJDIR = ./obj

#  compilador e flags
CC = gcc
CFLAGS = -Wall -lm -g -ggdb -I$(INCDIR)
RM = -rm

# nome do projeto (executavel)
PROJ_NAME = proj

# Make magic
HEADERS := $(wildcard $(INCDIR)/*)
SOURCES := $(wildcard $(SRCDIR)/*.c)
OBJECTS := $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: project

project: $(OBJECTS) $(HEADERS) | $(BINDIR)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(BINDIR)/$(PROJ_NAME)
	@ln -sfv $(BINDIR)/$(PROJ_NAME) $(PROJ_NAME)
	@echo "Compilado com sucesso! Para executar digite ./$(PROJ_NAME) imagem.ppm"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

# CLEAN PHONY TARGETS
.PRONY: clean clean_proj

clean: clean_proj

clean_proj:
	@echo "Removendo OBJDIR..."
	@$(RM) -r $(OBJDIR)
	@echo "Removendo BINDIR..."
	@$(RM) -r $(BINDIR)
	@echo "Removendo symlink..."
	@$(RM) -f $(PROJ_NAME)
	@echo "Binários excluidos com sucesso!"





