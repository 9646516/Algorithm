template <class T = ll> pair<vector<T>, vector<int>> dijkstra(const vector<vector<pair<int, int>>> &g, int s) {
    const int n = g.size();
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> Q;
    vector<T> dist(n, numeric_limits<T>::max());
    vector<int> from(n, -1);
    const auto add = [&](int v, T d, int f) {
        if (dist[v] > d) {
            dist[v] = d;
            from[v] = f;
            Q.emplace(d, v);
        }
    };
    add(s, 0, -1);
    while (!Q.empty()) {
        T d;
        int v;
        tie(d, v) = Q.top();
        Q.pop();
        if (dist[v] == d) {
            for (const auto &e : g[v]) {
                add(e.first, d + e.second, v);
            }
        }
    }
    return make_pair(dist, from);
}

template <class T = ll> pair<vector<T>, vector<int>> dijkstra2(const vector<vector<pair<int, int>>> &g, int s) {
    const int n = g.size();
    multiset<pair<T, int>> Q;
    vector<T> dist(n, numeric_limits<T>::max());
    vector<int> from(n, -1);
    const auto add = [&](int v, T d, int f) {
        if (dist[v] > d) {
            Q.erase(make_pair(dist[v], v));
            dist[v] = d;
            from[v] = f;
            Q.emplace(d, v);
        }
    };
    add(s, 0, -1);
    while (!Q.empty()) {
        T d;
        int v;
        tie(d, v) = *Q.begin();
        Q.erase(Q.begin());
        for (const auto &e : g[v]) {
            add(e.first, d + e.second, v);
        }
    }
    return make_pair(dist, from);
}
