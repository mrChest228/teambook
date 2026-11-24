long isqrt(long x) { long r = sqrt(x); r -= ulong(r) * r > x; r += ulong(r + 1) * (r + 1) <= x; return r; }
