vector <int> z(string &s) {
    int n = s.size(), l = 0;
    vector <int> z(n);
    for (int i = 1; i < n; ++i) {
        if (i < l + z[l])
            z[i] = min(l + z[l] - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] > l + z[l])
            l = i;
    }
    return z;
}
