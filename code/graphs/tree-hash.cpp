const int N = 2e5 + 9, M = (1ll << 61) - 1;
int rd[N], h[N], ht[N]; // $"rd"_i$ - случайные из [0, M), ht - высота поддерева
vector <int> g[N];

int mul(int a, int b) {
    return (int128)a * b % M;
}
// Хеш поддерева v. O(n)
int dfs(int v, int p) {
    ht[v] = 0;
    for (int u : g[v])
        if (u != p) {
            dfs(u, v);
            ht[v] = max(ht[v], ht[u] + 1);
        }
    h[v] = 1;
    for (int u : g[v])
        if (u != p)
            h[v] = mul(h[v], (rd[ht[v]] + h[u]) % M);
    return h[v];
}
int sz[N];
vector <int> cen;

void dfsCen(int v, int p, int n) {
    int mx = 0;
    sz[v] = 1;
    for (int u : g[v])
        if (u != p) {
            dfsCen(u, v, n);
            sz[v] += sz[u];
            mx = max(mx, sz[u]);
        }
    if (max(mx, n - sz[v]) * 2 <= n)
        cen.pb(v);
}
// Хеш некорневого дерева из n вершин, в котором лежит v
int treeHash(int v, int n) {
    cen.clear();
    dfsCen(v, -1, n);
    int a = dfs(cen[0], -1), b = dfs(cen.back(), -1);
    return mul(min(a, b) + 1, max(a, b) + 2);
}
