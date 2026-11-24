bool b[N + N];
int comp[N + N];
vector <int> v[N + N], w[N + N], order;

void add(int x, int y) { //Первый бит обозначает отрицание (0 - x, 1 - !x)
    v[x ^ 1].pb(y); //!x >= y
    v[y ^ 1].pb(x); //!y >= x
    w[y].pb(x ^ 1);
    w[x].pb(y ^ 1);
}
void topSort(int x) {
    if (b[x])
        return;
    b[x] = 1;
    for (int u : v[x])
        topSort(u);
    order.pb(x);
}
void dfs(int x, int c) {
    if (comp[x] > -1)
        return;
    comp[x] = c;
    for (int u : w[x])
        dfs(u, c);
}

//... Добавление ребер ...
for (int i = 0; i < n + n; ++i)
    topSort(i);
reverse(order);
int cnt = 0;
fill(comp, comp + n + n, -1);
for (int u : order)
    dfs(u, cnt++);
for (int i = 0; i < n + n; ++i)
    if (comp[i] == comp[i + 1])
        //No solution
for (int i = 0; i < n; ++i)
    cout << (comp[i + i] < comp[i + i + 1] ? "!" : "") << i << nl;
