template<long long MOD,long long seed,typename T>
struct HashString {
	vector<T>val,po;
	HashString(const string&a) {
		val.resize(a.size());
		val[0]=a[0];
		for(int i=1; i<(int)a.size(); i++) {
			val[i]=(1LL*val[i-1]*seed+a[i])%MOD;
		}
		po.resize(a.size());
		po[0]=1;
		for(int i=1; i<(int)a.size(); i++) {
			po[i]=1LL*po[i-1]*seed%MOD;
		}
	}
	long long get_hash(int l,int r) {
		long long R=val[r];
		long long L=l>0?1LL*val[l-1]*po[r-l+1]%MOD:0;
		return ((R-L)%MOD+MOD)%MOD;
	}
	void append(const string&a) {
		int tot=po.size();
		val.resize(tot+a.size());
		po.resize(tot+a.size());
		for(int i=0; i<(int)a.size(); i++) {
			int idx=i+tot;
			val[idx]=(1LL*val[idx-1]*seed+a[i])%MOD;
			po[idx]=1LL*po[idx-1]*seed%MOD;
		}
	}
	bool match(int L,int R,long long ps) {
		return get_hash(L,R)==ps;
	}
	static long long calc_hash(const string&a) {
		long long ret=0;
		for(auto i:a) {
			ret=(ret*seed+i)%MOD;
		}
		return ret;
	}
};
