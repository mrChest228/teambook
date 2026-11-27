vector <int> q;
map <char, int> to[N];
int suf[N], cnt[N], sz = 1;

int add(string &s) {
    int v = 0;
    for (char c : s) {
        if (!to[v].count(c))
            to[v][c] = sz++;
        v = to[v][c];
    }
    return v;
}
int go(int v, char c) {
    while (v && !to[v].count(c))
        v = suf[v];
    return to[v].count(c) ? to[v][c] : 0;
}
void build() {
    q = {0};
    for (int i = 0; i < q.size(); ++i) {
        int v = q[i];
        for (auto [c, u] : to[v]) {
            suf[u] = v ? go(suf[v], c) : 0;
            q.pb(u);
        }
    }
}
vector <int> occ(vector <string> &s, string &t) {
    vector <int> end, res;
    for (string &x : s)
        end.pb(add(x));
    build();
    int v = 0;
    for (char c : t) {
        v = go(v, c);
        ++cnt[v];
    }
    for (int i = q.size() - 1; i > 0; --i)
        cnt[suf[q[i]]] += cnt[q[i]];
    for (int v : end)
        res.pb(cnt[v]);
    return res;
}
