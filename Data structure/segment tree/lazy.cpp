#include<bits/stdc++.h>
using namespace std;
struct node {
	long long val;
	long long lazy;
	int l;
	int r;
} tree[8666666];
int n,q,a,b,c,d;
void build(int root,int l,int r) {
	tree[root].l=l;
	tree[root].r=r;
	tree[root].val=tree[root].lazy=0;
	if(l==r)return;
	int mid=(l+r)/2;
	build(root*2+1,l,mid);
	build(root*2+2,mid+1,r);
}
void change(int root,int l,int r,int val) {
	int op=tree[root].l;
	int ed=tree[root].r;
	if(op>ed)return;
	if(tree[root].lazy) {
		tree[root*2+1].val+=(tree[root*2+1].r-tree[root*2+1].l+1)*tree[root].lazy;
		tree[root*2+2].val+=(tree[root*2+2].r-tree[root*2+2].l+1)*tree[root].lazy;
		tree[root*2+1].lazy+=tree[root].lazy;
		tree[root*2+2].lazy+=tree[root].lazy;
		tree[root].lazy=0;
	}
	if(op==l&&ed==r) {
		tree[root].val+=(tree[root].r-tree[root].l+1)*val;
		tree[root].lazy+=val;
		return;
	}
	int mid=(op+ed)/2;
	if(r<=mid)change(root*2+1,l,r,val);
	else if(l>mid)change(root*2+2,l,r,val);
	else {
		change(root*2+1,l,mid,val);
		change(root*2+2,mid+1,r,val);
	}
	tree[root].val=tree[root*2+1].val+tree[root*2+2].val;
}
long long sum(int root,int l,int r) {
	int op=tree[root].l;
	int ed=tree[root].r;
	if(op>ed)return 0;
	if(tree[root].lazy) {
		tree[root*2+1].val+=(tree[root*2+1].r-tree[root*2+1].l+1)*tree[root].lazy;
		tree[root*2+2].val+=(tree[root*2+2].r-tree[root*2+2].l+1)*tree[root].lazy;
		tree[root*2+1].lazy+=tree[root].lazy;
		tree[root*2+2].lazy+=tree[root].lazy;
		tree[root].lazy=0;
	}
	if(op==l&&ed==r)return tree[root].val;
	int mid=(op+ed)/2;
	if(r<=mid)return sum(root*2+1,l,r);
	else if(l>mid)return sum(root*2+2,l,r);
	return sum(root*2+1,l,mid)+sum(root*2+2,mid+1,r);
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>q;
	build(0,1,n);
	while(q--) {
		cin>>a>>b>>c>>d;
		if(a)cout<<sum(0,b,c)<<endl;
		else change(0,b,c,d);
	}
	return 0;
}
