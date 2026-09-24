class Aresta:
    '''
    Classe Aresta
    Representa uma aresta de um grafo, que pode ser direcionada ou nao
    '''
    def __init__(self, verticeOrigem, verticeDestino, peso = 1, direcionada = True):
        '''
        :param verticeOrigem: Vertice
        :param verticeDestino: Vertice
        :param peso: indefinido (int, float, etc...)
        :param direcionada: boolean
        '''
        self.__verticeOrigem = verticeOrigem
        self.__verticeDestino = verticeDestino
        self.__peso = peso
        self.__direcionada = direcionada

    def __str__(self):
        '''
        Metodo __str__ converte o objeto da classe para um formato string imprimivel
        :return: str
        '''
        if self.__direcionada:
            padraoDeImpressao = "{0} |-{1}-> {2}"
        else:
            padraoDeImpressao = "{0} <-{1}-> {2}"
        return padraoDeImpressao.format(self.__verticeOrigem.getValor(), self.__peso, self.__verticeDestino.getValor())

    def __repr__(self):
        return str(self)

    def getVerticeOrigem(self):
        '''
        Retorna o vertice de origem da aresta
        :return: Vertice
        '''
        return self.__verticeOrigem

    def getVerticeDestino(self):
        '''
        Retorna o vertice de destino da aresta
        :return: Vertice
        '''
        return self.__verticeDestino

    def getOutraPonta(self, vertice):
        '''
        Dado um dos extremos da aresta, retorna o outro extremo
        :param vertice: Vertice
        :return: Vertice
        '''
        if vertice == self.__verticeOrigem:
            return self.__verticeDestino
        return self.__verticeOrigem

    def getPeso(self):
        '''
        Retorna o peso da aresta
        :return: indefinido (int, float, etc...)
        '''
        return self.__peso

    def direcionada(self):
        '''
        Retorna True se a aresta for direcionada
        :return: boolean
        '''
        return self.__direcionada

    def __chave(self):
        '''
        Chave usada para comparar arestas e gerar o hash
        Em arestas nao direcionadas (a, b) e (b, a) sao a mesma aresta
        '''
        origem = self.__verticeOrigem.getValor()
        destino = self.__verticeDestino.getValor()
        if self.__direcionada:
            return (origem, destino, self.__peso)
        return (frozenset((origem, destino)), self.__peso)

    def __lt__(self, outraAresta):
        '''
        Verifica se a aresta atual tem peso menor que uma dada aresta
        :param outraAresta: Aresta
        :return: boolean
        '''
        return self.__peso < outraAresta.getPeso()

    def __eq__(self, outraAresta):
        '''
        Duas arestas sao iguais se tem os mesmos extremos e o mesmo peso
        :param outraAresta: Aresta
        :return: boolean
        '''
        if not isinstance(outraAresta, Aresta):
            return NotImplemented
        return self.__chave() == outraAresta.__chave()

    def __hash__(self):
        '''
        Gera um hash a partir dos extremos e do peso da aresta
        :return: int
        '''
        return hash(self.__chave())
