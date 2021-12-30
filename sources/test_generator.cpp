#include <iostream>
#include <string>
#include <fstream>

#define MAX_EDGES(n) (0.5 * n * (n - 1))

void clear_matrix(int ver, int **mat)
{
    for (int i = 0; i < ver; i++)
        for (int j = 0; j < ver; j++)
            mat[i][j] = 0;
}

void fill_matrix(int n, int e, int **mat)
{
    int x = 0, y = 0, edgesLeft = e;

    while (edgesLeft > 0)
    {
        while (x <= y || mat[x][y] == 1)
        {
            x = rand() % n;
            y = rand() % n;
        }
        mat[x][y] = mat[y][x] = 1;
        x = y = -1;
        edgesLeft--;
    }
}

int main()
{
    srand(time(NULL));
    int ver, n_of_tests, max_edges;
    int **graphMatrix;

    std::cin >> n_of_tests >> ver;

    max_edges = MAX_EDGES(ver);

    graphMatrix = new int *[ver];
    for (int i = 0; i < ver; i++)
    {
        graphMatrix[i] = new int[ver];
        for (int j = 0; j < ver; j++)
            graphMatrix[i][j] = 0;
    }

    clear_matrix(ver, graphMatrix);

    for (int i = 3; i <= max_edges; i++)
    {
        std::fstream file;
        std::string path = "/run/media/lukaszk/SSD/new_tests/" + std::to_string(ver) + "_" + std::to_string(i) + ".txt";
        std::cout << "Current file: " << path << "\n";
        file.open(path, std::ios::out);
        file << ver << " " << i << " " << n_of_tests << "\n";

        if (file.is_open())
        {
            for (int j = 0; j < n_of_tests; j++)
            {
                fill_matrix(ver, i, graphMatrix);

                for (int k = 0; k < ver - 1; k++)
                {
                    for (int l = 1; l < ver - k; l++)
                        file << graphMatrix[k][l+k];
                }
                file << "\n";
                clear_matrix(ver, graphMatrix);
            }
        }
        file.close();
    }


    for (int i = 0; i < ver; i++)
        delete [] graphMatrix[i];
    delete [] graphMatrix;
    std::cout << "Done!\n";

    return 0;
}
