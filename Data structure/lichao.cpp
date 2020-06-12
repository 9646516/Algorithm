template<typename V> struct LeChaoTree {
	static const V inf=3LL<<60;
	const ll range=1<<20;
	const bool cmptype=true; //true:max false:min
	struct node {
		node(V a=0,V b=-inf) : A(a),B(b){ le=ri=NULL;}
		V val(ll x) { return A*x+B;}
		V A,B;  // Ax+B
		node *le, *ri;
	};
	
	node* root;
	LeChaoTree() { root=new node(0,-inf);}
	
	void add(node* n, V a,V b,ll L,ll R) {
		ll M=(L+R)/2;
		
		bool lef=(n->val(L) > a*L+b);
		bool mid=(n->val(M) > a*M+b);
		bool ri=(n->val(R) > a*R+b);
		
		if(lef&&ri) return;
		if(!lef&&(!ri || R-L==1)) {
			n->A=a;
			n->B=b;
			return;
		}
		
		if(R-L==1) return;
		if(!n->ri) n->ri=new node();
		if(!n->le) n->le=new node();
		add(n->ri,a,b,M,R);
		add(n->le,a,b,L,M);
	}
	
	void add(V a,V b) { 
		if(!cmptype) a=-a,b=-b;
		add(root,a,b,0,range);
	}
	
	V query(ll x) {
		V ret=-inf;
		node* cur=root;
		ll L=0, R=range;
		while(cur) {
			ret=max(ret,cur->val(x));
			ll m=(L+R)/2;
			if(x<m) cur=cur->le, R=m;
			else cur=cur->ri, L=m;
			
		}
		
		if(!cmptype) ret=-ret;
		return ret;
	}
};
