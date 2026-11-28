const int N = 2e5 + 9;
pair <int, int> a[N]; // Жениху подходят невесты a[i].f..a[i].s из 0..m - 1

// Сколько женихов останутся без пары. O((n + m) * log(n))
int marriage(int n, int m) {
    sort(a, a + n);
    int ans = n;
    multiset <int> st;
    for (int j = 0, i = 0; j < m; ++j) { // Невесте j - жених с мин. правой границей
        while (i < n && a[i].f <= j)
            st.in(a[i++].s);
        while (st.size() && *st.begin() < j)
            st.erase(st.begin());
        if (st.size()) {
            --ans;
            st.erase(st.begin());
        }
    }
    return ans;
}
