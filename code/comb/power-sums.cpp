// O(c log(mod)), c = 10^6 за 200 мс. powm и inv из 5.2
// Другой многочлен: свои y[i], k = степень + 1
long sumPow(long n, int c) {
    int k = c + 2; // Число точек, k < mod
    vector <long> y(k), f(k, 1), l(k + 1, 1), r = l;
    for (int i = 1; i < k; ++i) {
        y[i] = (y[i - 1] + powm(i, c)) % mod; // S_c(i)
        f[i] = f[i - 1] * i % mod; // i!
    }
    n %= mod;
    for (int i = 0; i < k; ++i) // (n - 0)...(n - i)
        l[i + 1] = l[i] * (n - i + mod) % mod;
    for (int i = k - 1; i >= 0; --i) // (n - i)...(n - k + 1)
        r[i] = r[i + 1] * (n - i + mod) % mod;
    long res = 0;
    // Лагранж: сумма y[i] * П (n - j) / (i - j) по j != i
    for (int i = 0; i < k; ++i) {
        long t = y[i] * l[i] % mod * r[i + 1] % mod;
        t = t * inv(f[i] * f[k - 1 - i] % mod) % mod;
        res += (k - i) % 2 ? t : mod - t; // Знак П (i - j)
    }
    return res % mod;
}
