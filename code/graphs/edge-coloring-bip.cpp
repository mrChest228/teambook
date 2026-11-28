const int N = 1e3 + 9, M = 1e5 + 9;
int ex[M], ey[M], col[M];
int to[N][N]; // $"to"_(v c)$ - номер ребра цвета c из v, -1 - цвет свободен

// Двудольный граф (можно кратные рёбра), вершины 0..n - 1, рёбра ex[i] - ey[i]
// Цвета 0..D - 1 в col, возвращает D - макс. степень, D < N. O(n * m)
int colorBip(int n, int m) {
    int D = 0;
    fill(col, col + n, 0);
    for (int i = 0; i < m; ++i)
        D = max({D, ++col[ex[i]], ++col[ey[i]]});
    for (int v = 0; v < n; ++v)
        fill(to[v], to[v] + D, -1);
    for (int i = 0; i < m; ++i) {
        int x = ex[i], y = ey[i], a = 0, b = 0;
        while (to[x][a] != -1)
            ++a;
        while (to[y][b] != -1)
            ++b;
        for (int v = y, c = a; v != -1; c ^= a ^ b) { // Путь a, b, a, ... из y: меняем a и b местами
            int e = to[v][c];
            swap(to[v][a], to[v][b]);
            v = e == -1 ? -1 : ex[e] ^ ey[e] ^ v;
        }
        to[x][a] = to[y][a] = i;
    }
    for (int v = 0; v < n; ++v)
        for (int c = 0; c < D; ++c)
            if (to[v][c] != -1)
                col[to[v][c]] = c;
    return D;
}
