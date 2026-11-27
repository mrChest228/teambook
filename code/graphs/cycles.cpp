int cycles(int n, vector <pair <int, int>> &e) {
    int m = e.size();
    vector <vector <pair <int, int>>> g(n);
    for (int i = 0; i < m; ++i) {
        int x = e[i].f, y = e[i].s;
        g[x].pb({y, i});
        g[y].pb({x, i});
    }
    vector <int> par(n, -1), pe(n, -1), order = {0};
    par[0] = 0;
    for (int i = 0; i < order.size(); ++i) {
        int v = order[i];
        for (auto [u, id] : g[v])
            if (par[u] == -1) {
                par[u] = v;
                pe[u] = id;
                order.pb(u);
            }
    }
    vector <int> extra;
    for (int i = 0; i < m; ++i)
        if (pe[e[i].f] != i && pe[e[i].s] != i)
            extra.pb(i);

    int k = extra.size(), ans = 0;
    for (int mask = 1; mask < 1 << k; ++mask) {
        vector <int> parity(n);
        vector <vector <int>> adj(n);
        auto add = [&](int x, int y) {
            adj[x].pb(y);
            adj[y].pb(x);
        };
        for (int j = 0; j < k; ++j)
            if (mask >> j & 1) {
                int id = extra[j], x = e[id].f, y = e[id].s;
                parity[x] ^= 1;
                parity[y] ^= 1;
                add(x, y);
            }
        for (int i = order.size() - 1; i > 0; --i) {
            int v = order[i];
            if (parity[v]) {
                int p = par[v];
                add(v, p);
                parity[p] ^= 1;
            }
        }
        int s = -1, cntV = 0;
        bool ok = true;
        for (int v = 0; v < n; ++v)
            if (adj[v].size()) {
                s = v;
                ++cntV;
                if (adj[v].size() != 2)
                    ok = false;
            }
        int len = 0;
        if (ok && s != -1) {
            int p = s, v = adj[s][0];
            len = 1;
            while (v != s) {
                int u = adj[v][0] == p ? adj[v][1] : adj[v][0];
                p = v;
                v = u;
                ++len;
            }
        }
        ans += ok && s != -1 && len == cntV;
    }
    return ans;
}
