#include <iostream>
using namespace std;

const int maxSz = 7;

int minKey(int key[], bool mstSet[]) {
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < maxSz; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

void printMST(int parent[], int graph[maxSz][maxSz]) {
    cout << "Edge    Weight" << endl;
    for (int i = 1; i < maxSz; i++)
        cout << parent[i] + 1 << " - " << i + 1 << " \t" << graph[i][parent[i]] << endl;
}
void primMST(int graph[maxSz][maxSz]) {
    int parent[maxSz];
    int key[maxSz];
    bool mstSet[maxSz];
    for (int i = 0; i < maxSz; i++){
        key[i] = INT_MAX, mstSet[i] = false;
    }
    key[0] = 0, parent[0] = -1;
    for (int i = 0; i < maxSz - 1; i++) {
        int j = minKey(key, mstSet);
        mstSet[j] = true;
        for (int k = 0; k < maxSz; k++)
            if (graph[j][k] && !mstSet[k] && graph[j][k] < key[k])
                parent[k] = j, key[k] = graph[j][k];
    }
    printMST(parent, graph);
}

int main() {
    int graph[7][7] = {{0, 2,  4, 1, 0,  0, 0},
                       {2, 0,  0, 3, 10, 0, 0},
                       {4, 0,  0, 2, 0,  5, 0},
                       {1, 3,  2, 0, 7,  8, 4},
                       {0, 10, 0, 7, 0,  0, 6},
                       {0, 0,  5, 8, 0,  0, 1},
                       {0, 0,  0, 4, 6,  1, 0}};
    primMST(graph);
}