const int N = 50;

long a[N]; // Edges bitmask
int n, m, k, mx;

void dfs(long clck, long cndt, long bad) {
    if (cndt == 0 && bad == 0) {
        int cnt = __builtin_popcount(clck);
        if (cnt > mx)
            mx = cnt;
        return;
    }

    for (int i = 0; i < n; ++i)
        if (((1LL << i) & bad) && (a[i] & cndt) == cndt)
            return;

    for (int i = 0; i < n; ++i) {
        long u = (1LL << i);
        if ((u & cndt) == 0)
            continue;
        cndt -= u;
        dfs(clck | u, cndt & a[i], bad & a[i]);
        bad |= u;
    }
}
// Main
dfs(0, (1LL << n) - 1, 0);
