const int N = 2e5 + 9, T = N * 20, MX = N; // $T > N (log_2("MX") + 2)$, значения в [0, MX)
int lc[T], rc[T], sm[T], root[N], cnt = 1; // Вершина 0 - пустое дерево

// Новая версия: v с +1 в позиции p. O(log(MX))
int add(int v, int p, int l = 0, int r = MX) {
    int u = cnt++;
    lc[u] = lc[v], rc[u] = rc[v], sm[u] = sm[v] + 1;
    if (r - l > 1) {
        int m = (l + r) / 2;
        if (p < m)
            lc[u] = add(lc[v], p, l, m);
        else
            rc[u] = add(rc[v], p, m, r);
    }
    return u;
}
// k-е с 0 значение в мультимножестве a + b - c - d: спуск по 4 версиям. O(log(MX))
int kth(int a, int b, int c, int d, int k) {
    int l = 0, r = MX;
    while (r - l > 1) {
        int m = (l + r) / 2, s = sm[lc[a]] + sm[lc[b]] - sm[lc[c]] - sm[lc[d]];
        if (k < s)
            a = lc[a], b = lc[b], c = lc[c], d = lc[d], r = m;
        else
            a = rc[a], b = rc[b], c = rc[c], d = rc[d], l = m, k -= s;
    }
    return l;
}
