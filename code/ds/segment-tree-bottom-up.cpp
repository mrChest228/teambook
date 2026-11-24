int n, h, sz[N + N];
long sum[N + N], mn[N + N], mx[N + N], lzMul[N + N], lzAdd[N + N];
void apply(int v, long mul, long add) {
    sum[v] = (sum[v] * mul + sz[v] * add) % MOD;
    mn[v] = (mn[v] * mul + add) % MOD;
    mx[v] = (mx[v] * mul + add) % MOD;
    if (v < n) {
        lzMul[v] = (lzMul[v] * mul) % MOD;
        lzAdd[v] = (lzAdd[v] * mul + add) % MOD;
    }
}
void calc(int v) {
    sum[v] = (sum[v << 1] + sum[v << 1 | 1]) % MOD;
    mn[v] = min(mn[v << 1], mn[v << 1 | 1]);
    mx[v] = max(mx[v << 1], mx[v << 1 | 1]);
}
void push(int v) {
    for (int s = h; s > 0; --s) {
        int w = v >> s;
        if (lzMul[w] != 1 || lzAdd[w] != 0) {
            apply(w << 1, lzMul[w], lzAdd[w]);
            apply(w << 1 | 1, lzMul[w], lzAdd[w]);
            lzMul[w] = 1;
            lzAdd[w] = 0;
        }
    }
}
void build(int v) {
    while (v > 1) {
        v >>= 1;
        calc(p);
    }
}
void init() {
    h = 32 - __builtin_clz(n);
    for (int i = n; i < n + n; ++i) {
        sum[i] = mn[i] = mx[i] = a[i - n];
        lzMul[i] = sz[i] = 1;
        lzAdd[i] = 0;
    }
    for (int i = n - 1; i > 0; --i) {
        calc(i);
        sz[i] = sz[i << 1] + sz[i << 1 | 1];
        lzMul[i] = 1; lzAdd[i] = 0;
    }
}
void upd(int l, int r, long mul, long add) {
    l += n; r += n;
    int l0 = l, r0 = r;
    push(l); push(r - 1);
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) apply(l++, mul, add);
        if (r & 1) apply(--r, mul, add);
    }
    build(l0); build(r0 - 1);
}
long get(int l, int r) {
    l += n; r += n;
    push(l); push(r - 1);
    long res = 0;
    for (; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res = (res + sum[l++]) % MOD;
        if (r & 1) res = (res + sum[--r]) % MOD;
    }
    return res;
}
