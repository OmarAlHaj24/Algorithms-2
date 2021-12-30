#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const long long OO = 1e18;

struct UnionFind {
    vector<int> rank, parent;
    int forests;

    UnionFind(int n) {
        rank = vector<int>(n), parent = vector<int>(n);
        forests = n;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
    }
    int find_set(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find_set(parent[x]);
    }
    void link(int x, int y) {
        if (rank[x] > rank[y]) swap(x, y);
        parent[x] = y;

        if (rank[x] == rank[y]) rank[y]++;
    }
    bool union_sets(int x, int y) {
        x = find_set(x), y = find_set(y);

        if (x != y) {
            link(x, y);
            forests--;
        }
        return x != y;
    }
};

struct edge {
    int from, to, w;
    edge(int from, int to, int w) : from(from), to(to), w(w) {}
    bool operator<(const edge &e) const {
        //return w > e.w;
        if (w > e.w) {
            return true;
        } else if (w == e.w) {
            if (from + to + w > e.from + e.to + e.w) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
};

pair<int, vector<edge> > MST_Kruskal(vector<edge> edgeList, int n) {
    UnionFind uf(n);
    vector<edge> edges;
    int mstCost = 0;
    priority_queue<edge> q;
    for (int i = 0; i < edgeList.size(); i++)
        q.push(edgeList[i]);
    while (!q.empty()) {
        edge e = q.top();
        q.pop();
        if (uf.union_sets(e.from, e.to)) {
            mstCost += e.w;
            edges.push_back(e);
        }
    }
    if (edges.size() != n - 1)
        return make_pair(-OO, vector<edge>());
    return make_pair(mstCost, edges);
}

int main() {
    vector<edge> edgeList;
    int n, m;
    cin >> n >> m; //n is the number of nodes, m is the number of edges.
    for (int i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        edgeList.push_back(edge(x - 1, y - 1, z));
    }
    pair<int, vector<edge>> ans;
    ans = MST_Kruskal(edgeList, n);
    cout << "Cost: " << ans.first << endl;
    cout << "To  From  Cost" << endl;
    for (auto i: ans.second) {
        cout << i.from + 1 << "    " << i.to + 1 << "    " << i.w << endl;
    }
}