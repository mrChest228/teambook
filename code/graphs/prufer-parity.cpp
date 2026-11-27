const int N = 1e4 + 9, MOD = 1e9 + 7;
int cnt[2 * N], nw[2 * N]; // cnt[t + n] - сумма знаков по способам получить t

// s[i] - размер группы i, par[i] - чётность суммы степеней в ней. n >= 2, O(n * m)
int trees(int n, int m, int *s, int *par) {
    fill(cnt, cnt + 2 * n + 1, 0);
    cnt[n] = 1;
    int ans = 0, half = 1;
    for (int i = 0; i < m; ++i) {
        if (!s[i]) {
            if (par[i])
                return 0;
            continue;
        }
        int sign = (par[i] - s[i]) % 2 ? MOD - 1 : 1; // Чётность $c_i = a_i - s_i$
        for (int t = 0; t <= 2 * n; ++t) {
            nw[t] = t >= s[i] ? cnt[t - s[i]] : 0;
            if (t + s[i] <= 2 * n)
                nw[t] = (nw[t] + sign * cnt[t + s[i]]) % MOD;
        }
        copy(nw, nw + 2 * n + 1, cnt);
        half = half * (MOD + 1) / 2 % MOD;
    }
    for (int t = 0; t <= 2 * n; ++t)
        ans = (ans + cnt[t] * powm((t - n + MOD) % MOD, n - 2)) % MOD;
    return ans * half % MOD;
}
