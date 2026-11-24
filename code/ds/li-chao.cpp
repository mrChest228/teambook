const ld oo = 1e18, eps = 1e-9;

struct line {
    ld k, b;
    ld operator() (ld x) const {
        return k * x + b;
    }
};

struct LiChao { // For max
    line ln;
    ld l, md, r;
    LiChao *L = 0, *R = 0;
    LiChao(ld l, ld r, line ln = {0, -oo}): l(l), md((l + r) / 2), r(r), ln(ln) {}
    void add(ld _l, ld _r, line nw) {
        if (r - l < eps) {
            if (ln(l) < nw(l))
                ln = nw;
            return;
        }
        if (_l <= l && r <= _r) {
            if (ln(md) < nw(md) || (ln(md) == nw(md) && nw(l) < ln(l))) // For max
                swap(ln, nw);
            if (ln.k == nw.k)
                return;
            if ((ln.b - nw.b) / (nw.k - ln.k) <= md)
                if (!L)
                    L = new LiChao(l, md, nw);
                else
                    L -> add(_l, _r, nw);
            else
                if (!R)
                    R = new LiChao(md, r, nw);
                else
                    R -> add(_l, _r, nw);
            return;
        }
        if (_l <= md) {
            if (!L)
                L = new LiChao(l, md);
            L -> add(_l, _r, nw);
        }
        if (md < _r) {
            if (!R)
                R = new LiChao(md, r);
            R -> add(_l, _r, nw);
        }
    }
    ld get(ld x) {
        ld ans = ln(x);
        if (x <= md && L)
            ans = max(ans, L -> get(x));
        if (md <= x && R)
            ans = max(ans, R -> get(x));
        return ans;
    }
};
// Main
LiChao tr(0, n);
tr.add(l, r, {k, b});
tr.get(x);
