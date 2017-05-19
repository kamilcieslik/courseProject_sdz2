//
// Created by mrfarinq on 13.05.17.
//

#include "UsefulStructuresForAlgorithms.h"

Heap::Heap() {
    arrayOfEdges = new Edge[0];
    this->numberOfEdges = 0;
}

Heap::~Heap() {
    delete[] arrayOfEdges;
    numberOfEdges = 0;
    arrayOfEdges = nullptr;
}

Edge Heap::GetEdgeFromTheBeginning() {
    return arrayOfEdges[0];
}

void Heap::AddEdge(Edge newEdge, int edge_weight) {
    
    Edge *temporaryTable;
    temporaryTable = new Edge[numberOfEdges + 1];
    for (int i = 0; i < numberOfEdges; i++) {
        temporaryTable[i] = arrayOfEdges[i];
    }
    delete[] arrayOfEdges;
    arrayOfEdges = temporaryTable;
    
    int i, j;
    i = numberOfEdges++;
    j = (i - 1) / 2;
    
    while (i && arrayOfEdges[j].edge_weight > edge_weight) {
        arrayOfEdges[i] = arrayOfEdges[j];
        i = j;
        j = (i - 1) / 2;
    }
    
    arrayOfEdges[i] = newEdge;
}

void Heap::DeleteEdgeFromTheTop() {
    if (numberOfEdges == 0) {
        throw std::underflow_error("Kopiec jest pusty.");
    }
    
    int i, j;
    Edge lastLeaf;
    
    if (numberOfEdges) {
        lastLeaf = arrayOfEdges[--numberOfEdges];
        
        i = 0;
        j = 1;
        
        while (j < numberOfEdges) {
            if ((j + 1 < numberOfEdges) && (arrayOfEdges[j + 1].edge_weight < arrayOfEdges[j].edge_weight)) j++;
            if (lastLeaf.edge_weight <= arrayOfEdges[j].edge_weight) {
                break;
            }
            arrayOfEdges[i] = arrayOfEdges[j];
            i = j;
            j = 2 * j + 1;
        }
        
        arrayOfEdges[i] = lastLeaf;
        
        Edge *temporaryTable;
        temporaryTable = new Edge[numberOfEdges];
        for (auto k = 0; k < numberOfEdges; k++) {
            temporaryTable[k] = arrayOfEdges[k];
        }
        delete[]arrayOfEdges;
        arrayOfEdges = temporaryTable;
    }
}

int Heap::getAmountOfEdges() {
    return numberOfEdges;
}


void Edge::AddEdge(int vertex_from, int vertex_to, int edge_weight) {
    this->vertex_from = vertex_from;
    this->vertex_to = vertex_to;
    this->edge_weight = edge_weight;
}



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
