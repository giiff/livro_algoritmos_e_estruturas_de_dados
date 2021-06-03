class Aresta:
    '''
    Classe Aresta
    representa uma aresta de um grafo, pode ser direcionado ou nao
    '''
    def __init__(self, verticeOrigem, verticeDestino, peso = 1, direcionada = True):
        '''
        :param verticeOrigem: Vertice
        :param verticeDestino: Vertice
        :param peso: indefidido (int, float, etc...)
        :param direcionada: boolean
        '''
        self.__verticeOrigem = verticeOrigem
        self.__verticeDestino = verticeDestino
        self.__peso = peso
        self.__direcionada = direcionada

    def __str__(self):
        '''
        Método __str__ converte o objeto da classe para um formato string impimivel
        :return: str
        '''
        if self.__direcionada:
            padraoDeImpressao = "{0} |-{1}-> {2}"
        else:
            padraoDeImpressao = "{0} <-{1}-> {2}"
        return padraoDeImpressao.format(self.__verticeOrigem.getValor(), self.__peso, self.__verticeDestino.getValor())

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

    def getPeso(self):
        '''
        Retorna o peso da aresta
        :return:
        '''
        return self.__peso

    def __lt__(self, outraAresta):
        '''
        Verifica se uma dada aresta tem peso maior que a aresta atual
        :param outraAresta: Aresta
        :return: boolean
        '''
        return self.__peso < outraAresta.getPeso()

    def __eq__(self, outraAresta):
        '''
        Compara se duas arestas tem o mesmo peso
        :param outraAresta: Aresta
        :return: boolean
        '''
        pesoIgual = self.__peso == outraAresta.getPeso()
        verticeOrigemIgual = self.__verticeOrigem == outraAresta.getVerticeOrigem()
        verticeDestinoIgual = self.__verticeDestino == outraAresta.getVerticeDestino()
        return pesoIgual == verticeOrigemIgual == verticeDestinoIgual == True

    def __hash__(self):
        '''
        Gera um hash a partir do valor do vertice
        :return: str
        '''
        return hash(self.__verticeOrigem.getValor() +
                    self.__verticeDestino.getValor() + str(self.__peso))
