#!/bin/bash

rm -f *.aux *.mtc* *.out *.idx *.bcf *.log *~ *.ptc *.toc *.run.xml *.maf *.blg

pdflatex livro_algoritmos_e_estruturas_de_dados -interaction=nonstopmode

biber livro_algoritmos_e_estruturas_de_dados

pdflatex livro_algoritmos_e_estruturas_de_dados -interaction=nonstopmode

pdflatex livro_algoritmos_e_estruturas_de_dados -interaction=nonstopmode

rm -f *.aux *.mtc* *.out *.idx *.bcf *.log *~ *.ptc *.toc *.run.xml *.maf *.blg *.bbl
