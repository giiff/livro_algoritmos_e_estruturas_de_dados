class Vertice:
    '''
    Classe Vertice
    Representa um verticeLabel de um grafo
    Cada verticeLabel, tem 3 atributos:
        valor: valor do verticeLabel
        direcionado: Treu ou False para identificar se as arestas que eventualmente incidam no verticeLabel sera direcionadas ou nao
        arestas: um conjunto de arestas
    '''
    def __init__(self, valor, direcionado = True):
        '''
        Metodo construtor da classe Vertice
        :param valor: indefinido (str, int, etc...)
        :param direcionado: boolean
        '''
        self.__valor = valor
        self.__direcionado = direcionado
        self.__arestas = set()

    # def __str__(self):
    #     '''
    #     Método __str__ converte o objeto da classe para um formato string impimivel
    #     :return: str
    #     '''
    #     arestasDeSaida = ""
    #     for aresta in self.getArestasSaida():
    #         arestasDeSaida += str(aresta) + ", "
    #     arestasDeEntrada = ""
    #     for aresta in self.getArestasEntrada():
    #         arestasDeEntrada += str(aresta) + ", "
    #     return "{0} --> {1} --> {2}\n".format(arestasDeEntrada, self.__valor,arestasDeSaida)

    def getArestasSaida(self):
        '''
        Retorna uma lista com as arestas que saem do verticeLabel
        :return: list
        '''
        # lista vazia quando o verticeLabel nao e parte de um grafo direcionado
        if self.__direcionado == False:
            return self.__arestas
        # lista com arestas que saem do verticeLabel
        arestasDeSaida = []
        for aresta in self.__arestas: # percorre todas as arestas
            if aresta.getVerticeOrigem() == self: # verifica quais arestas estao saindo verticeLabel
                arestasDeSaida.append(aresta) # adiciona cada aresta que sai
        return arestasDeSaida

    def getArestasEntrada(self):
        '''
        Retorna uma lista com as arestas que entram do verticeLabel
        :return: list
        '''
        # lista vazia quando o verticeLabel nao e parte de um grafo direcionado
        if self.__direcionado == False:
            return self.__arestas
        # lista com arestas que entram do verticeLabel
        arestasDeEntrada = []
        for aresta in self.__arestas: # percorre todas as arestas
            if aresta.getVerticeDestino() == self: # verifica quais arestas estao saindo verticeLabel
                arestasDeEntrada.append(aresta) # adiciona cada aresta que sai
        return arestasDeEntrada

    def getArestas(self):
        '''
        Retorna o conjunto de arestas do verticeLabel (entradas e saidas)
        :return:
        '''
        return self.__arestas

    def getValor(self):
        '''
        retorna o valor do verticeLabel
        :return:
        '''
        return self.__valor

    def adicionarAresta(self, aresta):
        '''
        Adiciona uma nova aresta no conjunto de arestas do verticeLabel
        :param aresta: Aresta
        :return: void
        '''
        self.__arestas.add(aresta)

    def removerAresta(self, aresta):
        '''
        Remove uma dada aresta do conjunto de arestas do verticeLabel
        :param aresta: Aresta
        :return: void
        '''
        if aresta in self.__arestas:
            self.__arestas.remove(aresta)
        else:
            raise ValueError(
                "Nao foi possivel encontrar a aresta {0} no verticeLabel {1}".format(str(aresta), str(self)))

    def __eq__(self, outroVertice):
        '''
        Compara dois vertices
        :param outroVertice: Vertice
        :return: boolean
        '''
        return self.__valor == outroVertice.getValor()

    def __hash__(self):
        '''
        Gera um hash a partir do valor do verticeLabel
        :return: str
        '''
        return hash(self.getValor())
