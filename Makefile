# Alvos principais:
#   make livro     - compila o PDF do livro (latexmk + biber)
#   make exemplos  - compila todos os exemplos em C em build/exemplos
#   make testes    - testa os exemplos em C e em Python
#   make limpar    - remove arquivos gerados
LIVRO    = livro_algoritmos_e_estruturas_de_dados
CC      ?= gcc
CFLAGS  ?= -std=c17 -Wall -Wextra -Wpedantic
FONTES_C = $(shell find Code/C -name '*.c')

.PHONY: livro exemplos testes testes-c testes-python limpar

livro:
	latexmk -pdf -interaction=nonstopmode -halt-on-error $(LIVRO).tex

exemplos:
	@mkdir -p build/exemplos
	@for f in $(FONTES_C); do \
		echo "$(CC) $$f"; \
		$(CC) $(CFLAGS) $$f -o build/exemplos/$$(basename $$f .c) || exit 1; \
	done

testes: testes-c testes-python

testes-c:
	tests/c/testar_exemplos.sh

testes-python:
	python3 -m pytest -q

limpar:
	latexmk -C $(LIVRO).tex || true
	rm -rf build .pytest_cache
