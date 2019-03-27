#include<bits/stdc++.h>
using namespace std;
char a[123465];
unsigned long long hashs[123465],seed=163,power[123456];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>(a+1);
	int len=strlen(a+1),cas,L,R;
	power[0]=1;
	for(int i=1;i<=len;i++)power[i]=power[i-1]*seed;
	for(int i=1; i<=len; i++)hashs[i]=hashs[i-1]*seed+a[i]-'a';
	cin>>cas;
	while(cas--){
		cin>>L>>R;
		cout<<hashs[R]-hashs[L-1]*power[R-L+1]<<endl;
	}
	return 0;
}
