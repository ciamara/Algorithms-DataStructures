#ifndef GRAPHARRAY_H
#define GRAPHARRAY_H

class GraphArray {
    private:

        int** array;
        unsigned int* adjacents;
        unsigned int vertices;

        void resize();

    public:
    
        GraphArray(unsigned int vertices);
        ~GraphArray();
        void AddEdge(int u, int v);
        const int* GetAdjacentVertices(int vertex) const;
        unsigned int GetDegree(int vertex) const;
};

#endif