#include<bits/stdc++.h>
using namespace std;
struct node {
	long long val,maxx,minn;
	int l,r;
} tree[6666666];
void build(int root,int l,int r) {
	tree[root].l=l;
	tree[root].r=r;
	tree[root].val=tree[root].minn=tree[root].maxx=0;
	if(l==r)return;
	int mid=(l+r)/2;
	build(root*2+1,l,mid);
	build(root*2+2,mid+1,r);
}
void push_up(int root) {
	tree[root].val=tree[root*2+1].val+tree[root*2+2].val;
	tree[root].maxx=max(tree[root*2+1].maxx,tree[root*2+2].maxx);
	tree[root].minn=min(tree[root*2+1].minn,tree[root*2+2].minn);
}
void change(int root,int id,int val) {
	int op=tree[root].l;
	int ed=tree[root].r;
	if(op>ed)return;
	if(op==ed&&ed==id) {
		tree[root].val=tree[root].maxx=tree[root].minn=val;
		return;
	}
	int mid=(op+ed)/2;
	if(id<=mid)change(root*2+1,id,val);
	else change(root*2+2,id,val);
	push_up(root);
}
long long sum(int root,int l,int r) {
	int op=tree[root].l;
	int ed=tree[root].r;
	if(op>ed)return 0;
	if(op==l&&ed==r)return tree[root].val;
	int mid=(op+ed)/2;
	if(r<=mid)return sum(root*2+1,l,r);
	else if(l>mid)return sum(root*2+2,l,r);
	return sum(root*2+1,l,mid)+sum(root*2+2,mid+1,r);
}
long long maxx(int root,int l,int r) {
	int op=tree[root].l;
	int ed=tree[root].r;
	if(op>ed)return -1e18;
	if(op==l&&ed==r)return tree[root].maxx;
	int mid=(op+ed)/2;
	if(r<=mid)return maxx(root*2+1,l,r);
	else if(l>mid)return maxx(root*2+2,l,r);
	else return max(maxx(root*2+1,l,mid),maxx(root*2+2,mid+1,r));
}
long long minn(int root,int l,int r) {
	int op=tree[root].l;
	int ed=tree[root].r;
	if(op>ed)return 1e18;
	if(op==l&&ed==r)return tree[root].minn;
	int mid=(op+ed)/2;
	if(r<=mid)return minn(root*2+1,l,r);
	else if(l>mid)return minn(root*2+2,l,r);
	else return min(minn(root*2+1,l,mid),minn(root*2+2,mid+1,r));
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int n,q,a,b,c;
	cin>>n>>q;
	build(0,1,n);
	while(q--) {
		cin>>a>>b>>c;
		if(a)cout<<sum(0,b,c)-maxx(0,b,c)-minn(0,b,c)<<endl;
		else change(0,b,c);
	}
	return 0;
}
