#include<iostream>
#include<queue>
#include<cstring>
using namespace std;
const int maxn=50*10000+5;
struct AC_Automation {
	int Next[maxn][30],Fail[maxn],End[maxn];
	int L,root;
	int create() {
		for(int i=0; i<26; i++)Next[L][i]=-1;
		End[L++]=0;
		return L-1;
	}
	void init() {
		L=0;
		root=create();
	}
	void insert(string a) {
		int len=a.size();
		int now=root;
		for(int i=0; i<len; i++) {
			if(Next[now][a[i]-'a']==-1)	Next[now][a[i]-'a']=create();
			now=Next[now][a[i]-'a'];
		}
		End[now]++;
	}
	void build() {
		queue<int>ans;
		Fail[root]=root;
		for(int i=0; i<26; i++) {
			if(Next[root][i]==-1)Next[root][i]=root;
			else {
				Fail[Next[root][i]]=root;
				ans.push(Next[root][i]);
			}
		}
		while(!ans.empty()) {
			int now = ans.front();
			ans.pop();
			for(int i=0; i<26; i++) {
				if(Next[now][i]==-1)Next[now][i] = Next[Fail[now]][i];
				else {
					Fail[Next[now][i]]=Next[Fail[now]][i];
					ans.push(Next[now][i]);
				}
			}
		}
	}
	int query(string a) {
		int now = root;
		int res = 0;
		int len = a.size();
		for(int i = 0; i < len; i++) {
			now = Next[now][a[i]-'a'];
			int temp = now;
			while(temp != root) {
				res += End[temp];
		//		End[temp] = 0;
				temp = Fail[temp];
			}
		}
		return res;
	}
} AC;
int q,n;
string a,b;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>q;
	while(q--) {
		cin>>a>>n;
		AC.init();
		getline(cin,b);
		while(n--) {
			getline(cin,b);
			AC.insert(b);
		}
		AC.build();
		cout<<AC.query(a)<<endl;
	}
	return 0;
}
