#include <bits/stdc++.h>

using namespace std;

vector<int> tree[15];
vector<int> nodes;
int dist[15] = {0};
int w[15][15];
int parent[15];
int nb = 0;

void TVSP(int node, int tol) {
    if (tree[node].size() != 0) {
        dist[node] = 0;
        for (auto v : tree[node]) {
            TVSP(v, tol);
            dist[node] = max(dist[node], w[node][v]+dist[v]);
        }
        if (node != 1 && (dist[node]+w[parent[node]][node]) > tol) {
            nodes.push_back(node);
            dist[node] = 0;
            nb++;
        }
    }
}

int main() {
    ifstream in("tvsp.txt");
    if (in.is_open()) {
        int n, u, v, wt;
        while (in >> u >> v >> wt) {
            w[u][v] = wt;
            tree[u].push_back(v);
            parent[v] = u;
        }
        cout << "Enter the tolerance : "; cin >> n;
        TVSP(1, n);
    }
    cout << "Number of booster: " << nb << endl;
    cout << "The nodes are ..." << endl;
    sort(nodes.begin(), nodes.end());
    for(auto node : nodes) cout << node << endl;
}
