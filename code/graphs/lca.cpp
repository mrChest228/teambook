const int N = 2e5 + 9, L = 19; // $2^L > 2 N$
int tin[N], dep[N], k;
int sp[L][2 * N]; // Эйлеров обход: вершина с мин. глубиной на отрезке длины $2^l$
vector <int> g[N];

void dfs(int v, int p) {
    tin[v] = k;
    sp[0][k++] = v;
    for (int u : g[v])
        if (u != p) {
            dep[u] = dep[v] + 1;
            dfs(u, v);
            sp[0][k++] = v;
        }
}
int higher(int a, int b) {
    return dep[a] < dep[b] ? a : b;
}
// После k = 0, dep[root] = 0, dfs(root, -1). O(n * log(n))
void build() {
    for (int l = 1; 1 << l <= k; ++l)
        for (int i = 0; i + (1 << l) <= k; ++i)
            sp[l][i] = higher(sp[l - 1][i], sp[l - 1][i + (1 << l - 1)]);
}
// O(1)
int lca(int a, int b) {
    int l = min(tin[a], tin[b]), r = max(tin[a], tin[b]) + 1, t = __lg(r - l);
    return higher(sp[t][l], sp[t][r - (1 << t)]);
}
