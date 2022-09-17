#include<iostream>
#include<set>
#include<fstream>
#include<vector>

bool dfs(int current_vertex, int** graph, int size, std::set<int>& visited, int previous_vertex) {
    visited.insert(current_vertex);
    for (int v = 0; v < size; v++) {
        if (graph[current_vertex][v]) {
            if (v == previous_vertex)
                continue;
            if (visited.find(v) != visited.end())
                return true;
            if (dfs(v, graph, size, visited, current_vertex))
                return true;
        }
    }
    return false;
}

bool hasCycle(int** graph, int size) {
    std::set<int> visited;
    for (int v = 0; v < size; v++) {
        if (visited.find(v) != visited.end())
            continue;
        if (dfs(v, graph, size, visited, -1)) {
            return true;
        }
    }
    return false;
}

void read_file(std::vector<int>& matrix_doc)
{
    int buffer;
    std::ifstream fin; 
    fin.open("input.txt");
    if (fin.is_open())
    {
        while (!fin.eof())
        {
            fin >> buffer;
            matrix_doc.push_back(buffer);
        }
    }
    fin.close();
}

int main()
{
    std::vector<int> matrix_doc;
    read_file(matrix_doc);

    int size = sqrt(matrix_doc.size());

    int buffer = 0;
    int** graph = new int* [size];

    for (int row = 0; row < size; row++)
        graph[row] = new int[size];

    for (int row = 0; row < size; row++)
    {
        for (int column = 0; column < size; column++)
        {
            graph[row][column] = matrix_doc[buffer];
            buffer++;
        }
    }

    if (hasCycle(graph, size))
        std::cout << "Cyclic" << std::endl;
    else
        std::cout << "Acyclic" << std::endl;

    for (int rows = 0; rows < size; rows++)
        delete[] graph[rows];
    delete[] graph;
}