const int N = 2e5 + 9;
int par[N], dep[N], sz[N], top[N], tin[N], k;
vector <int> g[N];

void dfsSz(int v, int p) {
    par[v] = p;
    sz[v] = 1;
    for (int &u : g[v])
        if (u != p) {
            dep[u] = dep[v] + 1;
            dfsSz(u, v);
            sz[v] += sz[u];
            if (g[v][0] == p || sz[u] > sz[g[v][0]])
                swap(u, g[v][0]); // Тяжёлый ребёнок первым
        }
}
// Путь - отрезок по tin, поддерево v - $["tin"_v, "tin"_v + "sz"_v)$
void dfsHld(int v, int t) {
    top[v] = t;
    tin[v] = k++;
    for (int u : g[v])
        if (u != par[v])
            dfsHld(u, u == g[v][0] ? t : u);
}
// После k = 0, dep[root] = 0, dfsSz(root, -1), dfsHld(root, root). O(log(n))
int lca(int x, int y) {
    for (; top[x] != top[y]; x = par[top[x]])
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
    return dep[x] < dep[y] ? x : y;
}
// Путь x - y: O(log(n)) отрезков [l, r] по tin
template <class F>
void path(int x, int y, F f) {
    for (; top[x] != top[y]; x = par[top[x]]) {
        if (dep[top[x]] < dep[top[y]])
            swap(x, y);
        f(tin[top[x]], tin[x]);
    }
    f(min(tin[x], tin[y]), max(tin[x], tin[y]));
}
