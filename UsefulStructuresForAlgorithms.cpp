//
// Created by mrfarinq on 13.05.17.
//

#include "UsefulStructuresForAlgorithms.h"

//---------------------------------------------------------------------------
// Kolejka na bazie kopca na użytek algorytmów problemu MST.
//---------------------------------------------------------------------------
Edge::Edge() : vertex_from(0), vertex_to(0), edge_weight(0) {
};

Edge::Edge(int _vertex_from, int _vertex_to, int _edge_weight) : vertex_from(_vertex_from), vertex_to(_vertex_to),
                                                                 edge_weight(_edge_weight) {
};

Heap::Heap(int size) : numberOfEdges(0) {
    arrayOfEdges = new Edge[size];
    this->size = size;
}

Heap::~Heap() {
    delete[] arrayOfEdges;
    numberOfEdges = 0;
    size = 0;
    arrayOfEdges = nullptr;
}

void Heap::PushEdge(Edge newEdge) {
    if (numberOfEdges > size)
        throw std::overflow_error("Brak miejsca w kopcu.");
    int i, j;
    i = numberOfEdges++;
    j = (i - 1) / 2;
    while (i && arrayOfEdges[j].edge_weight > newEdge.edge_weight) {
        arrayOfEdges[i] = arrayOfEdges[j];
        i = j;
        j = (i - 1) / 2;
    }
    arrayOfEdges[i] = newEdge;
}

Edge Heap::PopEdge() {
    if (numberOfEdges == 0)
        throw std::underflow_error("Kopiec jest pusty.");

    int i, j;
    Edge lastLeaf;
    Edge top = arrayOfEdges[0];

    lastLeaf = arrayOfEdges[--numberOfEdges];

    i = 0;
    j = 1;

    while (j < numberOfEdges) {
        if ((j + 1 < numberOfEdges) && (arrayOfEdges[j + 1].edge_weight < arrayOfEdges[j].edge_weight))
            j++;
        if (lastLeaf.edge_weight <= arrayOfEdges[j].edge_weight)
            break;
        arrayOfEdges[i] = arrayOfEdges[j];
        i = j;
        j = 2 * j + 1;
    }

    arrayOfEdges[i] = lastLeaf;
    return top;
}




//---------------------------------------------------------------------------
// Kolejka na bazie kopca na użytek algorytmu Dijkstry dla problemu SP.
//---------------------------------------------------------------------------
void Vertex::AddVertex(int vertex, int distanceFromFirstVertex) {
    this->vertex = vertex;
    this->distanceFromFirstVertex = distanceFromFirstVertex;
}

HeapForVertices::HeapForVertices(int size) : amountOfVertices(0) {
    arrayOfVertices = new Vertex[size];
    this->size = size;
}

HeapForVertices::~HeapForVertices() {
    delete[] arrayOfVertices;
    amountOfVertices = 0;
    size = 0;
    arrayOfVertices = nullptr;
}

Vertex HeapForVertices::GetVertexFromTheBeginning() {
    return arrayOfVertices[0];
}

void HeapForVertices::AddVertex(Vertex newVertex, int vertex_distanceFromFirstVertex) {
    int i, j;
    i = amountOfVertices++;
    j = (i - 1) / 2;

    while (i && arrayOfVertices[j].distanceFromFirstVertex > vertex_distanceFromFirstVertex) {
        arrayOfVertices[i] = arrayOfVertices[j];
        i = j;
        j = (i - 1) / 2;
    }

    arrayOfVertices[i] = newVertex;
}

void HeapForVertices::DeleteVertexFromTheTop() {
    if (amountOfVertices == 0) {
        throw std::underflow_error("Kopiec jest pusty.");
    }

    int i, j;
    Vertex lastLeaf;

    if (amountOfVertices) {
        lastLeaf = arrayOfVertices[--amountOfVertices];

        i = 0;
        j = 1;

        while (j < amountOfVertices) {
            if ((j + 1 < amountOfVertices) &&
                (arrayOfVertices[j + 1].distanceFromFirstVertex < arrayOfVertices[j].distanceFromFirstVertex))
                j++;
            if (lastLeaf.distanceFromFirstVertex <= arrayOfVertices[j].distanceFromFirstVertex) {
                break;
            }
            arrayOfVertices[i] = arrayOfVertices[j];
            i = j;
            j = 2 * j + 1;
        }

        arrayOfVertices[i] = lastLeaf;
    }
}

int HeapForVertices::getAmountOfVertices() {
    return amountOfVertices;
}

void HeapForVertices::changeDistanceFromFirstVertex(int vertex, int vertex_distanceFromFirstVertex) {
    int index;
    for (auto i = 0; i < amountOfVertices; i++) {
        if (arrayOfVertices[i].vertex == vertex) {
            index = i;
            arrayOfVertices[i].distanceFromFirstVertex = vertex_distanceFromFirstVertex;
            break;
        }
    }

    int i = index;
    int j = (i - 1) / 2;
    while (i && arrayOfVertices[j].distanceFromFirstVertex > arrayOfVertices[i].distanceFromFirstVertex) {
        Vertex tmpVertex = arrayOfVertices[i];
        arrayOfVertices[i] = arrayOfVertices[j];
        arrayOfVertices[j] = tmpVertex;
        i = j;
        j = (i - 1) / 2;
    }
}




//---------------------------------------------------------------------------
// Implementacja zbiorów rozłącznych na potrzeby algorytmu Kruskala dla problemu MST.
//---------------------------------------------------------------------------
DisjointSetDataStructure::DisjointSetDataStructure(int numberOfNodes) {
    disjointSetTree = new DisjointSetDataStructure::NodeOfDisjointSetDataStructure[numberOfNodes];
}

DisjointSetDataStructure::~DisjointSetDataStructure() {
    delete[] disjointSetTree;
}

/*
 * Na początku każdy z elementów tworzy osobny zbiór, w którym jest reprezentanem (ojcem).
 * Koszt przejścia do reprezentanta (samego siebie) równy zero.
 */
void DisjointSetDataStructure::Init(int vertex) {
    disjointSetTree[vertex].parent = vertex;
    disjointSetTree[vertex].rank = 0;
}

/*
 * Wyszukiwanie reprezentanta + kompresja ścieżek.
 * Wszystkie elementy zostaną podłączone "bezpośrednio" do reprezentanta zbioru -> skrócenie czasu wyszukiwania.
 */
int DisjointSetDataStructure::FindParent(int vertex) {
    if (disjointSetTree[vertex].parent != vertex)
        disjointSetTree[vertex].parent = FindParent(
                disjointSetTree[vertex].parent);
    return disjointSetTree[vertex].parent;
}

/*
 * Łączenie zbiorów.
 * W funkcji odbywa się wybór kierunku łączenia.
 * Różne rangi: zbiór niższy do wyższego -> brak zmian rangi, wysokość drzewa nie zmienia się.
 * Rangi równe: wysokość jednego ze zbiorów zwiększa się o jeden -> zwiększenie rangi.
 */
void DisjointSetDataStructure::Union(int vertex_from, int vertex_to) {
    int parent_vertex_from = FindParent(vertex_from);
    int parent_vertex_to = FindParent(vertex_to);
    if (disjointSetTree[parent_vertex_from].rank < disjointSetTree[parent_vertex_to].rank) {
        disjointSetTree[parent_vertex_from].parent = parent_vertex_to;
    } else {
        disjointSetTree[parent_vertex_to].parent = parent_vertex_from;
    }

    if (disjointSetTree[parent_vertex_from].rank == disjointSetTree[parent_vertex_to].rank) {
        disjointSetTree[parent_vertex_from].rank += 1;
    }
}
