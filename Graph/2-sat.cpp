#include <bits/stdc++.h>

#define REP(i,s,n) for(int i=(int)(s);i<(int)(n);i++)

using namespace std;
typedef long long int ll;
typedef vector<int> VI;
typedef vector<ll> VL;
typedef pair<int, int> PI;
class SCC {
	private:
		int n;
		int ncc;
		typedef std::vector<int> vi;
		std::vector<vi> g; // graph in adjacent list
		std::vector<vi> rg; // reverse graph
		vi vs;
		std::vector<bool> used;
		vi cmp;
	public:
		SCC(int n): n(n), ncc(-1), g(n), rg(n), vs(n), used(n), cmp(n) {}
		void add_edge(int from, int to) {
			g[from].push_back(to);
			rg[to].push_back(from);
		}
	private:
		void dfs(int v) {
			used[v] = true;
			for (int i = 0; i < g[v].size(); ++i) {
				if (!used[g[v][i]]) {
					dfs(g[v][i]);
				}
			}
			vs.push_back(v);
		}
		void rdfs(int v, int k) {
			used[v] = true;
			cmp[v] = k;
			for (int i = 0; i < rg[v].size(); ++i) {
				if (!used[rg[v][i]]) {
					rdfs(rg[v][i], k);
				}
			}
		}
	public:
		int scc() {
			std::fill(used.begin(), used.end(), 0);
			vs.clear();
			for (int v = 0; v < n; ++v) {
				if (!used[v]) {
					dfs(v);
				}
			}
			std::fill(used.begin(), used.end(), 0);
			int k = 0;
			for (int i = vs.size() - 1; i >= 0; --i) {
				if (!used[vs[i]]) {
					rdfs(vs[i], k++);
				}
			}
			return ncc = k;
		}
		std::vector<int> top_order() const {
			if (ncc == -1) assert(0);
			return cmp;
		}
		std::vector<std::vector<int> > dag() const {
			if (ncc == -1) {
				assert(0);
			}
			typedef std::set<int> si;
			std::vector<si> ret(ncc);
			for (int i = 0; i < g.size(); ++i) {
				for (int j = 0; j < g[i].size(); ++j) {
					int to = g[i][j];
					if (cmp[i] != cmp[to]) {
						assert (cmp[i] < cmp[to]);
						ret[cmp[i]].insert(cmp[to]);
					}
				}
			}
			std::vector<std::vector<int> > vret(ncc);
			for (int i = 0; i < ncc; ++i) {
				vret[i] = std::vector<int>(ret[i].begin(), ret[i].end());
			}
			return vret;
		}
		std::vector<std::vector<int> > rdag() const {
			if (ncc == -1) {
				assert(0);
			}
			typedef std::set<int> si;
			std::vector<si> ret(ncc);
			for (int i = 0; i < g.size(); ++i) {
				for (int j = 0; j < g[i].size(); ++j) {
					int to = g[i][j];
					if (cmp[i] != cmp[to]) {
						assert (cmp[i] < cmp[to]);
						ret[cmp[to]].insert(cmp[i]);
					}
				}
			}
			std::vector<std::vector<int> > vret(ncc);
			for (int i = 0; i < ncc; ++i) {
				vret[i] = std::vector<int>(ret[i].begin(), ret[i].end());
			}
			return vret;
		}
};
std::vector<int> two_sat(int n, const vector<pair<int, int> > &cons) {
	SCC scc(2 * n);
	for (int i = 0; i < cons.size(); ++i) {
		pair<int, int> c = cons[i];
		int x, y;
		if (c.first > 0) {
			x = c.first - 1 + n;
		} else {
			x = -c.first - 1;
		}
		if (c.second > 0) {
			y = c.second - 1;
		} else {
			y = -c.second - 1 + n;
		}
		scc.add_edge(x, y);
		scc.add_edge((y + n) % (2 * n), (x + n) % (2 * n));
	}
	scc.scc();
	std::vector<int> result(n);
	std::vector<int> top_ord = scc.top_order();
	REP(i, 0, n) {
		if (top_ord[i] == top_ord[i + n]) {
			return std::vector<int>();
		}
		result[i] = top_ord[i] > top_ord[i + n] ? 1 : 0;
	}
	return result;
}
int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n, m;
	cin >> n >> m;
	vector<PI> cons;
	REP(i, 0, m) {
		int a,b,c;
		cin>>a>>b>>c;
		cons.push_back(PI(b, a == 0 ? c : -c));
		cons.push_back(PI(-b, a == 0 ? -c : c));
	}
	VI res = two_sat(n, cons);
	cout << (res.size() == 0 ? "NO" : "YES") << endl;
}
