#include <bits/stdc++.h>
using namespace std;
vector<int> manacher(const string &a) {
    vector<char> sb{'#', '$'};
    for (int i = 0; i < (int)a.size(); i++) {
        sb.push_back(a[i]);
        sb.push_back('$');
    }
    vector<int> ret(sb.size(), 1);
    int centerOfCycle = 0, rEndOfCycle = 0;
    for (int i = 0; i < (int)sb.size(); i++) {
        if (rEndOfCycle > i) {
            ret[i] = min(ret[2 * centerOfCycle - i], rEndOfCycle - i);
        }
        while (sb[i + ret[i]] == sb[i - ret[i]])
            ret[i]++;
        if (i + ret[i] > rEndOfCycle) {
            rEndOfCycle = i + ret[i];
            centerOfCycle = i;
        }
    }
    return ret;
}
int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout.precision(10);
    cout << fixed;
    string a;
    cin >> a;
    vector<int> res = manacher(a);
    int ans = 0;
    for (int i : res) {
        ans = max(ans, i - 1);
    }
    cout << ans << '\n';
    return 0;
}
