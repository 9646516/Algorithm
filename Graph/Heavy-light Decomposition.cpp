using T = int;
const T ID = 0;
template <int SZ> struct Seg {
#define F0R(i, a) for (int i = 0; i < (a); i++)
#define F0Rd(i, a) for (int i = (a)-1; i >= 0; i--)
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
    void set(const T &x) {
        for (int i = 0; i < SZ; i++) {
            seg[i + SZ] = x;
        }
        build();
    }
    void build() { F0Rd(i, SZ) seg[i] = comb(seg[2 * i], seg[2 * i + 1]); }
    T comb(const T &a, const T &b) const { return a + b; }
    void upd(int p, T value) {
        for (seg[p += SZ] = value; p > 1; p >>= 1)
            seg[p >> 1] = comb(seg[(p | 1) ^ 1], seg[p | 1]);
    }
    T ask(int l, int r) {
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
template <int N> struct HLD : public Seg<N> {
    vector<int> V[N];
    int fa[N], dep[N], sum[N], son[N];
    int idx[N]; // 下标转dfs序
    int raw[N]; // dfs序转下标
    int top[N]; // i点所在链的顶端
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
    int lca(int x, int y) {
        int fa1 = top[x], fa2 = top[y];
        while (fa1 != fa2) {
            if (dep[fa1] < dep[fa2]) {
                swap(fa1, fa2);
                swap(x, y);
            }
            x = fa[fa1];
            fa1 = top[x];
        }
        if (dep[x] > dep[y])
            return y;
        else
            return x;
    }
    int distance(int x, int y) {
        int LCA = lca(x, y);
        return dep[x] + dep[y] - dep[LCA] - dep[LCA];
    }
    T query(int x, int y) {
        T ret = ID;
        int fa1 = top[x], fa2 = top[y];
        while (fa1 != fa2) {
            if (dep[fa1] < dep[fa2]) {
                swap(fa1, fa2);
                swap(x, y);
            }
            ret = comb(ret, ask(idx[fa1], idx[x]));
            x = fa[fa1];
            fa1 = top[x];
        }
        if (idx[x] > idx[y])
            swap(x, y);
        ret = comb(ret, ask(idx[x], idx[y]));
        return ret;
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
};
constexpr int N = 1 << (__lg(maxn) + 1);
HLD<N> st;
