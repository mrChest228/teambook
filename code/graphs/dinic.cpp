struct edge {
    int to, rev, cap, flow;
};

int n, ptr[N], lvl[N];
vector <edge> v[N];

void add(int x, int y, int cap, int flow) {
    v[x].pb({y, v[y].size(), cap, flow});
    v[y].pb({x, v[x].size() - 1, cap, cap - flow});
}

bool bfs(int s, int t, int delta) {
    fill(lvl, lvl + n, oo);
    list <int> q;
    lvl[0] = 0;
    q.pb(0);
    while (q.size()) {
        int p = q.front();
        q.pop_front();
        for (auto &u : v[p])
            if (lvl[u.to] == oo && u.cap - u.flow >= delta) {
                lvl[u.to] = lvl[p] + 1;
                q.pb(u.to);
            }
    }
    return lvl[t] < oo;
}
int dfs(int x, int flow, int t, int delta) {
    if (x == t)
        return flow;
    int pushed = 0;
    for (; ptr[x] < v[x].size() && pushed < flow; ++ptr[x]) {
        auto &u = v[x][ptr[x]];
        if (lvl[u.to] != lvl[x] + 1 || u.cap - u.flow < delta)
            continue;
        int push = dfs(u.to, min(flow - pushed, u.cap - u.flow), t, delta);
        u.flow += push;
        v[u.to][u.rev].flow -= push;
        pushed += push;
    }
    return pushed;
}
int maxFlow(int s, int t) {
    int maxCap = 0;
    for (int i = 0; i < n; ++i)
        for (auto &u : v[i])
            maxCap = max(maxCap, u.cap);
    int delta = maxCap;
    while ((delta & (delta - 1)) > 0)
        delta &= delta - 1;
    int maxFlow = 0;
    while (delta) {
        while (bfs(s, t, delta)) { //We go on min-dist paths only (n * m times)
            fill(ptr, ptr + n, 0);
            while (int flow = dfs(s, oo, t, delta))
                maxFlow += flow;
        }
        delta >>= 1;
    }
    return maxFlow;
}
// Main
add(x, y, cap, flow);
cout << maxFlow(s, t);
