#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include "headers/graph.h"

Graph::Graph(unsigned int n, unsigned int e)
{
    vertices = n;
    edges = e;
    maxTriangles = maxNumberOfTriangles(n);
    maxEdges = maxNumberOfEdges(n);

    graphMatrix = new int *[n];
    for (int i = 0; i < n; i++)
    {
        graphMatrix[i] = new int[n];
        for (int j = 0; j < n; j++)
            graphMatrix[i][j] = 0;
    }
}

Graph::~Graph()
{
    for (int i = 0; i < vertices; i++)
        delete [] graphMatrix[i];
    delete [] graphMatrix;
}

void Graph::fillGraph(unsigned int e)
{
    unsigned int x, y, edgesLeft = e;

    while (edgesLeft > 0)
    {
        while (x <= y || graphMatrix[x][y] == 1)
        {
            x = rand() % vertices;
            y = rand() % vertices;
        }

        graphMatrix[x][y] = graphMatrix[y][x] = 1;
        x = y = -1;
        edgesLeft--;
    }
}

void Graph::drawGraphMatrix()
{
    printf("     ");
    for (int i = 0; i < vertices; i++)
        printf("%3d ", i);
    printf("\n\n");

    for (int i = 0; i < vertices; i++)
    {
        printf("%3d  ", i);
        for (int j = 0; j < vertices; j++)
            printf("%3d ", graphMatrix[i][j]);
        printf("\n");
    }
}

int Graph::findTriangles()
{
    int n = 0;

    for (int i = 0; i < vertices - 2; i++)
        for (int j = i + 1; j < vertices - 1; j++)
            if (graphMatrix[i][j])
                for (int k = j + 1; k < vertices; k++)
                    if (graphMatrix[k][i] && graphMatrix[j][k])
                        n++;
    return n;
}

unsigned int Graph::maxNumberOfTriangles(unsigned int n)
{
    return ((n * (n - 1) * (n - 2)) / 6);
}

unsigned int Graph::maxNumberOfEdges(unsigned int n)
{
    return (n * (n - 1) * 0.5);
}

unsigned int Graph::getMaxTriangles()
{
    return maxTriangles;
}

unsigned int Graph::getMaxEdges()
{
    return maxEdges;
}

void Graph::clearGraphMatrix()
{
    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            graphMatrix[i][j] = 0;
}
