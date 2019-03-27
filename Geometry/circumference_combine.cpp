#include<iostream>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;
struct node2 {
	int xl;
	int xr;
	int h;
	int tag;
	friend bool operator < (node2 a,node2 b) {
		return a.h<b.h;
	}
};
struct node {
	int seg;
	int val;
	int sum;
	int op;
	int ed;
	int l;
	int r;
} tree[8666666];
vector<int>v;
vector<node2>V;
int n,xl,yl,xr,yr,ans=0,last=0;
void build(int root,int l,int r) {
	tree[root].l=l;
	tree[root].r=r;
	tree[root].val=tree[root].sum=tree[root].seg=0;
	if(l==r)return;
	int mid=(l+r)/2;
	build(root*2+1,l,mid);
	build(root*2+2,mid+1,r);
}
void pushup(int root) {
	if(tree[root].val) {
		tree[root].sum=v[tree[root].r+1]-v[tree[root].l];
		tree[root].op=1;
		tree[root].ed=1;
		tree[root].seg=2;
	} else if(tree[root].r==tree[root].l)tree[root].sum=tree[root].seg=tree[root].op=tree[root].ed=0;
	else {
		tree[root].seg=tree[root*2+1].seg+tree[root*2+2].seg;
		if(tree[root*2+1].ed&&tree[root*2+2].op) tree[root].seg-=2;
		tree[root].sum=tree[root*2+1].sum+tree[root*2+2].sum;
		tree[root].op=tree[root*2+1].op;
		tree[root].ed=tree[root*2+2].ed;
	}
}
void change(int root,int l,int r,int val) {
	int op=tree[root].l;
	int ed=tree[root].r;
	if(op>ed)return;
	if(op==l&&ed==r) {
		tree[root].val+=val;
		pushup(root);
		return;
	}
	int mid=(op+ed)/2;
	if(r<=mid)change(root*2+1,l,r,val);
	else if(l>mid)change(root*2+2,l,r,val);
	else {
		change(root*2+1,l,mid,val);
		change(root*2+2,mid+1,r,val);
	}
	pushup(root);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n;
	for(int i=0; i<n; i++) {
		cin>>xl>>yl>>xr>>yr;
		V.push_back({xl,xr,yl,1});
		V.push_back({xl,xr,yr,-1});
		v.push_back(xl);
		v.push_back(xr);
	}
	sort(V.begin(),V.end());
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	build(0,0,v.size());
	for(int i=0; i<(int)V.size(); i++) {
		xl=lower_bound(v.begin(),v.end(),V[i].xl)-v.begin();
		xr=lower_bound(v.begin(),v.end(),V[i].xr)-v.begin()-1;
		change(0,xl,xr,V[i].tag);
		ans+=abs(last-tree[0].sum);
		last=tree[0].sum;
		if(i!=(int)V.size()-1)ans+=(V[i+1].h-V[i].h)*tree[0].seg;
	}
	cout<<ans<<endl;
	return 0;
}
