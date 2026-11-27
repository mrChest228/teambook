// Кол-во y из [0, L] с y & x == 0
long cntY(long L, long x) {
    long res = 0;
    for (int i = 62; i >= 0; --i)
        if (L >> i & 1) {
            res += 1LL << __builtin_popcountll(~x & ((1LL << i) - 1)); // Здесь 0, младшие - любые вне x
            if (x >> i & 1)
                return res;
        }
    return res + 1;
}
// Пар a, b >= 0 с a ^ b == x и a + b <= s
long pairs(long x, long s) {
    return s < x ? 0 : cntY((s - x) / 2, x) << __builtin_popcountll(x);
}
