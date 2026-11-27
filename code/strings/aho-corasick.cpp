// O(N log K), sparse edges
namespace linear {
const int N = 100005;
map <char, int> to[N];
int suf[N], cnt = 1;
vector <int> q;

int add(string &s) {
    int v = 0;
    for (char c : s) {
        if (!to[v].count(c))
            to[v][c] = cnt++;
        v = to[v][c];
    }
    return v;
}
void build() {
    q = {0};
    for (int i = 0; i < q.size(); ++i) {
        int v = q[i];
        for (auto [c, u] : to[v]) {
            int p = suf[v];
            while (p && !to[p].count(c))
                p = suf[p];
            suf[u] = v && to[p].count(c) ? to[p][c] : 0;
            q.pb(u);
        }
    }
}
int go(int v, char c) {
    while (v && !to[v].count(c))
        v = suf[v];
    return to[v].count(c) ? to[v][c] : 0;
}
}

// O(NK), lazy transitions
namespace dense {
const int N = 100005;
const int K = 26;
int to[N][K], go[N][K], suf[N], par[N], pc[N], cnt = 1;

void init() {
    memset(to, 0, sizeof(to));
    memset(go, -1, sizeof(go));
    memset(suf, -1, sizeof(suf));
    cnt = 1;
    suf[0] = 0;
}
int add(string &s) {
    int v = 0;
    for (char c : s) {
        int x = c - 'a';
        if (!to[v][x]) {
            to[v][x] = cnt++;
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
}

// Частоты: заведите cnt[N], при проходе t увеличивайте cnt[v], затем по q с конца: cnt[suf[v]] += cnt[v].
// Для dense q строится обходом trie; map можно заменить одной hash map по v * K + c: быстрее и экономнее, но возможны коллизии.
