#include<bits/stdc++.h>
using namespace std;
string in;
int kmp[100005],cas;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>cas;
	while(cas--) {
		int i=0,j=kmp[0]=-1,len;
		cin>>len>>in;
		while(i<len) {
			while(j!=-1&&in[i]!=in[j])j=kmp[j];
			i++;
			j++;
			kmp[i]=j;
		}
		if(!kmp[len])cout<<len<<endl<<in<<endl;
		else {
			int tp=len-kmp[len];
			cout<<tp<<endl<<in.substr(0,tp)<<endl;
		}
	}
	return 0;
}
