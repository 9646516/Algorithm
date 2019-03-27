#include<bits/stdc++.h>
using namespace std;
int main() {
	const int maxn=1e5+1;
	static char a[maxn],b[maxn];
	bitset<maxn>st[26],ans,tp;
	scanf("%s%s",a,b);
	int len1=strlen(a),len2=strlen(b);
	for(int i=0; i<len1; i++)st[a[i]-'a'][i]=1;
	for(int i=0; i<26; i++)tp|=st[i];
	ans.set();
	for(int i=0; i<len2; i++)ans&=((b[i]=='?'?tp:st[b[i]-'a'])>>i);
	int res=ans.count()-(ans>>len1).count();
	printf("%d\n",res);
	for(int i=ans._Find_first(); res--; i=ans._Find_next(i))printf("%d ",i);
	return 0;
}
