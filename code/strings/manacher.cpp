vector <int> manacher(string &s) {
    string t;
    for (char x : s) {
        if (t.size())
            t += '=';
        t += x;
    }
    int m = t.size();
    vector <int> d(m);
    for (int i = 1, mx = 1; i < m; ++i) { // mx: центр самого правого
        int k = max(int(0), min(d[2 * mx - i], mx + d[mx] - i));
        while (k < i && i + k + 1 < m &&
               t[i - k - 1] == t[i + k + 1])
            ++k;
        d[i] = k;
        if (i + k >= mx + d[mx])
            mx = i;
    }
    return d;
}
// t[i - d[i]..i + d[i]] - палиндром. Длина в s: d[i] + 1,
// если t[i + d[i]] - буква, иначе d[i]
// s = "abaab", t = "a=b=a=a=b": d[2] = 2 ("aba"),
// d[5] = 3 ("=baab=", в s "baab")
