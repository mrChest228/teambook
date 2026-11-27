vector <int> colorBip(int n, vector <pair <int, int>> &e) {
    int D = 0;
    vector <int> deg(n), ans(e.size());
    for (auto [x, y] : e)
        D = max({D, ++deg[x], ++deg[y]});
    vector <vector <int>> to(n, vector <int>(D, -1)); // to[v][c] - сосед v по ребру цвета c
    for (auto [x, y] : e) {
        int a = 0, b = 0;
        while (to[x][a] != -1)
            ++a;
        while (to[y][b] != -1)
            ++b;
        for (int v = y, c = a; v != -1; c ^= a ^ b) { // Путь a, b, a, ... из y: меняем a и b местами
            int u = to[v][c];
            swap(to[v][a], to[v][b]);
            v = u;
        }
        to[x][a] = y;
        to[y][a] = x;
    }
    for (int i = 0; i < e.size(); ++i)
        while (to[e[i].f][ans[i]] != e[i].s)
            ++ans[i];
    return ans;
}
