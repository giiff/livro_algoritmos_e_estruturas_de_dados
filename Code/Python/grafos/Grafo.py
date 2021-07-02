import numpy as np
import pandas as pd
from collections import deque
from .Aresta import Aresta
from .Vertice import Vertice
import math

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
        self.__vertices = {}  # dicionario
        self.__arestas = set()  # conjunto
        self.__direcionado = direcionado  # boolean

    def __str__(self):
        '''
        Método __str__ converte o objeto da classe para um formato string impimivel
        :return: str
        '''
        grafoString = ""
        for valor in self.__vertices:
            grafoString += str(self.__vertices[valor]) + '\n'
        return grafoString

    def adicionarVertice(self, valor):
        '''
        Adicina um valor ao grafo
        A partir do valor informado, cria-se um valor com os metodos da classe Vertice
        Esse valor e entao inserido no dicionario de valor do grafo tendo o valor como chave*
            *atencao que neste caso nao pode haver vertices com o mesmo valor
        :param valor: indefinido (int, float, str, etc)
        :return: void
        '''
        if valor not in self.__vertices:  # ainda nao existe um valor com esse valor?
            self.__vertices[valor] = Vertice(valor, self.__direcionado)

    def adicionarAresta(self, origem, destino, peso = 1):
        '''
        Adiciona uma aresta ao conjunto de arestas do grafo
        A aresta e criada utilizando os metodos da classe Aresta
        Precisam existir vertices de origem e destino comos valores previamente informados
        :param origem: indefinido (int, str, etc) valor do valor de onde sai a aresta
        :param destino: indefinido (int, str, etc) valor do valor onde entra a aresta
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

    def removerAresta(self, origem, destino, peso = 1):
        '''
        Remove uma aresta do grafo
        :param origem: indefinido (int, str, etc) valor do valor de onde sai a aresta
        :param destino: indefinido (int, str, etc) valor do valor onde entra a aresta
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
        Remove um valor do grafo com base em seu valor
        :param valor: indefinido (int, str, etc)
        :return: void
        '''
        if valor not in self.__vertices:  # valor nao existe no dicionario de vertices?
            raise ValueError("Não foi possível encontrar {0} no grafo".format(valor))
        vertice = self.__vertices[valor]
        # Como podem existir arestas ligadas ao valor que sera deletado,
        # Faz-se uma copia delas para evitar erros de uma aresta apontando para apenas um valor apos remocao
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
        # remove finalmente o valor do grafo
        self.__vertices.pop(valor)

    def getVertice(self, valor):
        '''
        Retorna um valor com base em seu valor
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
        Retorna o grau de entrada de um dado valor a partir de seu valor
        :param valor: indefinido (int, str, etc)
        :return: int
        '''
        return len(self.getVertice(valor).getArestasEntrada())

    def getGrauSaida(self, valor):
        '''
        Retorna o grau de saida de um dado valor a partir de seu valor
        :param valor: indefinido (int, str, etc)
        :return: int
        '''
        return len(self.getVertice(valor).getArestasSaida())

    def getGrau(self, valor):
        '''
        Retorna o grau de um valor (quantidade de arestas entrada e saida)
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
        V = []
        E = self.getArestas()
        [V.append(v) for v in self.getVertices()]
        matriz = np.zeros(( len(V), len(V)), dtype=object)
        matrizDeAdjacencias = pd.DataFrame(matriz, columns = V, index = V)
        for index, row in matrizDeAdjacencias.iterrows():
            for e in E:
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

    def DFS(self, valor, visitados = []):
        '''
        Busca em profundidade
        Retorna uma lista com os vertices visitados
        :param valor: str
        :param visitados: list()
        :return: list()
        '''
        V = self.getVertices()
        if valor not in visitados:  # valor da vez ainda nao foi visitado?
            visitados.append(valor)  # adiciona-o aos visitados
            for v in V:
                if v not in visitados:
                    return visitados
                else:
                    for adjacente in self.getVertices():
                        visitados = self.DFS(adjacente, visitados)
        return visitados

    def BFS(self, verticeLabel, visitados = [], fila = deque([])):
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
                vAdjacente = e.getVerticeDestino().getValor()  # para cada aresta, um vertice adjacente
                if vAdjacente not in visitados:  # se o vertice adjacente nao esta em visitados
                    visitados.append(vAdjacente)  # insere o adjacente em visitados
                    fila.append(vAdjacente)  # insere o adjacente da fila a visitar
        return visitados  # retorna a lista de visitados

    def Prim(self):
        '''
        Arvore geradora minima de Prim
        Retorna o subgrafo que configura uma arvore geradora minima de Prim
        :return: list()
        '''
        V = []
        [V.append(v_i) for v_i in self.getVertices()]# todos os vertices do grafo para visitar
        arvoreGeradoraMinima = [] # arvore geradora minima: lista de vertices
        for valor in V:
            menorPeso = math.inf
            for e in self.getVertice(valor).getArestasSaida(): # todas arestas saindo de v_i
                if e:
                    if e.getPeso() < menorPeso:
                        menorPeso = e.getPeso()
            for e in self.getVertice(valor).getArestasSaida(): # todas arestas saindo de v_i
                if e and e.getPeso() == menorPeso:
                    arvoreGeradoraMinima.append( [valor, e.getPeso(), e.getVerticeDestino().getValor()] )
        return arvoreGeradoraMinima

    def Dijkstra(self, origem):
        '''
        Algoritmo de menor caminho usando Dijkstra em um grafo G = (V,E)
        :param origem: str
        :return: peso:dict, antessores:dict
        '''
        peso = {}
        antecessor = {}
        V = []
        [V.append(v_i) for v_i in self.getVertices()]# todos os vertices do grafo para visitar O(n)
        for v in V: # O(n)
            peso[v] = math.inf # peso desconhecido entre origem e todos vertice v
            antecessor[v] = math.inf # vertice de onde vem o menor peso
        peso[origem] = 0 # peso zero quando origem = destino
        while V:
            vComMenorPeso =  self.getVComMenorPeso( V, peso ) # v com menor peso
            V.remove(vComMenorPeso) # retira o vComMenorPeso do conjunto V
            for e in self.getVertice(vComMenorPeso).getArestasSaida(): # todas arestas saindo do v_i adjacente O(n(e)+n(v))
                pesoSomadoParaComparacao = peso[vComMenorPeso] + e.getPeso() # peso somado
                if pesoSomadoParaComparacao < peso[e.getVerticeDestino().getValor()]: # compara peso somado
                    peso[e.getVerticeDestino().getValor()] = pesoSomadoParaComparacao # novo menor peso de v_i
                    antecessor[e.getVerticeDestino().getValor()] = vComMenorPeso # adiciona v_i na lista de antecessores
        return peso, antecessor

    def getVComMenorPeso(self, V:list, pesos:dict):
        vComMenorPeso = None
        for v in V: # O(n)
            if vComMenorPeso == None:
                vComMenorPeso = v
            elif pesos[v] < pesos[vComMenorPeso]:
                vComMenorPeso = v
        return vComMenorPeso

    def getCaminho(self, origem: str, destino:str, Dijkstra:dict):
        caminho = [destino] # Goiânia, Brasília, Formosa
        while Dijkstra[1][destino] != origem: # O(n)
            if destino in Dijkstra[1]:
                caminho.append(Dijkstra[1][destino])
                Dijkstra[1][destino] = Dijkstra[1][Dijkstra[1][destino]]
        caminho.append(origem)
        caminho.reverse()
        
        distanciaTotal = None
        if destino in Dijkstra[0]:
            distanciaTotal = Dijkstra[0][destino]

        return caminho, distanciaTotal


if __name__ == "__main__":
    G = Grafo()

    G.adicionarVertice("a")
    G.adicionarVertice("b")
    G.adicionarVertice("c")

    G.adicionarAresta("a", "b", 2)
    G.adicionarAresta("a", "c", 7)
    G.adicionarAresta("c", "b", 1)
    G.adicionarAresta("b", "c", 3)
