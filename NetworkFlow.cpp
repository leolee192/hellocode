
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

/** ----- min cost flow ----- */

template<typename cap_t=long long, typename cost_t=long long,
    cost_t NOT_FOUND=-1, cost_t INF=0x3f3f3f3f3f3f3f3fLL>
struct MinCostFlow {
  struct P {
    cost_t dist;
    int v;
    P(cost_t _dist, int _v): dist(_dist), v(_v) {}
    friend bool operator<(const P &l, const P &r) {
      if (l.dist != r.dist) return l.dist < r.dist;
      return l.v < r.v;
    }
    friend inline bool operator>(const P& lhs, const P& rhs) {return rhs < lhs; }
  };

  struct edge_t {
    int to;
    cap_t cap;
    cost_t cost;
    int rev;
  };

  int UPPER_V;
  vector<vector<edge_t> > G;
  vector<cost_t> h; // 顶点的势
  vector<cost_t> dist; // 最短距离
  vector<int> prevv, preve; // 最短路中的前驱节点和对应的边
  /** V index: [0, UPPER_V) */
  MinCostFlow(int _upper_v): UPPER_V(_upper_v), G(_upper_v),
  h(_upper_v), dist(_upper_v), prevv(_upper_v), preve(_upper_v) { }

  void add_edge(int from, int to, cap_t cap, cost_t cost) {
    G[from].push_back((edge_t) {to, cap, cost, G[to].size()});
    G[to].push_back((edge_t) {from, 0, -cost, G[from].size() - 1});
  }

  // 求解从s到t流量为f的最小费用流
  // 如果没有流量为f的流，返回-1
  // 执行完后，G中存储的是最小费用流状态下的残余图
  cost_t min_cost_flow(int s, int t, cap_t f) {
    cost_t res = 0;
    h.assign(UPPER_V, 0);
    while (f > 0) {
      // 使用Dijkstra算法更新h
      priority_queue<P, vector<P>, greater<P> > que;
      dist.assign(UPPER_V, INF);
      dist[s] = 0;
      que.push(P(0, s));
      while (!que.empty()) {
        P p = que.top(); que.pop();
        int v = p.v;
        if (dist[v] < p.dist) continue;
        for (int i=0; i<G[v].size(); ++i) {
          edge_t &e = G[v][i];
          if (e.cap > 0 && dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
            dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
            prevv[e.to] = v, preve[e.to] = i;
            que.push(P(dist[e.to], e.to));
          }
        }
      }
      if (dist[t] == INF) {
        // 不能再增广
        return NOT_FOUND;
      }
      for (int v=0; v<UPPER_V; ++v) h[v] += dist[v];

      // 沿s到t的最短路尽量增广
      cap_t d = f;
      for (int v=t; v != s; v = prevv[v]) {
        d = min(d, G[prevv[v]][preve[v]].cap);
      }
      f -= d;
      res += d * h[t];
      for (int v=t; v != s; v = prevv[v]) {
        edge_t &e = G[prevv[v]][preve[v]];
        e.cap -= d;
        G[v][e.rev].cap += d;
      }
    }

    return res;
  }
};

/** ----- END of min cost flow ----- **/
