#include <bits/stdc++.h>
using namespace std;
const int maxn = 50 * 10000 + 5;
const int ALPHA = 26;
struct AC_Automation {
    int next[maxn][ALPHA], fail[maxn], val[maxn], idx, root;
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
        queue<int> Q;
        fail[root] = root;
        for (int i = 0; i < ALPHA; i++) {
            if (next[root][i] == -1)
                next[root][i] = root;
            else {
                fail[next[root][i]] = root;
                Q.push(next[root][i]);
            }
        }
        while (!Q.empty()) {
            int now = Q.front();
            Q.pop();
            for (int i = 0; i < ALPHA; i++) {
                if (next[now][i] == -1)
                    next[now][i] = next[fail[now]][i];
                else {
                    fail[next[now][i]] = next[fail[now]][i];
                    Q.push(next[now][i]);
                }
            }
        }
    }
    inline int ord(char s) { return s - 'a'; }
    void insert(const string &a) {
        int now = root;
        for (int i = 0; i < (int)a.size(); i++) {
            if (next[now][ord(a[i])] == -1)
                next[now][ord(a[i])] = create();
            now = next[now][ord(a[i])];
        }
        val[now]++;
    }
    int query(const string &a) {
        int now = root;
        int ret = 0;
        for (int i = 0; i < (int)a.size(); i++) {
            now = next[now][ord(a[i])];
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
