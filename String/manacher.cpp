#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5; 
int q,len,s[maxn],Ma[maxn*2+5],Mp[maxn*2+5];
void Manacher() {
	int l=0;
	Ma[l++]=-1;
	Ma[l++]=-2;
	for(int i=0; i<len; i++) {
		Ma[l++]=s[i];
		Ma[l++]=-2;
	}
	Ma[l]=0;
	int mx=0,id=0;
	for(int i=0; i<l; i++) {
		Mp[i]=mx>i?min(Mp[2*id-i],mx-i):1;
		while(Ma[i+Mp[i]]==Ma[i-Mp[i]])Mp[i]++;
		if(i+Mp[i]>mx) {
			mx=i+Mp[i];
			id=i;
		}
	}
}
int main() {
	scanf("%d",&q);
	while(q--) {
		cin>>len;
		for(int i=0;i<len;i++)	scanf("%d",&s[i]);
		Manacher();
		int ans=0;
		for(int i=0; i<2*len+2; i++)ans=max(ans,Mp[i]-1);
		printf("%d\n",ans);
	}
	return 0;
}
