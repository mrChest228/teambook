const int N = 2e5 + 9;
int n, t, k; // k - кол-во блоков
int tin[N], up[N]; // up[v] - мин. tin, куда из поддерева v ведёт одно обратное ребро
vector <int> g[N], st, bct[2 * N]; // В дереве вершины 0..n - 1, блоки n..n + k - 1

void dfs(int v) {
    tin[v] = up[v] = ++t;
    st.pb(v);
    for (int u : g[v]) {
        if (tin[u]) {
            up[v] = min(up[v], tin[u]);
            continue;
        }
        dfs(u);
        up[v] = min(up[v], up[u]);
        if (up[u] < tin[v])
            continue;
        // Из поддерева u нет ребра выше v: всё, что в стеке после u, вместе с v - блок
        bct[n + k].pb(v);
        bct[v].pb(n + k);
        for (int x = -1; x != u; st.pop_back()) {
            x = st.back();
            bct[n + k].pb(x);
            bct[x].pb(n + k);
        }
        ++k;
    }
}
// Main
for (int v = 0; v < n; ++v)
    if (!tin[v])
        dfs(v), st.pop_back();
// v - точка сочленения <=> bct[v].size() > 1
