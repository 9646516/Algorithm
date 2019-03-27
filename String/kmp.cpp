#include<bits/stdc++.h>
using namespace std;
//find d in c
const int maxn=123465;
int c[maxn],d[maxn],kmp[maxn];
vector<int>ans;
int main() {
	cin>>c>>d; 
	int len1=strlen(c),len2=strlen(d);
	int i=0,j=kmp[0]=-1;
	while(i<len2) {
		while(j!=-1&&d[i]!=d[j])j=kmp[j];
		i++;
		j++;
		kmp[i]=d[i]==d[j]?kmp[j]:j;
	}
	i=j=0;
	while(i<len1) {
		while(j!=-1&&c[i]!=d[j])j=kmp[j];
		i++;
		j++;
		if(j>=len2) {
			ans.push_back(i-len2);
			j=kmp[j];
		}
	}
	sort(ans.begin(),ans.end());
	cout<<ans.size()<<endl;
	for(int i=0;i<(int)ans.size();i++)cout<<ans[i]<<(i==(int)ans.size()-1?'\n':' ');
	return 0;
}
