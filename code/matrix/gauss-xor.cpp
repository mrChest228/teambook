const int N = 4e3 + 9, K = 8; // K ~ log2(n) - 3
int n, m;
int pre[N], his[N]; // pre - K бит строки в текущем блоке, his - маска опорных строк блока, которые в неё надо добавить
bitset <N> a[N], t[1 << K]; // t[mask] - xor опорных строк блока из mask

// Ступенчатый вид a (n строк, m столбцов), возвращает ранг. O(n * m * (m / 64) / K)
int gauss() {
    int r = 0;
    for (int c = 0; c < m && r < n; c += K) {
        int k = min(K, m - c), p = 0;
        for (int i = r; i < n; ++i) {
            pre[i] = his[i] = 0;
            for (int j = 0; j < k; ++j)
                pre[i] |= a[i][c + j] << j;
        }
        for (int j = 0; j < k && r + p < n; ++j) {
            int v = r + p, i = v;
            while (i < n && !(pre[i] >> j & 1))
                ++i;
            if (i == n)
                continue;
            swap(a[v], a[i]);
            swap(pre[v], pre[i]);
            swap(his[v], his[i]);
            a[v] ^= t[his[v]]; // Опорная строка нужна целиком
            for (int mask = 0; mask < 1 << p; ++mask)
                t[mask | 1 << p] = t[mask] ^ a[v];
            for (i = v + 1; i < n; ++i)
                if (pre[i] >> j & 1) {
                    pre[i] ^= pre[v];
                    his[i] ^= 1 << p;
                }
            ++p;
        }
        r += p;
        for (int i = r; i < n; ++i)
            a[i] ^= t[his[i]]; // Один длинный xor на строку вместо p
    }
    return r;
}

// Решение системы после r = gauss(), правая часть - последний столбец (m - 1). Нет решения - false
bool solve(int r, bitset <N> &x) {
    x.reset();
    for (int i = r - 1; i >= 0; --i) {
        int c = a[i]._Find_first();
        if (c == m - 1)
            return false;
        x[c] = a[i][m - 1] ^ (a[i] & x).count() & 1;
    }
    return true;
}
