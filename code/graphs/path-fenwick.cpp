int tin[N], tout[N], k = 1; // Времена 1..2n, Фенвик t на 2n
vector <int> g[N];

void dfs(int v, int p) {
    tin[v] = k++;
    for (int u : g[v])
        if (u != p)
            dfs(u, v);
    tout[v] = k++;
}
// 1) Значение в вершине меняется, сумма на пути корень - v
void addVertex(int v, int x) {
    add(tin[v], x);
    add(tout[v], -x);
}
int sumToRoot(int v) {
    return sum(tin[v]);
}
// 2) Прибавление на пути корень - v, значение в вершине (отдельный Фенвик)
void addToRoot(int v, int x) {
    add(tin[v], x);
}
int getVertex(int v) {
    return sum(tout[v]) - sum(tin[v] - 1);
}
