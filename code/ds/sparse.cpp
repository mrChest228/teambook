const int N = 2e5 + 9, L = 18; // $2^L > N$
int a[N];
int sp[L][N]; // Индекс минимума на $[i, i + 2^l)$

bool cmp(int i, int j) {
    return a[i] < a[j];
}
// O(n * log(n))
void build(int n) {
    iota(sp[0], sp[0] + n, 0);
    for (int l = 0, h = 1; h * 2 <= n; ++l, h *= 2)
        for (int i = 0; i + h * 2 <= n; ++i)
            sp[l + 1][i] = min(sp[l][i], sp[l][i + h], cmp);
}
// Индекс минимума на [l, r], при равных - самый левый. O(1)
int rmq(int l, int r) {
    int t = __lg(r - l + 1);
    return min(sp[t][l], sp[t][r - (1 << t) + 1], cmp);
}
