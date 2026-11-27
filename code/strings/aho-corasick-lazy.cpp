int to[N][K], go[N][K], suf[N], par[N], pc[N], cnt[N], sz = 1;

void init() {
    fill(&go[0][0], &go[0][0] + N * K, -1);
    fill(suf, suf + N, -1);
}
int add(string &s) {
    int v = 0;
    for (char c : s) {
        int x = c - 'a';
        if (!to[v][x]) {
            to[v][x] = sz++;
            par[to[v][x]] = v;
            pc[to[v][x]] = x;
        }
        v = to[v][x];
    }
    return v;
}
int getGo(int v, int c);
int getSuf(int v) {
    if (suf[v] == -1)
        suf[v] = par[v] ? getGo(getSuf(par[v]), pc[v]) : 0;
    return suf[v];
}
int getGo(int v, int c) {
    if (go[v][c] == -1)
        go[v][c] = to[v][c] ? to[v][c] : (v ? getGo(getSuf(v), c) : 0);
    return go[v][c];
}
vector <int> occ(vector <string> &s, string &t) {
    vector <int> end, res;
    for (string &x : s)
        end.pb(add(x));
    vector <int> q = {0};
    for (int i = 0; i < q.size(); ++i)
        for (int c = 0; c < K; ++c)
            if (to[q[i]][c])
                q.pb(to[q[i]][c]);
    int v = 0;
    for (char c : t) {
        v = getGo(v, c - 'a');
        ++cnt[v];
    }
    for (int i = q.size() - 1; i > 0; --i)
        cnt[getSuf(q[i])] += cnt[q[i]];
    for (int v : end)
        res.pb(cnt[v]);
    return res;
}
