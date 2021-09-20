#include <bits/stdc++.h>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
using ll = long long;
int xpow(ll a, ll b, const ll MOD) {
    ll ret = 1;
    while (b) {
        if (b & 1)
            ret = ret * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return int(ret);
}
int main() {
#ifdef RINNE
    freopen("in", "r", stdin);
#endif
    cc_hash_table<int, int> mp;
    ll MOD, A, B;
    cin >> MOD >> A >> B;
    ll m = sqrt(MOD);
    for (int i = 0; i < m; i++) {
        mp[xpow(A, i, MOD) * B % MOD] = i;
    }
    for (int i = 1; i <= m; i++) {
        ll cur = xpow(A, i * m, MOD);
        if (mp.find(cur)!=mp.end()) {
            cout << i * m - mp[cur] << endl;
            return 0;
        }
    }
    cout << "no solution" << endl;
    return 0;
}
