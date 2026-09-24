# Plano de Atualização do Livro *Algoritmos e Estruturas de Dados*

Documento de trabalho gerado a partir da revisão de `livro_algoritmos_e_estruturas_de_dados.tex`, `bibliography.bib`, `Code/C`, `Code/Python`, notebooks e figuras (estado do commit `49aaee2`).

## Situação

| Fase | Estado |
|---|---|
| 0 — Infraestrutura | Concluída (`.gitignore`, `Makefile`, testes, CI) |
| 1 — Correções | Concluída (itens das tabelas 1.2, 1.3 e 1.4, exceto redesenho das figuras de terceiros) |
| 2 a 6 | Pendentes |

---

## 1. Diagnóstico do conteúdo atual

### 1.1 Situação por capítulo/seção

| Capítulo / Seção | Situação | Exemplos associados | Observação |
|---|---|---|---|
| Prefácio | Esboço (1 frase) | — | Epígrafe com texto provisório "Um bonita citação..." em todos os capítulos |
| Introdução / Análise de Algoritmos | Parcial | — | Só notação $O$; faltam $\Omega$, $\Theta$, melhor/pior/caso médio, recorrências |
| Programação (C) | Parcial | `prog001`–`prog013` | Faltam laços, funções, ponteiros, alocação dinâmica, arquivos |
| Vetores, *strings*, *structs* | Parcial | `rev001`–`rev003`, `Struct*.c` | Sem exercícios |
| Listas encadeadas | Parcial | `ListaEncadeada02/03.c` | Código com erro de memória (ver 1.3) |
| Pilhas | **Vazia** | — | Existe figura `FIFO.png` e conteúdo no notebook de ED |
| Filas | **Vazia** | — | Idem |
| Ordenação | Completa na forma, com erros | 5 programas em C | Sem análise de complexidade; exercícios repetidos 5 vezes |
| Árvores | Mínima (2 frases) | `ArvoreBinaria.c` | Legenda errada; sem percursos, remoção, balanceamento |
| Tabelas *Hash* | **Vazia** | — | Conteúdo existe em `Disciplina_Estrutura_de_Dados.ipynb` |
| Grafos | Mais desenvolvida | Python OO (`Code/Python/grafos`) | Erros conceituais (ver 1.2); sem código de BFS/DFS no texto |
| Aplicações | **Vazia** | — | Datasets em `csv_files/` e figuras De Bruijn sem uso |
| Apêndice | **Vazio** | — | Título grafado "Apêncice" |

### 1.2 Erros conceituais e de texto (prioridade alta)

| Local (`.tex`) | Problema | Correção proposta |
|---|---|---|
| l. 228 | "$O$ denota ... o pior caso" confunde limite assintótico com caso de análise | Separar *limite superior* ($O$) de *pior caso*; apresentar $O$, $\Omega$, $\Theta$ [1][2] |
| l. 251–252 | Definição de dominação assintótica omite a constante $c$ na frase seguinte | Reescrever: $f(n)=O(g(n)) \iff \exists\, c>0, n_0 : 0 \le f(n) \le c\,g(n),\ \forall n\ge n_0$ [1] |
| l. 211 | *Millennium Problems* apresentados como "matemático-computacionais"; um deles (Poincaré) já foi resolvido | Citar apenas P vs NP como problema computacional em aberto |
| l. 356 | "*warnning*" | "*warning*" |
| l. 360–363 | Executável com extensão `.sh` (sugere *script shell*) | Usar `gcc -Wall prog001.c -o prog001` |
| l. 406–424 | Tabela de tipos: `int` com 4 bytes e faixa de 16 bits; `long int` com 8 bytes e faixa de 32 bits; `double` como "precisão simples"; `char` sempre com sinal | Informar faixas mínimas do padrão e valores típicos (LP64); usar `<limits.h>`, `<stdint.h>` [3] |
| l. 428 | Especificador escrito "`\d`" | "`%d`" |
| l. 499–510 | Precedência cita "potência" e "div/mod", inexistentes em C | Tabela de precedência real de C (incluir relacionais, lógicos, atribuição) |
| l. 768 | Legenda da árvore: "lista duplamente encadeada" | "Árvore binária de busca" |
| l. 891 | Matriz da direita descrita como "grafo direcionado"; é a forma triangular do mesmo grafo não direcionado | Corrigir legenda; incluir matriz de um digrafo real |
| l. 949 | "*Deep-First Search*" | "*Depth-First Search*" |
| l. 955 | Figura de DFS descrita como "busca em largura" | "busca em profundidade" |
| l. 978–985 | Condição de caminho euleriano sem exigir conexidade; regra de grau par/ímpar aplicada a digrafo | Separar grafo não direcionado (grau) de digrafo (grau de entrada = saída) [1][6] |
| l. 999 | "NP ... cujas soluções **não** podem ser verificadas em tempo polinomial" (invertido) | NP = soluções **verificáveis** em tempo polinomial; citar Cook [4] e Karp [5] |
| Figuras de grafos | Imagens de terceiros (UNICAMP) | Redesenhar em TikZ/Graphviz para evitar problemas de licença |
| Todo o texto | Erros de digitação ("algortimo", "crecismento", "cadeira de caracteres", "próximonó", "dterminado", "oerientada" etc.) | Revisão ortográfica completa |

### 1.3 Erros nos exemplos de código (verificados com `gcc -Wall -Wextra` e `-fsanitize=address`)

| Arquivo | Problema | Efeito | Correção |
|---|---|---|---|
| Todos os `.c` | `void main()` | Fora do padrão C; aviso `-Wmain` | `int main(void)` com `return 0;` |
| `Ordenacao/SelectionSort.c` | Laço externo `i < TAMANHO-2` | **Resultado errado**: `{0,1,3,2}` permanece desordenado; 29 % de falhas em 100 mil vetores aleatórios | `i < TAMANHO-1`; remover variável `aux` não usada |
| `Listas/ListaEncadeada01/02/03.c` | `malloc(sizeof(no))` (tamanho do ponteiro) | **Estouro de *heap*** detectado pelo ASan | `malloc(sizeof *no)` + verificar `NULL` |
| `Listas/ListaEncadeada01.c` | `no->prox` não inicializado na lista vazia | Comportamento indefinido | Inicializar com `NULL` |
| Listas (todas) | Memória nunca liberada | Vazamento | Função `liberarLista()` |
| `ArvoreBinaria/ArvoreBinaria.c` | `getValor()` sem `return` no ramo `NULL`; `free(raiz)` libera só a raiz | UB; 36 blocos vazados | Remover `getValor`; `liberarArvore()` pós-ordem |
| `Basics/prog008.c` | `%d` para `sizeof` e `long`; `%.1f` para `long double` | UB | `%zu`, `%ld`, `%Lf` |
| `Revisao/rev002.c` | Percorre `TAMANHO` em vez de parar em `'\0'` | Funciona por acaso | Laço até `'\0'` ou `strlen` |
| `Ordenacao/MergeSort.c` | Protótipo `mergeSort(..., int meio)` difere da definição; `stdlib.h` duplicado | Legibilidade | Harmonizar |
| `Ordenacao/InsertionSort.c` | Comentário "método da seleção" | Confunde o leitor | Corrigir comentário |
| `Ordenacao/*.c` | Cronometragem inclui geração e impressão do vetor | Medição imprecisa | Medir só a ordenação |
| `Listas/Diretorios.c` | Não compila (erro de sintaxe) | — | Corrigir ou remover |
| `Code/Python/grafos/Grafo.py` l. 58 e 76 | `if (verticeOrigem or verticeDestino) is None` só detecta quando **ambos** faltam | Aresta criada com vértice `None` | `if verticeOrigem is None or verticeDestino is None` |
| `Code/Python/grafos.py` | Arquivo vazio que sombreia o pacote `grafos/` | Erro de importação | Remover |

### 1.4 Infraestrutura do repositório

| Item | Situação | Ação |
|---|---|---|
| `.gitignore` | Inexistente; versionados `__pycache__/`, `.idea/`, `.ipynb_checkpoints/` | Criar `.gitignore` e remover do índice |
| PDF compilado | Versionado na raiz | Publicar via *GitHub Releases* gerado pela CI |
| Compilação | `compilar.sh` manual | `Makefile` / `latexmk` + CI |
| Testes dos exemplos | Inexistentes | Testes automatizados (seção 4) |
| `bibliography.bib` | ~30 entradas sem uso (metodologia, engenharia de software, UML); `ziviani2007` como `@article` com título errado | Limpar e corrigir tipos/títulos |
| Pasta `temp/` | Notebook solto | Integrar ou remover |
| `README.md` | Instruções de Git com `master` e imagem de outro repositório | Atualizar |

---

## 2. Estrutura proposta (novo sumário) e exemplos por capítulo

Convenção: cada exemplo em C terá equivalente em Python (`Code/Python/capXX/`), com saída esperada documentada.

| Cap. | Título | Conteúdo a produzir/revisar | Exemplos (C / Python) | Origem |
|---|---|---|---|---|
| 1 | Prefácio | Público-alvo, pré-requisitos, como usar o repositório | — | Reescrever |
| 2 | Introdução e Análise de Algoritmos | Modelo RAM; contagem de operações; melhor/pior/médio caso; $O$, $\Omega$, $\Theta$ [1][2]; tabela de crescimento; noção de P, NP [4] | `busca_linear`, `busca_binaria`, `contagem_operacoes` (medição empírica vs. teórica) | Revisar + expandir |
| 3 | Fundamentos de Programação em C | Tipos (`<stdint.h>`), E/S, operadores, decisão (`if`, `switch`), **repetição** (`for`, `while`, `do-while`) | `prog001`–`prog013` corrigidos + `laco_for`, `laco_while`, `switch_menu`, `tabuada` | Revisar + expandir |
| 4 | Funções, Recursão e Ponteiros | Escopo, passagem por valor/referência, ponteiros, aritmética de ponteiros, `malloc`/`free`, recursão e pilha de chamadas | `fatorial`, `fibonacci` (recursivo × iterativo), `troca_ponteiros`, `vetor_dinamico`, `torre_hanoi` | **Novo** (parte existe no notebook de ED) |
| 5 | Estruturas Homogêneas e Heterogêneas | Vetores, matrizes, *strings*, `struct`, `typedef`, arquivos | `rev001`–`rev003`, `Struct*.c` corrigidos + `leitura_csv` (usando `csv_files/`) | Revisar |
| 6 | Tipos Abstratos de Dados e Listas | TAD com `.h`/`.c`; lista simples, dupla, circular; complexidade das operações | `lista.h/.c` (inserir início/fim, buscar, remover, liberar), `lista_dupla`, `lista_circular` | Revisar + corrigir |
| 7 | Pilhas e Filas | LIFO/FIFO com vetor e com lista; fila circular; aplicações (balanceamento de parênteses, notação pós-fixa, escalonamento) | `pilha_vetor`, `pilha_lista`, `fila_circular`, `fila_lista`, `parenteses`, `posfixa` | **Novo** (usar `FIFO.png`) |
| 8 | Ordenação | Bubble (com parada antecipada), Selection, Insertion, Merge, Quick [7] (escolha de pivô), Heap Sort, Counting Sort; estabilidade; limite $\Omega(n \log n)$ para comparação [1]; tabela comparativa | 5 programas corrigidos com função `ordenar(int*, size_t)` separada de `main`; `heap_sort`, `counting_sort`; `benchmark_ordenacao` (vetores crescente, aleatório, decrescente; comparações, trocas, tempo) | Revisar + expandir |
| 9 | Busca e Tabelas *Hash* | Busca sequencial e binária; funções de *hash*; colisões (encadeamento, endereçamento aberto); fator de carga | `busca_binaria`, `hash_encadeamento`, `hash_sondagem_linear`; Python: `dict` × implementação própria | **Novo** (base no notebook) |
| 10 | Árvores | Terminologia; árvore binária de busca (inserir, buscar, **remover**); percursos pré/in/pós-ordem e em nível; altura; AVL [8]; *heap* binário; exportação Graphviz [9] | `abb.h/.c` corrigida, `percursos`, `avl`, `heap_binario`, `arvore_dot` (gera `.dot`) | Revisar + expandir |
| 11 | Grafos | Definições corrigidas; representações (matriz × lista, custo de memória); BFS e DFS com código; ordenação topológica; Dijkstra [10]; árvore geradora mínima (Prim/Kruskal); caminhos de Euler (Hierholzer) e Hamilton (NP-completo [5]) | `grafo_matriz`, `grafo_lista`, `bfs`, `dfs`, `dijkstra`, `kruskal`; pacote Python `grafos` corrigido + testes | Revisar + expandir |
| 12 | Aplicações | Estudos de caso com os dados do repositório: ordenação/busca em `Apple.csv`; agregação com *hash* em `CarPrice.csv`; montagem de sequências com grafo de De Bruijn [11] (figuras já existentes); *blockchain* simplificada com *hash* (notebook) | `ranking_precos`, `agrupamento_hash`, `debruijn_montagem`, `mini_blockchain` | **Novo** |
| A | Apêndice | Instalação de GCC/Python/LaTeX; Git básico (conteúdo do `README`); uso de `valgrind` e `-fsanitize`; gabarito resumido | — | **Novo** |

Cada capítulo deverá conter: objetivos de aprendizagem, texto, exemplos, quadro-resumo de complexidade e lista de exercícios (graduados: fixação, implementação, desafio).

---

## 3. Padrões para os exemplos

| Aspecto | Padrão adotado |
|---|---|
| Padrão da linguagem C | C17 (ISO/IEC 9899:2018) [3]; compilar com `gcc -std=c17 -Wall -Wextra -Wpedantic` sem avisos |
| Assinatura | `int main(void)` e `return 0;` |
| Memória | Todo `malloc` com `sizeof *ptr`, checagem de `NULL` e `free` correspondente; zero erros em `-fsanitize=address,undefined` |
| Organização | Algoritmo em função própria, separado de `main`; TADs em `.h`/`.c` |
| Nomes | Identificadores em português, sem acentos, `snake_case` ou `camelCase` (escolher um e manter) |
| Entrada/saída | Semente fixa (`srand(42)`) nos exemplos do livro, para saída reprodutível; saída esperada em comentário no fim do arquivo |
| Python | Python ≥ 3.10, *type hints*, `if __name__ == "__main__":`, testes com `pytest` |
| Inclusão no LaTeX | `\lstinputlisting` com `label` e `caption` corretos; usar `firstline/lastline` para mostrar só a função relevante |
| Figuras | Produzidas pelo próprio autor (TikZ, Graphviz ou draw.io com fonte versionada) |

---

## 4. Infraestrutura e automação

| Tarefa | Descrição |
|---|---|
| `.gitignore` | Ignorar `*.aux`, `*.log`, `*.pdf` (exceto figuras), `__pycache__/`, `.idea/`, `.ipynb_checkpoints/`, executáveis |
| `Makefile` | Alvos `livro`, `exemplos`, `testes`, `limpar` |
| Testes em C | Script que compila cada `.c`, executa com entrada fixa e compara com saída esperada (`tests/esperado/*.txt`) |
| Testes em Python | `pytest` para o pacote `grafos` e demais módulos |
| CI (GitHub Actions) | *Job* 1: compilar e testar exemplos C (com ASan/UBSan); *Job* 2: `pytest`; *Job* 3: compilar o PDF com `latexmk` e anexá-lo como artefato/*release* |
| Verificação de texto | `chktex` para LaTeX e revisão ortográfica (ex.: `hunspell -d pt_BR`) |

---

## 5. Fases de execução

| Fase | Escopo | Entregáveis | Prioridade | Esforço estimado |
|---|---|---|---|---|
| 0 — Infraestrutura | `.gitignore`, limpeza de arquivos gerados, `Makefile`, CI mínima | Build reproduzível | Alta | 1 semana |
| 1 — Correções | Todos os itens das tabelas 1.2 e 1.3; revisão ortográfica; limpeza do `.bib` | Livro atual sem erros conceituais; exemplos sem avisos/UB | **Crítica** | 1–2 semanas |
| 2 — Lacunas estruturais | Caps. 3 (repetição) e 4 (funções, recursão, ponteiros) | Base necessária para listas e árvores | Alta | 2 semanas |
| 3 — Seções vazias | Pilhas, Filas, *Hash* | Caps. 7 e 9 completos | Alta | 2–3 semanas |
| 4 — Aprofundamento | Ordenação (análise, *heap*, *counting*), Árvores (remoção, percursos, AVL, *heap*), Grafos (código BFS/DFS, Dijkstra, MST) | Caps. 8, 10, 11 revisados | Média | 3–4 semanas |
| 5 — Aplicações e Apêndice | Estudos de caso com `csv_files/` e De Bruijn; apêndice | Caps. 12 e A | Média | 2 semanas |
| 6 — Acabamento | Prefácio, epígrafes, índice remissivo (`\printindex` já previsto), lista de exercícios, revisão final | Versão 1.0 publicada em *Release* | Média | 1 semana |

Ordem sugerida: 0 → 1 → 2 → 3 → 4 → 5 → 6 (cada fase em um *branch*/PR separado).

---

## 6. Critérios de aceite

| Critério | Verificação |
|---|---|
| Nenhuma seção vazia ou texto provisório | `grep` por "Um bonita citação", seções sem conteúdo |
| Todos os exemplos compilam sem avisos | CI com `-Wall -Wextra -Wpedantic -Werror` |
| Nenhum erro de memória | CI com `-fsanitize=address,undefined` |
| Saídas conferem com o texto | Testes de saída esperada |
| Todo exemplo citado no texto e vice-versa | Script que cruza `\lstinputlisting` com arquivos em `Code/` |
| Todas as referências citadas e usadas | `biber` sem avisos; nenhuma entrada órfã |
| PDF gerado automaticamente | Artefato da CI |

---

## Referências

[1] CORMEN, T. H.; LEISERSON, C. E.; RIVEST, R. L.; STEIN, C. *Introduction to Algorithms*. 4. ed. Cambridge: MIT Press, 2022.

[2] KNUTH, D. E. Big Omicron and big Omega and big Theta. *ACM SIGACT News*, v. 8, n. 2, p. 18–24, 1976. DOI: 10.1145/1008328.1008329.

[3] ISO/IEC. *ISO/IEC 9899:2018 — Information technology — Programming languages — C*. Genebra: ISO, 2018.

[4] COOK, S. A. The complexity of theorem-proving procedures. In: *Proceedings of the 3rd Annual ACM Symposium on Theory of Computing (STOC)*, p. 151–158, 1971. DOI: 10.1145/800157.805047.

[5] KARP, R. M. Reducibility among combinatorial problems. In: MILLER, R. E.; THATCHER, J. W. (ed.). *Complexity of Computer Computations*. Nova York: Plenum, 1972. p. 85–103. DOI: 10.1007/978-1-4684-2001-2_9.

[6] SEDGEWICK, R.; WAYNE, K. *Algorithms*. 4. ed. Boston: Addison-Wesley, 2011.

[7] HOARE, C. A. R. Quicksort. *The Computer Journal*, v. 5, n. 1, p. 10–16, 1962. DOI: 10.1093/comjnl/5.1.10.

[8] ADELSON-VELSKY, G. M.; LANDIS, E. M. An algorithm for the organization of information. *Soviet Mathematics Doklady*, v. 3, p. 1259–1263, 1962.

[9] ELLSON, J. et al. Graphviz and Dynagraph — static and dynamic graph drawing tools. In: JÜNGER, M.; MUTZEL, P. (ed.). *Graph Drawing Software*. Berlim: Springer, 2004. p. 127–148.

[10] DIJKSTRA, E. W. A note on two problems in connexion with graphs. *Numerische Mathematik*, v. 1, p. 269–271, 1959. DOI: 10.1007/BF01386390.

[11] PEVZNER, P. A.; TANG, H.; WATERMAN, M. S. An Eulerian path approach to DNA fragment assembly. *Proceedings of the National Academy of Sciences*, v. 98, n. 17, p. 9748–9753, 2001. DOI: 10.1073/pnas.171285098.
