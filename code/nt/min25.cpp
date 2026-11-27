int n, sq;
const int MOD = 1e9 + 7;
vector <int> w, g0, g1, primes, pref;

int id(int x) {
    return x <= sq ? int(w.size()) - x : n / x - 1;
}

// f(p^k), pk = p^k; для другой f заменить и f(p) = p - 1 в g1 - g0 и pref
int f(int p, int pk) {
    return (pk - pk / p) % MOD;
}

int calc(int x, int j) {
    if (x < 2 || (j < primes.size() && primes[j] > x))
        return 0;
    int ans = (g1[id(x)] - g0[id(x)] - pref[j]) % MOD;
    if (ans < 0)
        ans += MOD;
    for (int i = j; i < primes.size() && primes[i] <= x / primes[i]; ++i) {
        int p = primes[i];
        for (int pk = p; pk <= x / p; pk *= p) {
            ans = (ans + f(p, pk) * calc(x / pk, i + 1) + f(p, pk * p)) % MOD;
        }
    }
    return ans;
}

int min25(int N) {
    if (N <= 1)
        return N;
    n = N;
    sq = sqrtl(n);
    while ((sq + 1) * (sq + 1) <= n)
        ++sq;
    while (sq * sq > n)
        --sq;
    w.clear();
    g0.clear();
    g1.clear();
    primes.clear();
    pref.clear();
    for (int l = 1, r; l <= n; l = r + 1) {
        int x = n / l;
        r = n / x;
        w.pb(x);
    }
    g0.resize(w.size());
    g1.resize(w.size());
    for (int i = 0; i < w.size(); ++i) {
        g0[i] = w[i] - 1;
        g1[i] = (w[i] % MOD * ((w[i] + 1) % MOD) % MOD * ((MOD + 1) / 2) - 1 + MOD) % MOD;
    }
    int lim = max(sq, int(2));
    vector <int> sieve(lim + 1, 1);
    sieve[0] = sieve[1] = 0;
    for (int i = 2; i <= lim; ++i)
        if (sieve[i]) {
            primes.pb(i);
            if (i <= lim / i)
                for (int j = i * i; j <= lim; j += i)
                    sieve[j] = 0;
        }
    int c = 0, s = 0;
    for (int p : primes) {
        if (p > sq)
            break;
        for (int i = 0; i < w.size() && w[i] >= p * p; ++i) {
            int j = id(w[i] / p);
            g0[i] -= g0[j] - c;
            int d = (g1[j] - s + MOD) % MOD;
            g1[i] = (g1[i] - p % MOD * d % MOD + MOD) % MOD;
        }
        ++c;
        s = (s + p) % MOD;
    }
    pref.pb(0);
    for (int p : primes)
        pref.pb((pref.back() + p - 1) % MOD);
    return (1 + calc(n, 0)) % MOD;
}
