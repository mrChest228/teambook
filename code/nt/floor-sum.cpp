long floorSum(long n, long m, long a, long b) { // Ответ должен помещаться в long
    int128 ans = 0;
    while (true) {
        long qa = divFloor(a, m), qb = divFloor(b, m);
        ans += int128(qa) * n * (n - 1) / 2 + int128(qb) * n;
        a -= qa * m;
        b -= qb * m;
        int128 y = int128(a) * n + b;
        if (y < m)
            return (long)ans;
        n = y / m;
        b = y % m;
        swap(m, a);
    }
}
