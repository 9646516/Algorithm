// 无向图,欧拉路径 除了终点和起点为奇点,其它点的度数均为偶点
// 无向图,欧拉回路 均为偶点
// 有向图,欧拉路径 起点出度比入度大1，终点入度比出度大1,其它点入度=出度
// 有向图,欧拉回路 所有点入度=出度

//欧拉路径 输出点
template <int N> struct Hierholzer {
    vector<multiset<int>> V;
    vector<int> deg, res;
    Hierholzer() {
        V.resize(N + 5);
        deg.resize(N + 5);
    }
    void dfs(int x) {
        while (!V[x].empty()) {
            int u = *V[x].begin();
            V[x].erase(V[x].begin());
            V[u].erase(V[u].lower_bound(x));
            dfs(u);
        }
        res.emplace_back(x);
    }
    void add(int a, int b) {
        V[a].insert(b);
        V[b].insert(a);
        deg[a]++;
        deg[b]++;
    }
    void init() {
        fill(deg.begin(), deg.end(), 0);
        res.clear();
        for (int i = 0; i < N + 5; i++) {
            V[i].clear();
        }
    }
    bool solve() {
        vector<int> odd;
        for (int i = 1; i <= N; i++) {
            if (deg[i] & 1) {
                odd.emplace_back(i);
            }
        }
        if (odd.size() != 0 and odd.size() != 2) {
            return false;
        }
        dfs(odd.empty() ? 1 : odd.front());
        reverse(res.begin(), res.end());
        return true;
    }
};

//欧拉通路 输出边
template <int N> struct Hierholzer {
    vector<multiset<pair<int, int>>> V;
    vector<int> deg, res;
    Hierholzer() {
        V.resize(N + 5);
        deg.resize(N + 5);
    }
    void init() {
        fill(deg.begin(), deg.end(), 0);
        res.clear();
        for (int i = 0; i < N + 5; i++) {
            V[i].clear();
        }
    }
    void dfs(int x) {
        while (!V[x].empty()) {
            pair<int, int> u = *V[x].begin();
            V[x].erase(V[x].begin());
            V[u.second].erase(V[u.second].lower_bound(make_pair(u.first, x)));
            dfs(u.second);
            res.push_back(u.first);
        }
    }
    void add(int a, int b, int c) {
        V[a].insert(make_pair(c, b));
        V[b].insert(make_pair(c, a));
        deg[a]++;
        deg[b]++;
    }
    bool solve(int root) {
        vector<int> odd;
        for (int i = 1; i <= N; i++) {
            if (deg[i] & 1) {
                odd.push_back(i);
            }
        }
        if (odd.size() != 0) {
            return false;
        } else {
            dfs(root);
            reverse(res.begin(), res.end());
            return true;
        }
    }
};
