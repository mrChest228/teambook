int t[N]; // Индексы с 1

int sum(int r) {
    int res = 0;
    for (; r > 0; r -= r & -r)
        res += t[r];
    return res;
}
int sum(int l, int r) {
    return sum(r) - sum(l - 1);
}
void add(int k, int x) {
    for (; k <= n; k += k & -k)
        t[k] += x;
}
int lowerBound(int s) {
    int k = 0;
    for (int l = LOGN; l >= 0; --l) {
        if (k + (1 << l) <= n && t[k + (1<<l)] < s) {
            k += (1 << l);
            s -= t[k];
        }
    }
    return k;
}
