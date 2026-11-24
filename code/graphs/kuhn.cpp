int mt[N];
bool b[N];
vector <int> g[N];

bool dfs(int v) {
    if (b[v])
        return 0;
    b[v] = true;
    for (int u : g[v])
        if (mt[u] == -1 || dfs(mt[u])) {
            mt[u] = v;
            return 1;
        }
    return 0;
}
// Main
int cnt = 0;
fill(mt, mt + n, -1);
for (int i = 0; i < n; ++i) {
    fill(b, b + n, 0);
    cnt += dfs(i);
}
