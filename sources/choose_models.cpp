#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

#define MAX_TRIANGLES(n) ((n * (n - 1) * (n - 2)) / 6)

int findTriangles(int ver, int **mat)
{
    int n = 0;

    for (int i = 0; i < ver - 2; i++)
        for (int j = i + 1; j < ver - 1; j++)
            if (mat[i][j])
                for (int k = j + 1; k < ver; k++)
                    if (mat[k][i] && mat[j][k])
                        n++;
    return n;
}

void DFS(int u, bool visited[], int **mat, int ver)
{
    visited[u] = 1;
    for (int v = 0; v < ver; v++)
        if (mat[u][v] && !visited[v])
            DFS(v, visited, mat, ver);
}

int checkConnected(int **mat, int ver)
{
    int n = 0;
    bool *vis = new bool[ver];

    for (int v = 0; v < ver; v++)
        vis[v] = 0;
    for (int v = 0; v < ver; v++)
        if (!vis[v])
        {
            DFS(v, vis, mat, ver);
            n++;
        }
    return n;
}

int main(int args, char* argv[])
{
    int ver, edges, n_of_line, triangles, n_of_tests, models = 0;
    ver = edges = n_of_line = triangles = n_of_tests = 0;
    std::string line;

    int **graphMatrix;
    std::fstream holes;
    holes.open(argv[1], std::ios::in);

    if (holes.good())
    {
        while (getline(holes, line))
        {
            ver = std::stoi(line.substr(0, line.find(" ")));
            line.erase(0, line.find(" ") + 1);
            triangles = std::stoi(line.substr(0, line.find(" ")));
            line.erase(0, line.find(" ") + 1);
            edges = std::stoi(line);

            //std::string path = "../tests/" + std::to_string(ver) + "_" + std::to_string(edges) + ".txt";
            std::string path = "/run/media/lukaszk/SSD/new_tests/" + std::to_string(ver) + "_" + std::to_string(edges) + ".txt";
            std::cout << "Current file: " << path << "\n";
            std::fstream test;
            test.open(path, std::ios::in);
            graphMatrix = new int *[ver];
            for (int j = 0; j < ver; j++)
            {
                graphMatrix[j] = new int[ver];
                for (int k = 0; k < ver; k++)
                    graphMatrix[j][k] = 0;
            }

            if (test.good())
            {
                getline(test, line);
                while (getline(test, line))
                {
                    int idx = 0;
                    for (int k = 0; k < ver - 1; k++)
                    {
                        for (int l = 1; l < ver - k; l++)
                        {
                            graphMatrix[l+k][k] = graphMatrix[k][l+k] = line[idx] - '0';
                            idx++;
                        }
                    }

                    if (findTriangles(ver, graphMatrix) == 0)
                    {
                        for (int k = 0; k < ver - 1; k++)
                        {
                            for (int l = 1; l < ver - k; l++)
                            {
                                graphMatrix[l+k][k] = graphMatrix[k][l+k] = !graphMatrix[l+k][k];
                                idx++;
                            }
                        }

                        if (checkConnected(graphMatrix, ver) == 1)
                        {
                            path = "../models/" + std::to_string(ver) + "_" + std::to_string(edges) + ".txt";
                            std::fstream model;
                            model.open(path, std::ios::app);

                            for (int k = 0; k < ver - 1; k++)
                                for (int l = 1; l < ver - k; l++)
                                    model << graphMatrix[l+k][k];
                            models++;
                            model << "\n";
                            model.close();
                            /* All holes (so far):
                            5 3 6
                            6 3 6
                            6 1 9
                            6 6 9
                            6 8 10
                            6 9 10
                            6 9 11
                            7 3 6
                            7 6 9
                            7 8 10
                            7 9 10
                            7 9 11
                            7 1 12
                            7 14 14
                            7 15 14
                            7 15 15
                            7 17 15
                            7 18 15
                            7 19 15
                            7 18 16
                            7 19 16
                            7 20 17
                            */
                        }
                    }


                    for (int i = 0; i < ver; i++)
                        for (int j = 0; j < ver; j++)
                            graphMatrix[i][j] = 0;
                }
            }
            n_of_line = 0;
            test.close();
        }
    }
    holes.close();

    for (int i = 0; i < ver; i++)
        delete [] graphMatrix[i];
    delete [] graphMatrix;
    std::cout << "Modeli: " << models << "\n";
    std::cout << "Done!\n";

    return 0;
}
