#include<bits/stdc++.h>
using namespace std;
const int maxn=1e6+5;
int n;
string s;
int ch[maxn][30],idx=0;
int cnt[maxn],ne[maxn];
void insert(string x){
	int p=0;
	for(int i=0;i<x.size();i++){
		int j=x[i]-'a';
		if(!ch[p][j]){
			ch[p][j]=++idx;
		}
		p=ch[p][j];
	}
	cnt[p]+=1;
}
void build(){
	queue<int>q;
	for(int i=0;i<26;i++){
		if(ch[0][i]){
			q.push(ch[0][i]);
		}
	}
	while(!q.empty()){
		int u=q.front();
		q.pop();
		for(int i=0;i<26;i++){
			int v=ch[u][i];
			if(v){
				ne[v]=ch[ne[u]][i];
				q.push(v);
			}
			else{
				ch[u][i]=ch[ne[u]][i];
			}
		}
	}
}
int query(string x){
	int ans=0,sum=0;
	for(int k=0;k<x.size();k++){
		sum=ch[sum][x[k]-'a'];
		for(int j=sum;j&&~cnt[j];j=ne[j]){
			ans+=cnt[j];
			cnt[j]=-1;
		}
	}
	return ans;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>s;
		insert(s);
	}
	build();
	cin>>s;
	cout<<query(s);
	return 0;
}