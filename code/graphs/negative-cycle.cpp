const int N = 2e3 + 9, M = 1e4 + 9;
int ex[M], ey[M], ew[M]; // Ребро ex[i] -> ey[i] веса ew[i]
int d[N], par[N];

// Вершины 0..n - 1. Любой отрицательный цикл в порядке обхода, либо пустой вектор. O(n * m)
vector <int> negCycle(int n, int m) {
    fill(d, d + n, 0); // Как будто из новой вершины в каждую идёт ребро веса 0
    fill(par, par + n, -1);
    int x = -1;
    for (int it = 0; it < n; ++it) {
        x = -1;
        for (int i = 0; i < m; ++i)
            if (d[ex[i]] + ew[i] < d[ey[i]]) {
                d[ey[i]] = d[ex[i]] + ew[i];
                par[ey[i]] = ex[i];
                x = ey[i];
            }
        if (x == -1)
            return {};
    }
    for (int it = 0; it < n; ++it) // x изменилась на шаге n: n шагов назад - точно на цикле
        x = par[x];
    vector <int> c{x};
    for (int v = par[x]; v != x; v = par[v])
        c.pb(v);
    reverse(c.begin(), c.end());
    return c;
}
