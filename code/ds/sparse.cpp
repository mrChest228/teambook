const int N = 2e5 + 9, L = 18; // $2^L > N$
int a[N];
int sp[L][N]; // Индекс минимума на $[i, i + 2^l)$

int better(int i, int j) {
    return a[j] < a[i] ? j : i;
}
// O(n * log(n))
void build(int n) {
    iota(sp[0], sp[0] + n, 0);
    for (int l = 1; 1 << l <= n; ++l)
        for (int i = 0; i + (1 << l) <= n; ++i)
            sp[l][i] = better(sp[l - 1][i], sp[l - 1][i + (1 << l - 1)]);
}
// Индекс минимума на [l, r], при равных - самый левый. O(1)
int rmq(int l, int r) {
    int t = __lg(r - l + 1);
    return better(sp[t][l], sp[t][r - (1 << t) + 1]);
}
