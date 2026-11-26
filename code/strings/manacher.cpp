vector <int> manacher(const string &s) {
    string t;
    for (char x : s) {
        if (t.size())
            t += '=';
        t += x;
    }
    int m = t.size();
    vector <int> d(m);
    for (int i = 1, c = 1; i < m; ++i) { // c: центр самого правого
        int k = max(0, min(d[2 * c - i], c + d[c] - i));
        while (k < i && i + k + 1 < m &&
               t[i - k - 1] == t[i + k + 1])
            ++k;
        d[i] = k;
        if (i + k >= c + d[c])
            c = i;
    }
    return d;
}
// t[i - d[i]..i + d[i]] - палиндром. Длина в s: d[i] + 1,
// если t[i + d[i]] - буква, иначе d[i]
// s = "abaab", t = "a=b=a=a=b": d[2] = 2 ("aba"),
// d[5] = 3 ("=baab=", в s "baab")
