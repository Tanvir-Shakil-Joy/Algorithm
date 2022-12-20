#include <bits/stdc++.h>

using namespace std;

const long long inf = 2e9 + 10;
long long cost[9][9];
long long dis[9];
long long parent[9];

void dijkastra(long long src) {
    priority_queue<pair<long long, long long>> q;
    q.push({0, src});
    for (long long i = 0; i < 9; i++)
        dis[i] = inf;
    dis[src] = 0;
    while (!q.empty()) {
        long long u = q.top().second;
        q.pop();
        for (long long i = 0; i < 9; i++) {
            if (i == u)
                continue;
            if (dis[i] > (dis[u] + cost[u][i])) {
                dis[i] = dis[u] + cost[u][i];
                q.push({-dis[i], i});
                parent[i] = u;
            }
        }
    }
}

void find_path(long long x, long long src) {
    long long u = x;
    stack<long long> s;
    s.push(u);
    while (u != src) {
        u = parent[u];
        s.push(u);
    }
    while (!s.empty()) {
        cout << s.top() << ' ';
        s.pop();
    }
    cout << endl;
}

int main() {
    ifstream in("dijkstra.txt", ios::in);
    if (in.is_open()) {
        for (long long i = 0; i < 9; i++) {
            for (long long j = 0; j < 9; j++) {
                long long x;
                in >> x;
                if (x == -1)
                    x = inf;
                cost[i][j] = x;
            }
        }
    }
    long long src;
    cout << "Enter the source: ";
    cin >> src;
    dijkastra(src);
    cout << "Node\tCost\tPath\n\n";
    for (long long i = 0; i < 9; i++) {
        cout << i << '\t' << dis[i] << '\t';
        find_path(i, src);
    }
}