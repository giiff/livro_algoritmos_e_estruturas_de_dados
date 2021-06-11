import numpy as np
import pandas as pd
from collections import deque
from .Aresta import Aresta
from .Vertice import Vertice

class Grafo:
    '''
    Classe Grafo
    Representa um grafo que pode ou nao ser direcionado
    '''

    def __init__(self, direcionado=True):
        '''
        Metodo construtor da classe Grafo
        Por padrao o grafo sera direcionado, a menos que explicite-se False para o parametro direcionado
        :param direcionado: boolean
        '''
        self.__vertices = {}  # dicionario
        self.__arestas = set()  # conjunto
        self.__direcionado = direcionado  # boolean

    def __str__(self):
        '''
        Método __str__ converte o objeto da classe para um formato string impimivel
        :return: str
        '''
        grafoString = ""
        for chave in self.__vertices:
            grafoString += str(self.__vertices[chave]) + '\n'
        return grafoString

    def adicionarVertice(self, valor):
        '''
        Adicina um verticeLabel ao grafo
        A partir do valor informado, cria-se um verticeLabel com os metodos da classe Vertice
        Esse verticeLabel e entao inserido no dicionario de verticeLabel do grafo tendo o valor como chave*
            *atencao que neste caso nao pode haver vertices com o mesmo valor
        :param valor: indefinido (int, float, str, etc)
        :return: void
        '''
        if valor not in self.__vertices:  # ainda nao existe um verticeLabel com esse valor?
            self.__vertices[valor] = Vertice(valor, self.__direcionado)

    def adicionarAresta(self, origem, destino, peso=1):
        '''
        Adiciona uma aresta ao conjunto de arestas do grafo
        A aresta e criada utilizando os metodos da classe Aresta
        Precisam existir vertices de origem e destino comos valores previamente informados
        :param origem: indefinido (int, str, etc) valor do verticeLabel de onde sai a aresta
        :param destino: indefinido (int, str, etc) valor do verticeLabel onde entra a aresta
        :param peso: indefinido (int, float)
        :return: void
        '''
        verticeOrigem = self.getVertice(origem)
        verticeDestino = self.getVertice(destino)
        if (verticeOrigem or verticeDestino) is None:  # verifica se existem os vertices de origem e destino
            raise ValueError("Nao ha no grafo, vertices de origem ou de destino com os valores informados.")
        aresta = Aresta(verticeOrigem, verticeDestino, peso, self.__direcionado)
        verticeOrigem.adicionarAresta(aresta)
        if verticeOrigem != verticeDestino:
            verticeDestino.adicionarAresta(aresta)
        self.__arestas.add(aresta)

    def removerAresta(self, origem, destino, peso=1):
        '''
        Remove uma aresta do grafo
        :param origem: indefinido (int, str, etc) valor do verticeLabel de onde sai a aresta
        :param destino: indefinido (int, str, etc) valor do verticeLabel onde entra a aresta
        :param peso: indefinido (int, float)
        :return: void
        '''
        verticeOrigem = self.getVertice(origem)
        verticeDestino = self.getVertice(destino)
        if (verticeOrigem or verticeDestino) is None:  # verifica se existem os vertices de origem e destino
            raise ValueError("Nao ha no grafo, vertices de origem ou de destino com os valores informados.")
        aresta = Aresta(verticeOrigem, verticeDestino, peso, self.__direcionado)
        if aresta not in self.__arestas:  # aresta informada nao existe no conjunto de arestas do grafo
            raise ValueError("Não foi possível encontrar {0} no grafo.".format(str(aresta)))
        verticeOrigem.removerAresta(aresta)
        verticeDestino.removerAresta(aresta)
        self.__arestas.remove(aresta)

    def removerVertice(self, valor):
        '''
        Remove um verticeLabel do grafo com base em seu valor
        :param valor: indefinido (int, str, etc)
        :return: void
        '''
        if valor not in self.__vertices:  # verticeLabel nao existe no dicionario de vertices?
            raise ValueError("Não foi possível encontrar {0} no grafo".format(valor))
        vertice = self.__vertices[valor]
        # Como podem existir arestas ligadas ao verticeLabel que sera deletado,
        # Faz-se uma copia delas para evitar erros de uma aresta apontando para apenas um verticeLabel apos remocao
        arestasOrigemCopia = vertice.getArestasEntrada().copy()
        for aresta in arestasOrigemCopia:
            verticeAdjacente = aresta.getVerticeOrigem()
            verticeAdjacente.removerAresta(aresta)
            if aresta in self.__arestas:
                self.__arestas.remove(aresta)
        arestasSaidaCopia = vertice.getArestasSaida().copy()
        for aresta in arestasSaidaCopia:
            verticeAdjacente = aresta.getVerticeDestino()
            verticeAdjacente.removerAresta(aresta)
            if aresta in self.__arestas:
                self.__arestas.remove(aresta)
        # remove finalmente o verticeLabel do grafo
        self.__vertices.pop(valor)

    def getVertice(self, valor):
        '''
        Retorna um verticeLabel com base em seu valor
        :param valor: indefinido (int, str, etc)
        :return: Vertice
        '''
        return self.__vertices.get(valor)

    def getVertices(self):
        '''
        Retorna o dicionarios com todos os vertices
        :return: Dict
        '''
        return self.__vertices

    def getArestas(self):
        '''
        Retorna o conjunto de arestas
        :return: Set
        '''
        return self.__arestas

    def getGrauEntrada(self, valor):
        '''
        Retorna o grau de entrada de um dado verticeLabel a partir de seu valor
        :param valor: indefinido (int, str, etc)
        :return: int
        '''
        return len(self.getVertice(valor).getArestasEntrada())

    def getGrauSaida(self, valor):
        '''
        Retorna o grau de saida de um dado verticeLabel a partir de seu valor
        :param valor: indefinido (int, str, etc)
        :return: int
        '''
        return len(self.getVertice(valor).getArestasSaida())

    def getGrau(self, valor):
        '''
        Retorna o grau de um verticeLabel (quantidade de arestas entrada e saida)
        :param valor: 
        :return: int
        '''
        if self.direcionado():
            grau = len(self.getVertice(valor).getArestasEntrada()) + len(self.getVertice(valor).getArestasSaida())
        else:
            grau = len(self.getVertice(valor).getArestasSaida())
        return grau

    def direcionado(self):
        '''
        Retorna um boolean (True or False) se o grafo e ou nao direcionado
        :return: boolean
        '''
        return self.__direcionado

    def getMatrizAdjacencia(self):
        '''
        Retorna um matriz de adjacencias como objeto pandas dataframe
        Os indices das linhas e colunas sao os labels dos vertices
        Os valores são os pesos das arestas
        :return: pd.DataFrame
        '''
        listaDeVertices = []
        for l in self.getVertices():
            listaDeVertices.append(l)
        matriz = np.zeros((
            len(listaDeVertices),
            len(listaDeVertices)),
            dtype=object)
        matrizDeAdjacencias = pd.DataFrame(matriz, columns=listaDeVertices, index=listaDeVertices)
        for index, row in matrizDeAdjacencias.iterrows():
            for e in self.getArestas():
                matrizDeAdjacencias.loc[e.getVerticeOrigem().getValor(), e.getVerticeDestino().getValor()] = e.getPeso()
        return matrizDeAdjacencias

    def getMatrizAdjacenciaComoArray(self):
        '''
        Retorna a matriz de adjacencias convertida para um array numpy
        :return: np.Array
        '''
        return self.getMatrizAdjacencia().to_numpy()

    def getMatrizAdjacenciaComoDict(self):
        '''
        Retorna a matriz de adjacencias convertida para um dicionario
        :return: dict
        '''
        return self.getMatrizAdjacencia().to_dict('dict')

    def DFS(self, verticeLabel, visitados=[]):
        '''
        Busca em profundidade
        Retorna uma lista com os vertices visitados
        :param verticeLabel: str
        :param visitados: list()
        :return: list()
        '''
        if verticeLabel not in visitados:  # verticeLabel da vez ainda nao foi visitado?
            visitados.append(verticeLabel)  # adiciona-o aos visitados
            for v in self.getVertices():
                if v not in visitados:
                    return visitados
                else:
                    for adjacente in self.getVertices():
                        visitados = self.DFS(adjacente, visitados)
        return visitados

    def BFS(self, verticeLabel, visitados=[], fila=deque([])):
        '''
        Busca em largura
        Retorna uma lista com os vertices visitados
        :param verticeLabel: str
        :param visitados: list()
        :param fila: collections.deque()
        :return: list()
        '''
        fila.append(verticeLabel)  # adiciona o vertice 1 a fila
        if verticeLabel not in visitados:  # se vertice 1 nao esta em visitados
            visitados.append(verticeLabel)  # adiciona vertice 1 a visitados
        while fila:  # enquanto houver vertices na fila
            vertice = self.getVertice(fila.popleft())  # tira vertice ja visitado da fila
            for e in self.getVertice(vertice.getValor()).getArestas():  # percorre todas as arestas saindo do vertice
                adjacente = e.getVerticeDestino().getValor()  # para cada aresta, um vertice adjacente
                if adjacente not in visitados:  # se o vertice adjacente nao esta em visitados
                    visitados.append(adjacente)  # insere o adjacente em visitados
                    fila.append(adjacente)  # insere o adjacente da fila a visitar
        return visitados  # retorna a lista de visitados


if __name__ == "__main__":
#     G = Grafo()

#     G.adicionarVertice("a")
#     G.adicionarVertice("b")
#     G.adicionarVertice("c")

#     G.adicionarAresta("a", "b", 2)
#     G.adicionarAresta("a", "c", 7)
#     G.adicionarAresta("c", "b", 1)
#     G.adicionarAresta("b", "c", 3)
