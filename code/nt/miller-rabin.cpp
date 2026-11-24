// Мин. простой делитель, MX = 1e6. Без решета fct для n < 1e6 в 27 раз медленнее, для n < 1e12 в 1.4 раза
int lp[MX];
vector <int> primes;

void init() {
    iota(lp + 2, lp + MX, 2); // lp[1] = 0, чтобы простое p == lp[p]
    for (int i = 2; i < MX; ++i) {
        if (lp[i] == i)
            primes.pb(i);
        for (int j = 0; j < primes.size() && i * primes[j] < MX && primes[j] <= lp[i]; ++j)
            lp[i * primes[j]] = primes[j];
    }
}

long mulm(long a, long b, long mod) {
    return int128(a) * b % mod;
}

long powm(long x, long n, long mod) {
    long ans = 1;
    for (long y = x; n > 0; n >>= 1, y = mulm(y, y, mod))
        if (n & 1)
            ans = mulm(ans, y, mod);
    return ans;
}

// Миллер-Рабин. 7 оснований точны для нечётных n < 2^64,
// подходят и 12 первых простых (2..37)
int isPrime(long n) {
    if (n < MX)
        return n > 1 && lp[n] == n;
    if (n % 2 == 0)
        return 0;
    long d = n - 1, s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }
    for (long a : {2, 325, 9375, 28'178, 450'775,
                   9'780'504, 1'795'265'022}) {
        long x = powm(a % n, d, n);
        if (x <= 1 || x == n - 1)
            continue;
        for (int r = 1; r < s && x != n - 1; ++r)
            x = mulm(x, x, n);
        if (x != n - 1)
            return 0;
    }
    return 1;
}

// n - составное. Возвращает делитель d, 1 < d < n
long pollardRho(long n) {
    assert(n >= MX);
    while (1) {
        long x = rnd() % n, y = x, c = rnd() % n, d = 1;
        auto f = [&](long x) {
            return (int128(x) * x + c) % n;
        };
        while (d == 1) {
            x = f(x);
            y = f(f(y));
            d = gcd(abs(x - y), n);
        }
        if (d != n)
            return d;
    }
}

// Дописывает в res простые делители n (с повторами, не по порядку)
void fct(long n, vector <long> &res) {
    if (n < MX) {
        for (; n > 1; n /= lp[n])
            res.pb(lp[n]);
        return;
    }
    if (isPrime(n)) {
        res.pb(n);
        return;
    }
    long d = pollardRho(n);
    fct(d, res);
    fct(n / d, res);
}
