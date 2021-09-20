#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const int MOD = 19260817;
const int maxn = 1e3;
int inv[maxn + 555];
int invp[maxn + 555];
int p[maxn + 555];
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    inv[1] = 1;
    for (int i = 2; i <= maxn; i++)
        inv[i] = (ll)inv[MOD % i] * (MOD - MOD / i) % MOD;
    p[0] = 1;
    for (int i = 1; i <= maxn; i++)
        p[i] = (ll)p[i - 1] * i % MOD;
    invp[0] = 1;
    for (int i = 1; i <= maxn; i++)
        invp[i] = (ll)invp[i - 1] * inv[i] % MOD;
    auto C = [&](int a, int b) -> ll {
        if (a < b)
            return 0;
        else
            return (ll)p[a] * invp[b] % MOD * invp[a - b] % MOD;
    };
    int a, b;
    int cas;
    cin >> cas;
    while (cas--) {
        cin >> a >> b;
        ll ans = C(a - 1, b - 1);
        cout << ans << ' ';
    }
    cout << '\n';
    return 0;
}
