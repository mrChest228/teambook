long a[N][N];
long u[N], v[N], mn[N];
int p[N], way[N];
bool used[N];

long hungarian(int n, int m) {
    fill(u, u + n + 1, 0);
    fill(v, v + m + 1, 0);
    fill(p, p + m + 1, 0);

    for (int i = 1; i <= n; ++i) {
        p[0] = i;
        int j0 = 0;
        fill(mn, mn + m + 1, LLONG_MAX);
        fill(used, used + m + 1, 0);

        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0;
            long delta = LLONG_MAX;
            for (int j = 1; j <= m; ++j)
                if (!used[j]) {
                    long cur = a[i0][j] - u[i0] - v[j];
                    if (cur < mn[j]) {
                        mn[j] = cur;
                        way[j] = j0;
                    }
                    if (mn[j] < delta) {
                        delta = mn[j];
                        j1 = j;
                    }
                }

            for (int j = 0; j <= m; ++j)
                if (used[j]) {
                    u[p[j]] += delta;
                    v[j] -= delta;
                }
                else
                    mn[j] -= delta;
            j0 = j1;
        } while (p[j0]);

        do {
            int j1 = way[j0];
            p[j0] = p[j1];
            j0 = j1;
        } while (j0);
    }

    long res = 0;
    for (int j = 1; j <= m; ++j)
        if (p[j])
            res += a[p[j]][j];
    return res;
}
