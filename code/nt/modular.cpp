long inv(long x) { // mod простое, иначе gcdex (5.0)
    // или powm(x, phi(mod) - 1), только при gcd(x, mod) == 1
    return x == 1 ? 1 : mod - mod / x * inv(mod % x) % mod;
}

long powm(long x, long k) {
    long ans = 1;
    for (long y = x; k > 0; k >>= 1, y = y * y % mod)
        if (k & 1)
            ans = ans * y % mod;
    return ans;
}

// Первообразный корень простого mod: g^((mod - 1) / q) != 1 для каждого простого q | mod - 1. O(sqrt(mod))
long primRoot() {
    vector <long> q;
    long x = mod - 1;
    for (long i = 2; i * i <= x; ++i)
        if (x % i == 0) {
            q.pb(i);
            while (x % i == 0)
                x /= i;
        }
    if (x > 1)
        q.pb(x);
    for (long g = 1;; ++g) {
        bool ok = true;
        for (long u : q)
            ok &= powm(g, (mod - 1) / u) != 1;
        if (ok)
            return g;
    }
}

// Корень степени k из c: x^k = c (mod простое), g - первообразный корень. -1, если корня нет. O(sqrt(mod))
long root(long c, long k) {
    if (c == 0)
        return 0;
    // Ищем t: g^t = c. Все c * g^j, j < m кладём в pos, затем перебираем g^(i * m)
    long m = sqrtl(mod) + 1, gm = powm(g, m), t = 0;
    unordered_map <long, long> pos;
    for (long j = 0, cur = c; j < m; ++j, cur = cur * g % mod)
        pos[cur] = j;
    for (long i = 1, cur = gm; !t; ++i, cur = cur * gm % mod)
        if (pos.count(cur))
            t = i * m - pos[cur];
    // x = g^y: k * y = t (mod mod - 1)
    long d = gcd(k, mod - 1), y, z;
    if (t % d)
        return -1;
    gcdex(k / d, y, (mod - 1) / d, z);
    return powm(g, t / d % ((mod - 1) / d) * y % ((mod - 1) / d));
}
