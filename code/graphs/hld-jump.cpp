const int L = 5; // $2^L > log_2(N)$
int up[L][N]; // $"up"_(j, h)$ - начало пути через $2^j$ путей вверх от начала h
int lt[N], ver[N]; // lt - число лёгких рёбер до корня, $"ver"_("tin"_v) = v$

// После dfsHld. O(n * log(log(n)))
void buildUp(int n) {
    for (int v = 0; v < n; ++v)
        ver[tin[v]] = v;
    for (int i = 0; i < n; ++i) {
        int v = ver[i], p = par[v];
        lt[v] = p == -1 ? 0 : lt[p] + (top[v] == v);
        up[0][v] = p == -1 || top[v] != v ? top[v] : top[p];
    }
    for (int j = 1; j < L; ++j)
        for (int v = 0; v < n; ++v)
            up[j][v] = up[j - 1][up[j - 1][v]];
}
// O(log(log(n)))
int lcaFast(int x, int y) {
    if (lt[x] < lt[y])
        swap(x, y);
    if (int d = lt[x] - lt[y]) {
        x = top[x];
        for (int j = 0; j < L; ++j)
            if (d - 1 >> j & 1)
                x = up[j][x];
        x = par[x];
    }
    if (top[x] != top[y]) {
        x = top[x], y = top[y];
        for (int j = L - 1; j >= 0; --j)
            if (up[j][x] != up[j][y])
                x = up[j][x], y = up[j][y];
        x = par[x], y = par[y];
    }
    return dep[x] < dep[y] ? x : y;
}
// k-й предок v, k <= $"dep"_v$. O(log(log(n)))
int kth(int v, int k) {
    int d = dep[v] - k, h = top[v];
    for (int j = L - 1; j >= 0; --j)
        if (dep[up[j][h]] > d)
            h = up[j][h];
    if (dep[h] > d)
        h = top[par[h]];
    return ver[tin[h] + d - dep[h]];
}
