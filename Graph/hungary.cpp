//hdu2063
#include <bits/stdc++.h>
using namespace std;
int hungary(const vector<vector<int>> &G, int N, int M) {
    vector<int> go(N + 5, -1);
    vector<int> fa(M + 5, -1);
    deque<bool> vis(M + 5);
    function<bool(int)> dfs = [&](int x) {
        for (int i : G[x]) {
            if (!vis[i]) {
                vis[i] = true;
                if (fa[i] == -1 || dfs(fa[i])) {
                    fa[i] = x;
                    go[x] = i;
                    return true;
                }
            }
        }
        return false;
    };
    int res = 0;
    for (int i = 1; i <= N; i++) {
        if (go[i] == -1) {
            fill(vis.begin(), vis.end(), false);
            res += dfs(i);
        }
    }
    return res;
}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout.precision(10);
    cout << fixed;
    int k, n, m;
    while (cin >> k && k) {
        cin >> n >> m;
        vector<vector<int>> V(n + 5);
        for (int i = 0; i < k; i++) {
            int a, b;
            cin >> a >> b;
            V[a].emplace_back(b);
        }
        cout << hungary(V, n, m) << endl;
    }
    return 0;
}
