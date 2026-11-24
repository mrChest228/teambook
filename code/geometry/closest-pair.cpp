// Квадрат расстояния между двумя ближайшими точками
long closest(vector <pair <long, long>> p) {
    sort(p.begin(), p.end());
    set <pair <long, long>> st; // {y, x}
    long best = 8e18;
    for (int i = 0, j = 0; i < p.size() && best; ++i) {
        long d = sqrtl(best) + 1;
        for (; p[i].f - p[j].f >= d; ++j)
            st.erase({p[j].s, p[j].f});
        for (auto it = st.lower_bound({p[i].s - d, -8e18}); it != st.end() && it->f <= p[i].s + d; ++it) {
            long dx = p[i].f - it->s, dy = p[i].s - it->f;
            best = min(best, dx * dx + dy * dy);
        }
        st.insert({p[i].s, p[i].f});
    }
    return best;
}
