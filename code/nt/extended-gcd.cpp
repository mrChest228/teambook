long gcdex(long a, long &x, long b, long &y) {
    long x1, y1;
    x = y1 = 1;
    y = x1 = 0;
    while (b > 0) {
        long k = a / b;
        swap(x -= k * x1, x1);
        swap(y -= k * y1, y1);
        swap(a -= k * b, b);
    }
    if (x < 0) {
        if (x1 < 0) {
            x1 *= -1;
            y1 *= -1;
        }
        x += x1;
        y += y1;
    }
    return a;
}
