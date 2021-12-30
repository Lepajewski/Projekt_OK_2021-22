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

inline bool exists(const std::string& name)
{
    std::ifstream f(name.c_str());
    return f.good();
}

int main(int args, char* argv[])
{
    int ver, edges, n_of_line, triangles, n_of_tests, max_triangles;
    ver = edges = n_of_line = triangles = n_of_tests = 0;
    std::string line;

    int **graphMatrix;
    int *histogram;

    for (int i = 1; i < args; i++)
    {
        std::fstream file;
        file.open(argv[i], std::ios::in);
        std::cout << "Current file: " << argv[i] << "\n";

        if (file.is_open())
        {
            while (getline(file, line) && n_of_line < 100001)
            {
                if (n_of_line == 0)
                {
                    ver = std::stoi(line.substr(0, line.find(" ")));
                    line.erase(0, line.find(" ") + 1);
                    edges = std::stoi(line.substr(0, line.find(" ")));
                    line.erase(0, line.find(" ") + 1);
                    n_of_tests = std::stoi(line);
                    max_triangles = MAX_TRIANGLES(ver);

                    histogram = new int [max_triangles + 1];
                    for (int j = 0; j <= max_triangles; j++)
                        histogram[j] = 0;

                    graphMatrix = new int *[ver];
                    for (int j = 0; j < ver; j++)
                    {
                        graphMatrix[j] = new int[ver];
                        for (int k = 0; k < ver; k++)
                            graphMatrix[j][k] = 0;
                    }
                }
                else
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

                    histogram[findTriangles(ver, graphMatrix)]++;

                    for (int i = 0; i < ver; i++)
                        for (int j = 0; j < ver; j++)
                            graphMatrix[i][j] = 0;
                }
                n_of_line++;
            }
        }
        bool br = 0;

        for (int j = 1; j < max_triangles; j++)
            if (histogram[j] == 0)
            {
                for (int k = 0; k < j && br == 0; k++)
                    if (histogram[k] > 0)
                        for (int l = j + 1; l <= max_triangles; l++)
                            if (histogram[l] > 0)
                            {
                                //wierzchołki | trójkąty, których nie może być | krawędzie
                                //std::cout << ver << " " <<  j << " " << edges << "\n";
                                std::fstream holes;
                                holes.open("../all_holes/all_holes.txt", std::ios::out | std::ios::app);

                                holes << ver << " " <<  j << " " << edges << "\n";

                                holes.close();
                                br = 1;
                                break;
                            }
                br = 0;
            }
        file.close();
        ver = edges = n_of_line = triangles = n_of_tests = 0;

    }

    for (int i = 0; i < ver; i++)
        delete [] graphMatrix[i];
    delete [] graphMatrix;
    delete histogram;
    std::cout << "Done!\n";

    return 0;
}
