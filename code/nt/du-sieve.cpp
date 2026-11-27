vector <int> primes;
const int S = 5e6 + 9;
vector <int> prefMu, prefPhi;
unordered_map <int, int> memoM, memoPhi;

void init() {
    primes.clear();
    vector <int> lp(S);
    vector <int> mu(S), phi(S);
    prefMu.assign(S, 0);
    prefPhi.assign(S, 0);
    mu[1] = phi[1] = 1;
    for (int i = 2; i < S; ++i) {
        if (!lp[i]) {
            lp[i] = i;
            primes.pb(i);
            mu[i] = -1;
            phi[i] = i - 1;
        }
        for (int p : primes) {
            if (p > lp[i] || i * p >= S)
                break;
            lp[i * p] = p;
            if (p == lp[i]) {
                mu[i * p] = 0;
                phi[i * p] = phi[i] * p;
                break;
            }
            mu[i * p] = -mu[i];
            phi[i * p] = phi[i] * (p - 1);
        }
    }
    for (int i = 1; i < S; ++i) {
        prefMu[i] = prefMu[i - 1] + mu[i];
        prefPhi[i] = prefPhi[i - 1] + phi[i];
    }
    memoM.clear();
    memoPhi.clear();
    memoM.reserve(100'000);
    memoPhi.reserve(100'000);
}

int M(int n) {
    if (n <= 0)
        return 0;
    if (n < S)
        return prefMu[n];
    auto it = memoM.find(n);
    if (it != memoM.end())
        return it->second;
    int ans = 1;
    for (int l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans -= (r - l + 1) * M(n / l);
    }
    return memoM[n] = ans;
}

int Phi(int n) { // точная сумма помещается в long при n <= ~5e9
    if (n <= 0)
        return 0;
    if (n < S)
        return prefPhi[n];
    auto it = memoPhi.find(n);
    if (it != memoPhi.end())
        return it->second;
    __int128 ans = (__int128)n * (n + 1) / 2;
    for (int l = 2, r; l <= n; l = r + 1) {
        r = n / (n / l);
        ans -= (__int128)(r - l + 1) * Phi(n / l);
    }
    return memoPhi[n] = (int)ans;
}
