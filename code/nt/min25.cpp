int n, sq;
const int MOD = 1e9 + 7, K = 2;
int c[K] = {MOD - 1, 1}; // f(p) = c[0] + c[1] p + ... + c[K - 1] p^(K - 1), здесь phi: p - 1
vector <int> w, primes, sp[K], g[K]; // g[k][id(x)] - сумма p^k по простым p <= x, sp[k][j] - по первым j простым

int f(int p, int e, int pe) { // f(p^e) по модулю MOD, pe = p^e, здесь phi
    return (pe - pe / p) % MOD;
}
int sumPow(int x, int k) { // сумма i^k по 2 <= i <= x, k <= 2
    int a = x % MOD, b = (x + 1) % MOD;
    if (!k)
        return (a + MOD - 1) % MOD;
    if (k == 1)
        return (a * b % MOD * ((MOD + 1) / 2) + MOD - 1) % MOD;
    return (a * b % MOD * ((2 * x + 1) % MOD) % MOD * 166666668 + MOD - 1) % MOD; // 166666668 = 1 / 6
}
int id(int x) {
    return x <= sq ? w.size() - x : n / x - 1;
}
int calc(int x, int j) { // сумма f(i) по 2 <= i <= x с мин. простым делителем >= primes[j]
    if (x < 2 || (j < primes.size() && primes[j] > x))
        return 0;
    int ans = 0;
    for (int k = 0; k < K; ++k) // простые
        ans = (ans + c[k] * ((g[k][id(x)] - sp[k][j] + MOD) % MOD)) % MOD;
    for (int i = j; i < primes.size() && primes[i] * primes[i] <= x; ++i) { // составные: мин. простой p в степени e
        int p = primes[i];
        for (int e = 1, pe = p; pe <= x / p; ++e, pe *= p)
            ans = (ans + f(p, e, pe) * calc(x / pe, i + 1) + f(p, e + 1, pe * p)) % MOD;
    }
    return ans;
}
int min25(int N) { // сумма f(i) по 1 <= i <= N
    n = N;
    sq = sqrtl(n);
    while (sq * sq > n)
        --sq;
    while ((sq + 1) * (sq + 1) <= n)
        ++sq;
    w.clear();
    primes.clear();
    for (int l = 1; l <= n; l = n / (n / l) + 1)
        w.pb(n / l);
    vector <int> isP(sq + 1, 1);
    for (int i = 2; i <= sq; ++i)
        if (isP[i]) {
            primes.pb(i);
            for (int j = i * i; j <= sq; j += i)
                isP[j] = 0;
        }
    for (int k = 0; k < K; ++k) {
        g[k].resize(w.size());
        sp[k] = {0};
        for (int i = 0; i < w.size(); ++i)
            g[k][i] = sumPow(w[i], k);
        for (int p : primes) { // вычёркиваем числа с мин. простым делителем p
            int pk = 1;
            for (int t = 0; t < k; ++t)
                pk = pk * p % MOD;
            for (int i = 0; i < w.size() && w[i] >= p * p; ++i)
                g[k][i] = (g[k][i] - pk * ((g[k][id(w[i] / p)] - sp[k].back() + MOD) % MOD) % MOD + MOD) % MOD;
            sp[k].pb((sp[k].back() + pk) % MOD);
        }
    }
    return (1 + calc(n, 0)) % MOD;
}
