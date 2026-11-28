int tin[N], ver[N], k; // $"ver"_("tin"_v) = v$
vector <int> g[N];

// a - массив для rmq: tin предка вершины с этим tin
void dfs(int v, int p) {
    ver[k] = v;
    a[k] = p == -1 ? -1 : tin[p];
    tin[v] = k++;
    for (int u : g[v])
        if (u != p)
            dfs(u, v);
}
// После k = 0, dfs(root, -1), build(n)
int lca(int x, int y) {
    if (x == y)
        return x;
    int l = min(tin[x], tin[y]), r = max(tin[x], tin[y]);
    return ver[a[rmq(l + 1, r)]];
}
