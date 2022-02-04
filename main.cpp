#include <bits/stdc++.h>

using namespace std;

#define MY_DEBUG false

#define $(x) {if (MY_DEBUG) {cout << __LINE__ << ": "; cout << #x << " = " << x << " " << endl;}}


// REMEMBER: modify MY_DEBUG to false
// main region begin (DO NOT DELETE ABOVE)

void dfs(int node, vector<vector<int> > &graph, vector<bool> &visited) {
    visited[node] = true;

    for (vector<int>::iterator it = graph[node].begin(); it != graph[node].end(); ++it) {
        int adj = *it;
        if (!visited[adj]) {
            dfs(adj, graph, visited);
        }
    }
}

int main()
{
    int N, M;
    cin >> N >> M;

    vector<vector<int> > graph(N);
    for (int i=0; i<M; ++i) {
        int x, y;
        cin >> x >> y;

        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    vector<bool> visited(N);
    int cnt = 0;
    for (int i=0; i<N; ++i) {
        if (!visited[i]) {
            dfs(i, graph, visited);
            ++cnt;
        }
    }

    cout << cnt << endl;

    return 0;
}
