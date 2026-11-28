// n - степень двойки. inv = true - обратное преобразование. O(n * log(n))
void fwht(int n, int *a, bool inv) {
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += k * 2)
            for (int j = i; j < i + k; ++j) {
                int u = a[j], v = a[j + k];
                a[j] = (u + v) % MOD;
                a[j + k] = (u - v + MOD) % MOD;
            }
    if (inv) {
        int r = powm(n, MOD - 2);
        for (int i = 0; i < n; ++i)
            a[i] = a[i] * r % MOD;
    }
}
// $a_i = sum_(j xor k = i) a_j b_k$, b портится
void xorMult(int n, int *a, int *b) {
    fwht(n, a, false);
    fwht(n, b, false);
    for (int i = 0; i < n; ++i)
        a[i] = a[i] * b[i] % MOD;
    fwht(n, a, true);
}
