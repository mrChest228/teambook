int marriage(int n, int m, vector <pair <int, int>> a) {
    sort(a.begin(), a.end());
    int ans = n;
    multiset <int> st;
    for (int j = 0, i = 0; j < m; ++j) {
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
