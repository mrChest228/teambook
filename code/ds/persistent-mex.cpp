const int N = 2e5 + 9, T = N * 20, MX = N; // MX > n
int lc[T], rc[T], mn[T], root[N], cnt = 1; // mn - мин. последняя позиция значений, $"mn"_0 = -1$

// Новая версия: значение p последний раз стоит в позиции x
int upd(int v, int p, int x, int l = 0, int r = MX) {
    int u = cnt++;
    lc[u] = lc[v], rc[u] = rc[v], mn[u] = x;
    if (r - l > 1) {
        int m = (l + r) / 2;
        if (p < m)
            lc[u] = upd(lc[v], p, x, l, m);
        else
            rc[u] = upd(rc[v], p, x, m, r);
        mn[u] = min(mn[lc[u]], mn[rc[u]]);
    }
    return u;
}
// До запросов: mn[0] = -1, root[i + 1] = a[i] < MX ? upd(root[i], a[i], i) : root[i]
// MEX на [l, r]: мин. значение, которого нет правее l - 1. O(log(MX))
int mex(int l, int r) {
    int v = root[r + 1], x = 0, y = MX;
    while (y - x > 1) {
        int m = (x + y) / 2;
        if (mn[lc[v]] < l)
            v = lc[v], y = m;
        else
            v = rc[v], x = m;
    }
    return x;
}
