// O(c log(mod)), c = 10^6 за 200 мс. powm и inv из 5.2
const int C = 1e6 + 9; // c + 3 <= C
long val[C], fact[C], pref[C], suf[C];

// Другой многочлен: свои val[i], k = степень + 1
long sumPow(long n, int c) {
    int k = c + 2; // Число точек, k < mod
    fact[0] = pref[0] = suf[k] = 1;
    for (int i = 1; i < k; ++i) {
        val[i] = (val[i - 1] + powm(i, c)) % mod; // S_c(i)
        fact[i] = fact[i - 1] * i % mod; // i!
    }
    n %= mod;
    for (int i = 0; i < k; ++i) // (n - 0)...(n - i)
        pref[i + 1] = pref[i] * (n - i + mod) % mod;
    for (int i = k - 1; i >= 0; --i) // (n - i)...(n - k + 1)
        suf[i] = suf[i + 1] * (n - i + mod) % mod;
    long res = 0;
    // Лагранж: сумма val[i] * П (n - j) / (i - j) по j != i
    for (int i = 0; i < k; ++i) {
        long t = val[i] * pref[i] % mod * suf[i + 1] % mod;
        t = t * inv(fact[i] * fact[k - 1 - i] % mod) % mod;
        res += (k - i) % 2 ? t : mod - t; // Знак П (i - j)
    }
    return res % mod;
}
