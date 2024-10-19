#include "GraphArray.cpp"
#include "Stack.cpp"
#include <iostream>
using namespace std;

void Merge(int* data, int* index, int* auxData, int* auxIndex, int left, int mid, int right) {

    int i = left, j = mid + 1, k = left;

    for (int l = left; l <= right; ++l) {

        auxData[l] = data[l];
        auxIndex[l] = index[l];
    }

    while (i <= mid && j <= right) {

        if (auxData[i] >= auxData[j]) {

            data[k] = auxData[i];
            index[k] = auxIndex[i];
            ++i;
        } else {

            data[k] = auxData[j];
            index[k] = auxIndex[j];
            ++j;
        }
        ++k;
    }

    while (i <= mid) {

        data[k] = auxData[i];
        index[k] = auxIndex[i];
        ++i;
        ++k;
    }
    while (j <= right) {

        data[k] = auxData[j];
        index[k] = auxIndex[j];
        ++j;
        ++k;
    }
}

void MergeSort(int* data, int* index, int* auxData, int* auxIndex, int left, int right) {

    if (left < right) {
        int mid = left + (right - left) / 2;
        MergeSort(data, index, auxData, auxIndex, left, mid);
        MergeSort(data, index, auxData, auxIndex, mid + 1, right);
        Merge(data, index, auxData, auxIndex, left, mid, right);
    }
}

void MergeSortHelper(int* data, int* index, int n) {

    int* auxData = new int[n];
    int* auxIndex = new int[n];
    MergeSort(data, index, auxData, auxIndex, 0, n - 1);
    delete[] auxData;
    delete[] auxIndex;
}

void DFS(const GraphArray& graph, int v, bool* visited) {

    visited[v] = true;
    const int* neighbors = graph.GetAdjacentVertices(v);

    for (int i = 0; neighbors[i] != -1; ++i) {

        int neighbor = neighbors[i];

        if (!visited[neighbor]) {

            DFS(graph, neighbor, visited);
        }
    }
}

void ComplementEdges(const GraphArray& graph, int vertices) {

    long long edges = 0;

    for (int v = 0; v < vertices; ++v) {

        edges += graph.GetDegree(v);
    }

    edges /= 2;
    long long totalEdges = static_cast<long long>(vertices) * (vertices - 1) / 2;
    long long complementEdges = totalEdges - edges;

    std::cout << complementEdges << std::endl;
}

void C4Subgraphs(){

    std::cout << "?";
    std::cout << std::endl;
}

void ColoursSLF(){

    std::cout << "?";
    std::cout << std::endl;
}

void ColoursLF(const GraphArray& graph, int vertices){

    int* colors = new int[vertices];
    bool* availableColors = new bool[vertices + 1];
    int* degrees = new int[vertices];
    int* vertexOrder = new int[vertices];

    for (int v = 0; v < vertices; ++v) {

        degrees[v] = graph.GetDegree(v);
        vertexOrder[v] = v;
        colors[v] = -1;
    }

    MergeSortHelper(degrees, vertexOrder, vertices);

    for (int i = 0; i < vertices; ++i) {

        int v = vertexOrder[i];

        if(graph.GetDegree(v) == 0){
            colors[v] = 1;
            continue;
        }
        
        const int* neighbors = graph.GetAdjacentVertices(v);

        std::fill(availableColors, availableColors + vertices + 1, true);

        for (int j = 0; neighbors[j] != -1; ++j) {

            int neighborColor = colors[neighbors[j]];

            if (neighborColor != -1) {

                availableColors[neighborColor] = false;
            }
        }

        int cr;

        for (cr = 1; cr <= vertices; ++cr) {

            if (availableColors[cr]) break;
        }

        colors[v] = cr;
    }

    for (int i = 0; i < vertices; ++i) {

        std::cout << colors[i] << " ";
    }
    std::cout << std::endl;

    delete[] colors;
    delete[] availableColors;
    delete[] degrees;
    delete[] vertexOrder;
}

void ColoursGreedy(const GraphArray& graph, int vertices) {

    int* colors = new int[vertices];
    bool* availableColors = new bool[vertices + 1];

    for (int v = 0; v < vertices; ++v) {

        colors[v] = -1;
    }

    for (int v = 0; v < vertices; ++v) {

        if(graph.GetDegree(v) == 0){
            colors[v] = 1;
            continue;
        }

        const int* neighbors = graph.GetAdjacentVertices(v);

        for (int i = 1; i <= vertices; ++i) {

            availableColors[i] = true;
        }

        for (int i = 0; neighbors[i] != -1; ++i) {

            int neighborColor = colors[neighbors[i]];

            if (neighborColor != 0) {

                availableColors[neighborColor] = false;
            }
        }

        int cr;

        for (cr = 1; cr <= vertices; ++cr) {

            if (availableColors[cr]) break;
        }

        colors[v] = cr;
    }

    for (int i = 0; i < vertices; ++i) {

        cout << colors[i] << " ";
    }
    cout << endl;

    delete[] colors;
    delete[] availableColors;
}

void Planarity(){

    std::cout << "?";
    std::cout << std::endl;
}

void Eccentricity(){

    std::cout << "?";
    std::cout << std::endl;
}

bool IfBipartite(const GraphArray& graph, int src, int* colorArr) {

    Stack stack;
    stack.push(src);
    colorArr[src] = 1;

    while (!stack.isEmpty()) {

        int u = stack.pop();

        const int* neighbors = graph.GetAdjacentVertices(u);

        for (unsigned int i = 0; neighbors[i] != -1; ++i) {

            int v = neighbors[i];

            if (colorArr[v] == -1) {

                colorArr[v] = 1 - colorArr[u];
                stack.push(v);
            } else if (colorArr[v] == colorArr[u]) {

                return false;
            }
        }
    }
    return true;
}

void Bipartiteness(const GraphArray& graph, int vertices){

    int* colorArr = new int[vertices];

    for (int i = 0; i < vertices; ++i) {

        colorArr[i] = -1;
    }

    for (int i = 0; i < vertices; ++i) {

        if (colorArr[i] == -1) {

            if (!IfBipartite(graph, i, colorArr)) {

                std::cout << "F" << std::endl;
                delete[] colorArr;
                return;
            }
        }
    }

    std::cout << "T" << std::endl;
    delete[] colorArr;
}

void Components(const GraphArray& graph, int vertices) {

    bool* visited = new bool[vertices]();
    int componentCount = 0;

    for (int v = 0; v < vertices; ++v) {

        if (!visited[v]) {

            DFS(graph, v, visited);
            componentCount++;
        }
    }

    std::cout << componentCount << std::endl;
    delete[] visited;
}

void DegreeSequence(const GraphArray& graph, int vertices) {

    int* degreeList = new int[vertices];
    int* indices = new int[vertices];

    for (int i = 0; i < vertices; ++i) {

        degreeList[i] = graph.GetDegree(i);
        indices[i] = i;
    }

    MergeSortHelper(degreeList, indices, vertices);

    for (int i = 0; i < vertices; ++i) {
        
        std::cout << degreeList[i] << " ";
    }

    std::cout << std::endl;

    delete[] degreeList;
    delete[] indices;
}

int main() {

    long long int adjacents, adjacent;
    int k, n;

    std::cin >> k;

    for (int i = 0; i < k; ++i) {

        std::cin >> n;

        GraphArray graph(n);

        for (int j = 0; j < n; ++j) {

            std::cin >> adjacents;

            for (int p = 0; p < adjacents; ++p) {

                std::cin >> adjacent;

                graph.AddEdge(j, adjacent-1);
            }
        }

        DegreeSequence(graph, n);
        Components(graph, n);
        Bipartiteness(graph, n);
        Eccentricity();
        Planarity();
        ColoursGreedy(graph, n);
        ColoursLF(graph, n);
        ColoursSLF();
        C4Subgraphs();
        ComplementEdges(graph, n);
    }
return 0;
}