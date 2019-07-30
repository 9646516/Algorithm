using ll = long long;
using T = pair<ll, ll>;
const int N = 1 << 22;
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
template <int SZ> struct Seg {
    T seg[2 * SZ], ID = make_pair(LONG_LONG_MIN, LONG_LONG_MAX);
    Seg() { F0R(i, 2 * SZ) seg[i] = ID; }
    T comb(const T &a, const T &b) const {
        return make_pair(max(a.first, b.first), min(a.second, b.second));
    }
    void build() { F0Rd(i, SZ) seg[i] = comb(seg[2 * i], seg[2 * i + 1]); }
    void upd(int p, T value) {
        for (seg[p += SZ] += value; p > 1; p >>= 1)
            seg[p >> 1] = comb(seg[(p | 1) ^ 1], seg[p | 1]);
    }
    T query(int l, int r) {
        T res1 = ID, res2 = ID;
        r++;
        for (l += SZ, r += SZ; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                res1 = comb(res1, seg[l++]);
            if (r & 1)
                res2 = comb(seg[--r], res2);
        }
        return comb(res1, res2);
    }
};
