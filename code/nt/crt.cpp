pair <long, long> crt(long a, long n, long b, long m) {
    if (n < m) {
        swap(n, m);
        swap(a, b);
    }
    long x, y, g = gcdex(n, x, m, y);
    assert((a - b) % g == 0); // else no solution
    m /= g;
    x = (b - a) / g % m * x % m * n + a;
    return {x + (x < 0) * n * m, n * m};
}
