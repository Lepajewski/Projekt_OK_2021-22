#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include "headers/graph.h"

#define MAX_EDGES(n) (0.5 * n * (n - 1))
#define MAX_TRIANGLES(n) ((n * (n - 1) * (n - 2)) / 6)

int main()
{
    srand(time(NULL));
    unsigned int N_OF_TESTS = 0;
    unsigned int VER = 0;
    unsigned int edges = 0;
    unsigned int triangles = 0;
    unsigned int maxTriangles = 0;
    double *histogram;
    double saturation;
    clock_t start, end;
    Graph *g;

    scanf("%u\n%u", &N_OF_TESTS, &VER);

    edges = MAX_EDGES(VER);
    maxTriangles = MAX_TRIANGLES(VER);

    printf("%u\n%u\n%u\n\n", VER, edges, maxTriangles);

    start = clock();

    for (unsigned int i = 3; i <= edges; i++)
    {
        g = new Graph(VER, i);
        maxTriangles = g->getMaxTriangles();

        histogram = new double[maxTriangles];
        for (unsigned int j = 0; j < maxTriangles; j++)
            histogram[j] = 0;

        for (unsigned int j = 0; j < N_OF_TESTS; j++)
        {
            g->fillGraph(i);
            triangles = g->findTriangles();

            //g->drawGraphMatrix();
            //printf("Trójkątów: %d\n", g->findTriangles());
            //printf("test: %2d, ver: %2d, sat: %.3lf | trian: %3d, max_trian: %4u\n", j, i, sat, triangles, maxTriangles);
            histogram[triangles]++;
            triangles = 0;
            g->clearGraphMatrix();
        }
        saturation = (double) i / (double) edges;

        for (unsigned int j = 0; j <= maxTriangles; j++)
        {
            histogram[j] /= N_OF_TESTS;

            //printf("%.9lf  %.9lf  %.9lf\n", (double) j / (double) maxTriangles, histogram[j], saturation);
            //X: %uzyskanych trójkątów
            //Y: prawdopodobieństwo, że wypadło n trójkątów
            //Z: %nasycenia grafu

            //X: liczba trójkątów uzyskana w grafie w N_OF_TESTS próbach
            //Y: prawdopodobieństwo wystąpienia x trójkątów w grafie o \binom{n}{3} maksymalnych trójkątów i n wierzchołkach
            //Z: nasycenie krawędziami dla zadanego grafu o n wierzchołkach
        }
        //printf("\n\n");

        maxTriangles = 0;
        delete [] histogram;
        delete g;
    }

    end = clock();

    printf("%lf", ((double) (end - start)) / CLOCKS_PER_SEC);
    //delete g;

    return 0;
}
