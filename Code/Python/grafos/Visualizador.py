from .Grafo import Grafo
from PIL import Image
import pydot
import tempfile

def mostrarGrafo(grafo, tituloGrafo = None):
    '''
    Gera uma imagem do grafo usando pydot e graphviz
    Mostra a imagem gerada usando PIL (Python Image Library)
    '''
    tipoGrafo = "digraph" if grafo.direcionado() else "grafo"
    pydotGrafo = pydot.Dot(graph_type = tipoGrafo)

    if tituloGrafo:
        pydotGrafo.set_label(tituloGrafo)

    # vertices
    for vertice in grafo.getVertices().values():
        no = pydot.Node(vertice.getValor())
        no.set_style("filled")
        no.set_fillcolor("#CDE6D4")
        pydotGrafo.add_node(no)

    # arestas
    for aresta in grafo.getArestas():
        valorVerticeOrigem = aresta.getVerticeOrigem().getValor()
        valorVerticeDestino = aresta.getVerticeDestino().getValor()
        peso = str(aresta.getPeso())
        pydotAresta = pydot.Edge(valorVerticeOrigem, valorVerticeDestino)
        pydotAresta.set_label(peso)
        pydotGrafo.add_edge(pydotAresta)

    temp = tempfile.NamedTemporaryFile()
    pydotGrafo.write_png(temp.name)
    image = Image.open(temp.name)
    temp.close()
    image.show()
