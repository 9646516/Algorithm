#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 1e9 + 7;
namespace linear_seq {
#define rep(i, a, n) for (long long i = a; i < n; i++)
#define SZ(x) ((long long)(x).size())
    const long long N = 10010;
    ll xpow(ll a, ll b) {
        ll res = 1;
        a %= MOD;
        assert(b >= 0);
        for (; b; b >>= 1) {
            if (b & 1)
                res = res * a % MOD;
            a = a * a % MOD;
        }
        return res;
    }
    ll res[N], base[N], _c[N], _md[N];
    vector<long long> Md;
    void mul(ll *a, ll *b, long long k) {
        rep(i, 0, k + k) _c[i] = 0;
        rep(i, 0, k) if (a[i]) rep(j, 0, k) _c[i + j] = (_c[i + j] + a[i] * b[j]) % MOD;
        for (long long i = k + k - 1; i >= k; i--)
            if (_c[i])
                rep(j, 0, SZ(Md)) _c[i - k + Md[j]] = (_c[i - k + Md[j]] - _c[i] * _md[Md[j]]) % MOD;
        rep(i, 0, k) a[i] = _c[i];
    }
    long long solve(ll n, vector<long long> a, vector<long long> b) {
        ll ans = 0, pnt = 0;
        long long k = SZ(a);
        assert(SZ(a) == SZ(b));
        rep(i, 0, k) _md[k - 1 - i] = -a[i];
        _md[k] = 1;
        Md.clear();
        rep(i, 0, k) if (_md[i] != 0) Md.push_back(i);
        rep(i, 0, k) res[i] = base[i] = 0;
        res[0] = 1;
        while ((1ll << pnt) <= n)
            pnt++;
        for (long long p = pnt; p >= 0; p--) {
            mul(res, res, k);
            if ((n >> p) & 1) {
                for (long long i = k - 1; i >= 0; i--)
                    res[i + 1] = res[i];
                res[0] = 0;
                rep(j, 0, SZ(Md)) res[Md[j]] = (res[Md[j]] - res[k] * _md[Md[j]]) % MOD;
            }
        }
        rep(i, 0, k) ans = (ans + res[i] * b[i]) % MOD;
        if (ans < 0)
            ans += MOD;
        return ans;
    }
    vector<long long> BM(vector<long long> s) {
        vector<long long> C(1, 1), B(1, 1);
        long long L = 0, m = 1, b = 1;
        rep(n, 0, SZ(s)) {
            ll d = 0;
            rep(i, 0, L + 1) d = (d + (ll)C[i] * s[n - i]) % MOD;
            if (d == 0)
                ++m;
            else if (2 * L <= n) {
                vector<long long> T = C;
                ll c = MOD - d * xpow(b, MOD - 2) % MOD;
                while (SZ(C) < SZ(B) + m)
                    C.push_back(0);
                rep(i, 0, SZ(B)) C[i + m] = (C[i + m] + c * B[i]) % MOD;
                L = n + 1 - L;
                B = T;
                b = d;
                m = 1;
            } else {
                ll c = MOD - d * xpow(b, MOD - 2) % MOD;
                while (SZ(C) < SZ(B) + m)
                    C.push_back(0);
                rep(i, 0, SZ(B)) C[i + m] = (C[i + m] + c * B[i]) % MOD;
                ++m;
            }
        }
        return C;
    }
    long long gao(vector<long long> a, ll n) {
        vector<long long> c = BM(a);
        c.erase(c.begin());
        rep(i, 0, SZ(c)) c[i] = (MOD - c[i]) % MOD;
        return solve(n, c, vector<long long>(a.begin(), a.begin() + SZ(c)));
    }
}; // namespace linear_seq
