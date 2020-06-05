namespace Eulerian {
const int N = 1234567, M = 1234567;
int t, n, m, tot, cc, hd[N], nxt[M], to[M], bh[M], vis[M], in[N], out[N],
    ans[M];
void add(int x, int y, int id) {
  nxt[++tot] = hd[x];
  hd[x] = tot;
  to[tot] = y;
  bh[tot] = id;
  in[y]++;
  out[x]++;
}
void dfs(int x) {
  for (int i = hd[x]; i; i = hd[x]) {
    while (i && vis[abs(bh[i])])
      i = nxt[i];
    hd[x] = i;
    if (!i)
      break;
    vis[abs(bh[i])] = 1;
    dfs(to[i]), ans[++cc] = bh[i];
  }
}
 
void init() {
  memset(hd, 0, sizeof(hd));
  memset(nxt, 0, sizeof(nxt));
  memset(to, 0, sizeof(to));
  memset(bh, 0, sizeof(bh));
  memset(vis, 0, sizeof(vis));
  memset(in, 0, sizeof(in));
  memset(out, 0, sizeof(out));
  memset(ans, 0, sizeof(ans));
  t = 1;
  n = 0;
  m = 0;
  tot = 0;
  cc = 0;
}
bool solve() {
  for (int i = 1; i <= n; i++)
    if ((t == 1 && in[i] & 1)) {
      return false;
    }
  dfs(to[1]);
  if (cc < m)
    return false;
  else {
    path.clear();
    for (int i = cc; i >= 1; i--)
      path.push_back(ans[i]);
    return true;
  }
}
} // namespace Eulerian
