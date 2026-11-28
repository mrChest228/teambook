const int N = 1e7 + 9, K = 1 << 16;
ulong a[N], b[N];
int c[K];

// 4 прохода по 16 бит, каждый - устойчивая сортировка подсчётом. O(4 * (n + K))
void radixSort(int n) {
    for (int s = 0; s < 64; s += 16) {
        fill(c, c + K, 0);
        for (int i = 0; i < n; ++i)
            ++c[a[i] >> s & K - 1];
        for (int i = 1; i < K; ++i)
            c[i] += c[i - 1];
        for (int i = n - 1; i >= 0; --i)
            b[--c[a[i] >> s & K - 1]] = a[i];
        copy(b, b + n, a);
    }
}
