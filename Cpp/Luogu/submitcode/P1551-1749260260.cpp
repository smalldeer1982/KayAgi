#include<bits/stdc++.h>
using namespace std;
int n,m,p;
int fa[5005];
void init(){
	for(int i=1;i<=5000;i++){
		fa[i]=i;
	}
}
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int x,int y){
	int fx,fy;
	fx=find(x);
	fy=find(y);
	if(fx!=fy){
		fa[fy]=fx;
	}
}
 main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	init();
	cin>>n>>m>>p;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		merge(u,v);
	}
	while(p--){
		int u,v;
		cin>>u>>v;
		if(find(u)==find(v)){
			cout<<"Yes"<<'\n';
		}
		else{
			cout<<"No"<<'\n';
		}
	}
	return 0;
} 