const int N = 509, INF = 2e18;
bool used[N];
int p[N], way[N]; // $p_j$ - строка в столбце j (0 - нет)
int a[N][N], u[N], v[N], mn[N]; // $u_i + v_j <= a_(i j)$, равенство на рёбрах паросочетания

// Строки 1..n, столбцы 1..m, n <= m. Мин. сумма, $O(n^2 m)$
int hungarian(int n, int m) {
    fill(u, u + n + 1, 0);
    fill(v, v + m + 1, 0);
    fill(p, p + m + 1, 0);
    for (int i = 1; i <= n; ++i) {
        fill(mn, mn + m + 1, INF);
        fill(used, used + m + 1, 0);
        int j0 = 0;
        p[0] = i;
        do {
            used[j0] = true;
            int i0 = p[j0], j1 = 0, d = INF;
            for (int j = 1; j <= m; ++j)
                if (!used[j]) {
                    int cur = a[i0][j] - u[i0] - v[j];
                    if (cur < mn[j]) {
                        mn[j] = cur;
                        way[j] = j0;
                    }
                    if (mn[j] < d) {
                        d = mn[j];
                        j1 = j;
                    }
                }
            for (int j = 0; j <= m; ++j)
                if (used[j]) {
                    u[p[j]] += d;
                    v[j] -= d;
                } else
                    mn[j] -= d;
            j0 = j1;
        } while (p[j0]);
        for (; j0; j0 = way[j0])
            p[j0] = p[way[j0]];
    }
    return -v[0];
}
