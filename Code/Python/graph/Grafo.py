from .Aresta import Aresta
from .Vertice import Vertice

class Grafo:
    '''
    Classe Grafo
    Representa um grafo que pode ou nao ser direcionado
    '''
    def __init__(self, direcionado = True):
        '''
        Metodo construtor da classe Grafo
        Por padrao o grafo sera direcionado, a menos que explicite-se False para o parametro direcionado
        :param direcionado: boolean
        '''
        self.__vertices = {} # dicionario
        self.__arestas = set() # conjunto
        self.__direcionado = direcionado # boolean

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
        Adicina um vertice ao grafo
        A partir do valor informado, cria-se um vertice com os metodos da classe Vertice
        Esse vertice e entao inserido no dicionario de vertice do grafo tendo o valor como chave*
            *atencao que neste caso nao pode haver vertices com o mesmo valor
        :param valor: indefinido (int, float, str, etc)
        :return: void
        '''
        if valor not in self.__vertices: # ainda nao existe um vertice com esse valor?
            self.__vertices[valor] = Vertice(valor, self.__direcionado)

    def adicionarAresta(self, origem, destino, peso = 1):
        '''
        Adiciona uma aresta ao conjunto de arestas do grafo
        A aresta e criada utilizando os metodos da classe Aresta
        Precisam existir vertices de origem e destino comos valores previamente informados
        :param origem: indefinido (int, str, etc) valor do vertice de onde sai a aresta
        :param destino: indefinido (int, str, etc) valor do vertice onde entra a aresta
        :param peso: indefinido (int, float)
        :return: void
        '''
        verticeOrigem = self.getVertice(origem)
        verticeDestino = self.getVertice(destino)
        if (verticeOrigem or verticeDestino) is None: # verifica se existem os vertices de origem e destino
            raise ValueError("Nao ha no grafo, vertices de origem ou de destino com os valores informados.")
        aresta = Aresta(verticeOrigem, verticeDestino, peso, self.__direcionado)
        verticeOrigem.adicionarAresta(aresta)
        if verticeOrigem != verticeDestino:
            verticeDestino.adicionarAresta(aresta)
        self.__arestas.add(aresta)

    def removerAresta(self, origem, destino, peso = 1):
        '''
        Remove uma aresta do grafo
        :param origem: indefinido (int, str, etc) valor do vertice de onde sai a aresta
        :param destino: indefinido (int, str, etc) valor do vertice onde entra a aresta
        :param peso: indefinido (int, float)
        :return: void
        '''
        verticeOrigem = self.getVertice(origem)
        verticeDestino = self.getVertice(destino)
        if (verticeOrigem or verticeDestino) is None: # verifica se existem os vertices de origem e destino
            raise ValueError("Nao ha no grafo, vertices de origem ou de destino com os valores informados.")
        aresta = Aresta(verticeOrigem, verticeDestino, peso, self.__direcionado)
        if aresta not in self.__arestas: # aresta informada nao existe no conjunto de arestas do grafo
            raise ValueError("Não foi possível encontrar {0} no grafo.".format(str(aresta)))
        verticeOrigem.removerAresta(aresta)
        verticeDestino.removerAresta(aresta)
        self.__arestas.remove(aresta)

    def removerVertice(self, valor):
        '''
        Remove um vertice do grafo com base em seu valor
        :param valor: indefinido (int, str, etc)
        :return: void
        '''
        if valor not in self.__vertices: # vertice nao existe no dicionario de vertices?
            raise ValueError("Não foi possível encontrar {0} no grafo".format(valor))
        vertice = self.__vertices[valor]
        # Como podem existir arestas ligadas ao vertice que ser adeletado,
        # faz-se uma copia delas para evitar erros de uma aresta apontando para apenas um vertice apos remocao
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
        # remove finalmente o vertice do grafo
        self.__vertices.pop(valor)

    def getVertice(self, valor):
        '''
        Retorna um vertice com base em seu valor
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
        Retorna o grau de entrada de um dado vertice a partir de seu valor
        :param valor: indefinido (int, str, etc)
        :return: int
        '''
        return len(self.getVertice(valor).getArestasEntrada())

    def getGrauSaida(self, valor):
        '''
        Retorna o grau de saida de um dado vertice a partir de seu valor
        :param valor: indefinido (int, str, etc)
        :return: int
        '''
        return len(self.getVertice(valor).getArestasSaida())

    def getGrau(self, valor):
        '''
        Retorna o grau de um vertice (quantidade de arestas entrada e saida)
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


if __name__ == "__main__":
    G = Grafo()

    G.adicionarVertice("a")
    G.adicionarVertice("b")
    G.adicionarVertice("c")

    G.adicionarAresta("a", "b", 2)
    G.adicionarAresta("a", "c", 7)
    G.adicionarAresta("c", "b", 1)
    G.adicionarAresta("b", "c", 3)

    # print(test_graph)
