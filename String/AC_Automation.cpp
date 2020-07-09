#include <bits/stdc++.h>
using namespace std;
const int maxn = 50 * 10000 + 5;
const int ALPHA = 26;
struct AC_Automation {
    int next[maxn][ALPHA], fail[maxn], val[maxn];
    int idx, root;
    int create() {
        for (int i = 0; i < ALPHA; i++)
            next[idx][i] = -1;
        val[idx] = 0;
        return idx++;
    }
    void init() {
        idx = 0;
        root = create();
    }
    void build() {
        queue<int> ans;
        fail[root] = root;
        for (int i = 0; i < ALPHA; i++) {
            if (next[root][i] == -1)
                next[root][i] = root;
            else {
                fail[next[root][i]] = root;
                ans.push(next[root][i]);
            }
        }
        while (!ans.empty()) {
            int now = ans.front();
            ans.pop();
            for (int i = 0; i < ALPHA; i++) {
                if (next[now][i] == -1)
                    next[now][i] = next[fail[now]][i];
                else {
                    fail[next[now][i]] = next[fail[now]][i];
                    ans.push(next[now][i]);
                }
            }
        }
    }
    void insert(const string &a) {
        int now = root;
        for (int i = 0; i < (int)a.size(); i++) {
            if (next[now][a[i] - 'a'] == -1)
                next[now][a[i] - 'a'] = create();
            now = next[now][a[i] - 'a'];
        }
        val[now]++;
    }
    void insert(char a[]) {
        int len = strlen(a);
        int now = root;
        for (int i = 0; i < len; i++) {
            if (next[now][a[i] - 'a'] == -1)
                next[now][a[i] - 'a'] = create();
            now = next[now][a[i] - 'a'];
        }
        val[now]++;
    }
    int query(const string &a) {
        int now = root;
        int ret = 0;
        for (int i = 0; i < (int)a.size(); i++) {
            now = next[now][a[i] - 'a'];
            int p = now;
            while (p != root) {
                ret += val[p];
                val[p] = 0;
                p = fail[p];
            }
        }
        return ret;
    }
    int query(char a[]) {
        int len = strlen(a);
        int now = root;
        int ret = 0;
        for (int i = 0; i < len; i++) {
            now = next[now][a[i] - 'a'];
            int p = now;
            while (p != root) {
                ret += val[p];
                val[p] = 0;
                p = fail[p];
            }
        }
        return ret;
    }
} AC;
int q, n;
string a, b;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int cas;
    cin >> cas;
    while (cas--) {
        int n;
        AC.init();
        cin >> n;
        string x;
        while (n--) {
            cin >> x;
            AC.insert(x);
        }
        AC.build();
        cin >> x;
        cout << AC.query(x) << '\n';
    }
    return 0;
}
