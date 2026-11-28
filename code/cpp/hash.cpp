// splitmix64, R - случайный сдвиг против заготовленных тестов
struct H {
    static inline ulong R = chrono::steady_clock::now().time_since_epoch().count();
    size_t operator()(ulong x) const {
        x += R + 0x9e3779b97f4a7c15;
        x = (x ^ x >> 30) * 0xbf58476d1ce4e5b9;
        x = (x ^ x >> 27) * 0x94d049bb133111eb;
        return x ^ x >> 31;
    }
    // Не H(a) ^ H(b): у пар (x, x) хеш был бы 0, у (a, b) и (b, a) - равный
    template <class A, class B>
    size_t operator()(pair <A, B> p) const {
        return (*this)(p.f ^ (*this)(p.s));
    }
};
gp_hash_table <int, int, H> mp;
unordered_map <pair <int, int>, int, H> mpPair;
