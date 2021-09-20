#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
int cnt = 0;
struct node {
    int l, r, val;
    int ch[2];
} tree[maxn * 20];
int root[maxn];
void build(int root, int l, int r) {
    tree[root].l = l;
    tree[root].r = r;
    if (l == r) {
        tree[root].val = 0;
        return;
    }
    int mid = (l + r) / 2;
    tree[root].ch[0] = cnt++;
    tree[root].ch[1] = cnt++;
    build(tree[root].ch[0], l, mid);
    build(tree[root].ch[1], mid + 1, r);
}
int update(int root, int idx, int val) {
    int ret = cnt++;
    tree[ret] = tree[root];
    if (tree[root].l == tree[root].r && tree[root].l == idx) {
        tree[ret].val += val;
        return ret;
    }
    int mid = (tree[root].l + tree[root].r) / 2;
    if (idx <= mid)
        tree[ret].ch[0] = update(tree[root].ch[0], idx, val);
    else
        tree[ret].ch[1] = update(tree[root].ch[1], idx, val);
    tree[ret].val = tree[tree[ret].ch[0]].val + tree[tree[ret].ch[1]].val;
    return ret;
}
int query(int root1,int root2, int val) {
    // cerr<<tree[root1].l <<' '<<tree[root1].r<<endl;
    if (tree[root1].l == tree[root1].r) {
        return tree[root1].l;
    }
    if (tree[tree[root2].ch[0]].val-tree[tree[root1].ch[0]].val>=val)
        return query(tree[root1].ch[0],tree[root2].ch[0],val);
    else
        return query(tree[root1].ch[1],tree[root2].ch[1],val-(tree[tree[root2].ch[0]].val-tree[tree[root1].ch[0]].val));
}
int main() {
#ifdef RINNE
    freopen("in", "r", stdin);
#endif
    int n, m, l, r, val;
    scanf("%d%d", &n, &m);
    root[0] = cnt++;
    build(root[0], 0, n-1);
    vector<int>V;
    static int a[maxn];
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        V.push_back(a[i]);
    }
    sort(V.begin(),V.end());
    V.erase(unique(V.begin(),V.end()),V.end());
    for(int i=1;i<=n;i++){
        root[i] = update(root[i - 1], lower_bound(V.begin(),V.end(),a[i])-V.begin(), 1);
    }
    while (m--) {
        scanf("%d%d%d", &l, &r, &val);
        printf("%d\n",V[query(root[l - 1], root[r], val)]);
    }
    return 0;
}
