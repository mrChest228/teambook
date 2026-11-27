map <char, int> to[N];
int suf[N], sz = 1;
vector <int> q;

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
