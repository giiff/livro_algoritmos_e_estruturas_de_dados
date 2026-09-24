class Vertice:
    '''
    Classe Vertice
    Representa um vertice de um grafo
    Cada vertice tem 3 atributos:
        valor: valor (rotulo) do vertice
        direcionado: True ou False para identificar se as arestas que incidem no vertice sao direcionadas ou nao
        arestas: arestas incidentes no vertice (dicionario usado como conjunto que preserva a ordem de insercao)
    '''
    def __init__(self, valor, direcionado = True):
        '''
        Metodo construtor da classe Vertice
        :param valor: indefinido (str, int, etc...)
        :param direcionado: boolean
        '''
        self.__valor = valor
        self.__direcionado = direcionado
        self.__arestas = {}

    def __str__(self):
        '''
        Metodo __str__ converte o objeto da classe para um formato string imprimivel
        :return: str
        '''
        arestasDeSaida = ", ".join(str(aresta) for aresta in self.getArestasSaida())
        arestasDeEntrada = ", ".join(str(aresta) for aresta in self.getArestasEntrada())
        return "{0} --> {1} --> {2}".format(arestasDeEntrada, self.__valor, arestasDeSaida)

    def __repr__(self):
        return "Vertice({0!r})".format(self.__valor)

    def getArestasSaida(self):
        '''
        Retorna uma lista com as arestas que saem do vertice
        Em grafos nao direcionados, todas as arestas incidentes
        :return: list
        '''
        if not self.__direcionado:
            return list(self.__arestas)
        return [aresta for aresta in self.__arestas if aresta.getVerticeOrigem() == self]

    def getArestasEntrada(self):
        '''
        Retorna uma lista com as arestas que entram no vertice
        Em grafos nao direcionados, todas as arestas incidentes
        :return: list
        '''
        if not self.__direcionado:
            return list(self.__arestas)
        return [aresta for aresta in self.__arestas if aresta.getVerticeDestino() == self]

    def getArestas(self):
        '''
        Retorna a lista de arestas do vertice (entradas e saidas)
        :return: list
        '''
        return list(self.__arestas)

    def getAdjacentes(self):
        '''
        Retorna a lista de vertices alcancaveis a partir deste vertice por uma aresta de saida
        :return: list
        '''
        adjacentes = []
        for aresta in self.getArestasSaida():
            vizinho = aresta.getOutraPonta(self)
            if vizinho not in adjacentes:
                adjacentes.append(vizinho)
        return adjacentes

    def getValor(self):
        '''
        Retorna o valor (rotulo) do vertice
        :return: indefinido (str, int, etc...)
        '''
        return self.__valor

    def adicionarAresta(self, aresta):
        '''
        Adiciona uma nova aresta ao conjunto de arestas do vertice
        :param aresta: Aresta
        :return: void
        '''
        self.__arestas[aresta] = None

    def removerAresta(self, aresta):
        '''
        Remove uma dada aresta do conjunto de arestas do vertice
        :param aresta: Aresta
        :return: void
        '''
        if aresta in self.__arestas:
            del self.__arestas[aresta]
        else:
            raise ValueError(
                "Nao foi possivel encontrar a aresta {0} no vertice {1}".format(str(aresta), self.__valor))

    def __eq__(self, outroVertice):
        '''
        Compara dois vertices pelo valor
        :param outroVertice: Vertice
        :return: boolean
        '''
        if not isinstance(outroVertice, Vertice):
            return NotImplemented
        return self.__valor == outroVertice.getValor()

    def __hash__(self):
        '''
        Gera um hash a partir do valor do vertice
        :return: int
        '''
        return hash(self.__valor)
