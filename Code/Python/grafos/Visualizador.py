import tempfile


def mostrarGrafo(grafo, tituloGrafo = None):
    '''
    Gera uma imagem do grafo usando pydot e graphviz
    Mostra a imagem gerada usando PIL (Python Image Library)
    Dependencias: pip install pydot pillow; e o Graphviz instalado no sistema
    '''
    import pydot  # importacoes locais: so sao exigidas quando a funcao e usada
    from PIL import Image

    tipoGrafo = "digraph" if grafo.direcionado() else "graph"
    pydotGrafo = pydot.Dot(graph_type = tipoGrafo)

    if tituloGrafo:
        pydotGrafo.set_label(tituloGrafo)

    # vertices
    for vertice in grafo.getVertices().values():
        no = pydot.Node(str(vertice.getValor()))
        no.set_style("filled")
        no.set_fillcolor("#CDE6D4")
        pydotGrafo.add_node(no)

    # arestas
    for aresta in grafo.getArestas():
        valorVerticeOrigem = str(aresta.getVerticeOrigem().getValor())
        valorVerticeDestino = str(aresta.getVerticeDestino().getValor())
        pydotAresta = pydot.Edge(valorVerticeOrigem, valorVerticeDestino)
        pydotAresta.set_label(str(aresta.getPeso()))
        pydotGrafo.add_edge(pydotAresta)

    with tempfile.NamedTemporaryFile(suffix = ".png") as temp:
        pydotGrafo.write_png(temp.name)
        image = Image.open(temp.name)
        image.load()
    image.show()
