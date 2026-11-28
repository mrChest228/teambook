const int N = 2e5 + 9, L = 18; // $2^L >= N$
int a[N], t[L][N];

int op(int x, int y); // Ассоциативная

// $t_(k, i)$ - op на отрезке от i до середины блока длины $2^(k + 1)$, в котором лежит i. O(n * log(n))
void build(int n) {
    for (int k = 0; 1 << k < n; ++k)
        for (int m = 1 << k; m < n; m += 2 << k) {
            t[k][m - 1] = a[m - 1];
            for (int i = m - 2; i >= m - (1 << k); --i)
                t[k][i] = op(a[i], t[k][i + 1]);
            t[k][m] = a[m];
            for (int i = m + 1; i < min(n, m + (1 << k)); ++i)
                t[k][i] = op(t[k][i - 1], a[i]);
        }
}
// op на [l, r]: один вызов op
int get(int l, int r) {
    if (l == r)
        return a[l];
    int k = __lg(l ^ r); // Старший бит, где l и r различаются: блок, где они по разные стороны середины
    return op(t[k][l], t[k][r]);
}
