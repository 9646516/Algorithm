using ull = unsigned long long;
const long long MAX=5170427,MOD=1000000007;
bool used[MAX];
struct Hash {
	ull val;
	long long count;
} HashTable[MAX];
int searchHash(ull s) {
	ull tmp=s;
	tmp=(tmp%MAX+MAX)%MAX;
	while(used[tmp]&&HashTable[tmp].val!=s) {
		tmp++;
		tmp=tmp%MAX;
	}
	return tmp;
}
void insert(ull s,int k) {
	int pos=searchHash(s);
	HashTable[pos].val=s;
	HashTable[pos].count+=k;
	used[pos]=true;
}
