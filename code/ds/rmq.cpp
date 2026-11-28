const int N = 1e6 + 9, L = 14; // $2^L > N \/ 64$
int a[N];
ulong msk[N]; // Бит k: $a_(i - k)$ не больше всех $a_j$ правее него до i
int sp[L][N / 64 + 1]; // Разреженная таблица по блокам из 64

bool cmp(int i, int j) {
    return a[i] < a[j];
}
// r - l < 64
int small(int l, int r) {
    return r - __lg(msk[r] << (63 - r + l) >> (63 - r + l));
}
// O(n)
void build(int n) {
    ulong cur = 0;
    for (int i = 0; i < n; ++i) {
        cur <<= 1;
        while (cur && a[i - __builtin_ctzll(cur)] > a[i])
            cur &= cur - 1;
        msk[i] = cur |= 1;
    }
    int m = n / 64;
    for (int i = 0; i < m; ++i)
        sp[0][i] = small(i * 64, i * 64 + 63);
    for (int l = 0, h = 1; h * 2 <= m; ++l, h *= 2)
        for (int i = 0; i + h * 2 <= m; ++i)
            sp[l + 1][i] = min(sp[l][i], sp[l][i + h], cmp);
}
// Индекс минимума на [l, r], при равных - самый левый. O(1)
int rmq(int l, int r) {
    if (r - l < 64)
        return small(l, r);
    int res = small(l, l + 63);
    int x = (l + 63) / 64, y = (r + 1) / 64; // Целые блоки [x, y)
    if (x < y) {
        int t = __lg(y - x);
        res = min(res, sp[t][x], cmp);
        res = min(res, sp[t][y - (1 << t)], cmp);
    }
    return min(res, small(r - 63, r), cmp);
}
