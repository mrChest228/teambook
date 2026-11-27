vector <int> prufer(vector <vector <int>> &g) {
    int n = g.size();
    vector <int> deg(n), code(n - 2);
    for (int v = 0; v < n; ++v)
        deg[v] = g[v].size();

    int ptr = 0;
    while (deg[ptr] != 1)
        ++ptr;
    int leaf = ptr;
    for (int i = 0; i < n - 2; ++i) {
        int v = -1;
        for (int u : g[leaf])
            if (deg[u]) {
                v = u;
                break;
            }
        code[i] = v;
        --deg[leaf];
        --deg[v];
        if (deg[v] == 1 && v < ptr)
            leaf = v;
        else {
            while (ptr < n && deg[ptr] != 1)
                ++ptr;
            leaf = ptr;
        }
    }
    return code;
}

vector <pair <int, int>> unprufer(vector <int> &code) {
    int n = code.size() + 2;
    vector <int> deg(n, 1);
    for (int v : code)
        ++deg[v];

    int ptr = 0;
    while (deg[ptr] != 1)
        ++ptr;
    int leaf = ptr;
    vector <pair <int, int>> e;
    for (int v : code) {
        e.pb({leaf, v});
        --deg[leaf];
        --deg[v];
        if (deg[v] == 1 && v < ptr)
            leaf = v;
        else {
            while (ptr < n && deg[ptr] != 1)
                ++ptr;
            leaf = ptr;
        }
    }
    e.pb({leaf, n - 1});
    return e;
}
