const int MOD = 1e9 + 7, K = 2, Y = 1e7 + 9, B = 1e5 + 9; // Y > y, B > n / y; память 16 Y байт
int c[K] = {MOD - 1, 1}; // f(p) = c[0] + c[1] p + ... + c[K - 1] p^(K - 1), здесь phi: p - 1
int n, y, m, big[B], res[B]; // точки x = n / d: большие x > y лежат в big[d], res[d] (d <= m), малые x <= y - в pr[x]
signed lp[Y], fv[Y], pr[Y], fw[Y]; // lp - мин. простой делитель, fv[i] = f(i), fw - Фенвик по числам до y
vector <int> primes;

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
int pw(int x, int k) { // x^k
    int ans = 1;
    for (int t = 0; t < k; ++t)
        ans = ans * x % MOD;
    return ans;
}
void add(int i, int v) {
    for (; i <= y; i += i & -i)
        if ((fw[i] += v - MOD) < 0)
            fw[i] += MOD;
}
int get(int i) {
    int ans = 0;
    for (; i; i -= i & -i)
        ans += fw[i];
    return ans % MOD;
}
void build() { // Фенвик из fw[i] = a[i] за O(y)
    for (int i = 1; i <= y; ++i)
        if (i + (i & -i) <= y)
            fw[i + (i & -i)] = (fw[i + (i & -i)] + fw[i]) % MOD;
}
// Сумма в точке x = n / d в момент обработки простого p. Большая точка - из массива a.
// Малая: при x < p^2 в сумме только простые (pr), иначе - Фенвик
int at(int *a, int d, int p) {
    if (d <= m)
        return a[d];
    int x = double(n) / d;
    return x < p * p ? pr[x] : get(x);
}
void init(int N) { // точки и линейное решето до y ~ n^(2 / 3)
    n = N;
    int sq = sqrtl(n);
    y = min(n, max(sq + 1, min(Y - 1, (int)(powl(n, 2.0 / 3) / 10))));
    m = n / (y + 1);
    primes.clear();
    iota(lp, lp + y + 1, 0);
    fv[1] = 1;
    for (int i = 2; i <= y; ++i) {
        if (lp[i] == i)
            primes.pb(i);
        for (int j = 0; j < primes.size() && primes[j] <= lp[i] && i * primes[j] <= y; ++j)
            lp[i * primes[j]] = primes[j];
        int p = lp[i], e = 1, pe = p;
        while (lp[i / pe] == p)
            ++e, pe *= p;
        fv[i] = f(p, e, pe) * fv[i / pe] % MOD;
    }
}
// Шаг 1: res[d] = сумма f(p) по простым p <= n / d, pr[x] = сумма f(p) по простым p <= x
void primeSum() {
    fill(res, res + m + 1, 0);
    for (int k = 0; k < K; ++k) {
        fw[1] = pr[1] = 0; // сначала в сумме все i^k, i >= 2
        for (int i = 2; i <= y; ++i) {
            fw[i] = pw(i, k);
            pr[i] = (pr[i - 1] + (lp[i] == i) * fw[i]) % MOD;
        }
        build();
        for (int d = 1; d <= m; ++d)
            big[d] = sumPow(n / d, k);
        for (int p : primes) { // вычёркиваем числа p t с мин. простым делителем p
            if (p * p > n)
                break;
            int pk = pw(p, k);
            for (int d = 1; d <= m && d * p * p <= n; ++d) // точки x >= p^2 по убыванию x
                big[d] = (big[d] + (MOD - pk) * (at(big, d * p, p) + MOD - pr[p - 1])) % MOD;
            for (int t = p; p * p * p <= n && t * p <= y; ++t) // Фенвик читают только при x >= p^3
                if (lp[t] >= p)
                    add(t * p, MOD - pw(t * p, k));
        }
        for (int d = 1; d <= m; ++d)
            res[d] = (res[d] + c[k] * big[d]) % MOD;
    }
    for (int i = 2; i <= y; ++i) {
        pr[i] = pr[i - 1];
        for (int k = 0; k < K && lp[i] == i; ++k)
            pr[i] = (pr[i] + c[k] * pw(i, k)) % MOD;
    }
}
int min25(int N) { // сумма f(i) по 1 <= i <= N
    if (N < 2)
        return N > 0;
    init(N);
    primeSum();
    // Шаг 2: res[d] = сумма f(i) по 2 <= i <= n / d. Простые p идут по убыванию,
    // в сумму возвращаются составные с мин. простым делителем p
    fw[1] = 0;
    for (int i = 2; i <= y; ++i) // в Фенвике простые и составные с большим lp: их не читают, пока x < p^3
        fw[i] = lp[i] == i || lp[i] * lp[i] * lp[i] > n ? fv[i] : 0;
    build();
    for (int j = primes.size() - 1; j >= 0; --j) {
        int p = primes[j];
        if (p * p > n)
            continue;
        for (int d = 1; d <= m && d * p * p <= n; ++d)
            for (int e = 1, pe = p; d * pe * p <= n; ++e, pe *= p) // числа p^e t, t > 1, и число p^(e + 1)
                res[d] = (res[d] + f(p, e, pe) * (at(res, d * pe, p) + MOD - pr[p]) + f(p, e + 1, pe * p)) % MOD;
        for (int t = p; p * p * p <= n && t * p <= y; ++t)
            if (lp[t] >= p)
                add(t * p, fv[t * p]);
    }
    return ((m ? res[1] : get(n)) + 1) % MOD;
}
