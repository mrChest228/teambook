array <vector <int>, 2> manacher(const string &s) {
    int n = s.size();
    array <vector <int>, 2> d = {vector <int>(n), vector <int>(n)};
    for (int z = 0; z < 2; ++z)
        for (int i = 0, l = 0, r = -1; i < n; ++i) {
            int k = i > r ? 0 : min(d[z][l + r - i + z], r - i + z);
            int a = i - k - 1, b = i + k + 1 - z;
            while (a >= 0 && b < n && s[a] == s[b])
                --a, ++b;
            d[z][i] = i - a - 1;
            if (b - 1 > r) {
                l = a + 1;
                r = b - 1;
            }
        }
    return d;
}
// d[0][i] = k: s[i - k..i + k] - палиндром длины 2k + 1
// d[1][i] = k: s[i - k..i + k - 1] - палиндром длины 2k
// s = "abaab": d[0] = {0, 1, 0, 0, 0}, d[1] = {0, 0, 0, 2, 0}
