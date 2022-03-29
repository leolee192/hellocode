
/** ----- Dinic Algorithm ----- **/

template<typename cap_t=long long, cap_t INF=LLONG_MAX>
    struct Dinic {
  struct edge_t {
    int to;
    cap_t cap;
    /** reverse edge be G[to][rev] */
    int rev;
  };

  int UPPER_V;
  /** V index: [0, UPPER_V) */
  Dinic(int _upper_v): UPPER_V(_upper_v), G(_upper_v), level(_upper_v), iter(_upper_v) { }
  vector<vector<edge_t> > G; // 图的邻接表表示
  vector<int> level; // 从源点起的距离编号
  vector<int> iter; // 当前弧，在其之前的边已没有用了

  void add_edge(int from, int to, cap_t cap) {
    G[from].push_back((edge_t){to, cap, G[to].size()});
    G[to].push_back((edge_t){from, 0, G[from].size() - 1});
  }

  void bfs(int s) {
    level.assign(UPPER_V, -1);
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
      int v = q.front(); q.pop();
      for (int i=0; i<G[v].size(); ++i) {
        edge_t &e = G[v][i];
        if (e.cap > 0 && level[e.to] < 0) {
          level[e.to] = level[v] + 1;
          q.push(e.to);
        }
      }
    }
  }

  cap_t dfs(int v, int t, cap_t f) {
    if (v == t) return f;
    for (int &i = iter[v]; i < G[v].size(); ++i) {
      edge_t &e = G[v][i];
      if (e.cap > 0 && level[v] < level[e.to]) {
        cap_t d = dfs(e.to, t, min(f, e.cap));
        if (d > 0) {
          e.cap -= d;
          G[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  // 求解从s到t的最大流
  // 执行后，G中保存的是残余网络
  // 返回最大流量
  cap_t max_flow(int s, int t) {
    cap_t flow = 0;
    while (true) {
      bfs(s);
      if (level[t] < 0) return flow;
      iter.assign(UPPER_V, 0);
      cap_t f;
      while ((f = dfs(s, t, INF)) > 0) {
        flow += f;
      }
    }
  }
};

/** ----- END of Dinic Algorithm ----- **/
