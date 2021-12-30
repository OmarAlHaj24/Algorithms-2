#include <iostream>
using namespace std;

const int N = 100;
int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < N; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
    return min_index;
}

int dijkstra(int graph[N][N], int src, int target) {
    int dist[N];
    bool sptSet[N];
    for (int i = 0; i < N; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
    dist[src] = 0;
    for (int count = 0; count < N - 1; count++) {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < N; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
    return dist[target];
}

int main() {
    int t; cin >> t; //number of test cases
    int cnt = 0;
    while (t--) {
        int n, m, s, d; cin >> n >> m >> s >> d; //number of servers, number of routes, source, destination
        int graph[N][N];
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                graph[i][j] = 0;
            }
        }
        for (int i = 0; i < m; i++) {
            int x, y, z; cin >> x >> y >> z;
            graph[x][y] = z;
            graph[y][x] = z;
        }
        int ans = dijkstra(graph, s, d);
        if(ans != INT_MAX){
            cout << "Case #" << ++cnt << ": " << ans  << endl;
        }else{
            cout << "Case #" << ++cnt << ": unreachable" << endl;
        }
    }
}