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
    vector <int> tree(m), extra;
    for (int v = 1; v < n; ++v)
        tree[pe[v]] = 1;
    for (int i = 0; i < m; ++i)
        if (!tree[i])
            extra.pb(i);

    int k = extra.size(), ans = 0;
    vector <int> mask(k);
    while (true) {
        int bit = 0;
        while (bit < k && mask[bit])
            mask[bit++] = 0;
        if (bit == k)
            break;
        mask[bit] = 1;
        vector <int> parity(n);
        vector <vector <int>> sub(n);
        for (int j = 0; j < k; ++j)
            if (mask[j]) {
                int id = extra[j], x = e[id].f, y = e[id].s;
                parity[x] ^= 1;
                parity[y] ^= 1;
                sub[x].pb(y);
                sub[y].pb(x);
            }
        for (int i = order.size() - 1; i > 0; --i) {
            int v = order[i];
            if (parity[v]) {
                int p = par[v];
                sub[v].pb(p);
                sub[p].pb(v);
                parity[p] ^= 1;
            }
        }
        int start = -1, touched = 0;
        bool ok = true;
        for (int v = 0; v < n; ++v)
            if (sub[v].size()) {
                start = v;
                ++touched;
                if (sub[v].size() != 2)
                    ok = false;
            }
        if (!ok || start == -1)
            continue;
        vector <int> seen(n), q = {start};
        seen[start] = 1;
        for (int i = 0; i < q.size(); ++i)
            for (int u : sub[q[i]])
                if (!seen[u]) {
                    seen[u] = 1;
                    q.pb(u);
                }
        ans += q.size() == touched;
    }
    return ans;
}
