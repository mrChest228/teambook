struct edge {
    int to, revNum, cap, cost, flow;
};

vector <edge> v[N];
pair <int, int> par[N];
int n, delta, potentials[N], dists[N];

void addEdge(int x, int y, int cap, int flow, int cost) {
    v[x].pb({y, v[y].size(), cap, cost, flow});
    v[y].pb({x, v[x].size() - 1, cap, -cost, cap - flow});
}

void bellmanFord(int s) {
    fill(potentials, potentials + n, oo);
    potentials[s] = 0;
    for (int step = 0; step < n - 1; ++step)
        for (int i = 0; i < n; ++i)
            if (potentials[i] < oo)
                for (auto &u : v[i])
                    potentials[u.to] = min(potentials[u.to], potentials[i] + u.cost);
}
bool dijkstraWithPotentials(int s, int t) {
    fill(dists, dists + n, oo);
    priQue <pair <int, int>> q;
    dists[s] = 0;
    q.push({s, 0});
    while (q.size()) {
        auto [d, u] = q.top();
        q.pop();
        if (dists[u] < d)
            continue;
        for (int i = 0; i < v[u].size(); ++i) {
            auto &e = v[u][i];
            if (e.cap - e.flow >= delta && dists[e.to] > d + e.cost + potentials[u] - potentials[e.to]) {
                dists[e.to] = d + e.cost + potentials[u] - potentials[e.to];
                par[e.to] = {u, i};
                q.push({dists[e.to], e.to});
            }
        }
    }
    for (int i = 0; i < n; ++i) //Update potentials
        if (dists[i] < oo)
            potentials[i] += dists[i];
    return dists[t] < oo;
}
pair <int, int> maxFlowMinCost(int s, int t) {
    bellmanFord(s); //Make potentials for negative costs (reversed edges, for example)

    int maxCap = 0;
    for (int i = 0; i < n; ++i)
        for (auto &u : v[i])
            maxCap = max(maxCap, u.flow);
    delta = maxCap;
    while ((delta & (delta - 1)) > 0) //Make delta the power of 2
        delta &= delta - 1;

    int maxFlow = 0, minCost = 0;
    while (delta) {
        while (dijkstraWithPotentials(s, t)) {
            int flow = maxCap;
            for (int i = t; i != s; i = par[i].f) {
                auto &e = v[par[i].f][par[i].s];
                flow = min(flow, e.cap - e.flow);
            }
            maxFlow += flow;
            for (int i = t; i != s; i = par[i].f) {
                auto &e = v[par[i].f][par[i].s];
                e.flow += flow;
                v[e.to][e.revNum].flow -= flow;
                minCost += flow * e.cost;
            }
        }
        delta >>= 1;
    }
    return {maxFlow, minCost};
}

addEdge(x, y, cap, flow, cost);
auto [flow, cost] = maxFlowMinCost(s, f);
