// Коэффициенты многочлена степени < n по n точкам, O(n^2)
// 0 <= p[i].f, p[i].s < mod, p[i].f разные. inv из 5.2
// В ld: без % mod, inv(d) -> 1 / d, mod - x[i] -> -x[i]
vector <long> lagrange(const vector <pair <long, long>> &p) {
    int n = p.size();
    vector <long> m(n + 1), q(n + 1), res(n);
    m[0] = 1; // m = (X - p[0].f)...(X - p[n - 1].f)
    for (int i = 0; i < n; ++i) {
        long x = p[i].f;
        for (int j = i; j >= 0; --j) {
            m[j + 1] = (m[j + 1] + m[j]) % mod;
            m[j] = m[j] * (mod - x) % mod;
        }
    }
    for (int i = 0; i < n; ++i) {
        long x = p[i].f, y = p[i].s;
        long d = 0; // Знаменатель L_i = q(p[i].f)
        for (int j = n - 1; j >= 0; --j) { // q = m / (X - p[i].f)
            q[j] = (m[j + 1] + q[j + 1] * x) % mod;
            d = (d * x + q[j]) % mod;
        }
        d = y * inv(d) % mod;
        for (int j = 0; j < n; ++j) // res += p[i].s * L_i
            res[j] = (res[j] + d * q[j]) % mod;
    }
    return res; // P = res[0] + res[1] * X + ...
}
