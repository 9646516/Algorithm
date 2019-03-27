#include<bits/stdc++.h>
using namespace std;
template<typename base_type, base_type _MOD>
struct IntMod {
	static const int INVERSE_CACHE_SIZE = (1 << 20);
	static base_type MOD;
	static void set_mod(base_type new_mod) {
		MOD = new_mod;
	}
	base_type n;
	IntMod(long long d = 0) {
		n = (d >= 0 ? d % MOD : (d % MOD + MOD) % MOD);
	}
	virtual ~IntMod() = default;
	IntMod operator-() const {
		return build(n == 0 ? 0 : MOD - n);
	}
	IntMod& operator+=(IntMod a) {
		n = (n >= MOD - a.n ? n - MOD + a.n : n + a.n);
		return *this;
	}
	IntMod& operator-=(IntMod a) {
		n = (n >= a.n) ? n - a.n : n - a.n + MOD;
		return *this;
	}
	IntMod& operator*=(IntMod a) {
		*this = *this * a;
		return *this;
	}
	IntMod& operator/=(IntMod a) {
		*this = *this / a;
		return *this;
	}
	static IntMod build(base_type n) {
		IntMod L;
		L.n = n;
		return L;
	}
	static base_type inverse_cache[INVERSE_CACHE_SIZE];
	static bool inverse_cache_ready;
	friend IntMod inverse(IntMod n) {
		return build(inverse_internal(n.n));
	}
	static base_type inverse_internal(base_type n) {
		if (!inverse_cache_ready) {
			inverse_cache_ready=true;
			inverse_cache[0] = 0;
			inverse_cache[1] = 1;
			for (int n = 2; n < INVERSE_CACHE_SIZE; ++n) inverse_cache[n] = (MOD - (base_type)((long long)inverse_cache[MOD % n] * (MOD / n) % MOD));
		}
		return n < INVERSE_CACHE_SIZE ? inverse_cache[n] : MOD - (base_type)((long long)inverse_internal(MOD % n) * (MOD / n) % MOD);
	}
	friend bool operator==(IntMod a, IntMod b) {
		return a.n == b.n;
	}
	friend bool operator!=(IntMod a, IntMod b) {
		return a.n != b.n;
	}
	friend IntMod operator+(IntMod a, IntMod b) {
		return build(a.n >= MOD - b.n ? a.n - MOD + b.n : a.n + b.n);
	}
	friend IntMod operator-(IntMod a, IntMod b) {
		return build(a.n >= b.n ? a.n - b.n : a.n - b.n + MOD);
	}
	friend IntMod operator*(IntMod a, IntMod b) {
		return build(static_cast<base_type>(static_cast<long long>(a.n) * b.n % MOD));
	}
	friend IntMod operator/(IntMod a, IntMod b) {
		return a * inverse(b);
	}
	friend IntMod pow(IntMod p, long long e) {
		if (e <= 0) return IntMod(1);
		IntMod L = IntMod(1);
		while(e) {
			if(e&1)L*=p;
			p*=p;
			e>>=1;
		}
		return L;
	}
	friend ostream&operator<<(ostream&os,const IntMod&p) {
		os<<p.n;
		return os;
	}
	friend istream&operator>>(istream&is,IntMod&p) {
		is>>p.n;
		return is;
	}
};
template<typename base_type, base_type _MOD> base_type IntMod<base_type, _MOD>::inverse_cache[INVERSE_CACHE_SIZE];
template<typename base_type, base_type _MOD> bool IntMod<base_type, _MOD>::inverse_cache_ready;
template<typename base_type, base_type _MOD> base_type IntMod<base_type, _MOD>::MOD = _MOD;
const long long MOD=1e9+7;
using Int=IntMod<int,MOD>;
const int maxn=1e5+555;
int n,q,r,p;
vector<int>V[maxn];
int val[maxn],fa[maxn],dep[maxn],sum[maxn],son[maxn],idx[maxn],top[maxn],raw[maxn];
void dfs1(int now,int pre,int d) {
	fa[now]=pre;
	dep[now]=d;
	sum[now]=1;
	for(int i:V[now]) {
		if(i==pre)continue;
		dfs1(i,now,d+1);
		sum[now]+=sum[i];
		if(son[now]==-1||sum[son[now]]<sum[i])son[now]=i;
	}
}
void dfs2(int now,int pre,int op,int&dfn) {
	top[now]=op;
	idx[now]=dfn;
	raw[dfn]=now;
	dfn++;
	if(son[now]==-1)return;
	dfs2(son[now],now,op,dfn);
	for(int i:V[now]) {
		if(i==pre||i==son[now])continue;
		dfs2(i,now,i,dfn);
	}
}
namespace Segment_tree {
	struct node {
		int l,r;
		Int val,lazy;
	} tree[maxn*8];
	void push_down(int root) {
		if(tree[root].lazy!=0) {
			tree[root*2+1].val+=(tree[root*2+1].r-tree[root*2+1].l+1)*tree[root].lazy;
			tree[root*2+2].val+=(tree[root*2+2].r-tree[root*2+2].l+1)*tree[root].lazy;
			tree[root*2+1].lazy+=tree[root].lazy;
			tree[root*2+2].lazy+=tree[root].lazy;
			tree[root].lazy=0;
		}
	}
	void push_up(int root) {
		tree[root].val=tree[root*2+1].val+tree[root*2+2].val;
	}
	void build(int root,int l,int r) {
		tree[root].l=l;
		tree[root].r=r;
		tree[root].lazy=0;
		if(l==r) {
			tree[root].val=val[raw[l]];
			return;
		}
		int mid=(l+r)/2;
		build(root*2+1,l,mid);
		build(root*2+2,mid+1,r);
		push_up(root);
	}
	void change(int root,int l,int r,int val) {
		int L=tree[root].l,R=tree[root].r;
		int mid=(L+R)/2;
		push_down(root);
		if(L==l&&R==r) {
			tree[root].val+=(Int)val*(r-l+1);
			tree[root].lazy+=val;
			return;
		}
		if(mid>=r)change(root*2+1,l,r,val);
		else if(mid<l)change(root*2+2,l,r,val);
		else {
			change(root*2+1,l,mid,val);
			change(root*2+2,mid+1,r,val);
		}
		push_up(root);
	}
	Int ask(int root,int l,int r) {
		int L=tree[root].l,R=tree[root].r;
		int mid=(L+R)/2;
		push_down(root);
		if(L==l&&R==r)return tree[root].val;
		if(mid>=r)return ask(root*2+1,l,r);
		else if(mid<l)return ask(root*2+2,l,r);
		else return ask(root*2+1,l,mid)+ask(root*2+2,mid+1,r);
	}
}
void add(int x,int y,int z) {
	int fa1=top[x],fa2=top[y];
	while(fa1!=fa2) {
		if(dep[fa1]<dep[fa2]) {
			swap(fa1,fa2);
			swap(x,y);
		}
		Segment_tree::change(0,idx[fa1],idx[x],z);
		x=fa[fa1];
		fa1=top[x];
	}
	if(idx[x]>idx[y])swap(x,y);
	Segment_tree::change(0,idx[x],idx[y],z);
}
void add(int x,int z) {
	Segment_tree::change(0,idx[x],idx[x]+sum[x]-1,z);
}
int query(int x,int y) {
	Int ret=0;
	int fa1=top[x],fa2=top[y];
	while(fa1!=fa2) {
		if(dep[fa1]<dep[fa2]) {
			swap(fa1,fa2);
			swap(x,y);
		}
		ret+=Segment_tree::ask(0,idx[fa1],idx[x]);
		x=fa[fa1];
		fa1=top[x];
	}
	if(idx[x]>idx[y])swap(x,y);
	ret+=Segment_tree::ask(0,idx[x],idx[y]);
	return ret.n;
}
int query(int x) {
	return Segment_tree::ask(0,idx[x],idx[x]+sum[x]-1).n;
}
int main() {
	scanf("%d%d%d%d",&n,&q,&r,&p);
	for(int i=1; i<=n; i++)scanf("%d",&val[i]);
	int x,y,z,op=1;
	for(int i=1; i<n; i++) {
		scanf("%d%d",&x,&y);
		V[x].push_back(y);
		V[y].push_back(x);
	}
	Int::set_mod(p);
	memset(son,-1,sizeof(int)*(n+5));
	dfs1(r,-1,0);
	dfs2(r,-1,r,op);
	Segment_tree::build(0,1,n);
	while(q--) {
		scanf("%d",&op);
		if(op==1) {
			scanf("%d%d%d",&x,&y,&z);
			add(x,y,z);
		} else if(op==2) {
			scanf("%d%d",&x,&y);
			printf("%d\n",query(x,y));
		} else if(op==3) {
			scanf("%d%d",&x,&z);
			add(x,z);
		} else {
			scanf("%d",&x);
			printf("%d\n",query(x));
		}
	}
	return 0;
}
