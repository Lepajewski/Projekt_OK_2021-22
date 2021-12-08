#pragma once

class Graph
{
    unsigned int vertices; //liczba wierzcholkow
    unsigned int edges; //liczba krawedzi
    int **graphMatrix; //macierz grafu
    unsigned int maxTriangles;
    unsigned int maxEdges;

    unsigned int maxNumberOfTriangles(unsigned int n);
    unsigned int maxNumberOfEdges(unsigned int n);

public:
    Graph(unsigned int n, unsigned int e);
    ~Graph();

    void fillGraph(unsigned int e);
    void drawGraphMatrix();
    int findTriangles();
    void clearGraphMatrix();

    //accessors
    unsigned int getMaxTriangles();
    unsigned int getMaxEdges();
};
