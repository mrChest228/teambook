// Коэффициенты многочлена степени < n по n точкам, O(n^2)
// 0 <= x[i], y[i] < mod, x[i] разные. inv из 5.2
vector <long> interp(vector <long> x, vector <long> y) {
    int n = x.size();
    vector <long> m(n + 1), q(n + 1), res(n);
    m[0] = 1; // m = (X - x[0])...(X - x[n - 1])
    for (int i = 0; i < n; ++i)
        for (int j = i; j >= 0; --j) {
            m[j + 1] = (m[j + 1] + m[j]) % mod;
            m[j] = m[j] * (mod - x[i]) % mod;
        }
    for (int i = 0; i < n; ++i) {
        long d = 0; // Знаменатель L_i = q(x[i])
        for (int j = n - 1; j >= 0; --j) { // q = m / (X - x[i])
            q[j] = (m[j + 1] + q[j + 1] * x[i]) % mod;
            d = (d * x[i] + q[j]) % mod;
        }
        d = y[i] * inv(d) % mod;
        for (int j = 0; j < n; ++j) // res += y[i] * L_i
            res[j] = (res[j] + d * q[j]) % mod;
    }
    return res; // P = res[0] + res[1] * X + ...
}
