// Кол-во y из [0, L] с y & x == 0
int cntY(int L, int x) {
    int res = 0;
    for (int i = 62; i >= 0; --i)
        if (L >> i & 1) {
            res += 1ll << __builtin_popcountll(~x & ((1ll << i) - 1)); // Здесь 0, младшие - любые вне x
            if (x >> i & 1)
                return res;
        }
    return res + 1;
}
// Пар a, b >= 0 с a ^ b == x и a + b <= s
int pairs(int x, int s) {
    return s < x ? 0 : cntY((s - x) / 2, x) << __builtin_popcountll(x);
}
