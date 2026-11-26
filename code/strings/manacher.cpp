vector <int> manacher(const string &s) { // s без $, # и ^
    string t = "$#";
    for (char c : s)
        t += c, t += '#';
    t += '^';
    vector <int> d(t.size());
    for (int i = 1, l = 1, r = 0; i + 1 < t.size(); ++i) {
        int k = max(0, min(d[l + r - i], r - i));
        while (t[i - k - 1] == t[i + k + 1])
            ++k;
        d[i] = k;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    return d;
}
// d[i]: длина наибольшего палиндрома в s с центром в t[i]
// s = "abaab", t = "$#a#b#a#a#b#^":
// d[4] = 3 ("aba", центр b), d[7] = 4 ("baab", центр #)
