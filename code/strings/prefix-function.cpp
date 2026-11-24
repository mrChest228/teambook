vector <int> prefFun(string s) {
    int n = s.size();
    vector <int> p(n);
    for (int i = 1; i < n; i++) {
        int cur = p[i - 1];
        while (s[i] != s[cur] && cur > 0) // уменьшаем cur значение, пока новый символ не сматчится
            cur = p[cur - 1];
        if (s[i] == s[cur])
            p[i] = cur + 1;
    }
    return p;
}
