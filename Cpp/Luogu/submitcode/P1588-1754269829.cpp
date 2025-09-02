#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
int t,dis[maxn];
void bfs(){
	int x,y;
	memset(dis,-1,sizeof(dis));
	cin>>x>>y;
	queue<int>q;
	q.push(x);
	dis[x]=0;
	while(!q.empty()){
		int p=q.front();
		q.pop();
		if(p+1<maxn&&dis[p+1]==-1){
			q.push(p+1);
			dis[p+1]=dis[p]+1;
		}
		if(p-1>0&&dis[p-1]==-1){
			q.push(p-1);
			dis[p-1]=dis[p]+1;
		}
		if(p*2<maxn&&dis[p*2]==-1){
			q.push(p*2);
			dis[p*2]=dis[p]+1;
		}
		if(p==y){
			cout<<dis[y]<<endl;
			return;
		}
	}
}
int main(){
	cin>>t;
	while(t--){
		bfs();
	}
	return 0;
}