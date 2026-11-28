const int N = 1e7 + 9, INF = 2e18;
int a[N], lo[N], hi[N];

// Макс. разность соседних в отсортированном a, n >= 2. O(n)
int maxGap(int n) {
    int mn = *min_element(a, a + n), mx = *max_element(a, a + n);
    if (mn == mx)
        return 0;
    int sz = (mx - mn + n - 2) / (n - 1); // Ответ >= sz, блоков <= n
    fill(lo, lo + n, INF);
    fill(hi, hi + n, -INF);
    for (int i = 0; i < n; ++i) {
        int b = (a[i] - mn) / sz;
        lo[b] = min(lo[b], a[i]);
        hi[b] = max(hi[b], a[i]);
    }
    int ans = 0, last = mn;
    for (int b = 0; b < n; ++b)
        if (lo[b] != INF) {
            ans = max(ans, lo[b] - last);
            last = hi[b];
        }
    return ans;
}
