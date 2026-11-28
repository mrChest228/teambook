// $a_i = sum_(gcd(j, k) = i) a_j b_k$, индексы 1..n, b портится. O(n * log(n))
void gcdMult(int n, int *a, int *b) {
    for (int i = 1; i <= n; ++i)
        for (int j = i * 2; j <= n; j += i) { // Суммы по кратным
            a[i] = (a[i] + a[j]) % MOD;
            b[i] = (b[i] + b[j]) % MOD;
        }
    for (int i = n; i > 0; --i) {
        a[i] = a[i] * b[i] % MOD; // Пары, где i делит gcd
        for (int j = i * 2; j <= n; j += i)
            a[i] = (a[i] - a[j] + MOD) % MOD;
    }
}
