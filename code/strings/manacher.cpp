vector <int> manacher(const string &s) {
    if (s.empty())
        return {};
    int n = s.size(), m = 2 * n - 1;
    vector <int> d(m);
    auto equal = [&](int i, int j) {
        return i & 1 || s[i / 2] == s[j / 2];
    };
    for (int i = 0, l = 0, r = -1; i < m; ++i) {
        int k = i > r ? 0 : min(d[l + r - i], r - i);
        while (i - k - 1 >= 0 && i + k + 1 < m && equal(i - k - 1, i + k + 1))
            ++k;
        d[i] = k;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    // Длина в s: при чётном i — 2 * (d[i] / 2) + 1, при нечётном — 2 * ((d[i] + 1) / 2).
    return d;
}
