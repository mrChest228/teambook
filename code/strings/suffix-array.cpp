void sufArr(const string &s, int *sf, int *num, int *lcp) {
    assert(s.back() == '$');
    int n = s.size();
    // static: stored like globals, not on the stack; not cleared between calls
    static int pr[N], tmp[N];
#define blk num // '$' makes all blocks different, so blk[i] is the position of i in sf, i.e. num
    iota(sf, sf + n, 0);
    sort(sf, sf + n, [&](int i, int j) {
        return s[i] < s[j];
    });
    blk[sf[0]] = 0;
    for (int i = 1; i < n; ++i)
        blk[sf[i]] = blk[sf[i - 1]] + (s[sf[i - 1]] < s[sf[i]]);
    for (int k = 1; blk[sf[n - 1]] < n - 1; k <<= 1) { // all blks are different after the end of sufArr
        // tmp: suffixes sorted by second half
        for (int i = 0; i < n; ++i)
            tmp[i] = sf[i] - k + n * (sf[i] < k);
        fill(pr, pr + n, 0);
        for (int i = 0; i < n; ++i)
            ++pr[blk[i] + 1];
        for (int i = 2; i < n; ++i)
            pr[i] += pr[i - 1];
        for (int i = 0; i < n; ++i)
            sf[pr[blk[tmp[i]]]++] = tmp[i];
        // tmp is free now, store new blocks in it
        // equal first halves have no '$', so sf[i] + k < n
        tmp[sf[0]] = 0;
        for (int i = 1; i < n; ++i)
            tmp[sf[i]] = tmp[sf[i - 1]] + (blk[sf[i - 1]] < blk[sf[i]] || blk[sf[i - 1] + k] < blk[sf[i] + k]);
        copy(tmp, tmp + n, blk);
    }
#undef blk
    lcp[n - 1] = 0; // may be left from the previous call
    for (int i = 0, cur = 0; i < n; ++i, cur -= (cur > 0)) {
        if (num[i] == n - 1)
            continue;
        int nxt = sf[num[i] + 1];
        while (s[i + cur] == s[nxt + cur])
            ++cur;
        lcp[num[i]] = cur;
    }
}
