#include "GraphArray.h"
#include <iostream>
#include <cstring>

GraphArray::GraphArray(unsigned int vertices) : vertices(vertices) {

    array = new int*[vertices];
    adjacents = new unsigned int[vertices]();
    
    for (unsigned int i = 0; i < vertices; ++i) {
        array[i] = new int[2];
        array[i][0] = -1;
    }
}

GraphArray::~GraphArray() {

    for (unsigned int i = 0; i < vertices; ++i) {

        delete[] array[i];
    }

    delete[] array;
    delete[] adjacents;
}

void GraphArray::AddEdge(int u, int v) {
    
    if (adjacents[u] % 2 == 0) {

        int newSize = adjacents[u] + 2;
        int* newAdjList = new int[newSize + 1];
        std::memcpy(newAdjList, array[u], adjacents[u] * sizeof(int));
        delete[] array[u];
        array[u] = newAdjList;
    }

    array[u][adjacents[u]] = v;
    adjacents[u]++;
    array[u][adjacents[u]] = -1;
}

const int* GraphArray::GetAdjacentVertices(int vertex) const {
    
    return array[vertex];
}

unsigned int GraphArray::GetDegree(int vertex) const {
    
    return adjacents[vertex];
}

// unsigned int GraphArray::GetNumVertices() const {

//     return vertices;
// }