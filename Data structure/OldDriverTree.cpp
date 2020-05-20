template <typename T> struct OldDriverTree {
    struct node {
        int l, r;
        mutable T v;
        explicit node(int L, int R = -1, T V = 0) : l(L), r(R), v(V) {}
        bool operator<(const node &o) const { return l < o.l; }
    };
    using iter = typename set<OldDriverTree<T>::node>::iterator;
    using const_iter = typename set<OldDriverTree<T>::node>::const_iterator;
    set<node> st;
    explicit OldDriverTree(const int N) {
        st.insert(node(1, N, 0));
        st.insert(node(N + 1, N + 1, 0));
    }
    explicit OldDriverTree(const vector<T> &x) {
        for (int i = 0; i < (int)x.size(); i++) {
            st.insert(node(i + 1, i + 1, x[i]));
        }
        st.insert(node(x.size() + 1, x.size() + 1, 0));
    }
    iter split(int pos) {
        iter it = st.lower_bound(node(pos));
        if (it != st.end() && it->l == pos)
            return it;
        --it;
        int L = it->l, R = it->r;
        T V = it->v;
        st.erase(it);
        st.insert(node(L, pos - 1, V));
        return st.insert(node(pos, R, V)).first;
    }
    void add(int l, int r, const T val, const T MOD) {
        iter R = split(r + 1), L = split(l);
        while (L != R) {
            L->v = (L->v + val) % MOD;
            L++;
        }
    }
    void mul(int l, int r, const T val, const T MOD) {
        iter R = split(r + 1), L = split(l);
        while (L != R) {
            L->v = L->v * val % MOD;
            L++;
        }
    }
    void assign(int l, int r, const T val) {
        iter R = split(r + 1), L = split(l);
        st.erase(L, R);
        st.insert(node(l, r, val));
    }
    void insert(T val) {
        iter p = prev(st.end());
        p->v = val;
        T last = p->l;
        st.insert(node(last + 1, last + 1, 0));
    }
#ifdef RINNE
    void out(iter p) { cout << p->l << ' ' << p->r << ' ' << p->v << endl; }
    void out(node p) { cout << p.l << ' ' << p.r << ' ' << p.v << endl; }
#endif
    T sum(int l, int r, const T MOD) {
        T ret = 0;
        iter R = split(r + 1), L = split(l);
        while (L != R) {
            ret = (ret + 1LL * L->v * (L->r - L->l + 1)) % MOD;
            L++;
        }
        return ret;
    }
};
