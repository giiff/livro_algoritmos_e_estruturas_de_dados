import itertools
import math
import random

import pytest

from grafos import Grafo

# Grafo da Figura "Exemplo de grafo" do livro:
# V = {a, b, c, d, e}; E = {(a,b),(a,c),(b,c),(b,d),(c,d),(c,e),(d,e)}
V_LIVRO = ["a", "b", "c", "d", "e"]
E_LIVRO = [("a", "b"), ("a", "c"), ("b", "c"), ("b", "d"), ("c", "d"), ("c", "e"), ("d", "e")]


def grafo_livro():
    G = Grafo(direcionado=False)
    for v in V_LIVRO:
        G.adicionarVertice(v)
    for origem, destino in E_LIVRO:
        G.adicionarAresta(origem, destino)
    return G


def test_cardinalidades():
    G = grafo_livro()
    assert len(G.getVertices()) == 5
    assert len(G.getArestas()) == 7


def test_handshaking_lemma():
    G = grafo_livro()
    assert sum(G.getGrau(v) for v in V_LIVRO) == 2 * len(G.getArestas())


def test_laco_conta_em_dobro():
    G = Grafo(direcionado=False)
    G.adicionarVertice(1)
    G.adicionarAresta(1, 1)
    assert G.getGrau(1) == 2


def test_matriz_adjacencia_igual_a_do_livro():
    esperada = [
        [0, 1, 1, 0, 0],
        [1, 0, 1, 1, 0],
        [1, 1, 0, 1, 1],
        [0, 1, 1, 0, 1],
        [0, 0, 1, 1, 0],
    ]
    assert grafo_livro().getMatrizAdjacenciaComoArray().tolist() == esperada


def test_aresta_sem_vertice_gera_erro():
    G = Grafo()
    G.adicionarVertice("a")
    with pytest.raises(ValueError):
        G.adicionarAresta("a", "x")
    with pytest.raises(ValueError):
        G.adicionarAresta("x", "a")


def test_remover_aresta_nao_direcionada_em_qualquer_sentido():
    G = grafo_livro()
    G.removerAresta("b", "a")
    assert len(G.getArestas()) == 6
    assert G.getGrau("a") == 1


def test_remover_vertice_remove_arestas_incidentes():
    G = grafo_livro()
    G.removerVertice("c")
    assert "c" not in G.getVertices()
    assert len(G.getArestas()) == 3
    assert G.getGrau("a") == 1


def test_buscas_percorrem_na_ordem_esperada():
    G = grafo_livro()
    assert G.BFS("a") == ["a", "b", "c", "d", "e"]
    assert G.DFS("a") == ["a", "b", "c", "d", "e"]
    assert G.DFS("e") == ["e", "c", "a", "b", "d"]


def test_buscas_respeitam_direcao():
    G = Grafo(direcionado=True)
    for v in "abc":
        G.adicionarVertice(v)
    G.adicionarAresta("a", "b")
    G.adicionarAresta("c", "b")
    assert G.BFS("a") == ["a", "b"]
    assert G.DFS("b") == ["b"]


def test_buscas_nao_compartilham_estado_entre_chamadas():
    G = grafo_livro()
    assert G.BFS("a") == G.BFS("a")
    assert G.DFS("a") == G.DFS("a")


def grafo_aleatorio(n, p, direcionado, semente):
    rnd = random.Random(semente)
    G = Grafo(direcionado=direcionado)
    for v in range(n):
        G.adicionarVertice(v)
    arestas = []
    pares = itertools.permutations(range(n), 2) if direcionado else itertools.combinations(range(n), 2)
    for u, v in pares:
        if rnd.random() < p:
            peso = rnd.randint(1, 20)
            G.adicionarAresta(u, v, peso)
            arestas.append((u, v, peso))
    return G, arestas


def floyd_warshall(n, arestas, direcionado):
    d = [[0 if i == j else math.inf for j in range(n)] for i in range(n)]
    for u, v, w in arestas:
        d[u][v] = min(d[u][v], w)
        if not direcionado:
            d[v][u] = min(d[v][u], w)
    for k in range(n):
        for i in range(n):
            for j in range(n):
                d[i][j] = min(d[i][j], d[i][k] + d[k][j])
    return d


@pytest.mark.parametrize("semente", range(30))
@pytest.mark.parametrize("direcionado", [True, False])
def test_dijkstra_confere_com_floyd_warshall(semente, direcionado):
    n = 7
    G, arestas = grafo_aleatorio(n, 0.35, direcionado, semente)
    esperado = floyd_warshall(n, arestas, direcionado)
    for origem in range(n):
        resultado = G.Dijkstra(origem)
        peso, _ = resultado
        for destino in range(n):
            assert peso[destino] == esperado[origem][destino]
            caminho, distancia = G.getCaminho(origem, destino, resultado)
            assert distancia == esperado[origem][destino]
            if distancia == math.inf:
                assert caminho == []
            else:
                assert caminho[0] == origem and caminho[-1] == destino


def peso_floresta_minima_forca_bruta(n, arestas):
    # Kruskal com union-find como referencia
    pai = list(range(n))

    def raiz(x):
        while pai[x] != x:
            pai[x] = pai[pai[x]]
            x = pai[x]
        return x

    total = 0
    for u, v, w in sorted(arestas, key=lambda a: a[2]):
        ru, rv = raiz(u), raiz(v)
        if ru != rv:
            pai[ru] = rv
            total += w
    return total


@pytest.mark.parametrize("semente", range(30))
def test_prim_gera_arvore_de_peso_minimo(semente):
    n = 8
    G, arestas = grafo_aleatorio(n, 0.4, False, semente)
    arvore = G.Prim()
    assert sum(peso for _, peso, _ in arvore) == peso_floresta_minima_forca_bruta(n, arestas)
    # uma floresta geradora nao tem ciclos: |arestas| = |V| - numero de componentes
    componentes = set()
    for v in range(n):
        componentes.add(frozenset(G.BFS(v)))
    assert len(arvore) == n - len(componentes)
