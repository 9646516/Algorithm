const int INF = 1e9;
// AGC031E
// AGC034D
//負辺あったら壊れるからBellman-Fordとかやるといいんじゃない？
#define rng(i, a, b) for (int i = int(a); i < int(b); i++)
#define rep(i, b) rng(i, 0, b)
template <class D> struct mincf {
    template <class t> using vc = vector<t>;
    template <class t> using vvc = vc<vc<t>>;
    using pi = pair<int, int>;
    using vi = vc<int>;
    using P = pair<D, int>;
    struct E {
        int to, rev, cap;
        D cost;
    };
    int n;
    vvc<E> g;
    vc<D> h, d;
    vi pv, pe;
    mincf(int nn) : n(nn), g(n), h(n), d(n), pv(n), pe(n) {}
    pi ae(int a, int b, D cost, int cap) {
        pi res(a, g[a].size());
        g[a].push_back({b, (int)g[b].size(), cap, cost});
        g[b].push_back({a, (int)g[a].size() - 1, 0, -cost});
        return res;
    }
    P go(int s, int t, int f) {
        priority_queue<P, vc<P>, greater<P>> q;
        fill(d.begin(), d.end(), INF);
        d[s] = 0;
        q.push(P(0, s));
        while (q.size()) {
            D a;
            int v;
            tie(a, v) = q.top();
            q.pop();
            if (d[v] < a)
                continue;
            rep(i, (int)g[v].size()) {
                E e = g[v][i];
                if (e.cap > 0) {
                    D w = d[v] + e.cost + h[v] - h[e.to];
                    if (w < d[e.to]) {
                        d[e.to] = w;
                        q.push(P(w, e.to));
                        pv[e.to] = v;
                        pe[e.to] = i;
                    }
                }
            }
        }
        if (d[t] == INF)
            return P(0, 0);
        rep(i, n) h[i] = min(h[i] + d[i], INF);
        int a = f;
        for (int v = t; v != s; v = pv[v])
            a = min(a, g[pv[v]][pe[v]].cap);
        for (int v = t; v != s; v = pv[v]) {
            E &e = g[pv[v]][pe[v]];
            e.cap -= a;
            g[e.to][e.rev].cap += a;
        }
        return P(a * h[t], a);
    }
    D calc(int s, int t, int f) {
        D res = 0;
        while (f > 0) {
            P w = go(s, t, f);
            if (w.second == 0)
                return INF;
            f -= w.second;
            res += w.first;
        }
        return res;
    }
};
