import heapq
import math
from collections import deque
from itertools import count

from .Aresta import Aresta
from .Vertice import Vertice


class Grafo:
    '''
    Classe Grafo
    Representa um grafo G = (V, E) que pode ou nao ser direcionado
    '''

    def __init__(self, direcionado=True):
        '''
        Metodo construtor da classe Grafo
        Por padrao o grafo sera direcionado, a menos que explicite-se False para o parametro direcionado
        :param direcionado: boolean
        '''
        self.__vertices = {}  # dicionario: valor -> Vertice
        self.__arestas = {}  # dicionario usado como conjunto que preserva a ordem de insercao
        self.__direcionado = direcionado  # boolean

    def __str__(self):
        '''
        Metodo __str__ converte o objeto da classe para um formato string imprimivel
        :return: str
        '''
        return "\n".join(str(vertice) for vertice in self.__vertices.values())

    def adicionarVertice(self, valor):
        '''
        Adiciona um vertice ao grafo
        A partir do valor informado, cria-se um objeto da classe Vertice
        O vertice e inserido no dicionario de vertices do grafo tendo o valor como chave*
            *atencao que neste caso nao pode haver vertices com o mesmo valor
        :param valor: indefinido (int, float, str, etc)
        :return: void
        '''
        if valor not in self.__vertices:  # ainda nao existe um vertice com esse valor?
            self.__vertices[valor] = Vertice(valor, self.__direcionado)

    def __getVerticesDaAresta(self, origem, destino):
        '''
        Retorna os vertices de origem e destino, verificando se ambos existem no grafo
        '''
        verticeOrigem = self.getVertice(origem)
        verticeDestino = self.getVertice(destino)
        if verticeOrigem is None or verticeDestino is None:  # os dois vertices precisam existir
            raise ValueError("Nao ha no grafo, vertices de origem ou de destino com os valores informados.")
        return verticeOrigem, verticeDestino

    def adicionarAresta(self, origem, destino, peso = 1):
        '''
        Adiciona uma aresta ao conjunto de arestas do grafo
        A aresta e criada utilizando a classe Aresta
        Precisam existir vertices de origem e destino com os valores previamente informados
        :param origem: indefinido (int, str, etc) valor do vertice de onde sai a aresta
        :param destino: indefinido (int, str, etc) valor do vertice onde entra a aresta
        :param peso: indefinido (int, float)
        :return: void
        '''
        verticeOrigem, verticeDestino = self.__getVerticesDaAresta(origem, destino)
        aresta = Aresta(verticeOrigem, verticeDestino, peso, self.__direcionado)
        verticeOrigem.adicionarAresta(aresta)
        if verticeOrigem != verticeDestino:
            verticeDestino.adicionarAresta(aresta)
        self.__arestas[aresta] = None

    def removerAresta(self, origem, destino, peso = 1):
        '''
        Remove uma aresta do grafo
        :param origem: indefinido (int, str, etc) valor do vertice de onde sai a aresta
        :param destino: indefinido (int, str, etc) valor do vertice onde entra a aresta
        :param peso: indefinido (int, float)
        :return: void
        '''
        verticeOrigem, verticeDestino = self.__getVerticesDaAresta(origem, destino)
        aresta = Aresta(verticeOrigem, verticeDestino, peso, self.__direcionado)
        if aresta not in self.__arestas:  # aresta informada nao existe no conjunto de arestas do grafo
            raise ValueError("Nao foi possivel encontrar {0} no grafo.".format(str(aresta)))
        verticeOrigem.removerAresta(aresta)
        if verticeOrigem != verticeDestino:
            verticeDestino.removerAresta(aresta)
        del self.__arestas[aresta]

    def removerVertice(self, valor):
        '''
        Remove um vertice do grafo com base em seu valor, junto com todas as arestas incidentes nele
        :param valor: indefinido (int, str, etc)
        :return: void
        '''
        if valor not in self.__vertices:  # vertice nao existe no dicionario de vertices?
            raise ValueError("Nao foi possivel encontrar {0} no grafo".format(valor))
        vertice = self.__vertices[valor]
        for aresta in vertice.getArestas():  # getArestas devolve uma copia: e seguro remover durante o laco
            vizinho = aresta.getOutraPonta(vertice)
            if vizinho != vertice:
                vizinho.removerAresta(aresta)
            self.__arestas.pop(aresta, None)
        # remove finalmente o vertice do grafo
        self.__vertices.pop(valor)

    def getVertice(self, valor):
        '''
        Retorna um vertice com base em seu valor (None se nao existir)
        :param valor: indefinido (int, str, etc)
        :return: Vertice
        '''
        return self.__vertices.get(valor)

    def getVertices(self):
        '''
        Retorna o dicionario com todos os vertices
        :return: dict
        '''
        return self.__vertices

    def getArestas(self):
        '''
        Retorna a lista de arestas
        :return: list
        '''
        return list(self.__arestas)

    def getGrauEntrada(self, valor):
        '''
        Retorna o grau de entrada de um vertice a partir de seu valor
        :param valor: indefinido (int, str, etc)
        :return: int
        '''
        return len(self.getVertice(valor).getArestasEntrada())

    def getGrauSaida(self, valor):
        '''
        Retorna o grau de saida de um vertice a partir de seu valor
        :param valor: indefinido (int, str, etc)
        :return: int
        '''
        return len(self.getVertice(valor).getArestasSaida())

    def getGrau(self, valor):
        '''
        Retorna o grau de um vertice (quantidade de arestas incidentes)
        Em grafos nao direcionados, lacos sao contados em dobro
        :param valor: indefinido (int, str, etc)
        :return: int
        '''
        vertice = self.getVertice(valor)
        if self.direcionado():
            return len(vertice.getArestasEntrada()) + len(vertice.getArestasSaida())
        return sum(2 if aresta.getVerticeOrigem() == aresta.getVerticeDestino() else 1
                   for aresta in vertice.getArestas())

    def direcionado(self):
        '''
        Retorna um boolean (True ou False) se o grafo e ou nao direcionado
        :return: boolean
        '''
        return self.__direcionado

    def getMatrizAdjacencia(self):
        '''
        Retorna uma matriz de adjacencias como objeto pandas DataFrame
        Os indices das linhas e colunas sao os rotulos dos vertices
        Os valores sao os pesos das arestas (0 indica ausencia de aresta)
        :return: pd.DataFrame
        '''
        import pandas as pd  # importacao local: pandas so e exigido quando o metodo e usado
        V = list(self.getVertices())
        matrizDeAdjacencias = pd.DataFrame(0, columns = V, index = V, dtype = object)
        for e in self.getArestas():
            origem = e.getVerticeOrigem().getValor()
            destino = e.getVerticeDestino().getValor()
            matrizDeAdjacencias.loc[origem, destino] = e.getPeso()
            if not self.__direcionado:  # matriz simetrica em grafos nao direcionados
                matrizDeAdjacencias.loc[destino, origem] = e.getPeso()
        return matrizDeAdjacencias

    def getMatrizAdjacenciaComoArray(self):
        '''
        Retorna a matriz de adjacencias convertida para um array numpy
        :return: np.ndarray
        '''
        return self.getMatrizAdjacencia().to_numpy()

    def getMatrizAdjacenciaComoDict(self):
        '''
        Retorna a matriz de adjacencias convertida para um dicionario
        :return: dict
        '''
        return self.getMatrizAdjacencia().to_dict('dict')

    def DFS(self, valor, visitados = None):
        '''
        Busca em profundidade a partir do vertice com o valor informado
        Retorna uma lista com os vertices visitados, na ordem de visita
        Complexidade: O(|V| + |E|)
        :param valor: indefinido (int, str, etc)
        :param visitados: list() ou None
        :return: list()
        '''
        if visitados is None:  # evita o uso de lista mutavel como valor padrao
            visitados = []
        if valor not in visitados:  # vertice ainda nao foi visitado?
            visitados.append(valor)  # marca-o como visitado
            for adjacente in self.getVertice(valor).getAdjacentes():
                self.DFS(adjacente.getValor(), visitados)  # aprofunda pelo adjacente
        return visitados

    def BFS(self, valor, visitados = None, fila = None):
        '''
        Busca em largura a partir do vertice com o valor informado
        Retorna uma lista com os vertices visitados, na ordem de visita
        Complexidade: O(|V| + |E|)
        :param valor: indefinido (int, str, etc)
        :param visitados: list() ou None
        :param fila: collections.deque() ou None
        :return: list()
        '''
        if visitados is None:
            visitados = []
        if fila is None:
            fila = deque()
        if valor not in visitados:  # vertice inicial ainda nao esta em visitados?
            visitados.append(valor)
            fila.append(valor)  # adiciona o vertice inicial a fila
        while fila:  # enquanto houver vertices na fila
            vertice = self.getVertice(fila.popleft())  # retira o proximo vertice da fila
            for adjacente in vertice.getAdjacentes():  # percorre os vertices adjacentes
                vAdjacente = adjacente.getValor()
                if vAdjacente not in visitados:  # se o adjacente ainda nao foi visitado
                    visitados.append(vAdjacente)  # insere o adjacente em visitados
                    fila.append(vAdjacente)  # insere o adjacente na fila a visitar
        return visitados  # retorna a lista de visitados

    def Prim(self):
        '''
        Arvore geradora minima pelo algoritmo de Prim
        As arestas sao tratadas como nao direcionadas
        Se o grafo for desconexo, retorna uma floresta geradora minima
        Complexidade: O(|E| log |E|) com fila de prioridade (heap)
        :return: list() de [origem, peso, destino]
        '''
        arvoreGeradoraMinima = []
        naArvore = set()
        desempate = count()  # evita comparar vertices quando os pesos empatam
        for inicio in self.getVertices():
            if inicio in naArvore:
                continue
            naArvore.add(inicio)
            heap = []
            for e in self.getVertice(inicio).getArestas():
                heapq.heappush(heap, (e.getPeso(), next(desempate), inicio, e))
            while heap:
                peso, _, origem, e = heapq.heappop(heap)  # aresta mais leve que sai da arvore
                destino = e.getOutraPonta(self.getVertice(origem)).getValor()
                if destino in naArvore:  # formaria ciclo
                    continue
                naArvore.add(destino)
                arvoreGeradoraMinima.append([origem, peso, destino])
                for proxima in self.getVertice(destino).getArestas():
                    vizinho = proxima.getOutraPonta(self.getVertice(destino)).getValor()
                    if vizinho not in naArvore:
                        heapq.heappush(heap, (proxima.getPeso(), next(desempate), destino, proxima))
        return arvoreGeradoraMinima

    def Dijkstra(self, origem):
        '''
        Algoritmo de menor caminho de Dijkstra em um grafo G = (V,E) com pesos nao negativos
        Complexidade desta implementacao: O(|V|^2 + |E|)
        :param origem: indefinido (int, str, etc)
        :return: peso:dict, antecessor:dict
        '''
        peso = {}
        antecessor = {}
        V = list(self.getVertices())  # todos os vertices do grafo para visitar O(n)
        for v in V:  # O(n)
            peso[v] = math.inf  # peso desconhecido entre origem e todo vertice v
            antecessor[v] = None  # vertice de onde vem o menor peso
        peso[origem] = 0  # peso zero quando origem = destino
        while V:
            vComMenorPeso = self.getVComMenorPeso(V, peso)  # v com menor peso
            V.remove(vComMenorPeso)  # retira o vComMenorPeso do conjunto V
            if peso[vComMenorPeso] == math.inf:  # os vertices restantes sao inalcancaveis
                break
            for e in self.getVertice(vComMenorPeso).getArestasSaida():  # arestas que saem de vComMenorPeso
                destino = e.getOutraPonta(self.getVertice(vComMenorPeso)).getValor()
                pesoSomadoParaComparacao = peso[vComMenorPeso] + e.getPeso()  # peso somado
                if pesoSomadoParaComparacao < peso[destino]:  # relaxamento da aresta
                    peso[destino] = pesoSomadoParaComparacao  # novo menor peso
                    antecessor[destino] = vComMenorPeso  # atualiza o antecessor
        return peso, antecessor

    def getVComMenorPeso(self, V: list, pesos: dict):
        '''
        Retorna o vertice de V com o menor peso acumulado
        '''
        vComMenorPeso = None
        for v in V:  # O(n)
            if vComMenorPeso is None or pesos[v] < pesos[vComMenorPeso]:
                vComMenorPeso = v
        return vComMenorPeso

    def getCaminho(self, origem, destino, Dijkstra: tuple):
        '''
        Reconstroi o menor caminho a partir do resultado de Dijkstra(origem)
        :param origem: valor do vertice de origem
        :param destino: valor do vertice de destino
        :param Dijkstra: tupla (peso, antecessor) devolvida pelo metodo Dijkstra
        :return: caminho: list, distanciaTotal (math.inf e caminho vazio se inalcancavel)
        '''
        peso, antecessor = Dijkstra
        if peso.get(destino, math.inf) == math.inf:
            return [], math.inf
        caminho = [destino]
        while caminho[-1] != origem:  # volta pelos antecessores ate a origem
            caminho.append(antecessor[caminho[-1]])
        caminho.reverse()
        return caminho, peso[destino]


if __name__ == "__main__":
    G = Grafo()

    G.adicionarVertice("a")
    G.adicionarVertice("b")
    G.adicionarVertice("c")

    G.adicionarAresta("a", "b", 2)
    G.adicionarAresta("a", "c", 7)
    G.adicionarAresta("c", "b", 1)
    G.adicionarAresta("b", "c", 3)

    print(G)
    print("DFS:", G.DFS("a"))
    print("BFS:", G.BFS("a"))
    print("Dijkstra:", G.getCaminho("a", "c", G.Dijkstra("a")))
