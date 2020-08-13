using ll = long long;
const int MOD = 1e9 + 7;
// Kth,矩阵大小,初始值,转移方程
// a F0,F1 =>Fn,Fn+1
void solve(ll n, int m, int a[], int c[]) {
    if (!n)
        return;
    vector<ll> v(m, 1 % MOD), u(m << 1);
    ll mask = !!n;
    for (ll i = n; i > 1; i >>= 1) {
        mask <<= 1;
    }
    for (ll x = 0; mask; mask >>= 1, x <<= 1) {
        fill_n(u.begin(), m << 1, 0);
        int b = !!(n & mask);
        x |= b;
        if (x < m) {
            u[x] = 1 % MOD;
        } else {
            for (int i = 0; i < m; i++) {
                for (int j = 0, t = i + b; j < m; j++, t++) {
                    u[t] = (u[t] + v[i] * v[j]) % MOD;
                }
            }
            for (int i = (m << 1) - 1; i >= m; i--) {
                for (int j = 0, t = i - m; j < m; j++, t++) {
                    u[t] = (u[t] + c[j] * u[i]) % MOD;
                }
            }
        }
        copy(u.begin(), u.begin() + m, v.begin());
    }
    for (int i = m; i < 2 * m; i++) {
        a[i] = 0;
        for (int j = 0; j < m; j++) {
            a[i] = (a[i] + (ll)c[j] * a[i + j - m]) % MOD;
        }
    }
    vector<ll> b(m);
    for (int j = 0; j < m; j++) {
        b[j] = 0;
        for (int i = 0; i < m; i++) {
            b[j] = (b[j] + v[i] * a[i + j]) % MOD;
        }
    }
    for (int j = 0; j < m; j++) {
        a[j] = b[j];
    }
}
