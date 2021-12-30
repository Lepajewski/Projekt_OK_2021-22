#include <iostream>
#include <fstream>
#include <string>

int main(int args, char* argv[])
{
    int ver = atoi(argv[1]);
    std::string line;
    int model_no = 0;

    int **graphMatrix;

    graphMatrix = new int *[ver];
    for (int j = 0; j < ver; j++)
    {
        graphMatrix[j] = new int[ver];
        for (int k = 0; k < ver; k++)
            graphMatrix[j][k] = 0;
    }

    for (int v = 2; v < args; v++)
    {
        std::fstream file;
        file.open(argv[v], std::ios::in);

        if (file.good())
        {
            while (getline(file, line) && model_no < 50)
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
                std::fstream res;
                res.open("models_ready/" + std::to_string(ver) + "_" + std::to_string(model_no) + "_" + std::to_string(v - 2) + "_d.csv", std::ios::out);

                if (res.good())
                {
                    int i;
                    for (i = 0; i < ver - 1; i++)
                        res << (char) ('A'+i) << ',';
                    res << (char) ('A'+i) << '\n';

                    for (int i = 0; i < ver; i++)
                    {
                        res << (char) ('A'+i) << ',';
                        for (int j = 0; j < ver - 1; j++)
                            res << graphMatrix[i][j] << ',';
                        res << graphMatrix[i][ver-1] << '\n';
                    }
                }
                res.close();

                for (int k = 0; k < ver - 1; k++)
                {
                    for (int l = 1; l < ver - k; l++)
                    {
                        graphMatrix[l+k][k] = graphMatrix[k][l+k] = !graphMatrix[l+k][k];
                        idx++;
                    }
                }

                res.open("models_ready/" + std::to_string(ver) + "_" + std::to_string(model_no) + "_" + std::to_string(v - 2) + ".csv", std::ios::out);

                if (res.good())
                {
                    int i;
                    for (i = 0; i < ver - 1; i++)
                        res << (char) ('A'+i) << ',';
                    res << (char) ('A'+i) << '\n';

                    for (int i = 0; i < ver; i++)
                    {
                        res << (char) ('A'+i) << ',';
                        for (int j = 0; j < ver - 1; j++)
                            res << graphMatrix[i][j] << ',';
                        res << graphMatrix[i][ver-1] << '\n';
                    }
                }
                res.close();
                for (int i = 0; i < ver; i++)
                    for (int j = 0; j < ver; j++)
                        graphMatrix[i][j] = 0;
                model_no++;
            }

        }
        file.close();
        model_no = 0;
    }

    /*
    std::cout << "DOPEŁNIENIE:\n";
    for (int i = 0; i < ver; i++)
    {
        for (int j = 0; j < ver; j++)
            std::cout << graphMatrix[i][j] << " ";
        std::cout << "\n";
    }

    for (int k = 0; k < ver - 1; k++)
    {
        for (int l = 1; l < ver - k; l++)
        {
            graphMatrix[l+k][k] = graphMatrix[k][l+k] = !graphMatrix[l+k][k];
            idx++;
        }
    }

    std::cout << "GRAF:\n";
    for (int i = 0; i < ver; i++)
    {
        for (int j = 0; j < ver; j++)
            std::cout << graphMatrix[i][j] << " ";
        std::cout << "\n";
    }*/


    for (int i = 0; i < ver; i++)
        delete [] graphMatrix[i];
    delete [] graphMatrix;

    return 0;
}
