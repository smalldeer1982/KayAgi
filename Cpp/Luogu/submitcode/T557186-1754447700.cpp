#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
int n,m,w[maxn],f[maxn];
int ans=2e9+5;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>w[i]; 
	}
	deque<int>q;
	for(int i=1;i<=n;i++){
		while(q.size()&&f[q.back()]>=f[i-1]){
			q.pop_back();
		}
		q.push_back(i-1);
		if(q.front()<i-m){
			q.pop_front();
		}
		f[i]=f[q.front()]+w[i];
		if(i>n-m){
			ans=min(ans,f[i]);
		}
	}
	cout<<ans;
	return 0;
}
