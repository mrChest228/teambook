const int N = 1e3 + 9, M = 1e5 + 9;
int ex[M], ey[M], col[M];
int to[N][N]; // $"to"_(v c)$ - сосед v по ребру цвета c, -1 - цвет свободен
int fan[N], fanCol[N], fr[N], loc[N]; // $"fr"_v$ - какой-то свободный цвет v

// Простой граф, вершины 0..n - 1, рёбра ex[i] - ey[i]. Цвета 0..D в col, возвращает D - макс. степень. O(n * m)
int color(int n, int m) {
    int D = 0;
    fill(col, col + n, 0);
    for (int i = 0; i < m; ++i)
        D = max({D, ++col[ex[i]], ++col[ey[i]]});
    for (int v = 0; v < n; ++v) {
        fill(to[v], to[v] + D + 1, -1);
        fr[v] = 0;
    }
    for (int i = 0; i < m; ++i) {
        int u = ex[i], v = ey[i], c = fr[u], d, k = 0, at = u, end = u;
        fill(loc, loc + D + 1, 0);
        fan[0] = v;
        // Веер: рёбра из u, цвет следующего свободен у предыдущего конца
        while (d = fr[v], !loc[d] && to[u][d] != -1) {
            v = to[u][d];
            loc[d] = ++k;
            fanCol[k] = d;
            fan[k] = v;
        }
        fanCol[loc[d]] = c;
        // Путь d, c, d, ... из u: меняем c и d местами, d освобождается у u
        for (int cd = d; at != -1; cd ^= c ^ d) {
            int nx = to[at][cd];
            swap(to[at][cd], to[at][cd ^ c ^ d]);
            end = at;
            at = nx;
        }
        // Сдвигаем цвета вдоль веера до вершины, где d свободен
        for (k = 0; to[fan[k]][d] != -1; ++k) {
            int l = fan[k], r = fan[k + 1], e = fanCol[k + 1];
            to[u][e] = l;
            to[l][e] = u;
            to[r][e] = -1;
            fr[r] = e;
        }
        to[u][d] = fan[k];
        to[fan[k]][d] = u;
        for (int y : {fan[0], u, end})
            for (fr[y] = 0; to[y][fr[y]] != -1;)
                ++fr[y];
    }
    for (int i = 0; i < m; ++i)
        for (col[i] = 0; to[ex[i]][col[i]] != ey[i];)
            ++col[i];
    return D;
}
