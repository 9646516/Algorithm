#include <bits/stdc++.h>
using namespace std;
template <typename A, typename B> string to_string(pair<A, B> p);
template <typename A, typename B, typename C> string to_string(tuple<A, B, C> p);
template <typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D> p);
string to_string(const string &s) { return '"' + s + '"'; }
string to_string(const char *s) { return to_string((string)s); }
string to_string(bool b) { return (b ? "true" : "false"); }
string to_string(vector<bool> v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}
template <size_t N> string to_string(bitset<N> v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}
template <typename A> string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}
template <typename A, typename B> string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename A, typename B, typename C> string to_string(tuple<A, B, C> p) { return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")"; }
template <typename A, typename B, typename C, typename D> string to_string(tuple<A, B, C, D> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}
void debug_out() { cerr << endl; }
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}
#ifdef RINNE
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:\t", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif
template <typename base_type, base_type MOD> struct IntMod {
    base_type n;
    IntMod(long long d = 0) { n = (d >= 0 ? d % MOD : (d % MOD + MOD) % MOD); }
    IntMod operator-() const { return build(n == 0 ? 0 : MOD - n); }
    IntMod &operator+=(IntMod a) {
        n = (n >= MOD - a.n ? n - MOD + a.n : n + a.n);
        return *this;
    }
    IntMod &operator-=(IntMod a) {
        n = (n >= a.n) ? n - a.n : n - a.n + MOD;
        return *this;
    }
    IntMod &operator*=(IntMod a) {
        *this = *this * a;
        return *this;
    }
    static IntMod build(base_type n) {
        IntMod r;
        r.n = n;
        return r;
    }
    friend bool operator==(IntMod a, IntMod b) { return a.n == b.n; }
    friend bool operator!=(IntMod a, IntMod b) { return a.n != b.n; }
    friend IntMod operator+(IntMod a, IntMod b) { return build(a.n >= MOD - b.n ? a.n - MOD + b.n : a.n + b.n); }
    friend IntMod operator-(IntMod a, IntMod b) { return build(a.n >= b.n ? a.n - b.n : a.n - b.n + MOD); }
    friend IntMod operator*(IntMod a, IntMod b) { return build(static_cast<base_type>(static_cast<long long>(a.n) * b.n % MOD)); }
    friend istream &operator>>(istream &stream, IntMod &a) {
        stream >> a.n;
        return stream;
    }
    friend ostream &operator<<(ostream &stream, const IntMod &a) {
        stream << a.n;
        return stream;
    }
};
const long long MOD = 1e9 + 7;
using Int = IntMod<int, MOD>;
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
using T = Int;
const T ID = 1;
struct HLD {
    static const int maxn = 1e5 + 555;
    vector<int> V[maxn];
    int fa[maxn],dep[maxn],sum[maxn], son[maxn];
    int idx[maxn]; // 下标转dfs序
    int raw[maxn]; // dfs序转下标
    int top[maxn]; // i点所在链的顶端
    void dfs1(int now, int pre, int d) {
        fa[now] = pre;
        dep[now] = d;
        sum[now] = 1;
        for (int i : V[now]) {
            if (i == pre)
                continue;
            dfs1(i, now, d + 1);
            sum[now] += sum[i];
            if (son[now] == -1 || sum[son[now]] < sum[i])
                son[now] = i;
        }
    }
    void dfs2(int now, int pre, int op, int &dfn) {
        top[now] = op;
        idx[now] = dfn;
        raw[dfn] = now;
        dfn++;
        if (son[now] == -1)
            return;
        dfs2(son[now], now, op, dfn);
        for (int i : V[now]) {
            if (i == pre || i == son[now])
                continue;
            dfs2(i, now, i, dfn);
        }
    }
    static constexpr int N = 1 << (__lg(maxn) + 1);
    template <int SZ> struct Seg {
        T seg[2 * SZ];
        void init() { F0R(i, 2 * SZ) seg[i] = ID; }
        Seg() { init(); }
        void set(const vector<T> &x) {
            assert((int)x.size() <= SZ);
            for (int i = 0; i < (int)x.size(); i++) {
                seg[i + SZ] = x[i];
            }
            build();
        }
        void build() { F0Rd(i, SZ) seg[i] = comb(seg[2 * i], seg[2 * i + 1]); }
        T comb(const T &a, const T &b) const { return a * b; }
        void upd(int p, T value) {
            for (seg[p += SZ] = value; p > 1; p >>= 1)
                seg[p >> 1] = comb(seg[(p | 1) ^ 1], seg[p | 1]);
        }
        T query(int l, int r) {
            if (l > r)
                return 0;
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
    Seg<N> seg;
    int query(int x, int y) {
        Int ret = 1;
        int fa1 = top[x], fa2 = top[y];
        while (fa1 != fa2) {
            if (dep[fa1] < dep[fa2]) {
                swap(fa1, fa2);
                swap(x, y);
            }
            ret *= seg.query(idx[fa1], idx[x]);
            x = fa[fa1];
            fa1 = top[x];
        }
        if (idx[x] > idx[y])
            swap(x, y);
        ret *= seg.query(idx[x], idx[y]);
        return ret.n;
    }
    void add(int u, int v) {
        V[u].push_back(v);
        V[v].push_back(u);
    }
    void init(int root = 1) {
        memset(son, -1, sizeof(son));
        int idx = 0;
        dfs1(root, -1, 0);
        dfs2(root, -1, root, idx);
    }
} HLD;

class Solution {
  public:
    vector<int> solve(int n, int m, vector<int> &a, vector<int> &u, vector<int> &v, vector<int> &x, vector<int> &y) {
        for (int i = 0; i < n - 1; i++) {
            int x = u[i], y = v[i];
            HLD.add(x, y);
        }
        HLD.init();
        vector<Int> val;
        for (int i = 0; i < n; i++)
            val.push_back(a[HLD.raw[i] - 1]);
        HLD.seg.set(val);
        vector<int> ret;
        for (int i = 0; i < m; i++) {
            int u = x[i], v = y[i];
            ret.push_back(HLD.query(u, v));
        }
        return ret;
    }
};
