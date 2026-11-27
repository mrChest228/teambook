const int MOD = 1e9 + 7, S = 5e6 + 9, B = 1e5 + 9; // S ~ n^(2 / 3), B > n / S
int bigMu[B], bigPhi[B]; // суммы в точках n / d > S, индекс d
signed lp[S], sumMu[S], sumPhi[S]; // sumMu[x] = mu(1) + ... + mu(x) по модулю, sumPhi так же
vector <int> primes;

void init() { // линейное решето: сначала в массивах сами mu(i) и phi(i), затем префиксные суммы
    iota(lp, lp + S, 0);
    sumMu[1] = sumPhi[1] = 1;
    for (int i = 2; i < S; ++i) {
        if (lp[i] == i)
            primes.pb(i);
        for (int j = 0; j < primes.size() && primes[j] <= lp[i] && i * primes[j] < S; ++j)
            lp[i * primes[j]] = primes[j];
        int p = lp[i], t = i / p;
        sumMu[i] = t % p ? -sumMu[t] : 0;
        sumPhi[i] = t % p ? sumPhi[t] * (p - 1) : sumPhi[t] * p;
    }
    for (int i = 2; i < S; ++i) {
        sumMu[i] = (sumMu[i] + sumMu[i - 1] + MOD) % MOD;
        sumPhi[i] = (sumPhi[i] + sumPhi[i - 1]) % MOD;
    }
}
// Суммы mu и phi по 1 <= i <= n по модулю, нужен init(). Точки x = n / d идут по возрастанию,
// поэтому все нужные меньшие точки x / l = n / (d l) уже посчитаны
pair <int, int> sumMuPhi(int n) {
    if (n < S)
        return {sumMu[n], sumPhi[n]};
    for (int d = n / S; d > 0; --d) {
        int x = n / d, mu = 1, phi = x % MOD * ((x + 1) % MOD) % MOD * ((MOD + 1) / 2) % MOD;
        for (int l = 2, r; l <= x; l = r + 1) {
            r = x / (x / l);
            int cnt = (r - l + 1) % MOD, big = d * l <= n / S;
            mu = (mu + (MOD - cnt) * (big ? bigMu[d * l] : sumMu[x / l])) % MOD;
            phi = (phi + (MOD - cnt) * (big ? bigPhi[d * l] : sumPhi[x / l])) % MOD;
        }
        bigMu[d] = mu;
        bigPhi[d] = phi;
    }
    return {bigMu[1], bigPhi[1]};
}
