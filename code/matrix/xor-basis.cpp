ulong b[64];
int r;

bool add(ulong x) {
    for (int i = 63; i >= 0; --i)
        if (x >> i & ulong(1)) {
            if (b[i])
                x ^= b[i];
            else {
                b[i] = x;
                ++r;
                return true;
            }
        }
    return false;
}
ulong mx(ulong x = 0) {
    for (int i = 63; i >= 0; --i)
        if ((x ^ b[i]) > x)
            x ^= b[i];
    return x;
}
ulong kth(ulong k) {
    ulong c[64];
    for (int i = 0; i < 64; ++i)
        c[i] = b[i];
    for (int i = 63; i >= 0; --i)
        if (c[i])
            for (int j = i + 1; j < 64; ++j)
                if (c[j] >> i & ulong(1))
                    c[j] ^= c[i];
    ulong ans = 0;
    for (int i = 0, bit = 0; i < 64; ++i)
        if (c[i]) {
            if (k >> bit & ulong(1))
                ans ^= c[i];
            ++bit;
        }
    return ans;
}
