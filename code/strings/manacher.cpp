vector <int> manacher(const string &s) {
    string t;
    for (char c : s) {
        if (t.size())
            t += '=';
        t += c;
    }
    int m = t.size();
    vector <int> d(m);
    for (int i = 0, l = 0, r = -1; i < m; ++i) {
        int k = i > r ? 0 : min(d[l + r - i], r - i);
        int a = i - k - 1, b = i + k + 1;
        while (a >= 0 && b < m && t[a] == t[b])
            --a, ++b;
        d[i] = b - i - 1;
        if (b - 1 > r) {
            l = a + 1;
            r = b - 1;
        }
    }
    return d;
}
// t[i - d[i]..i + d[i]] - палиндром. Длина в s: d[i] + 1,
// если t[i + d[i]] - буква, иначе d[i]
// s = "abaab", t = "a=b=a=a=b": d[2] = 2 ("aba"),
// d[5] = 3 ("=baab=", в s "baab")
