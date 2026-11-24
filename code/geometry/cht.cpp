struct line {
    ld k, b;
    bool operator< (const line &x) const {
        if (k != x.k)
            return k < x.k;
        return b > x.b;
    }
    ld operator() (ld x) const {
        return k * x + b;
    }
};
// You can speed up this code by adding "inline" to each func
vector <line> cht;

// If lst.k < new.k, it is maximum CHT, else it's minimum. sort without reverse is for max, sort with reverse is for min
// .  max  .
//  \     /
//   .___.
//
//   .---.
//  /     \
// .  min  .

// it isn't necessary
ld cross(const line &a, const line &b) {
    assert(a.k != b.k);
    return (a.b - b.b) / (b.k - a.k);
}

// it returns cross(b, c) - cross(a, b), but it works when b.b == c.b!!!. If <= 0, delete b from CHT
inline ld cross(const line &a, const line &b, const line &c) { return (b.b - c.b) * (b.k - a.k) - (a.b - b.b) * (c.k - b.k); }

void add(const line &a) { // lst.k != a.k || (lst.k == a.k && lst.b != a.b). "!=" is < or >, depending on what suits you best, from sorting, from the need to find the maximum or minimum along straight lines
    if (cht.size() && cht.back().k == a.k) // The new is a copy of the previous, but worse
        return;
    while (cht.size() > 1 && cross(cht[cht.size() - 2], cht.back(), a) <= 0)
        cht.pop_back();
    cht.pb(a);
}

ld get(ld x) {
    assert(cht.size());
    int l = 0, r = cht.size() - 1;
    while (l < r) {
        int md = (l + r + 1) / 2;
        ld a = cht[md - 1].b - cht[md].b, b = x * (cht[md].k - cht[md - 1].k);
        if (a == b || ((a < b) ^ (cht[md - 1].k > cht[md].k)))
            l = md;
        else
            r = md - 1;
    }
    return cht[l].k * x + cht[l].b;
}

// 1e-9l = long double 1e-9
inline ld _floor(ld x) { return floor(x + 1e-9l); }
inline ld _ceil (ld x) { return ceil (x - 1e-9l); }
